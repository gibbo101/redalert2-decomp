# Supplied RA2 1.006 complete shadow cache and world drawing

October 15, 2026, after `cd03eb9`. This checkpoint joins the complete healthy
Unit shadow parent to actual fresh raster, compressed pool snapshot, recursive
cache hit and raw/cached RGB565 world drawing. The readable
`src/render/ShadowVoxelWorld.*` helper remains unwired. It is a dependency in the
same moving/turning/current-cell-light drawing delivery, not a gameplay milestone.
The complete Unit/world root still supplies its shadow callback.

## Exact identity and reference hypothesis

Engine: `private/official-1006-probe/game.exe`, 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Both this and the approved private Windows copy were rehashed. Embedded 1.08,
supplied 1.006 lineage and reported no-CD modifications remain separate facts;
pristine authenticity is not established. No Windows action/transfer, source
installation/disc, sibling-project or system change occurred.

Consulted [REFERENCES.md](REFERENCES.md)'s pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439`, `docs/voxels.md` Shadows/cache
and LICENSE, and YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88`,
`TechnoClass.h`, `FootClass.h`, `Surface.h` and `TechnoTypeClass.h`.
Hypothesis: successful shadow misses can nest the original fresh renderer and
snapshot, then recursively hit the same compressed wrapper verified previously.
Exact base instructions and execution decide it; YR/HD behavior is only a lead.
No reference/header/generated or lifted code was incorporated. No dependency or
notice was added; the reference MIT grant excludes generated game-derived code.

## Recovered join and boundaries

The complete original root `0x6D21E0` executes with fresh renderer `0x6D2810`,
actual type dispatcher/leaf, HVA matrix multiplication, projection queue/flush,
shadow plotter, `0x69A1D0` snapshot encoding and successful signed index growth/
sort/search. A successful miss recursively reenters the shadow parent, then
uses `0x6D29D0`, the actual compressed selector/surface and RGB565 depth-read
span. A bypass directly uses the raw selector/surface/span. Original instructions
are unchanged. The code-only allowlist composes complete prior inspections and
adds the entire shadow plotter, including its out-of-line unmasked loop and
second return; inspected data tables never grant execution permission.

Preserve these decisions:

- Actor suppression, type NoShadow and loaded-model invalidity precede cache
  lookup. A warm hit still needs a valid loaded model; it can omit current HVA.
- Null index or DisableShadowCache forces key -1. Bypass renders even when
  rebuild is disallowed. An ordinary cacheable miss obeys the rebuild guard.
- Fresh drawing uses HVA frame **zero**. The supplied pose multiplied by that
  HVA is the **model** transform, applied before Z flattening. The distinct global/
  half-scale camera transform follows; this profile supplies identity globals
  and disables half scale. Do not pass the pose as that camera transform.
- Cacheable fresh rendering does no direct world copy. Snapshot append is
  followed by recursive lookup, which sorts/sets the hot record before cached
  drawing. Keep signed keys and the successful 10/20/40 capacity progression.
- Cached drawing performs the Unit dirty union even on world surfaces, then
  queries gradient before depth. Raw bypass queries gradient/depth/selector and
  does **not** union dirty bounds. Both use flags 0x2001, gradient 2, strict
  depth reads and RGB565 half mask 0x7BEF. Cached selection is Convert +0xF0;
  raw selection is +0x2C. World depth remains unchanged.

Only one loaded VXL section, supplied positive-frame fresh HVA, successful heap/
sufficient pool, healthy Unit/world, identity globals/no half scale, ordinary
nonnull converter and gradient 2/checked zero Z-shape are covered. Three supplied
HVA frames test frame-zero selection, not animated actor timing. Pose fixtures
reuse identity-checked original barrel receipts; they are supplied inputs, not
original actor construction. Stencil, color/depth planes, actor scalars, converter/
house records and native pool/index ownership are supplied. The exact converter
+0x17C scratch store is declared; other converter bytes remain immutable.

Matched/bounded planes, finite matrices, snapshot bounds, null-model refusal and
native pool-exhaustion exceptions are safety boundaries. Native snapshot headers
use pool-relative offsets. Allocation/pool failure, eviction, full ownership/
lifetime, alternate status/shape/scale, read ordering and whole-frame parity are
not claimed. The runtime does not execute the original binary.

## Evidence and reproduction

**402 fresh original/native results including three resets** pass. The groups
are 96 cold part/heading/HVA/stencil/recursive-hit cases, 96 warm cases with
missing HVA and changed pose/stencil/planes, 96 reverse signed-key searches with
changed placement/depth, 72 raw bypass/clipping cases, 36 precheck-before-cache
cases and three disallowed cold misses. All three supplied models and 32 original
pose pairs execute. Stencils are supplied 256x256 byte planes with zero origins;
planes are 160x144. Full raster, world color/depth, dirty bounds, normalized pool/
cursor and complete index size/capacity/sorted/hot/key state match.

Audits record **807 checked roots / 49 guarded allocations**, 495 shadow-parent
entries, 168 fresh renderer/queue/flush/plotter calls, 96 snapshots, 288 cached
wrapper calls, 7,302 compressed spans, 1,224 raw spans, 255,558 checked zero
Z-shape bytes and 113,043 bounded padded encoder reads. These are execution
counts, not additional independent comparisons. Caller stack/return/callee-saved
registers, declared writes, immutable actor/type/model/HVA/stencil/planes/old
pool/other heap, capacity tail, padded reads and restored surface locks retain
scoped audits. Native/original write order and general malformed inputs are not
compared.

Receipts are under `private/unit-draw-1006/shadow-world-v1/`, with transitive
source/input/inspection identities, exact engine/profile and protected expectation
fingerprints. Normal/sanitizer replays are recorded there. Existing Unit/world
and cached-shadow runner hashes remain identical on both builds; their accepted
source-matched replays stay eligible.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/python tools/verify_shadow_voxel_world.py \
  --exe private/official-1006-probe/game.exe
build/tools-env/bin/python tests/compare_shadow_voxel_world.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/unit-draw-1006/shadow-world-v1/expected.json \
  --report private/unit-draw-1006/shadow-world-v1/NEW-REPLAY.json
# Add --native build/sanitize/shadow-voxel-world-vectors for sanitizer replay.
# Fresh original execution needs authorized host JIT access, a NEW --output
# directory and no --expectations. Never overwrite accepted receipts.
./run.command --crossing-demo
```

