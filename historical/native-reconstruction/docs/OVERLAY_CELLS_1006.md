# Supplied RA2 1.006 overlay Cell decisions

October 15, 2026, after `86240fd`. This continues the same terrain-aware
Foot/world crossing and parked-cliff capability. It recovers overlay-dependent
Cell recalculation, empty-cell passability and resource classification/update.
These helpers remain unwired. Original overlay loading, registry/default/INI
construction and the overlay-bearing map preparation parent remain prerequisites.
This is a locally verified checkpoint, not a completed playable milestone or
independent acceptance. Full base RA2, then YR, remains incomplete.

## Identity and references

Both private supplied engines rehash to 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 lineage and reported no-CD changes remain distinct;
pristine authenticity is unverified. The approved Windows transfer was already
complete. This checkpoint performs no new Windows action or transfer and changes
no source installation, system tool selection, security setting or DRM driver.
The native application never executes this binary.

Consulted [REFERENCES.md](REFERENCES.md), pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` `docs/voxels.md`/LICENSE and YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` `OverlayTypeClass.h`,
`TiberiumClass.h` and `CellClass.h`. Hypothesis: overlays can replace tile land,
take a separate recalculation path and change passability/resource data before
Foot consumes map fields. Exact base inspection and execution verify the bounded
decisions below. YR vocabulary does not establish base offsets or original
construction. Recomp is a research reference, not an oracle. No upstream/header/
generated/lifted code or extracted table was incorporated; no new dependency or
THIRD_PARTY notice is required.

## Recovered behavior

[MapOverlay.cpp](../src/assets/MapOverlay.cpp) implements readable C++ around
supplied type records, Wheel speeds, directions and frame-table inputs:

- `0x5DC0B0..0x5DC16E`: complete classifier. Overlay -1 or a zero resource byte
  returns -1. Two adjacent signed ranges use wrapped endpoints; the first match
  returns the resource's stored index. A resource-marked overlay with no matching
  range logs and returns **zero**. Logging is an explicit supplied service.
- `0x478F40..0x4790E9`: complete passability root restricted to no occupants,
  with actual permission/lookup children. Permission comes first, then selected
  type byte +0x1FD, wall, overlay Wheel speed, rock and rubble gates. The overlay
  speed comparison tests zero and its x87 C3 test also accepts unordered; ordinary
  Cell land instead tests against double 0.01. Preserve the distinct predicates,
  special land results and gate priority. +0x1FD remains unnamed here.
- `0x476BA0..0x476CB2`: complete resource amount/update for argument **zero**.
  Classify the current overlay, save resource value, visit all eight neighbors
  with signed-word addition and actual map lookup, and count matching resource
  indices. The remainder after division by NumFrames selects the table byte.
  Store OverlayData, then return the low 32 bits of `(data+1)*value`. Random
  overlay replacement is outside this proof and has no native API.

These five complete inspected ranges, including permission and lookup, total
**392 instructions**, and all five are entered by the child suite. Original
instructions and original frame-table bytes are unchanged. The native helper
accepts the frame table as input; it adds no runtime executable-read boundary.

[MapCellAttributes.cpp](../src/assets/MapCellAttributes.cpp) now accepts explicit
overlay bindings. It stores overlay land before tile decisions. Land 4/9 or a
nonzero NoUseTileLandType byte takes the early path: obtain ramp when eligible,
clear a resource overlay/data on any nonzero slope, apply cliff checks, call LAT
then passability, and store four-byte level, ten-byte level, passability. That path
preserves level/extra height and can set **any** incoming land to rock in cliff
mode exactly 2. It does not use the ordinary final land filter.

The ordinary valid-image path calls the actual classifier after LAT. A resource
on slope greater than 4 restores tile land and clears overlay/data; a retained
resource whose type land is zero selects land 5. Other resource land is retained.
Nonresources restore tile land. Sentinel and invalid-image paths retain their
distinct land and buffer decisions. Saved TMP type use after LAT remains intact.
New tube/animation allocation and shadow-casting neighbor writes remain refused.

The joined suite inspects **17 complete ranges / 1,473 instructions** and executes
the complete Cell root with actual classifier, no-occupant passability, permission,
resident validation/getter/land/ramp/dimension and buffer-index children. Some
inherited input constructors and the separate resource-update root are inspected
but not entered by this join. LAT tile results and cliff neighbors are supplied
services; resource update is verified separately, not nested into the map parent.

## Evidence and limits

**6,795 fresh original/native results** pass, followed by both normal and
ASan/UBSan replays:

| Suite | Results | Boundary |
| --- | ---: | --- |
| `overlay-children-v3` | 4,491 | Classifier, empty passability/permission/lookup, argument-zero resource update |
| `overlay-recalculation-v4` | 2,304 | Complete Cell root with actual classifier/passability/permission and resident TMP children |

Child cases include explicit permitted zero/NaN/threshold/flag decisions, signed
wrapped and overlapping classifier ranges, and all 256 masks with all eight
neighbors present, plus aliases/fallbacks, varied positive divisors and wrapped
values. Counts: 4,491 audited roots; 12,090 classifier, 2,376 passability/permission,
1,283 resource and 9,976 lookup entries; 8,095 selected stores, 12,352 lookup
events and 967 supplied missing-resource logger calls.

