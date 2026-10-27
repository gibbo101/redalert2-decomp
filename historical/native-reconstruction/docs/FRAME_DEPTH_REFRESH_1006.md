# Depth refresh on the existing frame plane

The shared region kernel now also recovers complete alpha4110B0; see
[FRAME_TERRAIN_REQUESTS_1006.md](FRAME_TERRAIN_REQUESTS_1006.md). Original depth
and plane proofs below retain their independent scope and are replayed against
current native; no frame scheduling follows from the explicit composition.

The explicit [plane clear/scroll seam](FRAME_PLANES_1006.md) now owns persistent
Renderer depth/alpha offsets and bases; this consumer borrows those fields.
The original answers below retain their recorded field/input provenance; the
former actual-owner association started at zero scroll. Production frame
scheduling and other nonzero-scroll consumers remain open.

Complete7761C0 now refreshes the Renderer’s existing depth vector beneath the
explicit6A33F0 region-preparation seam. This removes another entered frame child
needed to present the original Boot Camp structures after genuine redraw requests.
It does not finish the outer6A45A0 dispatcher, terrain drawing, sight/discovery or
an objective transition. Base RA2 and Yuri’s Revenge remain incomplete; only
Apple Silicon macOS is tested.

## Original evidence

Exact supplied executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Complete7761C0 spans371 bytes/133
instructions, SHA256`b85f7075334ed2e5f6ead801066f31408c16e09ccb6746ed07ced3848cf83f1b`.
Its final block follows its earlier return; the verifier includes that block and
the backedge at776331. Actual stock411370/4112F0/4113B0/4113C0/4112C0 execute,
with the original BSurface vtable associations checked. No child instruction is
intercepted or patched. Original execution is confined to the research oracle.

607 original sequences compare ordered surface identity/lock/format/pitch/width/
unlock calls, wrapping lock stores, depth-field reads, all2/4byte pixel stores,
final fields and the complete2,048byte backing hash. Cases include every initial
alignment, both sides of a ring split, exact-end equality, zero widths/nonpositive
heights, small spans, multiple row wraps, distinct lock owners, live surface and
geometry changes, saved-versus-late buffer/pitch inputs, signed coordinates and
wrapped stock pitch products. Both byte and numeric-word host backing are checked.
Caller stack/return/callee-saved/code/vtable and unrelated arena guards pass.
Fixture entry mutations are authored probes, not original-game observations.

## Recovered behavior

The child reads live surface14 and locks at the incoming X/Y. It saves the lock
return, rereads surface14 and unlocks that receiver **before any pixel write**.
Thus a service mutation can leave different lock counters incremented/decremented.
The ordinary facade reuses the existing stock lock, early format/saved allocation,
late pitch/width and wrapping unlock kernels; it does not introduce another lock
implementation.

After unlocking, add owner10 to the saved lock result with wrapping32. Compare
against end1C as unsigned; if greater or equal, subtract bytes20 exactly once.
Only then test signed rectangle height. A nonpositive height returns after those
calls/reads. Width is not a clipping bound or early empty-rectangle test.

Each row compares `start+width*2` against the saved end. Equality enters the split
path. The first span takes unsigned `(end-start)>>1`; the second takes the
remaining width at live begin18. Within each span, **bit1** of the address gates
a first word store. Then write dword pairs and a final word only if the original
pair loop established a nonnull tail pointer. An unprefixed one-word span
therefore writes nothing. Preserve that omission, including either side of a
split; do not replace it with an ordinary rectangle fill. Odd byte addresses
retain the original bit test and little-endian partial-word writes.

After every row, including the last, read live rowWords28, add twice its wrapped
value, reload end1C and subtract live bytes20 once if needed. This is not a modulo
operation or a repeated wrap loop. Initial allocation, geometry, scroll offset
and original surface construction remain supplied.

Native offsets normalize one nonnull common backing allocation with a four-byte-
aligned logical origin (prefix offsets retain other alignments), without truncating
host pointers. A logical offset0 remains a valid nonnull original address. A null
lock still invokes Unlock, then refuses outside the accepted profile; original
null/fault behavior is not recovered. Negative entered widths, widths/heights over
1,048,576, products over67,108,864, spans over1,048,576, ambiguous backing and
out-of-backing stores refuse. Nonpositive heights return before width checks.
These are host safety limits, not original malformed-input compatibility. Child
bindings/backing must remain alive synchronously; tracing is observational.

## Actual owner composition

`Renderer::refreshFrameDepth` borrows the current depth_ vector and renderWidth_,
with one supplied persistent software lock counter. Its bounded association uses
zero scroll offset, begin0/end equal to that vector’s bytes and actual raster row
width. No parallel plane, original executable read, runtime-code execution or
frame-loop call was added. The overload of `Renderer::prepareFrameRegions`
without an explicit depth callback binds this recovered child. The prior explicit
callback profile remains available for focused caller checks.

