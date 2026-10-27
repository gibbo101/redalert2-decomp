# Supplied RA2 1.006 complete healthy Unit drawing integration

October 15, 2026, after `43dea64`. The selected capability is a moving/turning
healthy Rhino drawn through ordinary Unit visibility and DrawIt, current-cell
brightness, actual lit staging/cache/final surfaces and actual shadow children.
The patched playable renderer now uses that chain. The retained disc renderer
keeps its historical integration. This closes the bounded caller-to-pixels work
following [CROSSING_1006.md](CROSSING_1006.md); it does not establish whole-frame
fidelity, full actor construction or the complete game.

## Identity, references and hypothesis

Supplied `private/official-1006-probe/game.exe`: 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
The approved private Windows copy has the same hash. Embedded 1.08, supplied
1.006 patch lineage and reported no-CD modifications remain distinct; pristine
authenticity is not established. The native app does not execute this binary.
Source discs/installations, Windows and Outpost 2 remain unchanged.

[REFERENCES.md](REFERENCES.md)'s pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439`, `docs/voxels.md` and LICENSE,
plus YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88`, Unit/Techno/Foot/
TechnoType/Surface declarations supply leads. Hypothesis: the recovered ordinary
caller can forward actual current-cell brightness into the complete Unit/world/
shadow child, with independent type indexes and unchanged saved-dirty cleanup.
Exact base instructions and execution decide this. No upstream/header/generated
or lifted game code was incorporated; no dependency or notice was added.

## Joined original boundary

`UnitCallerWorld.*` binds unchanged `drawOrdinaryUnitCaller` to unchanged
`drawHealthyUnitVoxelAndShadowToWorld`. The new original fixture nests actual
`0x6FF350` / Object visibility and `0x700E70` DrawIt around actual `0x6FF690`,
the complete lit/cache/raster/staging/depth/final-surface/shadow children and
saved-dirty byte cleanup. Some cases start at DrawIt directly. Parent coordinate/
word-cell map lookups, height wrapper and screen registration execute unchanged.
The complete coordinate-copy leaf `0x5D4E40` is additionally inspected and allowed;
data tables never grant execution permission.

Preserve signed screen-byte subtraction, resource bit-0 initialization, layer-5
early exit, registry limits/margins/origin and capacity tails, separate light-cell
queries, wrapped ambient/optional -500/ExtraUnitLight arithmetic, exact secondary
byte 0xFF, original type restoration before Foot decoration and gate clip-relative
point adjustment. Current-cell flags/ambient are immutable within each fixture;
the two light lookups are distinct calls. Cached geometry, pool/index decisions,
raw shadows and cleanup remain as in
[UNIT_VOXEL_SHADOW_WORLD_1006.md](UNIT_VOXEL_SHADOW_WORLD_1006.md).

The new fixture prepares caller fields before the inherited actor snapshots.
It retains four-index/heap/pool/planes/type/caller-stack audits and adds actual
registry stores/tail checks, a checked immutable map-pointer table and explicit
resource/type stores. Parent map lookup executes; child neighbor lookup retains
the earlier read-only service against those same synthetic cells. Ground zero,
projection result, original-visible type, unused shape lookup and Foot decoration
remain services. No original instruction is patched. This is a bounded joined
fixture, not original map/actor/converter construction or ordered full-actor writes.

Original-visible healthy Track/ground/ramp-zero, loaded one-section body/one-frame
HVA, stock metadata 10/8/13/0/TooBig=1, inactive timer, no bridge/harvester/flag/
add-14/alternate type, identity global/no half scale and zero Z-shape bound it.
Successful heap, sufficient compressed pool, palette/planes/camera and actor/type/
house records remain supplied. Caller coordinate-cell bit 0x100 is refused.
Selected false visibility/layer/secondary cases skip drawing without changing
pixels or pool. Native guards are safety refusals, not malformed-input parity.
Joined pixel cases keep the incoming final brightness within 0..65535, the
verified span domain. Caller-only arithmetic extremes retain their separate
original receipts; they are not claimed as joined pixel cases here.

## Runtime associations and remaining adapters

Patched GameAssets reads the recovered draw metadata/default associations and
FireAngle through the native INI reader, requiring stock 10/8/13/0/1 and angle 8.
Present integer parsing and full type/model/actor construction remain host work.
The runtime supplies settled barrel heading **14336**, one frame and zero status
fields. Four independent snapshot indexes share a bounded native 512 KiB pool.
No original pool allocation/eviction/ownership/lifetime claim follows. The native
renderer fails explicitly on exhaustion; it does not silently invent eviction.

Current Drive coordinates select immutable map-light records twice through the
caller. The house converter remains independent of local source tint; brightness
changes do not invalidate indexed images. Ordinary coordinate-cell flags and
visibility/type predicates remain supplied zero/visible policies. Foot depth
storage deliberately supplies neutral flat tile/tunnel/cliff/contact fields;
their real map initialization is unrecovered. Base depth still uses the recovered
flat/elevation calculation. This integration does not infer original actor/map
field associations from native tile metadata.

Projection/inverse camera, zoom, always-visible alpha, force=1, whole static-layer
restoration, registration lifetime and UI/decorations remain host policies.
Diagnostic cache bypass supplies raw key gate zero as well as child bypass:
otherwise the original warm-matrix shortcut can precede a disabled child. This
does not rename that global gate as DisableVoxelCache or recover its lifetime.
Read-only cache keys and scratch final surfaces provide native coverage/count
telemetry; they do not alter actual drawing or serve as original fidelity evidence.
Full pitch/status invalidation, alternate actors/ramps, fog, scheduling and
whole-frame parity remain open.

## Evidence and reproducible capability

**56 fresh original/native results including four resets** pass. The remaining
52 commands cover twelve cold calls, twelve warm changed-light/offset/clip calls,
eight reverse-heading/raw-shadow/lit-bypass calls, twelve ambient/extra-light/
predicate/NoShadow calls and eight secondary/layer/visibility rejection cases.
Stock and black staging palettes execute. Full world color/depth/alpha, staging,
pre-shadow request/stencil, saved-dirty cleanup, normalized pool/cursor, all four
indexes, caller resource/registry/tails and ordered caller events match. Depth
and alpha remain unchanged. Receipts are
`private/unit-draw-1006/caller-world-v1/{expected,report}.json`.

The receipt records 124 checked roots / 96 guarded successful allocations,
48 actual DrawIt and 26 visibility entries, 44 Unit/Foot-shadow entries, 62 shadow
parent entries, 26 fresh shadow renders, 1,350 compressed / 278 raw shadow spans,
54,023 checked zero Z-shape bytes and 98,441 bounded encoder reads. Both final
gradients execute. These are execution counts within the bounded fixtures, not
additional independent comparisons or original-frame evidence.

Normal and ASan/UBSan replays use the same accepted expectations and retain
transitive source/input/inspection identities. Eight previous child runner hashes
and source entries remain unchanged; their 284 Unit/world, 160 cached-shadow,
402 complete-shadow and 152 Unit+shadow results retain eligible normal/sanitizer
receipts. Eleven caller/type/metadata/placement/traversal/redraw suites replay
**79,978 cached original results per build**, with current identity validation.
They are not new original executions. Historical caller/type state receipts were
correctly refused; the current harvester-profile receipts were then selected.

The optional host scenario places one stock invisible INGALITE at 92,101 beside
the retained traffic-light crossing. The Rhino moves from 86.5,101.5 to 92.5,101.5
in 78 simulation updates, turning from its initial facing. Both ordinary and
lighted checks retain scenery occlusion, fresh final/no trails, raw cache bypass,
offscreen culling, partial clipping and pan return. The lighted variant also
checks current-cell brightness changes, stable house converter/indexed images
and reversible source toggles. These are native integration checks, not original
screenshots, observations or whole-frame parity.

Actual SDL passes selection/right-click, 79 samples / 78 updates, 22 occluded
samples / maximum 150 hidden pixels and brightness 1450..1512. Normal/sanitizer
ordinary and light crossings pass. The occluded PNG was visually inspected.
All 380 Python tests, 17 normal / 16 sanitizer CTests, normal/sanitizer owned
presentation on both datasets and complete owned-data test commands on both
datasets pass, including two 170-frame SDL checks each, 19 light/cache and 81
scenery/profile/export checks per dataset plus four patched-only metadata guards.
Source/diff/local-link checks and arm64 identity pass; no proprietary file is tracked.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
./run.command --crossing-light-demo
# Select the tank, then G or right-click to move. L toggles the host-placed light.
build/native/crossing-check private/official-1006-probe \
  private/unit-draw-1006/NEW-LIGHT-CHECK --light
build/native/redalert2-native --data-dir private/official-1006-probe \
  --crossing-light-smoke-test private/unit-draw-1006/NEW-LIGHT-SDL
build/tools-env/bin/python tests/compare_unit_caller_world.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/unit-draw-1006/caller-world-v1/expected.json \
  --report private/unit-draw-1006/caller-world-v1/NEW-NATIVE-REPLAY.json
# Add --native build/sanitize/unit-caller-world-vectors for sanitizer replay.
# Fresh original execution needs authorized host JIT access, a NEW --output
# directory and no --expectations. Never overwrite accepted receipts.
```

