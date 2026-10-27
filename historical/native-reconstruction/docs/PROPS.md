# Milestone 17: ordinary static props and raw SHP drawing

The separately hash-selected supplied 1.006 migration is recorded in
[SCENERY_1006.md](SCENERY_1006.md). This note preserves the original disc evidence.

October 14, 2026. Baseline `8310640`. Ivalice / Apple Silicon macOS.
Base Allied-disc GAME.EXE, embedded 1.08, image base `0x400000`, SHA-256:
`135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743`.
Every original oracle verifies the complete hash before addresses. Runtime original
executable reads remain track data only; no original instructions execute in the game.

## Result and references

The prototype renders **565 ordinary scenery placements across 30 map types** in
mp03t4.map: 531 trees plus **34 props across eight types** (HDSTN01, LT_SGN01,
LT_SGN04, POLE02 and TRFF01..04). The eight TIBTRE01/02 placements remain omitted
because they require alternate/animated terrain recovery. All object locations
retain conservative route exclusions; original occupation is unrecovered.

The owned installation supplies **23 ordinary static prop images**: HDSTN01,
LT_GEN01..04, LT_SGN01..04, LT_EUR01..02, POLE01..02, SIGN01..06 and TRFF01..04.
All have healthy two-frame images. SIGN03..06 use **raw format-1 bodies and
compressed format-3 shadows**; the others use format 3 for both frames. Owned
rules/art specify Theater=yes, Foundation=1x1 and no IsAnimated, SpawnsTiberium,
IsVeinhole or WaterBound. Stock traffic lights are static here; frame count does
not authorize invented animation. BOXES, temperate ICE, VEINTREE and SPKR01 images
were absent in the inspected inventory and are not enabled. No replacements downloaded.

Consulted [REFERENCES.md](REFERENCES.md)'s terrain/SHP entry and pinned sources:

- OpenRA `e7e9e4ad270221d7fb9725b348c75504d48c1ebd`,
  `OpenRA.Mods.Common/SpriteLoaders/ShpTSLoader.cs`, ShpTSFrame raw/header branch,
  and COPYING. GPL-3.0-or-later, Copyright The OpenRA Developers and Contributors.
  The existing attributed format adaptation now includes format 1; exact crop
  dimensions are retained without upstream export padding. Formats 0/2 remain
  refused. See [THIRD_PARTY.md](../THIRD_PARTY.md).
- YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88`, `TerrainClass.h` and
  `TerrainTypeClass.h`. Healthy/type/frame vocabulary supplied hypotheses only.
  No incorporation license exists in this snapshot; no header code was reused.

The question was whether ordinary props share the healthy Terrain profile and
whether raw and compressed bodies share a depth phase. Exact-base evidence verifies
the healthy caller for every supplied prop and establishes different clipping
phases. Reference rendering and generated recompilation code are not behavior sources.

## Exact-base routines and numeric rules

| Executed original boundary | Address |
| --- | --- |
| Complete healthy Terrain draw | `0x6D8B00` |
| Complete SHP wrapper | `0x49EA80` |
| Raw / compressed BSurface drawing | `0x434A00` / `0x434F80` |
| Raw blitter selection | `0x485880` |
| Raw alpha/color/depth-write span | `0x489000` |
| Raw half-shadow/depth-write span | `0x4878C0` |
| Ordinary LightConvert constructor | `0x5368F0` |

Raw body flags `0x4E00` select converter field **+0xBC**, vtable `0x78918C`
(methods `0x48CEF0`, `0x489000`, `0x4890F0`). Raw shadow flags `0x4E01` select
**+0x54**, vtable `0x7892FC` (methods `0x48CA50`, `0x4878C0`, `0x487930`). The
oracle asserts these actual constructor identities, then executes original selection/spans.

`assets/Shp.cpp` reads format 1 as contiguous width-times-height indexed pixels.
`ShpFrame::format` reaches `render/Scenery.cpp` to preserve the original phase
decision. Compressed decoding/terminal padding remain as in [SCENERY.md](SCENERY.md).
Malformed-data guards are native engineering, not original corrupt-file evidence.

Canvas halves, crop origins, linked clipping and healthy Terrain inputs remain:

```text
body: frame 0, flags 0x4E00, ZAdjust=-heightPixels(Z)-12,
      gradient 2, brightness=signed cell terrain light +0x10C
shadow: frame frames/2, flags 0x4E01, ZAdjust=-heightPixels(Z)-3,
        gradient 0, brightness=1000
