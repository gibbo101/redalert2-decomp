# Warm discarded Boot Camp world previews

The bounded discarded Walk arrival preview now starts from a complete warm host
world instead of reconstructing only an initialized player GI. It retains moved
placement, all five GI records, actual primary/elevated resident heads, Building
owners, map buffers/floor/fallback, visibility, House and mission/Tag/deferred
state. Live sight/arrival scheduling and Objective1 remain disabled.

## Ownership adapter

`BootCampWalkWorld::clone()` makes independent mutable owners and binds the same
`PreparedInfantryWalk` movement kernel against them. `bindWorld` is shared with
startup; only startup inserts initial Building heads and marks/occupies GIs.
Cloning never reinserts or remarks a warm actor. The existing mission clone is
constructed before movement borrows its Houses and Building records. All actor,
House, type, registry, random, foundation, scratch, sight and position values are
retained, including all24 route words and the actual frame/retry/wait state.

Mutable map Cells, floor planes/lazy flags, fallback, tables and buffers are
independent. Cell targets are remapped to clone Cells. The four supplied weapon
identities are rebound to their clone slots. Immutable prepared terrain/image
backing remains shared with explicit lifetime ownership; immutable GameAssets,
mission and Ini inputs remain borrowed and must outlive both world owners.
Numeric services are freshly bound to immutable assets rather than copied from
the source. Other movement, resident and discovery callbacks capture the clone.
The clone stays at a stable address behind a unique pointer.

`BootCampVisibilityWorld::clone` copies warm visibility values/startup tables,
House values, counters and fallback state, rebuilding its pointer table and
callbacks against the new map/mission. Each visibility140 reference borrows its
clone terrain flags word, including fallback. Binding makes no source map/floor
or resident query and does not warm the source's lazy state.

Split source table/slot/attribute associations and external map observers refuse;
the snapshot does not silently canonicalize a different source graph. Active
Walk dispatch, external effect/Team/position pointers and foreign Cell/weapon
identities refuse. The mission clone retains its own in-progress-dispatch,
external-observer and opaque-radio-interface refusals. Existing algorithm
refusals remain. This is the bounded ordinary Day1 owner, not a general game
serialization or arbitrary-world clone.

`composeUpdatePositionPreviewSequence` now uses this clone. The selected actor
runs through the existing actual Process/selected-head notification and composed
position/sight/discovery algorithms, retaining the supplied selected-actor preview
schedule and4096-call/1..16-notification bounds. Returned Cell identities are
translated back to source identities; no pointer into the discarded world escapes.
Requests and deferred counts are returned as diagnostics, not committed effects.
Success, unmet-notification bounds and ownership refusals discard the clone;
no preview floor, visibility, actor or mission writes are committed.

The previous initialized-tick/position/visibility/House/head/Building guards are
replaced only by this verified warm composition. Unsupported algorithm paths
are not widened. Ordinary play still uses its prior supplied arrival services;
this checkpoint does not turn discovery on in play.

## Checks and evidence limits

The private-data owner check retains all prior initialized outputs: first/later
selected-head arrivals at Process26/52, discovery1/0 and position Cell queries3/2.
New checks cover warm active sight after7 Process steps (19 remaining calls),
changed Building flags, moved placement/heads, later orders and warm fallback.
They retain distinct GI/target/Cell/buffer ownership and visibility140 references.
Clones continue after destroying source owners, before and after queued mission
cleanup. Repeated cloning after drain preserves discovery and Tag lifetime.

A later ordinary route approaches the objective Buildings. The discarded actual
arrival sight reaches Building discovery and Tag/actions, yielding one text
request, two deferred deletions and zero Tag instances. Full live actor/map/
visibility/Houses/Building snapshots and public mission state remain unchanged.
These are native composition observations; they are not an observation of the
original game or a newly joined original instruction proof of that whole chain.

Source isolation checks observe stored records, full route/occupation/head/floor/
buffer state, backing pointers and visibility counters without invoking consumer
queries. Test-only friendship exposes hidden host records for source-mutation
snapshots. Trivially copyable host object representations are used only to detect
same-source mutation, never as portable serialization, original object layout,
or cross-address clone-value evidence. Clone continuation separately verifies
logical outputs and identities. External Team/map observer and split-map refusals,
and exhaustion after two arrivals while requesting three, preserve source state.

