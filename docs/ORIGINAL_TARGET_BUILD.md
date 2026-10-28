# Canonical original-target build

The source of truth is tracked `src/recovered/`, selected by
the catalog `manifests/original_target/`. The active build executes tracked Python under
`tools/original_target/`. Frozen old private source, manifests and receipts stay
unchanged as provenance; they are not the source implementation consumed by this
build. The catalog is sharded by population (`index.json` holds the global keys,
the populations and region order and every shard's SHA-256;
`populations/<id>.json` holds a population's entry, reference table and
regions). Tools load and dump it only through `tools/original_target/catalog_io.py`,
which presents the same dictionary the former monolithic
`manifests/original_target.json` did and rewrites only changed shards; the build
receipt's `canonical_manifest_sha256` is the index's hash. [Prior setup/evidence](history/ORIGINAL_TARGET_BUILD_HISTORY_20261020.md) and
[A10](history/ORIGINAL_TARGET_BATCH_20261020_A10.md) retain the historical commands.

## Local inputs

Use the existing Python environment with `requirements-research.txt`; select it
with `RA2_PYTHON` if it is not the default Python. No package installation is part
of the build. Private configuration defaults to
`private/original-target.local.json`; pass `--config /absolute/path/config.json`
to select another. Paths are explicit local values; no machine or timestamped
input path is embedded in active tooling or the source catalog.

Configuration keys:

| Key | Input |
| --- | --- |
| `executable` | Absolute path to legitimate supplied PE, 4,485,392 bytes, SHA256 `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f` |
| `compiler_directory` | Existing VC6 directory containing CL.EXE, C1.DLL, C1XX.DLL, C2.DLL, MSPDB60.DLL |
| `linker` | Existing VC6 LINK.EXE, with MSPDB60.DLL beside it |
| `wine` | Wine executable: CrossOver's `wine`, or plain Wine's `bin/wine` |
| `wine_kind` | Optional `wine` for plain Wine; default `crossover` |
| `wine_prefix`, `wineserver` | Plain Wine only: project-local prefix and its `wineserver` (started with `-p`) |
| `bottle` | CrossOver only: existing working private bottle; setup is not run |
| `lock` | Shared compiler/linker lock file, common to any local recovery jobs |
| `assembler` | Optional clang path; otherwise `xcrun --find clang` honors `DEVELOPER_DIR` |
| `populations` | Map each catalog population ID to absolute `inventory` and `gaps` JSONL input paths |

Compiler/linker components are pinned by `manifests/toolchain.json`. Each catalog population's frozen original inventory/gap pair is pinned by catalog hashes.
These private files contain original analysis/byte evidence; no ignored authored
Python is loaded. A fresh checkout needs these legitimate private inputs, existing
tools/bottle and Python dependencies supplied explicitly. It does not need old
candidate sources, reports, compiler objects, aggregate files or build scripts.

## Commands and acceptance

```sh
./test.command
./run.command
./build.command
# Optional deterministic destination, which must not already exist:
./build.command --output build/my-fresh-build
```

`run.command` verifies sources, inventories, executable and tool hashes, without
launching original code. CMake is an optional wrapper with `LANGUAGES NONE`:
configure using a Python with the listed dependencies, then build target
`original-target` or `check-inputs`. Root entrypoints do not configure SDL.

The accepted-only compiler groups preserve historical population, recorded options
and relative source order: 39 groups for A10 and40 for A11, one recorded option per source.
Base flags are `/nologo /c /TP /Zp4 /GX- /GR- /W3`; accepted options are in the
catalog. An explicitly recorded `/GR` replaces the base `/GR-`; default
candidate trials keep RTTI disabled. With `/GR`, emitted RTTI structures bind
only through the exact original RTTI graph and every resolved structure and
vtable is byte-compared. Unreachable, conflicting or mismatching structures
refuse acceptance. Use ordinary C++ casts rather than handwritten compiler
helper calls. No misses or four-option candidate searches run during reproduction.
All compile groups run in one Wine session (each group keeps its own source,
object, `compile.log` and `returncode.txt`); session startup, about 5.5s, had
dominated the former one-session-per-group build (310s → 45s on the SSD, with
identical code/data sections and named relocations). Compiler/linker sessions
share the configured lock and sanitized environment;
CrossOver requires local IPC access outside a restricted shell sandbox.

