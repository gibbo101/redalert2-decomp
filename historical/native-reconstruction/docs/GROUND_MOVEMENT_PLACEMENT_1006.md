# Drive location and ground-height placement

Follow-up: [complete committed Advance](GROUND_DRIVE_ADVANCE_1006.md) establishes
that `0x4A2054..0x4A2112` is reached at track completion. Its legacy helper name
`placeDriveResidualGround` must not be read as regular fractional interpolation:
that separate path updates location without SetHeight. The scoped evidence below
retains its original boundary; the later note verifies the complete parent domain.

After `1ce16a6`, **1,108 fresh exact-engine comparisons** and normal/ASan/UBSan
replays verify complete Foot/Object SetLocation and two aligned placement blocks
inside Drive Advance. Actual relative-height/map/Cell/floor children execute.
This is a locally verified recovery checkpoint; helpers are unwired and the demo
is unchanged. Complete native base RA2 then Yuri's Revenge remain incomplete.

## Identity, references and scope

Both supplied private engines were rehashed equal: 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Fresh execution uses `private/official-1006-probe/game.exe`; the approved Windows
copy already exists at `private/windows-baseline-20261014/game.exe`. Embedded
1.08, supplied 1.006 lineage and reported no-CD modifications remain distinct;
pristine authenticity is unverified. No new Windows action/transfer/download,
source-install/disc modification or system change occurred.

Consulted [REFERENCES.md](REFERENCES.md), pinned YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` `ObjectClass.h`, `FootClass.h`
and `DriveLocomotionClass.h`, and retained recomp snapshot
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` voxel context. Hypothesis: Drive's
location/height call order depends on Cell crossing and marked state; copying a
candidate's Z does not establish the final actor height. Exact base inspection
and execution decide the result. YR/recomp remain naming/research leads, not an
oracle. Existing license boundaries apply: no YRpp license file found; recomp
MIT excludes generated/lifted game code, with stale The Movies wording recorded.
No upstream/header/generated/lifted code or extracted table incorporated; no new
dependency/THIRD_PARTY.md change.

[verify_ground_movement_placement.py](../tools/verify_ground_movement_placement.py)
pins two complete new ranges / **33 instructions** and two executed aligned blocks /
**84 instructions**. It also inspects the entire **1,613-instruction Advance
parent** to verify those boundaries; it does not execute or recover that parent
as a whole. Existing height-family ranges/dispatch remain pinned.

| Address | Executed scope |
| --- | --- |
| `0x4CA160..0x4CA1A0` | Complete Foot SetLocation |
| `0x5D51C0..0x5D51DD` | Complete Object coordinate setter |
| `0x4A2054..0x4A2112` | Residual candidate Cell comparison and location/height placement |
| `0x4A1AB0..0x4A1AFB` | Committed same-Cell location/height placement, including on-map gate |

The second block can branch to `0x4A263A`; the harness stops **before that
cleanup instruction**. Entry registers, computed candidate and parent scratch
are supplied. Candidate calculation/selection, the other committed Cell-crossing
path, remaining Advance/Process, original route/clearance and frame scheduling
remain outside this proof. No synthetic guest instruction or original byte patch.

## Recovered behavior

[GroundMovementPlacement.cpp](../src/sim/GroundMovementPlacement.cpp) preserves:

- Foot saves the initial nonzero `+0x74` test. That branch calls Mark(0), reads
  supplied candidate coordinates through the complete Object setter, then Mark(1).
  A Mark service can change flags or candidate data; it does not cancel the saved
  branch's final Mark call. Object reads/stores X, Y, Z in that order.
- Residual placement divides each full signed coordinate by 256 toward zero,
  then compares the low **word** Cell coordinates. It does not replace that
  comparison with full integer Cell equality or independent map bounds.
- Same-Cell residual movement saves the marked byte, writes zero, runs Foot
  SetLocation, runs actual SetHeight(0), then restores the saved byte. This
  suppresses nested Mark calls. The computed candidate Z is an intermediate;
  the actual floor plus any bridge-height offset determines final actor Z.
