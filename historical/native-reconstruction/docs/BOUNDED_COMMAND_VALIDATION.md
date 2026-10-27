# Bounded movement command acceptance

The owned SDL runtime now calls `commandOwnedUnitMove` in
`src/platform/OwnedUnitMoveCommand.hpp`. Acceptance constructs at most 23 direct
route steps, checks the current prepared Cell domain and immutable clearance
mask, validates both actors' required services, and applies only the floor/order
effects to a discarded owner. It executes **zero Process calls or future ticks**.
On acceptance, the same floor/order sequence runs live. Positions, time, wait,
turret state and renderer storage are never advanced during acceptance.

This replaces the full-journey prediction requirement for normal owned-demo
commands. `previewOwnedUnitMove` and its `moveOwnedUnit` diagnostic helper retain
their previous complete cloned schedule, arrival/tick-limit and isolation checks.
They remain useful tests, but the SDL command path no longer calls them.
An accepted command can wait, fail to arrive, or encounter an unsupported later
state. Original Process/Advance admission and existing refusals still run on each
live tick. No recovered movement algorithm, original address or runtime binary
read changes in this patch.

The guard samples quarter-Cell footprints along the supplied direct route at
16-lepton intervals. It checks both actors' initial/committed segments and
refuses bridges, missing/masked Cells, invalid directions, overly long routes,
stationary occupants and conflicting commanded endpoints. Moving crossings are
left to actual tick admission. It does not reserve an entire future trajectory;
the original Advance7 SDL crossing remains supported. These checks and routing
are supplied prototype policies, not original pathfinding, collision proofs or
original command semantics. Curved future footprints are not predicted here.

The clone is the bounded command transaction: rejected validation/command effects
never reach the source. Clone callbacks are rebound by the existing world owner;
the renderer is not passed to validation. Arbitrary externally throwing callback
effects are not transactional. The live owner-local floor/order commit keeps the
existing synchronous contract. Live ticks retain their existing failure semantics;
this change is not a tick rollback or complete unsupported-state recovery system.

Focused checks cover both actor identities, exact accepted floor/order effects,
zero simulated ticks even with supplied speed zero, independent retained arrival
diagnostics, intermediate masks, bridge/input/services/fault isolation and source
values/associations. Runtime integration checks retain concurrent movement,
membership, independent controls, append/replacement, pause/reset and complete
warm drawing. Actual SDL acceptance uses the existing ordinary-input scenario,
including its genuine moving-resident Advance7 and later arrivals. This is native
integration evidence; it adds no new original-routine fidelity claim.

```sh
./build.command
./run.command --owned-demo
./run.command --owned-smoke-test private/command-sdl-new
./test.command
DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/owned-terrain-runtime \
  --target owned-terrain-runtime-check --parallel 6
build/tools-env/bin/ctest --test-dir build/owned-terrain-runtime --output-on-failure
# Repeat the standalone build/check using build/owned-terrain-runtime-sanitize.
```

Current receipts, measured costs and the remaining occupied-area encounter work
belong in [HANDOFF.md](HANDOFF.md). Runtime Scatter/Advance6 remains guarded;
production borrowed admission and the displacement route phase remain next.
