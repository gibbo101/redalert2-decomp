# Admission and live Unit membership on owned Cells

The later [runtime adoption](RUNTIME_ADMISSION_1006.md) enables this binding in the
terrain demo after queue/lifetime/refusal guards and scoped missing input proof.
Statements below about the unwired demo describe the `29eba92` checkpoint.

After `d7edfebe`, the production owned-map binding joins actual gate checks,
Unit admission and required next-Cell with complete ordinary Process and live
Mark/membership/discovery/occupation/recalculation. Current proof is
`private/map-depth-1006/owned-unit-admission-v4/` matches **228 fresh results /
17,960 complete original Process ticks**, followed by normal and ASan/UBSan
replays.

This entry requires an explicit `TerrainUnitContext::enableAdmission`; the
terrain demo does **not** enable it yet. This is a movement prerequisite, not a
new playable collision/gate capability. Complete base RA2, then Yuri's Revenge,
remain incomplete. No workers were used.

## Ownership and binding

`assets/PreparedUnitAdmission` borrows the same canonical `MutableUnitMap`,
`PreparedUnitMembership` and stable `GroundDriveProcessState` as movement and
Mark. Before every gate/admission/next-Cell decision it refreshes Cell level,
ramp, flags, land, both list heads and both occupation dwords from live owned
storage, together with the actor's actual Next and discovery/mission state.
It does not derive decisions from the initial prepared rendering snapshot.

Inner word lookups forward fallback-coordinate writes immediately through
`PreparedUnitMembership::world()`. Map, floor, list and visibility views therefore
share the current fallback identity and coordinates. No deferred end-of-tick copy
or mutation of renderer/preview preparation is used. A small const membership
accessor keeps its internal Cell-ID base private.

The context replaces the legacy supplied `reserve/admit/markNext` services only
when explicitly enabled. Its virtual Process dispatch selects the admitted entry;
the legacy entry remains the default. Cloning reconstructs the admission owner
against independently cloned Cells, actors, lists and buffers, and drops query,
decision and Drive-store observers. Moves retain stable callback addresses.
The admission owner itself is explicitly noncopyable/nonmovable; only its owning
pointer moves. Native compile-time checks enforce that lifetime boundary.
Concrete `TerrainUnitContext` objects also require a stable address: existing
consumers move their owning pointers or reconstruct through `clone()`. An explicit
concrete-context move prohibition remains a safety guard to add before adoption;
the current replay and runtime paths do not relocate those objects.

The accepted domain is **one nonbridge Unit and otherwise empty resident lists**,
House0/loading1/null Tag, empty registry/weapons, unpromoted state and supplied
ordinary type associations. Primary lists can contain self. Stationary residents
are refused before a decision: their separate admission proof does not establish
shared Building/Unit list construction or occupied recalculation here. No gate
animation or playable gate behavior is established by empty/self-only traversal.

## Field-label correction and exact identity

UnitType **+B94 is `MovementRestrictedTo`, not `MovementZone`**. Pinned YRpp's
`UnitTypeClass.h` supplied the naming lead. Exact base instructions establish
the association:

- `70A607` sets EDI=-1; `70A61B` stores it at type+B94.
- `70AD45` reads the old field; `70AD4E` pushes `"MovementRestrictedTo"`.
- `70AD5A` calls `46A970`; `70AD5F` stores the result back at type+B94.

The verifier hashes and checks these aligned blocks and the key. Their inspection
does not execute the omitted constructor/INI loader. That reader is an enum/string
reader, not the ordinary integer GetInt.
The owned HTNK entry has `MovementZone=Destroyer` and no `MovementRestrictedTo`;
the two fields must stay distinct. This profile continues to **supply -1**.
An additional private scoped probe executes both stores, the missing-section and
missing-key paths, actual ReadString/trim/copy and enum/locale-zero comparison
children; both yield -1. Its scoped stack/write/input audits pass. This remains
an exploratory probe, not a standard native replay proof or full type-construction
claim; `restriction-missing-probe.py/.json` preserves its source and evidence.
Earlier fixtures supplied the same numerical value, so the old label did not
alter their compared decisions. Their historical names are not behavioral facts.

