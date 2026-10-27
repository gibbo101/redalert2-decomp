# Milestone 10: ordinary map-light inputs

[MAP_LIGHTING_1006.md](MAP_LIGHTING_1006.md) adds independently mapped and executed
RA2 1.006 coverage for the retained 17,510-result domain, both sanitizer replays
and scoped caller/input/write audits. Runtime/data promotion remains pending;
the historical disc evidence below retains its exact identity.

[VOXEL_CACHE.md](VOXEL_CACHE.md) supersedes the historical exact-matrix lit-part
cache with verified ordinary actor keys and successful wrapper/index reuse.
Runtime shadow identity, shared pool/lifecycle and full-frame parity remain open.

[UNIT_LIGHTING.md](UNIT_LIGHTING.md) supersedes the historical unit cell/house
lighting adapter with verified ordinary brightness and house-converter selection.
House initialization/lifetime and full actor/full-frame parity remain open.

[STATIC_LIGHT.md](STATIC_LIGHT.md) extends this historical milestone with one
static source, immediate updates and terrain converter decisions. It also verifies
that the earlier unknown gate is graphics detail, not a timer.

October 12, 2026. Baseline: `45ba7e3` (milestone 9). Tested on Ivalice,
Apple Silicon macOS. The Allied-disc base GAME.EXE is embedded version `1.08`,
image base `0x400000`, SHA-256:

`135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743`

Every oracle checks the entire hash before addresses. No patch/YR equivalence is
assumed. This note supersedes the direct ambient/elevation-to-alpha adapter in
[PRESENTATION.md](PRESENTATION.md) and [COMPOSITION.md](COMPOSITION.md).
It verifies ordinary cell inputs, not original fog, source actors, house assignment
or full-frame parity. Simulation and its existing movement evidence are unchanged.

## Result and boundary

`MapLighting.cpp` quantizes supplied map settings as the original loader does,
then calculates ordinary per-cell ambient, elevation, Ground subtraction,
ordered light-source contributions and normalized tint. The renderer prepares
these values for the supplied map and passes brightness to the recovered blitters.
The old `(Ambient + elevation * Level) * 128` alpha formula is removed.

Map brightness and visibility alpha are separate inputs. The complete original
alpha-buffer constructor fills **127**. The native prototype retains that value
everywhere as an explicitly fully visible host policy. It does not reconstruct
the original shroud/visibility SHP writes or alpha-buffer scrolling/lifetime.

The chosen mp03t4.map has 80 placed structures and no emitting LightIntensity
among their supplied rules types. At milestone 10 runtime supplied an empty source
list and refused maps with placed emitting types. Milestone 11 extends that boundary
to one healthy INGALITE; see STATIC_LIGHT.md. The milestone 10 kernel and oracle accept explicit
original source records; that does not mean the prototype instantiates lights.
Map/rules type merging, dynamic lights and time-of-day transitions are absent.

Terrain uses the recovered cell brightness/tint. Applying the current cell's
brightness/tint to the selected named player converter is still an **actor/house
association adapter**. All entries are affected in the existing converter profile.
Native value-keyed palette caches are a storage/lifetime adapter. Missing INI keys
retain native defaults (1 for ambient/tints, 0 for Ground/Level); a complete original
INI parser and Scenario constructor/default sequence were not executed. The tested
original map provides all six ordinary keys explicitly.

## Reference lead and original evidence

