# Ordinary Building sprite pixels

The explicit Building composition now writes original SHP body/shadow pixels
through the existing renderer's color/depth/alpha planes. It reuses the scenery
pixel kernel with verified Building flags and depth gradients. This is a frame
presentation dependency of Boot Camp discovery/Objective1, not a newly scheduled
lesson or a complete original frame. Base RA2 and Yuri's Revenge remain incomplete;
only Apple Silicon macOS is tested.

## Original evidence

Exact supplied executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. No original instructions are modified.

The inspected complete49EEA0 wrapper is1,275 bytes through ret34 at49F398.
Existing [scenery recovery](SCENERY_1006.md) supplies full surface/selector/raw/RLE
span inspection. The new exact-build verifier records wrapper, compressed surface,
selector and four body/shadow span ranges plus the gradient-table fingerprint.
It does not infer an address displacement or YR equivalence.

Ordinary flags6E00/6E01 retain the extra2000 bit. In this bounded profile it
selects the same body/shadow raw/RLE blitters as4E00/4E01. The original wrapper
stores argument6, the ordinary fixed zero word, on converter17C. Earlier wording
here incorrectly identified it as drawing flags. The subsequent
[converter-word proof](SPRITE_CONVERTER_WORD_1006.md) verifies that store and joins
it on the selected native converter. This pixel-only checkpoint's receipts stay
unchanged; consumers, construction, lifetime and actual selection remain open.

Gradient0 is not a synonym for shadow. A body can use it while retaining normal
alpha/light color lookup. Its depth starts from the wrapped16 value32768 minus
the clipped top row, plus Z adjustment, then decrements once per row. Gradient2
retains the existing raw-versus-RLE clipped/crop-height phase and thirds stepping.
Shadow uses gradient0 and RGB565 half-darkening. Source zero stays transparent;
depth uses a strict comparison, with original unsigned16 destination stores.
The shared kernel keeps crop/canvas placement, clip origins and alpha shade lookup.
The terrain facade still refuses the newly entered Building-only profiles.

384 original calls execute complete49EEA0 and actual raw/RLE surface/spans against
synthetic valid two-frame SHPs and RGB565 palettes/planes. They cover both formats,
terrain and Building flags, body gradients0/2, shadow0, eight location/clip cases,
four light/Z cases, transparency and mixed accepting/rejecting depths. Color and
depth planes match by SHA256; stack/registers, immutable inputs, bounded writes,
converter allocations and lock state retain the inherited fixture audits.
These are whole surfaces for the selected input corpus, not whole game frames.

The first384-case proof used all-zero optional tails and remains unchanged under
`private/building-pixels-20261019/fresh-a1/`. The actual ordinary parent forwards
nonzero198/446 offsets even with optional depth image null. A second fresh proof
uses null image, frame3 and offsets198/446 on all384 original calls:
`private/building-pixels-20261019/fresh-a2/expected.json`. Its color/depth answers
also equal the first proof. Inspection shows those words are unused in this null
branch. The native binding now preserves them; it does not silently clear them.
A nonnull optional depth image remains refused until its original children and
actual backing are joined. Named native flags are not stripped to pass a guard.

## Existing owners and supplied boundaries

`blitOrdinarySpriteFrame` is the one shared pixel implementation.
`blitTerrainFrame` retains its original narrower domain and delegates to it.
`Renderer::drawBuildingSpritePixels` accepts the same renderer surface identity,
existing selected House converter and exact loaded SHP identity. Unsupported
association, nonzero fixed word or nonnull optional depth image refuses. Actual
color/depth/alpha planes stay on Renderer; no parallel framebuffer or actor/image
cache was added. The host `drawMap` inspection reset now initializes all three
current planes from its existing ground planes before explicit overlays. This
reset/presentation policy is supplied, not original frame consumption.

The existing actual-owner test composes static -> visibility -> ordinary ->
6D1510 -> shared pixels for the loaded Objective1 Building images, including
auxiliary gradient0, live D8/negative ambient, clones and source destruction.
It requires visible pixel writes, not only successful/empty requests. Its earlier
parent-only request assertions remain, with supplied mode/converter/House/timer
leaves; the pixel subcheck explicitly supplies a null optional depth image.
Source snapshots and Cell redraw queues remain unchanged.

