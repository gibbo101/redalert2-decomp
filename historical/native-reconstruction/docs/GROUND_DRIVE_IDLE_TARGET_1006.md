# Inactive-track Process target handling

`processOrdinaryIdleTarget` is a separate SDL-free dependency for the complete
Process join. It reconstructs the interior before the rotation test, using the
actual borrowed Unit destination, Drive, actor, mission and 24-word queue records.
It either identifies the original early false return or continues to the rotation
test. It does not execute complete Process or enable runtime Scatter/Advance6.
The existing two-commandable-Rhino `--owned-demo` capability is unchanged.

## Exact original and recovered behavior

The supplied target remains 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
It was rehashed before using these addresses. Embedded1.08, supplied1.006 lineage
and reported no-CD provenance are distinct; pristine authenticity is unverified.
Existing [reference and license boundaries](REFERENCES.md) apply. No new upstream
code, generated/lifted output, reference header, extracted data or dependency was
incorporated.

The original interior starts at `4A0770`, after complete Process selects an
inactive track (`track == -1` or driving byte zero). `ESI` denotes the Drive+4
interface and `EDI` the full Drive. The first continuation is `4A0879`, before
Facing::IsRotating. Successful paths execute the actual Process epilogue/ret4.
This supplied interior context does not establish the enclosing caller behavior.

- A nonnull target receives its actual kind query. Kind11 selects a Cell.
  The target pointer is saved after that query. Actual actor virtual1A0,
  `41B320`, divides signed location X/Y by256 and then truncates to signed words.
  These are compared against the target's **direct +24/+26 words**. Target Y is
  read only after X matches. No target center, floor, Foot/head/registry query or
  terminal height threshold belongs to this predicate.
- If that predicate fails, **raw mission98 == 5**, a zero driving byte and a
  nonempty Drive destination must all hold. The actor's location and destination
  must match in all three components. The mission getter and queued mission do
  not replace the raw mission test; head coordinates do not replace the actor.
- On either match, vector count488 equal to zero calls actual Unit virtual410
  `7053F0(null,1)`, including the already recovered ordinary Unit/Foot/Drive null
  destination chain. Its same-null-target fast return can retain a nonempty
  Drive destination. Otherwise the actual vector clearing, stop cap, queue-head
  clear and word-at-a-time timer stores execute. All23 queue tails remain intact.
- Any **nonzero**, including negative, vector count executes `4CD9B0`: field490
  clears before target494. Virtual414(0,1) then runs as a **named supplied effect**.
  Its raw AL is ignored by this caller. Both matched branches return Process AL0.
  A failed predicate means continuation, not an invented Process return value.

The readable helper reuses `setOrdinaryUnitDestination`; it owns no mirrored
movement or command state. Target-kind/word bindings and initial class/Cell
associations are explicit. The native diagnostic accepts driving0/1 and kinds1/11;
other entered destination exclusions remain those of
[UnitDestination](UNIT_DESTINATION_1006.md), including non7/non16 ordinary powered
missions. Missing entered services and active-track entry are native refusals.
Refusals can retain actual prefix stores; there is no rollback claim.

## Differential evidence and limits

Canonical evidence is private under
`private/map-depth-1006/ground-drive-idle-target-v1/`:
**477 scenarios /886 original interior executions**, with534 continuations and
352 actual AL0 returns. There are441 actor Cell queries and target X reads, but
only196 target Y reads;195 Cell predicates match. The raw mission5/full-coordinate
predicate matches157 times. All162 actual Unit410 calls execute;82 enter the
Foot/Drive stop chain and80 take the same-target fast return. The190 clear/414
calls retain supplied mission effects. Nine heap disposals use the existing named
supplied service, not recovered heap destruction. There are328 distinct original
instructions executed.

Coverage includes signed division around zero and int32 extremes, wrapped signed
Cell words, negative direct Cell words that differ from center-derived words,
conditional Y reads, separate kinds/identities, all three destination components,
raw versus queued mission5, negative vector counts, ignored raw414 returns,
forced and same-target commands, owned/unowned vector buffers, stop percentages,
signed timer/padding extremes, all24 queue words and later calls. All21 supplied
target ramps are present in no-floor-query cases. They do not constitute new
floor recovery: no target-center/floor/map child executes in this suite.

