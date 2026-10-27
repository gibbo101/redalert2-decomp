# Terrain admission in the native demo

After `29eba92`, the opt-in terrain demo enables actual gates, Unit admission and
required next-Cell on its owned mutable map. Those decisions share complete
ordinary Process and live Mark/membership/discovery/occupation/recalculation.
The fixed stock test refuses a right-click from Cell (73,41) onto (74,41), whose
Track speed is zero, while crossing/ramp/stop/turn/cliff regressions remain intact.
This is one ordinary Unit on an otherwise actor-empty map, not playable gates,
general collision/pathfinding or complete base RA2. The whole-game goal remains
active; Yuri's Revenge follows base RA2. No workers were used.

## Runtime ownership and commands

`TerrainScenario` reads the owned HTNK Crusher byte and checks the supported
missing MovementRestrictedTo input before explicitly enabling
`PreparedUnitAdmission`. Legacy supplied reserve/admit callbacks are removed;
the virtual Process entry uses actual decisions. Initial type/House/registry/
direction/owner/mission associations retain their earlier supplied scope.

All 24 `GroundDriveProcessState::route` words now persist between ticks. The
public `Drive::route` is only the visible prefix ending at the first -1. Explicit
move/waypoint, stop and body-turn commands replace the complete queue; ordinary
ticks, copies and previews retain its tail. Direct mutation of the public Drive
route is not a supported ground command interface. Target lifetime, sampled
footprint clearance and direct route construction remain host policies.

The route preview clones complete mutable state and runs actual Process on the
clone. A refusal leaves live actor/Cells/lists/occupation/House/buffers/lazy state
and queue unchanged. A successful command changes its queue at the command
boundary; it does not apply the preview's simulated map or movement state.
Concrete `TerrainUnitContext` copying and moving are now explicitly prohibited.
Move owning pointers or rebuild through `clone()` so callbacks keep stable
addresses. The admission owner retains its existing immovable guard.

`UnsupportedGroundAdmission` carries an unsupported Advance result. Preview
reports an explicit unsupported command and returns false; unrelated exceptions
still propagate. Live stepping propagates this refusal because its missing
effects cannot be fabricated. No rollback of partially executed live effects is
claimed. A supported refusal that ends short of the target is reported as
movement rejected, not arrival or preview timeout.

`terrainCommandCell` keeps host local bounds, scenery and unsupported missing/
overlay/tube/bridge/ramp/land guards. It deliberately does not apply the older
zero-speed whitelist. Actual admission now makes that terrain decision. These
guards and the sampled footprint are not recovered tactical picking, original
pathfinding or a general collision system. Shared renderer preparation remains
immutable; every simulation and preview owns independent mutable Cells.

## Exact original evidence

The complete owned-map proof has **232 fresh results / 18,088 complete original
Process ticks**, including 128 actual blocked-state samples in four incoming FP
modes. All samples retain (18816,10624,832), driving false and queue prefix
[-1,4,5]; the final queue word remains -1. Actual admission returns are 261 zero /
90 code7, with 346 first / three second / two Advance callers. All 411 gate checks
return true; next-Cell enters 256 times. There are 1,376 actual Mark/recalculation
calls, 256 eligible old-location unmarks, 15,610 selected membership stores,
50,851 selected preparation stores and 90 supplied retry-padding words. Each
tick's actor57A is sampled from the guest, with 36,176 body/shadow pose calls and
4,587 distinct entered original instructions. Stored/current-Cell ramp lag occurs
on 80 ticks; 280 matrices differ, with 124 positive / 120 negative relative-height
samples. These are scoped routine/state results, not complete original frames.

The expanded production binding proof is
`private/map-depth-1006/owned-unit-admission-v6/`. It adds the stock blocked route
in all four incoming FP modes, with a queue that retains words after rejection.
The earlier 228 command/result/label projections remain an unchanged prefix.
Code/input/arena/stack/register/write checks and unsupported-branch guards remain
active. Same-guest original finalization and live membership effects precede the
actual decisions; no original result records supply native runtime state.

This profile still has no stationary residents. Its gate checks return true;
self-skip, result3 and false-gate branches are not new joined coverage. Earlier
standalone/diagnostic proofs keep those scopes. Do not describe the single-Unit
stock test as a playable gate or multi-actor collision demonstration.

