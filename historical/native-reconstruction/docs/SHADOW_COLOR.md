# Milestone 8: voxel shadows and player ColorScheme remapping

[SHADOW_COLOR_1006.md](SHADOW_COLOR_1006.md) adds independently mapped and executed
RA2 1.006 coverage for this retained 9,812-case domain, scoped fixture audits and
profile-specific replay. Runtime/data promotion remains pending; the historical
disc evidence below keeps its original identity.

[SHADOW_KEYS.md](SHADOW_KEYS.md) supersedes the heading-only shadow identity for
the healthy flat stock Track Rhino and verifies Foot dispatch. Shared ownership,
nonflat/status invalidation, lifecycle and full-frame parity remain open.

[VOXEL_CACHE.md](VOXEL_CACHE.md) supersedes the historical exact-matrix lit-part
cache with verified ordinary actor keys and successful wrapper/index reuse.
Runtime shadow identity, shared pool/lifecycle and full-frame parity remain open.

[UNIT_LIGHTING.md](UNIT_LIGHTING.md) supersedes the historical unit cell/house
lighting adapter with verified ordinary brightness and house-converter selection.
House initialization/lifetime and full actor/full-frame parity remain open.

[STATIC_LIGHT.md](STATIC_LIGHT.md) extends map lighting with one bounded static
source and immediate updates. Source lifecycle, unit/house association, visibility
and full-frame parity remain open; historical milestone limits below are retained.

[STAGING.md](STAGING.md) supersedes the manual indexed stencil and per-part world
blits with bounded verified part staging and one final surface copy. Successful
shadow wrapper/index decisions are verified; full actor keys, invalidation and
global compressed-pool lifetime remain outside the claim. Historical limitations
below are retained for their milestone's evidence.

October 12, 2026. Baseline: `bc6b772`, milestone 7. Tested on Ivalice,
Apple Silicon macOS 26.6.2. Windows testing is deferred at the user's request.
The supplied Allied-disc base RA2 GAME.EXE remains embedded version `1.08`,
preferred image base `0x400000`, SHA-256:

`135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743`

Every address-based oracle checks the whole executable hash before using it.
This note supersedes the ellipse-shadow and absent-player-remap limitations in
[RASTER.md](RASTER.md) and [COMPOSITION.md](COMPOSITION.md). Their indexed-buffer,
world projection and ordinary composition evidence remains current. Full actor,
ColorScheme lifecycle, cache and whole-screen parity remain unverified.

## Result and boundaries

The renderer replaces the temporary ellipse with a projected occupied-column
shadow from the original body VXL. It applies the original integer HSV conversion
and sixteen-entry player palette ramp before the existing RGB565 LightConvert
kernel. Body, turret and barrel use the same selected player palette; their
independent headings and directional drawing order are preserved.

`--player-color NAME` chooses a supplied rules.ini `[Colors]` entry, default
`DarkRed`. C cycles the entries in the native window. Names are case-insensitive;
an unknown name is rejected. Selection, default and cycling order are host policies,
not a recovered house-ID-to-ColorScheme association. The supplied rules have 19
named entries; some are not ordinary skirmish player choices.

`PlayerColor.cpp` and `VoxelShadow.cpp` belong to SDL-free `ra2_render`. GameAssets
loads the named HSV inputs; SDL handles the controls and final display. Simulation
is unchanged. No dependency or preparation file is added. Runtime GAME.EXE access
stays limited to hash-checked drive **track data**, never instruction execution.

The visible profile remains a healthy flat Rhino, one section per part, stock
identity HVA frames, neutral barrel pitch, and ordinary RGB565 composition.
The runtime assembles a temporary indexed stencil from the three lit part buffers
and generates only the body shadow. That staging/selection is an explicit adapter;
the tests below verify the shadow routines with supplied stencils, not the complete
Unit actor or its original staging/cache lifetime.

## Reference leads and inspected original evidence

