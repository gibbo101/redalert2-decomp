# Original message surface consumer

`src/render/MessageText.hpp` recovers complete base `600830`: bounded UTF-16
scratch copying/splicing/masking, caret validation, scrolling, fitting, background
request, segmented drawing and cursor requests. All348 fresh original calls match
scratch contents, scroll, box, font, pixels and ordered projected events. Actual
CRT/metric/alignment/text/glyph children execute in the proof. This remains an
unwired dependency; the application still does not display objective messages.

## Target and scope

Exact supplied executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. `verify_message_text.py` fingerprints it
through the previous verifier before inspecting complete600830/783605/783622/
783850 and737E30 ranges. Original code/data, receipts and GAME.FNT stay private.
No public/YR/recomp/CRT implementation, new dependency or runtime executable read
was incorporated. Unicorn remains research/test-only.

The nine stack arguments are text, caret, font, RGB, scroll pointer, IME enable,
mask, background enable and reveal. The node6F1620 pushes mask0/background1;
transient pushes must be accounted for when interpreting stack offsets. Surface
and mutable box are the ECX/EDX receivers. Null text uses an empty string. A
negative caret or one beyond the original NUL-terminated length becomes0.

Actual783622 copies forward in UTF-16 units and pads the remaining count with
zeros after the first NUL, without guaranteeing termination when count runs out.
The native helper preserves that successful separate-owner behavior, not the
original grouped dword store trace. The consumer copies2048 units to its own
scratch buffer, optionally inserts composition at the validated caret, appends
the original suffix, then always clears scratch unit2047. It measures length
again and optionally replaces all visible units with `*`. Source text stays
unchanged. Unsafe scratch offsets/counts explicitly refuse; no original fault or
arbitrary pointer-alias compatibility is claimed.

IME refresh is an explicit supplied service. With no IME context, the proof
executes actual737E30's zero-context branch: first composition unit, composition
length and cursor clear, while the extra flag remains. Native fixture refresh
models those projected effects. The nonzero Windows conversion path is not
reconstructed:93 cases supply the named refresh leaf and then execute actual
600830 splicing/fitting/segment control. This does not add Windows support.
Composition globals/initial associations and diagnostic fixture inputs remain
supplied. No live IME/window/session observation is claimed.

Cursor index is the caret unless composition length or extra is nonzero, in
which case it is wrapped caret+compositionCursor. If it lies before scroll+5,
scroll becomes cursor-5 for cursor>=5, otherwise0. Actual431710 fits each suffix
against wrapped boxWidth-5 with zero max-count/word-wrap, advancing scroll until
the cursor fits or scratch length is reached. Preserve signed comparisons and
wrapped dword additions/subtractions; do not use a replacement text layout.

Prefix, composition and suffix counts retain the original signed/clamped split,
including the adjusted delta when the caret precedes scroll. Background height+2
is saved before actual431690 measures the scrolled suffix. The supplied fill
leaf receives `(boxX-1,boxY-1,measuredWidth+5,savedHeight+2)` and color0. The fill
implementation is not recovered here; pixel comparison covers actual text stores
over the supplied initial canvas, not original background-fill rasterization.

Every entered segment uses the single actual5FE1B0/432350/text/glyph composition,
then updates the shared box's X and width by its returned advance, clamping only
negative resulting width to0. Prefix/suffix use requested RGB; composition uses
the live highlight RGB, splitting around an in-range composition cursor. Each
segment receives the same reveal value. Cursor X is captured between the
composition pieces or after the prefix when composition is absent. With IME,
positive cursor X and late suppression0, two supplied5FD290 leaves receive X/X+1,
current Y through Y+height-2, live cursor color and alpha255. Suppression always
clears on normal return. Cursor-line rasterization is not recovered here.

`MessageTextServices` owns logical composition/global records and names the
refresh/fill/line leaves. `FontTextBox`, font and scroll are borrowed mutable
records; scratch is local. Surface/SetRect services retain earlier supplied scope.
The node caller ignores incidental machine EAX and returns its own status; this
API deliberately projects no unused raw return bits. Refusals can follow earlier
writes; no rollback, production owner, warm-clone or whole-frame claim follows.

