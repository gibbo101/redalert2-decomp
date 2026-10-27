# Per-actor route, stop and deferred body commands

`src/platform/OwnedUnitOrders.hpp` adds a borrowed, SDL-free command adapter over
`OwnedUnitWorld`. It owns no simulation records and introduces no second Drive,
map or drawing state. Every command names actor0 or actor1 and changes that
actor's actual membership-bound Process state, queue and command record. Selection
is independent of these explicit command IDs. The application remains unchanged;
Unit1 in `--resident-demo` is still inspection-only.

The subsequent [scheduled-preview integration](OWNED_SCHEDULED_PREVIEW_1006.md)
records the shared both-actor schedule and warm simulation/renderer isolation.
Earlier open-preview statements below describe this command checkpoint.

## Original boundary and supplied policy

The exact supplied executable is 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 lineage and reported no-CD provenance remain
separate; pristine authenticity is unverified. The new inspection checks actual
base-binary addresses rather than assuming an offset from another executable:

| Routine | Actual address | Bounded behavior |
| --- | --- | --- |
| Drive Move_To | `0x49FE30` | Healthy actor, destination stores then coordinate-Cell lookup, nonbridge target |
| Drive Stop_Moving | `0x49FEF0` | IsTrain0, percentage cap then null destination; committed track retained |
| Drive Do_Turn | `0x4A0FD0` | Forwards to this actor's body Facing |
| Facing SetDesired | `0x4B8A30` | Existing wrapped/interrupted turn arithmetic |
| Unit ObjectType wrapper / UnitType getter | `0x6C12C0` / `0x705020` | Actual type association during stop |
| Actor guard bytes | `0x6D6DF0` / `0x6D6E00` | Actual actor byte reads during Move_To |

The original stop constant at `0x79EA48` is the binary64 value
`0.30000001192092896`, not a rounded decimal 0.3. The caller passes the immutable
`DriveData::stopScale` read by the existing hash-checked loader; the command adapter
does not add a runtime executable read. Disabled predicates remain named supplied
false services. Train propagation, bridge destinations and immobilized actors
are outside this profile. An unsupported bridge is refused after the destination
stores/query; callers must discard a preview rather than treating this low-level
command as an atomic live request.

`directRoute` is a pure prototype policy: it produces at most23 directions,
diagonals first, without queries or mutation. Replacement starts at the committed
head when driving; append starts at the host navigation target and copies only
the queue prefix before its first sentinel. Supplied destination Z, clearance,
map/domain validation and route acceptance belong to the enclosing integration.
It is not original pathfinding. Zero-distance, out-of-bounds and oversized plans
are rejected. Explicit orders validate and copy their input before replacing all24
queue words, including when the supplied span aliases the live queue. Process
retains queue tails between commands.

Stop clears the supplied queue and coordinate target without aborting a committed
track. Manual body turns stop first; a committed track defers the requested wrapped
heading. Reissuing a pending turn uses the actual body's desired heading, not the
previous pending heading. A new move clears that pending turn and manual turret
override. These are prototype command policies, not recovered input/mission rules.

`finishTick` is an explicit host scheduling operation after the supplied Process0 /
Process1 pair. It clears an arrived target before ordinary turret update and applies
a pending body Facing request afterward, once the committed track has finished.
It does not recover the original scheduler, mission completion or target lifetime.
The earlier independent turret boundary remains in
[OWNED_TURRET_WORLD_1006.md](OWNED_TURRET_WORLD_1006.md).

## Evidence and remaining gates

The new distinct-address fixture executes original Move_To, Stop_Moving and
Do_Turn on the two actual actor/Drive addresses used by complete Process and
interleaved complete drawing. It reuses only map/initial-command inputs from the
earlier private two-Process schedule, not expected actor/map/pose/cache/pixel
outputs. New command states and all subsequent original results execute afresh.
Command calls audit their inspected instructions, caller stack, callee-saved
registers, immutable code/type/vtable inputs and both actor/Drive arenas. Original
command stores are retained privately; they are not a native ordered-store proof.
Complete Process retains its selected ordered-store/query/return comparisons.
Drawing retains the shared type indexes, image, pool and final world projections.
Accepted receipts, coverage, counts and costs belong in the opening
[HANDOFF.md](HANDOFF.md).

Native checks separately cover pure direct/append/committed-head routes, limits,
alias-safe queue replacement, invalid-command isolation, independent stop/turn
state, unchanged committed motion, interrupted pending turns, turret/body ordering,
warm clones and rejected/bridge command-preview isolation. These native tests do
not establish original route or preview policy. The generic discarded-copy preview
continues to preserve typed unsupported admissions and propagate unrelated faults.

Complete scheduled command previews, sampled clearance on both actors, renderer
cache/image/pool isolation and selected-actor runtime routing remain open. Actual
SDL movement/stop/body/turret/reset/interaction acceptance still precedes Unit1
controls. Unsupported Advance6/7 aftermath, scatter and earlier route exclusions
remain refusals. Initial records, House/type/visibility, numeric and opaque timer
inputs, named services, controls, camera and scheduling remain supplied. This is
local verification, not independent acceptance or whole-frame/game parity.

## Build and reproduce

```sh
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake -S tests/owned_orders_world \
  -B build/owned-orders-world -DCMAKE_BUILD_TYPE=RelWithDebInfo \
  -DCMAKE_OSX_ARCHITECTURES=arm64 -DCMAKE_PREFIX_PATH=/opt/homebrew
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/owned-orders-world \
  --target owned-orders-world-check owned-orders-world-vectors --parallel 6
build/tools-env/bin/ctest --test-dir build/owned-orders-world --output-on-failure
# Sanitizer: use build/owned-orders-world-sanitize, Debug and -DRA2_SANITIZE=ON.

PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/unit-draw-1006/orders-new.audit.json \
  tests/compare_owned_orders_world.py \
  --exe private/official-1006-probe/game.exe \
  --native build/owned-orders-world/owned-orders-world-vectors \
  --output private/unit-draw-1006/orders-new
# Fresh original execution requires the authorized host Unicorn JIT context.
# Replay: replace --output with --expectations CURRENT_EXPECTED_JSON
# --report NEW_PRIVATE_JSON and use a new audit. Use the sanitizer runner for
# ASan/UBSan; put --uncached before the driver for the inspection-reuse control.

./build.command
./test.command
./run.command --resident-demo
```

Only Apple Silicon macOS is tested. This dedicated check project leaves the
application and earlier runners unchanged. Proprietary inputs, disassembly,
receipts, frames, environments and binaries stay ignored. No workers, Windows
actions/transfers, downloads, source-install/disc/outpost2 writes, system/Xcode/DRM
changes, publication or runtime executable-read expansion are part of this work.
Base RA2 then Yuri's Revenge remain incomplete.