## Delivery accounting and next dependency

This closes the same moving/turning/current-cell-light drawing delivery begun
after the crossing; the intervening recovery commits were prerequisites. The
instrumented continuation started at 14:10:31 UTC on October 15 after `43dea64`;
full inherited delivery time and uninstrumented preparation costs are unavailable.
Private `caller-world-start.json`, `caller-world-attempts.json` and
`caller-world-closing.json` record scope, failures, measured costs and closing
state. No worker or new evidence-cache infrastructure was used.

Fresh driver/original/native times are **543.737/492.357/0.503 s** (CLI 543.95 s).
Final normal/sanitizer broad builds took **12.05/9.08 s**; complete owned-data
commands **18.34/17.81 s** patched/disc; sanitizer CTest **2.05 s** and Python
discovery **1.22 s**. Patched normal/sanitizer owned presentation took
**1.39/15.78 s**, disc sanitizer **16.27 s**; ordinary/light sanitizer crossing
checks are retained in private logs. Light crossing took **0.86/13.81 s** on
normal/sanitizer builds. Actual light SDL took **1.04 s**. Initial/corrected cached
replay drivers took **5.73/1.45 s**. These checks overlap and are not gameplay FPS.
New parent normal/sanitizer replays took **49.45/49.78 s** CLI, including
**0.028/0.979 s** native execution; the rest includes identity/inspection work.

