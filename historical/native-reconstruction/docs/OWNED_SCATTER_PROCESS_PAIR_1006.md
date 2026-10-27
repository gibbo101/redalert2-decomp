# Distinct Process pair through resident Scatter and arrival

This research fixture joins the existing production `OwnedUnitWorld` and
`OwnedTerrainRuntime` diagnostic `ordinaryScatter` profile to one original guest
with two distinct actors, Drives and shared graphics/map state. It changes no
simulation algorithm or normal SDL policy. Actual SDL displacement remains the
next capability gate; normal `--owned-demo` still guards Scatter/Advance6.

The exact supplied executable is 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. The executable was rehashed before the
address-based work. No original instructions are modified or executed by the
application. All original data, guest environments and receipts remain private.

## Scenario and supplied boundaries

Actor0 starts stationary at Cell11,12; actor1 at13,12. Both body headings are
16384. An ordinary direct command asks actor0 to reach14,12. Scheduled ticks101
through228 execute Process0, follow pending Scatter routes, Process1, follow
pending routes, then finishTick0/1. Drawing alternates actor0/1 initially,
immediately after the resident's actual dispatch, and after the journey.
No diagnostic K/position/target/list edits occur during the interaction.

Preparation's actual candidate-Cell caller4A32B4 dispatches the resident Unit1.
The actual zero-point Unit/nearby tree chooses Cell12,11 at tick112. The original
and native actors must subsequently reach its exact center XYZ,3200,2944,0,
clear the actual target and stop driving. Drawing consumes the actual nonnull
target between dispatch and arrival. Destination assignment alone cannot pass
the fixture. Actor0's supplied direct route ends at14,12.

The small flat map/type inputs derive from authored commands in the earlier
owned-Advance pilot; none of its expected outputs is consumed. Initial records,
all-one clearance mask, land-speed inputs, close threshold0, successful heap
growth/release, atomic services, mission/notification effects, temporary bytes,
direct routes and the explicit schedule remain supplied. Initial
UnitDestination profile sentinels are supplied consistently on both sides.
This is not original pathfinding, rules/startup recovery or frame scheduling.

Only preparation's initial4C3000 caller4A28E7 can receive a supplied positive
route, at most once per Process. The moving-wait caller4A3A0A supplies failure,
matching the production service. Other routing callers remain refused. Between
Process calls, the supplied followScatter adapter installs the selected direct
route without clearing the actual Cell target. The separate Drive height global
8529D0 is supplied as104, established by the earlier distinct ten-root Drive
initializer proof in [ADVANCE_CELL_SCATTER_1006.md](ADVANCE_CELL_SCATTER_1006.md).
That initializer is not rerun here; the graphics guest's Cell/shadow initialization
does not initialize or alias this Drive global.

## Audit and comparison scope

`AttachedScatterProcesses` extends the original two-Process guest with inspected
preparation/Cell/Unit/nearby/destination ranges. Logical actor identity changes
only during actual Cell-to-Unit dispatch and restores on the actual return.
Destination stores require the active actor, inspected instruction, offset and
width. Inactive-owner guards, register/stack/caller/code/input checks and complete
unselected-arena audits remain. Snapshot allocation uses a separate heap; its
release cannot also invoke the graphics loader's allocator. The legacy guest's
default guards and scope are unchanged.

The comparator checks every selected actor/Drive/wait/turret/command/target
snapshot, all24 queue words, shared membership/occupation/map hashes and every
complete drawing token. Draws include matrices, cache/renderer/pool effects,
pixel/depth/alpha hashes and map/floor queries. Process event prefixes are retained
as native diagnostics, **not compared as a complete ordered-store trace**.
Snapshots occur after each scheduled Process pair; they do not independently
prove every intermediate machine write. The earlier separately verified kernels
retain their own ordering evidence and bounded scopes.

Expectation validation requires consecutive ticks, both actual root counts,
interleaved complete drawings, actual child counts, balanced interface references,
the resident's recorded selected destination, target-bearing middle draws and
exact subsequent XYZ arrival. All declared and transitive Python oracle/verifier
sources, native sources, supplied inputs, runner, receipt and expectation hashes
remain guarded. Strict same-source replay retains its current-source checks.
The driver also supports the existing opt-in
[whole-original-generation protocol](ORIGINAL_RESULT_REUSE.md): eligible
native-only changes reuse original expectations while always executing the
current runner and full comparison. Its original generator does not run a native
input producer. The retained fixture contributes authored commands only and its
complete hash remains guarded. No historical origin is imported or relabeled.

## Reproduction

```sh
./build.command
./test.command
./run.command --owned-demo

env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/owned-terrain-runtime --parallel 4
build/tools-env/bin/ctest --test-dir build/owned-terrain-runtime --output-on-failure
# Sanitizer directory: build/owned-terrain-runtime-sanitize.

# Fresh original execution requires the authorized Mac-host Unicorn JIT context.
# Use new private output and audit paths for every invocation.
/usr/bin/time -p env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/scatter-pair-next.audit.json \
  tests/compare_owned_scatter_world.py \
  --exe private/official-1006-probe/game.exe \
  --native build/owned-terrain-runtime/owned-terrain-runtime-vectors \
  --original-cache private/original-results \
  --output private/scatter-pair-next

# Reuse accepted originals, while always executing current native code.
/usr/bin/time -p env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/scatter-pair-replay-next.audit.json \
  tests/compare_owned_scatter_world.py \
  --exe private/official-1006-probe/game.exe \
  --native build/owned-terrain-runtime/owned-terrain-runtime-vectors \
  --original-cache private/original-results --original-cache-require-hit \
  --output private/scatter-pair-replay-next
# Sanitizer: build/owned-terrain-runtime-sanitize/owned-terrain-runtime-vectors.
# Add --uncached before the driver for an inspection-only control.
```

Current results, receipt paths, measured costs and failures belong in the opening
handoff. No unchanged full matrix, whole inventory or closed finalizer is rerun.
No new upstream code, generated/lifted output, dependency, runtime executable read,
Windows action or system change is added. Actual SDL displacement must precede
adopting this policy in the application. Only Apple Silicon macOS is tested;
local verification is not independent acceptance or whole-frame/game fidelity.
