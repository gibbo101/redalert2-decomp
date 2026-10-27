# Radar footprint shape initialization

Boot Camp Objective1's action37 House sight/radar refresh requires initialized
radar storage. `RadarShapeBuckets.hpp` recovers complete632700 plus its actual
stock5B16E0 Clear and5B1B00 Resize children (Resize's second argument0). It now
initializes22 owned point vectors through the existing RadarStorage finish seam.
These vectors at Map1274 are **not** the256 actor-mark buckets at1254. The service
remains explicit and unscheduled; this adds no SDL radar or objective transition.

## Recovered arithmetic and vector behavior

For each vector the initializer calls Clear first, then reads the corresponding
width/height from the two22-entry dimension tables. Dimension exactly1 computes
scale+.5 with minimum1; every other dimension computes dimension*scale+.5 with
minimum**2**. Both conversions execute the original signed-qword FTOL and retain
its low dword. The native code preserves53-bit/toward-zero arithmetic, live scale
reads after Clear, signed wrapped row/column arithmetic and ordered point stores.
No floor/round convenience function or different fixed-point model is substituted.

There are width+height-1 rows. The left/right extents change at the retained scaled
height/width, producing ordered points from left to right. A scaled2-by2 footprint
contains5 points. Append checks signed count/capacity, allocation ownership and
positive growth. Successful growth rereads the live count and backing, increments
count **before** storing X then Y. Failed growth skips that point and continues.
Host row/column/allocation/backing bounds refuse excessive/unsafe entered states;
no rollback or arbitrary original fault compatibility is claimed.

Complete Clear writes count0 first. A nonnull owned buffer is released and its
pointer cleared; an external buffer remains referenced. Ownership then clears and
capacity becomes0; valid is untouched. Resize with requested0 delegates to Clear.
For a nonzero request it sets valid0, allocates requested*8 wrapped bytes, then
sets valid1 even on failure. Success copies min(old capacity, requested capacity)
points, **including inactive capacity tails**, frees owned old backing, stores the
new pointer/capacity/ownership and finally clamps count down by signed comparison.
The original heap functions are supplied services; no heap allocator is recovered.

`NativeRadarShapeBuckets` owns the allocations for exactly those22 borrowed vector
records. Production allocation uses bounded zero-initialized native arrays; unused
allocation contents and constructor defaults remain supplied policy. RadarStorage
passes its actual scale1484 by reference and retains the resulting vectors. The
stock dimension data is caller supplied, never embedded in tracked code. No second
shape model, general-purpose container engine or runtime executable read is added.
Original Map constructor/destructor and complete startup/scheduling are not claimed.

## Exact original evidence and reuse

Supplied executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Inspection pins459-byte632700,42-byte
5B16E0,214-byte5B1B00 and61-byte77F110 plus stock vector virtuals and numeric/data
hashes. Constructor inspection identifies table7A6FA8 for the22 vectors. Extracted
width/height content remains private. Original instructions/vtables are unchanged;
authored dimension probes are explicitly supplied data before entry and immutable
during calls. Heap results/initial records remain supplied.

All260 original sequences match complete ordered vector/point stores, heap calls,
final records and every padded allocation digest. They execute102 complete632700
roots,2,310 Clears,13,130 Resizes and4,488 FTOL calls. Cases include stock private
dimensions, authored special-one/minimum-two probes, zero/subnormal/negative/NaN/
infinite scales, signed count extrema, raw ownership/valid bytes, external/null/
owned backing, allocation failure, zero/negative growth, capacity-tail copying,
count clamp and repeated initialization. Full4MiB guest arena, input code/data/
vtable hashes, entered instructions, permitted writes and caller ABI are guarded.

Canonical original-only generation:
`private/boot-camp-20261020/radar-shapes-fresh-a1/{expected,report}.json`.
Generation7.909s. Its original generation and all native output comparisons finished,
but A1's final native guard failed: it incorrectly expected4 rather than5 points
for minimum2-by2. Only the native assertion changed. A1's failed audit/stdout remain;
its completed original-only expectations are reused without relabeling that failed
native attempt. New normal/sanitizer/inspection-uncached replays each report260 hits,
zero misses and run current native comparisons/guards. Both rebuilt startup runners
also retain all8 earlier original sequences. No original matrix was regenerated.

An initial preflight assumed the nonspecial clamp constant was0; inspection found
2 and corrected the verifier/kernel before original generation. No false numeric
comparison was accepted. The first private export destination was rejected because
it was inside the source directory; no output was written there. The export was
then written to a separate ignored research directory. These are separate from
the completed original generation and native-only guard repair above.

## Actual Day1 storage and private data boundary

Research-only `extract_radar_shape_dimensions.py` fingerprints the executable and
exports176 bytes outside the source installation. Canonical private export:
`private/boot-camp-20261020/radar-shape-dimensions-a1.bin`, SHA256
`a6d13a225bbbb52f1178acf67175788d24784bc167317fed350c45ac76d6422e`.
The explicit test loader checks that exact size/hash. A tampered same-size file
refuses before asset loading. The application does not load this file or acquire
new executable reads. Future production callers must supply dimensions through
an approved asset/provenance association; this research path is not automatic setup.

With that explicit input, the actual mutable Day1 startup finish calls the recovered
initializer on the existing storage's live scale. All22 vectors have valid owned
backing. Reinitializing reproduces their complete ordered points and leaves device
pixels, projected terrain/RGB and sampled mission/Walk/visibility state unchanged.
Both normal/sanitizer owner checks pass in4.631/38.185s. Existing source overlay
edit/restore, image sharing, first-device copy/pixels, clones and eight GI journeys
remain covered. This is native integration, not original Day1 startup execution.

Full current builds pass (16.819/15.770s normal/sanitizer), as do192 normal/191
sanitizer CTests (driver wall3.217/17.560s; CTest reports3.11/16.40s) and10 focused
Python checks. Initial configure/target-build/edit/repair/total task wall and Python
wall beyond the reported test runtime are unavailable. These parallel timings are
not a summed task cost. No unchanged SDL smoke was repeated for the unscheduled
service. Local verification is not independent acceptance or whole-frame fidelity.
Reports/hashes/failure scopes: `private/boot-camp-20261020/radar-shapes-receipt-a1.json`.

## Commands and next integration

```sh
./build.command
./test.command
./run.command --boot-camp-walk
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake --build build/native --target radar-shape-buckets-vectors boot-camp-walk-check --parallel 6
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_radar_shape_buckets
# Choose a fresh private destination; this is research/test export only.
PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/extract_radar_shape_dimensions.py \
  --exe private/official-1006-probe/game.exe --output private/NEW-radar-dimensions.bin
# '-' preserves the authored threat stencil; a private threat file can replace it.
build/native/boot-camp-walk-check private/official-1006-probe - private/NEW-radar-dimensions.bin
# Use fresh private audit/report names on every comparison.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/NEW-RADAR-SHAPES.audit.json tests/compare_radar_shape_buckets.py \
  --exe private/official-1006-probe/game.exe --native build/native/radar-shape-buckets-vectors \
  --expectations private/boot-camp-20261020/radar-shapes-fresh-a1/expected.json \
  --report private/NEW-RADAR-SHAPES.json
```

Use `build/sanitize/` runners for sanitizer checks. `--uncached` before the driver
disables inspection reuse while retaining explicit original-answer reuse. Fresh
original generation needs a new output directory and research-only Unicorn JIT.
No shipped executable, proprietary data or emulator dependency is introduced.

Next make the shared refresh composition device aware and bind the actual mutable
House/coverage/actor owners. Retain the first surface's recovered device copy/
Lock/Unlock/pixels; do not overwrite them with software-only binding callbacks.
Production association, warm clone/lifetime checks and genuine sight/arrival
producers still precede live effects and ordinary SDL Objective1. Base RA2 and YR
remain incomplete. Only Apple Silicon macOS is tested. No public implementation,
dependency, worker, Windows action, download, system/Xcode/DRM change or runtime
executable-read expansion was introduced.
