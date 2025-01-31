#!/usr/bin/env python3

from pathlib import Path
import re
import subprocess

root_dir = Path(__file__).parents[1]
tests_dir = root_dir.parent / "typst" / "tests" / "suite"
tests_files = list(tests_dir.glob("**/*.typ"))
with open(root_dir / "test" / "corpus" / "typst.scm", "w") as file:
    for test in tests_files:
        for name, typ in re.findall(r"--- ([A-Za-z0-9-]+) (?:render )?(?:html )?(?:large )?---(.+?(?=---|$))", test.read_text(), re.DOTALL):
            file.write(f"{'=' * 20}\ntypst/{test.stem}/{name}\n{'=' * 20}\n{typ}\n{'-' * 20}\n\n")
subprocess.run(["tree-sitter", "test", "-i^typst/", "-u"], cwd=root_dir)
