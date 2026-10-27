# RA2 1.006 ordinary map-light and visible-alpha migration

October 14, 2026. Ivalice / Apple Silicon macOS. This extends indexed staging
checkpoint `ac6adab`. [BASELINE_1006.md](BASELINE_1006.md) records supplied-patch
lineage and the completed private Windows transfer; neither was repeated here.

**17,510 fresh original/native results pass on each engine.** Both native
ASan/UBSan replays pass. Native algorithms are unchanged. Runtime and prepared-data
gates remain disc-only pending the remaining profile and archive-precedence
migration. This verifies the retained [MAP_LIGHTING.md](MAP_LIGHTING.md) domain;
milestone 19 remains the gameplay checkpoint. Full actor, source/house/visibility
association, converter lifetime and whole-frame parity remain outside this claim.

## Exact identities and reference hypothesis

| Research profile | Executable SHA-256 |
| --- | --- |
| Allied disc | `135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743` |
| Supplied RA2 1.006 patch output | `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f` |

Inputs are `private/disc-allied/game.exe` and
`private/official-1006-probe/game.exe`. The latter remains byte-identical to the
approved Windows copy at `private/windows-baseline-20261014/game.exe`. Both embed
1.08; complete hashes select profiles. Supplied-patch lineage does not authenticate
the publisher or establish pristine status of the entire installation reported
to contain no-CD modifications. No Windows gameplay/frame observation was added.

Consulted [REFERENCES.md](REFERENCES.md)'s final lighting and isolated-test leads:
redalert2-recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439`, `docs/voxels.md`
(Following the image onto the battlefield, Units flashed), `docs/testing.md` and
LICENSE. Hypothesis: independently locate the ordinary numeric inputs and actual
alpha constructor on our patched engine, then execute the retained domain. The
reference supplies no verified map-light formula. Its YR/HD addresses, changes
and replacement host behavior are leads only. Its MIT scope excludes generated
game code; no upstream, unlicensed header or generated/lifted code was incorporated.

## Inspected mappings and constructor selection

`tools/verify_map_light_mapping.py` checks **13 instruction ranges / 1,064
instructions**, four consumed constants and actual BSurface RTTI/slots. Changed
operands have explicit mappings, internal branches retain relative targets and
remaining instruction bytes agree. No opcode difference was found in these
ranges. This is inspection evidence, not parity for unexecuted branches/services.

| Boundary | Disc VA | Supplied 1.006 VA |
| --- | --- | --- |
| Complete ordinary cell calculation | `0x479040` | `0x479440` |
| Complete tint normalization | `0x536450` | `0x5383C0` |
| Multiply-by-100 numeric block | `0x659071..0x65907C` | `0x662211..0x66221C` |
| Multiply-by-1000 numeric block | `0x659160..0x65916B` | `0x662300..0x66230B` |
| Ordinary / alternate selectors | `0x51F040`, `0x51F050` | `0x51FC50`, `0x51FC60` |
| Complete visible-alpha constructor | `0x410A60` | `0x410A60` |
| Buffer constructor | `0x438140` | `0x4382C0` |
| Surface-fill wrapper / complete fill | `0x75F930`, `0x75F960` | `0x774390`, `0x7743C0` |
| Actual constructor call and alpha-global store | `0x498A87..0x498A91` | `0x498DF7..0x498E01` |
| BSurface vtable | `0x785EF8` | `0x79AEF8` |

Range ends are exclusive. Two similar patched constructors were discovered at
`0x410A60` and `0x775B80`. The actual caller and alpha-global store establish
**0x410A60**; prefix similarity does not select the other copy. BSurface slot 5
selects the surface-fill wrapper, with lock/unlock/bpp/stride/bounds slots checked
against explicit metadata. No general displacement is assumed.

`tests/map_light_profiles.py` adds 28 explicit mappings to inherited staging
metadata. `MapLightOracle` and its local surface fixture require explicit patched
opt-in. Static/unit light and other descendants retain their disc defaults.
Inherited mapping verifiers run independently for patched research. Accepting
these addresses does not promote another subsystem or the native runtime.

## Executed boundary and audit limits

| Passing results per engine | Count |
| --- | ---: |
| Complete visible-alpha constructor buffers | 8 |
| Actual numeric conversion blocks and decimal neighbors | 1,544 |
| Complete normalization, ties/clamps/dark cutoff | 1,509 |
| Complete ordinary cell/source calculations | 838 |
| Every supplied map cell's numeric outputs | 13,515 |
| Complete combined lit color/depth surfaces | 96 |
| **Total** | **17,510** |

The actual numeric blocks consume supplied binary64 values; original INI parsing
does not execute. Complete normalization/cell routines execute unchanged original
instructions. Sources, scenario/cell records and inactive selector globals are
explicit inputs; one flat coordinate/height getter is supplied. Native map decoding
provides fixture coordinates, not original map construction. Complete alpha
construction uses successful guarded allocations and original fill/lock routines.
Combined cases run scalar palette updates and complete final surface copies with
supplied palette, source, placement, visibility and depth planes. See MAP_LIGHTING.md
for numeric bounds, source gates and retained fixture services.

Per engine, **16,354 callable roots**, **18,541 isolated blocks**, **17 guarded
allocations** and **1,768 supplied getter calls** are recorded, including setup/
inherited calls. Calls check return/caller stack, ESP, callee-saved registers,
immutable inputs and permitted writes. Numeric blocks preserve input/return/caller
bytes, permit lower-stack scratch only and check stop EIP/ESP. Cell calls preserve
cell/scenario/source-array/source records and selector globals while permitting
declared outputs/stack. Alpha allocations retain canaries and restore surface locks.
These are bounded original-fixture audits, **not ordered native/original writes,
full actor arenas, original heap ownership or lifetime/frame parity**.

Recovered rounding, float32 stores, table square root, per-source truncation,
dominant-channel ties/asymmetric normalization denominators, low-32-bit scaling
products and fully visible alpha 127 retain their meaning. Supplied map settings
remain `(100,100,100,86,0,28)` after quantization; spawn terrain brightness is 1112.
No native arithmetic or runtime algorithm changed.

## Evidence, reproduction and remaining work

Fresh protected exports, expectations and receipts remain ignored under:

```text
private/migration/allied-disc/map-light/
private/migration/supplied-ra2-1006/map-light/
```

Fresh execution refuses existing expectations/receipts. Replay pins exact engine/
profile, oracle/mapping sources, exporter, assets, render data and expectation
fingerprint; it cannot replace fresh evidence. Ten synthetic profile/evidence
guards pass. Historical disc evidence is preserved. Native map-light vectors consume
render data only, retaining disc file hash
`50d2876e6bf8a3b9d535a1843ef93f41109b7021a15e1dbacb47aaa881389c6d`.
Patched research requires explicit `--native-data-exe` disc identity. Owned map,
rules and palettes remain retained disc inputs; archive precedence is not promoted.

```sh
./build.command
./test.command --data-dir "$PWD/private/game"
build/tools-env/bin/python tests/test_map_light_profiles.py
build/tools-env/bin/python tools/verify_map_light_mapping.py \
  --disc private/disc-allied/game.exe --patched private/official-1006-probe/game.exe
