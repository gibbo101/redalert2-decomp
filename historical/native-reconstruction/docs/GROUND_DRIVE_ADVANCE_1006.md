# Committed ordinary Drive Advance on terrain

[GROUND_DRIVE_STORES_1006.md](GROUND_DRIVE_STORES_1006.md) adds optional selected
Drive-store observation and verifies the terminal zero-head correction: head and
driving clears are conditional on any nonzero head coordinate. The earlier
514-scenario projection remains unchanged. Current receipt versions and runtime
regressions are in the opening HANDOFF; unwired statements below are historical.

Later [MEMBERSHIP_DRIVE_1006.md](MEMBERSHIP_DRIVE_1006.md) binds actual Unit +BC
to live +5A0 and verifies the committed old-location occupation-unmark/byte-clear
branch. The earlier provisional jumpjet name describes a supplied-false fixture,
not this Unit dispatch. Current earlier-domain proof is v4, with unchanged v3
commands/results/labels and both replays; the checkpoint scope below stays intact.

The no-queue source proof was refreshed after `2700647` while joining queued
Process: [GROUND_DRIVE_PROCESS_1006.md](GROUND_DRIVE_PROCESS_1006.md). Current
v3 commands, results and labels equal v2, with fresh original execution and both
replays. The new queued non-Passive extension additionally preserves admission
queries before rejecting a switch; it is verified by that separate Process suite.
The no-queue domain below is unchanged.

After `c23e2c5`, **514 fresh exact-engine sequences / 10,866 complete Advance
calls** match the native implementation, followed by normal and ASan/UBSan
replays. Actual Foot/Object location, relative SetHeight, map/Cell floor,
coordinate lookup, transform, interpolation, speed and Facing children execute.
This is a locally verified recovery checkpoint. The helper is unwired; the SDL
application and playable capabilities are unchanged. Base RA2 then Yuri's Revenge
remain incomplete.

## Identity and references

Both supplied engines were rehashed equal: `private/official-1006-probe/game.exe`
and the previously approved private Windows copy, 4,485,392 bytes / SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Fresh execution uses the former. Embedded 1.08, supplied 1.006 patch lineage and
reported no-CD modifications remain distinct; pristine authenticity is unverified.
No new Windows action, transfer, download, source-installation/disc write or system
change occurred. Runtime executable reads and prepared-data formats are unchanged.

Consulted [REFERENCES.md](REFERENCES.md), pinned YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` `DriveLocomotionClass.h`,
`TechnoTypeClass.h`, `UnitTypeClass.h`, and retained recomp snapshot
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` testing/voxel reference context.
Hypothesis: the complete Advance parent determines where floor updates belong;
overwriting Z after every native movement update would lose original ordering.
Exact base inspection and execution decide the behavior below. YR/recomp names
remain leads. Existing license boundaries apply: no YRpp license file was found;
recomp MIT excludes generated/lifted game code. No upstream/header/generated/
lifted code or extracted table incorporated; no dependency or THIRD_PARTY change.

## Executed domain

[verify_ground_drive_advance.py](../tools/verify_ground_drive_advance.py) pins
**16 complete additional/retained ranges / 2,128 instructions**, including the
**complete 1,613-instruction Advance parent** `0x4A1000..0x4A2649`. Earlier floor
ranges remain pinned. The execution allowlist includes complete ordinary children:

| Boundary | Address |
| --- | --- |
| Track transform | `0x4A4740..0x4A47BC` |
| Percentage setter / current speed / type speed | `0x4C2DF0`, `0x4C9B10`, `0x6D8E90` |
| Country speed factor / Facing timer | `0x4F5A20`, `0x453EB0` |
| Vector interpolation / Facing SetCurrent | `0x7220C0`, `0x4B8B10` |
| Actor word Cell coordinates / word Cell lookup | `0x41B320`, `0x548070` |
| Foot/Object location / relative height | `0x4CA160`, `0x5D51C0`, `0x5D4860` |

The full root executes in this bounded domain: already committed ordinary track,
queue head -1, no short track, `Accelerates=0`, `IsTrain=0`, on-map=1, bridge=0,
empty overlay-free Cells, null destination object, no jumpjet/turret rotation or
Passive switch. Actual speed children use supplied unit/type/house/country state,
country and instance factors one, no veteran ability and no special speed halving.
Mark effects are supplied either unchanged or updating only the marked byte.
Occupation unmark, notification and post-Cell effects are supplied no-ops.

Initial track/head/index, actor/type/globals and a shared 9x9 resident Cell table
or shared fallback are supplied. This is **not** actual preparation, original
route finding, full Process, finalized-map association or whole actor construction.
Callbacks must preserve that domain; arbitrary mutation, aliasing, throwing
services, bridges, trains, occupants and alternate speed/status branches are not
proved. Type names are checked against the exact base INI association: `+0xB59`
is Accelerates (constructor default 1); `+0xAA0` is IsTrain (default 0).
Those constructor/read blocks are **inspection only** here. Supplied owned HTNK
rules explicitly contain `Accelerates=false` and omit IsTrain; host text decoding
is not full original type initialization. Crusher is the separately established
`+0xAF3`, not `+0xAA0`.

