#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 21
#define LARGE_STATE_COUNT 10
#define SYMBOL_COUNT 17
#define ALIAS_COUNT 0
#define TOKEN_COUNT 10
#define EXTERNAL_TOKEN_COUNT 9
#define FIELD_COUNT 0
#define MAX_ALIAS_SEQUENCE_LENGTH 3
#define PRODUCTION_ID_COUNT 1

enum ts_symbol_identifiers {
  sym_text = 1,
  sym_space = 2,
  sym_star = 3,
  sym_underscore = 4,
  sym_hash = 5,
  sym_ident = 6,
  sym_int = 7,
  sym_raw_delim = 8,
  sym_raw_content = 9,
  sym_source_file = 10,
  sym_markup = 11,
  sym_strong = 12,
  sym_emph = 13,
  sym_raw = 14,
  sym__expr = 15,
  aux_sym_markup_repeat1 = 16,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym_text] = "text",
  [sym_space] = "space",
  [sym_star] = "star",
  [sym_underscore] = "underscore",
  [sym_hash] = "hash",
  [sym_ident] = "ident",
  [sym_int] = "int",
  [sym_raw_delim] = "raw_delim",
  [sym_raw_content] = "text",
  [sym_source_file] = "source_file",
  [sym_markup] = "markup",
  [sym_strong] = "strong",
  [sym_emph] = "emph",
  [sym_raw] = "raw",
  [sym__expr] = "_expr",
  [aux_sym_markup_repeat1] = "markup_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [sym_text] = sym_text,
  [sym_space] = sym_space,
  [sym_star] = sym_star,
  [sym_underscore] = sym_underscore,
  [sym_hash] = sym_hash,
  [sym_ident] = sym_ident,
  [sym_int] = sym_int,
  [sym_raw_delim] = sym_raw_delim,
  [sym_raw_content] = sym_text,
  [sym_source_file] = sym_source_file,
  [sym_markup] = sym_markup,
  [sym_strong] = sym_strong,
  [sym_emph] = sym_emph,
  [sym_raw] = sym_raw,
  [sym__expr] = sym__expr,
  [aux_sym_markup_repeat1] = aux_sym_markup_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [sym_text] = {
    .visible = true,
    .named = true,
  },
  [sym_space] = {
    .visible = true,
    .named = true,
  },
  [sym_star] = {
    .visible = true,
    .named = true,
  },
  [sym_underscore] = {
    .visible = true,
    .named = true,
  },
  [sym_hash] = {
    .visible = true,
    .named = true,
  },
  [sym_ident] = {
    .visible = true,
    .named = true,
  },
  [sym_int] = {
    .visible = true,
    .named = true,
  },
  [sym_raw_delim] = {
    .visible = true,
    .named = true,
  },
  [sym_raw_content] = {
    .visible = true,
    .named = true,
  },
  [sym_source_file] = {
    .visible = true,
    .named = true,
  },
  [sym_markup] = {
    .visible = true,
    .named = true,
  },
  [sym_strong] = {
    .visible = true,
    .named = true,
  },
  [sym_emph] = {
    .visible = true,
    .named = true,
  },
  [sym_raw] = {
    .visible = true,
    .named = true,
  },
  [sym__expr] = {
    .visible = false,
    .named = true,
  },
  [aux_sym_markup_repeat1] = {
    .visible = false,
    .named = false,
  },
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static const uint16_t ts_non_terminal_alias_map[] = {
  0,
};

