// swift-tools-version:5.3
import PackageDescription

let package = Package(
    name: "TreeSitterTypst",
    products: [
        .library(name: "TreeSitterTypst", targets: ["TreeSitterTypst"]),
    ],
    dependencies: [
        .package(url: "https://github.com/ChimeHQ/SwiftTreeSitter", from: "0.8.0"),
    ],
    targets: [
        .target(
            name: "TreeSitterTypst",
            dependencies: [],
            path: ".",
            sources: [
                "src/parser.c",
                // NOTE: if your language has an external scanner, add it here.
            ],
            resources: [
                .copy("queries")
            ],
            publicHeadersPath: "bindings/swift",
            cSettings: [.headerSearchPath("src")]
        ),
        .testTarget(
            name: "TreeSitterTypstTests",
            dependencies: [
                "SwiftTreeSitter",
                "TreeSitterTypst",
            ],
            path: "bindings/swift/TreeSitterTypstTests"
        )
    ],
    cLanguageStandard: .c11
)
