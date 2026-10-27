# Cell/Unit Scatter over actual prepared owners

This is an internal checkpoint under the active **two-tank occupied-area
encounter** capability. The acceptance scenario is: order one tank into the
other's occupied area, execute the original nearby-displacement decision, move
both tanks, and continue independent commands and complete drawing. Acceptance
also needs rejected-order/full discarded-preview isolation and ordinary SDL
controls. This checkpoint establishes the borrowed Cell/Unit/nearby join only.
It does not make displacement playable. The current `--owned-demo` still has two
commandable Rhinos using ordinary Advance0/2/7, with Scatter/6 refused.

## Exact target and implementation

The supplied private target is `private/official-1006-probe/game.exe`, 4,485,392
bytes, SHA256 `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. The existing exact-base verifiers and
unchanged original Cell476920 -> Unit7072D0 / nearby5502E0 -> destination roots
are reused. See [CELL_UNIT_SCATTER_WORLD_1006.md](CELL_UNIT_SCATTER_WORLD_1006.md),
[CELL_NEARBY_SCATTER_1006.md](CELL_NEARBY_SCATTER_1006.md) and
[BORROWED_UNIT_ADMISSION_1006.md](BORROWED_UNIT_ADMISSION_1006.md).

`BorrowedCellUnitScatterWorld.hpp` exposes the borrowed aliases of the same
structural Unit/Cell composition used by the retained value APIs. Nearby uses
the same kernels too. There is no second snapshot, Scatter, admission or nearby
algorithm. All legacy aliases, projection refresh and entered refusals remain.
The borrowed Cell view consumes `BorrowedPreparedUnitAdmission::motion()` and
requires empty eligibility/short-track projection spans. It validates actual
Drive position/destination/head/body/queue/track/index/eligibility and target494
addresses, distinct actors/Drives/reference counts, and shared map/floor/numeric/
lifetime associations. It never refreshes copied motion or target values.
Binding itself makes no world queries, cache warm-up or fallback stores.

Map roots already assign the physical fallback point. The new
`PreparedUnitMembership::forwardAssignedFallback` checks that point, updates its
membership and visibility associations, and emits one store observation. The
borrowed Unit composition calls it before its read-only trace. Direct admission
lookup still assigns/forwards once through its canonical store operation; its
later F observer only reports the event. The legacy value composition retains
its existing projection synchronization and event stream. No observer is used
to refresh borrowed gameplay fields. Named diagnostic callbacks may throw; scoped
observers/references restore, while snapshot release is not invoked on exceptional
dispatch. No transactional rollback is claimed.

The test fixture supplies initial records once, binds exactly actors0/1 to the
prepared membership and independently addressed Drives, then consumes only the
prepared records throughout each sequence. Three unused original actors remain
unreachable in the five-address original diagnostic arena. Exporting final
observations formats the old oracle output after all calls; it is never fed back
into admission. This is not original construction, ownership of arbitrary actors,
production Process adoption or proof of complete actor1 Process. Extra profiles,
heap/atomic/timer-padding services and initial associations remain supplied.
Stable owners and numeric services must outlive views; clones require rebinding.

## Evidence

Canonical fresh evidence is `private/map-depth-1006/borrowed-cell-scatter-v1/`:
**170 sequences /196 complete original Cell calls**, 3,134 distinct original
instructions. Both actors dispatch at their own original addresses. Nonzero
roots include128 actual resident-distance returns and admission0/2/6/7. Nearby
roots include186 searches; all193 zero-point dispatches retain RNG and queued
mission. These counts describe entered branches, not completeness or a playable
milestone. Normal/sanitizer replays and a fresh inspection-uncached generation
retain every command, label and output. All ordered query/store streams, final
queues, targets, timers, references, RNG, floor cache, retained motion and fallback
are compared by the existing exact-original harness.

Sixteen native ownership/refusal checks include no-query binding, split
Drive/target rejection, rejection of projection spans/missing live motion, live
queue/destination/target writes at the supplied snapshot-allocation boundary,
single fallback forwarding before observation, RNG preservation and observer-fault
cleanup without a false rollback/release claim. The first native check attempt
miscounted existing observer calls after intentional admission queries; its log
is preserved. It was repaired to compare the observer count relative to entry.
Original/native behavior was not changed to accommodate the test.

Current legacy projection refresh, root/standalone tests, SDL identities and costs
are in HANDOFF and `private/borrowed-cell-scatter-candidate-20261017/`. The old
205 receipt/closure hashes stay unchanged. This is not a current full refresh of
the old204-record downstream gameplay inventory; its closed finalizer stays
pinned. Local verification is not independent acceptance, an original-game
observation or original-frame fidelity. No new public source, generated/lifted
code, extracted table or dependency is incorporated.

Fresh original generation/native comparison takes79.915s/4.601s; the fresh
inspection-uncached control takes79.120s/3.442s. These are bounded verification
costs under overlapping checks, not game-performance or whole-task timings.
Manual review/repair time is unmeasured. The separate whole-generation reuse
protocol remains restricted to its eight reviewed drivers. This new driver does
not opt in merely because its inputs are called original fixtures. Existing
strict `--expectations` replay is used for its current-source runners.

## Build, original and replay commands

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake -S tests/borrowed_cell_scatter \
  -B build/borrowed-cell-scatter -DCMAKE_BUILD_TYPE=Debug
DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/borrowed-cell-scatter -j 4
build/tools-env/bin/ctest --test-dir build/borrowed-cell-scatter --output-on-failure
```

