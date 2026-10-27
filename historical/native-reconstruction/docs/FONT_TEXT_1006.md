# Original text drawing and surface binding

`src/render/FontText.hpp` joins complete base `431CC0` to the single verified
`4318E0` glyph kernel and actual `4314B0` measurement. Complete surface binding
`4320B0`, unbinding `432150`, tab-origin setter `4318D0` and caller `432350` are
recovered alongside their actual `432000` intersection and `63CF20` color child.
All278 complete original sequences match native pixels, returns, projected font
state and ordered raster/surface-service events. This remains an unwired rendering
dependency. Message-node drawing, production text and Boot Camp Objective1 remain
incomplete; no visible-text SDL acceptance follows from these checks.

## Target and recovered behavior

Exact supplied executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. The verifier fingerprints the binary
before checking complete instruction ranges, child/caller associations, actual
metric tables and the supplied SetRect import. No public/YR/recomp implementation,
new dependency or runtime executable read was added. Original data stays private.

Text iteration consumes UTF-16 units until NUL or a nonzero character limit.
CR and LF consume that limit but do not draw or reposition the pen. Tabs reach
the existing signed glyph-tab calculation. With reveal0, the text draws without
fading. Nonzero reveal uses a signed ordinal comparison before the current unit:
the last eight admitted units blend the saved packed color toward a supplied
live RGB target. The inclusive factor is low-byte `(9-reveal+ordinal)*31`;
per-channel signed products divide by256 with truncation toward zero. Preserve
16-bit unpack shifts, byte shifts/truncation, dword pack shifts and their masked
counts; this is not host color interpolation or a normalized floating-point fade.
The saved font color is restored on both ordinary and shortened-reveal returns.

The shortened-reveal tail has already fetched the current unit. It measures from
the saved NEXT pointer, excluding that current unit, with no character limit or
width limit. The measurement width output aliases the saved-pointer scratch slot.
The return therefore adds suffix width to current pen X; it does not return an
address. Tests vary the original text address to verify this. Negative reveal
reaches that tail immediately. The original scratch alias is represented by its
ordered semantic result, not a guest stack or host pointer dependency.

Binding calls lock(0,0), stores the returned surface, queries byte pitch, stores
logical `pitch >> 1` in pixels, then queries width and height separately. All-zero
clip words initialize the inclusive full surface bounds, regardless of clipping
flag. Otherwise actual432000 intersects the existing clip IN PLACE. Late height
service changes are consumed by the following clip test. Unbinding calls unlock
before clearing the surface and pitch, including when unlock changes those words.
The full432350 caller refuses a null font by returning X before any service; on a
font it binds, stores X as tab origin, draws actual text and unbinds in that order.
Unused binding-machine return bits are not projected or claimed.

`FontGlyphState` gains its separate line-height field for the existing measurement
consumer. Bitmap rows and line height retain their distinct original owners.
Font records still borrow immutable `GameFont` bytes. Surface/clip/color/tab/
spacing/initial associations and pixel-format shifts are explicit supplied state.
No application owner or renderer currently adopts this composition.

## Proof and limits

Canonical original results:
`private/boot-camp-20261018/font-text-fresh-a2/expected.json`, SHA256
`bcf11a01ef6936365badde659948120e0eba8bd8ec9b2479fb43d4cfb05bd8c2`.
The guest executes265 complete text roots,1,213 glyph roots,1,247 intersections,
760 color adjustments,134 measurements,186 complete wrapper entries,185 origin
setters and197 binding/unbinding pairs. There are290 checked top-level calls.
Only named surface lock/pitch/width/height/unlock and USER32 SetRect are supplied;
all listed drawing/color/metric instructions run unchanged in the same guest.

Cases cover empty/embedded-NUL text, CR/LF/tabs, limits, signed reveal and last-eight
fades, missing/fallback glyphs, unbound surfaces, absent primary/font, stock
GAME.FNT, packed color/shift edge cases, clipping and negative positions, odd byte
pitch, zero/negative surface dimensions and late height/unlock service mutations.
The binding-only cases exercise extreme arithmetic without pretending an invalid
surface is drawable. Native pixels use the original stock glyph owner or explicit
synthetic bitmaps; no font is downloaded or shipped.

