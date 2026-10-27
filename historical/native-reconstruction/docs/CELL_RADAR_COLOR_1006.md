# Cell radar color selection

Tutorial purpose: Boot Camp Objective1 action37's alliance effect needs the
House sight/coverage/radar chain. Complete4712C0 now supplies colors to the same
631250 traversal and630B70 projection owners. It replaces authored output triples
with the recovered selector operating on authored TMP/animation/type inputs.
This is not yet actual Boot Camp asset color provenance or runtime adoption.

## Recovered policy and shared owners

`cellRadarColors` borrows `MapCellAttributes` and existing `TileSweepType`/`Data`
owners through explicit services. It adds no original object-layout mirror or
parallel map. The terrain fixture now uses `MapCellAttributes.input.position`
for both traversal and the color child. Existing T commands retain all88 prior
original outputs; C commands compose actual color selection on those same Cells.

4712C0 first calls471760 with kind36/argument0; any nonnull result returns both
RGB triples(200,200,160). Next Cell flag100 takes overlay registry entry24 with
color argument0 before any primary tile lookup. Otherwise65535 selects ClearTile
and other indexes select the primary tile directly, before overlay handling.
No meaning beyond the recovered fields is assigned to these flags/type numbers.

An overlay with clear279 calls5DD000. Overlay indexes74..99 and205..230 force
argument1; others forward the current overlay-data byte.100/101 and231/232 retain
the entered behavior of the actual base instructions; no YR exception was imposed.
A set279 with alternate26C reads its image's signed16 frame count, compares the
zero-extended data byte as unsigned32 and selects RGB at20+24*data. Out-of-range
frames yield black. A missing alternate calls5DC0B0; any result except-1 yields
(170,170,130), while-1 continues to tile selection.

Ordinary multi-variant tiles call actual52B730 semantics: GetImage, signed
remainder by image columns*rows, subheader existence and flag4. Flag4 selects
(Cell flags>>13)&1; otherwise4767A0 chooses.65535 always calls the selector,
even at count1. The native fixture binds the existing `selectTileVariant` kernel;
original4767A0 actually executes with initialized authored cache/tables. Fresh
RNG/cache initialization retains its earlier independent scope and is not exercised
here.529520 reduces only results greater than variants-1, then follows exactly
that many alternate links. The selected type's image may invoke supplied52B560
installation through actual GetImage/5293A0. Native unsupported negative walks,
invalid divisors, missing owners/images or truncated Data refuse safely.

A missing selected TMP subheader returns(60,60,60). Otherwise bytes2B/2C/2D
are scaled through complete63CDF0/FTOL semantics and each resulting byte is halved
by a logical right shift. The scale is the supplied float32 theater-table value
selected by the original scenario838 field. It is not a newly approved runtime
executable read. The53-bit/toward-zero profile is explicit; caller rounding restores
on return. Unordered/NaN products follow the original upper clamp, then halve255
to127; they do not fall through to FTOL's indefinite zero. Both RGB destinations
use ordered word-pair then third-byte stores, including aliased output pointers.

## Executed evidence and supplied boundaries

Exact supplied target:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Complete4712C0 is924 bytes, SHA256
`15b7d35a5308a5c9cd9ed0a842b11bd8d7f323ba539ed87f2c5599f2450e16f5`.
Complete529520,52B730,5293A0,5293D0, initialized4767A0,63CDF0,432D70 andFTOL
execute unchanged below the root; complete631250 and630B70 execute in joined cases.
No public code, new dependency or runtime executable read was added.

The471760 resident result,5DD000 overlay-color child,5DC0B0 classification and
52B560 image installation remain explicit supplied leaves. Actual Cell/type/
registry/overlay/animation construction, primary associations, ClearTile, eight
relative-offset TMP fixtures, initialized variant tables and scenario/theater scale
are authored inputs. Only the isolated guest relocates TMP references. Native
uses Data-relative offsets on the existing type owners. This is not original
allocation/file/heap ownership, actual asset loading or complete leaf recovery.

All254 sequences match:206 standalone (including output aliasing) and48 composed
through terrain,24 of those through projection. They execute350 complete4712C0
calls,62 actual selector calls,222 GetImage calls,150 alternate selections,
50 flag tests,132 scales and22 zero-color constructors. Supplied leaves include
350 resident searches,112 overlay colors,30 resource classifications and60 image
installations. Joined cases execute192 iterator advances,144 intersections,
480 ordered RGB stores and480 projected pixels. All ordered output stores and
leaf arguments match. Standalone final image-presence fields and composed complete
RGB/pixel/bitmap backings also match.

The corpus covers resident/flag precedence, overlay index boundaries/forced data,
black/valid/negative-signed frame counts, resource fallback, ClearTile, count1 and
multi-variant paths, modulo/link traversal, lazy images, null TMP headers, flag4,
bit13, float32 fractional/zero/negative/infinite/NaN scaling and output aliasing.
Full Map/arena/type snapshots, immutable Cell/slot/source/code/constants/globals,
caller stack and saved registers are audited. Supplied image installs update the
expected type snapshot explicitly. No original instruction is patched. This is
local verification, not independent acceptance or whole-frame fidelity.

Canonical originals:
`private/boot-camp-20261020/cell-color-fresh-a1/expected.json`.
Fresh generation2.206s/native.050s/driver2.645s. Normal/sanitizer/uncached replays
each report254 hits/zero misses; wall.662/.657/1.478s. Rebuilt old terrain runners
retain all88 old expectations in both profiles (.320/.692s), without regeneration.
Ten Python checks, three CTests/profile, refusal-with-unchanged-output and four
caller-rounding modes pass. Initial inspection/edit/configure/build/task/repair
wall costs were not separately instrumented. No failed proof was accepted.
Checks: `private/boot-camp-20261020/cell-color-checks-a1.json`.
Receipt: `private/boot-camp-20261020/cell-color-receipt-a1.json`.
App/owner hashes retain prior SDL scope; no GUI acceptance/runtime change is claimed.

## Commands and next integration

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake -S . -B build/native
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake --build build/native --target cell-radar-color-vectors radar-terrain-vectors --parallel 6
build/tools-env/bin/ctest --test-dir build/native -R '^(cell-radar-color|radar-terrain|radar-projection)-domain$' --output-on-failure
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_cell_radar_color test_radar_terrain test_radar_projection
# Explicit supported reuse; select fresh report/audit paths.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/NEW-CELL-COLOR.audit.json tests/compare_cell_radar_color.py \
  --exe private/official-1006-probe/game.exe --native build/native/cell-radar-color-vectors \
  --terrain-native build/native/radar-terrain-vectors \
  --expectations private/boot-camp-20261020/cell-color-fresh-a1/expected.json \
  --report private/NEW-CELL-COLOR.json
```

For sanitizer select both runners under `build/sanitize/`; for the inspection
control add `--uncached` before the driver. Fresh generation replaces expectations/
report with new `--output` and needs research-only Unicorn JIT. Normal app commands
remain `./build.command`, `./test.command`, `./run.command --boot-camp-walk`.

Next bind/recover the required resident/overlay/resource/loading children on actual
Boot Camp map/tile/overlay owners, then join actual630A00 startup with aliased
projection/native storage and relevant first DSurface lock/pixel semantics. Keep
unrecovered leaves explicit; do not promote authored images or brightness inputs
to original asset provenance. Shared production House/coverage/actor integration,
live arrival/sight scheduling and ordinary SDL Objective1 acceptance remain open.
Both games remain incomplete; only Apple Silicon macOS is tested. No workers,
Windows actions, transfers, downloads or system changes occurred.
