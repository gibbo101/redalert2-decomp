# Movement gate interaction and actual Mission children

The subsequent [complete Process gate join](GROUND_DRIVE_GATE_PROCESS_1006.md)
executes the formerly inspection-only false-return caller: 297 fresh sequences /
13,048 Process calls and both replays. The new result-bearing entry is unwired;
nonzero admission/next-Cell and production-map joins still precede runtime adoption.
The standalone gate-v4 receipt below remains current and unchanged.

Subsequent [Unit admission recovery](UNIT_ADMISSION_1006.md) joins actual
IsTraversable/House/Mission children inside complete admission in a bounded
ordinary profile. Current gate proof is freshly movement-gate-v4 after CMake
fingerprints changed, with unchanged v3 command/result/label projection and both
replays. Prepared projection is freshly terrain-runtime-map-v15. v3 correction
history below stays explicit. Both helpers remain unwired; result-bearing caller
and next-Cell joins still precede runtime adoption.

After `266a875`, complete base map gate interaction and both Building helpers
match **2,074 fresh results / 2,494 isolated original calls**, followed by normal
and ASan/UBSan replays. Actual House/object alliance, three animation-byte
predicates, Mission getter/Set/Queue/Commence and kind/owner leaves execute in the
same guest. The new SDL-free helper is **unwired**. The terrain demo and its
previously verified single-Unit movement remain unchanged. Complete base RA2,
then Yuri's Revenge, remain incomplete; no workers were used.

## Identity and reference boundary

