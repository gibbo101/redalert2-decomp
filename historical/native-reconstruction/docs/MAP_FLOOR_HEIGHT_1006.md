# Supplied RA2 1.006 Cell and map floor height

October 15, 2026, after `f7b247b`. **4,279 fresh original/native sequences /
13,382 queries** match for Cell floor height, Cell center coordinates, map floor
lookup and actor height relative to the floor. This replaces the supplied height
child in the new Cell-center suite; previous wall/map suites retain their older
service boundaries. The new helper is unwired. Prepared map-to-Foot/base-depth/
Unit-world and the terrain-aware crossing/parked cliff capability remain open;
runtime depth stays neutral.

## Identity and reference hypothesis

Both private supplied engines were freshly rehashed: 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`, at
`private/official-1006-probe/game.exe` and
`private/windows-baseline-20261014/game.exe`. Embedded version 1.08, supplied
1.006 lineage and reported no-CD changes remain separate provenance; pristine
authenticity is unverified. The approved Windows copy already exists. No new
Windows/transfer/source-install/system action, dependency or worker was introduced.
The native application never executes the original binary.

Consulted [REFERENCES.md](REFERENCES.md), pinned YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` `CellClass.h` GetFloorHeight/
GetCellCoords, `MapClass.h` GetCellFloorHeight and earlier Abstract/Unit caller
leads. Hypothesis: original ramp/level state supplies Cell-center and current
map-floor heights before actor-relative subtraction. Exact base inspection and
execution decide the arithmetic and associations; YR addresses/names are leads.
The pinned recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439` `docs/voxels.md`
remains surrounding drawing context, not a floor-height oracle. Existing license
boundaries apply: recomp's MIT excludes generated/lifted game code; its stale
The Movies text is recorded, and the YRpp snapshot has no license file. No
upstream/header/generated/lifted code or extracted table was incorporated.
Private fixtures supply the initial plane template; native initialization uses
readable geometric construction. No THIRD_PARTY.md change is needed.

## Complete executed boundary

[verify_map_floor_height.py](../tools/verify_map_floor_height.py) pins five
complete ranges / **413 instructions**, constants and the initial template hash.
All five roots enter:

| Base root | Executed scope |
| --- | --- |
| `0x4706C0..0x470E7A` | Complete Cell finite floor query and lazy ramp initialization |
| `0x55A280..0x55A2F8` | Complete map floor lookup and actual Cell child |
| `0x5D4810..0x5D485E` | Complete actor-relative height and bridge-byte subtraction |
| `0x47BA50..0x47BA98` | Complete Cell-center coordinate query and actual floor child |
| `0x77F110..0x77F14C` | Actual qword FTOL / low-dword return |

[MapFloorHeight.cpp](../src/assets/MapFloorHeight.cpp) lives in assets, with no
SDL/render dependency. Current level-height global, initial static template/
lazy state and Cell/map/actor/bridge storage are supplied inputs. Native runtime
does not read additional executable data. The incoming x87 53-bit/toward-zero
mode `0x0E7F` is a supplied caller profile; native scopes restore host rounding.
Original instructions remain unchanged. No numerical child is intercepted.

Preserve three independent lazy bits and all upper flag bits. Bit 1 caches the
current integer height as double; bit 2 caches height/256; bit 4 initializes ramp
planes. The first plane's X/Y/offset retain their supplied static-template values.
Changing the live global later **does not reset cached height/scale/planes**;
the level product still uses the new live global. The original writes portions
of doubles separately; this native projection compares final state after every
query, not initializer memory-store order or concurrent observation.

Multiply the **signed level byte** by the live height with low-32-bit wrapping,
add 0.5 in FP and truncate to qword/low dword. Thus level -1 at height 104 and
ramp zero returns **-103**, not -104. For ramps 1..20 use X/Y's low bytes;
multiply each by its plane coefficient then cached scale, add X+Y, offset, then
addend. Apply the lower zero test before the upper limit test, even when supplied
negative heights put the upper limit below zero. Add the signed base result and
truncate to qword/low dword again. Preserve negative zero in retained/initialized
state. Native nonfinite/ramp>20/qword-overflow refusals are safety boundaries,
not original malformed-input behavior.

The map wrapper divides **full signed X/Y by 256 toward zero**, forms the
low-32-bit `Y*512+X` index, then tests its sign/count and pointer. Do not first
truncate each coordinate to a word or reject X/Y independently. This preserves
combined-index aliases, including cases that cross a word boundary or wrap the
combined index. Only fallback lookup stores truncated signed-word coordinates;
the floor child still receives the original world X/Y. Native fallback observers
see the store immediately. Cell center uses its signed-word position, *256+128.
Relative height wraps actor Z-minus-floor and subtracts the bridge-height global
for **any nonzero** bridge byte, not only one.

## Evidence and limits

`private/map-depth-1006/floor-height-v1/` contains:

- 2,520 sequences for every ramp, signed level/coordinate edges and warm live-height
  changes; 256 sequences covering all 256 level bytes and product wrapping.
- 256 sequences with independent lazy/upper bits, seeded cached state, retained
  first-plane data and all final plane/cache bits compared after each query.
- 735 actual Cell-center sequences, including signed-word edges and `(51,72)`.
- 512 map/relative sequences for successful aliases, null/out-of-range fallback,
  low-byte ramp samples, noncanonical bridge bytes and wrapped subtraction.

Counts: **13,382 audited calls / actual Cell entries**, 2,048 actual map entries,
1,024 relative-height entries, 1,470 Cell-center entries, 24,653 FTOL entries,
12,453 lazy flag stores, 1,154 fallback position stores and 955,191 audited guest
writes. Compare all return values/coordinates and full cached state/template/
fallback-position hashes after every query. Caller return/ESP/register/code/write
guards, immutable Cell/input/actor/table/global records and nonselected fallback
bytes pass. Complete memory-read order, split initializer-store order and original
heap/concurrent access are not compared. Native guards additionally check FP
restoration, negative-level bias, warm cache retention, combined-index aliasing,
immediate fallback visibility and unsupported ramp refusal.

The full original level-height initializer is outside the accepted profile. An
exploratory private call sequence `0x470490/0x470520/0x470540/0x470560` yielded
104 with caller/write guards; its CRT power/internal code is not fully inspected
or compared with native code. This is a diagnostic lead, not full startup proof.
Initial Cell/type/actor/occupant/tag/bridge associations, original startup/
ownership/lifetime, ramp locomotion/base-depth branches, runtime wiring and
whole-frame fidelity remain open. Tested synthetic signed extremes do not imply
that stock map loading produces those states. No YR behavior is promoted to base.

## Reproduce

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

# Fresh original execution needs the authorized Mac host JIT context.
# Choose an unused ignored destination.
build/tools-env/bin/python tests/compare_map_floor_height.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/floor-height-new
build/tools-env/bin/python tests/compare_map_floor_height.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/floor-height-v1/expected.json \
  --report private/map-depth-1006/floor-height-v1/replay-new.json
# Add --native build/sanitize/map-floor-height-vectors for sanitizer replay.

./run.command --crossing-light-demo
```

Existing demo: select Rhino; G/right-click moves, L toggles light, R resets.
This scenario does not invoke the new helper. Only Apple Silicon macOS is tested;
local verification is not independent acceptance. Closing regression inventory,
SDL result and timings are in [HANDOFF.md](HANDOFF.md).

Next bind the actual height child into the shared map/wall path and associate
prepared map records with Foot/base-depth/Unit-world. Preserve the separate
initialization/service boundaries. Complete actual SDL level crossing and parked
cliff `(51,72)`, elevation 4 before promoting runtime depth. Full base RA2 then
Yuri's Revenge remain active and incomplete.
