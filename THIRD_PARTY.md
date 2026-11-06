# Source and dependency provenance

Authored project tools and the preserved native reconstruction use the repository
GPL-3.0-or-later license; retain LICENSE and all dependency notices. Canonical
recovered C/C++ in root `src/` is reconstructed from the supplied original target.
This migration makes no new grant of rights in the original game or compiler,
and authorizes no publication. Original executables/assets, instruction-byte
scaffolding, disassembly and proprietary tools remain ignored private inputs.

The historical native provenance record below is preserved byte-for-byte in
[historical/native-reconstruction/THIRD_PARTY.md](historical/native-reconstruction/THIRD_PARTY.md),
where its relative paths resolve against the native project. OpenRA format-reader
adaptations remain in that project, with their notices and LICENSE. They do not
implement the active original-target build. Capstone and pefile are active local
inspection tools; VC6 and CrossOver are legitimate user-supplied local build tools.

## Public references inspected

- **OpenRA**, commit `e7e9e4ad270221d7fb9725b348c75504d48c1ebd`:
  https://github.com/OpenRA/OpenRA/tree/e7e9e4ad270221d7fb9725b348c75504d48c1ebd
  GPL-3.0-or-later, Copyright The OpenRA Developers and Contributors.
  `MixFile.cs`, `PackageEntry.cs`, `BlowfishKeyProvider.cs`, `VxlReader.cs`,
  `HvaReader.cs`, `TmpTSLoader.cs`, `LCWCompression.cs`, `ImportGen2MapCommand.cs`
  informed the new bounded C++ readers and format interpretation. `Voxel.cs`
  informed HVA translation scaling and axis interpretation. Treat these portions
  as GPL-covered adaptations; preserve this attribution and LICENSE. No OpenRA
  simulation or mod is linked. Its rendering/movement behavior is not an oracle.
  Milestone 15 additionally used `OpenRA.Mods.Common/SpriteLoaders/ShpTSLoader.cs`
  and `OpenRA.Mods.Common/FileFormats/RLEZerosCompression.cs` for the bounded
  format-3 SHP reader in `src/assets/Shp.cpp/.hpp`, under the same GPL attribution.
  Milestone 17 extends that adaptation to the same source's raw format-1 branch.
  Exact cropped sizes are retained; no OpenRA export padding or renderer is used.
  The public MIX RSA modulus is format metadata, not a private cryptographic key.
- **Phobos-developers/YRpp**, commit
  `b22f1860dd7b100cad57123d4ca5d459b9020d88`:
  https://github.com/Phobos-developers/YRpp/tree/b22f1860dd7b100cad57123d4ca5d459b9020d88
  No license file was found in this snapshot. No headers or code were incorporated.
  `Facing.h`/`Dir.h`, locomotion declarations and Unit/Foot/Techno declarations
  supplied search vocabulary and structure hypotheses only.
  Milestone 5 additionally inspected Drawing/Convert/ColorScheme/IsometricTile
  declarations for naming and type hypotheses. Their headers/implementations were
  not incorporated; lighting, palette and depth primitives were located and
  verified independently in the fingerprinted base binary.
  Milestone 6 used VXL.h only as a runtime-layout lead; the base VXL loader and
  raster routines verified that layout. No YR headers or implementation were copied.
  Milestone 7 additionally inspected Tactical/Surface/BlitterFlags names and
  declarations as leads. Projection, depth, clipping and alpha behavior came from
  the pinned base routines; no reference implementation was incorporated.
  All implemented facing behavior was re-established from the base RA2 executable;
  a material division-order difference was found. No YR addresses are used.
  Milestone 8 used ColorScheme/Techno/TechnoType/UnitType declarations for shadow
  and palette naming leads only; the base binary and isolated oracles establish
  implemented behavior. No headers or implementation were incorporated.
- **Outpost 2 native**, user's sibling checkout: read-only design reference, not a
  code/library dependency. No source from it was copied into this project.
