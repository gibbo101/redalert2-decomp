# Infantry update-position — bounded ordinary E1 path

The complete base `500AA0..501CA8` range is pinned, and one complete argument-2
path is now recovered into readable C++ for the existing translated ordinary-E1
Walk fixture. This closes the parent orchestration around the previously recovered
sight suffix. It does not recover every branch in the 4,617-byte parent, its
large `4C7220` effect child, or original Boot Camp startup. The child is now
recovered and composed in the separate notes, and the initialized resident
search now has an explicit Boot Camp owner; this fixture remains unscheduled.

## Exact path

The supplied executable is 4,485,392 bytes with SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
The complete parent range has 1,441 instructions and SHA256
`d9144d32fcf31d627c658ea4bcaf19f109d55ea5a8e8854c6026363b6215fbc2`.
The verifier also pins the exact Infantry vtable and the entered mission,
resident-kind, target-kind and locomotor predicate helpers.

For the bounded fixture, `updateInfantryPositionE1` preserves this order:

1. lookup the actor's current Cell before testing argument 2;
2. query the live mission five separate times while rejecting missions 8, 9,
   8, 11 and 25;
3. read type byte `+C14`, then invoke the current-Cell getter independently
   before each kind 6, kind 2 and kind 1 resident probe, forwarding actor byte
   `+79` to the latter two probes;
4. require the nonnull target's exact kind 11, obtain its coordinates, lookup
   its Cell, then probe kinds 6, 2 and 1 with elevated-list argument 1 for the
   final two probes;
5. query the mission twice more while rejecting missions 7 and 17, then reject
   the entered actor `+370` branch;
6. preserve the queued-mission/target gate and call the recovered sight suffix;
7. lookup the current Cell again, read its `+EC` value, call the locomotor
   predicate, then call supplied `4C7220(2)` only when actor byte `+7D` is set.

The recovered helper global is initialized to one in the refreshed fixture.
Both entered Cells have explicit null primary heads, so the actual kind-6 helper
returns before kind or `Next` callbacks. The portable function still refuses
nonnull resident results and every alternate branch rather than inventing their
effects. Actual nonempty ownership is proved separately in
`BOOT_CAMP_RESIDENT_SEARCH_WORLD_1006.md`.

In this parent-only receipt, the four sight calls remain the separately recovered
Mission Commence, removal, addition and post-sight kernels supplied at their
dispatch boundaries. The newer joined sight receipt executes those children in
the complete bounded guest without relabelling this earlier projection. Map lookup, current-Cell lookup, target-coordinate and
`4C7220` effects are also supplied boundaries. The locomotor predicate and the
simple mission/resident/type helpers execute original instructions.

## Evidence and limits

Sixty-four fresh complete parent calls vary signed coordinates, signed range,
queued mission, bridge/list byte and on-map byte. They contain 448 actual mission
getter calls, 192 supplied coordinate-map calls, 192 supplied current-Cell calls,
64 target-coordinate calls, one ordered sight suffix per root and 32 supplied
`4C7220(2)` calls. Normal, sanitizer and uncached-inspection replays each retain
64 hits and zero misses. The refreshed accepted expectation SHA256 is
`f4f6f02d9752f02aed4f2da73980a02e278d4e976e7dc625d19ddd3058b87aa2`.

Canonical original-only receipts are under
`private/boot-camp-20261018/update-position-e1-current-services-fresh-a1/`.
This refresh makes the native kernel's three independent current-Cell service
calls explicit while retaining the parent oracle's supplied child identity.
Earlier failed `a1`,
`a2` and `a3` audits are retained: the first corrected a helper boundary, the
second found the exact Walk locomotor predicate, and the third found a native
runner-only trailing token after all effects matched. Superseded `a5` retains
the image-initial-zero resident fixture. No original result was edited or
relabeled. Fresh original generation took 0.029 seconds.

This milestone is intentionally unscheduled. `BootCampWalkWorld::step`, Walk
arrival and SDL still do not call the new parent. The exact fixture target is a
synthetic kind-11 object, while the Boot Camp order now owns an actual mutable
Cell target. The initialized resident owner and recovered `4C7220` child are now
composed with this parent over the actual Boot Camp GI in a discarded preview.
The strengthened joined proof separately replaces this parent receipt's supplied
coordinate/getter/target boundaries with actual code and actual Cell ownership.
The sight children are now joined separately. Exact inspection identifies
selected-head Walk arrival as the producer; production wiring still requires a
joined original Walk-to-parent root.

The discarded composition in `BOOT_CAMP_UPDATE_POSITION_PREVIEW_1006.md` now
binds those actual owners through both child permission decisions. The separately
verified permission-success continuation bypasses the first active-placement
predicate and stores actor byte `+32D = 1` in the tail before the position/map/
dirty boundaries. The later joined coordinate proof closes the parent map and
target-coordinate boundaries. The newer sight-child receipt closes that named
join. Production selected-head notification remains unscheduled pending the
joined original caller root and its late-byte continuation.

## Reproduce

```sh
./build.command
./test.command

env DEVELOPER_DIR=/Library/Developer/CommandLineTools PYTHONHASHSEED=0 \
  PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/update-position-e1-next.audit.json \
  tests/compare_infantry_update_position_e1.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/infantry-update-position-e1-vectors \
  --expectations private/boot-camp-20261018/update-position-e1-current-services-fresh-a1/expected.json \
  --report private/update-position-e1-next.json
# Use build/sanitize/infantry-update-position-e1-vectors for sanitizer replay.
# Add --uncached for an inspection-cache control. Use new private path names.
```
