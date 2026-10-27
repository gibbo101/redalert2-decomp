# Infantry Walk arrival continuation

This extends the [committed Walk kernel](WALK_MOVEMENT_1006.md) toward Boot Camp
Day 1 movement. `processSelectedWalk` uses that same kernel and adds arrival at
an already selected head. **No playable GI movement or objective transition is
delivered yet.** Initial/next nonempty subcell preparation, ordinary commands,
actual infantry occupation/speed, production map binding and animation remain.
Selection/action scheduling and genuine discovery are still required afterward.

## Recovered boundary

The exact supplied base executable remains4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08/supplied1.006 lineage/reported no-CD provenance are distinct; pristine
authenticity remains unverified. Private aligned inspections, logs and receipts
stay in `private/infantry-walk-20261018/`. No new upstream code, headers, extracted
tables, dependency, runtime executable reads or original execution is added to
the application. Existing pinned YRpp names remain hypotheses, not base evidence.

Complete original Process71DFF0 enters Movement_AI71E220 and its distance<17
branch71F0D3..71F2D6. The actual empty-point path of head helper71F590 executes,
followed by Foot coordinates4CA6F0 -> Walk71DF70 where entered. Completion uses
actual interface+48 **Stop_Moving71E110**, independently checked against the base
vtable; it is not the immediate-destination setter71E1A0. The legacy
`processCommittedWalk` entry still refuses arrival and empty heads. Both entries
share one movement kernel, with no tank substitution or duplicate algorithm.

New borrowed fields are the24-word actor4D0 queue, packed450 Cell words, raw
7D/76/7A flags and signed574 secondary index. Arrival preserves:

- Mark0 before the queue read; when queue0==-1, duplicate queue1=-1 before
  copying23 words forward, then queue23=-1. This differs from retaining tails
  during committed tank Process and must not change those existing kernels.
- Foot location at the selected head, head-derived450 words, relative height0,
  clear5A1; release old head, clear all three head words, claim live actor point.
- Queue0 reread after those services, conditional percentage0, notification174(2),
  then late raw7D/76/7A reads. Those early exits skip final Mark1 and57A clearing.
- Empty destination bypass; otherwise signed /256 and word Cell comparisons,
  two separate Foot coordinate queries, wrapped signed Z subtraction/absolute
  value and strict comparison against wrapped twice-level-height. INT_MIN is
  not repaired into a mathematical absolute value.
- Destination410(0,1), percentage0, duplicate head clears, actual Stop destination
  word stores and raw34/36 clears, unconditional4D0 reset on the empty head,
  duplicate36 clear, final Mark1/57A/processing35 stores and raw34 return.

The existing Foot coordinate kernel is reused with the actual borrowed negative
574 index; entered nonnegative indexed queries explicitly refuse until their pool
is bound. No query is made on an empty-destination bypass. Host FP rounding is
restored on exceptions. Missing services retain preceding state changes; no
transaction/rollback claim is made for these low-level calls.

Actual Infantry EC/E8 release/claim effects, notification174, destination410 and
movement reset4D0 remain named supplied services. Initial actor/type/route/head/
global records, Mark/floor/speed/map/dirty effects retain their supplied scope.
Diagnostic callbacks mutate occupation-associated coordinates, queue0 and late
flags/destination to test ordered consumption, not to claim recovered occupation,
mission notification, gameplay observations or a production simulation.

## Evidence and efficient replay

`arrival-fresh-a1/expected.json` and receipt compare **380 complete original
Process roots**:375 actual arrivals, five distance17 interpolation controls,
223 completion/Stop/reset paths,593 actual Foot/Walk coordinate queries,881 Mark
calls,12,201 arrival-selected stores and5,226 earlier selected stores. Coverage
includes queue/head/tail extremes, raw bytes, nested Mark effects, late service
mutations, on-map/76/7A early returns, signed coordinates, sentinel fallback,
distance16/17, strict height equality and wrapped numeric extremes.

Original parent/helper/Stop/Foot/numeric/setter instructions are unchanged.
Declared services alone are intercepted; ABI, callee-saved registers, caller
return/tail, code/tables/globals and all other arena bytes are audited. Selected
traces are not exhaustive field-read or whole-actor store comparisons; opaque
Facing scratch high words/timer padding retain the earlier exclusion.

Current normal/sanitizer arrival replays retain all380 outputs. Separate current
normal/sanitizer movement replays retain all624 earlier outputs using their
original `fresh-a1` expectations. Those generation receipts are not relabeled;
current native-source and runner identities are recorded separately. Three native
arrival guards cover missing release with preceding writes retained, late off-map
return without57A clearing, and entered indexed-Foot refusal. The four earlier
movement guards, seven Walk Python evidence tests and four focused mission/Walk
CTests pass in normal/sanitizer builds. This is an unwired dependency checkpoint;
no broad capability closure, unchanged original matrix or SDL rerun is claimed.
Existing static-preview and two-tank acceptance retain their scopes. Local
verification is not independent acceptance or whole-frame fidelity.

Measured initial proof1.40s (original1.082s/native0.032s); initial normal/sanitizer
arrival replay0.192s/0.313s, earlier-movement replay0.166s/0.270s. Later indexed
guard/source/runner changes reuse those immutable originals; final receipts are
`arrival-replay-*-a2.json` and `movement-replay-*-a3.json`. First build invocations
cost13.70s/13.94s: make regenerated but did not recognize the newly added target
in that invocation. The separate target builds passed in1.11s/1.07s. Final rebuild
and replay costs are recorded in private validation. Focused checks0.04s/0.23s;
Python10 tests0.049s. Overlapping costs are not additive. Manual repair/total task
wall were not separately measured. No new cache framework or original-answer
regeneration was needed for the native guard change.

## Reproduce

```sh
./build.command
build/native/walk-arrival-vectors --guards
env PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_walk_arrival test_walk_movement

# New private report/audit names; current native executes, originals do not.
env DEVELOPER_DIR=/Library/Developer/CommandLineTools PYTHONHASHSEED=0 \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/walk-arrival-next.audit.json tests/compare_walk_arrival.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/walk-arrival-vectors \
  --render-data private/derived/ra2-1006/render-data.bin \
  --raster-data private/derived/ra2-1006/raster-data.bin \
  --direction-data private/derived/ra2-1006/direction-data.bin \
  --expectations private/infantry-walk-20261018/arrival-fresh-a1/expected.json \
  --report private/walk-arrival-next.json
# Separate sanitizer replay: build/sanitize/walk-arrival-vectors.
# Earlier624 outputs: compare_walk_movement.py, walk-movement-vectors and
# private/infantry-walk-20261018/fresh-a1/expected.json, with new audit/report names.
# Fresh originals only after genuine original dependencies change: omit
# expectations/report, use --output private/walk-arrival-new-fresh and a new
# audit name in the existing authorized Mac-host JIT context.
```

`./run.command --boot-camp-preview` still exposes static content/selection and an
explicit RMB refusal. Next recover original nonempty subcell selection and actual
infantry occupation against the existing map owners, then ordinary preparation/
commands and SDL walking. General pathfinding/combat and tutorial transitions
remain incomplete. Only Apple Silicon macOS is tested.
