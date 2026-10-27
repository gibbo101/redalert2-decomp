# Ordinary Unit admission and actual terrain/resident decisions

The separate [overlay admission entry](OVERLAY_UNIT_ADMISSION_1006.md) now extends
the same kernel with actual wall/House/weapon decisions:473 scenarios /481 complete
original roots and normal/sanitizer replays. Existing ordinary/runtime bindings
retain their overlay-free scope. Candidate preparation, later effects and runtime
overlay traversal remain unjoined; admission success is not crushing.

The later [stationary Unit/Process proof](GROUND_DRIVE_RESIDENT_PROCESS_1006.md)
executes actual resident admission6 through both ordinary Process callers. The
new entry is unwired; production shared resident membership/drawing remain open.

[Owned admission/membership](OWNED_UNIT_ADMISSION_1006.md) corrects the earlier
UnitType+B94 label to **MovementRestrictedTo**, distinct from MovementZone. This
fixture still supplies -1; its numbers are unchanged. Current standalone proof
is unit-admission-v5, with fresh execution and both replays. The new single-Unit
owned-map join remains unwired and does not expand occupied/gate runtime support.

The later [admission/Process join](GROUND_DRIVE_ADMISSION_PROCESS_1006.md)
executes actual 0/3/7 preparation admission and zero-result Advance admission,
gates and required next-Cell in one guest. That entry is unwired; nonzero Advance
outcomes and production mutable-map/membership binding remain open. The following
earlier statements retain their historical checkpoint scopes.

Subsequent [gate/Process recovery](GROUND_DRIVE_GATE_PROCESS_1006.md) verifies
result-bearing gate waits through complete Process, while admission remains
supplied zero in that fixture. Nonzero admission-result handling and the actual
admission/next-Cell/production-map join are still required before runtime adoption.
This standalone admission-v3 evidence remains current and unchanged.

After `35a04ab`, the complete Unit admission root executes with actual Foot,
registry/map, Drive, House, Mission, kind/cast, weapon, ability and stationary
resident children in one guest: **2,391 fresh scenarios / 3,619 calls**, followed
by normal and ASan/UBSan replays. The SDL-free native entry is **unwired**.
This recovers result-bearing decisions that were previously a supplied zero;
it does not adopt them into Process or add playable collision/gates. Complete
base RA2, then Yuri's Revenge, remain incomplete. No workers were used.

## Identity and reference boundary

