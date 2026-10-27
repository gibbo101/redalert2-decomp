# Original RGB text alignment caller

`src/render/FontAlignment.hpp` recovers complete base `5FE1B0` through actual
measurement, clipping/color setters and the existing complete surface/text/glyph
composition. All810 fresh original calls match native returns, complete pixel
backing, ordered raster/service events and both font records. This is an unwired
rendering dependency; upper message consumers and visible objectives remain open.

## Target and recovered scope

Exact supplied executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. `verify_font_alignment.py` fingerprints it
before inspecting complete caller/setter/child ranges and existing metric tables.
No public/YR/recomp code, new dependency or runtime executable read was added.

The caller returns0 immediately for a zero enable byte. A nonzero byte selects
the explicit surface or supplied default, packs the low RGB bytes using masked
dword shifts, saves box X/Y/width/height and selects the explicit font or supplied
default. RGB is low-byte R, next-byte G, next-byte B; the high byte is ignored.
The exact Font measurement kernel consumes the box width as its wrapping limit,
with separate width/height outputs, before any alignment or surface query.

Horizontal values1/2/3/4 use respectively `(boxWidth-measuredWidth+1)/2`,
`-((measuredWidth+1)/2)`, `-1-measuredWidth`, and
`boxWidth-measuredWidth-1` as X offsets. Vertical1/2/3 apply the corresponding
first three formulas to heights. Other values leave the saved pen unchanged.
Every add/subtract wraps as a signed dword; signed halves truncate toward zero
after the original wrapping operations. Do not replace this with host centering,
floating-point layout or clamping negative/overflowed dimensions.

Clipping reloads current box X/Y after measurement/alignment, while retaining the
saved width/height. It sets an inclusive rectangle ending at X+width/Y+height,
without subtracting1. The clip remains anchored to the box rather than the aligned
pen. The actual clipping byte/rectangle/color setters precede432350, which binds,
sets tab origin, draws real UTF-16 text/pixels and unbinds. The return is wrapped
drawn X minus aligned starting X. The chosen packed color and final intersected
clip remain in that chosen font; its surface and pitch are cleared by unbinding.
Unused setter machine return bits are not projected.

`FontTextBox`, `FontBlitContext` and two logical font/surface records are host
associations over the recovered fields. Pixel-format/default-font/default-surface/
enable/color records and initial font/box/bitmap state remain supplied. The proof
uses distinct mutable font records with different spacing/line-height/tab/origin
and distinct surface receivers. Their immutable glyph bytes and one canvas are
intentionally shared; no independent surface-backing or warm-clone claim follows.
The measurement trace observes actual results; it is never a layout callback.

## Evidence, limits and checks

Canonical original expectations:
`private/boot-camp-20261018/font-alignment-fresh-a1/expected.json`, SHA256
`8009af3f3449124ac8a86b5f2a9fb21bee38c20ed86e66a48fc8da9005dab5fe`.
All810 complete caller roots pass fresh comparison. Normal/sanitizer/uncached
replays each retain810 hits/zero misses. Both rebuilt text runners retain all278
prior original sequences without regenerating them. Earlier glyph, application,
owner, loader, metric, insertion and expiry runners remain hash-identical to the
text receipt; their closed evidence and SDL retain scope without rerunning.
No visible-text SDL acceptance or independent acceptance is claimed.

The guest executes857 actual measurements,802 each clipping/rectangle/color
setters, wrappers, bindings, origin setters, text roots and unbindings,2,149 glyph
roots,2,737 intersections and185 fade adjustments. Eight entries take the early
disabled return. Only named surface virtual methods and USER32 SetRect are supplied;
no measurement, alignment, setter, color, glyph or text answer is replaced.
Diagnostic post-measurement box mutations verify saved pen/sizes versus late X/Y
reloads. Separate late height/unlock mutations retain their existing service scope;
these are diagnostic dependency checks, not observations of live game scheduling.

Cases cover all horizontal/vertical values and defaults, odd/even/signed/wrapped
alignment, actual measurement wrapping, UTF-16 controls/embedded NUL/limits/reveal,
packed color and shift edge cases, zero/nonzero enable bytes, default/explicit
font/surface selection, stock GAME.FNT and current-box/service changes. Extreme
rectangle cases use empty text to verify arithmetic/state without claiming invalid
canvases can safely draw. Ordinary/odd-even/color/stock cases compare actual pixels.

Each case compares the complete32x24 canvas, ordered raster reads/stores, measured
width/height, surface receiver identities and service observations, return delta,
final state/clipping flag of BOTH fonts and resulting diagnostic box. The original
caller stack/return/callee-saved registers, code/tables/IAT/globals, unselected font,
untouched padding and all unowned arena storage are guarded. Full raw-store order,
original font/surface startup, allocator/window implementation, arbitrary aliasing,
faulting inputs and whole UI/frame fidelity remain outside this proof.

Stock GAME.FNT SHA256:
`ec8d6d85db3eedf5a862cc6ffb87bfad4c77279dd946bc2d30879ad9140c8d3f`.
Its private location is `private/boot-camp-20261018/game-font-research-a1.bin`;
the comparison driver explicitly checks asset identity before/after execution
and each replay. Loader proof is separate; the original loader is not entered
in this guest. No proprietary input or extracted payload is tracked.

Existing font byte/pixel bounds, work/division refusals and no-rollback scope stay.
Missing selected/default font or surface owners explicitly refuse natively;
original invalid-pointer faults are not executed or claimed as compatible. A
missing surface can be detected after clipping/color stores; do not assume every
failure leaves state unchanged. Production callers still need valid ownership,
warm discarded previews and an actual SDL surface conversion/interaction check.

Fresh original generation took2.408s, native comparison0.052s and driver2.829s.
Full normal/sanitizer builds took26.07/10.64s;124 normal/123 sanitizer CTests
passed in2.00/11.18s. All1,391 Python tests pass (36.007s test time/54.04s shell
elapsed). Additional replay times and final
source/runner identities are in `font-alignment-receipt-a1.json`; complete commands
are in `font-alignment-replay-commands-a1.json`. Repair/manual-review/approval costs
were not separately measured. No new cache was added or closed finalizer rerun.
Original results and eligible immutable inspections use the existing identity/
receipt-checked reuse path. Local verification is not independent acceptance.

## Commands and next integration

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
./test.command
DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/sanitize --parallel 6

env PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/font-alignment-next.audit.json \
  tests/compare_font_alignment.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/font-text-vectors \
  --font-file private/boot-camp-20261018/game-font-research-a1.bin \
  --expectations private/boot-camp-20261018/font-alignment-fresh-a1/expected.json \
  --report private/font-alignment-next.json

./run.command --boot-camp-walk
```

Use fresh audit/report destinations. Select the sanitizer runner or add
`--uncached` before the driver for replay controls. Replace expectations/report
with `--output private/NEW-DIRECTORY` for fresh execution. The existing application
command remains a walking scene; it does not yet display objective messages.

Next recover600830's actual scratch/copy/fitting/scroll/segment consumer and join
this caller, then6F1620's admission/color/typewriter. Production font/list/expiry/
drawing ownership, warm discarded previews and ordinary SDL text acceptance still
precede visible objectives. Live sight/arrival and remaining effects still gate
Boot Camp Objective1. Both full games remain incomplete; goal active. No workers,
Windows actions/transfers or downloads were used.
