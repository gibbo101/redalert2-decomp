# Stock ramp and Cell numeric geometry

October 15, 2026, after `577b407`. The new `stockRampGeometry` helper derives
the stock level height and axis/diagonal tilts, then feeds the previously verified
21-matrix shadow initializer. Two distinct original numeric chains agree with
the native values. This is a recovery checkpoint; the helper is unwired and the
prepared Unit-world current-ramp-zero guard remains required. Complete native
base RA2 then Yuri's Revenge remain active and incomplete.

## Identity and references

Both supplied private engines remain 4,485,392 bytes / SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 lineage and reported no-CD modifications remain
distinct provenance; pristine authenticity is unverified. The approved Windows
copy already exists. No new Windows/transfer/source-install/system action.

Consulted [REFERENCES.md](REFERENCES.md), the pinned YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` `Unsorted.h`, `MapClass.h`,
`CellClass.h`, `DriveLocomotionClass.h` and `Matrix3D.h` naming leads, and recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` `docs/voxels.md` Shadows / MIT
LICENSE. Hypothesis: stock geometry produces the two shadow tilt globals and the
Cell floor's level-height input; neither host trig nor an assumed height constant
establishes that association. Exact base instructions/execution decide the result.
YR declarations are leads and recomp is not an oracle. The prior license boundaries
remain: no YRpp license file found; recomp's MIT excludes generated/lifted game
code, and its stale The Movies text is recorded. No upstream/header/generated/
lifted code or extracted table was incorporated; no THIRD_PARTY.md change.

## Recovered numeric scope

[verify_ramp_geometry.py](../tools/verify_ramp_geometry.py) pins **41 inspected
regions / 1,788 instructions**: twenty complete numeric roots, the complete tangent
and arctangent leaves, the prior shadow initializer/numerical children and five
bounded CRT regions. These are not 41 newly recovered general routines. Only
the positive finite **256 squared** path through the original CRT power code
executes; unexpected error/alternate dispatch outside the inspected regions is
refused. The native implementation uses the exact product 256*256 for that fixed
input. It does not recover or substitute a general `pow` implementation.

The ten shadow roots start at `0x717CE0`, `0x717D10`, `0x717D30`, `0x717D50`,
`0x717D70`, `0x717D90`, `0x717DB0`, `0x717DF0`, `0x717E20`, `0x717E50`.
The distinct ten Cell roots start at `0x470490`, `0x4704C0`, `0x4704E0`,
`0x470500`, `0x470520`, `0x470540`, `0x470560`, `0x4705A0`, `0x4705D0`,
`0x470600`. The two sets write separate globals, not aliases. Both derive:

| Final value | Result |
| --- | --- |
| Table-sqrt diagonal | 362.0386657714844 |
| Diagonal / 60 | 6.033977762858073 |
| Reciprocal of that stored double | 0.16572815467691362 |
| Level height | **104** |
| Diagonal tilt | 0.3723885416984558 |
| Axis tilt | 0.5116347670555115 |
| Four-times height with original +0.5/FTOL | 416 |

The three 45/60/90-degree products are also compared as exact double bits.
Preserve stored doubles between roots, table sqrt's float32 result, table tangent
of the stored 90-minus-60 angle, ordered tangent*diagonal*0.5 and original FTOL
truncation. The diagonal tilt uses height/256; the axis tilt uses twice-height /
stored diagonal. These are the verified stock inputs; native general height/overflow
behavior is not claimed by the fixed initializer projection.

The shadow chain stores its height at `0xAF89F8`, diagonal tilt at `0xAF7398`
and axis tilt at `0xAF77A0`. The separate Cell chain stores height at `0x850C40`.
Inspection of the already verified Cell floor root `0x4706C0` confirms it reads
`0x850C40` for lazy height and signed level multiplication. This checkpoint
executes both numeric chains, but does **not** newly join a floor query to them
or establish actor placement/update. Earlier floor/map proofs retain their supplied
initialization boundaries until that joined execution is verified.

Tangent `0x4BA520` multiplies the full double by its original scale, truncates
then normalizes a signed remainder into 4096 table bins. Arctangent `0x4BA5B0`
stores a float32 sign copy while retaining the full double for division by the
existing direction table's slope step. It takes the absolute truncated index,
uses entries 0..4096 and saturates higher indexes to the stored float half-pi.
Only a **negative stored float** negates the result; negative zero and a negative
double that underflows to float zero do not trigger negation. Do not use host
`tan`, `atan`, sine/cosine division or a signbit shortcut.

