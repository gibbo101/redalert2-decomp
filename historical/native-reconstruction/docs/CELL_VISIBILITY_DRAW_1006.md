# Cell shroud and fog alpha drawing

Complete475520,474260 and474510 now compose on the existing mutable Boot Camp
Cells and Renderer alpha plane through explicit synchronous calls. This finishes
one entered6A3EF0 child needed by phase1 of the original frame protocol, which in
turn is needed for tutorial structure presentation. It does not schedule frames,
sight, arrival, discovery or Objective1. Animation41F1C0, rectangular6A7820 and
other entered phase1 effects remain open before full0/1/map-callback/2 composition.
No surface swap or queue reset is enabled.

## Original evidence

Target: user-supplied4,485,392-byte executable, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. The verifier fingerprints before using
addresses and checks full instruction spans and the stock alpha vtable.

| Entry | Bytes/instructions | SHA256 |
|---|---|---|
|475520|172/66|`6c5e2e9323d4a623c3f928a805e8ad3b7d8881feba7033c21c9d2dcd0bd6e23f`|
|474260|675/241|`561fb32902d53582c3a77c6856d721c8ed0a52d7420f1c822ce9edb4d1898aa9`|
|474510|794/260|`50e541422a3278e3b91b785942bade632411a2c107303ad27c7476d6cc9394b9`|

1,180 complete original root calls compare284,169 ordered alpha-word stores,
2,236 stock lock stores and1,088 Cell byte stores, plus final backing hashes,
Cell coordinates, mask bytes, scenario/House/cache fields and caller ABI. The
original runs actual nested raster and stock411230/lock/unlock/format/pitch/width
children. Mask6A8D40 and loader5956C0 are named **supplied services** in this proof.
Separate128 complete mask answers are replayed; native actual-owner composition
binds that recovered mask to the actual private result table. This is not a
nested-original6A3EF0/whole-frame proof or an original-game observation.

The parent stores primary120 before shroud drawing, then recalculates using the
live point and Tactical owner for secondary121. Both drawing frame arguments
sign-extend the low byte, mapping-2 to15 and-1 to0. Secondary is stored even if
fog is skipped. Fog requires current scenario bit1000hex and current House13D
zero, read after the second mask. The screen/clip identities are forwarded intact.
Probes cover late point/scenario/House mutations and low-byte/raw-byte gates.

Shroud publishes its lazy flag before loading SHROUD.SHP then FOG.SHP. Scenario
bit1000 selects the latter cache. Fog has a separate lazy flag/cache. Loader/heap
internals, cache startup and ownership association remain adapters. The actual
files were resolved read-only through the existing archive inspector from
`private/official-1006-probe/ra2.mix`; both are88,712 bytes:

- SHROUD.SHP: `9818f7e2685fb1e8ed75ceff568aaf5d36350c747cbd4f30856458bba12e4964`
- FOG.SHP: `b8e3640435140041f0ac3d4ff18ad99b035a2292b685a2fd89c64bf1cc55e73f`

Both expose96 header frames; the288 actual-asset probes exercise all48 populated
frames in shroud, shroud-with-fog-data and fog modes, fast and ring-wrapped.
The raster reads signed16 frame bounds and raw byte payloads at the stored file
offset. It deliberately does not use the general authored SHP decoder. Invalid
frame fallback bounds remain supplied zero. Unsupported null/faulting payloads,
truncated headers/backing, ambiguous backing and geometry outside the bounded
nonoverflowing profile refuse; this is not malformed-original-input support.

The pixel path preserves the original preliminary clipping comparisons, source
crop/row gaps, viewportY subtraction, address lock/unlock-before-write, retained
scroll offset and single ring wraps. Shroud's wrapped path skips byte254; its
fast path compares against global79DAD0 (stock254). Fog skips bytes above127.
For other pixels, destination127 takes the source directly; otherwise it stores
low16(max(0,destination+source-127)). Byte and numeric-word backings agree.
Shroud's fast row and pixel loops are do/while: an entered empty clip can write
one pixel. Fog and wrapped shroud test height first. Keep these paths distinct.
Alpha views/read telemetry and pixel traces are synchronous and observational;
concurrent mutation during pixel writes is outside the accepted host profile.

