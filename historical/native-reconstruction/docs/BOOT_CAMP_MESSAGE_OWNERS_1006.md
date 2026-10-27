# Boot Camp message ownership and full warm previews

The bounded `BootCampMissionWorld` now requires an actual stable message owner.
Action11 inserts into it through the verified `insertMissionMessage` adapter
before recording request telemetry. Warm mission/world clones retain the actual
message state and rebuild its bindings; discarded objective discovery can now
produce real message nodes and stock-font text pixels, rather than only a request
counter. Live sight/arrival/mission scheduling and visible SDL objective text
remain disabled. Both full games and Boot Camp Objective1 remain incomplete.

## Ownership and supplied startup

The constructor takes a unique message owner and refuses null. There is no silent
record-only fallback. `BootCampWalkWorld` supplies the existing user-installation
`game.fnt` through `GameFont` and `makeBootCampMessages`. Cloning calls the same
owner clone used by the standalone ownership checks, sharing immutable font data
and keeping distinct nodes, list/slots/focus, mutable font state, pixel backing,
IME/clock/request values and all bound callbacks. Mission callbacks capture their
new Impl and reach its message owner, never a source-world service or observer.
World cloning retains this owner through the existing mission/visibility/movement
composition. Assets/mission inputs retain their prior borrowed lifetime contract.

`makeBootCampMessages` is explicit temporary presentation startup: the current
1024x720 walking viewport, X12/Y96/width1000, six lines, loaded font line height,
mode0/clockStart0, RGB565 packing, sound IDs-1 (recorded only), and nine color
slots associated with the rules' LightGrey HSV. This preserves signed selector
behavior but does not recover original ColorScheme vector ordering, UI geometry,
clock scheduling or audio IDs. The first check exposed a mistaken supplied name
`white`; stock rules use `LightGrey`. That startup failure remains in the a1 log;
a2 uses the corrected association without a recovered-kernel change.

`messages()` exposes this actual owner for the upcoming presentation consumer.
The clock is explicit; neither Walk steps nor mission frames silently advance it.
Checks supply milliseconds for typewriter and expiry. Fill/line/sound requests
are recorded only. Background/cursor rasterization, SDL composition, ordinary
message-update scheduling and original UI startup remain open. No new executable
read was added; font bytes are ordinary user-supplied archive content. There is
no application execution of original instructions or new research dependency.

`PositionCompositionResult::finalMissionMessageLines` observes the actual final
clone list without a map/floor/font query. A discarded objective arrival must
produce at least one node as well as the prior text request/deferred effects.
It returns counts, never a pointer into the discarded owner. Live play retains
all prior sight/arrival and unsupported-effect guards.

## Native ownership evidence

The private-data owner check passes on normal and ASan/UBSan builds. It now checks:

- Objective discovery inserts flagsC046/identifier0 only into the clone; its actual
  localized payload draws stock-font pixels and records the supplied fill request.
- Warm queued/drained mission clones retain message values with different node,
  metric and pixel owners and shared immutable glyph data. Drawing and expiry
  continue after their source mission owners are destroyed.
- The full world snapshot includes actual message slots, all allocated nodes
  (including destroyed records), clock, font/metric/color/default/surface
  associations, canvas, IME and request values/backing/capacities. The test-only
  inspection friend observes stores without invoking consumers or warming caches.
- A warm full world creates and draws an objective, then discards further message
  drawing/expiry and actual arrival previews in a clone. All live world/message
  values/backing and warm Renderer pixels/camera stay unchanged. Later full-world
  drawing/discovery/cleanup continue after destroying the source world.
- Prior moved/warm/fallback/queued/drained/foreign-owner/refusal/tick-bound and
  route/Stop checks remain. A real discarded objective arrival produces actual
  message nodes while preserving the live source's empty list and mission state.

Same-source object bytes/addresses detect mutation only; they are not portable
serialization, original layouts or cross-address equality. Clone continuation and
logical outputs supply separate identity/lifetime evidence. No rollback of a
partially mutated direct owner is claimed; discarded previews own their writes.
These are host composition checks, not an original-game observation or a new
whole-chain original mission proof. Local verification is not independent acceptance.

## Differential and SDL boundaries

The original action11-to-owned-message evidence in
[MISSION_MESSAGE_PRESENTATION_1006.md](MISSION_MESSAGE_PRESENTATION_1006.md)
retains123 original sequences. The native ownership inspection declaration
rebuilt its two runners; normal/sanitizer/uncached replays each retain123 hits and
zero misses against the same original-only expectation identity. No original
regeneration or closed finalizer rerun was necessary. The 242 shared-lifecycle
and all earlier font/metric/node/list/expiry runners remain hash-identical,
retaining their separate original receipts/scopes.

Exact original target remains4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`;
embedded1.08/supplied1.006 lineage/reported no-CD/unverified pristine authenticity
remain distinct. Private GAME.FNT SHA256 remains
`ec8d6d85db3eedf5a862cc6ffb87bfad4c77279dd946bc2d30879ad9140c8d3f`.

Actual rebuilt SDL input/drawing smoke passes under
`private/boot-camp-20261018/boot-camp-messages-sdl-a2/`. It retains the106-tick
selection/move/pause/refusal/Stop/repeated-order/deselection baseline. At source
tick2, a discarded warm arrival takes25 Process calls and one GI discovery.
The smoke now explicitly preserves the message canvas values/backing, slots,
availability, head/node count, mutable font values and request counts alongside
existing world/renderer guards. The arrival image was inspected. Receipt fields
keep `original_fidelity_from_this_smoke:false`, `visible_objective_text:false`
and `objectives_enabled:false`. The first sandboxed SDL launch could not enumerate
displays; its log remains, and the successful launch used WindowServer access.
No system, Xcode, DRM, Windows or download action was performed.

Both full builds and128 normal/127 sanitizer CTests pass. Python sources/tests
are unchanged; the prior1,407-test pass retains scope without rerunning discovery.
Seven prior binaries rebuilt (application, both owner checks, both standalone
message ownership checks, both mission-message vectors);16 prior runners retain
identical hashes. Normal/sanitizer private-data owner checks took2.84/24.99s;
successful SDL4.16s. Other measured build/check/replay costs, explicit runner/
source/receipt identities and exact commands are in private
`boot-camp-messages-receipt-a1.json`. Repair/review/approval costs were not separately
measured. No caching mechanism or public/YR/copied code was added.

## Commands and next integration

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
./test.command
DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
build/native/boot-camp-walk-check private/official-1006-probe
build/sanitize/boot-camp-walk-check private/official-1006-probe
./run.command --boot-camp-walk-smoke-test private/NEW-SDL-DIRECTORY
./run.command --boot-camp-walk
```

Use a new ignored SDL output directory; GUI checks require display access.
Original replay commands remain in the message presentation note and new private
`boot-camp-messages-replay-commands-a1.json`; use new audit/report paths and keep
all source/asset/runner/receipt guards.

Next resolve the entered message surface fill (and cursor line if entered) or
explicitly bound its temporary raster adapter, then connect message time/update/
drawing to ordinary SDL presentation and verify actual visible objective text.
Preserve the full warm discarded previews. Live sight/arrival and the remaining
objective effects still precede normal Objective1 progression. No workers or
runtime executable-read expansion.
