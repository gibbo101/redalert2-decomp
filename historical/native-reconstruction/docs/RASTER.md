# Milestone 6: flat voxel poses and indexed rasterization

[RASTER_1006.md](RASTER_1006.md) extends this bounded domain to the supplied
RA2 1.006 engine with explicit profiles, fresh evidence and caller/heap audits.
Runtime and prepared data remain disc-only. Its guarded receipt/replay commands
supersede the historical evidence paths below.

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

[COMPOSITION.md](COMPOSITION.md) supersedes ordinary placement/depth composition
and removes the auxiliary voxel depth plane described below. Indexed-buffer
evidence remains current. [SHADOW_COLOR.md](SHADOW_COLOR.md) supersedes the ellipse
and absent player remap below with bounded verified kernels. Special actor/cache
branches and full staging integration remain unverified.

October 10, 2026, Ivalice / Apple Silicon macOS. Baseline: `a6b49b9`.
The oracle remains the supplied Allied-disc base RA2 GAME.EXE, embedded version
`1.08`, preferred base `0x400000`, SHA-256:

`135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743`

This note supersedes the triangle-rasterizer, flat-pose camera and lighting-input
limitations in [PRESENTATION.md](PRESENTATION.md). Its shade/palette evidence remains
current. Exact single-section indexed buffers are now compared to the original;
**whole-screen, terrain-composite and full cache-lifetime parity are not claimed**.

## Implemented boundary

The visible Rhino now uses the recovered indexed voxel raster path. Cube meshes
and triangle coverage have been removed. The portable asset reader retains each
validated compressed VXL span alongside decoded voxels. VoxelRaster.cpp consumes
those spans using original traversal and packed coordinate arithmetic, producing
a 256×256 indexed scratch buffer and the original crop rectangle.

The bounded profile is one section per part, lit VXL normal encodings 2/4, flat
drive pose, HTNK's zero TurretOffset, neutral barrel pitch and identity HVA frame.
Body, turret and barrel remain separate original assets. Rendering is SDL-free;
SDL only presents the final portable framebuffer. Simulation code is unchanged.

## Binary-derived behavior

| Evidence | Base-game VA |
| --- | --- |
| Full drive Draw_Matrix | `0x49FC20` |
| Base locomotion pose and heading key | `0x53B0C0` |
| Relative turret rotation block | `0x6F4744..0x6F47B4` |
| Unit camera/pose composition | `0x6F43CE..0x6F43DC`, `0x6F48AA..0x6F48EA` |
| Unit draw setup | `0x6C7900` |
| Camera initialization tail | `0x70D6DE..0x70D714` |
| Camera degree initializers | `0x70C7B0`, `0x70C7D0` |
| Sine / cosine lookup helpers | `0x4B9FA0` / `0x4B9FF0` |
| Trig data / input scales | `0x7EA0E4` / `0x7C3128` |
| Rotate X / Y / Z | `0x58D410` / `0x58D530` / `0x58D650` |
| Matrix multiply / point transform | `0x58DE30` / `0x58E030` |
| Inverse-like transpose / direction transform | `0x58E0D0` / `0x58D980` |
| Full original VXL loader | `0x70DBC0` |
| Clear/reset drawing scratch state | `0x70BC30` |
| Project section bounds | `0x70BF20` |
| Flush sections and calculate crop | `0x70C340` |
| Generate raster state | `0x70E3A0` |
| Traversal table / dispatch table | `0x7E36B0` / `0x7E3630` |
| Lit dispatch 4 / 5 span rasterizers | `0x784180` / `0x7842A0` |
| Indexed scratch buffer | `0xACAE68` |

YRpp VXL declarations were inspected as layout leads only. The base loader was
executed to verify runtime corner construction and span pointers. No header or
third-party implementation was copied. Disassembly and extracted tables stay
under ignored private/raster/ and private/derived/.

### Heading, camera and lighting transforms

Simulation facing remains a 16-bit angle. Rendering quantizes it using:

`(((heading >> 10) + 1) >> 1) & 31`

This is 32 bins with the original boundary ties and wrap. Body rotation uses
`(bin - 8)` times the stored negative pi/16 constant. A zero-offset turret applies
the difference between its quantized angle and the body's to the existing body
matrix; replacing that composition with an independently generated turret matrix
can lose intermediate float32 behavior.

The original camera initializes identity, rotates X by negative 60 degrees, then
Z by negative 45 degrees. These are executed lookup-table rotations, not calls to
std::sin/cos. The lookup index preserves integer truncation, signed division,
negative wrapping and odd-index adjustment. Camera/pose multiplication and point
transforms retain their distinct operation orders and float32 stores. The full
flat drive matrix and its heading cache key are compared against the original.

The double-light setup now follows the original wrapper too: initialize the light
with its original scalar/vector and table rotation, transpose the pose using the
original inverse-like helper, then rotate the light as a **direction**. That
operation ignores translation and uses a different operation order from a point
transform. An initial implementation that applied translation failed the shifted
pose test and was corrected. The original shade kernel from milestone 5 then runs
with that light, the identity-transform view direction, and intensity 3.

The tested FP context remains `0x0E7F`: 53-bit x87 precision, rounding toward zero.
Native operations scope/restore the host rounding mode and compile without fused
contraction. Original table values are supplied as data, never compiled arrays.

### Bounds, traversal and packed coordinates

