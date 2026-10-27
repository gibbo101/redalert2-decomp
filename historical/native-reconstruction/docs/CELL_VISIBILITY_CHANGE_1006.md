# Complete Cell visibility change

The subsequent [late scenario flag recovery](CELL_VISIBILITY_LIVE_FLAGS_1006.md)
adds an explicit getter that rereads globalA3D290 and its first dword after
redraw/discovery and both Cell gates.578 complete original parents cover child
mutation/pointer replacement. The scalar API and existing application callers
retain their supplied snapshots; neither their default0 nor the `refreshRules`
name establishes the original scenario value/meaning. Earlier receipts below
prove their fixed-input domain. Live scheduling remains off.

The subsequent [Cell redraw recovery](CELL_REDRAW_1006.md) replaces the supplied
6AADD0 child inside an explicit actual-owner viewport scope. Isolated parent
receipts below retain their original supplied-child scope; runtime stays off.

Both counter paths through base `62FCA0 -> 499FC0` now have a readable SDL-free
implementation. The parent performs actual map lookup, Cell mutations, mask
queries and effect dispatch. The legacy ordinary-reveal facade retains its
strict final-argument-zero guard while the complete kernel exposes both paths.

## Exact boundary

The supplied executable is 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Original instructions execute only in the private research fixture; the
application never reads or executes the executable.

`tools/verify_cell_visibility_change.py` pins five complete ranges:

| Base range | Recovered role |
| --- | --- |
| `62FCA0..62FCBC` | three-argument boolean wrapper |
| `499FC0..49A0E9` | complete Cell visibility parent |
| `47C840..47C89A` | counter-decrement child |
| `47C8A0..47C8F3` | counter-increment/removal child |
| `548070..5480A8` | actual word-Cell map lookup/fallback store |

Mask calculator `6A8D40`, redraw `6AADD0`, resident projection `568520` and
local refresh `47BE00` remain explicit children. The parent selects decrement
when the final argument's low byte is zero and increment otherwise.

## Recovered behavior

The parent preserves this order:

1. Look up the signed-word point through the actual 512-wide table. A miss
   immediately writes the shared fallback point.
2. Save whether Cell flag `+140` bit1 was clear. Notification is true when that
   bit was clear or Cell flag `+12C` bit3 was clear.
3. Clear low-byte flag `+140` bit6 and set bit1, preserving other bits.
4. For low byte zero, `47C840` turns initial counter one into zero, decrements
   with 32-bit wrap, then updates flags from bits3/4, counter sign and bit5.
   For a nonzero low byte, `47C8A0` turns initial `-1` into zero, increments with
   32-bit wrap, clamps down to signed maximum `+134`, and sets low flag `+140`
   bit `0x20` only when old was nonpositive and final is positive.
5. Query primary then secondary masks. Changed bytes store to `+120/+121`;
   primary `FF` sets `+12C` bit4 and secondary `FF` sets `+140` bit0.
6. If notification or either mask byte changed, request redraw then invoke
   `568520(Cell, House, notification)`. Counter mutation may occur on false.
7. Independently request `47BE00` when bit1 is now set, it was initially clear,
   and rules has bit `0x1000`. Return the changed byte.

## Evidence and limits

Accepted fresh evidence is
`private/boot-camp-20261018/cell-visibility-both-fresh-a1/`. Its 192 complete
wrapper/parent/map calls include 135 decrements, 57 increments, 384 supplied mask
calculations, 90 redraw/discovery calls and 15 refreshes. Coverage includes
upper-byte-only final arguments, which correctly select decrement.

Expectation SHA256 is
`6a8f763214b30d3d4e25c16130302b001275deda0c934ce53191b1c129b4d2cc`.
Normal, sanitizer and uncached replays each retain 192 hits and zero misses.
Fresh generation took 0.157 seconds; replay elapsed times were 0.175, 0.388 and
0.276 seconds. Earlier zero-only evidence remains historical; this combined
receipt supersedes it for the changed source.

Redraw/refresh internals, initial visibility state, sight scheduling, shroud/fog
drawing and objective UI remain open. The running application still has no sight
producer. No Windows action, download, runtime executable read or public/
generated/lifted code was introduced. Only Apple Silicon macOS is tested.

## Reproduce and next integration

```sh
./build.command
./test.command

env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  PYTHONHASHSEED=0 PYTHONPATH=tests:tools \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/cell-visibility-change-next.audit.json \
  tests/compare_cell_visibility_change.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/cell-visibility-change-vectors \
  --expectations private/boot-camp-20261018/cell-visibility-both-fresh-a1/expected.json \
  --report private/cell-visibility-change-next.json
```

The later [Boot Camp sight composition](BOOT_CAMP_SIGHT_WORLD_1006.md) now
consumes both branches on shared Cells and verifies repeated-arrival isolation.
Runtime scheduling remains off pending the sibling arrival effects and crossing
audit.
