# Supplied RA2 1.006 materialization and first migrated oracle

Current runtime/preparation status: [PROMOTION_1006.md](PROMOTION_1006.md). The
bounded prototype now selects the supplied 1.006 dataset by default, with distinct
source-matched prepared files. Historical checkpoint gates/commands below preserve
their original evidence scope and do not describe the current runtime gate.

[TERRAIN_LIFECYCLE_1006.md](TERRAIN_LIFECYCLE_1006.md) completes the retained
occupation/lifecycle/layer research profiles with 17,340 fresh results per engine
and all four sanitizer replays. Earlier subsystem migration checkpoints remain in
their notes. Archive precedence and prepared/runtime promotion are still pending;
historical identity/Facing details below keep their original checkpoint scope.

October 14, 2026. Ivalice / Apple Silicon macOS. This completes the bounded
**baseline identity and Facing** checkpoint, committed as `291e30b`.
[DRIVE_1006.md](DRIVE_1006.md) extends it with 108,475 executed Drive/curves/
timing/targeting comparisons per engine and resolves the duplicate Drive/Ship
streams. [PRESENTATION_1006.md](PRESENTATION_1006.md) adds 8,568 executed primitive
cases per engine; remaining rendering/lifecycle migration and promotion are pending.
This note does not promote the patched
installation into the native app or complete milestone 20.

## Identity and provenance

The supplied `RA21006EN.EXE` was completely applied to legitimate Allied inputs
inside a private in-memory research host. Its unchanged embedded engine returned
**0**, reporting **13 patches applied: four files modified and nine added**, with
zero missing/invalid/skipped inputs. All **16 final root files** were saved and
independently fingerprinted in `private/official-1006-probe/`. Input disc/prepared
file hashes were rechecked afterward; they remain unchanged.

| Output | Bytes | SHA-256 |
| --- | ---: | --- |
| `game.exe` | 4,485,392 | `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f` |
| `ra2.mix` | 281,888,480 | `896a8b64f9f1bb8ad5e0bc64fc0b8ea8c84112494761ea1a43478d10c5ef9914` |
| `language.mix` | 53,116,040 | `30345ccc41ab98d225cb87c8ea8629eb8cb1467ce0d7f15de87fb307424801e6` |
| `mph.exe` | 77,824 | `a8206165656c0430c11a73cfb9ba00aca08c651834f69ef5315cddfa7392309a` |

Added outputs are `patch.doc`, `launcher.txt`, `amazon.mmx`, `eb1.mmx`..`eb5.mmx`
and `invasion.mmx`. `ra2.exe`, `maps01.mix` and `multi.mix` are unchanged. There
is no new `patch.mix` in this package's result; it modifies `ra2.mix` itself.
The full inventory, logs, initial virtual hashes and API result are in its private
`manifest.json`; independent checks are in
`private/patch-inspection/materialization-verification.json`.

The user explicitly approved transferring only Windows base `game.exe` to
`private/windows-baseline-20261014/game.exe`. Both sides verified 4,485,392 bytes
and the hash above; Windows reports stable source creation/last-write metadata.
The Mac compared its bytes with the independently materialized output: **identical**.
Eleven output archives/maps also match Windows's reported asset hashes/sizes.
No additional proprietary payload was transferred. Windows metadata and the
receipt's provenance are retained in `reported-metadata.json` in that folder.

This establishes identity relative to the **user's supplied patch and media**;
it does not authenticate the package's publisher. The base engine is not different
from that output despite the user's reported no-CD installation provenance.
The supplied launcher and presentation wrapper remain separately identified;
this does not certify the entire installation or Yuri's Revenge as pristine.

The engine is PE32/i386, preferred base `0x400000`, entry RVA `0x385AA0`, timestamp
`991869933` (2001-06-06 23:25:33 UTC). Embedded FileVersion/ProductVersion remain
literally **1.08**. The patch lineage, not that string, establishes this 1.006 target.
PE raw layout: `.text` RVA/file 4096, 3,772,416 bytes; `.rdata` RVA/file 3,776,512,
192,512 bytes; `.data` RVA/file 3,969,024, 425,984 bytes; `.rsrc` RVA 7,524,352,
file 4,395,008, 90,112 bytes. Security directory is empty.

