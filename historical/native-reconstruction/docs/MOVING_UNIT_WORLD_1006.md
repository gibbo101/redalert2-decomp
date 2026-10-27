# Live ordinary Drive state through complete Unit drawing

This checkpoint joins the actor moved by complete ordinary Process to complete
body/turret/barrel, shadow, cache, staging, Foot/base depth and final RGB565 drawing.
The native entry is `drawPosedGroundUnitVoxelToWorld`; it remains unwired. Runtime
promotion and actual SDL terrain crossing / parked-cliff acceptance remain required.
Complete native base RA2, then Yuri's Revenge, remain incomplete.

## Exact input and references

The supplied base executable is `private/official-1006-probe/game.exe`, 4,485,392
bytes / SHA256 `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
The authorized private Windows copy has the same bytes. Embedded 1.08, supplied
1.006 lineage and reported no-CD modifications remain separate provenance;
pristine authenticity is unverified. No new transfer, Windows action, download,
source installation/disc write, DRM change or system-wide tool change is involved.

Consulted [REFERENCES.md](REFERENCES.md), pinned YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` `DriveLocomotionClass.h`,
`TechnoClass.h` BarrelFacing and `Matrix3D.h`, plus recomp snapshot
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` `docs/voxels.md` / LICENSE.
Hypothesis: a live stored-ramp body matrix must reach the complete Unit caller;
rebuilding a flat matrix from heading loses its tilt and translation. Exact base
instructions and execution decide the result. YR declarations and recomp's changed
HD rendering remain leads. No YRpp license file was found. The recomp MIT grant
excludes generated/lifted game code and retains the previously recorded stale
The Movies scope wording. No upstream/header/generated/lifted code, extracted
content or new dependency was incorporated. Runtime executable reads and private
prepared formats are unchanged. Simulation remains SDL-free.

## Drawing contract

[GroundUnitVoxelWorld](../src/render/GroundUnitVoxelWorld.hpp) adds an explicit
result-bearing body pose service. The caller initializes the key seed to zero
when enabled, otherwise -1. Actual Drive pose mutates that seed before Unit adds
the frame bits. The existing flat/nonpositive and flat/height-aware entries retain
their supplied lit-state contracts and the earlier nonpositive guard.

The complete Unit root `0x6FF690..0x7005A5` consumes actual Drive body pose
`0x4A0050`. Its cold turret path rotates this matrix by the quantized turret
angle minus quantized body angle, with the original binary64 subtraction followed
by a float32 angle store. The ordinary profile has stock TurretOffset zero; no
nonzero offset or recoil association is inferred.

The barrel path saves the turret matrix's translation, translates by its negation,
rotates X/Z by the negative quantized barrel angle and translates by the saved
pivot. The original `0x5900F0` stores X/Y translation accumulators after each
component but retains the Z accumulator at full precision across its intermediate
stores. Camera multiplication follows these operations. A warm turret plus any
present warm barrel bypasses pose construction and forwards the untransformed
body matrix, even though the cached child does not use its geometry. Part ordering,
keys, staging flags and saved pre-shadow cleanup remain intact.

Shadow pose independently uses the actor's current Cell, its Drive timer and
rocking state. It must not reuse the body's stored ramp or matrix. Preserve the
height profile's repeated actual height queries, positive stencil-Y-only increment,
independent X getter, Foot's later world point and wrapped additions. Fractional
Process movement retains actor Z; drawing does not force it onto the floor.

[verify_moving_unit_world.py](../tools/verify_moving_unit_world.py) checks the
complete earlier inspection ancestors and the aligned turret/barrel consumer
span `0x6FFC14..0x6FFDCF`. These are joined profiles of already inspected roots,
not a new general graphics or startup API.

## Shared original fixture

The graphics guest owns the original loaded VXLs, finalized map, stock numeric/
matrix/quaternion initialization, actor, locomotor, floor lazy state, pool and
four indexes. [AttachedMovement](../tests/original_moving_unit_movement.py) binds
ordinary movement services explicitly to that guest's actor/type/locomotor arenas.
Its extra service/type/country/rules arena is disjoint from graphics storage.
No second original guest supplies final Cells, movement state, poses or pixels.
Historical receipts provide scenario inputs only.

Actual SetHeight(0) and Drive Unlimbo initialize height and stored ramps, followed
by complete Process/preparation/Advance. Drawing keeps the resulting location,
body Facing, stored ramps and timer intact. It changes only its explicit
presentation/type/surface fixture inputs and checks actor/locomotor immutability
during drawing. The fixture does not restore a moved actor from another guest or
supply a final settled pose. Selected supplied rocking fields test the nonzero
translation/pivot consumer on this same live actor; they are not recovered physics.

The native test binds the same prepared map to `PreparedDriveTerrain` and the
existing SDL-free movement kernels, then passes the live state to both Drive pose
consumers and complete drawing. Draw commands contain no supplied body heading or
absolute location. Exact forwarded part matrix dwords are compared even on warm
branches, in addition to body pose/key, shadow matrix/key, selected ordered queries,
final RGB565/depth/alpha planes, staging cleanup and four indexes/normalized pool.

## Evidence

Fresh evidence is `private/map-depth-1006/moving-unit-world-v1/`:
**228 results / 867 complete Process calls / 92 complete Unit draws** match the
exact supplied engine. All 21 ramp indices, interpolation/settled states, cold and
warm parts, raw bypass, clipping, NoShadow, barrel absence and supplied rocking
are represented, followed by the owned map's parked cliff and four crossing
sequences. Movement entry varies across four native rounding modes with restoration;
drawing uses its default caller mode and scoped original rounding.

Actual returned state establishes **24 stored/current-Cell ramp-lag draws,
20 positive-height draws, 17 negative-height draws and five nonzero body-translation
draws**. This is not coverage inferred from scenario names. The owned parked
actor derives Z=416 through actual SetHeight; 13,515 shared Cells are finalized.
There are 92 actual body poses, **274 forwarded part matrices**, 92 shadow poses,
**512 actual relative-height returns**, 276 point getters, 184 full-coordinate
and 14,557 word-Cell lookups and 229 TMP dimension queries during drawing.
The original positive stencil-Y branch enters 20 times; its other point branch
enters 72 times. The scoped consumer inspection is **111 instructions / 443 bytes**.

The fixture audits 1,596 world/setup/movement roots and 22 map roots, with the
complete existing inspection ancestors, instruction/write allowlists, caller
return/ESP/callee-saved/tail checks, immutable map/type/table inputs and selected
actor/locomotor/fallback arena changes. Complete Process state, selected ordered
queries/stores, body/shadow keys, exact forwarded part matrix dwords, final color/
depth/alpha planes, four indexes/normalized pool and staging cleanup match.
Full memory-read/native internal-write order and arbitrary mutable/aliasing
services are not established.

Normal and ASan/UBSan replays pass. Fresh CLI/original/native times are
1367.935 / 1212.301 / 0.300 s; normal replay CLI/native 159.270 / 0.168 s,
sanitizer 159.261 / 1.899 s. Earlier ground and height profiles have fresh v3
proofs and both replays, with unchanged commands/results/labels. The closing
audit retains 98 replay sets / 5,814 source entries (6,080 transitive entries
checked); 92 prior sets remain unchanged without reexecution. Both builds,
759 Python tests and 52 normal / 51 sanitizer CTests pass. Full inherited work
time and separate normal-build time are unavailable. See the handoff for measured
boundary checks and development failures; this is local verification, not
independent acceptance or completed SDL delivery.

## Boundaries and next work

Healthy ordinary Move, Accelerates=IsTrain=Passive=0, nonbridge, empty overlay-free
traversed Cells, supplied sentinel-terminated routes/speeds/slope factors, successful
admission/reservation and supplied Mark/occupation/mission/notification effects
remain the movement domain. Opaque timer padding is supplied at the child boundary.
Initial actor/type/map/resource/terrain records, type doubles 30.5/24.25, selected
rocking, one-frame identity HVA, turret/barrel facings, camera, contact, house/
converter/palettes, brightness/status/visibility/predicate responses, initial color
and immutable depth/alpha planes and successful heap/sufficient pool remain supplied.
These fixture inputs do not establish stock construction, physics, original camera
or whole frames. General cache invalidation/ownership/lifetime, startup/scheduling,
Mark/occupation effects, fog, pathfinding and arbitrary mutable services stay open.

The next capability work is runtime promotion followed by actual SDL movement
across supported prepared terrain and parked `(51,72)`, elevation 4, with derived
height, pose and occlusion. Do not enable unsupported overlays/bridges/general
routes or claim original full-frame fidelity from native-only tests/screenshots.
Only Apple Silicon macOS is tested. There is no new SDL capture for this unwired
entry; earlier evidence applies to the unchanged runtime only.

```sh
./build.command
./test.command
PYTHONDONTWRITEBYTECODE=1 build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

