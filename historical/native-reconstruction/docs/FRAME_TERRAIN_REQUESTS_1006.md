# Queued terrain/visibility requests and alpha refresh

Complete6A3EF0 now consumes the Renderer’s existing dirty regions and actual
Boot Camp Cell queue through an explicit synchronous seam. Complete4110B0 clears
its existing alpha plane, including retained nonzero scroll offsets. This is a
remaining phase1 dependency of6A45A0 before adopting the original frame protocol
for tutorial structures. It does not schedule a frame, discovery, arrival or an
objective transition. Terrain475520, animation41F1C0 and rectangular6A7820 draw
children remain required explicit services, not implemented pixels or no-ops in
the application loop. No queue reset or surface swap is enabled.

## Exact original evidence

The supplied executable is4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. No public implementation or dependency
was incorporated; original instructions run only in the research oracle.

Complete6A3EF0 is528 bytes/160 instructions, code hash
`cb7b454058168b0d5e9d8586b8722fdae1c4bef46361cba01007a8f04cadbe47`.
507 complete original roots execute actual475D60 center,6A27A0 projection and
41FDF0 intersection, with named supplied height/terrain/animation/rectangle/alpha
services. They compare ordered Cell/count/backing/flag queries, exact forwarded
arguments and rectangle identities, plus final fields, slots, both dirty backings
and unused tails. Original code, return/stack/callee-saved and unrelated arena
checks pass. These are authored probes, not original-game observations.

A nonzero full-argument low byte requests the viewport rectangle. Otherwise each
queued Cell queries its center (including its height child), forces Z=0, projects,
then reads current origin and viewport fields with wrapped(-30,-15) offsets.
A live nonnull B263D8 gates475520, which reloads the Cell slot after projection.
41F1C0 is requested afterward even when terrain is absent. Both retain the
original caller clip identity and saved screen point. Cell count is reread after
each visit. Positive first/second edge rectangles follow only for low-byte zero.

Dirty traversal follows even for full redraw. It visits forward using a live
count and retained backing pointer, translates both X and Y by viewport origin,
and intersects with the caller clip. **The translated region is the helper’s
first operand**; wrapped clipping is not commutative. The backing reload and flag
load occur after intersection. Any nonzero flag requests alpha4110B0 by value,
then rectangle6A7820 using a retained copy. Empty intersections are forwarded.
Another backing reload follows that rectangle child and is retained into the
next iteration; the false-flag path retains its preceding flag-load backing.
Neither queue nor any capacity tail is cleared.

Scenarios cover low-byte truth, negative/empty counts, duplicate Cells, full and
partial paths, signed16 Cell extremes, live growth/shrink, replaced backing and
late Cell slot, viewport/edge mutation, nonzero flags and wrapped/empty clipping.
507 roots encounter364 centers/projections,259 terrain requests,364 animation
requests,1,206 rectangle requests and505 supplied alpha calls. These supplied
child calls are not original pixel effects. The projection’s native coordinate
bound now includes all signed16 Cell centers; at8,388,608 the original32-bit
products and sums remain safe. The original signed16 extremes are tested rather
than silently removed from the comparison domain.

## Complete alpha effect

Complete4110B0 is377 bytes/133 instructions, including4111E3..411228 after its
first return. Code hash:
`5ed64ee64c345325d870ae83198edfcc656870a9c1925e28ab8a8635d98d24cc`.
607 complete original sequences compare10,274 ordered pixel stores,1,214 lock
stores, live fields and full backing hashes. Actual stock surface lock/unlock/
format/pitch/width children execute, without patched or redirected instructions.
Each depth and alpha entry remains independently verified. Native byte and word
backings match. Cases include live surface replacement/geometry/offset mutation,
wrapped locks, row/ring boundaries, alignments, zero/negative height and short
spans. The existing607 depth answers retain their own provenance and are replayed.

Alpha shares the readable region-refresh kernel with7761C0, using127 instead of
65535. Both lock and unlock before writes, preserve live surface resolution and
single wraps, and use the original prefix/pairs/conditional-tail span. An aligned
one-word span still writes nothing. Nonnull bounded backing, stock surface
association and supplied initial geometry remain the accepted profile. Invalid
backing/extent, unsupported faults or missing services refuse; no rollback after
already ordered effects is claimed.

## Actual owner composition and boundaries

`Renderer::requestTerrainDraws` borrows the actual Cell queue and its canonical
center/floor query, the same mutable dirty-region vector and existing Tactical
origin. Its alpha child calls `Renderer::refreshFrameAlpha` on the existing alpha
vector, persistent offset and stock lock; no copied queue or parallel plane is
introduced. Other entered drawing children must be explicitly bound by the
caller. The actual owner test records those requests, runs both partial and full
paths after original region preparation and Building drawing, and requires
alpha stores, original ordering/counts, retained colors/depth/queues/tails/locks
and source-owner isolation. Building invalidation itself correctly produces
flag0. The test supplies one flag1 request through the existing recovered6A3020
registration kernel on this same owner; its frame/camera invocation is still
supplied. `registerFrameDirtyRegion` also serves the existing Building
invalidation callback, preserving a single registration kernel. This does not
recover an ordinary flag1 producer. A separate check after actual plane scrolling
requires alpha’s first subsequent store at the retained nonzero offset.

