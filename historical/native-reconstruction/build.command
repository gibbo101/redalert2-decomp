#!/bin/bash
set -euo pipefail
cd "$(dirname "$0")"
if [[ -z "${DEVELOPER_DIR:-}" && -x /Library/Developer/CommandLineTools/usr/bin/clang++ ]]; then
  export DEVELOPER_DIR=/Library/Developer/CommandLineTools
fi
cmake_bin="${CMAKE:-cmake}"
if ! command -v "$cmake_bin" >/dev/null 2>&1; then cmake_bin="$PWD/build/tools-env/bin/cmake"; fi
if [[ ! -x "$cmake_bin" ]] && ! command -v "$cmake_bin" >/dev/null 2>&1; then
  echo 'CMake missing. See README.md for the isolated tool setup.' >&2; exit 1
fi
"$cmake_bin" -S . -B build/native -DCMAKE_BUILD_TYPE=RelWithDebInfo \
  -DCMAKE_PREFIX_PATH="${CMAKE_PREFIX_PATH:-/opt/homebrew}" "$@"
"$cmake_bin" --build build/native --parallel 6
