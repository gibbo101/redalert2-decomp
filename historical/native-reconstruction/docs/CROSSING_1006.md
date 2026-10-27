# Supplied RA2 1.006 moving Rhino and scenery integration

October 14, 2026, following `b1ae7e7`. Milestone 20 delivers the bounded moving
Rhino/scenery crossing with the recovered patched static and dynamic callers.
Selection and a movement order pass through actual SDL events; the Rhino moves
past an original traffic light, becomes partly occluded and emerges. This is a
locally verified native integration delivery, not independent acceptance or
original whole-frame/input/scheduler parity. The full game/YR goal remains open.

## Identity and evidence authority

Only the supplied patched engine selects the new dynamic integration:
SHA256 `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`,
4,485,392 bytes, `private/official-1006-probe/game.exe`. Its hash was rechecked
against the approved private Windows copy; they remain identical. Embedded 1.08,
supplied 1.006 patch lineage and user-reported no-CD provenance remain separate
facts. Pristine authenticity is not established. The retained disc integration
and its exact-hash evidence remain separate. Runtime never executes originals.

This milestone integrates the already recovered boundaries in
[ACTOR_TRAVERSAL_1006.md](ACTOR_TRAVERSAL_1006.md),
[UNIT_VISIBILITY_1006.md](UNIT_VISIBILITY_1006.md),
[STATIC_TRAVERSAL_1006.md](STATIC_TRAVERSAL_1006.md) and
[STATIC_REDRAW_1006.md](STATIC_REDRAW_1006.md). Their original receipts and scopes
are unchanged. The pinned recomp/YRpp leads in [REFERENCES.md](REFERENCES.md)
remain references, not an oracle or runtime. No new subsystem addresses, generated
game code, upstream code or dependency were introduced.

## Runtime behavior and explicit host boundaries

The static cache rebuild retains the recovered reverse Terrain scan and drawing
gate through the static request caller's full branch. The moving Rhino now uses
the recovered five-layer forward two-pass caller, nested ordinary Unit gate and
Foot/Drive secondary getters. Its body/turret/barrel staging and shadow work run
inside the Unit gate's final drawing callback, with the caller's point and clip.
The original ordinary Unit DrawBehind branch is a no-op; extras are counted, and
the existing native selection/command UI follows afterward. No combined painter's
sort replaces the distinct static and dynamic passes.

The renderer supplies these inputs and services explicitly:

- Healthy static Terrain flags=2; one healthy Unit with zero upper allocation
  flag bits, recovered low bits=7, special state=0 and secondary index=-1. Scoped
  field recovery is not complete construction or original actor ownership.
- A copy of the registered ground layer with the single Unit appended. Static
  Terrain is skipped by the dynamic pass. Original Unit registration, movement-time
  reinsertion and general actor/layer lifetime remain open.
- Existing analytic flat camera inversion, fully visible tactical projection,
  clear scenario bit 0x1000 and a false map predicate. Fog is not enabled.
- Force=1 every display, because the host restores the complete static color/depth/
  alpha cache before drawing the Unit. Original outer frame scheduling, regional
  invalidation and surface/cache ownership remain open. Visible-cell and dirty
  lists are empty on this host's full static rebuild; queue recovery is not a
  claim that original regional scheduling is integrated.
- Foot uses the committed Drive track endpoint (`sim.drive.head`), adding the
  presentation elevation only when nonzero. The zero sentinel is preserved. This
  is distinct from the queued route's final destination; the caller discards the
  getter result, as the original does.

Public per-display telemetry reports visibility clears, Foot queries, Unit draw
callbacks, extras calls and the Unit's final visibility bit. In the visible supplied
scene those are 566 / 2 / 1 / 1 / true. This is inspection state, not a simulation
ownership or scheduler implementation. The retained disc path keeps its historical
direct vehicle draw and does not acquire patched-only traversal claims.

## Reproducible scenario and regression

`CrossingScenario` is a host fixture for `mp03t4.map`, locating `trff03` by type
and cell (89,103), rather than relying on its current vector index. The Rhino
starts at (86.5,101.5), moves to (92.5,101.5), elevation 4. A fixed camera centered
on that traffic light uses zoom 2 and a 1024x720 framebuffer. The interactive
demo starts unselected: select the tank, press G to order the crossing, and R to
reset. G and all native controls remain host adapters. Right-click orders still
work normally; the SDL regression uses left/right mouse events, not G.

The existing direct-route adapter accepts the full original map's conservative
clearance. Diagnostic rendering removes scenery from a separate asset copy only;
that copy is never used to approve a route. The native fixture reaches its endpoint
in 78 updates, producing 79 samples, 22 with scenery occlusion and a maximum of
150 hidden vehicle pixels. Entry and exit have zero scenery-hidden pixels.
These counts are native regression expectations, not a new original movement run.

