# Infantry update-position and position-effects composition

The bounded ordinary-E1 argument-2 path now executes complete base
`500AA0..501CA8`, enters complete base `4C7220..4C7AB1`, and then enters complete
base `6C2B40..6C2C3E` when the actor is on-map. The readable native composition
uses the existing `postUpdate(2)` seam and requires the parent and child views to
share the same coordinates, alternate target and on-map byte.

This is an explicit SDL-free composition fixture. The initialized resident
search and complete chain now have a discarded actual Boot Camp owner preview,
but remain unscheduled in `BootCampWalkWorld::step`.

The later [sight-child join](INFANTRY_UPDATE_POSITION_SIGHT_CHILDREN_E1_1006.md)
strengthens this same guest with complete `594C50`, `6D5E90` and `6D5C30` in
all 80 roots plus complete `54A550` in two Day 1 shaped roots. It also unifies
actor byte `+32D` across sight gating and the tail. The coordinate-only receipt
below remains an immutable earlier checkpoint.

## Joined behavior

The supplied executable is 4,485,392 bytes with SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
The joined verifier reuses the exact complete-range, helper and vtable pins from
the separate parent and child proofs. The new original oracle executes all three
parent/child/tail ranges unmodified in one call.

`updateInfantryPositionE1WithEffects` retains this structure:

1. require one logical actor identity for the three fields consumed on both
   sides of the seam;
2. run the recovered complete bounded `500AA0` path, including its initial direct
   full-coordinate lookup, three independent current-Cell getters with two
   full-coordinate lookups each, actual target Cell center/floor, ordered sight
   suffix and post-sight full-coordinate/locomotor queries;
3. when actor byte `+7D` is zero, retain the parent's no-dispatch return and leave
   the child's `+59A/+59C` bytes unchanged;
4. when actor byte `+7D` is set, dispatch exact argument 2 into the recovered
   child on the shared actor, preserving its `+59C`, `+59A`, scratch, mission,
   Cell, permission and resident order;
5. use the first permission result to run the active-placement predicate on
   false or bypass it on true, then enter the recovered `6C2B40(2)` tail;
6. preserve signed `/256` truncation and word wrap, then store `+32D = 1` when
   the tail permission succeeds before the two map associations and dirty call.

The join does not duplicate actor fields or silently adapt mismatched references.
Its guard refuses separate coordinate, alternate-target or on-map owners before
the parent runs.

## Evidence and limits

Eighty fresh complete `500AA0` roots retain the prior 64 signed/extreme cases and
add 16 actual-map permission-success cases around Day 1 Cells
`(57..60,89..92)`. Each target is an actual Cell identity registered in the same
table used by the current and fallback Cells. All 80 execute the complete bounded
parent, three complete `5D51E0` getters, nine actual `548000` calls and actual
`47BA50 -> 4706C0 -> 77F110`; 48 enter complete `4C7220` and `6C2B40`. Each
entered chain also executes complete
`508530 -> 6C1380`, four actual `548070` calls, complete `6C2990` through its
Cell-mask exit and complete `47BB30` through its overlay exit. The joined calls
contain 752 actual mission queries, 240 current-Cell getters, 720 full-coordinate
map calls, 80 target floor calls, 592 ordered fallback-coordinate stores, 48
selectors, 192 actual child map calls and 48 each of the cloak and dirty children.
At the coordinate checkpoint, the four sight calls remained supplied. The newer
receipt executes the first three in all 80 roots and post-sight in two roots,
with reveal/mask/redraw retained as named supplied leaves. Every entered child
preserves the selected ordered stores `+59C = 0`, `+59A = 0`, then
`A35E24 = 0`. Eight initially disabled permission-success cases store
`+32D = 1`; eight already-enabled cases preserve the same shared byte without a
duplicate store. Native output matches every complete original trace. Normal,
sanitizer and uncached replays each retain 80 hits and zero misses.

Canonical accepted original-only receipts are under
`private/boot-camp-20261018/update-position-coordinate-children-e1-fresh-a3/`.
Expectation SHA256 is
`fd506fc88c32dd1774d80d45466f2c2c62be2b23638e50c3bff82691084e49c4`.
Normal, sanitizer and uncached-inspection replays each pass 80/80; their scoped
audits took about 0.92, 1.16 and 4.06 seconds. Earlier accepted `a7` retains its
supplied parent-coordinate identity. Failed coordinate attempts `a1`/`a2` are
diagnostic only and are not canonical replay inputs.

The complete project rebuild, all 113 normal CTests, all 112 SDL-disabled
sanitizer CTests and 1,340 Python tests pass. Normal/sanitizer focused owner
checks and the fresh 106-tick SDL regression at
`private/boot-camp-20261018/parent-coordinate-children-sdl-a2/` are recorded in
the Boot Camp preview note; production remains unchanged.

The newer fixture joins sight transition/removal/addition and two complete
post-refresh roots. The parent current/full-coordinate/target-center children,
alternate selector and child map/cloak/dirty instructions now execute in this
same guest. The refreshed fixture uses recovered initialized-one resident state
with explicit empty heads; the separate Boot Camp owner proves the actual
player-GI head and `kind/Next`. The kind-11 target is now the actual table-owned
Cell consumed by `47BA50`, matching Boot Camp's mutable Cell target ownership.
Production walking and SDL Objective1 remain unchanged. The discarded
actual-owner composition and refusal isolation are recorded below; the exact
caller schedule still precedes production use.

That owner composition is now present as the discarded preview documented in
`BOOT_CAMP_UPDATE_POSITION_PREVIEW_1006.md`. It reaches both actual Day 1
permission calls, observes the local `+32D` store and completes through the
position/map/dirty boundaries. Live owner isolation passes in normal and
sanitizer builds. The sight children are now joined on a disposable owner graph;
production scheduling still requires a joined original selected-head Walk call.

## Reproduce

```sh
./build.command
./test.command

env DEVELOPER_DIR=/Library/Developer/CommandLineTools PYTHONHASHSEED=0 \
  PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/update-position-coordinate-children-e1-next.audit.json \
  tests/compare_infantry_update_position_effects_e1.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/infantry-update-position-effects-e1-vectors \
  --expectations private/boot-camp-20261018/update-position-sight-children-e1-fresh-a5/expected.json \
  --report private/update-position-coordinate-children-e1-next.json
# Use build/sanitize/infantry-update-position-effects-e1-vectors for sanitizer replay.
# Add --uncached for an inspection-cache control. Use new private path names.
```
