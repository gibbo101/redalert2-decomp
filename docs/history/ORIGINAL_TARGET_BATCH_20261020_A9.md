# Original-target batch A9 — append and live registry lookup

Historical batch record: lifecycle and commands below describe that batch. Current authority, paused goal status and canonical build are in [HANDOFF.md](../HANDOFF.md) and [ORIGINAL_TARGET_BUILD.md](../ORIGINAL_TARGET_BUILD.md).

This follows [A8](ORIGINAL_TARGET_BATCH_20261020_A8.md). The full base
original-target recovery goal remains active and incomplete. This checkpoint
combines work by both medium source workers; the owner independently reviewed
the accepted sources and owns reproduction/integration. Final artifact/ledger review passed as recorded below.

## Source behavior and scope

New components cover **44 nonoverlapping intervals / 4,540 C++ body bytes /
260 frozen NOP padding bytes**: 24 append routines and 20 live name-registry
lookup/allocation routines (initial 5 plus refined 15). Accepted combined state:
6,705 intervals /208,822 body /56,947 padding /265,769 compiler extent bytes,
leaving 3,504,036 logical `.text` scaffold bytes. Intervals are not certified
original functions, and scaffold is not all classified as code.

Append preserves signed count/capacity and positive-growth gates, raw owner-byte
truth, wrapped capacity+growth, virtual slot8 thiscall-compatible arguments and
low-byte result. After growth it reloads count/items and increments count before
reading the caller's value pointer, then stores at the saved index. This retains
alias-sensitive behavior. All 24 matched first attempt. Two entries without strong
refs in the frozen original proposal remain excluded; later corroboration is
separate, not a mutation of this source population.

Registry lookup compares two fixed strings in order, scans with live signed count
and backing reloads, compares item+36, and reloads the found item after the call.
Otherwise it calls storage with the original size, then the actual thiscall
initializer when nonnull, returning that child's result. The outer ECX-only
fastcall-compatible interface/plainRET, two-word cdecl comparison, one-word cdecl
storage and one-stack-word thiscall child are explicit. Mutable globals can live
in the original implicit-zero tail. API/class/constructor/comparison/library/data
identities remain qualified; opaque declarations recover no helper bodies.

Owner `owner-review-a9/append24-source-review.json` and
`registry21-source-review.json` independently checked every complete source text,
original operands, width/order/ABI and references. Source is an exact VC6 x86
model, not an unrestricted portable alias/type model. Registry review covered all
21 source texts; only strict full-extent matches are accepted. Unchanged refined
source/body identity and membership are separately verified, reusing this review.

## Original registry gap refinement and failures

The first 21 registry sources matched five complete extents. Sixteen retained
size-only failures; their 131 original body bytes were not sufficient for full
extent acceptance. No body-prefix result was accepted. The initial source/run
and all failures remain frozen.

Owner `owner-original-registry-gap-a9/` independently froze an original-only gap
partition from baseline 21 hypotheses. Actual CFGs, consecutive NOP bytes,
independently referenced following entries, symbol/data/flow/literal exclusions
and every unaligned raw32 pointer candidate support 20 regions, each with 13 NOPs.
Fifteen old gaps are split; all 1,383,530 original gap bytes and unknown suffixes
remain accounted for. `41def0` lacks verified following-entry evidence and stays
refused. Baseline functions remain byte-identical SHA256
`82d76aac864d26e1a63b17341b43281aa316ce10c95f0d35474ebdba4d64c791`;
new gap SHA256 `0f8a82bfa5e2e54019d4f8b45d9f5ceb890fdacadc4588ae674ba3627d879abb`.
No candidate/source/compiler/object/section length or alignment selected boundaries.
Unknown computed references remain a whole-phase uncertainty.

The other source worker independently rechecked the owner's original evidence:
`goal-recovery-append24-a9/peer-registry-gap-review/receipt.json`, SHA256
`240e04a273bff5bfbe3fffb8f8e8ffb0152989046578494933a9fec97653e830`.
It verifies the whole partition, all 20 original CFGs/endpoints/known-reference
exclusions and 23 called-target RET observations, including the allocator witness.
This permits normal call fallthrough without proving always-return/nothrow/helper
implementation. Only after that review did the registry author regenerate the 15
new supported regions, excluding the initial five and refusal. Per-entry sources
and original function rows stayed byte-identical. All 15 then matched.

A separate three-routine cached lookup trial accepted **zero** after two ordinary
source attempts/24 option cases. Full 208-byte extents/call positions matched, but
register allocation/count lifetime differed. One evidence-driven source correction
did not improve the best 57-byte difference. No further tuning or source credit:
`goal-recovery-lookup3-a9/final-evidence.json`, SHA256
`f79f076e197880178a1472451340b0ea4914b862cd462e416ab7d0f8c6b19b7f`.
A sandbox socket launch failed before VC6 during the registry attempt; the failed
run remains preserved, followed by the scoped authorized local-bottle invocation.

## Frozen components and reproduction

Paths are beneath ignored `private/original-target-20261020/`.

| Component | Accepted manifest | Body / padding |
| --- | --- | --- |
| Append24 | `goal-recovery-append24-a9/accepted-sweep-1792518220130921000/manifest.json` |1,920 /0 |
| Registry5 | `goal-recovery-registry21-a9/accepted-sweep-1792518376883100000/manifest.json` |655 /65 |
| Registry15 | `goal-recovery-registry15-refined-a9/accepted-sweep-1792518620259138000/manifest.json` |1,965 /195 |

