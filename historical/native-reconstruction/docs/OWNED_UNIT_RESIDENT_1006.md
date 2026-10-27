# Shared owned movement and a parked Unit

After `9a53330`, an explicit parked-Unit extension joins production owned Cells,
Unit Mark/membership/discovery/occupation/recalculation and complete ordinary
Process with actual allied stationary admission 6. **112 fresh results / 1,744
original Process ticks** match native C++. The SDL demo still has one Unit; the
new extension runs in the differential driver and native ownership checks only.
Complete base RA2, then Yuri's Revenge, remain incomplete. No workers.

## Ownership and original effects

`TerrainUnitContext` owns an optional stable parked record alongside its mover.
Both bind to one `PreparedUnitMembership`, mutable map, Cell lists, foundation,
House records, visibility, occupation dwords, lazy floors and full attribute
buffers. Each has separate actor/Drive, Mark and discovery state. The context
does not compose two independent maps or compute a replacement collision flag.

Mark binds the explicit actor identity into insert/remove, selected stores and
discovery notification. Discovery retains the live shared House world; a scoped
observer maps its actor-subject-zero stores to the correct Unit and restores the
previous observer on return or exception. There is no persistent active-actor ID
or fallback to Unit 0. Notification still executes the existing recovered root.
Diagnostic observer failures are not original game fault/rollback behavior.

Before each gate/admission/next-Cell decision, the view refreshes both actors'
actual shared `Next`, discovery/mission, Cell heads and occupation. The extra
profile is explicitly opted into with `PreparedUnitAdmissionInputs::parkedResident`.
It admits only a bound, stationary, nonbridge allied Unit in House 0, with supplied
ordinary type associations and flags 5. Unknown actor/list identities, moving or
rotating residents, tags, foreign owners and unsupported associations are refused.
The legacy one-Unit entry retains its domain.

The opted-in owner calls `processResidentOrdinaryGroundDrive`, preserving distinct
first/second result-6 retry padding, first6's retained head, queue tails and the
recursive flag-zero empty-queue path. Nonzero Advance admission still throws its
typed refusal. The final proof requires an actual native admission-6 event
immediately before that refusal; it does not discard missing Advance effects.
Flag-zero scatter/close-enough remains excluded.

Cloning reconstructs the entire group and admission owner against independent
Cells, lists, actors, House records, buffers, fallback and floor state. Both actor
bindings and the parked services refer to the clone. Query/store/decision observers
are dropped. Concrete contexts remain immovable; move their owning pointers.
This is host preview infrastructure, not recovery of original clone behavior.

## Exact original evidence

