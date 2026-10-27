# Milestone 7: ordinary world-depth and unit composition

[COMPOSITION_1006.md](COMPOSITION_1006.md) adds independently mapped and executed
RA2 1.006 coverage for this retained 424-case domain, scoped fixture audits and
profile-specific replay. Runtime/data promotion remains pending; the historical
disc evidence below keeps its original identity.

[VOXEL_CACHE.md](VOXEL_CACHE.md) supersedes the historical exact-matrix lit-part
cache with verified ordinary actor keys and successful wrapper/index reuse.
Runtime shadow identity, shared pool/lifecycle and full-frame parity remain open.

[UNIT_LIGHTING.md](UNIT_LIGHTING.md) supersedes the historical unit cell/house
lighting adapter with verified ordinary brightness and house-converter selection.
House initialization/lifetime and full actor/full-frame parity remain open.

[STATIC_LIGHT.md](STATIC_LIGHT.md) extends map lighting with one bounded static
source and immediate updates. Source lifecycle, unit/house association, visibility
and full-frame parity remain open; historical milestone limits below are retained.

[MAP_LIGHTING.md](MAP_LIGHTING.md) supersedes the direct ambient/elevation-to-alpha
adapter with verified ordinary cell lighting and separate visibility alpha. Source
actor creation, fog and unit/house association remain outside that claim. Historical
milestone limits below are retained for their original evidence.


[STAGING.md](STAGING.md) supersedes the manual indexed stencil and per-part world
blits with bounded verified part staging and one final surface copy. Successful
shadow wrapper/index decisions are verified; full actor keys, invalidation and
global compressed-pool lifetime remain outside the claim. Historical limitations
below are retained for their milestone's evidence.

[SHADOW_COLOR.md](SHADOW_COLOR.md) supersedes the absent player-remap and original
voxel-shadow limitations below. This document retains milestone 7's evidence;
actor staging/selection, lighting sources and full cache integration remain open.

October 11, 2026. Baseline: `4f8a099`. Tested on Ivalice, arm64, macOS 26.6.2.
The supplied base RA2 GAME.EXE remains embedded version `1.08`, image base
`0x400000`, SHA-256:

`135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743`

Every address-based oracle checks the complete hash. This note supersedes the
auxiliary voxel depth and ordinary placement/composition limitations in RASTER.md.
Indexed-buffer evidence remains current. Whole-game and whole-screen parity are
still outside the verified boundary.

## Result

The renderer composes original indexed voxel buffers using the recovered ordinary
flat-drive unit blit, world projection and terrain depth convention. The auxiliary
per-voxel depth plane and quarter-pixel depth adapter have been removed.
Terrain and units now use different original depth rules: terrain writes depth
and accepts ties; ordinary units read depth, reject ties and leave the depth plane
unchanged. Barrel/turret painting order follows the original direction branch.

Original pixels are composed at unzoomed resolution into RGB565, depth and alpha
planes. The host then scales the result for its camera zoom and SDL presentation.
Simulation is unchanged and remains SDL-free. No original executable code runs
inside the application.

## Original evidence

| Item | Base-game VA |
| --- | --- |
| Tactical projection scale initialization | `0x6975D0`, `0x697660`, `0x697930` |
| World-coordinate projection | `0x697C90` |
| Height-to-pixel helper | `0x697E60` |
| Healthy flat unit depth adjustment | `0x6C52C0` |
| Drive depth contribution / gradient selector | `0x4A4400` / `0x4A4410` to `0x53B540` |
| Cell-to-TMP draw inputs | `0x475333..0x4753C9` |
| Complete ordinary TMP draw | `0x52A340` |
| TMP depth baseline / normal pixel loop | `0x52A5B3..0x52A5ED` / `0x52ADF0..0x52AE5C` |
| Unit final-blit inputs | `0x6C7BA6..0x6C7C08` |
| Final blit wrapper / surface blit | `0x49EF70` / `0x434A00` |
| Rectangle clipping helpers | `0x760730`, `0x760950` |
| Blitter selection / normal alpha Z-read span | `0x485880` / `0x488650` |
| Alpha shade-map generation | `0x41E40E..0x41E475` |
| Gradient descriptors | `0x7B90F8` |
| Depth-buffer default maximum 0x8000 | `0x4989F8` |
| Normal barrel/turret order block | `0x6F4A38..0x6F4B57` |

YRpp Tactical/Surface/BlitterFlags declarations were naming/layout leads only;
no implementation or headers were copied. These addresses and behaviors were
re-established in the pinned base binary. New disassembly and probes remain
under ignored private/composition/.

## Recovered numeric and composition rules

### World projection and height

For the tested coordinate domain, X/Y projection is integer division toward zero:

`screenX = (30 * X - 30 * Y) / 256`

`screenY = (15 * X + 15 * Y) / 256 - heightPixels(Z)`

The height coefficient is initialized using the original quantized square-root
and sine helpers, not standard-library substitutes. Its reproduced binary64 value
is `0.14350360082660085`. Height conversion retains the original operation order:

`int(Z * coefficient + int(Z >= 728) + 0.5)`

The original helper's correction at 728 leptons is consequential. Native arithmetic
scopes/restores round-toward-zero and retains strict compilation. Projection is
bounded to +/-2^20 leptons per X/Y component and +/-65,536 for height; arbitrary
integer overflow and exceptional floating-point inputs are not claimed.

The flat healthy depth helper returns `-heightPixels(Z) - 1`. Its full original
routine is exercised with empty flat neighboring cells and small tile dimensions.
Ramps, bridges, tall-neighbor depth overrides and status/veterancy adjustments are
outside that fixture. A map elevation level is 104 leptons; the cell terrain draw
uses its original integer 15-pixel level adjustment.

