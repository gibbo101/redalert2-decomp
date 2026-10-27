# Two commandable Units on one owned terrain world

[SDL resident displacement](OWNED_SCATTER_SDL_1006.md) now explicitly adopts
ordinary Scatter/Advance6 in normal owned play/reset after actual acceptance.
The optional factory argument stays guarded, and ordinary smoke retains its
previous profile. Destination delay8 is supplied consistently with the original
encounter. Earlier refusals below retain their checkpoint scopes; other routes/
timings can still enter unsupported terrain children. See the current note and
opening handoff for that preserved failure, proof scopes and next recovery.

Normal movement acceptance now uses [bounded command validation](BOUNDED_COMMAND_VALIDATION.md),
with zero future ticks. Full-journey previews described below remain diagnostics;
their former role as a mandatory runtime command gate is superseded. Current
SDL/regression receipts and limits belong in the opening HANDOFF.

`--owned-demo` is a bounded two-tank prototype on the supplied `mp03t4.map`.
Either Rhino can be selected and commanded. The retained `--resident-demo` still
has one commandable mover and an inspection-only parked tank. Base RA2 and Yuri's
Revenge remain incomplete. Current receipts, counts and acceptance status belong
in the opening [HANDOFF.md](HANDOFF.md).

The subsequent [ordinary Advance command/preview integration](OWNED_ADVANCE_RUNTIME_1006.md)
explicitly enables 0/2/7 in the bounded SDL factory and reset path, after genuine
original commands/finalization, full preview isolation and actual SDL acceptance.
The optional factory argument and low-level inputs retain guarded defaults.
Earlier 6/7 guard descriptions below retain their checkpoint scope; Advance6 and
scatter still refuse. There is no new movement kernel or mirrored state.

## Ownership and runtime boundary

`OwnedTerrainRuntime.hpp` owns one stable `OwnedUnitWorld`, an explicit tick,
pause/status, immutable clearance bytes and the supplied step policy. There is no
`Simulation`, mirrored `Drive`, second map or second authoritative command state.
The factory creates distinct actor0/actor1 records at (86.5,101.5) and
(90.5,101.5), with body headings16384 and independent turret headings16384/32768.
Actual initial height, Unlimbo and Mark run in actor1-before-actor0 order on the
shared prepared mutable map. Legacy single-Process admission is never enabled.
The type, House, visibility, starting poses, wait duration8 and zero runtime
retry/timer padding remain supplied construction inputs.

The runtime retains shared immutable Drive/numeric lifetimes. Its square-root
callback captures a copied immutable `RenderData` owner, not mutable `GameAssets`
or a renderer. Clearance copies `terrainCommandCell`'s asset/domain/scenery mask
and does not borrow rendering or floor callbacks. `move` previews both actual
actors on one discarded clone with the same Process0 -> Process1 -> finishTick0
-> finishTick1 schedule as live advancement. Only accepted live floor/order
effects are applied; no preview time, actor, map or renderer state is committed.
See [OWNED_SCHEDULED_PREVIEW_1006.md](OWNED_SCHEDULED_PREVIEW_1006.md).

Both actors' named services and speeds are validated before advancing the live
tick. Reentry is refused. Unrelated live faults propagate and release the guard;
partially executed live steps are not rolled back. Tick addition preserves signed32
wrapping. Preview domain/admission refusals stay typed; unsupported Advance6
aftermath, scatter, nonzero57A/sound and earlier excluded paths remain refusals.
Callbacks and observers must obey the existing explicit-owner/pure-numeric
contracts. Arbitrary external side effects are not transactional.

`OwnedUnitDrawFrame` carries only the supplied display tick. The renderer receives
this frame and `OwnedUnitDrawScene`'s explicit actor/turret/map references, rather
than a dummy `Simulation`. Actual selected-actor location/destination supplies the
temporary selection/command markers. Per-actor resources, screen registry IDs,
visibility and staging bytes remain distinct; all four type indexes, image,
staging surface, pool and world planes remain shared. `center(Coord)` supplies
the camera coordinate. Legacy renderer entry points remain available.

`OwnedSdlApp.hpp` enters before any legacy `Simulation` construction. LMB selects
either actor; empty selection commands nobody. RMB replaces the selected actor's
route, Ctrl-RMB appends, Shift-RMB aims its turret, Q/E turns its body, A/D turns its
turret and S stops after the committed track. G requests two Cells in +X from the
selected actor's current Cell. Space pauses, R reconstructs the owner, H centers
the selected actor (actor0 if none), arrows pan, +/- or wheel zoom, brackets change
speed, C changes color, T/P inspect scenery/props and Esc exits. Controls, direct
routes, sampled clearance, picking, visibility, camera, layer order, deferred
turns, target lifetime and the two-actor frame schedule are supplied policies.
This is not original pathfinding, mission scheduling or UI recovery.

