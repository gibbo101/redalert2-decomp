#!/bin/zsh
set -eu
cd "${0:A:h}"
exec "${RA2_PYTHON:-python3}" -B tools/original_target/build.py --verify-inputs "$@"
