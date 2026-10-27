# Original-target batch A8 — initialization and virtual-call loops

Historical batch record: lifecycle and commands below describe that batch. Current authority, paused goal status and canonical build are in [HANDOFF.md](../HANDOFF.md) and [ORIGINAL_TARGET_BUILD.md](../ORIGINAL_TARGET_BUILD.md).

This follows [A7](ORIGINAL_TARGET_BATCH_20261020_A7.md). The sustained base
original-target goal remains active and incomplete. The components and complete composition have passed independent source and
artifact review.

## Source components and behavior

The new components cover **53 nonoverlapping intervals / 5,724 C++ body bytes /
148 frozen NOP padding bytes**, comprising 19 initializer-like methods and 34
virtual-call loops. Accepted combined state is 6,661 intervals / 204,282 body /
56,687 padding / 260,969 compiler extent bytes, with 3,508,836 logical `.text`
bytes remaining scaffold. Counts are intervals, not certified original functions
or a whole-game percentage.

The 19 initializers retain the actual A7 source bytes and function rows, using
only newly audited original gap metadata. One original routine (`58f2d0`) shifts
count by three; the other 18 shift by two. Preserve unsigned32 shifts, supplied
buffer selection, owner-byte-one even on null storage result, ordered startup
stores, ECX receiver and RET8. Original class/constructor/vtable/storage/API
identities remain hypotheses. Thirty-one already accepted A7 intervals and two
unsupported endpoints (`46d020`, `5a6dd0`) were excluded before generation.
The initial 21 size failures remain historical evidence, not edited receipts.

The loops copy the collection count into a local, call first-object vtable slot16
with that local's address and `(4,0)`, then iterate signed-positive count. Each
iteration reads items, zeros the interface local, reads the indexed element,
queries element slot0 with the original literal, calls the original import and
then interface slot8. Every call has a signed-negative immediate return check,
including slot8; failure adds no cleanup. Count/items/interface reloads and actual
callee-cleaned stack calls are preserved. The outer wrapper is fastcall-compatible
with ECX/EDX and plain RET. The PE import is `ole32.dll!OleSaveToStream`; no full
COM/type/interface/class identity or indirect callee implementation is inferred.

Initial loop source matched zero of 34, despite a full extent size of128: the
compiler scheduled interface-local initialization after argument pushes/element
selection. One source-order refinement explicitly reads items base, initializes
the local, then selects the element. All 34 match after that change using the same
four standard options. The failed source/sweep remains frozen. No extra option
hunt, instruction masks, prefix matching or padding trimming was used.

## Original partition and independent source evidence

Paths below are beneath ignored `private/original-target-20261020/`.

Coverage's original-only `goal-coverage-a7/targeted-constructor-gap-v1/` retains
baseline function SHA256
`82d76aac864d26e1a63b17341b43281aa316ce10c95f0d35474ebdba4d64c791`,
new gap SHA256 `c99254a32c074ff700a3f884f6cadc91ae6c5621ff8f97d03bd45f9fdb116516`.
It supports 50 regions / 3,700 body /300 NOP, including 31 already accepted; 19
original gaps are newly split and both unsupported endpoints stay refused.
All 1,383,530 gap bytes remain accounted for, including unknown suffixes.

The owner independently checked original CFGs, consecutive NOP bytes, following
entry instructions/incoming references, raw unaligned pointer exclusions, helper
return witness and exact whole-gap partition before generation:
`owner-original-constructor-audit-a8/{audit.py,receipt.json,endpoints.json}`,
1.415s. No candidate/compiler/source/object/section-length/alignment input selected
the bounds; baseline and seeded bodies/gaps were not mixed. Unknown computed
references remain uncertainty. Allocator return evidence refutes a seeded
non-return annotation without recovering helper implementation or linker metadata.

Independent `goal-coverage-a8/independent-constructor19-{audit,source-review,
membership,fresh-mapping}.json` checks actual full source, original operands,
strict full extents, exact ready50-minus-A7 membership and fresh actual COFF
mapping. Its initial uniform-shift assertion failed on the actual shift3;
that review failure is preserved and corrected from original operands, with
no source or original-boundary changes.

## Frozen source and reproduction

- Initializers: `goal-recovery-constructor19-a8/final-evidence.json`, SHA256
  `223b97b31e11ea202e40c9b3c13df4b49108974c2c633a87b672a0f92e6bf3d5`.
  Component `accepted-sweep-1792517680127519000/manifest.json`, SHA256
  `d53b8f825fd74e84816ab34da58648bf7b439ec0506dc37ef6606ce86e93e726`:
  19 exact /1,406 body /114 padding; 19 exact/57 mismatching option cases.
- Virtual loops: `goal-recovery-virtual34-a8/final-evidence.json`, SHA256
  `421d6e20ce4be382894ec69cb151f206b95bfa8f185e6054f690ad88b873bc28`.
  Component `accepted-sweep-1792517896755536000/manifest.json`,
  SHA256 `80df92d1730b2d8a9f6536a3771de99ec0f635f7f8d4ee9d307923a6e2d863f9`:
  34 exact /4,318 body /34 padding;34 exact/102 mismatching option cases.
- Owner V4 provenance reports: `owner-original-constructor-audit-a8/` files
  `constructor19-provenance.json` and `virtual34-provenance.json`.
