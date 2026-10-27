# Position cloak-effect ordered early returns

Complete base `6C2990..6C2B35` is pinned and its two ordered prefix exits are
readable. This closes the position child reached by the discarded ordinary E1
update-position preview when its actual Cell has no cloak-generator House bit.
It does not recover the entered object traversal or uncloaking effects.

## Recovered behavior

The supplied executable remains 4,485,392 bytes with SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
The complete 421-byte/133-instruction range has SHA256
`0c679420f3e9152c6ef66b3958a1c4bb15ef580d4a2783c75842f34dfa358d89`.

The bounded kernel preserves this order:

1. obtain the actor coordinates through virtual `+48`;
2. truncate signed X/Y toward zero by 256 and retain the low words;
3. perform actual map lookup `548070`;
4. read actor owner `+1B4`, then its signed House index `+30`;
5. use complete helper `47C2C0` to test that index in Cell mask `+78`; and
6. return immediately when the Cell bit is clear, or call virtual `+280` and
   return when that supplied actor predicate is false.

If both gates pass, the original builds a temporary vector from the global
object list, filters objects whose `+228` target is this actor, invokes further
Cell/House tests, calls actor virtual `+3F4`, then dispatches virtual `+370` to
the retained objects. Allocation, list ownership, those predicates and effects
remain refused rather than approximated.

`MapCellAttributes::cloakedByHouses` now owns the corresponding bounded Cell
state. Prepared terrain initializes it to zero. No cloak-generator producer is
recovered, so nonzero masks remain outside production ownership.

## Evidence and Boot Camp join

Canonical private evidence is
`private/boot-camp-20261018/position-cloak-effect-fresh-a2/`. Its 64 fresh
complete calls make 64 actual coordinate/map/Cell-mask queries and 32 supplied
actor-predicate calls. All cases exit before the global list. Expectation SHA256
is `f8fe9eb9a9872ce955a9ed046a3a68178d654cfdc8fc639100c6618566e49f87`.
Normal, sanitizer and uncached replays each retain 64 hits and zero misses.

The discarded Boot Camp update-position preview binds `6C2990` to the same
actual current mutable Cell used by the following map associations and dirty
effect. At `(57,89)`, its supplied initialized cloak mask is zero, so the kernel
returns at the Cell-mask gate without calling the actor predicate. Normal and
sanitizer owner checks preserve all live Walk, mission, visibility and Cell
state.

The strengthened complete `4C7220` and joined `500AA0` receipts also execute
this complete range and its actual map/mask helpers in the same guest as the
selector and dirty child. Each has 48 entered zero-mask exits. The earlier
standalone receipt remains the broader two-exit proof.

The complete rebuild and all 112 CTests pass. A fresh 106-tick actual
host-display SDL regression passes selection, movement, drawing, pause, refusal,
Stop, repeated order and deselection at
`private/boot-camp-20261018/position-cloak-effect-sdl-a1/`. Its report retains
`objectives_enabled: false`; production scheduling remains unchanged.

This is recovered behavior plus an actual-owner native composition. It is not
an original-game observation. Exact original cloak-mask startup, cloak-generator
updates, virtual `+280`, the resident-bearing dirty branch and the Cell-crossing
schedule remain open.

## Reproduce

```sh
./build.command
./test.command

env DEVELOPER_DIR=/Library/Developer/CommandLineTools PYTHONHASHSEED=0 \
  PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/position-cloak-effect-next.audit.json \
  tests/compare_position_cloak_effect.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/position-cloak-effect-vectors \
  --expectations private/boot-camp-20261018/position-cloak-effect-fresh-a2/expected.json \
  --report private/position-cloak-effect-next.json
# Use build/sanitize/position-cloak-effect-vectors for sanitizer replay.
# Add --uncached for an inspection-cache control. Use new private path names.
```
