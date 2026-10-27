# Supplied RA2 1.006 compressed Unit shadow child

October 15, 2026, after `ee3dc9b`. **160 fresh original/native results** verify
the complete cached Unit shadow child and actual compressed RGB565 span. This
is a dependency of the same drawing delivery, not a gameplay milestone.
`src/render/CachedVoxelShadow.*` remains unwired. The complete Unit/world join
still supplies its shadow service; fresh rendering and the shadow cache parent
must nest before runtime integration.

## Identity and reference hypothesis

Exact supplied engine: `private/official-1006-probe/game.exe`, 4,485,392 bytes,
SHA256 `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Its private Windows copy is equal. Embedded 1.08, supplied 1.006 lineage and
reported no-CD modifications remain separate; pristine authenticity is not
established. No Windows action/transfer or source installation/disc, sibling
project or system change occurred.

Consulted [REFERENCES.md](REFERENCES.md)'s pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439`, `docs/voxels.md` Shadows/cache
and LICENSE, plus YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88`,
`TechnoClass.h`, `FootClass.h`, `Surface.h` and `TechnoTypeClass.h`.
Hypothesis: the shadow cache hit uses the previously inspected compressed
wrapper with a different selector/span, while still updating Unit dirty bounds.
Exact base instructions and execution decide it. No reference/header/generated
or lifted code is incorporated; no dependency/notice is added. The MIT grant
for reference-authored work excludes generated game-derived code.

## Verified domain

The complete cached wrapper `0x6D29D0..0x6D2C96`, selector `0x485D60`,
compressed generic surface `0x4350C0` and actual RLE shadow span
`0x489D90..0x489E5B` execute. RTTI identifies
`RLEBlitTransDarkenZRead<uint16>` at `0x79E0E0`; its span slot is checked.
The new verifier composes the earlier complete inspections and adds the complete
203-byte RLE span. Only inspected code ranges grant execution permission.

This is healthy Unit kind 1, world surface, nonnull supplied converter/blitter,
flags **0x2001**, gradient **2**, no status adjustment and checked zero Z-shape.
The original depth-read selector mask is **0x3000**, so these flags select
Convert **+0xF0**, rather than the no-depth +0xD4 slot. Native services preserve
kind -> selector -> kind -> dirty union -> gradient -> depth order. Shadow hits
update global Unit dirty bounds even though the receiver is the world surface.
Keep signed 16-bit crop offsets, dimensions, relative clip origins, clipped-left
zero-run overshoot, strict depth reads and RGB565 half mask **0x7BEF**. Depth
is unchanged. Original RLE reads signed Z-shape bytes; the selected profile
asserts every corresponding supplied byte is zero.

The readable native helper decodes valid snapshot rows, then uses the recovered
ordinary shadow blit. It does not compare read ordering or general malformed
input behavior. Matched plane sizes, bounded dimensions/rectangles and snapshot
checks are safety guards. Native pool offsets replace original process pointers.
Source/plane/converter storage, actor scalars, house association and zero Z-shape
remain supplied. Aliased mutable inputs, alternate shape/gradient/status,
allocation/eviction/lifetime, fresh rendering and parent dispatch are excluded.

## Evidence and reproduction

The 160 cases cover four row patterns (opaque, transparent, clipped zero runs,
sparse), five sizes from 1x1 to 256x64, eight point/clip/depth/dirty profiles,
signed adjustments, edge/offscreen/empty clips and nonzero clip origins. Entire
color/depth hashes, dirty bounds and getter/selector order match. Actual original
snapshot encoding provides the compressed input. These are synthetic planes/
rows; no shadow raster or original actor construction is inferred.

There are **329 audited roots**, **2,604 actual RLE shadow spans** and
**214,328 checked zero Z-shape bytes**. Actor/pool/converter/plane/argument inputs,
caller stack/return/registers, declared writes and restored world/depth/alpha
locks retain scoped audits. Original instructions are unchanged. Execution
counts are not additional comparisons or whole-frame proof.

Receipts: `private/unit-draw-1006/cached-shadow-v1/{expected,report}.json` and
normal/sanitizer replays. Fresh generation first compared a separately compiled
private runner; the CMake runner is independently hashed on each eligible replay.
Transitive source/input/inspection identities and expectation fingerprints are
checked. Previous Unit/world runners remain byte-identical after the new link;
their accepted normal/sanitizer replays remain eligible.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/python tools/verify_cached_voxel_shadow.py \
  --exe private/official-1006-probe/game.exe
build/tools-env/bin/python tests/compare_cached_voxel_shadow.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/unit-draw-1006/cached-shadow-v1/expected.json \
  --report private/unit-draw-1006/cached-shadow-v1/NEW-REPLAY.json
# Add --native build/sanitize/cached-voxel-shadow-vectors for sanitizer replay.
# Fresh original execution needs authorized host JIT access, a NEW --output
# directory and no --expectations. Never overwrite accepted receipts.
./run.command --crossing-demo
```

## Accounting and continuation

Shadow work overlapped the frozen Unit/world generation. Full inherited delivery
and initial pilot/compile elapsed time are unavailable. One direct compile lacked
the configured Homebrew include path; configured flags fixed it. The first pilot
supplied +0xD4 while the original selected +0xF0, yielding a null blitter/no draw.
Inspection corrected that fixture; the next four-case pilot passes. No native
numeric workaround or original instruction patch was used.

Accepted fresh driver/original/native time: **136.772/109.375/0.035 s**.
Normal/sanitizer builds: **5.432/6.305 s**. Replay driver/native times are
**28.004/0.021 s** normal and **29.389/1.543 s** sanitizer. **356 Python tests**,
**14 normal / 13 sanitizer CTests** and source/diff/local-link audits pass.
Actual unchanged SDL crossing takes **2.532 s**: 79 samples / 78 updates,
22 occluded samples / maximum 150 hidden pixels, selection/right-click, fresh
final/no trails, bypass, clipping and pan return all pass. Its occluded PNG is
visually inspected. This tests the existing runtime, not the unwired child or
original frame parity. The app remains arm64. Runs may contend; these are not
FPS measurements. No gameplay repair, worker or new cache was introduced.

Next nest actual fresh shadow rendering with compressed snapshot/recursive cache
hit into the Unit/world join, then complete caller/runtime integration and the
current-cell-light crossing acceptance. Full ownership/lifetime, pitch cache
invalidation, ramps/status, decorations, scheduling/camera/fog/UI and whole-frame
parity remain open. Only Apple Silicon macOS is tested. Locally verified does
not mean independently accepted; full base RA2 then YR remains active/incomplete.
