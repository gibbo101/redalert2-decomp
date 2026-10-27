# Supplied RA2 1.006 shared overlay map preparation

October 15, 2026, after `d8eada9`. This continues the terrain-aware Foot/world
crossing and parked `(51,72)`, elevation 4 capability. A native preparation helper
now joins the decoded reader to actual temporary Object/Overlay construction,
ordinary/wall placement, wall update, retirement and cleanup on shared Cells.
Both supplied-map scenarios execute all 660 placements and nonempty cleanup.
The helper remains unwired; actual resource/Cell recalculation effects and the
broader map parent still precede Foot/world runtime promotion. This is local
checkpoint verification, not independent acceptance or a completed playable
milestone. Full base RA2 then YR remains incomplete.

## Identity and references

Both supplied private engines retain SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`,
4,485,392 bytes. Embedded 1.08, supplied 1.006 lineage and reported no-CD changes
remain separate provenance; pristine authenticity is unverified. The Windows
transfer was already complete. No new transfer/Windows/source-install/system
operation, worker, dependency or upstream code is part of this checkpoint.

Consulted [REFERENCES.md](REFERENCES.md), pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` `docs/voxels.md`/LICENSE and YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` `OverlayClass.h` constructor/destructor,
`ObjectClass.h` Unlimbo/Mark, and earlier Map/Cell/type declarations. Hypothesis:
the decoded reader must retain shared placement/wall mutations and then drain
its actual inactive temporary-object collection, rather than merely assigning
Cell overlay bytes. Exact base execution verifies the scoped join below. YR
names remain leads and recomp is not an oracle. No upstream/header/generated/
lifted code was copied; THIRD_PARTY.md needs no new notice.

## Native and original boundary

[OverlayMapPreparation.cpp](../src/assets/OverlayMapPreparation.cpp) adds
`prepareDecodedMapOverlays`. It binds existing recovered kernels rather than
adding another placement implementation:

1. The decoded reader performs image/crate/permission decisions and allocation.
2. A successful allocation registers a native temporary handle and executes
   Abstract/Object/resource construction, identity and Overlay registration.
3. Ordinary or wall construction dispatches through actual Unlimbo/Mark logic.
   Walls bind the actual wall-update kernel to the same selected Cell fields.
4. Actual retirement appends the inactive actor; reader cleanup removes queued
   duplicates, calls Release/Overlay destruction and supplied base destruction/free.

`OverlayLoadCell` now extends `MapWallCell`, and `OverlayPlacementCell` extends
that reader record. Reader, placement and wall update access the same fields;
no synchronization copies are involved. The helper binds all their lookups to
one storage provider. Empty object/registry counts at entry are native scope
checks; capacity/growth, provider state, invalid coordinates and raw initial flag
bits are supplied. Native records/handles and retained released records are host
storage for inspection, not original ABI/heap ownership. Base registrations are
not claimed destroyed by the supplied base-destructor service.

Preserve type-before-data/Y-major order, identity/registration before invalid
coordinate tests, count-before-slot stores, low-byte growth, constructor flag -1
and reset, unchanged type adjustment and rejected base writes. Wall update occurs
before owner/neighbor/final recalculation and retirement. Data-only loading writes
permitted Cells even without constructed overlays. Enabled-zero construction
retains active actors through cleanup. Cleanup preserves registry capacity tails.

The oracle enters **38 complete ranges / 3,176 inspected instructions**, unchanged:
the complete reader/permission/lookup/resident-image/buffer roots from
[OVERLAY_LOADING_1006.md](OVERLAY_LOADING_1006.md), complete lifetime roots from
[OVERLAY_OBJECT_LIFETIME_1006.md](OVERLAY_OBJECT_LIFETIME_1006.md), and complete
wall construction/update/connection/rectangle children from
[OVERLAY_WALL_CONSTRUCTION_1006.md](OVERLAY_WALL_CONSTRUCTION_1006.md).
All 38 roots enter. Existing exact-engine dispatch verifiers execute; earlier
inspection-only/service labels retain their historical suite scope. This suite
actually executes base construction/retirement/cleanup and wall update nested
inside the reader.

## Evidence and supplied boundaries

Current receipts: `private/map-depth-1006/overlay-map-preparation-v1/`, containing
fresh expected/report and normal/ASan/UBSan replays. **Ten complete original/native
scenarios** cover old version, nonpositive sections, ordinary/wall/resource/crate
placement with both passes, type-only loading, allocation failure, disabled
Unlimbo, data-only/short reads, and two supplied-map scenarios. Each owned scenario
uses **660 overlays / 13,515 Cells**: one runs both streams, the other preserves
placement effects before saved-data loading. These are two executions of the same
supplied map, not 1,320 distinct map placements.

Counts across all scenarios: **10 outer audits**, **1,332 constructors**, 1,328
Mark/retirement/cleanup-destructor entries, 2,664 resource constructors, 2,656
already-limbo rejection entries and 3,984 actual pointer searches. There are
1,574,204 permission, 20,088 lookup, 1,344 image getter, 194 wall-update/loaded
permission, 1,552 neighbor, 1,536 connection, 776 word-add, 1,940 union and 970
subtraction/rectangle entries each. Compare **982,224 selected guest stores** and
**3,437,518 supplied service calls** through ordered digests.

Compare complete selected shared Cell/fallback state, actor/base fields, identity
provider/placement global, six registry counts/capacities/ownership/all slots,
stream cursors, allocation attempts and freed-service counts. Caller stack/
return/registers, code allowlists, immutable type/table/geometry/global/direction/
visit/stream scratch inputs, nonselected Cell/actor bytes, raw allocation tails
and registry capacity tails pass. Full memory read order is not claimed.

The owned streams retain the prior manifest-checked fixture/source hashes.
Registry names and Wall/Land/Tiberium inputs are host-decoded from those rules;
all images are supplied resident, CellAnim/initial occupancy and slope are supplied
zero, and initial overlay/passability/owner/counters are supplied -1/0/-1/0.
No original parsing/full type startup or actual loaded TMP association follows.
The original Cell resource/recalculation roots remain **services**: the resource
fixture writes `(overlay*3+seed)&255`, and recalculation writes passability from
presence. These diagnostic effects are not original resource amount or clearance
behavior. Actual image bounds/camera, dirty/map/zone queues, heap/vector growth,
full expiration broadcasts, RTTI and base Object destruction remain supplied.
Wall bounds are zero fixtures; native union binds the earlier recovered kernel.
There is no complete map startup, heap lifetime, runtime or whole-frame proof.

Changed record sources have fresh reader **v2 (1,111)**, ordinary placement
**v6 (1,180)**, object lifetime **v5 (3,681)**, wall Mark **v3 (2,000)** and
wall construction **v3 (1,560)** comparisons and both replays. Their commands,
labels and expected outputs equal their previous scopes; older receipts remain
historical, never relabeled. Other source/runner identities and decoder stay
current: **48 sets / 1,118 source entries**.

## Verification and reproduction

Both builds, **567 Python tests**, **37 normal / 36 sanitizer CTests**, source/
diff/local-link audits pass. Rebuilt actual SDL baseline passes selection/right-
click, 79 samples/78 updates, changing light, clipping/culling/cache bypass/pan
return and no trails. Captured PPM was converted and the occluded frame inspected.
This is existing native integration, not the new preparation helper in runtime
or original-frame fidelity. Only Apple Silicon macOS is tested.

Full driver/original/native 218.050/214.897/0.168 s, CLI 218.263 s. Normal/
sanitizer replay CLI 2.221/14.827 s; four-scenario original probe 41.068 s.
Normal builds 11.696/6.428 s; sanitizer builds 10.615/7.308 s. Fresh reader/
ordinary/lifetime/wall-Mark/wall-construction CLI 114.326/1.320/17.824/2.888/18.222 s.
Python final CLI 0.433 s (unittest 0.245 s); test.command 2.474 s, sanitizer CTest
2.692 s and actual SDL 2.424 s. Independent checks ran concurrently. Full inherited/
active-delivery elapsed remains unavailable; measured commands stay private.

An unmatched Python parenthesis was caught before the original probe. The first
Python test run failed one assertion because a valid empty command was labeled
malformed; using an actually truncated command fixed the test. A private closing
audit initially raced an unfinished sanitizer receipt and passed after that same
run completed. A sandbox status command was unavailable; original runs were
tracked through their existing live exec handles and were not restarted. No
original/native mismatch, failed build or gameplay repair occurred.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
# Uses the prior manifest-backed fixture; see OVERLAY_LOADING_1006.md to prepare it.
# Fresh original execution needs the authorized host JIT context and unused output.
build/tools-env/bin/python tests/compare_overlay_map_preparation.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/overlay-map-preparation-new
build/tools-env/bin/python tests/compare_overlay_map_preparation.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/overlay-map-preparation-v1/expected.json \
  --report private/map-depth-1006/overlay-map-preparation-v1/replay-new.json
# Add --native build/sanitize/overlay-map-preparation-vectors for sanitizer replay.
./run.command --crossing-light-demo
# Select Rhino; G/right-click moves, L toggles light, R resets.
```

Next bind actual resource classification/update and complete Cell recalculation/
LAT/passability/TMP children over the same records, with required type/resource/
frame/geometry inputs and the overlay-bearing preparation parent. Then verify
prepared Cell/TMP-to-Foot/base-depth and Unit/world, and exercise actual SDL level
crossing plus parked cliff before capability completion. Runtime depth fields
stay neutral until those dependencies are verified. Full parser/defaults/actor/
contact/cache/heap lifetime, scheduling/camera/fog/UI/pathfinding and whole-frame
parity remain open. Special long-bridge/vein gameplay remains deferred beyond this
map's required placement domain.
