# Reveal-area parent

Base `0x54A110` now has a readable SDL-free implementation of the complete
reveal-area parent called by Techno sight and mission reveal logic. It performs
the actual spread admission, Cell lookup and Cell flag `0x40` clear. The two
visibility-effect children remain explicit boundaries, so this checkpoint does
not yet change shroud, fog, discovery counters or the running Boot Camp mission.

## Exact boundary

The supplied executable is 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and pristine
authenticity remain distinct. Original instructions execute only in the private
research fixture; the application never reads or executes the executable.

`tools/verify_reveal_area.py` pins four complete ranges / 393 instructions:

| Base range | Recovered role |
| --- | --- |
| `54A110..54A550` | complete reveal-area parent |
| `6A2970..6A29AC` | height-to-screen projection conversion |
| `4BA410..4BA47E` | table square-root child |
| `77F110..77F14D` | original integer conversion |

The verifier pins the radius-count table, numeric constants, FTOL control word,
Cell fields and direct calls to House predicate `4E5540`, fog child `49A0F0` and
ordinary reveal wrapper `62FCA0`. The root and all three numeric children execute
unchanged. House predicate and the two effect children are supplied.

The offset arrays at `A6F248/A6ED18` and projection scale at `ABE490` are
runtime-initialized storage, not executable constants. The native boundary
therefore accepts those arrays and scale explicitly. Fresh tests provide
synthetic arrays to prove parent behavior without checking extracted original
tables into Git. The executable's immutable radius counts are identity-checked.

## Recovered behavior

The parent receives eight arguments in this order: coordinates, range, House,
trim mode, an unused value, fog mode, height-check mode and the final child
argument. It preserves the following order:

1. Divide Z by the global height divisor and call the height projection child
   twice. Each result shifts X and Y by its negated signed `/30` quotient.
2. Convert raw and adjusted coordinates to wrapping signed-word Cells, including
   the packed subtraction and borrow used by the later height-check point.
3. Apply all four isometric map bounds before range handling. Zero returns;
   values 11 or greater clamp to 10.
4. Select the radius count and, when rules byte `+1432` is zero, trim mode is
   enabled and radius exceeds two, skip the earlier radius's prefix.
5. Resolve the House to the current House through exact identity, alliance-mask
   and supplied predicate/rules-`+142B` gates. Other identities return.
6. For every selected offset, perform wrapping candidate composition, map bounds,
   absolute-X and signed-word circular-distance admission using actual table
   square root and FTOL.
7. Look up the candidate in the map owner's primary table or shared fallback. If
   height-check mode and rules `+1432` are both nonzero, compose the paired
   height-offset point, use the distinct global Cell table/shared fallback and
   reject levels greater than signed `Z/divisor + 3`.
8. Clear Cell `flags140` bit `0x40`. Fog mode requires bit0 set, bit1 clear and
   Cell `flags12C` bit8 before `49A0F0`. Ordinary mode calls `62FCA0`
   unconditionally with candidate, resolved House and argument8.

Fallback coordinate stores happen immediately. A secondary miss can overwrite
the same fallback point after the primary lookup while the primary Cell identity
remains borrowed. Repeated offsets can therefore observe earlier flag clears.

## Evidence and limits

Fresh private evidence lives at
`private/boot-camp-20261018/reveal-area-fresh-a4/`. Its 48 complete roots execute
96 height projections, 2,437 table-square-root/FTOL distance paths, 4,241 primary
Cell observations, 622 secondary height observations, 2,206 fallback stores,
2,341 ordered flag writes, 1,438 ordinary reveal calls, 45 fog calls and 13
supplied House predicates. Coverage includes map/range exits, clamp10, trim,
current/null/other/allied Houses, predicate/rules combinations, present/missing/
shared Cells, both child modes, optional height admission, level rejection and
repeated mutations.

Expectation SHA256 is
`accd92b12358e348337f750a92d1c469b7812715464cfeee3f632b46e8c751a5`.
Normal, sanitizer and uncached replays each retain 48 hits and zero misses:

- `reveal-area-replay-normal-a1.json`
- `reveal-area-replay-sanitize-a1.json`
- `reveal-area-replay-uncached-a1.json`

Fresh original generation took 1.335 seconds. Final normal, sanitizer and
uncached replays took 0.257, 0.400 and 0.522 seconds. Restricted `fresh-a1`
ended with SIGILL before evidence. `fresh-a2` exposed uninitialized fallback
fixture state, and `fresh-a3` corrected the secondary fallback trace point;
neither failed comparison was accepted. `fresh-a4` is the accepted run.

This does not recover `62FCA0 -> 499FC0`, `49A0F0`, visibility counters/flags,
Cell discovery dispatch, startup spread arrays, E1 scheduling, structure Cell
membership, shroud/fog drawing or objective UI. Techno sight is not wired to
this parent in production. No arrival/distance trigger was introduced. No
Windows action, download, runtime executable read or public/generated/lifted
code was introduced. Only Apple Silicon macOS is tested.

## Reproduce and next integration

```sh
./build.command
./test.command

env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  PYTHONHASHSEED=0 PYTHONPATH=tests:tools \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/reveal-area-next.audit.json \
  tests/compare_reveal_area.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/reveal-area-vectors \
  --expectations private/boot-camp-20261018/reveal-area-fresh-a4/expected.json \
  --report private/reveal-area-next.json
```

Fresh original execution needs the authorized Mac-host JIT context and a new
private destination. Add `--uncached` before the comparison driver for the
inspection-reuse control.

Next recover ordinary wrapper `62FCA0` and the stock-E1 branch of `499FC0` that
mutates visibility counters and invokes the existing `568520` discovery
projection. Then provide the verified runtime spread initialization, join actual
structure Cell membership and let ordinary SDL movement produce discovery.
