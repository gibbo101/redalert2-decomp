# Complete Process over actual prepared Scatter owners

This is an internal integration checkpoint toward the bounded two-tank
occupied-area encounter. It carries the prepared admission, motion, target,
mission, membership, occupation and floor owners through complete ordinary
Process and result-bearing Advance, including terminal Cell handling and
Cell -> Unit Scatter -> nearby/destination children. The application still uses
ordinary Advance0/2/7. Runtime Scatter/6 remains refused; destination assignment
is not movement.

The supplied private executable is 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. The existing exact-base complete
Process4A05F0/preparation4A2670 oracle and its independently addressed Unit
children are reused. No original instruction is modified.

## Implementation and supplied boundaries

The four existing Advance/Process composition headers now accept structural
admission/motion views. Both legacy value and prepared borrowed views use the
same movement, preparation, terminal, snapshot, Scatter and nearby algorithms.
The legacy aliases, refresh scope and entered refusals remain.

Process checks the actual shortTrack owner in the borrowed live motion record,
with no copied short-track or eligibility spans. It checks Drive position,
destination, head, Facing, queue head, track/index, eligibility and target494
addresses before querying or storing. Advance's map-root fallback callback now
forwards already-assigned membership/visibility associations before its
read-only observer, exactly once per actual store. Legacy fallback scope and
outputs are retained. No observer refreshes borrowed motion, mission or targets.

The diagnostic runner uses one parser and output protocol for both compositions.
Its borrowed build supplies initial records once, then consumes only prepared
owners through Process admission, gate and next-Cell services. Exports to the
five-actor observation layout happen after the complete call sequence, never
between roots or as input to admission. Only two actors are bound; the three
remaining original diagnostic actors stay unreachable. Each clone still needs
fresh bindings and target-pointer rebinding.

Original Process root coverage remains actor0. Native ownership checks call
both actual prepared actors and later actor0, but that does not establish
original Process1, interleaved complete drawing or the production two-Process
join. Initial healthy400/400/threshold0.5, records/associations, per-Advance frame
bytes, heap/atomic/padding, Mark/occupation, notification174, mission414,
postCell490 and failed-route effects remain supplied. Existing special actor,
bridge, target and child exclusions remain explicit. Prefix effects on refusal
are possible; there is no low-level rollback claim.

No new public, generated or lifted code, table or dependency is incorporated.
Runtime executable reads are unchanged. Original files/research/receipts and
binaries remain ignored and unshipped. Only Apple Silicon macOS is tested.
Local verification is not independent acceptance or original-frame fidelity.

## Verification and reproduction

Canonical `private/map-depth-1006/borrowed-process-scatter-v1/` matches
**332 scenarios /339 complete original Process calls**, executing 5,253 distinct
original instructions. Every previous Process command, label and output is
identical. Both current native compositions match the one fresh expectation set.
Normal and borrowed-sanitizer replays and a second fresh inspection-uncached
control pass. The sanitizer replay retains the identity-pinned normal legacy
runner, as described below.

Actual counts retain all three Advance callers 265/2/31, both preparation sites'
0/2/6/7 admissions, 136 Advance6 continuations and136 dispatches to each distinct
actor, 272 nearby searches, 20 null Unit410 requests and 3 direct Move_To calls.
Those branch counts do not expand the profile or prove Process1. Nineteen new
native ownership/fallback/refusal checks pass in both modes; eight Python tests
protect the new profile, source/runner/receipt guards and execution of both
current native runners. Prior legacy guard checks also pass.

Fresh guarded wall/original generation/dual-native comparison is
259.211s/233.330s/8.074s. Normal and borrowed-sanitizer replays take 32.126s/40.626s
guarded wall, with no original instructions executed. The uncached control
is 264.789s guarded/240.128s original generation. These bounded times overlap
other checks and are not whole-task or game-performance measurements.
The three directly affected Advance families freshly retain all 625 prior
scenarios and pass normal/sanitizer replays: 160 isolated block calls and 507
complete Advance calls. Their build/fresh/replay sum is 637.871s, including
536.985s reported original generation. All 205 historical receipt/closure hashes
remain identical. The old 204-record downstream inventory is not represented as
a current full refresh, and closed finalizers are not rerun.

Root build and manual review/repair costs are unmeasured. Early configure/build
attempts (unfinished CMake configuration, reference-map indexing and const tick
assignment) remain in private logs; no original/native mismatch was found.
The 20-scenario pilot predates the added split-Drive guard and keeps its own
source identity. Receipts are never overwritten or relabeled. Private aggregation
also correctly refused a replay passed to the fresh-only receipt validator;
its repaired script validates fresh receipts first and separately checks replay
source/input/runner hashes and execution metadata. That failed attempt is
preserved privately. No driver, guard or receipt was changed for the repair.

Current receipt identities, counts, measured costs and remaining integration
belong in the opening HANDOFF. The existing original Process matrix is executed
once per fresh run and compared with both current borrowed and retained legacy
native runners. A sanitizer replay executes the current borrowed sanitizer
runner and the identity-pinned normal legacy runner; it does not claim a full
sanitizer legacy Process matrix. Inspection reuse has a separate fresh uncached
control. Those are the retained checkpoint receipts. The driver now supports
explicit whole-generation reuse; current commands below select it. See
[ORIGINAL_RESULT_REUSE.md](ORIGINAL_RESULT_REUSE.md) and the opening HANDOFF for
the new normal and full sanitizer comparison results.

```sh
./build.command
./test.command
./run.command --owned-demo

env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake -S tests/borrowed_process_scatter \
  -B build/borrowed-process-scatter -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_OSX_ARCHITECTURES=arm64 -DCMAKE_PREFIX_PATH=/opt/homebrew
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/borrowed-process-scatter --parallel 4
build/tools-env/bin/ctest --test-dir build/borrowed-process-scatter --output-on-failure
# Separate build/borrowed-process-scatter-sanitize with -DRA2_SANITIZE=ON.
# Retained normal legacy runner must also be built from current sources:
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake -S tests/process_terminal_scatter \
  -B build/process-terminal-scatter -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_OSX_ARCHITECTURES=arm64 -DCMAKE_PREFIX_PATH=/opt/homebrew
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/process-terminal-scatter --parallel 4

# New private paths; a miss requires authorized Mac-host Unicorn.
env DEVELOPER_DIR=/Library/Developer/CommandLineTools PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/borrowed-process-new.audit.json \
  tests/compare_borrowed_process_scatter.py \
  --exe private/official-1006-probe/game.exe \
  --native build/borrowed-process-scatter/borrowed-process-scatter-vectors \
  --legacy-native build/process-terminal-scatter/process-terminal-scatter-vectors \
  --original-cache private/original-results \
  --output private/map-depth-1006/borrowed-process-new
# Native-only check: add --original-cache-require-hit, choose new output/audit.
# Both runners may use their sanitizer builds without changing the original key.
# Fresh control: add --original-cache-mode refresh; new output/audit paths.
# --uncached before the driver disables inspection reuse only.
# Strict historical replay: omit --original-cache; replace --output with
# --expectations EXPECTED_JSON --report NEW_JSON. It retains exact source guards.
```

Next establish genuine original Process0 -> Process1 -> interleaved complete
draws -> later Process over production owners, command/fault isolation and
warm drawing checks, followed by ordinary
SDL displacement. A Scatter-installed destination needs a bounded positive
route phase before `OwnedUnitOrders::finishTick` clears an idle empty-queue
destination. Keep that phase supplied and outside recovered roots; it is not
original pathfinding. Host navigation/turret state must follow the actual actor.
