# Ordinary terrain-aware Drive Process and preparation

The later [result-bearing gate join](GROUND_DRIVE_GATE_PROCESS_1006.md) executes
actual gate children through complete Process/preparation/Advance, including
false waits before Facing/admission/commitment. It preserves this legacy entry's
supplied-success scope. Its admission/next-Cell services remain supplied and the
new entry remains unwired. This older proof is freshly ground-drive-process-v3,
with unchanged v2 command/result/label projection and both replays.

Later [gate recovery](MOVEMENT_GATE_1006.md) identifies the provisional direct
reserve/55ACD0 service as gate interaction. This note's supplied-success profile
and historical reserve/R protocol remain unchanged. Real false returns still need
a result-bearing preparation/Process join; they are not supported by this entry.

After `2700647`, **194 fresh sequences / 28,552 complete original Process calls**
match native, followed by normal and ASan/UBSan replays. This checkpoint joins
complete ordinary Process, preparation and Advance with
actual Foot/Object location, relative height, map/Cell floor, Facing, speed,
track transforms and interpolation. The helpers remain unwired; SDL gameplay,
prepared-map drawing and whole-frame fidelity are not established by this test.
Complete native base RA2, then Yuri's Revenge, remain incomplete.

## Identity and reference boundary

Both supplied engines rehash equal: `private/official-1006-probe/game.exe` and
`private/windows-baseline-20261014/game.exe`, 4,485,392 bytes / SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Fresh isolated execution uses the first. Embedded 1.08, supplied 1.006 lineage and
reported no-CD modifications remain distinct; pristine authenticity is unverified.
No new Windows action, transfer, download, installation/disc write or system change.

Consulted [REFERENCES.md](REFERENCES.md), the pinned YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` DriveLocomotion declarations and
retained recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439` reference context.
Hypothesis: preparation's floor/speed decisions and Process's pre-movement ramp
observation must be recovered together with queued movement. Exact base execution
and inspection decide behavior. YR/replacement behavior is not the oracle.
Existing license boundaries apply: no YRpp license file found; recomp's MIT grant
excludes generated/lifted game code. No upstream/header/generated/lifted code or
extracted data incorporated. No new dependency or runtime executable read.

## Bounded profile

The simulation core is SDL-free. `GroundDriveProcess` accepts supplied, sentinel-
terminated direction queues and shared resident/fallback Cells. Healthy ordinary
Unit, Move mission, Accelerates=0, IsTrain=0, Passive=0, no bridge, overlays,
occupants, destination object, jumpjet, turret rotation or special tracks.
Initial actor/type/map/table state, land speed and slope factors are supplied.
Admission always succeeds, reservations succeed, occupation/Mark/notifications/
mission effects are explicit supplied services. The pathfinder supplies failure;
there is no general pathfinding implementation. Retry delay is supplied zero.
Copied temporary timer padding is supplied at the child boundary, not recovered
initialization. Arbitrary service mutation, aliasing and exceptions are outside
this profile.

`verify_ground_drive_process.py` pins the complete 493-instruction Process
`0x4A05F0..0x4A0BBB`, complete 2,583-instruction preparation
`0x4A2670..0x4A4725` and the existing complete Advance. Additional actual children
include current-Cell/coordinate/absolute-height getters, Cell center/neighbor,
health fraction, desired/rotating Facing, timer, IsMoving and moving predicates,
vector construction and original table square root. Admission, reservation,
occupation, mission and pathfinder remain services even though their caller
instructions execute.

## Behavior preserved

- Process observes the actor's current ramp before moving, through two actual
  coordinate lookups. Changes store previous before current and restart the
  three-tick timer; equal ramps retain the timer.
- Preparation reserves the next Cell before deciding whether to turn. Turning
  does not consume the route or commit a track. Completion notification occurs
  on the later Process update that sees turning end.
- Admission runs between Mark(0) and Mark(1). Repeated word-Cell queries, signed
  level differences and the forced land selector for differences >=2 remain.
- Land speed is loaded as float, clamped above one before slope multiplication,
  then uses actual next-Cell center/local floor, separate next map-floor and
  current map-floor queries for uphill/downhill choice. A resulting exact zero
  becomes one half. The later speed setter has its own clamp.
- Saved Cell records retain identity. Intervening map-floor queries can change
  the shared fallback record's coordinates before the neighbor helper reads them;
  copying the first query's word coordinates loses original behavior.
- Track selection uses two directions, straight fallback, and one/two-entry
  queue consumption. Word coordinates wrap; world additions wrap separately.
  The original retained queue capacity tail is preserved in the supported
  sentinel-terminated domain.
- With no second queued direction, distance to destination can trigger a failed
  route request and mission service before committing the first direction.
  Original table square root and integer conversion determine that boundary.
- The occupation helper may mark the transformed descriptor Cell point before
  the head, using actor absolute Z. This is separate from committed track Z=0
  followed by actual SetHeight(0).
- A non-Passive Unit can still query current level and admission at a curve's
  switch point before rejecting the switch. Its committed track remains intact.