Both supplied engines rehash equal, 4,485,392 bytes / SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`:
`private/official-1006-probe/game.exe` and the already authorized private copy
`private/windows-baseline-20261014/game.exe`. Fresh execution uses the first.
Embedded 1.08, supplied 1.006 lineage and reported no-CD changes remain separate;
pristine authenticity is unverified. No Windows action or transfer was needed.

Pinned YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88`,
`Interfaces.h` Can_Enter_Cell and `FootClass.h` TryCrushCell supply naming leads.
The base vtables, complete ranges and execution establish the actual behavior;
YR return names, addresses and behavior are not promoted to base RA2 facts.
No YRpp license file was found. The retained recomp snapshot
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` has no Git metadata; its MIT text
covers its authored tools/docs, excludes original/lifted code and retains stale
The Movies wording. No upstream/header/generated/lifted code, extracted table or
new dependency is incorporated. See [REFERENCES.md](REFERENCES.md).

## Boundary and preserved decisions

The complete root is `0x703040..0x703BC8`; Unit virtual +194 dispatches there.
Its five arguments are target Cell, direction, level seed, previous Cell (null
in the ordinary preparation caller), and the low-byte consult-locomotor flag.
The level argument is by value. Its local level/elevated outputs are passed to
actual Foot +198, `0x4C8730..0x4C8937`. Standalone Foot calls compare the caller's
retained level dword and elevated byte as well as the root result.

- Registry lookup uses the signed short Cell +116, actual global count/table,
  null slots and stored registry direction/coordinates. Direction8 has a separate
  coordinate shortcut. Other directions preserve signed wrapped subtraction,
  wrapped absolute value (including INT_MIN), signed comparisons and -1 handling.
- Opposite-neighbor selection is `(direction-4)&7`. Coordinates add as words;
  the combined signed `y*512+x` index is bounded after combination. The Unit
  parent and Foot helper make separate lookups. A missing previous Cell triggers
  another lookup even for direction -1, and even when target and result are the
  same shared fallback. Its newly stored coordinates feed subsequent queries.
- Foot uses signed byte levels, bridge bits100/200 and zero/nonzero ramps. It
  can write level before returning7. Direction -1 can write target level+4 but
  retains the elevated byte. Other paths write elevated=1 only at the actual
  instruction. No blanket initialization or normalization of either output.
- Initial elevated-list selection and later elevated occupation/owner selection
  are distinct decisions. Actual primary +E4 and elevated +E8 lists are separate.
  Self is skipped before kind and clears only local bit5/occupation bit0x20;
  no Cell occupation field is changed by this admission root.
- Actual Foot locomotor wrapper `0x4C86E0..0x4C8729` consumes the consult flag.
  With the supplied nonnull Drive association, virtual +1C dispatches to actual
  `0x53D4F0`, a complete zero-return leaf. Its result is binary-derived, not a
  supplied successful admission callback.
- Actual gate IsTraversable, mission fallback and exact animation19==1 execute
  inside this root. A closed allied gate promotes result to3; a closed enemy
  gate needs actual selected-weapon presence and can promote to5. Gate checking
  here does not open the gate. The separately recovered map gate predicate does.
- Generic stationary residents use actual empty passenger membership, two mover
  mission probes, settled Facing and Drive IsMoving, House/object alliance and
  cast/kind children. Allied stationary Units can promote to6; an allied generic
  Building returns7. Enemy state +1B8==2 can promote to1. Weapon, IsTrain and
  Building +1350 participate in other enemy decisions. These numeric fields and
  return codes are deliberately not named from YR enums.
- Result promotion is ordered across residents. An earlier nonzero result does
  not bypass later rejection, and terrain speed is checked after list traversal
  but before returning the accumulated result. Selected land speed is a float32
  at `land*9+supplied movement-type1`. Both zero signs and unordered NaNs reject;
  negative finite values, subnormals and infinities are not replaced by a
  positive-speed policy. Native bit classification preserves this predicate;
  x87 exception/status flags are outside the comparison.
- Tail occupation preserves low-six-bit testing, separate bit5 handling,
  stored owner index equality/alliance, unpromoted ability, Crusher, IsTrain,
  repeated first weapon-slot lookup and projectile byte +275. A single generic
  blocked/unblocked boolean would discard these decisions.

`sim/UnitAdmission` shares logical identities with `MovementGateWorld` for
coordinates, primary lists, Next, kind, House and mission/animation state. It
borrows that world's slot span and owns no original allocation/startup. Observers
are read-only. Finite lists, canonical slots, supported kinds, nonnull target and
known Cell records are native safety boundaries, not emulation of original faults.

## Evidence and supplied state

Current proof is `private/map-depth-1006/unit-admission-v3/`. It executes complete
roots without patches or callback services. Every entered instruction must lie
in one of 31 inspected complete ranges (1,528 instructions); excluded branch
entries fail rather than simulate an answer. Current counts, normal/sanitizer
replays and closing audit are in [HANDOFF.md](HANDOFF.md).

The profile supplies initial actor/type/House/Cell/registry records, eight
synthetic direction pairs, speed-table bits and all their associations. It fixes
UnitType+B94 restriction=-1, overlay=-1, loading=1, null team, empty passenger vector,
unpromoted 0.0, Type 704=0, first weapon slot and settled resident Facing/Drive.
Native specializations of those leaves are valid only for these supplied states;
they do not recover constructors, moving residents, promotions or weapon selection.
Generic Building special type flags are zero except Gate and +1350. Unit and
Building kinds 1/6 are supported; Terrain36 and other resident kinds are refused.
The fixture explicitly supplies queued mission 7; current mission -1 therefore
exercises an actual distinguishable queued fallback. No game observation or
original initialization is inferred from these diagnostic records.

Raw occupation/owner flags, signed registry bounds/directions, signed levels,
retained output bytes, ordered mixed resident lists, gate animation bytes,
distinct selected land speeds, House masks, self skip and shared fallback
forwarding are compared. The root returns 0/1/2/3/5/6/7 in the accepted profile;
return 4 belongs to excluded overlay behavior. Both Foot returns 0/7 execute.
Root return, ESP, callee-saved registers, caller tail, code/dispatch/table/global
inputs, instruction/write allowlists, complete unselected actor/type/House/Cell/
registry arenas and fallback attributes are checked. Selected level/elevated and
fallback stores are compared in order and width. Native full machine read/store
order, startup memory and hardware FP exception behavior are not claimed.

The first v1 probe has 2,219 scenarios / 3,447 calls. v2 explicitly supplies queued
mission 7 instead of leaving its unused word A5-seeded, adds pending-mission and
registry-count/null-slot cases and asserts actual parent/Foot returns and selected
instruction coverage. v3 additionally varies each of 12 land entries independently
and all 60 ordered three-resident lists. v1/v2 remain historical with their own
source identities; they are not silently upgraded to current proof.

Earlier gate and prepared-map proofs are freshly `movement-gate-v4` and
`terrain-runtime-map-v15`, with both replays and unchanged earlier command/result
projections. The application remains byte-identical to the previous runtime.
No new SDL playtest or original-game frame comparison is claimed. Only Apple
Silicon macOS has been tested; the app is still a local dependency-linked build.

## Next join and reproduce

Movement-zone/overlay/special Building paths, moving allied residents, crushing
residents, other actor kinds, promoted abilities, general weapon selection,
visibility/loading0, scenario construction and full map associations remain open.
The existing Process still has supplied-success admission and next-Cell behavior.
Do not wire this helper into its void callback: recover the result-bearing
preparation branches, next-Cell/crusher behavior required by the accepted route,
and joined shared mutable map/state/write evidence first. Older guards and
immutable renderer/preview ownership stay intact. Bridge decision probes do not
enable bridge gameplay or original bridge/lifetime initialization.

```sh
./build.command
./test.command
build/tools-env/bin/python -B -m unittest discover -s tests -p 'test_*.py'
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
build/tools-env/bin/python -B tests/compare_unit_admission.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/unit-admission-v3/expected.json \
  --report private/map-depth-1006/unit-admission-v3/replay-new.json
# Add --native build/sanitize/unit-admission-vectors for sanitizer replay.
# Fresh isolated-original execution: omit --expectations/--report, use a NEW
# private --output directory and the authorized Mac host Unicorn JIT context.
./run.command --terrain-demo
```

Select Rhino; G/right-click moves; Q/E body turn; A/D turret; S finishes the
committed track then stops; R resets. These controls, direct routes, clearance,
initial runtime records and currently supplied admission policies remain adapters.
General pathfinding, combat, AI, campaigns, multiplayer, economy, audio, saves
and YR remain later work. No full-game completion or independent acceptance claim.
