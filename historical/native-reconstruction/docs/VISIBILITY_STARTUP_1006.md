# Visibility startup tables and projection scale

Base startup now has a readable SDL-free owner for the Cell-spread offsets,
height-direction offsets, radius counts and the fixed projection coefficient
consumed by reveal-area `54A110`. The owner is not yet bound to production
sight. The private 256-entry result table used by visibility-mask `6A8D40`
remains a separate supplied input.

## Exact boundary

The supplied executable is 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and pristine
authenticity remain distinct. Original instructions execute only in the private
research fixture; the application never reads or executes the executable.

`tools/verify_visibility_startup.py` pins two complete constructors, their
adjacent startup registration and the already verified projection initializers:

| Base range | Bytes | Instructions | Result |
| --- | ---: | ---: | --- |
| `5441E0..546186` | 8,102 | 1,664 | 369 packed spread points |
| `5461A0..54792C` | 6,028 | 1,384 | 309 packed height points |
| `6A20E0`, `6A2170`, `6A2440` | inherited | inherited | fixed projection scale |

The constructors make 81 and 68 actual calls to the packed-point constructor
`42AD30`; their other 529 points are direct ordered stores. Startup registration
contains thunk `5441D0` before `546190`. The immutable executable radius-count
bytes have SHA256
`8ff78b31007c60e1b4f2b67c9b49ba1bfdfd6d63921ab2a57caa050d22f896cd`.

The pinned YRpp CellSpread enumerator comment was consulted as a hypothesis. Its
source was not copied. The independently implemented state machine was accepted
only after every produced point matched these complete base constructors.

## Recovered behavior

The main constructor produces cumulative radius counts
`1, 9, 21, 37, 61, 89, 121, 161, 205, 253, 309` through radius 10. Each ring
retains the constructor's exact scan order. Radius 1 writes its two upper corners
in the stock reversed order rather than normalizing them.

The separate height constructor quantizes every radius-0-through-10 point toward
the center. A component becomes zero when its magnitude is less than half the
other component; otherwise it becomes the opposite sign. Equality enters the
diagonal. The stock entry corresponding to spread point `(5,-2)` is the sole
exception and remains `(1,0)` rather than being repaired to `(-1,0)`.

The main constructor also owns 60 radius-11 entries for other stock callers.
Reveal-area clamps to radius 10, but the native owner retains radius 11's distinct
quadrant order and its duplicate `(-3,11)` entry. The complete native table has
368 distinct points, not 369.

The exact spread and height byte hashes are respectively
`fc228aefe48c2afdb75e7077a94831099277038652eb81eb0314536609d72942`
and `603a62313a2343fc1e4678d7aae33a35bc950a74f0e72863c09cb2814ef2384e`.
No extracted table bytes are compiled or tracked; native code generates the
points from the recovered rules.

Projection initialization reuses the prior exact evidence for
`6A20E0 -> 6A2170 -> 6A2440`. Those routines consume fixed constants and private
lookup tables and produce binary64 bits `0x3FC25E5374344960`, or
`0.14350360082660085`. The native owner retains that proven result by bits. It
does not substitute host `libm`, copy the lookup tables or claim a general
implementation of the original square-root/sine helpers.

## Evidence and limits

Accepted fresh evidence is
`private/boot-camp-20261018/visibility-startup-fresh-a2/`. One complete startup
sequence executes five audited original calls and compares all 11 counts, 738
spread components, 618 height components and the projection bit pattern: 1,368
values total. Expectation SHA256 is
`1cc542f84f0b8277bd5bfc848183d67fbe8a32b3c6cd4832431c8757afc6181b`.

Normal, sanitizer and uncached replays each retain one original-sequence hit and
zero misses. Fresh original generation took 0.006 seconds; native comparison
took 0.017 seconds. Normal, sanitizer and uncached replay comparison bodies took
0.004, 0.104 and 0.004 seconds; complete audited invocations took 0.210, 0.334
and 1.015 seconds.

The first `a1` attempt is retained as failed evidence. It modeled height entries
as opposite signs and differed at the radius-3 shallow component. Inspection of
all 309 pairs established the 2:1 dominant-component rule and isolated the stock
`(5,-2)` anomaly; only the corrected `a2` result was accepted.

This does not establish ownership of the private visibility-mask result table,
shared production Cells, structure membership, sight timing, fog/shroud drawing
or Objective1 progress. The runtime does not yet call reveal-area or these tables.
No Windows action, download, executable-read expansion or upstream/generated/
lifted code was introduced. Only Apple Silicon macOS is tested.

## Reproduce and next integration

```sh
./build.command
./test.command

env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  PYTHONHASHSEED=0 PYTHONPATH=tests:tools \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/visibility-startup-next.audit.json \
  tests/compare_visibility_startup.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/visibility-startup-vectors \
  --expectations private/boot-camp-20261018/visibility-startup-fresh-a2/expected.json \
  --report private/visibility-startup-next.json
```

Fresh original execution requires the authorized Mac-host JIT context and a new
private destination. Add `--uncached` before the comparison driver for the
inspection-reuse control.

Next create one shared native visibility owner for actual Boot Camp Cells and
the still-private mask result table, then compose mask `6A8D40` into ordinary
Cell change `499FC0` and discovery `568520`. Bind actual structure Cell
membership before adding ordinary SDL sight scheduling.
