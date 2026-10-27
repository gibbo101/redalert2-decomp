# Frame region preparation on shared queues

Current native composition now binds recovered depth7761C0; see
[FRAME_DEPTH_REFRESH_1006.md](FRAME_DEPTH_REFRESH_1006.md). The403 original caller
answers below retain their supplied-depth scope. Terrain and scheduling remain open.

Complete6A33F0 now prepares the Renderer’s existing dirty-region queue and visits
the actual Boot Camp Cell queue through an explicit synchronous seam. It translates
and clips regions, removes empty entries in reverse order, requests depth refresh
for positive regions, then requests the entered per-Cell terrain pass. This is a
required first child of phase1 in6A45A0, on the path to presenting Objective1’s
structures under the original frame protocol. It does not complete that dispatcher,
schedule sight/discovery, draw its named child effects or advance a lesson.

## Original evidence and behavior

The supplied executable is4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Complete6A33F0 is626 bytes/188 instructions,
code SHA256 `626244b769aa670d18a9298c0cb2c51dde4b2e7df9b794321a8cd6215ac336e7`.
The verifier also pins actual475D60,47D040,453E40,6A27A0,41FDF0,FTOL and the
projection literal. Unchanged original instructions execute only in the oracle.
Original height4706C0, depth refresh7761C0 and terrain4754B0 are supplied services
in this caller proof; the latter two effects are not implemented by this milestone.
The prior floor-height proof remains separate evidence for the existing native
floor kernel used by the actual-owner seam.

A zero full-argument low byte saves the dirty count once and visits entries in
reverse, reloading backing before each copy and each four-word result store.
Translation wraps32. Actual47D040 subtracts two equal viewport-origin copies;
453E40 thus builds a **local(0,0,width,height) clip**, even for a nonzero viewport
origin.41FDF0 intersects the translated region against that rectangle.

An empty result is stored before testing the live count. A removable entry first
decrements the count, then shifts all following five-word records, reloading the
backing and live count on each shift. It retains the old capacity tails. A positive
result instead calls depth7761C0 by value. Callback mutations to count, backing,
earlier regions and viewport affect subsequent iterations; the original saved
reverse index remains. Full low-byte nonzero skips the entire region pass.

The caller then reads actual Cell count even for a full redraw. Only a positive
count and zero full byte enter the Cell pass.475D60 loads signed16 Cell coordinates
and forms `x*256+128,y*256+128` while invoking its height child. The caller forces
Z=0 afterward, projects, then reads the current Tactical origin and viewport
origin with wrapped subtraction/offsets(-30,-15). A live nonnull B263D8 gates
4754B0. That branch **reloads the Cell slot** before drawing and forwards the
original clip pointer. Count is reread after every iteration. No Cell queue reset,
D7D clear or outer-frame cleanup occurs here.

403 original sequences compare ordered queue reads, four-word result stores,
count-before-shift, fifth-word flag copies, depth/terrain arguments, Cell center/
projection, supplied mutations and final counts/backing/slots/tails/fields.
Cases include low-byte truth, negative/empty counts, wrapped rectangles/deltas,
nonzero viewport origins, duplicate Cells, live growth/shrink, replaced backing,
late Cell-slot changes and terrain absence. All entered parents/geometry children
are reached. Original caller stack/return/register/code and unrelated arena guards
pass. Region padding is supplied zero; native DirtyRegion preserves its meaningful
flag byte, not arbitrary original padding. The optional native store trace is observational; mutation during a store trace
is outside the accepted profile. Native safety limits remain800 Cells,
128 regions, valid backing and the existing projection domain. INT32_MIN dirty
count refuses its wrapped enormous traversal. These are host limits, not recovered
malformed-input behavior.

## Actual composition and limitations

`Renderer::prepareFrameRegions` borrows frameDirtyRegions_, actual Tactical origins
and the existing CellRedrawQueue. `BootCampVisibilityWorld::redrawCellCenter`
resolves the canonical Cell/shared fallback and reuses mapCellCenterHeight with
that world’s actual map/floor cache. Foreign identities refuse. Callbacks and
rectangles must remain alive for the synchronous call; clones bind their own
center/Cell owners. No parallel registry or pixel buffer was added.

The actual-owner check first queues an actual GI Cell and populates regions via
existing Building invalidation. It checks full-byte bypass, local clipping and
positive depth requests, actual Cell visits with caller clip identity, then
requires positive regions and, with full redraw disabled, composes those regions
through Building requests/static scan/visibility/
ordinary/Techno/converter into visible depth-bound Building pixels. Offscreen
translation exercises reverse empty removal, retained capacity and unchanged
Cell queue/source world. The supplied depth callback records requests; it does
**not** clear the Renderer depth plane. Terrain drawing is also a supplied recorder.
This is a native owner integration check, not a newly rooted original proof of
the complete nested frame, independent acceptance or original-game observation.

