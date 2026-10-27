# Milestone 2: bounded original drive movement

[DRIVE_1006.md](DRIVE_1006.md) records the separately hash-selected supplied RA2
1.006 profile and fresh comparisons on both engines. This note retains its disc
addresses/evidence; native prepared/runtime inputs remain disc-only.

The drive recovery remains current. [TIMING_TARGETING.md](TIMING_TARGETING.md)
supersedes the 15 Hz host cadence and destination-bearing limitations below.
[CURVES.md](CURVES.md) supersedes the straight-only, two-stream and cell-boundary
redirect limitations below with six ordinary streams, curved transitions and a
tested Passive guard. This document retains the milestone 2 evidence and scope.

October 10, 2026. Baseline commit: `d5bdc66` (tested milestone 1).
The oracle remains the Allied-disc base RA2 `GAME.EXE`, SHA-256:

`135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743`

Embedded version strings are `1.08`; no retail-patch equivalence is inferred.
See RECOVERY.md for complete identity. Every oracle and runtime table read first
checks the full hash. Source discs, the original installation and Outpost 2 remain
read-only. No original code or extracted track tables are compiled into the app.

## Implemented result

The prototype's 0.08-cell normalized movement adapter has been replaced by an
integer-coordinate drive process for straight cardinal/diagonal tracks. It uses
original track points, speed conversion, seven-unit accumulator accounting,
interpolation, arrival correction, stop behavior, body-turn gating and the
no-target turret update. The simulation remains SDL-free.

The bounded profile is an undamaged, unpromoted Rhino, flat unobstructed terrain,
no towing, no combat target, and a supplied queue of one repeated direction.
The shipped prototype's stock Clear/Road/Rough Track factors are all 100%; the
oracle also checks several smaller float32 factors. Full map/path/mission/target
integration is not claimed.

## Recovery provenance and addresses

DriveLocomotion was identified using the base executable's RTTI/type descriptors,
class GUID and vtable, not YR addresses. Public YRpp declarations were naming and
layout leads only, with the existing no-incorporation license boundary retained.

| Item | Verified base-game VA |
| --- | --- |
| Drive class GUID | `0x78CF78` |
| ILocomotion vtable | `0x78B4D4`, interface pointer is object +4 |
| Grid direction CRT initializers | `0x491400`, `0x4914B0` |
| Drive Move_To / Stop_Moving / Do_Turn | `0x49FA00`, `0x49FAC0`, `0x4A0BA0` |
| Full drive Process | `0x4A01C0` |
| Advance track | `0x4A0BD0` |
| Prepare next track | `0x4A2240` |
| Track coordinate/facing transform | `0x4A4310` |
| Track descriptor table / raw-track descriptors | `0x78B188` / `0x78B0A8` |
| Straight cardinal / diagonal point streams | `0x789A68` / `0x789B88` |
| INI Speed conversion basic block | `0x6D2021` through `0x6D2061` |
| Type-speed getter / Foot current speed | `0x6CE2B0` / `0x4C95C0` |
| Speed-percentage setter | `0x4C2910` |
| No-target turret update (full Unit routine) | `0x6F03D0` |
| Float-vector interpolation helper | `0x716B20` |
| Integer conversion helper / control word | `0x76A6B0` / `0x7C39F4` |
| Stop cap / reciprocal seven / arrival constants | `0x789A50` / `0x78B5C8` / `0x78B5D0`, `0x78B5D8` |

Base Unit/Foot fields used by the fixture: location +0x88 (three signed integers),
primary facing +0x2E0, secondary facing +0x2F8, turret-turning flag +0x3F0, speed
percentage +0x468, instance multiplier +0x470, supplied direction queue +0x4D0,
locomotor interface +0x564, UnitType +0x5AC. Type speed is +0x5A0 and ROT +0x638.