## Private data and evidence

[prepare_ramp_geometry_data.py](../tools/prepare_ramp_geometry_data.py) accepts
only this exact patched source. It extracts the 4096 floats at `0x80FDE4` and
double tangent scale at `0x7A0F80`, with no instruction execution. The separate
16,432-byte artifact is stored under ignored `private/derived/ra2-1006/` and
fingerprinted `2168b23a8a6b2e86a2c1fa6d2447aceef39c8f5c2d8fdf42537ae4dbd76b2b6b`.
`readRampGeometryData` validates the full artifact and optional expected source.
Existing render/raster/direction formats and their receipts remain unchanged.
There is no additional runtime GAME.EXE read, and no data table is tracked.

Receipts `private/map-depth-1006/ramp-geometry-v1/` contain **16,914 fresh
native results**: four differently seeded original stock chain pairs / sixteen
native stock results, plus **16,514 original table-leaf calls**. The ordinary
leaf samples cover every bin with both signs; selected truncation/remainder/
saturation/float-underflow boundaries run under all four native incoming FP
modes. Every native call restores its incoming mode. Ordinary bin samples cycle
the four modes. The original entry profile is supplied 53-bit/toward-zero.
Four repeated stock executions test output initialization, not four distinct
stock geometries. All 20 numeric global values and all 252 shadow matrix dwords
are compared per stock result.

The original harness executes unchanged instructions, including the actual fixed
CRT power, sqrt/tan/atan and complete matrix initializer. It checks code/block
bounds, return/ESP/callee-saved registers/caller stack, immutable code/constants/
tables and permitted writes. **16,598 root/leaf calls** are audited; 80 numeric
global stores and 1,008 matrix dword stores have exact destinations/values checked.
Original numerical children are not replaced. Table leaves use a separate cdecl
audit: arguments remain on the caller stack and arctangent overwrites its first
argument dword. Return values are read from the x87 physical register and consumed
by the harness, without synthetic guest code. CRT flag zero and initial output
storage remain explicit supplied inputs. Full memory-read order, native ordered
global stores, actual startup invocation/order/CRT initialization, general power,
Drive pose/key, actor ownership and whole-frame parity remain outside the claim.

Normal and ASan/UBSan replays pass with identical source/input/expectation identities.
Fifteen malformed/out-of-domain native commands are separately refused. Reader
size/hash and evidence/source/input/engine guards have regression tests. Such
refusals are native safety behavior, not original malformed-input parity.

Fresh CLI/original/native times: **4.073/3.214/0.058 s**. The first original-only
diagnostic succeeded. A later pilot correctly rejected the test harness's
callee-clean expectation for the cdecl leaves; the corrected 17-result pilot
passed. An inspection check rejected a trailing NOP in the arctangent range;
the range now ends at its actual return. Neither failure supplied accepted
expectations or changed original code. Closing build/test/accounting and retained
unchanged SDL evidence are in [HANDOFF.md](HANDOFF.md).

## Reproduce and continue

```sh
build/tools-env/bin/python tools/prepare_ramp_geometry_data.py \
  --exe private/official-1006-probe/game.exe
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

# Fresh original execution needs authorized Mac host JIT access and a new output.
build/tools-env/bin/python tests/compare_ramp_geometry.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/ramp-geometry-new
build/tools-env/bin/python tests/compare_ramp_geometry.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/ramp-geometry-v1/expected.json \
  --report private/map-depth-1006/ramp-geometry-v1/replay-new.json
# Add --native build/sanitize/ramp-geometry-vectors for sanitizer replay.

# Existing playable baseline; this helper is not wired into gameplay.
./run.command --crossing-light-demo
```

Next recover the complete current-ramp Drive pose/key wrapper, join actual
floor-relative height and established shadow consumers with prepared Cells, then
resolve floor-to-actor placement/update before runtime depth promotion. Actual
SDL level crossing and parked `(51,72)`, elevation 4 remain required scenarios.
Only Apple Silicon macOS is tested. This local checkpoint is not independent
acceptance, a new playable capability or complete startup/frame fidelity.
