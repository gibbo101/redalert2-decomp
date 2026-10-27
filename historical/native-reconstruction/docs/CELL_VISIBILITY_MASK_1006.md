# Cell visibility mask

Base `0x6A8D40` now has a readable SDL-free implementation of the complete
primary/secondary Cell visibility-mask calculation used twice by ordinary Cell
visibility change. It performs the exact center gates, neighbor order, wrapped
point composition, map/fallback queries and signed result selection. The result
table remains explicit startup data, and the new kernel is not yet bound into
the running application.

## Exact boundary

The supplied executable is 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and pristine
authenticity remain distinct. Original instructions execute only in the private
research fixture; the application never reads or executes the executable.

`tools/verify_cell_visibility_mask.py` pins two complete ranges / 289
instructions:

| Base range | Recovered role |
| --- | --- |
| `6A8D40..6A911D` | complete primary/secondary visibility mask |
| `548070..5480A8` | actual word-Cell lookup/fallback store |

The verifier pins both branch gates, the two returns and signed byte selection
from `7AC3BC`. It records SHA256
`2a5a40e39bae9655c359008c5894a2c1082e012ff04cdd78ebc168644546f8f1`
for the executable's 256-byte result table. The table contents remain private;
native code accepts a caller-owned signed span and fresh tests use generated
tables. No extracted table was checked into Git.

## Recovered behavior

The routine first looks up the center Cell. Secondary mode reads low flags
`+140`, uses bits 0/1 for the initial state and admits full calculation on bit 1.
Primary mode reads low flags `+12C`, uses bits 3/4 for the initial state and
admits full calculation on bit 3.

When neither initial bit is set, failure is `-2`; otherwise the provisional
failure is `-1`. A center without the admission bit returns that value after one
lookup. An admitted center queries exactly eight wrapped signed-word points in
this order and assigns a bit when that neighbor lacks the same admission bit:

| Neighbor | Mask bit |
| --- | ---: |
| northwest `(-1,-1)` | `0x40` |
| north `(0,-1)` | `0x80` |
| northeast `(1,-1)` | `0x01` |
| west `(-1,0)` | `0x20` |
| east `(1,0)` | `0x02` |
| southwest `(-1,1)` | `0x10` |
| south `(0,1)` | `0x08` |
| southeast `(1,1)` | `0x04` |

The composed byte directly indexes the supplied 256-entry table and the selected
signed byte becomes the 32-bit return. Every missing lookup immediately updates
the one shared fallback point. Repeated/aliased Cells are reread in sequence;
there is no neighbor cache or bounds shortcut above actual map lookup.

## Evidence and limits

Accepted fresh evidence is
`private/boot-camp-20261018/cell-visibility-mask-fresh-a1/`. Its 128 complete
roots execute 904 actual map lookups and 98 fallback stores. Thirty-one roots
return after the center gate; 97 query all eight neighbors and span 88 distinct
mask indices including zero and 255. Coverage includes both modes, `-1/-2`,
present/missing/aliased Cells, shared fallback state, upper flag bits and wrapped
signed-word boundary points.

Expectation SHA256 is
`6f26657a53b4d3635ab6ed2873d10298162f25d9297f4befa6b6a61a50c1804b`.
Normal, sanitizer and uncached replays each retain 128 hits and zero misses:

- `cell-visibility-mask-replay-normal-a1.json`
- `cell-visibility-mask-replay-sanitize-a1.json`
- `cell-visibility-mask-replay-uncached-a1.json`

Fresh original generation took 0.086 seconds. Final comparison bodies took
0.008, 0.385 and 0.008 seconds; complete audited invocations took 0.149, 0.570
and 0.257 seconds. The first complete host run matched; no failed result was
accepted.

This does not establish startup ownership or construction of the result table,
reveal spread/height arrays, projection scale, shared Cell ownership, binding to
`499FC0`, structure membership, sight scheduling, fog/shroud drawing or objective
UI. The production application does not call this kernel. No Windows action,
download, runtime executable read or public/generated/lifted code was introduced.
Only Apple Silicon macOS is tested.

## Reproduce and next integration

```sh
./build.command
./test.command

env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  PYTHONHASHSEED=0 PYTHONPATH=tests:tools \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/cell-visibility-mask-next.audit.json \
  tests/compare_cell_visibility_mask.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/cell-visibility-mask-vectors \
  --expectations private/boot-camp-20261018/cell-visibility-mask-fresh-a1/expected.json \
  --report private/cell-visibility-mask-next.json
```

Fresh original execution requires the authorized Mac-host JIT context and a new
private destination. Add `--uncached` before the comparison driver for the
inspection-reuse control.

Next recover verified reveal spread/height-table/projection-scale initialization
and shared visibility table ownership. Then join this kernel into ordinary Cell
visibility change and the existing resident-discovery projection on actual Boot
Camp structure Cells before enabling ordinary SDL sight scheduling.