Joined cases include early/ordinary/sentinel/invalid/fallback paths, signed levels,
override preservation, resource removal, cliff modes and ordered buffer writes.
Counts: 4,608 audited calls including separate buffer-index calls, 6,912 supplied
cliff-neighbor queries, 1,226 supplied LAT calls, 2,254 actual passability calls,
123 actual classifier calls, nine logger services and 18,130 selected guest stores.
Counts describe executed scope, not fidelity percentages.

Both suites audit caller stack/return/registers, code allowlists, immutable inputs,
unmodeled Cell/neighbor/fallback bytes and selected ordered stores/service events.
The joined suite also guards buffer capacity tails. Full memory-access order is
not compared. Initial Cells, repeated overlay-type bindings, resource/image
registries, directions, geometry, speed records and TMP pointer relocation are
supplied fixtures. The join does not prove heterogeneous registry construction.
Missing bindings, out-of-range indices, nonpositive frame divisors and short tables
are native safety refusals, not original malformed-input parity.

Private host decoding found 660 overlays on the owned map's active records. Raw
indices are useful discovery inputs, **not** proof of original registry order.
The INI list starts with key 1; directly treating raw zero-based indices as INI
keys gave incorrect names during discovery. List-order names remain hypotheses
until original construction/loading is executed. No owned-map overlay result,
complete startup, pathfinding, actor/contact/heap/cache lifetime or frame parity
is claimed. Runtime map-depth fields remain neutral. Source files stay separate
from original assets, private research and the SDL platform layer.

## Regression, reproduction and accounting

Affected ordinary suites have fresh evidence and both replays: Cell attributes
**v4 (2,816)**, Cell preparation **v4 (1,536)**, map preparation **v5 (65)** and
resident map **v4 (51)**. Each command/result sequence exactly equals its previous
scope. Earlier receipts remain untouched. Twenty unchanged source/runner sets are
retained by exact identity. The final audit checks **32 sets / 716 source entries**;
the map decoder identity remains unchanged.

Both builds, **500 Python tests**, **29 normal / 28 sanitizer CTests**, source,
diff and local-link audits pass. Actual SDL baseline checks pass selection/right-
click, 79 samples / 78 updates, lighted movement, culling/clipping/cache bypass and
pan return. This is a rebuilt-baseline regression, not new overlay/map-depth
integration or original frame fidelity. Only Apple Silicon macOS is tested.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

# Fresh original execution needs the authorized Mac host JIT context.
# Choose unused ignored destinations; supplied source stays read-only.
build/tools-env/bin/python tests/compare_map_overlay.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/overlay-children-new
build/tools-env/bin/python tests/compare_map_overlay_recalculation.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/overlay-recalculation-new
build/tools-env/bin/python tests/compare_map_overlay_recalculation.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/overlay-recalculation-v4/expected.json \
  --report private/map-depth-1006/overlay-recalculation-v4/replay-new.json
# Add --native build/sanitize/map-overlay-recalculation-vectors for sanitizer replay.

./run.command --crossing-light-demo
# Select Rhino; G/right-click moves, L toggles light, R resets.
```

Child driver/original/native: 5.745/5.288/0.136 s, CLI 5.856 s. Joined:
4.640/3.864/0.112 s, CLI 4.703 s. Four final normal/sanitizer replays overlap
over 9.660 s; the earlier twelve v2/ordinary replays took 14.748 s. Individual
CLI/native times remain private. Join v4 final replay CLI normal/sanitizer
times are retained separately after whitespace cleanup. Fresh ordinary refresh CLI:
3.005/5.328/10.180/32.385 s. Initial/final normal builds:
6.789/13.899 s; intermediate builds retained, final sanitizer 9.166 s. Python CLI:
1.229 s (500 tests, 0.421 s); final CTest CLI 0.645/3.459 s; SDL 3.354 s.
Full active-delivery elapsed and turn-start timing are unavailable. Private
`overlay-*-time.json`, replays, coverage and closing records retain measurements.
An initial complete-range length was corrected before execution. The expanded
join's failed comparison exposed two fixture variable collisions (permission
height and TMP Y); these were repaired before current evidence. Earlier v1/v2 receipts
remain historical. Final review made the saved resource-value read explicit and
corrected the oracle scope docstring; v3 freshly repeats the same commands/results
as v2, with both replays. Join v4 repeats v3 after final whitespace cleanup;
all recorded sources match the receipts. A py_compile attempt hit the host bytecode-cache sandbox;
unittest/import verification passes. An unsupported timing-wrapper help probe
failed without running game code. No native/original behavior mismatch remains,
gameplay repair, worker or evidence cache was introduced.

Continue with original overlay/default/INI/registry and decoded loading associations,
then the overlay-bearing map parent's resource/wall-owner effects. Keep unrelated
zones/pathfinding deferred. Verify prepared Cell/TMP fields against actual Foot
base-depth branches before runtime promotion. Require actual SDL level crossing
and parked `(51,72)`, elevation 4, before calling that capability complete.
