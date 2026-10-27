# Supplied RA2 1.006 resident map preparation

October 15, 2026, after `44ff3d7`. This joins the recovered ordinary map parent
to native LAT/passability/permission/resident-TMP children, using evolving shared
Cells and the verified **Wheel** column. It closes the earlier all-images-absent
fixture gap. The helper remains unwired; the terrain-aware Foot/world crossing
and cliff capability is still incomplete. This is a locally verified prerequisite,
not an independently accepted gameplay milestone.

## Identity and references

Both private supplied engines rehash to 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded version 1.08, supplied 1.006 lineage and reported no-CD modifications
remain separate provenance; pristine authenticity is unverified. No new transfer,
Windows action, source-install or system change occurred. The app never executes
this binary.

Consulted [REFERENCES.md](REFERENCES.md), pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` `docs/voxels.md`/LICENSE and YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` `MapClass.h`, `CellClass.h`,
`IsometricTileTypeClass.h` and `ScenarioClass.h`. Hypothesis: scenario preparation
revisits loaded Cells, and general resident TMP metadata changes their depth inputs.
Exact base inspection/execution resolves this hypothesis. Recomp is not an
original-behavior oracle; YR names are leads. No upstream/header/generated/lifted
code or extracted table was incorporated. Existing license boundaries/notices apply.

## Startup order: inspected, not executed

The earlier creation-time call alone does **not** establish loaded-map ordering.
`verify_resident_map_preparation.py` adds complete inspection of:

| Complete range | Instructions | Scope here |
| --- | ---: | --- |
| `0x65EB40..0x65F979` | 963 | Scenario caller, inspection only |
| `0x49CFD0..0x49D905` | 636 | Map INI caller, inspection only |
| `0x52B650..0x52B683` | 18 | Usage reset, inspection only |

The Map INI caller creates empty geometry before reading decoded records. Its
theater branch either reloads at `0x529870` or resets usage at `0x52B650`; the
reset is **not unconditional**. Decoded IsoMapPack5 reading is called at
`0x49D818`, tile sweep at `0x49D875`, then LocalSize setup and level scan.

The scenario caller invokes Map INI at `0x65F6C0`, later iterates Cells and calls
recalculation with -1 at `0x65F71B`, loads additional actors, then invokes the full
two-pass parent at `0x65F846`. Intermediate services/actor effects are not recovered
by inspecting this order. The 18-instruction reset walks primary/alternate chains
and clears usage; no executed reset result is claimed here. Discovery xrefs are
private leads; aligned complete-root inspection establishes these call sites.

## Native join and executed boundary

[MapPreparation.cpp](../src/assets/MapPreparation.cpp)'s `prepareResidentMapCells`
binds the existing parent to unchanged Cell/LAT/passability/permission/TMP kernels.
Lighting remains a callback into presentation. Map lookup uses shared evolving
Cells and the supplied fallback. The land records select Wheel; unrelated speed
columns are varied independently in synthetic tests. Preserve saved type retention
across LAT changes, both pass resets/terminal-null advances, lighting before
recalculation, cliff neighbor order and original selected buffer/store order.

The original suite executes the same **29 complete ranges / 3,050 inspected
instructions**, with 24 entered roots, as [MAP_PREPARATION_1006.md](MAP_PREPARATION_1006.md).
The three new caller ranges above add 1,617 inspected instructions, not new executed
startup proof. Original instructions are unchanged. Caller stack/ESP/registers,
return address, immutable general image/type/table/scenario/geometry inputs,
unmodeled Cell/fallback bytes and buffer capacity tails are guarded.

`Q` fixtures extend the existing native vector runner to general resident images
with up to 60 subtiles, optional null entries, independent dimensions, signed
Y/extra-Y and raw land/ramp bytes. The oracle supplies relocated pointer records;
it does not run the file loader, TMP parser or type constructor. Native geometry,
slot/position/fallback, buffer and callback refusals are safety guards, not original
malformed-input parity. The existing `P` protocol/scope is retained.

## Evidence and limits

**51 fresh original/native results** and normal/ASan/UBSan replays pass: 48 seeded
general-image/shared-map cases and three owned tile-only map projections, one per
cliff mode 0/1/2. Each owned projection includes all **13,515 records**, 838 supplied
primary type records and **268 resident primary images**. All 1,532 sloped Cells
and 872 extra-height Cells participate. In mode 2, 28 clear Cells become rock.
At `(51,72)`, level 4, original output is tile 0 / land 3 / slope 0 /
extra height 0 / passability 6; modes 0/1 retain land 0 / passability 0.