Both normal and ASan/UBSan replays pass with distinct runner hashes. A second
**fresh original generation with inspection reuse disabled** reproduces every
command, label and expected output. Complete code/tables and declared inputs stay
immutable; original owner arena/unmodeled fields, selected ordered stores/queries,
caller/frame canaries, saved registers on early return and continuation register
identities are checked. Full floor/fallback/slot state remains unchanged. Seven
Python guards protect scope, source/receipt identity, parser and flow shape;
15 native guards pass per mode. This is local verification, not independent
acceptance, original-game observation or complete Process/game fidelity.

Current source/runner audits, complete stream equality, check logs and costs are
in `private/map-depth-1006/idle-process-candidate-20261017/validation.json` and
`checks.json`. Guarded fresh proof wall time is1.591s (original generation0.675s,
native comparison0.595s). Normal/sanitizer replay wall is1.045s/1.582s. The fresh
uncached control takes2.158s. These measurements do not justify extending persistent
original-result caching to this driver; it retains strict replay. Scheduling was
not controlled. Full manual review/repair and build wall time were not measured.

The first sandbox pilot exits132 because of restricted Unicorn JIT; its Mac-host
rerun passes. The first full audit fails at the inherited supplied heap import:
the new exact-instruction guard had omitted that existing checked service boundary.
The failed audit is retained; the corrected oracle passes at new audit paths.
Two read-only validation commands were corrected (system Python lacked pefile;
`git check-ignore --quiet` accepts one path). No original/native algorithm mismatch
or sanitizer defect was found.

No previous tracked implementation source, app target or existing runner changed.
Existing 200-record terminal-Advance closure stays immutable/historical; no closed
finalizer was rerun. No original family is relabeled as a new complete Process
proof. **1,108 Python tests,67 normal/66 sanitizer legacy CTests, both new standalone
CTests and `./test.command` pass.** There is no new SDL test/claim because no runtime
or presentation code changed. Only Apple Silicon macOS is tested.

## Build and reproduce

From the project directory, keep `DEVELOPER_DIR` as configured. No system tool or
license change is needed. The existing tools environment supplies CMake and Python.

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake -S tests/ground_drive_idle_target \
  -B build/ground-drive-idle-target -DCMAKE_BUILD_TYPE=Debug
DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/ground-drive-idle-target -j4
build/tools-env/bin/ctest --test-dir build/ground-drive-idle-target --output-on-failure
build/ground-drive-idle-target/ground-drive-idle-target-vectors --guards
# Sanitizer: configure a separate build/ground-drive-idle-target-sanitize
# with -DRA2_SANITIZE=ON, then build and run that directory's CTest.

PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  -m unittest test_ground_drive_idle_target_evidence
./test.command
./run.command --owned-demo

# Fresh original: use the authorized Mac host Unicorn JIT context and NEW paths.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/idle-target-new.audit.json \
  tests/compare_ground_drive_idle_target.py \
  --exe private/official-1006-probe/game.exe \
  --native build/ground-drive-idle-target/ground-drive-idle-target-vectors \
  --output private/idle-target-new

# Strict current-runner replay; use a new report/audit path each invocation.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/idle-target-replay-new.audit.json \
  tests/compare_ground_drive_idle_target.py \
  --exe private/official-1006-probe/game.exe \
  --native build/ground-drive-idle-target/ground-drive-idle-target-vectors \
  --expectations private/map-depth-1006/ground-drive-idle-target-v1/expected.json \
  --report private/idle-target-replay-new.json
```

For the fresh control, add `--uncached` before the driver and use another new
output/audit pair; this disables inspection reuse. Reuse only eligible identities.
Never overwrite the canonical/control receipts or reopen a closed finalizer.

Next: join this dependency and the result-bearing Advance tree into **one**
complete Process/preparation kernel on the same actors/Drives/map. The first
Advance caller tests AL; the later two ignore it and reread on-map. Other entered
ordinary idle-tail paths and actual timer/command aliases still need caller-level
coverage. Then production mutable ownership, discarded full scheduled previews,
warm renderer isolation and actual SDL displacement precede runtime Scatter/6.
Base RA2 and YR remain incomplete. No workers, Windows actions/transfers, downloads,
publication, system/Xcode/DRM changes or new runtime executable reads occurred.
Installations/discs/Outpost2 remain read-only and all proprietary research stays
ignored/private. Unicorn remains research/test-only.
