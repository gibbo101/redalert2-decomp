# Supplied RA2 1.006 Unit caller and voxel staging join

October 15, 2026, after `93a5b46`. This joins the complete healthy Unit voxel
caller with actual Foot/Drive, Techno cache, raster/staging, compressed snapshot
and cached drawing children. Actual BSurface bounds and saved-dirty byte Fill
also execute. `src/render/UnitVoxelStaging.*` remains unwired to the runtime.
This is a prerequisite in the same moving/turning/current-cell-light delivery;
the playable scenario remains [milestone 20's crossing](CROSSING_1006.md).

## Identity and reference hypothesis

The supplied engine is `private/official-1006-probe/game.exe`, 4,485,392 bytes,
SHA256 `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Its separately authorized private Windows copy rehashes identically. Embedded
1.08, supplied 1.006 lineage and reported no-CD modifications remain distinct;
pristine authenticity is not established. No Windows action/transfer or source
installation, disc, sibling-project or system change is needed.

Consulted [REFERENCES.md](REFERENCES.md)'s pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439`, `docs/voxels.md` staging/cache chain
and LICENSE, and YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88`,
`TechnoClass.h`/`Surface.h`. Hypothesis: the existing pixel children can execute
inside the real Unit root, using independent part indexes and the caller's real
staging cleanup. Exact base instructions and execution decide this; YR addresses
and replacement behavior are not evidence for base RA2. No reference/header,
generated or lifted code is incorporated. No dependency or notice is added;
the reference MIT grant excludes game-derived generated output.

## Joined boundary

`drawHealthyUnitVoxelIntoStaging` binds the unchanged readable Unit kernel to
three caller-owned snapshot indexes and one supplied pool. It derives barrel
presence from the selected model and turret-cache presence from the real index.
Body HVA must remain present and one-frame even when the current body model is
missing: the Unit caller reads its frame count before the Techno validity check.
Camera, ramp-zero identity, empty-dirty template and ordinary actor/type records
remain fixture inputs. Alternate/status actors, allocation failure, insufficient
pool/eviction and animated actor timing are refused or outside this domain.

The earlier `drawOrdinaryFootVoxelPart` now forwards once to exported
`drawOrdinaryTechnoVoxelPart`. The Unit kernel already executes Foot forwarding;
its lit callback binds directly to Techno. It must not invoke Foot a second time.
Existing 732 Foot results have fresh source-matched evidence after extraction;
older receipts remain historical and are not relabeled.

The original root `0x6FF690..0x7005A5` now nests:

- Actual Drive/Facing/matrix and independent `0x70A3F0`/`0x70A350` cache prechecks.
- Actual Foot `0x4C9880`, zero Drive offset and complete Techno `0x6D1D00`.
- Cold part/raster/byte staging plus snapshot/index insertion, or actual cached
  wrapper/byte selector/compressed surface/span.
- Actual BSurface GetBounds `0x411290`, Fill wrapper `0x774390`, complete Fill
  `0x7743C0`, rectangle/intersection/locking helpers and byte row stores.

Preserve the original dirty reset before body drawing, relative staging clip,
zero part flags from complementing caller `0x2800`, fresh +0x0C/cached +0xD0
Convert slots, part ordering and the dirty union's extra pixel. The dirty state
is synchronized around each native lit child. Final drawing observes the fully
composed stencil; surface/staging flags restore before shadow; only saved dirty
pixels clear after shadow. The dirty rectangle itself is retained, and bytes
outside the clipped rectangle survive. Clearing the entire surface would fail
these patterned persistent-surface fixtures.

Warm prechecks can select untransformed body matrices before later Techno cache
bypass/validity decisions. Tests cover changed pitch, DisableVoxelCache and absent
models without claiming actor-driven pitch invalidation. Separate part indexes
share the supplied pool; signed keys, hot/sorted state, capacity and normalized
pool offsets remain observable. Native ownership and successful allocation are
host boundaries, not original pool-management or ordered heap-write parity.

`tools/verify_unit_voxel_staging.py` composes existing Foot/Unit/raster/presentation
and map-light Fill inspections. It adds the complete 17-byte / six-instruction
rectangle-origin getter `0x435560` and checks the actual surface slots. Only
inspected code ranges grant execution; deduplication/order of those intervals
in this new fixture does not widen them. Full Fill inspection includes other
pixel sizes, but this join executes and implements the byte staging branch only.

## Evidence and reproduction

**286 fresh results, including 20 explicit host resets**, pass on normal and
ASan/UBSan builds. The changed-source Foot refresh adds **732 fresh results,
including six resets**, with both replays. Existing **584 snapshot results**
replay on both current builds with their unchanged identities.

| Fresh Unit results | Count |
| --- | ---: |
| Cold complete parts/headings/order/growth/sort | 64 |
| Warm changed pose/brightness/missing models | 64 |
| Reverse warm queries and persistent cleanup | 64 |
| Warm prechecks before disable/bypass/model changes | 8 |
| Independent body/turret/barrel cache states | 18 |
| Bypass/absent barrel/invalid/clipped cleanup | 48 |
| Three-index/pool/patterned-surface resets | 20 |

Both supplied TEMPERAT.PAL and all-black converters execute original
initialization. Two supplied camera matrices and all 32 body/turret bins are
covered, with neutral and nonneutral barrel pitch. These are supplied consecutive
facing values, not recovered actor timing or cache invalidation.

The Unit receipts record **542 audited roots / 124 guarded allocations**, **266
actual Unit roots and byte fills**, **702 actual Foot/Drive/cache calls**,
**280 raster calls**, **220 snapshots**, **386 cached draws / 13,796 spans**,
**1,078 bounds calls** and **300,982 bounded encoder reads**. Unit prechecks
execute 216/160 times, pose construction/pitch rotation 114 times and the warm
matrix shortcut 152 times. Original signed searches/sorts execute 520/220 times.
These counts establish what executed within the bounded fixture; they are not
additional independent behavior comparisons.

Builds, **341 Python tests**, **12 normal / 11 sanitizer CTest checks**, and
source/diff/link audits pass. Receipts are under `private/unit-draw-1006/unit-stage-v1/` and the
changed-source Foot refresh under `private/unit-draw-1006/foot-stage-v2/`.

Compared Unit outputs include final-call arguments, full composed staging hash
and dirty bounds, complete shadow pose/key/stencil arguments with the same
staging state, post-clear full surface, full normalized pool hash/cursor and all
three index states/keys/capacities/hot/sorted flags. Original visibility,
map/height/predicate, final RGB565/world drawing and shadow rendering remain
read-only services. Staging scalar getters +0x2C0=-1 and +0x2C4=2 remain
supplied. The final service does not alter the source stencil.
These are joined caller/pixel checks, not complete actor or frame fidelity.

Caller return/stack/ESP/callee-saved registers, declared writes, immutable actor/
type/model/HVA/old-pool/other-heap inputs, heap canaries, pool capacity tail,
encoder padded reads and restored surface locks are audited. Type writes are
restricted to the three index records. Actual pixels execute in the Unit root;
they are not generated by self-consistent native tests alone.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/python tools/verify_unit_voxel_staging.py \
  --exe private/official-1006-probe/game.exe
build/tools-env/bin/python tests/compare_unit_voxel_staging.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/unit-draw-1006/unit-stage-v1/expected.json \
  --report private/unit-draw-1006/unit-stage-v1/NEW-REPLAY.json
# Add --native build/sanitize/unit-voxel-staging-vectors for sanitizer replay.
# Fresh original execution needs the authorized Mac host JIT context, a NEW
# --output directory and no --expectations. Never overwrite accepted receipts.
./run.command --crossing-demo
```

Runtime crossing remains unchanged and is checked through actual SDL selection,
right-click movement, occlusion/no trails, bypass, partial/offscreen clipping and
pan return. Its occluded frame is visually inspected. This checks milestone 20,
not the unwired join or original whole-frame fidelity. Only Apple Silicon macOS
is tested; the native application remains an arm64 Mach-O.

## Accounting and next dependency

Private `unit-stage-start.json` starts this continuation at `93a5b46`. Full
inherited drawing-delivery elapsed time is unavailable. The four-case original/
native pilot passed. A preliminary full Unit generation was deliberately stopped
before receipts to change inspection call tuples to JSON-stable lists, preserving
strict replay identities. No original instruction or native arithmetic was
changed for that correction. Initial/final build and interrupted-generation
elapsed times were not measured; accepted driver/replay/SDL costs are in receipts.
Accepted Unit driver/original/native times are **443.955/428.101/0.162 s**;
Foot refresh **612.488/602.215/0.247 s**. Unit native/sanitizer replay comparisons
take **0.084/0.617 s**, Foot **0.195/1.461 s**, snapshot **0.074/1.295 s**.
Fresh runs/replays may contend; none of these is an FPS measurement. Actual SDL
crossing takes **3.339 s**, with 79 samples / 78 updates, 22 occluded samples /
maximum 150 hidden pixels, selection/right-click and all listed checks passing.

A sandboxed process listing was refused; a scoped host listing identified only
this turn's Unit process for interruption. No automatic approval review rejected
the authorized research. One shell glob and an assumed SDL receipt filename
were corrected during read-only inspection. No gameplay repair was needed.
No worker or new evidence caching infrastructure was introduced.

Next nest actual ordinary Foot/base depth and the stock nonzero bridge-size
final surface branch into this Unit root, then shadow children before runtime
wiring. Keep the existing patched moving/turning/current-cell-light scenario as
the observable acceptance target. Full construction/ownership, pitch invalidation,
pool management/lifecycle, decorations, scheduling/camera/fog/UI and whole-frame
parity remain open. This is locally verified recovery, not independent acceptance
or a completed new gameplay milestone. Full base RA2 then YR remains incomplete.
