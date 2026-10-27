# Supplied RA2 1.006 Terrain draw eligibility checkpoint

Runtime update: [STATIC_TRAVERSAL_1006.md](STATIC_TRAVERSAL_1006.md) subsequently
wires these kernels into the patched static scenery pass. The original checkpoint
description below preserves its prerequisite scope; general actor traversal and
the crossing delivery remain incomplete.

October 14, 2026, Ivalice / Apple Silicon macOS. This is a focused recovery
checkpoint toward the moving-Rhino/scenery crossing delivery. The native kernels
are available to the renderer but are **not yet wired into runtime traversal**.
The existing immutable scenery layer followed by tank drawing remains a host
policy. This checkpoint does not complete that observable delivery.

## Identity and reference boundary

Original: `private/official-1006-probe/game.exe`, 4,485,392 bytes, SHA-256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
It matches the approved private Windows transfer. Embedded 1.08 and user-reported
no-CD provenance remain recorded separately from supplied 1.006 patch lineage.
This suite accepts this exact engine only; no disc/YR mapping is inferred.

Consulted YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88`,
`ObjectClass.h`, `TerrainClass.h`, `TacticalClass.h`, and `DisplayClass.h` for
DrawIfVisible/GetRenderDimensions/visibility hypotheses. Those names and layouts
were leads; no header or generated recompilation code was incorporated. The
existing [reference and license boundaries](REFERENCES.md) still apply.

`tools/verify_terrain_visibility.py` checks nine complete ranges / **425 decoded
instructions**, actual Terrain/Type RTTI and virtual slots, and empty-rectangle
initial data. The original initializer also executes in the oracle.

| Routine | Patched address | Scope |
| --- | --- | --- |
| Rectangle intersection | `0x41FDF0` | Complete, optional independent X/Y adjustments |
| Terrain eligibility | `0x6E4430` | Complete, dimensions/projection/draw boundaries below |
| Terrain render bounds | `0x6E4910` | Complete ordinary SHP metadata path |
| Empty rectangle initializer | `0x6E2FE0` | Complete |
| Image dispatch | `0x5D27B0` | Actual type/image virtual dispatch |
| Terrain type getter | `0x6E4900` | Actual actor type pointer |
| Type image getter | `0x41C300` | Actual image pointer |
| Render coordinates | `0x41B270`, `0x5D4E40` | Actual nested coordinate getters |

## Recovered behavior

`src/render/TerrainVisibility.*` contains readable SDL-free C++ kernels.

- Intersection preserves signed comparisons, sequential truncation and low-32-bit
  wrapping. Both original extents must be positive. A failed extent returns four
  zeroes, and optional adjustment values change only on success, by original
  viewport origin minus clipped origin. This is deliberately not a general
  mathematical rectangle-intersection API.
- Render bounds subtract tactical origin from cached screen coordinates, use
  body frame zero and shadow frame count/2, and interpret canvas/crop metadata as
  signed words. Nonpositive first crop selects the second; nonpositive second
  retains a valid first. Extending right/bottom to the second crop adds one extra
  pixel. Moving the left/top edge alone does not. Canvas halves divide toward zero.
  Null image returns the initialized empty rectangle without screen translation.
- An unnamed global byte or null global context bypasses the initial state gates.
  Otherwise force's low byte can bypass the redraw requirement, while on-map must
  be nonzero and limbo zero. No global or argument meaning is inferred from YR names.
- Accepted initial gates clear redraw **before** intersecting and overwriting the
  caller's bounds, then obtain render bounds even when the intersection is empty.
  Strict wrapped overlap comparisons decide whether to proceed. Do not add an
  early empty-intersection rejection: some unusual inputs still pass those tests.
  The routine obtains coordinates, calls projection, adjusts the point for a
  clipped left/top origin, then dispatches DrawIt and returns true. The projection
  boolean and third eligibility argument are not used.

Negative signed frame counts, pointer aliasing between optional adjustment
outputs, malformed image pointers and unbounded frame metadata are not supported
claims. Native negative-count refusal is a safety guard. Metadata tests with signed
negative crop words do not enable drawing malformed SHP files.

## Executed evidence and audits

**9,364 fresh original/native results pass**, with identity-checked normal and
ASan/UBSan replays. Groups: 3,096 intersections; 816 actual tree/prop metadata bounds;
1,024 synthetic signed/empty/odd/union metadata cases; 12 null-image bounds;
1,536 complete state gates; 2,048 clipping/strict-overlap/projection-result cases;
832 complete eligibility calls through actual owned-image or null-image bounds.
All 51 supplied ordinary images are included, with source hashes.

The oracle executes unchanged instructions and actual Terrain/type/image/
coordinate dispatch. For isolated gate vectors, dimensions are supplied; combined
vectors execute the complete original dimensions routine. Projection and final
DrawIt remain supplied services in every eligibility vector. Earlier independently
verified projection and surface routines are not reclassified as executed here.

9,365 callable roots include the initializer. Root return addresses, ESP,
callee-saved registers, caller-owned stack, all writes outside stack/declared
outputs, whole 64 KiB fixture arenas including guards/tails, ordered external
redraw/bounds writes and service order are checked. Native traces match those
ordered external events. Internal scratch writes, whole real actor storage,
original traversal/drawing, visibility scheduling and actor/cache lifetime remain
outside this evidence. Native/sanitizer CTest and seven synthetic evidence
invalidation guards pass.

Private accepted receipts: `private/traversal-1006/visibility-integrated/`, containing
`expected.json`, `report.json`, `native-replay-report.json` and `sanitize-report.json`.
The earlier 8,532-case `visibility/` receipt is a superseded exploratory checkpoint
with its own older source identities; do not replay it as current proof. Static
traversal discovery dumps in the parent folder remain unverified leads.

An initial mixed-suite attempt missed a narrow service hook on a previously
translated Unicorn block and failed comparison before saving evidence. Permanent
service hooks are now installed before dimensions/getter translation. This was a
fixture instrumentation repair, not a native parity fix or accepted result.

## Reproduce and continue

```sh
./build.command
build/tools-env/bin/python tools/verify_terrain_visibility.py \
  --exe private/official-1006-probe/game.exe