## Evidence and verification

Canonical original expectations:
`private/boot-camp-20261018/message-consumer-fresh-a1/expected.json`, SHA256
`06385084c1cea9deeae8da837415e4bb4284413d222d9ebeefc0ce89504727c1`.
All348 fresh calls match. Final normal/sanitizer/uncached replays retain348 hits
and zero misses each, without repeating original execution. Both rebuilt runners
retain810 alignment and278 earlier text cases each. A native-only review repair
preserved the background-height load before measurement; saved originals remain
eligible and match. Earlier audit/report destinations were not overwritten.

The guest enters348 complete consumers/probes,696 length calls,534 bounded
copies,15,101 prefix fits,332 width calls,440 aligned segments,434 complete text/
binding/unbinding chains,9,514 glyphs,9,932 intersections and66 fade children.
Sixteen actual zero-context IME updates execute;93 nonzero refreshes,332 fills and
158 cursor lines are named supplied leaves. Cases include null/embedded-NUL/
CR/LF/tab text, caret validation, scroll correction, stock font, masks/background/
suppression, composition splits/out-of-range cursors, reveal,2046/2047/2048/4096
source lengths and composition at the scratch boundary. Extreme box arithmetic
uses empty text rather than claiming invalid raster buffers can safely draw.

Each call compares all2048 scratch units through an observation trace, complete
32x24 pixel backing, projected ordered glyph/measurement/surface/fill/line events,
font state, mutable box, scroll and consumed global fields. Caller stack/return/
callee-saved registers, code/tables/IAT/immutable globals, unrelated arena/font/
text/padding are guarded. Full raw-store ordering, arbitrary aliases, original
surface allocation/fill/line code, nonzero IME conversion, node admission/
typewriter/color selection, production expiry/drawing and SDL text remain open.
Diagnostic fixtures are not live original-game observations.

Both full builds,124 normal/123 sanitizer CTests and1,395 Python tests pass.
Following the native load-order/include review, both text targets were rebuilt;
focused domain checks and all affected original replays pass on the final sources.
The application and12 other owner/font/metric/list/expiry/glyph runners
retain their previous hashes; closed proofs and SDL keep scope without rerunning.
There is no new visible-text SDL or independent acceptance claim.

Fresh original generation took23.269s, native comparison0.047s and driver23.942s.
Full normal/sanitizer builds took21.31/10.84s; CTests3.05/12.94s. Python tests took
33.343s test time/42.70s shell elapsed. Final replay costs, exact commands, source/
runner identities and unavailable separately measured repair/review/approval costs
are in `message-consumer-receipt-a1.json` and
`message-consumer-replay-commands-a3.json`. No new cache was added; unchanged
original expectations and eligible immutable inspections use existing guards.

## Commands and next integration

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
./test.command
DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/sanitize --parallel 6

env PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/message-consumer-next.audit.json tests/compare_message_text.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/font-text-vectors \
  --font-file private/boot-camp-20261018/game-font-research-a1.bin \
  --expectations private/boot-camp-20261018/message-consumer-fresh-a1/expected.json \
  --report private/message-consumer-next.json

./run.command --boot-camp-walk
```

Use new audit/report paths. Select the sanitizer runner or add `--uncached` before
the driver for replay controls. For fresh original execution replace expectations/
report with `--output private/NEW-DIRECTORY`. GAME.FNT has the prior separately
verified SHA256 `ec8d6d85db3eedf5a862cc6ffb87bfad4c77279dd946bc2d30879ad9140c8d3f`;
the driver checks it before/after each invocation and replay.

Next join6F1620's admission/color/typewriter to this actual consumer, then stable
production font/list/expiry/drawing owners, discarded warm previews and ordinary
SDL visible-text acceptance. The existing run command remains a walking scene
without objective text. Live sight/arrival and remaining mission effects still
gate Boot Camp Objective1. Both full games remain incomplete; goal active.
