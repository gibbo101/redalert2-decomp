# Two actors sharing Unit staging and type indexes

This prerequisite follows the owned mover/parked membership checkpoint
`8e92ebe`. It separates the selected actor's staging byte, type-owned body/
turret/barrel indexes and shared surface/dirty rectangle/pool. The new entry
`drawSharedUnitVoxelIntoStaging` is unwired. The SDL demo still has one Unit;
complete live two-actor world/shadow drawing and selection remain next.

## Exact engine and reference boundary

Both private engines remain 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 lineage and reported no-CD provenance remain
separate facts; pristine authenticity is unverified. No new Windows action,
transfer, installation/disc/outpost2 mutation or download is involved.

The retained recomp reference snapshot labeled
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439`, `docs/voxels.md`, describes YR's
global staging/cache chain. Pinned YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88`, `TechnoClass.h` DrawVoxel/cache
declarations, is a naming lead. Hypothesis: per-actor cache copies would hide
cross-actor warm reuse and the original global scratch ownership. Exact base
instructions and interleaved execution decide this profile, not YR offsets or
replacement rendering. The retained recomp MIT terms cover authored tools/docs,
exclude lifted/game-derived output and retain stale The Movies wording. No YRpp
license file was found. No upstream/header/generated/lifted code, original table,
proprietary extracted content or dependency is incorporated. See
[REFERENCES.md](REFERENCES.md).

## Ownership and observation contract

`verify_shared_unit_staging.py` checks selected operands inside the already
inspected complete Unit root `0x6FF690..0x7005A5`. It reads the type from actor
`+0x5AC` and accesses the three type index records `+0x214/+0x228/+0x250`.
It writes actor byte `+0x5BB` separately from global current surface `0x83995C`
and dirty rectangle `0xAD0490..0xAD049F`. The existing actual cache parent uses
the shared supplied pool at `0x839AA0`. This is association/consumer evidence;
original allocation, constructors, lifecycle, eviction and arbitrary types are
not established.

Native storage expresses those owners as `UnitVoxelActorStage`,
`UnitVoxelTypeIndexes` and `SharedUnitVoxelStage`. Successful sequential calls
share actual cache objects and bytes; they do not copy cache results between
actors. The existing one-actor APIs remain unchanged. The new adapter forwards
recovered surface/actor/reset stores immediately, then binds actual Techno
cache/raster/staging/snapshot/cached/cleanup children. Dirty state is live around
each child and the saved region clears after the shadow observation. No whole-
surface clear or automatic cache reset is added.

The original fixture executes two actor addresses (`0x1100000`, `0x4100000`),
separate Drive records and a supplied common type in one guest. Each actor has
its own supplied body, turret and barrel Facing and location. The second actor
is never copied onto the first address for execution. Both entire actor records,
both Drive records and the second 64-KiB arena/gaps are immutable during drawing
apart from the selected actor's staging byte, which must finish unchanged.
Type changes are limited to the actual indexes; pool prefix/tail, heap canaries,
surface locks, caller registers/stack and code/write allowlists retain audits.

Compared outputs include actor-specific query order and coordinates, all eight
selected caller stores (surface/actor flags and four dirty resets), exact part
keys/matrices, composed image at final/shadow observations, complete post-clear
staging, normalized full pool and all index count/capacity/sort/hot/key state.
Cross-actor hits are counted only when an actual cached child uses a snapshot
inserted by the other actor. Heap/global scratch writes beyond the selected
caller stores are audited, not claimed as ordered native heap-write parity.

The profile is healthy flat/settled Track, one-frame body HVA, successful heap
and sufficient pool. Actor/type/Drive/global/camera/model associations, height
zero, visibility, scalar depth, final world and shadow observations remain
supplied. These draws do not join owned membership/Process, prepared-map reads,
RGB565 world/shadow pixels, screen registry, selection, construction or scheduling.
Pitch and camera changes with retained warm keys are diagnostic inputs, not
recovered gameplay invalidation/timing. Keep stored body ramps distinct from
current-Cell shadow ramps in the later complete drawing join.

## Evidence, reproduction and remaining work

The final receipt, totals, test/refresh identities and measured costs are recorded
in [HANDOFF.md](HANDOFF.md). The suite covers opposite and equal actor headings,
all 32 bins, interleaved cold/warm calls, changing only one actor, cross-actor
cache hits, bypass, absent parts, clipped/patterned cleanup and two remaps.
Native guards separately check rejected ownership/domain states and immediate
partial writes after a throwing diagnostic observer. Those exception tests are
host policy, not original-game fault/rollback behavior.

```sh
./build.command
./test.command
build/tools-env/bin/python -B -m unittest discover -s tests -p 'test_*.py'
build/native/shared-unit-staging-check
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

# Fresh original execution requires the authorized host Unicorn JIT context.
# Use a NEW private destination; do not overwrite accepted evidence.
build/tools-env/bin/python -B tests/compare_shared_unit_staging.py \
  --exe private/official-1006-probe/game.exe \
  --output private/unit-draw-1006/shared-unit-stage-new
# Replay uses --expectations CURRENT_EXPECTED_JSON --report NEW_PRIVATE_JSON.
# Add --native build/sanitize/shared-unit-staging-vectors for sanitizer replay.
./run.command --terrain-demo
```

Next join these owners with complete posed body/turret/barrel, actual shared
prepared-map depth/height and raw/cached shadow/world consumers, using both live
owned actors in one original guest. Verify mutable map field/identity forwarding
without changing immutable renderer/preview Cells. Then expose the bounded parked
scenario through SDL drawing/selection and occupied-target/empty-Cell input.
Selecting an inspection-only parked actor must never command actor 0. General
pathfinding, moving residents/nonzero Advance/scatter, combat/economy/AI/campaigns/
multiplayer/audio/saves and Yuri's Revenge remain open. No workers, runtime binary
reads, system/Xcode/DRM changes, two-Unit gameplay or full-frame claim.
