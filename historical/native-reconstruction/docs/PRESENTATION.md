# Milestone 5: lighting, palettes and terrain depth

[PRESENTATION_1006.md](PRESENTATION_1006.md) records separately hash-selected
supplied RA2 1.006 primitive mappings and fresh comparisons on both engines.
This note retains its disc addresses/historical evidence; prepared/runtime inputs
remain disc-only, and full raster/actor profiles are not migrated by those kernels.

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


[COMPOSITION.md](COMPOSITION.md) replaces the temporary depth projection with a
verified ordinary TMP/unit composition path. This document retains milestone 5
evidence and its historical scope.

[RASTER.md](RASTER.md) supersedes the triangle coverage, flat-pose camera and
lighting-input limitations below. World composition and full-screen parity remain
unverified. This document retains milestone 5 evidence and its original scope.

October 10, 2026. Baseline: `b2a5617`. Tested on Ivalice, Apple Silicon macOS.
The supplied base RA2 GAME.EXE has embedded version `1.08`, image base `0x400000`,
and SHA-256:

`135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743`

Every address-based operation checks this hash. This note supersedes the fixed
cube-face lighting and tank-always-over-terrain descriptions in RECOVERY.md.
It does **not** claim original rasterizer, full-frame or screenshot parity.

## Implemented result and architecture

`ra2_assets` reads original `voxels.vpl` and validates separately prepared normal
and square-root tables. `ra2_render` owns recovered shade, palette and depth
primitives in Lighting.cpp, plus their integration into the existing CPU triangle
renderer. Simulation and movement are unchanged and remain SDL-free.

Each VXL section now selects its own original normal encoding. The body/turret
use encoding 2; the barrel uses encoding 4. Its normal index drives the recovered
lighting kernel, then the original VPL shade/color lookup. The mapped palette
index goes through recovered RGB565 palette conversion. Fixed brightness by cube
face is gone. Body and turret headings independently rotate the lighting inputs.

Terrain and tank pixels now share a depth buffer. The original transparent depth
comparison/store primitive decides visibility. TMP depth planes supply terrain
shape within the temporary shared coordinate mapping. Higher foreground terrain
can cover the tank; this is tested with a static cliff pose on the original map.

## Original-routine evidence

YRpp Drawing/Convert/ColorScheme declarations supplied vocabulary only; no headers
or implementation were incorporated. Base RTTI, references and call sites located
these functions independently. OpenRA remains a format reference, never a
behavior oracle. All disassembly and extracted data remain under ignored private/.

| Item | Verified base VA |
| --- | --- |
| Single-light normal shade routine | `0x710480` |
| Double-light normal shade routine | `0x710500` |
| Initialize 256 shade slots to 16 | `0x710740` |
| Normal table pointers / counts | `0x7E37D0` / `0x7E37E4` |
| Quantized square-root helper / table | `0x4B9F30` / `0x80011C` |
| Single/double lighting setup wrappers | `0x70BAB0` / `0x70BB30` |
| Unit double-light setup call, intensity 3 | `0x6C7961` |
| Default light-direction initialization | `0x70CA10` |
| VPL load wrapper / structured file reader | `0x70B9A0` / `0x710840` |
| Scalar voxel shade/color lookup block | `0x70F4C9..0x70F4FC` |
| Full LightConvert color-table update | `0x536B30` |
| Scalar RGB565 channel loop | `0x536E1D..0x536F3A` |
| Transparent palette/depth span | `0x487750` |
| Depth-buffer global | `0x821F8C` |

### Normal shading and consequential arithmetic

The five normal-table counts read from this binary are 0, 16, 36, 64 and **245**.
The exact stored arrays are extracted from the owned binary; no public normal
arrays or generated replacements are compiled into the game. Unused shade slots
are initialized to 16, and both routines explicitly set slots 253–255 to 16.
Asset validation rejects normal indices outside their encoding except those
three special slots. Tests exercise encodings 1–4; the chosen Rhino uses 2 and 4.

The single-light routine uses its original dot-product operation order, clamps
negative results to zero, multiplies by the stored float32 scale 16, truncates,
and writes the low byte. The double-light routine constructs a normalized half
vector from the light and view inputs. For each normal it combines a nonnegative
diffuse term with a nonnegative float32 specular term:

`h / ((intensity - h * intensity) + h)`

It then scales and truncates the sum. Operation order and intermediate float32
stores are preserved; this expression is not replaced by a power function.

Normalization calls a **table-quantized square root**. The helper stores its input
as float32, splits the exponent, uses exponent parity plus mantissa bits to select
one of 16,384 stored mantissas, and reconstructs the float result. Using std::sqrt
failed an original/native shade comparison by one level. The implementation now
uses the owned table, including that regression case.

The verified numeric context is x87 control word `0x0E7F`, the round-toward-zero,
53-bit mode established by the original conversion helper. Native functions scope
and restore the FP mode and compile with rounding-aware operations and contraction
disabled. Tests do not claim arbitrary incoming x87 state, exceptional floating
inputs or arbitrary modded normal arrays. The bounded input domain uses finite
light/view components of magnitude at most 2 and intensity 1–8; the runtime uses 3.

### VPL and RGB565 palettes

The VPL reader checks the 16-byte header, 768-byte **eight-bit** RGB palette and
complete 256-byte shade sections. Unlike .pal files, its embedded RGB channels are
not shifted left by two. The supplied file has remap range 16–31 and 32 sections.
Original file-reader inspection establishes the layout. The executed scalar
rasterizer block verifies `sections[shade][color]` for every supplied pair.

