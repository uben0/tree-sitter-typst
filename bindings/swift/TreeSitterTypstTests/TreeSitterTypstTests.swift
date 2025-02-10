import XCTest
import SwiftTreeSitter
import TreeSitterTypst

final class TreeSitterTypstTests: XCTestCase {
    func testCanLoadGrammar() throws {
        let parser = Parser()
        let language = Language(language: tree_sitter_typst())
        XCTAssertNoThrow(try parser.setLanguage(language),
                         "Error loading Typst grammar")
    }
}
