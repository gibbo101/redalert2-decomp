# Native message frame composition

Boot Camp now composes ordinary owned messages after terrain/sprites on every
SDL frame. The supplied uint32 millisecond clock feeds actual expiry followed by
actual list/node/text/software-fill drawing. Message timing continues while Walk
is paused. This is an explicit host schedule, not recovered original frame cadence.
Live mission actions and objective progression remain disabled.

## Implementation and boundaries

`src/render/MessageFrame.hpp` forwards only actual glyph and fill stores into the
ARGB framebuffer through the existing RGB565 expansion adapter. Untouched RGB8
terrain is retained exactly; expired messages cannot copy stale canvas pixels.
No whole-frame quantization, seed/mask canvas or duplicate raster is introduced.
Dimensions, software policy, RGB565 packing and unfocused ordinary presentation
are checked before mutation. Cursor/IME presentation remains excluded; line and
audio requests are still recorded only. Startup geometry and LightGrey color
ordering retain their supplied scope.

`OwnedMessagePresentation::draw` borrows a fill observer only during drawing,
clears it on success or exception, and refuses reentrant drawing or mid-draw
cloning. Partially bound refused draws can still be cloned and continued after
source destruction. This does not promise rollback of a partially drawn owner.
The adapter is authored native glue over recovered kernels, not a new original
algorithm proof or original full-frame comparison.

Exact supplied executable remains4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD and unverified pristine
authenticity remain distinct. Exact-base inspection identifies fixed A3DC70
receivers at540606 followed by call54060B->5B5610, and4E0BFE followed by
call4E0C03->5B5B30. These are inspected call sites only, not proof of complete
frame order, pause behavior or scheduling. Private navigation at4E0BD0 starts
mid-instruction; its initial decoded instructions are not evidence.
No public/YR/recomp code, new dependency, runtime executable read or Windows
action was added. Original execution remains research/test-only.

## Verification

Both settled builds pass. All130 normal and129 sanitizer CTests pass in2.71s
and11.12s respectively. Both private-data Boot Camp checks and standalone
synthetic/stock-font owner checks pass. New checks cover strict expiry equality,
actual fill/glyph forwarding, unrelated terrain preservation, stale-canvas
exclusion, full warm source/renderer isolation, refusal before mutation, observer
exception cleanup and source-destruction continuation. Prior1,413 Python tests
retain scope; no Python source/test changed and discovery was not repeated.

Both123-case software and requests-only families pass normal/sanitizer/uncached
identity-checked replays, each123 hits/zero misses. No fresh original execution
was needed. Canonical expectations remain:

- `software-message-fresh-a1/expected.json`, SHA256
  `1ce2f978f9f13ee8a686a077e06fec1babd271bddfcf00cd20c1af74c0390920`.
- `mission-message-fill-dependency-refresh-a1/expected.json`, SHA256
  `121a744d92f3525116e9b9cb0f8e69a4cc5777cc8ff601e0fca3c2c5bf0f9338`.

Paths above are under ignored `private/boot-camp-20261018/`. The runner inventory
retains18 unchanged identities, including the751-case raster runners; nine
runners/application/checks rebuilt. Historical receipts remain immutable; no
closed finalizer was rerun. Exact commands, hashes and measured replay costs are
in `message-frame-receipt-a1.json` and `message-frame-replay-commands-a1.json`.
Build/repair/review/approval/GUI costs were not separately measured; no new cache.

Actual SDL baseline passes106 ticks: selection, movement, pause, retarget refusal,
Stop, repeated orders, deselection and discarded warm preview isolation.
`message-frame-sdl-a1/message-presentation.json` separately records an isolated
mission clone with injected discovery1019675 and supplied4000ms clock. Actual
mission logic/action11 produces the stock localized “Objective 1 Complete” text;
468 glyph stores plus1,121 fill stores forward2,691 pixel stores. The diagnostic
texture was presented and its PPM was visually inspected. The SDL header labels
injected discovery and disabled live objectives. The PPM captures the composed
terrain/text buffer before SDL marker/header overlays, not the entire window.
The source mission has no text request/head and retains paused tick/position.
This is visible presentation acceptance only, not ordinary objective acceptance,
Objective1 completion, original gameplay observation or whole-frame fidelity.
Local verification is not independent acceptance.

## Commands and next capability

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
build/tools-env/bin/ctest --test-dir build/native --output-on-failure
DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
build/native/boot-camp-walk-check private/official-1006-probe
build/sanitize/boot-camp-walk-check private/official-1006-probe
./run.command --boot-camp-walk
./run.command --boot-camp-walk-smoke-test private/NEW-SDL-DIRECTORY
```

Use new output/audit paths. Replay commands and fresh-original options remain
in [SOFTWARE_MESSAGE_1006.md](SOFTWARE_MESSAGE_1006.md); keep all identity guards.
Finish source edits before final builds; do not overlap same-directory builds.
Next join live arrival/sight and remaining entered effects, sample message time
before live producers, then require ordinary SDL movement to produce objective
text. Keep diagnostic coverage separate. Both games remain incomplete; goal active.
