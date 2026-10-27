# Original-target batch A3 — container search and equality loops

Historical batch record: lifecycle and commands below describe that batch. Current authority, paused goal status and canonical build are in [HANDOFF.md](../HANDOFF.md) and [ORIGINAL_TARGET_BUILD.md](../ORIGINAL_TARGET_BUILD.md).

This batch follows [A2](ORIGINAL_TARGET_BATCH_20261020_A2.md). The sustained
base original-target recovery goal remains active and incomplete.

## Result and scope

Added **458 nonoverlapping source regions / 23,063 C++ body bytes / 3,801 frozen
NOP padding bytes**:304 word searches and154 word-array equality loops. Sources
use ordinary classes, reference parameters, signed loop counters and four-byte
word comparisons. Validity-guarded searches preserve the original zero return;
ordinary exhausted searches return minus one. Equality preserves the initial
count comparison, signed empty-range behavior and early unequal-element return.

A reusable count-equality guard enclosing the loop reproduced original shared
return-block placement. No inline original assembly, instruction arrays, masks,
trimming or inferred replacement bounds were used. Seven candidates remain
full-extent size mismatches:one equality, three ordinary searches and three guarded
searches.465 independently bounded candidates were attempted; repeated compiler
variants and the second transformation do not multiply distinct source recovery.

The cumulative composed state is **4,503 regions / 122,668 body bytes / 41,960
padding bytes**; remaining logical `.text` scaffold is **3,605,177 bytes**, not all
classified as instructions. Region counts are not verified original function
counts. Temporary class/layout/thiscall/reference signatures remain hypotheses;
exact target bytes do not establish portable source semantics or original API
names. There are no relocations in these458 new regions. Game/library identity
remains unclassified; these are source intervals, not final library exceptions.

## Frozen evidence and reproduction

All payload paths below are beneath ignored `private/original-target-20261020/`.

- `goal-recovery-loops-a1/final-evidence.json`, SHA256
  `0e4602ea3c7584d22eb728167670422dcad263b527928f1534e9e526f9ef0a24`:
  source populations, script snapshots, compiler reports, attempts/misses and costs.
- `goal-recovery-loops-a1/accepted-sweep-1792514120511360000/manifest.json`:
  304regions/13,515body/3,493padding; SHA256
  `f4a6da950a6244688921bb7e2e047a870d0e4df1a4049f05f7a38f83e5f507f7`.
- `goal-recovery-loops-a1/accepted-sweep-1792514170879966000/manifest.json`:
  154regions/9,548body/308padding; SHA256
  `39276cfb78ba22e917c4b1b021835e3f7e76ff8092f1265de570a6fcbf4197b8`.
- Owner fresh source reproductions:
  `build/rebuild-1792514171829168000/` (304regions,21.730s), and
  `build/rebuild-1792514213156125000/` (154regions,14.498s).
  Each recompiled its entire frozen source population across the four original
  options and checked a complete packaged reference executable.

Run from the repository root using the existing local toolchain:

```sh
RA2_RESEARCH_ROOT=private/original-target-20261020
PYTHONDONTWRITEBYTECODE=1 private/matching-pilot/20261020T123117Z/env/bin/python \
  "$RA2_RESEARCH_ROOT/scripts/rebuild.py" \
  "$RA2_RESEARCH_ROOT/goal-recovery-loops-a1/accepted-sweep-1792514120511360000/manifest.json"
PYTHONDONTWRITEBYTECODE=1 private/matching-pilot/20261020T123117Z/env/bin/python \
  "$RA2_RESEARCH_ROOT/scripts/rebuild.py" \
  "$RA2_RESEARCH_ROOT/goal-recovery-loops-a1/accepted-sweep-1792514170879966000/manifest.json"
```

Compose unchanged A2 with the two newly emitted `build/rebuild-*/accepted.json`
manifests, in that order, using tracked `tools/original_target/compose.py`,
`--research-root private/original-target-20261020`, a fresh `--tag` and three
`--manifest` arguments. Do not compile the combined manifest as one population.
Existing CrossOver/compiler.lock and private-input rules apply. Unchanged original
matrices and native/SDL checks are outside this batch's changed coverage.

