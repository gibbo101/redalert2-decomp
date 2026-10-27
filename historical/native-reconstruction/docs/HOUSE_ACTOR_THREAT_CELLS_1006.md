# House threat grid with actual Object Cell and map children

The separate grid composition now joins complete4F3420/54E370, stock actor
threat/type/kind children, complete Object current-Cell5D51E0 and both actual
coordinate map548000 calls. No virtual child in this joined proof is intercepted.
The new `ObjectCurrentCell.hpp` copies the borrowed coordinates twice and returns
the second lookup's record/view; `HouseActorThreatCells` scopes that dependency
onto the existing single grid kernel. Production grid ownership and diplomacy
adoption remain open. This is not a new game command or scheduled effect.

## Recovered behavior and ownership

Both stock Infantry and Building vtables select5D51E0 at virtual1A4. The grid's
kind15 path still uses stored signed Cell454 words and Owner filtering; it does
not call the current-Cell getter. Its Building path now consumes the actual second
map result's Cell24 words, without the stored-Cell Owner/invalid exclusions.
Do not replace this with actor coordinates divided once, a cached first pointer,
or a separate temporary fallback. The first lookup can write the shared fallback
although its pointer is discarded. Coordinates are recopied for the second call;
the actual map also rereads its count and backing at each lookup.

Coordinate lookup reuses `mapCoordinateCell`: full signed X/Y division by256
before low32 wrapped combined indexing, signed count comparison, resident pointer
or one mutable fallback, and a word-pair fallback store on every miss. Z is copied
and forwarded but does not enter that map index. Resident Cell position words
remain independent of actor coordinates and table indices. A negative X or large
axis does not justify adding independent per-axis bounds. Native invalid storage/
count/out-of-grid stencil refusals retain their earlier scope, not fault parity.

The scoped binding borrows live actor coordinates and a coordinate service bound
to the same map/count/fallback owners. It makes no queries at construction, copies
no map or actor, and restores the prior Cell callback on destruction/unwind.
The caller owns all referenced lifetimes. Services return borrowed Cell word views;
lookup effects stay visible immediately. The stock threat/grid kernels are reused,
not duplicated. Other existing current-Cell callers keep their previous scopes.

## Exact original evidence

Supplied base executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08/supplied1.006 lineage/reported no-CD/unverified pristine remain distinct.
The new verifier composes existing grid/threat/coordinate pins, fingerprints all
87 bytes of5D51E0, checks its two call sites and both stock1A4 vtable associations.
Original instruction bytes remain unchanged; Unicorn is research/test-only.

All806 fresh complete grid roots match. Actual entries include2,038 stock threat/
type80 calls,1,476 Building getters,786 current-Cell getters,1,572 coordinate map
calls and1,528 projections. Every entered current-Cell getter has exactly two map
calls. The ordered trace records actor/type/kind/getter entries, every map input,
returned resident/fallback identity and every packed fallback write. Getter4532F0
execution counts remain audited separately because it is a pure field load.

Cases retain shared types, null/negative/wrapped threat behavior and Owner filters,
then add signed full-coordinate limits, wrapped combined indices, resident/missing
Cells, supplied map counts, repeated actors and shared fallback padding. Diagnostic
first-miss hooks alter actor coordinates, map count or table backing to distinguish
second-copy/second-query behavior and later shared consumers. These mutations are
supplied probes, not observed gameplay or a new production callback. Initial
actors/types/House/session/registry/table/Cell/global associations remain supplied.

The same guest owns every routine and record. Caller stack/register audits and
code/table guards remain active. All arena/padding outside grid writes is checked;
map tables and Cells are immutable; map count/backing match only explicit probe
changes; fallback bytes outside the position word-pair remain unchanged. Expected
grid/state results come from original memory, not a native or Python formula.
No live-original gameplay or whole-game/frame claim follows.

Canonical original-only expectations:
`private/boot-camp-20261018/grid-map-fresh-a1/expected.json`, SHA256
`48d6a4ba4edd56f0eb3759d9de1af7de69abd1904f09bec295c427e0efedc85c`.
Original execution34.511s/native comparison0.087s. Both targeted builds,6 focused
CTests per profile,35 Python tests and21 guarded normal/sanitizer/uncached replays
pass. Replays cover this join, earlier grid/threat join, stock threat, legacy House
grid/score/projection, diplomacy, full-coordinate lookup and actor ground state.
Prior immutable expectations keep their original identities; current runner/source/
input guards remain. No whole inventory refresh or closed finalizer rerun.

A Python preflight test first found that the new trace validator still admitted
legacy supplied V420 records through inherited validation. The guard was repaired
before any original execution; the failure note and corrected log remain private.
A negative-X fixture was also moved into the admitted grid stencil domain before
original execution; malformed address behavior is not claimed. No original/native
comparison failed. Local verification is not independent acceptance.

Configuration normal/sanitizer7.092s/8.116s; initial targeted builds2.461s/2.175s;
final rebuilt runner1.096s/1.006s. Exact commands/check timings belong in
`grid-map-build-*-a1.json`, `grid-map-final-build-*-a1.json` and
`grid-map-validation-*-a1.json`. Receipt:
`private/boot-camp-20261018/grid-map-receipt-a1.json`. Repair/task-wall costs are
unavailable. No caching was added. Unchanged app/owner binary hashes retain their
prior106-tick SDL walking scope; no drawing/input change or new SDL run is claimed.

## Reproduce and next integration

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake -S . -B build/native
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake --build build/native --target house-actor-threat-cells-vectors --parallel 6
build/tools-env/bin/ctest --test-dir build/native --output-on-failure -R '^(house-actor-threat-cells|house-actor-threat|techno-threat|house-threat|house-diplomacy|actor-ground-state)-domain$'
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_house_actor_threat_cells test_house_actor_threat test_techno_threat test_house_threat test_house_diplomacy test_map_coordinate_cell_evidence test_actor_ground_state_evidence
# Keep previous originals immutable; choose new audit/report paths.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/NEW-GRID-MAP.audit.json \
  tests/compare_house_actor_threat_cells.py --exe private/official-1006-probe/game.exe \
  --native build/native/house-actor-threat-cells-vectors \
  --expectations private/boot-camp-20261018/grid-map-fresh-a1/expected.json \
  --report private/NEW-GRID-MAP.json
./run.command --boot-camp-walk
```

Use the sanitizer runner or put `--uncached` before the driver for other profiles.
Fresh originals require a new `--output` directory and research-only JIT.
`./build.command`, `./test.command` and `./run.command` remain project entry points.

Next bind grid/House/actor/map owners in the production world with explicit private
table lifetimes and warm clone isolation, without adding runtime executable reads.
The remaining map/redraw/type/image effects still precede diplomacy/action37.
Startup/session/Team/audio/live scheduling/UI/ordinary SDL Objective1 remain open.
Both games and Objective1 are incomplete. Original tables stay private; no public
code, dependency, worker, download or Windows action was added.
