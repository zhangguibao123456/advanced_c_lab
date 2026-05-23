#!/usr/bin/env bash
set -euo pipefail

cd "$(dirname "$0")/.."

mapfile -t c_files < <(find src -type f \( -name '*.c' -o -name '*.h' \) | sort)

clang-format --dry-run --Werror "${c_files[@]}"
cmake -S . -B build -G Ninja
cmake --build build
ctest --test-dir build --output-on-failure

