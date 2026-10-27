# Prepared ground Unit and shadow drawing

The later [live movement/drawing join](MOVING_UNIT_WORLD_1006.md) changes the shared
native implementation. This earlier profile has fresh v3 evidence and both
replays, with commands/results/labels unchanged from v2. V2 and its measurements
below retain their historical identities. Current replay commands use v3.

After the shared implementation's height extension, this earlier nonpositive
profile has fresh `ground-unit-world-v2/` evidence with unchanged commands,
results and labels. V1 keeps its historical sources and timings. Current replay
commands below use v3; the separate height-aware entry is documented in
[GROUND_UNIT_HEIGHT_1006.md](GROUND_UNIT_HEIGHT_1006.md).

October 15, 2026, after `6957a16`. This profile joins shared finalized map Cells,
stock numeric/matrix initialization, actual Drive shadow pose/key, repeated
floor-relative height and shadow-point queries, and complete lit/shadow drawing.
**87 fresh results / 43 complete draws match the exact engine.** It is a
recovery checkpoint toward terrain-aware drawing, not a new playable
milestone. `drawGroundUnitVoxelToWorld` remains unwired. Complete base RA2 then
Yuri's Revenge remain active and incomplete.

## Exact engine and references

Both supplied private engines are 4,485,392 bytes / SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Fresh execution loads `private/official-1006-probe/game.exe`; the previously
approved Windows copy is rehashed equal, not separately executed for this join.
Embedded 1.08, supplied 1.006 lineage and reported no-CD modifications remain
separate provenance. Pristine authenticity is unverified. No Windows action,
transfer, source-install write, DRM/system change or replacement download.

