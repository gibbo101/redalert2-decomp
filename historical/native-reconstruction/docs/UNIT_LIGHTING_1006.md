# RA2 1.006 ordinary unit-light migration

October 14, 2026. Ivalice / Apple Silicon macOS.

**3,257 fresh original/native results pass on each engine.** Both ASan/UBSan
native replays pass. Outputs also equal the retained disc suite. Native C++
algorithms are unchanged. Runtime and prepared-data gates remain disc-only until
remaining subsystem profiles and effective archive precedence are verified.
This extends the baseline coverage of [UNIT_LIGHTING.md](UNIT_LIGHTING.md);
milestone 19 remains the gameplay checkpoint. Full actor, original house creation,
allocator/converter lifetime and whole-frame parity remain outside the claim.

## Identities and reference hypothesis

| Original engine | SHA-256 |
| --- | --- |
| Allied disc, embedded 1.08 | `135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743` |
| Supplied RA2 1.006 patch output, embedded 1.08 | `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f` |

Both are PE32/i386 at image base `0x400000`. The patched file is 4,485,392 bytes
and equals the privately transferred Windows base engine. [BASELINE_1006.md](BASELINE_1006.md)
records supplied-patch lineage and the user's no-CD provenance; this does not
certify publisher authentication, a pristine entire installation or YR equivalence.
Every executed oracle verifies the full hash before addressing original code.

Consulted redalert2-recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439`,
`docs/voxels.md` (Following the image onto the battlefield, Units flashed),
`docs/testing.md` and LICENSE. Final house-palette separation and isolated testing
supply leads, not a base RA2 oracle. YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88`, `TechnoClass.h` GetDrawer,
`RulesClass.h` ExtraUnitLight, `ScenarioClass.h` and `ConvertClass.h` supply
vocabulary only. Hypothesis: independently locate ordinary brightness/house
selection and the complete RGB565 converter path on the supplied patched engine,
then compare the retained bounded domain. No upstream/header/generated code was
incorporated. See [REFERENCES.md](REFERENCES.md).

## Independent inspection

`tools/verify_unit_light_mapping.py` checks **14 ranges / 2,238 instructions**,
encoded operand differences, four numeric/mask ranges and actual metadata/slots.
`tests/unit_light_profiles.py` adds **111 explicit mappings** to the inspected
ancestor profiles. No blanket address displacement or installer label selects code.

| Inspected boundary | Disc VA | Supplied 1.006 VA |
| --- | --- | --- |
| ExtraUnitLight numeric block and field store | `0x63D76E` | `0x64680E` |
| Complete coordinate-to-word-cell getter | `0x41B320` | `0x41B320` |
| Ordinary brightness block | `0x6F5B21` | `0x700FF1` |
| Complete brightness-effects helper | `0x6CCDF0` | `0x6D79D0` |
| House/scheme/converter selection block | `0x6F4013` | `0x6FF4E3` |
| Complete scheme recreation | `0x65A9A0` | `0x663B40` |
| Complete palette copy/remap/allocation | `0x65A4F0` | `0x663690` |
| Complete LightConvert constructor | `0x5368F0` | `0x538860` |
| Full byte/word Convert blitter initializer | `0x4838E0` | `0x483B00` |
| Complete alpha registry lookup/creation helper | `0x41E3E0` | `0x41E3E0` |
| Unit coordinate caller | `0x6F59FB` | `0x700ECB` |
| Effects/final-draw caller | `0x6F4C28` | `0x7000F8` |
| Theater scheme-input caller | `0x519605` | `0x51A1E5` |
| Scheme one-/53-row load caller | `0x63EE52` | `0x647EF2` |

The full initializer ends after both word-branch returns at `0x4850E1` /
`0x485301`. [STAGING_1006.md](STAGING_1006.md) inspected its byte branch only.
The word continuation is resolved through the actual initializer branch, extending
that inspection rather than assuming an offset from similar allocator calls.
All **103 constructed blitter-table RTTI identities** agree. Only the retained
ordinary executed span receives behavioral parity; other blitter methods do not.

Actual Unit main table `0x798C90 → 0x7ADDF8`, slot 104 / `+0x1A0`, selects the
coordinate getter. LightConvert `0x7905C4 → 0x7A55DC` is independently identified;
its destructor slot is inspected but destruction is not executed. Ordinary
`BlitTransXlatAlphaZRead<unsigned short>` table `0x78920C → 0x79E20C`, slot 1,
selects `0x488650 → 0x488870`. Full Convert construction, primitive palette update
and surface dispatch retain their earlier independently verified ancestor ranges.
The affected mask `0x7DC228 → 0x7F264C` and neutral fallback mask agree byte-for-byte,
as do the actual numeric multiplier and four contiguous color-ramp doubles.
Instruction-shape agreement does not establish unexecuted branch parity.

## Executed domain and audit limits

