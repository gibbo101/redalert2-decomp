# Supplied RA2 ramp shadow matrix initialization

October 15, 2026, after `fa9bb28`. The native `voxelRampShadowMatrices` helper
recovers all **21 final shadow matrices** for explicitly supplied axis/diagonal
tilt globals. It is not wired into Unit/Drive drawing or gameplay. The prepared
Unit-world current-ramp-zero guard remains required. Complete native base RA2
then Yuri's Revenge remain active; this is a focused recovery checkpoint.

## Identity and reference hypothesis

Exact supplied engine: 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Both private supplied copies retain this identity. Embedded 1.08, supplied 1.006
lineage and reported no-CD modifications remain separate provenance; pristine
authenticity is unverified. No Windows action/transfer or source/system change.

Consulted [REFERENCES.md](REFERENCES.md), pinned YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` `DriveLocomotionClass.h`,
`LocomotionClass.h`, `Matrix3D.h`, and recomp snapshot
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` `docs/voxels.md` Shadows / MIT
LICENSE. Hypothesis: the complete initializer builds a separate ramp shadow table
from angle globals; the Drive shadow getter must not use a flat identity for
nonzero ramp. Exact base instructions/execution determine the result. YR names
remain leads; recomp is not an oracle. Its MIT grant excludes generated/lifted
code and the stale The Movies scope text remains recorded. No YRpp license file
was found. No upstream/header/generated/lifted code or extracted table was copied;
existing notices are unchanged.

## Recovered projection and remaining boundary

[verify_voxel_ramp_shadow.py](../tools/verify_voxel_ramp_shadow.py) pins **14
complete ranges / 1,357 instructions**, including initializer
`0x718060..0x718D3A`, matrix constructors/rotations/point application, quaternion
children, table sqrt/trig and FTOL. All 14 roots execute unchanged in this profile;
there are no replacement numerical children or instruction patches. Block execution
must stay within inspected code. Caller return/ESP/registers/stack, angle/code
inputs and allowed global writes are guarded.

The original full initializer was already inspected and used as fixture setup in
[SHADOW_COLOR_1006.md](SHADOW_COLOR_1006.md). That earlier proof compared flat
outputs; it did not compare every nonflat table. This checkpoint supplies nonzero
angle globals and compares **only the final shadow table** at `0xAF8608`.
It does not promote the other original initializer outputs to native parity.

The initializer converts two supplied doubles to float32 under toward-zero:
axis tilt from `0xAF77A0`, diagonal tilt from `0xAF7398`. Each sloped matrix starts
at identity and rotates Z(direction), X(tilt), then Z(-direction), using original
table trig and a float32 store after each component. Preserve the decimal angle
literals: recomputing 3/6 quarter-turns from the smaller float differs by a bit.
Entry 0 and entries 17..20 are explicitly initialized to identity. Entries 1..4
use axis tilt/cardinal directions; 5..8 and 9..12 use the same diagonal tilt/
diagonal directions; 13..16 use axis tilt/diagonal directions. These duplicate
ranges follow actual base instructions rather than an inferred geometric model.

Native returns a value array. Original table write addresses/values are audited,
but native/original ordered global stores and interleaved other initialization
are not compared. The angle globals, zero camera/light globals and starting
output storage are supplied; their startup/height association is **not recovered**.
Finite angles within [-3,3] bound this profile; nonfinite/out-of-domain and malformed
fixture refusals are native safety guards, not original malformed-input parity.
No runtime executable-read boundary or prepared-data format changes.

## Verification and reproduction

**44 fresh complete original initializer calls** supply expectations for **176
native results** under four incoming FP modes. All 252 matrix dwords match per
result, including signed zeros, tiny/negative angles, float32 rounding boundaries,
zero/nonzero pairs and deterministic finite pairs. Native restores every incoming
FP mode. There are **11,088 audited shadow-table dword stores**, exactly 252
distinct destinations per original call, and seven separate native safety refusals.
Nested root counts in the receipt are execution counts, not extra comparisons.
Normal and ASan/UBSan replays use the same source/input/expectation identities.
Receipts: `private/map-depth-1006/ramp-shadow-v3/`.

Fresh CLI/original/native times: **2.958/2.417/0.023 s**; normal replay
CLI/native **0.648/0.010 s**, sanitizer **1.145/0.254 s**. Both builds,
670 Python tests, 47 normal / 46 sanitizer CTests and source/diff/link audits pass.
All 74 prior unchanged replay sets remain current; closing coverage is 76 sets /
3,080 inventory source entries. [HANDOFF.md](HANDOFF.md) records accounting,
retained SDL application identity and the remaining integration boundaries.

Three earlier original-only probes found the table's full 21-slot initialization.
The first diagnostic allowlist stopped at table-sqrt's early return; the guard
rejected the later branch, and the complete already-inspected 110-byte sqrt range
was used. A subsequent assertion incorrectly expected slots 17..20 to remain
untouched; inspection/execution found the four later identity calls. Those failed
probes are retained as diagnostics, not accepted comparison receipts. The initial
successful native profile was regenerated after tightening incomplete/trailing
fixture refusals and then adding native reader sources to its identity inventory;
old receipts are historical and were not relabeled.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

# Fresh execution requires authorized host JIT access and a new private output.
build/tools-env/bin/python tests/compare_voxel_ramp_shadow.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/ramp-shadow-new
build/tools-env/bin/python tests/compare_voxel_ramp_shadow.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/ramp-shadow-v3/expected.json \
  --report private/map-depth-1006/ramp-shadow-v3/replay-new.json
# Add --native build/sanitize/voxel-ramp-shadow-vectors for sanitizer replay.

# Existing playable baseline; the new helper remains unwired.
./run.command --crossing-light-demo
```

Only Apple Silicon macOS is tested. The existing SDL capture verifies the unchanged
application binary; no original frame or new runtime ramp integration is claimed.
Next recover angle initialization and complete current-ramp Drive pose/key/relative-
height associations, then join established shadow consumers and prepared map before
runtime promotion. Actual SDL level crossing and parked cliff remain acceptance
scenarios. Full startup/ownership/pathfinding/scheduling/frame parity remain open.
