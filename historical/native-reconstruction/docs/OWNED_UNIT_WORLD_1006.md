# Owned movement and interleaved two-Unit world drawing

This milestone joins the production mutable map and actual resident membership
to complete posed Unit drawing. `OwnedUnitDrawingMap` borrows the movement owner's
canonical Cells, lazy floor state and membership fallback callback. Binding makes
no queries. Coordinate and attribute roots remain separate; missing owner/actor
associations are refused. Immutable renderer preparation and preview clones stay
independent. `OwnedUnitDrawScene` passes explicit actor references from platform
to render without introducing a render-to-platform dependency.

The fresh joint proof has **303 results / 210 original Process ticks / 78 complete
draws**. Actual coverage includes four stored-body/current-Cell ramp-lag draws,
two positive / four negative-height draws and both occupied-target retry paths.
These actor poses produce no cross-actor cache hit; the freshly replayed broader
shared-world and staging suites retain that coverage. Full shared cache state is
still compared after every draw. Receipts, replays and delivery checks are in
[HANDOFF.md](HANDOFF.md).

The opt-in `--resident-demo` supplies two allied HTNK actors on `mp03t4.map`: a
commandable mover at (86.5,101.5) and an inspection-only parked Unit at
(90.5,101.5). The parked Unit has a separately supplied turret Facing. Its actual
height/Unlimbo/initial Mark run before resident admission is enabled. Both actors
enter the existing dynamic traversal and complete drawing roots with distinct
resources, visibility records, staging bytes and registry IDs. They share the
type's four indexes and global staging/pool. No actor1-as-actor0 execution or
whole drawing-state copy substitutes for identity.

## Exact engine and reference boundary

The two private engine files are 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 lineage and reported no-CD provenance remain
distinct; pristine authenticity is unverified. The previously authorized Windows
copy was already present and matches. No new Windows action or transfer occurs.

The existing recomp snapshot labeled
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439`, `docs/voxels.md`, and YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88`, TechnoClass cache declarations, are
ownership leads. Hypothesis: live Process and both draws must retain the same
Cells, House, lists, floor/fallback and shared cache owners across phase changes.
Exact base execution decides this profile. Retained recomp MIT excludes lifted/
game-derived output and still contains The Movies wording; no YRpp license file
was found. No upstream/header/generated/lifted code, original table or dependency
is incorporated. See [REFERENCES.md](REFERENCES.md).

## Joint differential contract

`original_owned_unit_world.py` attaches service bookkeeping and disjoint fixture
storage to the existing graphics guest. It never constructs another `Uc` or
transfers final actor/map records. Units remain at `0x1100000` and `0x4100000`,
with separate Drives and a common supplied type. Actual map finalization,
height/Unlimbo/Mark, resident admission and complete ordinary Process run before
interleaved complete draws and later Process calls. The command protocol requires
fresh preparation, reset and initialization in that order. Drawing never resets
location, body Facing, stored ramps or House associations.

Every initialization, Process and draw compares both actors' supported state,
including destinations/heads, body and turret Facings, six ramp timer words,
all 24 route entries, separate retry words, Mark/Next/discovery and mission state.
Shared Cell fields, lists, occupation, visibility words, full attribute buffers,
foundation/House/redraw and lazy floor state are compared. Complete drawing retains
the earlier ordered caller stores, exact body/part/shadow matrices and keys,
normalized pool/index/staging state, ordered query hashes and world/shadow pixels.
Code, immutable inputs, allowed writes, actor/Drive arenas, heap/pool and caller
register/stack boundaries are audited. Initial records are supplied once; actual
phase effects are retained.

Preserve old-location unmark and ordered eligibility clears, whole occupation
assignments, shared Next/fallback identity, retained queue tails and distinct
result-6 retry padding. Body pose uses stored ramps; shadow uses the current
Cell. Retain fractional Z, independent height/point queries, cold turret/barrel
pivots, warm matrix forwarding and saved pre-shadow cleanup. Mutable-owner
renderer telemetry observes consumer queries rather than warming floor/fallback
state in advance.

The bounded workflows cover first/second occupied-target retry, empty movement,
ramp entry/exit, stock crossing and parked cliff, with cold/warm interleaved
draws. Coverage counts and accepted receipt locations belong in
[HANDOFF.md](HANDOFF.md); exploratory pilots are separate from acceptance.

## Supplied behavior and limitations

Initial actor/type/House/contact/visibility associations, settled parked state,
turret and barrel pitch, route/speed inputs, retry padding, status/eligible-mover
and drawing House/visibility predicates, converter selection, and named
notification/mission/pathfinder/atexit services remain supplied. The empty contact
vector must have valid storage even with count zero;
drawing dereferences its first-slot association. The actual flag getters remain
original children. The shared type's actual UnitType kind getter also executes
through the stock speed caller; its exact leaf, caller association, unchanged
bytes and return value 40 are checked. Earlier movement fixtures keep their supplied
kind-service scope. Drawing preserves the actual membership House rather than
replacing it with the older graphics fixture's diagnostic House.

Host direct routing, clearance preview, picking, selection, camera, target lifetime,
layer ordering and frame scheduling remain adapters. Selecting parked clears the
mover's command selection; right-click/G/Q/E/A/D/S must never silently command
the mover while parked is selected. Parked movement is deliberately unavailable.
Unsupported moving/rotating residents, nonzero Advance admission, scatter,
bridges/overlays/crushing and other earlier refusals remain. There is no original
startup/construction, complete two-Unit behavior, full-frame, general pathfinding
or whole-game claim. Base RA2 and then Yuri's Revenge remain incomplete. Only
Apple Silicon macOS is tested.

## Build, try and verify

```sh
./build.command
./run.command --resident-demo
# Left-click either Unit. Parked selection is inspection only.
# Select mover: G moves to (88.5,101.5); right-click parked tests refusal.
# Q/E body, A/D turret, S finish active track then stop, R reset.

./test.command
build/tools-env/bin/python -B -m unittest discover -s tests -p 'test_*.py'
build/native/terrain-resident-check --guards
build/native/terrain-resident-check private/official-1006-probe
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
build/sanitize/terrain-resident-check private/official-1006-probe

# Fresh original execution: authorized host Unicorn JIT context, new private dir.
build/tools-env/bin/python -B tests/compare_owned_unit_world.py \
  --exe private/official-1006-probe/game.exe \
  --output private/unit-draw-1006/owned-unit-world-new
# Replay: --expectations CURRENT_EXPECTED_JSON --report NEW_PRIVATE_JSON
# Sanitizer replay: add --native build/sanitize/owned-unit-world-vectors
./run.command --resident-smoke-test private/unit-draw-1006/resident-sdl-new
./run.command --terrain-smoke-test private/unit-draw-1006/terrain-sdl-new
```

The comparison driver's executable read is research-only. Runtime executable
reads remain limited to the previously approved hash-checked track data.
SDL checks inject events through the actual application and save native frames;
they are neither original-game observations nor OS-level pointer acceptance.
Native clone/error/ownership policies are tested host behavior, not recovered
original failure semantics. Source installations/discs and outpost2-native remain
read-only; proprietary inputs, receipts and frames stay ignored. No workers,
downloads, system/Xcode/DRM changes or publication.
