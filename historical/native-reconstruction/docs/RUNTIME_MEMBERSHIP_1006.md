# Runtime Unit membership on privately owned Cells

After `26c9174`, the opt-in terrain demo uses the recovered Unit Mark,
map/Cell membership, visibility/discovery, occupation and occupied recalculation
binding during actual ordinary Drive movement. It owns its mutable map state.
Route previews and copied simulations have independent Cells, lists, occupation,
buffers, fallback coordinates, lazy floor planes, House flags and redraw state.
The shared terrain/scenery rendering preparation remains immutable.

This completes adoption of the bounded single-Unit membership profile. Complete
base RA2 and then Yuri's Revenge remain incomplete. Original startup, full
scenario/actor lifetime, general pathfinding and whole-frame fidelity are not
claimed. Only Apple Silicon macOS has been tested. No workers were used.

## Ownership and integration

`assets/MutableUnitMap` copies prepared Cells, the canonical slot table, full
four-/ten-byte attribute buffers, fallback/floor values and resident type/land/
Wheel/resource inputs. It rebuilds every mutable pointer table. Resident TMP image
bytes stay immutable and borrowed; a shared keepalive retains their prepared owner.
Caller observation callbacks are removed from the snapshot. Native dimension,
capacity, slot and type-table refusals are explicit safety boundaries.

`platform/TerrainUnitContext` owns one actor, this map, its membership views,
terrain services and redraw state. Its callbacks bind to the stable heap-owned
actor. `Simulation` deep-clones the context on copy and retains its address on
move. Assignment replaces or transfers the complete owner. Clone copies logical
values into destination storage and retains destination callbacks/pointer tables;
unsupported Tag callbacks are refused. Supplied policies must be copy-safe and
retain their borrowed assets; the demo's policies are stateless except its
read-only numeric-table reference.

`PreparedTerrainMap` now retains the buffers and resident inputs that finalization
previously discarded. It exposes a const snapshot seed. Each terrain simulation
owns a separate mutable copy. There is no const-cast into renderer storage and no
new runtime executable read. The default earlier flat demo remains separate.

The adapter starts on-map zero with a **supplied eligibility byte 1**, applies
actual relative height and Drive Unlimbo, then calls recovered Mark(1). The prior
joined oracle deliberately supplies eligibility 7, companion byte 9 and temporary
timer padding 7; these are test inputs, not recovered constructor values. The
runtime's zero padding and other initial actor/type/House/visibility records are
also supplied. The new differential profile exercises the production context
under the earlier explicit test inputs; local integration tests separately cover
the demo's initial values and command lifecycle. It does not establish original
initialization of either profile.

Preserve old-location occupation unmark before ordered +5A0/+5A1 clearing,
shared fallback forwarding, list/Next identity, discovery/mission write order,
immediate occupied recalculation and all buffer stores. Body stored ramps and
shadow current-Cell ramps remain distinct. Fractional Z is not snapped to floor.

## Exact-original evidence