Both private executable copies rehash to 4,485,392 bytes / SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`:
`private/official-1006-probe/game.exe` and the already supplied
`private/windows-baseline-20261014/game.exe`. Fresh execution uses the first.
Embedded 1.08, supplied 1.006 lineage and reported no-CD changes remain separate;
pristine authenticity is unverified. No new Windows action or transfer occurred.

Pinned YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88`,
`BuildingClass.h` MakeTraversable/IsTraversable comments and
`BuildingTypeClass.h` Gate/GateStages declarations supplied naming leads.
Hypothesis: the older movement fixture's direct “reserve” service actually
interacts with gates. Exact base callers, dispatch and execution confirm the
gate behavior; YR addresses/behavior are not applied to base RA2. No YRpp license
file was found. The retained recomp snapshot
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` has no Git metadata; its MIT text
covers own tools/docs, excludes lifted/original game code and retains stale
The Movies wording. No upstream/header/generated/lifted code, data table or new
dependency was incorporated. Existing [reference rules](REFERENCES.md) apply.

## Corrected boundary

`0x55ACD0..0x55AD65` is a complete **map gate interaction predicate**, not a
generic reservation operation. Historical fixtures retain their `reserve`/`R`
protocol and supplied-success scope; no old receipt is renamed or relabeled.
Actual Unit admission `+0x194 -> 0x703040` and next-Cell interaction
`+0x4B8 -> 0x705160` remain open. Inspection suggests the latter includes crusher
decisions, so its old supplied no-op is not a recovered reservation store either.
The larger routines have not yet been completely bounded or verified.

The full preparation routine is inspected, not executed by this new suite.
At `0x4A341E` the gate predicate precedes Facing comparison and admission.
A false result returns from preparation with AL=1 before turning, consuming a
route or committing a track. Other call sites use it after admission result3
and handle the result differently. The current ordinary native Process has a
void supplied-success callback; adding real failure requires a result-bearing
caller boundary and joined proof. Do not substitute the new helper into that
callback or infer complete blocked-route/gate behavior from this leaf proof.

## Preserved behavior

- Combine signed Cell words as `y*512+x`, then bound the combined index; axes
  are not independently clamped. Missing/outside slots assign the packed words
  to the shared fallback before examining residents.
- Traverse **primary +0xE4** only, following shared Next +0x30. Skip mover identity
  before querying kind. Only kind6 with a nonzero type +0x1351 reaches alliance.
  Elevated +0xE8 and unrelated +0xEC decoy residents are deliberately populated
  and ignored.
- Alliance first calls the mover's actual owner virtual. Null object/owner is
  false; equal House pointers or stored indices are true, including equal -1
  indices. A different owner index -1 is false. Other indices use the x86
  low-five-bit shift count against the Building owner's alliance mask. Terrain's
  owner virtual returns null even with nonzero bytes in its supplied owner slot.
- An allied gate returns its helper result immediately. A nonallied open gate
  returns true immediately; a nonallied closed gate continues the list. Exhaustion
  returns true. This predicate alone does not establish enemy-gate passability.
- The animation predicates differ: `18!=0 && 19==0`, `18==0 && 19==0`, and
  `18==0 && 19==1`. The last requires exactly one, not any nonzero byte. Mission
  and Gate are reread along the allied path; repeated query order is retained.
- Opening requests actual SetMission(-1), QueueMission(24,0), then Commence,
  with all selected mission/status/frame/timer stores compared in order and width.
  Both temporary timer padding words are supplied explicitly at child entry;
  their copied values do not establish original initialization. The existing
  QueueMission implementation is reused within its previously verified zero
  second-argument domain.

`sim/MovementGate` uses logical ids to preserve Cell/object/House identity, one
shared fallback, stable primary lists and read-only observers. It does not own or
construct those original records. Native finite-list/slot/kind and malformed-input
refusals are safety boundaries, not emulation of original faults. Supported kind
dispatch is Unit1/Building6/Terrain36; arbitrary callback mutation is excluded.
Gate Buildings have a nonnull supplied House; movers may have null owners.

## Evidence and remaining scope

Current private proof: `private/map-depth-1006/movement-gate-v3/`. A later base
admission inspection exposed an error in v1/v2: their logical Terrain tag was 21,
while the actual kind leaf returns 36 (`0x24`). The earlier gate outputs are
unaffected because only Building 6 is tested, and the actual Terrain owner leaf
already returned null. Their trace recorded the object queried but omitted its
kind result, so it did not catch the mistaken label. v1/v2 remain historical;
they must not be silently relabeled or reused as proof of kind 21.

v3 corrects the tag, pins each actual kind immediate/dispatch, asserts returned
kinds against supplied records and compares 603 returned-value events: Unit 1=40,
Building 6=448, Terrain 36=115. The parser rejects the old Terrain 21 tag. Normalize
only the acknowledged 21-to-36 command field and remove the added three-token `V`
events to reproduce every v2 command/output/label exactly. This normalization is
a historical comparison, never an acceptance rule for fresh proof. Both actual
elevated +E8 and unrelated +EC decoy lists are now populated and ignored. The
old note's elevated +EC label was incorrect; primary +E4 traversal was already
correct. No original instruction or earlier receipt was edited.
Coverage includes raw Gate/animation bytes, current/queued missions, signed House
indices and tick/padding words, aliased heads, self skips, mixed residents,
enemy-before-allied ordering, fallback rewrites and repeated opening requests.
Forty-eight animation changes are explicitly supplied caller transitions, not
recovered gate animation or original-game observations.

The verifier pins 16 complete executable ranges / 297 inspected instructions;
all ranges enter, with 275 distinct instructions executed. The complete 2,583-
instruction preparation caller is separately inspection-only. There are 8,814
selected original object/fallback stores and 958 supplied child-entry padding
stores. Root return, ESP, callee-saved registers, caller tail, code/dispatch/type/
House/slot inputs, instruction/write allowlists, complete unselected actor/type/
House/Cell arenas and fallback bytes are checked. No original instruction is
patched; no final original state is transferred to native execution. Full native
machine read/write order and whole startup/frame parity are not claimed.

Normal and sanitizer builds, 818 Python tests, 60 normal / 59 sanitizer CTests,
the evidence guards and both replays pass. Of the prior 120 replay records, 116
retain current source/runner identities without reexecution. The prepared-map
projection fingerprints CMake and all simulation sources, so it has fresh
`terrain-runtime-map-v14` evidence and both replays: all 13,515 selected Cells /
255 source slices remain equal to v13. The arm64 application is
byte-identical to the previous runtime milestone, SHA256
`f1a5a2921b14ec6b43279e2f9eb8c59a9b49c9faf7a169ccd8cc29a6e805011e`;
no new SDL playtest is claimed or required for this unwired helper. Earlier SDL
event checks apply to that unchanged binary; OS-level input testing remains open.

Initial map/list/House/type/mission/animation records, animation progression,
admission, next-Cell/crusher interaction, pathfinding, mission scheduling and
runtime adoption remain supplied or open. This is a verified movement dependency,
not a completed gate system or new playable capability. Only Apple Silicon macOS
has been tested. Closing source/receipt/privacy audit and timings are recorded in
[HANDOFF.md](HANDOFF.md).

## Reproduce and next step

```sh
./build.command
./test.command
build/tools-env/bin/python -B -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

# Fresh original execution requires the authorized host Unicorn JIT context.
build/tools-env/bin/python -B tests/compare_movement_gate.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/movement-gate-new
build/tools-env/bin/python -B tests/compare_movement_gate.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/movement-gate-v3/expected.json \
  --report private/map-depth-1006/movement-gate-v3/replay-new.json
# Add --native build/sanitize/movement-gate-vectors for sanitizer replay.
./run.command --terrain-demo
```

Select Rhino, G/right-click moves, Q/E turns the body, A/D aims, S finishes the
committed track then stops, R resets. Controls, routes and clearance remain host
adapters. Next recover supported actual Unit admission and next-Cell decisions,
then join the gate result and complete preparation/Process on shared mutable Cells
before runtime changes or occupied-route/multiple-actor expansion. General
pathfinding, combat, AI, campaigns, multiplayer, audio, original saves and YR
remain later work.
