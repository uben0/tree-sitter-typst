/**
 * @file Typst grammar for Tree-Sitter
 * @author Eddie Gerbais-Nief <eddie.gerbais-nief@proton.me>
 * @license MIT
 */

/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

module.exports = grammar({
  name: "typst",
  externals: $ => [
    $.text,
    $.space,
    $.star,
    $.underscore,
    $.hash,
    $.ident,
    $.int,
    $.raw_delim,
    $.raw_content,
  ],
  rules: {
    source_file: $ => $.markup,
    markup: $ => prec.left(repeat1(choice(
      $.text,
      $.space,
      $.strong,
      $.emph,
      $.raw,
      seq($.hash, $._expr),
    ))),
    strong: $ => prec.left(seq($.star, optional($.markup), $.star)),
    emph: $ => prec.left(seq($.underscore, optional($.markup), $.underscore)),
    raw: $ => seq($.raw_delim, alias($.raw_content, $.text), $.raw_delim),
    _expr: $ => choice($.ident, $.int),
  }
});
