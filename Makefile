test: src/parser.c
	tree-sitter test --file-name Test

all: src/parser.c
	tree-sitter test

fixme: src/parser.c
	tree-sitter test --file-name Fixme

src/parser.c: grammar.js
	tree-sitter generate

build: src/parser.c size

size: src/parser.c
	du -b src/parser.c
	du -b src/parser.c > size.txt

.PHONY: fixme test build all size
