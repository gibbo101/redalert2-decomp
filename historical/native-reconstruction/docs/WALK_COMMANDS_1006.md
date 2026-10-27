# Walk interface commands joined to queued Process

`moveWalkTo`, `stopWalkMovement` and `setWalkHeadImmediate` use the existing
`WalkMovementState`. Arrival uses the same Stop implementation. A separate
`walk-queued-vectors --commands` diagnostic issues actual interface Move_To
and optional Stop before complete Process calls on the same actor/Walk/Cells.
This unblocks the locomotor-command dependency of Boot Camp Day 1 GI walking.
**The preview remains static; ordinary Infantry/Foot destination commands,
production GI ownership/drawing and the first objective transition are not delivered.**

## Recovered behavior

Before relying on addresses, the supplied executable was rehashed:
4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Private inspections/receipts are under
`private/infantry-walk-20261018/`. No upstream/generated/lifted code, new data,
dependency or application executable read was added.

Complete unchanged original roots execute through Walk interface7AEAD8:
Move_To71E020..71E100 (+44), Stop71E110..71E16E (+48) and immediate-head
setter71E1A0..71E211 (+78). The interface pointer is Walk+4; the native state
retains base-Walk destination1C/head28 and raw bytes34/35/36.

- Move_To executes actual Infantry+324/6D8E80 (signed actor3FC>0), then
  +1BC/6D6DF0 (raw actor204), then +1C0/6D6E00 (raw actor205), stopping at the
  first true result. Walk has no additional Drive+328 timer guard.
- It stores by-value destination X/Y/Z before coordinate lookup548000. If the
  returned Cell140 has bit100, actual6A29B0 calculates `(60-.5)*ABE520`, calls
  FTOL77F110, consumes its signed64 result's low32 and adds it to the **late**
  destination Z with dword wrapping. It then stores moving34=1. No clamp or
  hardcoded bridge-height replacement is used. Initial projection scale is supplied.
- An empty destination retains raw moving34 while the head is nonempty. With
  both empty, Move_To clears moving34 and resets only if its saved value was
  nonzero. Full X/Y/Z equality matters, including Z-only nonempty heads.
- Stop always writes the empty destination. A committed head retains moving34
  and reallyMoving36. An empty head clears both bytes and calls reset even if
  already stopped. Stop does not cancel a committed subcell step.
- The immediate-head setter saves moving34 before its three ordered head stores.
  If head and destination are empty, it clears moving34 and conditionally resets
  from the saved byte; it does not independently clear reallyMoving36.
- Actual Infantry reset508750 tests raw actor5CC, clears it before calling
  animation4DC/504740 with `(27,0,0)`. That animation effect remains a named
  supplied service. The command fixture executes the actual reset root;
  Process's existing reset callback retains its earlier supplied scope.

Native bridge numerics preserve the tested original0E7F entry precision/rounding
and signed64 invalid-conversion low zero; host rounding is restored. Other x87
entry-control states/exception flags are not proved. Diagnostic service-time
mutations verify late destination/scale/Cell reads and callback store ordering;
they are not original-game observations. Trace observers are read-only.

`WalkCommands.hpp` contains the shared Stop body so prior Process comparators'
transitive native-source guards include it. Other commands live in the separate
SDL-free implementation; there is no second Walk algorithm, Drive substitution,
actor/map copy or application-default change. Refusals retain their earlier scope.

## Verification, reuse and costs

Canonical standalone originals: `commands-fresh-a2/expected.json` and immutable
original-only `report.json`. **370 sequences /942 complete command roots** match
normal/sanitizer/uncached current-native replay (`commands-replay-*-a2.json`).
Coverage includes signed guard extremes, raw nonboolean flags, repeated Stop,
all coordinate components, nonzero supplied empty sentinels, signed64 conversion
boundaries/nonfinite values, wrapped Z and late service mutations. Selected
ordered stores, named effects and final raw state match.

Canonical joined originals: `command-process-fresh-a1/expected.json` and immutable
original-only `report.json`. **251 sequences /10,040 complete original Process
roots,451 command roots and three actual initializers** match. The composition
executes251 Move_To and200 Stop calls,203 actual admissions,2,445 actual speed
calls,402 head/occupation calls and199 arrival Stops. Commands precede preparation,
interpolation and arrival on the same owners. It covers all eight directions,
negative coordinates, three base speeds, Stop before/during/after commitment,
elevated commands and actual country/promotion speed. Current
`command-process-replay-{normal,sanitize,uncached}-a1.json` each reports251 reuse
hits/zero misses and zero original execution. Standalone replays report370 hits.
Native results are never cached.

