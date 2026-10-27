# Supplied RA2 1.006 selected theater tile inputs

October 15, 2026, after `360ba0c`. This recovers selected theater set/type inputs
needed for the same crossing/cliff map-depth capability. The helper stays unwired;
the renderer still supplies neutral Foot tile/contact fields.

## Identity and references

Exact supplied base engine: 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`,
`private/official-1006-probe/game.exe`, equal to the approved private Windows copy.
Both were rehashed unchanged. Embedded 1.08, supplied 1.006 lineage and reported
no-CD modifications remain separate; pristine authenticity is unverified.
The app never executes this binary. No new transfer or Windows action occurred.

[REFERENCES.md](REFERENCES.md)'s pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439`, `docs/voxels.md`/LICENSE and
YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88`,
`IsometricTileTypeClass.h`, `CellClass.h` and `MapClass.h` supply vocabulary.
Hypothesis: the base theater loader associates General set numbers with cumulative
tile bases and initializes the type bytes consumed by Cell recalculation/Foot.
The base instructions and fresh execution establish the associations below;
YR offsets/property names do not establish them. No upstream/header/generated or
lifted code was incorporated. No dependency or THIRD_PARTY notice was added.

## Verified projection and correction

`assets/TheaterTileInputs.*` implements a **selected projection**, with decoded
INI results supplied and **every TMP/alternate image absent**. The complete original
theater root `0x529870..0x52B2DA` and actual tile constructor
`0x528EE0..0x52911D` execute unchanged: two complete ranges / **1,730 instructions**.
The earlier `0x529710` theater-load lead is a two-instruction false-return leaf,
not this loader. `verify_theater_tile_inputs.py` pins the exact ranges/image slot.

The selected General keys are `WaterBridge`, `ShorePieces`, `ClearToRoughLat`,
`ClearToSandLat`, `ClearToGreenLat`, `ClearToPaveLat`, `MiscPaveTile`, `PavedRoads`,
`Medians`, `RampSmooth`, `RampBase`, `RoughTile`, `SandTile`, `GreenTile`, `PaveTile`
and **BridgeSet**. The first fifteen retain existing LAT-global order. BridgeSet
populates Foot's `0xA52C74`. Set numbers are converted to cumulative primary tile
indices, not passed directly to Foot/LAT. Missing/unvisited associations remain -1.
The loader stores the terminal set's base and applies matching General associations
**before** testing `TilesInSet == -1`. Other negative counts do not terminate.

`LastTilesInSet` absent/equal uses the current count. A differing non--1 value
advances the old cumulative count by that value and appends a shift with that
threshold and wrapped `current-last` delta. Preserve order and low-32-bit arithmetic.
MarbleMadness/NonMarbleMadness default to 65535; other supplied set numbers are
converted after all sets using that set's base plus the primary tile's local index.
ToSnowTheater/ToTemperateTheater retain their supplied integer values here.

The selected base type association is:

| Base field | Input / default |
| --- | --- |
| `+0x2B0` | Morphable, false |
| `+0x2B1` | ShadowCaster **and nonzero ShadowTiles**; initially false |
| `+0x2B2` | AllowToPlace, true |
| `+0x2B3` | RequiredForRMG, false |
| `+0x2D5` | AllowBurrowing, true |
| `+0x2D6` | AllowTiberium, false |

**Correction:** Cell recalculation tests `+0x2B1`, previously provisionally named
`morphable` in `MapTileAttributes`. It is now named `shadowCaster`; the guarded
neighbor-write branch remains refused. The numerical kernel/guard condition is
unchanged. [MAP_CELL_ATTRIBUTES_1006.md](MAP_CELL_ATTRIBUTES_1006.md) and
[MAP_CELL_PREPARATION_1006.md](MAP_CELL_PREPARATION_1006.md) have freshly generated
v3 receipts, **2,816 and 1,536 results**, plus both replays. Earlier v1/v2 receipts
remain historical, never relabeled as current source evidence. This does not
enable either shadow-casting neighbor writes or morphable gameplay.

## Fixture services and limits

Supplied services cover original INI parsing, base ObjectType construction, heap,
file objects/data, timer/progress, graphics reset and empty vector clear. Original
tile construction and its successful appends run with sufficient supplied vector
capacity. No existing types/shifts are destroyed, tile animation section is absent,
all TMP/alternate requests return null and only selected type fields are compared.
The owned INI is host-decoded into results passed to the original GetInt/GetBool
boundaries; this does not verify original INI parsing. Defaults passed by the actual
loader are asserted. No original instruction is patched.

Return/ESP/callee-saved registers/stack tail, immutable vector headers, exact allowed
image writes, dynamically allocated arena bounds, unmodeled type bytes and all
registry/shift/set-table capacity tails are checked. Selected metadata/tables match;
full store/read order, full type/base construction, loaded TMP/alternate behavior,
file/archive/graphics behavior and allocation/ownership/lifetime are not claimed.
Native limits/terminator/alternate-set refusals are safety guards.

The owned temperate values cover **82 sets / 838 primary types**, plus a terminal
set entry, with images deliberately absent. The INI was privately read from the
physical source slice pinned by the retained effective-asset receipt. Its hash is
`bf656852ad19636068f2dde6f9ddd1440ecf0e13e6e4de6cd7fb179a3592549d`;
`private/map-depth-1006/theater-assets/provenance.json` records source offset/hash.
This reuses the source receipt, not a fresh original archive query or loaded-map run.

## Evidence, commands and continuation

**481 fresh original/native results**, normal and ASan/UBSan replays pass: 384
signed count/shift/flag/alternate-set cases, 96 individual key associations and one
owned-temperate projection. Counts: 481 complete loader calls, 5,096 actual tile
constructors, 49,689 supplied INI calls and 1,202,672 audited guest stores. Counts
describe fixture execution, not a fidelity percentage.

Current receipts: `private/map-depth-1006/theater-inputs-v2/{expected,report}.json`,
`native-replay.json`, `sanitize-replay.json`. V1 is historical after strengthening
arena/unmodeled-byte audits and source identities; v2 is fresh execution.

```sh
./build.command
build/tools-env/bin/ctest --test-dir build/native --output-on-failure
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
# Fresh execution: authorized Mac host JIT context; use an unused destination.
build/tools-env/bin/python tests/compare_theater_tile_inputs.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/theater-inputs-new
build/tools-env/bin/python tests/compare_theater_tile_inputs.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/theater-inputs-v2/expected.json \
  --report private/map-depth-1006/theater-inputs-v2/replay-new.json