Compare every selected Cell/light field, full buffers, final cursor/fallback,
ordered visits and selected child/query/store digests. Counts: 52 audited roots
(51 parents plus direction initialization), 41,830 recalculation/light/resource
entries each, 83,762 iterator entries and 9,675,055 audited guest stores. This is
selected write/query order, not complete memory-access ordering.

Owned metadata comes from hash-checked local slices resolved by the native archive
reader. The private manifest records physical sources/offsets/lengths/hashes. Host
INI/decoded-stream preparation, primary image selection, type animation -1/lazy 0/
shadow-caster false, initial fields, geometry, land table and scenario inputs are
**supplied fixtures**. Overlays, actors/tags/occupants and palette allocation are
deliberately absent. Alternate selection, complete original initialization, parser/
heap ownership, converters, contacts, actor effects and full-map/frame parity are
not established. The real-map dimensions/metadata improve the tested input domain;
they do not turn a tile-only fixture into a complete original startup oracle.

Current receipts: `private/map-depth-1006/resident-map-v3/`. v1/v2 are historical
following native safety tightening, including an early height bound that prevents
signed overflow while refusing malformed geometry. v3 is freshly executed and its
commands/results equal both earlier sets. Changed parent sources have fresh
**map-preparation-v4 (65)** proof and both replays; its commands/results equal
v2/v3. Earlier receipts remain untouched.
Twenty-four earlier source/runner sets replay retained identity-checked expectations
(including land-v2 and sweep-v3). The map decoder identity is unchanged.

Both builds, **485 Python tests**, **28 normal / 27 sanitizer CTests** and source/
diff/local-link audits pass. Runtime behavior is unchanged. The rebuilt existing
lighted crossing passes actual SDL selection/right-click/presentation, 79 samples /
78 updates, culling/clipping/cache bypass and pan return. This checks the existing
baseline, not the new unwired helper or new cliff capability. Actual SDL cliff
acceptance remains required at integration. Only
Apple Silicon macOS is tested; no worker or evidence cache was added.

## Reproduction

```sh
./build.command
build/tools-env/bin/ctest --test-dir build/native --output-on-failure
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
# Configure sanitizers as in README, then:
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

# Choose a new ignored destination; source installation is read-only.
build/tools-env/bin/python tools/prepare_resident_map_fixture.py \
  --data-dir private/official-1006-probe \
  --output private/map-depth-1006/resident-fixture-new
# Fresh original execution requires the authorized Mac host JIT context.
build/tools-env/bin/python tests/compare_resident_map_preparation.py \
  --exe private/official-1006-probe/game.exe \
  --assets private/map-depth-1006/resident-fixture-new \
  --output private/map-depth-1006/resident-map-new
build/tools-env/bin/python tests/compare_resident_map_preparation.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/resident-map-v3/expected.json \
  --report private/map-depth-1006/resident-map-v3/replay-new.json
# Add --native build/sanitize/map-preparation-vectors for sanitizer replay.

# Current playable baseline, unchanged by this prerequisite:
./run.command --crossing-light-demo
# Select Rhino; G/right-click moves, L toggles light, R resets.
```

Fresh v3 driver/original/native: 31.833/29.659/0.166 s (CLI 32.015 s).
Normal/sanitizer replay CLI: 2.099/5.088 s. Initial/final normal builds:
7.268/13.104 s; final sanitizer 9.019 s. Intermediate builds and guard-target
rebuilds are retained privately. Fresh parent refresh CLI: 10.080 s; replays
1.687/3.146 s. Python CLI 1.737 s (485 tests, 0.537 s); final CTest CLI
0.534/2.117 s. Twenty-two prior replays overlap, wall 54.724 s, plus sweep
replays 1.356/2.602 s. Actual baseline SDL 2.309 s. Independent checks overlap;
private start/attempt/closing records retain all times and inherited work.
Full active-delivery elapsed is unavailable. One guard-test token initially
changed a still-valid height and was corrected. Review found and repaired the
malformed-height guard overflow before final evidence. No native/original mismatch,
failed original execution, or gameplay repair occurred.

## Next capability dependency

Use the inspected scenario order to choose the relevant stage explicitly. Verify
remaining initial state/usage reset/variant associations and overlay/actor branch
inputs that can affect the Foot consumers; keep unrelated zone/pathfinding deferred.
Then test actual prepared Cell/TMP dimensions against the relevant Foot/base-depth
branches and join Unit/world drawing. Do not promote runtime neutral fields from
this supplied tile-only fixture alone. Require actual SDL level crossing and the
parked `(51,72)` cliff scenario before calling the capability complete. Full base
RA2, then YR, remains active and incomplete.