## Private materialization boundary

`private/patch-inspection/probe_engine.py` is an **experimental private probe**,
not a supported installer/importer or a shipped dependency. Its final SHA-256 is
`ed60a4c46ae98eec7ab7c1daf7b085c117e8f36c32e6d14ac8652ecb8ea4d070`.
It validates the supplied patch through `tools/inspect_patch.py`, loads its pinned
171,520-byte DLL into research-only Unicorn, and supplies bounded API fixtures.
All file access seen by the DLL is an in-memory virtual filesystem. Actual host
reads obtain the retained legitimate inputs; actual writes save fresh ignored
output only after the engine succeeds. No game executable is launched.

The explicit command was `-NOPATHSEARCH -NOSUBDIRSEARCH "c:\ra2" "c:\patch\ra2.rtp"`.
The DLL still reads `HKLM\Software\Westwood\Red Alert 2\InstallPath`, and its
resolved file operations use the virtual `c:\` aliases. It also writes six virtual
DWORD `Version` values ending at **0x00010006**. Therefore its update-directory
argument alone is **not a safe host confinement mechanism**. No real Mac/Windows
registry, installation path, process, network, share, driver or security setting
is exposed to this probe. Only that exact registry key/value is modeled; unknown
APIs and other registry operations fail closed.

The engine raises exception **0x4A4E4B**, with one status parameter **0**, at its
normal final exit. The probe dispatches to the unchanged DLL handler/filter and
models only the tested head-registration/no-intervening-frame unwind service.
The original cleanup produces the API return value; success is not forced and
no original instruction bytes are patched. File mappings are reclaimed after
unmapping. Timestamp/disk/registry/OS services are fixtures, not a complete Windows
host. Package file verification and independent Windows engine/archive matches
support the resulting byte identities.

The probe and resource bytes remain private. A local rerun requires a **fresh output
name** in the probe and the authorized Mac JIT context; preserve the successful
output. Its console log is `private/patch-inspection/probe-console.txt`. Earlier
missing-input/mapping/registry/exception failures are separate private reports and
are not successful patch runs. Do not execute this DLL on the host against a source
installation or generalize its fixtures to Yuri's Revenge.

## Verified Facing profile

Consulted [REFERENCES.md](REFERENCES.md) and pinned redalert2-recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439`, `docs/RECON.md` and `docs/testing.md`.
Their binary-family/testing guidance supplied the hypothesis that version labels
and upstream addresses cannot select our target. Its reported Steam base size
5,077,312 differs from this output. No upstream/generated code was incorporated.

Local signature discovery, complete instruction-range inspection and operand/call
checks independently established these mappings. `tools/verify_facing_mapping.py`
checks **358 instructions in eight complete padded routine ranges**, allowing only
explicit frame-counter/helper/relative-branch address changes. It executes no
original instructions and claims no whole-engine equivalence.

| Facing/helper | Allied disc VA | Supplied 1.006 VA |
| --- | --- | --- |
| SetDesired | `0x4B8550` | `0x4B8A30` |
| SetCurrent | `0x4B8630` | `0x4B8B10` |
| Current | `0x4B8700` | `0x4B8BE0` |
| IsRotating | `0x4B87B0` | `0x4B8C90` |
| Clockwise | `0x4B87E0` | `0x4B8CC0` |
| Counterclockwise | `0x4B8820` | `0x4B8D00` |
| SetROT | `0x4B89B0` | `0x4B8E90` |
| Remaining timer helper | `0x453B30` | `0x453EB0` |
| Frame counter | `0xA2894C` | `0xA40D2C` |

