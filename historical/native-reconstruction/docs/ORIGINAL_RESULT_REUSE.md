# Guarded reuse of complete original generations (v2)

The [Building pixel profile](BUILDING_SPRITE_PIXELS_1006.md) adds the scoped
`compare_scenery_current.py` adapter for420 scenery/808 prop original answers.
Every original Python/mapping/render/asset/synthetic input and receipt is checked.
The captured exported bytes, rather than a rerun of the old exporter executable,
are the original inputs; all are independently hash-matched. Historical exporter
provenance stays unchanged in the origin. Current runner/source identity is
separate in reports/audits; missing or changed bytes refuse. Normal/sanitizer each
report1,228 historical hits/zero misses and always run current native. No receipt
migration, native verdict caching or unchanged original regeneration occurs.


The [GI Mark redraw binding](BOOT_CAMP_MARK_REDRAW_1006.md) extends the existing
`compare_membership_current.py` adapter with `--family redraw` for17,272 historical
redraw results. It keeps the original receipt/inspection/Python dependencies
unchanged, records current native identities separately and executes all current
native commands. It does not treat old native pass/fail as reusable evidence.

The [Infantry recalculation](INFANTRY_RECALCULATION_1006.md) work extends the
existing `compare_membership_current.py` adapter with `--family resident` for
784 historical resident-Cell sequences. Original inspection/listed Python sources
and the immutable old receipt stay checked; current native sources/runner are
separate. No original generation or native input producer is involved. Normal/
sanitizer commands explicitly select `--expectations` and report784 hits/zero
misses. The new160-case Infantry passability comparator likewise separates full
transitive Python/environment provenance from current native identities. Exact
commands and bounded scope are in the subsystem note. These are explicit receipt
replays, not imports into the whole-generation cache or cached native verdicts.


Format v2 supports reuse across separate Codex tool commands. Exactly
`CODEX_TOOL_CALL_ID` and `CODEX_SANDBOX` are kept as hashed invocation metadata
outside the original key. The supported Python generators/oracles/verifiers do
not read these orchestration variables; the isolated original routines cannot
see parent command identifiers. The sandbox marker determines whether original
JIT execution is available. A hit executes no original code and still runs the
current native comparison. Every other environment variable, including unknown
CODEX variables, remains in the key. Invocation context must stay unchanged
during each run. Origin and current reports retain their own context hashes;
missing, malformed or inherited context is refused.

Dependency discovery also reuses parsed Python imports within one process.
`source_imports` retains at most 512 immutable import-name tuples, keyed by exact
source bytes and diagnostic filename. Every closure check still reads and hashes
each current file, resolves local imports and discovers newly present/missing
modules. It does not cache a dependency closure, file hash, file metadata,
original execution, native execution or pass/fail. Syntax errors are not cached.
This remains separate from both whole-original-result reuse and binary inspection
reuse; no new option or runtime dependency is required. A source edit that
preserves size and timestamps still changes provenance. Changes to this helper
itself conservatively require a fresh original key, as before; old origins stay
immutable. Populate only the family needed for current work.

Whole-original-result reuse remains off by default.
`--original-cache-require-hit` makes a cold key fail before
original execution or publication. It requires a cache in `use` mode and cannot
combine with `refresh`. This execution-policy option does not alter the original
key. It is useful for predictable native checks in the restricted sandbox.
V1 entries are historical and unchanged; there is no import or migration.

## Production two-tank encounter

The later [Infantry destination join](INFANTRY_DESTINATION_1006.md) also has a
targeted historical replay adapter, `compare_unit_destination_current.py`.
It checks all819 old Unit destination sequences using current rebuilt native
runners while independently matching every original Python/inspection source
and validating the unchanged mixed-identity receipt against its actual origin.
Only current C++/header/CMake and runner identities are separate; no native input
producer exists in that generator. Tests retain original-source, scope and receipt
refusals. This is an explicit adapter, not a change to the old comparator's strict
`--expectations` semantics, a general-cache import or a relabeled old receipt.
Its source guards follow declared/transitive dependencies; exact commands and
measured normal/sanitizer/uncached controls are in the subsystem note.

`compare_owned_scatter_world.py` uses this protocol for its complete 139-result
encounter. Its generator executes the Python/original guest from authored
commands; it never runs a native input producer. The retained owned-Advance
fixture supplies command inputs only; its complete hash stays in the identity.
The supplied executable, retained disc inspection executable, assets, derived
data, nested fixtures, transitive Python/oracle sources and environment remain
original dependencies. Current native sources and runner stay in current receipts
and during-run guards, but rebuilding them does not require new original answers.

Use a new private output/audit name for each command:

