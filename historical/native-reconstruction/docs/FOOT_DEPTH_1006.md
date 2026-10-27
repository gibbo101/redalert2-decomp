# Supplied RA2 1.006 Foot depth and gradient

October 15, 2026, after `06c2c8c`. **5,952 fresh original/native results** and
normal/ASan/UBSan replays pass. Complete Foot wrappers and five cell predicates
now execute, including a narrow healthy actual base-depth path nested into final
Unit RGB565 drawing. This is a prerequisite checkpoint in the same healthy Rhino
drawing delivery. The new helper remains unwired; the observable runtime remains
[milestone 20's crossing](CROSSING_1006.md), not a new gameplay milestone.

## Identity and reference hypothesis

Exact engine: `private/official-1006-probe/game.exe`, 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Fresh generation and both replays check this identity. The previously approved
private Windows copy was not transferred again. Embedded 1.08, supplied 1.006
patch lineage and reported no-CD provenance remain separate facts; pristine
authenticity is not established. Source installations/discs, Windows task and
system configuration remain unchanged.

Consulted pinned redalert2-recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439`, `docs/voxels.md` and LICENSE,
and YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88`, `FootClass.h`,
`TechnoClass.h` and `TechnoTypeClass.h`. Hypothesis: Foot contributes cell/type
depth adjustments and optional locomotor depth/gradient before final drawing.
YR's ZFudge names are leads only; numeric offsets remain until exact base loader
association is verified. No upstream/header/generated or lifted code was adopted.

## Inspected and executed scope

`tools/verify_foot_depth.py` pins **20 complete ranges / 1,340 instructions**.

| Boundary | Patched VA | Executed scope |
| --- | --- | --- |
| Complete Foot depth / gradient | `0x4C9930`, `0x4C9A10` | Actual Unit slots `+0x2C0/+0x2C4` |
| Drive depth / gradient | `0x4A4830`, `0x4A4840`, `0x53D4B0` | Actual interface slots `+0x38/+0x3C` |
| Flag predicates, masks `0x100/0x400` | `0x6CF670`, `0x6CF820` | Complete functions |
| Three numeric predicates | `0x6CF9D0`, `0x6CFB60`, `0x6CFDA0` | Complete functions |
| Cell predicate | `0x479CC0` | Signed `+0x116` against supplied count, `+0xEC==10` |
| Coordinates and direction initializer | `0x41B320`, `0x491620` | Full signed divide/word conversion, all eight offsets |
| Existing base depth | `0x6CFEA0..0x6D050D` | Healthy height-zero, flat/ramp-zero, steady zero-facing only |

Actual Unit type/coordinate/height/kind slots are checked. Type, coordinate and
Drive leaves execute unchanged. Map lookup `0x548070` is a read-only service on
immutable supplied 9x9 cell records. Original map construction/association and
its normal fallback cell are not recovered here. Null fixture returns exercise
only the predicates' explicit null branches; two native required-current-cell
refusals are safety guards, not original malformed-input behavior.

Nested healthy base calls execute actual instructions with supplied tile registry
and `0x52B690` dimension service writing twelve zero bytes to checked stack output.
That narrow domain returns the retained native flat kernel's result. Internal
base query trace is suppressed for comparison because the native kernel models
its number, not its full query sequence; execution and write/caller guards remain.
Other base depth, ramp/bridge/status branches, stock metadata/defaults, cell flags,
tile/global construction, allocation/ownership and full frame remain open.

## Preserved decisions

`src/render/FootDepth.*` stays SDL-free. Signed coordinates divide by 256 toward
zero before signed-word truncation, including full-int inputs crossing word wrap.
This is separate from the older bounded lighting coordinate adapter. Neighbor
additions wrap words. Repeated coordinate/type/cell queries retain original order.

The wrapper queries type three times for three low-32-bit products, takes their
signed maximum with a fourth type value selected by a predicate's **low byte**,
then wraps base + maximum + optional locomotor contribution. A fourth type query
occurs only for nonzero predicate byte. Null locomotor gradient returns 2.

Both flag helpers fetch all four neighbors before testing. Center mask suffices;
south/north require bit `0x800` set, west/east require it clear. Tile predicate 0
rejects 255/65535, uses wrapped tile-minus-base-plus-one in signed range 7..16,
sets one for either of the first two qualifying tiles and increments for the third.
Predicate 2 initially returns 2 for a signed level delta at least four, but a
qualifying second delta returns 1, overriding 2. Predicate 1 preserves candidate
priority, invalid sentinel equality, repeated neighbor queries and cell tests.

## Evidence and reproduction

| Fresh matching results | Count |
| --- | ---: |
| Foot signed products, maximum, low-byte and locomotor cases | 2,048 |
| Five cell predicates, ordered queries, flags, tiles, levels and word wrap | 2,560 |
| Foot wrapper with actual cell predicates | 1,024 |
| Foot wrapper with actual healthy base depth | 128 |
| Unit final surface with actual Foot/base depth and RGB565 pixels | 192 |
| **Total** | **5,952** |

All outputs 0/1/2 for predicates 0/2 and 0/1 for 1/3/4 are covered.
**9,152 new roots**, five inherited/setup roots including the direction initializer,
and one inherited alpha block are audited. There are **320 actual base calls**,
960 guarded dimension writes, 37,412 map-service calls, 192 actual final-surface
calls and **751 RGB565 spans**. Pixel cases compare full color/depth hashes;
3,135 fixture pixels change. Depth/alpha/source/palette/actor/type/cell inputs
remain unchanged and surface lock counts return to zero. Caller ESP, return
address, callee-saved registers, stack tail and permitted writes are guarded.
No original instructions are patched. Mutable callback/aliasing equivalence and
original storage/heap ownership are excluded.

Receipts: `private/unit-draw-1006/foot-depth-v1/{expected,report}.json`,
`native-replay.json`, `sanitize-replay.json`, `crossing-sdl/`. Relevant source,
engine, inspection and expectation fingerprints are checked; runner hashes are
recorded separately. Eight receipt tests and native domain guards pass.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/python tools/verify_foot_depth.py \
  --exe private/official-1006-probe/game.exe
build/tools-env/bin/python tests/compare_foot_depth.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/unit-draw-1006/foot-depth-v1/expected.json \
  --report private/unit-draw-1006/foot-depth-v1/NEW-REPLAY.json
# Add --native build/sanitize/foot-depth-vectors for sanitizer replay.
# Fresh execution requires the authorized Mac host JIT context:
build/tools-env/bin/python tests/compare_foot_depth.py \
  --exe private/official-1006-probe/game.exe --output private/unit-draw-1006/NEW-DEPTH
./run.command --crossing-demo
```

Normal/sanitizer builds, **8 normal / 7 sanitizer CTest checks**, **262 distinct
Python tests**, source/diff audits and actual SDL selection/right-click crossing
pass. SDL retains 79 samples / 78 updates, 22 occluded samples / 150 maximum hidden
pixels, no trails, cache bypass, clipping and camera return. This verifies the
unchanged runtime, not integration of the new helper or original frame parity.
Broad unrelated numeric suites were not repeated. Only Apple Silicon macOS is tested.

## Accounting and continuation

Fresh driver/original/native: **20.284/19.467/0.072 s**. Normal/sanitizer replay:
0.647/1.079 s driver, 0.056/0.487 s native. CTest totals 0.39/1.27 s; full test
command 1.59 s. Python discovery 0.489 s, external 1.64 s. Actual SDL 3.33 s.
Build, failed-attempt and external fresh elapsed measurements are unavailable.
Some checks contended; no FPS claim. Inherited continuation began 06:21:54 UTC;
private checkpoint records closing time. Full inherited delivery time is unavailable.

Before accepted evidence, an initial build lacked a Drive include; the first
generation named nonexistent header-only `Facing.cpp`; two later generations
stopped in native comparison at the old bounded lighting coordinate guard.
A separate recovered full-word coordinate helper fixes that domain. The fourth
generation then exposed a real native north-neighbor bit-`0x800` polarity error;
exact instructions and the fifth successful generation verify its correction.
Failed logs remain private; no accepted receipt was overwritten. No game playtest
repair, Windows action, source-install/system change or worker/cache infrastructure.

Next verify stock depth/split metadata defaults and type/model/neutral-field
associations, then nest the established caller/cache/raster/staging/surface path
before runtime wiring. Moving/turning past scenery and changing current-cell light
remains the observable delivery. Full construction/ownership, decorations,
outer scheduling, camera/fog/UI and whole-frame parity remain open. Full base
RA2/YR remains active and incomplete; this checkpoint is locally verified,
not independently accepted.