# Add --native build/sanitize/theater-tile-input-vectors for sanitizer replay.
```

Both builds, **421 Python tests**, **21 normal / 20 sanitizer CTests** and audits
pass. Six earlier complete-world/input/child runner/source identity sets remain
unchanged, including all 160 complete-world source entries; their receipts are
retained. No runtime source changed and no new SDL run was performed for this
unwired prerequisite. Actual SDL remains required at capability integration.
Only Apple Silicon macOS is tested. Locally verified is not independent acceptance.

Fresh v2 driver/original/native: **8.668/8.212/0.028 s**, CLI **8.827 s**.
Normal/sanitizer replay CLI **0.472/0.513 s**, native **0.016/0.191 s**.
Final builds **6.954/6.992 s**, CTest **0.74/3.13 s**. Private theater start/attempts/
build/fresh/replay/closing records retain the initial missing-base mismatch and
correction, historical v1, inherited work and unavailable initial-build/active-total
times. No original execution failed; the initial pilot's native comparison failed.
No worker/evidence-cache infrastructure/source-install/system changes occurred.

Next verify original map geometry and initialization order, resident-image/type
association and supplied tables used in complete Cell preparation. The absent-image
projection must not be presented as a complete loaded-theater result. Keep neutral
runtime fields until those dependencies and unsupported overlay/bridge/tube/contact
guards are established; then join Foot depth and retained Unit/world drawing and
exercise the level crossing and parked cliff `(51,72)`, elevation 4, in SDL.
Pathfinding, actor/map/contact/cache ownership/lifetime, camera/fog/scheduling and
whole-frame parity remain open. Full base RA2 then YR remains active and incomplete.
