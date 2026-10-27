# Stationary allied Unit admission through complete Process

The later [shared parked ownership join](OWNED_UNIT_RESIDENT_1006.md) binds this
entry to production owned two-Unit membership in its recovery/native ownership
drivers. The SDL demo remains one Unit pending parked drawing/selection.

After `a8bc50a`, a separate SDL-free `processResidentOrdinaryGroundDrive` entry
handles actual allied stationary-Unit admission result 6 in complete ordinary
Process. **137 fresh results / 1,192 complete original ticks** match native,
followed by normal and ASan/UBSan replays. This entry is **unwired**. It is a
prerequisite for the next parked-Unit capability; the terrain demo still owns
one Unit. Base RA2, then Yuri's Revenge, remain incomplete. No workers.

## Original caller and preserved effects

Both ordinary Process preparation calls, `4A0734` and `4A0B70`, pass preparation
flag 1. Actual stack arguments are checked at every entry. The result-6 branch
therefore uses retry handling, rather than entering the flag-zero close-enough
or Cell-scatter branches. Their existence does not imply ordinary Process takes
them. The recursive preparation at `4A4513` passes flag 0 after queue[0] clears;
it enters the empty-queue failed-pathfinder boundary in this profile.

First admission6 clears queue[0], writes retry start/current tick, copies the
opaque word from its temporary +48 slot, writes remaining zero, then recursively
prepares. Unlike first result7, it does **not** clear a nonzero Drive head before
the queue/timer writes. Two actual nonzero-head entries verify this distinction.
Second admission6 runs after track assignment, clears queue[0], copies the
separate temporary +54 word and joins the same retry. It retains the assigned
track at that boundary. All remaining queue words survive. Do not normalize 6
to 7 or a generic blocked flag.

`GroundDriveResidentRetry` supplies those two opaque words independently of the
existing ramp/retry padding input. The oracle supplies each word exactly at its
original load, without modifying instructions. The recursive empty-queue path
also copies its separately supplied temporary padding; later stores can overwrite
the earlier timer words. Both intermediate ordered stores and final state are
compared. This does not recover original temporary initialization or retry-delay
configuration; delay remains supplied zero.

The earlier ordinary, gated and 0/3/7 admitted entries keep their scopes. Only the
new entry permits preparation6. Advance's rejected-switch caller still requires
zero. A new native safety scenario requires an actual admission6 trace immediately
before the typed unsupported-Advance refusal. Nonzero Advance effects are not
silently discarded. The flag-zero scatter/close-enough route, other unsupported
codes, moving/crushing residents, bridges, overlays and special actor branches
remain outside this extension.

## Exact-binary evidence and scope