The caller original proof has supplied alpha, while the separate alpha proof
executes the original effect. Their actual-owner composition is current native
integration, not a nested-original whole-frame proof or independent acceptance.
Startup associations, projection height scale and other drawing consumers retain
their existing scope. Original frame0/1/map-callback/2 composition, remaining draw
children and nonzero-offset/base consumers remain open. Do not bind production
frame/sight/arrival/Objective1 scheduling, swap surfaces or reset queues based on
this checkpoint. Both games remain incomplete; only Apple Silicon macOS is tested.

## Build, test, reuse and try

```sh
./build.command
./test.command
build/native/boot-camp-walk-check private/official-1006-probe
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest \
  tests/test_frame_alpha_refresh.py tests/test_frame_terrain_requests.py
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/NEW-alpha.audit.json \
  tests/compare_frame_alpha_refresh.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/frame-alpha-refresh-vectors \
  --expectations private/frame-alpha-20261019/fresh-a1/expected.json \
  --report private/NEW-alpha.json
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/NEW-terrain-requests.audit.json \
  tests/compare_frame_terrain_requests.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/frame-terrain-requests-vectors \
  --expectations private/frame-terrain-requests-20261019/fresh-a1/expected.json \
  --report private/NEW-terrain-requests.json
env DEVELOPER_DIR="${DEVELOPER_DIR:-/Library/Developer/CommandLineTools}" \
  build/tools-env/bin/cmake --build build/sanitize --parallel 6
# Substitute build/sanitize runners for sanitizer replays and owner checks.
./run.command --boot-camp-walk
./run.command --boot-camp-walk-smoke-test private/NEW-SDL
```

Choose unused report/audit/capture names. Explicit `--expectations` validates the
original executable/oracle/input/environment/receipt independently from current
native sources and runner. It always executes current native and reports actual
hits/misses. Fresh original scope uses `--output private/NEW` instead of
expectations/report and requires authorized host JIT access. Unicorn is
research/test-only. No runtime executable reads are added.

## Validation and repair record

Alpha’s fresh original/native comparison passed first try. The terrain caller’s
original generation also completed; its initial native run refused a signed16
extreme at the old projection bound. Native trace comparison exposed an omitted
late backing load, then an extra per-iteration backing load, then reversed
wrapped-intersection operands. All three failed audits remain failed at their
actual scope. The valid original expectations are unchanged; repairs rerun only
current native using guarded reuse. No native verdict is cached and no receipt
is relabeled. An initial focused alpha build also caught renamed fixture types;
it remains recorded separately from behavioral comparison. The first actual-owner
check rejected its assumption that Building regions would be flagged. That check
remains failed; the repaired fixture explicitly supplies flag1 through recovered
registration and documents the producer boundary. Renderer consumers/registries
and the already-passing standalone original comparisons were unchanged by that
fixture repair.

Normal/sanitizer each reuse8,567 original answers with zero misses:607 alpha,
507 caller and7,453 retained frame/fill/Building roots. Each also replays424
historical composition answers. Every comparison executes current native; no
unchanged original matrix was regenerated.222 normal/221 sanitizer CTests,
39 focused Python guards, both repaired actual-owner checks and the rebuilt
256-tick SDL walking/input/drawing regression pass. Horizontal GI capture hashes
remain unchanged. Local verification is not independent acceptance.

Original generation took.322s alpha and.551s caller. Initial full builds took
60.674s normal/63.610s sanitizer; the later native owner/app repair build27.878s.
The18.833s sanitizer repair command rebuilt its owner successfully before failing
on the absent SDL app target; a3.358s owner-only confirmation passed. Final owner
checks took9.664s/80.102s. Final normal/sanitizer test entry points8.082s/22.951s,
Python5.298s, rebuilt SDL6.508s. Alpha replay1.452s/.541s; caller replay.587s/.499s;
historical composition8.519s/7.022s. Initial failed owner9.113s and earlier passing
test/SDL costs are retained separately. Concurrent costs are nonadditive. Initial
focused builds, manual inspection/repairs and total milestone wall time were not
measured. Complete commands, reports, source/runner hashes, failed audits and
costs are in `private/frame-terrain-requests-receipt-a1.json` and
`private/frame-terrain-requests-20261019/validation/`.

Next recover the entered475520/41F1C0/6A7820 effects and remaining phase1 drawing
parents, then complete0/1/map-callback/2 on these same owners before scheduling
frames. Preserve the separate genuine sight/arrival and mission-effect gates to
Boot Camp’s first actual objective. No workers, runtime-read expansion, Windows/
transfer/download/system/Xcode/DRM changes or proprietary shipment.
