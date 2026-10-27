# Supplied RA2 1.006 resident Cell and overlay preparation

October 15, 2026, after `046a089`. This continues the terrain-aware Foot/world
crossing and parked `(51,72)`, elevation 4 capability. The decoded overlay
reader now nests actual resource and resident Cell/LAT/passability/TMP children
over shared evolving records. The later two-pass map parent, actual supplied
terrain/type input association and Foot/world/runtime integration remain open.
Runtime depth stays neutral; this is not a completed playable capability.

## Identity and reference hypothesis

The private supplied base engines remain pinned to 4,485,392 bytes and SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 lineage and reported no-CD modifications remain
distinct; pristine authenticity is unverified. No Windows/transfer/source-install/
system/driver/bypass action or new dependency is involved.

Consulted [REFERENCES.md](REFERENCES.md)'s pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` `docs/voxels.md`/LICENSE and YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` `CellClass.h` SetupLAT/
RecalcAttributes, `OverlayClass.h`, `OverlayTypeClass.h` and `ObjectTypeClass.h`.
Hypothesis: reader/placement/wall/resource mutations must be immediately visible
to actual Cell recalculation and later neighbors, including slope/resource
clearing and later saved-data writes. Exact base execution decides this; YR
names are leads and recomp is not an oracle. MIT covers authored recomp work,
not generated/lifted output; the pinned stale The Movies text remains noted.
No upstream/header/generated/lifted code or extracted table was incorporated;
no THIRD_PARTY change is needed.

## Joined boundary

[ResidentOverlayPreparation.cpp](../src/assets/ResidentOverlayPreparation.cpp)
binds the unchanged decoded reader/base lifetime/ordinary-wall placement/update/
retirement/cleanup path to `updateLoadedMapResource()` and
`recalculateResidentCell()`. Placement and terrain records retain explicit native
association. Each overlay/data/slope/passability mutation is forwarded before
observers or subsequent queries; the world pointer table references canonical
terrain records directly. Reader saved-data writes and wall updates use the same
binding. Fallback coordinate stores remain visible through both projections.
Bindings/type projections are guarded; no final bulk reconciliation supplies
child results. Native store-observer guards exercise resource clearing and reject
inconsistent type projections, direction/width associations and incomplete buffers.
Buffer offsets use host-sized address arithmetic without changing the original
wrapped/clamped index calculation.

Original resource initialization runs in its separately audited guest; selected
initialized records transfer into the overlay guest. The actual decoded reader
`0x5DB670` then nests complete construction/Mark/wall/resource/Cell children in
one guest. This supersedes diagnostic Cell recalculation in the new suite;
earlier suite scope labels remain historical. It does not execute an original
startup parent or prove phase ordering. Original instructions are unchanged.

The allowlist has **54 complete ranges / 5,171 inspected instructions**;
**50 ranges / 4,943 instructions enter**. Inherited map reader/constructor and
ensure-image ranges not entered remain inspection-only within this join. The actual
later map parent `0x54B2E0` is not part of this execution. Do not remove its
native no-overlay guards without verifying those branches.

Initial terrain fields, resident TMPs/types, geometry, land/Wheel speeds, LAT
settings, directions, type flags and native record association are supplied.
Four deliberate terrain profiles use resident/differing saved TMP inputs,
resource-clearing ramps, absent images and cliff mode. They are diagnostic
consumer inputs, not original terrain/type initialization for the supplied map.
The two owned overlay scenarios retain the real decoded overlay streams and
13,515 Cell positions, but that does not establish whole-map preparation fidelity.

Decoding, type/base/parser/CRT/color/animation/vector/heap, image/bounds/camera,
queues/zones/broadcast/RTTI/base destruction remain explicit services. New tube/
animation/shadow-casting/lazy-load/occupant profiles remain refused or outside
scope. Resource spread/growth/economy and full ownership/scheduling/pathfinding/
visibility/frame parity remain open. Native malformed-input refusals are safety
guards, not original error handling. The stable-origin ordinary resource boundary
from [OVERLAY_MAP_RESOURCES_1006.md](OVERLAY_MAP_RESOURCES_1006.md) still applies.

## Verification

**Nine fresh original/native scenarios** and both normal/ASan/UBSan replays pass.
The owned both-stream and type-only scenarios each process all 660 overlays /
13,515 Cell positions. Selected initialized resource records, complete selected
Cell/actor/registry/stream/provider/global/freed state, resident terrain fields,
both full 65,536-record buffers and ordered stores/services compare independently.
The original phases have nine checked calls each, with 16 resource constructors /
18 INI / nine list entries. Within the overlay guest: **1,727 actual Cell/LAT/
passability/permission entries each**, 958 resource updates, 9,483 classifier
entries, four missing logs, 1,347 temporary constructors and 194 wall updates.
There are **993,350 selected Cell/actor/registry stores**, **5,181 buffer stores**
and **3,435,109 supplied calls**. These are scoped counts, not fidelity percentages.

