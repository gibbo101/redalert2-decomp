# Supplied RA2 1.006 nonneutral barrel pose and cache decisions

October 15, 2026, after `812e463`. **5,379 fresh original/native comparisons**
and normal/ASan/UBSan replays pass. The complete healthy Unit voxel root now
executes with nonneutral barrel facing and independently warm/empty turret and
barrel caches. Its readable native helper accepts a barrel facing and preserves
all tested matrix words and forwarding decisions. The helper remains unwired;
current gameplay still uses the earlier flat barrel presentation.

This closes the pose prerequisite exposed by [UNIT_PLACEMENT_1006.md](UNIT_PLACEMENT_1006.md).
It does not establish firing, pitch-driven cache invalidation, complete actor
construction, raster pixels or whole-frame parity. The same moving/turning/
current-cell-light drawing delivery remains active.

## Identity and reference hypothesis

The hash gate rechecks the supplied base engine at
`private/official-1006-probe/game.exe`, 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
The preceding checkpoint rehashed it equal to the authorized private Windows copy.
Embedded 1.08, supplied 1.006 lineage and reported no-CD provenance remain distinct;
pristine authenticity is not established. No Windows task, transfer, source
installation/disc or system configuration changed.

Consulted [REFERENCES.md](REFERENCES.md)'s voxel/cache entry: pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439`, `docs/voxels.md` (part chain,
staging, cache cost) and LICENSE, plus YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88`, `TechnoClass.h` BarrelFacing.
Hypothesis: the original barrel facing changes pose on a miss while cached part
images may bypass geometry. Exact base instructions and execution establish the
behavior below. No YR layout/arithmetic, upstream/header/generated or lifted code
was incorporated. The inspected MIT scope excludes generated game code; no new
dependency or notice is needed.

## Recovered boundary

`tools/verify_unit_voxel_draw.py` now pins **30 complete ranges / 2,396
instructions**, including complete root `0x6FF690..0x7005A5`, selected Drive,
Foot, Facing, matrix/trig and cache-precheck children. It verifies the barrel
field/call/quantization/angle-store/rotation operands at `0x6FFD21..0x6FFD55`.
The new execution allowlist also explicitly pins inherited floating-to-integer
helper `0x77F110..0x77F14C` and height arithmetic `0x6A2970..0x6A29AB`.
These add 33 inspected instructions; their presence is not a new depth-domain claim.

On the ordinary flat, zero-offset path:

- Quantize barrel Current with the same 32-bin heading rule, subtract eight,
  multiply by the original binary64 heading step, negate, and store float32.
- The original `0x590880` rotates matrix **X/Z columns** using table sine/cosine.
  Its first store is `X*cos - Z*sin`; its second is `X*sin + Z*cos`, using old
  column values and float32 stores. Body/turret heading rotation uses X/Y.
- Rotate the pre-camera turret pose, then multiply by the supplied camera.
  The original surrounds rotation with translations about the turret pivot;
  this domain has zero translation. Nonzero offset, recoil, tilt and ramp pivots
  are outside this helper's claim.
- Preserve the existing turret/barrel key. This caller does **not** add pitch to
  it. If turret and any present barrel have cached images, copy the untransformed
  body matrix and skip the pitch query/rotation. Otherwise build both poses,
  including when only one part is cached. A missing barrel does not require a
  barrel cache hit before the shortcut.
- Preserve every existing part-order, signed frame remainder, dirty/surface
  store, Foot forwarding, brightness/status and shadow/stencil decision.

Stock placement's supplied sampled facings 16384 and 15360 both quantize to bin
8; settled 14336 quantizes to bin 7. These three drawing cases use **steady facing
fixtures**, not an actual placement-to-draw actor lifecycle. Placement and its
transient numeric sequence have their own exact evidence. The API's default
16384 retains the earlier neutral fixture; it is not stock settled initialization.

Cache inputs are matching hot entries or empty counts, independently per part.
The test does not recover cold searches, compressed storage, eviction, cache
invalidation when barrel state changes, construction or ownership. Do not add
pitch to runtime cache identity, force rebuilding or reuse a stale image as a
claimed original lifecycle solution without recovering the responsible caller.

## Evidence and verification

| Fresh results | Count |
| --- | ---: |
| Prior complete-root neutral scenarios, freshly executed on changed sources | 3,200 |
| Settled stock pitch over all body/turret bin pairs | 1,024 |
| Every pitch bin, four cache masks, barrel absence, key bypass and two cameras | 1,024 |
| Raw pitch ties/wrap | 128 |
| Three supplied stock placement samples | 3 |
| **Total** | **5,379** |

There are **5,379 audited roots**, **20,353 bounded supplied writes**, **3,669
actual barrel Facing/rotation/pose-build calls** and **1,710 warm matrix-copy
branches**. Every ordered event, argument and raw matrix dword matches. Return
address, ESP, callee-saved registers, caller tail, fixture arena, allowed image
writes and execution ranges are checked. No original instruction is modified.
Surface/map/visibility/height/brightness/status/final Techno drawing remain supplied
services. Camera, ramp-zero identity and initialized dirty template are inputs.
Native object layout, arbitrary callback mutation and aliasing are not parity claims.

Receipts: `private/unit-draw-1006/barrel-v1/{expected,report}.json`, normal and
sanitizer replays. Earlier `voxel-root-v1/` retains its original sources and neutral
domain; it was not overwritten or relabeled. Changed-source evidence freshly
executes its 3,200 scenarios instead of relaxing identity checks.

**305 Python tests**, **9 normal / 8 sanitizer CTest checks**, native builds and
source/diff/link audits pass. The executable remains arm64 Mach-O. Actual unchanged
SDL selection/right-click crossing passes: 79 samples / 78 updates, 22 occluded
samples / maximum 150 hidden pixels, fresh final/no trails, bypass, clipping and
pan return. SDL checks milestone 20 integration; it does not execute this unwired
helper or establish original frame parity. Only Apple Silicon macOS is tested.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/python tools/verify_unit_voxel_draw.py \
  --exe private/official-1006-probe/game.exe
build/tools-env/bin/python tests/compare_unit_voxel_draw.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/unit-draw-1006/barrel-v1/expected.json \
  --report private/unit-draw-1006/barrel-v1/NEW-REPLAY.json
# Add --native build/sanitize/unit-voxel-draw-vectors for sanitizer replay.
# Fresh original execution requires the authorized Mac host JIT context:
build/tools-env/bin/python tests/compare_unit_voxel_draw.py \
  --exe private/official-1006-probe/game.exe --output private/unit-draw-1006/NEW-BARREL
./run.command --crossing-demo
```

