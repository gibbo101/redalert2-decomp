# Actor floor-height and Drive ramp state writers

October 15, 2026, after `0bce269`. **1,696 fresh exact-engine results** and normal
and ASan/UBSan replays pass. New SDL-free `ActorGroundState` functions recover
Object's relative-height setter, Drive's initial ramp assignment and the changed-ramp
prefix of Process. Actual original Cell/map/floor children execute together. These
are state writers, not proof of which complete placement/movement callers use them.
The helpers remain unwired; the existing playable baseline and all runtime guards
remain unchanged. Complete native base RA2 then Yuri's Revenge remain incomplete.

## Identity and reference hypothesis

Both supplied engines were rehashed: `private/official-1006-probe/game.exe` and
`private/windows-baseline-20261014/game.exe`, 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Fresh execution uses the first; equality of the already-approved Windows copy
is an identity check, not separate execution. Embedded 1.08, supplied 1.006 lineage
and reported no-CD modifications remain distinct; pristine authenticity is unverified.
No new Windows action, transfer, installation/disc write, download or system change.

Consulted [REFERENCES.md](REFERENCES.md), YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` `ObjectClass.h`, `FootClass.h`,
`LocomotionClass.h` and `DriveLocomotionClass.h`, and recomp snapshot
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` `docs/voxels.md` Shadows / LICENSE.
Hypothesis: terrain-floor reads and stored ramp transitions are distinct actor
inputs; neither follows merely from a correct shadow matrix. Base inspection and
execution establish the behavior below; YR declarations and recomp replacement
presentation remain leads. No YRpp license file was found; recomp's MIT grant
excludes lifted/generated game code and its stale The Movies wording remains
recorded. No upstream/header/generated/lifted code or extracted data was incorporated.
No dependency or THIRD_PARTY.md change.

## Inspected and executed boundary

[verify_actor_ground_state.py](../tools/verify_actor_ground_state.py) pins six
complete added ranges / 156 instructions, plus the prior floor family. It inspects
the complete 493-instruction Process parent to establish aligned prefix boundaries;
**only its first 30 instructions, ending before `0x4A064A`, execute here**.

| Root | Verified execution |
| --- | --- |
| `0x5D4860..0x5D4911` | Complete Object relative-height setter |
| `0x49FC30..0x49FC65` | Complete Drive Force_New_Slope |
| `0x4A05C0..0x4A05E5` | Complete Drive Unlimbo wrapper |
| `0x5D51E0..0x5D5237` | Complete Object current-Cell getter, two actual lookups |
| `0x548000..0x548068` | Complete full-coordinate map lookup |
| `0x463F80..0x463F94` | Complete timer constructor |
| `0x4A05F0..0x4A064A` | Scoped Process ramp-change prefix; suffix excluded |

Actual Unit relative-height/current-Cell/Mark and Drive Unlimbo/Force/Process
vtable slots are pinned. Original map floor `0x55A280`, Cell floor `0x4706C0`
and FTOL `0x77F110` execute without numerical stubs. The fixture supplies level
height 104 and the original static plane template; it does not execute stock
numeric startup here. Earlier stock-geometry evidence stays separate.

## Preserved behavior

[ActorGroundState.hpp](../src/sim/ActorGroundState.hpp) and
[ActorGroundState.cpp](../src/sim/ActorGroundState.cpp) preserve:

- Relative SetHeight saves the requested signed height, adds bridge height with
  low-dword wrap for **any nonzero bridge byte**, then tests actor byte `+0x74`.
  A nonzero byte calls Mark(0) before copying the actor's current coordinates.
  Actual map/floor lookup supplies Z; wrapped floor-plus-offset is stored at
  `+0x90` before Mark(1). The unmarked path omits both Mark calls. Mark's result
  is ignored. A supplied Mark service can change coordinates or flags; the bridge
  addition remains based on the earlier byte, and the branch still calls Mark(1).
- The current-Cell getter copies coordinates and looks up the map **twice**,
  discarding the first pointer. It copies coordinates again for the second lookup.
  Test bindings preserve the queries and test a supplied mutation between them.
  No coordinate-word truncation or independent X/Y bounds replaces the established
  full signed divide/wrapped combined index/shared fallback behavior.
- Drive Unlimbo obtains the current Cell's unsigned ramp byte, then dispatches
  actual Force_New_Slope. Force writes previous ramp, then current ramp, then
  timer start, copied padding, remaining zero and duration zero. Direct Force
  retains the entire signed input; it does not clamp to valid rendering ramps.
