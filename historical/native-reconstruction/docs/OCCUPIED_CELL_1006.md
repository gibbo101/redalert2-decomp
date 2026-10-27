# Occupied Cell passability and joined Unit recalculation

Later [MEMBERSHIP_DRIVE_1006.md](MEMBERSHIP_DRIVE_1006.md) joins these actual
children into complete ordinary Process on shared prepared Cells. This note's
standalone/membership proofs retain their checkpoint scope; runtime adoption
still requires separate mutable simulation ownership and SDL acceptance.

After `1fa329a`, actual resident Cell recalculation joins Unit Mark/membership/
discovery/occupation on shared Cells. **796 fresh standalone results** and **367
fresh joined sequences / 1,921 complete calls** match native, with normal and
ASan/UBSan replays. Helpers remain SDL-free and unwired. Complete movement Process
integration, actor construction, original frames and complete base RA2 then YR
remain incomplete. This is a recovery checkpoint, not a new playable capability
or independent acceptance. No workers.

## Identity and references

Both private copies rehash equal: `private/official-1006-probe/game.exe` and
`private/windows-baseline-20261014/game.exe`, 4,485,392 bytes / SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 lineage and reported no-CD modifications remain
distinct; pristine authenticity is unverified. The authorized Windows copy was
already present. No new Windows action/transfer/download, source-install/disc/
outpost2 write, DRM/system change or runtime executable-read expansion occurred.

Pinned YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88` BuildingType
LaserFencePost/LaserFence, TerrainType occupation fields and Scenario Theater
declarations supplied naming leads. Native fields retain numeric names: base
inspection/execution decide behavior, not YR names/addresses or replacement code.
No YRpp license file was found. Retained recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` MIT text covers its own tools/docs,
excludes lifted/original code and retains stale The Movies wording. No upstream/
header/generated/lifted code, extracted table or new dependency enters Git or the
application. See [REFERENCES.md](REFERENCES.md).

## Recovered behavior

`verify_occupied_cell.py` pins complete passability `0x478F40..0x4790E9` and
actual Unit/Building/Terrain kind leaves `0x70A2D0/0x453C40/0x6E4B00`, including
their base vtable slots. These four ranges contain **148 instructions**. Reused
complete Cell/LAT/permission/lookup/TMP and membership/discovery children make
**110 ranges / 5,846 instructions** in the combined allowlist. Standalone enters
five / 225 instructions; the joined fixture enters 65 / 4,004 instructions.

Passability preserves permission first (false writes 7), crushable overlay 1,
wall 2, zero/unordered overlay speed 6, rock 6, and rubble 0 without visiting
occupants. Ordinary land 2 writes 4, land 6 writes 3; Wheel speed <= binary64
0.01 or unordered writes 6. The reused early helper retains its prior arithmetic.

Only primary head `Cell+0xE4` is traversed, following Object `+0x30`; alternate
head `+0xE8` is ignored. Unit kind 1 continues without a special result. Building
kind 6, type `+0x135A` nonzero, tests owner `+0x142`: nonzero writes 6 and returns;
zero continues without testing the other type byte. Otherwise type `+0x1359`
nonzero and actor mission `+0x4EC` neither 12 nor 8 writes 6 **and continues**.
Final 0, or a later Terrain, can overwrite that intermediate 6. Preserve ordered
assignment; do not accumulate or take a maximum.

Terrain kind 36 reads scenario global `0xA3D290`, field `+0x838`. Exactly 1
selects type `+0x27C`; every other value selects `+0x278`. Value 7 writes 2,
otherwise 5; the first Terrain returns immediately. End of list writes 0.
Raw bytes and signed mission/theater/type fields are retained. Stable Unit/
Building/Terrain lists are the native domain. Cycles, unknown kinds and missing
bindings are safety refusals, not original fault emulation. Selected records do
not promote Building/Terrain gameplay or construction.

`assets/OccupiedCellPassability` updates the destination before its read-only
store observer, including intermediate assignments. Native views are logical
records, not copied layouts. Full native machine read/store order, padding and
original ownership are not claimed.

## Shared membership fixture

New `K` input in `unit-membership-vectors` retains `U/J` domains and binds actual
`recalculateMapCellAttributes`, LAT, TMP/type lookup, permission and occupied
passability. Actual original `0x472540` executes instead of returning through a
supplied recalculation service. Membership head/Next changes are immediately
visible to passability. Attribute/passability stores and selected four-/ten-byte
map-buffer writes are compared in order after each root.

Coverage includes all 21 ramps, signed levels, primary/alternate occupation,
absent/invalid/sentinel images, subtile/type selection, warm fields, long Unit
lists, full-coordinate versus word aliases and shared fallback forwarding.
Fixtures supply initial actor/type/House/Cell/TMP/geometry/Wheel records, LAT
globals -1, cliff mode 0, no overlay, one existing tube, animation -1, ShadowCaster
0, null Tag and loading 1. TMP metadata is resident, without allocation. This is
not original startup, owned-map association or general actor placement. Floor,
visibility and membership share canonical fallback identity. Recalculation
observes current lists; it is not a diagnostic passability callback.

