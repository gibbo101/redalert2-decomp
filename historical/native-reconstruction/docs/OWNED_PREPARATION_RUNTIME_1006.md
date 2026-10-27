# Preparation Scatter on production owners

The subsequent [distinct original pair](OWNED_SCATTER_PROCESS_PAIR_1006.md) now
compares both actors through resident displacement and interleaved target-bearing
drawing in a supplied flat encounter. The earlier unjoined-original statements
below retain this preparation checkpoint's scope. Actual SDL displacement still
precedes adoption of Scatter there.

The diagnostic `ordinaryScatter` owner now binds the recovered positive-route
preparation caller to its actual actors, Drives, Cells and destination tree.
`OwnedUnitScatter` owns each actor's separate `53C` counter and copies its logical
value when cloning. The existing `ProcessPreparationInputs` borrows that counter;
the simulation/preparation algorithm is unchanged. Lower-level callers without
a route callback retain the earlier optional-binding scope.

`OwnedUnitWorld` supplies a synchronous route callback on each Process invocation.
It uses the same bounded direct-route builder as explicit orders, and the same
immutable sampled clearance/Cell checks as between-Process Scatter routing. It
installs all 24 supplied queue words only after validation, preserves destination
Z and actual target identity, and updates the actor's separate host command
record. Clones reconstruct the callback against their own world; no callback is
copied from the source owner. It never invokes another Process.

There is at most one positive supplied route response per Process invocation.
The direct router has no detour search: returning the same rejected route on
every recursive request caused unbounded recursion in an early private attempt.
Subsequent requests now supply failure to the existing recovered caller. This
budget, direct routing, initial counters and the diagnostic close threshold of
zero are **supplied host policy**, not recovered original pathfinding or rules
initialization. Failed callbacks can follow original prefix writes; there is no
live-tick rollback claim.

## Native encounter and limits

On `mp03t4.map`, ordinary commands stage actor0 at 91,104 and actor1 at 93,104.
Actor0 receives a direct order toward 94,104. The recovered preparation caller
dispatches the actual actor1 resident of its candidate Cell. One actual Cell/Unit
dispatch assigns the nearby destination 92,103. Actor1's subsequent Process
calls move it there and clear its target; this is displacement, not merely a
destination assignment. Two actor0 `53C=10` stores occur. A later command moves
actor0 into the vacated 93,104 Cell; actor1 then independently moves to 92,104.
Complete native draws interleave movement and retain both actor poses and warm
pixel reuse. No live positions or membership lists are edited to force the case.
The earlier curved self-Scatter test also remains passing with its original
one-dispatch scope.

A discarded diagnostic clone deliberately clears only its queue head to enter
the new callback on actor1. Its target points to the clone's actual Cell and its
counter changes independently. A separate preview throws from the `53C` observer;
the unrelated fault propagates, with source world/target/counter snapshots and
existing renderer pixels unchanged. These are native ownership tests, not
original command/frame scheduling observations or exhaustive renderer isolation.

Early private tests retain their true failures: routes outside the immutable
clearance domain, the repeated-route recursion, and a later command that caused
another encounter instead of moving away. No mask, Cell identity or original
algorithm was relaxed to make those attempts pass.

The existing exact-binary 45-root preparation proof remains an actor0 proof of
the shared kernel. This integration adds **no original Scatter Process1 proof**.
Current normal and ASan/UBSan owned-Process runners replay the retained ordinary
two-actor pilot: 16 Process calls, 9 complete draws and 29 results. Both execute
against immutable original key
`df8c2f6c84a90b0669fc5e9dee8fc3571fc35b3f327889d65f3a55e545865689`,
with zero original instructions executed. That pilot retains its ordinary scope;
it does not verify the new interaction against the original.

Normal SDL still selects `ordinaryAdmission` with reservations and its Scatter/6
guard. The current 1,573-frame SDL check preserves the previous input/drawing
baseline; it does not exercise Scatter displacement. Its trace and all 58 PPMs
match the retained native baseline. The sandbox attempt failed before drawing
because no display was available; the Mac host run passed. Only Apple Silicon
macOS is tested. Local verification is not independent acceptance or original
whole-frame fidelity. No new runtime executable reads or external code is added.

## Reproduction and next integration

```sh
./build.command
./test.command
./run.command --owned-demo
./run.command --owned-smoke-test private/my-owned-sdl

env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/owned-terrain-runtime --parallel 4
build/tools-env/bin/ctest --test-dir build/owned-terrain-runtime --output-on-failure
# Same commands in build/owned-terrain-runtime-sanitize (RA2_SANITIZE=ON).

# Current production ordinary pilot, reusing originals; choose fresh output names.
/usr/bin/time -p env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/owned-preparation-next.audit.json \
  tests/compare_owned_unit_processes.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/owned-unit-world-vectors --pilot \
  --original-cache private/original-results --original-cache-require-hit \
  --output private/owned-preparation-next
# Sanitizer: build/sanitize/owned-unit-world-vectors, new audit/output names.
```

Build the dedicated CMake directories as documented in
`OWNED_SCATTER_INTEGRATION_1006.md`. New receipts and measured costs are in
`private/preparation-production-20261017/validation.json` and the opening handoff.
No unchanged original matrix, whole inventory or closed finalizer is regenerated.

Next bind a representative distinct-original Process0 then Process1 interaction
to these production owners and compare displacement, ordered effects and
interleaved drawing. Then perform the displacement scenario through actual SDL
input/drawing before adopting Scatter in the application. Keep direct routing,
the one-response budget, threshold and scheduling labeled as supplied policies.
