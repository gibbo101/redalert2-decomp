# Original-target batch A5 — affine and chained FP wrappers

Historical batch record: lifecycle and commands below describe that batch. Current authority, paused goal status and canonical build are in [HANDOFF.md](../HANDOFF.md) and [ORIGINAL_TARGET_BUILD.md](../ORIGINAL_TARGET_BUILD.md).

This batch follows [A4](ORIGINAL_TARGET_BATCH_20261020_A4.md). The sustained
base original-target decompilation goal remains active and incomplete.

## Result

Added **706 disjoint source intervals / 26,417 C++ body bytes / 7,471 frozen NOP
padding bytes** from 724 independently bounded candidates. The first component
has 241 affine integer/FP casts and 226 integer-scale/math wrappers; the second
has 239 chained power/math wrappers. All 18 remaining candidates are full-extent
size mismatches: three affine, nine integer-scale and six chained wrappers. No
boundary repair, padding trimming, masks or prefix acceptance was used.

The cumulative state is **5,941 source intervals / 170,404 body bytes / 51,342
padding bytes**, totaling 221,746 compiler extent bytes. **3,548,059 logical
`.text` bytes remain original scaffold**, not all proven code. Counts are source
intervals, not confirmed original functions or whole-game completion percentages.

Sources are ordinary C++ expressions with explicit original global/call bindings.
Affine arithmetic wraps as unsigned 32-bit arithmetic before signed integer-to-FP
conversion. Chained wrappers use VC6's recognized `pow` intrinsic lowering to the
original x87-register helper, preserving operand/load order, then a separate
cdecl math call. No inline original assembly, machine-code arrays or hand-written
instruction intrinsics are present. Exact emitted target operations remain the
acceptance boundary; shared global/API/type/alias/ABI and portable FP semantics
remain qualified.

## Helper evidence and limits

The original 25-byte wrapper at `0x7821b0` exactly matches the complete `__CIpow`
function extent in the legitimate VC98 `LIBC.LIB` and `LIBCMT.LIB` `pow.obj`
members. The next independent COFF function symbol bounds that wrapper. Wrapper
SHA256: `a39b146e16cbbab84442ad0a2ac74ad3532fec7ad9f70bf38cf2d7d8f4a99ff9`.
It rearranges the two x87 operands into stack doubles and calls the following
implementation. This supports the intrinsic/helper ABI; it does not establish
all 541 bytes of the object section, its 23 external/data relocations, the full
power implementation, a final library exception or any C-source credit there.
Targeted archive inspection took 0.178s; no broad library matrix was regenerated.

The original integer-conversion helper at `0x77f110` differs from stock VC98
`__ftol`: its 61-byte body conditionally loads control word `0x0e7f` from
`0x7d8964` and leaves it in force. That word selects truncation and 53-bit precision
with exception masks set. The stock 39-byte archive helper instead saves/restores
the control word. Source cast lowering binds the actual target; stock CRT identity,
a recovered helper implementation and portable cast/FP-state equivalence are not
claimed. The separate math callee at `0x4ba410` remains opaque; inspected rounding/
table operations are not a complete recovered algorithm or standard-library identity.

Private targeted evidence: `goal-coverage-a5/targeted-helper-library-probe.json`
and its helper analysis; worker source-model/reference audit and copied evidence
snapshot preserve these qualifications.

## Frozen source and fresh reproduction

Payload paths below are beneath ignored `private/original-target-20261020/`.

- `goal-recovery-fp-a5/final-evidence.json`, SHA256
  `5470da1f8ee35a2520ef371b42faa9e9232a8df43624bf6fd9f619d0986a59b8`:
  both component populations, source/script snapshots, original reference widths,
  source models, misses and costs.
- `goal-recovery-fp-a5/accepted-sweep-1792515092312257000/manifest.json`:
  467 intervals / 16,857 body / 5,559 padding bytes; SHA256
  `e7abb21d584500431e6bdb4403dc6aafe9dedab90fcfa36cf2092b1a760e9695`.
- `goal-recovery-fp-a5/accepted-sweep-1792515158598585000/manifest.json`:
  239 intervals / 9,560 body / 1,912 padding bytes; SHA256
  `02122b14886eadd38f1db97e67f3c7447477126535e05cc2542610ff356a3134`.
- `build/rebuild-1792515235245202000/`: owner fresh first-population reproduction,
  22.909s. Entire frozen source population across the original four options.
- `build/rebuild-1792515243491814000/`: owner fresh chained-population reproduction,
  20.313s. Both reproductions also checked a complete packaged reference file.

Run each component separately from the repository root:

```sh
RA2_RESEARCH_ROOT=private/original-target-20261020
PYTHONDONTWRITEBYTECODE=1 private/matching-pilot/20261020T123117Z/env/bin/python \
  "$RA2_RESEARCH_ROOT/scripts/rebuild.py" \
  "$RA2_RESEARCH_ROOT/goal-recovery-fp-a5/accepted-sweep-1792515092312257000/manifest.json"
PYTHONDONTWRITEBYTECODE=1 private/matching-pilot/20261020T123117Z/env/bin/python \
  "$RA2_RESEARCH_ROOT/scripts/rebuild.py" \
  "$RA2_RESEARCH_ROOT/goal-recovery-fp-a5/accepted-sweep-1792515158598585000/manifest.json"
```

