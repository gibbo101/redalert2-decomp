# Supplied RA2 1.006 ordinary Cell recalculation

October 15, 2026, after `209397b`. This continues the same map/tile-depth
initialization capability. `assets/MapCellAttributes.*` recovers the bounded
ordinary recalculation around supplied LAT/passability services. It stays unwired;
the playable renderer still supplies neutral Foot tile/contact fields.

Current update: [THEATER_TILE_INPUTS_1006.md](THEATER_TILE_INPUTS_1006.md) establishes
that the guarded type byte +0x2B1 is ShadowCaster with nonzero ShadowTiles, not
Morphable (+0x2B0). The native field is now `shadowCaster`; the guard/arithmetic
is unchanged. Fresh v3 repeats all 2,816 results and both replays after that source
correction. Earlier v1/v2 receipts remain historical. Original checkpoint check
counts/times below retain their original scope; the new note records current checks.

## Identity and references

Exact supplied base engine: 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`,
`private/official-1006-probe/game.exe`, equal to the approved private Windows copy.
Embedded 1.08, supplied 1.006 lineage and reported no-CD modifications remain
distinct; pristine authenticity is unverified. No new Windows action or transfer.
The native app never executes this binary.

[REFERENCES.md](REFERENCES.md)'s pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439`, `docs/voxels.md` and LICENSE,
and YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88`, `CellClass.h`,
`MapClass.h` and `IsometricTileTypeClass.h` supply map/attribute vocabulary.
Hypothesis: a complete ordinary Cell recalculation consumes the verified decoded
map/TMP inputs, computes height/land/ramp and updates buffer records before Foot
depth uses them. Exact base instructions and isolated execution establish only
the bounded result below. No reference/header/generated or lifted game code was
incorporated; no dependency or THIRD_PARTY notice was added.

## Original and native boundary

`verify_map_cell_attributes.py` checks twelve complete ranges / 1,081 instructions,
including [MAP_CELL_INPUTS_1006.md](MAP_CELL_INPUTS_1006.md)'s nine ranges. Added:

| Root | Scope |
| --- | --- |
| `0x472540..0x472FF2` | Complete Cell recalculation; no overlay/new tube/new animation/shadow-casting neighbor writes |
| `0x529340..0x529393` | Resident sub-tile validity; optional loading is refused |
| `0x54FAB0..0x54FAE6` | Actual wrapped/clamped map-buffer index |

The fixture executes the complete recalculation root and actual validation,
resident getter, ramp, land and dimension children. Original `0x471D10` LAT and
`0x478F40` passability remain explicit services: the first supplies the resulting
tile index, the second supplies Cell `+0x4C`. Neighbor lookup `0x548070` returns
supplied signed levels. Table/record/buffer construction and tube count are supplied.
Synthetic initial/missing/invalid/fallback cells are fixtures, not original map
initialization. No original instruction is patched. No original LAT/passability,
decompression/relocation, allocation/ownership or whole-frame parity claim follows.

Preserve sentinel 65535 and signed upper-bound handling, invalid image/sub-tile
reset, level override only on the valid-tile path, signed level bytes, ramp byte,
height-minus-30 low-32-bit subtraction and signed divide by 15 before byte storage.
LAT can change the tile index while subsequent metadata reads still use the saved
original type pointer. The buffer-index helper wraps the dimension sum/product,
tests the resulting signed index, then clamps to zero or capacity minus one.

Cliff checks visit `(0,-1),(-1,0),(2,2),(1,1),(-1,1),(1,-1)` relative to the cell,
with signed-word wrapping and early exit when neighbor level is at least current
level plus four. Nonzero mode performs queries; only byte mode exactly 2 changes
eligible land to 3. The invalid-image early return permits only land 0; the final
path permits 0/2/6/8. Passability follows those checks. Normal final writes are
four-byte record level, passability, then ten-byte record level; invalid-image
early return writes ten-byte level before passability. Untouched record bytes and
capacity tails remain unchanged.

Caller return/ESP/callee-saved registers, stack tail, allowed guest writes,
immutable map/type/image/land/global inputs, unmodeled Cell bytes, selected record
bytes/tails and ordered selected stores/service events are audited. Supplied
service writes use explicit API writes; they are not recovered internal writes.
The comparison establishes selected writes and service order, not all read order.
Native geometry/negative-subscript/nonpositive-capacity/unsupported-branch refusals
are safety guards, not original malformed-input parity. Overlay is refused; loaded
ordinary land 10 requires a supplied valid tube index/count. Animation construction
and shadow-casting neighbor writes remain refused. Those guards do not enable tunnels
or animation gameplay.

## Verification and reproduction

**2,816 fresh results** pass: 512 actual buffer-index cases and 2,304 complete
ordinary recalculation cases. They include resident/null/missing sub-tiles,
fallback, sentinel/out-of-range tiles, every cliff query position/no-match scan,
mode distinctions, signed levels, wrapped dimensions and supplied LAT tile changes.
Counts: 5,120 audited roots, 6,858 neighbor calls, 257 LAT and 2,254 passability
service calls, 14,979 ordered selected stores. The 13-result pilot and full suite
match. No owned-map recalculation or runtime association is established here.

Current receipts: `private/map-depth-1006/cell-attributes-v3/{expected,report}.json`,
`native-replay.json`, `sanitize-replay.json`. Initial v1 is historical after the
receipt's source list was expanded to include imported native/verifier helpers;
v2 was freshly generated, never relabeled. Relevant engine/source/inspection/
runner/expectation identities are checked before and after runs.

```sh
./build.command
build/tools-env/bin/ctest --test-dir build/native --output-on-failure
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
# Isolated original execution requires the authorized Mac host JIT context.
# Always choose an unused output directory for fresh evidence.
build/tools-env/bin/python tests/compare_map_cell_attributes.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/cell-attributes-new
build/tools-env/bin/python tests/compare_map_cell_attributes.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/cell-attributes-v3/expected.json \
  --report private/map-depth-1006/cell-attributes-v3/replay-new.json
# Add --native build/sanitize/map-cell-attribute-vectors for sanitizer replay.
```

Both builds, **396 distinct Python tests**, **19 normal / 18 sanitizer CTests**
and normal/sanitizer original replays pass. The preceding 537 input expectations
also replay on both current runners. Earlier complete caller/world normal and
sanitizer runner hashes and all 160 recorded source entries remain identical;
their accepted receipts are retained, not new original execution. Source/diff/
local-link audits pass. No runtime source changed and no new SDL run was performed
for this unwired prerequisite; actual SDL checks remain required at capability
integration. Only Apple Silicon macOS is tested; locally verified is not independent
acceptance.

Private `recalc-start.json`, attempts/closing records and logs retain timings,
the initial field-owner compile error, duplicate imported-test discovery correction,
source-list expansion, historical v1 and unavailable inherited elapsed measurements.
No worker/new evidence cache/source-install/system/Windows change or new transfer.

## Next dependency

Recover the actual LAT and ordinary passability children, relevant theater tile
type/default associations and initialization order before promoting cell fields.
Then join prepared cells with Foot predicates/depth and existing Unit/world
receipts, followed by actual SDL crossing and parked cliff `(51,72)`, elevation 4.
Contact/overlay/bridge/tube construction, full map/actor lifetime, heap ownership,
camera/fog/scheduling/pathfinding and whole-frame fidelity remain open. This
checkpoint does not complete that observable capability or the full base RA2/YR game.
