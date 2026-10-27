# Supplied RA2 1.006 wall construction and shared update

October 15, 2026, after `fc87af8`. This continues the same terrain-aware
Foot/world crossing and parked `(51,72)`, elevation 4 capability. The complete
Overlay constructor/Object Unlimbo/loaded wall Mark now execute with the actual
wall-update children in one comparison. Native placement and wall update share
selected Cell storage. The helper remains unwired; decoded-reader nesting and
actual Cell/resource/recalculation effects are still pending. This is a locally
verified prerequisite, not a completed playable milestone or independent
acceptance. Full base RA2 then YR remains incomplete.

## Identity and references

Both private supplied engines retain SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`,
4,485,392 bytes. Embedded 1.08, supplied 1.006 lineage and reported no-CD changes
remain separate provenance; pristine authenticity is unverified. The approved
Windows transfer was already complete. No new transfer/Windows/source-install/
system action, worker, dependency or upstream code is part of this checkpoint.

Consulted [REFERENCES.md](REFERENCES.md), pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` `docs/voxels.md`/LICENSE and YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` `OverlayClass.h`,
`ObjectClass.h` Unlimbo/Mark and `CellClass.h` connection/owner/neighbor names.
Hypothesis: the constructor's placement flag must remain visible through the
actual loaded wall update, followed by owner assignment, neighbor increments
and retirement. Exact base execution verifies the scoped join below. YR names
remain leads and recomp is not an oracle. No upstream/header/generated/lifted
code was copied; THIRD_PARTY.md needs no new notice.

## Executed join

[OverlayPlacement.cpp](../src/assets/OverlayPlacement.cpp) adds
`constructLoadedMapWall` and `unlimboLoadedMapWall`. Ordinary and wall entry points
share private constructor/Unlimbo implementations while retaining their separate
type guards and Mark dispatch. `OverlayPlacementCell` extends the selected
`MapWallCell` record; placement, connection, owner and neighbor effects access
the same fields without synchronizing copies. These are portable records, not
original ABI layouts. The constructor supplies a live placement-flag reference
through Mark and resets the flag to -1 after Unlimbo, including rejection. An
invalid Cell coordinate still consumes identity/registration and skips both flag
stores. Preserve low-byte growth results and count-before-slot writes.

The oracle enters **20 complete ranges / 2,269 inspected instructions**, unchanged:
all twelve placement/identity roots from [OVERLAY_PLACEMENT_1006.md](OVERLAY_PLACEMENT_1006.md),
the loaded permission and neighbor roots from
[OVERLAY_WALL_PLACEMENT_1006.md](OVERLAY_WALL_PLACEMENT_1006.md), and all six
wall-update/connection/word/rectangle roots from
[MAP_WALL_UPDATE_1006.md](MAP_WALL_UPDATE_1006.md). Actual Overlay/type vtable
slots and visit table are pinned. Base Object constructor and retirement roots
remain inspection only **in this suite**; their separate execution evidence is
retained in [OVERLAY_OBJECT_LIFETIME_1006.md](OVERLAY_OBJECT_LIFETIME_1006.md).

Preserve enabled/limbo/onMap gates, unchanged OverlayType coordinate adjustment,
base writes before slope rejection, data before index, wall update(1) before owner,
then eight word-wrapped neighbor increments, final recalculation, onMap=0,
limbo=1 and retirement. The wall update uses evolving shared Cells across five
visits; surrounding walls can be removed and their owner/counter effects are
retained before placement continues. Constructor flag -1 suppresses the later
owner store. Direct Unlimbo reads the supplied live flag. Unsupported special
placement/type/loading profiles are refused before mutation.

## Evidence and remaining services

Current receipts: `private/map-depth-1006/overlay-wall-construction-v2/` with
fresh expected/report and normal/ASan/UBSan replays. **1,560 fresh original/native
cases**:

- 108 actual Unlimbo gates and rejected base states;
- 396 constructor registration/growth/identity/invalid-coordinate/flag cases;
- 960 complete shared wall-placement/update/owner/neighbor cases;
- 96 supplied direction wrapping/aliases/byte overflow/provider-absence cases.

Counts: **1,560 outer audits**, 972 constructor/identity, 960 identity-counter,
1,461 Unlimbo, 1,272 Mark/base/type/adjust/position/word/redraw/kind entries,
693 loaded permission/wall-update, 5,544 neighbor, 11,976 connection,
2,772 word-add, 6,930 union and 3,465 subtraction/rectangle entries each;
**27,725 ordered selected guest stores**, **59,348 supplied service calls**.
All six special removal paths execute: indices 2/26/0/1/22/3 have
12/10/12/6/12/1 entries. Zone addition/removal counts are 2,120/18; all 18 removed
and changed cases enter neighbor decrements. Old/complete bounds have 2,772/3,465
entries.

Compare complete selected actor/identity/counter/placement-flag/registry-capacity
state, all selected shared Cell fields and ordered query/store/service digests.
Caller stack/register/return address, immutable type/registry/occupant/rules/
global/direction/vtable/visit inputs, constructor result, nonselected actor/Cell
bytes and capacity-tail guards pass. All 20 complete roots enter. v1 passed
before tightening the fixture's skip-byte guard and correcting the inspection-only
metadata label; v2 freshly verifies final sources. Do not relabel v1.

Base Object construction, provider initialization/lifetime, vector growth/heap,
image bounds/camera, lookup/linked occupants/virtual kind, redraw/map/zone queues,
expiration broadcasts, Cell recalculation and retirement effects remain supplied.
Recalculation changes passability in controlled ways; retirement clears active.
The join does not nest base lifetime, decoded reader, actual Cell preparation or
complete map startup. The native union binds the earlier recovered render kernel.
No runtime or whole-frame fidelity follows.

Changed shared sources have fresh ordinary **placement-v5 (1,180)**,
**object-lifetime-v4 (3,681)** and **wall-placement-v2 (2,000)** original comparisons
and both replays. Their commands/labels/outputs equal the prior suites; older
receipts remain historical. Other source/runner identities and decoder remain
current: **46 sets / 1,012 source entries**.

## Verification and reproduction

Both builds, **560 Python tests**, **36 normal / 35 sanitizer CTests**, source/
diff/local-link audits pass. The rebuilt actual SDL baseline passes selection/
right-click, 79 samples/78 updates, changing light, culling/clipping/cache bypass/
pan return and no trails. Captured occluded frame inspected after PPM-to-PNG
conversion. This is existing native integration, not new wall/runtime or original-
frame proof. Only Apple Silicon macOS is tested.

Final v2 driver/original/native 16.100/14.853/0.108 s, CLI 16.182 s; normal/
sanitizer replay CLI 1.491/2.079 s. Builds 9.351 and 6.317 s, then final runner
rebuild 7.605 s; sanitizer build/rebuild 11.544/5.890 s. Fresh ordinary placement/
lifetime/wall-Mark CLI 1.168/15.329/2.189 s. Python CLI 2.814 s (unittest 1.475 s),
test.command 0.908 s, sanitizer CTest 2.703 s and actual SDL 3.696 s. Independent
checks ran concurrently. v1 passed (17.393 s); no original/native mismatch or
failed build/test occurred. System Python bytecode compilation first hit its
unwritable user cache; explicitly directing it to build/ passed. The SDL tool
emits PPM, so the initially absent PNG was converted before inspection. No
native algorithm or gameplay repair resulted. Full inherited/active-delivery
elapsed remains unavailable; measured commands/attempts stay private.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
# Fresh original execution needs the authorized host JIT context and unused output.
build/tools-env/bin/python tests/compare_overlay_wall_construction.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/overlay-wall-construction-new
build/tools-env/bin/python tests/compare_overlay_wall_construction.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/overlay-wall-construction-v2/expected.json \
  --report private/map-depth-1006/overlay-wall-construction-v2/replay-new.json
# Add --native build/sanitize/overlay-wall-construction-vectors for sanitizer replay.
# Earlier suites now use placement-v5, object-lifetime-v4 and wall-placement-v2.
./run.command --crossing-light-demo
# Select Rhino; G/right-click moves, L toggles light, R resets.
```

Continue shared base lifetime/decoded reader/Cell resource and recalculation
nesting on the actual supplied overlay inputs. Complete overlay-bearing map
resource/wall-owner effects before prepared Cell/TMP-to-Foot/base-depth and
Unit/world runtime integration. Require actual SDL level crossing and parked
cliff before capability completion; runtime depth stays neutral. Full parser/
defaults/actor/contact/cache/heap lifetime, scheduling/camera/fog/UI/pathfinding
and whole-frame parity remain open. Special long-bridge/vein gameplay remains
deferred beyond this map's required placement domain.
