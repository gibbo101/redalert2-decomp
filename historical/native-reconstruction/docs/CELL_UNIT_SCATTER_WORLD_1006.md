# Cell dispatch with actual Unit Scatter and shared world queries

The subsequent [zero-point nearby join](CELL_NEARBY_SCATTER_1006.md) reuses this
Cell composition with the verified nearby Unit entry. Its separate facade does
not widen this legacy nonzero entry. Refreshed `cell-unit-scatter-world-v8` retains
all 165 prior commands/labels/outputs and 10 native guards per mode. Earlier
zero-point-unjoined statements below describe the original checkpoint; the
Advance6/Process/owned-world/preview/drawing/SDL and runtime gates remain open.

`CellUnitScatterWorld.hpp` joins the complete Cell resident snapshot/dispatch
policy to actual nonzero-point Unit Scatter, world queries, moving admission and
Cell destination effects. It borrows distinct Unit/Drive/mission/target/reference
records, primary/elevated heads, Next, owner, veterancy and shared rule/type/House
inputs. This is a **separate unwired entry**. It installs destinations without
pathfinding or advancing Units. The two-Rhino `--owned-demo` and all runtime
Scatter/Advance6 refusals remain. Base RA2 first, then Yuri's Revenge remain
incomplete.

## Original target and ownership

The exact private executable is 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 lineage and reported no-CD provenance remain
separate; pristine authenticity is unverified. The existing local file suffices;
the authorized Windows transfer was unnecessary.

The unchanged Cell root is `476920..476ABD` exclusive, with `ret 10h` at
`476ABA`. Its actual Unit +15C dispatch reaches complete `7072D0..7078E7` and
returns to `476A89`; this is no longer a replacement member callback. The existing
coordinate/layer/floor/map/permission/level/admission/projection/destination
children execute unchanged. The moving-resident extension also executes actual
Facing, bearing, coordinate/distance and ordinary Drive+A4 children. Ranges and
dispatch are pinned by `tools/verify_cell_unit_scatter_world.py`, composing the
three existing exact-base verifiers. Inspected ranges are not a claim that every
branch or instruction executed.

The native binding rejects non-Unit members, missing actors, mirrored actor/
Drive/reference owners, mismatched mission associations and split map/floor/global
owners. Binding performs no map/floor queries. A local structural view borrows
heads and Next; it does not copy a settled resident or mutate the original view's
callbacks. Unit-specific extras and command records remain separate.

Refresh admission motion projections **only at actual admission consumption**,
using each live actor's position, body, destination, head, queue head, track and
index. Earlier dispatch can install a destination or clear queue word 0 before a
later dispatch queries that resident. Preserve those writes. A nonnull Cell
target is explicitly represented as a non-actor identity (`-2`); it must neither
be hidden as null nor alias an actor ID in mission 7's equality test. Initial
eligibility/short-track bytes are explicitly borrowed supplied inputs. The
projection is not a production owned-world association or an original store.

Preserve elite prepass then head reload, separate primary E4/elevated E8 heads,
snapshot member order, capacity+10 and low-byte growth outcomes, live Next after
failed growth, late eligibility and ignoreDestination rather than ignoreMission.
Keep per-actor target/destination/queue/timer/reference state, full RNG and shared
fallback/lazy floor cache. Mission 7's Cell branch retains all 24 queue words;
ordinary destination clears only word 0. Scoped world observers restore on
returns and refusals. Unsupported calls may have changed a supported prefix;
future previews must discard the complete call.

## Evidence and remaining boundaries

Canonical `private/map-depth-1006/cell-unit-scatter-world-v6/` matches 165
sequences / 305 complete original Cell calls / 788 nested Unit Scatter calls in
normal/sanitizer/uncached replay. Actual admission returns 0/2/6/7 occur
732/128/152/40 times, distance returns 64 times and pending-switch true/false 8/2
times. All five actor IDs and all 21 ramps execute; 2,754 distinct instructions
execute. Ten native ownership/refusal checks pass per mode. Fresh parent Cell v5
and world v5 preserve their complete v1 projections. The closing 182-record
inventory and full regression/measurement/repair details are in HANDOFF.
The original guest keeps five distinct Unit/type/Drive addresses and ten Cell
identities, including one fallback. Compare complete logged dispatch/query/return
streams, selected ordered stores, all actors' command/queue/timer/reference state,
retained movement, full RNG, cache/fallback, Next and veterancy. Whole actor/type/
House/Cell/RNG arenas and the separate snapshot heap are guarded; code/tables/
slots/globals and caller registers/stack/canaries are protected. No original
instructions are modified. Atomic shims at unchanged import targets perform the
actual counter increments/decrements; original heap/API execution is not claimed.

