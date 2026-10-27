# Supplied RA2 1.006 complete ordinary Cell recalculation join

October 15, 2026, after `ecf1c91`. The new native runner binds the unchanged
`recalculateMapCellAttributes` to unchanged LAT/passability/permission/lookup
helpers. The original fixture nests their actual instructions inside the complete
recalculation root. This is a verified prerequisite of the crossing/cliff map-depth
capability. No runtime field is promoted and no playable capability is added.

Current update: [THEATER_TILE_INPUTS_1006.md](THEATER_TILE_INPUTS_1006.md) corrects
the guarded +0x2B1 field's provisional `morphable` name to `shadowCaster`. The
guard/arithmetic is unchanged. Fresh v3 repeats all 1,536 results and both replays
after that source correction; v1/v2 remain historical. Original checkpoint check
counts/times below retain their original scope; the new note records current checks.

## Identity and reference hypothesis

Exact supplied base engine: `private/official-1006-probe/game.exe`, 4,485,392 bytes,
SHA256 `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`,
equal to the approved private Windows copy. Embedded 1.08, supplied 1.006 lineage
and reported no-CD modifications remain separate; pristine authenticity is
unverified. The app never executes this binary. No new Windows action/transfer.

[REFERENCES.md](REFERENCES.md)'s pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439`, `docs/voxels.md`/LICENSE and
YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88`, `CellClass.h`, `MapClass.h`
and `IsometricTileTypeClass.h` supply connectivity/map vocabulary. Hypothesis:
actual children can nest in the complete ordinary root while retaining saved type,
level updates, lookup effects and buffer write order. Exact base instructions and
fresh joined execution decide this. No upstream/header/generated or lifted game
code was incorporated; no dependency or THIRD_PARTY notice was added.

## Joined boundary and audits

`verify_map_cell_preparation.py` composes
[MAP_CELL_ATTRIBUTES_1006.md](MAP_CELL_ATTRIBUTES_1006.md) and
[MAP_CELL_CHILDREN_1006.md](MAP_CELL_CHILDREN_1006.md) inspection: **18 unique
complete ranges / 1,896 instructions**, including inherited selected-constructor/
reader ranges that this join does not execute. The actual complete root
`0x472540` now nests actual resident validation/TMP consumers, LAT `0x471D10`,
passability `0x478F40`, permission `0x55A660`, map getter `0x548070`, word-add
and resident/null image getter/ensure-image children. No API service replaces
LAT/passability/neighbor lookup here. No original instruction is patched.

The native runner supplies a stable 9x9 pointer grid and fallback, binds ordinary
LAT against the actual current record, then forwards passability through permission
and the supplied float32 speed table. Callback tracing observes the same entry/
selected-store ordering; it does not supply child results. The parent retains
its earlier type pointer after LAT changes the tile index. Distinct alternate
type/image/land/ramp/dimension inputs ensure a mistaken re-selection can change
the expected result. New tile images can be resident or null with lazy-load byte
zero; their original final checks execute without loading.

The fixture supplies the 1,024-entry registry, resident TMP pointer headers,
initial fields, geometry, tile-set globals, directions, land mapping, float32
speeds, tube count and immutable neighboring records. It starts from an ordinary
nonfallback cell, no overlay/occupants, no new tube/animation/shadow-casting writes.
Signed levels/overrides, header dimensions, table aliases/missing cells, shared
type pointers and low-32-bit arithmetic retain the earlier recovered behavior.
Full type/theater/map construction and initialization order remain unverified.
This is not a whole owned-map preparation run or original gameplay observation.

Return/ESP/callee-saved registers, stack tail, exact allowed guest stores,
immutable type/image/map/table/neighbor/direction/global/speed inputs, unmodeled
current/fallback bytes, record capacity tails and ordered selected stores are
audited. Fallback coordinate writes are original guest stores. Native refusals
remain safety guards; no malformed-input/full memory read-order/ownership claim.
The renderer's neutral tile/contact fields remain explicit host inputs.

## Evidence and commands

**1,536 fresh original/native results** and normal/ASan/UBSan replays pass.
The 16-result pilot also passes. Counts: 3,072 checked roots (one index setup
and one complete recalculation per case), 1,536 actual recalculation/passability/
permission entries, 438 actual LAT/ramp/land/dimension entries, 305 actual LAT
changes/alternate-type image queries, 218 null-image ensure calls, 6,940 separate
map getters, 8,476 total lookup events and 17,506 ordered selected stores.
Final selected fields, fallback coordinate, both record buffers and events match.
These are scoped execution counts, not fidelity percentages.

Current receipts: `private/map-depth-1006/cell-preparation-v3/{expected,report}.json`,
`native-replay.json`, `sanitize-replay.json`. V1 is historical after fixture
strengthening with differing post-LAT metadata; v2 was freshly generated, never
relabeled. The numerical recovery kernels did not change. Relevant engine,
inspection, sources, runner and expectation identities are checked before/after runs.

```sh
./build.command
build/tools-env/bin/ctest --test-dir build/native --output-on-failure
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
# Fresh isolated original execution requires the authorized Mac host JIT context.
# Use a fresh, unused output directory.
build/tools-env/bin/python tests/compare_map_cell_preparation.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/cell-preparation-new
build/tools-env/bin/python tests/compare_map_cell_preparation.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/cell-preparation-v3/expected.json \
  --report private/map-depth-1006/cell-preparation-v3/replay-new.json
# Add --native build/sanitize/map-cell-preparation-vectors for sanitizer replay.
```

Both builds, **413 distinct Python tests**, **20 normal / 19 sanitizer CTests**,
source/diff/local-link audits and both replays pass. Eight earlier input/root/
child/complete Unit-world normal/sanitizer runner/source identity sets remain exact
(`joined-retention.json`), retaining their accepted receipts. No runtime source
changed; no new SDL run for this unwired fixture join. Actual SDL remains required
at complete map-depth capability integration. Only Apple Silicon macOS is tested;
local verification is not independent acceptance.

Fresh v2 driver/original/native **5.711/4.501/0.097 s**, CLI **5.86 s**. Normal
replay CLI **1.15 s**, native **0.078 s**. Initial sanitizer full build **11.59 s**;
updated native/sanitizer runner builds **1.93/1.69 s**. Normal CTest **0.60 s**.
Private joined start/attempts/closing/log records retain other replay/check times,
initial normal build/inherited elapsed unavailable, the no-occupant preparation
correction before pilot and v2 strengthening. No failed original execution or
gameplay repair occurred. No worker/evidence cache/source-install/system/Windows
change or transfer occurred.

## Next dependency and capability acceptance

Verify original theater tile/type/default/shift associations, map geometry and
initialization order from this exact engine before deriving runtime fields from
the supplied map. Keep overlays/bridges/tubes/contact association explicit and
refuse unsupported profiles. Then join prepared cells to existing Foot predicates/
depth and retained Unit/world drawing; require level crossing and parked cliff
`(51,72)`, elevation 4, with actual SDL input/render checks. Camera/fog/scheduling,
pathfinding, ownership/lifetime and whole-frame fidelity remain open. Full base
RA2 then YR remains active and incomplete.