The scoped input proof `unit-movement-restriction-v3/` has **11 fresh results**,
33 audited constructor/loader blocks and 260 distinct entered original
instructions, followed by normal and ASan/UBSan replays. It executes the two
constructor default/store blocks and the exact missing-section/missing-key loader
block with actual ReadString, trim/copy and locale-zero enum children. Neighboring
BA4 byte writes and their order are checked for five supplied raw AL bytes;
stack/register/arena/code/locale inputs remain audited. Initial decoded hot
indexes and live registers are supplied. This is not a full constructor, original
text/index parser or present-value enum proof. Present MovementRestrictedTo keys,
including empty/None/-1 text, are explicitly refused by the native reader.
MovementZone remains a separate field. The owned runtime rules hash must equal
the private rules export used for this input proof.

Both private engines remain 4,485,392 bytes / SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 lineage and reported no-CD status remain distinct;
pristine authenticity is unverified. No new Windows action or transfer occurred.
Pinned YRpp supplied the earlier naming lead; exact base instructions and
execution establish the scoped association. Existing YRpp license absence and
recomp MIT exclusions remain as recorded in [REFERENCES.md](REFERENCES.md).
No upstream/header/generated/lifted code, table or dependency was incorporated.

## Regression and presentation evidence

Both builds, **859 Python tests / 63 normal / 62 sanitizer CTests** pass.
`ground-command-check` uses diagnostic Process outcomes to test queue retention,
explicit command resets, clone/preview isolation, typed refusal, unrelated fault
propagation and rejection status. These checks establish host ownership and
control semantics, not original gameplay fidelity. Production native membership
checks additionally snapshot the full owned state around the actual stock
admission rejection and successful preview.

The rebuilt arm64 SDL app passes injected-event selection/right-click/G movement,
actual zero-speed terrain refusal, active-track stop, body/turret turns and live
membership. Crossing remains 78 updates; ramp remains 44 updates / 29 tilted /
one lag / 23 positive-height samples. Parked cliff remains Z416 / depth-52 /
153 visible / 886 rejected pixels. The blocked scene keeps the actor at
(18816,10624,832). Native frame, CSV and admission diagnostics remain private.
The rendered blocked-terrain frame was visually inspected. These are native
integration/presentation checks, not original screenshots or whole-frame parity.
OS-level pointer/keyboard input, original-game timing, independent acceptance,
audio and platforms beyond Apple Silicon macOS remain unverified.

Application SHA256:
`a2a76ab3591efc03a037233c7a81de53f5509206fdd37f74175791f17020f7d1`.

All 11 affected legacy families have fresh original execution and normal/sanitizer
replays with unchanged earlier command/result/label or map-input projections:
unit-admission-v6, movement-gate-v7, unit-next-cell-v4,
ground-drive-admission-process-v4, ground-drive-gate-process-v7,
ground-drive-process-v8, prepared-drive-state-v9, moving-unit-world-v6,
membership-drive-v6, runtime-membership-v5 and terrain-runtime-map-v20.
All 33 refresh checks pass. The map projection retains 13,515 selected Cells /
255 source slices. The current inventory is **132 replay records / 9,762 source
entries**: 106 unchanged prior source/runner/expectation identities, 22 refreshed
legacy replays, two corrected owned-admission replays and two restriction replays.
Earlier receipts remain historical; no earlier profile is enlarged by a refresh.

Private `runtime-admission-*` receipts record builds/tests, fresh/replay times,
source/runner/receipt identities, links/AST/privacy audits and delivery. Initial
complete builds took 15.339s / 32.730s; final incremental native/sanitizer builds
25.603s / 10.149s. Final Python wall time is 2.754s (859 tests), normal CTests
1.980s, sanitizer CTests 14.988s and actual SDL 8.332s. Explicit owned-data terrain
checks took 4.268s / 23.576s. New owned proof fresh CLI is 452.074s, comprising
408.962s original generation and 0.568s native comparison plus identity/inspection
work. Normal/sanitizer replay CLIs are 52.164s / 59.804s, with 0.591s / 9.703s
native comparison. Restriction fresh/normal/sanitizer CLIs are
1.840s / 0.905s / 1.145s. The corrected focused blocked probe took 44.479s.
Moving-world fresh CLI took 1398.480s, including 1246.685s original
generation and 0.204s native comparison. These are verification
measurements, not native gameplay performance. Concurrent times must not be
summed; total inherited research/delivery and initial unwrapped build elapsed
remain unavailable. Existing duplicate static-library warnings persist; no final
sanitizer diagnostic or new SDL playtest repair occurred.

