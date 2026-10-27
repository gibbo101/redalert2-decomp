# Supplied RA2 1.006 final Unit surface wrapper

October 15, 2026, after `c0746b5`. **5,602 fresh original/native results** and
normal/ASan/UBSan replays pass. The complete final Unit wrapper now executes with
actual house selection and, on its ordinary path, the actual final surface,
clipping, alpha/depth readers and RGB565 span. This is a prerequisite checkpoint
for the same healthy Rhino drawing delivery. The helper remains unwired;
[milestone 20's crossing](CROSSING_1006.md) is the observable runtime capability.

## Identity and reference hypothesis

The exact supplied engine is `private/official-1006-probe/game.exe`, 4,485,392
bytes, SHA256 `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Fresh generation and both replays verify that identity. The approved private
Windows copy was already verified equal during the preceding checkpoints; it
was not recopied or executed this turn. Embedded 1.08, supplied 1.006 patch
lineage and user-reported no-CD provenance remain separate facts. Pristine
authenticity is not established. No Windows task/source installation/disc/system
configuration changed.

Consulted pinned redalert2-recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439`,
`docs/voxels.md` and LICENSE, and pinned YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88`, `TechnoClass.h` and `Surface.h`.
Hypothesis: the Unit wrapper joins indexed staging to the battlefield through
house conversion, caller flags, clipping and depth. The headers' disguise flag
declaration is a naming lead, not evidence for base layout or phase arithmetic.
Exact base instructions establish the decisions below. No upstream/header,
generated or lifted game code was incorporated; no new dependency was added.

## Complete inspected boundaries and executed scope

`tools/verify_unit_surface.py` pins **23 complete ranges / 1,741 instructions**,
including the **217-instruction root `0x6FF3E0..0x6FF67F`**. Its final instruction
is `ret 0x20` at `0x6FF67C`; trailing padding and the four-entry jump table are
separate. The entire root is inspected. Execution requires type byte `+0xBAE`
zero; the nonzero alternate/split branch and that byte's semantic name are open.

| Boundary | Patched VA | Executed scope |
| --- | --- | --- |
| Unit final wrapper, actual Unit slot `+0x4E0` | `0x6FF3E0` | Complete ordinary root |
| Disguise draw flags, Unit `+0x3D0` | `0x6D8C30` | Complete, including active/paused/wrapped timers |
| Status byte leaves, Unit `+0x1BC/+0x1C0` | `0x6D6DF0`, `0x6D6E00` | Actual actor `+0x204/+0x205` reads |
| Owner visibility / disguise byte | `0x4F52B0`, `0x41B410` | Actual supplied-house/actor reads |
| Initialized converter selector | `0x485AA0` | Flags `0x2800` plus bits 1..3, original mask `0x3000` |
| Foot / Drive / Techno layer | `0x4C8FA0`, `0x53D4C0`, `0x6CF3C0` | Healthy zero-state branch only |
| BSurface bounds | `0x411290` | Actual source rectangle output |
| Final surface / clipping / RGB565 span | `0x434B40`, `0x7753B0`, `0x488870` | Ordinary gradient 2, actual alpha/depth reads |

Actual healthy layer cases use supplied type `+0xAA6=0`, actor `+0x1B8=0` and a
nonnull actual Drive interface. Drive returns zero, then Techno performs two
actual type queries and returns zero. This verifies the selected branch, not
full layer calculation or stock construction of those fields. Other layer values
are explicit read-only overrides. Depth and gradient wrappers remain services;
the layer-four direct helper `0x6D6750` is also a service. Their bodies are not
new recovered behavior. Final pixels use supplied gradient 2 and depth adjustment.

## Preserved native decisions

`src/render/UnitSurfaceDraw.*` stays SDL-free and uses portable values/services:

- Query layer with `(0,0)`. Default/out-of-range layers use `0x2800`; layer 1
  uses `0x2802`; layers 2/3 use `0x2804`. Layer 4 uses `0x280A` for actor
  `+0x1BC` zero, otherwise `0x280C`, then queries the extra argument.
- Read actor byte `+0x204` first; only if its low byte is zero read `+0x205`.
  Either nonzero ORs flag 4. These retain offset names.
- Query owner visibility before the disguise byte, and call the actual disguise
  flag helper only for visible owner and nonzero disguise. Its active timer with
  false owner returns unchanged. Preserve compare-before-subtract signed timer
  arithmetic, paused nonzero durations and signed wrapped phase remainder.
- Phase `(frame-origin+64) % 256` ORs 2 in 64..67, 76..79, 112..115, 124..127;
  it ORs 4 in 68..75 and 116..123. Other phases preserve all bits.
- Select actor owner `+0x1B4`, owner scheme index `+0x15F40`, global array
  `0xAB6EFC`, then scheme converter `+0x30C`. Initialized ordinary selector
  slots are `0x98`, `0xA8`, `0xA4`, `0xA0`, `0xB4`, `0xB0`, `0xAC` for
  flags `0x2800/02/04/06/0A/0C/0E`, respectively. The native slot helper refuses
  other high/low bits. Other blitter families and lazy construction are open.
- Destination is `(point.x+dirty.x-128, point.y+dirty.y-128, dirty.w, dirty.h)`
  with 32-bit wrapping. Preserve even empty/negative dimensions at this forwarding
  boundary. Query gradient, depth and source bounds in that order, then forward
  the dirty source rectangle, by-value clip, brightness and extra unchanged.

The final child owns clipping/pixel behavior. Nested pixel fixtures use a viewport
contained in the destination surface, as required by that original caller's
contract. Source rectangles and destination placements cross its edges; source
zero is transparent, alpha varies per pixel, and depth is read without writes.
The existing `blitUnit` implements this ordinary child; this checkpoint changes no
existing composition arithmetic. Nonordinary selector cases capture arguments
and opaque image identities, not their blitter pixels.

## Evidence, guards and reproduction

| Matching fresh results | Count |
| --- | ---: |
| Signed phase windows and preserved incoming flag bits | 2,048 |
| Wrapped/paused timers and owner early return | 1,458 |
| Layer/low-byte/short-circuit flags and wrapped placement | 432 |
| House/disguise/timer selection and extreme signed inputs | 1,024 |
| Actual healthy Foot/Drive/Techno layer inside wrapper | 256 |
| Complete wrapper and actual final surface/RGB565 pixels | 384 |
| **Total** | **5,602** |

**5,602 new roots**, four inherited setup roots and one inherited alpha setup
block are audited. There are **2,096 final-child calls**: 1,712 captured argument
calls and 384 actual surface calls. **751 original RGB565 span calls**, **640
actual healthy layer calls** and 4,442 changed fixture color pixels are recorded.
Every pixel case compares full color/depth hashes; depth/alpha/source/palette and
actor/house/converter arenas must remain unchanged. All surface lock counts end
zero. Caller ESP, return address, callee-saved registers, stack tail and permitted
write ranges are guarded. Services write no guest memory. No instructions are
patched. Immutable inputs/callbacks are the domain; aliasing/mutation equivalence,
original storage/heap ownership and stock construction are not claimed.

Receipts: `private/unit-draw-1006/surface-v1/{expected,report}.json`,
`native-replay.json`, `sanitize-replay.json`, `crossing-sdl/`. They pin the exact
engine, complete inspection and relevant source identities; runner hashes are
recorded separately. Eight receipt guards and native unsupported-domain guards
pass. Earlier checkpoint sources/receipts are unchanged.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/python tools/verify_unit_surface.py \
  --exe private/official-1006-probe/game.exe
build/tools-env/bin/python tests/compare_unit_surface.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/unit-draw-1006/surface-v1/expected.json \
  --report private/unit-draw-1006/surface-v1/NEW-REPLAY.json
# Add --native build/sanitize/unit-surface-vectors for sanitizer replay.
# Fresh original execution requires the authorized Mac host JIT context:
build/tools-env/bin/python tests/compare_unit_surface.py \
  --exe private/official-1006-probe/game.exe --output private/unit-draw-1006/NEW-SURFACE
./run.command --crossing-demo
```

Normal/sanitizer builds, **7 normal / 6 sanitizer CTest checks**, **254 distinct
Python tests**, source/diff audits and actual SDL selection/right-click crossing
pass. Crossing retains 79 samples / 78 updates, 22 occluded samples / 150 maximum
hidden pixels, fresh final/no trails, cache bypass, clipping and camera return.
It checks the unchanged runtime, not integration of this new helper. Broad
unrelated numeric suites were not repeated. Only Apple Silicon macOS is tested.

## Accounting and next dependency

Fresh driver/original/native costs: **8.526/7.410/0.064 s**. Normal/sanitizer replay
driver: 0.613/1.011 s, native: 0.056/0.466 s. CTest totals: 0.22/0.85 s. Python
discovery: 0.522 s. Actual SDL: **2.331 s**. Initial/incremental build and external
fresh CLI elapsed measurements are unavailable. Checks sometimes contended;
these are not FPS claims. This continuation inherited a 06:07:06 UTC start;
the private checkpoint records closing time. Full inherited delivery time is
unavailable. No cache/coordinator/worker infrastructure was added.

Two original-generation attempts failed before any accepted receipt was saved.
The layer-four direct call initially lacked its service interception and accessed
an unprepared object; binding its inspected address fixed the fixture. The next
attempt's viewport exceeded destination bounds; the write guard rejected it.
Restricting pixel viewports to the caller contract fixed that fixture. Extreme
rectangles remain in forwarding cases. No original/native behavior was altered
to force a match, and no game playtest repair was needed.

Next recover the actual ordinary Foot depth/gradient wrappers and required stock
type/model/neutral-field associations (including the alternate split gate), then
nest the established drawing children under the Unit caller before runtime wiring.
Keep moving/turning past scenery and changing current-cell light as the observable
delivery. Full construction/ownership, decorations, scheduling, camera/fog/UI and
whole-frame parity remain open. Full base RA2/YR stays active and incomplete.
This is locally verified work, not independent acceptance or a new gameplay milestone.
