# Milestone 15: one static terrain tree and its SHP draws

The separately hash-selected supplied 1.006 migration is recorded in
[SCENERY_1006.md](SCENERY_1006.md). This note preserves the original disc evidence.

October 14, 2026. Baseline `23f2b37` (milestone 14). Ivalice, Apple Silicon macOS.
Base Allied-disc GAME.EXE, embedded version 1.08, image base `0x400000`, SHA-256:

`135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743`

Every original oracle checks the complete hash before using addresses. Runtime
executes no original instructions, and executable reads remain track data only.
This slice adds one healthy static TREE01 type. It does not recover general SHP
animation, scenery actors, original occupation/pathfinding or whole-frame parity.

[TREE_TYPES.md](TREE_TYPES.md) extends this historical one-tree checkpoint to
all supplied ordinary tree images and 531 map placements, preserving these kernels.
[PROPS.md](PROPS.md) adds ordinary props and the separately recovered raw format-1
depth phase; the format-3-only and omitted-prop limits below are historical.

## Result and references

`assets/Shp.cpp` reads bounded format-3 TS/RA2 SHP files. `render/Scenery.cpp`
recovers the healthy ordinary Terrain draw inputs and compressed body/shadow blits.
The prototype draws all **27 TREE01 placements** already recorded in mp03t4.map.
Press **T** to cycle their camera locations; **H** returns to the Rhino. These are
host inspection controls. The trees keep the existing conservative route exclusions.
Other trees, signs, lights and overlays remain omitted from presentation.

