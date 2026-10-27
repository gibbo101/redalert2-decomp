# Ordinary Terrain placement, removal and layers — milestone 19

[TERRAIN_LIFECYCLE_1006.md](TERRAIN_LIFECYCLE_1006.md) adds independently mapped,
freshly executed disc/1.006 profiles and both sanitizer replays, preserving ordered
writes/arenas/capacity tails and the whole-map sequence. Its protected replay paths
supersede the historical paths below; runtime/data promotion remains pending.

October 14, 2026. Baseline `aa0b5a3`. Ivalice / Apple Silicon macOS.

The prototype prepares **565 ordinary scenery actors**, including occupation,
**4,520 neighbor contributions**, projected screen coordinates and sorted ground
layer registration. Rendering consumes that registration order. **3,868 new
original/native vector results pass**, including a **1,695-call** whole-map
place/remove/restore sequence. This extends [OCCUPATION.md](OCCUPATION.md).
It does not recover original construction, global draw/update scheduling, mixed
unit/scenery traversal, visibility or locomotor clearance. Conservative exclusions
remain active. The renderer still rebuilds an immutable static layer as a host policy.

## Identity and references

Exact original: the user's Allied-disc GAME.EXE, embedded **1.08**, image base
`0x400000`, SHA-256:
`135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743`.
Every original oracle checks that hash. The runtime executes no original instructions
and reads executable **track data only**. No new table or dependency was added.