The canonical adapter checks source completeness/hashes and private original
bounds, then uses the tracked V4 verifier for complete decoding, emitted-section
coverage, supported DIR32/REL32 relocations, original operand/call targets, frozen
padding and full resolved extent equality. Unaccounted code/data, ambiguous or
unbound references, common symbols and overlapping extents refuse acceptance.
The integrator transfers verified fresh compiler byte snapshots, creates remaining
scaffold directly from the pinned executable, assembles i386 COFF and invokes VC6
LINK. No previous accepted object is reused.

The audit runs per compile group in a pool of forked processes
(`RA2_VERIFY_JOBS` or `--verify-jobs`, default min(4, CPUs); 1, or a host
without fork, audits in-process through the same code). The build first writes
`fresh-accepted.json` streamed (each population's reference table is encoded
once and spliced into its rows; the bytes equal `json.dumps` of the manifest)
and records each row's byte span. Every task reads its group's rows back from
that file, re-reads and re-parses its object and audits every row completely
(`Audit.audit_row`); nothing is cached across builds or reused from earlier
objects. The parent replays what the tasks recorded (discarded output, RTTI and
data copies, kept-elsewhere names) in the serial audit's row order and checks
extent overlap over all rows, so `fresh-verification.json` and every receipt are
byte-identical to the serial `Audit.audit` path. The former path held the 2.4 GB
manifest and its parsed copy in one process (about 10 GB at peak); the parent
now peaks near 1.6 GB and each worker near 0.7 GB.

Final input checks read each file once: (1) authored tools, toolchain manifest,
catalog and policies equal their build-start fingerprints; (2) `validate_catalog`
again over the tree as it is now (every source and header hash, no uncatalogued
file, includes), so source drift cannot hide behind the audit's snapshots; (3)
every proof input the audit read is unchanged: by content for files read in the
build process (compared with the bytes step 2 just read where they overlap), by
SHA-256 for inputs read in workers and for the streamed manifest
(`Audit.verify_inputs_unchanged`). After a successful build the compile-NNN
folders and `fresh-accepted.json` are deleted (hashes stay in
`compile-receipt.json`, `fresh-verification.json` and `integration-receipt.json`;
the build receipt lists the removal), leaving about 50 MB. `--keep-intermediates`
keeps them, e.g. for `source_ledger.py`, which reads `fresh-accepted.json`.

Packaging checks all four logical payloads/RVAs/virtual sizes and complete zero
tails, then retains original headers/file padding/overlay. Every packaged byte
must match the supplied target. Raw linker equality is reported separately.
Outputs and command/cost/dependency receipts remain in ignored root `build/`.
Failures preserve their actual outputs/logs and require a new build destination.
TMP/TEMP assignments use quoted CMD syntax; A11 validated that repair with
the shared-header build changes.
No original game launch, full decompilation, native-port or playability claim.

[Migration evidence](history/ORIGINAL_TARGET_MIGRATION_20261020.md) records the fresh
tracked-source reproduction. Native build entrypoints are preserved separately
under `historical/native-reconstruction/`; old root native caches are stale after
the move and were not tested during this migration.

## Shared headers and candidate regeneration

The canonical catalog may declare `headers: [{"path": "src/shared/name.hpp",
"sha256": "..."}]`. Header hashes and completeness are checked with source
hashes, and quoted includes must resolve to declared tracked headers beneath
`src/`. The compiler includes root `src/`; implicit private/SDK headers and computed
includes are not part of this workflow. Shared declaration changes receive normal
strict compiler/reference/full-extent checks. Do not move functions across accepted
compiler populations/settings merely to share files.

Family generation writes fresh candidates under ignored private/build paths.
Canonical manual edits remain authoritative until explicit promotion.
A generation test must demonstrate that current canonical comments/names/types
survive regeneration. This is part of normal batch acceptance, not a new pilot.

Candidate commands for the existing A11 families (completed first application):

```sh
python3 -B tools/original_target/generate_com_collection.py \
  --output private/my-com-candidates
python3 -B tools/original_target/generate_word_storage_family.py \
  --repository . \
  --plan tools/original_target/word_storage_family.json \
  --template tools/original_target/templates/word_storage.cpp.in \
  --exe /path/to/legitimate/game.exe \
  --evidence-inputs /path/to/private/evidence-inputs.json \
  --output private/my-storage-candidates
```

The word-storage evidence map binds the plan's `functions`, `gaps`, `facts` and
`peer_review` IDs to private immutable paths. All are hash-pinned; the exact
independent-approval status/counts/held entry must match. The plan/template carry
no original-byte payload or machine-specific paths. These commands do not compile
or promote candidates. A11 records the actual regeneration/manual-edit proofs.

