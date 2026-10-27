# Original message node drawing

`src/render/MessageNodeDrawing.hpp` recovers complete base `6F1620` through
actual gadget admission, font selection, HSV conversion, focus and the complete
message surface/text/glyph composition. All371 original sequences /567 complete
node calls match native return sequences, mutable nodes, both fonts, text pixels
and ordered projected events. It borrows the existing `MessageNode`, `MessageList`
text slots and `MessageListGlobals::focused[2]`; production drawing remains unwired.

## Target and recovered behavior

Exact supplied executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. `verify_message_node.py` fingerprints it
before inspecting complete node/helper/HSV and prior text ranges. Constructor
`6F15C0` installs vtable `7ADCCC`; its actual draw slot6C selects6F1620 and focus
slot58 selects4CF630. The final fixture uses this original unmodified table,
with its bytes identity-checked and guarded during calls. Constructor bytes are
inspected here; construction has separate earlier insertion evidence.

A nonzero node40 byte returns false before admission and leaves dirty unchanged.
Actual4CF240 then admits a nonzero force or dirty byte and clears dirty before
later color checks. Color count0 refuses; a signed selector<=0 or>=count chooses
index0. A null selected color pointer refuses. Negative nonzero counts still
select index0; they are not treated as an empty vector. Native color-span bounds
are explicit refusals rather than invented successful lookup behavior.

Actual497A50 ignores node2C and returns the selected global font. The caller
saves this font and node X/Y/maximumWidth. Negative maximumWidth queries the
current surface width, then font line height is read. A second surface-width
query always follows. Wrapped X+width-surfaceWidth determines right clipping;
only a positive excess enters the branch that rejects a nonpositive resulting
width or font height. Do not move those rejections to unconditional admission.
The saved font remains selected if a surface service changes the global font.

Actual4FF050 converts selected color+308 HSV to low-byte R/G/B. This reuses the
existing `originalHsvToRgb`, independently verified on this base in
[SHADOW_COLOR_1006.md](SHADOW_COLOR_1006.md), and executes that complete original
helper inside the new caller proof. The selected color pointer is saved before
width queries, while its HSV values are consumed afterward. RGB is saved before
clock/audio. No public/YR replacement color behavior is used.

The original UTF-16 length is saved before testing node41. With typewriter
on, the named raw timeGetTime leaf returns a dword; the caller then reloads reveal
count44. A zero count becomes1. Otherwise count advances by
`(now-lastTime48) >> 4`, with unsigned wrapped subtraction **before** shifting
and wrapped addition. It updates lastTime only when count changes. The sound
branch compares signed count against saved length and includes equality; it can
request sound on a draw where no time progress occurred. Rules+5E4 supplies the
sound ID, with flags2000/volume1/extra0. This differs from insertion's5CC sound.
With typewriter off, existing reveal count is still passed through unchanged.

After any sound request, the caller reads reveal44 and actual4CF630 compares the
node identity with live focus865FF8. It reloads the text association, uses the
saved length as caret, resolves the current surface and calls actual600830 with
mask0/background1. Thus an audio callback can change text/focus/reveal/scroll
before drawing without changing the saved length, pen, dimensions, font or RGB.
It returns true after the consumer, even if the lower blit enable byte suppresses
text. Background remains an entered named leaf in those disabled cases.

The consumer now accepts either signed or unsigned dword scroll storage through
a constrained template and explicit bit interpretation. Node3C is the actual
existing unsigned owner; no mirrored scroll or casted signed reference is used.
Signed arithmetic/queries remain the same single consumer kernel. Existing signed
consumer fixtures retain all348 results on both rebuilt runners.

`MessageNodeDrawGlobals` supplies color count/table, selected font/surface and
Rules sound associations. `MessageListServices` names time/audio; existing text
services name IME/fill/cursor and surface/SetRect leaves. Initial records remain
supplied. Slot association resolves the existing14x162-unit owner before length
and again before draw. Absent initial text, absent font/surface/services, invalid
slots and insufficient table storage explicitly refuse; original pointer faults
are not executed or claimed compatible. Refusal can follow dirty/other writes;
there is no rollback claim. Production font/metric associations still need one
stable owner and clone bindings.

## Evidence and limits

