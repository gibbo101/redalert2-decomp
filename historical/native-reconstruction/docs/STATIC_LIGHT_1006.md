# RA2 1.006 static-source and terrain-converter migration

October 14, 2026. Ivalice / Apple Silicon macOS. This extends ordinary map-light
checkpoint `8c82d86`. [BASELINE_1006.md](BASELINE_1006.md) records supplied-patch
lineage and the completed private Windows transfer; neither was repeated here.

**2,574 fresh original/native results pass on each engine.** Both ASan/UBSan
native replays pass. All outputs also equal the retained disc suite's outputs.
Native algorithms are unchanged. Runtime and prepared-data gates remain disc-only
pending the remaining profile and archive-precedence migration. This verifies
the retained [STATIC_LIGHT.md](STATIC_LIGHT.md) domain; milestone 19 remains the
gameplay checkpoint. Deferred updates, whole building/house lifecycle, original
converter ownership/redraw implementation and full-frame parity remain open.

## Identity and reference hypothesis

| Research profile | Executable SHA-256 |
| --- | --- |
| Allied disc | `135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743` |
| Supplied RA2 1.006 patch output | `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f` |

Inputs are `private/disc-allied/game.exe` and
`private/official-1006-probe/game.exe`. The latter remains byte-identical to the
approved copy at `private/windows-baseline-20261014/game.exe`. Both embed 1.08;
complete hashes select profiles. Supplied-patch lineage does not authenticate the
publisher or certify the entire installation reported to contain no-CD changes.
No Windows gameplay/frame observation was added.

Consulted [REFERENCES.md](REFERENCES.md), redalert2-recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439`, `docs/voxels.md` (Following the image
onto the battlefield, Units flashed), `docs/testing.md` and LICENSE; YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88`, `LightSourceClass.h`,
`GameOptionsClass.h`, `BuildingClass.h` and `BuildingTypeClass.h` for source/detail/
foundation vocabulary. Hypothesis: independently map actual source operations,
cell installation and building coordinate dispatch, then execute the retained
immediate domain. The recomp supplies no verified static-source formula; YR fields
and addresses are leads only. MIT excludes generated game code, and this YRpp
snapshot lacks an incorporation license. No upstream/header/generated code was reused.

## Inspected mappings

`tools/verify_static_light_mapping.py` checks **15 instruction ranges / 851
instructions**, two numeric constants, the supplied 1×1 width/height entries and
actual Building/LightSource RTTI metadata. Changed operands have explicit mappings;
internal branches retain relative targets and remaining instruction bytes agree.
No opcode difference was found in these ranges. This is inspection evidence,
not parity for unexecuted branches or external services.

| Boundary | Disc VA | Supplied 1.006 VA |
| --- | --- | --- |
| Actual type numeric block | `0x45A1D0..0x45A1E1` | `0x45A55E..0x45A56F` |
| Complete source constructor | `0x5352D0` | `0x537240` |
| Complete activate / deactivate | `0x5355D0`, `0x5355F0` | `0x537540`, `0x537560` |
| Complete update, including immediate cell-installation tail | `0x535660..0x5358BD` | `0x5375D0..0x53782D` |
| Complete cell numeric installation | `0x478CF0..0x479034` | `0x4790F0..0x479434` |
| Complete ordinary terrain converter factory | `0x5276A0` | `0x529590` |
| Complete clamp/detail-mask helper | `0x536630` | `0x5385A0` |
| Building source creation/activation block | `0x442B3F..0x442BD6` | `0x442DD3..0x442E6A` |
| Actual building coordinate getter | `0x443E10` | `0x444080` |
| Foundation width / height helpers | `0x4585B0`, `0x4585C0` | `0x458930`, `0x458940` |
| Actual map lookup / membership | `0x5453B0`, `0x5453F0` | `0x548070`, `0x5480B0` |
| Building / LightSource main vtables | `0x787BBC`, `0x790548` | `0x79CBBC`, `0x7A5560` |

Range ends are exclusive. The update's immediate-mode tail follows an earlier
return and jumps back into traversal; it is included in the complete inspected
range. Building slot 18 (+0x48) selects the actual coordinate getter in each engine.
Both foundation index-0 entries are 1. The unchanged base constructor is inspected
and executes inside source construction. No general address displacement is used.

`tests/static_light_profiles.py` adds **57 explicit mappings** to inherited
map-light metadata. Static research requires explicit patched opt-in; unit/cache/
scenery and other oracles keep their disc defaults. Patched commands run inherited
mapping verifiers too. Deferred-update and full LightConvert addresses encountered
in operands remain metadata/services, not executed implementation parity.

## Executed domain and audits

| Passing results per engine | Count |
| --- | ---: |
| Actual type numeric blocks and decimal neighbors | 779 |
| Complete ordinary terrain converter decisions | 1,524 |
| Complete source constructors | 128 |
| Complete immediate activation/deactivation updates | 128 |
| Supplied stock INGALITE values | 1 |
| Building creation/activation blocks at detail 0/1/2 | 3 |
| Zero-intensity building skips at detail 0/1/2 | 3 |
| Complete owned-map activate/deactivate/no-op | 3 |
| Numeric repeatability after source calls | 5 |
| **Total** | **2,574** |