Both private engines are 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`:
`private/official-1006-probe/game.exe` and
`private/windows-baseline-20261014/game.exe`. Embedded 1.08, supplied 1.006 lineage
and reported no-CD provenance remain distinct. Pristine authenticity is unverified.
The approved Windows copy was already present; no transfer or Windows action was
needed.

The same guest finalizes the map, executes actual SetHeight/Unlimbo/initial Mark
for both Units, then complete mover Process with actual decisions, shared Mark/
membership/discovery/occupation/recalculation and both mover poses. Unit 1 uses
actual base Unit/type dispatch and a separate Drive. No final original actor/map
records are transferred into native execution.

Actual results include 84 admission6, 41 zero and four code7 returns, 63 first and
21 second result-6 retry loads, 436 Mark/recalculations, 41 next-Cell calls and
20 eligible old-location occupation unmarks. There are 5,439 selected preparation
stores, 5,619 inherited selected membership-effect stores, 991 parked selected
stores, 90 parked initializations/full-arena checks and 3,488 mover poses. Every
one of the 1,744 actor57A samples is read from the guest. 4,414 distinct original
instructions enter. No actual admission self-skip enters this joined profile;
earlier standalone/diagnostic proofs retain that coverage.

Cases cover all 21 ramp types for parked placement and first/second admission,
all eight directions and four incoming native FP modes, distinct signed timer
words, signed clock wrap, turning before admission, zero Track speed overriding
the resident, movement across empty Cells before a later resident, both insertion
orders in a shared initial Cell and the owned 13,515-Cell map. This new suite has
no positive/negative relative-height or ramp-lag coverage; earlier complete
movement/drawing proofs retain those scopes. Do not infer them from the ramp
case labels.

In both overlapping-start cases the original stores a whole ground-occupation
zero to Cell 131 (`+0x124`) while its head still points to parked Unit 1, once
per case. Preserve that ordered whole-field assignment. A reference count or
recomputed union would change the measured behavior.

Cell heads and both actors' Next pointers normalize only actual null/Unit0/Unit1
pointers. Initial Mark writes, preparation stores, shared map fields, full buffers,
fallback/lazy digests and final actor fields are compared in order. Original
caller/register/stack/code/dispatch/input/write audits remain enabled. The parked
64-KiB arena includes its full actor/type/Drive records and gaps; after initialization
only shared Next writes are allowed, with a complete final arena comparison.
Actual initial Mark must leave its type and Drive records unchanged. No supplied
service is allowed inside actual admission or next-Cell.

Initial actor/type/House/mission/visibility/registry/direction/speed/owner records
and associations remain supplied, including flags5, null Tag/loading1, empty
passengers, ordinary type fields and settled Facing/Drive. Temporary timer words,
zero retry delay, atexit and other notification/mission/failed-pathfinder effects
retain supplied scopes. No original construction/startup, arbitrary moving
residents, bridges/overlays/crushing, combat or whole frames are established.

Current final proof and replay identities are recorded in [HANDOFF.md](HANDOFF.md).
v1 retains the first successful join before the stricter whole-arena/write and
native safety/receipt guards. Historical receipts are not relabeled.

## Native checks and runtime limit

The native ownership check exercises per-actor discovery, exception restoration,
clone/reclone observer isolation, canonical Cells/fallback and resident-domain
refusals. Its owned-data mode verifies occupied-target preview rejection without
any live group mutation, empty-Cell movement, warm Simulation copy/assignment/move,
body/turret turns and parked Mark removal/reinsertion on the clone. A freshly
reconstructed scenario verifies immutable renderer preparation was unchanged.
These checks establish native ownership, not original fidelity by themselves.

The rebuilt arm64 SDL demo retains selection/right-click/G, actual zero-speed
terrain refusal, active-track stop, body/turret turns, live membership, crossing,
ramp and parked-cliff checks. The terrain-refusal frame was viewed. SDL events are
injected, so OS-level pointer/keyboard acceptance and original-game observations
remain unverified. The demo does not draw or select the parked Unit yet; no
playable two-Unit or full-frame claim is made. Only Apple Silicon macOS is tested.

No upstream/header/generated/lifted code, table or dependency was incorporated.
Pinned YRpp ObjectClass NextObject/DiscoveredBy and CellClass content names remain
leads; unchanged exact base execution establishes behavior. YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` has no license file found. Retained
recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439` MIT terms cover authored
tools/docs, exclude original/lifted content and retain stale The Movies wording.
See [REFERENCES.md](REFERENCES.md). No new runtime executable read, source-install/
disc/outpost2 write, download, system/Xcode/DRM change or publication occurred.

## Reproduce and continue

```sh
./build.command
./test.command
build/tools-env/bin/python -B -m unittest discover -s tests -p 'test_*.py'
build/native/terrain-resident-check --guards
build/native/terrain-resident-check private/official-1006-probe
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
build/sanitize/terrain-resident-check private/official-1006-probe

# Fresh original execution: authorized host Unicorn JIT, NEW private output.
build/tools-env/bin/python -B tests/compare_owned_unit_resident.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/owned-unit-resident-new
# Replay: use the current expected.json path recorded in HANDOFF.md, plus
# --expectations PATH --report NEW_PATH. Add
# --native build/sanitize/runtime-membership-vectors for sanitizer replay.
./run.command --terrain-demo
```

Next draw the parked Unit from its own verified state and shared prepared Cells,
with distinct actor/cache identities, then selection and actual SDL occupied-
target/empty-Cell movement acceptance. The one-mover prototype's control, direct
route, clearance, camera, picking and target lifetime remain explicit host adapters.
General pathfinding, moving residents, nonzero Advance and flag-zero scatter,
combat/economy/AI/campaigns/multiplayer/audio/saves and YR remain later work.