Both private supplied engines rehash equal, 4,485,392 bytes / SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`:
`private/official-1006-probe/game.exe` and the already authorized private Windows
copy `private/windows-baseline-20261014/game.exe`. Embedded 1.08, supplied 1.006
lineage and reported no-CD changes remain distinct; pristine authenticity is
unverified. No new Windows action, transfer, download, DRM or system change occurred.

`private/map-depth-1006/runtime-membership-v1/` executes the same original guests
and 84-case domain as [MEMBERSHIP_DRIVE_1006.md](MEMBERSHIP_DRIVE_1006.md), but the
native driver instantiates the production `MutableUnitMap/TerrainUnitContext`.
All **6,652 Process ticks, 782 Mark calls/recalculations, 175 eligible unmarks,
8,502 selected membership-effect stores and 13,304 body/shadow poses** match.
Normal and ASan/UBSan replays pass. The actual initialized map and native map are
independently prepared; no original final records enter native execution.

The profile includes all 21 ramps, reversing/turning, zero speed, key presence,
signed tick wrap, four caller FP modes, 13,515 owned map Cells and the parked
cliff/crossing. Its canonical pointers, state, ordered queries/selected writes,
complete buffers and lazy-floor/fallback digests retain the earlier arena,
stack/register, instruction/write and immutable-input audits. Combined inspection
remains 185 ranges / 15,025 instructions; 144 ranges / 12,132 instructions enter.
The native driver keeps mutable map values between M sequences while resetting
logical actor lists like the original fixture. Its TMP bytes remain alive in the
fixture's prepared image owner.

`membership-drive-v2/` freshly refreshes the earlier binding after the new logical
copy API changed its source identity. Commands/results/labels equal v1 and the
new production-binding suite. `terrain-runtime-map-v12/` freshly verifies all
13,515 selected prepared fields from 255 owned source slices; both replays pass.
Its command/inputs/results equal v9. Intermediate v10/v11 remain historical,
never relabeled after SDL source changes. Unaffected earlier drawing and recovery
receipts retain their own narrower scope and current identities.

The new suite executes the binding, not Simulation's command/preview copying,
complete Unit pixel drawing or the whole SDL runtime. Its inherited metadata's
runtime/startup/frame exclusion refers to those broader scopes. Existing complete
drawing proofs remain separately scoped. SDL and native integration do not turn
those isolated proofs into whole-game or whole-frame evidence.

## Native and SDL regression

`terrain-membership-check` verifies initial recovered Mark/discovery/occupation,
exactly one current Cell membership, successful and partially rejected preview
isolation, copies made during movement, copy/move assignment, stopping/turning,
old-Cell cleanup and independent fallback/lazy/House/list/buffer/redraw values.
It compares logical fields rather than host padding. Its owned-map checks also
confirm the source rendering preparation stays unchanged. `--guards` covers
positive ownership/cloning and invalid dimensions, height, buffers, table/land
inputs, noncanonical slots and unsupported Tags. Normal and sanitizer runs pass.
All 809 Python tests,59 normal and58 sanitizer CTests pass.

The actual SDL terrain smoke now sends selection, right-click/G, S, Q and D events
through the app's event queue. It checks live membership every update, stops before
the route endpoint after finishing the active track, and waits for both turns to
settle. Crossing remains78 updates. Ramp remains44 updates /29 tilted /one lag /
23 positive-height samples, Z416..676. Parked cliff remains Z416 /depth-52 /
gradient2 /153 visible /886 rejected. Both170-frame legacy SDL regressions pass.
Ramp/cliff captures were visually inspected. This verifies native SDL integration;
OS pointer/keyboard automation and original-game frame measurements were not completed.

Current app is arm64, SHA256
`f1a5a2921b14ec6b43279e2f9eb8c59a9b49c9faf7a169ccd8cc29a6e805011e`.
Private reports/captures and timing logs use the `runtime-membership-*` prefix.
The closing audit pins all current source/runner/receipt/input hashes, unchanged
prior records, Python syntax, local links and source privacy. Development builds
still link local Homebrew dependencies; this is not a self-contained app bundle.

## Limitations and next work

Domain remains one nonbridge Unit on otherwise actor-empty membership lists,
stock single-Cell foundation, null Tag/loading1, supplied current human House/
visibility/threshold/type state and overlay-free traversed/recalculated Cells.
Static scenery still has its separate conservative clearance exclusions; this
does not recover mixed Unit/Terrain list construction or general collision.
Host parsers, raw overlay placement, primary TMP selection, initial buffers,
heap/atexit/ownership, successful admission/reservation, missions/targets and the
direct route/clearance/picking/camera/control/presentation adapters remain explicit.
The oracle's A5-seeded buffers and runtime's retained geometry/zeroed buffer inputs
do not establish original full startup memory. Unsupported routes stay refused.

Next replace supplied successful movement admission/reservation with original
query/state/write evidence on the shared map, including occupied Unit Cells,
before expanding routes or multiple actors. Actor/type/House construction,
bridges, full fog/lifecycle, pathfinding, combat, economy, AI, campaigns,
multiplayer, audio, original saves and YR remain open. No independent acceptance
or whole-game completion is claimed.

Pinned YRpp/recomp references and license boundaries in [REFERENCES.md](REFERENCES.md)
are unchanged. No upstream/header/generated/lifted code, proprietary content,
extracted table or new dependency is incorporated. Supplied installations/discs,
`outpost2-native`, system tools and Xcode settings remain untouched.

## Reproduce

```sh
./build.command
./test.command
./run.command --terrain-demo
./run.command --parked-cliff-demo
build/native/terrain-membership-check private/official-1006-probe
build/sanitize/terrain-membership-check private/official-1006-probe
build/native/terrain-runtime-check private/official-1006-probe
./run.command --terrain-smoke-test private/map-depth-1006/my-membership-sdl
build/tools-env/bin/python -B tests/compare_runtime_membership.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/runtime-membership-v1/expected.json \
  --report private/map-depth-1006/runtime-membership-v1/my-native-replay.json
# For ASan/UBSan, also pass --native build/sanitize/runtime-membership-vectors
# and a separate --report destination. README documents the sanitizer build.
# Fresh isolated-original proof: omit --expectations/--report and use a NEW
# private --output directory; use the authorized Mac host Unicorn JIT context.
```

Select Rhino, G crosses the fixed ramp, Q/E turns the body, A/D turns the turret,
S finishes the active track and stops, R resets. Right-click requests a bounded
direct route; unsupported/blocked routes fail without modifying live simulation
state. These controls remain host adapters.