Consulted OpenRA `e7e9e4ad270221d7fb9725b348c75504d48c1ebd`,
`OpenRA.Mods.Common/SpriteLoaders/ShpTSLoader.cs` (frame headers/format 3) and
`OpenRA.Mods.Common/FileFormats/RLEZerosCompression.cs` (zero runs), plus COPYING.
GPL-3.0-or-later, Copyright The OpenRA Developers and Contributors. This format
interpretation is a GPL-covered adaptation, attributed in [THIRD_PARTY.md](../THIRD_PARTY.md).
OpenRA's even export padding and rendering are not original-behavior evidence.
YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88`, `TerrainClass.h`,
`TerrainTypeClass.h`, `ObjectClass.h`, `ObjectTypeClass.h`, `FileFormats/SHP.h`
and `Surface.h` supplied names/layout/call-signature leads only. No unlicensed
header or generated game code was incorporated. Exact-base code independently
established all implemented drawing operations. See [REFERENCES.md](REFERENCES.md).

## Exact-base evidence

| Evidence | Base address |
| --- | --- |
| Complete healthy ordinary Terrain draw | `0x6D8B00` |
| Terrain DrawIfVisible dispatch to vtable +0x10C, inspected | `0x6D95A0..0x6D96DD` |
| Terrain constructor cell-center inputs, inspected | `0x6D85F4..0x6D8620` |
| TerrainType constructor zero flags, inspected | `0x6DA3D0..0x6DA447` |
| TerrainType defaults/INI stores, inspected | `0x6DA7A0..0x6DA9A3` |
| Theater image reload/name construction, inspected | `0x6DA5D0..0x6DA67D` |
| Complete SHP wrapper | `0x49EA80` |
| Complete compressed BSurface drawing | `0x434F80` |
| Actual compressed blitter selection | `0x485B40` |
| Ordinary alpha/color depth-write RLE span | `0x48BC60` |
| Ordinary half-shadow depth-write RLE span | `0x48A4A0` |
| Complete LightConvert constructor / scalar palette | `0x5368F0` / `0x536B30` |
| Cell converter factory / palette provenance | `0x5276A0`, `0x527CA4..0x527D0E` |

Terrain main vtable is `0x79827C`; its +0x10C entry is `0x6D8B00`.
Type +0x281 selects the alternate SpawnsTiberium converter/vertical offset; +0x283
is IsAnimated. Constructor zero stores and corresponding INI strings/stores were
inspected. Ordinary TREE01 has neither flag. Its healthy strength is above 1
(stock rules TreeStrength=200); frame zero is selected. Damaged, burning/crumbling,
animated, veinhole and alternate-converter profiles are excluded. Native refuses
selected type overrides instead of silently applying the healthy profile.

The caller uses **cell converter +0x34** and **signed word terrain light +0x10C**.
It does not use the tank's ambient-plus-ExtraUnitLight or house player remap.
The previously inspected factory loads ISOTEM.PAL as the primary palette, with
TEMPERAT.PAL as the secondary palette. This milestone executes the full ordinary
LightConvert constructor: its all-entry affected mask, palette tables and actual
RLE blitter initialization are checked with supplied RGB565 masks and successful
heap/alpha-registry storage. Converter ownership and lifetime remain excluded.

## SHP and numeric rules

The owned `tree01.tem` is an SHP despite its theater extension: signature 0,
canvas **155×155**, two 24-byte frame records. Body crop is `(61,1,33,78)`;
shadow crop is `(79,43,74,36)`. Both frames have format flags 3.
The owned SHP SHA-256 is
`619cb6cba054eaf7c00cb6331eb70a686be25e60fd86573b352df22e22b1956e`.

Each row has a little-endian length including its two-byte prefix. A nonzero byte is a palette
index; zero followed by a count skips transparent pixels. The stock encoder can
append one transparent pixel beyond the declared crop. Original spans stop at
crop width; native retains exact cropped dimensions and permits only that bounded
terminal zero padding. It refuses truncated/overlapping headers, short rows,
excess padding, empty runs and formats other than 3. It bounds dimensions, frame
count and total decoded bytes. Those malformed-data guards are native engineering,
not a claim about the original loader's handling of corrupt files.

The wrapper subtracts the signed canvas half (155/2 = **77**), adds the cropped
frame origin, then applies the clip origin. It does not pad odd cropped dimensions.
Destination and source clipping remain linked. Zero source pixels skip both planes;
a successful nonzero pixel requires signed candidate depth **strictly less** than
stored uint16 depth and writes **both color and depth**. This differs from the
ordinary voxel unit's depth-read-only world blit.

Healthy static input sequence:

```text
body:   frame 0, flags 0x4E00, ZAdjust = -heightPixels(Z)-12,
        gradient 2, brightness = signed cell terrain light
shadow: frame frames/2, flags 0x4E01, ZAdjust = -heightPixels(Z)-3,
        gradient 0, brightness = 1000
