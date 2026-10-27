# Ordinary sprite auxiliary depth pixels

The explicit Building composition now consumes the renderer-owned, normalized
BUILDNGZ.SHP through the shared raw/RLE pixel kernel. This unblocks a Building
presentation dependency of Boot Camp discovery/Objective1. It does not schedule
Building frames, sight, arrival or mission progress. Both games remain incomplete;
only Apple Silicon macOS is tested.

## Evidence and recovered behavior

Exact supplied executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity are distinct. The driver fingerprints complete49EEA0,
4350C0, selector and four raw/RLE body/shadow spans plus the gradient table.
Original instructions execute unchanged in the research fixture, never the app.

The wrapper adjusts offsets by the main canvas halves/crop origin and auxiliary
crop origin. It intersects the main crop-local bounds with the shifted auxiliary
bounds using the existing complete41FDF0 null-adjustment kernel. An empty
intersection or out-of-range auxiliary frame draws no pixels. The raw path uses
this intersection but consumes no auxiliary bytes. Its depth phase remains the
existing raw surface phase.

The RLE path instead starts a byte pointer at the adjusted auxiliary offset plus
host clip displacement, advances it by auxiliary crop width each row, and skips
the null-auxiliary gradient correction/row stepping. Gradient2 retains the
wrapped16 base from the intersected crop height and unclipped destination top;
gradient0 retains the clipped-top base. Both remain constant across rows while
auxiliary backing is present. Each nontransparent source pixel subtracts the
**signed8** auxiliary byte from the signed candidate before strict comparison
against the unsigned16 destination. Accepted depth stores narrow to16 bits.
Body color still uses alpha/light lookup; shadow still halves RGB565 color.

The RLE left skip has a distinct zero-run boundary effect: if skipping consumes
beyond the left edge, destination/depth/alpha pointers advance by that excess,
but the auxiliary byte pointer does not. The SHP reader now retains encoded row
boundaries alongside decoded pixels, so the one shared kernel preserves this
behavior even when adjacent encoded runs have identical decoded zeros. It does
not infer original run boundaries from decoded pixels.

480 complete original calls compare SHA256 of both full color/depth planes:
raw/RLE, body gradients0/2, shadow0, eight location/clip cases, zero/mixed depth
acceptance, brightness, signed bytes0/1/127/128/255, multibyte zero runs, empty
intersection and invalid frame.48 calls use the actual normalized BUILDNGZ data;
its source and normalized payload hashes match the separately verified initializer
in [BUILDING_DEPTH_IMAGE_1006.md](BUILDING_DEPTH_IMAGE_1006.md).
Stack/register, immutable source/auxiliary/converter/plane inputs, heap canaries,
allowed writes and existing surface lock audits remain active. Allocator/free
children remain supplied; this is pixel-result evidence, not a complete ordered
wrapper store/allocator/lifetime proof or a whole original frame.

## Native ownership and boundaries

`SpriteDepthInput` borrows an immutable decoded image. BuildingSpriteRequest and
TechnoSpriteBlit carry an explicit host identity separately from their unchanged
32-bit diagnostic words. The owning composition binds the actual renderer image
at the existing ordinary -> Techno seam. The Techno body preserves that identity;
shadow emits no auxiliary image. No pointer is truncated to32 bits, and no second
pixel buffer, image cache or renderer is introduced.

Renderer checks the supplied identity against its current shared owner before
consuming it, rejecting foreign/missing/contradictory associations. The actual
Boot Camp owner test preserves the former null-depth composition and additionally
runs the depth-bound main/shadow composition on actual loaded Structure/Type/SHP,
House converter and renderer planes. It requires visible depth-bound body writes.
Startup/global-token association and explicit invocation remain supplied host
bindings. Renderer preparation/reload retains the prior immutable-view lifetime
and source-immutability checks. These native checks are separate from original
expectation provenance.