Consulted pinned redalert2-recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439`,
`docs/voxels.md` (Following the image onto the battlefield, Units flashed),
`src/runtime/hdvox.c` header and `docs/testing.md`. The final palette/lighting blit
chain suggested an input boundary; no verified map-light formula or source
creation lead was supplied. Recovery continued independently in the exact base
binary. The MIT/generated-code boundary was rechecked; no upstream code was copied.
See [REFERENCES.md](REFERENCES.md) and [THIRD_PARTY.md](../THIRD_PARTY.md).

| Original evidence | Base VA |
| --- | --- |
| Ordinary map Lighting load/conversion fields | `0x65904E..0x6591B2` |
| Ambient/tint multiply and integer conversion block | `0x659071..0x65907C` |
| Ground/Level multiply and conversion block | `0x659160..0x65916B` |
| Complete ordinary cell-light calculation | `0x479040` |
| Complete tint normalization and ambient scaling | `0x536450` |
| Cell converter/input field installation, inspected | `0x478CF0` |
| Normal TMP brightness field/call, inspected | `0x475374..0x4753C9` |
| Complete alpha-buffer construction/visible fill | `0x410A60` |
| Original source array/count / signed graphics detail | `0xA5642C`, `0xA56438` / `0xA2874C` |
| Ordinary versus alternate lighting selectors | `0x51F040`, `0x51F050` |

Ordinary Scenario fields are Ambient `+0x22AC`, tint `+0x22B4/+0x22B8/+0x22BC`,
Ground `+0x22C0`, Level `+0x22C4`. Loader Ambient first writes `+0x22A8` and copies
to `+0x22AC/+0x22B0`. Original cell installation stores scale at `+0x104`, source
intensity at `+0x108`, unnormalized ambient at `+0x10A`, terrain brightness at
`+0x10C`, bridge brightness at `+0x10E`, tint at `+0x110/+0x112/+0x114`.
Installation/ownership/refcounts and the complete converter factory were inspection
evidence only in this milestone. STATIC_LIGHT.md extends numeric installation and
factory decision verification with listed fixtures. The full calculation outputs
are differentially verified.

Source records supply intensity/tints `+0x24..+0x30`, minimum detail `+0x34`,
position `+0x38..+0x40`, visibility radius `+0x44`, active byte `+0x48`.
Milestone 11 independently verified that the threshold is graphics detail and
constructor default 2; no frame/time conversion applies. Disassembly/probes, original expectations and owned inputs
stay under ignored `private/lighting/`.

## Consequential arithmetic

The loader truncates supplied binary64 Ambient/R/G/B times **100**, and Ground/Level
times **1000**, in the established `0x0E7F` context. It does not directly multiply
all six map decimals by 1000. For example, supplied binary64 0.6 times 100 truncates
to **59**; Blue=0.87 becomes **86**. Native functions preserve operation order,
scope/restore round-toward-zero and compile strictly without fused contraction.

The ordinary cell routine expands Ambient/tints with integer `value * 1000 / 100`,
then accumulates active sources whose signed minimum-detail threshold is met. It tests the
integer squared XY distance against radius squared. Inside that radius it uses
the original table-quantized square root and truncates the resulting distance:

```text
falloff = (radius - distance) * 1000 / radius
source contribution = intensity_or_tint * falloff / 1000
terrain = min(2000, ambient + sourceIntensity + elevation * Level - Ground)
bridge = ambient + sourceIntensity + (elevation + 4) * Level - Ground
```

Falloff ignores source/cell Z in this routine. Ordered contributions preserve
individual signed integer truncation. Sources with inactive bytes or minimum detail above the supplied graphics
detail contribute nothing. Cell coordinates (0,0) and (-1,-1) bypass scenario
and sources and return neutral inputs.

Tint channels clamp to 0..2000. A neutral triple (1000,1000,1000) retains 65536
scale. Otherwise the largest channel determines `int(channel * 65536 * 0.001)`.
Red wins maximum ties, then green. Red divides other channels by its **untruncated
floating denominator**; green/blue divide by the **truncated integer scale**.
The dominant channel becomes 1000. Scale below 66 restores neutral tint/65536
and sets brightness to zero. Tint normalization changes brightness through a
low-32-bit multiply and arithmetic shift by 16. Bridge gets that same scale.
Brightness finally clamps to 0..2000. No smooth RGB or standard sqrt replacement
is used. Original normalization can therefore affect both color and brightness.

The native API bounds map values to +/-10, cells to +/-1023 and elevation 0..31,
sources to 256 records, radius 1..32767, source channels +/-10000, and non-overflowing
squared distances. Normalization bounds its explicit inputs. It models low-32-bit
scaling multiplication without C++ signed overflow; arbitrary overflowing/modded
world-distance behavior and invalid zero radii are outside the claim.

The actual map supplies (Ambient,R,G,B,Ground,Level) = (1,1,1,0.87,0,0.028),
quantized to **(100,100,100,86,0,28)**. Spawn (33,86), elevation 4, yields brightness
**1112**, bridge **1224**, scale 65536 and tint **(1000,1000,860)**. These are original
routine outputs with supplied map inputs, not measured original-frame pixels.

## Differential and integration verification

`original_map_light.py` maps the hash-pinned PE and executes unchanged instructions.
Numeric conversion tests supply an explicit double, load it using one existing
original instruction, then run the actual loader's multiply/conversion block.
They do not execute original INI string parsing. The input-load translation cache
is invalidated before reuse and its stop address checked: earlier sqrt execution
must not cause Unicorn to reuse a block across the isolated load boundary.

The complete normalization and cell-light routines execute. The ordinary lighting
selector globals are supplied as inactive; their original helpers run. One explicit
flat-cell coordinate/height getter at `0x4702C0` supplies the environment service;
the routine computes its own XY distance and does not consume that fixture's Z
for falloff. Original sqrt/FTOL/normalization instructions run, with no code patch.

Alpha cases execute the complete constructor with successful allocation fixtures
and original BSurface fill/lock methods. Combined surface cases execute the actual
cell kernel, full scalar LightConvert palette update and complete final surface
copy. Palette, source image, visibility alpha, placement and depth are explicit
inputs; whole actor, house, source creation and original visibility are excluded.

| Matching cases | Count |
| --- | ---: |
| Complete visible-alpha constructor buffers | 8 |
| Actual INI numeric conversion blocks, decimal boundaries and neighbors | 1,544 |
| Complete normalization, dominant channels/ties/clamps/dark cutoff | 1,509 |
| Complete ordinary cell inputs, all elevations, sentinels, ordered overlapping sources, radial boundaries and inactive/detail gates | 838 |
| Every supplied map cell, complete original numeric outputs | 13,515 |
| Combined lighting/palette/final blit, complete RGB565/depth planes | 96 |
| **Total** | **17,510** |

All match. The supplied map's cells are decoded by the native asset reader as
explicit fixture inputs; original map construction is not counted as executed.
Source cases vary Z, positive/negative intensity/tints and one to eight records.
Combined buffers include clipping, source zero, depth ties and varied alpha.
Reports pin original/native/data/owned-input hashes and inventory fixture services.

```sh
./build.command
./run.command
./test.command --data-dir "$PWD/private/game"
build/tools-env/bin/python tests/compare_map_light.py --exe private/disc-allied/game.exe
build/native/presentation-check private/game build/lighting
# After the sanitizer build documented in README:
build/tools-env/bin/python tests/compare_map_light.py \
  --exe private/disc-allied/game.exe --native build/sanitize/map-light-vectors \
  --expectations private/migration/allied-disc/map-light/expected.json \
  --report private/migration/allied-disc/map-light/sanitize-report.json