Both private supplied engines remain 4,485,392 bytes / SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`:
`private/official-1006-probe/game.exe` and
`private/windows-baseline-20261014/game.exe`. Embedded 1.08, supplied 1.006 lineage
and reported no-CD changes remain distinct; pristine authenticity is unverified.
The already authorized Windows copy was present; no transfer or Windows action
was needed.

Current proof is `private/map-depth-1006/ground-drive-resident-process-v4/`.
Actual returns are 33 zero, 98 code6 and 12 code7. First preparation returns6
74 times; second returns6 24 times. Both enclosing Process callers reach6:
97 idle-caller entries and one post-Advance entry. Every one of 1,192 actor57A
samples is read from the original guest. There are 3,365 selected preparation
stores, 31 actual next-Cell calls, 3,053 distinct entered instructions and 209
stationary-record checks. Zero result3, nonzero Advance, false gates and actual
scatter are not new original coverage here; older proofs retain their scopes.

Stationary residents use the actual Unit vtable, Unit/type/Drive associations,
empty passengers and promotion state, and optional settled Facing/Drive queries.
Their full actor/type/locomotor records are checked unchanged after each sequence.
Tests include all directions, first/second admission, turning before admission,
empty-Cell movement before a later resident, nonzero retained heads, queue tails,
shared Next lists/self-skip/fallback identity, allied House indices/masks, zero
Track-speed override, signed clocks/padding and all four incoming native FP modes.
Native rounding restoration remains checked.

The same guest executes complete unchanged Process/preparation/Advance and actual
Unit admission/terrain/gate/House/Mission/kind/Facing/Drive/next-Cell children. It
retains the earlier code/dispatch/input, instruction/write allowlists, caller
stack/register/tail and full arena audits. No supplied service is allowed inside
actual admission or next-Cell. Original results are expectations for tests, never
runtime input. Initial actors/types/House/Cells/directions/speed/route records,
settled states and their associations remain supplied. Mark, occupation,
notification, other mission and failed-pathfinder effects are diagnostic services
in this fixture. It does not join production mutable membership or construction.

No upstream/header/generated/lifted code, table or dependency was incorporated.
Pinned YRpp names remain leads only; exact base callers and execution decide the
new behavior. YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88` still has no license
file found. Retained recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439` MIT terms
cover its authored tools/docs, exclude lifted/original code and retain stale
The Movies wording. See [REFERENCES.md](REFERENCES.md).

## Verification and runtime boundary

Both builds, **869 Python tests / 63 normal / 62 sanitizer CTests** pass. The new
proof has seven native safety refusals and receipt/parser/source guards. v1
contains the initial 113 cases; v2 predates the explicit nonzero-head/both-caller
assertions, and v3 predates the stricter actual-Advance6 trace assertion. None
is relabeled as the final proof.

The existing arm64 SDL demo passes selection/right-click/G movement, terrain
refusal, active-track stop, body/turret turns, live membership, crossing/ramp and
parked-cliff checks. Crossing remains 78 updates; ramp remains 44 / 29 tilted /
one lag / 23 positive-height samples. Cliff remains Z416 / depth-52 / 153 visible /
886 rejected. The terrain-refusal rendered frame was viewed. The initial sandbox
launch could not access a display; the host desktop rerun passed. Injected SDL
events and native rendered frames establish integration/presentation QA, not
original-game observation, OS pointer/keyboard acceptance or whole-frame parity.

Runtime shared renderer preparation is still immutable. No new executable-read
boundary, private data format, source-install/disc/outpost2 write, download,
DRM/system/Xcode change or publication occurs. Only Apple Silicon macOS is tested.
Current affected legacy proof identities and final receipt audit are in
[HANDOFF.md](HANDOFF.md).

## Reproduce and continue

```sh
./build.command
./test.command
build/tools-env/bin/python -B -m unittest discover -s tests -p 'test_*.py'
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

# Fresh original execution requires authorized host Unicorn JIT and a NEW output.
build/tools-env/bin/python -B tests/compare_ground_drive_resident_process.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/ground-drive-resident-process-new
build/tools-env/bin/python -B tests/compare_ground_drive_resident_process.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/ground-drive-resident-process-v4/expected.json \
  --report private/map-depth-1006/ground-drive-resident-process-v4/replay-new.json
# Add --native build/sanitize/ground-drive-process-vectors for sanitizer replay.
./run.command --terrain-demo
./run.command --terrain-smoke-test private/map-depth-1006/terrain-resident-local-new
```

Next join a stationary resident through actual Unit Mark and shared owned
membership/discovery/occupation/recalculation, then this Process entry. Preserve
both Unit Next/list identities, House/type associations, immediate recalculation
and independent clone storage. Existing `PreparedUnitMembership` hardcodes actor0
and notification state; `PreparedUnitAdmission` explicitly refuses extra actors.
Those guards must be replaced by verified associations, not removed in isolation.
The original owned-map oracle also normalizes Cell heads/Next only to null/Unit0;
extend its complete arena/ordered-write audits before accepting resident results.

Then add the parked Unit to drawing/selection and test movement toward it and
across empty Cells through actual SDL. That acceptance still precedes a playable
multi-Unit claim. General pathfinding, scatter/close-enough flag-zero callers,
nonzero Advance admission, combat/economy/AI/campaigns/multiplayer/audio/saves and
YR remain later work. Keep the whole-game goal active.
