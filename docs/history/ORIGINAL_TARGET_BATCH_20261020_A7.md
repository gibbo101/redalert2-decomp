# Original-target batch A7 — initialization and conditional cleanup

Historical batch record: lifecycle and commands below describe that batch. Current authority, paused goal status and canonical build are in [HANDOFF.md](../HANDOFF.md) and [ORIGINAL_TARGET_BUILD.md](../ORIGINAL_TARGET_BUILD.md).

This batch follows [A6](ORIGINAL_TARGET_BATCH_20261020_A6.md). The sustained
base original-target goal remains active and incomplete.

## Accepted result and behavior

Added **86 nonoverlapping source intervals / 6,309 C++ body bytes / 571 frozen
NOP padding bytes**: 31 initializer-like methods and 55 conditional cleanup methods.
Cumulative state is **6,608 intervals / 198,558 body bytes / 56,539 padding bytes**,
or 255,097 compiler extent bytes. **3,514,708 logical `.text` bytes remain original
scaffold**, not all classified as code. Intervals are not certified original
functions or a whole-game completion denominator.

Initializers preserve items-zero, count-argument, valid-byte-one, owner-byte-zero
and table-word stores in original order. Nonzero count selects a supplied buffer
or calls an opaque storage helper with unsigned32 `count << 2`; owner becomes one
even on a null result. Receiver return and RET8 are retained. Of 52 initial
candidates, 31 match; 21 full-extent-size misses remain in their original evidence.
These are ordinary mutable initializer methods, not certified original C++
constructors or complete class/API/allocator identities.

Cleanup preserves the pointer read before table write, raw ownership-byte truth,
conditional buffer release and pointer clear, unconditional owner/count clears,
then flags-bit-one conditional receiver release and receiver return with RET4.
All 55 approved candidates match; their C++ bytes and original function rows are
identical to A1. Only independently audited original gap metadata changed. Five
unsupported following entries were excluded before generation/compilation:
`4b57c0`, `4f6fc0`, `53ae60`, `5a22d0`, `6ec220`.
Opaque helper/table declarations recover no callee/data implementation. Actual
original destructor, vtable, heap, API and full lifetime/type identities remain
qualified.

## Original gap evidence and independent checks

Coverage froze `goal-coverage-a7/targeted-dtor-gap-v1/` using original CFGs,
actual NOP bytes, independently referenced following entries, frozen symbol/data/
flow/literal exclusions and every unaligned raw32 pointer-word candidate. It did
not use source/compiler/object/section lengths or alignment to choose bounds.
All 55 approved prefixes are seven bytes; 55 original gaps are split, retaining
unknown suffixes. Five lack independently verified next-entry references.
Baseline functions remain byte-identical SHA256
`82d76aac864d26e1a63b17341b43281aa316ce10c95f0d35474ebdba4d64c791`;
new gap SHA256 `21f64252f3fcb8274a774e959238f0f224727b0f9c98bca222ac927a23e841e4`.
All 1,383,530 original gap bytes remain accounted for.

The same release-wrapper normal-return witness used in A6 refutes a seeded
non-return annotation. The owner independently checked original bodies/CFGs,
endpoints/incoming references, raw pointer exclusions and the exact whole-gap
partition in `owner-original-dtor-audit-a7/` (0.830s). Unknown computed references
remain whole-phase uncertainty; this does not recover original linker metadata.
No seeded bodies/gaps were mixed, no original bodies trimmed or extended and no
old failure relabeled exact.

## Frozen source and reproduction evidence

All following paths are beneath ignored `private/original-target-20261020/`.

- Initializers: `goal-recovery-lifetime-a7/final-evidence.json`, SHA256
  `d7a4a21adc962383ba354faa83b5caf3a22f8d7eaaa38db2e51a9ba85e60b584`.
  Component `accepted-sweep-1792517105188890000/manifest.json`, SHA256
  `7908cf582a53fe3635241de0d482c2d1201ff912c3b467ee4445a95928ffa4fc`:
  31 exact / 2,294 body / 186 padding; 31 exact and 177 mismatching option cases.
- Refined cleanup: `goal-recovery-dtor-refined-a7/final-evidence.json`, SHA256
  `c8b9ffb74ee5540269eea63eecc3dba3d3100c1504a538d616010e4dd7bf7753`.
  Component `accepted-sweep-1792517316143172000/manifest.json`, SHA256
  `dc411632c2c2a1a5928c6abb3ac47da101b25f98374e6e1684f1a1c925c29351`:
  55 exact / 4,015 body / 385 padding; 55 exact and 165 mismatching option cases.
