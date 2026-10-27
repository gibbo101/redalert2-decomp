# Stable message presentation ownership

`OwnedMessagePresentation` is an SDL-free, immovable host composition owner for
the existing recovered insertion, expiry, ordinary list/node drawing and text
pixels. It shares one immutable `GameFont` and owns the actual mutable list,
14x162 UTF-16 slots, availability words, stable nodes, focus, clock, font style,
IME values, requests and 16-bit pixel backing. There is no mirrored message list
or alternative layout/raster kernel. It is available for production integration
but not yet consumed by Boot Camp or SDL.

## Supplied adapter and clone contract

`MessagePresentationConfig` supplies initial geometry, line/capacity/mode/clock,
color/packing, sound IDs and untouched allocator padding. None is claimed as
original global/UI startup. Slots initially contain zero, available words1. An
explicit millisecond value supplies timeGetTime; advancing game/UI time remains a
caller policy. A stable node pool reuses destroyed records and supplies untouched
padding before the recovered constructor writes its fields. Returned message
pointers are borrowed only until expiry/capacity removal; allocation reuse is a
host policy, not original heap address/identity parity.

Surface width/height/pitch/lock/unlock bind only this owner's contiguous pixels.
Callers may supply a base canvas with `replacePixels`; it copies values without
replacing the backing. Recovered drawing mutates the same canvas and font state.
Fill, line and sound requests are recorded, not rasterized or played; callers
must consume/clear request vectors. This is deliberately explicit adapter scope.
No nonzero IME conversion, editor/input path, original background/cursor drawing,
whole-frame or visible SDL claim follows. Focus refresh uses the existing
zero-context IME behavior. Native dimensions/backing are bounded host safeguards.
Refusals can leave partial state; there is no rollback claim.

Cloning copies values, shares immutable font data, then remaps head, Next,
Previous and all three focus references onto distinct stable nodes. It rebuilds
metric/color/global/default/font/surface associations and every mutable-owner
callback instead of copying bound functions. It copies text/IME fields and
request values explicitly. A warm bound font surface is rebound to the clone's
backing, while an unbound font stays unbound. Absent/foreign link associations
refuse instead of retaining source pointers. Move owning pointers, not contexts.
A foreign/destroyed focus refuses. Production mission/renderer/world composition
must invoke this clone rather than copying its logical records or callbacks.

## Verification and limits

`owned-message-check` checks synthetic glyphs without proprietary inputs and
accepts a separately supplied GAME.FNT path for private checks. Normal and
ASan/UBSan runs pass with both fonts. Checks include actual inserted UTF-16 text
outliving its request, focus/cursor/typewriter warm drawing, changed pixels,
independent list/link/metric/pixel identities with shared immutable backing,
clone-only expiry/focus cleanup, allocation reuse and repeated capacity removal.
All source slots, message values, font/IME values, pixels and request records
remain unchanged after discarded mutations/drawing. Independently rebound clones
continue identically after source and external font references are destroyed.
Later drawing/insertion still works when the final clone becomes the sole owner.

A separate deliberately invalid glyph-row fixture enters a byte-backing refusal
*after* surface binding. Its warm bound surface is cloned onto different storage;
later refused drawing changes only that clone and survives source destruction.
The initial fault fixture was clipped before its intended work refusal, so its
native test failed; the corrected row-backing fixture and final logs are retained
separately as a2. No recovered kernel was changed. These are host lifetime and
isolation tests, not original-game observations or fresh differential evidence.

Original algorithm evidence retains the exact supplied target SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f` and scope
in [MESSAGE_LIST_DRAWING_1006.md](MESSAGE_LIST_DRAWING_1006.md), its dependencies,
and the prior private receipt. The242 shared original sequences are not relabeled
as proofs of this owner. Their implementation and runners are unchanged; no new
original execution was needed. GAME.FNT used privately remains SHA256
`ec8d6d85db3eedf5a862cc6ffb87bfad4c77279dd946bc2d30879ad9140c8d3f`.

Both full builds plus final focused rebuilds pass. All127 normal/126 sanitizer
CTests pass. Python sources/tests are unchanged; the prior1,403-test pass retains
scope without another run. Application and18 prior runners are hash-identical to
the shared-pipeline receipt; closed original evidence and SDL retain prior scope.
No runtime executable read, cache, dependency, public/YR/copied code or proprietary
tracked payload was added. Local verification is not independent acceptance.
Private `owned-message-receipt-a1.json` records source/runner identities, exact
commands and measured build/check costs. Repair/review/approval costs were not
separately measured. Failed fixture and build-target-before-configure logs remain.

## Commands and next integration

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
./test.command
DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
build/native/owned-message-check
build/sanitize/owned-message-check
build/native/owned-message-check private/boot-camp-20261018/game-font-research-a1.bin
build/sanitize/owned-message-check private/boot-camp-20261018/game-font-research-a1.bin
./run.command --boot-camp-walk
```

The existing walking scene still records objective requests only. Next join the
actual action11/localization/color request to insertion/lifecycle on these owners,
then include the owner in full warm discarded mission/world/renderer previews
and verify source-destruction continuation. Resolve required fill/line raster
children or explicitly bound their supplied adapter scope before visible SDL
objective-text acceptance. Original editor/input remains separate. Live sight/
arrival and remaining mission effects still gate Objective1; both games remain
incomplete and the active goal remains unchanged. No workers, Windows actions/
transfers, downloads or system/DRM changes.