## Accounting and verification limits

Fresh driver/original/native time is **361.541/323.420/0.172 s**.
Normal replay driver/native time is **34.506/0.122 s**;
sanitizer replay is **38.498/4.113 s**. Builds, **364 Python tests**,
**15 normal / 14 sanitizer CTests**, source/diff/local-link audits and actual SDL
crossing pass. Sanitizer CTest driver takes **2.120 s**; SDL takes **1.240 s**.
SDL records 79 samples / 78 updates, 22 occluded samples / maximum 150 hidden
pixels, selection/right-click, no trails, bypass, clipping and pan return. Its
occluded PNG was visually inspected. It checks the existing crossing runtime,
not this unwired helper or original whole-frame parity; the app remains arm64.

Private start/attempts/closing notes record continuation accounting; full inherited
delivery elapsed and exact build/pilot/normal-test driver times are unavailable.
The initial pilot stopped at an uninspected no-stencil loop. Inspection expanded
only this new fixture's code allowlist. The second stopped at the known raw
converter scratch write; its exact four-byte output was declared. The third
exposed a real nontrivial-barrel transform mismatch, corrected from the original
call/stack ordering described above. The final ten-result pilot and subsequent
fresh full suite pass. Earlier frozen sources/receipts remain unchanged.
No worker, evidence cache, gameplay repair, instruction patch or source/system/
Windows change occurred. Contended timings are not FPS measurements.

Next bind this complete shadow child to the existing complete Unit/world root
with a fourth independent index sharing its supplied pool, then finish caller/
runtime integration and the current-cell-light crossing acceptance. Full actor/
pool ownership, pitch invalidation, failure/eviction/lifetime, ramps/status,
decorations, scheduling/camera/fog/UI and whole-frame parity remain open. Only
Apple Silicon macOS is tested. This is locally verified recovery, not independent
acceptance; full base RA2 then YR remains active and incomplete.