The rejected v5 coverage attempt took 441.227s fresh / 37.642s normal replay /
45.350s sanitizer replay; its successful comparisons do not establish rejection.
Early unsuccessful terrain probes took 1.906s / 2.800s; the corrected diagnostic
took 2.670s. Other exploratory/failed logs remain private, with unavailable
individual elapsed times left unclaimed.

The v5 fixture's four intended blocked cases inherited a positive synthetic
Track-speed table and actually moved. Its native comparison and replays passed,
but those labels were rejected as blocked-route evidence. v6 explicitly supplies
zero Track speed for those cases and requires 128 actual guest state samples:
unchanged position, driving false, retained queue tail and an actual admission7
return. A focused original/native probe passed before the complete v6 run.
The runtime independently checks the stock target's actual zero Track speed;
the joined fixture does not establish complete stock speed-table initialization.

Early native probes incorrectly required the old zero-speed host whitelist and
found no eligible rejection. The checks were corrected to distinguish supported
domain from original admission. An inherited snapshot assertion was updated for
the intentional command-boundary queue change; it still checks every other
owned field. The first scoped comparison used a nonexistent loose rules.ini;
an existing private scenery export was selected instead. v1 stays historical
after the rules-path receipt guard was added. The closing audit then caught
v2's older rules hash, f34900cb..., differing from runtime fd1e95ce.... v3 repeats
the same scoped results with the exact effective runtime rules exported in the
resident fixture; its rules hash must match the terrain proof. v1/v2 retain
their historical identities. All
failed/exploratory logs remain private. No failing comparison was accepted.

## Try and continue

```sh
./build.command
./test.command
build/tools-env/bin/python -B -m unittest discover -s tests -p 'test_*.py'
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
./run.command --terrain-demo
./run.command --terrain-smoke-test private/map-depth-1006/terrain-admission-local-new

# Fresh original execution requires authorized host Unicorn JIT and a NEW output.
build/tools-env/bin/python -B tests/compare_owned_unit_admission.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/owned-unit-admission-new
build/tools-env/bin/python -B tests/compare_owned_unit_admission.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/owned-unit-admission-v6/expected.json \
  --report private/map-depth-1006/owned-unit-admission-v6/replay-new.json
build/tools-env/bin/python -B tests/compare_unit_movement_restriction.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/unit-movement-restriction-v3/expected.json \
  --report private/map-depth-1006/unit-movement-restriction-v3/replay-new.json
# Add --native build/sanitize/<respective-vector-runner> for sanitizer replay.
```

Select Rhino; G follows the fixed ramp route, right-click requests a direct route,
Ctrl-right-click appends a waypoint, Q/E turns the body, A/D the turret, S finishes
the committed track then stops, R resets. The smoke command stages the separate
stock blocked-terrain check after movement/stop/turn/crossing/ramp/cliff.

Next extend the same owned-map/list/type/House associations to a stationary
resident and verify the occupied result through complete Process and membership.
The intended next capability is a move toward another parked Unit that preserves
both memberships and refuses occupation, while movement across empty Cells still works.
The standalone proof already observes allied stationary Unit result6; the current
joined Process profile accepts only preparation results0/3/7. Recover the actual
chosen resident's caller effects before adopting it; do not substitute result7
or a generic blocked boolean to fit the existing profile.
Shared resident construction/recalculation/Next and drawing/selection acceptance
must precede a multi-Unit playable claim. General pathfinding, combat, economy,
AI/campaigns/multiplayer, save compatibility and YR remain later work. No runtime
executable-read expansion, source-install/disc/outpost2 mutation, system/Xcode/DRM
change, worker or publication occurred.
