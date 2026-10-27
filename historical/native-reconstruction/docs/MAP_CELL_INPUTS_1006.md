# Supplied RA2 1.006 decoded map-cell inputs

October 15, 2026, after `2bb36af`. This is a verified prerequisite of the
map/tile-depth initialization delivery. It adds no playable capability and does
not replace the runtime's deliberately neutral Foot tile/contact fields.

## Identity and references

The supplied `private/official-1006-probe/game.exe` and approved private Windows
copy are 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 lineage and reported no-CD modifications remain
separate provenance facts; pristine authenticity is unverified. The native app
never executes this binary. No Windows action or transfer was needed here.

[REFERENCES.md](REFERENCES.md)'s pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439`, `docs/voxels.md` and LICENSE,
and YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88`, `CellClass.h`,
`MapClass.h`, `IsometricTileTypeClass.h` and GeneralDefinitions supply leads.
Hypothesis: original decoded map records and resident TMP metadata initialize
the inputs later consumed by Cell recalculation and Foot depth. Exact base
instructions decide field meanings and arithmetic. No reference/header/generated
or lifted game code was incorporated; THIRD_PARTY.md needs no new entry.

## Recovered boundary

`assets/MapCellInputs.*` implements the complete decoded IsoMapPack5 record loop,
the signed tile-index remap, selected Cell constructor fields, and resident TMP
land/ramp/dimension consumers. `verify_map_cell_inputs.py` checks nine complete
ranges / 326 instructions:

| Root | Scope |
| --- | --- |
| `0x54E1E0` | Decoded IsoMapPack5 record reader, through `ret 4` |
| `0x529550` | Signed threshold/ordered tile-index remap |
| `0x470F10`, `0x40FF10`, `0x40FFD0` | Complete Cell/Abstract constructors and null-scenario registration; selected field projection only |
| `0x5293D0` | Actual resident/null tile image getter |
| `0x529300`, `0x52B690`, `0x52B6F0` | Land, dimensions and ramp consumers |

The actual base IsometricTileType vtable is `0x7A51A8`; its image slot `+0x9C`
targets `0x5293D0`. RTTI/getter xrefs were inspected separately from YR headers.
The reader's original INI call at `0x49D818` identifies IsoMapPack5. This does
not verify the INI/decompression/stream constructor above that boundary.

Preserve signed `y*512+x` lookup and its coordinate aliases, missing-cell reads,
tile=65535 prewrite, ordered signed shift thresholds against the original index,
wrapped additions, duplicate records, separate stream terminator and constructor
invalid coordinates, and terminal fallback construction. The selected constructor
projection preserves flags `& 0xFF800000`; complete Cell construction is not
recovered by comparing those fields. TMP consumers preserve signed bytes,
sub-tile remainder, null image/missing sub-tile behavior and wrapped extra-height
subtraction. The land mapping is supplied at the boundary, not copied into source.

The original fixture executes these unchanged roots. Stream construction/link/
read/destruction at `0x53EFB0`/`0x69B050`/`0x53F050`/`0x53F010` are services.
Resident TMP pointer headers and map/cell storage are supplied; unexpected lazy
loading at `0x52B560` is refused. Caller return/ESP/callee-saved registers, stack,
allowed writes, immutable pointer/shift/type/image tables and unmodeled ordinary
cell bytes are audited. Ordered selected stores include explicit supplied stream
stores because Unicorn API writes do not invoke guest write hooks. No original
instructions are patched. Native malformed geometry/subscript/table/stream
refusals are safety guards, not original malformed-input parity.

## Evidence and commands

**537 fresh original/native results** pass, plus normal and ASan/UBSan replay:
64 selected constructor cases, 80 complete reader cases, 384 resident TMP cases,
eight supplied clear/cliff/slope sub-tiles, and one complete original-reader
sequence over all **13,515** supplied map records. Counts are 1,321 audited roots,
85,515 ordered selected stores, 70,536 supplied stream reads and 1,176 actual
TMP helper roots. Counts describe execution scope, not a fidelity percentage.

Receipts and source/input identities:
`private/map-depth-1006/cell-inputs-v1/{expected,report}.json`,
`native-replay.json`, `sanitize-replay.json`. The owned map is
`private/migration/supplied-ra2-1006/map-light/assets/mp03t4.map`; owned TMPs are
under that profile's `composition/assets/`. Existing native decoding supplies
the map fixture bytes. No original LZO/map decompression or TMP relocation parity
follows. Inputs and sources are fingerprinted before/after generation/replay.

```sh
./build.command
build/tools-env/bin/ctest --test-dir build/native --output-on-failure
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'

# New original execution: choose a fresh, unused private output directory.
build/tools-env/bin/python tests/compare_map_cell_inputs.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/cell-inputs-new

# Reuse identity-checked original expectations; these commands do not execute x86.
build/tools-env/bin/python tests/compare_map_cell_inputs.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/cell-inputs-v1/expected.json \
  --report private/map-depth-1006/cell-inputs-v1/replay-new.json
build/tools-env/bin/python tests/compare_map_cell_inputs.py \
  --exe private/official-1006-probe/game.exe \
  --native build/sanitize/map-cell-input-vectors \
  --expectations private/map-depth-1006/cell-inputs-v1/expected.json \
  --report private/map-depth-1006/cell-inputs-v1/sanitize-replay-new.json
```

Fresh driver/original/native: 3.019/2.586/0.057 s (3.17 s CLI). Normal replay:
0.99 s CLI / 0.043 s native; sanitizer: 1.53 s CLI / 0.587 s native. Final
sanitizer build: 16.39 s. Both builds, 388 Python tests, 18 normal / 17 sanitizer
CTests, source/diff/local-link audits pass. Private start/attempts/closing records
retain failed inspections, the stream-store pilot correction, sanitizer target
configuration retry and unavailable inherited elapsed measurements. No SDL run
was repeated for this assets-only prerequisite; the previous delivery's actual
SDL receipts remain separate. This is a local verified checkpoint, not independent
acceptance or a completed map-depth capability.

## Continue the same capability

Recover Cell recalculation `0x472540` and its ordinary loaded-tile children before
replacing neutral runtime Foot associations. Explicitly scope overlay, cliff,
tunnel/bridge, passability, animation and side effects. Retain existing joined
Unit/world receipts, then reproduce the level-ground crossing and parked cliff
cell (51,72), elevation 4, with actual SDL rendering/input checks. Source records,
tile/type construction, theater shift construction, actor/contact initialization,
heap ownership, dynamic map lifetime and whole-frame parity remain open. No
worker, evidence-cache infrastructure, source-install/system/Windows changes or
new transfer occurred. Full base RA2 then YR remains active and incomplete.
