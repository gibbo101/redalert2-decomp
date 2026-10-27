# Infantry argument-2 position effects — bounded ordinary E1 path

The complete base `4C7220..4C7AB1` range is pinned, and its bounded ordinary-E1
argument-2 path is recovered together with the entered complete
`6C2B40..6C2C3E` tail. This closes the large child left supplied by the bounded
`500AA0` update-position proof. The initialized resident helper now has an
explicit Boot Camp owner, but this fixture does not establish complete original
Day 1 startup or production scheduling.

## Exact path

The supplied executable is 4,485,392 bytes with SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
The verifier pins both complete parent ranges, the exact Infantry vtable entries
for coordinates, type, mission, Cell point, alternate query, tail child and
active-placement predicate, and every entered direct-call association.

For the bounded fixture, `applyInfantryPositionEffectsE1` preserves this order:

1. clear actor bytes `+59C` and `+59A`;
2. obtain the type and reject nonzero footprint type, footprint transfer and
   mode 2;
3. call complete `508530 -> 6C1380` with actor `+228`, then query the live
   mission four separate times while rejecting 21, 11, 1 and 15;
4. obtain the current Cell point, lookup its Cell, reject object/edge branches,
   store zero to scratch global `A35E24`, and run the actual empty kind-6
   resident search;
5. reject bridge handling and return immediately when actor byte `+7D` is zero;
6. for an on-map actor, query the Cell point again and call actual permission
   with flag 1; a false result runs the actual inactive-placement predicate,
   while a true result bypasses it and joins the same continuation; reject
   visible-map and animation-offset branches;
7. enter complete `6C2B40(2)`: copy actual coordinates, truncate signed X/Y
   toward zero by 256 and wrap each result to a word, reject actor `+208`, call
   complete `6C2990` through its zero-mask exit, reject nonnull actor `+34`, call actual
   permission, store actor byte `+32D = 1` when permission succeeds and it was
   zero, perform two actual `548070` map associations, then
   call complete `47BB30` through its overlay exit on the second Cell identity.

The original `55A660` permission helper executes unmodified. Its internal
fallback-coordinate store remains inside the existing permission service
boundary. The original oracle independently asserts the selected ordered writes
`actor +59C = 0`, `actor +59A = 0`, then `A35E24 = 0` on every root and the
later `actor +32D = 1` store on each permission-success case.

The native function refuses every unentered footprint, mode-2, Cell object/edge,
bridge, entered active-placement, visible-map, animation-offset and special-map,
tail-effect and tail-target branch. It does not replace those effects with
defaults.

## Evidence and limits

Eighty fresh complete `4C7220` calls retain the prior 64 signed/extreme cases and
add 16 actual-map permission-success cases around Day 1 Cells
`(57..60,89..92)`. They contain 80 complete `508530 -> 6C1380` selectors,
320 actual mission calls, 80 actual empty resident searches, 96 actual permission
calls and 224 actual `548070` map calls. The 48 complete entered `6C2B40` tails
make 48 complete `6C2990` zero-mask exits, 48 complete `47BB30` overlay exits
and 16 verified `+32D = 1` stores. The 32 permission-false entered cases call the
active-placement helper; the 16 permission-success cases bypass it. Normal,
sanitizer and uncached replays each retain 80 hits and zero misses.

Canonical original-only receipts are under
`private/boot-camp-20261018/position-effects-e1-fresh-a10/`. The refreshed accepted
expectation SHA256 is
`c21f49f5f4b472ad01991dbe48f7cdaa4e2debec16075d53cdf3b8733300c60a`.
Normal, sanitizer and uncached replays each pass 80/80. Earlier accepted `a7`
remains immutable evidence for the former supplied selector/map/cloak/dirty
boundaries. Intermediate `a8`/`a9` runs predate the final identity assertions
and are not the canonical replay input.

The complete project rebuild, all 113 normal CTests, all 112 SDL-disabled
sanitizer CTests and 1,340 Python tests pass. Normal/sanitizer focused owner
checks and the fresh 106-tick SDL regression are recorded in the Boot Camp
preview note; production remains unchanged.

This milestone remains unscheduled. The selector, map, bounded position-cloak and
dirty-effect exits now execute in the same original guest over one actor/type/
House/Cell/table/fallback fixture. Nonzero cloak masks and the resident-bearing
dirty branch remain refused. The initialized resident global and actual nonempty
Boot Camp owner are proved separately.
`BootCampWalkWorld::step`, arrival and SDL are unchanged. The discarded actual-
owner composition is recorded below; joined parent sight/map ownership and the
caller schedule precede production use.

The discarded owner preview in `BOOT_CAMP_UPDATE_POSITION_PREVIEW_1006.md` now
performs that join through both actual permission decisions, observes the local
active-byte store and reaches the position/map/dirty boundaries. Scheduling
still requires those state-changing children and the Cell-crossing caller policy.

## Reproduce

```sh
./build.command
./test.command

env DEVELOPER_DIR=/Library/Developer/CommandLineTools PYTHONHASHSEED=0 \
  PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/position-effects-e1-next.audit.json \
  tests/compare_infantry_position_effects_e1.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/infantry-position-effects-e1-vectors \
  --expectations private/boot-camp-20261018/position-effects-e1-fresh-a10/expected.json \
  --report private/position-effects-e1-next.json
# Use build/sanitize/infantry-position-effects-e1-vectors for sanitizer replay.
# Add --uncached for an inspection-cache control. Use new private path names.
```
