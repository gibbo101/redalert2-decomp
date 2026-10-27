# Supplied RA2 1.006 shared resident Cell recalculation

October 15, 2026, after `75d664f`. This closes the gap between the earlier
ordinary Cell/LAT join and overlay recalculation with supplied LAT results.
`recalculateResidentCell()` now binds actual LAT, overlay classification,
no-occupant passability, permission, lookup and resident TMP consumers on the
same mutable Cell. This is a prerequisite checkpoint of terrain-aware Foot/world
crossing and parked `(51,72)`, elevation 4. The helper is unwired; runtime depth
stays neutral and that playable capability remains incomplete.

## Identity and reference hypothesis

Both private supplied base engines were freshly checked: 4,485,392 bytes,
SHA256 `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 lineage and reported no-CD modifications remain
separate provenance; pristine authenticity is unverified. No new Windows action,
transfer, source-install, system, driver or bypass change occurred.

Consulted [REFERENCES.md](REFERENCES.md), pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` `docs/voxels.md`/LICENSE and YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` `CellClass.h` SetupLAT/
RecalcAttributes and OverlayType/ObjectType fields. Hypothesis: actual child
nesting must retain the saved original TMP/type after LAT changes the tile and
make resource clearing visible before passability/neighbor queries. Exact base
instructions and joined execution decide this; YR names remain leads. Recomp's
MIT covers authored work, not generated/lifted output; its stale The Movies text
remains recorded. No upstream/header/generated/lifted code or extracted table was
incorporated; no new dependency or THIRD_PARTY notice is needed.

## Native and original boundary

[ResidentCellPreparation.cpp](../src/assets/ResidentCellPreparation.cpp) calls
the existing complete `recalculateMapCellAttributes()` and binds its children
to `setupMapLAT()`, `classifyMapOverlay()`, `overlayCellPassability()`,
`mapCellPermitted()` and `mapAttributeCell()`. The pointer grid references the
current `cell.input` directly; earlier stores are visible to later lookups.
Observers record entry and selected store order without supplying child results.
The passability child updates the actual Cell before notifying its store
observer, matching the original child store at +0x4C. A sentinel regression
checks that callback visibility; resource/data clear order is also checked.

Actual original roots include Cell `0x472540`, LAT `0x471D10`, passability
`0x478F40`, permission `0x55A660`, lookup `0x548070` and classifier `0x5DC0B0`.
The allowlist contains **19 complete ranges / 1,968 inspected instructions**;
**14 ranges / 1,728 instructions enter** in this fixture. Inherited constructor/
reader ranges are inspection only here. The original instructions are unchanged.
The selected Cell state, buffers and ordered events compare with native results.

Supplied inputs remain initial Cell/grid/fallback state, tile/type/resource
registries and defaults/INI, resident TMP pointer headers, land/speed tables,
geometry, direction offsets, LAT settings, tube count and cliff mode. Missing
resource logging is a service. This suite does not join resource initialization,
overlay reader/placement or the map parent, nor execute original startup ordering.
New tubes, animation allocation, shadow-casting writes, lazy image loading and
occupants remain refused/outside this profile. Native malformed-input refusals
are safety guards, not recovered original error behavior.

The fixture preserves saved type/TMP across LAT changes, overlay land shortcuts,
resource clearing, per-path level/height and buffer order, shared/fallback lookup
effects, signed/wrapped arithmetic and distinct overlay/ordinary speed checks.
Caller/return/ESP/callee-saved registers, code allowlist, immutable inputs,
unselected Cell/fallback bytes, buffer capacity tails and ordered selected stores
are audited. There is no complete memory-read-order or ownership claim.

## Evidence, checks and reproduction

**784 fresh original/native results** pass: 768 varied shared Cell cases and
16 explicit saved-TMP/LAT/resource-clear cases. Both normal and ASan/UBSan
replays pass. Counts: **1,568 audited calls**, 784 complete Cell/passability/
permission entries each, 729 LAT entries, 157 classifier entries, 60 missing-
resource log services, 589 LAT changes/alternate-type getters, 5,753 lookup
events and 8,469 selected ordered stores. These are scoped counts, not fidelity
percentages or whole-map/frame evidence. Eleven original probes also passed.

Current receipts: `private/map-depth-1006/resident-cell-v2/`. V1 is historical
after review corrected observer visibility; v2 commands/results/labels equal v1.
The guard starts passability at 17 so the calculated zero cannot mask a stale
observation. No original/native mismatch or failed test prompted this correction.
Shared oracle refactoring uses class-specific selected fields and a pre-snapshot
fixture hook; deterministic input generation is reused without monkeypatching.

Three changed-source suites have fresh proofs and both replays:
`cell-preparation-v5` (1,536), `map-preparation-v6` (65), `resident-map-v5` (51).
Their commands/results/labels equal the respective v4/v5/v4 receipts exactly.
Closing audit `private/map-depth-1006/resident-cell-coverage.json` checks **56 sets /
1,508 source entries**, runner/expectation hashes and retained map-decoder identity.
Older receipts remain intact. Both builds, **595 Python tests**, **41 normal /
40 sanitizer CTests**, source/diff/local-link checks pass.

Actual rebuilt SDL moving-light crossing passed 79 samples/78 updates, brightness
1450..1512, selection/right-click, occlusion, clipping/culling, cache bypass, pan
and no trails. Converted capture was inspected. This checks existing native
integration, not new Cell runtime use or original-frame fidelity. Only Apple
Silicon macOS is tested; local verification is not independent acceptance.

Final fresh driver/original/native **10.026/7.305/0.091 s** (CLI 10.481 s),
normal/sanitizer replay CLI **1.378/3.321 s**. Refreshed ordinary/parent/resident
fresh CLI **6.422/11.305/35.982 s**, replay CLI normal **1.612/2.273/2.850 s**,
sanitizer **5.640/3.893/5.987 s**. Final guard rebuilds **7.268/7.882 s**;
observer rebuilds **11.641/12.770 s**. Final Python CLI **2.537 s** (unittest
0.679 s), test.command **2.522 s**, sanitizer CTest **5.705 s**. Initial proof/
build/replay logs remain private; original probes **1.587 s**, SDL **2.278 s**.
Independent checks overlap. Full inherited/active-delivery elapsed is unavailable.
A nonexistent private audit-script read path was corrected by search. No build,
original/native comparison or test failed; no gameplay repair or evidence-cache
infrastructure was added. No workers were used.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
# Fresh original execution requires the authorized Mac host JIT context.
# Use an unused output directory.
build/tools-env/bin/python tests/compare_resident_cell.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/resident-cell-new
build/tools-env/bin/python tests/compare_resident_cell.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/resident-cell-v2/expected.json \
  --report private/map-depth-1006/resident-cell-v2/replay-new.json
# Add --native build/sanitize/resident-cell-vectors for sanitizer replay.
./run.command --crossing-light-demo
# Select Rhino; G/right-click moves, L toggles light, R resets.
```

Next bind this helper to shared overlay placement/wall updates with immediate
ordered field forwarding, then verify the overlay-bearing map preparation
parent. Do not remove the parent's no-overlay guards without original branch
proof. Then prepared Cell/TMP-to-Foot/base-depth and Unit/world plus actual SDL
crossing/parked cliff before runtime depth promotion or capability completion.
Full startup/type/parser/heap/cache lifetime/scheduling/pathfinding/visibility/
frame parity and full base RA2 then YR remain open.
