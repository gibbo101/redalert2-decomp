# Original-target batch A2 — global FP recovery

Historical batch record: lifecycle and commands below describe that batch. Current authority, paused goal status and canonical build are in [HANDOFF.md](../HANDOFF.md) and [ORIGINAL_TARGET_BUILD.md](../ORIGINAL_TARGET_BUILD.md).

Accepted after [A1](ORIGINAL_TARGET_BATCH_20261020_A1.md), 2026-10-20. The sustained
goal remains active; this is another exact-source batch, not phase completion.

## Result

Added **1,646 disjoint source regions / 44,096 body bytes / 19,731 frozen padding
bytes** from1,687 independently bounded candidates. The accepted cumulative state
is **4,045 regions / 99,605 body bytes / 38,159 padding bytes**. Remaining logical
`.text` scaffold: **3,632,041 bytes**, not all classified as instructions.

Sources are ordinary extern-C cdecl wrappers for global FP expressions and scalar
math/integer conversions, with explicit typed global DIR32 and direct-call REL32
bindings. The compiler's `__ftol` conversion reference is bound to the inspected
original call target; helper implementation/library identity is still unresolved.
Original operand order is retained through source-expression ordering and exact
compiler-output comparison. A two-option `/Op` trial yielded zero; no `/Op` case
was accepted.41 candidates remain full-extent mismatches, not prefix matches or
boundary repairs. No instruction arrays, original inline asm or native adaptation.

## Immutable evidence

Paths are under ignored `private/original-target-20261020/`.

| Path | Evidence |
| --- | --- |
| `goal-recovery-fp-a1/final-evidence.json` | Component order, hashes, generation snapshots, three compiler sessions and failures/limits |
| `goal-recovery-fp-a1/accepted-sweep-1792512924028134000/manifest.json` | First706regions /19,276body /7,060padding; SHA256 `dd0be2b341c32a0a27f873cc71c066488b4360872ef66337f8bcd0d217faeac7` |
| `goal-recovery-fp-a1/accepted-sweep-1792513074876791000/manifest.json` | Next940regions /24,820body /12,671padding; SHA256 `8de50c162b500ca1c1d3ff7b6703041c8db21c68f8e160b089349f7f218ee9fd` |
| `build/goal-a2-composed/accepted.json` | First reviewed4,045-region composition, SHA256 `4aace635f8000abf96949eb4f34b28e0502dd2cfdc339a9f860e6b6ec26aff5e` |
| `build/rebuild-1792513376499199000/rebuild-receipt.json` | Owner fresh706-source population reproduction,36.575s |
| `build/rebuild-1792513377938683000/rebuild-receipt.json` | Owner fresh940-source population reproduction,29.610s |
| `build/goal-a2-fresh-composed/accepted.json` | Final accepted manifest SHA256 `00eda8fda68fa947eb68ef187741941cb46f52c0b2956224c720d239038dd4a1` |
| `build/goal-a2-fresh-composed/composition-receipt.json` | Final composition of newly reproduced FP outputs with unchanged freshly built A1,35.248s |
| `goal-coverage-a1/ACCEPTANCE_REVIEW_FP706.md`, `ACCEPTANCE_REVIEW_FP940.md` | Author-independent source/type-width/reference/component audits |
| `goal-coverage-a1/ACCEPTANCE_EXTENSION_A2_FRESH_FINAL.md` | Independent changed-object, relocation, source-mapping, section/zero-tail and complete-file extension |
| `goal-coverage-a1/final-source-ledger-a2/` | Full-file partition/summary/input hashes; earlier ledgers and library evidence preserved |

Both full compositions match all **4,485,392** supplied bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
The final assembly/link used newly recompiled FP objects plus the unchanged fresh
A1 source outputs; unchanged A1 candidate matrices were not rerun for A2. Each
FP population's source rebuild also checked a complete reference file. Compiler
object paths/hashes changed legitimately; source/options/bounds/raw and resolved
bytes/reference mappings were independently checked equivalent across reproductions.
Raw linker output remains structurally different; original PE headers, padding
and overlay packaging remain explicit. Independent review did not rerun compilers.

