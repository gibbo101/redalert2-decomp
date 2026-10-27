# Original-target batch A1 — 2026-10-20

Historical batch record: lifecycle and commands below describe that batch. Current authority, paused goal status and canonical build are in [HANDOFF.md](../HANDOFF.md) and [ORIGINAL_TARGET_BUILD.md](../ORIGINAL_TARGET_BUILD.md).

The user activated the sustained recovery goal after process commit `73b48f5`.
This accepted batch advances that goal; full decompilation remains incomplete.
The existing chat owns build/integration; two medium workers performed source
recovery and independent inventory/acceptance review in isolated private outputs.

## Source result and accounting

| Measure | Previous accepted state | A1 integrated state |
| --- | ---: | ---: |
| Nonoverlapping matched source regions | 1,815 | 2,399 |
| C++ body bytes | 23,970 | 55,509 |
| Separate frozen NOP padding | 14,594 | 18,428 |
| Remaining original logical `.text` scaffold | 3,731,241 | 3,695,868 |

New source: **584 regions / 31,539 body bytes / 3,834 padding bytes**. These include
forwarding/virtual-call wrappers, multiple-call constructors and 314 repeated
owned-buffer cleanup regions. Reusable transformations retain conditional clears,
original call identities, vtable/global references, stack arguments and returns.
No original instruction arrays or inline assembly were inserted into candidates.
All counts remain matched source intervals, not confirmed original function counts.
Most program code remains unrecovered; game/library/type/ABI classification is open.

The `5d1d20` first-delivery literal-global source is superseded by a separately
frozen source with an explicit DIR32 global binding. It is selected before the
older overlapping source and counted once. Prior accepted extents otherwise win
conflicts; no analysis boundaries are merged to create passing comparisons.

## Reproduction and actual evidence

All artifact paths below are under ignored `private/original-target-20261020/`.

| Artifact | Meaning |
| --- | --- |
| `goal-recovery-calls-a1/final-evidence.json` | Six successful compiler sessions, immutable candidate/accepted manifests, failures and source/script snapshot limitations |
| `build/goal-a1-composed/accepted.json` | Hash `a56c5bc79832ff2114252639f8517892394a6a9cb7b4797c3e7c16221e94eafa`; reviewed source mapping from reused verified compiler outputs |
| `build/goal-a1-composed/composition-receipt.json` | Actual combined assembly/link/package check, 22.360s; correctly records compiler-output reuse |
| `shared/union-1792512611408384000/manifest.json` | Fresh-source accepted manifest, SHA256 `37f4468d9fa552d5bbea18942ac442695982a3fe1f19f2548eac87d550d2436c` |
| `build/union-1792512611408384000/rebuild-receipt.json` | Fresh all-source eight-population compile/compare/assemble/link/package build, **149.025s** |
| `goal-build-a1/fresh-source-provenance-audit-v4.json` | Current tracked acceptance verifier passes all2,399 fresh compiler-output regions |
| `goal-build-a1/fresh-mapping-equivalence.json` | Fresh source/options/ranges/full bytes/references/relocations equal reviewed composition; object file hashes legitimately changed |
| `goal-coverage-a1/ACCEPTANCE_REVIEW_V4_FINAL.md` | Author-independent source review, negative probes, compiled-section placement and actual whole-file artifact check |
| `goal-coverage-a1/ACCEPTANCE_EXTENSION_FRESH_A1.md` | Independent check of changed fresh COFF objects, resolved relocations, mapping equivalence, linked sections and full file |
| `goal-coverage-a1/final-source-ledger-a1/` | Updated full-file partition, hashes and preserved underlying evidence |

The fresh and composed final files each equal all **4,485,392 supplied bytes**,
SHA256 `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Raw VC6 output still differs structurally and has7,606,784bytes; original PE
headers/file padding/overlay packaging remains explicit. No original game launch,
Windows action, native adaptation or native regression was needed for this batch.

Fresh reproduction from the repository root with existing dependencies:

```sh
RA2_RESEARCH_ROOT=private/original-target-20261020
PYTHONDONTWRITEBYTECODE=1 private/matching-pilot/20261020T123117Z/env/bin/python \
  "$RA2_RESEARCH_ROOT/scripts/rebuild_union.py" \
  "$RA2_RESEARCH_ROOT/recovery-b/accepted-sweep-1792510345458019000/manifest.json" \
  "$RA2_RESEARCH_ROOT/recovery-b/accepted-sweep-1792510520585375000/manifest.json" \
  "$RA2_RESEARCH_ROOT/goal-recovery-calls-a1/accepted-sweep-1792512407619603000/manifest.json" \
  "$RA2_RESEARCH_ROOT/goal-recovery-calls-a1/accepted-sweep-1792512087235131000/manifest.json" \
  "$RA2_RESEARCH_ROOT/goal-recovery-calls-a1/accepted-sweep-1792512209333468000/manifest.json" \
  "$RA2_RESEARCH_ROOT/goal-recovery-calls-a1/accepted-sweep-1792512253018717000/manifest.json" \
  "$RA2_RESEARCH_ROOT/goal-recovery-calls-a1/accepted-sweep-1792512324520805000/manifest.json" \
  "$RA2_RESEARCH_ROOT/goal-recovery-calls-a1/accepted-sweep-1792512391145808000/manifest.json"