- Owner V4 provenance checks: `owner-original-dtor-audit-a7/` files
  `lifetime31-provenance.json` and `dtor55-provenance.json`.
- Owner fresh whole-population/four-option source rebuilds and full references:
  `build/rebuild-1792517272415847000/` (initializers, 13.729s) and
  `build/rebuild-1792517379896282000/` (cleanup, 13.276s).
- Coverage's independent original/source/order/width/ABI reviews and actual fresh
  COFF mappings are `goal-coverage-a7/independent-constructor31-*.json` and
  `independent-dtor55-*.json`. This is separate from owner compiler execution.

Reproduce each frozen population separately:

```sh
RA2_RESEARCH_ROOT=private/original-target-20261020
PYTHONDONTWRITEBYTECODE=1 private/matching-pilot/20261020T123117Z/env/bin/python \
  "$RA2_RESEARCH_ROOT/scripts/rebuild.py" \
  "$RA2_RESEARCH_ROOT/goal-recovery-lifetime-a7/accepted-sweep-1792517105188890000/manifest.json"
PYTHONDONTWRITEBYTECODE=1 private/matching-pilot/20261020T123117Z/env/bin/python \
  "$RA2_RESEARCH_ROOT/scripts/rebuild.py" \
  "$RA2_RESEARCH_ROOT/goal-recovery-dtor-refined-a7/accepted-sweep-1792517316143172000/manifest.json"
```

Compose unchanged A6 plus the two newly emitted accepted manifests using tracked
`tools/original_target/compose.py`, `--research-root` above and a fresh `--tag`.
Do not compile a union as a single source population. Existing local CrossOver/
VC6/compiler-lock rules apply; no new installation or Windows action is needed.

## Complete composition, costs and remaining work

Final manifest: `build/goal-a7-fresh-composed/accepted.json`, SHA256
`711d2eea3670f527a5c81273264a91b191558aa95c7332c0178bca1309f9cb2a`.
Complete composition took 36.999s: input validation 14.357s, integration 9.278s,
linking 6.722s, packaging 0.452s plus other verification/report overhead.
Initializer generation/compiler/comparison: 0.324s / 8.512s / 0.153s;
cleanup: 0.526s / 6.787s / 0.150s. Queues negligible. These scopes overlap and are
not additive whole-turn timings. Manual/model/token and per-source compiler costs
are unavailable. Unchanged original/compiler matrices and native tests were not
regenerated. Tracked acceptance tools and private build drivers are unchanged;
postrun identities/snapshots accompany the composition without rewriting receipts.

Packaged output equals every supplied **4,485,392 bytes**, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
The raw 7,606,784-byte linker file differs; original headers/file padding/272-byte
overlay are explicitly retained after logical section and zero-tail validation.
Independent final review `goal-coverage-a7/REVIEW_A7_FINAL.md` passes all
6,608 actual sections/bindings, four logical linked payloads, 3,127,748 zero-tail
bytes and the exact three-component union. Reviewer artifact inspection is
separate from owner compiler/linker execution.

Ledger `goal-coverage-a7/final-source-ledger-a7/partition.jsonl`, SHA256
`44ae800bcabedd9694344da76349493f9366f1130965258711a41cfc1a0a6960`,
covers all file bytes in 72,407 ranges. All 8,245 archive-identity bytes remain
scaffold with zero source credit/library exceptions. Sixteen instruction/data
conflict and nine body-without-instruction bytes remain unresolved. Independent
union/output/ledger checks took 0.322s / 0.486s / 0.739s; original destructor gap
audit took 8.606s. Earlier categories, evidence and refusals are preserved.
No original game launch, native port, playability, pristine authenticity or YR
claim follows from this batch.

Next original-only evidence includes the constructor50 gap freeze and virtual34
loop proposal under `goal-coverage-a7/`. Constructor50 covers 31 already accepted
initializers plus 19 newly supported intervals; two endpoints remain refused.
The owner independently rechecked that freeze in `owner-original-constructor-audit-a8/`
before new source generation. It is not additional A7 source credit. Remaining
scaffold, unresolved classes/ABI/types and all prior misses/refusals remain open.
