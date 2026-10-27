# Techno sight update

Base `0x6D5C30` now has a readable SDL-free implementation of the ordinary
Techno sight update used above reveal-area `0x54A110`. It is the next recovered
link in the first Boot Camp objective's real discovery chain. Reveal-area and
the Cell visibility-changing parents remain outside this boundary, so the
application does not invoke this kernel yet.

## Exact boundary

The supplied executable is 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and pristine
authenticity remain distinct. Original instructions execute only in the private
research fixture; the application never reads or executes the executable.

`tools/verify_techno_sight.py` pins these complete ranges:

| Base range | Recovered role |
| --- | --- |
| `6D5C30..6D5E86` | Techno sight update and three reveal-area branches |
| `6C12C0..6C12C8` | Techno virtual type thunk |
| `705020..705027` | Unit type owner getter |
| `7133A0..7133C7` | veteran interval predicate |
| `713420..713438` | elite interval predicate |
| `77F110..77F14D` | original integer conversion |

The verifier also pins Unit vtable slots `+80`, `+84` and `+418`, the four FP
constants, FTOL control word and all three direct calls to `54A110`. The fixture
executes the sight root, both type thunks, both timer predicates and FTOL
unchanged. Only `54A110` is supplied.

## Recovered behavior

The root first requires actor byte `+32D` and rejects an owner-country byte
`+1A6`. It divides current Z by rules `+1324` with signed truncation, wraps the
quotient times ten as a signed 32-bit value, compares that value with signed
actor byte `+378`, and clears only the low byte of the first incoming argument
when the new value is greater. It then stores the new value's low byte at
`+378` even when that byte changes sign through wrapping.

Range calculation preserves the original staged double operations and FTOL:

```text
range = FTOL(type.Sight * (signed(actor[+378]) * 0.01 + 1.0))
```

Timer `1 <= value < 2` selects veteran state; `value >= 2` selects elite state.
The function repeats timer and type queries in their original order. Type bytes
`+271/+283` gate multiplication by rules VeteranSight `+5A0`; exactly zero and
unordered multipliers skip it. A nonzero multiplier produces a second FTOL.

On first use, byte `+1E4` and last sight X/range/Y/Z at `+1E8..+1F4` are written
in that exact order. A nonzero range then calls reveal-area with current
coordinates, range, the explicit House only when argument3 is nonzero and
argument4 is nonnull, otherwise the actor owner, the possibly low-byte-cleared
arguments1/2, and fixed tail `0,1,0`. Once sight is active, no last-sight field is
updated; reveal occurs only for nonzero argument3, nonzero range and a nonnull
explicit House.

## Evidence and limits

Fresh private evidence lives at
`private/boot-camp-20261018/techno-sight-fresh-a5/`. Its 96 complete calls
execute 149 type chains, 149 veteran predicates, 106 elite predicates, 115 FTOL
conversions and 50 supplied reveal-area calls. Cases cover both early gates,
signed positive/negative height division, comparison and byte wrapping, zero and
negative ranges, timer boundaries and NaN, both promotion bytes, zero/nonzero/
negative/NaN multipliers, first/active state, null/explicit Houses and all four
incoming arguments.

Expectation SHA256 is
`fbf196066bdea3a4693435c982feb89fa0ae7463f736a7e079d07658f9daa3ff`.
Normal, sanitizer and uncached replays each retain 96 hits and zero misses:

- `techno-sight-replay-normal-a2.json`
- `techno-sight-replay-sanitize-a2.json`
- `techno-sight-replay-uncached-a2.json`

Fresh original generation took 0.027 seconds. Final normal, sanitizer and
uncached replays took 0.174, 0.328 and 0.296 seconds respectively. Failed
`fresh-a1` was a verifier call-site correction; `fresh-a2` was the expected
restricted-sandbox JIT stop; `fresh-a3/a4` repaired fixture interval and supplied
child interception errors before any result was accepted.

This does not recover `54A110`, Cell visibility counters/flags, structure Cell
membership, sight scheduling, shroud/fog drawing or objective UI. It adds no
arrival or distance trigger. The Boot Camp runtime remains GI walking, Stop and
pause. No Windows action, download, runtime executable read or public/generated/
lifted code was introduced. Only Apple Silicon macOS is tested.

## Reproduce and next integration

```sh
./build.command
./test.command

env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  PYTHONHASHSEED=0 PYTHONPATH=tests:tools \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/techno-sight-next.audit.json \
  tests/compare_techno_sight.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/techno-sight-vectors \
  --expectations private/boot-camp-20261018/techno-sight-fresh-a5/expected.json \
  --report private/techno-sight-next.json
```

Fresh original execution needs the authorized Mac-host JIT context and a new
private destination. Add `--uncached` before the comparison driver for the
inspection-reuse control.

The later [Boot Camp sight composition](BOOT_CAMP_SIGHT_WORLD_1006.md) joins
this kernel through reveal-area and shared Cells. Runtime scheduling remains off
pending the sibling arrival effects and Cell-crossing caller audit.