Keep semantic improvements in canonical tracked source, templates/shared declarations
and existing symbol mappings. Capture names, interfaces and relationships during
recovery; generation cannot erase manual work. Descriptive function/symbol renames
and purpose-based reorganization require normal affected compiler/reference checks
and preservation of compiler populations/options and original address bindings.
These are ongoing procedures, not an instruction to rename or rebuild the A11
example on every checkpoint. The final source-organization outcome is defined in
[the process](ORIGINAL_TARGET_PROCESS.md); portable API design is deferred.

## Existing-family catch-up reproduction

The [bounded accepted-source catch-up](history/ACCEPTED_SOURCE_CATCHUP_20261020.md) changes
names/layout views without changing original coverage or compiler settings.
`generate_word_views.py` renders the fixed A3/A4 membership through four templates;
`generate_com_collection.py` now emits descriptive persistence operation names.
Both write fresh ignored candidates and retain actual canonical hashes for review.

```sh
python3 -B tools/original_target/generate_word_views.py \
  --output private/my-word-view-review
python3 -B tools/original_target/generate_com_collection.py \
  --output private/my-com-name-review
```

Canonical manual comments/names remain authoritative; these commands do not install
or compile candidates. The purpose index and family map link current operation
names and descriptive actual paths to the canonical manifest. The catch-up used focused strict
comparison of only the changed823 sources/four recorded-option groups, followed by
one fresh full canonical build. No candidate-search matrices or native tests are
needed merely to rename/format already-accepted source. Scope new checks to actual
changes; the catch-up is not a recurring ceremony.

## Descriptive canonical paths

Understood operations use descriptive filenames with address suffixes under
conservative purpose/family directories. Unknown/discovery sources may remain
address-only. The canonical manifest is the authoritative path mapping; no build
or family generator derives a canonical path from an address. The index
supplements the actual source tree. Safe nested paths retain containment,
normalization, duplicate/hash/completeness and include-closure checks. The shared
stdlib path resolver is also pinned among build dependencies.

The [bounded filename correction](history/ACCEPTED_SOURCE_PATHS_20261020.md) moves exactly
823 existing sources without changing bytes, compiler populations/options/order
or bindings. All three family generators render new candidates at catalog paths,
preserving manual canonical edits. Frozen historical manifests/receipts remain
unchanged; [the move ledger](../manifests/accepted_source_path_moves_20261020.json)
records old/new paths and unchanged hashes separately.

```sh
RA2_PYTHON=private/matching-pilot/20261020T123117Z/env/bin/python ./test.command
RA2_PYTHON=private/matching-pilot/20261020T123117Z/env/bin/python ./build.command --output build/named-paths-fresh
```

The fresh-build destination must be new. The completed proof is recorded in
the correction note: all6,780sources/40groups,281.267s, complete target SHA256
exact. Receipt `build/named-paths-fresh/build-receipt.json`, SHA256
`a00888781d3bf29d62f2b58936a3d8f79219097f0dfeecd03eed231b710723c8`.
Historical proof directories are not overwritten.

## A12 source and ledger reproduction

[A12](history/ORIGINAL_TARGET_BATCH_20261020_A12.md) adds19regions in populations29/30 and
changes seven existing initializer declarations to shared storage interfaces.
The configured paired inventories remain hash-pinned. The current fresh complete
build compiles6,799sources/42groups in288.830s and matches all target bytes:
`build/recovery-a12-fresh/build-receipt.json`, SHA256
`f00d3ce0441d1557968a59862145193b23ad663525d8bfa7699c553d3bcd5c9b`.

`compile_candidates.py --manifest <frozen-private-population> --output <new-ignored-child>`
performs supported-option source trials plus strict V4 checks, retaining misses
without canonical writes. `generate_copy_word_storage.py` and
`generate_message_gadget.py` take tracked plans/templates and explicit pinned
private evidence maps; both render review candidates only. The initializer
renderer selects its pinned shared-declaration variant only for canonical rows
that declare that header. Manual canonical source remains authoritative.
`source_ledger.py` overlays the current fresh source on a hash-pinned prior
partition, preserving archive/unknown/conflict labels; the A12note gives the exact
command. It does not regenerate inventories or establish a library exception.

## A13 connected-source reproduction

