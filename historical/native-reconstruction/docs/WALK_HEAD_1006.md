# Ordinary infantry Walk head preparation

This joins the recovered Infantry subcell/occupation rules to their actual
Walk71F590 caller, a prerequisite for Boot Camp Day 1 walking. `prepareWalkHead`
borrows Walk, Object coordinates, mission/target fields, Cell words/flags/House
slots and distinct height globals. It owns no second actor, map or simulation.
**The Boot Camp preview remains static; no runtime GI walking or objective
transition is delivered yet.** Initial/next queued preparation in complete Walk
Process, ordinary commands/speed, production bindings and animation remain.

## Recovered boundary

The executable was freshly rehashed:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08/supplied1.006 lineage/reported no-CD provenance and unverified
pristine authenticity remain distinct. Private aligned head/Cell/Process
inspections and receipts stay under `private/infantry-walk-20261018/`. No new
public code/header, generated/lifted game code, dependency, table or runtime
executable read was incorporated. Existing private prepared subcell data is
fixture-only; the application does not load it.

The complete ordinary71F590 paths execute actual Infantry EC5084A0 release,
Cell4764B0 selection, E8508410 claim, mission getter594770, House getter6C7420,
offset initializer483390 and existing numeric/RNG children. All queries use one
borrowed Cell service. Preserved ordering includes:

- Release before reading the requested point. A nonempty old head is borrowed;
  an empty head releases a snapshot of Object coordinates. Input may alias the
  head or Object position, so copying it before release changes behavior.
- Copy the request after release; empty requests skip mission/selection/Cell
  effects. Nonempty requests query mission separately for8,9,7,11,25, with exact
  short circuit ordering and the actual98==-1 ->A0 fallback getter.
- Special missions enter target-specific force logic only when target494 is
  nonnull. That entered child explicitly refuses. A nonnull target is not
  consumed for ordinary mission2; this bypass is independently covered.
- Lookup the saved candidate, inspect bridge flag0x100, then save actor Z before
  an optional floor query. Compare it strictly against floor plus wrapped three
  times the late level-height global. Bridge height, occupation threshold and
  level height remain separate borrowed inputs.
- Lookup the saved candidate again before actual subcell selection. Store all
  three selected head words, then lookup the selected head and call476CC0 even
  when selection returned the empty point. Do not drop this lookup.
- Claim a nonempty head by reference and return1. Otherwise claim a fresh Object
  coordinate snapshot and return0. Other Walk fields and destination stay intact.

`476CC0` is a Cell entry-effects routine, not the ordinary passability decision
suggested by the earlier next-step label "admission." Its original no-overlay
branch (Cell+44==-1) reaches478646 and returns AL1 before effects. This actual
branch executes; it is not stubbed. Entered overlays refuse after preceding
release/selection/head stores. Effectful overlay/destructive children and their
AL0 continuation, nonnull target children and entered selector building policy
remain unjoined. No unsupported result is replaced with success.

The shared `WalkHeadTransfer` kernel now also serves the existing selected-head
arrival's empty-request facade. That facade retains its named occupation
services and prior scope. Object-coordinate copies replace its former borrowed
claim argument; the original helper actually makes those copies. An added
arrival guard mutates Object Z during claim and verifies that the claim snapshot
does not change. The full head proof exercises the same transfer kernel through
actual Infantry children. No second implementation of the transfer is added.

Initial actor/Cell/House/mission/Walk/global associations, scenario/RNG seeding,
empty sentinel values and named lookup/floor effects remain supplied. The
diagnostic map chooses between two distinct Cells; it is not production map
ownership or original-game observation. Floor mutations of actors, requests,
heads and globals verify saved-versus-live consumption. Observers are read-only.
Host FP state is restored on returns/exceptions; refusals retain prior effects.

## Evidence and efficient verification

