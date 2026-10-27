# Patched executable baseline transition

Current runtime/preparation status: [PROMOTION_1006.md](PROMOTION_1006.md). The
bounded prototype now selects the supplied 1.006 dataset by default, with distinct
source-matched prepared files. Historical checkpoint gates/commands below preserve
their original evidence scope and do not describe the current runtime gate.

October 14, 2026. **Preferred targets: base RA2 1.006, then YR 1.001.**
The user supplied both patches and requested patched versions as the basis for
future recovery. The supplied base patch is now completely materialized; its engine
hash is `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`,
identical to the privately copied Windows base engine. [BASELINE_1006.md](BASELINE_1006.md)
records all outputs, virtual-host boundaries and 16,598 passing patched Facing
comparisons. [DRIVE_1006.md](DRIVE_1006.md) adds 108,475 passing Drive/curves/
timing/targeting comparisons per engine. [PRESENTATION_1006.md](PRESENTATION_1006.md)
adds 8,568 lighting/palette/depth primitive cases per engine. Remaining rendering/lifecycle profiles,
native asset/data promotion and YR materialization
remain pending. No patched native-runtime support is claimed.

The native application's intended runtime needs **no mounted disc or DRM**. It
loads user-supplied local assets; the original launcher, SafeDisc and CD checks
are outside reconstruction scope. Pristine inputs are for recovery provenance,
not a requirement to run a protected original launcher. On October 14 the user
explicitly selected existing supplied no-CD versions for Windows testing. Pin
those modified executables independently and verify relevant routines; do not
silently label their observations as pristine official-patch behavior.

## Inspected inputs

These hashes pin the user's packages. Their banners identify the advertised
targets; this inspection does not authenticate their publisher or distribution.

| Supplied file | Bytes | SHA-256 | Advertised target |
| --- | ---: | --- | --- |
| `private/patches/RA21006EN.EXE` | 2,943,038 | `9b66734863c12f7634c44ef9a401a136d897010eed10f3aafe28d5a424e48156` | RA2 1.006, banner date 06/06/2001 |
| `private/patches/YURI-1001-ENGLISH.EXE` | 2,499,822 | `49acccbec1e5264bc1538b497682a8eae0cab790b5a4d858e9812a2b10e9b104` | YR 1.001, banner date 11/15/2001 |

Both are PE32/i386 RTPatch wrappers. Embedded version **5.20 describes RTPatch**,
not the game. Both have a zero-length PE security directory. Their identical
`20530/19274/1033` resource contains a four-byte length followed by a 171,520-byte
patch-engine DLL, SHA-256
`8b8d253f39d734611644d4d0833cf5c297c63dd9acaca55d5117a8f0af8eb7a2`.
No engine code was extracted into tracked source or incorporated. The later private
virtual materialization executes the supplied DLL in research-only Unicorn; it is
not a runtime dependency. Its successful result and fixtures are recorded separately.

Payloads begin at file offset 209,408 (`0x33200`), with RTPatch signature
`4b 2a 08 02`. RA2's 2,733,630-byte overlay hashes to
`ab94ac694862f93735a54155376cc34283f5ba4b6b43fba049745b572ac7228e`;
YR's 2,290,414-byte overlay hashes to
`5775644db479da5167e28c8c8de4763013d811a68c597b1dcb2bd4f39be8f336`.
These are delta packages, not standalone replacement game executables. Overlay
strings mention game and archive files; strings alone are not a decoded patch
manifest. Assets must be inventoried before and after a successful application.

The packages contain Westwood `InstallPath` registry lookup strings for their
respective games. The wrapper imports no registry functions directly; its embedded
engine imports registry read/write and process APIs. Merely copying an installer
or changing its working directory does not establish copy-only targeting or
absence of registry effects. Verify both before applying it; never target the
user's source installation. The engine's embedded usage mentions explicit update
directory/patch-file arguments and file-operation callback setters. These are
static research leads, not a validated safe invocation.

Reproduce read-only inspection with the existing research environment:

```sh
build/tools-env/bin/python tools/inspect_patch.py private/patches/RA21006EN.EXE
build/tools-env/bin/python tools/inspect_patch.py private/patches/YURI-1001-ENGLISH.EXE
PYTHONPYCACHEPREFIX=build/pycache build/tools-env/bin/python tests/test_patch_inspection.py
# Fresh output names only; reports must stay under private/ or build/:
build/tools-env/bin/python tools/inspect_patch.py private/patches/RA21006EN.EXE \
  --output private/patch-inspection/ra2-1006.json
```

Both owned packages passed the complete inspector. Three synthetic regression
tests verify unknown/tampered-hash rejection before PE parsing, source/public
output refusal, overwrite preservation and symlink refusal. Local JSON reports
are `private/patch-inspection/ra2-1006.json` and `yr-1001.json`.