```

The body uses the recovered alpha shade lookup, RGB565 converter and one depth
increment per three rows. **Compressed** drawing retains the original crop height
when the bottom is clipped; top clipping advances its original phase. If `atY`
is the absolute uncut crop top and `top` the visible top:

```text
remaining = cropHeight - (top - atY)
base = uint16(32768 - cropHeight - atY + 1) + ZAdjust
candidate = (base / 3) * 3 - remaining / 3
phase = 3 - remaining % 3
if phase == 3: phase = 0; candidate += 1
```

Then increment depth after each third row using that phase. Integer division is
toward zero. Do not reuse the uncompressed unit blit's clipped-height phase.
The shadow starts at `uint16(32768-top)+ZAdjust`, **decrements** depth per row,
changes color to `(RGB565 >> 1) & 0x7BEF`, and writes depth on success. Its frame
is a supplied original shadow image, not a voxel stencil or an ellipse.
No z-shape, remap, tint/status, alternate gradient or special draw branch is claimed.

Map placement uses inspected cell centers `(x*256+128,y*256+128)` and the already
verified world projection/height helper. Native map elevation times 104 supplies
height. Full original Unlimbo, foundation/occupation, visibility and bridge height
integration are not executed. The static renderer layer is sorted by x+y and
cached with terrain; camera/light changes rebuild it. Those scheduling/storage
choices are host adapters, not original actor ordering or redraw queues.

## Differential verification

`original_scenery.py` executes unchanged original instructions. Complete Terrain
calls supply map lookup, raw image virtual getter and a warm cell converter. Actual
Object word-coordinate and height getters execute. Recording cases assert all
other shape arguments, converter/surface identity, location and clip unchanged.
Combined cases let the actual Terrain caller execute both complete shape draws.
No final draw or scanline implementation is substituted in those combined cases.

SHP tests use actual BSurface methods, linked clipping, compressed traversal and
selected RLE spans. Original raw SHP bytes are supplied directly; full file/archive
loader and reference-cache lifecycle are excluded. Full color and depth planes
compare as explicit little-endian word hashes, across owned and synthetic valid
format-3 files, odd dimensions, clipped edges, nonzero clip origins, transparent
runs, light/depth variation and encoder padding.

| Matching boundary | Cases |
| --- | ---: |
| Complete healthy Terrain caller / unchanged forwarding | 80 |
| Complete compressed SHP color/depth surfaces | 240 |
| Complete Terrain caller through both body/shadow shape draws | 48 |
| Complete ordinary LightConvert palette tables | 4 |
| Owned sprite draws with actual original converters | 48 |
| **Total** | **420** |

All pass, including ASan/UBSan native replay. The four converter profiles include
neutral 53 rows, stock quantized map tint 53 rows and two dark 27-row converters.
Original successful heap/free and warm alpha registry are supplied storage; map,
actor, palette ownership, refcounts/lifecycle, complete arena/ordered-write audits
and whole-frame parity are outside the claim. Native integration checks separately
cover 27 map placements, tree/shadow visibility, repeated layers, player-color
separation, reversible local lighting, tree/tank overlap and T/H SDL controls.
Native previews are visual QA, not original-game capture evidence.

```sh
./build.command
./run.command                 # T cycles TREE01; H returns to Rhino
./test.command --data-dir "$PWD/private/game"
build/native/presentation-check private/game build/scenery
build/tools-env/bin/python tests/compare_scenery.py --exe private/disc-allied/game.exe
# After the headless sanitizer build described in README:
build/tools-env/bin/python tests/compare_scenery.py \
  --exe private/disc-allied/game.exe --native build/sanitize/scenery-vectors \
  --expectations private/terrain/expected.json --report private/scenery-sanitize-report.json
```

Exports use `scenery-vectors --export OWNED_INSTALL private/terrain/assets` and
refuse source-tree output, symlink destinations/parents and different replacements.
Expectations, synthetic files and raw disassembly remain under private/terrain/;
reports are private/scenery-report.json and private/scenery-sanitize-report.json.
Reports pin executable, native binary, render data, oracle source and supplied
input hashes; replay checks them and records the expectation hash. The provided
source installation and sibling outpost2-native are untouched. No new dependency
or prepared executable table is added. Only Apple Silicon macOS is tested.

## Next recovery and Windows measurements

Next bounded slice: extend the static terrain profile to other stock nonanimated
map tree types and verify their type/image/placement decisions against this base
binary before enabling them. Keep signs, traffic animation, damaged scenery,
general SHP flags and original actor lifecycle as separate questions. Recover
original foundation/occupation and object ordering before expanding pathfinding.

When Windows is ready, pin the executable, mp03t4.map, TREE01 at (71,114), its
cell height/light/converter, detail, resolution/pixel format and console versus RDP.
Record selected frames, draw flags, screen points, ZAdjust/gradient/brightness,
converter identity and complete color/depth crops while panning across all four
viewport edges. Then place a healthy Rhino behind and in front of the tree, log
actor draw order and repeat after light toggles. This distinguishes the verified
kernel from missing full actor scheduling, visibility and invalidation. Screenshots
alone cannot validate depth writes or converter lifetime. No Windows/original-game
observation was performed here. The full-game goal remains incomplete.
