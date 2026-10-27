# Radar marker coordinates and dirty-point production

The next layer is now joined in [actor marker buckets](RADAR_MARKER_BUCKETS_1006.md):
complete631910/631AF0 use the same dirty queue and actual-owner drawing buckets.
Complete actor footprint/placement callers and production scheduling remain open.

`RadarMarkerPlacement.hpp` recovers complete631BA0 and632620 on the supplied
base executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. The executable was fingerprinted before
address inspection. No public/generated/lifted implementation was used.

These helpers support the original actor-marker producer, a dependency of radar
refresh below the sight/discovery work needed for Boot Camp Objective1. They do
not themselves discover a structure or advance a lesson. Ordinary Objective1,
base RA2 and YR remain incomplete.

## Recovered behavior

631BA0 reads both world-coordinate words before writing either output word,
allowing input/output aliasing. Its two integer expressions wrap before conversion:
`(origin148C << 8) - y + x` and `y - (origin1494 << 8) + x`. Each multiplies by
float32 scale1484, then1/256, under the original53-bit/toward-zero profile and
uses the actual FTOL low-dword behavior. It does not subtract height. A nonzero
low argument byte enables sequential lower/upper clamps against14A0/14A4; zero
dimensions produce-1 after the upper clamp. This is distinct from the inverse
pixel-to-Cell projection in `SurfaceRadarPixel.hpp`.

632620 rejects negative/out-of-surface coordinates in original query order:
x sign, live first width7C, y sign, live first height80, then another live first
width7C. Coordinates remain late reads after callbacks. It computes the wrapped
linear bitmap index, uses arithmetic shift for the byte and returns immediately
if the bit is already set. Otherwise it stores the bit **before** attempting to
append to Map1258's point vector. Full vectors grow only if owned or capacity0,
and only for positive growth. Complete stock5B1B00, including its capacity-tail
copy, valid-byte stores, count clamp and null-allocation behavior, reuses the
existing `RadarShapeVector` kernel. Count increments before x/y stores.

Failed/disabled growth still sets14D5=1 and leaves the bit set. A repeated request
therefore does not retry allocation. No extra capacity test, bit rollback or
convenient retry is introduced. The clear child is pinned as a resize dependency;
the current queue corpus does not enter a zero-capacity resize request.

`RadarStorage::queueDirtyPoint` explicitly borrows its actual first surface and
mark bitmap, with one owned1258 vector and14D5 byte. Native allocation and initial
empty vector/zero dirty flag are supplied platform/startup boundaries. Queue
consumption, constructor fidelity and automatic scheduling remain unjoined.
The API does not insert actor buckets, draw pixels or create a frame callback.

## Evidence and limits

271 sequences match unmodified original execution:188 complete coordinate roots
and310 complete dirty roots. Coverage includes aliases, fractional/negative/zero/
nonfinite scales, wrapped integer extremes, raw clamp bytes, degenerate sizes,
bounds short circuits, duplicate/unique requests, full/external/empty backing,
disabled/failed/successful growth, inactive capacity tails, and late surface/point
mutations after each getter. Allocation/free are supplied test services; getters,
resize and FTOL execute original code. Caller stack/return/callee-saved registers,
entered code spans, immutable inputs, allowed writes and the full arena are checked.
Comparisons retain ordered field/point/bitmap/dirty writes and full backing hashes.
This does not establish every possible input or native memory access width.

The actual Day1 owner check passes the actual GI coordinates through631BA0 using
the existing radar scale and explicit full-map geometry. It then queues that
point on the existing radar storage, checks its shared bitmap, duplicate
suppression and growth retaining earlier entries, and verifies unchanged terrain/
display/mission/Walk/visibility owners. The initial bitmap clear is a controlled
test setup; it is not recovery of a constructor or production invocation.

193 normal/192 ASan/UBSan CTests and17 focused Python tests pass. Both actual-map
owner profiles pass. Both rebuilt profiles replay271 new expectations and940
matching coverage/refresh expectations with zero misses; originals are reused,
never native pass/fail results. These retain separate proof scopes. New original
generation took.091s. Broad builds15.947/28.369s; CTest driver wall8.253/14.889s;
owner checks6.420/46.396s. Python body3.279s. Concurrent costs are not additive.
Configuration/exploration/edit/preflight/total task wall is unavailable. No
build/proof/test failure occurred. Exact source/binary hashes, costs and artifacts:
`private/boot-camp-20261020/marker-helpers-receipt-a1.json`.

Local verification is not independent acceptance. Only Apple Silicon macOS is
tested. No runtime executable reads, new dependency, Windows/download/system/
Xcode/DRM action, proprietary tracked content or source-installation write was
added. No SDL rerun was needed for these unscheduled helpers; the preceding GI
facing recheck remains a separate successful actual SDL observation.

## Next joined producer

Complete631910 insertion and631AF0 removal, stock16-byte vector resize/find and
CRT movement are now joined; see the newer actor-marker note above. Preserve
player prepend/other append order, repeated actor trailer, offscreen Building
rejection, clamped1A0/1A4 stores, duplicate bypass and failed-growth refresh.
Next recover the actual actor registration/footprint/placement callers on these
same owners before production scheduling.

Hash-checked static direct-call inspection finds631910 at451845/6D74E7 and631AF0
at4518A5/6D7517. Coordinate helper callers include42DE5A/6C487C/6D81AD/6D82E2.
These are inspected call sites, not recovered complete callers. Raw disassembly
and the call-site inventory remain private. Actor/type footprint production,
startup geometry/associations, queue draining and live sight scheduling must be
joined before production adoption. Do not turn these explicit calls into
arrival-based or synthetic objective progress.

## Reproduce

```sh
./build.command
./test.command
build/native/boot-camp-walk-check private/official-1006-probe - private/boot-camp-20261020/radar-shape-dimensions-a1.bin
build/sanitize/boot-camp-walk-check private/official-1006-probe - private/boot-camp-20261020/radar-shape-dimensions-a1.bin

# Explicit supported original-only reuse. Choose fresh report/audit names.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
 --audit private/marker-next.audit.json tests/compare_radar_marker_placement.py \
 --exe private/official-1006-probe/game.exe \
 --native build/native/radar-marker-placement-vectors \
 --expectations private/boot-camp-20261020/marker-helpers-fresh-a1/expected.json \
 --report private/marker-next.json
# Repeat with build/sanitize/radar-marker-placement-vectors and fresh paths.
PYTHONPATH=tools:tests build/tools-env/bin/python -m unittest tests/test_radar_marker_placement.py

# Existing player-facing checkpoint; this change adds no live radar.
./run.command --boot-camp-walk
```