- Process first gets the current Cell and its ramp. Equality performs **no ramp
  or timer writes**. A change writes old current to previous, writes new current,
  constructs a timer with the supplied current tick and remaining 3, then copies
  start/padding/remaining and stores duration 3. Timer start -1 remains a possible
  wrapped clock value; it is not silently repaired. The rest of Process is excluded.

The copied timer padding word is **uninitialized by the original timer constructor**.
Native makes it an explicit opaque fixture input. Original Force receives it at
its child-entry scratch-stack boundary; Process's temporary receives it at prefix
entry. This is supplied stack state, not recovered initialization or evidence that
padding has a gameplay role. The nested getter overwrites old stack slots, so it
would be incorrect to seed Force's padding only before the outer Unlimbo call.
Original instructions remain unchanged. Actual start/remaining/duration semantics
are compared separately from that supplied word.

Store observers are read-only. Selected mutable Mark/between-lookup fixtures test
ordering, not arbitrary aliasing or arbitrary service mutation. Actual Mark effects,
actor/locomotor/map construction, startup, heap/ownership and the original caller
that requests a given height remain supplied/open. Supported floor ramps remain
0..20; byte-only ramp state writers can retain 0..255 and direct Force any int32.
That does not enable unsupported render/movement profiles.

## Evidence, commands and limits

Receipts: `private/map-depth-1006/actor-ground-state-v1/`. Cases cover every floor
ramp; signed levels; zero/nonzero byte gates; extreme wrapped height additions;
same/changed ramps; signed ticks and retained timer fields; direct Force inputs;
map aliases/fallback; supplied Mark and getter mutations; and four incoming native
FP modes with restoration. Compare ordered service/scalar events, complete selected
actor/ramp/timer state, lazy floor state and fallback coordinates.

Actual execution: **906 floor/height setters, 1,278 current-Cell getters / 2,556 map
lookups, 545 Force calls, 429 Unlimbo wrappers, 831 timer constructors and 849
Process prefixes**. There are 1,451 audited complete root calls and **9,162 actual
scalar state stores**; 953 separately counted supplied service/scratch scalar writes
are not recovered original writes. Complete roots guard return address, caller tail,
ESP and callee-saved registers; prefix checks its exact endpoint, prologue stack and
saved registers. Execution ranges, image writes, immutable map/Cell/type-table inputs,
entire arena canaries and fallback nonselected bytes are guarded. Floor lazy-state
final bytes are compared; their full ordered native stores remain the earlier limit.
Twelve native malformed/domain refusals are separate from original parity.

Fresh CLI/original-generation/native times: **3.327 / 2.531 / 0.099 s**.
Normal replay CLI/native: **0.916 / 0.135 s**. Sanitizer timings and closing checks
are in [HANDOFF.md](HANDOFF.md). The first comparison rejected the incorrectly
seeded outer-call padding; the corrected child-boundary fixture passes fresh.
No failed expectations were accepted or relabeled. An initial inspection range
ended two bytes early and was corrected to the actual final return boundary.

```sh
./build.command
./test.command
PYTHONDONTWRITEBYTECODE=1 build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

# Fresh original execution requires authorized Mac host JIT and a new private path.
PYTHONDONTWRITEBYTECODE=1 build/tools-env/bin/python tests/compare_actor_ground_state.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/actor-ground-state-new
PYTHONDONTWRITEBYTECODE=1 build/tools-env/bin/python tests/compare_actor_ground_state.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/actor-ground-state-v1/expected.json \
  --report private/map-depth-1006/actor-ground-state-v1/replay-new.json
# Add --native build/sanitize/actor-ground-state-vectors for sanitizer replay.

# Existing playable baseline; the new helpers are not used by the application.
./run.command --crossing-light-demo
```

These fixtures start from supplied map/actor records, not the complete prepared
map or a running Windows game. [GROUND_UNIT_WORLD_1006.md](GROUND_UNIT_WORLD_1006.md)
retains its supplied actor Z and flat/settled lit locomotor inputs; its expectations
were not changed. Next recover the actual placement/movement callers and stored
ramp-to-body-pose consumer, then join the state to prepared-map drawing before
runtime promotion. Actual SDL level crossing and parked `(51,72)`, elevation 4
remain acceptance scenarios. No new SDL, body-pose, original frame or playable
capability claim; existing runtime binary reads/data formats and simulation/SDL
boundaries are unchanged. Only Apple Silicon macOS is tested.