Drive-object fields (before the +4 interface adjustment): linked unit +0xC,
destination +0x34, current track endpoint +0x40, speed accumulator +0x4C,
movement scale +0x50, track descriptor number +0x58, index +0x5C,
rotating flag +0x62, driving flag +0x63. These were checked through original
instructions and exercised state, rather than copied from expansion layouts.

## Recovered numeric behavior

- Cell centers are integer `cell * 256 + 128`; coordinates and arithmetic use
  original signed integer leptons. The current flat-plane simulation uses Z=0
  relative to its selected terrain elevation. Rendering consumes a cell-space
  double snapshot; that is not the authoritative movement position.
- INI Speed `-1` retains the previous value. Other values clamp to 0–100, scale by
  `256 / 100` with integer truncation, then cap at 255. **Speed=6 becomes 15**.
- The bounded current-speed calculation uses the original integer type speed,
  country/instance multipliers equal to one, no veteran multiplier, and a clamped
  movement percentage. Integer conversion truncates toward zero.
- A stationary unit first requests the queued direction as `direction << 13`.
  The process waits while the body is rotating. On the update when that turn
  finishes, it prepares a track and begins translation immediately.
- Each movement update adds current speed to an integer accumulator. The loop
  consumes points while accumulator **>7**, subtracting seven per point. Residual
  seven is handled by interpolation rather than an additional consumed point.
- Cardinal and diagonal paths have different original point streams. The diagonal
  stream contains an irregular point; it is retained from the supplied executable.
  No newly generated evenly spaced path substitutes for it.
- For a residual update, the process multiplies the accumulator by the original
  binary64 reciprocal of seven, stores a float32 fraction, multiplies coordinate
  differences by that fraction and truncates each component to integer.
- At a diagonal cell corner, if the candidate enters neither the old cell nor the
  next point's cell, the process holds position for residual ≤3, otherwise takes
  the next point. This avoids an intermediate step into a third cell.
- On reaching the zero-point terminator, it snaps to the cell endpoint and adds
  the truncated correction `(1 - ManhattanDistance * stored(1/11)) * 7` to the
  accumulator. Residual credit may advance the next straight cell in the same
  update, without adding speed twice.
- **Stop is not an instant position freeze.** Stop_Moving caps movement scale at
  the stored binary64 value `0.30000001192092896`, clears the destination, and
  finishes the active cell track. At Speed=6 that produces internal speed 4.
  The supplied route is cleared at the command boundary. Stop completion retains
  the remaining accumulator; a later order can use that credit.

A direct cardinal one-cell advance at Speed=6 and scale 1 takes twelve movement
updates in the fixture. This is a per-update result, not a wall-clock speed claim.

### Floating-point mode was consequential

The original conversion helper loads control word **0x0E7F** and leaves it active:
53-bit precision with rounding toward zero. Later arithmetic and float32 stores
therefore depend on that mode. For residual seven, the stored interpolation fraction
is `0.9999999403953552`, not 1.0. Using ordinary nearest rounding caused a detected
one-lepton error in the first cardinal trace.

The arm64 core scopes `FE_TOWARDZERO` around recovered arithmetic and restores the
host's prior mode on exit. CMake disables contraction and enables rounding-aware
compilation; MSVC is configured for strict FP but is untested. Exact binary64
reciprocal literals preserve the source constants. This does not impose a new
fixed-point or universal-double model. Original x87 behavior outside the tested
flat-drive domain remains a separate recovery obligation.

Synthetic checks verify restoration of the host rounding mode. Original traces
were exercised with initial x87 control words 0x027F and 0x037F; the original
conversion helper brings the movement path to 0x0E7F in either case.

## Turret behavior and integration boundary

The Unit initialization path at `0x6EF0EA..0x6EF111` reads Type ROT +0x638 for both
primary and secondary facing. The checked Rhino therefore uses ROT=5 for both.
That call-site evidence was inspected; the large COM-allocating constructor was
not represented as an isolated executed constructor test.