The check also requires ordinary traversal/gate telemetry at every sample, final
equality with a fresh renderer (no trailing image), equality with lit/shadow caches
bypassed, four offscreen camera directions with no Unit drawing/cache builds, two
partially clipped viewport edges with fresh-render equality, and exact restoration
after camera return. Private CSV records positions, coverage and callback counts;
entry/maximum-occlusion/exit previews and a JSON summary stay ignored. The previews
were inspected as visual QA only. No original-game frame is a comparison fixture.

```sh
./build.command
./run.command --crossing-demo             # select Rhino, G to cross, R to reset
./test.command --data-dir "$PWD/private/official-1006-probe"
build/native/crossing-check private/official-1006-probe \
  private/traversal-1006/crossing/NEW-HEADLESS
build/native/redalert2-native --data-dir private/official-1006-probe \
  --crossing-smoke-test private/traversal-1006/crossing/NEW-SDL
# With README's sanitizer build:
build/sanitize/crossing-check private/official-1006-probe \
  private/traversal-1006/crossing/NEW-SANITIZER
```

The fixture refuses the retained disc profile and other map names. Existing
ordinary runs remain available on both datasets. Crossing mode is separate from
the light demo and other smoke modes. SDL checks require Mac desktop access.

## Delivery validation and accounting

Normal and ASan/UBSan headless crossing checks pass, as does the final actual SDL
crossing. Both existing 170-frame SDL regressions pass on each dataset. Normal/
sanitizer CTest, all 209 Python tests, owned presentation on both datasets/builds,
arm64 identity, source and diff audits pass. Unchanged archive/Facing families keep
their prior proof; they were not freshly executed for this integration.

All seven patched traversal/redraw suites replay **45,451 cached original results
per build** against current normal/sanitizer runners, retaining exact engine,
source, fixture and receipt checks. No fresh original execution was necessary:
the recovered kernels and fixture profiles are unchanged. Receipts and a measured
summary are in `private/traversal-1006/crossing/replays/`. Earlier fresh-generation
claims in the individual notes are not relabeled as fresh work here.

The complete promoted-data replay passes **180,573 cached original results per engine/
table pass**, with retained then source-matched inputs, on normal/sanitizer builds.
Delivery receipts are `private/migration/crossing-{patched,disc}-{normal,sanitize}/`.
The complete summary in each directory is the acceptance receipt; partial logs are
not completion evidence. Measured elapsed costs (two table passes): 194.78 s patched
normal, 194.82 s disc normal, 238.27 s patched sanitizer and 239.16 s disc sanitizer.
These repeated comparisons are not new distinct
original cases or whole-game fidelity.

The delivery inherited the committed traversal, eligibility, field/getter and
redraw recovery, plus the uncommitted Renderer integration. Full elapsed delivery
and pre-instrumentation costs are unavailable. Instrumented checks include final
normal/sanitizer crossing 2.06/17.70 s, final SDL crossing 2.37 s, traversal replays
16.76 s combined, normal/sanitizer CTest 2.41/1.94 s CLI, Python discovery 1.56 s
CLI (0.691 s tests), patched owned presentation 3.01/21.49 s and retained owned
presentation 4.42/20.74 s. Normal/sanitizer builds after adding edge checks took
6.13/4.52 s; the final test-only preview-size rebuilds are logged separately.
The first continuation build and inherited build costs are unmeasured. Concurrent replay
and checks contend; these timings are not gameplay FPS measurements.

Failed/repaired attempts: the inherited private search helper first linked a
nonexistent Homebrew zlib path, corrected to `-lz`; one source patch had stale
context and made no changes. Visual QA found the small diagnostic viewport cropped
the exit tank, so the headless fixture was changed to the actual SDL dimensions.
Its final three previews show both complete endpoints. Edge assertions were added
after the first successful SDL run, then both headless builds and SDL were rerun.
No accepted parity mismatch, sanitizer diagnostic or gameplay repair occurred.
No extra workers, cache infrastructure, Windows action or public release occurred.

## Next observable boundary

Continue toward an ordinary healthy Rhino whose drawing inputs come through the
original Unit DrawIt dispatch while moving/turning past the same scenery and
changing current-cell light. Recover its prechecks and actor/type/house/cache
associations before replacing the remaining healthy-input adapters. Completion
requires exact-patched nested caller evidence, retained surface/kernel regressions
and an actual SDL crossing/light scenario. The current final draw callback is a
bounded native composition, not recovered complete Unit DrawIt.

Original outer frame scheduling, full actor construction/ownership/lifetime,
camera inversion, fog, UI/extras, alternate terrain and animated/nonflat/status
branches remain open. General pathfinding, combat, economy, AI, campaigns,
multiplayer, audio, original saves and YR remain later work. Only Apple Silicon
macOS is tested. Supplied sources, Windows installation and Outpost 2 are untouched.