The owner check warms a real map/scenery Renderer, verifies unchanged pixels,
backing/camera/cache counters during a discarded preview, and verifies redraw
output afterward. The actual SDL smoke now also invokes a discarded warm arrival
while ordinary selection, RMB movement and Space have paused a committed head.
At source tick2, the preview took25 more Process calls and entered one GI discovery
in its clone. Live position/destination/queue/time, map-query and text-request
counts, framebuffer values/backing and camera were retained. Ordinary SDL input
then completed the same106-tick movement/pause/refusal/Stop/repeated-order/
deselection baseline. No live sight, objective or action was enabled. This tests
the current Boot Camp map/scenery/temporary sprite presentation, not original GI
drawing or a different voxel-world renderer.

Actual SDL receipt and inspected arrival image:
`private/boot-camp-20261018/warm-world-sdl-a1/`. The receipt retains
`original_fidelity_from_this_smoke:false` and `objectives_enabled:false`.

Full normal/sanitizer builds pass, along with116 normal/115 sanitizer CTests,
1,353 Python tests and both final private-data owner checks. All9 affected proof
families retain4,350 old sequences per rebuilt runner, zero misses:360 position,
80 sight,128 mask,192 change,48 Walk/position,1600 admission,92 Walk journeys,
1034 Building coordinates and816 Building discovery. These are guarded expectation
replays, not fresh original execution. Existing canonical expectations and their
uncached controls retain their identities/scopes. No whole-inventory refresh,
original-execution cache or closed finalizer ran; no new recovered algorithm or
runtime executable read was added.

The executable remains supplied base `private/official-1006-probe/game.exe`,
4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Exact original proof scopes remain in
[resident/coordinate recovery](BOOT_CAMP_RESIDENT_OWNERS_1006.md),
[Building discovery](BUILDING_DISCOVERY_1006.md) and
[Walk/position recovery](WALK_UPDATE_POSITION_JOIN_1006.md).

Private files under `private/boot-camp-20261018/`:

- `warm-world-build-{native,sanitize}-a3.log`: final full builds.
- `warm-world-{normal,sanitize}-owner-a1.log`: final owner checks.
- `warm-world-{native,sanitize}-ctest-a1.log`, `warm-world-python-a1.log`.
- `warm-world-FAMILY-{native,sanitize}-a1.json` and `.audit.json`:9 replay families.
- `warm-world-replays-{native,sanitize}-a1.log`: complete replay results.
- `warm-world-replay-commands-a1.json`: exact guarded command manifest.
- `warm-world-receipt-a1.json`: local source/runner/log/report hashes.

Local verification is not independent acceptance or whole-game/frame fidelity.
Under concurrent checks, final normal/sanitizer owners took7.41/12.00s elapsed;
CTest suites reported4.95/11.41s; Python29.203s (29.97s command elapsed).
The9-family replay batches took24.90/26.59s elapsed; SDL5.06s. Builds, host approval,
clone-only overhead and manual review/repair costs were not separately measured.
Development corrected a snapshot-helper compile error and missing scenery setup
in the new renderer test. An earlier test invocation after the failed build ran
the old runner and its obsolete initialized-only expectation; it is not a final
receipt. Final owners/builds and guarded replays above use the final sources.
No caching was added.

## Reproduce and continue

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
./test.command
build/native/boot-camp-walk-check private/official-1006-probe
DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/sanitize/boot-camp-walk-check private/official-1006-probe

env PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/warm-next-coordinate.audit.json \
  tests/compare_building_coordinates.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/building-coordinates-vectors \
  --expectations private/boot-camp-20261018/building-coordinate-fresh-a2/expected.json \
  --report private/warm-next-coordinate.json

./run.command --boot-camp-walk
./run.command --boot-camp-walk-smoke-test private/NEW-DIRECTORY
```

Use fresh report/audit paths. The exact18 commands used for all affected replays
are in the private command manifest; they preserve the prior driver/executable/
input/expectation arguments, identify rebuilt runners and use new audits/reports.
The neighboring recovery notes retain exact original-generation commands and
original receipt scopes. No new original execution was needed for this host
ownership adapter.

Next verify required entered original caller/effect chains for ordinary arrival
and resident discovery. Text/localization/display, audio playback, alliance,
reveal and Team creation requests still need their real effects. Those dependencies
and ordinary SDL discovery acceptance still precede live arrival/sight scheduling
and Objective1 completion. Both full games remain incomplete and the goal stays
active. No workers, Windows actions, transfers, downloads, public/recomp code,
dependencies or system/Xcode/DRM changes were used.