Failed attempts remain recorded: an uninspected coordinate-copy leaf, fixture-only
`self.u` error and an extra native trace event were repaired before the final
pilot; the first full generation (**495.41 s**) exceeded the native span brightness
domain. Fixtures were bounded and freshly regenerated; arithmetic kernels were
not changed to fit. A warm-cache diagnostic mismatch was fixed by explicitly
selecting the supplied raw key gate along with child bypass. The headless sanitizer
build has no SDL application target; only supported targets were rebuilt. A stale
BalloonHover error expectation and stale receipt selection were corrected.
An initial documentation patch had stale heading context and applied no changes.
Python cache-path/import/default-runner/private-print issues and a missing PIL
preview converter were repaired with scoped tooling (`sips` for the preview).
Sandbox process listing was unavailable; the running tool session still supplied
completion. No original instruction, source installation, Windows setup, system
setting or shipped dependency was changed. No new executable transfer was needed.

Next bounded capability: verify the original map/tile fields consumed by ordinary
Foot depth at the retained level-ground crossing and parked cliff fixture (51,72,
elevation 4), replacing the neutral supplied field associations only where exact
initialization evidence supports them. Missing dependencies are original tile/
cell construction and contact associations, not the already recovered predicates.
Completion requires exact-patched initialization/consumer comparisons, retained
joined-drawing receipts and actual SDL checks at both scenarios. Original cache
ownership/lifetime, alternate status/ramps and outer scheduling remain separate
open work. This next boundary is not claimed implemented by the current delivery.

Only Apple Silicon macOS is tested; Windows/Linux support and original-game
full-frame observations remain unverified. Locally checked/committed work is not
independent acceptance. General pathfinding, combat, economy, AI, campaigns,
multiplayer, audio, original saves and Yuri's Revenge remain later work. The
full-game goal remains active and incomplete.