Canonical original expectations:
`private/boot-camp-20261018/message-node-fresh-a3/expected.json`; its SHA256 is
recorded in the opening handoff and private `message-node-receipt-a1.json`.
Normal/sanitizer/uncached replays retain371 hits/zero misses each. Both rebuilt
text runners retain348 consumer,810 alignment and278 text cases each. Earlier
logical-vtable and intermediate original-vtable proofs remain private under
fresh-a1/a2 with their original identities; their projected results agree with
the final proof. They were not silently relabeled or overwritten.

The guest enters567 complete node roots,495 admission helpers,413 font getters,
402 actual HSV/focus/consumer/probe/width chains,1,206 CRT length calls,2,784 fits,
375 aligned segments,374 complete text/bind/unbind chains,762 glyphs,1,136
intersections and316 fade helpers. Seventy-six actual zero-context IME updates
run. Named supplied leaves include227 raw clock calls,158 sounds,402 background
fills and152 cursor lines. Surface width is queried812 times across node and
binding. No layout, font/color/focus/admission, text, glyph or pixel answer is
replaced. Fill/line rasterization and nonzero IME conversion retain prior scope.

Cases cover hidden/dirty/force and signed color/null admission, repeated draws,
negative-width repeated queries, conditional clipping/height refusals, NUL/CR/LF/
tab text,160-unit slots, signed/wrapped reveal and raw clock boundaries, equality/
unchanged-time sound, all HSV sector boundaries and stock GAME.FNT. Diagnostic
width services change source pen/max-width, font height/global selection and
color values; time/audio services change text slot, focus and reveal/timer/scroll.
These test dependency order, not live original-game observations. Distinct mutable
fonts share immutable glyph data and one canvas; no independent-surface ownership
or original startup claim follows.

Each sequence compares all return booleans, full32x24 pixel backing, both fonts'
projected color/pitch/origin/binding/clip state, relevant node/association/global
fields, and the combined scratch/raster/measurement/service event digest. Caller
stack/return/callee-saved registers, original vtable/code/tables/IAT, unowned arena,
slots and padding are guarded. Native domain and receipt/scope/source/asset/runner
guards pass. This is local verification, not independent acceptance, whole-frame
fidelity, live mission completion or visible-text SDL acceptance.

Both full builds,125 normal/124 sanitizer CTests and1,399 Python tests pass.
Final fixture/vtable scope changes pass focused evidence guards and fresh/replay
checks. Application and12 other owner/font/metric/list/expiry/glyph runners remain
hash-identical to the prior receipt. Their closed proofs and SDL retain scope
without rerunning. No new cache, dependency, copied public/CRT/lifted code or
runtime executable read was added. Original inputs and all extracted material,
inspections, receipts and binaries stay ignored under private/build.

Exact source/runner identities, fresh/replay/build/check costs and unavailable
separately measured repair/manual-review/approval costs are in the private receipt.
The final node command set plus retained unchanged-family commands are in
`message-node-replay-commands-a3.json`. No Windows action/transfer, download,
system selection or license/DRM change was made.

## Commands and next integration

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
./test.command
DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/sanitize --parallel 6

env PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/message-node-next.audit.json tests/compare_message_node.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/message-node-vectors \
  --font-file private/boot-camp-20261018/game-font-research-a1.bin \
  --expectations private/boot-camp-20261018/message-node-fresh-a3/expected.json \
  --report private/message-node-next.json

./run.command --boot-camp-walk
```

Use fresh audit/report paths, the sanitizer runner or `--uncached` as appropriate.
Fresh original execution uses `--output private/NEW-DIRECTORY` instead of the
expectations/report options. GAME.FNT remains separately hash-checked before/
after each run/replay: `ec8d6d85db3eedf5a862cc6ffb87bfad4c77279dd946bc2d30879ad9140c8d3f`.

Next join ordinary list/gadget draw traversal, then original shared insertion/
expiry/draw sequences and stable production message/font/surface owners, warm
discarded previews and ordinary SDL visible-text acceptance. Navigation candidates
are private `message-list-draw-navigation-*`:5B5B30's final head+2C dispatch selects
4CF260, whose chain must reach the verified node+6C draw. Editor/input branches
retain separate unproved scope. The existing walking scene still records objective
requests only. Live sight/arrival and remaining effects still gate Objective1;
both full games remain incomplete and the goal stays active.
