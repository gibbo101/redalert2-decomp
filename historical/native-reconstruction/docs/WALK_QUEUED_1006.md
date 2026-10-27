# Ordinary queued infantry Walk Process

`processQueuedWalk` extends the existing SDL-free Walk kernel through ordinary
queued preparation, actual head selection/occupation, later interpolation and
arrival/Stop. It borrows the same actor coordinates, Facing, route, Cell fields
and head services; it adds no second actor/map/simulation. This unblocks the
queued-direction step needed for the first Boot Camp walking lesson. **The
preview still has no runtime GI walking or objective transition.** Actual
Infantry admission, speed/commands and production/SDL integration remain next.

## Recovered scope

The executable was freshly rehashed before inspection:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Private inspections/receipts stay under
`private/infantry-walk-20261018/`. No public code/header, copied original code,
new prepared data, dependency or application executable read was incorporated.

The complete Process71DFF0/Movement_AI71E220 profile adds empty-head ordinary
queue preparation and empty-destination idle. It executes actual71F590 head,
Infantry release/claim, selector, mission/RNG and overlay-free Cell entry-effects
children. Later selected-head calls use the existing interpolation/arrival
algorithm, with the actual head helper also used to release/reclaim on arrival.
Older committed/selected facades retain their earlier preparation refusal and
named occupation services. No runtime default or existing guard is widened.

Preserved ordering and arithmetic include:

- Save the raw queue direction; exactly8 is the special child. Mask ordinary
  offsets with7, but pass the original raw direction to Infantry admission.
  Actual4916D0 initializes851AC0; the existing authored direction kernel matches
  all eight offsets. Candidate addition wraps dwords, then packed Cells use
  signed division by256 followed by signed-word truncation.
- Keep the saved candidate distinct from the subsequent raw coordinate lookup.
  Cell flag100 is XORed against the **raw** bridge79 byte. A mismatch writes
  actor57B=1; a match does not clear its prior value.
- Actual5D47D0 calls Infantry+1A4 ->5D51E0. That getter performs two independent
  Object-coordinate snapshots/lookups, discarding the first result. Read the
  late bridge byte, then the second Cell's signed level, adding4 for any nonzero
  bridge byte. Keep the saved candidate/direction across these queries.
- Packed target lookup follows the level getter. Actual+194 dispatch is
  **Infantry503190**, distinct from the recovered Unit admission. Its five
  arguments are target Cell, raw direction, saved level,0,1. This join supplies
  that admission result as a named service and accepts only0. Nonzero results
  explicitly refuse; no passability approximation is substituted.
- Call actual head preparation. Success sets reallyMoving36, then reads late
  onMap7D. Off-map skips bearing/percentage/57A clearing. On-map sets body Facing
  and percentage1. Failure sets percentage0 without inventing a head or clearing
  reallyMoving36. Neither branch interpolates on that same call.
- Later calls reuse interpolation and arrival, including all24 queue words,
  actual occupation, notification-before-late-guards, Stop and raw moving34
  returns. Empty-destination idle changes percentage only when positive and
  leaves reallyMoving36 intact. Host FP state is restored, including refusals.

Route finding/retry (queue==-1 with nonempty destination), special direction8,
nonzero admission continuations and entered head target/building/overlay effects
remain refused. Admission, speed, Mark, map/floor, notification174,
destination410, reset4D0, initial records/associations and RNG seeding remain
supplied. The two-Cell fixture is diagnostic ownership, not initialized
production infantry or original-game observation. No general pathfinding,
original frame scheduling/animation/drawing or tutorial objective claim follows.

## Verification and costs

