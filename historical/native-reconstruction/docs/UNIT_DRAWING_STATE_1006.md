# Supplied RA2 1.006 scoped drawing state and status timer

[UNIT_PLACEMENT_1006.md](UNIT_PLACEMENT_1006.md) now verifies the candidate
FireAngle/placement boundary below: scoped stock default 8, actual facing
initializers and complete Techno wrapper yield settled pitch 14336. Its base
placement/map/house services remain supplied; nonneutral drawing is still open.
The earlier pending statements below retain this checkpoint's date and scope.

October 15, 2026, after `b9988d5`. **2,347 fresh original/native results** and
normal/ASan/UBSan replays pass. This verifies selected constructor fields needed
by the ordinary Unit drawing path. The helper remains unwired; this is a
prerequisite checkpoint in the same moving/turning/current-cell-light delivery.
It does not establish full actor construction or original frame parity.

## Identity and reference hypothesis

Both supplied private engines were rehashed before this work:
`private/official-1006-probe/game.exe` and
`private/windows-baseline-20261014/game.exe`, 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 patch lineage and reported no-CD provenance remain
separate facts. Pristine authenticity is not established. The approved transfer
was already complete; no Windows task, source installation or system was changed.

Consulted pinned recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439`,
`docs/voxels.md` and LICENSE, and YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88`, `TechnoClass.h` and `Facing.h`.
Their facing/status fields suggested the initialization boundary. Exact base
operands and execution establish the results below; no YR layout, reference
arithmetic, header or generated code was adopted. The recomp MIT grant excludes
generated game code. No upstream code or dependency was incorporated.

## Complete routines and scoped constructor blocks

`tools/verify_unit_drawing_state.py` inherits the complete aligned constructor
inspection in [UNIT_TYPE_VISIBILITY_1006.md](UNIT_TYPE_VISIBILITY_1006.md).
It adds **five complete ranges / 49 instructions** and **nine aligned scoped
blocks / 18 instructions**:

| Complete routine | Exact patched range |
| --- | --- |
| Default Facing constructor | `0x4B89D0..0x4B89EB` |
| Rate Facing constructor | `0x4B89F0..0x4B8A23` |
| Unit status timer, slot `+0x32C` | `0x41B390..0x41B3C4` |
| Byte `+0x204` getter, slot `+0x1BC` | `0x6D6DF0..0x6D6DF6` |
| Byte `+0x205` getter, slot `+0x1C0` | `0x6D6E00..0x6D6E06` |

Scoped constructor blocks execute the actual EBX-zero setup, status timer stores,
layer-four field, two flag bytes, the three actual Facing constructors, Foot
animation-frame store and Unit staging-byte store. ESI/current-frame storage are
supplied. Complete parent inspection finds no intervening explicit EBX assignment;
preservation across omitted children is an ABI boundary, not full construction.

| Selected field | Scoped initial value |
| --- | --- |
| Barrel Facing `+0x2C8` | desired/start 0, clock current frame, duration 0, rate 768 |
| Body/turret Facing `+0x2E0/+0x2F8` | desired/start 0, clock current frame, duration/rate 0 |
| Status timer `+0x154/+0x15C` | current frame / 0 |
| Layer-four value `+0x1BC` | 0 |
| Flags `+0x204/+0x205` | 0 / 0 |
| Animation frame `+0x430` | 0 |
| Staging byte `+0x5BB` | 0 |

Facing initialization writes two angle words, zero duration dword, current-frame
dword, then zero rate word. The rate constructor writes that rate word again:
signed values at least 127 clamp to 127; otherwise the low byte becomes the high
byte of the resulting word. Negative values are not clamped to zero. Untouched
bytes, including those between angle/timer words, retain their fixture values.
Native `UnitDrawingState.hpp` models numeric fields rather than original layout.

The status getter differs from a generic nonzero timer test. Start exactly -1
returns whether signed duration is **positive**. Otherwise compute wrapped signed
elapsed, compare it with signed duration before subtracting, then require the
wrapped remainder to be **positive**. Overflow can make that last check false
even after the earlier comparison passes. The two flag getters return their raw
low bytes, including noncanonical values; their semantic names remain unassigned.

## Neutral barrel pitch remains a distinct initialization boundary

