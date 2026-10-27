# Supplied RA2 1.006 compressed voxel snapshots and cached staging

October 15, 2026, after `607e25e`. **584 fresh original/native results** and both
normal/ASan/UBSan replays pass. This checkpoint recovers the compressed
snapshot representation and the complete ordinary cached-part staging draw.
It is a prerequisite in the same moving/turning/current-cell-light drawing
delivery. The helpers remain unwired; the playable scenario is still
[milestone 20's crossing](CROSSING_1006.md).

## Identity and reference hypothesis

The gate requires `private/official-1006-probe/game.exe`, 4,485,392 bytes,
SHA256 `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
The approved private Windows copy has the same identity. Embedded 1.08,
supplied 1.006 lineage and reported no-CD provenance remain separate facts;
pristine authenticity is not established. No Windows action/transfer, source
installation/disc, sibling project or system configuration changed.

Consulted [REFERENCES.md](REFERENCES.md)'s pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439`, `docs/voxels.md`'s cache-hit and
staging chain, and LICENSE; YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88`, `TechnoClass.h` DrawVoxel and
`Surface.h` declarations were leads only. Hypothesis: original cached hits use
a compressed image and a separate surface/span path, so copying the raw raster
does not establish the cached child's behavior. Exact base instructions and
execution decide the implementation. No upstream/header/generated/lifted code
or dependency was incorporated; no new notice is needed. The inspected MIT
grant excludes game-derived generated output.

## Recovered representation and behavior

The original snapshot has a 12-byte header: signed 16-bit X/Y offsets, unsigned
16-bit width/height and a pointer to encoded rows. Every row starts with a
little-endian uint16 total byte length including its two-byte prefix. Nonzero
bytes are literals; zero followed by a count is a transparent skip.

**Preserve the encoder's inclusive lookahead before its 255-byte cap.** On a
zero pixel it scans while the prospective count is less than or equal to the
remaining width, reading the following byte before incrementing the count.
Consequently it can read two bytes past the declared row and emit a final skip
one pixel longer than the row. It scans before capping, including when more
than 255 zeros remain. Native callers must supply two readable padding bytes,
including actual following surface pixels. This is not a conventional
row-limited RLE encoder. The decoder follows the row's encoded byte length,
including that possible extra decoded zero; cached spans never write zero runs.

The snapshot pool reserves the header first, writes the cropped fields and row
pointer, then encodes/copies rows individually. Insufficient header capacity
returns null without advancing. Insufficient later row capacity leaves the
header, earlier completed rows and advanced cursor intact. Equal capacity is
accepted. Source surface lock/unlock and actual stride queries execute.

The cached wrapper borrows its encoded-row buffer and cleans up without freeing
it. Unit kind 1 with the staging byte selects the staging converter. It clears
flag `0x10`; supported selected flags are zero. The actual cached selector uses
byte Convert **+0xD0**, whose vtable `0x79E4D0` selects span `0x4864F0`.
This differs from the fresh raster copy's Convert +0x0C. The wrapper unions
signed offset plus point into the dirty rectangle, retaining the extra right/
bottom pixel, then queries +0x2C4 before +0x2C0. The compressed surface copy
uses row prefixes to skip vertically and tokens to handle clipped-left starts
inside a zero run. Source zero preserves the destination; a nonzero literal
remapped to zero erases it. Surface clipping uses a relative clip origin.

`src/render/VoxelSnapshot.*` implements these operations in readable C++.
Native storage is caller-owned and the header's +8 field holds a pool-relative
offset instead of a process pointer. That pointer representation, storage and
remap association are explicit host boundaries. The native domain is byte
staging/Unit kind 1, bounded dimensions/crops and zero depth/alpha surfaces.
Malformed-input refusals are safety guards, not original behavior claims.

`tools/verify_voxel_snapshot.py` pins eleven complete ranges / 1,108 instructions, in addition to
the inherited part/staging/composition/cache inspections:

| Boundary | Patched range |
| --- | --- |
| Inner encoder | `0x63D150..0x63D1AF` |
| Length-prefixed encoder | `0x63D1B0..0x63D1EE` |
| Length-prefixed decoder | `0x63D260..0x63D2C5` |
| Snapshot append | `0x69A1D0..0x69A300` |
| Complete cached part wrapper | `0x6D29D0..0x6D2C96` |
| Cached converter selector | `0x485D60..0x486004` |
| Cached byte span | `0x4864F0..0x48656E` |
| Compressed surface copy | `0x4350C0..0x435531` |
| Surface base constructor | `0x49ED90..0x49EDA9` |
| Borrowed buffer constructor | `0x4382C0..0x4382F1` |
| Buffer cleanup | `0x438410..0x438438` |

The verifier also pins lookahead operands, zero-flag slot and actual cached
span dispatch. New cache executions have an instruction allowlist composed
from complete inspected ranges and explicitly supplied scalar getter services.
No original instruction is patched.

## Evidence and reproduction

| Fresh original/native results | Count |
| --- | ---: |
| Row encoding, count-only encoding, decoding and padded lookahead | 180 |
| Full snapshot rows and cached staging pixels | 64 |
| Capacity boundaries and retained partial pool contents | 62 |
| Clipping, relative origins, dirty unions and zero-remap erasure | 80 |
| Empty snapshot dimensions | 6 |
| Actual stock body/turret/settled-barrel raster, snapshot, cached staging | 192 |
| **Total** | **584** |

Rows cover lengths 0/1/2/3/7, both sides of 255 and 510, 1024 and 4096,
dense/zero/mixed patterns and explicit next-byte padding. Capacity cases include
failure before the header, after the header and after completed rows. Both
supplied TEMPERAT.PAL and all-black converters execute original initialization;
the latter makes nonzero-to-zero erasure observable. Stock cases cover all 32
headings for all three parts on each converter. Thirty-two identity-checked
prior original pose scenarios are reused inputs, not fresh pose recovery.

The stock cases execute three successive original roots: actual part/raster/
staging, actual snapshot append and actual cached wrapper/selector/compressed
surface/span. They **do not execute the cache parent or Foot between them**.
Results compare complete normalized pool hashes/cursors, row bytes/decoded
bytes, complete 65,536-byte raster/staging hashes, dirty bounds and query order.
Source-zero transparency, remapped-zero erasure and clipped-left runs match.

There are **1,690 audited roots**, **78 guarded allocations**, **404 actual
snapshot appends**, **352 actual cached wrapper/selector/surface calls** and
**6,468 actual cached spans**. Encoder calls total 7,176; decoder calls 180.
The 192 stock raster calls execute actual light/reset/project/flush and 384
matrix multiplies. Original source reads stay within each explicitly supplied
padded plane. Return address, caller-tail/ESP/callee-saved checks, immutable
actor/model/pool/converter inputs, heap canaries, permitted original writes,
pool capacity tails and restored source/staging locks pass. These are bounded
fixture audits, not ordered native/original heap writes or ownership parity.

Accepted receipts: `private/unit-draw-1006/snapshot-v1/{expected,report}.json`
and both replays. Sources, executable/profile, inspections, supplied assets,
palette, prepared data and prior pose receipt are checked before/after runs.
Changed inputs require fresh evidence. Earlier 242 part/staging results replay
on both current builds without new original execution.

Normal/sanitizer builds, **325 Python tests**, **10 normal / 9 sanitizer CTest
checks** and source/diff/link audits pass. The native application remains arm64
Mach-O. Actual unchanged SDL crossing passes 79 samples / 78 updates, selection/
right-click, 22 occluded samples / maximum 150 hidden pixels, fresh final/no
trails, cache bypass, clipping and pan return. This checks milestone 20, not
the unwired helpers or original whole-frame parity. Only Apple Silicon macOS
is tested.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/python tools/verify_voxel_snapshot.py \
  --exe private/official-1006-probe/game.exe
build/tools-env/bin/python tests/compare_voxel_snapshot.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/unit-draw-1006/snapshot-v1/expected.json \
  --report private/unit-draw-1006/snapshot-v1/NEW-REPLAY.json
# Add --native build/sanitize/voxel-snapshot-vectors for sanitizer replay.
# Fresh original execution needs the authorized Mac host JIT context and a NEW
# --output directory; omit --expectations. Never overwrite accepted receipts.
./run.command --crossing-demo
```

## Accounting and limits

Private `snapshot-start.json` and closing receipt record a measured interval
starting after initial implementation/first build. Earlier turn elapsed and full
inherited delivery time are unavailable. Subsequent normal/sanitizer builds:
**8.16/5.99 s**. Fresh driver/original/native: **158.077/152.216/0.103 s**.
Python discovery: 0.455 s; normal/sanitizer CTest: 0.21/1.51 s. Replay timings
are in their receipts; separate SDL elapsed was not measured. Checks contended;
these are not performance/FPS claims.

Before accepted generation, one verifier operand address was corrected from
an unaligned address to the inspected instruction start. One pilot allowlist
stopped on a supplied scalar getter because the code hook decoded its blank
service address as a two-byte instruction; handling the exact declared service
entry before original-range validation fixed the observer. No original instruction
was changed. The corrected complete pilot and fresh run passed without a native
numeric/pixel mismatch. No build/gameplay repair, new evidence caching infrastructure,
worker, Windows/source/system change occurred.

Next nest the actual Foot/cache parent around raster/staging/snapshot/cached
children, then join Unit/depth/shadow/final surfaces before runtime wiring.
Full construction/ownership, pool allocation/eviction, pitch invalidation,
decorations, scheduling/camera/fog/UI and whole-frame parity remain open. This
is locally verified recovery, not independent acceptance or a new observable
gameplay milestone. Full base RA2 then YR remains active and incomplete.
