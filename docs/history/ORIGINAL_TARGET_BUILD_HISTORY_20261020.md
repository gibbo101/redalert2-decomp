# Historical build setup before canonical-source migration

The commands and ignored scripts below are preserved historical evidence, not the active build. Use ORIGINAL_TARGET_BUILD.md for current reproduction.

# Original-target build and baseline evidence

All paths below are local research state; proprietary inputs/generated outputs
remain ignored. Tracked docs contain summaries, paths, hashes and commands only.
Active policy: [process](../ORIGINAL_TARGET_PROCESS.md), [evidence](../RECOVERY.md).

## Exact supplied target

Repository: `/Volumes/Lesalia/Code/redalert2-native`.
Research root: `private/original-target-20261020/` (relative to that repository).
Frozen executable: `inputs/game.exe` beneath that root.

- Size: **4,485,392 bytes**; PE32 i386, preferred image base `0x400000`.
- SHA256: `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
- Embedded1.08, supplied1.006 lineage and reported no-CD provenance are distinct;
  pristine authenticity remains unverified. Older disc `135a57a0` evidence is separate.

## Current accepted state

The user-started goal has accepted [batch A10](ORIGINAL_TARGET_BATCH_20261020_A10.md):
6,763 matched source intervals / 215,781 body bytes / 57,572 padding bytes. Its
fresh nonleaf-initializer/factory population reproductions, complete composition and independent artifact/
source review are recorded there; [A1](ORIGINAL_TARGET_BATCH_20261020_A1.md) and
[A2](ORIGINAL_TARGET_BATCH_20261020_A2.md) and
[A3](ORIGINAL_TARGET_BATCH_20261020_A3.md) and
[A4](ORIGINAL_TARGET_BATCH_20261020_A4.md) and
[A5](ORIGINAL_TARGET_BATCH_20261020_A5.md) and
[A6](ORIGINAL_TARGET_BATCH_20261020_A6.md) and
[A7](ORIGINAL_TARGET_BATCH_20261020_A7.md) and
[A8](ORIGINAL_TARGET_BATCH_20261020_A8.md) and
[A9](ORIGINAL_TARGET_BATCH_20261020_A9.md) are preserved. The initial baseline below is preserved, not the latest state.

## Immutable initial baseline

Paths in this table are beneath the research root, not tracked payloads.

| Artifact | Role |
| --- | --- |
| `shared/union-1792510609009051000/manifest.json` | 1,815 nonoverlapping accepted source intervals; 291 overlapping deliveries retained as refusals |
| `recovery-b/accepted-sweep-1792510345458019000/manifest.json` | Baseline 470-region component, including inspected call-relocation cleanup wrappers |
| `recovery-b/accepted-sweep-1792510520585375000/manifest.json` | Separately frozen seeded-inventory 1,636-region component |
| `build/union-1792510609009051000/rebuild-receipt.json` | Fresh two-component source rebuild, conservative composition, whole-file result |
| `build/union-1792510609009051000/reference.exe` | Complete exact packaged output, same size/SHA256 as supplied target |
| `build/union-1792510609009051000/integration-manifest.json` | Compiler source/object/section provenance and resolved bindings |
| `build/union-1792510609009051000/raw-link-differences.json` | Structural raw-linker versus supplied-file differences |
| `reports/MILESTONE.md`, `reports/milestone.json` | Measured original-target milestone summary |
| `recovery-a/HANDOFF.md`, `recovery-b/final-evidence.json`, `recovery-b/NOTES.md` | Inventory deltas, source generation, attempts, failures and limits |
| `build/rejection-checks/receipt.json` | Negative source-hash, extent-hash and original-call-binding checks refused integration |

Accepted C++ body bytes: **23,970**. Separate frozen NOP padding: **14,594**.
Total compiler-derived accepted extents: **38,564** bytes. Remaining original
`.text` scaffold: **3,731,241** bytes, not all classified as executable code.
Other original data/resources and explicitly retained PE metadata remain separate.
The fresh combined source rebuild took **73.545 seconds**; component compiler
sessions totaled about **16.048 seconds**. Preparation was about **997.190 seconds**
from original intake to the later summary receipt; this includes overlapping work
and documentation time, not a pure compiler benchmark. Individual function compile
costs and token/model usage were unavailable.

The combined fresh rebuild exercised 2,611 candidates across two different frozen
populations/four options: 10,444 cases, 5,411 exact option cases and 5,033 mismatches.
Repeated candidates/options do not multiply distinct source recovery. The owner
reproduced these results locally; that is not independent final-phase acceptance.

## Existing local tools and environment

- Python with pefile/capstone:
  `private/matching-pilot/20261020T123117Z/env/bin/python`.
- Existing VC6 **12.00.8168** components and functioning private CrossOver bottle:
  `private/matching-pilot/20261020T123117Z/crossover/compiler/` and
  `private/matching-pilot/20261020T123117Z/crossover/bottle-vc6-a2/`.
  Historical `setup.json` describes failed a1, not working a2. Do not rerun its
  original setup script or overwrite completed pilot evidence.
- CrossOver **26.3**:
  `/Applications/CrossOver.app/Contents/SharedSupport/CrossOver/bin/wine`.
- Extracted VC6 linker/libraries:
  `private/original-target-20261020/toolchain/media/VC98/`.
  `toolchain/receipt.json` records legitimate media members/hashes. No MASM was
  found on the inspected media; installed clang emits i386 COFF scaffold assembly.
- Assembler:
  `/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang`,
  target `i686-pc-windows-msvc`. No global tool selection or license change; honor
  `DEVELOPER_DIR` for any later tools that use it.
- Ghidra **12.1.4**: `/opt/homebrew/Cellar/ghidra/12.1.4/libexec`;
  OpenJDK21: `/opt/homebrew/opt/openjdk@21/libexec/openjdk.jdk/Contents/Home`.
  The private direct Java launcher keeps projects/settings/cache/temp under the
  research root; the stock launcher would write settings elsewhere.

Existing compiler scripts hash-check the five compiler files against the prior
probe, sanitize CL/_CL_/LINK/INCLUDE/LIB/WINEPREFIX/CX variables and use private temp
paths. Exact flags include `/nologo /c /TP /Zp4 /GX- /GR- /W3`, with four recorded
optimization variants; no assumption of one universal original module setting.
Wine uses the existing private bottle, Windows `Z:` paths and local socket access
outside the shell sandbox. Scope any required escalation to the authorized local
compiler/linker command. Serialize sessions on research `shared/compiler.lock`;
do not stop a global wineserver or change a running job's inputs.

Already supplied media, read-only if re-extraction is genuinely required:
`<windows-mount>/Users/Mike/en_vs6_ent/en_vs6_ent_cd1.iso`, 643,276,800 bytes,
SHA256 `d38250b86c3bef0d8123cade40abd1728a776e22e9633683c3e311a913ae0347`.
`scripts/extract_toolchain.py` records extraction; normal rebuild uses local frozen
inputs/extracted tools and does not require a mounted ISO or the Windows machine.
Missing local inputs/tools are concrete blockers, not permission for a download,
installer, Windows action or global system change.

## Rebuild the accepted baseline from source

Run from the repository root with existing dependencies:

```sh
cd /Volumes/Lesalia/Code/redalert2-native
PYTHONDONTWRITEBYTECODE=1 private/matching-pilot/20261020T123117Z/env/bin/python \
  private/original-target-20261020/scripts/rebuild_union.py \
  private/original-target-20261020/recovery-b/accepted-sweep-1792510345458019000/manifest.json \
  private/original-target-20261020/recovery-b/accepted-sweep-1792510520585375000/manifest.json
