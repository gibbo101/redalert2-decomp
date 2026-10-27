# Recovery-method assessment, 16 October 2026

This bounded assessment follows committed moving-resident recovery `6eac1dc`.
It does not restart the project or change the runtime architecture. The running
45-minute budget began at 02:24:51.871227 UTC on 17 October; the deadline was
03:09:51.871227 UTC. Measurements and diagnostic scripts are ignored under
`private/recovery-assessment-20261016/`. Current gameplay status belongs in the
opening [handoff](HANDOFF.md).

## Matching the original target

The supplied base engine remains 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Its PE header reports x86, image base `0x400000` and linker6.0. Rich records include
product11/build8447/count505, product11/build8168/count12 and product10/build8168/
count190, plus other linker/assembler/library records. These are build-lineage
clues, not function counts, compiler-option proof or authenticity evidence.
Embedded1.08, supplied1.006 lineage and reported no-CD provenance remain separate.

The community [Rich-product table](https://gist.github.com/skochinsky/07c8e95e33d9429d81a75622b5d24c8b)
labels products10/11 as the C/C++ generation associated with VC6. Treat that table
as a reference lead; its own provenance is qualified. Microsoft's
[version table](https://learn.microsoft.com/en-us/cpp/overview/compiler-versions?view=msvc-170)
associates Visual Studio6.0 with `_MSC_VER=1200`. Together with the local header,
this supports investigating VC6-family code generation. It does not pin the exact
compiler executable, service pack, assembler, libraries or per-module flags.

No compatible legitimately available legacy compiler/runtime was found in PATH
or the inspected private/build/Homebrew/CommandLineTools locations. Apple Clang21
is available; `cl`, `clang-cl`, `lld-link`, Wine/Wibo and the checked Homebrew LLVM
paths are absent. This was a scoped search, not an exhaustive machine census.
No installation, download, tool-selection change or Windows action was attempted.

Five representative original ranges were selected and fully decoded for a later
matching experiment:

| Candidate | Address | Bytes / instructions | Conditional branches |
| --- | --- | --- | --- |
| Unit kind leaf | `70A2D0` | 6 /2 | 0 |
| Facing current timer method | `4B8BE0` | 153 /67 | 7 |
| Map signed-coordinate lookup | `548070` | 56 /18 | 3 |
| Movement gate list/House method | `55ACD0` | 149 /52 | 10 |
| Object location setter | `5D51E0` | 87 /27 | 0 |

The branching timer/gate methods prevent an easy-leaf-only assessment. **Zero
compilation/matching attempts were made:** the necessary legacy toolchain was
unavailable, so that experiment stopped. No compiler triple or matching feasibility
verdict follows. If a legitimate toolchain later becomes available, compare these
methods' complete code and relocation/call associations under explicit options;
retain mixed-module possibilities. Modern Clang output would not test VC6 matching.

The requested BFM [starting guide](https://github.com/Druthulu/BFM-decomp/wiki/Start-a-new-decomp-project)
and [bootstrap discussion](https://github.com/Druthulu/BFM-decomp/wiki/How-to-AI-decomp-03-bootstrap-order)
reinforce compiler probes, checked denominators, early canonical types and measured
integration costs. Their console/compiler-specific matching and duplication
strategy is not evidence about this x86 game. No kit, source or dependency was
acquired or incorporated; ProjectArchitect was not installed.

## Partial program inventory

`partial-inventory.json` starts from the accepted closing receipt's146 replay
records, representing116 distinct normal/sanitizer runner paths. It walks existing
inspection manifests, selects current-target range hashes and rechecks every
selected span against the exact executable. This yields **420 distinct exact spans
at417 start addresses**, covering148,750 bytes after overlap removal. The nested
receipt trees contain76,002 occurrences of those spans. A separate byte bitmap
agrees with the sorted-interval union, independently checking overlap removal.
No candidate range hash differs.

These are inspection spans, including scoped blocks/tails; **417 is not a function
count and148,750 is not executed-code coverage**. The `.text` virtual size is
3,769,805 bytes, but its code/data split and complete function boundaries have not
been measured. There is no whole-program function denominator, matching percentage
or completion percentage. The baseline tracked tree has259 src,567 tests,132 tools
and142 docs files; file counts do not measure game coverage.

| Area | Current bounded result | Important open work |
| --- | --- | --- |
| Archives/map/assets | Owned files feed the selected temperate map; prepared projection13,515 Cells /255 slices | Full startup, alternate maps/theaters and arbitrary type construction |
| Unit simulation | Ordinary mover Process, actual mutable membership/admission; moving-resident wait/retry helper verified separately | Genuine independent Process1, general routes/pathfinding and excluded outcomes |
| Presentation | Both explicit actors share complete posed world/shadow drawing and type/global caches | Full scheduling, lifecycle/invalidation, fog/UI and whole frames |
| House/type/world ownership | Shared bounded records and explicit supplied associations | General constructors, registries, lifecycle and full game state |
| Other gameplay/platforms | No new claim | Combat, economy, construction, AI, campaigns, multiplayer, audio, saves, YR; Windows/Linux testing |

## Canonical owners and focused consolidation

| Owner | Source | Keep / next seam |
| --- | --- | --- |
| Mutable Cells, buffers, lazy floor/fallback | `src/assets/MutableUnitMap.*` | One canonical map; renderer seed and preview clones remain independent |
| Unit Mark/Next/discovery/occupation and House state | `src/assets/PreparedUnitMembership.*` | Explicit actor bindings already exist for0/1; retain shared lists and observer restoration |
| Locomotor/queue/Facing/retry/wait | `src/sim/GroundDriveProcess.hpp`, `src/platform/TerrainUnitContext.*` | Process0 is owned; parked1 lacks a Process owner. Give1 independent records/services before commands |
| Admission views | `src/assets/PreparedUnitAdmission.*`, `src/sim/MovingUnitAdmission.*` | Existing view refresh hardcodes mover0/stationary1. Add an explicit opted-in actor binding and live motion snapshot; keep old domain |
| Type/global drawing storage | `src/render/SharedUnitVoxelStaging.hpp`, `src/render/SharedGroundUnitVoxelWorld.hpp` | Share type indexes/global pool and scratch; retain actor staging/resources/registry identities |

A single giant Unit/Cell class would conflate proven records with supplied
associations. Keep the bounded record types and consolidate their bindings where
state is currently projected. Do not rewrite all owners or merge diagnostic views
into authoritative mutable Cells. In particular, Unit+564 holds Drive-base+4;
admission's pointer-relative track/index offsets correspond to the existing
Process track/index fields. The current mapping is correct, not an offset bug.

## Verification cost and reuse experiment

A real `compare_owned_unit_world.py` cached replay was profiled, preserving its
canonical source, runner, expectations and original receipt hashes. It compared
303 results /78 draws, executed no original instructions, and exited0. cProfile
wall time was280.012s; the driver recorded278.419s and native comparison0.336s.
Of roughly200 million profiled calls, there were1,858 `pefile.PE` constructions
with244.024s cumulative time. The whole-file histogram in PE parsing accounted
for213.459s self time. This establishes repeated parsing as a major cost in this
replay; it does not profile fresh Unicorn generation or all project verification.

A private diagnostic memoized immutable-byte/scalar `verify` calls only within
one invocation and returned defensive copies. It retained full verification on
cache misses, all native comparisons and existing source/runner/input/receipt
checks. It produced the same identities/results with canonical files unchanged,
in11.106s:65 actual verifier evaluations /87 hits. Inclusive nested evaluation
times must not be summed as wall time. The wrapper and output are explicitly
marked assessment-only, not accepted proof or adopted infrastructure.

A contemporaneous unprofiled control passed in246.643s versus the private
memoized diagnostic's11.106s, about22.2 times faster for this one local pair.
Both retained the same runner, expectations, identities and303 matched results.
This is a diagnostic opportunity, not a benchmark guarantee or cache acceptance.
The exact memoizer AST passes unchanged-input, changed-binary, changed-scalar,
defensive-copy and mutable-input controls. No ratio is inferred from cProfile's
instrumented time. Earlier accepted owned-world replay234.502s and shared-world
184.952s motivated this experiment but ran under different scheduling.

Existing dependency lists include transitive sources and, in some suites, the
whole `CMakeLists.txt`. The prior delivery also exposed three map suites pinned
to a relinked decoder. Those guards caught real identity changes. Keep them until
a verified replacement measures the actual build closure; do not simply remove
CMake or runner hashes to reduce refreshes. Fresh original changes, unchanged-
source rebuilt-runner replays and unchanged identities remain separate classes.
Batch already-known work after computing impact; do not regenerate unaffected
expectations or repeat successful delivery checks without a new reason.

## Decision and continuation

Continue readable C++ recovery and exact-original differential tests. Original-
target matching remains a useful optional research path, currently toolchain-
blocked; neither success nor infeasibility has been demonstrated. The strongest
measured efficiency opportunity is invocation-local inspection reuse, followed
by deliberate dependency granularity. Promote any cache only with source/input/
runner guards, changed-input and returned-value mutation controls and applicable
fresh/replay acceptance; do not transplant another project's cache setting.

Next reconstruct the shared two-Process owner join, keeping actual actor0 and1
at distinct addresses through Process0 -> Process1 -> interleaved draws -> later
Process, with interacting result2/narrow Advance2 and preserved6/7/scatter
refusals. The current one-mover/parked demo remains the baseline until that proof
and SDL acceptance. No new governance layer, workers, runtime executable reads,
original assets/code, system changes or full-game completion claim were added.

Reproduce the assessment diagnostics with the existing local research environment:

```sh
build/tools-env/bin/python -B private/recovery-assessment-20261016/collect-inventory.py
build/tools-env/bin/python -B private/recovery-assessment-20261016/cache-controls.py
# Assessment-only replay wrapper; this does not create accepted proof:
build/tools-env/bin/python -B private/recovery-assessment-20261016/memoized-replay-experiment.py
# Full unmodified-driver profile, writing a NEW private report:
build/tools-env/bin/python -B -m cProfile -o private/recovery-assessment-20261016/new.pstats \
  tests/compare_owned_unit_world.py --exe private/official-1006-probe/game.exe \
  --expectations private/unit-draw-1006/owned-unit-world-v5/expected.json \
  --report private/recovery-assessment-20261016/new-replay.json \
  --native build/native/owned-unit-world-vectors
```

The closing assessment receipt records actual duration, commands, artifact hashes,
guard controls and unchanged runtime/source identities. Builds and SDL acceptance
remain those of `6eac1dc`; this documentation/diagnostic assessment changed no
runtime or evidence-driver source and does not require repeating closed delivery.
