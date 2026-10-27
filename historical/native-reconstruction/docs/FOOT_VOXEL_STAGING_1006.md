# Supplied RA2 1.006 nested Foot and lit-cache drawing

Current source-matched receipts after the Unit join are `foot-stage-v2/`:
**732 fresh results and both replays**. `foot-stage-v1/` below records the earlier
checkpoint and no longer matches the extracted Foot/Techno source identity.
[UNIT_VOXEL_STAGING_1006.md](UNIT_VOXEL_STAGING_1006.md) now nests complete Unit
with these children and actual byte cleanup; final depth/world/shadow children
and runtime integration remain open. Commands below select current v2 receipts.

October 15, 2026, after `cc2b411`. This joins actual Foot/Drive forwarding,
the complete ordinary Techno cache parent, raster/staging drawing, compressed
snapshot insertion and cached staging. The native helper remains unwired.
It is a prerequisite in the same moving/turning/current-cell-light drawing
delivery; the playable scenario remains [milestone 20's crossing](CROSSING_1006.md).

## Identity and reference hypothesis

The exact supplied base engine is `private/official-1006-probe/game.exe`,
4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 lineage and reported no-CD provenance remain
separate facts; pristine authenticity is not established. The previously
authorized private Windows copy has this same identity. No Windows action,
transfer, source disc/installation, sibling-project or system change is needed.

Consulted [REFERENCES.md](REFERENCES.md)'s pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439`, `docs/voxels.md`'s cache-hit,
miss and staging chain and LICENSE, plus YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88`, `TechnoClass.h` and `Surface.h`.
Hypothesis: the established pixel children can execute inside the real parent
without render/snapshot/cached-draw services, while preserving its cold/warm
decisions. Exact base instructions and execution decide the result. No upstream,
header, generated or lifted code is incorporated; no dependency or notice is added.
The reference MIT grant excludes game-derived generated output.

## Joined boundary

`src/render/FootVoxelStaging.*` adds caller-owned snapshot index/pool storage
and `drawOrdinaryFootVoxelPart`. Its selected domain is healthy Unit kind 1,
staging byte set, inactive status, zero actor flags, false house predicate,
caller flags exactly `0x2800`, one stock loaded section, present identity HVA,
and sufficient supplied pool/successful allocation. Optional actual Drive
returns the recovered zero offset. Model and HVA validation follows lookup.

- The actual Foot root `0x4C9880` calls complete Techno root `0x6D1D00`.
  This supersedes the earlier fixtures' supplied pixel children only within
  this domain. Preserve the parent's `(0x2000|0x800)&~callerFlags`: staging
  flags are zero, independently of the final-world flags.
- A cacheable miss executes actual part root `0x6D24E0`, its lighting/HVA/
  raster children and the fresh byte-copy selector/surface/span. The parent
  updates the dirty union, obtains the real raster surface via `0x717040`,
  appends via `0x69A1D0`, then inserts the snapshot. It does not recursively hit.
- A warm hit executes actual cached root `0x6D29D0`, selector, compressed
  surface and span. It survives missing current model/HVA records and changed
  pose/frame/brightness; no raster or snapshot append occurs. Preserve the
  distinct cached Convert +0xD0 versus fresh +0x0C.
- Null index, DisableVoxelCache and key -1 bypass snapshots. Invalid misses
  and invalid bypasses skip drawing. Preserve signed keys, hot-before-sort,
  successful capacity 0/10/20/40, unsorted state after append, and hot clearing
  on growth. The generated domain has unique cacheable keys.
- Preserve the dirty union's extra right/bottom pixel, relative clip origins,
  transparent preservation, remapped-zero erasure and padded encoder lookahead.
  Native snapshot pointers are pool-relative offsets; native index/heap ownership
  and reset remain host storage boundaries.

Pool exhaustion/eviction and allocation failure are refused, not silently
approximated. The original fixture stops before its three failure branches;
native exhaustion throws after the already performed draw/partial pool writes.
This join is not a recoverable original pool-management API.

`tools/verify_foot_voxel_staging.py` composes the prior snapshot, Foot, raster,
Unit and presentation inspections. It adds six complete timer, brightness,
signed comparator and qsort/helper ranges / 244 instructions. Both complete
out-of-line raster span bodies add 82 instructions:
`0x798CA0..0x798D09` and `0x798DC0..0x798E29` are inspected through their final
jumps back to the already-inspected traversal, with exact disc/patched operand
mapping and actual parent jump checks. Four actual parent calls pin raster,
surface getter, snapshot and cached-child association. The execution allowlist
collects decoded code ranges only; inspected data tables do not grant execution.

## Evidence and reproduction

The comparison driver covers **732 results, including six explicit host resets**:

| Fresh joined results | Count |
| --- | ---: |
| Cold body/turret/settled-barrel, 32 headings and index growth/sort | 192 |
| Immediate warm hits with missing models and changed pose | 192 |
| Reverse warm traversal, signed search, changed placement/clip | 192 |
| Null/disabled/-1 bypass and clipping | 126 |
| Invalid misses/bypasses retaining pixels | 24 |
| Index/pool resets | 6 |

Both supplied TEMPERAT.PAL and all-black remaps execute original converter
initialization. Patterned destination pixels expose zero transparency and
nonzero-to-zero erasure. Signed keys include INT_MIN, -2, 0, 31 and INT_MAX.
The 32 original pose scenarios are identity-checked reused inputs, not fresh
pose recovery or original actor timing observations.

Compared outputs include complete raster hashes on fresh/bypass draws, complete
staging and normalized full-pool hashes, cursor, dirty bounds and index count,
capacity, sort/hot state and keys. Original actor/type/HVA/global records,
house query, scalar depth/gradient getters, file/heap allocation and surface
storage remain supplied. Original raster, snapshot, cached drawing and index
sort/search instructions execute unchanged inside the real Foot/cache parent.

Return address, caller tail/ESP/callee-saved registers, immutable actor/model/
old-pool/other-heap inputs, heap canaries, declared writes, pool capacity tail,
padded raster reads and restored locks are audited. These are bounded fixture
checks, not ordered native/original heap-write or ownership parity.

The receipts record **1,462 audited roots / 96 guarded allocations**, **726
actual Foot/cache calls**, **462 actual Drive offsets**, **318 raster calls**,
**192 snapshot appends**, **384 cached draws** and **12,412 cached spans**.
Actual signed search/sort execute 570/192 times; 262,196 bounded source reads
are checked during snapshot encoding. Matrix multiplication executes 636 times.
Normal/sanitizer builds, **333 Python tests**, **11 normal / 10 sanitizer CTest
checks** and source/diff/link audits pass.

Receipts are under `private/unit-draw-1006/foot-stage-v1/`. Fresh runs require
unchanged executable/profile, inspections, relevant source files, supplied assets,
palette, prepared files, prior pose receipt and runner. Replay pins original
expectations and their fresh receipt. Use a new report path; accepted evidence
is never overwritten. The prior 584 snapshot results also replay on current
normal and sanitizer builds without new original execution.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/python tools/verify_foot_voxel_staging.py \
  --exe private/official-1006-probe/game.exe
build/tools-env/bin/python tests/compare_foot_voxel_staging.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/unit-draw-1006/foot-stage-v2/expected.json \
  --report private/unit-draw-1006/foot-stage-v2/NEW-REPLAY.json
# Add --native build/sanitize/foot-voxel-staging-vectors for sanitizer replay.
# Fresh original execution needs the authorized Mac host JIT context and a NEW
# --output directory; omit --expectations. Never replace accepted receipts.
./run.command --crossing-demo
```

Actual unchanged SDL crossing passes 79 samples / 78 updates, selection/right-
click, 22 occluded samples / maximum 150 hidden pixels, fresh final/no trails,
cache bypass, clipping and pan return. The occluded frame was visually inspected.
This verifies existing milestone 20 integration, not the unwired join or original
whole-frame parity. The application remains arm64 Mach-O; only Apple Silicon
macOS is tested.

## Accounting and next dependency

Private `foot-stage-start.json`, `foot-stage-attempts.json` and closing receipt
record the measured interval and checks. Accounting starts after initial
implementation; earlier turn elapsed and full inherited delivery time are
unavailable. Build and failed-attempt elapsed times were not measured. SDL takes
2.321 s. Fresh driver/original/native times are **603.548/593.124/0.273 s**.
Replay costs are recorded in their receipts; checks may
contend, so none is an FPS claim.

Before accepted evidence, allowlist stops led to complete presentation/span
inspection; a stale raster source address and missing known encoder-scratch
allowance were corrected. The five-case cold/warm/invalid pilot passed. One
preliminary full generation was deliberately interrupted to exclude data tables
from the code allowlist, with a synthetic guard added before restarting. No
original instruction patch or native numeric workaround was made. No worker,
Windows/source/system change or new evidence caching infrastructure occurred.

Next nest the complete Unit root around these lit children, then combine actual
Foot/base depth, shadows and final surfaces before runtime wiring. Respect the
Foot-versus-Techno callback boundary: the existing Unit helper already performs
Foot forwarding, so integration must not apply that wrapper/offset twice.
Full construction/ownership, pitch invalidation, pool management/lifecycle,
decorations, scheduling/camera/fog/UI and whole-frame parity remain open. This is
locally verified recovery, not independent acceptance or a new gameplay milestone.
Full base RA2 then YR remains active and incomplete.