Current receipts: `private/map-depth-1006/resident-overlay-v2/`. The earlier v1
full attempt was deliberately interrupted after 404.757 s for review; it produced
no accepted expectations. Review tightened shared inputs, used host-sized buffer
offsets and delegated the already-inspected reader loop before scanning unrelated
Cell ranges. The final v2 is fresh execution, never relabeled earlier evidence.
There was no original/native mismatch or failed build/test. Four earlier original
probes pass in 248.299 s; those preceded the final review refinements.

The main suite's absent-image profile coincides with allocation failure, so it
does not execute those Cell children. A separate **fresh constructed-null-image
probe** compares current normal and sanitizer runners with the original;
`resident-overlay-null-probe.json` records command/results, engine/public-source/
private-producer/runner identities, entered roots and selected buffer stores.
This targeted receipt is separate from the reusable main-suite evidence inventory.
It executes seven actual recalculations/passability calls and 21 buffer stores.

Inherited caller/return/register/code allowlist, immutable input, nonselected
Cell/actor/fallback bytes, raw allocation and registry capacity-tail audits pass.
New buffer writes require one byte at the current Cell's actual wrapped/clamped
index and only the original offsets; complete buffer results retain untouched
bytes. No full memory-read-order or actual heap-ownership claim follows.

Shared oracle hooks install declared consumer fields before snapshots; the old
M/N/J protocols retain their diagnostic recalculation scope. Affected suites have
fresh **overlay-map-preparation-v2 (10)**, **overlay-map-resources-v3 (nine)** and
**resource-map-inputs-v2 (nine)** proofs and both replays. Their commands/results/
labels equal prior v1/v2/v1 exactly. Final resource/input replays use
`reviewed-native-replay.json` and `reviewed-sanitize-replay.json`; the unchanged
parent runner retains its first replay. Closing inventory
`private/map-depth-1006/resident-overlay-coverage.json` checks **58 sets / 1,704
source entries**, all runner/expectation hashes and retained decoder identity.
Both builds, **602 Python tests**, **42 normal / 41 sanitizer CTests**,
source/diff/local-link audits pass. Local verification is not independent acceptance.

Actual final rebuilt SDL moving-light crossing passes 79 samples/78 updates,
brightness 1450..1512, selection/right-click, occlusion, clipping/culling, cache
bypass, pan and no trails. The final occluded capture equals the inspected earlier
capture byte-for-byte. This checks existing native integration, not new helper
runtime use or original-frame fidelity. Only Apple Silicon macOS is tested.

Final driver/original/native **354.761/344.075/0.181 s** (CLI 354.924 s),
replay CLI **9.510/22.572 s**; targeted null-image CLI **65.392 s**. Earlier
parent/resource/input fresh CLI **220.733/257.293/258.612 s**; current normal/
sanitizer replays **2.665/18.411**, **5.003/19.209**, **7.368/22.470 s**.
Final builds **12.460/12.992 s**; Python CLI **2.314 s**, test.command **2.320 s**,
sanitizer CTest **4.182 s**, final SDL **2.491 s**. Earlier builds/replays/checks
and all attempt timings remain private. Independent runs overlap; full inherited/
active-delivery elapsed is unavailable. One nonexistent read path was corrected;
sandbox process inspection was unavailable, and the exact own research child was
then inspected/interrupted in the authorized host context. The first process-name
filter found no match before using its actual Python interpreter name. No other
task/process/source install was changed, no gameplay repair or cache infrastructure
was added, and no workers were used.

`resident-overlay-closing.json` retains the completed source/runner/null-probe
audit. The measured interval from commit `046a089` to that audit is **1,747.138 s**;
this excludes final documentation/commit time and all earlier inherited work.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
# Fresh original execution requires the authorized Mac host JIT context.
# Use an unused destination.
build/tools-env/bin/python tests/compare_resident_overlay.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/resident-overlay-new
build/tools-env/bin/python tests/compare_resident_overlay.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/resident-overlay-v2/expected.json \
  --report private/map-depth-1006/resident-overlay-v2/replay-new.json
# Add --native build/sanitize/overlay-map-resource-vectors for sanitizer replay.
./run.command --crossing-light-demo
# Select Rhino; G/right-click moves, L toggles light, R resets.
```

Next verify the overlay-bearing two-pass map parent and its wall/resource-owner
branches, plus required supplied terrain/type/default associations. Then bind
prepared Cells/TMPs into actual Foot/base-depth and Unit/world, with actual SDL
level crossing and parked cliff before runtime depth promotion or capability
completion. Full base RA2 then YR remains active and incomplete.