Consulted [REFERENCES.md](REFERENCES.md) and YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88`, `ObjectClass.h` Limbo/Unlimbo,
LastLayer/GetYSort/InWhichLayer, `ObjectTypeClass.h` IsLogic, `TerrainClass.h`
and `DisplayClass.h` Submit/Remove. These supplied lifecycle/layer vocabulary and
call-chain hypotheses. All addresses and operations were located independently
in our base executable. The YRpp snapshot lacks an incorporation license; no
header code was reused. The pinned recomp/tooling references are neither this
runtime architecture nor an original lifecycle oracle. No generated output was copied.

| Unchanged original routine/data | Exact base address |
| --- | --- |
| Terrain Unlimbo / Limbo | `0x6D9940` / `0x6D9290` |
| Object Unlimbo / Limbo | `0x5CBDD0` / `0x5CBC40` |
| Terrain type position adjustment / coordinate setter | `0x6DA9C0` / `0x5CD700` |
| Terrain placement/foundation dispatch | `0x6D8E20` |
| Display Submit / Remove | `0x4996D0` / `0x499720` |
| Layer insert / sorted insert | `0x5329B0` / `0x532A90` |
| Comparator / ordinary Terrain YSort | `0x5CD020` / `0x5CD990` |
| Ground layer getter / relative height | `0x5CB100` / `0x5CCD50` |
| Layer resize / value search | `0x40CD40` / `0x40CDF0` |
| Layer vtable / five records, stride 24 | `0x789870` / `0x83A888` |
| Disappear / unselected Deselect | `0x5CC150` / `0x5CB330` |
| Empty-registry resource clears | `0x405D50` / `0x405FE0` |
| Full-coordinate / word-coordinate map lookup | `0x545340` / `0x5453B0` |
| Tactical world projection | `0x697EC0` |
| Actual neighbor table initializer / table | `0x491400` / `0x839D80` |

The earlier actual Mark/Map/Cell/foundation operations remain unchanged and execute
inside these lifecycle calls. Foundation remains the supplied ordinary 1x1 pointer.

## Consequential recovered operations

Object Unlimbo requires a nonzero enable byte `0xA28588`, nonzero limbo and zero
onMap. When loading global `0xA283A4` is zero, it obtains the target cell and invokes
actual Terrain foundation dispatch. Stock non-water Terrain requests the Cell
permission service with **Track=1, null, null**. Refusal rejects before actor writes.
The full Cell permission calculation is supplied, not newly recovered here.

Accepted placement clears limbo/redraw, adjusts position and invokes actual Mark
mode 1. Type adjustment reads ground once and, only if input Z is below that result,
reads it **again** and uses the second value. It preserves X/Y and does not replace
the second result with a maximum. Standalone tests include above-ground and int32
edges; complete lifecycle/runtime support remains ground only, with explicit native
profile guards before mutation. Bridges/elevated membership are not enabled.

An active actor asks its layer, then submits. Ordinary ground Terrain selects 2.
Logic insertion requires both type logic and the veinhole byte. Ordinary stock
Terrain skips insertion even though its inspected constructor sets type logic=1;
accepted Limbo can still request logic removal. Veinhole flag branches are isolated
metadata tests only, not veinhole gameplay or runtime support.

Successful Terrain Unlimbo increments eight **Cell +0x122 bytes** in table order:
N, NE, E, SE, S, SW, W, NW. Counters wrap as uint8. Neighbor coordinates derive from
the input position with signed division by 256 and word stores. Ground adjustment
changes only Z. The actual initializer produces the offsets; no original table is
tracked. Owned complete lifecycle cases use present in-bounds neighbors.

Projection ignores viewport eligibility and preserves **six ordered stores** to
actor +0xC0/+0xC4: world X/Y, origin-subtracted X/Y, origin-added X/Y. Origin arithmetic
wraps at 32 bits. The native simulation receives projection via a callback; the
render boundary supplies the previously recovered world/height arithmetic. The
isolated original executes its actual projection and lookup initializers. The
veinhole post-branch clears overlay/frame via the original **input** coordinate.

When not already limbo, Terrain Limbo decrements neighbors and clears its own Cell
+0x124 bit **0x40 with a 32-bit store before base rejection checks**. This happens
even if the enable byte later rejects removal; repeating that rejected operation can
therefore decrement again. Accepted base removal executes unselected/no-resource
Disappear, Mark mode 0, layer removal, both count clears, optional logic removal and
limbo=1/redraw=0. Terrain always requests current-cell redraw afterward, including
rejection/already-limbo; loading=0 also invokes three follow-up map services.

The signed sort key is wrapped **X+Y**. YSort calls the coordinate getter twice.
Insertion calls candidate before existing and inserts before the first strictly
greater existing key, retaining equal-key registration order. It shifts right from
the end, stores the inserted actor then count. Unsorted append stores count first.

Growth requires owned storage or zero capacity, and a positive increment. Resize
preserves valid=0/allocation/valid=1, allocation failure, copying **capacity** rather
than count, optional free/null, pointer/capacity/ownership stores. Known-layer
removal deletes one occurrence, shifts left and leaves the capacity tail intact.
A stale LastLayer searches all five layers and repeatedly removes duplicates.
LastLayer=-1 skips removal. Submit removes prior registration before inserting;
LastLayer becomes 2 only on success, including removal followed by failed growth.

## Verification and supplied services

| Matching vector results | Boundary |
| ---: | --- |
| 768 | Signed wrapped sort keys, all insertion positions, ties and append |
| 576 | Ownership/valid bytes, increments, allocation success/failure and tails |
| 512 | Known/stale registrations, duplicates, submit/remove and all five layers |
| 4 | Null/unregistered actors and empty layers |
| 559 | Complete type adjustment, changing second ground result and int32 edges |
| 512 | Complete lifecycle gates, canonical/noncanonical bytes and rejection effects |
| 256 | Loading, permission, active/logic/veinhole metadata, failure and origin wrap |
| 64 | Repeated placement/removal/restoration and counter wrap |
| 51 | Every supplied supported ordinary tree/prop type input |
| 565 | Each map actor placed, removed and restored |
| 1 | All 565 actors over all 13,515 cells, 1,695 root calls |

These 1,449 lifecycle vectors execute **4,580 root lifecycle calls**. Tests compare
final actors/cells, all five layer records, **full capacity tails**, storage identities
and ordered writes/services. Write hooks assert field address/size and replay buffer
writes into independent arena expectations, including freed storage and canaries.
Actor/type/cell/map-table/scenario/tactical/input arenas, caller-owned stack canaries,
final ESP and callee-saved registers are audited. Original instruction bytes are
unchanged; no instruction patches or native formulas replace the original routines.

Fixtures supply ground `0x556F20`, flat cell height `0x4702C0`, Cell placement
`0x4714B0`, no attached animation `0x40DC20`, visibility `0x564DE0`, redraw queue/cell
`0x4DFEE0`/`0x472140`, map follow-ups `0x54CE60`/`0x562FE0`/`0x628AA0`, logic
`0x53C3C0`/`0x53C400`, global cleanup `0x6E1D00`, successful CRT registration and
allocation/free `0x76D5A7`/`0x76D2D5`. The registry is absent; resource objects,
selection, AlphaImage and radial indicators are excluded. Actual map lookups,
layer/relative-height/coordinate/type getters, marking, lists and projection execute.
Original internal height-service arguments are asserted; `g` entries in the shared
ordered trace represent type-adjustment calls only. Complete lifecycle fixtures
supply stable ground. Native profile checks read that service before mutation as
engineering guards; overall native/internal height-call counts are not compared.

The vector trace uses `kind a b c`, adapting the earlier occupation trace with a
zero fourth token. `N` represents member Next or layer count in their operation
context; final states independently disambiguate them. `W` similarly distinguishes
occupation-byte and logical layer-buffer stores by context. Logical actor/storage IDs
replace pointers; -2/-3 are supplied unused-slot canaries, not game values. Native
allocation/storage and the underlying original heap implementation are outside scope.

```sh
./build.command
./test.command --data-dir "$PWD/private/game"
build/tools-env/bin/python tests/compare_lifecycle.py --exe private/disc-allied/game.exe \
  --expectations private/migration/allied-disc/lifecycle/expected.json
