# Infantry orders through Walk retry and route refill

The same Walk kernel now connects an ordinary Infantry/Foot order to route
refill, preparation, interpolation and its actual null destination command at
arrival. This removes the queue-seeding gap in Day 1's first GI movement order.
**The Boot Camp preview remains static. Production GI walking, original
pathfinding, animation/drawing and objective transitions are not delivered.**

## Recovered behavior and supplied boundaries

The executable was freshly fingerprinted before using addresses:4,485,392 bytes,
SHA256 `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Disassembly and receipts stay ignored in
`private/infantry-walk-20261018/`. No public code/header, generated/lifted code,
dependency, extracted table or application executable read was added.

The complete Process71DFF0 -> Movement_AI71E220 profile adds the queue==-1
retry/wait and successful-refill caller71E28A..71E32C/71E63F..71E66F. Actual
Infantry501CE0/Foot4C8030 commands execute before Process and at arrival, with
the existing Walk commands, admission, speed, head/subcell occupation, numeric
and placement kernels. Each uses the same actor, Walk, target,24-word route and
timers. `WalkRouteContext` borrows these additional fields; the existing queued
context opts into it. Legacy facades retain the empty-route refusal.

- Retry530 snapshots start/remaining before the clock read. Start==-1 consumes
  the remaining value directly without reading the clock. Otherwise elapsed
  subtraction wraps32 bits and uses signed comparison/subtraction. Any nonzero
  remaining value, including a negative disabled timer, calls actual508730 and
  returns without clearing57A/reallyMoving/percentage or the timer.
- Infantry+4CC dispatches to508730, which changes state5AC to-1 only for3/6/17.
  Complete Process subsequently clears its processing byte and returns the raw
  IsMoving byte. Do not interpret the helper's incidental AL as the Process result.
- An expired timer reads Rules13C8, multiplies by900 (79B608), and calls actual
  FTOL77F110. Conversion is signed64 consumed as its low dword; invalid
  conversions have low0. The caller then reads the clock and scratch padding
  before separate start/padding/remaining stores. A later clock/interval mutation
  cannot change the already computed timer words.
- Destination X/Y use signed division by256 then signed-word truncation. The
  caller supplies the packed point and two zero arguments to Foot4C3000. This
  **route provider remains supplied**, writing the borrowed queue inside that
  call. Nothing reseeds the route after the Infantry command or outside this
  named service. Unfilled queue tails retain their values.
- Any nonzero provider byte stores counter53C=10, then calls actual Infantry
  +484 ->508AB0. With a nonnull target it scans up to24 directions, stopping at
  -1 or8; at least four bypass the JumpJet query. Otherwise ordinary B44==0
  returns false. Entered JumpJet children still refuse. Only afterward does the
  movement caller reread route[0] and continue existing preparation.
- Facing consumes the late live clock after refill. Arrival invokes actual
  Infantry/Foot null destination handling, retaining its route clear, Stop,
  independent timers and the subsequent Walk caller's separate Stop/reset.
  Neither command nor Process substitutes a mirrored Drive or a second mover.

Failed-route continuation, special8, nonzero admission and prior head/effect/
indexed-coordinate restrictions remain explicit refusals. A failed provider
clears reallyMoving36 before the native refusal; earlier timer stores remain.
There is no rollback claim. Moving/non-null Infantry retarget48C is still
unjoined. Initial actor/type/House/rules/RNG/Facing/queue/scale records, route
provider, target coordinates, map/floor/Mark/notification174 and animation effects
remain supplied. Initial E1 type construction, discovery and scheduling are not
proved. The diagnostic uses distinct House storage because its newly consumed
control bytes would overlap timers in an older narrow fixture's unused-memory
alias; older fixtures/receipts are unchanged. It is not the production mutable map.

## Evidence and regression

Canonical original-only receipts: `route-fresh-a2/{expected,report}.json`.
**165 sequences /2,401 complete Process roots +72 initial Infantry orders +three
initializers** match. Actual entered children include112 Infantry/Foot destination
calls (40 at arrival),136 supplied route responses and actual post-route checks,
75 retry-wait508730 calls,144 admissions,591 speeds and200 head/occupation calls.
All eight directions and repeated refill across two Cells are covered. Tests
also vary raw provider bytes, queue lengths1/3/4/23/24, nullable target, signed/
wrapped timers/coordinates, FTOL limits/NaN, raw state values, retained tails and
diagnostic late clock/interval/destination mutations.

Selected ordered stores/services, final fields, all24 queue words and full RNG
state match. Code/table/binary, ABI/callee-saved/caller-stack, remaining-arena,
source/runner/input/receipt guards remain. Initial commands also guard untouched
arena bytes. This is bounded original/native evidence; injected mutations are
diagnostics, not original gameplay observations. Other FP entry states/exception
flags and exhaustive read/store ordering remain unproved. Local verification is
not independent acceptance or whole-game fidelity.

`route-replay-{normal,sanitize,uncached}-a2.json` each report165 reuse hits, zero
misses and zero original execution. Current native code always runs, with its
identity separate from immutable original provenance. `route-regression-*-a1`
normal/sanitizer receipts retain all580 queued,199 admission-joined,121 speed-
joined and251 Walk-command/Process sequences, plus380 arrivals and624 committed
movement roots. Ten focused CTests in each build and100 focused Python tests
pass. No unchanged original matrix, broad capability closure or SDL rerun was
performed for this internal dependency. The earlier attachment retry succeeded;
its static preview observations remain in `private/boot-camp-20261018/`.

The first149-sequence original generation completed, but native comparison
caught a stale Facing clock after a diagnostic timer-store mutation. Fixing that
native read replayed the saved originals successfully, without regeneration.
The expanded165-sequence proof genuinely regenerated after adding two-Cell
coverage and stronger initial-command arena guards. All149 preserved original
streams are identical in a2. An initial uniqueness test caught a duplicate input;
its counter was differentiated before generation. An include-line typo produced
a compiler warning and was corrected before generation. Failed attempts stay private.

Fresh a2 original generation took11.245s; native comparison0.050s. Normal,
sanitizer and uncached replay driver times were0.407s/1.199s/2.748s; native portions
0.042s/0.789s/0.038s. Six old-family wrapper totals were3.592s normal /6.291s
sanitizer. These overlapped and are not additive task totals. CTest bodies took
0.09s/0.70s; Python100 tests1.859s. Individual focused rebuild tool waits were
partially yielded; total build, manual inspection/repair and task wall times were
not separately measured. `route-validation.json` retains identities, receipts,
measured/unavailable costs and failure scopes. No cache framework was introduced.

## Reproduce and next integration

```sh
./build.command
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/native --target walk-queued-vectors --parallel 6
build/native/walk-queued-vectors --guards
env PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_walk_route test_walk_command_process test_walk_commands test_walk_speed test_walk_admission test_walk_queued test_walk_head test_walk_arrival test_walk_movement test_infantry_destination test_infantry_speed test_infantry_admission test_infantry_subcell test_original_results test_inspection_reuse test_mission_event

