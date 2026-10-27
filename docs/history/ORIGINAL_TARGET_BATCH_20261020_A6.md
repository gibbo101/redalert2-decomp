# Original-target batch A6 — cleanup and request wrappers

Historical batch record: lifecycle and commands below describe that batch. Current authority, paused goal status and canonical build are in [HANDOFF.md](../HANDOFF.md) and [ORIGINAL_TARGET_BUILD.md](../ORIGINAL_TARGET_BUILD.md).

This batch follows [A5](ORIGINAL_TARGET_BATCH_20261020_A5.md). The sustained
base original-target goal remains active and incomplete.

## Result and source behavior

Added **581 nonoverlapping source intervals / 21,845 C++ body bytes / 4,626 frozen
NOP padding bytes**: 349 cleanup methods and 232 copy/request wrappers. Cumulative
state is **6,522 intervals / 192,249 body bytes / 55,968 padding bytes**, totaling
248,217 compiler extent bytes. **3,521,588 logical `.text` bytes remain original
scaffold**, not all classified as instructions. Counts are source intervals,
not confirmed original functions or a whole-game completion percentage.

Cleanup sources preserve a saved pointer read before any capacity preclear, raw
ownership-byte truth, conditional release and pointer clear, then unconditional
owner-byte/count writes in the original order. There are 174 capacity-preclear and
175 basic methods. The new 349-interval component includes the two earlier locally
matched cleanup intervals; they are counted once, not added again.

The other component contains 72 guarded four-word copies and 160 request wrappers.
Copies retain null-output refusal and interleaved original global reads/output
stores, including alias-sensitive order and the second stack argument/RET8 layout.
Request calls explicitly provide ECX and EDX plus two stack arguments in the original
order; inspected callee entry/return paths corroborate a fastcall-compatible ABI.
EDX zero is consumed by the callee. Original APIs, COM/HRESULT/constructor/lookup
roles, complete class layouts, data-pointer identity and helper semantics remain
hypotheses. Opaque reference declarations recover no callee/data implementation.
Four copy candidates remain full-extent size mismatches.

## Original inventory audit before cleanup regeneration

The initial cleanup attempt used 362 baseline function hypotheses. Only two full
extents matched; 360 retained full-size failures even where instruction bodies
matched. Their oversized original unknown gaps contained short NOP prefixes and
later code. The separately seeded pass omitted six post-call bytes from many
cleanup bodies. It was not valid to combine those seeded gaps with baseline bodies.
The original attempts remain frozen in `goal-recovery-cleanup-a6/` with their true
scope and zero additional canonical credit.

Independent inspection found an inconsistent non-return annotation at the release
wrapper `0x781d3b`: baseline false, seeded true, for the same 11 original bytes.
An explicit return and a reachable normal-return witness in its called helper
`0x7825e8` contradict that global non-return property. This explains the missing
fallthrough bytes; it does not recover free/release/helper/library semantics.

Coverage then produced a separately versioned original gap partition with no
compiler, candidate-source, object, section-size or alignment input. It retained
the baseline function JSONL byte-for-byte and checked original CFG reachability,
normal call fallthrough, actual consecutive NOP bytes, an independently referenced
following entry, and known function/symbol/data/flow/literal references. Every
unaligned raw 32-bit pointer-word candidate was also checked against proposed NOP
interiors. Proposed prefixes were limited to the existing 15-byte policy.

Of 362 regions, 349 were supported: 347 oversized gaps were split and two already
had supported gaps. Thirteen were refused before source generation: eight lacked
verified next-entry references; five had potential raw pointer-word interior
conflicts. All original gap bytes remain accounted for: 1,383,530 bytes, with
7,559 old rows partitioned into 7,906 rows. Unknown suffixes remain unknown.
No original body was extended/trimmed, no seeded body/gap was borrowed, and no
failure was retroactively renamed exact. Unknown computed references remain a
whole-phase uncertainty; this is bounded static evidence, not original linker
metadata or complete function-boundary certification.

