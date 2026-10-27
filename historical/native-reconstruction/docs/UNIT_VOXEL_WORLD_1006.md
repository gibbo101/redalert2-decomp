# Supplied RA2 1.006 Unit staging, depth and final world pixels

October 15, 2026, after `c6b305c`. This joins the healthy Unit root and its
actual staging/cache/pixel children with ordinary Foot depth/gradient and the
stock final surface/RGB565 path. `src/render/UnitVoxelWorld.*` remains unwired.
It is a prerequisite in the same moving/turning/current-cell-light delivery;
the observable runtime remains [milestone 20's crossing](CROSSING_1006.md).

## Identity and reference hypothesis

Exact engine: `private/official-1006-probe/game.exe`, 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
The authorized private Windows copy has the same identity. Embedded 1.08,
supplied 1.006 lineage and reported no-CD modifications remain separate facts;
pristine authenticity is not established. No further transfer/Windows action,
source installation/disc, sibling-project or system change was needed.

Consulted [REFERENCES.md](REFERENCES.md)'s pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439`, `docs/voxels.md` and LICENSE,
and YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88`, `FootClass.h`,
`TechnoClass.h`, `TechnoTypeClass.h` and `Surface.h`. Hypothesis: the complete
Unit root can use the actual Foot scalar getters and final surface child with
stock metadata, retaining the same staging bytes for shadow and cleanup.
Exact base instructions and execution decide the result. No upstream/header,
generated or lifted code was incorporated; no dependency or notice was added.
The reference MIT grant excludes generated game-derived code.

## Joined boundary

`drawHealthyUnitVoxelToWorld` binds the unchanged Unit staging helper to the
readable Foot depth predicates and `drawBridgeUnitSurface`. Both scalar staging
queries and the final copy use the same immutable map/type inputs and explicit
base-depth service. The runner supplies the existing healthy ramp-zero native
base kernel. Original base depth now executes under all body headings: its
neighbor selection depends on heading even when every cell ramp is zero.
This does not verify nonzero ramps, height, status or full map construction.

Stock metadata is Cliff/Column/Tunnel/Bridge = 10/8/13/0, with nonzero
`TooBigToFitUnderBridge`. Five bounded synthetic cell profiles exercise the
ordinary column/tunnel/cliff predicates, center flag and their combination.
Contact arrays/kind/type fields exercise conditional split selection. These
records establish routine inputs, not original contact association or bridge
gameplay. Tile dimensions are a checked supplied service writing twelve zero
bytes into the inspected caller stack region.

The actual original chain is Unit `0x6FF690`, Foot depth/gradient
`0x4C9930`/`0x4C9A10`, base depth `0x6CFEA0`, final wrapper `0x6FF3E0`,
generic surface `0x434B40` and RGB565 span `0x488870`, alongside the previous
actual Foot/Drive/cache/raster/staging/snapshot/cached children and saved-dirty
byte cleanup. Shadow remains an explicit supplied service. Existing exact
inspections compose the new code-only execution allowlist; original instructions
are unchanged. No data table grants execution permission.

The generic surface entry serves both staging and world receivers. The new
fixture checks each separately. World rendering needs initialized depth/alpha
globals while the earlier cached-byte fixture required null globals. This new
subclass removes only that earlier fixture assertion: actual cached instructions
still execute with zero staging flags and the initialized globals. Earlier
oracle/source identities and accepted receipts remain unchanged. No native
arithmetic or original instruction patch was used to accommodate the fixture.

Caller-owned color, immutable depth/alpha planes and 53 RGB565 palette rows
are supplied explicitly. Deterministic fixture colors/palettes/alpha/depth are
not original converter initialization. VXL/VPL, staging palette and prepared
numeric tables come from the user's supplied data. Destination clip containment,
matched plane sizes and the bounded 4096-pixel dimensions are native safety
guards, not claims about original malformed-input behavior.

## Evidence and reproduction

**284 fresh results including twelve resets** pass. The groups are 64 cold
complete-heading cases, 64 warm/missing-model/changed-brightness split cases,
64 reverse warm/clipped/map-factor cases and 80 additional cell-depth/split/
cold/warm/bypass cases. Both supplied and black staging remaps execute.
Normal and ASan/UBSan replay receipts accompany `unit-world-v1/{expected,report}.json`.

The receipts record 562 audited roots / 128 successful guarded allocations,
272 actual complete Unit/final/cleanup calls, 1,160 depth/base queries, 888
gradient queries, 408 world surface calls (136 gradient 0 / 272 gradient 2),
432 staging surface calls, 14,550 RGB565 spans, 36,006 map services and 1,680
checked twelve-byte dimension services. Actual part children include 432 rasters,
282 snapshots and 320 cached copies / 11,244 compressed spans; 462,596 padded
encoder reads are bounded. 238,599 color pixels change across the fixtures.
These are execution counts, not additional independent comparisons.

Builds, 349 Python tests and 13 normal / 12 sanitizer CTests pass. Prior unchanged
Unit staging (286), Foot depth (5,952) and surface split (3,264) expectations
replay on both builds; original receipt/source identities remain unchanged.

Compared outputs include complete world color/depth/alpha hashes, final-surface
arguments/gradient/depth and the full pre-shadow staging stencil, shadow request,
post-cleanup surface, normalized compressed pool/cursor and all three part-index
states. Color changes while depth/alpha/palette/map/house/contact/type/HVA/model
inputs remain immutable. Original caller stack, return address, callee-saved
registers, declared writes, successful heap/canaries, old pool, capacity tail,
padded encoder reads and restored locks retain the inherited scoped audits.
Ordered native/original writes, ownership and full actor arenas remain unclaimed.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/python tools/verify_unit_voxel_world.py \
  --exe private/official-1006-probe/game.exe
build/tools-env/bin/python tests/compare_unit_voxel_world.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/unit-draw-1006/unit-world-v1/expected.json \
  --report private/unit-draw-1006/unit-world-v1/NEW-REPLAY.json
# Add --native build/sanitize/unit-voxel-world-vectors for sanitizer replay.
# Fresh original execution needs the authorized Mac host JIT context, a NEW
# --output directory and no --expectations. Never overwrite accepted receipts.
./run.command --crossing-demo
```

Actual unchanged SDL crossing passes selection/right-click, 79 samples / 78
updates, 22 occluded samples / maximum 150 hidden pixels, fresh final/no trails,
cache bypass, clipping and pan return. Its occluded PNG was visually inspected.
Receipts are in `private/unit-draw-1006/unit-world-crossing-sdl/`; elapsed
**2.594 s**. This checks the existing runtime, not the unwired join or original
whole-frame fidelity. The application remains arm64; only Apple Silicon macOS
is tested.

## Accounting and next dependency

Private `unit-world-start.json` starts this continuation at `c6b305c`.
Inherited full-delivery and initial failed-build/pilot elapsed times are
unavailable. Final normal/sanitizer builds take **7.429/10.454 s**. A pilot
initially mistook every generic surface receiver for world; distinguishing the
actual staging receiver fixed the assertion. Six final pilot cases pass with
both gradients and changed world pixels. Initializing real depth/alpha globals
also required the cached-byte fixture expansion described above. No gameplay
repair, worker or new evidence cache was needed. Contended check times are not FPS.
Accepted driver/original/native time is **1293.497/1271.457/0.164 s**. The long
original run remained CPU-active and printed only at completion. Normal/sanitizer replay comparisons take **0.125/4.494 s**; their complete
driver times are in the protected receipts. Later shadow-child research ran
alongside this frozen generation without changing its sources or runner.

Next nest the actual shadow wrapper/render/compressed-copy children before
complete caller/runtime integration and current-cell-light crossing acceptance.
Healthy Track/layer-zero/ordinary house, supplied immutable map/contact/house/
palette/planes/camera/type/HVA and successful heap/sufficient pool remain explicit
boundaries. Full construction/ownership, pool failure/eviction/lifetime, pitch
invalidation, ramps/status, decorations, scheduler/camera/fog/UI and whole-frame
parity remain open. This is locally verified recovery, not independently accepted
or a new gameplay milestone. Full base RA2 then YR remains active and incomplete.
