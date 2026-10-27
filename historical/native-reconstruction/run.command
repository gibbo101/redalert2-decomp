#!/bin/bash
set -euo pipefail
cd "$(dirname "$0")"
if [[ -z "${RA2_DATA_DIR:-}" ]]; then
  if [[ -f private/official-1006-probe/game.exe && -f private/official-1006-probe/ra2.mix ]]; then
    export RA2_DATA_DIR="$PWD/private/official-1006-probe"
  elif [[ -f private/game/ra2.mix ]]; then
    export RA2_DATA_DIR="$PWD/private/game"
  fi
fi
exec build/native/redalert2-native "$@"
