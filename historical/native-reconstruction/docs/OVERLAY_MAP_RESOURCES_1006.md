# Supplied RA2 1.006 shared overlay resource updates

October 15, 2026, after `33e987f`. This continues terrain-aware Foot/world
crossing and parked `(51,72)`, elevation 4 preparation. The decoded overlay
reader now has a tested binding to the actual argument-zero resource update and
classifier over its evolving shared Cells. Cell terrain/passability recalculation
is still a diagnostic service in this join; runtime remains unwired. Full base
RA2 then Yuri's Revenge and this playable capability remain incomplete.

## Identity and references

Both private supplied engines retain 4,485,392 bytes and SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 lineage and reported no-CD modifications remain
separate provenance. Pristine authenticity is unverified. The approved Windows
transfer was already complete; this checkpoint performs no new Windows operation,
transfer, source-install modification, driver/security change or system selection.

Consulted [REFERENCES.md](REFERENCES.md), pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` `docs/voxels.md`/LICENSE, and
YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88` `TiberiumClass.h`
properties/FindIndex, `CellClass.h` resource declarations and `OverlayTypeClass.h`.
Hypothesis: resource placement must visit the current shared neighboring overlays
and preserve resource update before later crate/saved-data writes. Exact base
execution decides the scoped join. YR names and addresses do not establish base
behavior. The recomp MIT license covers its authored material and excludes lifted
game output; its stale The Movies scope text remains noted in REFERENCES.md.
No upstream/header/generated/lifted code or extracted table was incorporated;
no new dependency or THIRD_PARTY notice is required.

## Shared resource binding

[OverlayMapResources.cpp](../src/assets/OverlayMapResources.cpp) binds the
existing recovered `updateMapResource` and `classifyMapOverlay` kernels to
`OverlayPlacementCell` storage. It does not add another resource algorithm.
The origin's OverlayData is updated directly. Neighbor lookups see earlier
placements and wall changes through the same provider; classification uses each
overlay's own supplied Tiberium flag and the ordered resource registry.

Preserve resource value before neighbor queries, all eight word-wrapped visits,
first matching signed range/stored resource index, missing-range log then zero,
remainder-based frame selection, one byte store and wrapped returned amount.
The native/original event stream includes the returned amount even though loaded
placement ignores it. Resource update precedes crate 255; the reader's later
saved-data pass can overwrite the result, so type-only scenarios retain the
construction result for comparison. Absent/nonresource updates preserve data.
The supported origin is a stable ordinary Cell; mutation of its coordinates
through a self-aliasing fallback is outside this binding's profile.

The exact complete reader/construction/wall/lifetime/cleanup roots from
[OVERLAY_MAP_PREPARATION_1006.md](OVERLAY_MAP_PREPARATION_1006.md) now nest
the complete classifier `0x5DC0B0` and resource update `0x476BA0` from
[OVERLAY_CELLS_1006.md](OVERLAY_CELLS_1006.md). There are **40 complete ranges /
3,331 inspected instructions**. The resource argument is checked zero; original
random replacement and resource growth/spread are outside this proof.

## Fixture and service boundaries

The map's decoded bytes, 243 type flags, all-image-resident policy, empty occupancy,
slope/CellAnim zero and initial Cell fields remain supplied. Resource records are
**diagnostic inputs**, not recovered original initialization: each contiguous
host-decoded Tiberium-flagged run supplies a range, with no slopes, nine frames
and distinct signed values. This tests the join on all supplied-map placements;
it does not establish the actual Tiberium registry order, Image=1..4 association,
NumImages/NumSlopes/NumFrames defaults, INI parsing or resource value initialization.
Original frame bytes are hash-bound fixture inputs; native code embeds no table
and adds no executable-read boundary. These executable/table reads occur only
in research fixtures; the runtime's existing track-data boundary is unchanged.

Cell recalculation/passability still writes presence-based diagnostic values in
the full-reader fixture. Host decoding/type/default association, heap/registry
growth, bounds/camera/dirty/map/zone queues, broadcasts, RTTI and base destruction
remain supplied. Retained freed native records are diagnostic storage. No complete
startup, actor/cache/heap lifetime, gameplay economy or whole-frame proof follows.