- **sp00nznet/redalert2-recomp**, commit
  `eebcf725ef99f942a8f9a5e0437a8a6154d7d439`:
  https://github.com/sp00nznet/redalert2-recomp/tree/eebcf725ef99f942a8f9a5e0437a8a6154d7d439
  MIT for its own work, Copyright (c) 2026 sp00nz; generated lifted game code is
  explicitly excluded. LICENSE's explanatory scope text retains stale references
  to The Movies; README identifies RA2/YR. Build/runtime, analysis, voxel and test
  sources were inspected as leads. No code was incorporated or builds/tests run.
  Its Steam/EA RA2 1.006 and YR 1.001 addresses are not our disc build's addresses.
  Milestone 8 consulted `docs/voxels.md`, `src/runtime/hdvox.c` and `run_lift.py`
  for shadow/render call-chain hypotheses. Stock behavior was independently
  recovered from our disc executable; no HD/remaster or generated code was reused.
- **sp00nznet/pcrecomp**, commit
  `8f4aa77aaf9e70f486a0fbc6b39a7ee14ae4fda1`:
  https://github.com/sp00nznet/pcrecomp/tree/8f4aa77aaf9e70f486a0fbc6b39a7ee14ae4fda1
  MIT for its authored tools/runtime, Copyright (c) 2026 sp00nz; its grant does not
  cover the input game or generated lifted code. License, tool inventory and
  32-bit Win32/SDL runtime sources were inspected. No code was incorporated,
  tooling installed or builds/tests run. Neither reference is a new dependency.
  See [docs/REFERENCES.md](historical/native-reconstruction/docs/REFERENCES.md) for the use and verification procedure.

- **Electronic Arts Westwood source releases** (read-only shape references,
  see [docs/WESTWOOD_SOURCES.md](docs/WESTWOOD_SOURCES.md)):
  `electronicarts/CnC_Red_Alert` commit `0dc09bb1d6188d1ec79ab4765b22a48b75ffee32`,
  `electronicarts/CnC_Renegade` commit `3e00c3a1b97381bb28be89a35b856375e0629a08`,
  `electronicarts/CnC_Tiberian_Dawn` commit `e0d372dc582c053a699114942b984dad0457f9b3`.
  GPL-3.0 with EA's additional terms (section 7 of each LICENSE.md: no EA trademarks,
  modified versions marked, notice retained), Copyright Electronic Arts Inc. Cloned
  under the ignored `private/reference/`. No header, implementation or data was
  incorporated; they supply naming, member-order and idiom hypotheses that are
  verified on the base executable like every other reference.

- **TibSun reconstruction** (`OpenTS-Developers/TibSun` commit `dbfbfbfaac40364ce7e1cd8fad7bcade5c6fb0d4`,
  `code/` only; read-only shape reference, see [docs/WESTWOOD_SOURCES.md](docs/WESTWOOD_SOURCES.md)): a community
  source reconstruction of Tiberian Sun GAME.EXE 2.03, not Westwood text. GPL-3.0-or-later plus EA's section 7 terms
  for the parts derived from the Red Alert release. Cloned under the ignored `private/reference/TibSun`. Since 2026-11-06 (user decision) its text may be adopted into
  `src/` as candidates, adapted to our shared headers; an adopted file keeps the source's SPDX and copyright lines
  (including the EA line where present) and the commit subject says "from TibSun <file>". Acceptance is unchanged.

- **ra2-decomp** (`gibbo101/ra2-decomp` commit `ca9b8ad80205255e483496ec3c85ab4886589a48`, 2026-11-06; first pinned at 4453ab030): a matching
  decompilation of Yuri's Revenge gamemd.exe 1.001 built with the same VC6 SP3. Game source in `src/` and `include/`
  GPL-3.0-or-later, Copyright 2026 ra2-decomp contributors, with Electronic Arts' section 7 terms on files carrying an
  EA copyright line (COPYING.md); tooling and data MIT. The maintainer gave the user explicit permission to reuse it.
  Cloned read-only under the ignored `private/reference/ra2-decomp`. Since 2026-11-06 (user decision) functions whose
  RA2 body matches a YR twin may be adopted into `src/` adapted to our headers (their names follow YRpp and must be
  mapped to ours); an adopted file keeps their SPDX and copyright lines and the commit subject says
  "from ra2-decomp <YR address>". Acceptance is unchanged: strict audit and exact whole-file build.

