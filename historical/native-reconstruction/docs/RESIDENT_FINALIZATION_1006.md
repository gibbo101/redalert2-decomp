# Supplied RA2 1.006 overlay-bearing map finalization

October 15, 2026, after `a027325`. The later two-pass map parent now executes
with actual shared resource, resident Cell/LAT/passability/TMP, lighting and
wall-owner children. **35 fresh original/native scenarios** pass. This closes
the parent's overlay-absent restriction in a new bounded API; earlier APIs and
evidence retain their original guards and labels. The helper remains unwired.
Terrain-aware Foot/world crossing and parked `(51,72)`, elevation 4 remain
incomplete, and runtime depth stays neutral.

## Identity and references

Both supplied private engines are 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`:
`private/official-1006-probe/game.exe` and
`private/windows-baseline-20261014/game.exe`. They were rehashed during this
delivery. Embedded version 1.08, supplied 1.006 lineage and reported no-CD changes
remain separate provenance; pristine authenticity is unverified. The approved
Windows copy already existed. No new transfer, Windows/source-install/system
action, dependency or worker was introduced. Runtime never executes the binary.

Consulted [REFERENCES.md](REFERENCES.md), pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` `docs/voxels.md`/LICENSE, and
YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88` `MapClass.h`, `CellClass.h`
SetupLAT/RecalcAttributes/SetWallOwner and `ScenarioClass.h` lighting declarations.
Hypothesis: the later map parent accumulates resource returns before Cell
recalculation and tests the resulting overlay before owner selection, while
earlier stores remain visible to later Cells. Exact base inspection/execution
establishes this order. YR names are leads and recomp is not a behavior oracle.
MIT applies to authored recomp work, not generated/lifted output; its stale
The Movies text remains noted. The pinned YRpp snapshot has no license file.
No upstream/header/generated/lifted code or extracted table was incorporated;
existing notices remain sufficient and THIRD_PARTY.md is unchanged.

## Executed join

[ResidentMapFinalization.cpp](../src/assets/ResidentMapFinalization.cpp) projects
the complete `0x54B2E0..0x54B555` parent for an **empty transient list, no attached
tags and no occupants**. Preserve:

1. Complete first traversal clearing flags with `0xFFCFFFFF` before any second-pass
   lighting/resource/recalculation work, then reset the iterator.
2. For each visited Cell, zero field +0x30, initialize lighting, then clear flag
   `0x20000` with `0xFFFDFFFF`.
3. Update resources with argument zero; add the result to a **uint32-wrapped**
   total before recalculating the Cell with -1.
4. Read overlay +0x44 **after recalculation**. Only a remaining wall calls the
   owner selector; resource clearing can suppress that call. Return the wrapped
   total. The native result additionally exposes the final traversal cursor.

The actual guest nests numeric lighting/normalization and factory-disabled
installation, resource/classifier, Cell/LAT/no-occupant passability/permission/
lookup/TMP and owner/Cell-target coordinate/foundation/house-index/kind/sqrt/FTOL.
The native lighting and candidate services bind existing recovered kernels in
the fixture. Terrain height is supplied. The candidate service and observers
must not mutate Cell/slot/type/registry inputs; lighting owns separate storage.
The incoming x87 53-bit/toward-zero mode `0x0E7F` is a supplied caller profile,
not recovered startup initialization. Native distance restores host FP state.

[verify_resident_map_finalization.py](../tools/verify_resident_map_finalization.py)
combines **39 allowed complete ranges / 3,368 inspected instructions**;
**34 ranges / 3,128 instructions enter**. Constructor/reader ranges retained
by earlier inspectors are unentered here. The inspection records preserve each
inherited scope; the new top-level scope describes the expanded executed join.
Original instructions are unchanged. Supplied services intercept only declared
terrain-height and missing-resource-log calls.

Canonical world/slot/Cell/fallback identity, geometry, buffer, tag and cliff-mode
checks are native safety refusals. They do not establish original malformed-input
behavior. Existing `prepareMapCells()` keeps its no-overlay/tag guards; old P/Q
fixtures and earlier overlay M/N/J/R scopes are not widened or relabeled.

## Evidence and remaining boundaries

`private/map-depth-1006/resident-finalization-v1/` retains 32 seeded evolving
shared-map scenarios and three owned-input scenarios, cliff modes 0/1/2.
Each owned scenario includes **13,515 positions, 660 decoded overlays, 838 primary
type records and 268 resident primary images**. Resource totals are 133,800 in
all three. Synthetic totals include signed-negative/large values and 32-bit wrap.
Compare all selected Cell/light/owner fields, both complete buffers, cursor/
fallback, visits, ordered selected query/store events and resource-total return.
Native sentinel regressions also verify immediate observer visibility, cleared
wall suppression, retained resource return, empty-registry owner -1 and refused
inconsistent bindings/tags.

Counts: 36 audited calls (35 parents plus direction initialization), **41,249**
resource/Cell/passability/permission/light entries each, 17,078 classifier calls,
381 owner calls, 474 actual coordinate/distance/foundation/getter/sqrt chains,
430 owner-index getters, 361 missing-resource logs and 123,747 selected buffer
stores. The receipt's `selected_stores` counter is **9,842,466 total guest writes
seen by its write hook**, including stack writes, not that many Cell fields.
The ordered digests cover selected writes/queries, not every memory read.
Caller return/ESP/register/code/write guards, immutable input/registry capacity
tails, nonselected Cell/fallback bytes and buffer tails pass. Buffer writes must
target the current recalculation's original index/byte offsets.

Initial terrain/TMP records are pinned **input snapshots** from
`resident-map-v6/expected.json`; overlay bytes use the manifest-checked owned
decoded fixture. Host INI parsing projects overlay fields/defaults. Owned resource
records come from four actual constructors/four INI reads/one list call in a
**separate audited original guest**, with explicit selected-record transfer.
Synthetic resource records remain diagnostic inputs. These are not reused
behavior expectations or proof of original startup order. Building/house/type
records and height zero in the owned scenarios are supplied diagnostics, not
original actor loading. The earlier overlay reader does not execute in this guest.
Palette allocation, occupants/tags/transient objects, original initial/type/actor/
height/land/geometry/table construction, heap/converter/cache ownership, full
startup/visibility/scheduling/pathfinding and whole-frame fidelity remain open.
Unused Tunnel/Weeds land records do not establish gameplay on those branches.

## Reproduce

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

# Fresh unused private destination; original execution needs Mac host JIT access.
build/tools-env/bin/python tests/compare_resident_map_finalization.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/resident-finalization-new
build/tools-env/bin/python tests/compare_resident_map_finalization.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/resident-finalization-v1/expected.json \
  --report private/map-depth-1006/resident-finalization-v1/replay-new.json
build/tools-env/bin/python tests/compare_resident_map_finalization.py \
  --exe private/official-1006-probe/game.exe \
  --native build/sanitize/resident-map-finalization-vectors \
  --expectations private/map-depth-1006/resident-finalization-v1/expected.json \
  --report private/map-depth-1006/resident-finalization-v1/sanitize-new.json

# Existing playable baseline; this does not invoke the new helper.
./run.command --crossing-light-demo
```

Select the Rhino; G/right-click moves, L toggles the host-placed light, R resets.
Only Apple Silicon macOS is tested. This is local verification, not independent
acceptance. Closing regression inventory/timings are recorded in the handoff.

Next recover/bind the required original initial/type/actor/occupant/tag/height
associations and join prepared Cell/TMP state to Foot/base-depth and Unit/world.
Exercise actual SDL level crossing and parked cliff before promoting runtime
depth or claiming the observable capability. Full base RA2 then YR remain open.