## Evidence and limits

The original target remains 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage and reported no-CD provenance remain distinct;
pristine authenticity is unverified. No new binary range/runtime executable read,
external code, dependency or platform support is introduced. Original execution
uses test-only Unicorn; no original instructions execute in the shipped program.

The dedicated differential runner adopts `OwnedTerrainRuntime` and a borrowed
pointer to its genuine world. Consecutive H commands enter `runtime.step`; each
actor retains its own original actor/Drive address in one guest. Original-backed
finalization precedes interleaved complete drawing and later Process. Only authored
initial map/routes/labels are reused from earlier fixtures; new original results
execute afresh. Command timestamps remain explicit authored inputs, not a claim
that the original UI schedules commands this way. Differential padding stays the
earlier explicit nonzero diagnostic inputs; the runtime demo's zeros are supplied.

Comparisons retain each complete Process return, selected ordered stores and all
logged queries, both supported actor/map/command/turret/wait views, full queues,
House/Next/occupation/buffers/floor/fallback, body/turret/barrel/shadow matrices and
keys, type indexes/image/pool and final world RGB565/depth/alpha projections.
This is a bounded recovered-routine proof, not every machine store, original frame
scheduling, all renderer adapters or full startup/frame/game parity.

Native integration checks separately cover initial retained-resident presentation
parity, actual concurrent movement and membership, occupied/future-occupied refusal,
command-only live acceptance, independent stop/deferred body/turret turns,
pause/reset, append arrival, explicit-frame warm rendering, service validation,
observer order, reentry, live-fault cleanup and signed tick wrapping. The retained
warm preview checks cover complete simulation/map/renderer isolation.

The SDL smoke test injects real SDL events through the interactive handler and
uploads/presents each tested frame. It checks selection, unselected commands,
independent turns, two moving actors, occupied/future refusals, committed stop,
deferred body turn, replacement/append arrival, aim, pause/reset, shared membership,
distinct draw poses/resources/registry IDs and warm cache reuse. Private JSONL and
frames retain native evidence. This does not establish original controls or
OS-level pointer automation. Screenshots and self-consistent tests alone establish
no original fidelity. Only Apple Silicon macOS is tested; local verification is
not independent acceptance.

## Build, run and reproduce

```sh
./build.command
./run.command --owned-demo
./run.command --owned-smoke-test private/my-owned-sdl
./run.command --resident-smoke-test private/my-resident-sdl
./run.command --terrain-smoke-test private/my-terrain-sdl
./test.command

env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake -S tests/owned_terrain_runtime \
  -B build/owned-terrain-runtime -DCMAKE_BUILD_TYPE=RelWithDebInfo \
  -DCMAKE_OSX_ARCHITECTURES=arm64 -DCMAKE_PREFIX_PATH=/opt/homebrew
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/owned-terrain-runtime \
  --target owned-terrain-runtime-check owned-terrain-runtime-vectors --parallel 6
build/tools-env/bin/ctest --test-dir build/owned-terrain-runtime --output-on-failure
# ASan/UBSan: repeat in build/owned-terrain-runtime-sanitize, Debug,
# with -DRA2_SANITIZE=ON; run that directory's CTest.
PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  -m unittest discover -s tests -p 'test_*.py'

# Fresh original: authorized host Unicorn JIT, NEW ignored output/audit paths.
PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/unit-draw-1006/runtime-new-audit.json \
  tests/compare_owned_terrain_runtime.py \
  --exe private/official-1006-probe/game.exe \
  --native build/owned-terrain-runtime/owned-terrain-runtime-vectors \
  --output private/unit-draw-1006/runtime-new
# Replay: replace --output with --expectations CURRENT_EXPECTED_JSON
# --report NEW_PRIVATE_JSON and use a new audit. For ASan/UBSan, change the
# native path to its runner. --uncached before the driver is the reuse control.
```

The dedicated runtime checks are not registered in `./test.command`; invoke the
nested CTest explicitly. Never rerun a closed finalizer or relabel old expectations.
Keep public sources fixed during guarded original/replay invocations. The selected
terrain projection must be freshly verified when its full source closure changes.
Source installations/discs and outpost2-native remain read-only; all proprietary
inputs, frames, research environments and evidence stay ignored. No workers,
Windows action/transfer, download, publication or system/Xcode/DRM change is part
of this milestone. General pathfinding, combat, AI, economy, campaigns, multiplayer,
saves and Yuri's Revenge remain open.