Following [REFERENCES.md](REFERENCES.md), consulted redalert2-recomp commit
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439`, `docs/voxels.md`,
`src/runtime/hdvox.c` and `run_lift.py`. Its documented voxel/shadow render chain
and per-target patch sites suggested projection, scratch-buffer and final-blit
boundaries. Its HD shadow treatment is a remaster adaptation; its YR/Steam/EA
addresses are not our base-disc addresses. No code was copied or project built.

YRpp at the previously pinned `b22f1860dd7b100cad57123d4ca5d459b9020d88`
supplied naming leads in ColorScheme/Techno/TechnoType/UnitType declarations.
Their implementation and headers were not incorporated. The table below comes
from our hash-pinned binary, independently located and inspected.

| Item | Base-game VA |
| --- | --- |
| Complete integer HSV-to-RGB conversion | `0x4FE400` |
| ColorScheme copy/ramp prefix, stop before LightConvert allocation | `0x65A4F0..0x65A5ED` |
| ColorScheme constructor / rules Colors loader | `0x65A850` / `0x63EDC0` |
| Shadow queue and lower-corner projection | `0x70BDC0` |
| Complete shadow column plotter | `0x70E670` |
| Scratch reset / flush and crop | `0x70BC30` / `0x70C340` |
| Light direction and shadow-offset initialization | `0x70CA10` |
| Flat/ramp matrix initialization | `0x70CAC0` |
| Full Drive shadow matrix / base pose | `0x4A00D0` / `0x53B160` |
| Shadow wrapper/cache / render call | `0x6C7600` / `0x6C7C30` |
| Shadow Z-read span / vtable | `0x487170` / `0x78939C` |
| Final blit wrapper / blitter selection | `0x49EF70` / `0x485880` |
| Body shadow dispatch through Foot | `0x6F509E..0x6F50B0`, `0x4C94F0` |
| ShadowIndex INI field load/store | `0x6D2E66..0x6D2E7D`, type `+0x6F8` |

The inspected Unit body call supplies that type's ShadowIndex and body VXL/cache.
This is call-site evidence, not an executed type constructor/loader or proof of
all actor defaults. The native bounded profile selects its sole body section;
NoShadow, UseTurretShadow, alternate shadow indices, ramps, rocking, animated
poses and actor/cache branches are not implemented or claimed verified.
Raw probes and disassembly remain ignored under `private/presentation8/`.

## Recovered arithmetic

### HSV and player ramp

HSV channels are bytes. Sector and fraction are `6 * H / 255` and `6 * H % 255`.
The original integer divisions in the three intermediate channels are retained;
they are not floating HSV conversion. H=255 follows the red endpoint branch.

The ColorScheme prefix first copies all 768 source RGB bytes, then replaces only
palette indices **16–31**. For entry i=0..15 it uses the stored binary64 angles:

```text
saturationAngle = i * 0.046542113386515455 + 0.8726646259971648
valueAngle = i * 0.08144869842640204 + 0.3490658503988659
i == 0: valueAngle = 0.19634954084936207
S = truncate(tableSin(saturationAngle) * suppliedS)
V = truncate(tableCos(valueAngle) * suppliedV)
```

The derived S/V and supplied H feed the integer HSV routine. Original quantized
trigonometry comes from the existing hash-checked raster data. Operations use the
tested `0x0E7F` x87 context, modeled by scoped round-toward-zero, strict compilation
and restored host FP state. The ramp is compared before LightConvert allocation;
the existing palette suite separately verifies its scalar RGB565 tables.
House palette choice, affected-index masks, map-light inputs and lifecycle remain
outside this combined integration claim.

### Projected occupied columns and stencil

The four lower VXL corners are transformed by the model matrix, flattened to Z=0,
then transformed by the camera. The supplied shadow offset is added and projected
Y negated. Corner order, float32 stores, extents, midpoint and crop padding match
the original. The offset initializer produces X=`float(light.x * -6.0)`, Y=Z=0.
The flat shadow pose and heading key match the tested flat body pose.

The plotter starts at lower corner 2 and steps toward corners 1 and 3. X and Y use
**independent 16-bit accumulators**, unlike the lit rasterizer's packed coordinate
carries. A valid occupied span-start column writes two adjacent scratch pixels.
Each write is 1 for a zero staging/stencil pixel and 0 for a nonzero pixel;
later writes replace earlier writes. It does not project every voxel or fill an
analytic ellipse. Full 256×256 scratch masks and crop/corner fields are compared.

Original stencil sampling assumes valid coordinates. Differential cases stay
within supplied BSurface bounds, including shifted valid origins. The native
out-of-range guard is safety behavior outside that parity domain. Projected
extents above 240 pixels, nonfinite transforms and mismatched planes are rejected.

### Shadow composition

The ordinary call selects flags `0x2001`, the shadow Z-read blitter and flat
gradient 2. It shares the recovered relative clip origin and flat scanline
remainder convention documented in COMPOSITION.md. A nonzero source pixel halves
the destination only when the signed candidate depth is strictly less than stored
uint16 depth. Equal depth is preserved. Successful writes leave depth unchanged:

`RGB565 = (RGB565 >> 1) & 0x7BEF`

There is no continuous RGB darkening or alpha multiply. The 65,536 possible RGB565
values are compared in one complete surface case. Other shadow blitters, actor
depth/status overrides and terrain shadow branches are outside this profile.

## Oracle, results and reproduction

`tests/original_shadow_color.py` extends the original raster/composition fixture.
It runs unchanged original HSV, ColorScheme prefix, light initialization, full
flat Drive shadow pose, projection, column plotter, crop and complete shadow blit.
The original VXL loader runs with the existing bounded file/allocation services.
Shadow stencils and destination surfaces use the original BSurface methods;
pixels, depth and stencil contents are explicit inputs. The flat pose's map getter
returns a supplied zero-ramp cell. Actor/cache, house and world services are not
reconstructed by these fixtures.

The fixture executes full matrix initialization to build shadow tables, then
invalidates Unicorn's translated cache over `0x70CAC0..0x70D740`. This prevents a
cached block from crossing the older raster fixture's camera-setup stop. No
original instruction bytes are modified. The correct queue argument order is
camera followed by model, with the model transform executed first.

| Group | Matching cases |
| --- | ---: |
| Integer HSV conversions: every hue, saturation/value boundaries and seeded inputs | 6,912 |
| Full copied/remapped palettes: all hues and all 19 named supplied colors | 2,323 |
| Light-derived shadow offsets, compared float32 bits | 64 |
| Flat shadow pose/key, heading boundaries | 128 |
| Complete masks: all 32 headings of three owned parts, three stencil profiles | 288 |
| Complete clipped RGB565/depth shadow surfaces | 97 |
| **Total** | **9,812** |

All pass. Mask cases include independent turret headings and fractional model/
camera translations. Blits include transparent/nonzero source values, depth ties,
signed Z adjustments, source clipping and nonzero clip origins. Destination depth
is checked unchanged. Body-only runtime selection does not claim turret shadows.

```sh
./build.command
./run.command --player-color DarkBlue
./test.command --data-dir "$PWD/private/game"
build/tools-env/bin/python tests/compare_shadow_color.py \
  --exe private/disc-allied/game.exe
