# RA2 1.006 world, TMP and unit composition migration

[Queued Cell terrain depth](FRAME_TERRAIN_DEPTH_1006.md) separately verifies the
special depth-only flag used by4754B0. Its317 roots/82,870 ordered stores and
actual Renderer integration do not expand the historical ordinary-color proof
below into whole52C230 scratch-state or frame fidelity.

October 14, 2026. Ivalice / Apple Silicon macOS. This extends the voxel checkpoint
`3aff17d`. [BASELINE_1006.md](BASELINE_1006.md) records the supplied-patch lineage
and completed private Windows transfer; neither was repeated here.

**424 fresh original/native results pass on each engine**, including complete
clipped unit and TMP color/depth surfaces. Both native ASan/UBSan replays pass.
Native composition algorithms remain unchanged. The runtime and prepared-data
gates remain disc-only pending the remaining profile and archive-precedence
migration. This is a research checkpoint; milestone 19 remains the gameplay checkpoint.

## Exact inputs and reference hypotheses

| Profile | Executable SHA-256 |
| --- | --- |
| Allied disc | `135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743` |
| Supplied RA2 1.006 patch output | `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f` |

Inputs are `private/disc-allied/game.exe` and
`private/official-1006-probe/game.exe`. Both embed 1.08; complete hashes select
research profiles. The latter remains byte-identical to the approved copy at
`private/windows-baseline-20261014/game.exe`. This establishes supplied-patch
lineage, not publisher authentication or pristine status of the full reported
no-CD installation. No Windows gameplay or frame observation was added.

Consulted [REFERENCES.md](REFERENCES.md)'s final battlefield-composition and
isolated-test leads: redalert2-recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439`, `docs/voxels.md`
(Following the image onto the battlefield), `docs/testing.md` and LICENSE;
YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88`, `TacticalClass.h` and
`Surface.h` supplied naming/layout hypotheses. The hypothesis was that the bounded
ordinary projection, depth, part-order and surface paths could be mapped and
executed independently on our supplied patched engine. YR addresses, HD changes,
replacement gameplay and pointer-host architecture were not adopted. No upstream,
unlicensed header or generated/lifted game code was incorporated.

## Inspected mappings and consumed data

`tools/verify_composition_mapping.py` checks **34 instruction ranges / 4,255
instructions**, **10 data ranges**, and actual RTTI/vtable links. Every changed
operand has an explicit mapping; internal branches retain their relative targets,
and all remaining instruction bytes agree. No opcode difference was found in
these ranges. Prefix similarity alone was only a discovery lead.

| Boundary | Disc VA | Supplied 1.006 VA |
| --- | --- | --- |
| Projection initializers | `0x6975D0`, `0x697660`, `0x697930` | `0x6A20E0`, `0x6A2170`, `0x6A2440` |
| Complete world projection | `0x697C90` | `0x6A27A0` |
| Height-to-pixel helper | `0x697E60` | `0x6A2970` |
| Complete flat unit depth routine | `0x6C52C0..0x6C592D` | `0x6CFEA0..0x6D050D` |
| Drive depth / gradient forwarding | `0x4A4400`, `0x4A4410` | `0x4A4830`, `0x4A4840` |
| Gradient selector | `0x53B540` | `0x53D4B0` |
| Normal part-order block | `0x6F4A38..0x6F4B57` | `0x6FFF08..0x700027` |
| Complete blitter selector | `0x485880..0x485DE4` | `0x485AA0..0x486004` |
| Complete final wrapper / surface blit | `0x49EF70`, `0x434A00` | `0x49F3A0`, `0x434B40` |
| Complete clipping helpers | `0x760730`, `0x760950` | `0x775190`, `0x7753B0` |
| Selected alpha Z-read span | `0x488650` | `0x488870` |
| Complete TMP draw | `0x52A340..0x52BE77` | `0x52C230..0x52DD67` |
| Alpha-map construction block | `0x41E40E..0x41E475` | Same addresses |
| Actual BSurface vtable | `0x785EF8` | `0x79AEF8` |
| Actual alpha Z-read blitter vtable | `0x78920C` | `0x79E20C` |

Range ends are exclusive. The verifier includes rectangle copies, buffer pointer
helpers, selected original BSurface lock/unlock/bpp/stride/bounds/width/height
methods and math-helper ranges. Alpha-cache lookup prefix/hit tail and the alpha
construction block are inspected separately; full cache registration/construction
failure behavior is excluded. CRT exceptional branches and external CRT dependency
closure receive no complete-library parity claim.

RTTI identifies BSurface and `BlitTransXlatAlphaZRead<uint16>` in each engine.
Selected BSurface slots 23, 24, 28–32, blitter slot 1 and actual Drive interface
slots 14/15 point to inspected methods. These checks avoid assuming a generic
vtable displacement. Drive/movement and raster/presentation overlapping metadata
agree, and the patched comparison independently runs those mapping verifiers.

Consumed projection constants, gradient descriptors, blitter masks, TMP row offsets
and diamond bytes, and unit-depth constants match byte-for-byte. The retained
render/raster data hashes are unchanged:

- `render-data.bin`: `50d2876e6bf8a3b9d535a1843ef93f41109b7021a15e1dbacb47aaa881389c6d`
- `raster-data.bin`: `f357f3b4d7b048b7f65d7a43f4f96a41e6c21b5974bb1340d7fd98e92abcd8a3`

Runtime executable reads remain tracks only. No extracted tables or proprietary
assets are compiled into or tracked with the application.

