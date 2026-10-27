# Supplied RA2 1.006 healthy Unit voxel drawing caller

[UNIT_BARREL_1006.md](UNIT_BARREL_1006.md) extends this neutral checkpoint with
nonneutral barrel inputs and independent hot/empty part caches: 5,379 fresh results
and both replays, including newly executed instances of all 3,200 scenarios below.
Earlier receipts retain their source identities and recorded neutral domain.
Cache invalidation, final drawing children and runtime wiring remain open.

October 15, 2026, after `d1c9d9a`. **3,200 fresh original/native results** and
normal/ASan/UBSan replays pass. The complete original Unit voxel root executes
on a bounded healthy branch with actual Drive poses, Facing, matrix helpers,
cache prechecks and Foot lit/shadow wrappers. Final Techno drawing and surface
services remain supplied. The new native helper remains unwired; this is a
prerequisite checkpoint in the same moving/turning/current-cell-light delivery,
not a new observable milestone or original full-frame proof.

## Identity, references and boundaries

Exact supplied engine: `private/official-1006-probe/game.exe`, 4,485,392 bytes,
SHA256 `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
It was rehashed equal to the approved private Windows copy during the preceding
Foot checkpoint. The verifier and both replays recheck this engine's identity.
Embedded 1.08, supplied 1.006 patch lineage and user-reported no-CD provenance
remain separate facts; pristine authenticity is not established. No Windows task,
source installation, disc or system configuration changed.

Consulted pinned redalert2-recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439`,
`docs/voxels.md`/LICENSE, and YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88`, `FootClass.h`, `TechnoClass.h`,
`LocomotionClass.h` and `Interfaces.h`. Hypothesis: Unit joins body/turret/barrel
cache decisions, indexed staging, a final world draw and separate shadows.
Exact base instructions and actual vtable slots establish the path below;
YR layouts/signatures and recomp behavior are not the oracle. No upstream,
header, generated or lifted game code was incorporated.

`tools/verify_unit_voxel_draw.py` pins **28 complete ranges / 2,363 instructions**:
26 returning functions and two complete tail wrappers. The Unit root itself is
**`0x6FF690..0x7005A5`, 3,861 bytes / 1,076 instructions**, ending with `ret 0x1C`.
Trailing NOPs are excluded. The range is completely inspected; execution covers
the selected branch, not all its alternate branches.

| Nested boundary | Patched VA | Executed domain |
| --- | --- | --- |
| Drive Draw_Matrix / Shadow_Matrix | `0x4A0050`, `0x4A0500` | Flat healthy inputs |
| Base body/shadow matrices | `0x53D030`, `0x53D0D0` | Flat Track and ramp-zero matrix |
| Drive Draw_Point / Shadow_Point / predicate | `0x53D4D0`, `0x53D1C0`, `0x53D4E0` | Actual leaves, supplied ground height zero |
| Type getter wrappers / multiple-turret predicate | `0x6C12C0`, `0x705020`, `0x6D83E0`, `0x6DF680` | Synthetic type with count zero |
| Cache prechecks | `0x70A3F0`, `0x70A350` | Matching hot entries or empty counts |
| Facing getter | `0x4B8BE0` | Supplied steady facings |
| Foot lit / shadow | `0x4C9880`, `0x4C9A40` | Complete wrappers, actual Drive leaves |
| Camera/ramp copy, matrix copy/multiply/translate/rotate and trig | Verifier inventory | Complete selected helper calls |

The verifier checks actual Unit and Drive slots plus trig/scale/heading tables.
The native runner uses hash-checked `private/derived/ra2-1006/raster-data.bin`.
This uses the migrated table values already established by [RASTER_1006.md](RASTER_1006.md).
New receipts pin that prepared file's identity independently.

## Recovered ordinary orchestration

`src/render/UnitVoxelDraw.*` is SDL-free and uses readable part/state/services:

- Divide signed actor animation frame by positive body HVA frame count; retain
  the signed remainder. The body key keeps its low five bits. Synthetic frame
  counts exercise this caller arithmetic; they do not recover animated actor timing.
- Save the current surface, switch to staging, get its bounds, then set actor
  staging byte `+0x5BB`. Copy the supplied initialized empty-dirty rectangle in
  four ordered stores, including when a preceding draw left another rectangle.
- Global byte `0x839A58` zero seeds key **-1**; any nonzero byte seeds **zero**.
  Its startup/ownership and final semantic name remain open. It must not be
  called DisableVoxelCache from that test alone. The flat Drive and parent then
  pack the heading and frame using the already recovered key arithmetic.
- Body uses point (128,128), staging bounds, brightness unchanged and flags
  `0x2800`. Actual Foot obtains the zero Draw_Point and forwards its local matrix.
- Construct the turret key even before ordinary turret-model drawing decisions.
  A key other than -1 checks the turret cache only when its count is
  nonzero; the barrel precheck runs for a present barrel and key other than -1,
  even with an empty barrel cache. Both matching hot/empty cases are covered.
- When the turret and any present barrel both have cached images, forward copies
  of the **untransformed body matrix** to those parts. Otherwise compute the
  camera-transformed relative turret and neutral barrel poses. Cache hits make
  these matrices unused downstream, but the caller's forwarding still differs.
- Preserve repeated actual multiple-turret queries and heading-dependent
  barrel-before/after-turret order. Body/turret use the signed remainder frame;
  barrel uses frame zero. Each lit call passes through complete actual Foot.
- Apply the final brightness callback and status query only after the parts;
  final Unit wrapper receives the original world surface, point, by-value clip
  rectangle and returned brightness. Copy the resulting dirty rectangle before
  restoring the surface and clearing the staging byte.
- Derive the shadow seed from body key, execute actual flat Drive shadow pose,
  query height and cell in order, then test the predicate's **low byte**. For the
  tested Track/height-zero branch, a false predicate adds **`0x80000000`** to the
  packed shadow key and uses staging as its stencil. A true predicate retains
  the packed key and passes no stencil surface. Keep the following separate
  height query. The body key -1 still supplies its extracted 1023 seed here;
  final shadow-cache disabling is a separate child decision.
- Pass through complete Foot shadow forwarding, then clear staging using the
  dirty rectangle saved after the final world draw. Draw_Point, Shadow_Point
  and the true Drive shadow predicate execute unchanged.

The new high-bit/stencil decision is outside the partial key block tested in
[SHADOW_KEYS_1006.md](SHADOW_KEYS_1006.md). That earlier evidence remains valid
for its boundary; it did not prove this later caller decision. Current Renderer
still uses its earlier bounded composition and does not yet use this new root.

## Fixtures, audits and limits

The domain is original type visible, healthy flat Track, one ordinary turret,
zero turret offset, supplied neutral barrel pitch, height zero, no alternate body,
multiple turrets, HunterSeeker, BalloonHover, add-14, bridge, clip-height or active
status branches. These are selected field inputs, not full construction or proof
of every post-load stock actor field. Native API names and guards retain that scope.

The supplied body HVA record contains a positive frame count. Camera matrices
(identity and an exact fractional matrix), ramp-zero identity and initialized
empty-dirty template are explicit inputs. This new suite does not execute their
startup constructors. Visibility, map cell, height, brightness/status and surfaces
are bounded services. Final Techno lit and shadow children are captured after
actual Foot forwarding; they do not execute original raster pixels or compressed
cache storage. Each supplied successful lit draw writes a distinctive dirty
rectangle, so restoration, final argument selection and clearing are observable.
The actual final Unit wrapper `0x6FF3E0` is still a service here.

**3,200 callable roots** enforce unchanged return address, caller tail, ESP and
callee-saved registers, immutable fixture arenas, and image writes limited to
surface/dirty globals. Only actor staging byte may change in the fixture arena;
it must end clear, and the world surface must be restored. **12,149 supplied
writes** have explicit output-range checks; host writes are counted separately
from Unicorn memory hooks. No original instructions are patched. The prechecks
do not exercise nonempty cold lookup/search, insertion, allocation or failure.

| Fresh matching scenarios | Count |
| --- | ---: |
| All 32x32 heading pairs, cold and warm images, alternating cameras/predicates | 2,048 |
| Unique heading-boundary values with no barrel | 128 |
| Signed frame/remainder, gate byte, wrapped arguments, low-byte predicate | 1,024 |
| **Total** | **3,200** |

Normal/sanitizer replays match every ordered event, forwarded argument and raw
matrix dword. Native domain guards reject nonpositive HVA counts and reentrant
staging surfaces before callbacks. Separate tests check FP restoration for four
host rounding modes on a pre-draw service exception; broader exception/lifetime
equivalence is not claimed. All **246 Python tests**, 6 normal / 5 sanitizer CTest
checks, source/diff audits and actual SDL crossing pass. The unchanged crossing
has 79 samples / 78 updates, 22 occluded samples / 150 maximum hidden pixels,
fresh final/no trail, cache bypass, clipping and camera return. This verifies
existing native integration, not integration of the new kernel or frame parity.
Broad unrelated suites were not repeated; only Apple Silicon macOS is tested.

## Reproduction, accounting and next dependency

Receipts: `private/unit-draw-1006/voxel-root-v1/{expected,report}.json`,
`native-replay.json`, `sanitize-replay.json` and `crossing-sdl/`.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/python tools/verify_unit_voxel_draw.py \
  --exe private/official-1006-probe/game.exe
build/tools-env/bin/python tests/compare_unit_voxel_draw.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/unit-draw-1006/voxel-root-v1/expected.json \
  --report private/unit-draw-1006/voxel-root-v1/NEW-REPLAY.json
# Add --native build/sanitize/unit-voxel-draw-vectors for sanitizer replay.
# Fresh original execution requires the authorized Mac host JIT context:
build/tools-env/bin/python tests/compare_unit_voxel_draw.py \
  --exe private/official-1006-probe/game.exe --output private/unit-draw-1006/NEW-VOXEL
./run.command --crossing-demo
```