## Native linked libraries (tested development versions)

| Library | Version | License | Use |
| --- | --- | --- | --- |
| SDL3 | 3.4.2 | zlib | Window, input, texture upload, debug text |
| OpenSSL | 3.6.1 | Apache-2.0 | MIX RSA/Blowfish decoding and original-data SHA-256 |
| LZO | 2.10 | GPL-2.0-or-later | Safe LZO1X map decompression; compatible GPLv3 distribution |
| zlib | SDK 1.2.12 interface | zlib | MIX CRC-32 filename IDs |

Licenses were inspected from the installed Homebrew packages (SDL3 LICENSE.txt,
OpenSSL LICENSE.txt, LZO share/doc/lzo/COPYING) and public OpenRA COPYING. These
libraries are discovered by CMake, not copied into Git. The Blowfish API is the
legacy OpenSSL block API because MIX requires that historical cipher; this is
archive interoperability, not a choice of cipher for new security functionality.

## Local tooling only

CMake 4.4.4 (BSD-3-Clause), Unicorn 2.1.4 (GPL-2.0, plus dependency notices),
Capstone 5.0.9 (BSD), pefile 2024.8.26 (MIT) and macOS bsdtar/libarchive (BSD)
are build/import/research tools, not linked into the application. Python and its
virtual environment remain local. The temporary research probe used PyCryptodome
3.24.0; it is not required by the checked-in workflow or native reader.

No game content was downloaded. Network downloads comprise public references,
Python build/test packages and the separately recorded Windows research-host
cnc-ddraw release below. Nothing has been published externally.

Milestone 9 also consulted that pinned redalert2-recomp snapshot's `docs/voxels.md`,
`docs/testing.md` and `run_lift.py` for indexed staging and cache dispatch leads.
Its MIT license and generated-game-code exclusion were rechecked. No code was
incorporated. The readable C++ and differential fixtures were authored here from
our independently inspected hash-pinned executable; see [STAGING.md](historical/native-reconstruction/docs/STAGING.md).

Milestone 10 consulted the same snapshot's `docs/voxels.md`, `src/runtime/hdvox.c`
header and `docs/testing.md` for the final light-input boundary. No verified map-light
formula/source creation lead was available there. Ordinary light arithmetic and
alpha initialization were independently recovered and tested against our base
binary. The license/generated-code boundary was rechecked; no code was incorporated.
See [MAP_LIGHTING.md](historical/native-reconstruction/docs/MAP_LIGHTING.md).
Milestone 11 consulted the same redalert2-recomp commit's LICENSE, `docs/voxels.md`
and `src/runtime/hdvox.c` header. YRpp at the previously pinned
`b22f1860dd7b100cad57123d4ca5d459b9020d88` supplied naming/layout leads from
`LightSourceClass.h`, `GameOptionsClass.h`, `BuildingClass.h`, `BuildingTypeClass.h`.
The existing license/no-incorporation boundaries apply: no upstream authored or
generated code was reused, and no YR behavior was assumed to be base behavior.
Source operations and terrain decisions were independently recovered against
our hash-pinned disc executable; see [STATIC_LIGHT.md](historical/native-reconstruction/docs/STATIC_LIGHT.md).