build/tools-env/bin/python tests/compare_terrain_visibility.py \
  --exe private/official-1006-probe/game.exe \
  --output private/traversal-1006/NEW-ORIGINAL-RUN
# Fresh original execution needs the authorized host JIT context.
build/tools-env/bin/python tests/compare_terrain_visibility.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/traversal-1006/visibility-integrated/expected.json \
  --native build/sanitize/terrain-visibility-vectors \
  --report private/traversal-1006/visibility-integrated/NEW-REPLAY.json
build/tools-env/bin/python tests/test_terrain_visibility_evidence.py
```

Fresh runs refuse existing original receipts. Replay checks source, original,
asset, inspection and expectation/receipt identities before and after execution,
records the current native binary separately, and never invokes Unicorn. It
cannot replace original evidence. Existing exported private assets are required;
the suite never writes the supplied installation or exports into it.

The accepted fresh CLI took approximately 3 seconds; exact generation/native/
total times are in its receipt, with sanitizer/native replay times in separate
receipts. Whole inherited delivery elapsed/build costs remain unavailable. No SDL
playtest was repeated for these unused kernels; actual rendering/input checks
remain required at the crossing delivery boundary. No new caching infrastructure.

Next: resolve the complete traversal caller beginning at the `0x6A93F0` discovery
lead, actual Terrain/type eligibility field initialization, ordered layer visits,
stable ties, skipped actors and redraw transitions. Then integrate mixed actors
and dynamic invalidation into a reproducible crossing scenario. Preserve existing
conservative movement clearance and all full-frame/visibility limitations.
