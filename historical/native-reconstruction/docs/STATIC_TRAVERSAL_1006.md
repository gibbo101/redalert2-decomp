# Supplied RA2 1.006 static Terrain drawing pass

October 14, 2026, Ivalice / Apple Silicon macOS. This checkpoint integrates the
bounded original static scenery pass into the preferred 1.006 prototype. It is a
prerequisite of the planned moving-Rhino/scenery crossing delivery, which remains
incomplete: general per-frame actor traversal, original redraw-region lifetime
and dynamic invalidation are still open.

## Exact source and discovery

Original: `private/official-1006-probe/game.exe`, SHA-256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Supplied patch lineage and user-reported no-CD provenance remain separate claims;
the copied Windows engine is byte-identical. No executable runs in the runtime.

The pinned YRpp reference remains
`b22f1860dd7b100cad57123d4ca5d459b9020d88`, `ObjectClass.h`,
`TerrainClass.h`, `TerrainTypeClass.h`, `TacticalClass.h`, `DisplayClass.h` and
`GeneralDefinitions.h`. Alive/IsAnimated/crumbling/type-flag names were hypotheses.
Actual base-engine slots, instructions and the `IsAnimated` loader string were
checked independently. No reference header/generated game code was incorporated.

Inspection of the complete per-frame caller at `0x6A93F0..0x6A9E08` showed a
Terrain branch testing type byte `+0x283` and actor byte `+0xB5`: when both are zero,
that branch skips ordinary Terrain. This is a static control-flow finding, **not
executed proof of the entire dynamic caller**. It led to the separate static
region scan at `0x6A9E10..0x6A9F4C`, which is executed by this suite.

Actual Terrain vtable `0x7AD3CC` dispatches type slot `+0x2C` to `0x6E4B00`,
returning `0x24`, and predicate slot `+0x44` to `0x5D4F10`, returning whether actor
byte `+0x7D` is zero. Type loading reads `IsAnimated` and stores `+0x283` at
`0x6E57A1..0x6E57C1`; inspected actor construction clears `+0xB5` at `0x6E341A`
and `0x6E3666`. Full constructor/type loader execution is outside this suite.
The names do not enable animation, death or crumbling gameplay.

`verify_static_terrain.py` checks three complete additional ranges / **109
instructions**, their actual type/predicate slots and the loader string, alongside
the nine bounds/eligibility ranges from [TERRAIN_VISIBILITY_1006.md](TERRAIN_VISIBILITY_1006.md).
Private caller leads at `0x6A4449`, `0x6A451E`, `0x6A4543`, `0x6A456A`,
`0x6A4587` and dynamic call `0x6A4EED` are retained for scheduling recovery; they
do not establish complete original frame ordering or invalidation.

## Recovered pass and native use

`src/render/StaticTerrainTraversal.*` implements the complete bounded static
region scan using supplied layer identities and explicit actor services:

- Intersect the dirty and clip rectangles with the recovered signed/wrapped
  helper, preserving its empty result rather than adding a new early return.
- Visit active ground-layer slots **in reverse order**. Registration order and
  stable equal-key insertion remain the previously recovered lifecycle behavior.
- Obtain type first, then the actual predicate. Skip non-Terrain, predicate true,
  animated type byte nonzero or actor `+0xB5` nonzero, in that order.
- Obtain render bounds and use strict wrapped overlap against the dirty/clip
  intersection after adding the global viewport origin.
- Give each admitted actor a fresh copy of the original clip rectangle, invoke
  its complete eligibility gate, then clear redraw again. This final clear occurs
  even when the nested gate rejects the actor. An actor cannot clip the next
  actor's caller bounds.

The renderer uses this pass and the recovered bounds/eligibility kernels **only
for the verified patched hash**. The retained disc profile keeps its historical
forward static rebuilding policy; new patched results are not disc proof.
Supported scenery already has guarded healthy/nonanimated metadata and recovered
ground-layer registration/cached screen positions. Native healthy construction,
an available draw context and zero animation/crumbling fields remain supplied.
Renderer-owned redraw state mirrors the prepared member state without mutating
the asset installation or immutable asset object.

Whole-viewport background rebuilding, camera/zoom and lighting invalidation remain
host policies. Rebuilds supply force=1 and use the existing recovered SHP surfaces;
the tank is subsequently drawn over the depth-bearing background. The static path
is not an interchangeable mixed painter's sort. Unit/Foot eligibility, dynamic
actor traversal and full original frame order are not established by this change.