Milestones 13/14 consulted the same pinned redalert2-recomp `docs/voxels.md`
and LICENSE for lit/shadow cache leads. YRpp supplied type/key/interface naming
from Techno/Foot/ObjectType/Locomotion/Drawing/GeneralDefinitions declarations.
No upstream authored/generated or unlicensed header code was incorporated; exact
base-binary oracles established implemented behavior. See
[VOXEL_CACHE.md](historical/native-reconstruction/docs/VOXEL_CACHE.md) and [SHADOW_KEYS.md](historical/native-reconstruction/docs/SHADOW_KEYS.md).

Milestone 15 consulted pinned YRpp `TerrainClass.h`, `TerrainTypeClass.h`,
`ObjectClass.h`, `ObjectTypeClass.h`, `FileFormats/SHP.h` and `Surface.h` for naming,
layout and signature leads only. No unlicensed header or generated game code was
incorporated. Drawing operations were independently recovered and verified against
the exact base binary; the separately attributed OpenRA format adaptation is listed
above. See [SCENERY.md](historical/native-reconstruction/docs/SCENERY.md).

Milestone 16 revisited those pinned OpenRA ShpTSLoader/COPYING and YRpp
TerrainTypeClass leads. No additional upstream code was incorporated. Terrain
strength/image decisions and all supplied ordinary tree draws were independently
verified against the exact base binary; see [TREE_TYPES.md](historical/native-reconstruction/docs/TREE_TYPES.md).

Milestone 17 revisited those pinned OpenRA format/license and YRpp TerrainClass/
TerrainTypeClass leads. Only the separately attributed GPL SHP format adaptation
was extended. Original raw/compressed drawing operations and all ordinary prop
images were independently verified against the exact base binary; see
[PROPS.md](historical/native-reconstruction/docs/PROPS.md). No unlicensed header, generated output or original game
code was incorporated.

Milestone 18 consulted the same pinned YRpp Object/ObjectType/TerrainType/Cell
declarations for occupation, foundation and Mark vocabulary. No header, upstream
generated output or original code was incorporated. Readable C++ and scoped
original-routine tests were authored here; [OCCUPATION.md](historical/native-reconstruction/docs/OCCUPATION.md)
records the exact-base verification and host boundaries. No new dependency added.

Milestone 19 consulted the same pinned YRpp Object/ObjectType/Terrain/Display
declarations for lifecycle/layer hypotheses. Exact-base routines independently
establish the readable C++ operations and differential evidence in
[LIFECYCLE.md](historical/native-reconstruction/docs/LIFECYCLE.md). No header code, generated output or original
game code was incorporated; no new dependency was added.

October 14 patched-baseline preparation inspects user-supplied RTPatch packages
as private inputs only. Pocket Soft's embedded engine and EA's deltas remain
proprietary research material; no code was incorporated or redistributed. The
inspector uses the existing research-only pefile dependency. The successful private
virtual materialization executes that supplied DLL in research-only Unicorn; no
proprietary engine code, resources or disassembly are tracked or redistributed.
[BASELINE_1006.md](historical/native-reconstruction/docs/BASELINE_1006.md) records exact inputs/output and fixture
boundaries. Authored Facing mapping/test code uses the existing pefile/Capstone/
Unicorn tooling; no upstream code was copied or runtime dependency added.
[DRIVE_1006.md](historical/native-reconstruction/docs/DRIVE_1006.md) extends those authored research tools to bounded
Drive/curves/timing/targeting profiles. Pinned testing/interface references supply
hypotheses only; no upstream, YRpp header or generated game code was incorporated.

**FunkyFr3sh/cnc-ddraw v7.1.0.0**, MIT license, is used only in a private Windows
original-game observation copy, not linked or bundled with the native game.
https://github.com/FunkyFr3sh/cnc-ddraw/releases/tag/v7.1.0.0
The Windows task downloaded the release archive, preserved its license and tested
base menu/minimize/restore presentation; output is altered host presentation, not
an original pixel oracle. [WINDOWS_TESTING.md](historical/native-reconstruction/docs/WINDOWS_TESTING.md) records
archive/DLL hashes, configuration and private provenance. No code was incorporated.
