# Stable two-Unit command world owner

`src/platform/OwnedUnitWorld.hpp` is an SDL-free composition owner for the two
membership-bound actors, their shared mutable map and `OwnedUnitProcesses`.
It is intentionally separate from `Simulation` and is not wired into SDL.
The existing resident demo retains one commandable mover and inspection-only
Unit1. Base RA2 and Yuri's Revenge remain incomplete.

Per-actor route/stop/pending-body-turn integration is now recorded separately in
[OWNED_ORDERS_WORLD_1006.md](OWNED_ORDERS_WORLD_1006.md). The command/preview gates
below describe this owner's earlier construction checkpoint; full scheduled
preview and runtime/SDL acceptance remain open.

The owner keeps the existing immovable `TerrainUnitContext` at a stable address,
shared immutable Drive/numeric inputs, persistent per-actor wait records, two
separate host command records and explicit turret Facings. Actor0's turret is
owned directly; actor1's existing optional turret association is required.
`actor(id)` returns references to the exact membership-bound Process state,
turret, command and wait records. There is no mirrored `Drive`, second map or
actor1-as-actor0 substitution. The owner cannot be copied or moved; moving its
`unique_ptr` retains every callback address.

## Construction, clones and service scope

Construction requires two bound actors, actor1's explicit turret, immutable
Drive/numeric owners and no enabled legacy single-Process admission binding.
The existing canonical map/member/slot/fallback/type checks still run. Construction
makes no floor, fallback or Cell query. Supplied scalar/type/House/initial records
retain the bounded `OwnedUnitProcesses` contract.

Cloning copies logical map/member/actor/Next/House/discovery/occupation/buffer/
lazy/fallback values through the existing context clone, then constructs fresh
Process callbacks and copies both wait/command/turret records and selection.
Live construction-time membership/query observers are dropped by that clone.
Named notification, post-Cell and no-route callbacks copied internally from the
old context's supplied service record are replaced before constructing the new
Process binding. The new numeric callback has an explicit shared immutable
lifetime and must be pure; callers must not capture a live simulation or observer.

`process` requires explicit notify, postCell, noRoute and failedRoute services.
An intentionally effect-free supplied boundary uses explicit empty lambdas.
Actor/ramp/Drive stores, decisions and the owned admission's word-query observer
are optional per-call observations. The context's live construction observers
retain their existing scope. A scoped services pointer is cleared on ordinary
return and every exception; reentry into the same owner is refused before queries.
There is no retained reference to a previous call's services.

`preview` clones once, invokes a caller-supplied operation/schedule on that copy
and discards it. Only `UnsupportedGroundRoute` and `UnsupportedGroundAdmission`
become typed domain results, retaining the admission code. A false operation is
a rejection; unrelated exceptions propagate. The owner never commits a preview.
The operation must act on the supplied copy and must not capture or mutate live
owners. This is a host ownership facility, not recovered original pathfinding,
a transaction over arbitrary external callbacks, or full runtime route acceptance.

## Differential and native evidence

The dedicated authored runner adapts the existing two-Process fixture but actually
adopts `OwnedUnitWorld`, uses its actual Process calls, wait and turret references,
then feeds complete interleaved drawing from the owned mutable Cells. The original
protocol and distinct-address oracle remain unchanged. A separate driver retains
all original Process returns, selected ordered stores, logged queries, actor/shared
snapshots and complete drawing comparisons. It records the new owner, runner,
check, driver and nested CMake identities in addition to the full legacy closure.
No old expectation or closed finalizer is relabeled or rerun.

Current accepted receipts, counts, checks and timings belong in the opening
[HANDOFF.md](HANDOFF.md). The new source proof uses a new private directory;
preliminary native comparisons against earlier command streams are diagnostics,
not fresh original evidence. Original and native runs retain their own identities.