# Fresh evidence already exists here; replay without original execution:
build/tools-env/bin/python tests/compare_map_light.py \
  --exe private/official-1006-probe/game.exe \
  --native-data-exe private/disc-allied/game.exe \
  --expectations private/migration/supplied-ra2-1006/map-light/expected.json
# For instrumented replay after README's sanitizer build, add:
# --native build/sanitize/map-light-vectors
# --report private/migration/supplied-ra2-1006/map-light/sanitize-report.json
./run.command --light-demo
```

On a checkout without receipts, omit `--expectations` for fresh original execution
in the authorized Mac Unicorn JIT context. Both sanitizer replays pass without
diagnostics. Current receipt/source/input/native hashes, cross-engine outputs and
affected native/sanitizer disc regressions pass
`private/patch-inspection/verify-map-light-checkpoint.py`; its receipt is
`private/migration/map-light-checkpoint-verification.json`. Mapping evidence is
`private/patch-inspection/map-light-1006-mapping.json`; discovery/disassembly/probes
remain private. No original instruction bytes were patched or copied into source.

Fresh affected **disc** regressions pass in
`private/migration/disc-map-light-regressions/`: **2,574 static-light** and
**3,257 unit-light** results, plus both native ASan/UBSan expectation replays.
An initial replay used a relative engine path from this workspace and failed
before execution; the corrected absolute path passed. Historical reports remain
unchanged. Build, native/sanitizer synthetic checks, import/preparation guards,
owned-data checks and both 170-frame SDL regressions pass.

Native integration is not original input/timing/frame parity. Only Apple Silicon
macOS support is tested. Source installations/media, Outpost 2, Windows task and
system configuration are untouched. Next migrate static/unit light, cache, scenery,
occupation/lifecycle, then archive precedence and prepared inputs before runtime
promotion and milestone 20. Visibility, scheduling, actor/house/cache lifetime,
controls/routing/clearance and whole-frame parity remain adapters or open.
