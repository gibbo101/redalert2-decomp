# Supplied RA2 1.006 staged voxel part renderer

Later October 15 update: [VOXEL_PART_STAGING_1006.md](VOXEL_PART_STAGING_1006.md)
adds actual converter selection/final staging copy for the zero-flag byte path.
The independently supplied flags and service boundary below remain this
checkpoint's domain; complete Unit/cache/runtime integration is still open.

October 15, 2026, after `eb28019`. **342 fresh original/native comparisons**
and normal/ASan/UBSan replays pass. The complete ordinary Techno part-render
wrapper now nests actual original lighting, matrix, projection, raster and flush
children. Native `drawStagedVoxelPart` matches the complete indexed raster buffer,
crop, traversal, corner float words and ordered forwarding events in this domain.
The helper remains unwired. The final staging blit is still a service here;
this is a recovery prerequisite of the same Unit drawing delivery, not a new
observable gameplay milestone or whole-frame claim.

## Identity and references

The executable hash gate requires `private/official-1006-probe/game.exe`,
4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
It is the previously verified equal supplied Windows engine. Embedded 1.08,
supplied 1.006 lineage and reported no-CD provenance remain distinct; pristine
authenticity is not established. No Windows action or transfer was needed.

Consulted [REFERENCES.md](REFERENCES.md)'s voxel/cache leads: recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439`, `docs/voxels.md` (miss/view/
section/finish chain and staging) and LICENSE, and YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88`, `TechnoClass.h` DrawVoxel
declarations. Hypothesis: the part miss builds an indexed image before selecting
the staging converter and forwarding a clipped surface copy. Exact base
instructions and fresh execution establish the boundary below. No YR layout,
upstream/header/generated or lifted code was incorporated. The inspected MIT
grant excludes generated game code; no new dependency or notice is required.

## Recovered boundary

`tools/verify_voxel_part.py` pins **five complete ranges / 246 instructions**:
root `0x6D24E0..0x6D280E` (exclusive end, final `ret 0x20` at `0x6D280B`),
actual flag getters `0x6D6DF0` / `0x6D6E00`, Unit kind `0x70A2D0`, and raster
surface getter `0x717040`. Unit vtable associations and frame/point/clip/staging
operands are checked. Existing raster mapping verification separately pins the
selected nested children against the retained disc inspection. All new execution
is on the supplied patched engine; no old disc expectation is relabeled.

The root's eight stack arguments are output crop, model descriptor, pose,
point, clip, frame, flags and brightness. In the supported path:

- Compute section lighting from the supplied pose before applying HVA geometry.
- When HVA is present, select its frame with **unsigned DIV**, unlike the Unit
  caller's signed remainder. Multiply pose by HVA, then the identity global
  matrix. Preserve original float32 stores and rounding.
- Execute actual lighting `0x7170D0`, reset `0x7171D0`, matrix `0x591180`,
  project `0x7174C0` and flush `0x7178E0` children.
- Query actor flag +0x204, then +0x205 only when the first is zero. Preserve
  house/predicate/flag-adjustment short circuit and clear flag bit `0x10`.
- Unit kind 1 and nonzero staging byte select the supplied global staging
  converter. Query value +0x2C4 before +0x2C0, then select the blitter.
- Forward the four-field source rectangle, crop-adjusted wrapped destination
  point, unchanged clip, values, brightness and zero timer remainder.

Native scope is one loaded section, absent or supplied one-section HVA,
Unit kind 1, staging surface/byte, identity global matrix and ordinary light.
Flag bit 8 is refused, including when adjustment introduces it. Nonstaging
clip-height paths, alternate actor kinds, multiple sections and alternate light
remain excluded. House query, predicate/flag adjustment, value getters, blitter
selection and final surface draw remain explicit services. Actual converter
selection/blitting and the cache/Unit caller join are next.

## Evidence and audits

| Fresh original/native results | Count |
| --- | ---: |
| Three stock parts, three HVA modes and all 32 headings | 288 |
| Flag short circuit, low-byte house/predicate, adjustment, wrapped forwarding | 54 |
| **Total** | **342** |

HVA modes are absent, one identity frame and three synthetic transforms.
Frames include signed extremes and negative values to distinguish unsigned frame
selection. Thirty-two identity-checked scenarios from `barrel-v1/expected.json`
provide body/turret/settled-barrel pose inputs. These are reused inputs; all 342
new wrapper/raster executions are fresh. Synthetic HVA does not prove animation
timing or native HVA loader parity.

Each result compares the SHA256 of all **65,536 raster bytes**, six crop fields,
traversal, 24 corner float words and ordered service arguments/events. There are
**687 audited callable roots** and **12 guarded loader allocations**. Actual
nested call counts are 342 each for light/reset/project/flush and 570 matrix
multiplies. Inherited callable checks preserve return address, caller tail,
ESP, callee-saved registers and immutable fixture/heap inputs, and restrict image
writes to declared scratch/output ranges. Heap canaries remain intact. No original
instruction is modified. These audits are not native layout/ownership, arbitrary
callback mutation, compressed pool, lifecycle or full-frame evidence.

Accepted private receipts: `private/unit-draw-1006/part-v1/`, including
`expected.json`, `report.json`, `native-replay.json` and `sanitize-replay.json`.
All executable, source, asset, prepared-data, pose and inspection identities are
checked before and after runs. Rebuilt runners are permitted; changed inputs
require fresh evidence. The previous barrel expectations replay **5,379 results
on each current build**. Both builds, **312 Python tests**, **9 normal / 8
sanitizer CTest checks** and source/diff/link audits pass.

Actual unchanged SDL crossing also passes: 79 samples / 78 updates, 22 occluded
samples / maximum 150 hidden pixels, selection/right-click, fresh final/no trails,
cache bypass, clipping and pan return. This checks milestone 20 integration,
not the unwired helper or original whole-frame parity. Only Apple Silicon macOS
is tested; the native executable remains arm64 Mach-O.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/python tools/verify_voxel_part.py \
  --exe private/official-1006-probe/game.exe
build/tools-env/bin/python tests/compare_voxel_part.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/unit-draw-1006/part-v1/expected.json \
  --report private/unit-draw-1006/part-v1/NEW-REPLAY.json
# Add --native build/sanitize/voxel-part-vectors for sanitizer replay.
# Fresh original execution needs the authorized Mac host JIT context and a NEW
# --output directory; omit --expectations. Existing receipts are never replaced.
./run.command --crossing-demo
```

