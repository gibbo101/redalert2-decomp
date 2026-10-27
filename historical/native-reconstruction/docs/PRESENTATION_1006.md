# RA2 1.006 lighting, palette and depth primitive migration

October 14, 2026. Ivalice / Apple Silicon macOS. This extends the movement
checkpoint `5207979`. [BASELINE_1006.md](BASELINE_1006.md) records supplied-patch
materialization and the completed, approved private Windows engine transfer;
[DRIVE_1006.md](DRIVE_1006.md) records the migrated movement family.

**8,568 fresh original/native cases, comparing 312,208 values, pass on each
engine.** Both profiles also pass native ASan/UBSan replay. The native algorithms
are unchanged. This migrates presentation primitives only: the application,
preparation tools and other rendering/lifecycle oracles still default to disc
inputs. Patched runtime promotion and milestone 20 remain pending.

## Exact inputs and reference leads

| Profile | Executable SHA-256 |
| --- | --- |
| Allied disc | `135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743` |
| Supplied RA2 1.006 patch output | `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f` |

Inputs are the retained `private/disc-allied/game.exe` and
`private/official-1006-probe/game.exe`. The latter is byte-identical to the approved
Windows copy. Both embed version 1.08; complete hashes and supplied-patch lineage
select these profiles. Source installations/media are read-only. No materialization,
transfer, original-game launch or Windows task dispatch was repeated.

Consulted [REFERENCES.md](REFERENCES.md)'s voxel/palette and testing entries,
redalert2-recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439`, `docs/voxels.md`
(The buffers, Following the image onto the battlefield) and `docs/testing.md`, plus
its LICENSE. The hypothesis was to resolve lighting/output data from actual callers
and operands, then compare unchanged routines rather than adopting its YR/HD host
behavior or addresses. Its MIT grant covers authored work and excludes generated
game code; the stale license scope wording remains documented in REFERENCES.md.
No upstream, header, generated or lifted code was incorporated.

## Inspected mapping and data

Normalized instruction prefixes supplied unique discovery candidates. Complete
range/operand inspection, rather than a blanket offset, established the mappings:

| Boundary | Disc VA | Supplied 1.006 VA |
| --- | --- | --- |
| Single-light normal shades | `0x710480` | `0x71BA20` |
| Double-light normal shades | `0x710500` | `0x71BAA0` |
| Initialize 256 shade slots | `0x710740` | `0x71BCE0` |
| Complete palette update, scalar RGB565 branch selected | `0x536B30` | `0x538AA0` |
| Transparent depth span | `0x487750` | `0x487970` |
| Isolated scalar VPL lookup block | `0x70F4C9..0x70F4FC` | `0x71AA69..0x71AA9C` |
| Quantized square root / integer conversion | `0x4B9F30` / `0x76A6B0` | `0x4BA410` / `0x77F110` |
| Normal pointers / counts | `0x7E37D0` / `0x7E37E4` | `0x7F9F80` / `0x7F9F94` |
| Shade output / VPL sections | `0xAE0870` / `0xADC068` | `0xAF8E10` / `0xAF4608` |
| Depth-buffer global | `0x821F8C` | `0x839C6C` |

`tools/verify_presentation_mapping.py` checks **eight complete ranges / 615
instructions**, all internal branches, explicit changed operands and remaining
encoded bytes. It verifies nine constant/table ranges and all four normal arrays
through the pointer/count tables actually referenced by the shade routines.
Counts remain `(0,16,36,64,245)`. Referenced normal arrays, square-root mantissas,
shade scale and palette coefficient match byte-for-byte. Four palette dispatch
entries retain local offsets. Optimized callees are inspection metadata only;
the suite selects the scalar branch and does not establish their parity.

`tests/presentation_profiles.py` is research metadata, not a runtime mapping.
Patched selection requires explicit opt-in in `PresentationOracle`. Its subclasses
retain the disc-only default; accepting these primitive addresses does not enable
patched raster, map light, scenery, occupation or lifecycle layouts. Unknown hashes
and unmapped patched addresses fail closed.

## Executed boundary and audits

The same seeded domain from [PRESENTATION.md](PRESENTATION.md) now passes freshly
on each executable:

| Group | Cases | Compared values |
| --- | ---: | ---: |
| Single/double normal shades | 192 | 49,152 |
| Scalar RGB565 palette tables | 24 | 245,760 |
| Every supplied VPL lookup | 8,192 | 8,192 |
| Transparent depth spans, including circular wrapping | 160 | 9,104 |
| **Total per engine** | **8,568** | **312,208** |

No APIs/services are substituted or original instruction bytes patched. Light/view
vectors, palettes/masks/tints, converter fields, RGB565 channel metadata and span
buffers are explicit inputs. Full shade/palette/span routines execute, including
the original square-root and integer-conversion helpers. VPL tests execute only
the named lookup block. The numeric domain and `0x0E7F` context remain those in
PRESENTATION.md: original operation order, float32 stores, table square root,
integer truncation, RGB565 quantization and strict depth comparison are preserved.

**568 callable root invocations** per engine audit return addresses, final ESP,
callee-saved EBX/ESI/EDI/EBP, caller stack beyond consumed arguments, immutable
primitive inputs and permitted output/field/stack write ranges. Palette/span routines
reuse consumed argument slots; those slots are not asserted immutable. The **8,192
lookup blocks** audit unchanged ESP and their sole permitted stack-byte store.
Unexpected writes, including code/table writes, fail. This is a bounded primitive
write/input audit, not ordered native/original write parity or a full actor arena.
Occupation/lifecycle retain their stronger independent audits.

The native vector runner still consumes the verified **disc render-data file** and
supplied VPL. Patched commands require `--native-data-exe` explicitly to identify
the retained disc engine; a fresh mapping/data check verifies the consumed original
normal/math inputs before testing. It is not executed by the native runner.
The render file includes a light-angle field unused by this primitive suite;
its patched caller/association belongs to the later raster migration.
No mixed prepared-source profile or runtime acceptance was enabled. Original archive
precedence and effective patched inputs remain unverified.

Fresh reports/expectations are isolated under:

```text
private/migration/allied-disc/presentation/
private/migration/supplied-ra2-1006/presentation/
```

Each contains `expected.json`, `report.json`, `sanitize-report.json` and a protected
read-only VPL export. Receipts pin exact engines, runner, prepared render/VPL data,
oracle/profile/evidence/mapping sources and expectation fingerprint. Native replay
checks the fresh receipt and identities, records that original instructions were
not executed, and refuses replacing expectations or fresh receipts. Eight synthetic
profile/path/cache/receipt guards pass. The earlier `private/presentation/` evidence
is preserved and is historical, not a substitute for the new receipts.

## Reproduce and try the prototype

```sh
./build.command
./test.command --data-dir "$PWD/private/game"
./run.command
build/tools-env/bin/python tests/test_presentation_profiles.py
build/tools-env/bin/python tools/verify_presentation_mapping.py \
  --disc private/disc-allied/game.exe --patched private/official-1006-probe/game.exe
