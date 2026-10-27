# Invocation-local inspection reuse

[run_evidence.py](../tools/run_evidence.py) runs an existing evidence driver with
optional reuse of immutable-input binary inspections. This is supported test
infrastructure, separate from the closed method assessment and private pilot.
It changes neither native runtime code nor the driver's existing validation.

Only already loaded `verify` functions owned by `tools/verify_*.py` are installed.
Aliases of one function share one cache. Keys include the exact binary bytes,
argument types, scalar values and keyword names. Bool/int and floating-point bits,
including signed zero, stay distinct. Mutable arguments, Paths and unsupported
types bypass reuse. Exceptions are not cached. Insertions and every returned hit
use independent deep copies, preventing callers from changing later inspections.
Aliases are restored on exit, including aliases imported during the invocation.
The cache dies with that invocation; there is no disk cache or cross-run reuse.

Distinct verifiers also share **byte histograms within that invocation**. Profiling
the current owned two-Process pilot found 66 PE parses, of which 64 recounted bytes
already seen. While an installed immutable-input verifier runs, the wrapper lends
`pefile.Counter` a histogram helper keyed by an exact immutable snapshot of its
bytes/bytearray input. Each call receives an independent Counter; each full PE
parse and every actual instruction/range check still executes. The helper does
not share PE objects, parsed directories, original execution or native results.
Calls outside those verifiers and generic Counter inputs keep normal behavior.
The original binding is restored on success/failure; an unrecognized preexisting
binding is left alone. Both caches are research infrastructure only.

Original routines, original results, fixture construction, native comparisons and
mutable map/actor state are never cached by the inspection helper. A separate
explicit whole-generation protocol is now available for ten reviewed drivers;
see [ORIGINAL_RESULT_REUSE.md](ORIGINAL_RESULT_REUSE.md). `--uncached` controls
inspection reuse only, including the histogram helper. Put
`--uncached-byte-histograms` before the driver to disable only histogram reuse
while retaining verifier memoization, for a comparable scoped control. Audits
record `byte_histogram_reuse`, `byte_histogram_hits` and `byte_histogram_misses`.
Inspectors first imported
after installation may run uncached. This affects performance, not validation.
The supported inspectors read their supplied binary bytes/scalars; source hashes
and final guards protect their implementation. Do not apply this helper to a
function with hidden mutable inputs or side effects.

The wrapper requires explicit `--exe` and `--native`. Before and after execution
it fingerprints both files, explicit secondary runners/derived-data files, and
the replay expectations/original receipt when present. For drivers declaring
`SOURCES`, the source guard covers that declaration, transitive local Python
imports (including imports in functions), and quoted native headers. It records
`source_guard_scope=driver-dependency-closure-v1` and all guarded hashes in the
audit. An unrelated checkout edit does not invalidate this invocation. Drivers
without `SOURCES` retain the conservative `whole-source-legacy` guard. Relevant
source, input or runner changes during a run still fail; a rebuilt runner is a
new invocation. Default data dependencies retain the driver's own identity
checks. Existing driver identity,
receipt, input, output and runner guards still execute. Changed identities fail
the wrapper. A separate **new private audit** records those identities, arguments,
cache statistics, elapsed time and the driver's result hash. It is supplemental
to the driver's evidence receipt and cannot replace it. An uncached control uses
the same wrapper and guards with `--uncached`.

```sh
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest -v test_inspection_reuse

build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/map-depth-1006/reuse-replay-new.audit.json \
  tests/compare_ground_drive_stores.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/ground-drive-advance-vectors \
  --expectations private/map-depth-1006/ground-drive-stores-v1/expected.json \
  --report private/map-depth-1006/reuse-replay-new.json
# Put --uncached before the driver for an independent control, with new output paths.
```

Use `--output` and a new directory instead of `--expectations`/`--report` for fresh
original execution; the usual authorized host JIT context is still required.
Never use this wrapper to bypass changed-source proofs or original receipt guards.
Keep uncached controls at verification boundaries and record the actual command
and timing. `nested_inspection_seconds` is inclusive across nested inspectors and
can exceed wall time; `elapsed_seconds` and externally measured CLI time describe
the invocation.

The first supported-tool controls retain equal executable/source/input/runner/
expectations identities and pass the same native comparisons:

| Replay | Results | Uncached CLI | Reused inspection CLI |
| --- | --- | --- | --- |
| Selected Drive stores | 594 | 10.368s | 1.105s |
| Complete Unit caller/world | 56 | 66.342s | 4.454s |

The world run has 25 inspection hits /23 misses; the small run has 1 hit /5 misses.
Both pairs ran while the separate original-refresh queue was active, so scheduling
was not controlled. These are measured command-pair costs, not project-wide or
gameplay speedups. The private commands, logs, audits and result-identity comparison
are under `private/map-depth-1006/drive-store-candidate/supported-reuse-*`.
Twelve focused regression tests cover hits/misses, exact scalar types/bits,
mutable-input bypass, defensive copies, exception behavior, alias restoration,
invocation separation, verifier scope and binary/source/CMake/runner/receipt guards.

A separate fresh original run through the wrapper also executes all 11,026
Advance calls. Its 594 commands, original expected streams, labels, inspection/
source/input/runner identities and store counts equal the uncached canonical
suite. The unchanged original routines really execute; reuse does not substitute
their results. This validation takes 30.984s during the concurrent refresh and is
not a speed comparison. Its separate expectations and audit are private under
`drive-store-reuse-fresh-validation/` and `drive-store-candidate/reuse-fresh*`.

## Byte-histogram controls

The default wrapper enables both invocation-local caches. The scoped control
below disables only byte-histogram reuse; it retains original-result reuse and
runs the current native comparison. Use new private paths each time. A new
infrastructure identity needs a fresh authorized original generation before
`--original-cache-require-hit` can succeed; existing entries are never migrated
or relabeled. Keep the launch environment identical to the generation, including
the `/usr/bin/time -p env ...` order for the retained Process pilot.

```sh
/usr/bin/time -p env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/histogram-check-new.audit.json \
  tests/compare_owned_unit_processes.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/owned-unit-world-vectors --pilot \
  --original-cache private/original-results --original-cache-require-hit \
  --output private/histogram-check-new
# Add --uncached-byte-histograms BEFORE the driver for the scoped control,
# using new audit/output paths. Sanitizer: build/sanitize/owned-unit-world-vectors.

PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  -m unittest test_inspection_reuse test_original_results
./test.command
```

Seven additional regression cases cover independent mutable Counters, exact
buffer snapshots, generic/outside-inspection bypass, exception restoration,
invocation separation, unknown-binding preservation and the scoped control.
The histogram helper changes no shipped application or library dependency.

The current same-source owned-Process pilot takes12.67s with histogram reuse off
and6.15s on; the sanitizer hit takes6.38s. Both normal commands use the same
runner, source/input guards and original key. Each compares all29 results,
including16 Process calls and9 complete draws, without original execution.
The helper records64 histogram hits /2 misses. These are single bounded timings,
not a project-wide speedup. Fresh generation under the changed infrastructure
identity takes121.86s and executes the original routines; its complete streams
match the earlier pilot without modifying/importing its entry. The fresh,
normal/sanitizer hit and scoped-control receipts, hashes and measured costs are
in `private/verification-histograms-20261017/validation.json`. All1,164 Python
tests and67 root CTests pass. The application bytes are unchanged; no SDL rerun
or new gameplay fidelity claim follows from this research-tool improvement.