A13 adds seven regions/395body/21padding in populations31–34. Fresh canonical
build `build/recovery-a13-fresh` compiles6,806sources/46groups and matches the whole
supplied file in324.306s; receiptSHA256
`3a9a2f1ad2ee258b881d6ba9d75ebc628118adff33e6188411d74a8dce5f71f3`.
The shared message header now uses real constructors, a UTF16 pointer and the
observed link prefix. Full fresh compilation verifies affected old helpers too.

The existing `generate_message_gadget.py` also renders the connected plans
`message_gadget_family.json`, `font_message_family.json` and
`link_prefix_family.json`, using `--repository`, `--plan`, `--templates`,
`--executable`, two `--evidence NAME=PATH` bindings and a new ignored `--output`.
The plans pin private original-fact and peer-review evidence by hash; pass those
legitimate local files explicitly. They contain no machine-specific paths or
original bytes. Multi-header plans copy/recheck every pinned declaration, preserve
manual canonical source and use catalog paths. Actual A13 commands/results are
recorded in private `owner-a13-integration/render-commands.json` and
`regeneration-review.json`; the renderer and all essential authored logic are tracked.
[The batch note](history/ORIGINAL_TARGET_BATCH_20261020_A13.md) records bounds, failures,
reviewed actual COFF and packaging/ledger limitations. No candidate search matrix
is run during ordinary `./build.command` reproduction.

## Explicitly discarded compiler output

The reviewed A14 array-construction population opts into
`manifests/a14_array_compiler_output.json`. This closed policy pins the ordered
source hashes, actual recursive shared-header dependencies, compiler/options,
frozen original inventories and complete parsed object structure. All section
contents/flags, symbol/auxiliary identities and relocation targets are pinned;
physical file storage must partition completely. Only the COFF timestamp and
sole source-file debug pathname (and consequent offsets/indices) are normalized.
Unsupported header/line states, duplicates, extra output, changed references or
unknown helper variants refuse the proof. Populations without this explicit
policy retain the previous all-game-section coverage requirement.

The sole classified output is VC6's implicit vector-constructor iterator, whose
complete 48-byte section matches independently bounded original `40AED0` (42 body
plus six NOP bytes). Its only incoming reference is validated associated FPO
metadata; every runtime/alias/data/root reference still refuses. The 34-byte
variant is unapproved. `compiler_output.py` supplies accounting, not source or
library recognition and not a claim about ordinary linker dead stripping.

`discarded-output-receipt.json` proves that only the verified game-section
selectors enter the freshly generated placement object and records its hash plus
the actual two link inputs. Raw compiler objects are never linked. Every original
comparison and the complete packaged-file check remain required. The discarded
helper earns zero body/padding/library/source credit; original `40AED0` remains
scaffold. A changed source population or object structure requires a separate
reviewed policy, rather than inheriting this allowance by symbol name.

The separate eleven-source extension uses
`manifests/a14_array_extension_compiler_output.json`, with its own ordered sources,
header, coherent gap inventory and complete object fingerprint. It identifies the
same48-byte helper under a separately reviewed group; the original six-source
allowance does not transfer automatically. `compiler_trial_options` can restrict a
frozen candidate manifest to a nonempty unique subset of the three already
supported option lists. This supports recorded-G5 aggregate reproduction without
repeating other options; no new flags or code-generation search is introduced.


## A15 connected source reproduction

A15 adds nine empty word-storage constructors and two signed pair conversions in
populations37/38. The existing renderer consumes the tracked plans
`empty_word_vector_family.json` and `integer_coordinate_family.json`, with
`empty_word_vector_templates/` and `templates/` respectively. Bind
`original_facts` to each frozen private family facts file and `peer_source_review`
to its owner source-review receipt; plans pin the exact evidence hashes. Actual
regeneration from the promoted canonical catalog matches all11 sources and their
three header dependencies. No new generator or compiler-output policy is needed.

`./run.command` verifies the6,834-source catalog and legitimate input hashes.
Fresh combined build output is `build/recovery-a15-fresh/`; its final receipt,
packaged-byte verification and independent artifact review pass and are recorded in
[the batch note](history/ORIGINAL_TARGET_BATCH_20261020_A15.md). Failed
name-list/filter/projection/INI parser recipes and unsupported original gaps remain
private evidence; ordinary reproduction compiles accepted sources only.

## Rename batches

A signature or name change (a parameter retyped, a function, field or global
renamed, a template argument retyped) changes source text and manglings in many
accepted populations but no original byte. `apply_rename.py` lands it in one
pass instead of one whole-population plan per population:

