# Supplied RA2 1.006 wall connections and update parent

October 15, 2026, after `a5d2c49`. This continues the same terrain-aware
Foot/world crossing and parked `(51,72)`, elevation 4 capability. The wall-update
parent that the earlier loaded-wall suite supplied now has a separately verified
readable C++ projection, including the actual connection child and numeric
rectangle children. It is not yet nested into wall placement or the decoded
reader and remains unwired. This is a locally verified prerequisite, not a
completed playable capability or independent acceptance. Full base RA2 then YR
remains incomplete.

## Identity and references

Both supplied private engines retain 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 lineage and reported no-CD changes remain separate
provenance; pristine authenticity is unverified. The approved Windows transfer
was already complete. No new Windows/transfer/source-install/system action,
worker, dependency or upstream code is part of this checkpoint.

Consulted [REFERENCES.md](REFERENCES.md), pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` `docs/voxels.md`/LICENSE and YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` `CellClass.h`
`ConnectsToOverlay`, wall-owner/neighbor declarations, `OverlayTypeClass.h` Wall
and earlier Object/Overlay/Map declarations. Hypothesis: wall connection bits and
damage removal must evolve on shared Cells before map preparation can consume
their passability. Exact base execution verifies the bounded behavior below.
YR declarations remain leads and recomp is not an oracle. No upstream/header/
generated/lifted code or extracted table was incorporated.

## Executed boundary

[MapWallUpdate.cpp](../src/assets/MapWallUpdate.cpp) keeps selected Cell and
ordered occupant projections separate from original ABI/storage. Gate type
identities, wall flags, cardinal visits, direction offsets, screen origin and
initial Cells are supplied. Rendering remains separate: the native test binds
the existing recovered `unionDirtyBounds` through an explicit union service.

| Complete actual range | Executed behavior |
| --- | --- |
| `0x475960`, 1,015 bytes | Complete wall-update parent |
| `0x475840`, 276 bytes | Complete connection/equality/gate predicate |
| `0x42ADD0`, 41 bytes | Actual wrapped word-coordinate addition |
| `0x45EFE0`, 240 bytes | Actual asymmetric rectangle union |
| `0x47D040`, 32 bytes | Actual wrapped screen-origin subtraction |
| `0x453E40`, 33 bytes | Actual rectangle constructor |

All **six complete ranges / 540 inspected instructions** execute unchanged.
The exact original cardinal/self table is verified before use and supplied to
native tests; it is not compiled from extracted data into the implementation.

Connection equality succeeds only for equal non--1 overlay indices. Requested
-1 accepts existing 2 or 26 without visiting occupants. Requested 0/2 and 26
scan occupants in order: query kind first, require kind 6 and signed health >0,
then compare supplied type identities. Rules fields +0x77C/+0x784 accept directions
2/6, +0x780/+0x788 accept 0/4; +0x78C accepts either direction for requested
0/2. Preserve short circuits, duplicate/null identities and first qualifying
occupant. Other requested indices do not scan occupants.

The parent visits cardinal neighbors 0/2/4/6, then self (-1), using evolving
shared Cells. A nonzero byte argument skips only the center's two old-image
bound queries. Every visit then queries shadow, overlay and terrain bounds,
unites terrain with overlay before shadow, subtracts the supplied screen origin
with uint32 wrapping and requests a flag-zero dirty rectangle. The old-image
partial local union has no later selected effect; its provider calls are retained.
Notify the map Cell list before testing overlay absence or its Wall byte.

For walls, rebuild four connection bits while preserving the data high nibble.
Save passability before the data store. The special isolated damage decisions are:

| Index | Complete data byte after mask update | Removal owner store |
| --- | --- | --- |
| 2 or 26 | 0x20 or 0x30 | Preserve owner |
| 0 or 22 | 0x10 or 0x20 | Owner=-1 |
| 1 | 0x20 | Owner=-1 |
| 3 | 0x10 | Owner=-1 |

Removal stores overlay=-1 and data=0, optionally owner=-1, then announces
removed-byte-one pointer expiration. Always request Cell recalculation with -1
for a wall. Only a changed passability requests zone notifications. A removed
wall requests removal then the second notification and decrements all eight
neighbor byte counters with wrapping; a retained wall requests addition then
the second notification. A removed wall with unchanged passability does **not**
decrement counters. Preserve ordered repeated aliases and shared updates across
the five outer visits.