Manifest SHA256 respectively:
`5c16af4ffeeefdb7454820a3c92d40265c7f7d444f3f29072c6975c2a6d8c106`,
`51ef54a3fc85fdb6b985dda1ab37038cbbd25dc6fb4caef6197c43518ff6f6f8`,
`f4021bcfa46a813e0f66f294b8b6c2766962e56a9700ad79fc80ef2bacb2e483`.
Final evidence files are `goal-recovery-append24-a9/final-evidence.json`,
`goal-recovery-registry21-a9/initial-final-evidence.json`, and
`goal-recovery-registry15-refined-a9/final-evidence.json`; sources, generators,
compiler files/options/objects and original dependencies are hashed/snapshotted.

Run each frozen population separately with existing dependencies:

```sh
PYTHONDONTWRITEBYTECODE=1 private/matching-pilot/20261020T123117Z/env/bin/python \
 private/original-target-20261020/scripts/rebuild.py COMPONENT_MANIFEST
```

Registry5 reproduction recompiles the original21-source population, retaining its
16 failures. Owner fresh source/full references are
`build/rebuild-1792518321077809000/` (append24),
`build/rebuild-1792518462795685000/` (registry5), and
`build/rebuild-1792518645773993000/` (registry15). Compose unchanged A8 plus these
three newly emitted manifests using tracked `tools/original_target/compose.py`,
`--research-root private/original-target-20261020` and a fresh tag. Never compile
an accepted union as one source population. Local CrossOver/VC6/compiler-lock rules
apply; unchanged original/compiler matrices and native tests were not rerun.

## Throughput and next source models

Both medium workers produced source while the owner performed independent source
review; review/ledger duties rotated after source delivery. Small families share
this checkpoint. Generation/compiler/comparison seconds: append 0.314/7.386/0.072;
initial registry 0.339/6.677/0.092; refined registry 0.208/7.280/0.069. Original gap
freeze 7.542s, peer review 2.326s. Owner fresh reproductions 13.741s/13.764s/13.084s.
Lookup's two failed source attempts cost 0.880s generation and 13.564s compilation;
no further repair. Queues negligible. Scopes overlap and are not additive whole-turn
timing; manual/model/token, per-source compiler and uninstrumented costs unavailable.
Usage efficiency remains unmeasured without reliable token data.

`owner-large-opportunities-a9/` records a scoped original-only candidate ranking
for larger 200–1,600-byte routines with bounded calls/branches and no FP/SEH in this
screen. It is a heuristic, not measured acceptance/readiness. Nonleaf mixed-width
initializers at 498a50(281 bytes),732ea0(548),4c2930(816) suggest reusable call-plus-
ordered-field models; inspect actual ABI/full CFG/extents and previous misses
before source. The next tranche prioritizes accepted body-byte yield and larger
control flow, preserving bounded failures. No build micro-optimization was added.


## Final combined acceptance

Final manifest: `build/goal-a9-fresh-composed/accepted.json`, SHA256
`fb1066b858c2e00b64ee88631cad6d1ef04f3a8a7e8ec34e23236e82c2ac30b6`.
Composition 38.584s: input validation 15.344s, integration 8.720s, link 6.666s,
packaging 0.456s plus verification/report overhead. Unchanged tracked acceptance
code/private drivers have postrun snapshots alongside the composition.

The packaged output equals all 4,485,392 supplied bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Raw linker output remains 7,606,784 bytes and differs; original headers/padding/
272-byte overlay packaging is explicit after logical payload/zero-tail checks.
No gameplay, native adaptation, pristine authenticity or YR claim follows.

`goal-coverage-a9/REVIEW_A9_FINAL.md` and `HANDOFF_A9_FINAL.md` report the exact
four-component union, all 6,705 actual transferred sections/bindings, four linked
payloads, 3,127,748 zero-tail bytes and every packaged byte. Registry source author
performed final artifact/ledger inspection; independent full source review was by
the owner, and original-gap evidence was owner-authored/other-worker-reviewed.
Those roles are distinct, not a claim that a source author independently reviewed
their own source. Union/output/ledger checks: 0.398s/0.720s/0.854s.

Ledger `goal-coverage-a9/final-source-ledger-a9/partition.jsonl`, SHA256
`dc068ca158bc71968dccdbf3bb1fec222e5e54036794f0b014d4e362922c08f8`,
covers all file bytes in 72,419 ranges with prior categories and provenance intact.
All 8,245 archive identity bytes remain scaffold with zero library exceptions/source
credit. Sixteen instruction/data-conflict and nine body-without-instruction bytes
remain unresolved. Pow identity remains a separate classification-only sidecar.

`build/goal-a9-fresh-composed/checkpoint-cost-scope.json` records 603.675s from the
first A9 source generation completion UTC to final composition receipt filemtime
UTC, covering concurrent source development, bounded repairs, review, waiting and
integration. It excludes preparation before that source generation and final
artifact review/docs, so it is neither whole-turn timing nor a compiler benchmark.
New body bytes 4,540 over that scope are about 7.52 bytes/s. Reliable token data is
unavailable; no usage-efficiency conclusion follows. Future selection will measure
larger source-model development and repair burden rather than optimize this modest
build cost or maximize source interval count. Full recovery remains incomplete.