## Accounting and next work

Started 08:14:18 UTC; private accounting records closing time. Full inherited
delivery elapsed remains unavailable. Normal build passed without a separate
elapsed measurement; sanitizer build took 4.42 s. Fresh external/driver/original/
native: **71.42/71.198/70.610/0.151 s**. Replay/check/SDL measurements are in the
private checkpoint. The allowlist adds research overhead; no cache infrastructure
was added or performance/FPS claim made.

Two preliminary pilot executions stopped at previously unlisted inherited helpers;
each was inspected in full before allowing it. The final four-case pilot matched.
Their external times were 0.234/0.251/0.371 s. A sanitizer launch could not find
`cmake` on PATH (0.00 s); the existing bundled path succeeded. No compilation,
original/native numeric comparison or game-playtest failure/repair occurred.
No workers or Windows/source/system changes occurred.

Next combine actual Foot/base depth and the established Unit caller, lit-cache,
raster, staging, shadow and final-surface children before runtime wiring. Keep
stock pitch as an explicit input until the responsible lifecycle/invalidation
is established. Full construction/ownership, outer Unit/Foot placement,
decorations, scheduling, camera/fog/UI and whole-frame parity remain open.
Full base RA2 then YR remains active and incomplete; this is locally verified
recovery, not independent acceptance or a completed new gameplay milestone.