## Migration procedure and acceptance

1. Inventory `D:\Games\RA2` read-only using [WINDOWS_TESTING.md](WINDOWS_TESTING.md).
   Establish installed provenance, executable versions/hashes and any existing
   third-party modifications. An already-patched installation may make patch
   application unnecessary; its version label alone does not select an address table.
   The user believes official and no-CD patches are both present. Prefer clean
   official-patch output from untouched legitimate media inputs; treat installed
   executables and backups as modification candidates until compared. Do not
   reapply deltas blindly to modified inputs or obtain replacement game downloads.
2. Preserve the installation and create a fresh, complete research copy outside it,
   without symlinks/junctions. Inventory that copy. Apply the supplied RA2 package
   only after its explicit destination and registry behavior are established. If
   needed, use an isolated Windows research environment with copy-only installation
   records; do not redirect the host's source-install registry. Keep logs and compare
   source hashes afterward. The successful Mac route instead uses an entirely
   in-memory filesystem/registry, including the observed Version stores and the
   unchanged DLL's final exception handler; it exposes no host Windows APIs.
3. Record success, changed asset hashes, resulting `game.exe` SHA-256, bytes, PE
   layout and embedded version. Record `gamemd.exe` independently when YR work begins.
   Keep resulting files and reports in ignored private storage. Do not infer a
   resulting executable hash from the installer, a header, or upstream Steam/EA builds.
4. Consult pinned [REFERENCES.md](REFERENCES.md) binary-discovery/testing leads.
   Recover patched routine/table addresses and changed object layouts locally.
   Add explicit hash-selected profiles only for verified mappings. Unknown hashes
   must keep failing closed; do not disable existing gates or alias disc addresses.
5. Reverify migrated subsystems against unchanged patched original instructions,
   retaining ordered writes, caller/arena/stack checks and all numeric boundaries.
   Label unchanged-byte/table evidence separately from new differential results.
   Preserve the disc suite and its historical evidence, keyed to its own hash.
6. Add verified patch-archive precedence and compare effective map/rules/art inputs
   before promoting the patched data folder. Keep prepared tables and runtime
   fingerprints consistent with its executable profile. Promotion requires native
   integration regressions as well as the new original-routine evidence.

The preferred base target hash is established above; **Facing, bounded Drive/curves/
timing/targeting and presentation primitives have migrated executed profiles**.
Remaining rendering/lifecycle and native data promotion are pending. No new disc-address subsystem recovery should proceed
as a substitute for completing the remaining patched migration.
Baseline materialization does not require a runnable game UI; integration observations
do. Keep Windows launch troubleshooting separate from binary migration acceptance.
The earlier authorized backup-launcher tests used Allied media at F:, whose
engine/launcher/cabinet hashes match our Mac imports. The stock launcher reached
"Access Denied"; a subsequently user-authorized admin retry exited 1 with matching
Secdrv driver-block events. Protected-launcher testing is now superseded by the
user's no-CD direction. Clean inputs were separately prepared from that media.
[WINDOWS_TESTING.md](WINDOWS_TESTING.md) records paths, hashes and the exact tested
launcher/engine pair. The supplied delta has now succeeded in private virtual
materialization, with no host registry/installation changes. Keep launcher/startup
evidence separate from pristine patched engine provenance. No mounted media is
needed for static analysis or isolated original-routine tests.

## Retained evidence and current runtime

Bounded research profiles through ordinary occupation/lifecycle now have independent
disc/1.006 execution evidence; [TERRAIN_LIFECYCLE_1006.md](TERRAIN_LIFECYCLE_1006.md)
records the latest grouped checkpoint. The remaining transition is original archive
precedence and consistent prepared/runtime inputs, followed by applicable full and
real SDL verification on promoted data. Historical transition text above retains
its checkpoint scope; it does not imply that the runtime gate has been promoted.

Milestones 1–19 remain specific to Allied-disc `game.exe`, embedded version `1.08`,
SHA-256 `135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743`.
Their evidence is neither invalidated nor silently reassigned by this preference.
The existing app and unmigrated rendering/lifecycle oracles still use that build;
the separately verified primitive suite has an explicit patched research profile.
Patch/expansion archive merging remains unimplemented. `./build.command`, `./run.command` and the README
disc-build regressions remain usable. No new gameplay behavior was added.

The native app never executes original code. Its executable-read boundary remains
hash-checked track data only. The patch inspector and private virtual materialization
are private research tooling, not application dependencies. No Wine/Rosetta runtime,
game-content downloads, original-code incorporation, source-install changes or
Windows-native build support was introduced.