Configure a separate `build/borrowed-cell-scatter-sanitize` with
`-DRA2_SANITIZE=ON` for the sanitizer runner. For each verification invocation use
new private output/audit paths. Fresh original execution needs the authorized Mac
host JIT context; the application never executes original code.

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools \
PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/borrowed-cell-try.audit.json \
  tests/compare_borrowed_cell_scatter.py \
  --exe private/official-1006-probe/game.exe \
  --native build/borrowed-cell-scatter/borrowed-cell-scatter-vectors \
  --output private/borrowed-cell-try
```

For strict current-source replay, replace `--output` with
`--expectations private/map-depth-1006/borrowed-cell-scatter-v1/expected.json
--report NEW_PRIVATE_JSON`, and use a new audit. The sanitizer runner is a distinct
current replay. Add `--uncached` before the driver and a new output for a second
fresh original control; this disables immutable inspection reuse.

```sh
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest -v \
  test_borrowed_cell_scatter_evidence
./build.command
./test.command
./run.command --owned-demo
./run.command --owned-smoke-test private/borrowed-cell-sdl-try
```

A concrete production blocker is `OwnedUnitOrders::finishTick`: it currently
clears an idle Drive destination when the queue head is -1. A freshly installed
Scatter destination needs an explicit positive-route phase before it can cause
movement; simply swapping the Process entry would lose that destination at
finalization. Any bounded direct-route phase must stay a named supplied adapter
outside recovered roots, with its own ordered trace/proof boundary; it cannot be
called original pathfinding. Command navigation/turret state must then follow the
same actual actor, not an old host target. Clone target references must be rebound
to clone Cells/actors before queries, rather than retaining source pointers.

Next carry these exact mutable owners through Advance and complete Process,
prove Process0 -> Process1 -> interleaved complete draws -> later Process, then
full discarded command previews/warm renderer values, associations and backing
storage isolation, followed by actual SDL displacement. Destination assignment
is not movement; positive route production, route/clearance/frame/control policies
remain explicit supplied boundaries. Preserve all runtime Scatter/Advance6 and
special child refusals until that acceptance passes. Base RA2 and YR, general
pathfinding, combat, economy, AI, campaigns, multiplayer, saves and audio remain
incomplete. Only Apple Silicon macOS is tested. No workers, Windows actions,
downloads, publication, runtime-read expansion or system/Xcode/DRM changes occur.
