# Reference and license policy

The exact hash-checked supplied base executable decides original-target recovery;
see [RECOVERY.md](RECOVERY.md). Whole-program decompiler output, public recomp,
YRpp, replacement engines and old native notes provide hypotheses and navigation.
Verify any adopted interpretation against this target. YR addresses/layouts and
another RA2 build's labels are not interchangeable with the supplied base.

Before incorporating authored third-party code, inspect its actual file/license,
record the pinned revision and keep required notices in `THIRD_PARTY.md`.
Do not copy unlicensed headers or assume a tool/repository license covers
original/lifted/generated game code, original data or proprietary toolchains.
The retained reference record reported no YRpp license file; naming leads are
not authorization to incorporate its authored header code.

The user-approved layout tracks canonical accepted recovered C/C++ under root
`src/`. Explicit original assembly/byte scaffolding, original data, proprietary
toolchains and experimental candidates remain ignored private research inputs.
This supersedes older blanket exclusions of canonical recovered source;
it does not authorize publication or adopting an upstream lifted runtime as the
final native engine. No OpenRA gameplay or general Win32/CPU compatibility runtime.

Source media/installations and sibling projects stay read-only. Use legitimate
user-supplied compiler/game files and existing local tools. Routine continuation
authorizes no downloads, Windows actions, license acceptance, system/global tool
changes or publication. Extracted media contents, byte scaffolding, experimental recovery artifacts and
build outputs stay ignored under `private/` or `build/`. Do not run upstream installers/setup
against the user's source installation.

Pinned historical reference/license observations and previous native evidence are
preserved exactly in [REFERENCES_NATIVE_20261020.md](../historical/native-reconstruction/docs/REFERENCES_NATIVE_20261020.md).
Those observations may be stale: inspect the exact pinned license before reuse;
their former workflow, platform claims and next-step directives are not active
recovery instructions. Current architecture/phase authority is
[ORIGINAL_TARGET_PROCESS.md](ORIGINAL_TARGET_PROCESS.md).

The published Westwood sources (Electronic Arts' GPL releases of Red Alert,
Tiberian Dawn and Renegade) are the closest public relatives of RA2's code and
are cloned read-only under `private/reference/`: see
[WESTWOOD_SOURCES.md](WESTWOOD_SOURCES.md) for the pinned revisions, the
licence terms and a recovered-header to reference-file lookup table. They are
shape references under the same rule as everything else here: hypotheses only,
verified on the exact target, nothing copied.

The Yuri's Revenge matching decompilation at
[github.com/gibbo101/ra2-decomp](https://github.com/gibbo101/ra2-decomp)
(gamemd.exe 1.001, same VC6 SP3; source GPL-3.0-or-later with EA section 7
terms, tools MIT) has matched many functions whose RA2 body is byte-identical
apart from relocations. Since the user's decision of 2026-11-06 its source, and the TibSun archive's,
may be adopted into `src/` with attribution (see `THIRD_PARTY.md`); acceptance
is unchanged. Cloned read-only at `private/reference/ra2-decomp`. The owner
keeps the twin map in the ignored `build/ra2decomp/twins.json`.