Native ownership checks cover no-query constructor refusals; absent named-service
refusals; exact distinct actor references; per-actor command/turret/wait state;
logical warm clone/reclone equality; mutable map/floor/fallback and observer
isolation; stable pointer moves; exception cleanup and Process reentry refusal;
preview acceptance/rejection/domain results and unrelated-fault propagation;
and immutable numeric lifetime after destruction of source owners.
The two-Process runner additionally retains its existing association/unknown-actor,
warm-step and actual native Advance6/7 refusal checks. The result7 diagnostic
adopts an isolated context with an explicitly supplied zero-speed shared type;
it is not a live type mutation or execution of the excluded original aftermath.

`turnTurret` and `updateTurret` reuse the recovered Facing/bearing operations and
existing ordinary target/body policy without duplicating movement state. Their
per-actor original integration is now separately verified in
[OWNED_TURRET_WORLD_1006.md](OWNED_TURRET_WORLD_1006.md). The original canonical
owner stream retains supplied initial turrets; the separate extension exercises
these methods before later Process and complete drawing. Command/preview and
selected-actor runtime/SDL acceptance remain open.

## Build and reproduce

This unwired integration has a dedicated CMake check project. It builds the same
libraries from their source files and adds the new runner/check; the root CMake
registration, application sources and canonical legacy runner stay unchanged.
This keeps existing receipts attached to their actual source/runner identities.
It is not part of `./test.command` yet.

```sh
# Existing application:
./build.command
./test.command
./run.command --resident-demo

# New unwired owner and headless checks:
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake -S tests/owned_command_world \
  -B build/owned-command-world -DCMAKE_BUILD_TYPE=RelWithDebInfo \
  -DCMAKE_PREFIX_PATH=/opt/homebrew
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/owned-command-world \
  --target owned-command-world-check owned-command-world-vectors --parallel 6
build/tools-env/bin/ctest --test-dir build/owned-command-world --output-on-failure

# Sanitizer: repeat configure/build with build/owned-command-world-sanitize,
# -DCMAKE_BUILD_TYPE=Debug and -DRA2_SANITIZE=ON; then its CTest directory.
PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  -m unittest discover -s tests -p 'test_*.py'

# Fresh original: authorized host Unicorn JIT context, NEW private paths.
PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/unit-draw-1006/command-world-new.audit.json \
  tests/compare_owned_command_world.py \
  --exe private/official-1006-probe/game.exe \
  --native build/owned-command-world/owned-command-world-vectors \
  --output private/unit-draw-1006/command-world-new
# Replay: replace --output with --expectations CURRENT_EXPECTED_JSON
# --report NEW_PRIVATE_JSON; use a new audit. For sanitizer replay replace
# --native with build/owned-command-world-sanitize/owned-command-world-vectors.
# --uncached before the driver selects the inspection-reuse control.
```

Only Apple Silicon macOS is tested. The private executable remains 4,485,392
bytes, SHA256 `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage and reported no-CD provenance remain separate;
pristine authenticity is unverified. No new executable range or runtime read is
introduced. Unicorn and original executable reads remain research-only.

## Remaining gates

Initial actor/type/House/visibility/heap/camera/planes, opaque padding, routes,
speeds and named services remain supplied. Direct routing/clearance, selection,
controls, target lifetime, layer order and both-actor scheduling remain adapters.
Rendering retains separate actor resources/registry/staging and shared type
indexes/global pool; this owner adds no renderer cache or duplicate drawing state.
Preview drawing and full scheduled command/refusal behavior still need integration.

With independent turret command/step evidence recorded separately, route/stop/
body-turn policies over both actual records, complete preview/refusal isolation
including renderer boundaries,
selected-actor runtime routing and actual SDL move/stop/body/turret/reset/interaction
acceptance still precede two-mover promotion. Unsupported Advance6/7 aftermath,
scatter, nonzero57A/sound and earlier route exclusions remain refusals.
No original startup, general pathfinding, combat, full-frame or whole-game claim
follows from these bounded proofs. No workers, downloads, new Windows actions,
source installation/disc/outpost2 writes, system/Xcode/DRM changes or publication.
