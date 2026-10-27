# Prepared map Cells through complete lit Unit drawing

October 15, 2026, after `4453ac4`. **129 fresh original/native results / 111
complete lit draws** match, followed by normal and ASan/UBSan replays. This is a
locally verified recovery checkpoint, not independent acceptance or a new playable
terrain-depth milestone. Full native base RA2 then Yuri's Revenge remain active.

This profile joins the finalized resident map to the complete healthy Track Unit
lit draw. `PreparedUnitDepth` supplies stable projected Cell views and the actual
ordinary Unit base kernel to `drawHealthyUnitVoxelToWorld`. Foot predicates and
factors still run at each staging/final-copy call; no precomputed final-depth
callback replaces them. The actual current Cell must have ramp zero for the existing flat Drive shadow
consumer; neighboring ramps remain supported. The helper is not wired into gameplay.

The original harness prepares and finalizes the map in the **same guest** used
for Unit/cache/raster/staging/pool/final RGB565 drawing. `AttachedMap` installs
host bookkeeping and disjoint arenas on that guest; it creates no second guest
and copies no prepared records. Historical floor/Foot receipts supply scenario
inputs only. Their final outputs are not imported as new behavior proof. Earlier
synthetic-map Unit/world and standalone base/Foot scopes remain intact.

## Exact engine and boundaries

The supplied base engine is 4,485,392 bytes, SHA-256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Both private supplied copies have that identity. Embedded 1.08, supplied 1.006
patch lineage and reported no-CD modifications remain separate provenance;
pristine authenticity is unverified. No new Windows action or transfer is needed.

The existing complete Unit/world inspection and prepared Foot/map inspection
bound the joined chain. Coordinate lookup `0x548000..0x548068` is additionally
inspected through its complete return. It divides full signed X/Y by 256 toward
zero, combines the index with low-dword wrapping, compares against supplied map
`+0x13C`, and returns a resident Cell or the shared fallback. Only a miss stores
word coordinates in that fallback. Do not substitute per-axis bounds or truncate
to words before combining the index. The CellStruct lookup remains distinct.
`mapCoordinateCell` implements this behavior; oversized native table counts and
absent fallback storage are safety refusals, not original malformed-input parity.

Original dimension `0x52B690` executes on the prepared TMP/type registry; the
old world fixture's zero-dimension service is bypassed. Current Cells, neighbors,
overlay rock flags, tile/subtile images, signed levels and flags remain shared.
Original preflight requires a resident current Cell. The caller supplies that
association to the native binding, whose separate preflight checks its ramp before
drawing. The binding refuses nonflat current Cells and coordinates outside the
ordinary positive map domain; this guard is not an original malformed-input
behavior claim and is excluded from the original draw query digest.
Record identity keys the projected views, so absent coordinates reuse one mutable
fallback view. Requested absent TMP images remain refused: nested caller scratch
initialization is not established. The binding borrows its input/service records;
they must outlive it and every callback returned by `world()`.

Initial map/type/terrain/geometry/resource/global associations retain the earlier
preparation notes' boundaries. Actor coordinates, absolute Z, settled Facing,
stock factors 8/13/10/0, height scale/default tile, healthy Track metadata, camera,
house/contact records, palette rows and destination color/depth/alpha planes are
supplied. **Relative height remains the explicit zero service.** Supplied actor
Z is level times 104, not recovered placement/update or a guarantee of zero
relative height on a ramp. Shadow requests/stencils are observed; this profile
does not draw original shadow pixels. It does not establish actor startup,
heap/cache/converter ownership, full read order, runtime or whole-frame parity.

## Nonflat shadow dependency found during the join

The first full attempt completed original generation but failed comparison at
command 143, the first synthetic map's nonflat actor. The first difference was
in the shadow request after the lit surface: the existing native helper assumes
flat Drive shadow inputs. Inspection of actual `0x53D0D0` and `0x718D60` confirms
that Cell `+0x11C` selects matrix `0xAF8608 + 48*ramp` and participates in key
packing. Only matrix zero is initialized by this fixture. Zero nonflat matrices
in that failed run are **missing fixture initialization**, not original initialized
ramp matrices and not evidence of the original game's appearance. No receipt was
accepted or relabeled from that attempt.

The accepted profile enforces current ramp zero on the actual finalized
Cell. Synthetic scenarios constrain the supplied current tile's ramp metadata
**before** both original and native map recalculation; they never overwrite a
finalized Cell to neutralize it. Other tile/neighbor ramps, flags, levels,
overlays and dimensions still feed the actual depth path. Original ramp-matrix
initialization/pose and nonflat actor shadow integration remain separate work.
The normal and sanitizer domain guard checks include refusal of nonflat current
Cells. Do not remove that guard or apply flat shadow identity to a ramp.

Subsequent [VOXEL_RAMP_SHADOW_1006.md](VOXEL_RAMP_SHADOW_1006.md) recovers all
21 initialized shadow matrices for supplied tilt globals. The complete initializer
was already inspected/executed as earlier shadow fixture setup; its nonflat table
outputs now have differential proof. Angle startup and actual Drive pose/key/
relative-height integration remain open, so the current-ramp-zero guard stays.

## Coordinate lookup evidence

