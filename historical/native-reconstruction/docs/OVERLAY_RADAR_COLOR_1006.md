# Overlay header colors and retained map assets

Tutorial purpose: Objective1 action37 needs the original House sight/coverage/
radar effects. Day1's actual map contains overlay indexes127..138, so their color
branch is required before joining the terrain projection to production. Complete
5DD000 now joins the existing resident/Cell-color/terrain/projection chain. The
actual map also retains its source TMP bytes on canonical prepared tile owners.
There is no new radar drawing, sight scheduling or SDL objective transition.

## Recovered boundary

`OverlayRadarColor.hpp` borrows the existing `OverlayTypeInputs` index and CellAnim
fields. Query the primary image first. Only a null primary and a live nonzero
CellAnim invoke its image service. The index is read after those virtual calls;
tests supply index/CellAnim changes during the first query to check that order.
Image virtuals/loading remain services in portable code. The original executes
actual initialized5DD150 (resident image or demandLoad0) and an explicitly authored
5293D0 alternate binding with a resident image/lazy0. This does not establish the
original animation class association or the complete demand-loading branch.

An image's signed16 frame count is sign-extended, then compared with the full
unsigned32 frame argument. Frame addressing uses wrapped32-bit24*frame; negative
counts and frame0x80000000 can therefore reach a backed header after wrapping.
Native bounds checks refuse unsafe/truncated backing instead of allowing arbitrary
pointers. The guest null header-pointer wrap is outside the supported file-relative
backing domain. Missing images or out-of-range frames return black. Otherwise read
bytes20+24*frame through22+24*frame. Index127..138 or147..158 writes them inR,B,G
order; all other signed indexes useR,G,B. Both paths store the word pair before
the final byte. Complete432D70 executes on the original special invalid-frame
branch; the portable result has no separate constructor/heap identity claim.

Exact supplied target:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage and reported no-CD provenance are distinct;
pristine authenticity remains unverified. Complete5DD000 is329 bytes/109
instructions, SHA256
`17953ec1c3ff6f499bf61b4d6b113f8c0aefe83de1ca2584f62467e2dea5ec1a`.
The verifier fingerprints before addresses and checks the actual OverlayType
image slot. No generated/lifted/public implementation or new dependency was used.

## Composition and actual assets

Standalone366 original roots execute366 initialized primary getters,105 alternate
getters,44 zero constructors and732 ordered output stores. They cover missing/
present/fallback images, index boundaries, negative/zero/large counts, unsigned
frame extremes with safely backed wrapping and supplied late-field changes.
Full arena/code/image snapshots, permitted output stores, caller stack and saved
registers are checked. Authored alternate binding, images/registry/startup and
supplied virtual-call side effects retain their scopes.

The newL/B fixture commands opt into actual overlay header selection; oldK/C/T
commands retain their old behavior/evidence. All398 composed sequences execute
526 Cell-color/resident searches,288 actual5DD000 calls/initialized primary getters,
64 terrain joins and32 projection joins. Ordered outputs and full backings match
672 RGB/680 projected pixel writes. Resource5DC0B0 and TMP installation52B560
remain supplied here, along with initial type/image/brightness and variant tables.
Earlier254 Cell-color and254 resident-color answers remain unchanged on both
rebuilt profiles, without regenerating their original matrices.

`PreparedTerrainMap::tileImages` now uses existing `TileSweepType` owners. Each
resident type retains immutable Data and PreparedTileImage; `MapTileAttributes`
borrows that exact prepared image. Type filenames/indexes and source-reference-
only residency stay unchanged. The prepared map also retains the existing
constructed/INI `OverlayTypeInputs`, including image names and CellAnim fields;
its image/animation handles remain unbound. The existing primary-only association,
variants1 and default tile0 remain supplied policies, not reconstructed startup.
There is no second mutable map or new runtime executable read.

Actual Day1 normal and sanitizer owner checks verify retained TMP bytes equal
files read from the user installation, shared metadata identity, absent-file
policy and overlay registry/index association. They also retain ordinary movement,
Stop/repeated orders, clone/source-destruction, visibility and mission-owner checks.
These are native ownership/regression checks, not original file/startup proofs or
whole-frame acceptance. App rebuilt; no SDL input/drawing acceptance was repeated
for this internal storage change, and older app receipts keep their prior hashes.

## Validation, costs and remaining work

Fifteen focused Python checks,398 joined parser inputs and six CTests/profile
pass. Standalone/composed normal, sanitizer and uncached-inspection replays each
report366/398 original hits and zero misses. Original answers alone are reused;
current native comparisons run every time. Current runner hashes also match those
reports after the owner/app rebuild. Both real Day1 owner checks pass:3.676s
normal and36.893s sanitizer. The sanitizer cost is recorded separately.

Private canonical originals under `private/boot-camp-20261020/`:
`overlay-color-fresh-a1/expected.json`, `radar-overlay-fresh-a1/expected.json`.
Fresh original/native/driver costs:.050/.019/.399s and3.596/.043/4.035s. Normal
replay costs:.181/.256s; sanitizer.376/.690s; uncached-inspection.259/1.887s.
Receipt `overlay-color-receipt-a1.json` records hashes and unavailable initial
inspection/edit/configure/build/task/repair costs. The first normal and sanitizer
owner builds failed on a missing direct header include; A2 repairs it. These
failures remain private logs and were never accepted as proof. Local verification
is not independent acceptance.

Next bind the retained overlay file/animation provenance and recovered resource
classifier on the same actual map/type owners. Recover the entered image-loading
children before permitting unbound demand paths. Actual630A00 startup with aliased
source/region, native storage and first-DSurface semantics still precedes the
production House/coverage/actor/SDL join. Theater brightness and primary variant
startup remain explicit boundaries. Live arrival/sight and ordinary first-objective
progress remain incomplete, as do base RA2 and YR. Only Apple Silicon macOS is
tested. No workers, Windows actions, transfers, downloads or system changes.

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake -S . -B build/native
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake --build build/native --target overlay-radar-color-vectors cell-radar-color-vectors radar-terrain-vectors boot-camp-walk-check redalert2-native --parallel 6
build/tools-env/bin/ctest --test-dir build/native -R '^(overlay-radar-color|cell-resident-search|cell-resident-kind6|cell-radar-color|radar-terrain|radar-projection)-domain$' --output-on-failure
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_overlay_radar_color test_cell_radar_color test_radar_terrain test_radar_projection test_cell_resident_search
build/native/boot-camp-walk-check private/official-1006-probe
# Explicit supported reuse; choose fresh audit/report paths.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/NEW-OVERLAY.audit.json tests/compare_overlay_radar_color.py \
  --exe private/official-1006-probe/game.exe --native build/native/overlay-radar-color-vectors \
  --expectations private/boot-camp-20261020/overlay-color-fresh-a1/expected.json \
  --report private/NEW-OVERLAY.json
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/NEW-RADAR-OVERLAY.audit.json tests/compare_radar_overlay_color.py \
  --exe private/official-1006-probe/game.exe --native build/native/cell-radar-color-vectors \
  --terrain-native build/native/radar-terrain-vectors \
  --expectations private/boot-camp-20261020/radar-overlay-fresh-a1/expected.json \
  --report private/NEW-RADAR-OVERLAY.json
```

Use `build/sanitize/` runners for sanitizer; put `--uncached` before the driver
for inspection control, retaining expectations reuse. Fresh generation uses a new
`--output` instead of expectations/report and requires research-only Unicorn JIT.
App entry points remain `./build.command`, `./test.command`,
`./run.command --boot-camp-walk`.