The full original LightConvert update is tested in its scalar RGB565 branch with
supplied palettes, affected-index masks and tint values. Its channel inputs clamp
to 0–2000; coefficient conversion retains the binary64 constant at `0x7905D0` and
truncates. Shade rows interpolate fixed integer channel multipliers; unaffected
indices have a separate early-row brightness ramp. Index zero remains zero.
Channels saturate, then quantize to 5/6/5 bits. These integer operations replace
continuous RGB multiplication in the native renderer.

The runtime uses 53 rows and affects all palette entries. Selecting a row from
map ambient/elevation and translating map tints to those inputs remain adapters.
Original per-cell LightSources, player ColorScheme remapping, palette animation,
tint-state lifetime (including the -1 restore sentinel) and hardware-optimized
conversion branches are not recovered. The native builder handles explicit tints;
the differential fixture starts with a fresh supplied converter object.
The original VPL maps voxel indices; final unit colors still use the supplied
unittem.pal without a reconstructed house/player remap. RGB565-to-SDL RGB expansion
uses ordinary bit replication as a display adapter.

### Depth comparison and the remaining projection boundary

The original transparent span writes only when the source index is nonzero and
its signed candidate depth is **strictly less** than the unsigned stored 16-bit
depth. Equal depth preserves the previous writer. Successful writes replace both
color and depth, storing the candidate's low 16 bits. The routine also wraps the
depth pointer at the end of its circular buffer. Tests include transparency,
equality, negative candidates, 16-bit boundaries and repeated buffer wrapping.

The runtime uses the same per-pixel comparison/store for terrain and tank pixels.
The world-to-depth mapping is **not recovered**. It translates TMP values through
the existing camera's depth axis, uses four depth units per unzoomed pixel, and
chooses a camera-relative 16-bit origin. Geometry and raw TMP placement, triangle
coverage, camera angle/scale, light/view transforms, HVA interpretation beyond
this identity-frame Rhino, and the approximate ellipse shadow remain adapters.
The shadow is now constrained by terrain depth, but original shadow rendering is
still absent. The diagnostic option that disables terrain occlusion exists only
in the renderer/test API, not the normal game controls.

## Verification and reproducible commands

`tests/original_presentation.py` maps the hash-pinned original PE in isolated
Unicorn memory, supplies data/objects, and runs unchanged instructions. **No API
or environment services are stubbed.** The palette fixture selects its scalar
branch and supplies RGB565 format fields; it does not execute a surface constructor.
The VPL check executes the listed lookup block rather than the entire rasterizer.

| Group | Cases | Compared values |
| --- | ---: | ---: |
| Single/double normal shades | 192 | 49,152 |
| RGB565 palette tables | 24 | 245,760 |
| All supplied VPL lookups | 8,192 | 8,192 |
| Transparent depth spans | 160 | 9,104 |
| **Total** | **8,568** | **312,208** |

All pass. Cases include zero/opposite lighting vectors, multiple encodings and
intensities, seeded unit vectors, tint clamps, affected/unaffected palette indices,
and depth-buffer boundary conditions. These are primitive outputs, not complete
rendered frames. Existing 125,073 movement/facing/timing comparisons remain required.

Prepare the additional owned data once (already done on Ivalice):

```sh
python3 tools/prepare_render_data.py --exe private/disc-allied/game.exe
./build.command
build/tools-env/bin/python tests/compare_presentation.py --exe private/disc-allied/game.exe
./test.command --data-dir "$PWD/private/game"
build/native/presentation-check private/game build/presentation
```

The oracle exports voxels.vpl read-only from --data-dir (default private/game) to
private/presentation/voxels.vpl. Its native helper refuses output inside the source
installation and refuses replacement of different existing data. --vpl accepts an
already extracted private file. Reports/diagnostic vectors are ignored under
private/presentation/ and private/presentation-report.json, with source/native,
VPL and derived-data hashes. The research harness never enters runtime targets.

The prepared file private/derived/render-data.bin is 69,944 bytes, SHA-256:

`50d2876e6bf8a3b9d535a1843ef93f41109b7021a15e1dbacb47aaa881389c6d`

Its native reader verifies the complete hash. The preparation tool rejects unknown
executables, outputs inside the source installation and overwrites of different
data. It reads data only and executes no original instructions. --render-data can
select another private copy. The game still reads **only track data directly from
GAME.EXE**; all new normal/math tables are prepared separately. No game content or
extracted tables may enter Git or a distribution.

Native tests cover malformed VPL/derived data, normal bounds, transparent/equal
and wrapped depth behavior, palette row variation, FP-state restoration and source
installation protection. Owned-data checks render eight body and eight turret
headings and a partially obscured cliff pose at cell (51,76), elevation 4. That
static diagnostic pose is not a navigable gameplay route. The actual SDL controls,
curved movement and timing checks still pass. ASan/UBSan tests cover native and
owned-data integration and presentation oracle output. Images are visual QA only.

## Observations needed for broader fidelity

For an original-game comparison, record this executable hash, map, player color,
resolution, renderer/pixel format and lighting settings. Capture a stationary
Rhino on level grass at eight body headings, then eight independent turret headings.
Include a cliff-edge scene with a known unit cell/elevation. Compare palette indices
or lossless pixels, shadow bounds, body/turret pivots and the exact terrain masking
edge. This would constrain the unrecovered transforms, player palette, rasterizer
and depth projection. No such original-game capture was performed here.

The next presentation recovery should trace the complete Unit DrawVoxel matrix,
cache/rasterizer and map-depth call chain before replacing those remaining
adapters. Scenery, animated water, original UI, combat, pathfinding, audio and
Yuri's Revenge are still separate deferred work.
