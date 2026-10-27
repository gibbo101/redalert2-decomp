# Supplied RA2 1.006 map finalization with actual floor height

October 15, 2026, after `6cd79d3`. **268 fresh original/native scenarios**
match with the actual Cell-center/floor query nested inside wall-owner selection
and the later shared map parent. Both native and sanitizer replays pass. This replaces the supplied height boundary in the new
F profile only. Earlier G/wall evidence retains its supplied-height scope.
The helper is not wired into the application. Prepared-map Foot/base-depth/
Unit-world and the terrain-aware crossing/parked cliff capability remain open;
runtime depth stays neutral.

## Identity and references

Both private supplied engines were freshly rehashed: 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`, at
`private/official-1006-probe/game.exe` and
`private/windows-baseline-20261014/game.exe`. Embedded 1.08, supplied 1.006
lineage and reported no-CD changes remain separate provenance; pristine
authenticity is unverified. The approved private Windows copy already exists.
No new transfer, Windows/source-install/system action, dependency or worker
was introduced. The native application never executes the original binary.

Consulted [REFERENCES.md](REFERENCES.md), pinned YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` `CellClass.h`
SetWallOwner/GetCellCoords/GetFloorHeight and Map/Abstract distance leads.
Hypothesis: owner distance observes the current Cell level and recalculated
ramp, and lazy height state is shared across candidate queries and Cells.
Exact base execution verifies the join. YR names are leads, not base proof.
Recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439` `docs/voxels.md` is
surrounding context, not an oracle. Its MIT grant excludes generated/lifted
game code; the stale The Movies text and YRpp's absent license remain recorded.
No upstream/header/generated/lifted code or extracted table was incorporated;
THIRD_PARTY.md and existing notices are unchanged.

## Executed boundary

[ResidentMapFloor.cpp](../src/assets/ResidentMapFloor.cpp) binds the established
Cell-center/floor, foundation-adjusted Building coordinates and table-sqrt
Cell-target distance into `finalizeResidentMapWithFloor`. Simulation remains
SDL-free and the helper has no rendering/platform dependency. Supplied Building
positions/foundation dimensions follow the candidate registry's order; the house
index getter remains a service. An additional supplied distance callback is
refused so that it cannot silently replace this profile's numeric path.

The actual original parent, resource/classifier, Cell/LAT/passability/permission/
TMP, numeric lighting/factory-disabled installation, owner/getters/coordinates/
foundation/table-sqrt/FTOL and Cell floor/lazy planes run in **one shared guest**.
Only the existing missing-resource log service remains intercepted here; the
floor entry is observed without returning a supplied result or patching code.
[verify_resident_map_floor.py](../tools/verify_resident_map_floor.py) combines
42 allowed complete ranges / 3,737 inspected instructions; **35 ranges / 3,435
instructions enter**. The map-floor and actor-relative wrappers are inspected
dependencies but do not execute in this combined parent.

Preserve the full first pass and iterator reset, resource return/sum before
recalculation, then the **post-recalculation overlay read**. A cleared wall never
queries a candidate or initializes floor state. Eligible candidate distance queries
the current Cell after recalculation, then the Building. Do not capture the
fixture's initial slope or substitute a flat Z. Shared lazy flags/cached height/
scale/planes keep their independent initialization semantics across calls.
The supplied live level-height value is immutable within one parent invocation.
The selected x87 53-bit/toward-zero profile remains supplied; native arithmetic
restores host rounding. Original instructions are unchanged.

Canonical Cell/slot/fallback/buffer/geometry/tag guards, candidate-count checks and
finite ramp/state guards are native safety boundaries. Empty transient list,
no tags/no occupants and disabled palette factory remain explicit bounds.
The earlier APIs and G parser keep their existing guards and historical scope.
F commands reject nonzero supplied Cell heights and require ramps 0..20.

## Evidence and limits

`private/map-depth-1006/resident-floor-v1/` retains 32 shared synthetic maps,
three owned-input scenarios, 168 ramp/lazy-bit/level/live-height cases, 63 skipped
floor cases and two decisive owner cases. Each owned scenario includes 13,515
positions, 660 overlays and the supplied primary TMP/type inputs. Historical
`resident-finalization-v1/expected.json` contributes **scenario inputs only**,
with its receipt and hash checked; no historical behavior result is reused as
the new combined proof. Resource records retain their supplied, separately
recovered input provenance; constructors/INI/list startup do not execute here.

At Cell (1,2), level 4, two same-XY candidates at Z=0/832 give owner **7** on
flat terrain and **9** with ramp 1. Initial slope 20 in both fixtures would pick
the wrong first result if stale data were captured. All 20 ramps, cold/partial/
warm lazy state, live heights 104/208, post-clear suppression, empty/ineligible
registries and first-distance ties receive combined execution comparisons.

Counts: 269 audited calls including direction initialization; 41,482 actual
resource/Cell/passability/permission/light entries each, 594 owner calls and
**816 actual distance/center/floor chains**. There are 342 lazy flag stores,
20,520 plane writes and 124,446 selected buffer writes. The parent hook observes
9,941,197 total guest writes including stack writes. Compare every selected
Cell/light/owner field, both complete buffers, cursor/fallback, visits, ordered
query/store digests, wrapped resource total and final complete lazy-state hash.
Caller/return/ESP/register/code/write/immutable-input/capacity-tail/nonselected
Cell/fallback guards pass. Complete read order and split initializer-store order
are not compared; concurrent mutation is outside the profile.

Initial static/template/live-height/Cell/terrain/type/Building/house/registry/
geometry/table storage remains supplied. In particular **104 is a supplied
global input**, not a recovered startup result. Earlier separately audited
resource phases and decoded map/overlay inputs do not establish original reader/
startup order. Full actor/occupant/tag/bridge construction, original heap/cache/
converter ownership, visibility/scheduling/pathfinding and frame parity remain
open. No runtime executable-read boundary was expanded.

## Reproduce

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

# Use an unused private destination. Original execution requires Mac host JIT.
build/tools-env/bin/python tests/compare_resident_map_floor.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/resident-floor-new
build/tools-env/bin/python tests/compare_resident_map_floor.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/resident-floor-v1/expected.json \
  --report private/map-depth-1006/resident-floor-v1/replay-new.json
build/tools-env/bin/python tests/compare_resident_map_floor.py \
  --exe private/official-1006-probe/game.exe \
  --native build/sanitize/resident-map-finalization-vectors \
  --expectations private/map-depth-1006/resident-floor-v1/expected.json \
  --report private/map-depth-1006/resident-floor-v1/sanitize-new.json

# Existing playable baseline; the new map/floor helper is not invoked here.
./run.command --crossing-light-demo
```

Select the Rhino; G/right-click moves, L toggles the host-placed light, R resets.
Only Apple Silicon macOS is tested. Actual SDL crossing checks existing native
integration, not new helper use or original-frame parity. Current evidence,
regressions, timings and remaining dependencies are in [HANDOFF.md](HANDOFF.md).
This is a locally verified checkpoint, not independent acceptance or a completed
playable terrain-depth capability. Bind prepared Cell/TMP and current floor to
Foot/base-depth/Unit-world next; actual level crossing and parked `(51,72)`,
elevation 4 remain acceptance scenarios before runtime depth promotion.
