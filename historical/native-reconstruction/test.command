#!/bin/bash
set -euo pipefail
cd "$(dirname "$0")"
ctest_bin="${CTEST:-ctest}"
if ! command -v "$ctest_bin" >/dev/null 2>&1; then ctest_bin="$PWD/build/tools-env/bin/ctest"; fi
"$ctest_bin" --test-dir build/native --output-on-failure
python3 tests/test_import_disc.py
python3 tests/test_prepare_data.py
python3 tests/test_prepared_profiles.py
python3 tests/test_prepare_map_runtime_data.py
python3 tests/test_prepare_visibility_data.py
python3 tests/test_archive_store.py
if [[ $# -gt 0 ]]; then
  if [[ "$1" != --data-dir || $# -ne 2 ]]; then echo 'Usage: ./test.command [--data-dir OWNED_INSTALL]' >&2; exit 2; fi
  build/native/ra2-inspect "$2"
  build/native/presentation-check "$2"
  build/native/boot-camp-walk-check "$2"
  python3 tests/check_static_light_assets.py --data-dir "$2"
  python3 tests/check_unit_caller_assets.py --data-dir "$2"
  python3 tests/check_scenery_assets.py --data-dir "$2"
  build/native/redalert2-native --data-dir "$2" --smoke-test
  build/native/redalert2-native --data-dir "$2" --light-demo --smoke-test
fi
