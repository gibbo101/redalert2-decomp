# Techno sight removal

Base `6D5E90` now has a readable SDL-free implementation of complete old-sight
removal. It preserves actor/owner gates, the ordered active-byte clear, explicit
House behavior and all eight arguments forwarded to reveal-area `54A110`.
Reveal-area and its final-argument-1 visibility child are recovered separately;
their shared-world composition remains outside this boundary.

## Exact boundary

The supplied executable is 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and pristine
authenticity remain distinct. Original instructions execute only in the private
research fixture; the application never reads or executes the executable.

`tools/verify_techno_sight_removal.py` pins the complete 165-byte /
57-instruction range `6D5E90..6D5F34`, the direct `54A110` call and Infantry
vtable slot `+41C`. The fixture executes every root instruction unchanged while
supplying only the reveal-area child.

## Recovered behavior

The root returns without mutation unless actor byte `+32D` is nonzero and the
owner country byte `+1A6` is zero. When sight byte `+1E4` is active, it reads
last range `+1F4`, clears `+1E4` before any child call, and returns when the saved
range is zero. Otherwise it calls reveal-area using last coordinates `+1E8`, the
saved range and actor owner. A nonzero low byte of incoming argument3 plus a
nonnull argument4 substitutes the explicit House.

When sight is already inactive, no state is written. It calls reveal-area only
when argument3's low byte is nonzero, last range is nonzero and the explicit
House is nonnull. In both calling branches the exact reveal-area arguments are:

```text
(lastCoordinates, lastRange, resolvedHouse,
 forwarded1, forwarded2, 0, 1, 1)
```

The final `1` selects the other branch below ordinary Cell visibility wrapper
`62FCA0 -> 499FC0`. The existing readable Cell kernel accepts only final argument
zero, so repeated sight cannot yet be composed without recovering that increment/
removal branch.

## Evidence and limits

Fresh private evidence is under
`private/boot-camp-20261018/techno-sight-removal-fresh-a2/`. Its 96 complete
roots include 50 supplied reveal-area calls and cover both early gates, active/
inactive state, zero/negative/positive/extreme ranges, null/explicit Houses,
low-byte argument3 cases and arbitrary forwarded arguments. Expectation SHA256
is `b43b7fa63ef95bb8ae219cdba3341a51ed2679ddec5ce5747a93eb66deda416e`.

Normal, sanitizer and uncached replays each retained 96 hits and zero misses.
Fresh generation took 0.010 seconds; final elapsed replay times were 0.148,
0.278 and 0.260 seconds. `fresh-a1` preserved a fixture-only missing register
import before any expectation was accepted; `fresh-a2` is the accepted run.

This does not compose the final-argument-1 branch of `499FC0`, initial sight
state, shroud/fog drawing, redraw presentation, complete `500AA0`, mission
transition `594C50` or post-sight `54A550`. No production callback is wired, so
SDL walking still does not reveal terrain or advance Objective1. No Windows
action, download, runtime executable read or public/generated/lifted code was
introduced. Only Apple Silicon macOS is tested.

## Reproduce and next integration

```sh
./build.command
./test.command

env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  PYTHONHASHSEED=0 PYTHONPATH=tests:tools \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/techno-sight-removal-next.audit.json \
  tests/compare_techno_sight_removal.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/techno-sight-removal-vectors \
  --expectations private/boot-camp-20261018/techno-sight-removal-fresh-a2/expected.json \
  --report private/techno-sight-removal-next.json
```

The later [Boot Camp sight composition](BOOT_CAMP_SIGHT_WORLD_1006.md) joins
both directions through reveal-area and shared Cells. Runtime scheduling remains
off pending the sibling arrival effects and Cell-crossing caller audit.