## Executed evidence

**3,292 fresh original/native scenarios pass**, including 2,187 complete static
gate combinations; 1,024 reverse/duplicate/filter/clipping/wrap/state scenarios;
one empty layer; 64 equal-bounds supplied-order cases; and 16 scans of all 565
supported original-map placements with supplied flat screens and actual original
image bounds. Flat screen inputs are fixtures, not a map/elevation/projection
recovery claim. The supplied rules/images/map are hash recorded.

The unchanged original region routine, actual alive predicate, complete nested
eligibility and nested coordinate getters execute. Non-Terrain type IDs,
dimensions inside the scan, projection and final drawing are explicit services.
The map vectors obtain bounds through the separately executed original bounds
routine before invoking the scan. Complete rendering surfaces are verified by
earlier suites and native integration, not re-executed inside this oracle.

**12,333 audited callable roots** include the initializer, scans and map-bound
preparation. Checks cover caller return/ESP/callee-saved registers, permitted
writes, whole configured actor/type/layer/input arenas with guards/tails, ordered
actor visits/services and external redraw/bounds stores. Native traces match
those ordered events. Scratch writes, real heap ownership and full actor lifetime
remain outside this audit.

Accepted current receipts are `private/traversal-1006/static-v2/expected.json`,
`report.json`, `native-replay-report.json` and `sanitize-report.json`.
Normal and ASan/UBSan replay pass. The earlier `static/` checkpoint retains its
own older source identities after replay guards were strengthened; do not relabel
it as current evidence. Five static replay guards and seven inherited visibility
guards pass. All 9,364 current visibility results also pass sanitizer replay.

Native/sanitizer builds and CTest pass. The patched full owned-data command passes:
all existing presentation/cache/light/occupation/lifecycle/scenery checks, 19
light/profile checks, 81 scenery/profile/export checks, and both actual 170-frame
SDL input/rendering regressions. Retained-disc owned presentation and both SDL
regressions pass; patched sanitizer owned presentation passes. A diagnostic
Rhino/pole overlap frame was inspected. These are integration checks, not original
frame/input parity or a completed moving crossing observation.

## Reproduce

```sh
./build.command
./run.command
# T cycles scenery; P cycles props; H returns to the tank.
./test.command --data-dir "$PWD/private/official-1006-probe"
build/tools-env/bin/python tools/verify_static_terrain.py \
  --exe private/official-1006-probe/game.exe
build/tools-env/bin/python tests/compare_static_terrain.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/traversal-1006/static-v2/expected.json \
  --report private/traversal-1006/static-v2/NEW-REPLAY.json
# With README's sanitizer build, add --native build/sanitize/static-terrain-vectors.
build/tools-env/bin/python tests/test_static_terrain_evidence.py
# Fresh original execution, in the authorized host JIT context:
build/tools-env/bin/python tests/compare_static_terrain.py \
  --exe private/official-1006-probe/game.exe \
  --output private/traversal-1006/NEW-STATIC-ORIGINAL
```

Fresh evidence refuses existing receipts. Replays check source/engine/asset/
inspection identities and receipt fingerprints, run no original instructions,
record the rebuilt native runner separately and cannot overwrite original proof.
Private files/source installations remain outside Git and unchanged.

## Delivery accounting and next dependency

Current fresh CLI: **2.815 s total**, 2.101 s original generation and 0.227 s native.
Normal replay: 0.983 s total / 0.224 s native; sanitizer replay: 1.086 s total /
0.306 s native. Separate receipts preserve these measurements. Earlier elapsed
delivery/build/owned/SDL costs were not instrumented and are unavailable; no
precise whole-delivery total is claimed. Inherited committed work is the 1.006
promotion and `9194568` bounds/eligibility recovery. No cache infrastructure or
playtest repair was needed. A syntax-only check previously tried the system Python
cache outside the sandbox; in-memory compilation resolved it without escalation.

This remains a locally verified checkpoint, not independent acceptance. Continue
the chosen crossing delivery: execute the complete bounded ordinary per-frame
traversal on actual Unit/Foot/Terrain dispatch, recover the missing scheduler/
redraw-region services, and exercise a reproducible moving tank past scenery.
Preserve conservative movement clearance, static construction/visibility policies
and explicit full-frame limits. The full native game/YR goal remains active.