## Verification and reproduction

Fresh evidence is under `private/map-depth-1006/overlay-map-resources-v1/`:
**nine complete original/native scenarios** and both normal/ASan/UBSan replays
pass. All 40 complete ranges enter unchanged. Two scenarios execute all **660
overlays / 13,515 Cells** each, with both streams and type-only loading. These
are two executions of one supplied map, not 1,320 distinct placements. Other
scenarios cover shared adjacent resources, overlapping ranges/stored index,
missing-range logging/fallback, nonresource flags on resource land, allocation
failure, disabled Unlimbo and resource-before-crate ordering.

Counts: **956 resource updates**, **8,572 classifier entries**, nine supplied
missing-resource logs, 1,347 constructors, 1,343 Mark/retirement/destructor
entries, 194 wall-update entries and 27,716 map lookups. There are **984,347
selected guest stores / 3,436,841 supplied service calls**, compared in ordered
digests. Complete selected Cell/fallback, actor/base, registry capacity tails,
stream/provider/global/freed state and returned resource amounts compare.
Caller stack/return/registers, code allowlists, immutable type/resource/frame/
direction inputs and nonselected Cell/actor/raw-allocation bytes pass. Resource
inputs also have an immediate guest-write guard. Full memory read order is not
claimed. Earlier unchanged proofs retain their own source identities and scope:
the closing audit covers **50 sets / 1,250 source entries**.

Native-only guard tests cover missing bindings, absent/nonresource laziness,
repeated aliased neighbors, changed shared neighbor state and origin store identity.
They supplement exact-engine evidence and do not establish fidelity alone.

Both builds, **574 Python tests**, **38 normal / 37 sanitizer CTests**, source,
diff and local-link audits pass. Both actual rebuilt SDL crossings pass (79
samples / 78 updates each), including moving brightness 1450..1512 in the light
fixture, selection/right-click, occlusion, clipping/culling/cache bypass and pan
return without trails. The unlit occluded frame was converted and inspected.
This checks existing native integration, not the new resource path in runtime
or original frame fidelity. No gameplay repair or behavior mismatch occurred.

Full driver/original/native: **254.494/249.790/0.160 s**, CLI 254.634 s.
Normal/sanitizer replay CLI 4.039/16.001 s; original probe 15.968 s. Builds
10.563/12.871 s; Python CLI 3.614 s (unittest 0.885 s), test.command 3.618 s,
sanitizer CTest 6.634 s and unlit/lit SDL 2.723/2.307 s. Independent checks
overlap; private timing logs retain commands. Full inherited/active-delivery
elapsed is unavailable. One dry-run used system Python without pefile and failed
before execution; rerunning with the established tools environment passed.
An initial reference-path lookup missed the pinned snapshot and was corrected.
No original run failed, evidence cache was added, or source/runner proof was
relabelled. The new source files leave earlier implementation/runner identities
unchanged; prior receipts remain current.

Private `resource-input-*-lead*` files locate the next resource INI/default
association candidate, including its Image switch and field stores. These are
inspection leads only: no complete-range/dispatch/execution/default-initialization
claim or native behavior promotion follows from them.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
# Fresh execution needs the authorized Mac host JIT context and an unused path.
build/tools-env/bin/python tests/compare_overlay_map_resources.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/overlay-map-resources-new
build/tools-env/bin/python tests/compare_overlay_map_resources.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/overlay-map-resources-v1/expected.json \
  --report private/map-depth-1006/overlay-map-resources-v1/replay-new.json
# Add --native build/sanitize/overlay-map-resource-vectors for ASan/UBSan replay.
./run.command --crossing-light-demo
# Select Rhino; G/right-click moves, L toggles light, R resets.
```

Continue original resource/type/default associations and complete Cell
recalculation/LAT/passability/TMP over shared records, then the overlay-bearing
map preparation parent. Prepared Cell/TMP-to-Foot/base-depth and Unit/world,
actual SDL level crossing and the parked cliff remain required before runtime
depth promotion or capability completion. Only Apple Silicon macOS is tested;
Windows/Linux builds and full-frame parity remain unverified.