## Accounting and next work

Started 10:50:15 UTC; private closing receipt records end/elapsed time. Full
inherited delivery elapsed remains unavailable. Normal build failed at 2.73 s
because of a missing namespace brace, then passed at 5.84 s; final runner rebuild
took 1.88 s. Sanitizer build took 6.84 s. Fresh external/driver/original/native:
**159.51/159.429/157.101/0.086 s**. Replay/check/SDL measurements are retained
privately; SDL took 2.30 s. No performance/FPS claim or cache infrastructure.

The first original pilot put frame in the wrong stack position and stopped at
an unmapped read. Stack operand inspection corrected the argument order before
accepted evidence. The draw observer also initially read six dwords from the
four-dword source rectangle; corrected before native comparison (returned crop
still has six fields). Corrected three-case pilot passed. No accepted full-run
mismatch, gameplay defect/repair, worker, Windows/source/system change occurred.

Next nest actual staging converter selection/blit, join this child to the Foot/
Techno cache and Unit root, then combine depth, shadow and final surface children
before runtime wiring. Pitch-driven cache invalidation, full construction/
ownership, decorations, scheduler/camera/fog/UI and whole-frame parity remain
open. Full base RA2 then YR stays active and incomplete; this checkpoint is locally
verified recovery, not independent acceptance or a completed game.