Consulted [REFERENCES.md](REFERENCES.md), YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` `DriveLocomotionClass.h`,
`FootClass.h`, `ObjectClass.h`, `MapClass.h`, `CellClass.h` height/slope/locomotor
leads, and recomp snapshot `eebcf725ef99f942a8f9a5e0437a8a6154d7d439`
`docs/voxels.md` Shadows / MIT LICENSE. Hypothesis: original current-ramp pose,
relative height and repeated shadow-point queries must reach the actual cache,
stencil and world consumers together. Exact base instructions/execution decide
this result; YR names and recomp replacement presentation are not oracles.
Existing license boundaries remain: no YRpp license file found; recomp's MIT does
not authorize generated/lifted game code. No upstream/header/generated/lifted code
or extracted table incorporated; THIRD_PARTY.md is unchanged.

## Joined behavior

[verify_ground_unit_world.py](../tools/verify_ground_unit_world.py) pins the
existing complete Unit, Foot, staging, cache/pool, raster, final-surface and shadow
ancestors, prepared map/floor chain, stock numeric chains and Drive pose. It also
checks Unit's pose/height/predicate virtual consumers and the exact relative-height
vtable target. These are expanded joined profiles of inspected roots, not newly
recovered general rendering or startup routines.

The actual Unit root is `0x6FF690`; Drive pose is `0x4A0500` / `0x53D0D0`.
Relative height `0x5D4810` executes actual map floor `0x55A280` and Cell floor
`0x4706C0`. The actual stock Cell numeric chain supplies height `0x850C40=104`.
No service returns a precomputed floor, relative height or final depth. Preserve:

- Lit body/turret/barrel staging, one final world copy, restored staging flags,
  and a saved pre-shadow dirty rectangle for cleanup.
- The ten-bit body-derived Track shadow seed, actual Drive pose/key and camera
  product, including current Cell ramp selection and wrapped key writes.
- First relative-height query before the explicit current-Cell lookup. With
  predicate false, a second query adds key bit `0x80000000` when height <=0;
  the following query selects the ordinary nonpositive-height branch.
- Unit queries shadow-point Y and X separately, then Foot queries both again
  and adds that third point to the world position with dword wrapping. Each
  actual `0x53D1C0` point getter queries relative height and converts it through
  `0x6A2970`. Do not coalesce these calls. The first two point results become
  the staging stencil's origin. Nonzero negative Y is meaningful.
- Complete fresh/raw/cached shadow rendering, four independent indexes sharing
  one supplied pool, recursive cache reuse, clipping and saved-dirty cleanup.
  The native binding reuses established shadow raster/stencil/blit kernels.

The original harness attaches map bookkeeping/arenas to the same guest used by
Unit drawing. No finalized Cell records or final floor/draw outputs are imported from
another guest; initial type/resource/map records remain fixture inputs. Prior receipts supply input scenarios only. Before each draw the
actual stock numeric chains and complete matrix initializer run unchanged in this
guest. Other initializer outputs are outside the native numeric proof; the fixture
explicitly restores its supplied camera afterward. This is not original startup
invocation order or camera initialization recovery.

The new readable ground pipeline preserves earlier frozen flat entry points and
all lower kernels. `PreparedUnitDepth` still refuses a nonflat current Cell.
The new fixture separately binds stable prepared views, actual Foot predicates,
ordinary Unit base and available TMP dimensions. Its resident-current-Cell and
positive-height preflights are native safety guards outside the draw trace.

The fresh guest executes 43 Drive pose calls, **242 actual relative-height calls**,
**129 shadow-point getters**, 86 full-coordinate lookups, 7,307 CellStruct lookups
and 108 actual TMP dimension calls during drawing. There are 998 audited world/
setup roots and 22 audited map roots. Stock setup performs 860 numeric global stores and
10,836 shadow matrix dword stores across the 43 draws. Selected query/result order,
all shadow pose dwords/keys, final planes, saved cleanup and four indexes/pool
match; full memory-read/native write order is not claimed. Existing Drive-key
ordered-write proof remains the separate [prior profile](DRIVE_SHADOW_POSE_1006.md).

## Boundaries

Current Cell ramps 0..20 and zero/negative relative heights are supported in this
profile. Lit locomotor records remain explicitly **flat and settled**: the Cell's
ramp is not evidence for the body's stored current/previous ramp or its update.
Actor absolute Z, initial actor/type/map records, one-frame identity HVA, contact,
house/converter/palettes, camera, initial color and immutable depth/alpha planes and successful
heap/sufficient pool remain supplied. A zero relative height chosen by a fixture
is not recovered actor placement. No bridge, add-14, alternate type/status or
positive-height shadow matrix/point branch is enabled. Missing requested TMP
images and unsupported domains are refused rather than filled with guessed data.

Floor-to-actor placement/update and locomotor ramp association still precede
runtime promotion. General actor construction, startup/scheduling, cache ownership/
eviction/lifetime/invalidation, visibility/fog, original pathfinding and whole-frame
fidelity remain open. Existing prepared lit/flat world receipts keep their original
scope. Runtime executable reads and prepared data formats are unchanged; simulation
remains SDL-free. Only Apple Silicon macOS is tested.

## Reproduce

V2 receipts: `private/map-depth-1006/ground-unit-world-v2/`. The suite prepares
21 synthetic current-ramp maps and one full supplied map, then compares matrices,
selected query order/results, final RGB565/depth/alpha planes, staging cleanup, all four
indexes and normalized pool state. It includes parked `(51,72)`, elevation 4 and
crossing inputs, warm reuse, changed view/pitch/brightness/contact, raw bypass,
clipping and NoShadow. These supplied scenarios are not an SDL ramp playtest.

```sh
./build.command
./test.command
PYTHONDONTWRITEBYTECODE=1 build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

# Fresh original execution needs authorized Mac host JIT and a new private output.
PYTHONDONTWRITEBYTECODE=1 build/tools-env/bin/python tests/compare_ground_unit_world.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/ground-unit-world-new
PYTHONDONTWRITEBYTECODE=1 build/tools-env/bin/python tests/compare_ground_unit_world.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/ground-unit-world-v3/expected.json \
  --report private/map-depth-1006/ground-unit-world-v3/replay-new.json
# Add --native build/sanitize/ground-unit-world-vectors for sanitizer replay.

# Existing playable baseline; the new helper is not enabled there.
./run.command --crossing-light-demo
```

Fresh CLI/original-generation/native times are **618.494/527.686/0.125 s**.
Normal replay CLI/native times are **91.678/0.088 s**; sanitizer replay
**92.794/1.362 s**, both passing. Inspection/identity overhead is not separately
profiled. Eleven native safety refusals are separate from original parity. Closing replay/
verification, failed attempts and remaining work are recorded in
[HANDOFF.md](HANDOFF.md). Actual SDL level crossing and parked-cliff acceptance
remain required after placement/update integration. Local verification is not
independent acceptance or proof of original complete frames.

The observable capability target is a selected stock Rhino moving across the
prepared map's level crossing and parked at the cliff with terrain-derived height,
pose and occlusion. Completion requires exact-engine evidence for actor Z and stored
locomotor ramp updates, their joined drawing, then actual SDL input/render checks
for both scenarios. This checkpoint supplies only the shadow/height consumer join.