### Terrain depth

The ordinary TMP baseline is:

`uint16(maximum + depthOriginY - tileTopY - 30) - 15 * cellElevation`

A source depth byte is added, narrowed to uint16, then compared with stored depth.
A candidate **less than or equal** to stored depth writes both color and depth.
Palette zero in the base diamond is opaque, so coverage is stored separately from
color. The asset reader retains base and extra color/depth layers to compose them
in their original order, rather than overwrite base depth during decoding.
Transparent extra pixels remain omitted.

The complete original TMP draw is compared for every present subtile of the supplied
clear01.tem, cliff01.tem and slope01.tem, including clipped positions and multiple
cell elevations. This verifies those ordinary depth-enabled inputs; animated,
variant, shadow, tint and special TMP rendering branches remain unrecovered.

### Unit scanlines, clipping and alpha lighting

The checked stock unit call selects flags 0x2800 and the original alpha Z-read
blitter. Its flat-drive gradient selector is 2. Depth is derived per scanline from
the destination rectangle, depth baseline and supplied Z adjustment. The initial
value preserves the original uint16 narrowing and integer division; the gradient
advances one depth unit per three rows with its original remainder phase.

The destination coordinates supplied to the final wrapper are **relative to the
clip rectangle's origin**. Linked source/destination clipping retains that origin
and changes the scanline phase through the clipped destination height. The oracle
compares full output surfaces with negative locations, source edges, nonzero clip
origins and viewport boundaries; ordinary rectangle intersection alone initially
failed those cases.

A nonzero source index writes color only if its signed scanline candidate is
**strictly smaller** than stored uint16 depth. Successful writes leave depth intact.
Thus body/turret/barrel overlap is resolved by original painting order, rather
than an invented per-voxel world-depth plane.

The alpha palette row is generated by the original integer map:

`brightnessBin = min(254, max(0, brightness) * 261 / 2048)`

`row = min(shadeCount - 1, brightnessBin * alpha * (shadeCount - 1) / 32258)`

The divisor is exactly 32258. The checked profile uses alpha 0–255, brightness
0–2000 and 53 RGB565 shade rows. The original alpha map is generated by its original
instructions in research memory; no extracted alpha array is compiled into runtime.

After the body, the normal unit block draws turret then barrel for rounded turret
quadrants 1/2, and barrel then turret for quadrants 0/3. The directional boundary
and dispatch sequence are checked against the original block. Charger turrets,
barrel pitch, alternate images and other actor branches remain outside this profile.

## Oracle and results

`tests/original_composition.py` uses isolated original PE memory. For the unit blit,
it executes the full wrapper, clipping/surface routines, original BSurface
lock/stride/bounds methods and original selected alpha span. Pixel/depth/alpha
planes and palette tables are explicit inputs. The original depth plane is compared
as well as RGB565 output. No surface-method or scanline implementation is stubbed.

For TMP draws, the original complete drawing routine executes with a supplied raw
TMP file getter, palette, alpha plane and retained alpha-cache entry. The normal
part-order block uses a draw-dispatch recorder. The healthy depth helper uses the
existing flat-world map/getter fixture plus flat tile-dimension service. These are
isolation boundaries, not a reconstructed actor, map-light or cache manager.
Alpha-map creation uses a bounded allocator fixture and stops before cache
registration. Original instruction bytes are unchanged.

| Group | Matching cases |
| --- | ---: |
| World projection, including signed coordinates and height boundary | 256 |
| Barrel/turret dispatch order | 40 |
| Healthy flat unit depth helper | 8 |
| Complete clipped unit RGB565/depth surfaces | 96 |
| Complete TMP RGB565/depth surfaces, six present subtiles | 24 |
| **Total** | **424** |

All match. Full surfaces use hashes of explicitly little-endian RGB565/depth words.
The prior 125,073 movement/timing comparisons, 8,568 presentation cases (312,208
values), and 192 complete indexed raster buffers remain regression requirements.
Native tests also cover ties, opaque palette zero, unchanged unit depth, alpha
quantization, clip-origin placement, height correction and FP restoration.

```sh
./build.command
./run.command
./test.command --data-dir "$PWD/private/game"
build/tools-env/bin/python tests/compare_composition.py --exe private/disc-allied/game.exe
build/native/presentation-check private/game build/composition
```

Research assets are exported read-only to private/composition/assets/. Source-tree
writes, symlinks and replacement of different existing data are refused. The source
executable is never changed. Reports at private/composition-report.json and
private/composition-sanitize-report.json contain original/native and asset hashes;
local vectors, expected outputs and disassembly stay ignored. No new preparation
file is needed: this milestone reuses the existing hash-checked render/raster data.
Runtime executable access remains track data only. Unicorn/Python stay research-only.

## Remaining boundaries and next work

The host chooses viewport origin and zoom. Input inversion, map-light-to-alpha
integration, player colors, shadows, UI and cache lifetime remain adapters. The
normal flat profile excludes the original nearby-ramp/tall-terrain and status depth
adjustments. The static native cliff fixture proves integration, not an original
whole-screen comparison. Full match draw ordering, visibility, other unit types,
scenery and all special blit/TMP branches remain outside this milestone.

The next recommended bounded presentation milestone is original voxel shadows
and player ColorScheme remapping, preserving the new composition and indexed-buffer
oracles. For broader original-game validation, record the executable hash, map/cell,
elevation, headings, player color, pixel format and resolution. Compare lossless
frames at cliff edges and between unit parts, including stop/turn and camera motion.
That evidence would constrain the remaining actor/light/cache integration rather
than replace the isolated original-routine comparisons.