## Native behavior and boundaries

[GroundDriveAdvance.cpp](../src/sim/GroundDriveAdvance.cpp) preserves:

- Signed wrapped speed addition/subtraction, strictly `remaining > 7`, stored
  float32 interpolation fraction and original component truncation. Signed
  accumulators remain signed; supplied endpoint states can leave negative arrival
  credit before a later inactive call clears it.
- Committed coordinates use transformed X/Y and **Z=0**, then actual SetHeight(0)
  obtains the floor. Same-Cell placement separately suppresses/restores marking
  around location and height. Crossing calls Mark(0), Foot location, two word-Cell
  lookups, Mark(1), then the separately suppressed height setter. The previous
  committed track point supplies the first Cell when index is nonzero.
- Facing changes after floor placement, followed by the descriptor's occupation
  unmark point. Location/floor calls and original X/Y/Z store order stay visible
  to the supplied services.
- Ordinary fractional interpolation performs four ordered full-coordinate Cell
  lookups and compares **record identity**, including the shared fallback. At a
  third-Cell corner, residual <=3 holds the old point; >3 takes the next point.
  Its SetLocation preserves the old Z and **does not call SetHeight**. Same-Cell
  updates suppress marking; crossing updates use Mark(0)/location/Mark(1).
- A track terminator applies original Manhattan-distance/1/11 arrival credit,
  writes the two arrival bytes, places the final head through actual floor
  children, clears head/driving/track/index, then notifies and calls post-Cell.
  The earlier helper named `placeDriveResidualGround` is used at this terminator;
  it must not be substituted for regular fractional interpolation.
- Cell equality divides full signed coordinates by 256 before word truncation;
  map lookup retains full divisions before its wrapped combined index. These are
  separate operations. Every native call restores the incoming FP mode.

The new value-state kernel isolates this recovery boundary while the existing
flat Drive/runtime adapter remains intact. It is not an alternate engine or a
claim that the old adapter now handles terrain. Join actual Process/preparation,
stored ramp/body state and finalized shared Cells before adapting runtime Drive
and complete drawing. Keep the existing runtime depth guards until that join.

## Evidence and reproduction

Current receipts: `private/map-depth-1006/ground-drive-advance-v3/`. Earlier v1/v2
receipts retain their narrower development/source identity and are historical.
All 40 valid ordinary transforms, all 21 ramps, negative/zero/elevated terrain,
resident/fallback identity, marked-byte alternatives, four incoming native FP
modes, signed coordinate/accumulator boundaries, endpoint credit and strict-seven
cases are covered. Exact selected actor stores/services, actor/head/track/index/
accumulator/Facing state and final lazy-floor/fallback state match.

Counts: **14,489 actual Foot/Object setters, 9,961 SetHeight/map-floor/Cell-floor
calls, 23,585 transforms, 4,528 interpolations, 43,068 FTOL calls, 18,112 full
coordinate lookups, 1,066 word lookups, 101,050 selected actor stores and 1,672
supplied Mark calls**. There are 4,983 active speed calls; remaining complete
Advance roots include terminators and inactive follow-ups. Actual Facing
SetCurrent and timer execute; the separately allowed Facing-current range is not
entered in this settled fixture and gains no new execution claim.

Guards check exact code/dispatch/table/input identities, instruction allowlists,
complete-root return/ESP/callee-saved/caller tail, permitted actor/locomotor/image/
stack writes, whole Cell/actor/locomotor/fallback arenas and immutable tables/code.
Ordered selected actor stores and named service calls are compared; full memory
read order and every native internal write are not claimed. Thirteen malformed
native commands are separate safety refusals, not original malformed-input parity.

Initial allowlist runs stopped at two previously unlisted real children (country
factor and Facing timer); both were inspected and added. Native verification then
rejected an invented nonnegative-accumulator guard; it was removed and signed
edge cases added. A later branch hypothesis incorrectly called `+0xAA0` Crusher;
the exact IsTrain key rejected that identification before new expectations could
be accepted. The speculative branch was removed. No original instruction was
patched, failed expectation accepted or gameplay repair required. Final fresh
CLI/original/native times: **15.631 / 14.138 / 0.111 s**.

```sh
./build.command
./test.command
PYTHONDONTWRITEBYTECODE=1 build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

# Fresh original execution needs authorized Mac host JIT and a new private output.
build/tools-env/bin/python tests/compare_ground_drive_advance.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/ground-drive-advance-new
build/tools-env/bin/python tests/compare_ground_drive_advance.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/ground-drive-advance-v3/expected.json \
  --report private/map-depth-1006/ground-drive-advance-v3/replay-new.json
# Add --native build/sanitize/ground-drive-advance-vectors for sanitizer replay.

./run.command --crossing-light-demo
```

The demo is unchanged: select Rhino, G/right-click moves, L toggles light, R resets.
Only Apple Silicon macOS is tested. Next connect the complete bounded movement
caller and stored ramps/body pose to finalized shared Cells and complete drawing.
Actual SDL terrain crossing and parked `(51,72)`, elevation 4 remain required
acceptance scenarios. No new playable or whole-frame fidelity claim follows.
