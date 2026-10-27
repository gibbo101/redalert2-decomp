# Supplied RA2 1.006 part raster to indexed staging

October 15, 2026, after `237a644`. **242 fresh original/native results**
verify the complete staged part root with actual original byte-converter
selection, BSurface copy and indexed spans. The native join now calls the
recovered part wrapper and indexed blit together. The helper remains unwired;
the full Unit/cache/depth/shadow/final-surface join is still pending. This is a
prerequisite checkpoint in the same drawing delivery, not a new gameplay milestone.

## Exact engine and reference hypothesis

The hash gate requires `private/official-1006-probe/game.exe`, 4,485,392 bytes,
SHA256 `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
The approved private Windows copy was previously verified equal. Embedded 1.08,
supplied 1.006 lineage and reported no-CD provenance remain distinct; pristine
authenticity is not established. No Windows task/action/transfer, source disc/
installation, sibling project or system configuration changed.

Consulted [REFERENCES.md](REFERENCES.md)'s pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439`, `docs/voxels.md` staging/final-copy
chain and LICENSE, and YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88`,
`TechnoClass.h` DrawVoxel and `Surface.h` declarations as leads. Hypothesis:
the part root can nest the established original byte selector/copy without a
supplied draw service. Exact base instructions and execution establish the
boundary. No YR layout, upstream/header/generated or lifted code was incorporated;
no dependency or notice was added. The inspected MIT grant excludes game-derived
generated output.

## Flags and the recovered join

**The staging part receives flags zero on the ordinary cache path.** The Unit/
Foot caller supplies `0x2800` to the Techno cache root, but that root initializes
`0x2000`, ORs `0x800`, then ANDs with the complement of the caller's bits:
`(0x2000 | 0x800) & ~0x2800 == 0`. The final world copy separately uses
`0x2800`. Do not pass those final-copy flags to the one-shade staging selector.

`tools/verify_voxel_part_staging.py` composes the existing exact-engine part,
staging, composition and cache mapping inspections. It also checks the cache
parent's flag operations at `0x6D1DCA/0x6D1DD0/0x6D1DD4` and selector's zero-flag
slot read at `0x485BFC`. Complete inspected cache root `0x6D1D00..0x6D21CC`
establishes the argument association; **this new fixture does not execute that
cache parent**. Its actual nesting is the complete part root `0x6D24E0`,
lighting/matrix/raster children, selector `0x485AA0`, surface wrapper `0x49F3A0`
and byte span `0x486310`. Actual Convert constructor/byte initialization run
before the draws. No original instruction is modified.

The initialized byte Convert's zero-flag slot `+0x0C` selects its transparent
indexed remap blitter. The source is the original raster BSurface at `0xAE0DB8`.
The supplied staging surface is a 256x256 byte BSurface. Source-zero pixels leave
the destination intact; a nonzero source remapped to zero erases that destination
pixel. Linked clipping retains the original relative clip-origin convention.
Depth/gradient/brightness values are forwarded but do not add a depth test to
this selected byte span. Source and destination locks restore to zero.

`drawOrdinaryVoxelPartIntoStaging` in `src/render/VoxelPartStaging.*` joins the
existing readable C++ part root and indexed copy. It requires a 65,536-byte
destination and refuses any selected flags other than zero. Converter/remap and
surface storage remain caller inputs; actor flag/house/value callbacks remain
services. Nonordinary blitters, flag bit 8, nonstaging paths, multi-section models,
compressed snapshots/pool, ownership and lifecycle remain outside the domain.

The preceding [VOXEL_PART_1006.md](VOXEL_PART_1006.md) checkpoint remains valid
for its independently supplied flags and final-draw service. This join supersedes
that service boundary only for the selected zero-flag byte path; it does not
relabel the earlier fixtures as a complete Unit draw.

## Evidence and verification

| Fresh original/native results | Count |
| --- | ---: |
| Actual complete one-shade converters: supplied TEMPERAT.PAL and all-black | 2 |
| Three stock parts and 32 headings on both remaps | 192 |
| Clipped edges, empty/nonzero-origin clips, optional/synthetic HVA on both remaps | 48 |
| **Total** | **242** |

Patterned nonzero destination backgrounds expose transparent preservation and
nonzero-to-zero erasure. The all-black converter maps every visible source to zero.
Clip cases include all four edges, empty clip and a contained nonzero origin;
HVA frames include negative/extreme values. Thirty-two prior identity-checked
original pose scenarios supply the body/turret/settled-barrel matrices; they are
reused inputs, not new pose evidence. Synthetic HVA is not animation-timing proof.

There are **490 audited callable roots**, **78 guarded allocations**, **240
actual selector calls**, **240 actual surface calls**, **7,134 actual byte
spans**, 240 each of light/reset/project/flush and 456 matrix multiplies. Every
result compares six crop fields, traversal, 24 corner float words and SHA256 of
both complete 65,536-byte raster and staging planes. Both complete remaps match.
Inherited return/ESP/callee-saved/caller-tail checks, immutable actor/model/HVA/
converter/heap inputs, heap canaries and declared output/image-write ranges pass.
Temporary surface locks restore zero; converter slot identity remains unchanged.
These are bounded fixture audits, not ordered native/original writes or full
actor/heap/layout/frame parity.

Receipts: `private/unit-draw-1006/part-stage-v1/{expected,report}.json`, normal
and ASan/UBSan replays. Exact engine/profile, relevant sources, assets, prepared
data, palette, prior pose receipt and inspections are checked before/after runs.
Changed sources require fresh evidence; previous receipts are not overwritten.
The earlier **342 part results replay on both current builds**.

Builds, **318 Python tests**, **9 normal / 8 sanitizer CTest checks** and source/
diff/link audits pass. Actual unchanged SDL crossing also passes: 79 samples /
78 updates, 22 occluded samples / maximum 150 hidden pixels, selection/right-click,
fresh final/no trails, cache bypass, clipping and pan return. This verifies existing
milestone 20 integration, not the unwired join or original whole-frame parity.
Only Apple Silicon macOS is tested; the native executable is arm64 Mach-O.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/python tools/verify_voxel_part_staging.py \
  --exe private/official-1006-probe/game.exe
build/tools-env/bin/python tests/compare_voxel_part_staging.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/unit-draw-1006/part-stage-v1/expected.json \
  --report private/unit-draw-1006/part-stage-v1/NEW-REPLAY.json
# Add --native build/sanitize/voxel-part-staging-vectors for sanitizer replay.
# Fresh original execution needs the authorized Mac host JIT context and a NEW
# --output directory; omit --expectations. Existing receipts are never replaced.
./run.command --crossing-demo
```