## Actual owners and limitations

`BootCampVisibilityWorld::drawCellVisibility` resolves its existing mutable Cell,
borrows the actual table/shared fallback/mask results and retains actual query
and fallback effects. It reads the existing scenario and current House. Both
children call `Renderer::drawVisibilityMask`, which owns immutable raw asset
backing and uses the existing alpha vector, offset and stock lock owner. No new
parallel Cell/alpha world or runtime executable read is introduced.

The actual-owner test binds this child below existing queued6A3EF0 requests:
actual Cell center/projection -> both actual masks -> actual alpha stores.
It requires two mask queries per Cell, positive pixel stores, unchanged colors/
depth/queues/source owner and no discovery production. A foreign identity refuses.
Day1 startup has fog disabled; a clone explicitly supplies bit1000 and a screen
point to exercise fog-enabled composition while preserving its source world.
That flag/point are test inputs, not recovered fog scheduling or objective success.

Remaining startup/cache/global associations, normal frame invocation, rectangular
visibility traversal, animation drawing, frame surface operations and other
phase1 children keep their prior boundaries. Genuine sight/arrival scheduling
and mission children remain separate gates to Objective1. Screenshots/native
self-consistency do not establish original presentation fidelity. Both games are
incomplete; only Apple Silicon macOS is tested. No workers, public authored code,
dependency, proprietary shipment, Windows action, transfer, download, system,
Xcode, DRM change or runtime executable-read expansion was added.

## Build, test, reuse and try

```sh
./build.command
./test.command
build/native/boot-camp-walk-check private/official-1006-probe
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest \
  tests/test_cell_visibility_draw.py
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/NEW-visibility-draw.audit.json \
  tests/compare_cell_visibility_draw.py \
  --exe private/official-1006-probe/game.exe \
  --assets private/cell-visibility-draw-20261019/assets \
  --native build/native/cell-visibility-draw-vectors \
  --expectations private/cell-visibility-draw-20261019/fresh-a1/expected.json \
  --report private/NEW-visibility-draw.json
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/NEW-mask.audit.json \
  tests/compare_cell_visibility_mask.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/cell-visibility-mask-vectors \
  --expectations private/boot-camp-20261018/cell-visibility-mask-fresh-a1/expected.json \
  --report private/NEW-mask.json
env DEVELOPER_DIR="${DEVELOPER_DIR:-/Library/Developer/CommandLineTools}" \
  build/tools-env/bin/cmake --build build/sanitize --parallel 6
# Repeat comparisons/owner with build/sanitize runners; no SDL target there.
./run.command --boot-camp-walk
./run.command --boot-camp-walk-smoke-test private/NEW-SDL
```

Choose unused audit/report/capture names. `--expectations` explicitly validates
original executable, oracle/input/assets/environment and receipt identities,
then always runs current native and reports actual reuse hits/misses. A fresh
original run substitutes `--output private/NEW` for expectations/report; Unicorn
is research/test-only. The asset argument names privately extracted, hash-checked
original bytes; it is not a download or public fixture. Walking remains the
existing playable mode; the new alpha seam is intentionally unscheduled.

## Validation and repair

The initial instruction verifier incorrectly counted the final parent RET's
length; fixed before original generation. The first build caught a missing trace
type include. The first complete original generation succeeded, but its native
comparison exposed shroud's entered empty-clip do/while behavior. That failed audit
is retained. Only native code changed; all valid original answers were reused
unchanged. Four evidence guards cover domain, exact executable, receipt/scope and
native-only reuse/original invalidation. Native guards cover missing services,
lazy flag publication before refusal, bad backing/payload/header and address.

Validation totals/costs and delivery identity are recorded in HANDOFF and
`private/cell-visibility-draw-receipt-a1.json`. Private logs retain the failed
attempts and successful guarded replays. Local checks are not independent
acceptance. Next recover41F1C0/6A7820 and remaining phase1 children, then bind
complete0/1/map-callback/2 on these same owners before production frame/reset
wiring. Do not replace genuine sight/arrival or mission effects with a draw call.