Unchanged original instructions execute source construction/registration, active
guards, mode-0 traversal, actual membership/lookups, square root, cell calculation
and numeric installation. Building tests execute the actual coordinate/dimension
getters. Factory tests execute clamp/mask, lookup/shade decisions and registration
with a supplied neutral pool, successful allocator and constructor recorder.
Cell installation uses a null converter service; redraw is record-only. Numeric
tests supply doubles rather than original INI parsing. STATIC_LIGHT.md retains
the detailed domain and services; no complete building initialization is claimed.

Per engine, **1,914 callable roots**, **6,298 isolated blocks**, **1,524 supplied
allocation calls** and **2,856 flat coordinate/height getter calls** are recorded.
Callable audits check return/caller stack, ESP, callee-saved registers, immutable
inputs and permitted writes. Numeric blocks preserve double/return/caller bytes
and allow lower-stack scratch only. Update stores are limited to the active byte,
cell converter pointer and numeric lighting fields; scenario, source metadata,
map pointer table and selector/detail globals remain unchanged. Factory permits
only its registry count/slot and stack stores, preserving the neutral entry.
The building block preserves its input/type records outside the declared source
pointer, restores ESP and checks a caller guard. Its supplied actor/type arenas
were moved away from an overlap with the map-pointer table before fresh execution.
No runtime algorithm or original code changed.

These audits do **not** establish ordered native/original writes, full actor arenas,
original heap/failure/growth ownership or lifetime/frame parity. Allocation services
remain fixed successful fixtures, not a recovered guarded allocator. Original
type +0.1 conversion, zero-intensity skip, detail gate 2, inactive constructor,
idempotent active changes, Y-major visits/table-sqrt inclusion and neutral-before-
quantization terrain lookup retain their recovered meaning. The stock source's
1,201 map visits and hashes of all 13,515 numeric records match.

## Evidence and reproduction

Fresh exports, expectations and receipts remain ignored under
`private/migration/allied-disc/static-light/` and
`private/migration/supplied-ra2-1006/static-light/`. Fresh runs refuse existing
evidence. Replay pins engine/profile, sources/mapping tools, exporter, retained
assets/render data and expectation fingerprint; it cannot replace fresh receipts.
Ten synthetic profile/evidence guards pass. Historical disc evidence is preserved.

Native vectors retain disc render-data hash
`50d2876e6bf8a3b9d535a1843ef93f41109b7021a15e1dbacb47aaa881389c6d`.
Patched research requires explicit `--native-data-exe` disc identity. The separate
map-light exporter supplies the retained owned map/rules/palettes; archive precedence
and prepared/runtime data are not promoted.

```sh
./build.command
./test.command --data-dir "$PWD/private/game"
build/tools-env/bin/python tests/test_static_light_profiles.py
build/tools-env/bin/python tools/verify_static_light_mapping.py \
  --disc private/disc-allied/game.exe --patched private/official-1006-probe/game.exe
# Fresh evidence exists here; replay without original execution:
build/tools-env/bin/python tests/compare_static_light.py \
  --exe private/official-1006-probe/game.exe \
  --native-data-exe private/disc-allied/game.exe \
  --expectations private/migration/supplied-ra2-1006/static-light/expected.json
# After README's sanitizer build, add:
# --native build/sanitize/static-light-vectors
# --report private/migration/supplied-ra2-1006/static-light/sanitize-report.json
./run.command --light-demo
```

On a checkout without receipts, omit `--expectations` for fresh original execution
in the authorized Mac Unicorn JIT context. Both native sanitizer replays pass.
`private/patch-inspection/verify-static-light-checkpoint.py` verifies current
source/engine/input/native identities, both sanitizer receipts, cross-engine
outputs and equality with retained disc outputs. Its receipt is
`private/migration/static-light-checkpoint-verification.json`. Mapping evidence:
`private/patch-inspection/static-light-1006-mapping.json`; discovery/probes/
disassembly stay private. No original instruction bytes were patched or copied.

The preceding map-light checkpoint's build, native/sanitizer synthetic, owned-data
and both 170-frame SDL checks remain applicable: this changes isolated static
research fixtures only. Unit and other runtime algorithms/fixtures are unchanged;
no new native-platform or whole-frame claim is added. Source installations/media,
Outpost 2, Windows task and system settings are untouched.
[UNIT_LIGHTING_1006.md](UNIT_LIGHTING_1006.md) now verifies ordinary unit light.
Next migrate cache, scenery and occupation/lifecycle, then archive precedence/prepared inputs
before runtime promotion and milestone 20. Demo placement, visibility, controls/
clearance, actor/house/cache lifetime and redraw/scheduling remain adapters or open.
