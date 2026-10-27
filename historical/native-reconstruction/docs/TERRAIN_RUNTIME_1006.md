# Native prepared terrain, movement and Unit drawing

Current source-inventory proof is `terrain-runtime-map-v9`, refreshed in
[MEMBERSHIP_DRIVE_1006.md](MEMBERSHIP_DRIVE_1006.md) with unchanged v8 selected
outputs/inputs and both replays. The new mutable membership binding is unwired;
the runtime behavior below keeps its existing adapters and scope.

Current source-inventory proof refresh is `terrain-runtime-map-v6`, recorded in
[UNIT_MEMBERSHIP_1006.md](UNIT_MEMBERSHIP_1006.md). Selected outputs/inputs are
unchanged from v3/v4/v5; fresh original and both replays pass. The delivery evidence
below retains its original v3 date and scope.

The opt-in terrain prototype joins original-file map preparation, ordinary Drive
Process and live body/turret/barrel/shadow/depth drawing. It runs natively on Apple
Silicon macOS. This delivers the bounded level crossing, ramp movement and parked
cliff capability; complete base RA2, then Yuri's Revenge, remain incomplete.
The default flat prototype remains available for comparison.

## Try it

```sh
./build.command
# Existing privately prepared inputs are present on Ivalice.
./run.command --terrain-demo
./run.command --parked-cliff-demo
# Existing flat baseline:
./run.command --crossing-light-demo
```

In the ramp demo, left-click Rhino and press G to cross, or right-click a supported
Cell. R resets, Q/E turns the body, A/D turns the turret, S finishes the committed
track and stops, H centers, arrows pan and the wheel zooms. The cliff demo starts
at `(51.5,72.5)`, heading 49152, with most of the tank hidden by original terrain.
Unsupported/blocked orders return a status message. The camera, picking, selection,
controls, route generation and clearance are host policies. Cell-center picking
samples actual floor height but is not original tactical picking.

A legitimate supplied installation is required. The exact executable profile is
4,485,392 bytes / SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Both `private/official-1006-probe/game.exe` and the already authorized
`private/windows-baseline-20261014/game.exe` contain these bytes. Embedded 1.08,
supplied 1.006 lineage and reported no-CD modifications are separate provenance;
pristine authenticity is unverified. No new Windows action or transfer is needed.

For a fresh private setup, follow README's existing import and prepared-data steps,
including ramp geometry and pose data, then export the recovered immutable map
tables outside the supplied installation:

```sh
build/tools-env/bin/python tools/prepare_map_runtime_data.py \
  --exe private/official-1006-probe/game.exe \
  --output private/derived/ra2-1006/map-runtime-data.bin
```

The 940-byte hash-pinned artifact contains the already recovered land mappings,
resource frame entries and floor templates. SHA256:
`78b9bebc9ee7f9078619e05503fbce387b72e3ac20df84af3537e3462aee39f2`.
Runtime opens this prepared artifact; it reads no new executable ranges. The
exporter rejects another executable, writes within the source directory and
replacement of different derived data. Proprietary inputs/outputs stay ignored.

## Architecture and association boundary

`assets/PreparedTerrainMap` owns canonical Cells, the complete 262144-slot table,
primary resident TMP metadata, theater/land/overlay/resource records and finalized
selected fields. Host parsers decode supplied INIs, IsoMapPack5 and the bounded
Format80 overlay streams. Source declaration order defines type registry slots;
OverlayTypes' numeric keys have gaps. Numeric sorting or treating keys as slots
would be incorrect. Raw overlay placement, initial fields, primary image selection
and empty actor/house registries are supplied associations, not recovered startup.
No oracle commands or final records enter runtime.

The later recovered two-pass finalization runs with actual shared Cell/LAT/
passability/resource children. Lighting levels are retained at its pre-recalculation
lighting callback; the renderer owns the light/converter storage. On this owned
map the finalized levels also match those lighting levels. Only source-referenced
primary images and default tile zero are resident. There are 268 resident type
slots backed by 251 distinct TMP files; repeated filenames share source bytes.
Alternate variants/RNG selection and original loading order are not promoted.
The map has global Tags definitions but no attached CellTags; attached tags and
tubes are refused. Overlay-bearing Cells are prepared but not traversable by this
Unit and overlays are not newly rendered.

`TerrainMapView` gives each simulation, route preview and renderer its own lazy
floor/fallback state while borrowing stable canonical Cells. `PreparedDriveTerrain`
binds those records to SDL-free `GroundDriveProcess`. Height placement uses actual
SetHeight(0)/Unlimbo. Complete ordinary Process preserves fractional Z, live cell
identity and stored ramp timers. The public Drive snapshot remains the host command/
turret interface. Arrival and target lifetime, successful admission/reservation,
Mark/occupation/mission/notification effects remain adapters.

`Renderer` calls complete ordinary Unit DrawIt and the verified posed ground
entry. Body pose consumes the live stored ramps/timer/Facing; shadow pose queries
the current Cell independently. Actual floor-relative height and separate point
queries reach shadow/world composition, and actual ordinary base/Foot depth reads
prepared TMP/overlay/Cell fields. Earlier flat and nonpositive entries retain their
contracts/guards. Rocking is zero; type extent doubles contribute nothing there,
and rocking physics/association remain open. Camera, house/palettes/contact,
visibility, healthy actor fields, settled barrel pitch and successful allocation
remain supplied. Static restoration is still a full viewport host policy.

