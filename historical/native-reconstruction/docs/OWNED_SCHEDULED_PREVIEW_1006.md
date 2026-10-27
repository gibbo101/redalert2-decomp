# Scheduled two-Unit movement previews

`OwnedUnitSchedule.hpp` and `OwnedUnitMovePreview.hpp` add SDL-free host adapters
over the actual records in `OwnedUnitWorld`. The subsequent [owned runtime integration](OWNED_TERRAIN_RUNTIME_1006.md) adopts
these adapters in `--owned-demo`, with selected-actor SDL acceptance. The retained
`--resident-demo` still has one commandable mover and one inspection-only Unit.
Earlier open-runtime statements below describe this preview checkpoint.
The opening [HANDOFF.md](HANDOFF.md) records accepted evidence and limitations.

The schedule validates both actors' speeds and required named services before
Process0. It executes **Process0, Process1, finishTick0, finishTick1**, with scoped
observers and a reentry guard that clears on exceptions. This is a supplied host
schedule, not recovery of the original frame scheduler. Initial poses, queues,
House/type records, numeric inputs, padding and named effects retain their earlier
bounded contracts. The original Process, Move_To, Stop_Moving, Do_Turn and turret
boundaries remain those in [OWNED_ORDERS_WORLD_1006.md](OWNED_ORDERS_WORLD_1006.md).

Preview clones the world once, binds scoped services to that copy, constructs a
bounded route, obtains destination Z through its actual floor binding, applies
the command and advances both actors with that same schedule. Bounds/domain/
scenery clearance is an owned immutable 512 by 512 byte mask; it borrows no
renderer, mutable Cell or floor callback. Quarter-Cell footprint samples at most
16 leptons apart check both actors, including the unselected actor. Actual
admission still decides terrain speed and supported resident interactions.
This sampling and the diagonal-first route remain prototype policies, not
original pathfinding or a proof of continuous collision clearance.

Acceptance requires the selected actor to exhaust its queue, finish its committed
track and reach destination XY. Only the accepted route is returned; advanced
preview actors, map, callbacks and drawing state are discarded. Typed route and
admission refusals remain distinct from blocked, not-arrived and tick-limit
results. Other exceptions propagate. Tick addition wraps through unsigned32 and
the recovered signed conversion. The bounded preview limit is 1 to 4096 ticks.

`moveOwnedUnit` previews first. On acceptance it performs the actual live floor/
order sequence only; it never commits advanced clone state or simulated time.
This is a synchronous single-threaded boundary. Binding factories must not mutate
or query the live owner or capture live mutable services. Arbitrary external
callback side effects are not transactional. A fault during accepted live command
application still propagates; the low-level command is not a general transaction.

## Evidence boundary

The exact supplied executable remains 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage and reported no-CD provenance remain distinct;
pristine authenticity is unverified. No new address, binary range, runtime
executable read, external reference code or dependency is introduced.

The authored differential fixture executes Process on both genuine original
actor/Drive addresses, then original-backed finalization, followed by interleaved
complete drawing and later Process. It compares each Process's selected ordered
stores, queries and return separately, then both actor/shared-map/command views.
Complete draws retain body/turret/barrel/shadow matrices and keys, shared cache/
image/pool and final RGB565/depth/alpha projections. Only pinned authored initial
map/route/label inputs are reused. New original results execute afresh.

Native policy checks run around warm complete drawing state. They snapshot both
actors, all24 queue words, command/turret/wait/selection, shared Cells, membership
slots/Next/lists, House/discovery/occupation, buffers, floor/fallback and logical
map associations. Source pointer identities are separately checked. Renderer
snapshots include both staging bytes, shared surface/dirty/entire image, full
pool/cursor, all four type indexes with snapshot offsets, and world color/depth/
alpha planes. Index lookups for inspection occur on diagnostic copies only.
The renderer is never passed into preview or clearance.

Checks cover replacement/append for both moving actors, deferred stop/body work
on the other actor, invalid inputs, immediate/late clearance, a late block on the
other actor's route, tick limit, an unrelated fault after both clone positions
change, and accepted live command effects without simulated ticks. Actual native
unsupported Advance6/7 are reached on isolated diagnostic owners. The zero-speed
fixture supplies a new type at construction so reclones retain it; mutating a
bound service view is not a new construction input. Excluded original Advance
aftermath is never executed. These checks establish host isolation and refusal
behavior, not original clearance, controls, scheduling or pathfinding.

## Reproduction

```sh
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake -S tests/owned_scheduled_preview \
  -B build/owned-scheduled-preview -DCMAKE_BUILD_TYPE=RelWithDebInfo \
  -DCMAKE_OSX_ARCHITECTURES=arm64 -DCMAKE_PREFIX_PATH=/opt/homebrew
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/owned-scheduled-preview \
  --target owned-scheduled-preview-check owned-scheduled-preview-vectors --parallel 6
build/tools-env/bin/ctest --test-dir build/owned-scheduled-preview --output-on-failure
# Sanitizer: repeat with build/owned-scheduled-preview-sanitize, Debug and
# -DRA2_SANITIZE=ON, then run its CTest directory.
PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  -m unittest discover -s tests -p 'test_*.py'

# Fresh original execution: authorized host Unicorn JIT, new private paths.
PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/unit-draw-1006/scheduled-new.audit.json \
  tests/compare_owned_scheduled_preview.py \
  --exe private/official-1006-probe/game.exe \
  --native build/owned-scheduled-preview/owned-scheduled-preview-vectors \
  --output private/unit-draw-1006/scheduled-new
# Replay: replace --output with --expectations CURRENT_EXPECTED_JSON
# --report NEW_PRIVATE_JSON, using a new audit. For sanitizer replay change
# --native to its runner. --uncached before the driver disables inspection reuse.
```

Next: route selected-actor runtime commands through this owner and schedule, then
actually exercise both actors' move/stop/body/turret/reset/interaction and refusal
behavior in SDL before enabling Unit1 controls. Camera, picking, layer order,
clearance and direct routes remain supplied. Unsupported Advance6/7 aftermath,
scatter and earlier excluded routes remain refusals. This is local verification;
only Apple Silicon macOS is tested. No original UI observation, full-frame parity,
independent acceptance or whole-game completion follows. Base RA2 then Yuri's
Revenge remain incomplete. No workers or Windows actions are part of this work.