The new constructor evidence establishes barrel angle **zero**, not the **16384**
supplied as neutral pitch in [UNIT_VOXEL_DRAW_1006.md](UNIT_VOXEL_DRAW_1006.md).
Do not use constructor defaults as proof of that fixture's neutral actor state.

A private reference search found a candidate placement sequence at `0x6C4719`
that calls SetCurrent with 16384, followed by a type-byte adjustment read at
`0x6C4743` from type `+0x3A0` and another facing call. These are **inspection
leads only**: the complete parent, its acceptance gates, the stock type field,
and the nested sequence have not been verified by this suite. Verify them before
wiring the ordinary pitch assumption into runtime drawing. No replacement angle
or new runtime behavior was introduced to hide this dependency.

## Evidence, checks and commands

| Fresh comparisons | Count |
| --- | ---: |
| Signed rate clamp, low byte and constructor padding | 522 |
| Default constructor clocks/padding | 36 |
| Scoped three-Facing/scalar/byte initialization | 36 |
| Status timer signed edges, wrapping and paused values | 729 |
| Random full-word timers and every flag byte | 1,024 |
| **Total** | **2,347** |

There are **5,817 audited callable roots**, **324 scoped blocks** and **666 actual
Facing constructor calls**, including 108 nested in the parent blocks. Complete
roots enforce return/ESP/caller-tail/callee-saved guards. Blocks enforce ESP,
execution allowlists, current-frame immutability, exact ordered write widths/
values and unchanged full actor arenas, including untouched bytes outside
the selected fields. No original instruction is patched or substituted. Numeric
results are compared; native internal layout/store widths are not parity claims.

Receipts: `private/unit-draw-1006/drawing-state-v1/`, both replays and SDL.
**297 Python tests**, **9 normal / 8 sanitizer CTest checks**, builds and source/
diff/link audits pass. Actual SDL selection/right-click crossing retains 79 samples /
78 updates, 22 occluded samples / maximum 150 hidden pixels, fresh final/no trails,
cache bypass, clipping and pan return. The new helper is unused: SDL validates
the existing milestone 20 integration, not these original routines or frame parity.
Only Apple Silicon macOS is tested. Other numeric families were not regenerated.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/python tools/verify_unit_drawing_state.py \
  --exe private/official-1006-probe/game.exe
build/tools-env/bin/python tests/compare_unit_drawing_state.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/unit-draw-1006/drawing-state-v1/expected.json \
  --report private/unit-draw-1006/drawing-state-v1/NEW-REPLAY.json
# Add --native build/sanitize/unit-drawing-state-vectors for sanitizer replay.
# Fresh original execution requires the authorized Mac host JIT context:
build/tools-env/bin/python tests/compare_unit_drawing_state.py \
  --exe private/official-1006-probe/game.exe --output private/unit-draw-1006/NEW-STATE
./run.command --crossing-demo
```

## Accounting and next work

This checkpoint follows the preceding model-input review/commit; the private
accounting receipt records its start/close. Full inherited delivery time remains
unavailable. Normal/sanitizer builds: 5.56/4.93 s. Fresh external/driver/original/
native: 1.70/1.561/0.805/0.021 s. Normal/sanitizer replay external: 0.86/1.00 s;
test.command: 1.14 s; sanitizer CTest external/internal: 1.36/1.00 s; Python
discovery external/internal: 1.09/0.381 s. Concurrent checks may contend; these
are not FPS measurements. Actual SDL: 2.62 s. Closing times are in the private receipt.

No build, differential comparison or game-playtest failure occurred. Before
execution, review corrected an unverified slot guess to actual `+0x1BC/+0x1C0`
and tightened the constructor inspection interval. An exploratory whole-text
disassembly scan was stopped in favor of bounded inspection; its private leads
are not accepted evidence. The sandbox also refused a process listing; task-only
inspection/cleanup used the authorized host context. No original/native mismatch,
game repair, new cache infrastructure, extra workers or Windows/system changes.

Next verify the stock pitch-field/default and accepted placement sequence, then
combine actual Foot/base depth with the established caller/cache/raster/staging/
shadow/final-surface children before runtime wiring. Full constructors/ownership,
decorations, outer scheduling, camera/fog/UI and whole-frame parity remain open.
Full base RA2 then YR is active and incomplete; this checkpoint is locally verified,
not independently accepted or a new observable gameplay milestone.
