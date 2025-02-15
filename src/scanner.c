#include "tree_sitter/parser.h"
#include "tree_sitter/alloc.h"
#include "tree_sitter/array.h"

enum TokenType {
  TEXT,
  SPACE,
  STAR,
  UNDERSCORE,
  HASH,
  IDENT,
  INT,
  RAW_DELIM,
  RAW_CONTENT,
};

enum LexMode {
  MARKUP,
  CODE,
  MATH,
  RAW,
  RAW_TAIL,
};

typedef struct {
  int32_t last_symbol;
  uint8_t raw_level;
} Scanner ;

void *tree_sitter_typst_external_scanner_create() {
  Scanner *self = (Scanner*)malloc(sizeof(Scanner));
  self->last_symbol = 0;
  self->raw_level = 0;
  return self;
}

void tree_sitter_typst_external_scanner_destroy(void *payload) {
  free(payload);
}

unsigned tree_sitter_typst_external_scanner_serialize(
  void *payload,
  char *buffer
) {
  Scanner *self = payload;
  unsigned count = 0;

  *((int32_t*)(buffer + count)) = self->last_symbol;
  count += sizeof(int32_t);

  *((uint8_t*)(buffer + count)) = self->raw_level;
  count += sizeof(uint8_t);

  return count;
}

void tree_sitter_typst_external_scanner_deserialize(
  void *payload,
  const char *buffer,
  unsigned length
) {
  Scanner *self = payload;
  unsigned count = 0;
  if (length > 0) {
    self->last_symbol = *((int32_t*)(buffer + count));
    count += sizeof(int32_t);

    self->raw_level = *((uint8_t*)(buffer + count));
    count += sizeof(uint8_t);

    if (count != length) {
      printf("mismatched lengths when deserializing\n");
      exit(1);
    }
  }
  else {
    self->last_symbol = 0;
    self->raw_level = 0;
  }
}

static int32_t scanner_peek(Scanner *self, TSLexer *lexer) {
  if (lexer->eof(lexer)) {
    return 0;
  }
  return lexer->lookahead;
}

static int32_t scanner_visit(Scanner *self, TSLexer *lexer) {
  if (lexer->eof(lexer)) {
    return 0;
  }
  int32_t symbol = lexer->lookahead;
  self->last_symbol = symbol;
  lexer->advance(lexer, false);
  return symbol;
}

static int32_t scanner_advance(Scanner *self, TSLexer *lexer) {
  if (lexer->eof(lexer)) {
    return 0;
  }
  int32_t symbol = lexer->lookahead;
  self->last_symbol = symbol;
  lexer->advance(lexer, false);
  lexer->mark_end(lexer);
  return symbol;
}

static bool is_text(int32_t c) {
  switch (c) {
    case ' ':
    case '*':
    case '_':
      return false;
    default:
      return true;
  }
}

static bool is_new_line(int32_t character) {
  switch (character) {
    case '\n':
    case '\r':
    case 11:
    case 12:
    case 85:
    case 2028:
    case 2029:
      return true;
    default:
      return false;
  }
}

static bool is_whitespace(int32_t character) {
  // TODO: placeholder implementation
  // true implementation if rust char::is_whitespace
  switch (character) {
    case ' ':
    case '\t':
      return true;
    default:
      return false;
  }
}

static bool is_space(int32_t character, enum LexMode lex_mode) {
  switch (lex_mode) {
    case MARKUP:
      switch (character) {
        case ' ':
        case '\t':
          return true;
        default:
          return is_new_line(character);
      }
    default:
      return is_whitespace(character);
  }
}

// https://doc.rust-lang.org/src/core/char/methods.rs.html#906
static bool is_alphanumeric(int32_t character) {
  // TODO: placeholder implementation
  // true implementation is rust char::is_alphanumeric
  return character >= 'a' && character <= 'z' || character >= '0' && character <= '9';
}

static bool is_wordy(int32_t character) {
  // TODO: placeholder implementation
  // true implementation excludes scirpts Han Hiragana Katakana Hangul
  return character != 0 && is_alphanumeric(character);
}


// https://github.com/typst/typst/blob/e4f8e57/crates/typst-syntax/src/lexer.rs#L139
static bool self_whitespace(Scanner *self, TSLexer *lexer, enum LexMode lex_mode, int32_t c) {
  while (scanner_peek(self, lexer) != 0 && is_space(scanner_peek(self, lexer), lex_mode)) {
    scanner_advance(self, lexer);
  }
  lexer->result_symbol = SPACE;
  return true;
}

// https://github.com/typst/typst/blob/e4f8e57/crates/typst-syntax/src/lexer.rs#L514
static bool self_text(Scanner *self, TSLexer *lexer) {
  lexer->mark_end(lexer);
  lexer->result_symbol = TEXT;
  scanner_advance(self, lexer);
  while (scanner_peek(self, lexer) != 0) {
    switch (scanner_peek(self, lexer)) {
      case ' ': {
        scanner_visit(self, lexer);
        int32_t next = scanner_peek(self, lexer);
        if (next != 0 && is_alphanumeric(next)) {
          break;
        }
        else {
          return true;
        }
      }
      case '\t':
      case '\n':
      case '\x0b':
      case '\x0c':
      case '\r':
      case '*':
      case '_':
      case '#':
      case '`':
        return true; 
      default:
        break;
    }
    lexer->advance(lexer, false);
    lexer->mark_end(lexer);
  }
  return true;
}