```sh
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/scatter-check-next.audit.json \
  tests/compare_owned_scatter_world.py \
  --exe private/official-1006-probe/game.exe \
  --native build/owned-terrain-runtime/owned-terrain-runtime-vectors \
  --original-cache private/original-results --original-cache-require-hit \
  --output private/scatter-check-next
```

Use `build/owned-terrain-runtime-sanitize/owned-terrain-runtime-vectors` for a
separate sanitizer replay. A cold key fails before original/native execution or
output/store publication. Omit `--original-cache-require-hit` to authorize first
generation in the usual Mac-host JIT context. The first generation is still
required after genuine original dependency changes. Native comparisons, complete
stream validation and scope/receipt guards always run on hits. Historical strict
`--expectations` replay retains its same-source checks. No old receipt is imported.
Current measured miss/hits and preserved historical artifacts belong in HANDOFF.

## Complete Process comparison

`compare_borrowed_process_scatter.py` now supports the same opt-in protocol.
Its original generator uses authored commands, the exact supplied executable,
four private derived data identities, and the complete transitive Python oracle/
inspection closure; it has no native input producer or retained-disc read.
Both `--native` and `--legacy-native` are comparison-only binaries. Their hashes
remain in current receipts and during-run guards, but rebuilding either does
not change the original key. The legacy identity field is excluded only for
this explicitly reviewed driver. Native-produced input files in other drivers
remain original dependencies. No prior receipt is imported or relabeled.

Use this normal command with fresh output/audit names; a warm key prints `hit`
and still runs both current native comparisons and malformed-input guards:

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools \
PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/process-check-new.audit.json \
  tests/compare_borrowed_process_scatter.py \
  --exe private/official-1006-probe/game.exe \
  --native build/borrowed-process-scatter/borrowed-process-scatter-vectors \
  --legacy-native build/process-terminal-scatter/process-terminal-scatter-vectors \
  --original-cache private/original-results \
  --output private/process-check-new