static const TSStateId ts_primary_state_ids[STATE_COUNT] = {
  [0] = 0,
  [1] = 1,
  [2] = 2,
  [3] = 3,
  [4] = 4,
  [5] = 5,
  [6] = 6,
  [7] = 7,
  [8] = 6,
  [9] = 6,
  [10] = 10,
  [11] = 11,
  [12] = 12,
  [13] = 13,
  [14] = 14,
  [15] = 15,
  [16] = 16,
  [17] = 17,
  [18] = 18,
  [19] = 19,
  [20] = 20,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      if (eof) ADVANCE(1);
      END_STATE();
    case 1:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0, .external_lex_state = 1},
  [1] = {.lex_state = 0, .external_lex_state = 2},
  [2] = {.lex_state = 0, .external_lex_state = 2},
  [3] = {.lex_state = 0, .external_lex_state = 2},
  [4] = {.lex_state = 0, .external_lex_state = 2},
  [5] = {.lex_state = 0, .external_lex_state = 2},
  [6] = {.lex_state = 0, .external_lex_state = 2},
  [7] = {.lex_state = 0, .external_lex_state = 2},
  [8] = {.lex_state = 0, .external_lex_state = 2},
  [9] = {.lex_state = 0, .external_lex_state = 2},
  [10] = {.lex_state = 0, .external_lex_state = 2},
  [11] = {.lex_state = 0, .external_lex_state = 2},
  [12] = {.lex_state = 0, .external_lex_state = 2},
  [13] = {.lex_state = 0, .external_lex_state = 2},
  [14] = {.lex_state = 0, .external_lex_state = 3},
  [15] = {.lex_state = 0},
  [16] = {.lex_state = 0, .external_lex_state = 4},
  [17] = {.lex_state = 0},
  [18] = {.lex_state = 0, .external_lex_state = 5},
  [19] = {.lex_state = 0, .external_lex_state = 6},
  [20] = {.lex_state = 0, .external_lex_state = 7},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym_text] = ACTIONS(1),
    [sym_space] = ACTIONS(1),
    [sym_star] = ACTIONS(1),
    [sym_underscore] = ACTIONS(1),
    [sym_hash] = ACTIONS(1),
    [sym_ident] = ACTIONS(1),
    [sym_int] = ACTIONS(1),
    [sym_raw_delim] = ACTIONS(1),
    [sym_raw_content] = ACTIONS(1),
  },
  [1] = {
    [sym_source_file] = STATE(15),
    [sym_markup] = STATE(17),
    [sym_strong] = STATE(6),
    [sym_emph] = STATE(6),
    [sym_raw] = STATE(6),
    [aux_sym_markup_repeat1] = STATE(6),
    [sym_text] = ACTIONS(3),
    [sym_space] = ACTIONS(3),
    [sym_star] = ACTIONS(5),
    [sym_underscore] = ACTIONS(7),
    [sym_hash] = ACTIONS(9),
    [sym_raw_delim] = ACTIONS(11),
  },
  [2] = {
    [sym_markup] = STATE(18),
    [sym_strong] = STATE(8),
    [sym_emph] = STATE(8),
    [sym_raw] = STATE(8),
    [aux_sym_markup_repeat1] = STATE(8),
    [ts_builtin_sym_end] = ACTIONS(13),
    [sym_text] = ACTIONS(13),
    [sym_space] = ACTIONS(13),
    [sym_star] = ACTIONS(13),
    [sym_underscore] = ACTIONS(13),
    [sym_hash] = ACTIONS(13),
    [sym_raw_delim] = ACTIONS(13),
  },
  [3] = {
    [sym_markup] = STATE(19),
    [sym_strong] = STATE(9),
    [sym_emph] = STATE(9),
    [sym_raw] = STATE(9),
    [aux_sym_markup_repeat1] = STATE(9),
    [ts_builtin_sym_end] = ACTIONS(15),
    [sym_text] = ACTIONS(15),
    [sym_space] = ACTIONS(15),
    [sym_star] = ACTIONS(15),
    [sym_underscore] = ACTIONS(15),
    [sym_hash] = ACTIONS(15),
    [sym_raw_delim] = ACTIONS(15),
  },
  [4] = {
    [sym_markup] = STATE(18),
    [sym_strong] = STATE(8),
    [sym_emph] = STATE(8),
    [sym_raw] = STATE(8),
    [aux_sym_markup_repeat1] = STATE(8),
    [sym_text] = ACTIONS(17),
    [sym_space] = ACTIONS(17),
    [sym_star] = ACTIONS(19),
    [sym_underscore] = ACTIONS(7),
    [sym_hash] = ACTIONS(9),
    [sym_raw_delim] = ACTIONS(11),
  },
  [5] = {
    [sym_markup] = STATE(19),
    [sym_strong] = STATE(9),
    [sym_emph] = STATE(9),
    [sym_raw] = STATE(9),
    [aux_sym_markup_repeat1] = STATE(9),
    [sym_text] = ACTIONS(21),
    [sym_space] = ACTIONS(21),
    [sym_star] = ACTIONS(5),
    [sym_underscore] = ACTIONS(23),
    [sym_hash] = ACTIONS(9),
    [sym_raw_delim] = ACTIONS(11),
  },
  [6] = {
    [sym_strong] = STATE(7),
    [sym_emph] = STATE(7),
    [sym_raw] = STATE(7),
    [aux_sym_markup_repeat1] = STATE(7),
    [ts_builtin_sym_end] = ACTIONS(25),
    [sym_text] = ACTIONS(27),
    [sym_space] = ACTIONS(27),
    [sym_star] = ACTIONS(5),
    [sym_underscore] = ACTIONS(7),
    [sym_hash] = ACTIONS(9),
    [sym_raw_delim] = ACTIONS(11),
  },
  [7] = {
    [sym_strong] = STATE(7),
    [sym_emph] = STATE(7),
    [sym_raw] = STATE(7),
    [aux_sym_markup_repeat1] = STATE(7),
    [ts_builtin_sym_end] = ACTIONS(29),
    [sym_text] = ACTIONS(31),
    [sym_space] = ACTIONS(31),
    [sym_star] = ACTIONS(34),
    [sym_underscore] = ACTIONS(37),
    [sym_hash] = ACTIONS(40),
    [sym_raw_delim] = ACTIONS(43),
  },
  [8] = {
    [sym_strong] = STATE(7),
    [sym_emph] = STATE(7),
    [sym_raw] = STATE(7),
    [aux_sym_markup_repeat1] = STATE(7),
    [sym_text] = ACTIONS(27),
    [sym_space] = ACTIONS(27),
    [sym_star] = ACTIONS(25),
    [sym_underscore] = ACTIONS(7),
    [sym_hash] = ACTIONS(9),
    [sym_raw_delim] = ACTIONS(11),
  },
  [9] = {
    [sym_strong] = STATE(7),
    [sym_emph] = STATE(7),
    [sym_raw] = STATE(7),
    [aux_sym_markup_repeat1] = STATE(7),
    [sym_text] = ACTIONS(27),
    [sym_space] = ACTIONS(27),
    [sym_star] = ACTIONS(5),
    [sym_underscore] = ACTIONS(25),
    [sym_hash] = ACTIONS(9),
    [sym_raw_delim] = ACTIONS(11),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 1,
    ACTIONS(29), 7,
      sym_text,
      sym_space,
      sym_star,
      sym_underscore,
      sym_hash,
      sym_raw_delim,
      ts_builtin_sym_end,
  [10] = 1,
    ACTIONS(46), 7,
      sym_text,
      sym_space,
      sym_star,
      sym_underscore,
      sym_hash,
      sym_raw_delim,
      ts_builtin_sym_end,
  [20] = 1,
    ACTIONS(48), 7,
      sym_text,
      sym_space,
      sym_star,
      sym_underscore,
      sym_hash,
      sym_raw_delim,
      ts_builtin_sym_end,
  [30] = 1,
    ACTIONS(50), 7,
      sym_text,
      sym_space,
      sym_star,
      sym_underscore,
      sym_hash,
      sym_raw_delim,
      ts_builtin_sym_end,
  [40] = 2,
    STATE(10), 1,
      sym__expr,
    ACTIONS(52), 2,
      sym_ident,
      sym_int,
  [48] = 1,
    ACTIONS(54), 1,
      ts_builtin_sym_end,
  [52] = 1,
    ACTIONS(56), 1,
      sym_raw_content,
  [56] = 1,
    ACTIONS(58), 1,
      ts_builtin_sym_end,
  [60] = 1,
    ACTIONS(60), 1,
      sym_star,
  [64] = 1,
    ACTIONS(62), 1,
      sym_underscore,
  [68] = 1,
    ACTIONS(64), 1,
      sym_raw_delim,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(10)] = 0,
  [SMALL_STATE(11)] = 10,
  [SMALL_STATE(12)] = 20,
  [SMALL_STATE(13)] = 30,
  [SMALL_STATE(14)] = 40,
  [SMALL_STATE(15)] = 48,
  [SMALL_STATE(16)] = 52,
  [SMALL_STATE(17)] = 56,
  [SMALL_STATE(18)] = 60,
  [SMALL_STATE(19)] = 64,
  [SMALL_STATE(20)] = 68,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [13] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_strong, 2, 0, 0),
  [15] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_emph, 2, 0, 0),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [25] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_markup, 1, 0, 0),
  [27] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [29] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_markup_repeat1, 2, 0, 0),
  [31] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_markup_repeat1, 2, 0, 0), SHIFT_REPEAT(7),
  [34] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_markup_repeat1, 2, 0, 0), SHIFT_REPEAT(4),
  [37] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_markup_repeat1, 2, 0, 0), SHIFT_REPEAT(5),
  [40] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_markup_repeat1, 2, 0, 0), SHIFT_REPEAT(14),
  [43] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_markup_repeat1, 2, 0, 0), SHIFT_REPEAT(16),
  [46] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_strong, 3, 0, 0),
  [48] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_raw, 3, 0, 0),
  [50] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_emph, 3, 0, 0),
  [52] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [54] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [56] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [58] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1, 0, 0),
  [60] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [62] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [64] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
};