Fresh driver/original/native costs: **30.384/29.798/0.091 s**. Normal/sanitizer
replays: **0.685/0.932 s** driver, 0.076/0.345 s native. Normal builds: 3.973 s
initial, 7.193 s after dirty-template reset, 6.390 s with guards; sanitizer build
8.412 s. Final CTest totals: 0.10/0.49 s; Python discovery: 0.307 s, bundled
test.command/discovery 1.693 s. SDL: 2.303 s. Checks sometimes contended; these
are not FPS claims. External fresh CLI elapsed and full inherited delivery time
are unavailable. The private checkpoint records closing time after 05:51:02 UTC.

No accepted differential run failed. Exploratory probes exposed the raw gate's
polarity and an uninitialized ramp matrix in the fixture; the final fixture
supplies identity explicitly and does not claim startup recovery. Native dirty
state was changed before fresh generation to reset from a separate template
each call. Test discovery initially counted seven imported tests twice; using a
module import fixed the count (246 distinct tests). No game playtest repair,
new cache infrastructure, extra worker or Windows action was needed.

Next recover the ordinary final Unit surface wrapper `0x6FF3E0` and remaining
type/model/neutral-field associations needed by this branch, then nest the
established actual cache/raster/staging/house/surface children and drawing caller
before runtime integration. Keep the same moving/turning/scenery/current-cell
light scenario. Complete construction/ownership, decoration, outer scheduling,
camera/fog/UI and whole-frame parity remain separate work. Full base RA2/YR
stays active and incomplete. This is locally verified, not independently accepted.