build/tools-env/bin/python tests/compare_presentation.py \
  --exe private/official-1006-probe/game.exe \
  --native-data-exe private/disc-allied/game.exe --data-dir private/game
build/tools-env/bin/python tests/compare_presentation.py \
  --exe private/disc-allied/game.exe --data-dir private/game
# After README's headless sanitizer build:
build/tools-env/bin/python tests/compare_presentation.py \
  --exe private/official-1006-probe/game.exe --native-data-exe private/disc-allied/game.exe \
  --native build/sanitize/presentation-vectors \
  --expectations private/migration/supplied-ra2-1006/presentation/expected.json \
  --report private/migration/supplied-ra2-1006/presentation/sanitize-report.json
# Disc replay uses its own exe and allied-disc expectation/report paths.
```

Original execution needs the established authorized Mac JIT context. Replay needs
no original execution. Mapping output refuses replacement; omit `--output` to
recheck or select a fresh private filename. Discovery, full private disassembly,
operand inspection and mapping evidence remain under `private/patch-inspection/`.
The successful mapping receipt is `presentation-1006-mapping.json`.

After the shared fixture change, fresh **disc** regressions also pass: 128 voxel
poses plus 192 matrix products, lighting setups and complete 256×256 indexed
buffers; **17,510 map-light**, **13,472 occupation** and **3,868 lifecycle** results.
Their fresh evidence stays in the separate
`private/migration/disc-presentation-regressions/` workspace, preserving historical
paths. Map-light, occupation and lifecycle expectations also pass ASan/UBSan replay.
A first raster native invocation there lacked its hardcoded relative render-data
input; supplying an identical private copy and rerunning completed the check.
No original/native output mismatch was found.

Build, native/import/preparation tests, owned renderer/light/scenery/profile checks,
and both **170-frame SDL regressions** pass. These establish native integration,
not original input/scheduler or whole-frame fidelity. Only Apple Silicon macOS is
tested. No native Windows/Linux support, new gameplay or original-game observation
is claimed. Proprietary files/research stay ignored; Outpost 2 and source inputs
remain untouched.

Next migrate the flat voxel poses/loader/raster and composition profiles, followed
by light/cache/scenery/occupation/lifecycle, retaining each suite's audits and
historical evidence. Establish original asset precedence and consistent prepared
inputs before patched integration/promotion. Ground-layer traversal/eligibility is
still milestone 20. Direct routing/clearance, controls, visibility, scene scheduling,
actor/house/cache lifetime and full-frame integration remain adapters or open;
pathfinding, combat, economy, AI, campaigns, multiplayer, audio, saves and YR remain
later work. The full-game goal is active and incomplete.