Canonical `queued-fresh-a1/expected.json` and immutable original-only
`report.json` retain **580 sequences /1,557 complete Process roots plus two
initializers**. Actual counts include575 level/current-Cell pairs,575 supplied
admissions,599 head/release/claim calls,575 selectors,303 active interpolation
calls and24 Stop/arrival sequences. Tests cover raw directions, signed/wrapped
candidates, raw bridge bytes, signed levels, occupation/head failures,
saved-versus-late lookup mutations, later interpolation/arrival/idle and raw
returns. Selected ordered stores/services, final fields, all24 route words and
full RNG state match. This is bounded differential evidence, not exhaustive
original reads or whole-game fidelity. Local verification is not independent
acceptance.

The original instructions are unchanged. Complete range/table/initialized-data,
vtable, ABI, saved-register, caller-stack and remaining-arena guards remain.
Normal/sanitizer `queued-replay-*-a1.json` and the uncached control each report
580 reuse hits/zero misses and execute zero originals. Original provenance and
current rebuilt-native identities remain separate. Six new native guards pass
in each build;72 focused Python tests plus three mission-event tests and seven
CTest cases per build pass. Rebuilt prior runners retain1,840 head calls,
380 arrivals and624 interpolations in `head-replay-*-a2.json`,
`arrival-replay-*-a5.json`, `movement-replay-*-a6.json`. Earlier subcell receipts
retain their scope. No new broad capability closure or SDL run is claimed.

Fresh generation took7.801s; the first wrapper took8.470s and failed **after the
original/native streams matched**, on a native guard fixture. Empty order data
cannot choose a center subcell; the guard now uses an ordinary noncenter request.
Original answers had already been saved before native validation, so correcting
that native-only fixture required no original regeneration. The failed audit is
preserved. Normal/sanitizer/uncached replay elapsed0.368s/0.578s/1.422s; current
native comparison0.051s/0.219s/0.047s. Guard rebuild2.477s/2.553s; seven CTest
cases0.10s/0.48s (wrapper0.311s/0.542s). Python72 tests0.780s plus mission3
tests0.002s. An initial Python command used the nonexistent plural module name;
its failed log is retained and the actual singular module passes separately.
An initial inspection import typo was corrected before original generation.
Configure/initial build/manual repair/total task wall were not separately timed;
overlapping costs are nonadditive. `queued-validation.json` records receipts
and measured/unavailable costs. No new cache framework or unchanged original
matrix regeneration was needed.

## Reproduce and next integration

```sh
./build.command
build/native/walk-queued-vectors --guards
env PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_walk_queued test_walk_head test_infantry_subcell test_walk_arrival test_walk_movement test_original_results test_inspection_reuse test_mission_event

# New audit/report names. Current C++ executes; original instructions do not.
env DEVELOPER_DIR=/Library/Developer/CommandLineTools PYTHONHASHSEED=0 \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/walk-queued-next.audit.json tests/compare_walk_queued.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/walk-queued-vectors \
  --render-data private/derived/ra2-1006/render-data.bin \
  --raster-data private/derived/ra2-1006/raster-data.bin \
  --direction-data private/derived/ra2-1006/direction-data.bin \
  --subcell-data private/derived/ra2-1006/infantry-subcell-data.bin \
  --expectations private/infantry-walk-20261018/queued-fresh-a1/expected.json \
  --report private/walk-queued-next.json
# Sanitizer: build/sanitize/walk-queued-vectors and separate audit/report names.
# Uncached inspection: add --uncached before the driver.
# Fresh originals only after genuine original dependency changes: omit
# expectations/report, use --output private/walk-queued-new-fresh and a new
# audit in the authorized Mac-host JIT context. Originals are saved first.
```

`./run.command --boot-camp-preview` remains a static content/selection preview
with an explicit movement refusal. Next recover encountered Infantry503190
admission, ordinary speed/commands and bind to existing production map/actor
owners, then verify actual SDL walking. Genuine discovery/actions/scheduling
still precede the first objective; do not synthesize waypoint success. Use
`./test.command` for broad native regression at that integration boundary.
Base RA2/YR remain incomplete; only Apple Silicon macOS is tested.