both: cell converter +0x34, ordinary terrain palette
```

For raw bodies, top/bottom are clipped absolute crop limits:

```text
remaining = bottom - top
base = uint16(32768 - remaining - top + 1) + ZAdjust
```

Compressed bodies retain original crop height under bottom clipping:

```text
remaining = cropHeight - (top - uncutTop)
base = uint16(32768 - cropHeight - uncutTop + 1) + ZAdjust
```

Both continue with `candidate=(base/3)*3-remaining/3` and
`phase=3-remaining%3`; when phase is 3, set it to zero and increment candidate.
Depth then increments every third row. Division is toward zero. Nonzero source
pixels require signed candidate depth strictly less than stored uint16 depth,
then write both RGB565 color and depth. Zero source skips both planes. Raw and
compressed shadows start at `uint16(32768-top)+ZAdjust`, decrement per row, halve
RGB565 with `0x7BEF`, and write depth on success. These are scenery depth writes,
unlike the unit's final depth-read-only blit. Alternate flags, damaged/burning
frames, animation, z-shapes and alternate converters remain outside this claim.

## Verification and fixtures

`PropsOracle` extends the unchanged existing scenery oracle. Complete Terrain cases
execute actual coordinate/height getters and both original shape draws. Map/image/
healthy actor records and primitive surfaces are supplied isolation services.
Frame cases execute actual SHP, BSurface clipping/traversal and selected raw/RLE
spans. Owned converter cases use actual 27/53-row LightConvert constructions in
separate original memory spaces, with successful heap and warm alpha-registry
fixtures. Primitive cases redirect palette/alpha pointers only. Original instruction
bytes and final drawing operations remain unchanged.

| Matching original/native boundary | Results |
| --- | ---: |
| All 23 props through complete Terrain and both shape draws | 184 |
| Owned frames with original 27/53-row converters | 368 |
| Synthetic raw body/shadow complete surfaces | 256 |
| **Total** | **808** |

Complete little-endian RGB565/depth plane hashes compare. Inputs cover odd canvases/
crops, four clipped edges, shifted clip origins, outside draws, different heights,
depth ties, transparent source and signed light extremes. Reports pin executable,
native, render, oracle, asset and stock map/rules/art identities. Retained **420
scenery** and **1,128 tree-type** results still pass. ASan/UBSan replay passes with
identity-checked expectations. Full actor arena/caller-stack/ordered-write audits,
file-loader/cache ownership and whole-frame parity are excluded.

Native integration renders every map type and all 23 isolated props, including
four raw signs; checks body/shadow visibility/repeat layers; and runs **81** scenery/
profile/export checks in temporary maps. **T** cycles all ordinary scenery, **P**
map props, **H** the Rhino; both 170-frame SDL regressions exercise these controls.
Previews are visual QA, not original-game evidence. Static scheduling/order,
elevation placement, visibility, healthy actor state, registry storage and controls
remain host adapters. Windows/Linux remain untested.

```sh
./build.command
./run.command
./test.command --data-dir "$PWD/private/game"
build/native/presentation-check private/game build/props
build/tools-env/bin/python tests/compare_props.py --exe private/disc-allied/game.exe
# After README's headless sanitizer build:
build/tools-env/bin/python tests/compare_props.py \
  --exe private/disc-allied/game.exe --native build/sanitize/scenery-vectors \
  --expectations private/props/expected.json --report private/props-sanitize-report.json
```

`scenery-vectors --export` preflights all tree/prop inputs, refusing source-tree
output, symlink destinations/parents and different replacements. Expectations,
owned exports and synthetic SHPs stay ignored under `private/props/`. Reports:
`private/props-report.json`, `private/props-sanitize-report.json`. Inspected
disassembly/identities/inventory remain under `private/terrain/`. QA previews:
`build/props-props.ppm`, `build/props-sign03.ppm`. No dependency or executable
data table was added. Source discs/install and outpost2-native are untouched.

## Next recovery and future measurements

Recover ordinary Terrain foundation/occupation and actor ordering before relaxing
conservative route exclusions. Keep alternate/animated Tiberium trees, damage,
burning, overlays and general SHP flags separate.

When Windows is ready, pin executable/map/image hashes, resolution/RGB565 mode,
detail and viewport origin. Record SIGN03 body/shadow frames, raw/RLE dispatch,
screen point, converter, ZAdjust, brightness and complete color/depth crops while
clipping the bottom one row at a time. Repeat with a compressed sign, then move
the Rhino behind/in front while logging draw order and occupied cells. This tests
the remaining actor/order/occupation/invalidation boundary; screenshots alone
cannot verify depth writes or lifecycle. No original-game observation occurred here.
