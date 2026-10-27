# Two posed Units sharing complete world drawing

This prerequisite follows `013470b`. The separate, unwired entry
`drawSharedPosedGroundUnitVoxelToWorld` uses explicit actor staging bytes,
type-owned body/turret/barrel/shadow indexes and shared global scratch/pool.
It borrows these owners throughout the existing complete posed ground root;
there is no per-actor copy, temporary cache transfer or alternate drawing root.
The older flat, height-aware and posed entries retain their profiles and guards.
The SDL demo still contains one Unit.

## Engine, references and scope

The two private engines remain 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 lineage and reported no-CD provenance remain
distinct; pristine authenticity is unverified. No new Windows action or transfer
is involved. Original installations/discs and outpost2-native remain read-only.

The retained recomp snapshot labeled
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439`, `docs/voxels.md`, and YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88`, `TechnoClass.h`, remain ownership
leads, as recorded in [SHARED_UNIT_STAGING_1006.md](SHARED_UNIT_STAGING_1006.md).
Hypothesis: shared type indexes and global scratch must survive actor changes
through final drawing and the fourth shadow index, not just lit staging. Exact
base operands, matrices, state and pixels decide this profile. Recomp MIT excludes
lifted/game-derived output and retains stale The Movies wording; no YRpp license
file was found. No upstream/header/generated/lifted code, original table or
dependency is incorporated. See [REFERENCES.md](REFERENCES.md).

## Storage and original execution

`UnitVoxelWorldTypeIndexes` owns the three lit indexes and separate shadow
index corresponding to type `+0x23C`. They use the same global pool. The new
entry binds references directly to `SharedUnitVoxelStage` and the selected
`UnitVoxelActorStage`. Ordered caller stores are immediately visible to
observers; diagnostic exceptions retain partial writes. This is a native policy,
not recovered original exception/rollback behavior.

The original fixture executes actors `0x1100000` and `0x4100000`, separate Drives
and one common supplied type in a single Unicorn guest. Both actors have explicit
independent body/turret/barrel Facing, coordinates, stored ramp/timer and rocking
records. Neither actor is copied onto the other's address. The same guest runs
actual stock numeric/matrix initialization and prepared-map finalization, then
complete Unit drawing with actual body pose, depth/floor, raw/cached shadow,
RGB565 spans and cleanup. Color/depth/alpha planes, staging bytes, pool and index
state persist between the two draws; only explicit reset commands replace them.

Both whole actor/Drive records, the second 64-KiB arena/gaps, prepared Cells,
type/TMP input records, world depth/alpha/palettes, pool prefix/tail and caller
register/stack are audited. Selected actor staging byte and type indexes are the
only permitted actor/type draw writes; actor bytes must finish restored. Lazy
floor state and shared fallback position follow actual read/write forwarding.
Original instructions remain unchanged. All four normalized indexes and full
pool, final staging and world planes are compared, along with exact part keys/
matrices, selected ordered caller stores, surface/shadow observations and ordered
map/floor query hashes.

Preserve stored body ramps versus current-Cell shadow ramps, warm untransformed
turret/barrel matrices, the cold turret delta and barrel translation pivot.
Relative-height queries remain independent; Unit obtains Y, increments only the
positive-height stencil Y, then obtains X, while Foot obtains the world point
again. Saved pre-shadow dirty bounds determine cleanup even if shadow drawing
enlarges global dirty state. Shared shadow caches do not justify key, pitch or
camera invalidation changes.

Initial actor/Drive pose and Z, type/House/model/camera/contact/palette/planes,
successful heap and sufficient pool remain supplied. The map is prepared and
shared, but this fixture does not attach Process, actual actor membership or
production mutable-map ownership. Rocking, independent turret input and retained
warm-key camera changes are diagnostic inputs, not gameplay scheduling or
construction observations. There is no two-Unit SDL, screen-registry, selection,
startup, cache-lifetime or full-frame claim.

## Reproduction and next join

Accepted proof totals, refresh identities, costs and limitations are recorded in
[HANDOFF.md](HANDOFF.md). Private `shared-ground-*` logs retain exploratory and
accepted runs separately. Existing one-Unit SDL checks are regression evidence,
not original-game observations or acceptance of the new helper.

```sh
./build.command
./test.command
build/tools-env/bin/python -B -m unittest discover -s tests -p 'test_*.py'
build/native/shared-ground-world-check
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

# Fresh original execution requires the authorized host Unicorn JIT context.
# Use a new private destination, preserving all accepted receipts.
build/tools-env/bin/python -B tests/compare_shared_ground_world.py \
  --exe private/official-1006-probe/game.exe \
  --output private/unit-draw-1006/shared-ground-world-new
# Replay: --expectations CURRENT_EXPECTED_JSON --report NEW_PRIVATE_JSON
# Sanitizer: add --native build/sanitize/shared-ground-world-vectors
./run.command --terrain-demo
```

Next bind explicit parked turret Facing and production mutable Cell/fallback/
floor queries to the shared owned mover/parked group. Verify Process -> interleaved
complete draws -> Process in one original guest, without transferring final actor
or map records between guests. Preserve immutable renderer preparation and preview
clone isolation. Then expose the bounded parked scenario through separate SDL
resources/registry identities, drawing and inspection selection. Selecting an
inspection-only parked actor must never silently command Unit0. General
pathfinding, moving residents/nonzero Advance/scatter, construction/frame
scheduling, combat/economy/AI/campaigns/multiplayer/audio/saves and Yuri's Revenge
remain open. No workers, runtime executable-read expansion, downloads or
system/Xcode/DRM changes.
