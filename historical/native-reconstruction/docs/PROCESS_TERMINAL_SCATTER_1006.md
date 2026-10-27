# Complete ordinary Process with terminal and nearby Scatter children

`processWithTerminalScatter` is a separate SDL-free composition of complete
ordinary Drive Process, preparation, result-bearing Advance, Cell/Unit Scatter,
nearby search and destination handling. It borrows the same actual actor, Drive,
mission, Cell, floor and registry owners. It is not wired into the application.
The two-commandable-Rhino `--owned-demo` still uses ordinary Advance0/2/7;
runtime Scatter/Advance6 remains refused.

## Exact target and algorithm boundary

The supplied executable is 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
It is fingerprinted before addresses are used. Embedded1.08, supplied1.006
lineage and reported no-CD provenance are distinct; pristine authenticity is
unverified. Public YR/recomp names provide no substitute behavior evidence.

The oracle executes complete base Process `4A05F0` and preparation `4A2670`,
including actual prologues, children and returns. One portable Process/preparation
kernel serves legacy entries and the new optional result policy. No second
movement implementation or replacement pathfinder is introduced.

| Actual Advance call / continuation | Recovered Process control |
| --- | --- |
| `4A0666` / `4A066B` | Nonzero AL returns Process false; otherwise the live on-map byte is checked. |
| `4A0753` / `4A0758` | AL is ignored; the live on-map byte is checked. |
| `4A0B9E` / `4A0BA3` | AL is ignored; the live on-map byte is checked. |

Inactive-track handling runs the existing actual idle-target dependency before
rotation. Preparation retains repeated target-kind queries, actual gates and
first/second admission0/2/6/7, queued directions, retry/wait branches and track
continuation. It borrows the actual actor530 and558 timer words, including their
padding aliases, rather than synchronizing separate timer copies. Drive60/61/64
flags are explicit borrowed owners. Clears of the double percentage retain
the two ordered original dword stores. All24 queue words remain observable.

Actual null Unit410 requests enter the existing ordinary Unit/Foot/Drive command
chain. Direct idle-target Move_To uses the same extracted ordinary Move_To
algorithm as Foot destinations, retaining its command guards, stores and map
query. Unit destination mission and admission mission must be the same record;
equal copied values are insufficient. Binding makes no world queries.

The actual terminal/nearby Advance tree retains its earlier numeric and identity
contracts: target Cell words versus centers and actor/Foot coordinates, distinct
head+40 and destination+34, late destination Z/flags, strict wrapped height,
duplicate byte63 stores, all queue tails, floor/fallback identity, ordered
notification and live post-service reads. See
[ADVANCE_TERMINAL_SCATTER_1006.md](ADVANCE_TERMINAL_SCATTER_1006.md) and
[GROUND_DRIVE_IDLE_TARGET_1006.md](GROUND_DRIVE_IDLE_TARGET_1006.md).

## Supplied state and refusals

Initial actor/Drive/type/House/Cell/list/occupation/speed/route/pose/registry
associations remain supplied. This matrix explicitly supplies healthy400/400 and
condition threshold0.5; it does not recover damage behavior. Each actual Advance
entry receives explicitly supplied uninitialized frame bytes. Only Advance's
own low-word/byte stores are recovered; dead preparation stack is not asserted
to propagate into a later Advance. Process/retry/wait temporary padding remains
explicitly supplied as in earlier proofs.

Mark, occupation, notification174, mission414, postCell490, failed pathfinder,
accessibility, heap/atomic and padding boundaries retain named supplied effects.
Raw service returns test caller control, not original mission execution.
Diagnostic effect mutations are not gameplay observations. Ordinary special
flags325/32D, wake/effect238, nonordinary animation/disabled fields, initial
shortTrack, actor/terrain preparation targets and owned vector disposal remain
refused, alongside existing child exclusions. Refused paths can retain prefix
stores; no rollback is promised by this low-level entry.

## Differential evidence

Canonical evidence: `private/map-depth-1006/process-terminal-full-v2/`.
**332 scenarios /339 complete original Process calls** match native, executing
5,253 distinct original instructions. Actual counts include:

- 174 true /165 false Process returns and42 preparations.
- Advance callers0/1/2:265 /2 /31, including nonzero AL80 /1 /4.
- First and second preparation each enter admission0/2/6/7.
- Actual Advance admission6 occurs136 times;0/2/7 each occur once.
- 136 dispatches to each distinct actor0/1, with272 nearby searches.
- 20 actual null Unit410 requests and3 direct Move_To calls.

The complete Process root is actor0. Actor1 receives actual Scatter/destination
calls on distinct records; this does not establish complete Process1 or the
production Process0 -> Process1 join.

The matrix includes all ordinary curved switches and terminal tracks inherited
from the Advance proof, later Process calls, live timer/queue effects, supplied
terminal return variants, shared land-speed columns, post-rotation flags and
four native FP modes. Scenario labels are backed by asserted executed branch
counts; a label alone does not establish coverage.

