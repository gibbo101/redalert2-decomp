# Drawing with the actual movement target

This fixes a prerequisite of the occupied-area encounter proof. The shared
original graphics fixture formerly supplied actor `+494` from its contact-mode
argument before taking its immutable actor snapshot. All existing owned fixtures
passed zero, silently clearing a future live Scatter target before drawing.
Those earlier ordinary proofs had null targets and retain their historical scope.
They do not establish drawing over target-bearing original Scatter owners.

`OwnedUnitWorldOracle` now preserves both actual target fields across the entire
draw binding and original call. Its contact binding requires the initialized
empty first-contact association; a mismatch fails without repairing the guest.
The older pose-only shared fixture retains its explicit supplied contact/target
behavior. Neither changes original instructions or widens movement write guards.

The renderer's borrowed `OwnedUnitDrawActor` now carries an optional pointer to
the actual target field. The immovable world provides read-only storage access;
scenes borrow their own world's field. The recovered surface consumer only tests
zero/nonzero, so the adapter supplies 0/1 without narrowing a host address. It
does not dereference the target Cell or change it. Empty contacts remain a separate
supplied boundary. This does not implement contact-list construction or bridges.
Legacy scenes retain their prior supplied null-target scope.

The native preparation encounter now draws immediately after the resident's
actual dispatch, before route construction. Surface telemetry observes nonnull
target presence, both actors retain their exact Cell pointers, and subsequent
movement/arrival, commands, discarded clones and warm drawing still run. These
are native integration checks, not original Scatter Process1 or SDL displacement.

## Bounded original comparison

`compare_owned_target_drawing.py` uses the existing shared graphics guest and
production `OwnedTerrainRuntime` vector owner. The authored map/initialization
commands come from a retained input file; none of its expectations are consumed.
Diagnostic `Y` commands supply null or actual Cell targets on each actor's sole
destination field. This private runner mode refuses movement and commands; the
test-only initial-state write does not add a production target setter.

The six setup pairs include all four null/non-null combinations, distinct targets,
swapped Cell identities and clearing both fields. Each pair draws actor0, actor1,
actor0, actor1 on shared staging, type indexes, pool, map and world planes. The
comparison includes complete drawing output, pixel/depth/alpha hashes, caches,
floor/query observations and both actors' target coordinates. Original actor
arenas and Drives remain immutable throughout each call. Initial records,
contacts, frame tick, map/profile and target associations remain supplied.
**No Process roots execute in this focused drawing proof.** It is not a proof of
the original encounter, route finding, original scheduling or whole-frame parity.

The accepted fresh proof is
`private/target-drawing-fresh-20261017-a2/{expected,report}.json`:
**40 matching results /24 complete original draws**, taking228.88s wall,
220.276s original generation and0.155s native comparison. The first attempt
completed the original generation but its new comparison parser treated the
initial placement trace as snapshot data. Its failed receipt/diagnostic is
preserved under `target-drawing-fresh-20261017-a1`; it is not accepted evidence.
The parser now removes the existing setup prefix only for initialization/target
setup rows, never for drawing. A regression test requires every drawing token.
The second fresh run's command/label/expected streams match the first diagnostic;
no old original result was imported or relabeled.

Current-source normal/sanitizer replays match all40 results in3.99s/4.44s wall,
with0.031s/0.434s native comparison and zero originals. A separate `--uncached`
inspection control uses the same normal runner/expectations and passes in265.02s
wall (0.027s native), also executing zero originals. These overlapping command
samples measure inspection costs, not project-wide or game-performance gains.
Reports/audits are `private/target-drawing-{replay,sanitize,control}-20261017*`.
Scopes, complete streams, SDL baseline and artifact hashes are validated in
`private/target-drawing-validation-20261017/validation.json`.

All1,172 Python tests and67 root CTests, normal/sanitizer runtime/encounter checks
and actual1,573-frame SDL input/drawing pass. The SDL trace and all58 PPMs match
the retained ordinary baseline; Scatter is still guarded there. Normal/sanitizer
dedicated checks take4.05s/47.46s; app build/test.command22.15s/0.87s,
sanitizer build11.55s, final Python7.95s CLI /6.185s reported, SDL13.88s.
The initial focused normal build, manual repair and total task wall are unmeasured.
Local verification is not independent acceptance. No unchanged full matrix,
inventory or closed finalizer was rerun.

Changing the original fixture also requires a new ordinary pilot identity. Its
fresh16 Process calls (8 per distinct actor),9 complete draws /29 results retain
the complete earlier ordinary streams. Immutable original key:
`7f7cc281a825673e024157c054b69cc74f1ae3f0b59bf699eebbe0f9c32f1b22`.
The fresh run takes125.80s wall /116.394s generation; normal/sanitizer require-hit
replays take6.09s/6.27s wall and execute their current runners with zero originals.
This preserves ordinary coverage; it is not a Scatter Process1 proof.

The exact supplied executable is 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain separate facts. This reuses the existing inspected
base Unit/surface/contact chain described in [UNIT_SURFACE_SPLIT_1006.md](UNIT_SURFACE_SPLIT_1006.md).
No new public code, generated/lifted code, dependency or runtime executable read
is incorporated. Existing pinned reference/license boundaries remain unchanged.

## Commands and continuation

```sh
./build.command
./test.command
./run.command --owned-demo

env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/owned-terrain-runtime --parallel 4
build/tools-env/bin/ctest --test-dir build/owned-terrain-runtime --output-on-failure
# Same commands in build/owned-terrain-runtime-sanitize.

# Fresh original execution requires the authorized Mac host JIT context.
# Choose new private output/audit paths; never overwrite old originals.
/usr/bin/time -p env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/target-drawing-NEW.audit.json \
  tests/compare_owned_target_drawing.py \
  --exe private/official-1006-probe/game.exe \
  --native build/owned-terrain-runtime/owned-terrain-runtime-vectors \
  --output private/target-drawing-NEW

# Current-source replay always executes the current native runner.
# Use the actual accepted expectation path from HANDOFF, and fresh report/audit.
env DEVELOPER_DIR=/Library/Developer/CommandLineTools PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/target-drawing-replay-NEW.audit.json \
  tests/compare_owned_target_drawing.py \
  --exe private/official-1006-probe/game.exe \
  --native build/owned-terrain-runtime/owned-terrain-runtime-vectors \
  --expectations private/target-drawing-fresh-20261017-a2/expected.json \
  --report private/target-drawing-replay-NEW.json
# Sanitizer runner: build/owned-terrain-runtime-sanitize/owned-terrain-runtime-vectors.
# Put --uncached BEFORE the driver for an inspection control.

# Ordinary pilot: supported complete-original reuse, new output/audit names.
/usr/bin/time -p env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/ordinary-target-check-NEW.audit.json \
  tests/compare_owned_unit_processes.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/owned-unit-world-vectors --pilot \
  --original-cache private/original-results --original-cache-require-hit \
  --output private/ordinary-target-check-NEW
# Sanitizer: build/sanitize/owned-unit-world-vectors.
```

The next original interaction must retain actual targets through interleaved
draws on the same distinct Process0/Process1 owners, with scoped child-write
guards. The drawing setup above cannot substitute for that interaction. Original
destination vtable410 versus supplied mission414 bindings and distinct active/
dispatched actor writes still need the shared-guest join. Ordinary SDL continues
to select admission0/2/7 and guards Scatter/6. Actual SDL displacement remains a
gate before that policy changes. Only Apple Silicon macOS is tested; verification
here is local and does not constitute independent acceptance.