```

Expected: exit0; new `build/union-*/rebuild-receipt.json` beneath the research root,
`whole_file_exact: true`, `source_recovery_bytes: 23970`, output size4,485,392 and
expected SHA256. Each frozen population is recompiled/compared separately before
conservative nonoverlapping composition. Do not pass the combined union manifest
to single-population `scripts/rebuild.py`: it concatenates overlapping populations
and is not the union reproduction route. Keep each run's receipts/failures.

Raw VC6 output itself is **7,606,784 bytes and not the exact original file**.
The build checks logical section bytes at their original RVAs, validates the zero
tail and packages original 4,096-byte PE/DOS headers, raw-file padding and 272-byte
overlay. The copied resource section is opaque `.rawres` while linking because
VC6 crashed in ZeroPad for `.rsrc`; packaging restores the supplied section/header
metadata. No instruction/data masks are used. See `raw-link-differences.json`.

## Coverage and interpretation limits

Sources currently use reusable conservative original-instruction-to-C++ expression/
control-flow templates. Broad raw Ghidra C was exported separately; it was not the
accepted baseline candidate source. No per-function hand repairs were used by the
recovery worker, and candidates contain no inline assembly/instruction arrays.
These compiler-facing temporary register/layout names are not final engine types.

Baseline and seeded Ghidra populations are independently frozen. The seeded pass
changed2,257 earlier bodies, removed550 entries and includes2,764 noncontiguous
bodies, six C-export failures and nine body bytes without instruction coverage.
They do not establish complete original boundaries, ABI/type semantics or a sound
whole-game denominator. Exact accepted interval bytes and their recorded boundary
hypothesis scopes remain distinct. Library/game classification is unresolved.
No gameplay, full decompilation, native port or pristine authenticity claim follows.

For next work use [HANDOFF.md](../HANDOFF.md), full completion criteria in
[ORIGINAL_TARGET_PROCESS.md](../ORIGINAL_TARGET_PROCESS.md) and the prepared
[goal condition](../ORIGINAL_TARGET_GOAL.md). Documentation-only updates should verify
these existing artifacts/commands without rerunning unchanged expensive matrices.