# After README's headless sanitizer build:
build/tools-env/bin/python tests/compare_lifecycle.py \
  --exe private/disc-allied/game.exe --native build/sanitize/lifecycle-vectors \
  --expectations private/migration/allied-disc/lifecycle/expected.json \
  --report private/migration/allied-disc/lifecycle/sanitize-replay-report.json
```

Reports pin the executable, oracle/native sources, owned rules/art/map, prepared data
and current runner. Sanitizer replay also pins cached expectations. Private research,
exports and expectations remain under `private/placement/`; reports are
`private/lifecycle-report.json` and `private/lifecycle-sanitize-report.json`.

## Native integration, limits and next measurement

`prepareStaticScenery` supplies ground/projection to `GameAssets` preparation and
the SDL-free lifecycle. Native construction/IDs/map storage, zero resource/status
fields, active/healthy state and initial vector storage remain supplied. A deliberate
loading=1 host policy accepts existing map placements without claiming the original
map loader or placement permission. It returns to loading=0 after preparation.
Renderer reads recovered registration order and stored projected coordinates, within
its immutable terrain/scenery cache. There is no removal UI, global scheduler,
original draw traversal/visibility, dynamic invalidation or mixed tank/scenery order.

Native checks remove/restore every actor, all occupation/neighbor/layer states and
projection, then retain all previous render/lighting/clearance checks. Both 170-frame
SDL regressions and ASan/UBSan pass. The earlier 13,472 occupation, 808 prop, 420
scenery and 1,128 tree-type expectations replay on current native/sanitizer runners.
These checks demonstrate bounded recovery/integration, not whole-frame fidelity.
Only Apple Silicon macOS is tested. Windows mike-gaming remains deferred.

Next recover ordinary ground-layer sorting/draw traversal and Terrain draw eligibility
before mixing moving units into static scenery order. On the future Windows host,
pin this executable/map and log Unlimbo/Limbo, neighbor bytes, LastLayer and ordered
layer slots during map load, removal and replacement. Record global draw traversal,
visibility/redraw guards and tank/scenery draw order at equal/adjacent sort keys.
Capture color/depth separately with fixed resolution/detail/origin. Those measurements
connect these routines to actual loader/scheduler/invalidation; screenshots cannot.
No original-game/Windows observation has been performed here.
