# Walk selected-head update-position schedule

The newer [joined proof](WALK_UPDATE_POSITION_JOIN_1006.md) now executes the
original caller and complete child together. The inspected/scheduled-preview
checkpoint below retains its historical scope; live scheduling remains disabled.

The exact production producer for Infantry update-position is now identified.
It is the selected-head arrival continuation in Walk `Movement_AI 71E220`, not
the geometric Cell-crossing tail. The application still does not commit the
effects to the live world.

## Exact inspected order

The supplied executable is 4,485,392 bytes with SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
The complete `71E220` range is 4,967 bytes with SHA256
`c1d2fff335d910d70882a6f3c51d2fe05255299da2b6a3d764df7778d892f896`.
The selected-head block `71F0D3..71F2D6` is 516 bytes with SHA256
`3ca7d638c5674c470f2db49835573349595a77b0fb2250bcb13310121ab672c0`.

The pinned order is:

1. `71F0D7` dispatches `Mark(0)`;
2. the route shifts, actor location/Cell words/height are stored, and `71F172`
   enters the recovered head transfer;
3. `71F192` pushes argument `2`, then `71F196` dispatches Infantry vtable slot
   `+174`; the exact Infantry vtable maps that slot to `500AA0`;
4. only after the call returns, `71F19F`, `71F1AA` and `71F1B5` reread actor
   bytes `+7D`, `+76` and `+7A` for the late exits; and
5. the eventual completion/Mark tail proceeds according to those live values.

There is exactly one `+174` call in complete `71E220`. The separate geometric
Cell-crossing block at `71F4ED..71F534` performs current-Cell `548000` and dirty
`47BB30` calls; it contains no update-position dispatch. Calling this a
"Cell-crossing schedule" was imprecise.

The immutable inspection receipt is
`private/boot-camp-20261018/walk-update-position-schedule-a1.json`. This is exact
binary inspection combined with the earlier 380-call Walk arrival differential
proof. It does not execute Walk and complete `500AA0` in one original root.

## Scheduled disposable owner proof

`BootCampWalkWorld::composeUpdatePositionPreview` now creates a fresh Day 1
owner graph, copies the initialized selected GI/order state, and advances the
recovered Walk Process until its actual `arrivalNotification(id,2)` service
fires. That service invokes the complete native update-position/position/sight
composition on the same disposable actor, map, mission and visibility owners.

For the accepted `(57,89) -> (59,89)` order, the dispatch occurs on Process call
26 after the GI reaches `(58,89)` at `(15040,22976,208)`. The current Cell is
therefore `(58,89)`, not the initial Cell. Because exact arrival order has
already performed `Mark(0)`, all three current/target kind-6 searches return
empty without a GI kind or `Next` query. The remaining bounded parent results
stay the same: one sight add, 383 mask calls, 282 redraws, final range 5/active
sight, one permission query and the complete position/map/dirty early-return
tail.

The disposable run translates only recognized clone Cell identities for
inspection. The live Walk, mission, visibility, Cell, target and tick owners
remain unchanged. The exact value 26 follows the supplied direct route and
native tick policy; it is not an original frame-schedule claim.

The full rebuild, all 113 normal CTests, all 112 SDL-disabled sanitizer CTests
and 1,342 Python tests pass. A fresh 106-tick host-display SDL regression passes
selection, movement, drawing, pause, refusal, Stop, repeated order and
deselection at
`private/boot-camp-20261018/walk-update-position-schedule-sdl-a1/`. Its report
retains `objectives_enabled: false` and proves unchanged live runtime only.

## Limits and next gate

Runtime `step()`, ordinary SDL walking and Objective 1 still retain the no-op
arrival notification. The next evidence gate is a joined original
`Walk 71DFF0 -> 71F196 -> 500AA0` root over the selected-head owner state,
including post-callback late-byte behavior. Remaining entered nonzero cloak and
resident-bearing dirty branches stay outside the actual Day 1 zero-mask/
no-overlay path. Only after the joined caller proof and affected replay closure
should the live arrival service commit sight and mission mutations.

## Reproduce

```sh
env PYTHONPATH=tools build/tools-env/bin/python -B \
  tools/verify_walk_update_position_schedule.py \
  --exe private/official-1006-probe/game.exe \
  --output private/walk-update-position-schedule-next.json

DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
build/native/boot-camp-walk-check private/official-1006-probe
```

Use a new private output path; the verifier refuses to overwrite a receipt.
