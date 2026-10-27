# Production-owner Scatter integration in progress

The subsequent [preparation binding](OWNED_PREPARATION_RUNTIME_1006.md) now
displaces the stationary resident in the native diagnostic scenario. The curved
self-Scatter case below retains its scope; SDL policy and original interaction
acceptance remain open.

`OwnedUnitScatter` now binds the existing complete Process/Advance/Cell/Unit/
nearby/destination kernels to the actual two-actor production owners. This is
an explicit diagnostic `ordinaryScatter` policy. The SDL application still selects
`ordinaryAdmission`; its Scatter/6 refusal and command reservations remain.
This checkpoint does not deliver the occupied-area displacement capability.

## Ownership and host policy

The binding borrows actual Drives, missions, Cell heads/Next/occupation, mutable
terrain/floor/fallback, on-map bytes and destination targets. Foot destination
and Process use the same retry530 and wait558 words. Legacy fixture arrays remain
the default for existing callers; focused tests poison them while binding each
production timer owner. Stores remain ordered558 then530, word by word.

The optional target-store notification records a host routing request at the
actual Foot target assignment. It makes no queries or gameplay writes. Repeating
the same target is still a command; consuming a queue entry is not. The earlier
before/after queue-head heuristic incorrectly requested a fresh route during
ordinary advancement; the native self-Scatter scenario exposed and prevents it.

After each complete Process, the supplied schedule installs bounded positive
direct routes for pending targets before the next actor's Process. It retains
destination Z and validates immutable sampled clearance/nonbridge Cells before
queue/control writes. Routes, scheduling, explicit-command target lifetime,
initial records/type associations/permission geometry, mission-control bytes,
notification/mission414/postCell490 results, heap services, RNG initialization
and retained upper table bytes remain supplied. There is no original pathfinding,
mission execution, startup or general collision-resolution claim.

Clones copy logical extra/wait/admission state, rebind targets to independently
owned Cells and rebuild callbacks/views. Native checks discard a target-bearing
clone after routing and Process while retaining the source's map/actor/command/
timer snapshots and actual target/pending identities. This is bounded clone
coverage, not complete isolation acceptance for every newly entered state.
Low-level entered failures may retain prefix writes; no tick rollback is added.

## What the native encounter actually does

On the supplied `mp03t4.map`, ordinary commands stage actor0 at91,102 and actor1
at93,104, then give actor0 directions2,4,3. At the curved jump, admission checks
the occupied candidate93,104. The recovered result6 dispatch instead queries the
late Drive head92,103, whose actual list contains actor0. Actual Cell snapshot/
Unit nearby handling therefore **scatters the mover itself**, choosing92,104 in
this supplied frame schedule. The adapter routes it there; it arrives with the
recovered destination Z. Actor1 stays at93,104 and subsequently accepts its own
independent move. Complete interleaved native draws and warm pixel reuse pass.

The earlier2,3,4,4 scenario reaches result6 but its head93,103 is empty at that
jump. Its zero member dispatches were correct. Private failed attempts and track
inspection remain under `private/owned-scatter-runtime-20261017/`; neither test
was fixed by substituting candidate for head or inventing Cell membership.

These are native integration observations. They are not original gameplay
observations, a distinct-original Process0/Process1 interaction, stationary-blocker
displacement or SDL Scatter acceptance. The existing complete original matrix
still proves actor0 roots only. Its separate actor1 child calls are not Process1.
The earlier16-root ordinary two-actor pilot retains its own non-Scatter scope.

## Verification and commands

Current receipts/costs belong in the opening HANDOFF and
`private/owned-scatter-runtime-20261017/validation.json`. The normal and full
ASan/UBSan borrowed/legacy comparisons reuse the same immutable original
generation, with all332 scenarios/339 complete Process calls. Both current native
runners execute on every hit. No new original instructions or changed-address
claims are introduced. Exact executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct.

```sh
./build.command
./test.command
./run.command --owned-demo

env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake -S tests/owned_terrain_runtime \
  -B build/owned-terrain-runtime -DCMAKE_BUILD_TYPE=RelWithDebInfo \
  -DCMAKE_OSX_ARCHITECTURES=arm64 -DCMAKE_PREFIX_PATH=/opt/homebrew
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/owned-terrain-runtime --parallel 4
build/tools-env/bin/ctest --test-dir build/owned-terrain-runtime --output-on-failure
# Separate build/owned-terrain-runtime-sanitize with -DRA2_SANITIZE=ON.
# This includes the diagnostic self-Scatter scenario; SDL remains guarded.

# Build the two current comparison runners as in BORROWED_PROCESS_SCATTER_1006.md.
# Choose new output/audit paths on every invocation.
/usr/bin/time -p env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/owned-scatter-next.audit.json \
  tests/compare_borrowed_process_scatter.py \
  --exe private/official-1006-probe/game.exe \
  --native build/borrowed-process-scatter/borrowed-process-scatter-vectors \
  --legacy-native build/process-terminal-scatter/process-terminal-scatter-vectors \
  --original-cache private/original-results --original-cache-require-hit \
  --output private/owned-scatter-next
# Sanitizer: both corresponding -sanitize directories; new output/audit paths.
```

For this retained generation, `/usr/bin/time` precedes `env`, matching the
recorded invocation environment including `_`. Reversing those launch wrappers
selects a cold key and require-hit refuses before original execution. Preserve
those failed receipts; do not edit origins or suppress genuine identity checks.
This does not establish a project-wide speedup or measure manual repair time.

Next establish the representative distinct-original interaction on these
production owners. The observed curved self-Scatter path does not solve the
stationary blocker case. Inspect the actual preparation/failed-route Scatter
caller needed for that case; keep supplied route policy distinct from its
original decisions. Then complete new-state clone/refusal coverage and actual
SDL displacement before changing the application's policy. No new Windows
actions, downloads, workers, runtime executable reads or external code are used.
Only Apple Silicon macOS is tested; local verification is not independent
acceptance or original-frame fidelity.