Canonical `head-fresh-a1/expected.json` and original-only `report.json` retain
**635 sequences /1,840 complete head roots plus one initializer**. They include
1,840 actual releases,1,840 claims,1,266 selectors/overlay-free Cell calls,
6,258 mission queries,635 RNG calls,6,390 selected Cell stores and5,520 head
word stores. Tests cover all64 ordinary occupation masks, strict/wrapped bridge
height, both layers, repeated empty/occupied claims, RNG retention/wrap/disabled
state, negative bases and request aliases to head/Object coordinates. Complete
RNG state and selected ordered services/stores/final fields match.

Actual instructions are unchanged. The oracle audits ABI, saved registers,
caller return/tail, code/tables/initialized offsets and other arena bytes. Entered
target/building/overlay branches explicitly fail; only named map/floor services
are intercepted. Selected traces are not exhaustive field-read or whole-game
comparisons. Local verification is not independent acceptance.

Original answers are saved before native validation. Native-only sharing and
guard changes replay those answers without original execution. Final normal/
sanitizer `head-replay-*-a1.json` and uncached control each report635 reuse hits,
zero misses; current native identities are separate from original provenance.
Source/input/runner/receipt guards remain. Rebuilt affected runners retain the
earlier4,964 subcell calls,380 arrivals and624 interpolations in
`subcell-replay-*-a2.json`, `arrival-replay-*-a4.json`, `movement-replay-*-a5.json`.
No unchanged original matrix or new cache framework was needed.

Four head guards, four arrival guards and previous subcell/movement guards pass
in normal/sanitizer builds. Three new evidence tests bring the focused Python
set to69 passing tests; six mission/Walk/subcell CTests pass in each build. No
new broad capability closure or SDL rerun is claimed for this internal caller.
Existing static-preview and two-tank acceptance retain their scopes.

Measured fresh proof7.107s (original6.662s/native0.064s). Head normal/sanitizer
replay0.367s/0.524s; uncached control0.659s. Configure12.31s/9.74s; initial
build5.31s/5.62s; shared-kernel/affected-runner rebuild7.65s/7.86s; extra arrival
guard rebuild1.18s/1.14s. Focused CTests0.09s/0.44s and69 Python tests0.927s.
There were no failed build/proof attempts. Overlapping costs are nonadditive;
manual development/repair and total task wall were not separately measured.
`head-validation.json` records the measured reports and unavailable costs.

## Reproduce and next integration

```sh
./build.command
build/native/walk-head-vectors --guards
env PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_walk_head test_infantry_subcell test_walk_arrival test_walk_movement

# New report/audit names. Current native executes; original instructions do not.
env DEVELOPER_DIR=/Library/Developer/CommandLineTools PYTHONHASHSEED=0 \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/walk-head-next.audit.json tests/compare_walk_head.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/walk-head-vectors \
  --render-data private/derived/ra2-1006/render-data.bin \
  --subcell-data private/derived/ra2-1006/infantry-subcell-data.bin \
  --expectations private/infantry-walk-20261018/head-fresh-a1/expected.json \
  --report private/walk-head-next.json
# Sanitizer: build/sanitize/walk-head-vectors, separate report/audit names.
# Uncached inspection: add --uncached before the driver.
# Fresh originals only after genuine original dependency changes: omit
# expectations/report, use --output private/walk-head-new-fresh and a new audit
# in the authorized Mac-host JIT context. report.json stays original-only;
# native-comparison.json records fresh native validation separately.
```

`./run.command --boot-camp-preview` still offers static content/selection and an
explicit RMB refusal. `./test.command` remains the broad native entry point at
capability integration. Next recover the encountered ordinary queued preparation
in complete71E220 (queue !=-1, ordinary direction), Infantry admission/level/
speed and the actual command caller on existing production map/actor owners.
The aligned full Process inspection is private; inspected code is not proof of
that preparation. General pathfinding and entered tube/special/effect branches
remain deferred/refused. Then verify ordinary SDL walking and genuine
discovery/action scheduling before the first objective. Base RA2/YR remain
incomplete; only Apple Silicon macOS is tested.
