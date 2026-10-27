# Original-target batch A10 — nonleaf initialization and factory wrappers

Historical batch record: lifecycle and commands below describe that batch. Current authority, paused goal status and canonical build are in [HANDOFF.md](../HANDOFF.md) and [ORIGINAL_TARGET_BUILD.md](../ORIGINAL_TARGET_BUILD.md).

This follows [A9](ORIGINAL_TARGET_BATCH_20261020_A9.md). Full base original-target
recovery remains active and incomplete. Larger source-model experiments were kept
bounded and combined with a productive family sweep in one checkpoint.

## Accepted source scope

Added **58 nonoverlapping intervals / 6,959 C++ body bytes / 625 frozen NOP padding
bytes**: one 281-byte nonleaf initializer and 57 factory-like wrappers totaling 6,678
body bytes. Accepted combined state: 6,763 intervals /215,781 body /57,572 padding /
273,353 compiler extent bytes; 3,496,452 logical `.text` bytes remain scaffold,
not all classified as code. Counts are intervals, not certified original functions
or whole-game completion percentages.

The initializer at 498a50 calls the actual ECX/no-stack-word helper, then performs
42 ordered mixed-width receiver/global stores. A packed neutral layout preserves
the unaligned 32-bit field at 117e, two separate actual global loads, final table
word and three late global clears, then receiver return. Owner independently
reconstructed all declared offsets and compared every width/target/value store
against original instructions: `owner-review-a10/498a50-source-review.json`.
Original class/base/table/global meanings remain hypotheses; the helper declaration
earns no implementation credit. First source matched 281 body+7 NOP, no repair.

Factory-like wrappers preserve four stack-word stdcall-compatible arguments/RET16,
null output guard, saved outer value, output zero before outer rejection, exact
error words, allocation size, conditional actual initializer, null-result guard,
member-stdcall query slot0 and signed-negative result test. Failure calls actual
thiscall byte slot32 with flag 1; all paths return the original query/error result.
Original COM/API/class/library roles remain hypotheses. Constructor arguments are
independently decoded: 29 no args, 23 one zero, 3 two zeros, 1 five zeros, and 1 original
data-address ABD408 plus zero. Preserve actual push order and callee cleanup;
no uniform all-zero/one-signature assumption. All 57 match first source attempt.
Opaque helper/virtual/data declarations earn zero target implementation credit.

## Original-only seeded CFG repair before factory source

The seeded pass ended these factory hypotheses at an allocator call incorrectly
annotated non-returning. Existing original wrapper/inner normal-return evidence
contradicts that annotation. Owner `owner-factory-original-a10/` independently
followed actual reachable original CFGs beyond the old 51/54-byte prefixes. Complete
hypotheses span 114–127 bytes, not the first return or next alignment. All calls,
returns and internal paths remain original evidence; no compiler/source/object
length selected a boundary. The initial all 51-byte assertion failed on original
54-byte push-immediate variants; its script/failure is preserved.

The other worker independently reviewed reachable CFGs, constructor push counts/
RET cleanup, indirect calls, actual entry/end references, symbols/defined data,
known instruction flows/literals and every raw unaligned pointer-word candidate.
Of 72 initial regions, 57 have clean supported extensions. One original region lacks
following-entry/same-gap evidence; 14 others have 22 unresolved raw-word occurrences
into added code, some inside instructions. Those records retain exact source file
location/section/target/instruction alignment. They were not dismissed as string
coincidences. All 15 excluded function/gap rows remain unchanged; no source compiled
from them. NOP-reference conflicts are zero. Unknown computed refs remain uncertain.

Coherent versioned SEEDED-only inputs:
`goal-recovery-factory-a10/seeded-factory-cfg-v1/`.

- `functions.jsonl`, SHA256
  `5b41afa1757ff1a04d1bdf4723b42ae7795b7f46488a650b0b3e3786cdca48e0`.
  All 16,331 entry rows remain; only 57 original bodies are independently extended.
- `unassigned-executable.jsonl`, SHA256
  `76d1285f957de8fadd2cd3da1a2b1a99abfff8862513c9f58798826b8a4a1757`.
  Old 993,622 gap bytes equal new 989,956 gap bytes plus 3,666 actual newly classified
  instruction bytes. Unknown remainder/NOP bytes remain explicitly accounted for.
- Author-independent original review receipt SHA256
  `dea991769b329ba9535fa24d519af0609123cf81cd9a3ba75a09d6dc08fa97d7`.
  Raw-word details remain in `raw-added-review-details.json`.
- Owner recheck/approval before source: `owner-factory-original-a10/freeze-approval.json`.
  Every 57 body/CFG/NOP endpoint, unchanged rows, same-population gap accounting,
  exclusions and raw NOP scan were rechecked. No baseline bodies/gaps substituted;
  baseline callees/references are corroboration only. The 3,666 newly classified
  bytes are part of 6,678 recovered source bytes, not additional source credit.

## Bounded larger-model failures

The 548-byte initializer 732ea0 failed first source and one correction. The first
attempt's devirtualized global growth call was correctly refused as unbound;
a typed local pointer restored the real indirect slot8 call. Full 560-byte output
still differs 263 bytes in its best case; embedded-pointer/register lifetime and
store encoding remain unresolved. The 816-byte 4c2930 initializer also failed first
source plus one correction. Full 816-byte size did not establish source equality;
constant pooling, aggregate handling and count/item order still differ. Both trials
remain frozen with no further tuning or source credit.