Standalone audits **796 original roots / 838 selected stores**, with 474 Unit,
198 Building and 156 Terrain kind entries. Joined audits **1,932 roots** (1,921
sequence calls plus 11 stock numeric/direction initialization roots), **22,543
selected stores**, **1,548 recalculations**, **536 occupied Unit-kind queries**.
Atexit remains a supplied service (734 calls); initial associations and optional
Tag execution retain earlier boundaries. Complete block/width/write allowlists,
immutable input/code/dispatch, full arenas, caller/return/callee-saved registers,
ordered selected events and lazy floor digests pass. Unused buffer capacity and
unselected bytes remain unchanged. Five standalone/four joined malformed/domain
refusals are separate native safety checks.

## Evidence and validation

Current private proofs, each with fresh original evidence and both replays:

- `occupied-cell-v2`: 796 standalone results.
- `occupied-membership-v2`: 367 sequences / 1,921 complete calls.
- `unit-membership-v5`, `unit-discovery-v3`, `unit-membership-discovery-v3`:
  fresh earlier domains after shared vector-source changes; commands/results/
  labels retain v4/v2/v2 respectively.
- `terrain-runtime-map-v8`: all 13,515 selected Cells / 255 owned-input slices
  retain v7 commands/results/inputs after the broad source/CMake inventory change.

Occupied v1 receipts remain historical. Standalone v1 predates the joined vector
change; joined v2 adds explicit entered-child assertions. Both v2 sets retain v1
commands/results/labels. No failed expectation was accepted or original instruction
modified. Early inspection corrected a guessed Terrain vtable using the previously
verified base slot; a test-only SubTile offset typo was fixed before compilation/
original joined execution. Two initial runtime replay CLI calls omitted required
`--data-dir` and exited before comparison; corrected calls pass and failure logs/
timings remain private. No runtime/playtest repair.

Both builds, **802 Python tests, 58 normal / 57 sanitizer CTests** pass. Actual SDL
regression passes: crossing78 updates; ramp44, 29 tilted / one stored-ramp lag /
23 positive-height samples; parked cliff Z416/depth-52/gradient2/153 visible/886
rejected pixels. This exercises the existing runtime, not new helpers; screenshots
and native checks are not original-frame fidelity evidence. Only Apple Silicon
macOS is tested. App hash remains
`61731c8f45379c83107b8b73e85848e65523ba7558245b5c256ce6b0c4f63617`.

Timings/closing source/receipt/AST/link/privacy audit are private under
`private/map-depth-1006/occupied-cell-*`. Full inherited research/delivery elapsed
is unavailable. Builds17.029/28.053 seconds, Python wall5.286 (unittest1.798),
normal tests3.252, sanitizer6.501, actual SDL1.845. Independent checks ran
concurrently; these are not total delivery time. Existing harmless duplicate
static-library warning remains; no sanitizer diagnostic.

Closing audit: **114 replay records / 7,412 source entries**, recursively 7,678;
**102 prior records unchanged without reexecution**, 471 Python ASTs. New notes
and handoff are checked for local links and private/build exclusions. Fresh CLI
times: standalone10.607, joined30.272, old membership15.471, discovery7.676,
joined discovery23.980, runtime28.887 seconds. Standalone/joined original
generation4.123/24.524 seconds; normal/sanitizer replay CLI5.666/7.965 and
3.445/5.776. Runtime replays5.249/12.089 seconds. Private per-check logs retain
all measured times; inherited and early failed-attempt totals are unavailable.

## Reproduce and next capability

```sh
./build.command
./test.command
build/tools-env/bin/python -B -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

# Fresh execution needs authorized Mac host JIT and new private destinations.
build/tools-env/bin/python -B tests/compare_occupied_cell.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/occupied-cell-new
build/tools-env/bin/python -B tests/compare_occupied_membership.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/occupied-membership-new
build/tools-env/bin/python -B tests/compare_occupied_membership.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/occupied-membership-v2/expected.json \
  --report private/map-depth-1006/occupied-membership-v2/replay-new.json
# Add --native build/sanitize/unit-membership-vectors for sanitizer replay.
# Standalone replay uses compare_occupied_cell.py and occupied-cell-vectors.
./run.command --terrain-demo
./run.command --parked-cliff-demo
```

Select Rhino, G crosses the ramp, R resets, Q/E turns, A/D aims, S finishes the
committed track and stops. Controls/routes/clearance/picking/camera/presentation
and initial actor records remain adapters.

Next join actual Mark/membership/discovery/occupation/recalculation into complete
ordinary Process on shared owned prepared Cells, forwarding live actor fields
and Cell mutations at original service boundaries. Then promote the supported
runtime profile with actual SDL move/stop/turn and state/query/write evidence.
`PreparedDriveTerrain::bind` intentionally retains caller Mark/occupation services;
do not replace them with partial mutable effects. Admission/reservation/mission,
construction/startup, raw overlay placement/primary TMP selection and ownership
remain explicit boundaries. Bridge gameplay/general pathfinding/combat/economy/
AI/campaigns/multiplayer/audio/original saves/YR remain later.