Initial records, Cell membership/occupation, raw actor/type/House/rules/registry/
mission-control/speed/height/floor-template associations and skipped-coordinate
timer scratch remain supplied. Candidate lists are authored diagnostic inputs,
not observed original gameplay or complete construction. Heap growth/disposal
remain named supplied services; original allocation is not recovered. Native
ownership/refusal checks are integration safeguards, not original failure or
concurrency evidence. Native admission projection writes are not a claim about
native machine-store order.

Zero-point pathfinder, Building Scatter, mission16/active Object destination
interaction, owned nonnull vector disposal, bridge-adjusted commands, special
moving descriptors, entered promoted admission ability17 and earlier special
profiles remain unsupported. Cell ability3/promotion is separate from that
admission ability; the latter is refused at actual consumption before a supplied
false can be used. Mission7/null
in the destination extension remains inspected composition, not an original case
executed by these nonnull Scatter fixtures. No Advance6, complete Process,
production mutable membership, full discarded preview, drawing or SDL Scatter
join is established here. Initial construction, controls, routes, clearance and
scheduling remain supplied. No startup/frame/whole-game claim follows. Only Apple
Silicon macOS is tested; local verification is not independent acceptance.

## Build and verify

```sh
./build.command
./run.command --owned-demo
./test.command
PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  -m unittest discover -s tests -p 'test_*.py'

env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake -S tests/cell_unit_scatter_world \
  -B build/cell-unit-scatter-world -DCMAKE_BUILD_TYPE=RelWithDebInfo \
  -DCMAKE_OSX_ARCHITECTURES=arm64
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/cell-unit-scatter-world --parallel 6
build/cell-unit-scatter-world/cell-unit-scatter-world-vectors --guards
# Sanitizer: build/cell-unit-scatter-world-sanitize, Debug, -DRA2_SANITIZE=ON.

# Fresh original execution requires the authorized host Unicorn JIT context.
# Always choose new private output/audit paths; never rerun closed finalizers.
PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/map-depth-1006/cell-unit-scatter-new-audit.json \
  tests/compare_cell_unit_scatter_world.py \
  --exe private/official-1006-probe/game.exe \
  --native build/cell-unit-scatter-world/cell-unit-scatter-world-vectors \
  --output private/map-depth-1006/cell-unit-scatter-new
```

Replay the canonical private expectations without original execution:

```sh
PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/map-depth-1006/cell-unit-scatter-try-audit.json \
  tests/compare_cell_unit_scatter_world.py \
  --exe private/official-1006-probe/game.exe \
  --native build/cell-unit-scatter-world/cell-unit-scatter-world-vectors \
  --expectations private/map-depth-1006/cell-unit-scatter-world-v6/expected.json \
  --report private/map-depth-1006/cell-unit-scatter-try.json
```
 Use the sanitizer runner for its
replay, and `--uncached` before the driver for the inspection-reuse control.
Prepared direction/render data defaults remain under `private/derived/ra2-1006/`;
all executable reads by this runner are research-only. The application has no new
executable reads or dependency.

Next inspect and join the actual Advance6 call arguments and required nonzero/
zero-point and mission branches, then complete Process, production owned actors/
mutable map, full discarded previews and drawing/SDL acceptance. Keep every
runtime refusal until those joins pass. General pathfinding, combat, economy, AI,
campaigns, multiplayer, audio, original saves and YR remain open. No new upstream
code/header/generated/lifted output, extracted table or dependency is incorporated.
Private originals/assets/research/evidence/binaries remain ignored and unshipped.
Installations/discs and outpost2 remain read-only. No workers, Windows actions/
transfers, downloads, publication or system/Xcode/DRM changes occur.