```

Add `--original-cache-require-hit` for a native-only check that refuses a cold
key. Choose both sanitizer runners for a separate current sanitizer replay.
Relevant oracle/input/environment changes still cause a miss; there is no
native-result cache. The wrapper scopes guards to the driver's dependency
closure; see [INSPECTION_REUSE.md](INSPECTION_REUSE.md). Infrastructure changes
are themselves conservatively part of the key, so a changed helper pays a first
generation before reuse. Current measured miss/hits belong in HANDOFF.

## Separate-command v2 validation

Eight audited invocations pass across four separate real tool commands. Fresh
host generation and sandboxed normal/sanitizer require-hit replays retain the
same original keys. Each command records its own context hashes; host and
sandbox markers differ.
Every hit executes its current native runner; normal/sanitizer hashes differ.
Fresh controls with inspection reuse disabled retain every command/label/output.
V2 origin bytes and 35 pinned historical files, including the 204-record Process
closure, remain identical. Private commands, audits, metadata and validation:
`private/original-result-reuse-v2-20261017/`.

| Pilot | Fresh miss | Normal hit | Sanitizer hit | Fresh control |
| --- | --- | --- | --- | --- |
| Full Drive stores | 20.817s | 1.501s | 2.875s | 17.196s |
| Shared-world pilot | 93.359s | 9.033s | 9.154s | 286.831s |

Fresh misses and hits above use guarded inspection reuse. Controls generate
fresh originals with that separate inspection reuse disabled; their times are
not a controlled speed comparison. Full Drive stores cover 594 sequences / 11,026
original calls; the shared pilot covers 8 commands / 4 complete draws across
distinct actors and warm shared state. These are bounded verification timings,
not project-wide or game-performance measurements. A new original key still
pays first-generation cost; full v2 matrices were not repopulated for tooling.

**1,123 Python tests, 67 normal and 66 sanitizer CTests and `./test.command` pass.**
The 27 cache regressions include nine new context/require-hit/format checks; all
eight supported CLI interfaces expose the flag. A real cold request fails in
4.344s before original/native execution or output/store publication. Reported
Python/normal/sanitizer test times are 3.399s/1.95s/7.71s; complete wrapper wall
and manual review/repair time are not separately measured.

No C++/CMake/application source or dependency changes accompany v2. The last
actual SDL baseline remains the Process checkpoint; no SDL or full-family matrix
was rerun for this Python-only infrastructure change. The pilot entries live
under the evidence directory's `cache/`; new keys/stores populate only through
fresh successful generation. No historical receipt is imported. Local
verification is not independent acceptance or whole-game fidelity.

## Why original reuse helps

Original execution dominated the last terminal-Advance refresh: 10,160.069s
aggregate original generation versus 95.050s of reported native comparisons
(fresh/normal/sanitizer across 26 families). Wall time was 5,505.868s with at most
two original-test processes. Terrain-runtime comparison time was not separately
reported. These costs justified separating original provenance from native
implementation identity; they are not game performance measurements.

`tools/original_results.py` provides **opt-in, persistent whole-generation reuse**.
It never caches native execution or native pass/fail. It is separate from the
invocation-local immutable inspection cache in [INSPECTION_REUSE.md](INSPECTION_REUSE.md).
No gameplay, runtime reads, original addresses or recovered algorithms change.

Historical v1 full-family population during the Process join gives these
guarded wall measurements. Every normal/sanitizer hit executes its current native
comparison; original command/label/output streams remain identical to the prior
family proof.

| Full family | Fresh miss | Normal hit | Sanitizer hit |
| --- | --- | --- | --- |
| Moving Unit world | 1,168.187s | 9.304s | 10.916s |
| Shared ground world | 1,680.606s | 10.374s | 13.633s |
| Owned command world | 990.793s | 12.760s | 19.114s |
| Owned Unit processes | 988.848s | 17.699s | 20.184s |
| Owned Unit world | 852.566s | 12.418s | 18.273s |
| Owned Advance world | 1,117.969s | 13.591s | 18.586s |
| Owned Advance runtime | 801.488s | 17.859s | 27.927s |

Receipts and immutable audits:
`private/map-depth-1006/process-join-candidate-20261017/refresh.json` and the
corresponding family folders. These compare fresh generation with replay.
Same-source replay already existed; the new protocol also permits eligible
native C++/CMake and runner changes while preserving original provenance.
The first population still pays the full generation cost. These bounded timings
are not a project-wide speedup or game performance measurement.

The v1 checkpoint had a cross-command limitation: its full environment
fingerprint includes `CODEX_TOOL_CALL_ID` and `CODEX_SANDBOX`. These measurements
are valid within one coordinating command, but a separate Codex command changes
the key. This was measured before claiming cross-command reuse. V2 separates
those fields as described above. V1 measurements remain valid for their original
coordinator; they are not represented as cross-command hits or v2 entries.

## Supported drivers

Ten reviewed `tests/compare_*.py` drivers opt in explicitly:

- `compare_ground_drive_stores`
- `compare_moving_unit_world`
- `compare_shared_ground_world`
- `compare_owned_unit_world`
- `compare_owned_unit_processes`
- `compare_owned_command_world`
- `compare_owned_advance_world`
- `compare_owned_advance_runtime`
- `compare_borrowed_process_scatter`
- `compare_owned_scatter_world`

The seven expensive world/movement families represent about 75.5% of the previous
aggregate original-generation cost. This is coverage of a measured workload,
not a measured project-wide speedup. Their original generators use Python/original
routines and supplied data; they do not invoke the current native runner to
construct original inputs. Both pilot and full scopes have separate keys.
Other drivers retain existing behavior. In particular, `compare_terrain_runtime`
uses native-produced inputs and is **not supported**. Adding a driver requires
reviewing its generator and transitive helpers, input sources, nondeterminism and
any native/subprocess producers before opting in. Do not merely exclude a native
producer from provenance because its output is called an original input.

## Identities and receipts

Default is **off**. Existing `--expectations` replay remains strict, including its
mixed source identity checks. Cache mode cannot combine with `--expectations` or
`--report`; it requires a new output directory outside the store. Historical
receipts cannot be imported or silently relabeled. The first use of each new key
executes originals and the current native comparison before publishing an entry.
Closed gameplay inventories remain pinned to their original sources; this tooling
update does not regenerate them or reopen their finalizers. The Process checkpoint
has 204 records under its own frozen tool/source identities.

Each key includes:

- exact executable, supplied inputs and recursive asset-tree hashes; implicit
  retained disc executable for the drawing families;
- all original inspection/data identities, nested fixtures, input associations,
  scope options and deterministic seed/order construction;
- declared Python source dependencies plus the static transitive local import
  closure, including imports inside functions, oracle/service construction,
  verifiers, comparison helpers, the cache and audit tools;
- interpreter bytes/version/flags, stdlib files, Unicorn/Capstone/PE library trees
  including native libraries, environment bootstrap files, OS/architecture and
  import paths; all environment values except the exact two reviewed invocation
  fields above are hashed into the key rather than exposed.

Require Python `-B` and `PYTHONHASHSEED=0`. Seeded original-case generation remains
in the fingerprinted driver/helpers. Only C++/header/CMake entries in named source
maps and the current native runner are excluded from the **original** key. All
other identity fields remain exact. The two invocation fields have a separate
guarded identity. This is deliberately conservative: Python
helper/test, data, environment or research-runtime changes can require a fresh
original generation even when behavior would have stayed the same.

Every invocation still fingerprints and executes the current native runner.
Existing ordered-state/output comparisons and malformed-input/native guard checks
still run. The new report keeps current full source/runner identities, explicitly
states whether originals executed and records the original key and origin hashes.
A hit validates the untouched original receipt and every existing structural/scope
guard against its historical identity **after** matching current original
provenance. It never substitutes old identities into a current report. The outer
`run_evidence.py` audit retains its full before/after source/input/runner guards.

A store entry contains unchanged `expected.json` and `report.json` bytes plus a
manifest with provenance, origin paths and both content hashes. Complete entries
are published by same-filesystem directory rename after writing/fsyncing files.
Incomplete staging directories are never looked up. Missing, corrupt, symlinked
or mismatched entries fail closed; they are not silently replaced. Concurrent
publishers must agree on complete command/expected/label streams. Existing entries
and receipts are never replaced, including by a fresh-original control. This is
local evidence integrity, not independent acceptance or proof of original startup,
whole-frame fidelity or whole-game completion.

## Commands

Run from the project root. Choose new private output/audit paths each time.
Keep the toolchain environment identical between generation and replay. On this
Mac, use the explicit `DEVELOPER_DIR` below for both; do not change global tool
selection. A measured require-hit attempt without this variable correctly refused
the older shared-world pilot key. Setting it to the retained Command Line Tools
path permits eligible reuse; the variable is still part of the key. See the
current handoff for that replay's receipt. A require-hit refusal does not execute
originals or silently repopulate the cache.
The usual authorized Mac host JIT context is required on a miss or refresh.

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools \
PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/reuse-stores-01.audit.json \
  tests/compare_ground_drive_stores.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/ground-drive-advance-vectors \
  --original-cache private/original-results \
  --output private/reuse-stores-01
```

