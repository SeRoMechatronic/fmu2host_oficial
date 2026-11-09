#!/usr/bin/env python3
"""Remove the export workstation username from retained OpenModelica artifacts.

OpenModelica embeds absolute source and library paths in generated C, JSON, and
Windows binaries.  The substitutions below are byte-for-byte equal in length,
so they can also be applied safely to string data inside the retained DLLs.
Both the expanded model trees and the matching FMU ZIP members are rewritten.
No FMI identifiers, equations, value references, or scenario data are changed.
"""

from __future__ import annotations

import argparse
import os
import tempfile
import zipfile
from pathlib import Path


def build_replacements(old_prefix: str) -> tuple[tuple[bytes, bytes], ...]:
    old_slash = old_prefix.replace("\\", "/").rstrip("/").encode("utf-8")
    neutral_base = b"C:/fmu2host/"
    if len(old_slash) < len(neutral_base):
        raise ValueError("the path prefix is too short for a neutral replacement")
    new_slash = neutral_base + b"x" * (len(old_slash) - len(neutral_base))
    old_backslash = old_slash.replace(b"/", b"\\")
    new_backslash = new_slash.replace(b"/", b"\\")
    replacements = ((old_slash, new_slash), (old_backslash, new_backslash))
    if any(len(old) != len(new) for old, new in replacements):
        raise RuntimeError("privacy substitutions must preserve byte length")
    return replacements


def sanitize_bytes(
    data: bytes, replacements: tuple[tuple[bytes, bytes], ...]
) -> tuple[bytes, int]:
    total = 0
    for old, new in replacements:
        count = data.count(old)
        if count:
            data = data.replace(old, new)
            total += count
    return data, total


def sanitize_file(path: Path, replacements: tuple[tuple[bytes, bytes], ...]) -> int:
    original = path.read_bytes()
    sanitized, count = sanitize_bytes(original, replacements)
    if count:
        path.write_bytes(sanitized)
    return count


def sanitize_fmu(path: Path, replacements: tuple[tuple[bytes, bytes], ...]) -> int:
    total = 0
    fd, temp_name = tempfile.mkstemp(prefix=f".{path.stem}-", suffix=".fmu", dir=path.parent)
    os.close(fd)
    temp_path = Path(temp_name)
    try:
        with zipfile.ZipFile(path, "r") as source, zipfile.ZipFile(temp_path, "w") as target:
            target.comment = source.comment
            for info in source.infolist():
                data = source.read(info.filename)
                data, count = sanitize_bytes(data, replacements)
                total += count
                target.writestr(info, data)
        if total:
            os.replace(temp_path, path)
        else:
            temp_path.unlink()
    except Exception:
        temp_path.unlink(missing_ok=True)
        raise
    return total


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "models_dir",
        nargs="?",
        type=Path,
        default=Path(__file__).resolve().parents[1] / "models",
    )
    parser.add_argument(
        "--old-prefix",
        default=Path.home().as_posix(),
        help="absolute user/profile prefix embedded by the exporter (default: current home)",
    )
    args = parser.parse_args()
    root = args.models_dir.resolve()
    if not root.is_dir():
        parser.error(f"not a directory: {root}")

    replacements = build_replacements(args.old_prefix)
    file_count = file_replacements = 0
    fmu_count = fmu_replacements = 0
    for path in sorted(p for p in root.rglob("*") if p.is_file()):
        if path.suffix.lower() == ".fmu":
            count = sanitize_fmu(path, replacements)
            if count:
                fmu_count += 1
                fmu_replacements += count
        else:
            count = sanitize_file(path, replacements)
            if count:
                file_count += 1
                file_replacements += count

    print(
        f"Sanitized {file_replacements} path occurrence(s) in {file_count} expanded file(s); "
        f"{fmu_replacements} occurrence(s) in {fmu_count} FMU archive(s)."
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