`tests/compare_original.py` selects **Facing only** by full executable SHA-256.
All **16,598 original/native comparisons pass on each build**, preserving the
existing division order, signed ties/wrapping, timer sentinel/expiry, ROT truncation
and interrupted requests. The patched suite also passes against ASan/UBSan native
vectors. No APIs are stubbed or original instructions modified in these Facing
tests. Write ranges, object/input/result canaries, read-only arguments, caller
stack/ESP and callee-saved registers are audited on every original call.

Object padding/unused timer fields remain excluded from native result comparison;
ordered original/native writes are not compared. This is Facing arithmetic/state,
not complete unit turning/movement integration or a Windows gameplay observation.
The original `EXPECTED` import stays disc-only for all other existing oracles.
Reports use separate defaults per profile and refuse public/source-tree/symlink
destinations or replacement of another executable's evidence. Three synthetic
guard tests pass; all source bytes stay supplied by the user.

## Asset/table inspection and migration still required

Read-only candidate comparison finds **63 of 64 selected asset hashes unchanged**:
palettes/VPL, three Rhino VXL/HVA pairs, all 28 ordinary trees, all 23 props, theater
INI and art. `rules.ini` changes **15 keys**. All HTNK/INGALITE keys, TreeStrength
and ExtraUnitLight remain unchanged (**68 checked keys**). `maps01.mix` is entirely
unchanged, as are the relevant temperate theater archives. This compares archive
members in the current native candidate order, **not original load precedence**.
Private evidence: `archive-member-comparison.json` and `rules-comparison.json`.

Byte-identical candidates exist for bearing/sqrt/trig/normal/raster tables. The
transition table and all six raw movement streams initially each had **two candidates**.
`table-candidates.json` preserves those leads. DRIVE_1006.md now records the
independently inspected Drive/Ship RTTI, caller/descriptor pointers and executed
Drive profile; its first streams and transition data are verified.

The runtime, unmigrated rendering/lifecycle oracles and prepared files still require Allied hash
`135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743`.
Do not alias addresses, accept patched tables from a duplicate match, mix prepared
source headers or promote the patched folder yet. Drive/targeting and presentation
primitive migration have separate completed checkpoints; next migrate remaining
rendering/lifecycle profiles, re-run their retained differential suites, verify
effective archive/loose-file precedence, then run native patched integration.
Milestone 20's ground traversal/eligibility follows that migration.

## Reproduce and try the retained prototype

[COMPOSITION_1006.md](COMPOSITION_1006.md) adds 424 fresh world/depth/part-order/
unit/TMP surface results per engine and both sanitizer replays after the voxel
checkpoint. Native algorithms and runtime/data gates remain unchanged; the remaining
profile/archive-precedence migration still precedes promotion.

```sh
./build.command
./test.command --data-dir "$PWD/private/game"
./run.command                         # retained verified disc inputs; no mounted disc
build/tools-env/bin/python tests/test_facing_profiles.py
build/tools-env/bin/python tools/verify_facing_mapping.py \
  --disc private/disc-allied/game.exe --patched private/official-1006-probe/game.exe
build/tools-env/bin/python tests/compare_original.py \
  --exe private/official-1006-probe/game.exe --report private/facing-1006-report.json
build/tools-env/bin/python tests/compare_original.py \
  --exe private/disc-allied/game.exe --report private/recovery-report.json
build/tools-env/bin/python tests/compare_original.py \
  --exe private/official-1006-probe/game.exe --native-vectors build/sanitize/native-vectors \
  --report private/facing-1006-sanitize-report.json
```

Unicorn commands need the established authorized Mac JIT context. Current private
reports live under `private/patch-inspection/facing-{1006,disc}*-report.json` and
`facing-official-mapping.json`. The retained build, 228 native synthetic checks,
disc/preparation tests, owned light/scenery checks and both 170-frame SDL regressions
pass. These retained native checks use disc inputs and establish integration only.
Only Apple Silicon macOS is tested; no native Windows/Linux, full-frame or complete
game fidelity claim is added. Source installations/media and Outpost 2 are untouched.