## Evidence and supplied boundaries

Current receipts: `private/map-depth-1006/map-wall-update-v2/` with fresh
expected/report and normal/ASan/UBSan replays. **4,640 fresh original/native cases**:

- 800 equality/none/direction cases;
- 1,344 ordered live/dead/wrong-kind gate/tower cases;
- 128 duplicate/null type-identity cases;
- 1,920 complete shared-state wall-update scenarios;
- 448 isolated damage-nibble/passability cases.

Counts: **4,640 outer audits**, 2,368 parent, 35,252 connection, 9,472 word-add,
23,680 union and 11,840 subtraction/rectangle constructor entries each;
**8,933 ordered selected guest stores**, **144,164 supplied service calls**.
Explicit execution counts cover removals of indices 2/26/0/1/22/3
(18/20/24/17/31/12), zone add (4,794), zone removal (45), neighbor-decrement
loops (45), old bounds (9,946) and complete bounds composition (11,840).

Compare complete selected Cell position/index/passability/owner/data/counter
state and ordered bound/union/lookup/occupant/map/zone/store digests. Caller
stack/register/return address, immutable type/registry/occupant/rules/global/
direction/vtable/visit inputs and nonselected Cell bytes pass. Occupants use
supplied linked storage and supplied virtual kind results; they are not actual
building construction or gate animation/lifetime evidence.

Image/camera-dependent bound providers, lookup/storage, original dirty/map/zone
queues, virtual occupant kinds, full pointer-expiration broadcasts and Cell
recalculation effects remain services. The recalculation fixture changes only
passability in controlled ways to expose the parent gates. Earlier Cell kernels
are not yet nested here. No complete image bounds/camera/queue/zone/Cell map
preparation, wall placement/constructor/reader nesting, runtime or whole-frame
claim follows. v1 passed before explicit branch counts and isolated cases;
it remains historical. v2 is fresh evidence for the expanded final source.

## Verification and reproduction

Both builds, **553 Python tests**, **35 normal / 34 sanitizer CTests**, source/
diff/local-link audits pass. All prior 42 source/runner sets and decoder remain
identity-current; coverage is **44 sets / 938 source entries**. Actual rebuilt
SDL baseline passes selection/right-click, 79 samples/78 updates, changing light,
culling/clipping/cache bypass/pan/no trails. The captured occluded frame was
inspected. This is existing native integration, not new wall/runtime or original-
frame fidelity. Only Apple Silicon macOS is tested.

Fresh v2 driver/original/native 19.866/19.526/0.096 s, CLI 19.956 s. Normal/
sanitizer replay CLI 0.421/1.255 s; builds 11.096/9.345 s. Python CLI 2.622 s
(unittest 0.703 s), test.command 2.615 s, sanitizer CTest 5.101 s, actual SDL
2.343 s. Independent checks ran concurrently where possible. The first original/
native comparison stopped at case 4084 because Python fixture wall-flag addition
lacked C++ uint32 wrapping (18.422 s). Correcting that supplied-input mismatch
yielded the 4,192-case v1 pass (17.045 s); the native algorithm did not change.
No failed build/test or gameplay repair. Full active-delivery and original
continuation elapsed remain unavailable; measured logs/attempts stay private.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
# Fresh original execution needs the authorized host JIT context and unused output.
build/tools-env/bin/python tests/compare_map_wall_update.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/map-wall-update-new
build/tools-env/bin/python tests/compare_map_wall_update.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/map-wall-update-v2/expected.json \
  --report private/map-depth-1006/map-wall-update-v2/replay-new.json
# Add --native build/sanitize/map-wall-update-vectors for sanitizer replay.
./run.command --crossing-light-demo
# Select Rhino; G/right-click moves, L toggles light, R resets.
```

Continue wall constructor/Unlimbo dispatch and nest actual wall update with
placement, decoded reader and shared Cell/resource/recalculation state. Complete
overlay-bearing map resource/wall-owner effects before prepared Cell/TMP-to-Foot/
base-depth and Unit/world integration. Require actual SDL level crossing and
parked cliff before capability completion. Runtime depth fields stay neutral.
Full parser/defaults/actor/contact/cache/heap lifetime, scheduling/camera/fog/UI/
pathfinding and whole-frame parity stay open. Special long-bridge/vein gameplay
remains deferred beyond the chosen map's required placement domain.
