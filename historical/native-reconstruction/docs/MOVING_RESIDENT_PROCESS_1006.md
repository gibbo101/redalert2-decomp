# Moving Unit result2 inside complete ordinary Process

`processMovingResidentOrdinaryGroundDrive` is a separate opt-in simulation entry
joining complete Process/preparation/Advance with actual moving Unit admission.
It remains **unwired**. Runtime moving-resident, nonzero Advance and scatter
refusals remain, and the resident demo keeps one mover and one inspection-only
parked Unit. Current accepted proof/replays and regression status belong in the
opening [handoff](HANDOFF.md); a private pilot is not a canonical receipt.

The shared kernel retains the earlier ordinary/gated/0-3-7/stationary-resident
entries and their default domains. The original complete roots remain Process
`4A05F0`, preparation `4A2670`, Advance `4A1000` and admission `703040` with the
children recorded in [MOVING_UNIT_ADMISSION_1006.md](MOVING_UNIT_ADMISSION_1006.md).
No supplied callback supplies an admission return or modifies original code.

## Recovered caller effects

First preparation result2 clears a nonzero old Drive head through the existing
clear path before checking actor+5A1. Only a zero byte initializes it: write1,
then timer start/current tick at+558, opaque temporary padding at+55C, then
Rules+13D0 duration at+560. A nonzero initial byte retains all three timer words.
These ordered writes are separate from the retry timer at+530/+534/+538.

The retry timer is tested first. Its signed wrapped tick-minus-start calculation,
signed duration comparison and wrapped subtraction retain original sentinel
start=-1 behavior; do not normalize negative durations or replace it with an
unsigned host timeout. A nonzero remaining retry joins the bounded57A-zero path,
clears actor57A, writes Drive+58=-1 and retains the entire queue. The additional
sound branch for a nonzero57A remains excluded.

Expired retry tests the newly separate wait timer with the same signed/wrapped
semantics. The original selects failed-pathfinder option2 when the wait has
expired and option1 otherwise. `GroundDriveMovingWaitServices::failedRoute`
represents the named supplied failed pathfinder, false accessibility and mission
request in order. Its observed option is compared; no pathfinding implementation
or successful path result is inferred from this callback. Initial wait/retry
words, Rules duration and temporary padding remain supplied fixture inputs.

Second preparation result2 calls preparation recursively at`4A41DA`, preserving
its flag argument and setting the third argument to1. Ordinary enclosing Process
callers use arguments1/0; this recursive entry uses1/1. The third argument forces
the second direction to equal the first before transition selection. This is
distinct from result6's flag0 retry after queue[0] clears. Preserve assigned
track, head, all24 queue words and the selected ordered stores at each boundary.

Actual Advance dispatch sends0 and2 to the same Unit-kind1/Passive0 rejected-
switch path before commitment. Only the new entry permits2 at that tested
boundary. It does not turn every nonzero code into success or a no-effect wait.
Advance6/7 and other nonzero outcomes retain typed explicit refusals, and the
flag-zero scatter/close-enough branch remains refused.

## Evidence, identity and supplied state

The original fixture subclasses the existing resident Process oracle with
class-owned ranges/exclusions/Advance results/preparation caller maps. Legacy
defaults remain intact. Extra wait writes are exactly three dword stores at
their inspected instruction addresses; the full actor audit allows exactly
the12-byte wait record. Every scenario resets all additional timer words before
the original arena snapshot, so one case cannot inherit another case's wait.

Unchanged complete Process and actual gate/admission/terrain/House/Mission/kind/
Facing/Drive/next-Cell/numeric children execute in one guest. Both original
Process preparation callers must actually return2, as must the narrow Advance
caller. Coverage requires measured recursive1/1, wait initializations and ordered
stores, signed clock boundaries and both pathfinder options. All eight directions,
incoming native FP modes, full destination versus head-X/Y activity, Drive+A4
true/false, later stationary6 and late zero-speed7 are exercised. Native safety
fixtures trace actual native admission6/7 immediately before Advance refusals;
they are not additional original-game observations.

A separate private two-scenario/eight-tick diagnostic checks first2 with a
nonzero old head, including clear-before-5A1/wait-store order and nonzero5A1
retention. Complete original streams match both native builds, with source,
runner and canonical-expectations fingerprints checked before and after. It
supplements the canonical suite without changing its case count or identity;
its path and limits are recorded in the handoff.

Instruction/write/input/dispatch/numeric, complete actor/type/House/Drive/Cell/
slot arenas and caller registers/stack remain audited. Resident addresses stay
distinct, but their motion/Facing/queues are supplied initial records checked
unchanged; they do not take their own Process ticks in this fixture. Mark,
occupation, notification and other mission/pathfinder effects remain named
diagnostic services. This is not production owned movement or startup proof.

The separate diagnostic M protocol extends the existing native vector runner,
with explicit motion/wait records and private direction/render data. Legacy
P/G/A/R protocols retain their domains. Source/runner/input/receipt identities
are checked before and after each accepted run. Fresh results are test-only
expectations, never native runtime state. Native tests and SDL regressions
establish integration, not whole-frame fidelity or independent acceptance.

Both supplied engines remain4,485,392 bytes /SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage and reported no-CD provenance remain distinct;
pristine authenticity is unverified. Existing recomp/YRpp naming references keep
the license restrictions in [REFERENCES.md](REFERENCES.md). No upstream/header/
generated/lifted code, extracted table or dependency is incorporated. No runtime
executable-read expansion, Windows action/transfer, source installation/disc/
outpost2 write, download, system/Xcode/DRM change, worker or publication occurs.
Only Apple Silicon macOS is tested. Base RA2, then YR, remain incomplete.

## Reproduce and continue

```sh
./build.command
./test.command
build/tools-env/bin/python -B -m unittest discover -s tests -p 'test_*.py'
build/native/ground-drive-process-vectors --guards

# Fresh original execution needs authorized host Unicorn JIT and NEW output.
build/tools-env/bin/python -B tests/compare_moving_resident_process.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/moving-resident-process-new
# Replay: add --expectations CURRENT_EXPECTED_JSON --report NEW_PRIVATE_JSON.
# Sanitizer replay: add --native build/sanitize/ground-drive-process-vectors.
./run.command --resident-demo
```

Next join live motion records and genuine per-actor Process/queue/Facing/retry/
wait/turret owners with actual mutable membership. Preserve immediate shared
fallback, Next/lists/occupation/discovery/recalculation and drawing isolation.
Require Process0 -> Process1 -> interleaved complete draws at both distinct
original actor/Drive addresses, followed by later Process, before enabling
Unit1 commands and actual SDL acceptance. General pathfinding, combat, economy,
AI, campaigns, multiplayer, audio, saves and YR remain open. Keep the full-game
goal active.
