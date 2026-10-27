# Original-target build architecture

Active process: [ORIGINAL_TARGET_PROCESS.md](ORIGINAL_TARGET_PROCESS.md).
The original-target research build precedes native porting. Preserve original
x86 layouts, addresses, data and call connections while replacing machine-code
scaffolding with exact compiler-output C/C++ in bulk.

## Build layers

1. **Frozen inputs:** exact executable, PE layout and independently versioned
   analysis/boundary metadata. Keep original source media/installations read-only.
2. **Candidate recovery:** reusable signature/type/expression/control-flow
   transformations; broad Ghidra analysis and separate hypotheses. Candidates are
   ordinary source, without inline original instructions or machine-code arrays.
3. **Compiler and strict comparison:** legitimate VC6 in local CrossOver. Resolve
   only supported inspected references at the exact target addresses; compare
   full independently bounded COFF extents, including frozen padding.
4. **Composition:** the build owner transfers accepted compiler-output sections
   into sorted fixed-address `.text$VA` COFF fragments. Supported DIR32/REL32
   bindings are materialized with receipts; original direct call targets are
   independently checked. Unrecovered ranges remain explicit original-byte
   `.incbin` assembly scaffold. That scaffold is not source progress.
5. **Actual assembly/link:** installed clang emits i386 COFF scaffolding; VC6
   links it with accepted compiler sections. Copied resources are named opaque
   `.rawres` to avoid VC6's observed resource-parser/ZeroPad crash.
6. **Explicit packaging and whole-file check:** validate logical section bytes
   and omitted zero virtual tails, then retain original PE/DOS headers, raw-file
   padding and overlay. Compare the complete output without masks. Raw-linker
   headers/layout differ; this is not recovery of all original linker metadata.

[ORIGINAL_TARGET_BUILD.md](ORIGINAL_TARGET_BUILD.md) records exact existing paths,
commands, hashes, section boundaries and limitations. Keep canonical accepted C/C++ under tracked root `src/recovered/`, with
the catalog `manifests/original_target/` (sharded per population: `index.json`
plus `populations/<id>.json`, read and written only through
`tools/original_target/catalog_io.py`) recording source hashes, options,
references and frozen boundary identities. `tools/original_target/build.py` compiles these files
fresh; its acceptance adapter reuses the tracked V4 verifier. Private input paths
come from local configuration. Compiler files, original data/byte scaffolding,
experiments and all binaries remain under ignored private/build paths.
Shared declarations/symbols and canonical build/state changes have one owner.
Workers use separate private outputs; no concurrent mutation of frozen inputs.

## Later native architecture

After this phase, adapt readable recovered algorithms to portable C++20/CMake
and SDL, targeting Apple Silicon first. Preserve the existing simulation/assets/
rendering/audio/platform separation and native work for reuse. A source matching
batch does not need a new native owner, feature, test scene or gameplay milestone.
CrossOver is research/build-only; no original-code execution, Wine, Rosetta,
VM/emulator, mounted-media authentication or Windows-launcher runtime dependency
is authorized for the shipped game. No OpenRA gameplay or general-purpose engine.

Historical implementation/evidence/tests are active recovery inputs now, not
only future porting material. Check exact target/address mappings and proof scope
before reusing names, layouts or caller/callee knowledge. The native interface or
a supplied child is not automatically an original ABI/algorithm. Exact matching
rebuilds the original connected image, but source classes/ownership/architecture
still need supported shared types and source-level relationships during recovery;
per-function types/files are workflow choices. Porting will not be mechanical.

The exact previous architecture and its native acceptance policies are retained
in [ARCHITECTURE_NATIVE_20261020.md](../historical/native-reconstruction/docs/ARCHITECTURE_NATIVE_20261020.md). Historical
subsystem notes remain evidence at their stated scope, not current work orders.

The preserved native project is self-contained at
`historical/native-reconstruction/`, including CMake, source, tools, tests, scripts,
notices and native documents. The root CMake target invokes the active original
build and does not configure SDL. Historical private inputs/build caches remain
in place; relocation is not native validation.

Canonical source may include pinned shared declarations beneath `src/shared/`.
The compiler includes root `src/`; the catalog and verifier check header hashes
and a closed tracked include set before compilation and again at completion.
Shared names/layouts express evidence-backed relationships without assigning
unknown concrete class identities. Family generators render fresh ignored
candidates for review and never replace canonical manual source improvements.

## Connected recovery and source navigation

Capture purpose, meaningful operation names, layouts/interfaces and uncertainties
while examining original instructions, callers, callees and data. Name an
understood operation without guessing its concrete original game class. Keep
address provenance alongside descriptive actual filenames and function/symbol names; original symbol
spelling is not required. Formatting and exact output alone do not establish
semantic understanding.

Progressively connect families through observed calls, data and shared layouts.
Existing subsystem/batch notes, manifests and symbol maps explain supported purpose,
entry points, key data, interactions and unresolved questions. Group by purpose
when relationships are established; an address-only file tree is discovery storage,
not the final navigation model. Understood operations use descriptive filenames
with address suffixes in conservative purpose/family directories; unknown/discovery
files may remain address-only. The canonical manifest supplies actual source paths
to all consumers; the index supplements the tree rather than replacing it.
Defer broad cross-subsystem reorganization,
speculative class unification and portable API design until connected evidence
supports them. File/declaration changes must preserve original compiler populations,
options and symbol/reference bindings. Portability and enhancements remain later.
The full-phase criteria in [the process](ORIGINAL_TARGET_PROCESS.md) distinguish
maintainable source from anonymous matching coverage without demanding unknowable
original names or perfect field knowledge.

A closed, explicitly reviewed compiler-output policy can account an implicit
unreferenced helper as discarded build output. The verifier still accounts every
emitted section, and the placement container proves physical omission before
linking. This earns zero original-image/source/library credit and leaves the
original helper as scaffold. All game-region and complete-file comparisons remain
unchanged; see [build details](ORIGINAL_TARGET_BUILD.md#explicitly-discarded-compiler-output).