```sh
$RA2_PYTHON -B tools/original_target/apply_rename.py SPEC.json --dry-run
$RA2_PYTHON -B tools/original_target/apply_rename.py SPEC.json \
  --config private/original-target.interactive.json
./build.command
```

The spec names old -> new manglings (`renames`, or `mangling_rewrite` regex
rules expanded over every name in the catalog and symbols.json), regex text
rules for sources and headers (`rewrite`), worker header copies merged with
`git merge-file` against `header_base`, whole-file `sources` and file `moves`.
The tool renames the catalog, its reference tables, relocation receipts and
symbols.json exactly; recompiles every population that holds a changed source
or names an old mangling, as the build's whole compile groups with recorded
options (through `compile_units`, so `RA2_REMOTE_COMPILE` applies); requires every region to reproduce its complete original extent; and
runs the canonical V4 audit over those groups (`CanonicalAudit.verify_fresh`
with `complete=False`). `--header-users` also verifies unchanged units that
include a changed header. Population ids, inventories, source order, options
and semantic names stay as accepted; the population's `historical_*` hashes
point at the rename receipts under `private/original-target-20261020/rename-NAME/`.
Any miss, unbound reference or old name left anywhere restores every written
file and leaves the catalog untouched. The full build remains the final gate;
the batch still lands alone. New regions in the same round go through
`accept_sources.py` afterwards as usual.

## Plan bounds and template-instance bindings

A plan item that replaces an accepted region ending in switch tables and
states no `body_bytes` takes that region's recorded extent (code plus tables,
the evidence it was accepted with); the table length recomputed from the
original bytes must equal the recorded `switch_data_bytes`. Copied populations
no longer restate it by hand. A composite pass is frozen: rerunning a plan
name whose `composite-NAME` pass holds other rows refuses (rename the plan).

Each primary vtable of the original carries its class's decorated name in its
RTTI type descriptor, so every template instance has its own original copy:
`DynamicVectorClass<T *>`, `DynamicVectorClass<T const *>` and
`VectorClass<T *>` are three vtables with distinct slot functions. When a
population leaves an emitted vtable (`??_7X6B@`) or its deleting destructor
(`??_E`/`??_G`, slot 0 unless COM-derived) unbound, the audit binds it there
(`Audit.rtti_binding`) and still compares every slot. A plan or `@ref`
binding of a vtable name that the RTTI places elsewhere is printed as a
warning (a source may model a `T const *` instance as `T *`), and a vtable
that differs from the original names the RTTI class at the bound address and
each differing slot.

## Iteration tools

All write only to ignored `build/` directories and never touch the canonical
catalog. Run them with the research Python (`$RA2_PYTHON`, which needs capstone
and pefile) from the repository root.

```sh
# Ghidra export -> compilable scratch candidate in build/candidates/<entry>/
$RA2_PYTHON -B tools/original_target/seed_candidate.py 6b1710
# Compile under each recorded option set and print a scored, aligned diff
$RA2_PYTHON -B tools/original_target/diff_candidate.py build/candidates/006b1710/candidate.cpp --entry 6b1710 --watch
# Seed/compile/score many unrecovered functions (resumable) -> build/sweep/queue.md
$RA2_PYTHON -B tools/original_target/sweep_seeds.py --limit 1000
# Rank vtable classes by remaining bytes -> build/classes/classes.md
$RA2_PYTHON -B tools/original_target/class_inventory.py
# Split alignment NOPs from frozen gaps into '-aligned' inventory passes
$RA2_PYTHON -B tools/original_target/refine_gaps.py
# Strictly accept a sweep's byte-exact seeds into src/recovered/ (then build)
$RA2_PYTHON -B tools/original_target/promote_sweep.py --sweep build/sweep --output private/original-target-20261020/sweep-promotion-N
# Rewrite still-generated accepted seeds with the current generator (then build)
$RA2_PYTHON -B tools/original_target/regenerate_seeds.py
# Hill-climb signedness/option variants of near-miss seeds (promote like a sweep)
$RA2_PYTHON -B tools/original_target/permute_seeds.py --entries 004732d0 ... --output build/permute-N
# Seeded Ghidra discovery pass -> new frozen inventory pass (no compiler)
$RA2_PYTHON -B tools/original_target/ghidra_seed_pass.py --base-project P --project NEW --seeds S.jsonl --output INV
# RTTI class inventory, docs/CLASS_HIERARCHY.md and manifests/rtti_classes.json
$RA2_PYTHON -B tools/original_target/class_inventory.py --write-docs
# Move class-owned flat sources into src/recovered/classes/<Class>/
$RA2_PYTHON -B tools/original_target/organize_by_class.py
# Regenerate the numeric block in docs/STATUS.md
$RA2_PYTHON -B tools/original_target/status.py --write
```