The original loader's first four corners walk the lower Z plane in this order:
(max X,max Y), (max X,min Y), (min X,min Y), (min X,max Y). The upper plane follows.
The drawing pipeline transforms all eight corners, negates projected Y, tracks
min/max extents and selects the first strictly smallest-Z corner. Ties retain the
first corner, which matters at axis-aligned views.

That corner selects one of eight owned traversal records. These choose the start
column, column/row strides, projected axis endpoints and forward or reverse Z
span decoding. The pipeline recenters around the float32 midpoint of the extents,
adds 128 scratch pixels, converts to 8.8-style coordinates and stores low 16 bits.
The native implementation preserves these conversions and original crop padding.

The selected original assembly branch packs X and Y into one unsigned 32-bit word.
**Carries from the low X lane affect the Y lane.** Skips use separately accumulated
16-bit offset pairs, while occupied runs repeatedly add the packed step. A dense
voxel list with an independently calculated `origin + z * step` is not equivalent.
This is why the asset reader retains the original validated runs, including their
reverse traversal duplicate counts.

Original dispatch 4/5 writes one indexed pixel per occupied voxel and uses painter
order without the separate internal voxel Z-buffer. The fixture selects the
base game's initialized lit flags (internal Z off, flag 4 on). Other dispatch
variants, scalar fallback coverage, unlit voxels, shadows and multi-section sorting
are not covered. The native bound rejects projected extents above 240 pixels;
it does not claim arbitrary oversize scratch-buffer behavior.

### Cache and composition limits

The flat drive's heading key, the five heading bits and the relative turret pose
are recovered. The complete cache key layout, invalidation, cached sprite reuse
across body poses, animation/pitch states and full Unit DrawVoxel actor behavior
remain outside this milestone. The runtime keeps one last-result cache per part,
keyed by exact matrix bits and HVA frame. It does not claim original cache lifetime.

The indexed buffers are exact for the tested inputs **before compositing**.
Placing them at the world coordinate, nearest-neighbor zoom, the auxiliary depth
used to combine parts/terrain, TMP depth projection, map-light row selection,
player colors and the ellipse shadow remain host adapters. The internal no-Z
rasterizer supplies no per-pixel world depth, so the runtime records a separate
approximate depth alongside its indexed output. That extra plane is not counted
as original output. General nonidentity HVA timing, turret offsets, barrel pitch,
slopes, vehicle rocking and other unit types remain unverified.

## Differential and integration verification

`tests/original_raster.py` runs the **full original VXL loader** with bounded file
open/read/seek/close and allocation fixtures. It then runs unmodified original
pose, lighting, bound projection, state generation, selected rasterizer and crop
code. No service callbacks occur during pose/render execution. Original instruction
bytes are unchanged. Turret and camera setup use the explicitly listed blocks;
the full Unit actor renderer and its world services are not executed.

The final suite compares:

- 128 body/turret/camera pose cases, including heading boundaries and wrapped angles;
  all matrix float32 bits match, and the original flat heading key is checked.
- 192 camera/pose products and 192 full lighting setups.
- **192 complete 256×256 indexed section buffers**, including all 32 headings for
  body, turret and barrel, reversed views and fractional translations. All eight
  traversal choices are asserted to occur. Full-buffer SHA-256 values match; all
  projected-corner bits, selected traversals and crop fields also match.

These are complete section buffers, not screenshots of complete original gameplay.
The previously established 125,073 movement/facing/timing comparisons and 8,568
presentation cases (312,208 values) remain regression requirements.

Native checks cover retained spans, heading ties, data-hash rejection, a synthetic
single-voxel footprint/crop, scratch bounds and FP restoration. Owned-data tests
exercise independent body/turret headings, partial cliff occlusion, movement and
the 170-frame SDL input smoke. Sanitizers cover the headless and owned-data tests
and replay the complete raster expectations through the instrumented native runner.
Visual previews are inspected for integration, not used as original fidelity proof.

## Prepare, run and reproduce

```sh
python3 tools/prepare_raster_data.py --exe private/disc-allied/game.exe
./build.command
./run.command
./test.command --data-dir "$PWD/private/game"
build/tools-env/bin/python tests/compare_raster.py --exe private/disc-allied/game.exe
build/native/presentation-check private/game build/raster
```

Preparation is already done here. private/derived/raster-data.bin contains 41,312
bytes of traversal/trigonometry data and constants, SHA-256:

`f357f3b4d7b048b7f65d7a43f4f96a41e6c21b5974bb1340d7fd98e92abcd8a3`

The native reader validates the whole file. --raster-data selects another private
copy. Source-tree writes, unknown executable hashes and overwrites of different
derived data are refused. Runtime GAME.EXE access remains **track data only**.
All new executable-derived data is prepared separately, with no original code
execution. Python and Unicorn remain research dependencies only.

The oracle exports the four owned research assets read-only to private/raster/assets/,
refusing source-tree destinations, symlinks and differing existing output. Reports
at private/raster-report.json and private/raster-sanitize-report.json identify the
executable, native runner, derived data and asset hashes. Original buffers, diagnostic
vectors and disassembly remain private and must never be committed or distributed.

Next, recover the original terrain/world depth baseline and final unit blit path,
then cache/part composition. Original-game captures should pin this executable,
map/cell/elevation, body/turret headings, player color, pixel format and resolution.
Compare sprite placement, terrain masking edges, part overlap and shadows against
lossless original frames. Those measurements address the remaining composition
boundary; they do not replace the exact indexed-buffer oracle established here.