enum ts_external_scanner_symbol_identifiers {
  ts_external_token_text = 0,
  ts_external_token_space = 1,
  ts_external_token_star = 2,
  ts_external_token_underscore = 3,
  ts_external_token_hash = 4,
  ts_external_token_ident = 5,
  ts_external_token_int = 6,
  ts_external_token_raw_delim = 7,
  ts_external_token_raw_content = 8,
};

static const TSSymbol ts_external_scanner_symbol_map[EXTERNAL_TOKEN_COUNT] = {
  [ts_external_token_text] = sym_text,
  [ts_external_token_space] = sym_space,
  [ts_external_token_star] = sym_star,
  [ts_external_token_underscore] = sym_underscore,
  [ts_external_token_hash] = sym_hash,
  [ts_external_token_ident] = sym_ident,
  [ts_external_token_int] = sym_int,
  [ts_external_token_raw_delim] = sym_raw_delim,
  [ts_external_token_raw_content] = sym_raw_content,
};

static const bool ts_external_scanner_states[8][EXTERNAL_TOKEN_COUNT] = {
  [1] = {
    [ts_external_token_text] = true,
    [ts_external_token_space] = true,
    [ts_external_token_star] = true,
    [ts_external_token_underscore] = true,
    [ts_external_token_hash] = true,
    [ts_external_token_ident] = true,
    [ts_external_token_int] = true,
    [ts_external_token_raw_delim] = true,
    [ts_external_token_raw_content] = true,
  },
  [2] = {
    [ts_external_token_text] = true,
    [ts_external_token_space] = true,
    [ts_external_token_star] = true,
    [ts_external_token_underscore] = true,
    [ts_external_token_hash] = true,
    [ts_external_token_raw_delim] = true,
  },
  [3] = {
    [ts_external_token_ident] = true,
    [ts_external_token_int] = true,
  },
  [4] = {
    [ts_external_token_raw_content] = true,
  },
  [5] = {
    [ts_external_token_star] = true,
  },
  [6] = {
    [ts_external_token_underscore] = true,
  },
  [7] = {
    [ts_external_token_raw_delim] = true,
  },
};

