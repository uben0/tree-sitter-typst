# A Typst grammar for Tree-Sitter

Typst official page https://typst.app

Tree-Sitter documentation page https://tree-sitter.github.io

Typst doesn't have yet an official Tree-Sitter grammar. This grammar is complete but may contains bug as it is very recent.

## Get involved

Your help is welcome. You don't have to know anything about Tree-Sitter to help. You just have to use this grammar and report any bad highlighting you see! You can open an issue or simply send me by email the Typst code causing the bug. See below installation instructions for this grammar. Even if your not sure it is a bug, it doesn't hurt to repport it.

I need help to:
  - write the different "queries" for the different editors like Neovim or Helix. Indeed, the queries like the highlights or the indentation may vary between editors.
  - have more tests, by either directly writing some or by improving https://github.com/uben0/tree-sitter-typst-utils/tree/main/test-gen
  - implement the full rewrite on branch `rewrite`. This time the code is documented and you may get involve however you want. Ask me how to help, ask me what needs to be explained and documented. I aim at making this new implementation maintainable by the community.

Don't hesitate to contact me (mailto:eddie.gerbais-nief@proton.me) or to open an issue, even if you're not sure. It doesn't hurt.

The documentation of the current implementation (not the rewrite) is available in [DOC](DOC.md). But I suggest to ignore the current implementation as it is a spaghetti mess. However, the [DOC](DOC.md) brings up interesting chalenges.

## TODO

- [ ] Update 0.13
  - [ ] Identify changes
- [ ] More tests, objectif 1000, current 433
  - [x] generate tests from official Typst parser. https://github.com/uben0/tree-sitter-typst-utils/tree/main/test-gen
- [X] Editor support
  - [X] Helix
  - [X] Emacs
  - [X] NeoVim
- [ ] Simplification
  - [ ] Full rewrite for a correct and maintainable code base (on branch `rewrite`)
  - [ ] Implement a type 3/4 parser generator (work in progress). The rewrite have a lexer based on the official parser but may benefit from automatic code generation.
  - [ ] Migrate all lexing to external scanner (work in progress on `rewrite` branch)

## Features

- [X] Markup mode
- [X] Code mode
- [X] Math mode
- [X] Indentation
- [X] Foldable sections
- [X] Unicode characters

# Installation

## Language Server

Having syntax highlighting is great but having syntax highlighting and the language server is even greater. If you have `cargo` installed (Rust's package manager), you can install Typst language server with the following command (you don't have to be in any particular directory):

```sh
cargo install --git https://github.com/Myriad-Dreamin/tinymist --locked tinymist
```

## Neovim

The https://github.com/nvim-treesitter/nvim-treesitter provides this grammar.

## Emacs

Typst support for Emacs is available through the following package:

[typst-ts-mode](https://git.sr.ht/~meow_king/typst-ts-mode)

```scheme
(use-package typst-ts-mode
  :elpaca (:type git :host sourcehut :repo "meow_king/typst-ts-mode")
  :custom
  (typst-ts-mode-watch-options "--open"))
```

## Helix

This grammar is already builtin Helix. But it might not be up to date. To manyally install it:

1. Locate the configuration directory:

- Local `~/.config/helix`
- Global `/usr/share/helix`

2. Append the following configuration to the `languages.toml` file (create it if it doesn't exist).

```toml
[[language]]
name = "typst"
scope = "source.typst"
file-types = ["typst", "typ"]
indent = { tab-width = 2, unit = "  " }
comment-token = "//"
injection-regex = "typ(st)?"
roots = ["typst.toml"]
language-servers = [ "typst-lsp" ]

[language.auto-pairs]
'(' = ')'
'{' = '}'
'[' = ']'
'$' = '$'
'"' = '"'

[[grammar]]
name = "typst"
source.git = "https://github.com/uben0/tree-sitter-typst"
source.rev = "master"
```

3. Copy the content of the `queries` directory (`highlights.scm` and `injections.scm`) inside your corresponding `runtime/queries/typst` directory. You should have the following structure:

```
config.toml
languages.toml
runtime
└── queries
    └── typst
        ├── highlights.scm
        └── injections.scm
```

4. And finally execute (you don't have to be in any particular directory):

```sh
hx --grammar fetch
hx --grammar build
```

The fetch command will clone the git repository, and the build command will compile the grammar. Open the logs to have insightfull messages in case it doesn't work.