## Reproduce

The existing source driver was exercised separately for both FP populations:

```sh
RA2_RESEARCH_ROOT=private/original-target-20261020
PYTHONDONTWRITEBYTECODE=1 private/matching-pilot/20261020T123117Z/env/bin/python \
  "$RA2_RESEARCH_ROOT/scripts/rebuild.py" \
  "$RA2_RESEARCH_ROOT/goal-recovery-fp-a1/accepted-sweep-1792512924028134000/manifest.json"
PYTHONDONTWRITEBYTECODE=1 private/matching-pilot/20261020T123117Z/env/bin/python \
  "$RA2_RESEARCH_ROOT/scripts/rebuild.py" \
  "$RA2_RESEARCH_ROOT/goal-recovery-fp-a1/accepted-sweep-1792513074876791000/manifest.json"
```

Expected exit0 and new private `build/rebuild-*` directories. Combine A1's accepted
manifest with each new run's `accepted.json` using tracked
`tools/original_target/compose.py --research-root ... --manifest ...` in priority
order A1,706,940; select a new `--tag`. That route was exercised for the final
composition above. Existing Mac/CrossOver/compiler.lock rules apply.

For a full all-population source reproduction, use the A1 eight-population command
and append these two FP component manifests to `scripts/rebuild_union.py`.
Do not feed the already combined4,045-region manifest to a single-population source
driver. Normal iteration should reuse immutable unchanged sources/objects and check
changed coverage, rather than regenerate unrelated matrices.

The tracked verifier and tools are unchanged from reviewed V4. An explicit audit:

```sh
PYTHONDONTWRITEBYTECODE=1 private/matching-pilot/20261020T123117Z/env/bin/python \
  tools/original_target/verify_manifest.py \
  --manifest private/original-target-20261020/build/goal-a2-fresh-composed/accepted.json \
  --exe private/original-target-20261020/inputs/game.exe \
  --report private/original-target-20261020/NEW-a2-provenance.json
```

Choose a new report path; never overwrite prior evidence. All generated source,
objects, compiler tools, input binaries and receipts remain private/ignored.

## Accounting, costs and limits

The A2 ledger has72,286 nonoverlapping rows over all4,485,392file bytes. Partition
SHA256: `16e7f0be11184b86924a44783c159b86c85024363a2bb8aeee6f65c2d14f5390`.
Equivalence ties that reviewed partition to the final fresh-object manifest without
rewriting its original provenance. The8,245 archive-identity bytes remain entirely
scaffold, with no source credit or final library exception.16 instruction/data
conflict bytes and nine body bytes without instruction coverage remain unresolved.

Worker generation13.521s; three compiler sessions22.125s; comparisons23.555s;
recorded queue about0.000106s. Initial composition37.869s; fresh FP reproduction
36.575/29.610s and final composition35.248s are separate overlapping scopes, not
additive wall time. Script snapshots were frozen/verified for every generation.
Per-function compiler and model/token costs were unavailable. A stale displayed
count in an independent artifact report was preserved as an error copy, corrected
and rerun; final checks and counters cover all4,045 actual sections.

Exact byte matches preserve target x87 instruction/operand order but do not prove
portable FP semantics, original global API/type identities, helper-library origin
or whole-function boundaries. The source casts and compiler settings are VC6-specific;
control word/precision and signed conversion interpretations remain qualified.
Most game/program code and substantial classification work are still outstanding.

Next broad work: remaining loop/container comparison families, module/option variants
where extents genuinely differ, and shared global/type/reference classification.
Keep new C++ generation reusable and independently bounded. Do not force the41 FP
misses into source progress or treat successful file reconstruction as completion.