Both private engines freshly rehash equal: 4,485,392 bytes / SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`, at
`private/official-1006-probe/game.exe` and
`private/windows-baseline-20261014/game.exe`. Fresh execution uses the first.
Embedded1.08, supplied1.006 lineage and reported no-CD changes remain distinct;
pristine authenticity is unverified. The authorized private Windows copy already
exists; no new transfer or Windows action was needed.

YRpp remains `b22f1860dd7b100cad57123d4ca5d459b9020d88`, with no license file
found. Retained recomp snapshot `eebcf725ef99f942a8f9a5e0437a8a6154d7d439`
has MIT terms for authored tools/docs, excludes lifted/original code and retains
stale The Movies wording. No upstream/header/generated/lifted code, extracted
table or dependency was incorporated. See [REFERENCES.md](REFERENCES.md).

## Original evidence and supplied boundaries

The same original guest finalizes the map, runs initial Unit Mark, complete
Process/preparation/Advance, actual `55ACD0`, `703040`, `705160` and live Unit
membership/discovery/occupation/recalculation, then both body/shadow poses.
No original final records are transferred into native execution. The native
driver instantiates the production owned map/context and independently prepares
its map inputs.

The suite covers all 21 ramps at levels 0/1/2, forward/reverse movement, all eight
directions with raw Crusher0/1/255, curves, retained queue tails, signed clock
wrap, zero/signed-zero/positive speeds, four incoming FP modes, the owned
13,515-Cell map, parked cliff and level crossing. There are **1,364 actual Mark
calls/recalculations**, **256 eligible old-location unmarks**, 15,446 selected
membership-effect stores and 35,920 body/shadow pose calls. Actual admission
returns are 261 zero / 86 code7, at 342 first, three second and two Advance
callers. All 407 gate results are true; next-Cell enters 256 times. There are 50,451
selected preparation stores and 86 supplied retry-padding words. All 17,960 actor57A
values are read from the guest. Of 215 allowed complete ranges, 154 enter, with
4,582 distinct observed Process instructions.

There is **no actual admission self-skip entry in this profile** and no result3
or false gate. The earlier standalone/diagnostic proofs retain those branches;
this join does not establish them with production resident lists. Body/current-Cell
ramp lag occurs 80 ticks; 280 body/shadow matrices differ, with 124 positive and 120
negative relative heights. These are fixture observations, not whole-game samples.

Each tick compares the complete inherited actor/Drive/Cell/query/write stream,
all 24 queue words, actual actor57A, selected ordered preparation stores, pose/key
outputs, selected map fields, full attribute buffers and lazy/fallback digests.
Code/dispatch/type/House/Cell/slot/direction/registry/loading inputs and unselected
arenas retain immutable/write/stack/register checks. Newly entered original code
and supplied direction/registry/loading inputs are audited explicitly. No supplied
service may execute inside an actual admission or next-Cell decision. The actual
unpromoted ability child also executes where inherited Foot movement reaches it
outside those decisions. Excluded branch guards remain active.

Preparation still supports results0/3/7; Advance switch admission still requires
zero and refuses nonzero outcomes. This join does not expand either caller's
accepted codes. Preserve Mark(0)/decision/Mark(1), old-location occupation unmark,
ordered +5A0/+5A1 clears, self-local bit5 clearing, retained queue tails and
queue22/57B/queue23 order. Stored body and current-Cell shadow ramps remain distinct;
fractional Z is retained.

Initial actor/type/House/visibility/mission/registry/direction/speed/owner records
and associations remain supplied. Cell registry116=-1 and owners54/58=-1 are
explicit inputs. Mark/occupation/discovery/recalculation are actual in this join;
notification/other mission/pathfinder/atexit services keep their documented scopes.
Retry delay and copied temporary padding remain supplied. No full construction,
startup, arbitrary resident lists, overlays/bridges/crushing/warnings, animation
progression, original malformed-input behavior or transactional rollback is claimed.

## Regression, runtime boundary and next work

Native guard tests check refreshed occupation, unsupported list refusal, immediate
fallback forwarding, independently reconstructed clone owners/observers and
duplicate enabling. Existing owned-map preview/copy/move/assignment, House/buffer,
old-Cell cleanup and movement/stop/turn tests remain applicable. These establish
native ownership and safety, not fidelity by themselves. Both builds, 854 Python
tests, 62 normal / 61 sanitizer CTests and the final injected-event SDL checks pass.
Level crossing remains 78 updates; ramp 44 / 29 tilted / one lag / 23 positive-height
samples; parked cliff Z416/depth-52/153 visible/886 rejected pixels. The final
app is arm64, SHA256
`ee601b86bada192c9b6876453a464bfb6efb8460a6c83bcce99300d59d04ea67`.

Fourteen affected legacy families have fresh original execution and normal and
sanitizer replays, preserving their earlier command/result/label projections.
Current receipts are `unit-admission-v5`, `movement-gate-v6`, `unit-next-cell-v3`,
`ground-drive-admission-process-v3`, `ground-drive-gate-process-v6`,
`ground-drive-process-v7`, `prepared-drive-state-v8`, `moving-unit-world-v5`,
`membership-drive-v5`, `runtime-membership-v4`, `terrain-runtime-map-v19`,
`sweep-v8`, `map-preparation-v11` and `resident-map-v10`. The latter three also
refresh the rebuilt decoder identity; no stale decoder receipt is accepted.
The closing audit checks 130 current replay records: 50 unchanged without replay
or original reexecution, 50 unchanged-source relinked native replays, 28 refreshed
legacy replays and two new joined replays. All 42 fresh/replay refresh checks pass.
Historical receipts remain available.

Final native/sanitizer builds took 28.364s/8.729s; Python tests 3.104s, normal
tests 2.395s, sanitizer tests 5.638s and SDL checks 3.696s. The new fresh CLI took
439.335s, including 398.026s original generation and 0.569s native comparison;
normal/sanitizer replay CLIs took 35.791s/42.527s including identity/inspection
work. The moving-world legacy refresh took 1,423.438s, including 1,263.038s
original generation and 0.187s native comparison. Inherited research/delivery and
the first unwrapped rebuild elapsed times are unavailable; overlapping checks
must not be summed. These are verification timings, not gameplay measurements.

The SDL checks exercise the **legacy runtime entry**. OS pointer/keyboard input,
original-game timing/whole frames, independent acceptance and platforms beyond
Apple Silicon macOS remain unverified. The app uses local development dependencies.
No runtime executable read, private data format, source-install/disc/outpost2
mutation, Windows action, download, system/Xcode/DRM change or publication occurred.

Before adoption, formalize the scoped default/missing-key probe and preserve
the actual 24-word queue across Simulation ticks. The current adapter rebuilds it
from the public prefix and would discard retained words after a rejection.
Keep unsupported nonzero Advance outcomes explicit; preview must not disguise
them as successful movement. Then enable this profile and check actual SDL
blocked terrain plus movement/stop/turn/crossing/ramp/cliff. Stationary gate residents
need a further shared Next/list/recalculation/type/House join before a gate scenario.
General pathfinding, combat, AI/economy/campaigns/multiplayer/audio/saves and YR
remain later work. Keep the whole-game goal active.

```sh
./build.command
./test.command
build/tools-env/bin/python -B -m unittest discover -s tests -p 'test_*.py'
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

# Fresh original execution needs authorized host Unicorn JIT and a NEW directory.
build/tools-env/bin/python -B tests/compare_owned_unit_admission.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/owned-unit-admission-new
build/tools-env/bin/python -B tests/compare_owned_unit_admission.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/owned-unit-admission-v4/expected.json \
  --report private/map-depth-1006/owned-unit-admission-v4/replay-new.json
# Add --native build/sanitize/runtime-membership-vectors for sanitizer replay.

./run.command --terrain-demo
./run.command --terrain-smoke-test private/map-depth-1006/terrain-local-new
```

Select Rhino; G/right-click moves, Q/E body turn, A/D turret, S finishes the active
track then stops, R resets. These controls, direct routing/clearance and the demo's
current admission remain adapters. The new binding has no new control mode yet.