```

No new dependency or derived data file is added. Runtime GAME.EXE access remains
hash-checked track data only; Unicorn is research-only. Research export refuses
source-installation paths, symlinks and replacement of different existing data.
Original assets/instructions/tables/reports/binaries are never tracked or shipped.
Native previews establish integration only; original-game observations remain absent.

## Next bounded work and original measurements

The following was milestone 10's next-slice recommendation; STATIC_LIGHT.md now
records source recovery and the remaining actor/house association question.
Recover source creation/placement and actor/house light association before extending
this ordinary-input claim. A useful next slice is one stock static light-emitting
building: verify its rules quantization, position, source activation, affected cells,
converter choice and redraw/invalidation. Preserve these numeric and pixel oracles.
Fog/visibility alpha is another independent slice. Do not implement all dynamic
lights or a general weather system merely to broaden this prototype.

When Windows is available, pin the exact executable and record map/cell/elevation,
resolution/pixel format, color scheme and console versus RDP session. Compare one
healthy Rhino on flat cells at different elevations, then at measured distances
from one static light with known radius/intensity/tint. Log cell fields +0x104..+0x114,
source records/detail, selected terrain/house converter and final blit brightness.
Capture alpha-plane values separately from lossless RGB565 frames. Revisit the same
cell after moving/panning and switching player color. Those measurements resolve
actor association, visibility and cache lifetime; screenshots alone cannot do so.

Windows/Linux builds, full-frame parity, scenery, animated poses, pathfinding,
combat, AI, campaigns, multiplayer, audio, saves and Yuri's Revenge remain deferred.