- Owner fresh whole-population/four-option source rebuilds and full references:
  `build/rebuild-1792517734054142000/` (initializers,13.988s) and
  `build/rebuild-1792517940638265000/` (loops, 13.299s).

Reproduce each changed population separately:

```sh
RA2_RESEARCH_ROOT=private/original-target-20261020
PYTHONDONTWRITEBYTECODE=1 private/matching-pilot/20261020T123117Z/env/bin/python \
  "$RA2_RESEARCH_ROOT/scripts/rebuild.py" \
  "$RA2_RESEARCH_ROOT/goal-recovery-constructor19-a8/accepted-sweep-1792517680127519000/manifest.json"
PYTHONDONTWRITEBYTECODE=1 private/matching-pilot/20261020T123117Z/env/bin/python \
  "$RA2_RESEARCH_ROOT/scripts/rebuild.py" \
  "$RA2_RESEARCH_ROOT/goal-recovery-virtual34-a8/accepted-sweep-1792517896755536000/manifest.json"
```

Compose unchanged A7 plus both newly emitted accepted manifests using tracked
`tools/original_target/compose.py`, the research root above and a fresh tag.
Do not compile a union as one candidate population. Existing local CrossOver/
VC6/compiler-lock rules apply. No unchanged original/compiler matrix or native
checks are required for unchanged coverage.

## Bounded library classification and next original evidence

`owner-library-pow-a8/full-pow-identity.json`, independently checked by
`goal-coverage-a8/independent-pow-identity-review.json`, identifies the entire
541-byte VC6 LIBC `pow.obj` text section at `7821b0` and associated 12-byte data
at `82ec10`. All 23 relocation fields coincide with actual decoded original
operands; 12 symbol bindings are consistent and every resolved section byte
matches. The 541 includes the previously identified 25-byte wrapper, so only 516
text identity bytes are additional evidence. External symbol meanings remain
inferences, and no callee implementation outside the member is identified.

This is classification-only evidence: **zero source credit, no library exception,
no ledger reclassification or build substitution**. The existing 8,245 archive
identity bytes remain scaffold. The initial restricted mnemonic assertion omitted
an actual JE relocation; the failed script is preserved and corrected to actual
call/jump groups. No mask-based acceptance was introduced.

Next original proposals under `goal-coverage-a8/` cover 26 append-with-growth and 18
larger typed-global lookup routines. Two append and 15 lookup entries lack strong
verified direct-call/data-pointer entry references in that bounded audit. Preserve
that caveat; prioritize supported entries and inspect further original evidence
before treating remaining proposals as eligible. `owner-next-helpers-a8/` records
call-free normal-return witnesses for two lookup helpers, without claiming full
helper/source/API identity. Nonnull fallback paths may throw/use SEH.


## Final acceptance and measured costs

Final manifest: `build/goal-a8-fresh-composed/accepted.json`, SHA256
`dcb47799cdcf47184f9b0fc74514002f28af5ec7b5b70e103ea5d519e8b6b5bb`.
The exact three-component union contains unchanged A7 plus freshly reproduced 19
and 34 components. Composition 37.611s includes validation 15.179s, integration 8.102s,
link 6.777s, packaging 0.434s and other verification/report overhead. Owner source
reproductions took 13.988s and 13.299s. Initializer generation/compiler/comparison:
0.525s /8.274s /0.052s. Both virtual source attempts together:
0.520s /13.498s /0.264s; corrected compiler session 6.817s. Queues negligible.
Overlapping scopes are not additive whole-turn costs. Manual/model/token,
per-source compiler and uninstrumented audit costs are unavailable.

Independent `goal-coverage-a8/REVIEW_A8_FINAL.md` and `HANDOFF_A8_FINAL.md` cite
complete actual source/order/ABI review, strict audits, fresh COFF mappings,
exact union, all 6,661 actual transferred sections/bindings, four logical linked
payloads, 3,127,748 zero-tail bytes and every packaged byte. Reviewer did not execute
compiler/linker; the owner did. Union/output/ledger checks: 0.242s /0.492s /0.742s.
Source-worker audit initially used wrong hardcoded reload indices; its failure
is preserved and corrected from original disassembly without changing source or
compiler proof. Tracked acceptance tools/private drivers remain unchanged;
postrun snapshots accompany the composition without rewriting prior receipts.

Packaged output is exactly 4,485,392 supplied bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Raw linker output remains 7,606,784 bytes and differs; original PE headers/file
padding/272-byte overlay remain explicit packaging after logical section/zero-tail
validation. No original-game launch, native adaptation, playability, pristine
identity or YR claim follows.

Ledger `goal-coverage-a8/final-source-ledger-a8/partition.jsonl`, SHA256
`943c1ed5357db83db189fb248f3ef6f62650adf0b4599d904d2cc2b95925b03e`,
covers all file bytes in 72,410 ranges. Prior categories/source provenance and
refusals remain intact. All 8,245 archive identity bytes stay scaffold; zero library
exceptions/source credit. Sixteen instruction/data-conflict and nine body-without-
instruction bytes remain unresolved. The new pow identity is a separate sidecar,
with no ledger category changes. The full source-recovery goal remains incomplete.
