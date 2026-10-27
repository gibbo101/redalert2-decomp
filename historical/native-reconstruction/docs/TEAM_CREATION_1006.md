# TeamType factory on the first-objective action path

Successor: [TEAM_CONSTRUCTION_1006.md](TEAM_CONSTRUCTION_1006.md) now binds the
complete constructor parent to the actual mission owner. The factory origin
below keeps its supplied-constructor evidence scope; it is not relabeled.

This work addresses the demonstrated first-objective Create Team blocker in
[FIRST_DAY1_TRANSITION.md](FIRST_DAY1_TRANSITION.md). It recovers the complete
6BEC80 factory and joins it to the actual action4 caller in original and native
research. The owned mission action uses that factory instead of treating its
entry as a completed request. **Team construction, four GIs, placement, script
execution and live Objective1 remain incomplete.**

## Exact original evidence

Target:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Factory6BEC80 is138 bytes/47 instructions,
SHA256 `54a39ee9595d34dba0d18c4aeabc4f6ff0a33a18b773a8790c47a88946f0fad3`.
`tools/verify_team_creation.py` fingerprints the complete factory plus the already
verified complete action4 dispatch branch/tables before using addresses.

382 complete original roots match native:218 direct factory calls and164 actual
action4 -> factory roots. Logger4068F0, House count4F35F0, allocation782017 and
constructor6B7430 are named supplied children. Original factory and dispatcher
instructions execute unchanged; no original instruction executes in the app.
Caller stack, return address, saved registers, code/tables and unrelated arena
bytes are audited. Diagnostic child mutations have their own explicit scope.

The original-only origin is
`private/team-creation-20261019/fresh-a1/expected.json`; normal commands explicitly
reuse it and execute current native. This does not cache native pass/fail or alter
old action4 receipts. The older24-case action4 matrix remains separately reusable.

## Recovered behavior

`src/sim/TeamCreation.hpp` borrows Type identity/default HouseC0/maximumB8/countD4
and its name. It logs first, then resolves explicit House versus the live default
House. Only loading0 and a nonnegative maximum enter limit handling. Session0
uses Type count; other modes call House count, then reread the live maximum after
that child. Both compare signed values and reject count>=maximum. Nonzero loading
or a negative maximum bypasses limits.

The second logger precedes allocation156. Null allocation returns null without a
constructor request. Success forwards the allocated record, same Type, saved
chosen House and argument0 to6B7430 and returns that child's pointer unchanged,
including null or a different diagnostic pointer. The logger/name, heap and
constructor remain supplied services; a result pointer does not prove a valid
constructed Team or ownership. Unbound entered children refuse. A propagated
constructor exception retains action4's earlier increment, matching its existing
no-rollback boundary.

Cases cover direct/action entry, depth0/1/0xFFFFFFFF, signed limit/count edges,
null/default/explicit Houses, allocation failure and constructor return identity.
Named children mutate loading, default House and maximum at the original call
boundaries. In particular House-count comparison uses the new maximum, while
constructor uses the House saved before the later logger/allocation changes.
Action4's post-call decrement consumes the live global, including child rewrites.

## Actual Day1 association and missing child

The existing mission owner associates the actual0B197B7C record with its supplied
map House, Max and name, using the same stable TeamType identity and shared depth.
Its factory call requests156 bytes from retained owner-local diagnostic storage,
then enters the explicit constructor service. Telemetry records factory,
allocation and constructor requests separately. That service still records only
the original constructor request; it neither initializes a Team nor allocates
members. Clone checks include the new counters and bind fresh owner-local storage.
Startup Type/count/session associations remain supplied, not original loaders.

For the actual initial counter0, action4 increments to1 before entering6BEC80.
The joined original fixture verifies the limit/session block is not entered on
that path. Thus general team-count handling is not an additional first-objective
prerequisite. The next demanded child is6B7430, followed by the actual Script/
TaskForce/member producers that this Type enters. Initial aligned constructor
inspection is private, not executed recovery. Do not turn the four-GI name or
constructor request into a synthetic four-unit spawn.

## Commands

```sh
./build.command
./test.command
build/native/boot-camp-walk-check private/official-1006-probe
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest tests/test_team_creation.py
```

Use fresh report/audit destinations for explicit original reuse:

```sh
PYTHONHASHSEED=0 PYTHONDONTWRITEBYTECODE=1 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/NEW-team-creation.audit.json tests/compare_team_creation.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/team-creation-vectors \
  --expectations private/team-creation-20261019/fresh-a1/expected.json \
  --report private/NEW-team-creation.json
```

Sanitizer uses `build/sanitize/team-creation-vectors`. Fresh generation after a
genuine original-input/oracle/environment change replaces expectations/report with
`--output private/NEW-team-creation` and needs host Unicorn JIT permission.
Current native changes alone reuse originals. The startup/presentation route
remains `./run.command --boot-camp-walk`; this work does not enable live discovery
or objective actions. No worker, Windows action/transfer, download, runtime-read
expansion, public copied code, dependency or system/Xcode/DRM change is introduced.
Only Apple Silicon macOS tested; local checks are not independent acceptance.

## Current validation and costs

228 native and227 ASan/UBSan CTests pass, as do both actual-map owner checks,
seven focused Python guards and the256-tick actual desktop SDL smoke. Each build
replays382 factory/joined originals and24 legacy action4 originals:406 hits,
zero misses, always current native. The two horizontal GI captures are byte
identical to `private/gi-facing-recheck-20261019-a2/`'s inspected facing fix.
SDL still reports objectives disabled; no player-driven first transition is claimed.

Fresh382-answer original generation took0.113s. Successful normal/sanitizer builds
took51.489/34.629s; actual owners9.477/83.531s; test suites10.319/31.833s;
focused Python.569s and SDL6.495s. New native comparison kernels took.016/.204s;
legacy action4 kernels.004/.150s. Full comparison commands including evidence
wrapper cost1.183/.546s for the new family and38.021/28.965s for action4.
Those wrapper costs are not original execution costs. Concurrent costs are
nonadditive. Manual inspection, initial focused builds and total wall time were
not measured. Per-command timing/arguments/logs are under `validation/`.

Preserved failed attempts: the first focused target build preceded CMake
reconfiguration and reported an unknown target. Initial full normal/sanitizer
builds failed in15.227/35.155s because three lambdas referred to the constructor's
`source` parameter without capturing it. The repair uses the retained owner's
`this->source`, preserving lifetime; both builds and all affected checks above
then pass. No original answer was regenerated for that native-only repair.
Delivery/source/evidence hashes: `private/team-creation-receipt-a1.json`.
Local verification is not independent acceptance.