## Build overhead and costs

The private integrator read/hashed aggregate objects once per accepted region:
1,723,256,797bytes of reads for20 unique objects totaling4,020,586bytes in A2.
A bounded change reads, hashes and parses each immutable object once, while
checking every row's expected hash against the same snapshot. Same-runner control
was6.937s; candidate4.985s. `accepted.obj`, assembled scaffold, scaffold source and
integration manifest were byte-identical to control and A2. Independent source/
artifact review plus a later-row wrong-expected-hash rejection passed before
adoption. No source credit follows from this change.

Preserved before/candidate/adoption/timing receipts are in
`build/integrator-io-a3/`; independent review is
`goal-coverage-a3/integrator-cache-review.json`. Active private script SHA256:
`4be6f0c50fe209f3134ec33a4f251daf2f808e918a5ec8ab93b605393c0c26f5`.
The tracked V4 verifier/COFF/compose tools are unchanged. Immutable-input rules
remain necessary; the cache is not a detector of later filesystem mutation.

Worker generation8.100s; compiler sessions16.761s; comparison2.020s; queue about
0.000094s. Source reproduction timings above are separate overlapping scopes.
Per-source compiler, model/token, manual intervention and uninstrumented ranking/
handoff costs are unavailable. Previous failures and evidence remain preserved.

## Combined reference build

`build/goal-a3-fresh-composed/accepted.json`, SHA256
`7406931e584414fcda2ceef115f06881b92e6d9416232cea66c70d3b12d293b7`,
composes unchanged A2 with both newly source-reproduced loop populations.
`composition-receipt.json` records37.328s:17.602s input validation,5.365s
integration,6.959s linking and0.434s packaging (other audit/report overhead also
included). The isolated integrator improvement does not imply the larger combined
build became faster overall; source population and validation costs increased.
`private-driver-identities.json` and `private-driver-snapshot/` preserve post-run
identities of the actual unchanged private drivers; tracked V4 tools have the
normal separate compose snapshot. Original receipts remain unchanged.

The packaged output equals all4,485,392supplied bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Raw linker output is7,606,784bytes with different metadata/layout; original PE/DOS
headers, file padding and272-byte overlay remain explicitly retained. Logical
section payloads and implicit zero tails were checked. No game launch, native
port, gameplay, pristine authenticity or full-decompilation claim follows.

## Independent review, coverage and next work

`goal-coverage-a3/REVIEW_A3_FINAL.md` records author-independent source/layout,
actual COFF mapping, fresh-object equivalence and complete artifact acceptance.
`independent-a3-output-check.json` checks all4,503 transferred sections/bindings,
all four linked sections and3,127,748zero-tail bytes. The reviewer did not rerun
compilers; source reproduction was performed by the owner as recorded above.

`goal-coverage-a3/final-source-ledger-a3/` overlays the accepted extents on prior
frozen category evidence:72,397rows cover every supplied file byte. Partition
SHA256 `ced51ce68e3263ade784d0b63eb8e457340c0b98c837ab9f0ad464ca1d6b6796`.
All8,245 archive-identity bytes remain scaffold, with zero source credit or final
library exceptions.16instruction/data conflict bytes and9body bytes without
instruction coverage remain explicit. No unchanged Ghidra/library matrix rerun.

The shared-reference classification records7,630 accepted relocation uses and
2,923 distinct bound targets;2,487 are absolute-memory targets and2,421 have
explicit scalar-global source declarations. These overlapping views are not
whole-program object counts. Observed widths, pointer tables and zero overlaps
within these explicit access spans do not establish complete types, API identity,
alias freedom or game/library classification. See the superseding clarification
and frozen inputs in `goal-coverage-a3/`; no shared declaration rewrite follows.

Next work continues in a separate resize/copy-loop batch and remaining module/
option/classification hypotheses. Failed full extents stay scaffolded. Most
program code and substantial classification work remain; this batch is not the
full-phase completion boundary in [process](../ORIGINAL_TARGET_PROCESS.md).