| Fresh matching results per engine | Count |
| --- | ---: |
| ExtraUnitLight decimal boundaries/neighbors | 1,545 |
| Signed coordinate getter | 256 |
| Ordinary brightness/effects | 630 |
| Permuted house/converter selection | 512 |
| Owned ExtraUnitLight | 1 |
| Complete converters for all 19 supplied named colors | 19 |
| Saturation surfaces, each with all 256 alpha values | 109 |
| Combined cell/house complete color/depth surfaces | 182 |
| Numeric repeatability after constructors/surfaces | 3 |
| **Total** | **3,257** |

Preserve the retained numeric domain and [UNIT_LIGHTING.md](UNIT_LIGHTING.md)
behavior: no +0.1 bias, `-0.15 → -149`, signed word coordinates, wrapped ambient
plus extra, tested predicate/effects gates, neutral house tint, mask exclusion of
240–254 and brightness saturation at lookup bin 254. Local source tint does not
become ordinary house-converter tint. Combined tests include 54 radius-crossing
positions. Full palette and color/depth planes compare by their existing hashes.

Per engine, **2,037 callable roots**, **4,617 blocks**, **1,729 guarded scheme
allocations** and **19 independent scheme fixture resets** are audited, including
inherited setup/cell/surface calls. The supplied actor predicate is called 432
times. Call guards check return address, consumed arguments versus caller stack,
ESP, callee-saved registers, immutable inputs and permitted stores. Numeric blocks
preserve the supplied double/caller bytes; brightness preserves unrelated locals.
Surface locks and unchanged unit depth retain the inherited audits.

Each independent converter case copies its result to host arrays, checks heap
canaries, then resets only this fixture's allocator/ownership list. No guest model
or converter from the previous case is reused. The original-generated warm alpha
table remains at separate `0x1C00000`; its data and shade field are immutable,
while the inspected reference-count word at `+0x20004` may change. Full original
lookup/refcount operations execute. Heap/free, registry storage, house/actor records,
visibility and placement remain successful isolation fixtures. These audits do
not compare ordered native/original writes, full actor arenas, real allocator
ownership, failure/destruction, original house initialization or full Unit draw.

## Evidence and reproduction

Fresh expectations, receipts and protected exports:

```text
private/migration/allied-disc/unit-light/
private/migration/supplied-ra2-1006/unit-light/
```

Fresh execution refuses existing expectations/receipts. Replay pins the exact
engine/profile, mapping/oracle sources, **both exporters**, five owned exports,
raster/render files and fresh expectation fingerprint. It cannot replace original
receipts. Ten synthetic profile/evidence guards pass. Earlier disc evidence is
preserved, not relabeled. Initial preparation rejected an overly broad asset
inventory before original execution; corrected receipts pin only the five exports
this suite consumes. Successful short probes preceded fresh complete execution.

Retained native raster data:
`f357f3b4d7b048b7f65d7a43f4f96a41e6c21b5974bb1340d7fd98e92abcd8a3`.
Retained native render data:
`50d2876e6bf8a3b9d535a1843ef93f41109b7021a15e1dbacb47aaa881389c6d`.
Patched research requires explicit retained disc `--native-data-exe`.

```sh
./build.command
./test.command --data-dir "$PWD/private/game"
build/tools-env/bin/python tests/test_unit_light_profiles.py
build/tools-env/bin/python tools/verify_unit_light_mapping.py \
  --disc private/disc-allied/game.exe --patched private/official-1006-probe/game.exe
# Fresh receipts already exist here; replay without original execution:
build/tools-env/bin/python tests/compare_unit_light.py \
  --exe private/official-1006-probe/game.exe \
  --native-data-exe private/disc-allied/game.exe \
  --expectations private/migration/supplied-ra2-1006/unit-light/expected.json
# After README's sanitizer build, add:
# --native build/sanitize/unit-light-vectors
# --report private/migration/supplied-ra2-1006/unit-light/sanitize-report.json
./run.command --light-demo
```

On a checkout without receipts, omit `--expectations` for fresh original execution
in the authorized Mac Unicorn JIT context. Both sanitizer replays pass without
diagnostics. The current source/receipt/input/native checks, both sanitizer
receipts and cross-engine/retained-disc equality are recorded in
`private/migration/unit-light-checkpoint-verification.json`, produced by
`private/patch-inspection/verify-unit-light-checkpoint.py`. Mapping receipt:
`private/patch-inspection/unit-light-1006-mapping.json`. Discovery, disassembly,
assets and expectations remain private. No original instructions are modified,
tracked, shipped or executed by the native runtime.

Fresh affected disc regressions pass: 420 scenery, 808 prop and 1,128 tree-type
results, with all three sanitizer replays in
`private/migration/disc-unit-light-regressions-v2/`. Owned-data checks and both
170-frame SDL regressions verify retained integration; they do not establish
original full-frame parity. Only Apple Silicon macOS is tested. Lit cache/shadow
keys, scenery/types/props, occupation/lifecycle and archive precedence migration
remain before patched runtime/data promotion and milestone 20. Controls/routing,
clearance, visibility, scheduling, actor/house/cache lifetime, alternate/status
branches and full-frame parity remain adapters or open.