# Fresh execution needs the authorized Mac host JIT and a new private directory.
build/tools-env/bin/python tests/compare_moving_unit_world.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/moving-unit-world-new
build/tools-env/bin/python tests/compare_moving_unit_world.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/moving-unit-world-v1/expected.json \
  --report private/map-depth-1006/moving-unit-world-v1/replay-new.json
# Add --native build/sanitize/moving-unit-world-vectors for sanitizer replay.

# Existing playable baseline; the new entry is not enabled here.
./run.command --crossing-light-demo
```

Select Rhino, G/right-click moves, L toggles light, R resets. The existing demo's
route restrictions remain in force. Accounting and delivery limits are recorded
in [HANDOFF.md](HANDOFF.md).

Development notes: the first joined pilot rejected an omitted supplied map-slot
count. The map parent installs its table pointer, but this fixture must supply
`Map+0x13C=262144` before movement, as the earlier prepared-state fixture does.
Supplying it only during drawing made earlier floor queries return zero and
skip slope speed factors. The corrected pilot matches 12 ticks / two complete
draws; native movement code did not change. The earlier ground and height suites
have fresh v3 proofs and both replays, with unchanged commands/results/labels.
The complete joined proof above was then generated freshly; development logs
remain private and are not relabeled as accepted receipts. The extended pilot
matches 26 ticks / seven draws, including nonzero translation/pivot. Earlier
probes also rejected an unaligned inspection tail, an overlapping service arena,
missing supplied speed records, drawing dispatch left in movement-service mode
and a missing register import. A pivot-pilot invocation omitted its required
executable argument and was rerun correctly. No original instruction was patched
or failed expectation accepted; no gameplay repair was needed because runtime
is unchanged.