The existing actual-owner test queues a real GI Cell, invalidates real Building
regions, exercises the full-byte bypass, then uses recovered region clipping and
depth refresh. It requires changed depth words to become65535, a positive refresh
count and the persistent lock to return to zero. The following ordinary Building
requests run with full redraw disabled **without drawMap restoring the plane**;
the existing static/visibility/ordinary/Techno/converter/auxiliary-image chain must
write visible depth-bound pixels. Offscreen region removal retains Cell slots,
capacity tails and source/clone isolation. Terrain4754B0 remains a supplied recorder.

This native composition is separate from original expectation provenance: the
607 proof roots at7761C0; the retained403 parent answers still use their supplied
depth service and do not become a newly rooted nested original frame proof.
No whole-frame fidelity, original startup/surface association, independent
acceptance or ordinary objective completion follows. Production frame/sight/
arrival/Objective1 scheduling and queue-reset tails remain off.

## Commands and supported reuse

```sh
./build.command
./test.command
build/native/boot-camp-walk-check private/official-1006-probe
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest \
  tests/test_frame_depth_refresh.py tests/test_frame_region_preparation.py
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/NEW.audit.json \
  tests/compare_frame_depth_refresh.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/frame-depth-refresh-vectors \
  --expectations private/frame-depth-refresh-20261019/fresh-a2/expected.json \
  --report private/NEW.json
./run.command --boot-camp-walk
./run.command --boot-camp-walk-smoke-test private/NEW-SDL
```

Use unused private audit/report/capture names. Explicit `--expectations` checks
executable/oracle/input/environment/receipt identity and always reruns current
native plus guards, reporting actual reuse hits/misses. Never cache native verdicts.
Fresh scope substitutes `--output private/NEW` for expectations/report. Original
execution needs the authorized host JIT context; Unicorn remains research/test-only.
For sanitizers substitute build/sanitize runners/CTests/actual-owner checks, building
with `env DEVELOPER_DIR="${DEVELOPER_DIR:-/Library/Developer/CommandLineTools}" build/tools-env/bin/cmake --build build/sanitize --parallel 6`.
Retained comparison commands remain in their subsystem notes; unchanged original
matrices are reused, not regenerated.

The first original attempt incorrectly applied its pixel-write observer to legal
stack writes; the shared stack/write audit was already correct. Restricting that
observer to the research arena fixed the fixture. Its failed audit remains at
`private/frame-depth-refresh-20261019-fresh-a1.audit.json`; fresh-a2 is accepted.
No original/native behavior mismatch occurred. Final checks/costs follow below.
Local verification is not independent acceptance. No workers, Windows/transfer/
download/system/Xcode/DRM change, public code/dependency or proprietary shipment.

Next recover terrain4754B0 on the same actual Cell/terrain/pixel owners, then
remaining entered6A45A0 children under0/1/map-callback/2. Do not enable isolated
queue clearing or substitute phase3. Genuine sight/arrival and mission action
children remain separate gates to the first playable objective transition.

## Next terrain child inspection

Private inspection finds complete4754B0 forwards signed Cell10C and signed
Cell11B, the caller point and a by-value clip, fixed scalar arguments and live
global receiver/image/surface identities to52C230. These effects are not terrain
completion: inspect/recover the actual52C230 child and bind its real tile/image/
converter/pixel owners before adopting the callback. Do not implement a no-op
wrapper or use the existing host terrain cache as proof of the original child.
This is an inspection lead, not a verified interpretation of those globals.

## Current validation and costs

Normal/sanitizer each explicitly replay607 new and3,974 retained original answers:
**4,581 hits/zero misses per build**, always current native.218/217 CTests,
20 Python guards, both actual-owner checks and SDL256ticks pass. All607 depth
roots execute each actual stock child607 times;10,207 ordered depth stores and
1,214 wrapping lock stores match. No unchanged original matrix was regenerated.
Horizontal GI captures retain the prior hashes byte for byte; this is regression
coverage, not original frame-fidelity evidence.

Original generation.315s; builds62.90/60.39s, actual owners9.21/81.80s,
normal test.command8.20s/sanitizer CTests23.10s, Python guards3.33s, SDL6.86s.
Per-comparison/replay costs and source/input identities remain under
`private/frame-depth-refresh-20261019/`; receipt:
`private/frame-depth-refresh-receipt-a1.json`. Concurrent costs are nonadditive.
First kernel-only build, manual inspection/repair and total milestone wall time
were not measured. Local validation is not independent acceptance; both games
remain incomplete and the full reconstruction goal remains active.