Converter association, startup/frame choices, camera/presentation/reset and the
other named child services remain supplied. There is no production frame, sight,
arrival or Objective1 scheduling, new runtime executable read, runtime original
execution, Windows/system/Xcode/DRM action, public code/dependency or proprietary
shipment. Existing supplied GI animation/facing/phase/palette boundaries remain.
Local validation is not independent acceptance.

## Preserve old original answers

Normal and sanitizer each reuse384 new pixel answers plus420 scenery and808 prop
answers:1,612 hits/zero misses, always executing current native. The scoped
`compare_scenery_current.py` adapter validates each original receipt, all original
Python/mapping sources, render input and every captured asset/synthetic fixture
byte. It retains historical exporter provenance instead of claiming that the
new executable is the old exporter. Because all exported input bytes are captured
and independently matched, it neither reruns the exporter nor regenerates
unchanged originals. Missing/changed original inputs refuse. Current runner and
source closure are identified in the report/audit. Old receipts stay untouched.
This adapter applies only to the two named, fixed historical families.

## Commands

```sh
./build.command
./test.command
build/native/boot-camp-walk-check private/official-1006-probe
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest \
  tests/test_building_sprite_pixels.py tests/test_scenery_current.py \
  tests/test_techno_sprite.py
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/NEW.audit.json \
  tests/compare_building_sprite_pixels.py \
  --exe private/official-1006-probe/game.exe --native build/native/scenery-vectors \
  --render-data private/derived/render-data.bin \
  --expectations private/building-pixels-20261019/fresh-a2/expected.json \
  --report private/NEW.json
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/NEW-LEGACY.audit.json \
  tests/compare_scenery_current.py \
  --exe private/official-1006-probe/game.exe --native build/native/scenery-vectors \
  --render-data private/derived/render-data.bin \
  --expectations private/migration/supplied-ra2-1006/scenery/expected.json \
  --report private/NEW-LEGACY.json
./run.command --boot-camp-walk
./run.command --boot-camp-walk-smoke-test private/NEW-SDL
```

Substitute the props expectation path for the808-case historical replay. Use new
private audit/report/SDL paths. Build sanitizer with
`env DEVELOPER_DIR="${DEVELOPER_DIR:-/Library/Developer/CommandLineTools}" build/tools-env/bin/cmake --build build/sanitize --parallel 6`,
then substitute its runner and run its CTests/actual owner check. Fresh generation
uses a new `--output private/NEW` instead of expectations/report and requires
research-only Unicorn execution. Existing GI play is available; Building pixels
remain an explicit owner-test composition rather than a scheduled application
frame. Next join the actual converter state/selection and optional depth image
before removing those boundaries, then finish the outstanding frame children.

## Validation and costs

The first actual-owner check correctly rejected the overly strict all-zero tail
profile. Subsequent focused diagnostics identified198/446; their logs retain the
refusal. One diagnostic compile failed because the helper accepted const char*
rather than std::string; its stale-binary run is not accepted as current evidence.
The original fixtures never had a native/original pixel mismatch. All attempts,
current build/native/sanitizer/regression/SDL costs and unavailable measurements
are preserved in `private/building-pixels-receipt-a1.json`. Concurrent command
costs are nonadditive. No unchanged original matrix was regenerated.

Final validation:214 normal/213 sanitizer CTests,11 focused Python guards, normal/
sanitizer actual-owner tests and SDL256ticks pass. Both horizontal captures match
the prior inspected captures byte-for-byte. Final generation4.651s; final normal/
sanitizer builds37.40s/40.75s, owners5.23s/77.53s, normal test.command4.49s,
sanitizer CTests20.10s and SDL7.07s. Scoped native rebuild11.88s and first rejected
owner4.79s are also measured. Earlier builds/diagnostic repair and manual edit/
inspection wall times were not instrumented. Original and current replay costs
remain separate in the receipt; no claim is made that these sum to total elapsed.
