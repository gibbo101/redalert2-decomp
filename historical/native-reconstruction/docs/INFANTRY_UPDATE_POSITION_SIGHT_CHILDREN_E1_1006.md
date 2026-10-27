# Infantry update-position sight-child join

The bounded ordinary-E1 `500AA0 -> 4C7220 -> 6C2B40` guest now executes
complete Mission Commence `594C50`, complete sight removal `6D5E90` and
complete sight addition `6D5C30` in the exact argument-2 suffix order. Two
Day 1 shaped roots also execute complete post-sight refresh `54A550`; the other
78 retain that one call as a named supplied boundary so the existing broad
80-root parent projection does not repeat a separately proven spread loop in
every case.

## Exact shared state

The supplied executable is 4,485,392 bytes with SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
The joined verifier reuses the existing complete-range and dispatch pins for
all four children and their entered conversion/type helpers.

Actor byte `+32D` is now one logical field across the sight gates and the later
position-effects tail. The corpus separates disabled entries, which retain the
tail's `+32D = 1` store on permission success, from already-enabled entries,
which run meaningful sight work and do not invent a second store. Mission
Commence uses the actor's same mission, queue, status and timer fields. The two
complete post-sight cases use the same map pointer table, current/target Cells,
fallback and initialized 369-point spread table already proved by the isolated
post-sight fixture.

The original guest still supplies `54A110`, `6A8D40` and `6AADD0` leaves at
their established boundaries. Their complete recovered implementations and
shared Boot Camp composition remain separately verified. No old receipt is
relabelled as this stronger boundary.

## Evidence

The canonical private receipt is
`private/boot-camp-20261018/update-position-sight-children-e1-fresh-a5/`.
Its expectation SHA256 is
`97469dad5f194049a21234fe09e4f29c355182d4d53c6bc1d6c73489fd77ebf2`.
The 80 complete roots contain:

- 80 complete Mission Commence, sight-removal and sight-addition calls;
- 2 complete post-sight roots and 78 explicit supplied post-sight calls;
- 12 supplied reveal-area calls from eight enabled Day 1 cases;
- 490 supplied mask and redraw leaf calls from the two complete post-sight
  roots;
- the retained 240 current-Cell getters, 720 full-coordinate lookups, 80 target
  coordinate/floor chains and 48 complete position-effects/tail entries; and
- eight actual tail `+32D = 1` stores for initially disabled permission-success
  actors, beside eight already-enabled permission-success cases.

Fresh original generation took about 0.40 seconds and the full fresh comparison
took about 1.06 seconds. Normal, sanitizer and uncached-inspection replays retain
80 hits and zero misses; their elapsed times were about 0.51, 0.94 and 4.27
seconds. Earlier `a1..a4` attempts are retained as diagnostic or superseded
validator receipts and are not canonical replay inputs.

## Discarded Boot Camp preview

`BootCampWalkWorld::composeUpdatePositionPreview` now constructs a disposable
owner graph, copies the initialized selected GI/order state, rebinds its actual
Cell target into the clone, and advances recovered Walk Process until
selected-head notification kind 2 invokes the complete native four-child
schedule. For `(57,89) -> (59,89)`, it fires on Process call 26 at Cell
`(58,89)`. The clone records one reveal-area add, 383 total mask calls across
reveal and post-refresh, 282 redraws, final sight range 5 and active sight. The
result's logical Cell identities are translated back to corresponding live
owners for inspection.
Normal and sanitizer owner checks prove the live Walk, mission, visibility,
Cell, target and tick owners remain unchanged.

The full application rebuild, all 113 normal CTests, all 112 SDL-disabled
sanitizer CTests and 1,340 Python tests pass. A fresh 106-tick host-display SDL
regression passes selection, movement, drawing, pause, refusal, Stop, repeated
order and deselection at
`private/boot-camp-20261018/sight-children-sdl-a1/`. Its report retains
`objectives_enabled: false`; it verifies unchanged runtime behavior rather than
production sight scheduling.

This is discarded scheduled composition and exact original child evidence.
`step()`, live Walk arrival and SDL do not invoke the parent. Objective 1 remains
disabled. Exact caller inspection is recorded in
`WALK_UPDATE_POSITION_SCHEDULE_1006.md`; the next gate is a joined original
Walk-to-parent root and its post-callback late-byte behavior.

## Reproduce

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
build/native/boot-camp-walk-check private/official-1006-probe

env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  PYTHONHASHSEED=0 PYTHONPATH=tests:tools \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/update-position-sight-next.audit.json \
  tests/compare_infantry_update_position_effects_e1.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/infantry-update-position-effects-e1-vectors \
  --expectations private/boot-camp-20261018/update-position-sight-children-e1-fresh-a5/expected.json \
  --report private/update-position-sight-next.json
```

Use the sanitizer runner for the sanitizer replay and `--uncached` with new
private audit/report paths for the inspection-reuse control.
