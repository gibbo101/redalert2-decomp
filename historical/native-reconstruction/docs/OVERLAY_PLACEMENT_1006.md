# Supplied RA2 1.006 ordinary temporary Overlay placement

October 15, 2026, after `ddff77e`. This continues the same terrain-aware
Foot/world crossing and parked `(51,72)`, elevation 4 capability. The decoded
reader's temporary-constructor service now has separately verified readable C++
for ordinary loaded overlays. It is not yet nested into the reader or wired into
runtime. This is a locally verified checkpoint, not a completed playable milestone
or independent acceptance. Full base RA2 then YR remains incomplete.

## Identity and references

Both supplied private engines retain SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`,
4,485,392 bytes. Embedded 1.08, supplied 1.006 lineage and reported no-CD changes
remain separate provenance; pristine authenticity is unverified. The Windows
transfer was already complete. No new Windows/transfer/source-install/system
action, worker, dependency or upstream code is part of this checkpoint.

Consulted [REFERENCES.md](REFERENCES.md), pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` `docs/voxels.md`/LICENSE and YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` `OverlayClass.h`,
`ObjectClass.h`, `OverlayTypeClass.h`, `CellClass.h` and `MapClass.h`.
Hypothesis: temporary Overlay placement changes Cell state and retires its actor,
so Terrain's persistent lifecycle cannot be applied unchanged. Exact base
execution establishes the bounded decisions below. YR headers are leads and
recomp is not an oracle. No upstream/header/generated/lifted code was incorporated.

## Recovered boundary

[OverlayPlacement.cpp](../src/assets/OverlayPlacement.cpp) keeps explicit base,
storage, resource/recalculation and retirement services. Supported scope is a
nonzero loading global, ordinary nonwall/nonbridge/no-animation type. Walls,
land 9, CellAnim, indices 0x18/0x19/0xED/0xEE/0x7E/0xA7 and ranges
0x7A..0x7D/0xE9..0xEC are refused before mutation. These are native scope guards,
not original malformed-input or alternate-overlay behavior.

| Complete actual range | Executed behavior |
| --- | --- |
| `0x5DA7D0..0x5DA8CF` | Complete Overlay constructor |
| `0x5DA970..0x5DB623` | Complete Overlay Mark, bounded ordinary loaded path |
| `0x5D3890..0x5D3BC8` | Object Unlimbo with actual Overlay dispatch |
| `0x5D4160..0x5D422E` | Object Mark with supplied absence of attached animation |
| `0x5DC170..0x5DC177` | Overlay type getter |
| `0x5DCD50..0x5DCD6F` | OverlayType placement adjustment: copy X/Y/Z unchanged |
| `0x5D51C0..0x5D51DD` | Three ordered position stores |
| `0x41B320..0x41B35D` | Signed divide-by-256 then word-coordinate getter |
| `0x5D36E0..0x5D36F8` | Zero-to-one redraw flag and supplied queue request |
| `0x5DC2E0..0x5DC2E6` | Overlay kind 0x14 |
| `0x40FFD0..0x40FFF5` | Identity assignment with absent or present provider |
| `0x663170..0x66317E` | Wrapped uint32 identity-counter increment |

All **12 complete ranges / 1,339 inspected instructions** are entered. Actor
and type vtable slots are pinned, including placement/Mark/getters/adjustment and
the supplied retirement target. Complete Object constructor
`0x5D22E0..0x5D24F1` and retirement `0x5D4E90..0x5D4F0C` add **194 inspected
instructions**, but are **inspection only** and supplied services here.
Original code remains unchanged.

Constructor order: supplied Object construction, type store, identity child,
transient-registry append, invalid-position test, placement-global flag store,
centered Cell-to-world conversion, actual Object Unlimbo, then flag reset to **-1**.
The reset does not restore the incoming global value and occurs after rejected
Unlimbo too. Invalid coordinates skip both flag stores but still consume identity
and registration. Append stores count before slot. Growth needs owned storage or
zero capacity, positive increment and a nonzero low byte of its supplied result.

Identity-provider global `0xA3D290` is separate from map-loading global `0xA40774`.
Absent provider yields token zero. Present provider increments its +0x214 counter
with uint32 wrapping before storing actor +0x10. Provider initialization,
association and lifetime remain supplied; no complete startup claim follows.

Object Unlimbo requires nonzero enable/limbo and zero onMap. In the loaded profile
it clears limbo/redraw, executes the actual OverlayType copy adjustment, stores
position and calls Overlay Mark mode 1. Mark failure resets limbo to one without
rolling back earlier writes. A successful temporary Mark requests retirement;
the fixture retirement service clears active, so later persistent actor/layer/
logic/alpha/radial branches are not entered. Do not substitute Terrain's ground
adjustment or its post-Mark onMap condition.

Overlay Mark first executes actual base Mark. Modes 0 and 2 can mutate base state
but Overlay Mark still returns false; only accepted 1/3 enter placement. It queries
Cell through signed word coordinates. Slope >4 rejects except index **0xB2**,
preserving prior base writes. Loading skips the ordinary permission/Overrides
branch. Store overlay index, then data zero. Land 5 stores data one then requests
resource update with zero; a nonzero crate byte subsequently stores **255**.
Request Cell recalculation with -1, clear onMap, set limbo and request retirement.
That order is essential: an overlay updates a Cell, not a persistent Terrain actor.

## Evidence and remaining services

Current receipts: `private/map-depth-1006/overlay-placement-v3/`.
**1,180 fresh original/native results** and both normal and ASan/UBSan replays pass:
288 base/Mark decisions, 96 slope/dummy/resource/crate decisions, 144 Unlimbo gates,
264 registry/invalid-position cases, 384 seeded constructor cases and four explicit
identity absence/zero/wrap cases. All complete roots execute through actual dispatch.

Counts: 1,180 outer audits; 652 constructor/identity, 651 counter, 641 Overlay/base
Mark, 655 Unlimbo, 257 type getter/adjust/set, 359 word getter, 361 redraw and 416
kind entries. Compare **7,421 ordered selected guest stores**, **2,566 supplied
service calls**, complete selected actor/Cell state, identity counter, global flag,
registry count/capacity/ownership/all slots and service/store digests. Caller
stack/register/return address, immutable type/input/global/vtable records, actor/
Cell nonselected bytes and capacity tails are guarded.

Base Object construction deliberately supplies varied flags/position. Registry
growth/heap, absence of attached animation, redraw queue, Cell lookup/storage,
resource update, recalculation and retirement effects remain services. Resource
fixture writes a chosen byte; retirement fixture clears active. Those effects are
explicit fixture choices, not new executions of the corresponding Cell or lifetime
roots. Earlier separately verified Cell kernels are not yet nested here. Full
Object defaults/registrations, actual retirement/queue/destruction, alternate
overlays and complete map startup remain open.

v1 predates final inspection-only metadata; v2 keeps a provider-zero boundary.
v3 freshly executes the final source and adds actual provider/counter execution
and four cases. Earlier receipts remain historical and are not relabeled.

Both builds, **532 Python tests**, **32 normal / 31 sanitizer CTests**, source/diff/
local-link audits pass. All prior 36 source/runner sets and decoder stay current;
final audit is **38 sets / 810 source entries**. Actual rebuilt SDL baseline passes
selection/right-click, 79 samples/78 updates, lighted crossing, culling/clipping/
cache bypass/pan return. This is existing native integration, not new overlay or
original-frame parity. Only Apple Silicon macOS is tested.

Final driver/original/native 0.972/0.609/0.036 s (CLI 1.106 s). Normal/sanitizer
replay CLI 0.583/0.822 s. Final normal/sanitizer builds 14.806/9.643 s; test.command
1.147 s, sanitizer CTest 2.805 s, Python CLI 0.990 s, SDL 3.344 s. Earlier successful
builds/proofs/replays remain in private overlay-placement timing files. No original/
native mismatch, failed build/test or gameplay repair occurred in this checkpoint.
Inspection corrected the provisional identity-zero boundary before final evidence.
Full active-delivery and initial continuation elapsed remain unavailable.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
# Fresh original execution needs the authorized host JIT context and unused output.
build/tools-env/bin/python tests/compare_overlay_placement.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/overlay-placement-new
build/tools-env/bin/python tests/compare_overlay_placement.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/overlay-placement-v3/expected.json \
  --report private/map-depth-1006/overlay-placement-v3/replay-new.json
# Add --native build/sanitize/overlay-placement-vectors for sanitizer replay.
./run.command --crossing-light-demo
# Select Rhino; G/right-click moves, L toggles light, R resets.
```

Continue actual base/retirement/cleanup dependencies and map-required wall/bridge
placement, then nest the reader and Cell/resource/recalculation children on shared
state. Complete overlay-bearing map resource/wall-owner effects before prepared
Cell/TMP-to-Foot/base-depth and Unit/world runtime integration. Require actual SDL
level crossing and parked cliff before capability completion. Runtime depth fields
remain neutral; parser/defaults/actor/contact/cache/heap lifetime, scheduling/camera/
fog/UI/pathfinding and whole-frame parity stay open.