// https://github.com/typst/typst/blob/e4f8e57/crates/typst-syntax/src/lexer.rs#L193
static bool self_markup(Scanner *self, TSLexer *lexer, int32_t c, int32_t l) {
  switch (c) {
    case '#':
      lexer->mark_end(lexer);
      lexer->result_symbol = HASH;
      return true;
    case '*': {
      bool last_is_wordy = is_wordy(l);
      bool next_is_wordy = is_wordy(scanner_peek(self, lexer));
      // printf("check star in word %b %b\n", last_is_wordy, next_is_wordy);
      if (!(last_is_wordy && next_is_wordy)) {
        lexer->mark_end(lexer);
        lexer->result_symbol = STAR;
        return true;
      }
      break;
    }
    case '_': {
      bool last_is_wordy = is_wordy(l);
      bool next_is_wordy = is_wordy(scanner_peek(self, lexer));
      if (!(last_is_wordy && next_is_wordy)) {
        lexer->mark_end(lexer);
        lexer->result_symbol = UNDERSCORE;
        return true;
      }
      break;
    }
    case '`': {
      uint8_t level = 1;
      lexer->mark_end(lexer);
      while (scanner_peek(self, lexer) == '`') {
        level += 1;
        scanner_visit(self, lexer);
      }
      lexer->result_symbol = RAW_DELIM;
      if (level == 2) {
        self->raw_level = 1;
        return true;
      }
      else {
        lexer->mark_end(lexer);
        self->raw_level = level;
        return true;
      }
    }
    default:
      break;
  }
  return self_text(self, lexer);
}


static bool is_id_start(int32_t c) {
  return c >= 'a' && c <= 'z';
}


static bool is_id_continue(int32_t c) {
  return c >= 'a' && c <= 'z';
}


static bool self_ident(Scanner *self, TSLexer *lexer) {
  while (is_id_continue(scanner_peek(self, lexer))) {
    scanner_advance(self, lexer);
  }
  lexer->result_symbol = IDENT;
  return true;
}


static bool self_number(Scanner *self, TSLexer *lexer, int32_t c) {
  while (c >= '0' && c <= '9') {
    scanner_advance(self, lexer);
    c = scanner_peek(self, lexer);
  }
  lexer->result_symbol = INT;
  return true;
}

static bool self_code(Scanner *self, TSLexer *lexer, int32_t c) {
  lexer->mark_end(lexer);
  if (is_id_start(c)) {
    return self_ident(self, lexer);
  }
  if (c >= '0' && c <= '9') {
    return self_number(self, lexer, c);
  }
  return false;
}


static bool self_raw(Scanner *self, TSLexer *lexer, int32_t c) {
  uint8_t level = 0;
  if (c == '`') {
    level += 1;
  }
  while (level < self->raw_level && c != 0) {
    c = scanner_visit(self, lexer);
    if (c == '`') {
      level += 1;
    }
    else {
      level = 0;
      lexer->mark_end(lexer);
    }
  }
  lexer->result_symbol = RAW_CONTENT;
  return true;
}


static bool self_raw_tail(Scanner *self, TSLexer *lexer, int32_t c) {
  lexer->mark_end(lexer);
  if (c != '`') {
    printf("expecting raw delim\n");
    exit(1);
  }
  uint8_t level = self->raw_level - 1;
  while (level > 0) {
    c = scanner_advance(self, lexer);
    if (c != '`') {
      printf("expecting raw delim\n");
      exit(1);
    }
    level -= 1;
  }
  lexer->result_symbol = RAW_DELIM;
  return true;
}


bool tree_sitter_typst_external_scanner_scan(
  void *payload,
  TSLexer *lexer,
  const bool *valid_symbols
) {
  Scanner *self = payload;
  lexer->mark_end(lexer);
  int32_t l = self->last_symbol;
  int32_t c = scanner_visit(self, lexer);
  if (c != 0) {
    enum LexMode lex_mode;
    if (valid_symbols[TEXT]) {
      lex_mode = MARKUP;
    }
    else if (valid_symbols[IDENT]) {
      lex_mode = CODE;
    }
    else if (valid_symbols[RAW_CONTENT]) {
      lex_mode = RAW;
    }
    else if (valid_symbols[RAW_DELIM]) {
      lex_mode = RAW_TAIL;
    }
    else {
      printf("could not determine lexing mode\n");
      exit(1);
    }
    // printf("lex_mode = %d\n", lex_mode);
    
    if (lex_mode != RAW && lex_mode != RAW_TAIL && is_space(c, lex_mode)) {
      lexer->mark_end(lexer);
      return self_whitespace(self, lexer, lex_mode, c);
    }
    switch (lex_mode) {
      case MARKUP:
        return self_markup(self, lexer, c, l);
      case CODE:
        return self_code(self, lexer, c);
      case RAW:
        return self_raw(self, lexer, c);
      case RAW_TAIL:
        return self_raw_tail(self, lexer, c);
      case MATH:
        return false;
    }

  }
  return false;
}