With no combat target, no spinning turret, no locked weapon, and no destination
actor object, the full original Unit routine at `0x6F03D0` does the following:

1. An already rotating turret finishes its current request.
2. An idle turret requests the body's current facing.
3. The turret-turning flag reflects the resulting secondary-facing state.

The differential suite executes that full routine with the listed conditions.
It compares both headings and the flag on every update. A real destination actor
or combat target can take another branch; its aiming policy is not recovered here.

The native host's A/D and Shift-right-click controls explicitly enable a manual
override. A new move restores automatic following. Manual input is not claimed as
an original RA2 command. Body Q/E requests finish an active translation cell before
applying the manual turn; that sequencing is a host control policy.

## Oracle design and results

`tests/original_movement.py` creates a fresh isolated PE memory image, checks the
hash, executes the original direction-table initializers, and supplies a healthy
unit, its type, neutral speed multipliers, a flat empty map and direction queue.
Map cell identities are distinct by coordinate, so diagonal corner tests exercise
the original pointer/cell comparisons rather than collapsing all map cells.

The full original drive Process calls its original preparation, advancement,
speed, facing, coordinate transform and interpolation functions. The full turret
routine runs afterward. No original instruction bytes are changed. Explicit hooks
supply environment services: getters, empty-cell admission/occupation, flat height,
location writes, non-veteran/weapon predicates, notifications and mission effects.
The pathfinder service returns no new route; the test supplies the initial queue.
These are isolation boundaries, not verified native implementations of those systems.
The complete callback inventory and counts are in `private/movement-report.json`.

**30,608 comparisons across 144 traces passed**, plus the existing **16,598 facing
comparisons**. Movement comparisons include:

- Original Speed conversion block plus full current-speed routine (112 cases).
- Every cardinal and diagonal direction, multiple initial headings, one-, three-
  and 23-cell routes, exact integer positions and all relevant per-update state.
- Stop requests at multiple points, including before movement and during a body turn.
- Changed direction queues during a body turn, with the original process deciding
  when it requests the new heading; existing interrupted Facing tests remain active.
- Float32 terrain factors 1, 0.5, 0.625 and approximately 0.3; alternate ROT=2;
  both initial x87 precision modes described above.

Compared state includes X/Y/Z, original descriptor number, point index, accumulator,
driving flag, body and turret headings, rotating flag and turret-turning flag.
This verifies the defined flat-world profile, not every branch of these routines.

```sh
build/tools-env/bin/python tests/compare_movement.py \
  --exe private/disc-allied/game.exe
```

Local trace input/expected files are written under `private/movement/` for diagnosis;
reports include the native test executable hash. No reference arrays, original
machine code, snapshots or trace data enter Git.

## Runtime data and remaining adapters

`src/assets/MovementData.cpp` reads the original drive descriptors and two point
streams from the hash-checked user-supplied `game.exe`. It uses checked PE section
ranges and copies only data into portable simulation structures. It does not map
executable pages, call x86 code or require Unicorn. The executable remains a user
asset and is never packaged. The prepared `private/game` now includes the owned
copy, and the minimal-runtime regression directory includes that file as well.

Mouse orders select the nearest eight-way ray with a bounded 1–23-cell queue and
show the actual snapped endpoint. Clearance uses the existing conservative flat
terrain/object/overlay exclusions. This is an explicit temporary command adapter,
not original pathfinding. Changing orders while already translating finishes the
current cell and then uses straight segments; original curved turn tracks and
track-jump policies remain absent and are not covered by the fidelity claim.

The host still schedules 15 simulation updates per second. Original game-speed
mapping, frame ordering relative to the rest of a match, and integrated destination
actor/mission behavior require recovery or controlled original-game observations.
Presentation lighting, shadows, normals, occlusion, audio, scenery, ramps, combat,
AI, campaigns, multiplayer, saves and Yuri's Revenge remain outside this milestone.