Repeat in a separate command with a **new** output and audit path for a hit. Add
`--original-cache-require-hit` to refuse unexpected generation:

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools \
PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/reuse-stores-02.audit.json \
  tests/compare_ground_drive_stores.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/ground-drive-advance-vectors \
  --original-cache private/original-results --original-cache-require-hit \
  --output private/reuse-stores-02
```

Use the sanitizer runner
with those new paths for a separate current sanitizer comparison. Rebuilt runners
and changed C++ sources can share original expectations when original provenance
still matches. A changed original dependency selects a different key and executes
fresh originals. Old entries stay available under their old keys.

Append `--original-cache-mode refresh` to execute fresh originals as a control.
It never reads cached outputs into generation; after successful native comparison
it checks the complete command/expected/label streams against any retained entry
for that key. A mismatch fails and preserves both generations. `--uncached` before
the driver disables **inspection** reuse only; it does not disable original-result
reuse. To disable the latter entirely, omit `--original-cache`.

```sh
PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  -m unittest -v test_original_results test_inspection_reuse
PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  -m unittest discover -s tests -p 'test_*.py'
./test.command
```

## Historical v1 validation and measured costs

The private pilot commands, logs, audits, origins, cache entries and timing records
are under `private/original-result-reuse-20261017/`. Final-source invocations and
validation are in its `final/` subdirectory. Their wall times are:

| Pilot | Fresh miss | Normal hit | Sanitizer hit |
| --- | --- | --- | --- |
| Full Drive stores | 17.084s | 1.410s | 3.082s |
| Shared-world pilot | 86.681s | 9.374s | 14.736s |

The final Drive refresh control takes 24.503s. The initial shared refresh control
takes 93.330s and retains its earlier tool/key identity; final fresh streams match
it exactly, without importing that origin into a new key. Scheduling was not
controlled. These are bounded measurements, not a project-wide speedup. Full
source guards and distinct normal/sanitizer runner identities pass. See the
opening handoff for regression counts and review/repair limitations.

A full Drive-store generation covers 594 sequences and
11,026 original Advance calls. The bounded shared-world pilot exercises distinct
actors with complete original drawing and warm shared state; it is not the full
world-family matrix. The initial pilots each run a fresh miss, normal hit, sanitizer
hit and fresh control. After the report-label/seed-guard refinement, the final Drive suite repeats
all four modes and the final shared pilot repeats miss/normal/sanitizer with fresh
current originals. Native runner identities remain distinct; control streams must agree.

Focused tests also cover cross-invocation context changes and immutable metadata,
semantic/unknown CODEX environment invalidation, within-run context drift,
require-hit cold refusal and contradictory options, and v1 format refusal.
They cover changed native source/runner reuse with real subprocess
execution, current runner failures on hits, exact whole-sequence retention,
original code/data/seed/scope/runtime invalidation, explicit producer dependencies,
legacy strict validation, changed-during-run guards, corrupt/partial/symlinked
entries, failed publication and immutable fresh controls. Larger supported families
share this protocol; their full expensive matrices are not all repopulated merely
to test infrastructure. A future first miss still pays original-generation cost.
Manual implementation/review/repair time was not measured separately. Retained
failed attempts and measured command costs belong in the private pilot record.
