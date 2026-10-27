# Post-sight visibility refresh

The subsequent [Cell redraw recovery](CELL_REDRAW_1006.md) replaces the supplied
6AADD0 child inside an explicit actual-owner viewport scope. Isolated parent
receipts below retain their original supplied-child scope; runtime stays off.

Complete base `54A550..54A711` now has a readable SDL-free implementation. It
recomputes primary visibility masks over the exact requested spread slice,
stores changed masks, marks Cell byte `+138`, and requests redraw. A separate
explicit Boot Camp seam composes it with the recovered mask calculator and the
same visibility Cells used by Techno sight. The production arrival schedule
still does not invoke this seam.

## Exact boundary

The supplied executable is 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and pristine
authenticity remain distinct. Original instructions execute only in the private
research fixture; the application never reads or executes the executable.

`tools/verify_post_sight_refresh.py` pins these exact ranges:

| Base range | Bytes | Instructions | Role |
| --- | ---: | ---: | --- |
| `54A550..54A713` | 452 | 136 | complete post-sight parent through `ret 10h` |
| `6A2970..6A29AB` | 60 | 13 | unchanged height projection child |
| `77F110..77F14D` | 62 | 21 | unchanged FTOL child |

The parent makes direct calls to supplied mask calculator `6A8D40` and supplied
redraw child `6AADD0` at this isolated boundary. Its immutable radius-count
table contains `1, 9, 21, 37, 61, 89, 121, 161, 205, 253, 309, 369` and has
SHA256 `ad889698c5928fd25ea17d217321b2ff9918a1cc1be1b783e4bb9aecba8d17bc`.
The generated 369-point spread input retains SHA256
`fc228aefe48c2afdb75e7077a94831099277038652eb81eb0314536609d72942`.

## Recovered behavior

The outer radius clamps as a signed value to 3 through 11. The inner radius
clamps to zero through eight. Inner zero begins at spread entry zero; a positive
inner radius skips the cumulative count through radius `inner - 1`. Outer 11
uses all 369 entries. Bounded native use explicitly refuses the negative-count
combinations whose original loop would not terminate.

Argument four returns after radius handling and before projection or iteration.
Otherwise the routine performs two ordered height projections, signed `/30`,
wrapped coordinate adjustment, signed `/256`, word Cell composition, direct
512-wide lookup and shared fallback forwarding. Each Cell receives one primary
mask call. An unchanged byte returns to the loop. A changed byte is stored at
`+120`, followed by byte `+138 = 1`, then redraw, in that order.

The Boot Camp composition reuses one `VisibilityStartup`, the private
hash-checked mask-result table, the shared Cell pointer table and fallback. For
the stock E1 `Sight=5`, the arrival expression `lastSightRange + 3` produces
outer radius 8 and 205 mask calls. Cell `(63,89)` is outside the sight counter
spread but inside this refresh boundary: its counter remains zero while its
primary mask becomes 254 and redraw byte becomes one. This establishes shared
ownership; it is native composition evidence rather than a whole-chain original
execution.

## Evidence and acceptance

Accepted fresh evidence is under
`private/boot-camp-20261018/post-sight-refresh-fresh-a2/`. Sixty-four complete
calls include clamp edges, disabled returns, inner slices, outer 11, coordinate
and signed-height cases, alternate scale bits, fallback modes, changed and
unchanged masks. They execute 54 calls each to the height and FTOL children,
4,582 supplied mask calls and 4,575 supplied redraw calls. Expectation SHA256 is
`b8fa6468019b8778cca2053ac9ec268fc856b21484a8ff4561cf580d6288beb4`.
Fresh original generation took 0.621 seconds.

Final normal, sanitizer and uncached replays each retain 64 hits and zero misses.
The normal replay took 0.218 seconds, sanitizer 0.279 seconds and uncached 0.290
seconds. Rebuilt dependent Cell-change, mask and reveal-area runners also retain
192, 128 and 48 expectations respectively in all three modes. Normal and
sanitizer shared-owner checks pass. All 106 CTests and 1,328 project-local Python
tests pass. The rebuilt 106-tick actual SDL input/drawing smoke is accepted at
`private/boot-camp-20261018/post-sight-sdl-a2/`; the restricted first attempt is
retained as an unavailable-display failure.

The earlier `post-sight-refresh-fresh-a1` receipt is retained as failed evidence.
It used the 11-entry reveal-area count array for outer radius 11. The corrected
implementation uses all 369 startup offsets, as the exact parent does. Earlier
fixture repairs corrected the root range, added the FTOL child and EIP import,
and fixed fallback-audit overlap before accepted evidence.

## Limits and next integration

The Boot Camp seam is explicit. `step()`, Walk arrival and SDL do not invoke it,
so player movement still does not update sight or advance Objective1. The
Infantry vtable `+1D4` child at `594C50`, the complete `500AA0` parent and other
Cell-crossing sight producers remain supplied or uninspected. Mask and redraw
are supplied children in the isolated original proof; the Boot Camp composition
uses the separately recovered mask and records redraw state, while presentation
of fog/shroud remains open.

Mission transition `594C50` is now identified with the prior exact Commence
kernel and composed through the explicit suffix seam. Next recover a bounded
complete `500AA0` E1 path and inspect other Cell-crossing callers before binding
`arrivalNotification(2)`. Preserve
the recovered schedule order: `594C50`, `6D5E90(0,0,0,0)`,
`6D5C30(0,0,0,0)`, then `54A550(current,0,lastSightRange+3,0)`.

## Reproduce

```sh
./build.command
./test.command

env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  PYTHONHASHSEED=0 PYTHONPATH=tests:tools \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/post-sight-refresh-next.audit.json \
  tests/compare_post_sight_refresh.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/post-sight-refresh-vectors \
  --expectations private/boot-camp-20261018/post-sight-refresh-fresh-a2/expected.json \
  --report private/post-sight-refresh-next.json

build/native/boot-camp-walk-check private/official-1006-probe
build/sanitize/boot-camp-walk-check private/official-1006-probe
./run.command --boot-camp-walk-smoke-test private/post-sight-sdl-next
```

Use new private report, audit and SDL output paths. Add `--uncached` before the
comparison driver for the inspection-reuse control.