The owner independently rechecked all 349 original bodies/CFGs, NOP endpoints,
actual incoming references, first following instructions, raw pointer exclusions,
return witness and exact whole-gap partition (0.929s). It also compared actual old/
new C++ bytes and original function rows for every new interval: all unchanged.
Only the independently versioned original gap metadata differed. The source worker
filtered the frozen supported set before generation; the 13 refused regions were
not compiled in this new population. Strict complete COFF comparisons then passed
all 349. No acceptance-tool weakening, masks or prefix acceptance was introduced.

## Frozen evidence

Paths below are beneath ignored `private/original-target-20261020/`.

- `goal-coverage-a6/targeted-cleanup-gap-v1/`: original CFG/gap evidence, return
  witness, input hashes, baseline function copy and independently refined gaps.
  Function SHA256 remains `82d76aac864d26e1a63b17341b43281aa316ce10c95f0d35474ebdba4d64c791`;
  gap SHA256 `742ab82f9b9ce8a13fc404202f8f7820d64cb119d6caa482295bcde0783867b6`.
- `goal-coverage-a6/cleanup-gap-freeze-receipt.json`: every file identity and all
  13 explicit refusals. Frozen original-only generator SHA256
  `853b15e7482a7108152fee73414baa029e601aaa9b476b71c17e029dc5a8c1be`.
- `owner-original-gap-audit-a6/{audit.py,receipt.json,endpoints.json}` and
  `source-membership-check.json`: author-independent owner original audit and
  actual unchanged-source/function-row/supported-set checks.
- Initial `goal-recovery-cleanup-a6/final-evidence.json`, SHA256
  `9ea35eb2dcb650afcc71fbaf9c551549a2c5396b68ebc79f46da3041c57596a9`:
  362 initial candidates, two local matches, 360 size failures. Separate seeded
  generation yielded zero eligible contiguous candidates; no empty compiler run.
- `goal-recovery-cleanup-refined-a6/final-evidence.json`, SHA256
  `a06f5329157c75ddc63c4c0faa8989b04a1d331eaade92581aa352267c477160`:
  approved 349-source generation, snapshots, identities, reference checks and costs.
- Its `accepted-sweep-1792516437256798000/manifest.json`, SHA256
  `d0a53d965ce4471afd63c8c2f10e14e3207bb2faac3138f3ae49fece2b6cdc5c`:
  349 intervals / 14,133 body / 2,619 padding bytes; 698 exact/698 mismatching
  option cases. C++ text is byte-identical to the earlier per-entry templates.
- `goal-recovery-requests-a6/final-evidence.json`, SHA256
  `6521df51b64511b5dfae89943e15510001c13cd6770111604a72bee7e70a5ac2`.
  Its `accepted-sweep-1792516124456959000/manifest.json`, SHA256
  `870435ed12be9aa1e6b41ed97dbff5fceecc6066b0c0ea6e0def9c8a907b0896`:
  232 intervals / 7,712 body / 2,007 padding bytes; 236 attempted candidates,
  622 exact/322 mismatching option cases, four size-only copy misses.
- Owner fresh source/full-reference reproductions:
  `build/rebuild-1792516204721123000/` (requests) and
  `build/rebuild-1792516515154421000/` (refined cleanup). Each recompiled the whole
  frozen population across four original options and checked a complete output.

## Reproduce

Run each changed source population separately from the repository root:

```sh
RA2_RESEARCH_ROOT=private/original-target-20261020
PYTHONDONTWRITEBYTECODE=1 private/matching-pilot/20261020T123117Z/env/bin/python \
  "$RA2_RESEARCH_ROOT/scripts/rebuild.py" \
  "$RA2_RESEARCH_ROOT/goal-recovery-requests-a6/accepted-sweep-1792516124456959000/manifest.json"
PYTHONDONTWRITEBYTECODE=1 private/matching-pilot/20261020T123117Z/env/bin/python \
  "$RA2_RESEARCH_ROOT/scripts/rebuild.py" \
  "$RA2_RESEARCH_ROOT/goal-recovery-cleanup-refined-a6/accepted-sweep-1792516437256798000/manifest.json"
```

Compose unchanged A5, then the two newly emitted accepted manifests, with tracked
`tools/original_target/compose.py`, the research root and a fresh tag. Do not add
the initial two-overlap cleanup manifest or compile a union as one population.
Existing local CrossOver/VC6/compiler-lock rules apply. Earlier source/original
matrices and native/SDL checks are unchanged and were not regenerated for A6.

