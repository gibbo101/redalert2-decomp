# Supplied RA2 1.006 loaded TMP preparation

October 15, 2026, after `764e1ca`. This is an assets-only prerequisite of the
terrain-aware Foot/world crossing and cliff capability. It leaves runtime neutral
tile/contact fields in place; it does not establish complete theater or map loading.

## Identity and references

The executed engine is `private/official-1006-probe/game.exe`, 4,485,392 bytes,
SHA256 `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`,
rehashed before this work. The approved private Windows copy has the same identity
at the preceding checkpoint. Embedded 1.08, supplied 1.006 lineage and reported
no-CD modifications remain separate provenance; pristine authenticity is unverified.
No new Windows action or transfer was needed. The native application never executes
this file, and does not require mounted media or a Windows launcher.

Consulted [REFERENCES.md](REFERENCES.md), pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` `docs/voxels.md`/LICENSE, and YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` `MapClass.h` and
`IsometricTileTypeClass.h`. Hypothesis: loaded TMP dimensions, relocated sub-tile
references and prepared color ramps supply the resident metadata consumers already
verified below Cell recalculation. Recomp supplies no verified base tile-loader
algorithm; YR declarations are naming leads only. Exact base instructions and
execution decide the behavior. No upstream/header/generated/lifted code was
incorporated; no new THIRD_PARTY entry is required.

## Executed scope

`assets/TileImagePreparation.*` implements ordinary local TMP reference/metadata
preparation and its 13-pair color ramps, separately from `readTmp` pixel/depth
decoding. **Nine complete ranges / 593 instructions** are pinned:

| Actual original root | Scope |
| --- | --- |
| `0x52B560` | Complete lazy file load, reference relocation and color preparation |
| `0x52E3D0` | Complete color-vector rebuild |
| `0x63CC80`, `0x63CDF0`, `0x77F110` | Actual interpolation, scaling and FTOL |
| `0x5293D0` | Actual GetImage wrapper, null image and lazy loading enabled |
| `0x529300`, `0x52B690`, `0x52B6F0` | Actual land, dimension and ramp consumers |

The original roots execute unchanged. File construction/size/read/destruction,
successful heap allocation/free and sufficient vector storage/clear are supplied
services, with checked caller sites, receivers and arguments. Existing old-image
and old-color-buffer cleanup order is asserted as an original-only observation;
native portable storage does not reproduce original heap ownership.

The supported domain has signed dimensions 0..255 and at most 16,384 sub-tiles,
ordinary file-relative nonzero references and land-table indices below 16. Original
32-bit absolute references normalize to native file-relative offsets. Zero
references remain null. Preserve full image width/height and byte-derived type
columns/rows, land/ramp bytes, extra-height flag, Y and ExtraY. No host pointer is
stored in a portable asset record.

Each present sub-tile has **26 RGB565 words**, alternating two colors for steps
0..12. Preserve original binary32 1.4 scaling, per-channel truncation/clamping,
binary64 1/12 multiplication followed by a required binary32 interpolation store,
and x86 masked packing-shift counts. Scoped original rounding restores the caller's
FP mode on success and exception. Strict FP compilation is scoped to this new
source. It does not change other recovered kernels' compilation.

Malformed headers, table overlap, truncated references and unsupported dimensions
are native safety refusals, not original malformed-input parity. Broader relative/
absolute-pointer mixtures, allocation failure/growth, archive/file ownership,
theater filename/type/alternate association, usage/variant selection, map loading,
runtime integration and whole-frame fidelity remain outside the claim.

## Evidence and commands

**390 fresh original/native results**: 384 deterministic synthetic cases and six
supplied-image cases (direct lazy root and actual GetImage parent for each of
`clear01.tem`, `cliff01.tem`, `slope01.tem`). Cases cover null/duplicate references,
zero dimensions, signed/wrapped height metadata, color/clamping boundaries,
masked packing shifts, supplied land tables and prior buffer cleanup. They compare
normalized references, selected image/type metadata, every ramp word and the actual
metadata consumers' outputs. Normal and ASan/UBSan replays pass against the same
identity-checked original expectations.

Current receipts: `private/map-depth-1006/tile-image-v1/{expected,report}.json`,
`native-replay.json`, `sanitize-replay.json`. Source/inspection/owned-input identities
are checked before and after runs. Caller return/ESP/stack/registers, immutable type
bytes/headers/globals, actual allocation bounds, vector capacity tails and image
bytes after reference normalization are guarded. Counts: 4,485 audited roots,
863,910 guest stores, 4,467 supplied service calls, 390 lazy/builder entries each,
28,262 interpolation, 2,174 scale, 91,308 FTOL, 4,290 GetImage, and 1,365 entries
per metadata consumer. No all-read/write-order or complete ownership claim follows.

```sh
./build.command
build/tools-env/bin/ctest --test-dir build/native --output-on-failure
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'

# Fresh original execution requires the authorized Mac host JIT context.
# Choose an unused private output directory.
build/tools-env/bin/python tests/compare_tile_image.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/tile-image-new

# Replays do not execute original instructions.
build/tools-env/bin/python tests/compare_tile_image.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/tile-image-v1/expected.json \
  --report private/map-depth-1006/tile-image-v1/replay-new.json
# Add --native build/sanitize/tile-image-vectors for sanitizer replay.
```

Timing and final checks are recorded in the current [handoff](HANDOFF.md).
This is a locally verified prerequisite, not independent acceptance or a playable
delivery. No new SDL run is claimed for unwired assets work. Complete theater
loaded-file/type/variant association and broader map initialization still precede
prepared Cell to Foot/world integration, actual SDL level crossing and parked
cliff `(51,72)`, elevation 4. Only Apple Silicon macOS is tested. Full base RA2,
then YR, remains active and incomplete.
