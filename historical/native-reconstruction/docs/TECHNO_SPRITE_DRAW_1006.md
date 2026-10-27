# Shared Techno sprite parent on actual Building owners

Complete `6D1510` now composes beneath ordinary Building drawing on the existing
Boot Camp Structure, Type and immutable SHP owners. This is a dependency of
Building frame presentation needed for the original tutorial's discovery and
Objective1. It emits complete main/shadow wrapper requests; it does not yet draw
Building pixels or schedule frame consumption, sight, arrival or mission progress.
Base RA2 and Yuri's Revenge remain incomplete. Only Apple Silicon macOS is tested.

## Recovered and verified behavior

The exact supplied executable is4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. No original instructions are modified.

The complete parent is1,979 bytes/602 instructions, ending at its ret3C. Both
five-entry mode jump tables are pinned independently. Preserve the shadow byte
saved before mode64; null-image and mode5 short circuits; raw mask and low-byte
predicates; distinct Building/Infantry/Unit adjustments; saved converter versus
late Cell/Type/House queries; and wrapped32 point/depth arithmetic. The incoming
zero/flags words are unused here and must not be added to the computed flags.

Infantry metadata uses signed SHP count/canvas/crop words and an unsigned frame
index comparison. It reuses the existing inclusive dirty-bound union while
preserving the original ordered global rectangle reads/stores. The body passes
all13 wrapper words plus its saved converter and current surface. Its point is a
private copy, its clip is borrowed. Shadow reads height, flag37C and frame count
again after the body child; body mutations to that local point or shared clip
remain visible. Modes0/1 can add shadow; modes2/3/4 draw only the body. Out-of-range
modes retain preceding child effects and return without drawing through the table.

Actual numeric/getter children joined in the same original execution:

| Entry | Complete bytes/instructions | Behavior |
| --- | --- | --- |
| 4521B0 | 40/11 | Building brightness, D8 bit1 and signed1500 threshold |
| 6D6DF0 / 6D6E00 | 7/2 each | Actor204/205 low bytes |
| 41B410 | 7/2 | Actor170 low byte |
| 6C12C0 / 453C60 | 8/2 and7/2 | Type80 tail dispatch through84 to actor418 |
| 6A2970 / 77F110 | 60/13 and61/20 | Height projection and original FTOL |

Building brightness is distinct from the existing Unit effect: with D8 bit1
clear it retains input; with that bit set, signed input<=1500 adds500, otherwise
subtracts500, using wrapped32 arithmetic. Reusing the Unit rule would be wrong.

832 original/native sequences compare both mode tables, converter initialization/
null/fallback, raw gates, all relevant kinds, signed metadata, width/wrapping,
48 explicit brightness boundaries, null images and eight kinds of child mutation.
Ordered parent reads/stores, every wrapper argument/identity, points/clips and
final fields match. Code, vtables, stack/registers, unrelated arena/global bytes
are audited. Named mode/converter/House/timer/status/Cell/image services and final
49EEA0 remain supplied in this proof; matching requests do not prove pixels.

The first784-case proof used a supplied brightness service. It remains privately
preserved at `private/techno-sprite-20261019/fresh-a1/expected.json` with its true
scope. The new joined-child832-case proof is
`private/techno-sprite-20261019/fresh-a2/expected.json`. New generation was required
because the executed child scope changed; unchanged prior matrices were reused.

## Actual owner composition and limits

`BootCampMissionWorld::drawStructureSprite` binds kind6, live Type418/1386/B48,
Structure204/205/170/D8 and raw height, resolving saved SHP identities on existing
Type backing. It reuses complete `buildingCoordinates` for foundation-center48;
raw88 and the distinct A8 raw-minus128 getter are not substitutes. Supplied
foundation association changes refuse before reusing stale dimensions. New raw
sprite fields are supplied startup, not constructor/writer recovery. Clones copy
those records and resolve callbacks afresh; no duplicate actor/image cache exists.

Other entered children remain required services. Actual Building C8/CC return
null; the unsupported owner-predicate-false branch refuses instead of inventing
an Object/House to feed RTTI. Competing owner callbacks refuse. Null images return
without invoking child services. There is no new runtime executable read,
original-code execution, public dependency or proprietary shipment.

The existing actual-owner check now composes static -> visibility -> ordinary
->6D1510 -> main/shadow requests for both Objective1 Buildings, including auxiliary
layers, signed ambient-32768, live D8, missing/competing services and clone/source
destruction. These are native composition checks with supplied mode/converter/
House/timer/final-wrapper leaves; they are separate from original expectations.

The final wrapper cannot simply reuse the scenery API: that bounded API accepts
4E00/4E01 with body gradient2, while ordinary Building requests carry6E00/6E01
and auxiliary body gradient0. Inspect and verify the actual2000 flag and entered
surface/blitter paths before extending the shared kernel. Never mask the extra
flag or relabel requests as pixels. Other partner/timer, animation454, special
43ABD0 and frame children remain open. Sight/arrival/Objective1 stay unscheduled.

## Build, test and try

```sh
./build.command
./test.command
build/native/boot-camp-walk-check private/official-1006-probe
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest \
  tests/test_techno_sprite.py tests/test_building_cell_light.py \
  tests/test_building_ordinary.py tests/test_building_image_selection.py
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/NEW.audit.json \
  tests/compare_techno_sprite.py --exe private/official-1006-probe/game.exe \
  --native build/native/techno-sprite-vectors \
  --expectations private/techno-sprite-20261019/fresh-a2/expected.json \
  --report private/NEW.json
./run.command --boot-camp-walk
./run.command --boot-camp-walk-smoke-test private/NEW-SDL
```

Use new private report/audit/SDL paths. For sanitizer, build with
`env DEVELOPER_DIR="${DEVELOPER_DIR:-/Library/Developer/CommandLineTools}" build/tools-env/bin/cmake --build build/sanitize --parallel 6`,
then substitute that profile's runner and run its CTests/actual owner check.
For the unchanged Cell-light regression, substitute
`tests/compare_building_cell_light.py`, `building-cell-light-vectors` and
`private/building-cell-light-20261019/fresh-a1/expected.json`.
All documented comparison commands explicitly reuse originals and execute the
current native. Fresh scope generation uses a new `--output private/NEW` instead
of expectations/report. Unicorn is research/test-only. Existing GI walking is
available through ordinary SDL input; this seam enables no new Building pixels.

## Validation and costs

214 normal/213 sanitizer CTests,16 focused Python guards, actual normal/sanitizer
owners and SDL256ticks pass. Normal and sanitizer each reuse832 sprite plus1,004
unchanged Cell-light answers:1,836 hits/zero misses, always current native.
Both horizontal captures were inspected and match the preceding captures byte
for byte. This preserves the supplied GI facing correction; it is no claim of
original Infantry frame fidelity. Final normal build39.09s, normal owner8.74s,
sanitizer owner77.45s, normal test.command7.41s, sanitizer CTests22.10s and SDL7.93s.
The sanitizer build and first integrated build completed successfully but lacked
wall-time instrumentation. Current receipts and measured costs are recorded in
`private/techno-sprite-receipt-a1.json`. Local validation is not independent
acceptance. The original joined generation took1.206s, comparison.071s. Earlier
kernel build11.99s and unconfigured-target failure.23s are retained separately;
no original/native mismatch occurred. Manual inspection/edit/repair and total
turn cost were not instrumented. Concurrent command costs are nonadditive.