#ifdef __cplusplus
extern "C" {
#endif
void *tree_sitter_typst_external_scanner_create(void);
void tree_sitter_typst_external_scanner_destroy(void *);
bool tree_sitter_typst_external_scanner_scan(void *, TSLexer *, const bool *);
unsigned tree_sitter_typst_external_scanner_serialize(void *, char *);
void tree_sitter_typst_external_scanner_deserialize(void *, const char *, unsigned);

#ifdef TREE_SITTER_HIDE_SYMBOLS
#define TS_PUBLIC
#elif defined(_WIN32)
#define TS_PUBLIC __declspec(dllexport)
#else
#define TS_PUBLIC __attribute__((visibility("default")))
#endif

TS_PUBLIC const TSLanguage *tree_sitter_typst(void) {
  static const TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
    .state_count = STATE_COUNT,
    .large_state_count = LARGE_STATE_COUNT,
    .production_id_count = PRODUCTION_ID_COUNT,
    .field_count = FIELD_COUNT,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .parse_table = &ts_parse_table[0][0],
    .small_parse_table = ts_small_parse_table,
    .small_parse_table_map = ts_small_parse_table_map,
    .parse_actions = ts_parse_actions,
    .symbol_names = ts_symbol_names,
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
    .external_scanner = {
      &ts_external_scanner_states[0][0],
      ts_external_scanner_symbol_map,
      tree_sitter_typst_external_scanner_create,
      tree_sitter_typst_external_scanner_destroy,
      tree_sitter_typst_external_scanner_scan,
      tree_sitter_typst_external_scanner_serialize,
      tree_sitter_typst_external_scanner_deserialize,
    },
    .primary_state_ids = ts_primary_state_ids,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