## Executed boundary and audit limits

| Domain | Passing results per engine |
| --- | ---: |
| Signed world projection / height boundaries | 256 |
| Barrel/turret dispatch order | 40 |
| Healthy flat unit depth | 8 |
| Complete clipped unit RGB565 and depth surfaces | 96 |
| Complete ordinary TMP RGB565 and depth surfaces | 24 |
| **Total** | **424** |

The six supplied subtiles of clear01.tem, cliff01.tem and slope01.tem retain their
original hashes. Research exports are separate per profile, outside the source
installation. Symlink/source destinations and different existing data are refused.
Native `composition-vectors` now accepts explicit raster/render paths; the legacy
no-argument mode remains for existing callers.

The unit fixture executes the full wrapper, clipping, original BSurface methods
and selected span. It supplies palette/color/depth/alpha planes and a preinitialized
converter/blitter. TMP executes the complete original draw with a supplied virtual
file getter and successful retained alpha-cache entry. Original lazy diamond
preparation writes its scratch arrays; exact buffer bounds come from inspected
loops, including the interior span-table pointer, rather than guessed small arrays.
The part-order block supplies a draw recorder. Flat depth supplies healthy flat
cells, actor getters and zero tile dimensions through a local movement-fixture
subclass; it does not broaden movement or descendant profile gates.

Per engine, **523 callable roots**, **41 isolated blocks** and **17 flat-fixture
roots** are audited. The latter include eight tested depth calls and nine setup
calls. Callable checks preserve return/caller stack, ESP and callee-saved registers;
composition permits only declared scratch/output/lock-count stores and checks
immutable inputs. Unit draws also preserve depth, alpha, source/palette, rectangles,
surface records and guarded heap inputs. The alpha block uses one successful
allocator fixture, restricts guest stores to its allocation and checks canaries.
Flat depth retains movement's read-only-image and fixture-edge audits, bounds guest
stores to its stack, and checks actor/type/locomotor inputs remain unchanged.
Blocks check stop EIP, restored ESP, caller stack and declared immutable inputs.
These are scoped original-fixture audits, **not** ordered native/original writes,
complete actor arenas, allocation/lifetime or whole-frame parity.

The projection coefficient remains `0.14350360082660085`. Height correction at
728, division toward zero, terrain ties/opaque zero/depth writes, unit strict
read-only depth, relative clip origins, scanline remainder, alpha divisor 32258
and directional painting order retain [COMPOSITION.md](COMPOSITION.md)'s meaning.

## Evidence, reproduction and remaining work

Fresh receipts, expectations and assets are under:

```text
private/migration/allied-disc/composition/
private/migration/supplied-ra2-1006/composition/
```

Fresh execution refuses existing receipts/expectations. Replay checks engine/profile,
oracle and mapping-tool sources, prepared data, asset identities and expectation
fingerprints against the unchanged fresh receipt. It cannot overwrite that receipt
or original expectations. Nine synthetic profile/evidence guards pass.
The mapping receipt is `private/patch-inspection/composition-1006-mapping.json`;
private discovery, paired operand inspection and scratch probes remain alongside it.

```sh
./build.command
./test.command --data-dir "$PWD/private/game"
build/tools-env/bin/python tests/test_composition_profiles.py
build/tools-env/bin/python tools/verify_composition_mapping.py \
  --disc private/disc-allied/game.exe --patched private/official-1006-probe/game.exe
# On this checkout fresh evidence already exists. Replay without original execution:
build/tools-env/bin/python tests/compare_composition.py \
  --exe private/official-1006-probe/game.exe \
  --native-data-exe private/disc-allied/game.exe \
  --expectations private/migration/supplied-ra2-1006/composition/expected.json
# After README's headless sanitizer build, use --native build/sanitize/composition-vectors
# and --report private/migration/supplied-ra2-1006/composition/sanitize-report.json.
```

On a checkout without these receipts, omit `--expectations` for fresh original
execution in the authorized Mac Unicorn JIT context. Both profile sanitizer replays
check all 424 cached original results; they do not execute original instructions.
Historical disc evidence is preserved.

Fresh affected **disc** regressions pass in the separate
`private/migration/disc-composition-regressions/` workspace: 9,812 shadow/color,
2,603 staging, 3,257 unit-lighting, 4,743 lit-cache, 2,204 shadow-key, 420 scenery,
808 props and 1,128 terrain-type results. Counts include each suite's reset/protocol
results where applicable. These re-execute the descendant fixtures on their retained
disc profile; they do not migrate those subsystems to 1.006. Unaffected suites retain
their earlier checkpoint evidence.

Build, native/sanitizer synthetic checks, disc/preparation tests, owned-data
lighting/scenery checks and both 170-frame SDL regressions pass. Python syntax,
local Markdown links, current receipt/source/data/native identities, matching
cross-engine results, arm64 identity, diff checks and the 187-candidate source audit
pass. The supplied engine/copy hashes retain their recorded identities. No original
installation/media, Outpost 2 or system tool settings were changed.

Remaining presentation/light/cache/scenery/occupation/lifecycle migration and
original archive precedence precede runtime/data promotion and milestone 20.
Full actor depth/status/ramp/bridge branches, special TMP flags, converter/cache
construction/lifetime, draw scheduling, visibility, controls/camera and whole-frame
parity remain outside this boundary. Native Apple Silicon integration does not
establish Windows/Linux support or original-game frame/input/timing parity.
