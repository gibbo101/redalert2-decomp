# Prepared terrain through ordinary Drive movement and pose

After `ef434d3`, this checkpoint joins finalized shared Cells to actual actor
height, complete ordinary Drive Process/preparation/Advance, stored body ramps
and current-Cell shadow pose. **84 fresh results / 6,652 complete Process calls
and 13,304 body/shadow pose calls** match the exact supplied engine. The helper
is unwired. Complete Unit drawing and SDL terrain crossing/parked-cliff acceptance
remain required; complete base RA2, then Yuri's Revenge, remain incomplete.

## Identity and references

Both supplied copies rehash equal: `private/official-1006-probe/game.exe` and
`private/windows-baseline-20261014/game.exe`, 4,485,392 bytes / SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Fresh execution uses the first. Embedded 1.08, supplied 1.006 lineage and reported
no-CD modifications are distinct provenance; pristine authenticity is unverified.
No new Windows action, transfer, download, installation/disc write or system change.

Consulted [REFERENCES.md](REFERENCES.md), pinned YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` `DriveLocomotionClass.h` and the
retained recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439` LICENSE/context.
The hypothesis was that Process's stored ramp transition must remain distinct
from the shadow's current-Cell query when both consume finalized map records.
Exact base instructions/execution decide the result. YR names and replacement
behavior remain leads. No YRpp license file was found; recomp's MIT grant excludes
generated/lifted game code and its scope text has the previously recorded stale
The Movies wording. No upstream/header/generated/lifted code or extracted data
was incorporated. No dependency, prepared format or runtime binary-read expansion.

## Joined boundary

[PreparedDriveTerrain](../src/assets/PreparedDriveTerrain.hpp) borrows the final
Cell table, fallback record and lazy floor state. It binds full-coordinate lookup,
word-coordinate lookup, retained live-record access, Cell center and map floor
children to the existing [GroundDriveProcess](GROUND_DRIVE_PROCESS_1006.md).
The existing simulation kernels are unchanged and remain SDL-free. The binding
retains supplied Mark/admission/reservation/occupation/mission services, land speed,
slope factors and table square-root service. Records and the binding must outlive
all returned callbacks. An optional read-only owner check validates the supported
empty, nonbridge, overlay-free traversed Cell profile; it is outside original
query tracing. Native table/fallback/domain refusals are safety boundaries.

The original fixture attaches map bookkeeping and arenas to the existing movement
guest. It executes the actual later two-pass resident map/floor parent, both stock
numeric chains and the complete stock matrix/quaternion initializer there. The
older synthetic movement map allocations are replaced only inside the private
test guest. No second guest supplies prepared records or final movement/pose
outputs. Historical receipts provide scenario inputs only. This is an explicit
fixture invocation order, not recovery of the game's startup parent or actor
construction sequence.

Before each movement sequence, actual Object SetHeight(0) and Drive Unlimbo/Force
derive actor Z and initial stored ramps from this map. Initial coordinates/Z,
healthy actor/type fields, direction queue and destination remain supplied; the
subsequent Z and ramp values are outputs, not supplied settled pose inputs.
Each complete Process call is followed by actual Drive body pose `0x4A0050`,
shadow pose `0x4A0500` and relative height `0x5D4810` on that same actor/map.
Actual body type/Facing children execute; no precomputed pose is substituted.

Preserve the previous checkpoint's repeated queries, pre-movement ramp observation,
previous-before-current writes, three-tick timer, live fallback identity, float
land-speed clamp, ordered independent floor queries, signed accumulator/arrival
credit, queue tails and admission before non-Passive switch rejection. In addition:

- Body pose consumes stored previous/current ramps and their timer. Shadow pose
  independently looks up the actor's current Cell after movement. There are **96
  ticks where that Cell ramp differs from the stored current ramp** and **328
  ticks with different body/shadow matrices**. Do not replace either association.
- There are **288 actual quaternion interpolation calls**. Distinct previous/
  current stored values can persist after interpolation ends; their inequality
  alone is not an active-interpolation counter.
- Ordinary fractional movement retains Z without sampling a new floor. The
  joined fixture observes **153 positive and 194 negative floor-relative heights**.
  These are original outputs; forcing Z onto the floor each tick changes behavior.
- The owned parked `(51,72)` case derives **Z=416 / relative height=0** through
  actual SetHeight, using stock level height 104. This is routine/fixture evidence,
  not an SDL parked-cliff acceptance or original whole-frame observation.

## Evidence and limits