build/native/presentation-check private/game build/shadow-color
```

Reports are `private/shadow-color-report.json` and
`private/shadow-color-sanitize-report.json`. They pin the executable, native runner,
raster data and owned input hashes. Original expectations and buffers remain under
`private/shadow-color/`; research exports refuse source-installation destinations,
symlinks and differing existing data. No proprietary files or extracted tables
are tracked. Cached instrumented replay checks the recorded input identities:

```sh
build/tools-env/bin/python tests/compare_shadow_color.py \
  --exe private/disc-allied/game.exe \
  --native build/sanitize/shadow-color-vectors \
  --expectations private/shadow-color/expected.json \
  --report private/shadow-color-sanitize-report.json
```

All previous original/native suites were rerun and pass: 125,073 movement/timing
comparisons, 8,568 presentation cases / 312,208 values, 128 poses, 192 matrix products,
192 lighting setups, 192 complete indexed buffers and 424 composition cases.
ASan/UBSan native/owned-data checks and presentation/raster/composition oracles
pass; the 9,812 new expectations pass in the instrumented runner. Native checks
total 105, plus two disc-reader and six preparation/export-safety tests.
The 170-frame SDL event regression includes color cycling and movement; the
real-clock speed-3 smoke passed with 21 updates in 1,002 ms on this Mac.

Owned-data diagnostics show visible shadows, distinct DarkRed/Gold/DarkBlue frames,
invalid-color preservation and unchanged simulation. The prior cliff fixture
still shows 678/1,033 logical tank pixels visible. Inspected private previews are
native integration QA only; no original-game or full-frame observation was made.

## Remaining evidence and next work

The next bounded presentation recovery should trace actor staging, shadow/type
selection and cache validity, then verify their dispatch/state decisions with
isolated actor fixtures while preserving these buffer oracles. Map LightSources,
house palette association, visibility, animated poses, ramps/status depth, scenery,
zoom/input/UI and full match ordering still need their own recovery.

When Windows is available, pin its executable/hash and capture lossless RGB565
frames of one healthy Rhino on flat grass and near a cliff, with map/cell/elevation,
resolution, player color and body/turret headings recorded. Use all 32 body bins and
independent turret headings, repeat after stop/turn and camera movement, and inspect
shadow extent/offset, body suppression, terrain masking and remap pixels. These
measurements constrain staging, light, actor and cache integration; they do not
replace the isolated routine evidence. Record RDP versus console session too.
No Windows or Linux support is claimed. General pathfinding, combat, AI, campaigns,
multiplayer, audio, original saves and Yuri's Revenge remain deferred.