The accepted auxiliary backing is raw format1 with bounded decoded geometry and
nonnegative adjusted origins. Negative origins can produce original reads before
the frame payload and remain refused; compressed auxiliary images, allocation
failure/fault semantics and other drawing profiles remain unrecovered. The main
raw/RLE profile and old terrain facade retain their prior guards. Existing GI
orientation/animation/phase/palette/layering and15Hz scheduling are supplied.
No production frame/sight/arrival/Objective1 scheduling or runtime executable-read
expansion, Windows/system/Xcode/DRM action, download, worker or proprietary shipment.

## Commands and reuse

```sh
./build.command
./test.command
build/native/boot-camp-walk-check private/official-1006-probe
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest \
  tests/test_sprite_depth_pixels.py tests/test_building_depth_image.py \
  tests/test_sprite_selection.py tests/test_sprite_converter.py \
  tests/test_building_sprite_pixels.py tests/test_scenery_current.py
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/NEW.audit.json \
  tests/compare_sprite_depth_pixels.py --exe private/official-1006-probe/game.exe \
  --native build/native/scenery-vectors --render-data private/derived/render-data.bin \
  --asset private/sprite-depth-20261019/buildngz-source.shp \
  --expectations private/sprite-depth-pixels-20261019/fresh-a2/expected.json \
  --report private/NEW.json
./run.command --boot-camp-walk
./run.command --boot-camp-walk-smoke-test private/NEW-SDL
```

Use new report/audit/SDL paths. Reuse original answers explicitly and always run
current native. Sanitizer uses the same replay with build/sanitize's runner,
CTest and its actual-owner check. Build with
`env DEVELOPER_DIR="${DEVELOPER_DIR:-/Library/Developer/CommandLineTools}" build/tools-env/bin/cmake --build build/sanitize --parallel 6`.
Fresh changed-scope generation substitutes a new `--output private/NEW` for
expectations/report. Unchanged initializer/selector/converter/Techno/pixel/scenery/
prop answers retain their original provenance and are replayed, not regenerated.

The384-case synthetic proof remains at fresh-a1. Adding actual data and invalid
frames required fresh-a2; it does not relabel the earlier scope. A sandboxed JIT
probe terminated before producing evidence; the authorized isolated research
probe ran successfully. One owner-test compile attempt assigned a request with
reference members and failed; no stale owner binary is accepted for that attempt.
An initial ad hoc refusal check used the wrong token indexes; its broad error check
is rejected as compressed-backing evidence. The corrected normal/sanitizer checks
require each exact refusal message. No original/native pixel mismatch occurred. Costs and final checks are recorded
in HANDOFF and the private receipt; local verification is not independent acceptance.

Next finish the remaining original Building frame children/ordinary frame owner
binding before scheduling these pixels. Keep genuine sight/arrival/Objective1
conditions and original lesson effects as explicit remaining work; depth-image
success does not imply tutorial progression.

## Current validation and costs

Normal/sanitizer each replay480 auxiliary,390 initializer,2,430 selector,288
converter-word,832 Techno,384 prior pixel,420 scenery and808 prop answers:
6,032 original hits/zero misses per profile, always current native.215/214 CTests,
23 Python guards, both actual-owner checks, four exact auxiliary-profile refusals
and SDL256ticks pass. Left/right GI captures retain the prior inspected hashes.
No unchanged original corpus was regenerated. Prior synthetic384 proof remains
at its own scope; only the expanded480 scope generated new answers.

Expanded original generation6.187s; final normal/sanitizer builds53.07s/53.84s,
owners8.88s/81.79s, test.command7.69s/sanitizer CTests23.54s, SDL7.06s. Current
auxiliary replay13.36s/13.20s; retained pixel/scenery/prop replays10.66/9.66/31.65s
and10.38/10.50/35.74s. Other focused replays are each.38..3.19s. Concurrent costs
are nonadditive. Initial/failed builds, manual inspection/repair and overall
milestone wall time were not instrumented. Receipt:
`private/sprite-depth-pixels-receipt-a1.json`. Local verification is not independent
acceptance. Build/run/test/comparison commands and all remaining limits are above.