Camera/startup/invocation and all remaining outer-frame children retain their
existing boundaries. No production frame/sight/arrival/Objective1 scheduling,
queue-reset tail, runtime executable read, Windows/transfer/download/system/Xcode/
DRM action or proprietary shipment. Base RA2 and Yuri’s Revenge remain incomplete;
only Apple Silicon macOS is tested.

## Commands and reuse

```sh
./build.command
./test.command
build/native/boot-camp-walk-check private/official-1006-probe
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest \
  tests/test_frame_region_preparation.py tests/test_building_redraw_requests.py
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/NEW.audit.json \
  tests/compare_frame_region_preparation.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/frame-region-preparation-vectors \
  --expectations private/frame-region-preparation-20261019/fresh-a1/expected.json \
  --report private/NEW.json
./run.command --boot-camp-walk
./run.command --boot-camp-walk-smoke-test private/NEW-SDL
```

Choose unused private report/audit/SDL names. `--expectations` explicitly reuses
original answers with executable/oracle/input/environment validation and always
executes current native plus guards; it never reuses native verdicts. A fresh
original scope uses `--output private/NEW` instead of expectations/report. Unicorn
needs the authorized host JIT context and is research/test-only. For sanitizers
substitute build/sanitize’s runner, CTests and actual-owner check, building with
`env DEVELOPER_DIR="${DEVELOPER_DIR:-/Library/Developer/CommandLineTools}" build/tools-env/bin/cmake --build build/sanitize --parallel 6`.
Retained requests/scan/visibility/ordinary/Techno/depth comparisons use the explicit
reuse commands from their subsystem notes. Unchanged originals are not regenerated.

The initial inspection script incorrectly specified475D60 as173 bytes instead of
77; fingerprint validation rejected it before original generation. This remains
an inspection-tool failure, not an original/native mismatch. Costs and final
validation are recorded below. Local validation is not independent
acceptance. Next recover depth7761C0 and terrain4754B0 effects on existing owners,
then the other entered6A45A0 children under0/1/map-callback/2. Do not bind isolated
queue clearing or substitute phase3 for the original protocol. Genuine sight/
arrival and mission effect gates remain separate.

## Next-child inspection lead

Private inspection of7761C0 reaches the late block7762EF..776331 after the earlier
return at7762EC. Do not fingerprint/recover only the first linear return. The
caller passes a rectangle by value; the child locks then unlocks its surface
before writing depth words through a wrapped backing interval. Aligned/odd span
and row-wrap paths require original comparison, including very short rows.
This is inspected control flow only, not recovered depth behavior. Reuse actual
Renderer depth storage and existing surface lock/geometry kernels where their
dependencies match; do not introduce a parallel depth plane or treat a standard
rectangle fill as equivalent without verifying the original stores.

## Current validation and costs

Normal/sanitizer each replay403 new and3,571 retained original sequences:
**3,974 hits/zero misses per profile**, always executing current native.
217/216 CTests,16 Python guards, both actual-owner checks and the256tick SDL
input/drawing check pass. The owner test was strengthened after review to require
positive prepared regions and visible pixels with full redraw disabled; both
normal and sanitizer owners were rebuilt/rerun. No unchanged original answer
matrix was regenerated. Horizontal captures retain their prior hashes:
left`b563862e3269a58caabc92c6fb2b76b5d5eadd7753d5fb84ae841c2dd2d8c9a4`,
right`2d0364cb242b80dd7772264bad30d78af519f852dfef17ac6beca59e9b00b674`.
These retained screenshots are regression evidence, not original frame fidelity.

Original generation1.529s. Final test-only strengthening builds41.39/24.80s,
owners5.37/77.87s; earlier recorded builds48.47/55.39s then61.77/41.94s and owners
8.01/80.69s are retained separately. Normal test.command7.50s, sanitizer CTests
19.20s, Python guards3.09s, SDL5.92s. Per-comparison timing and original/native
identities are in `private/frame-region-preparation-20261019/`; receipt:
`private/frame-region-preparation-receipt-a1.json`. Concurrent costs are nonadditive.
The first uninstrumented full build, manual inspection/repair and total milestone
wall time were not measured. Local verification is not independent acceptance;
the full reconstruction goal remains active.