`diff_candidate.py` binds relocations from in-source `// @ref NAME=ADDRESS`
comments, accepted manifest symbols/references, address-named symbols
(`FUN_00401000`, `DAT_00830b50`, `_data_402190_4022c0`, Ghidra string labels),
`--ref NAME=ADDRESS` and `--refs-json` (a candidate population, which also
supplies frozen body lengths). `--include DIR` adds a private header tree.
Trailing alignment NOPs are reported separately; scores compare bodies.
Seeds and sweep matches are scratch: promotion still uses
`compile_candidates.py` and its strict audit. Each CrossOver session costs
roughly 7–10 seconds of startup, so the sweep batches about 150 compiles per
session.

## Plain Wine host

The default local config uses WineHQ's macOS build 11.18
(`wine-devel-11.18-osx64.tar.xz`, SHA256
`aa0ea4c82e636ae7bca2076387cb0a5affa26509ad13f119ecd0d62bd7ba6f82`, from
github.com/Gcenx/macOS_Wine_builds) extracted under `private/tools/wine-11.18/`,
with a fresh prefix at `private/tools/wine-prefix/` (`wineboot -i`, no other
setup). Homebrew disabled its Wine casks on 2026-09-01. It runs the same pinned
VC6 files from the compiler directory. A persistent `wineserver -p` brings each
session start to ~0.5s (CrossOver ~5.3s; its launcher blocks on a persistent
server). Verified: full fresh build exact in 35s, all 6,886 code/data sections
and named relocations identical to the CrossOver build. CrossOver remains
supported via `private/original-target.crossover.json`. Stop the server with
`WINEPREFIX=private/tools/wine-prefix <wineserver> -k`.

## Optional remote compile host

`build.py` and `compile_candidates.py` (so `accept_sources.py` and
`check_plans.py`) can send their VC6 compiles to a Windows host over ssh;
assembly, link, verification and packaging stay local. Opt in per shell or
per config:

```sh
export RA2_REMOTE_COMPILE='ssh://USER@HOST/C:/ra2/remote?identity=~/.ssh/KEY&jobs=6'
# or "remote_compile": "<same URL>" in the private config; RA2_REMOTE_COMPILE=off disables it
```

`remote_compile.py` stages the units' sources and every non-`.cpp` file under
`src/` into `ROOT\<job>` with the repository-relative layout, checks the five
compiler files in `compiler` (default `ROOT/toolchain`) against
`manifests/toolchain.json` with `certutil`, runs the same command lines in
`jobs` (default 6, at most 12) concurrent `start /belownormal` cmd sessions,
streams back only each unit's object, log and exit code and deletes the job
folder (`RA2_REMOTE_KEEP=1` keeps it). Remote jobs from one Mac serialize on
`remote-compile.lock` beside the compiler lock; they do not take the Wine
compiler lock. An unreachable host, ssh/tar failure, toolchain drift or
missing output falls back to local Wine, recorded as `remote_fallback` in
the compile receipt (`backend` says which ran). Compile errors are ordinary
results, not fallbacks.

Every unit compiles from its own directory with a relative source name. VC6
records the source name exactly as given in the object's `.file` symbol (it
was the absolute `Z:\...\compile-NNN\accepted.cpp` before), and `/I`, `/Fo`
and `TMP` paths do not reach the object, so objects no longer depend on the
host or on the build folder. Remote and local Wine objects for all build
groups are identical except the COFF header timestamp (bytes 4-7, the compile
time, which also differs between two local builds and is not read by the
verifier).

VC6 itself orders some symbol-table entries and COMDAT sections
nondeterministically (about 1.5% of build groups, under Wine and natively
alike; section bytes and relocation targets are unchanged), so object hashes
can differ between any two compiles; the verifier binds by name and the
packaged file stays exact. Measured on a 20-thread Windows PC (2026-10-27):
all 2,784 build groups compile in about 18 s with six sessions (29 s
including staging and fetch) against about 200 s in four local Wine sessions
on an idle Mac; host CPU rose by roughly a quarter during the run.
