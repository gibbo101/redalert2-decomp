# Radar resources on shared Day 1 owners

Day 1's radar terrain path is a dependency of its Objective1 alliance/House sight
refresh. Complete5DC0B0 now runs below the existing Cell color/terrain/projection
chain, and the asset binding reads the application's mutable Cells and canonical
prepared type/image/resource records. This remains an explicit unscheduled query;
SDL radar rendering, sight scheduling and ordinary Objective1 are incomplete.

## Recovery and composition

The existing `classifyMapOverlay` algorithm is reused through
`classifyOverlayResource`, which reads field279 from an `OverlayTypeInputs` owner.
It retains overlay-1/nonresource laziness, first matching record, signed wrapped
range endpoints, stored resource index, and missing-range diagnostic then zero.
The classifier does not infer resource startup or economy. The older placement
adapter and original classifier body remain unchanged.

The exact supplied engine is4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage and reported no-CD provenance remain distinct;
pristine authenticity is unverified. Complete5DC0B0 is190 bytes/72 instructions,
SHA256 `9246fdd038c45698671579cf0ea9362ab445b1c65d4e2fbd3b895c95477ae476`.
The verifier fingerprints before using addresses and retains the independently
verified Cell/resident/overlay/demand/terrain/projection children. No external,
generated or lifted code/dependency/runtime executable read was introduced.

The Cell parent uses the classifier only after its resource flag and null alternate
image branch. Any result except-1 selects RGB170,170,130. Therefore a missing
resource range (result0) still selects resource color, whereas a matching record
whose stored index is-1 falls through to TMP terrain color. Do not substitute an
ordinal position or treat missing ranges as nonresources.

All958 original sequences match1,310 Cell roots,814 classifier roots/returns,
584 missing diagnostics,288 overlay/demand calls,80 demand file loads,176 terrain
and88 projection joins. Whole output backings match2,016 terrain RGB stores and
2,080 projected pixel stores. Cases retain the preceding color domain and add
empty registries, adjacent/overlapping ranges, first-match reversal, stored-1,
signed endpoint overflow and aliased output. Y records expose classifier returns
in addition to the caller's colors. The oracle executes original instructions
unchanged and checks the whole guest arenas, allowed writes, immutable code/
constants/type/resource inputs, caller stack and saved registers. The diagnostic
call's format address and full49-byte copied name argument are checked.

Resource records, image-type/index associations and initial type/list/image/TMP/
brightness inputs in this differential fixture are authored. Missing logging,
file/cache/CRT services and TMP installation retain their supplied boundaries.
They are not execution of original Day1 startup. No whole-frame claim follows.

## Actual asset and mutable-world bindings

`render/PreparedRadarAssets.hpp` binds Cell color asset services to the existing
PreparedTerrainMap owners. Overlay flags, image/color queries and classification
read the same OverlayTypeInputs. The demand getter uses retained Data/owned fields;
TMP type queries borrow canonical tileImages. Resource lookup reads the live
resourceTypes vector, with explicit missing diagnostic service. It creates no
additional Cell/type registry or simulation.

The primary-only tile association, variant0 for variants1, clear tile, empty
resident query and brightness remain supplied policies in the checks. Alternate
startup/variants, missing lazy TMP installation and nonzero CellAnim/fallback
animation owners refuse. Nonlazy overlay startup is explicit; no guessed image
initialization loop or original cache implementation was added. Asset callbacks
borrow map/store lifetimes synchronously. The Boot Camp prepared backing is shared
across clones: do not add mutable image/type startup to a discarded clone or imply
source isolation for such future writes without an appropriate asset owner.

Actual Day1 checks use retained SROCK01.TEM and LOBRDG10.TEM headers and actual ore
Cells. Overlay127 TIB2_01 maps to stored resource index2/imageIndex127. Mutating the
canonical resource flag changes both the flag query and classifier; an empty
resource vector logs once and retains the original zero-result color. Unbound
animation identity refuses. An initial native test incorrectly expected index0;
read-only source/registry inspection established index2 and the assertion was
repaired. A1's failed attempt remains private; no original/native mismatch occurred.

A separate check binds the **actual BootCampWalkWorld prepared assets and mutable
map Cell**, verifies it is distinct from the initial seed, queries its resource
color, removes its overlay, observes TMP color through the same services, restores
it and observes resource color again. The seed remains unchanged and the sampled
Walk/mission/visibility/map state returns exactly to its original snapshot. This
is native integration/lifetime evidence, separate from original fixture answers.
No live application producer or SDL tick calls the new query.

## Verification and costs

Normal/sanitizer/inspection-uncached replays each select explicit original-answer
reuse and report958 hits/zero misses; current native execution always runs.
Earlier398 demand/color/terrain/projection answers replay unchanged on both
rebuilt profiles. Twenty-one focused Python tests and12 CTests/profile pass.
Actual Day1 normal/sanitizer owner checks pass, including all eight GI directions
and clone/mission isolation. Final costs/hashes are in
`private/boot-camp-20261020/radar-resource-receipt-a1.json`.
Fresh original/native:13.490/.059s. Normal/sanitizer/uncached drivers:
.524/1.279/2.533s. Separate inspection/edit/configure/build/repair/total task costs
are unavailable. Earlier normal/sanitizer owner phase costs3.566/41.121s retain
their scopes; A3 adds the actual mutable-world query and passes in4.173/36.920s.

App rebuilt. Its hash remains unchanged after the final relink; last actual SDL
acceptance is the GI-facing correction in `private/boot-camp-20261019-facing/`.
No new radar GUI/frame-fidelity claim follows. Only Apple Silicon macOS is tested;
local verification is not independent acceptance. Base RA2 and YR remain incomplete.

Next compose630A00 startup using aliased source/region, native backing and relevant
first-DSurface semantics, then production House/coverage/actor ownership and SDL.
Resolve animation ownership only where entered. Preserve explicit tile variant,
brightness, startup and cache boundaries. Do not call the tutorial transition done
from these internal rendering dependencies. No workers, Windows actions/transfers,
downloads, system/Xcode/DRM changes or new runtime executable-read boundary.

## Commands

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake --build build/native --target cell-radar-color-vectors radar-terrain-vectors boot-camp-walk-check redalert2-native --parallel 6
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_radar_resource_color test_overlay_startup test_overlay_image test_overlay_radar_color test_cell_radar_color test_radar_terrain test_radar_projection test_cell_resident_search
build/tools-env/bin/ctest --test-dir build/native -R '^(overlay-map-resource|overlay-startup|overlay-image|overlay-radar-color|cell-resident-search|cell-resident-kind6|cell-radar-color|radar-terrain|radar-projection|overlay-type-input|resource-type-input|map-overlay)-domain$' --output-on-failure
build/native/boot-camp-walk-check private/official-1006-probe
# Always select unused audit/report destinations. Only original answers are reused.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/NEW-RADAR-RESOURCE.audit.json tests/compare_radar_resource_color.py \
  --exe private/official-1006-probe/game.exe --native build/native/cell-radar-color-vectors \
  --terrain-native build/native/radar-terrain-vectors \
  --expectations private/boot-camp-20261020/radar-resource-fresh-a1/expected.json \
  --report private/NEW-RADAR-RESOURCE.json
```

Use existing `build/sanitize/` runners for sanitizer. Add `--uncached` before the
driver for inspection control while retaining explicit original reuse. Fresh
original generation uses a new `--output` instead of expectations/report and needs
research-only Unicorn JIT. Entry points: `./build.command`, `./test.command`,
`./run.command --boot-camp-walk`; this checkpoint adds no visible gameplay mode.
