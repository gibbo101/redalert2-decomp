# Ground Unit shadows above the prepared floor

The later [live movement/drawing join](MOVING_UNIT_WORLD_1006.md) changes the shared
native implementation. This earlier profile has fresh v3 evidence and both
replays, with commands/results/labels unchanged from v2. V2 and its measurements
below retain their historical identities. Current replay commands use v3.

After `a07db87`, this checkpoint extends complete ordinary Unit drawing through
the positive floor-relative-height shadow branch exposed by actual movement.
The earlier `drawGroundUnitVoxelToWorld` entry keeps its nonpositive-height guard;
the explicit `drawHeightAwareGroundUnitVoxelToWorld` entry shares its rendering
implementation and enables the additional branch. Both remain unwired. Complete
moving-actor drawing, runtime integration and actual SDL crossing/parked-cliff
acceptance remain required. Complete native base RA2, then Yuri's Revenge, remain
incomplete. **96 fresh results / 52 complete draws match the exact supplied
engine**, including all 21 current-Cell ramp indices and the supplied map.

## Identity and references

Exact supplied engine: `private/official-1006-probe/game.exe`, 4,485,392 bytes,
SHA256 `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
The authorized private Windows copy has the same bytes. Embedded 1.08, supplied
1.006 lineage and reported no-CD modifications remain separate provenance;
pristine authenticity is unverified. No new transfer, Windows action, installation/
disc write, download, DRM or system change.

Consulted [REFERENCES.md](REFERENCES.md), pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` `docs/voxels.md` Shadows / LICENSE
and YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88`
`DriveLocomotionClass.h`. Hypothesis: the positive relative heights observed in
[PREPARED_DRIVE_STATE_1006.md](PREPARED_DRIVE_STATE_1006.md) need a distinct
stencil-origin decision in the existing Unit caller. Exact base instructions and
execution decide the result. YR names and recomp's changed HD presentation remain
reference leads. Recomp's MIT grant excludes generated/lifted game code; its
explanatory scope retains the previously recorded stale The Movies wording.
No YRpp license file was found. No upstream/header/generated/lifted code, extracted
data or new dependency was incorporated. Runtime binary reads and prepared data
formats are unchanged; simulation remains SDL-free.

## Drawing boundary

[verify_ground_unit_height.py](../tools/verify_ground_unit_height.py) retains
the complete Unit/world, prepared-map/floor and stock numeric/matrix inspection
chain, then explicitly checks the **112-instruction / 368-byte aligned branch
span `0x700415..0x700585`**. This span is inside the earlier completely inspected
Unit root; it is not a newly recovered general routine.

With ordinary Track state, no bridge/add-14/status/type alternate:

- Keep the first relative-height query before the explicit current-Cell lookup.
  A false shadow predicate makes another query: height <=0 adds key bit
  `0x80000000`; height >0 replaces the key with -1. A true predicate skips that
  query/key decision. The separate following query chooses the point branch.
- Unit evaluates shadow-point Y, then X through separate actual getters. For
  positive height, `0x700489` increments **only that first Y**, with dword wrapping,
  before the X getter. These values become the stencil origin.
- Foot queries the point again and adds it to the world point with wrapping.
  Its Y is **not incremented**. Each point getter independently queries actual
  relative height and calls the original pixel conversion. Do not combine them.
- Both branches multiply the same shadow pose/camera operands and execute the
  actual Foot/shadow/cache/raster/pool/world children. Preserve separate indexes,
  raw bypass, conditional stencil, world-depth reads and saved pre-shadow cleanup.

The native extension changes no height placement: fractional movement must still
retain Z as established by the movement proof. It does not force actors onto the
floor or infer body tilt from the current Cell. Earlier public drawing/depth
guards stay intact. The new entry supports the height branch only; its lit
locomotor records remain explicitly flat and settled.

## Evidence and remaining work

V2 receipts: `private/map-depth-1006/ground-unit-height-v2/`. There are
**48 positive-height branches, 36 false-predicate key invalidations and four
nonpositive branches**. All **300 actual relative-height returns** are recorded:
276 positive, 12 zero and 12 negative. Boundary draws assert every repeated
original return at relative heights -1, 0, 1, 7, 8, 9 and 104, using synthetic
flat floor zero and the owned cliff's floor 416. No fixture label substitutes
for a returned height.

The complete guest makes 52 Drive shadow poses, **156 shadow-point getters**,
104 full-coordinate lookups, 8,218 word-Cell lookups and 370 actual TMP dimension
queries during drawing. There are 1,205 audited world/setup roots and 22 audited
map roots, 1,634 raw / 624 compressed shadow span calls, 52 gradient-2 / four
gradient-0 final surface calls, 1,040 numeric global stores and 13,104 shadow-matrix
dword stores. All 13,515 supplied Cells are finalized in the owned-map case.
Final RGB565/depth/alpha planes, dirty/staging cleanup, four indexes/normalized
pool state, shadow pose/key and selected query/result order match. Full memory-
read/native internal-write order and whole-frame fidelity are not established.

The new original fixture executes freshly finalized shared Cells, actual stock
numeric/matrix initialization, actual map/Cell floor and relative-height/point
consumers, and complete Unit drawing in the same guest. Historical receipts supply
map inputs only. No finalized Cell records, final pixels or poses transfer from
another guest. Separate fresh execution rechecks the earlier nonpositive drawing commands
after the shared native implementation changes; earlier receipts keep their
historical identities.

Development v1 matched all 96 results / 52 complete draws, but its synthetic
"zero-height" cases incorrectly used 104 as the floor of a level-zero Cell. The
owned cliff cases used the correct 416 floor. V2 corrects the synthetic boundary
inputs to floor zero and asserts every actual original relative-height return
for each boundary draw. Its additional branch counter is restricted to the
inspected branch span; inherited complete execution/write audits remain intact.
Native drawing code is unchanged between these runs. V1 retains its historical
identity and is not relabeled as corrected boundary coverage.

Both normal and ASan/UBSan replays pass. The earlier nonpositive profile has fresh
`ground-unit-world-v2/` proof and both replays, with unchanged commands/results/
labels. Both builds, 750 Python tests, 52 normal / 51 sanitizer CTests and source/
AST/link/diff audits pass. The current inventory has 96 replay sets / 5,174 source
entries (5,440 transitive entries checked); 92 prior sets retain unchanged identities
without reexecution. Source audit checks 924 candidates; private inputs/research
remain ignored. The arm64 app hash is unchanged; no new SDL capture was made.

V2 fresh CLI/original/native times: **889.691/777.733/0.176 s**; normal replay
**113.695/0.094 s**, sanitizer **113.689/1.565 s**. Development v1 took
926.213/813.680/0.154 s. The preserved profile's refreshed fresh run took
630.986/537.639/0.167 s; its replays 93.450/0.086 s and 93.802/1.345 s. Runs/checks
contended concurrently; no speed/FPS claim follows. Full inherited and failed-
attempt work time is unavailable. The normal build's elapsed time was not separately
measured; other boundary check times are in the handoff. No gameplay repair was
needed because runtime is unchanged. No original instruction was patched or failed
expectation accepted.

Initial actor absolute Z, flat/settled lit locomotor state, type/actor/map records,
one-frame identity HVA, camera, contact/house/converter/palettes, destination color
and immutable depth/alpha planes and successful heap/sufficient pool are supplied.
Unit shadow predicate, original-type visibility and brightness/status responses
also remain supplied services; their caller decisions execute. Both predicate
values test that boundary, not the predicate's general implementation.
This is not a movement-to-drawing join. Full actor/type construction, Mark and
occupation effects, live stored-ramp body/turret/barrel transforms, cache
ownership/invalidation/lifetime, startup/scheduling and whole-frame fidelity remain
open. Local verification is not independent acceptance or original whole-frame
observation. Only Apple Silicon macOS is tested.

The next required drawing join must consume the actual stored-ramp body matrix,
including its translation and turret/barrel pivot operations, on the actor moved
by complete Process. Then adapt the runtime and exercise actual SDL level crossing
and parked `(51,72)`, elevation 4. A cell's ramp alone cannot supply that body's
previous/current ramp timer state. Private complete-root inspection records the
barrel's translation/rotation/translation sequence as a lead; it is not new
execution evidence for tilted body drawing.

```sh
./build.command
./test.command
PYTHONDONTWRITEBYTECODE=1 build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

# Fresh original execution needs authorized Mac host JIT and a new private output.
build/tools-env/bin/python tests/compare_ground_unit_height.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/ground-unit-height-new
build/tools-env/bin/python tests/compare_ground_unit_height.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/ground-unit-height-v3/expected.json \
  --report private/map-depth-1006/ground-unit-height-v3/replay-new.json
# Add --native build/sanitize/ground-unit-world-vectors for sanitizer replay.

# Existing playable baseline; new drawing entry is not enabled here.
./run.command --crossing-light-demo
```

Select Rhino, G/right-click moves, L toggles light, R resets. The unchanged demo
still restricts routes to supported level terrain. Detailed final receipts,
verification and elapsed accounting are in [HANDOFF.md](HANDOFF.md).