`tests/compare_map_coordinate_cell.py` independently executes the complete
104-byte / 36-instruction coordinate lookup: **2,445 fresh queries in five
sequences**, with supplied table counts 0/1/512/65536/262144. Signed coordinate
extremes, negative aliases, full-versus-word index differences, resident hits,
missing slots, repeated fallback changes and arbitrary unused Z values match.
Every result includes record identity, returned position, retained fallback
position and the number of original fallback stores. Table/Cell/input/caller and
nonselected fallback bytes are guarded. Initial sparse table/storage remains
supplied; malformed pointers and startup are outside the claim.

## Verification and reproduction

Main receipts: `private/map-depth-1006/prepared-unit-world-v2/`. Nine actual map
finalizations and nine cache resets accompany 111 complete draws: 60 cold owned
cliff/crossing draws, 27 warm missing-model/changed-brightness/contact draws and
24 synthetic draws. Original draw-phase calls include **480 complete Foot depth /
Unit base**, 354 gradient, **1,103 TMP dimensions**, 14,475 CellStruct lookups and
222 full-coordinate lookups. There are 231 audited world roots and nine map roots.
Both final-copy gradients execute: 63 gradient-zero and 111 gradient-two surfaces;
3,984 actual RGB565 span entries execute. The parent includes 40,941 actual
resource/Cell/passability/permission/light calls each and 285 floor queries.
These are nested execution counts, not additional independent comparisons.

The suite freshly finalizes three owned-map cliff modes, including parked
`(51,72)`, elevation 4 and crossing `(86..93,101)`, plus six synthetic maps.
The parked cliff receives four cardinal body headings; crossing positions
receive opposing headings, and the synthetic maps receive four headings.
Draws cover body/turret directions, cold/warm indexes, missing models on warm
hits, changed brightness, bypass, contact splitting, camera and clipping.
Compare parent Cell/buffer/cursor/lazy-floor signatures; then surface arguments,
depth/gradient, complete staging and color/depth/alpha hashes, dirty cleanup,
compressed pool/index state and ordered map/TMP query/fallback-store digests.
Source/engine/input/inspection/runner/expectation identities guard fresh and replay
receipts. Caller return/ESP/registers/stack, immutable inputs and permitted writes
are audited. Original instructions are unchanged.

The native fixture uses bulk byte allocation and indexed little-endian stores
for trace hashing, preserving the digest byte order. The earlier measured
per-byte sanitizer trace overhead is test serialization, not game performance;
no cache infrastructure is introduced and old runners remain unchanged.

Fresh complete CLI/original/native times are **699.784/656.355/0.272 s**;
normal/sanitizer replay CLIs **41.976/44.149 s**, native execution
**0.203/2.561 s**. Builds, 663 Python tests, 47 normal / 46 sanitizer CTests,
source/diff/link audits and actual unchanged SDL crossing pass. Closing coverage
is 74 replay sets / 3,038 source entries, including 70 retained unchanged sets.
The first 979.598-second nonflat attempt remains failed evidence; the corrected
15-command pilot takes 73.641 s. [HANDOFF.md](HANDOFF.md) records other attempts,
timings, runtime capture and boundaries. These harness timings are not game FPS.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

# Fresh output must be a new private destination. Original execution needs
# the authorized Mac host JIT context; no original executable runs in gameplay.
build/tools-env/bin/python tests/compare_prepared_unit_world.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/prepared-unit-world-new
build/tools-env/bin/python tests/compare_prepared_unit_world.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/prepared-unit-world-v2/expected.json \
  --report private/map-depth-1006/prepared-unit-world-v2/replay-new.json
build/tools-env/bin/python tests/compare_prepared_unit_world.py \
  --exe private/official-1006-probe/game.exe \
  --native build/sanitize/prepared-unit-world-vectors \
  --expectations private/map-depth-1006/prepared-unit-world-v2/expected.json \
  --report private/map-depth-1006/prepared-unit-world-v2/sanitize-new.json

# The small standalone coordinate suite also has fresh/replay modes.
build/tools-env/bin/python tests/compare_map_coordinate_cell.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/coordinate-cell-v1/expected.json \
  --report private/map-depth-1006/coordinate-cell-v1/replay-new.json
# Add --native build/sanitize/map-coordinate-cell-vectors for sanitizer replay.

# Existing playable baseline; the new binding is not enabled here.
./run.command --crossing-light-demo
```

Next recover/initialize the required ramp shadow matrices, join the established
shadow consumers and actual floor-relative height,
resolve floor-to-actor placement/update associations and required initial/type/
global inputs, then promote runtime depth. Actual SDL level crossing and parked
cliff remain acceptance scenarios before that promotion. Screenshots alone do
not establish original fidelity. Only Apple Silicon macOS is tested. Complete
base RA2 and then Yuri's Revenge remain active and incomplete.

Pinned YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88`
`MapClass.h`/`CellClass.h`/`FootClass.h` declarations were naming leads only;
no license file was found, and no code/headers were incorporated. Their Coord
lookup forwarding does not replace the actual base binary's full signed index.
Pinned recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439`
`docs/voxels.md` and MIT LICENSE supply surrounding staging/final-copy context,
not an original-behavior oracle. No upstream/generated/lifted code, extracted
table or proprietary material is tracked. Runtime executable reads are unchanged.