```

Expected exit0, new `build/union-*` receipts and exact target size/hash, with55,509
source-body bytes. Existing CrossOver local-socket escalation and compiler.lock
rules apply. [Build setup](../ORIGINAL_TARGET_BUILD.md) documents tools and frozen
inputs. Do not pass a combined union manifest to a single-population source driver.

## Tracked acceptance tools and review

`tools/original_target/verify_manifest.py` independently ties each credited body/
padding range to frozen inventory/gaps, compiler aggregate/case, source/object
hashes, actual COFF selector/extent, inspected references and complete original
bytes. It accounts for all emitted code bytes in each frozen candidate population;
unknown data/section forms refuse. Metadata requires supported names AND flags.
Object validation is scoped to both object identity and candidate-population hash.
DIR32/REL32 binding checks use actual decoded original operand boundaries.

`coff.py` rejects truncated/bad symbol/relocation/backing ranges and handles
uninitialized data without large zero allocation. `compose.py` verifies immutable
inputs, retains true population provenance while resolving overlaps conservatively,
links the selected source sections and compares the complete packaged file. It is
an incremental composition route, not a claim of fresh source recompilation.
Use its `--help` for required inputs; fresh-source reproduction is above.

Seven synthetic parser tests pass:

```sh
python3 -B -m unittest discover -s tests -p test_original_target_coff.py
```

Independent review reproduced seven negative acceptance probes, including hidden
nonpopulation bytes, executable sections disguised as metadata, unsupported
section flags and mutated selectors/reference maps. Original defects and fixes
remain in the private V1–V4 review records. V4 review covers current supported
compiler objects; arbitrary malformed-format security fuzzing and future compiler
formats are not claimed. Independent artifact/source review is distinct from the
owner's fresh compiler/linker execution and from full-phase final acceptance.

## Coverage and library evidence

The updated partition has72,285 nonoverlapping rows totaling4,485,392file bytes;
its SHA256 is `2ef14230e74fde1cbf2f9d8570af2c296a3918fc0bceea6375ac3d70cb4ff337`.
A separate virtual-image ledger includes implicit zero tails rather than inventing
file bytes. Underlying conflicting/uncertain Ghidra evidence remains attached.

58 distinct target intervals totaling8,245bytes match complete supplied VC98
archive code sections. There are170 matching archive-section records, including
22 relocated records/390 resolved relocations. This is inspectable library-identity
evidence, **zero additional C-source credit and zero final library exceptions**.
No entire library or remaining executable region is assumed recovered/exempt.
The16 instruction/data conflict bytes and nine body bytes without instruction
coverage remain explicit. No whole-game percentage or proven function denominator.

## Costs, limitations and next work

New worker compiler sessions:48.473s; comparisons:2.438s; recorded queue time
about0.000194s. Ledger generation11.890s and archive probe3.292s; composition and
fresh build timings above are separate overlapping scopes and must not be added
as wall time. Initial Wine sandbox refusal and aggregate source argument-conversion
compile failure are preserved. Per-function compile times, model/token costs and
complete generation/repair wall costs were not instrumented.

Historical iterative generator versions were not all snapshotted; generated C++,
compiler scripts, manifests, object files and comparisons are frozen and the full
source rebuild passed. The final generator snapshot exists. Future generation
must snapshot each dependency version before reporting a reproducible generator.

Continue broad recovery using ranked remaining families, including global FP
initialization/conversion and additional control flow, while refining boundary/
library classification independently. No phase-completion claim: required game
code scaffold, unresolved types/ABIs and unexamined categories remain. See
[STATUS.md](../STATUS.md) and [HANDOFF.md](../HANDOFF.md) for the active continuation.
