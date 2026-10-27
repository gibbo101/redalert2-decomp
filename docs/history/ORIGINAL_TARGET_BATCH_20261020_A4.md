# Original-target batch A4 — initialization and guarded offsets

Historical batch record: lifecycle and commands below describe that batch. Current authority, paused goal status and canonical build are in [HANDOFF.md](../HANDOFF.md) and [ORIGINAL_TARGET_BUILD.md](../ORIGINAL_TARGET_BUILD.md).

This batch follows [A3](ORIGINAL_TARGET_BATCH_20261020_A3.md). The sustained
base original-target recovery goal remains active and incomplete.

## Global initialization source

The first component adds401source intervals /12,384C++bodybytes /254frozen NOP
padding bytes:247 multi-store routines and154 routines with a registration call.
416independently bounded candidates across four existing compiler variants yielded
895exact and769mismatching option cases.15distinct full-extent size misses remain
scaffolded; no boundary repairs, masks or prefix acceptance.

Ordinary C++ scalar stores preserve ordered original byte/word/dword writes.
All154 accepted call routines bind the same inspected original direct-call target.
Pushed code addresses use opaque external address declarations when the frozen
inventories do not establish entries. Those references recover no implementation,
function extent or API signature at the referenced addresses. Opaque declarations
are not instruction arrays or original-code execution. Callback/scalar-address
roles, global aliases, complete objects, cdecl signatures and startup semantics
remain hypotheses despite exact compiled target instructions.

Frozen private evidence beneath `private/original-target-20261020/`:

- `goal-recovery-globals-a1/final-evidence.json`, SHA256
  `88f68b5c323bc4f9c7d8453368fd7cbb83784136965baf8f9fc9d71fbaf4de17`.
- `goal-recovery-globals-a1/accepted-sweep-1792514590557512000/manifest.json`, SHA256
  `cc34a163044d6a2dbbcb618ebd4b0610677f5c5e1331d2c8b7cc56cd88f949c5`.
- `build/rebuild-1792514634390472000/`:owner fresh entire-population/four-option
  compile and complete packaged reference reproduction,15.186s. Fresh accepted
  manifest SHA256 `fe88bb62faca682322da9b6cf16b327cc384d4e39843f522eae83859909d32a4`.
- `goal-coverage-a4/independent-globals401-{audit,source-review}.json` and
  `independent-globals401-fresh-mapping.json`:independent strict interval/provenance,
  actual source/ordered fields and fresh COFF binding/byte checks.1,486ordered stores
  (491word,733dword,262byte) and154opaque pushed code-address uses were inspected.
  This reviewer did not rerun the compiler; owner source reproduction is separate.

Worker generation8.451s; compile6.578s; comparison1.190s. Per-source compiler,
model/token and uninstrumented manual/handoff costs are unavailable. Original
sources, compiler files and generated artifacts remain private/ignored.

## Preserved failed resize experiments

`goal-recovery-resize-a1/final-evidence.json`, SHA256
`7f7e06904b50bfd770fecc79b4de3da5478ed90f3740a1a4458ebfacecb6aed6`,
retains35resize/copy-loop hypotheses /6,160bodybytes and three source variants.
Four standard compiler options yielded0exact /420full-extent mismatches.
Worker generation13.021s; compiler21.160s; comparison0.547s. Copy-loop instructions
were reproduced, but failure-block placement, branch width and boolean-store
register/zero-extension differed. This is failure analysis, not accepted source.

`owner-resize-options-a1/final-evidence.json` extends only those three frozen
source populations with six additional module-option hypotheses: speed/size,
global optimization, frame pointer, intrinsic and alias settings.0exact /630
full-extent mismatches; compiler22.103s, comparison0.919s, negligible measured
queue. No source/bound changes, acceptance manifest or source credit. These trials
do not establish original compiler/module options or rule out other source forms.
Original failed artifacts/scripts are preserved, and no jobs from them remain.

## Guarded unsigned offset source

The second component adds331regions /8,935bodybytes /1,657frozen NOP padding
bytes.353independent candidates across four existing options yielded331exact and
1,081mismatching option cases;22distinct extent-size misses remain scaffolded.
Ordinary const methods preserve raw guard-byte truth, unsigned32wrapping subtraction,
and each original logical-right-shift constant. Original shifts vary from1through4;
this is not signed pointer subtraction or division. Member offset observations do
not establish original class, pointer provenance, element type, API or library role.
All observed entry references are data/table hypotheses rather than direct callers.

- `goal-recovery-offsets-a1/final-evidence.json`, SHA256
  `87f6c51fa2dedb26fe53d3ac7d70add3e7405c04cf8a16434caa7d3b0adf6b6f`.
- `goal-recovery-offsets-a1/accepted-sweep-1792514729787144000/manifest.json`, SHA256
  `fc99e9c64cb8d05031d575a25d4e82319178d71b44e54ec677677b48d307d5fc`.
- `goal-coverage-a4/guarded-offset-{bounds.jsonl,summary.json}` independently
  corroborates original whole-body operands/control flow/widths and frozen gaps
  against the4503region baseline before source generation; no source credit alone.
