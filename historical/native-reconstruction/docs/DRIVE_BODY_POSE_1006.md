# Stored-ramp Drive body pose

October 15, 2026, after `3addd1e`. **3,201 fresh exact-engine comparisons**
verify the complete Drive body-pose/key routine, stock initialized quaternions,
previous/current ramp interpolation, rocking and actual ramp-state children.
Normal and ASan/UBSan replays pass. This is a locally verified recovery checkpoint;
the helper is unwired and the playable application is unchanged. Complete native
base RA2 then Yuri's Revenge remain incomplete.

## Identity and references

Both supplied engines were rehashed: `private/official-1006-probe/game.exe` and
`private/windows-baseline-20261014/game.exe`, 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Fresh execution uses the former. Embedded 1.08, supplied 1.006 lineage and reported
no-CD modifications remain distinct; pristine authenticity is unverified. No new
Windows action/transfer, source-installation/disc write, download or system change.

Consulted [REFERENCES.md](REFERENCES.md), pinned YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` `DriveLocomotionClass.h`,
`LocomotionClass.h` and `Matrix3D.h` (including its Quaternion declarations),
and recomp snapshot `eebcf725ef99f942a8f9a5e0437a8a6154d7d439`
`docs/voxels.md` Shadows / LICENSE. Hypothesis: body drawing consumes stored
ramps and their timer, unlike the shadow's current-Cell lookup. Exact base
inspection/execution establishes the behavior below; YR/recomp declarations
remain leads. No YRpp license file was found; recomp's MIT excludes generated/
lifted game code, and its stale The Movies wording remains recorded. No upstream
headers, generated/lifted code or extracted tables were incorporated. No dependency
or THIRD_PARTY.md change.

## Executed scope

[verify_drive_body_pose.py](../tools/verify_drive_body_pose.py) pins **17 complete
added/retained ranges / 1,024 instructions**, including the two-instruction type
dispatch tail. Earlier numeric/initializer and ramp-state ranges remain pinned.

| Root | Executed scope |
| --- | --- |
| `0x4A0050..0x4A04F5` | Complete Drive body pose/key, 342 instructions |
| `0x53D030..0x53D0CF` | Actual base heading pose/key |
| `0x718D60..0x718D7C` | Direct selected ramp-matrix copy |
| `0x718DF0..0x718E64` | Previous/current ramp interpolation or equal-ramp copy |
| `0x622AC0..0x622C59` | Quaternion interpolation, actual table acos/sine |
| `0x622EB0..0x622FA5` | Quaternion-to-matrix conversion |
| `0x4A4D20..0x4A4D3C` | Signed timer remaining |
| `0x6C12C0`, `0x705020` | Actual Unit type dispatch/getter |

Actual Facing, translation/rotation/multiply/copy/identity and original FTOL
children execute unchanged. The same guest first runs both stock numeric chains
and the complete initializer. It compares all **84 dwords** at `0xAF6618` and
audits their 84 original dword stores. All 21 previously verified matrices at
`0xAF8608` feed the settled body path as well as shadows. No synthetic guest
instructions, original instruction patches or numerical replacement services.

Selected cases run actual Drive Unlimbo/Force or only Process's established
`0x4A05F0..0x4A064A` ramp prefix immediately before the body consumer. The suffix
and complete movement/placement callers remain excluded. Two actual current-Cell
lookups are retained; all fixture coordinates are resident. Temporary timer padding
is an explicit zero supplied at the Force child/prefix boundary, not recovered
initialization. Earlier state-writer evidence covers its other values separately.

## Preserved behavior

[DriveBodyPose.cpp](../src/render/DriveBodyPose.cpp) preserves:

- Signed wrapped timer subtraction and compare-before-subtract, including start
  -1 and duration zero. A fraction unequal to one, or either absolute rocking
  float at least the original **double 0.005**, selects the transient path. The
  float nearest 0.005 lies below that threshold.
- Settled cache identity writes `key << 6`, adds current ramp, then actual base
  heading writes `key << 5` and ORs a second Facing result. All packing wraps.
  Null/-1 keys still construct the full matrix; transient nonnull keys receive
  -1 even when already -1.
- Transient drawing queries type twice, narrowing doubles `+0x330` / `+0x338`
  into separate floats. Original table trig, intermediate truncations and sign
  gates produce rocking X/Y translation and Z lift. Rotations run X then Y.
- A nonzero duration and fraction below one selects previous-to-current
  interpolation. The interpolation wrapper narrows its double fraction to float;
  equal ramps copy the existing matrix. Other cases copy current ramp directly,
  with zero retaining identity. Body ramp selection does not read the current Cell.
- Original table acos/sine weights, ordered dot products, table-square-root axis
  normalization and float32 component stores. The matrix conversion retains the
  inspected unrounded `x*z` for one entry while another uses its stored float.
  Stock ramp quaternions have Z zero; this is not general quaternion API proof.
- Final products are `slope * heading` for settled state and
  `((lift * slope) * heading) * rock` for transient state, with float32 stores
  between products. Every native call restores the incoming FP mode.

Stock quaternion entries 0 and 17..20 are identity; 5..8 and 9..12 repeat diagonal
tilts, and 13..16 use axis tilt with the same corner directions. The initializer's
decimal direction literals are retained. Host libm inverse trig is not substituted.

The profile supplies initial actor/type/locomotor/Facing/tick/map storage and
read-only observers. Type double association/initialization, mutable callback
aliasing, actor placement/height updates, full Process, startup order, ownership,
complete Unit drawing and frame/runtime integration remain open. General antipodal
quaternion behavior and arbitrary tilt tables are not claimed. Existing ground-world
receipts retain their supplied flat/settled lit state; older flat guards stay intact.

## Private data and evidence

[prepare_ramp_pose_data.py](../tools/prepare_ramp_pose_data.py) extracts only the
exact-engine inverse-sine table and four scalar constants, without execution.
The separate **16,456-byte** `RA2RPO1` artifact is ignored under
`private/derived/ra2-1006/ramp-pose-data.bin`, SHA256
`7b104361249101badc8e5d893ff1b4982377510642779baf417fe96c5073eb69`.
The reader checks full size/hash and optional source identity. Runtime executable
reads and existing prepared formats are unchanged; simulation remains SDL-free.

Receipts: `private/map-depth-1006/drive-body-pose-v1/`. Cases include every settled
ramp/32-bin heading, every 21x21 pair at ticks 0..3, changed/equal Cell ramps,
Unlimbo, null/-1/wrapped keys, signed timer edges/extrapolation, both rocking axes,
threshold/sign boundaries, finite type-double narrowing and dynamic Facing.
Four native FP modes cycle; selected identical cases and all quaternions run in
each mode. Exact twelve matrix dwords, final ramp/timer state, ordered Cell/type/
Facing/key events and final key match.

Counts: **3,197 body roots, 3,323 audited complete calls, 210 Process prefixes,
105 Unlimbo/Force calls, 1,618 interpolation wrappers / 1,555 quaternion conversions,
4,232 Facing calls, 3,836 type queries and 5,817 key writes**. Guards cover inspected
execution bounds, exact dispatch/code/data identity, return/ESP/callee-saved/caller
stack, image writes, immutable code/tables/inputs, whole arena canaries and permitted
state/output/key writes. Full memory-read/native internal-store order is not claimed.
Fifteen native domain refusals and three corrupted prepared-reader inputs are
separate safety checks, not original malformed-input parity. Interpolation angles
whose scaled index cannot fit int are refused before a C++ narrowing overflow.

First complete comparison passed 3,201 cases. Inspection then added the integer
conversion guard, retained the unrounded matrix product and tightened dispatch/
quaternion-store audits; the final fresh run again passes. The first verifier
range was two bytes short and was corrected to end after the actual ret. Ad hoc
imports initially omitted tests/ from the search path. No failed expectations were
accepted or original instructions modified. First build and earlier inherited-work
elapsed are unavailable. Final fresh CLI/original/native times are
**9.974 / 8.155 / 0.048 s**; replay/build/check accounting is in [HANDOFF.md](HANDOFF.md).

## Reproduce and continue

```sh
build/tools-env/bin/python tools/prepare_ramp_pose_data.py \
  --exe private/official-1006-probe/game.exe
./build.command
./test.command
PYTHONDONTWRITEBYTECODE=1 build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

# Fresh original execution requires authorized Mac host JIT and a new destination.
build/tools-env/bin/python tests/compare_drive_body_pose.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/drive-body-pose-new
build/tools-env/bin/python tests/compare_drive_body_pose.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/drive-body-pose-v1/expected.json \
  --report private/map-depth-1006/drive-body-pose-v1/replay-new.json
# Add --native build/sanitize/drive-body-pose-vectors for sanitizer replay.

./run.command --crossing-light-demo
```

The demo is unchanged: select the Rhino, G/right-click moves, L toggles the light,
R resets. Only Apple Silicon macOS is tested. Next recover actual placement/movement
callers and join the established state writers/body pose to prepared-map complete
drawing before runtime promotion. Actual SDL level crossing and parked `(51,72)`,
elevation 4 remain acceptance scenarios. No new playable or whole-frame parity claim.