The SDL-free `ra2_scenarios` integration library joins these layers; simulation,
assets and rendering remain separate. SDL only handles the actual platform/input/
presentation loop. No general engine, emulation runtime or new dependency is added.

## Evidence

[Moving original actor through complete drawing](MOVING_UNIT_WORLD_1006.md)
already establishes 228 results / 867 complete Process ticks / 92 complete draws,
including all 21 ramps, body/current-Cell lag, positive/negative heights and
translation/pivot consumers. This milestone wires those kernels to owned files;
it does not relabel native frames as exact-original frame evidence.

`tests/compare_terrain_runtime.py` independently invokes the isolated original
later map parent with the prior owned fixture inputs and the runtime's empty
building registry. It compares the runtime's selected final Cell/light/overlay/
owner projection across all **13,515 Cells**. All **255 distinct source slices**
(map, rules, art, theater and resident TMP files) are recorded; the applicable
original fixture slices match exactly. The fixture contains extra scenery aliases,
which are not resident TMP inputs. The original's synthetic building was removed
explicitly; otherwise it assigns owner 7 to 95 walls. No expected output is
normalized to hide that difference. Current fresh proof is
`private/map-depth-1006/terrain-runtime-map-v3/`; earlier development v1 used a
nonstandard receipt envelope; v2 preceded the final replay-destination guard.
Both remain historical. Normal and sanitizer replay
must validate the standard fresh receipt, sources, inputs and native identities.
Only selected final map fields are compared here, not full startup or original
internal write order in the host association code.

Actual SDL selection/right-click and rendering pass in
`private/map-depth-1006/terrain-sdl-v2/`:

- Level crossing: 79 samples / 78 updates, 150 maximum pixels hidden by scenery
  over 22 samples, then emergence. Complete Unit caller/two light lookups, fresh
  final, bypass, four offscreen/two partial-clip checks and pan return pass.
- Fixed ramp `(65.5,26.5)` to `(69.5,26.5)`, heading 16384: 44 updates, 29 tilted
  samples, one stored/current-Cell ramp-lag sample and 23 positive-height samples.
  Z ranges 416..676 including the initial sample. No negative-height sample is
  claimed for this route. Every moving frame matches cache bypass; fresh final
  and pan return also match.
- Parked cliff: derived Z416, depth -52, gradient 2, 153 visible pixels and 886
  terrain rejections, with fresh/bypass/pan equality. Images were visually inspected.

These are native integration tests. They do not establish original input timing,
whole frames or performance parity. No new original-game observation is claimed.
Only Apple Silicon macOS is tested; development builds still use local libraries.

## Regression commands and remaining work

```sh
./test.command
PYTHONDONTWRITEBYTECODE=1 build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/native/terrain-runtime-check private/official-1006-probe
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
build/sanitize/terrain-runtime-check private/official-1006-probe
./run.command --terrain-smoke-test private/map-depth-1006/terrain-sdl-new

build/tools-env/bin/python tests/compare_terrain_runtime.py \
  --exe private/official-1006-probe/game.exe --data-dir private/official-1006-probe \
  --expectations private/map-depth-1006/terrain-runtime-map-v3/expected.json \
  --report private/map-depth-1006/terrain-runtime-map-v3/replay-new.json
# Add --native build/sanitize/terrain-runtime-check for sanitizer replay.
# Fresh original: use --output NEW_PRIVATE_DIRECTORY instead of expectations/report;
# this requires the authorized Mac host JIT research context.
```

Owned-data regression also checks blocked/unsupported order rejection, preview
actor immutability, arrival, turning, stop and center picking. Synthetic checks
reject unverified prepared artifacts and preserve sources/existing outputs on
export failure. Current totals/timings and prior receipt identities are in HANDOFF.

Development failures are retained privately: initial const-span assignment, rejecting
global Tags rather than attached CellTags, contiguous overlay-key assumptions,
missing OpenSSL include in a temporary diagnostic runner, and treating scenery
aliases as resident TMP requirements. Each was corrected before accepted evidence.
A diagnostic full-state comparison first exposed the deliberately supplied building
registry difference. The final proof executes the original with the correct empty
registry rather than editing expected final fields. No original instruction was
patched. Full inherited delivery/build times are unavailable; measured checks are
recorded separately. No worker or caching infrastructure was introduced.

Next bounded dependency: recover and join actual Unit Mark/occupation effects
used by ordinary movement on supported prepared Cells, preserving the verified
placement/height/Process/body/shadow chain. Establish a reproducible move/stop/
turn scenario and exact original state/query/write comparisons before extending
runtime admission. General pathfinding, bridges/overlay traversal, full actor/type/
house construction, damage/combat, economy/AI/campaigns/multiplayer/audio/save
compatibility and Yuri's Revenge remain open.

The existing pinned YRpp/recomp references in [REFERENCES.md](REFERENCES.md) remain
naming/research leads. No upstream code was consulted for a new behavior or
incorporated here; no new license/dependency claim is made. Supplied installations,
discs and `outpost2-native` remain untouched. No Xcode license acceptance, global
tool selection, DRM change, download, publication or public release occurred.
