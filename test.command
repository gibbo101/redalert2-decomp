#!/bin/zsh
set -eu
cd "${0:A:h}"
exec "${RA2_PYTHON:-python3}" -B -m unittest discover -s tests -p 'test*.py' "$@"