A 425-byte nested 16-bit raster loop at 5feb60 failed two sources/four options each.
Revised structured loops/width-specific accesses did not reproduce body codegen.
This is a substantial body mismatch, not merely missing padding. Its original
following gap contains 7 NOPs before an unreferenced code hypothesis at 5fed10;
no automatic tail adoption, trim, candidate-length boundary or source credit.
Owner raw pointer/call search also found no incoming candidates for that endpoint.

Failed final evidence:
`goal-recovery-nonleaf-init-a10/final-evidence.json` (also records the accepted initializer),
`goal-recovery-foot-init-a10/final-evidence.json`, and
`goal-recovery-raster-a10/final-evidence.json`. Historical source/options/refusals
stay immutable. No guessed direct target, masks, inline original instructions or
machine-code source arrays were introduced.

## Frozen source and reproduction

Paths below are beneath ignored `private/original-target-20261020/`.

| Source population | Accepted manifest | Body / padding |
| --- | --- | --- |
| Initializer281 | `goal-recovery-nonleaf-init-a10/accepted-sweep-1792519096113151000/manifest.json` |281 /7 |
| Factory57 | `goal-recovery-factory-a10/accepted-sweep-1792519679410325000/manifest.json` |6,678 /618 |

Manifest SHA256 respectively:
`f9b7c9c0a4b0b5b40147af63d4e70cdaf63b889bb6dcfcd8fc67c87927aba77f`,
`5a5eb292cfbd832e49b2e740e89e01273878dfa77a4af6fc3973b7e0f489af8f`.
Factory final evidence SHA256
`8bc570d552bc9d9f5d8b5bcca9e1a2673b93320f19ae947fb1509ab531655c91`.
Whole source/tool/input/COFF identities accompany each immutable population.

Recompile each changed population separately with existing dependencies:

```sh
PYTHONDONTWRITEBYTECODE=1 private/matching-pilot/20261020T123117Z/env/bin/python \
 private/original-target-20261020/scripts/rebuild.py COMPONENT_MANIFEST
```

Owner fresh whole-population/four-option source and full-reference builds:
`build/rebuild-1792519158948628000/` (initializer) and
`build/rebuild-1792519723683373000/` (factory57). Both pass every supplied byte.
Compose unchanged A9 plus both newly emitted manifests using tracked
`tools/original_target/compose.py`, the research root above and a fresh tag.
Do not compile an accepted union as one candidate population. Existing local
CrossOver/VC6/compiler-lock rules apply. Unchanged original/compiler matrices and
native tests were not regenerated.

## Costs and interpretation

First initializer generation 0.302s/compiler 7.508s, no source repair. Its lane's
three compiled source attempts (initializer plus two failed 548 recipes) totaled
20.827s compiler/0.019s comparison. Failed 816 model: generation 0.826s/compiler
13.886s/comparison 0.024s. Raster failure: 0.748s/15.417s/0.039s. Factory first source:
0.632s/6.715s/0.240s, 57 exact/171 other-option misses; no repair. Queues negligible.
Owner original CFG discovery 0.898s, peer original audit 7.620s, owner freeze recheck
0.953s. Early audit failures remain preserved; not all failure/manual/model costs
were measured. Owner fresh reproductions 12.976s/13.835s. Overlapping scopes are
not additive whole-turn timing. Per-source compiler/token usage is unavailable.

Final manifest: `build/goal-a10-fresh-composed/accepted.json`, SHA256
`429cc0e10efac56a089c0ba31234c0d9f917768a2fd9c26c138b162b05939d01`.
Composition 44.156s includes validation 17.423s, integration 10.354s, link 6.999s,
packaging 0.500s and other verification/report overhead. Tracked acceptance code
and private drivers remain unchanged with postrun snapshots; no build optimization.

Independent `goal-coverage-a10/REVIEW_A10_FINAL.md` and `HANDOFF_A10_FINAL.md`
record factory57 full-source/ABI/refs review, strict audits, both fresh COFF
mappings, exact three-component union, all 6,763 actual sections/bindings, four
linked logical payloads, 3,127,748 zero-tail bytes and every packaged byte.
Initializer source review is by owner; factory source review by the other worker;
original discovery by owner, freeze by peer, recheck/approval by owner. Final
artifact inspection does not substitute for those author-independent source reviews.
Union/output/ledger checks 0.349s/0.748s/0.801s. Reviewer did not execute linker;
owner did. No failed candidate entered this union.

Packaged output equals all 4,485,392 supplied bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Raw linker file remains 7,606,784 bytes and differs. Original headers/file padding/
272-byte overlay are explicit after logical payload/zero-tail validation. No
original-game launch, native adaptation, playability, pristine identity or YR claim.

Ledger `goal-coverage-a10/final-source-ledger-a10/partition.jsonl`, SHA256
`132557bde488bc47ea967741a875ba0914235a902746348e878ad2871cf716db`,
covers every file byte in 72,420 ranges. Existing 8,245 archive identity bytes remain
scaffold, zero source credit/library exceptions. Sixteen instruction/data-conflict
and nine body-without-instruction bytes remain unresolved; previous virtual and
classification-only helper/pow evidence is preserved. New factory refusals remain
explicit original hypotheses and were not silently reclassified as recovered code.

`build/goal-a10-fresh-composed/checkpoint-cost-scope.json`: 774.676s from first
source generation completion UTC to composition receipt filemtime UTC, 6,959 new
body bytes (about 8.98 bytes/s for that scope). It includes concurrent model work,
bounded failures, original inventory repair/review, waiting and integration;
excludes earlier preparation and final artifact review/docs. This is neither
whole-turn timing nor a compiler benchmark. Token usage/efficiency is unmeasured.
Larger-model failures are bounded evidence about source development cost, not an
excuse for indefinite tuning or a reason to count library/padding as source.
Full recovery remains incomplete.
