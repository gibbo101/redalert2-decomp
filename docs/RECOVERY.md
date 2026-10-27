# Exact original-target recovery evidence

Use [process/completion](ORIGINAL_TARGET_PROCESS.md) and
[build/provenance](ORIGINAL_TARGET_BUILD.md). This active policy supersedes the
native-feature-per-batch workflow preserved in
[RECOVERY_NATIVE_20261020.md](../historical/native-reconstruction/docs/RECOVERY_NATIVE_20261020.md).

## Input and hypothesis boundaries

Fingerprint before using addresses: 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity are distinct. Older disc `135a57a0` evidence is a different
target. Public names/YR addresses and decompiler output are hypotheses, not proof.

Freeze original ranges independently of candidates. Keep entry references,
explicit ranges, code/data/padding, calling convention, type and library confidence.
Disassembly may miss data or shared tails; first-return/next-alignment heuristics
alone do not establish complete functions. Preserve alternate analysis populations
and their deltas; do not merge one pass's bodies with another's gaps.

## Source acceptance

- Hash candidate source, declarations, compiler components/options, COFF output,
  original ranges, reference bindings and comparison logic. Investigate module/
  compiler/option variants; one VC6 configuration is not presumed universal.
- Preserve widths/wrapping, signed arithmetic, FP state/stores, original layouts,
  identities and ordered queries/writes/calls. Capture supported purpose, function/
  symbol/parameter/local names and observed layouts/interfaces while original
  instructions, callers, callees and data are in view. Descriptively name understood
  operations without waiting for original class/developer names; retain address
  provenance and honest placeholders for remaining unknowns. Formatting is not
  semantic recovery; uncertainty in inferred signatures/types stays visible.
- Resolve only explicitly inspected supported references. Unknown relocations,
  constants, allocatable sections or extents refuse automatic acceptance. Compare
  every byte of the complete bounded COFF extent and independently frozen padding.
  No instruction/data masks, tail trimming, prefix matches or candidate-derived
  expected lengths. A mismatch remains a mismatch even if behavior tests pass.
- Do not put original instructions/inline assembly or machine-code arrays into
  C/C++ candidates and call them recovered source. Track C body bytes separately
  from compiler padding and all original-code/data/library scaffolding.
- The owner reviews worker evidence and checks integration placement and the
  complete packaged reference file. Record raw-linker structural differences and
  retained original metadata explicitly. Full-file equality does not validate
  guessed function boundaries or prove all game code has been recovered.

## Efficient verification and records

Use broad automated batches and recurring transformations, with bounded hard
cases left in the scaffold. Focus iteration checks on changed dependencies.
Freeze shared inputs of running proofs, including native-produced inputs if any;
allow useful checks to finish. Reuse original evidence only when executable,
inputs, oracle and actual environment dependencies match. Never cache the current
candidate verdict instead of running changed code. The historical native reuse
policy remains in [ORIGINAL_RESULT_REUSE.md](../historical/native-reconstruction/docs/ORIGINAL_RESULT_REUSE.md) for later
native work; its native acceptance gates do not apply to this recovery phase.

Each batch records attempted population, exact source regions/body bytes/padding,
miss/refusal categories, manual/model interventions, library/code/data uncertainty,
remaining scaffold, dependencies and reproducible commands. Record generation,
compile/queue, comparison, link/package, repair and total wall costs, with unavailable
measurements explicit. Repeated option matches do not multiply unique recovery.
Prefer independently reproduced decisive checks/review; label local checks honestly.

Check the combined original-target build after accepted integration. Do not rerun
unchanged original/native matrices, native-owner adaptations or broad SDL tests
merely to accept a source batch. No original game was launched for the baseline;
no gameplay/whole-frame/Windows/Linux/native-port claim follows from byte matching.

Reference/license rules remain in [REFERENCES.md](REFERENCES.md). Canonical accepted recovered C/C++ is tracked in root `src/recovered/`; its
byte-free manifest is authoritative for fresh builds. Proprietary inputs,
extracted data, disassembly, original-byte scaffolding, failed experiments, bulky
evidence and all binaries remain private. Frozen historical source/receipts are
unchanged; relocation mappings and hashes are recorded separately.

Semantic/source-organization reports stay separate from body/padding/scaffold
accounting. Retain concise purpose, entry-point, data, caller/callee and interaction
explanations in existing subsystem/batch notes and manifests/symbol maps as evidence
connects families. Bound speculative investigation; names or a complete architecture
audit must not block an independently sound exact region. Final delivery must still
meet the navigable, meaningfully named source criteria in
[the process](ORIGINAL_TARGET_PROCESS.md): unresolved behavior/coverage is not merely
a naming uncertainty, while unknown original names or every field's game role are
not themselves completion gates.

Positive emitted-output accounting may explicitly classify a reviewed implicit
compiler helper that the build physically omits. A closed population policy pins
its provenance, complete section/metadata/alias/reference topology and complete
object structure; unknown output still refuses. This changes no original-image
coverage classification or source/library completion criterion. Original helper
bytes remain scaffold unless separately recovered with their own evidence. See
[build enforcement and discard receipts](ORIGINAL_TARGET_BUILD.md#explicitly-discarded-compiler-output).