The joined fixture still supplies route words, initial records/seeding/scale,
parity map, floor/Mark/notification/destination/reset services inside Process.
This is a locomotor interface command, not Infantry501CE0 or Foot4C8030, original
pathfinding, production map ownership, SDL walking or mission progression.
All24 route words, full RNG, selected stores/services and final state match.
ABI/stack/callee-saved/code/table/other-arena guards remain. Local verification
is not independent acceptance or whole-frame fidelity.

Current rebuilt prior normal/sanitizer replays retain:
`queued-replay-*-a5.json` (580 sequences /1,557 Process roots),
`walk-admission-replay-*-a4.json` (199 /2,093),
`walk-speed-replay-*-a3.json` (121 /3,592),
`arrival-replay-*-a6.json` (380 roots) and
`movement-replay-*-a7.json` (624 roots).
No original answers were regenerated for the native shared-Stop/runner changes.
38 focused Python tests and nine mission/Walk/Infantry CTests per normal/sanitizer
build pass. No broad capability closure or actual SDL rerun is claimed for this
internal dependency; earlier static-preview/two-tank acceptance retains its scope.

Standalone fresh a2 generation and full replay costs are recorded in
`commands-validation.json`; joined generation25.250s, comparison25.933s,
wrapper26.117s. Joined normal/sanitizer/uncached replay0.484s/1.550s/2.514s;
native comparison0.105s/1.137s/0.100s. Python38 tests0.709s; CTest0.14s/0.68s.
There were no failed build/comparison attempts. Standalone a1 remains unchanged;
a2 was genuinely regenerated after correcting the comparator's scope docstring,
and all original command/result streams are identical. No receipt was relabeled.
Initial build/repair and total task-wall times were not separately measured;
configure output reports normal0.3s+6.2s and sanitizer0.1s+5.2s. Costs overlap
and are nonadditive. No new cache framework or unchanged whole-inventory refresh.

## Reproduce and next join

```sh
./build.command
build/native/walk-command-vectors --guards
env PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_walk_commands test_walk_command_process

# Use fresh report/audit names. Current native executes; original code does not.
env DEVELOPER_DIR=/Library/Developer/CommandLineTools PYTHONHASHSEED=0 \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/walk-command-next.audit.json tests/compare_walk_commands.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/walk-command-vectors \
  --expectations private/infantry-walk-20261018/commands-fresh-a2/expected.json \
  --report private/walk-command-next.json

env DEVELOPER_DIR=/Library/Developer/CommandLineTools PYTHONHASHSEED=0 \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/walk-command-process-next.audit.json tests/compare_walk_command_process.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/walk-queued-vectors \
  --render-data private/derived/ra2-1006/render-data.bin \
  --raster-data private/derived/ra2-1006/raster-data.bin \
  --direction-data private/derived/ra2-1006/direction-data.bin \
  --subcell-data private/derived/ra2-1006/infantry-subcell-data.bin \
  --expectations private/infantry-walk-20261018/command-process-fresh-a1/expected.json \
  --report private/walk-command-process-next.json
```

Use `build/sanitize/` runners for a separate sanitizer replay; wrapper `--uncached`
is the inspection control. Deliberately fresh original proofs use a new `--output`
instead of expectations/report and the authorized Mac-host JIT context. Preserve
all old receipts. Entry points remain `./build.command`, `./run.command`,
`./test.command`; `./run.command --boot-camp-preview` remains static.

Next recover ordinary E1 Infantry501CE0 -> Foot4C8030 -> Walk destination handling,
including actual target/reference/timer/queue effects. Its exploratory disassembly
is private and is inspection, not differential proof. Ordinary mission2 bypasses
head's mission8/9/7/11/25 target-force children; do not turn that into general
nonnull-target support or clear targets to make a proof pass. Preserve the
existing entered-child refusals. Then join production mutable actors/type/map,
animation/drawing and ordinary SDL walking. Actual discovery/actions precede
first-objective success. Base RA2/YR remain incomplete; only Apple Silicon macOS
is tested. No workers, Windows actions, downloads or system changes occurred.
