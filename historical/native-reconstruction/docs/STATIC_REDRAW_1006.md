# Supplied RA2 1.006 static redraw request caller

October 14, 2026, following redraw checkpoint `6c4f48d`. The complete static
request caller now executes with the recovered nested Terrain scan/eligibility.
**1,172 fresh original/native results** and normal/ASan/UBSan replays pass. The
native patched renderer uses its full-viewport branch. The moving crossing remains
open: dynamic Unit traversal and the original outer frame scheduler are not wired.

## Identity and references

Only the supplied patch engine at `private/official-1006-probe/game.exe` is
accepted: SHA256 `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`,
4,485,392 bytes. Embedded version 1.08, supplied 1.006 lineage, byte equality with
the approved private Windows transfer and user-reported no-CD provenance remain
separate facts. Pristine authenticity is not established. Disc proof is separate.
No original file, instruction, Windows state or global system setting changed.

Continued the pinned YRpp Object/Display/Map/Tactical and recomp voxel-chain leads
recorded in REFERENCES.md and REDRAW_1006.md. Hypothesis: the static caller consumes
visible-cell/dirty-region requests independently of dynamic Unit traversal. Exact
base-binary call links and execution establish the result. No upstream/header/
generated or lifted game code was incorporated.

`tools/verify_static_redraw.py` pins **six complete ranges / 293 instructions**,
plus the inherited static Terrain inspection:

| Routine | Address |
| --- | --- |
| Complete static redraw request caller | `0x6A4350` |
| Coordinate initializer | `0x41B630` |
| World projection | `0x6A27A0` |
| Projection scale initializers | `0x6A20E0`, `0x6A2170`, `0x6A2440` |

All five caller links to `0x6A9E10` are checked. The actual caller, coordinate
initializer, world projection/scale initializers, nested complete static Terrain
scan and nested Terrain eligibility execute. Actual type/alive/coordinate methods
execute. Render dimensions, tactical projection and final Terrain drawing remain
supplied services; final surfaces are not compared in this oracle.

## Preserved behavior and runtime boundary

`src/render/StaticRedraw.*` preserves:

- Visible cells in forward supplied order, each making a 60x30 request. Signed
  word coordinates pass through `(cell*256+128)/256*256`, dividing toward zero.
  Negative cells therefore do not reduce to an unconditional `cell*256`. Projection
  precedes origin adjustment, X minus 30 and viewport Y addition.
- Dirty regions in reverse order, adding viewport Y before intersection. Only
  positive intersections request drawing. The region flag is not consulted here.
- Visible-cell and dirty-region requests occur **before** the full-viewport test.
  A nonzero low byte then requests the viewport, even if its extents are invalid.
  Otherwise first edge, then second edge request drawing only with positive sizes.
- Every nested scan receives force=1. Cell/dirty calls receive distinct copies
  with equal values; full/edge calls alias both rectangle arguments. Rectangles
  and collections stay immutable across the actual scan.

Native safety bounds are 800 visible cells, 128 dirty regions and the existing
world-projection coordinate domain of +/-1,048,576 leptons. Larger inputs are
refused before callbacks. They are not original malformed-input behavior.

The patched Renderer now invokes this caller with **empty visible/dirty lists and
full=1** when its host terrain cache rebuilds, then uses the recovered reverse
Terrain scan and drawing gate. It preserves the previous output. The host still
chooses whole-viewport invalidation and owns the color/depth/alpha cache. Recovered
queue kernels are not yet connected to original frame/camera invalidation. The
retained disc renderer is unchanged; patched evidence is not relabeled as disc.

## Evidence and reproduction

Private receipts: `private/traversal-1006/static-redraw/{expected,report}.json`,
`native-replay-report.json`, `sanitize-report.json`; previews remain private.
**1,176 audited roots** include the empty and three scale initializers.

| Group | Results |
| --- | ---: |
| Full argument low byte after cell/reverse-region requests | 7 |
| Signed cell conversion and projection | 98 |
| Edge size filters and argument aliasing | 25 |
| Combined request order, clipping/wrap, gates and actor state | 1,024 |
| 575 synthetic static actors with multiple requests | 16 |
| Empty caller and 800 visible-cell maximum | 2 |
| **Total** | **1,172** |

Dense actors are synthetic, not the map's 565 supplied placements. Comparisons
include request argument/order/aliasing, final redraw bytes and nested ordered
writes/events. Callable guards cover ESP/registers/return/caller stack; fixture
arenas, metadata, capacity tails, viewport and inputs remain unchanged except
permitted redraw bytes. Source/inspection/engine/receipt identities are required.

```sh
./build.command
./run.command
./test.command --data-dir "$PWD/private/official-1006-probe"
build/tools-env/bin/python tools/verify_static_redraw.py \
  --exe private/official-1006-probe/game.exe
build/tools-env/bin/python tests/compare_static_redraw.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/traversal-1006/static-redraw/expected.json \
  --report private/traversal-1006/static-redraw/NEW-NATIVE-REPLAY.json
# Add --native build/sanitize/static-redraw-vectors for sanitizer replay.
build/tools-env/bin/python tests/test_static_redraw_evidence.py
# Fresh execution needs the authorized Apple Silicon host JIT context:
build/tools-env/bin/python tests/compare_static_redraw.py \
  --exe private/official-1006-probe/game.exe --output private/traversal-1006/NEW-STATIC-REDRAW
```

Seven new evidence guards, native collection/coordinate safety guards, all **209
Python tests**, normal/sanitizer CTest, source audit and diff checks pass. Patched
owned-data decoding/lighting/cache/scenery/presentation pass on normal/sanitizer
builds. Both actual 170-frame SDL regressions pass, with and without the light demo.
A new overlapping Rhino/pole preview was inspected as visual QA only. No original
whole-frame, moving crossing or original input/scheduler parity is claimed.

## Accounting, failed attempt and continuation

Fresh CLI: 6.182 s total / 5.236 s original / 0.198 s native. Replay native costs:
0.209 s normal / 0.445 s sanitizer. Python discovery: 0.270 s; sanitizer CTest:
0.28 s. Actual SDL checks: 1.79 s ordinary / 1.67 s with light. Separate elapsed
build, owned-data and inherited whole-delivery measurements are unavailable.

The sandboxed owned-data command passed its non-SDL checks, then failed SDL with
"The video driver did not add any displays". Both affected SDL commands were
rerun successfully with authorized desktop access. No parity failure, playtest
repair, original mutation or system change was required.

Next integrate the already verified dynamic caller/Unit gate/getters with explicit
host camera inversion, healthy actor/layer inputs and redraw lifetime boundaries.
Exercise a moving Rhino past scenery with actual SDL input/rendering and record
depth/visit evidence; keep conservative routing. Original outer frame scheduling,
complete Unit DrawIt, general actor ownership, UI/extras and whole-frame parity
remain open. No extra worker or Windows action is needed. Full game/YR is incomplete.
