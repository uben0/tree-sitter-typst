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
};

enum LexMode {
  MARKUP,
  CODE,
  MATH,
};

typedef struct {
  int32_t last_symbol;
} Scanner ;

void *tree_sitter_typst_external_scanner_create() {
  Scanner *self = (Scanner*)malloc(sizeof(Scanner));
  self->last_symbol = 0;
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
  *((int32_t*)buffer) = self->last_symbol;
  return sizeof(int32_t);
}

void tree_sitter_typst_external_scanner_deserialize(
  void *payload,
  const char *buffer,
  unsigned length
) {
  Scanner *self = payload;
  if (length == sizeof(int32_t)) {
    self->last_symbol = *((int32_t*)buffer);
  }
  else {
    self->last_symbol = 0;
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
      lexer->result_symbol = HASH;
      return true;
    case '*': {
      bool last_is_wordy = is_wordy(l);
      bool next_is_wordy = is_wordy(scanner_peek(self, lexer));
      if (!(last_is_wordy && next_is_wordy)) {
        lexer->result_symbol = STAR;
        return true;
      }
    }
    case '_': {
      bool last_is_wordy = is_wordy(l);
      bool next_is_wordy = is_wordy(scanner_peek(self, lexer));
      if (!(last_is_wordy && next_is_wordy)) {
        lexer->result_symbol = UNDERSCORE;
        return true;
      }
    }
    default:
      return self_text(self, lexer);
  }
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
  if (is_id_start(c)) {
    return self_ident(self, lexer);
  }
  if (c >= '0' && c <= '9') {
    return self_number(self, lexer, c);
  }
  return false;
}


bool tree_sitter_typst_external_scanner_scan(
  void *payload,
  TSLexer *lexer,
  const bool *valid_symbols
) {
  Scanner *self = payload;
  lexer->mark_end(lexer);
  int32_t l = self->last_symbol;
  int32_t c = scanner_advance(self, lexer);
  if (c != 0) {
    enum LexMode lex_mode;
    if (valid_symbols[TEXT]) {
      lex_mode = MARKUP;
    }
    else if (valid_symbols[IDENT]) {
      lex_mode = CODE;
    }
    else {
      printf("could not determine lexing mode\n");
      exit(1);
    }
    
    if (is_space(c, lex_mode)) {
      return self_whitespace(self, lexer, lex_mode, c);
    }
    switch (lex_mode) {
      case MARKUP:
        return self_markup(self, lexer, c, l);
      case CODE:
        return self_code(self, lexer, c);
      case MATH:
        return false;
    }

  }
  return false;
}