- Process can finish a track, prepare another, then run Advance again with speed
  suppressed in the same tick. Preserve signed residual/arrival arithmetic and
  the earlier fractional interpolation that retains Z without SetHeight.

## Evidence and limits

Current receipts: `private/map-depth-1006/ground-drive-process-v1/`. All 64 queued
direction pairs, all 21 ramp indices, three-level terrain differences, distinct
float land-speed entries, slope factors, one/two-entry queue consumption, turning,
long mixed routes, signed tick wrap, shared fallback and zero/nonzero marked bytes
are covered. Original caller FPCW is supplied 0x0E7F; four incoming native modes
are tested with restoration. Fifteen malformed/domain refusals are native safety
checks, not original malformed-input parity.

There are **19,207 actual preparation calls, 27,226 Advance calls, 22,930 Foot/
Object location setters, 15,258 SetHeight calls, 16,326 map-floor queries, 16,860
Cell-floor queries, 91,886 full-coordinate lookups, 4,148 word lookups, 36,652
transforms and 7,672 interpolations**. Original Facing desired setter enters 140
times; 26 actual current-level queries precede rejected non-Passive switches.
There are 159,758 selected actor stores and 2,316 supplied Mark calls. The added/
retained complete inspection family has 18 ranges / 3,565 instructions, including
complete Process and preparation; earlier Advance/floor ranges stay pinned.
Return/ESP/callee-saved/caller-tail,
code/dispatch identity, instruction/write allowlists, actor/locomotor/Cell arenas,
ordered selected actor/ramp stores and named service calls are audited. Full native
internal write order and full memory-read order are not claimed.

The earlier no-queue Advance scope remains distinct. Its changed native source
has fresh `ground-drive-advance-v3/` proof: 514 sequences / 10,866 complete calls
and both replays. Commands, results and labels equal v2; old receipts retain their
historical source identities. This join uses synthetic Cells, not the finalized prepared map.
Stored ramp output still needs to reach complete body/shadow/drawing consumers on
that shared map before runtime promotion and actual SDL crossing/parked-cliff
acceptance at `(51,72)`, elevation 4.

Initial execution allowlists stopped at actual coordinate construction, table
sqrt and current-level children; each was inspected before admission. Native
comparisons rejected missing second-Cell admission and a copied fallback position.
The new live-record service fixes the latter. Final fresh evidence/replays pass;
no original instruction was patched or failed expectation accepted. A missing
prepared-data include caused one compile failure and was corrected. An initial
sanitizer target request preceded CMake regeneration and was retried after normal
configuration; no system-wide tool selection changed.

Both builds, **732 Python tests, 52 normal / 51 sanitizer CTests**, source/AST/link
and diff checks pass. Closing inventory: **92 replay sets / 4,258 source entries**,
recursively 4,524 checked. **88 prior sets retain unchanged identities without
reexecution**. Audit: `private/map-depth-1006/ground-process-closing-audit.py` and
JSON, 911 source candidates. Native arm64 app retains SHA256
`b736d7429556ba10b90e3122c870db28b8b13b4ceb6d73c23b25aaf7dcf031a5`.
No new SDL capture; earlier SDL evidence applies to this unchanged runtime only.
These are local checks, not independent acceptance or completed terrain gameplay.

Fresh Process CLI/original/native: **57.693 / 55.122 / 0.282 s**. Normal replay
CLI/native: **2.509 / 0.286 s**; sanitizer **4.636 / 1.324 s**. Refreshed Advance:
**16.736 / 15.388 / 0.097 s** fresh, normal replay **1.875 / 0.085 s**, sanitizer
**4.627 / 1.938 s**. Boundary build **20.328 s**, test-command **2.078 s** (CTest
1.36), Python unittest wall **2.109 s** (unittest 0.417), sanitizer build **13.685 s**,
sanitizer CTest wall **4.629 s** (CTest 4.32). Independent checks/oracles ran
concurrently, so these are elapsed measurements under that load. Earlier builds,
failed-attempt totals and full inherited delivery work are not separately measured;
intervals since the previous commit include idle time. No workers or caching
infrastructure introduced.

```sh
./build.command
./test.command
PYTHONDONTWRITEBYTECODE=1 build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

# Fresh original requires the authorized host JIT and a new private destination.
build/tools-env/bin/python tests/compare_ground_drive_process.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/ground-drive-process-new
build/tools-env/bin/python tests/compare_ground_drive_process.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/ground-drive-process-v1/expected.json \
  --report private/map-depth-1006/ground-drive-process-v1/replay-new.json
# Add --native build/sanitize/ground-drive-process-vectors for sanitizer replay.

# Existing playable baseline; new terrain-aware caller is not wired here yet.
./run.command --crossing-light-demo
```

Select Rhino, G/right-click moves, L toggles light, R resets. Only Apple Silicon
macOS is tested. General pathfinding, combat, economy, AI, campaigns, multiplayer,
audio, original saves and Yuri's Revenge remain later work.