## Costs and a rejected build experiment

Initial cleanup generation 9.308s, compiler 10.116s, comparison 1.060s. Independent
original gap audit 7.810s; owner original check 0.929s. Refined cleanup generation
0.658s, compiler 8.268s, comparison 1.022s. Requests generation 0.621s, compiler
7.478s, comparison 1.513s. Queues were measured negligible. Pipeline scopes overlap;
these are not additive whole-turn timings. Per-source compiler, model/token and
uninstrumented manual/handoff costs are unavailable. Previous failures remain intact.

One bounded private-integrator trial substituted the already reviewed indexed COFF
reader. All four generated integration artifacts remained identical, but candidate
16.652s versus same-runner control 15.564s showed no saving. It was not adopted;
active integrator SHA256 remains
`4be6f0c50fe209f3134ec33a4f251daf2f808e918a5ec8ab93b605393c0c26f5`.
Evidence: `build/integrator-index-a6/final-evidence.json`. Timing attribution is
unavailable; this gives no source credit. Tracked acceptance tools are unchanged.

## Final composition and independent accounting

Final manifest: `build/goal-a6-fresh-composed/accepted.json`, SHA256
`9de6b6ec976b15ea2b0293a30305647b792964b92fa7feaba0ca8bbd6adee6d4`.
It composes unchanged A5 with both newly source-reproduced A6 populations, excluding
the old two-overlap cleanup manifest. Complete composition took 37.250s: 13.413s
input validation, 9.125s integration, 6.797s linking, 0.479s packaging and other
verification/report overhead. Owner fresh requests reproduction took 15.156s;
refined cleanup 15.626s. Those stages overlap and are separate timing scopes.

The packaged output equals every supplied 4,485,392-byte target byte, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Raw linker output remains structurally different at 7,606,784 bytes. Original
headers, file padding and 272-byte overlay remain explicitly retained scaffold;
linked logical payloads and zero-filled virtual tails were checked. No original
game launch, playability, native port, pristine authenticity or YR claim follows.

Independent `goal-coverage-a6/REVIEW_A6_FINAL.md` and `HANDOFF_A6_FINAL.md` cite
actual complete source/width/order/ABI checks, strict component audits, fresh COFF
mappings, exact three-component union and actual transferred/linked/packaged
artifacts. All 6,522 actual sections/bindings, four linked payloads and 3,127,748
zero-tail bytes were checked. The reviewer did not rerun the compiler/linker;
owner execution and independent artifact inspection remain separate. The original
gap audit was authored by coverage and independently checked by the owner.

`goal-coverage-a6/final-source-ledger-a6/partition.jsonl`, SHA256
`6274f4c46fa0d6282eff40c36bad26f57baa5dc4140c6af8b80005fed45bd6f0`,
covers all 4,485,392 file bytes in 72,405 ranges while preserving original/prior
categories and attribution. All 8,245 archive-identity bytes remain scaffold with
zero source credit or library exceptions. Sixteen instruction/data-conflict and
nine body-without-instruction bytes remain unresolved. Existing virtual evidence
and the separate A5 25-byte helper-identity sidecar remain intact. The new 13
original-gap refusals and four copy misses remain explicit in their frozen inputs.
Most code and substantial classification/ABI work remain, so A6 does not complete
[the phase](../ORIGINAL_TARGET_PROCESS.md).

The owner cheaply refreshed existing recurring-shape ranks against 6,522 accepted
extents in `owner-rank-a6/remaining-shapes-after-a6.jsonl`, SHA256
`55d47f070ea1a99b6e705659bf641e0a1e7e3ae6b4a87bf5392598417b92e2c7`:
197 groups, 0.611s, no new Ghidra/library matrix. Remaining substantial hypotheses
include 60 destructor variants / 4,380 body bytes, 34 larger virtual-call loop
routines / 4,318, and 52 constructor-like routines / 3,848. Check prior source
attempts and independent original bodies/gaps/ABI before new generation. Baseline/
seeded views are separate, not additive source denominators. Known resize failures,
13 cleanup refusals and four copy misses are not wholesale new source populations.