# Choose new audit/report names. Current native executes; originals are reused.
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/walk-route-next.audit.json tests/compare_walk_route.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/walk-queued-vectors \
  --render-data private/derived/ra2-1006/render-data.bin \
  --raster-data private/derived/ra2-1006/raster-data.bin \
  --direction-data private/derived/ra2-1006/direction-data.bin \
  --subcell-data private/derived/ra2-1006/infantry-subcell-data.bin \
  --expectations private/infantry-walk-20261018/route-fresh-a2/expected.json \
  --report private/walk-route-next.json
```

Configure/build `build/sanitize` with `-DRA2_SANITIZE=ON` and select its runner
for sanitizer replay. Add `--uncached` before the comparison driver for the
inspection control. To generate fresh originals after genuine dependency changes,
replace `--expectations`/`--report` with `--output private/NEW_DIRECTORY`, choose a
new audit, and use the authorized Mac-host Unicorn JIT context. Preserve receipts.
Old-family exact commands are in their unchanged notes and the private audit
`arguments` arrays; replace report/audit paths and use rebuilt runners.

`./run.command --boot-camp-preview` still starts the static selection/content
preview; `./test.command` is the broad regression entry point. Next bind real E1
inputs and GI records to the existing mutable map and genuine borrowed Cell
views; recover encountered moving retarget/failed-route children, then animation/
drawing and ordinary SDL walking. Actual discovery, scheduler/actions and the
original conditions still precede the first objective transition. Base RA2/YR
remain incomplete; only Apple Silicon macOS is tested. Full-game goal stays active.