## Accounting and next work

Private `part-stage-start.json` and closing receipt record elapsed time; full
inherited delivery time remains unavailable. Normal/sanitizer builds: **5.04/
6.83 s**. Fresh external/driver/original/native: **139.57/139.491/134.951/0.100 s**.
Test command: 0.72 s; sanitizer CTest: 0.71 s external / 0.67 s internal; actual
SDL: 2.32 s. Replay/audit costs are retained privately. No performance/FPS claim
or cache infrastructure was added.

The first joined pilot incorrectly retained final-copy flags `0x2800`; its draw
assertion stopped before accepting any evidence because the byte selector returned
null. Inspection of the complete cache parent established flags zero. A diagnostic
pilot confirmed the cause, and the corrected three-part pilot passed. No original
code patch, native numeric workaround, accepted full-run mismatch, compilation
failure or gameplay defect/repair occurred. Pilot elapsed times were not measured.

Next join the actual Foot/cache/Unit root around this staged child and established
dirty-union/cache decisions, then combine depth, shadows and final surfaces before
runtime wiring. Full construction/ownership, pitch lifecycle/invalidation,
decorations, scheduler/camera/fog/UI and whole-frame parity remain open. Full base
RA2 then YR stays active/incomplete. This is locally verified recovery, not
independent acceptance or a completed observable milestone.
