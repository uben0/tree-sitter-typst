package tree_sitter_typst_test

import (
	"testing"

	tree_sitter "github.com/tree-sitter/go-tree-sitter"
	tree_sitter_typst "github.com/uben0/tree-sitter-typst/bindings/go"
)

func TestCanLoadGrammar(t *testing.T) {
	language := tree_sitter.NewLanguage(tree_sitter_typst.Language())
	if language == nil {
		t.Errorf("Error loading Typst grammar")
	}
}