Compose unchanged A4, then both newly emitted accepted manifests, with tracked
`tools/original_target/compose.py`, research root and a fresh tag. Never compile a
union manifest as one population. Existing local CrossOver/VC6/hash/compiler-lock
rules apply. Unchanged source/original matrices and native/SDL checks were not rerun.

## Reviewed COFF selector improvement

The prior selector scanned all symbols twice per requested function. Indexing the
immutable parsed object once preserves defined-function filtering, prefix ambiguity,
strictly later offsets, aliases, explicit auxiliary extents and section-backing
caps. Byte, original-bound, source, compiler, relocation and complete-extent checks
are unchanged. Parsed-symbol mutation is outside the immutable-object contract.

A full unchanged A4 audit took 19.664s before; an isolated prototype took 9.380s
with an identical complete result. The actual tracked candidate took 10.158s with
that same result. `build/audit-io-a5/` preserves original/candidate source identities
and receipts. Independent old/new comparison covered 25 actual A4 objects and
17,788 selectors: 17,666 successful results and 122 refusals agreed (8.427s).
Twelve synthetic tests, including five new ambiguity/alias/extent regression cases,
passed independently. Review: `goal-coverage-a5/coff-index-independent-review.json`.
No source progress or standalone benchmark/cache framework is claimed.

Tracked COFF reader SHA256:
`71a08ef7b773681db733dfae265d763056435a10012d01c735bcc04a812228e8`.
The V4 verifier and composer are unchanged. Focused parser check:

```sh
PYTHONDONTWRITEBYTECODE=1 private/matching-pilot/20261020T123117Z/env/bin/python \
  -B tests/test_original_target_coff.py
```

## Full composition and costs

Final manifest: `build/goal-a5-fresh-composed/accepted.json`, SHA256
`cd6660e576b1bae28fa75cdf4d9c80d099532d2be3c41636576edf6bfc240f09`.
The complete composition used unchanged A4 and both newly source-reproduced A5
objects, with the reviewed indexed COFF reader. It took 39.901s: 15.616s input
validation, 11.070s integration, 6.802s linking, 0.505s packaging and other audit/
report overhead. This larger build has different costs; the isolated audit saving
is not a claim that total build time halved. Actual private-driver identities are
preserved separately from the normal tracked acceptance-tool snapshot.

Every packaged byte matches the supplied 4,485,392-byte executable, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Raw linker output remains structurally different at 7,606,784 bytes; retained
original headers, file padding and 272-byte overlay remain explicit scaffold.
Logical payloads and zero-filled tails are checked. No original game launch,
pristine-authenticity, playability, native port or YR claim follows.

Worker generation 10.254s, compiler sessions 14.855s, comparisons 3.085s and
negligible measured queues. Owner reproductions and overlapping pipeline stages
are separate scopes, not additive wall time. Per-source compiler, model/token and
unmeasured manual/handoff costs are unavailable. Failed attempts remain preserved.

## Independent final accounting

`goal-coverage-a5/REVIEW_A5_FINAL.md` joins the actual source models/reference
widths/operand ordering, unchanged V4 strict acceptance with reviewed indexed COFF,
fresh object equivalence, actual transferred/linked/packaged artifact checks and
ledger. Compiler/linker sessions were executed by the owner, not independently
rerun by this reviewer. `independent-a5-output-check.json` covers all 5,941 actual
transferred sections and bindings, four linked payloads, 3,127,748 zero-tail bytes
and the complete packaged file (0.716s).

`goal-coverage-a5/final-source-ledger-a5/` overlays accepted extents on prior frozen
category evidence: 72,402 nonoverlapping ranges sum to all 4,485,392 file bytes;
partition SHA256 `761c9cd7437a76593a8b11802f1888e9ad9da500ce9560dcd11adc5764830a96`
(0.776s). Existing 8,245 archive-identity bytes remain scaffold with no source credit
or final library exception. The newly targeted 25-byte `__CIpow` identity remains
separate evidence with no exception/source credit. Sixteen instruction/data-conflict
and nine body-without-instruction bytes remain unresolved. Earlier ledgers and
virtual-domain evidence are preserved; no broad unchanged matrix regeneration.

The remaining source, classifications, ABI/types and library/assembly exceptions
still contradict full-phase completion. Re-filtered recurring families identify
next useful work; an exact source batch and original-byte reconstruction do not
complete [the phase](../ORIGINAL_TARGET_PROCESS.md).

The current-rank refresh is `goal-coverage-a5/remaining-shapes-after-a5.jsonl`,
SHA256 `42577c686a33733a188941926f47585c34bb13bdbecb95b22fb1223f4458e65e`:
198 groups in 0.579s. Next substantial hypotheses include the two baseline cleanup
families (179 / 7,518 body bytes and 183 / 7,137), guarded four-word global copies
(76 / 4,256), and global ECX-receiver initialization (160 / 3,680). Inventory
populations remain separate; these are not source matches or additive progress.
Inspect ordered pre-call clears, alias-sensitive writes and custom receiver/callee
conventions before generation. Failed resize work remains held with its actual
zero yield; already accepted FP families are not reassigned as new recovery.