- Cross-Cell residual movement calls Mark(0), Foot SetLocation, SetHeight(0), then
  Mark(1). These children can themselves call Mark when a supplied service leaves
  the marked byte set; no guessed deduplication is applied.
- The committed same-Cell block separately clears/restores the marked byte around
  location, **then** reads actor `+0x7D`. Zero branches to cleanup without a floor
  query. Nonzero clears/restores the marked byte again around SetHeight(0).
- Earlier SetHeight's pre-Mark bridge addition, post-Mark coordinate reads,
  wrapped Z and floor's lazy arithmetic remain unchanged. Simulation is SDL-free;
  floor/Mark services preserve its separation from assets and rendering.

Mark effects remain explicit supplied services. Fixtures exercise unchanged Mark,
a supplied marked-byte update, actor coordinate/bridge/on-map mutation, candidate
mutation and a final Z mutation. These prove caller ordering under those services,
not original Unit occupation/redraw/Mark behavior. Native store observers are
read-only; arbitrary aliasing and throwing-service behavior are not claimed.
Initial map/actor/level-height/static-plane state is supplied, not actual startup.
No body/world join or runtime field promotion follows from these isolated blocks.

## Evidence and reproduction

Receipts: `private/map-depth-1006/movement-placement-v1/`. All 21 ramps, negative/
zero/elevated levels, zero/nonzero marked and bridge bytes, on-map skip, signed
coordinate limits, word aliases, resident/fallback floor lookup and supplied
mutations are covered. Selected identical cases run in four native incoming FP
modes; every call restores the incoming mode. Exact actor/candidate bytes, selected
ordered scalar stores/services and lazy-floor/fallback state match.

Counts: **100 audited complete roots, 1,008 scoped Advance blocks, 1,108 actual
Foot/Object location calls, 960 SetHeight/map-floor/Cell-floor calls, 1,884 FTOL
calls, 6,164 actor scalar stores and 1,260 supplied Mark calls**. The floor parent
does not enter the separate `0x548000` current-Cell getter. Guards check exact
dispatch/code identity, inspected execution bounds, complete-call return/ESP/
callee-saved/caller tail, block endpoint/ESP/preserved parent records, selected
scratch writes, immutable inputs/code, arena/fallback canaries and permitted image/
actor writes. Full read order/native lazy-initializer store order remain unproved.
Thirteen native malformed/domain refusals are separate safety checks.

The first generation stopped on an inherited timer-fixture setup that this family
does not use. Two comparisons then rejected observer mistakes: an extra native
current-Cell event and high register bits reported for a one-byte store. The harness
now uses the actual call trace and masks observed writes to their actual width.
In the latter two diagnostics, compared final state matched. No failed expectations
were accepted or original instructions modified. The corrected fresh run passes. Fresh CLI/
original/native times: **5.187 / 3.306 / 0.082 s**. Closing checks/times and retained
unchanged application evidence are in [HANDOFF.md](HANDOFF.md).

```sh
./build.command
./test.command
PYTHONDONTWRITEBYTECODE=1 build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

# Fresh execution needs authorized Mac host JIT and a new private output.
build/tools-env/bin/python tests/compare_ground_movement_placement.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/movement-placement-new
build/tools-env/bin/python tests/compare_ground_movement_placement.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/movement-placement-v1/expected.json \
  --report private/map-depth-1006/movement-placement-v1/replay-new.json
# Add --native build/sanitize/ground-movement-placement-vectors for sanitizer replay.

./run.command --crossing-light-demo
```

The demo is unchanged: select Rhino, G/right-click moves, L toggles light, R resets.
Only Apple Silicon macOS is tested. Next bind these actual placement children to
the complete ordinary Advance path and stored ramp/body state on prepared Cells,
then complete drawing/runtime integration. Actual SDL level crossing and parked
`(51,72)`, elevation 4 remain required. No new playable or whole-frame fidelity claim.