Current receipts: `private/map-depth-1006/prepared-drive-state-v2/`. All 21 ramp
indices, forward/reverse routes, turning, two-direction tracks, stationary zero
speed, null/-1/wrapped keys, signed tick wrap and four incoming native FP modes
are covered. Twenty-one synthetic maps plus the complete **13,515-Cell supplied
map** are freshly finalized. The owned map includes the crossing and parked cliff
inputs. Traversed Cells have no overlays/occupants; the rest of the map can retain
its finalized overlays. Floor lazy state and fallback identity are shared across
movement, pose and relative-height queries.

There are **4,134 preparation, 6,513 Advance, 4,412 SetHeight and 62 Drive Unlimbo
calls**, **11,589 Cell-floor, 30,483 full-coordinate and 1,167 word lookups** in
the joined movement/pose phase, and 22 audited map roots. Numeric setup makes
440 selected global and 5,544 shadow-matrix stores. The union contains 147 allowed
ranges; 96 roots enter during joined setup/movement/pose (map-root entry accounting
is separate). Earlier complete-range inspections are reused, not claimed as new
general routines. Return/ESP/callee-saved/caller tail, code/dispatch/table identities,
execution/write allowlists, immutable prepared Cells/registries, actor/locomotor/
fallback arenas, selected ordered stores/services, exact matrix dwords/keys and
final lazy floor state are checked. Full memory-read/native internal-write order
and arbitrary mutable/aliasing services are not proved.

Initial actor/type/map/resource/terrain/geometry inputs, route finding, successful
admission/reservation, Mark's marked-byte-only or preserving effects, occupation,
notifications/mission and zero retry delay remain supplied. Opaque temporary timer
padding is supplied at the child boundary. The chosen read-only type doubles
30.5/24.25 are fixture inputs, not recovered stock associations; rocking is zero.
General Mark/occupation/redraw effects and actor construction remain open.

The complete Unit/cache/raster/staging/depth/final RGB565 draw is **not** executed
by this new suite. Earlier [ground Unit drawing](GROUND_UNIT_WORLD_1006.md)
still has supplied flat/settled lit state and a nonpositive-relative-height guard.
Do not remove that guard based on this state-only evidence. The live positive
height cases require verification of the Unit shadow branch (inspection shows
its extra Y increment at `0x700489`), then actual body/turret/barrel/complete
drawing integration on the moving actor. That branch is a lead, not execution
proof from this suite. Cache invalidation/lifetime/ownership, full startup/frame
scheduling, original pathfinding, fog and whole-frame fidelity remain open.

Development v1 matched the same commands/results/labels but its metric named
`interpolating_stored_ramps` counted unequal stored ramps, including settled
timers. V2 corrects that label, records actual interpolation entries and tightens
post-sequence arena checks. V1 keeps its historical identities; it is not relabeled.
Early probes rejected an unmapped direct-address call, a missing named-service
allowlist entry and an extra native relative-height lookup event. These were
fixture issues; no original instruction was patched or failed expectation accepted.
The initial native build also caught a wrong loader argument and missing include.
No gameplay repair was needed because runtime is unchanged.

## Reproduce and continue

```sh
./build.command
./test.command
PYTHONDONTWRITEBYTECODE=1 build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

# Fresh original execution needs authorized Mac host JIT and a new private output.
build/tools-env/bin/python tests/compare_prepared_drive_state.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/prepared-drive-state-new
build/tools-env/bin/python tests/compare_prepared_drive_state.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/prepared-drive-state-v2/expected.json \
  --report private/map-depth-1006/prepared-drive-state-v2/replay-new.json
# Add --native build/sanitize/prepared-drive-state-vectors for sanitizer replay.

# Existing playable baseline; the new binding is not enabled here.
./run.command --crossing-light-demo
```

Select Rhino, G/right-click moves, L toggles the light, R resets. Only Apple
Silicon macOS is tested. Next verify complete drawing with these live body and
shadow associations, including positive relative height, before runtime adaptation
and actual SDL level crossing/parked-cliff checks. No new playable/frame claim.
Boundary verification, receipts and elapsed accounting are in [HANDOFF.md](HANDOFF.md).

Both current builds and replays, 742 Python tests, 52 normal / 51 sanitizer CTests
and source/AST/link/diff audits pass. The closing inventory has 94 replay sets /
4,620 source entries (4,886 transitive entries checked); 92 prior sets keep unchanged
identities without reexecution. V2 fresh CLI/original/native times are
134.719/116.468/0.174 s; normal replay 20.445/0.147 s, sanitizer 21.775/1.532 s.
Full inherited/failed-attempt work time is unavailable. The closing discovery
command initially ran zero tests because its glob contained literal quotes; that
attempt was rejected and the corrected command ran all 742 tests.