Each case compares return, complete32x24 pixel backing, ordered raster index/
bitmap reads and16-bit writes, ordered service observations, final color/pitch/
origin/surface-presence/clip. Actual suffix measurement has its separate existing
ordered-read proof and is not replaced here; this suite traces raster reads only.
The guest guards caller stack/return/callee-saved registers, code/tables/IAT/live
color inputs, unrelated font words/padding and the whole unowned arena. It does
not claim all raw font-store granularity, arbitrary record overlap, raw binding
return bits, original allocator/window surface implementation or whole-frame UI.
The color child is translated for the actual nonoverlapping text-caller records.

Stock GAME.FNT SHA256:
`ec8d6d85db3eedf5a862cc6ffb87bfad4c77279dd946bc2d30879ad9140c8d3f`.
Its private location is `private/boot-camp-20261018/game-font-research-a1.bin`.
The driver explicitly checks asset identity before/after fresh execution and every
replay. The loader has separate existing proof; it is not executed in this guest.
Initial font/color/surface records and virtual services remain supplied, including
white/other target colors and RGB565/other packing fixtures. No original startup,
original window/SDL surface conversion, message drawing or scene ownership is
claimed. Host glyph bounds/refusals remain; text adds a1,048,576-unit work bound
and required-service refusal. Faults may retain earlier drawing/binding effects;
there is no rollback or unconditional unlock on failure.

Fresh-a1 stopped in the original wrapper because the research fixture had surface
and text arguments reversed; its failed audit remains. Fresh-a2 then completed
original generation but native comparison exposed an incorrect scratch-slot
interpretation of the shortened-reveal return. Only native code was repaired;
all278 saved original results remain unchanged. The fresh-a2 audit and mismatching
native output remain preserved. Passing normal/sanitizer/uncached replays carry
separate final source/runner identities and278 hits/zero misses each. No failed
native comparison was relabeled as a passing fresh run. The group label referring
to a borrowed-address return records that tested hypothesis; address variation
proves the corrected address-independent result.

Both rebuilt glyph runners also retain all363 prior original calls. Existing
application, owner and earlier font/metric/list/expiry runner hashes remain
unchanged from the glyph receipt, so their closed proofs and prior SDL evidence
retain their original scopes without rerunning. Local verification is not
independent acceptance, original UI/frame parity or completion of Objective1.
Both full builds,124 normal/123 sanitizer CTests and1,387 Python tests pass.
Normal/sanitizer builds took26.79/12.32s, CTests2.20/11.68s, Python37.391s test
time/54.93s shell elapsed. Current source/runner hashes and other costs belong in the private
`font-text-receipt-a1.json`; exact completed replay commands are in
`font-text-replay-commands-a1.json`. No cache mechanism was added or old original
matrix regenerated. Fresh original generation took1.017s. Repair/manual-review/
approval overhead was not separately measured. Configure/build/test/replay times
are retained in private logs and the receipt.

## Commands and next integration

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
./test.command
DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/sanitize --parallel 6

env PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/font-text-next.audit.json tests/compare_font_text.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/font-text-vectors \
  --font-file private/boot-camp-20261018/game-font-research-a1.bin \
  --expectations private/boot-camp-20261018/font-text-fresh-a2/expected.json \
  --report private/font-text-next.json

./run.command --boot-camp-walk
```

Use new audit/report destinations. The sanitizer runner and `--uncached` before
the driver provide respective replay controls. Replace expectations/report with
`--output private/NEW-DIRECTORY` for fresh original execution. The application
command retains existing walking behavior; it does not display objective text.

Next recover5FE1B0 RGB conversion/measurement/alignment/clip setters and join it
to this actual text/surface consumer, then600830 and6F1620. Production font/list/
expiry/drawing owners, warm discarded previews and ordinary SDL text acceptance
remain required before visible objectives. Live sight/arrival and remaining
mission effects still gate Boot Camp Objective1. Both games remain incomplete;
goal active. No workers, Windows actions/transfers or downloads were used.