- `build/rebuild-1792514783530357000/`:owner fresh entire-population/four-option
  source compile and complete packaged reference reproduction.

An initial generator assertion incorrectly required gap provenance even for a
body-only region with an excluded181-byte unknown gap. That partial generation
was preserved and never compiled. The correction respects the independently frozen
body-only region and checks gap identity only when padding was actually included.
No unknown bytes were added, removed or reclassified to obtain a match. See
`goal-recovery-offsets-a1/initial-generation-failure.json` and frozen script versions.

Worker successful generation0.413s; compile7.336s; comparison0.784s. Owner fresh
source/reference reproduction took 14.036s. Failed-generation/model/
per-source compiler and uninstrumented manual/handoff costs are unavailable.

## Combined state and reproduction

A4 adds **732 source intervals /21,319bodybytes /1,911paddingbytes**. Cumulative
state: **5,235 intervals /143,987C++bodybytes /43,871frozen NOP padding bytes**,
187,858total compiler extent bytes. Remaining logical `.text` scaffold:
**3,581,947bytes**, not all proven instructions. Neither interval counts nor
original-byte reconstruction are whole-game completion percentages.

To reproduce each changed source population from the repository root:

```sh
RA2_RESEARCH_ROOT=private/original-target-20261020
PYTHONDONTWRITEBYTECODE=1 private/matching-pilot/20261020T123117Z/env/bin/python \
  "$RA2_RESEARCH_ROOT/scripts/rebuild.py" \
  "$RA2_RESEARCH_ROOT/goal-recovery-globals-a1/accepted-sweep-1792514590557512000/manifest.json"
PYTHONDONTWRITEBYTECODE=1 private/matching-pilot/20261020T123117Z/env/bin/python \
  "$RA2_RESEARCH_ROOT/scripts/rebuild.py" \
  "$RA2_RESEARCH_ROOT/goal-recovery-offsets-a1/accepted-sweep-1792514729787144000/manifest.json"
```

Use tracked `tools/original_target/compose.py` with a fresh tag, research root,
and manifest priority unchanged A3 then the two newly emitted accepted manifests.
Do not compile a combined union as one population. Actual compiler/linker sessions
use the existing Mac CrossOver bottle/legitimate VC6 files and shared compiler lock.
Unchanged A1–A3 matrices/native/SDL checks were not rerun for A4.

## Complete reference build

`build/goal-a4-fresh-composed/accepted.json`, SHA256
`8cd350e44f4ade1cbcc8665c7f7f63321252e744d22c8c5ab4a77e3c708bd05c`,
composes unchanged accepted A3 with both newly source-reproduced A4 populations.
`composition-receipt.json` records40.546s:19.566s input validation,6.414s
integration,6.595s linking and0.470s packaging, plus other audit/report overhead.
Private-driver post-run identities/snapshots supplement the normal compose V4
tracked-tool snapshot. The reviewed A3immutable-object IO optimization is unchanged.

Every packaged file byte equals the supplied4,485,392-byte target, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Raw linker output remains7,606,784bytes and structurally different. Original PE/DOS
headers, raw padding and272-byte overlay remain explicit scaffold. All logical
section payloads and implicit zero tails are checked. Exact packaged reconstruction
does not establish pristine authenticity, complete source recovery or playability.
No native port/SDL/whole-frame/YR claim follows.

## Independent acceptance and coverage

`goal-coverage-a4/REVIEW_A4_FINAL.md` and `HANDOFF_A4_FINAL.md` join the component
source/width/order/reference audits, actual fresh-object mappings and complete
artifact review. The reviewer did not rerun compiler/linker sessions. Owner source
reproduction remains separate. `independent-a4-output-check.json` checks all5,235
actual transferred sections/bindings, four linked logical payloads and3,127,748
zero-tail bytes, plus every packaged file byte (0.629s).

`goal-coverage-a4/final-source-ledger-a4/` overlays accepted extents on previous
frozen category evidence:72,399nonoverlapping rows cover all4,485,392filebytes;
partition SHA256 `cde910139493ce89cc9945232c41dd561b5cbd3def46250c1eba2c36bfe1c3e6`
(0.811s).8,245archive-identity bytes remain scaffold, with no source credit/final
library exception.16instruction/data conflict bytes and9body/no-instruction bytes
remain unresolved. Earlier ledgers, library probes and virtual-domain evidence
are preserved; no unchanged Ghidra/library matrix regeneration.

Next useful source populations include chained x87/math wrappers and affine
integer/FP initialization wrappers identified in the refreshed4503-baseline
ranking. Re-filter against the final5235intervals before generation. Investigate
helper calling conventions/intrinsic lowering independently; do not presume
ordinary cdecl stack arguments for x87 register-helper calls. Shared symbols,
class/API/ABI and library/code/data classification remain incomplete. Most
program code remains original scaffold, so A4 does not meet the full-phase
completion criteria in [process](../ORIGINAL_TARGET_PROCESS.md).