A second fresh original generation with inspection reuse disabled reproduces
every command, label and output. Normal and ASan/UBSan replays pass with distinct
runner hashes. Both native modes pass71 ownership/order/refusal guards. Six
Python tests protect input, source, scope, receipt, projection and actual coverage
requirements. Original code/tables/globals, complete owner arenas/unmodeled
fields, heap, selected ordered stores and queries, caller/frame canaries,
registers, queues/references/RNG and complete floor/fallback state are audited.
This is not every native store, FP exception flags, startup, independent
acceptance, an original-game observation, whole-frame fidelity or a complete game.

Canonical original generation/comparison takes222.430s/1.580s (driver230.469s;
guarded wrapper236.775s). The fresh uncached control takes250.439s guarded wall.
Guarded normal/sanitizer replay wall is7.689s/9.184s. Current audits, full fresh
control, parent refresh, tests and SDL baseline evidence are under
`private/map-depth-1006/process-join-candidate-20261017/`. Full verification costs
and inventory closure belong in the opening handoff.

Failed/narrow pilots are retained separately. Inherited poison interpreted as
health, missing repeated kind queries, a gate trace reporting zero instead of
the returned kind, fixture speed-table association and reused dead stack bytes
were corrected before final proof. Full-v1 executed originals but failed its
coverage guard: second preparation admission0 had not actually run. A focused
13-case pilot then passed, followed by full-v2 and the fresh control. No failed
receipt is relabeled. Manual review/repair time was not measured separately.
`attempt-costs.json` records23 audited root attempts (20 pilots and three full
attempts),14 failed/interrupted, totaling1,187.753s of guarded invocation time.
Each retains its own source/scope identity; this sum is not a single proof's
latency or a measure of human repair time.

No upstream code/header/generated/lifted output, extracted table or dependency is
incorporated. Runtime executable reads are unchanged. Private originals, data,
receipts and binaries stay ignored/unshipped. Only Apple Silicon macOS is tested.
Local verification is not independent acceptance.

## Build and reproduce

```sh
./build.command
./run.command --owned-demo
# LMB either Rhino; RMB move; Ctrl-RMB append; Shift-RMB aim;
# Q/E body; A/D turret; S stop; Space pause; R reset.
./test.command
PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  -m unittest discover -s tests -p 'test_*.py'

env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake -S tests/process_terminal_scatter \
  -B build/process-terminal-scatter -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_OSX_ARCHITECTURES=arm64 -DCMAKE_PREFIX_PATH=/opt/homebrew
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/process-terminal-scatter --parallel 4
build/tools-env/bin/ctest --test-dir build/process-terminal-scatter --output-on-failure
build/process-terminal-scatter/process-terminal-scatter-vectors --guards
# Sanitizer: separate build/process-terminal-scatter-sanitize, -DRA2_SANITIZE=ON.

# Fresh originals require authorized host Unicorn and NEW private destinations.
PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/map-depth-1006/process-terminal-new.audit.json \
  tests/compare_process_terminal_scatter.py \
  --exe private/official-1006-probe/game.exe \
  --native build/process-terminal-scatter/process-terminal-scatter-vectors \
  --output private/map-depth-1006/process-terminal-new
# During repair only: --pilot --pilot-limit 13; identity/scope remains separate.
# Guarded replay, also with NEW audit/report destinations:
PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/map-depth-1006/process-terminal-replay-new.audit.json \
  tests/compare_process_terminal_scatter.py \
  --exe private/official-1006-probe/game.exe \
  --native build/process-terminal-scatter/process-terminal-scatter-vectors \
  --expectations private/map-depth-1006/process-terminal-full-v2/expected.json \
  --report private/map-depth-1006/process-terminal-replay-new.json
# Sanitizer: select its runner. Fresh uncached control: --uncached before driver.
```

Next is production mutable ownership, then full discarded scheduled previews
and warm drawing/storage/association isolation, then actual SDL displacement
before runtime Scatter/Advance6. The existing admission projections in
`OwnedUnitProcesses::refresh` cannot replace actual shared mutable Cell/Unit
owners. Keep legacy behavior/defaults, distinct actor Drives/commands/turrets/
resources and shared map/type/image/pool state. Clone logical state and rebind
callbacks without queries. Base RA2 first, then YR remain incomplete/active.

## Capability-boundary closure

All34 affected families retain every old command/label/output and pass normal/
sanitizer replays. The204-record inventory contains132 unchanged records, two
already accepted current stores records,68 refreshed records and two new Process
records. Sources/runners stayed frozen; closed historical finalizers/receipts were
not reopened. Affected-family refresh wall time is5,729.716s, with at most two original-test processes. Aggregate reported original-generation time is10,599.242s; reported native comparisons across fresh/normal/sanitizer take116.697s. Terrain-runtime comparison timing is unavailable. These overlapping totals are not task wall time. There are34 fresh generations,7 v1 misses and14 v1 hits. The read-only closure takes94.294s;38 boundary checks take25.413s, and36 affected build directories take124.993s. Canonical Process generation/comparison takes222.430s/1.580s (236.775s guarded); normal/sanitizer/control guarded wall is 7.689s/9.184s/250.439s. These are verification costs, not game-performance measurements.
