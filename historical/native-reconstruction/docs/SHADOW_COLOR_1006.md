# RA2 1.006 shadow and player-color migration

October 14, 2026. Ivalice / Apple Silicon macOS. This extends composition
checkpoint `9a12034`. [BASELINE_1006.md](BASELINE_1006.md) records the completed
private transfer and supplied-patch lineage; neither was repeated here.

**9,812 fresh original/native results pass on each engine.** Both native
ASan/UBSan replays pass. Native shadow/color algorithms remain unchanged.
Runtime and prepared-data gates remain disc-only pending the remaining profile
and archive-precedence migration. Milestone 19 remains the gameplay checkpoint;
this verifies the retained [SHADOW_COLOR.md](SHADOW_COLOR.md) research domain on
an independently selected patched engine, not whole-game or whole-frame parity.

## Identity and reference hypothesis

| Research profile | Executable SHA-256 |
| --- | --- |
| Allied disc | `135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743` |
| Supplied RA2 1.006 patch output | `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f` |

Inputs are `private/disc-allied/game.exe` and
`private/official-1006-probe/game.exe`. The latter remains byte-identical to the
approved private Windows copy at `private/windows-baseline-20261014/game.exe`.
Both embed version 1.08; only the complete hash selects a research profile.
This establishes supplied-patch lineage, not publisher authentication or pristine
status of the full installation reported to contain no-CD modifications.
No Windows gameplay or frame observation was added.

Consulted [REFERENCES.md](REFERENCES.md)'s shadow/final-composition/cache leads:
redalert2-recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439`, `docs/voxels.md`
(Following the image onto the battlefield, Shadows, Cost), `docs/testing.md` and
LICENSE. The hypothesis was to identify the actual palette-prefix, shadow pose,
projection, stencil sampling and final span on our patched engine, then execute
the retained ordinary domain. Its YR/Steam/EA addresses and HD treatment are
reference leads only. No upstream-authored, unlicensed header or generated/lifted
game code was incorporated; the checked license excludes generated game code.

## Inspected mappings and data

`tools/verify_shadow_color_mapping.py` checks **15 instruction ranges / 1,768
instructions**, **10 consumed data ranges**, and actual RTTI/dispatch slots.
Each changed operand has an explicit mapping, internal branches keep their relative
targets, and all remaining instruction bytes agree. No opcode difference was found
in those ranges. Addresses were independently discovered and inspected; no global
address displacement is assumed.

| Boundary | Disc VA | Supplied 1.006 VA |
| --- | --- | --- |
| Complete integer HSV | `0x4FE400..0x4FE515` | `0x4FF050..0x4FF165` |
| Copy/remap prefix, before LightConvert allocation | `0x65A4F0..0x65A5ED` | `0x663690..0x66378D` |
| Complete flat/ramp matrix initializer | `0x70CAC0..0x70D79A` | `0x718060..0x718D3A` |
| Complete Drive shadow pose | `0x4A00D0` | `0x4A0500` |
| Complete base shadow pose | `0x53B160` | `0x53D0D0` |
| Complete shadow queue/projection | `0x70BDC0` | `0x717360` |
| Complete occupied-column plotter | `0x70E670` | `0x719C10` |
| Selected shadow Z-read span | `0x487170` | `0x487390` |
| Complete BSurface pixel getter | `0x75F770` | `0x7741D0` |
| Actual BSurface / shadow blitter vtables | `0x785EF8`, `0x78939C` | `0x79AEF8`, `0x79E39C` |
| Actual Drive interface vtable | `0x78B4D4` | `0x7A04CC` |

Range ends are exclusive. Six complete palette-copy, rotation and quaternion
helpers are also checked: `0x5FAB10`, `0x58CBA0`, `0x58CC00`, `0x619BC0`,
`0x619C90`, `0x61A3F0`. Actual BSurface slot 10 selects its pixel getter;
`BlitTransDarkenZRead<uint16>` slot 1 selects the span. Drive interface slot 10
selects the shadow pose, resolving a similar Ship candidate. Inherited composition,
raster and primitive mapping verifiers also run for patched research.

Player ramp angles, midpoint, heading step, pose zero/threshold, coordinate scale/
rounding, axis-rotation one and quaternion constants match byte-for-byte. Adjacent
bytes are not assumed equal: the axis-rotation operand reads exactly four bytes.
The retained native raster input remains
`f357f3b4d7b048b7f65d7a43f4f96a41e6c21b5974bb1340d7fd98e92abcd8a3`.
Runtime executable reads remain tracks only; no original code or extracted arrays
are compiled into or shipped with the application.

## Execution and audit boundary

| Domain | Matching cases per engine |
| --- | ---: |
| Integer HSV, every hue plus boundaries/seeded cases | 6,912 |
| Complete copied/remapped palettes, including all 19 supplied names | 2,323 |
| Light-derived offset float32 bits | 64 |
| Flat shadow matrices and heading keys | 128 |
| Complete 256×256 masks and crop/corner metadata | 288 |
| Complete clipped RGB565/depth shadow surfaces | 97 |
| **Total** | **9,812** |

Masks cover all 32 headings of each stock body/turret/barrel and three stencil
profiles, with independent turret headings and fractional translations. The final
surface cases cover clipping, nonzero clip origins, depth ties, signed adjustments
and every RGB565 value. Destination depth remains unchanged. Original VXL loading
uses bounded file/heap services; pose uses a supplied zero-ramp map getter. Other
shadow/render services are absent. House, actor/cache and world inputs remain
explicit fixtures, not a complete original match.

Per engine, **8,747 callable roots** and **2,516 isolated blocks** audit caller
stack/ESP/registers, immutable inputs and permitted writes. The callable counts
include setup and inherited composition/raster calls. Thirteen guarded allocations
include the successful alpha allocation and twelve loader allocations. Actual
stencil/surface lock counts may change during draws but must return to zero.

The ColorScheme prefix stops with an open stack frame. Its dedicated audit checks
stop EIP, the inspected aligned frame (`ESP = entry - 0x40`, `EBP = entry - 4`),
return address, both arguments and caller stack beyond them. Guest stores are
restricted to a bounded frame and the 768-byte output; HSV and palette inputs
remain unchanged. A callable-return ABI is not imposed on this prefix.

The matrix initializer's two 256-vector output arrays are bounded from its
12-byte stride and `0xC00` loop limit. Other matrix/vector outputs are declared
separately and its input angle constants are immutable. The initializer executes
as original fixture setup; this does not establish differential parity for every
nonflat table or branch it initializes. Translated-cache invalidation retains the
existing camera-stop boundary and does not modify original instructions.

Shadow queue/reset/flush permit only declared global scratch, a single 72-byte
queue record, the output rectangle and temporary stencil lock. Models, matrices,
offset and stencil pixels remain immutable. Final blits restrict writes to color,
declared scratch and temporary locks, preserving depth/source/surface inputs.
These are scoped original-fixture audits, **not** ordered native/original writes,
full actor arenas, converter/cache lifetime or whole-frame parity.

Integer HSV divisions, palette slots 16–31, original table trig/float32 stores,
independent uint16 shadow coordinates, two-pixel replacement writes, strict depth
reads and half-mask `0x7BEF` retain their historical meaning. Named color/house
selection and body-only runtime shadows remain bounded host policies.

## Evidence and reproduction

Fresh expectations, receipts, assets and original buffers remain ignored under:

```text
private/migration/allied-disc/shadow-color/
private/migration/supplied-ra2-1006/shadow-color/
```

Fresh execution refuses existing receipts/expectations. Replay verifies engine,
profile, oracle/mapping sources, retained data, exporter, assets and the original
expectation fingerprint; it cannot replace fresh evidence. Nine synthetic profile/
evidence guards pass. The mapping receipt is
`private/patch-inspection/shadow-color-1006-mapping.json`; paired disassembly and
probes remain private alongside it. Historical disc evidence is preserved.

```sh
./build.command
./test.command --data-dir "$PWD/private/game"
build/tools-env/bin/python tests/test_shadow_color_profiles.py
build/tools-env/bin/python tools/verify_shadow_color_mapping.py \
  --disc private/disc-allied/game.exe --patched private/official-1006-probe/game.exe
# Fresh evidence already exists here; replay without original execution:
build/tools-env/bin/python tests/compare_shadow_color.py \
  --exe private/official-1006-probe/game.exe \
  --native-data-exe private/disc-allied/game.exe \
  --expectations private/migration/supplied-ra2-1006/shadow-color/expected.json
# For instrumented replay after README's sanitizer build, add:
# --native build/sanitize/shadow-color-vectors
# --report private/migration/supplied-ra2-1006/shadow-color/sanitize-report.json
```

On a checkout without receipts, omit `--expectations` for fresh execution in the
authorized Mac Unicorn JIT context. The native runner consumes one raster-data
argument; it does not consume render-data. The existing palette/rules export and
raster asset export supply the six retained input files with checked hashes.
Patched archive precedence is not promoted by reusing these disc inputs.

Fresh affected **disc** regressions pass in
`private/migration/disc-shadow-color-regressions/`: 2,603 staging, 3,257 unit-light,
4,743 lit-cache, 2,204 shadow-key, 420 scenery, 808 prop and 1,128 terrain-type
results, including reset/protocol commands. These exercise retained disc profiles;
they do not migrate those subsystems. Build, synthetic native/sanitizer checks,
import/preparation guards, owned-data checks and both 170-frame SDL regressions
pass. Current receipt/source/engine/data/native identities, all cross-engine
outputs, Python syntax, local links, arm64 identity and diff/source audits pass.
The checkpoint verification receipt is
`private/migration/shadow-color-checkpoint-verification.json`. No source install,
media, Outpost 2, Windows task or system configuration changed.

Remaining staging/light/cache/scenery/occupation/lifecycle mapping and effective
archive precedence precede runtime/data promotion and milestone 20. Full actor
prechecks, nonflat/status branches, cache pool/ownership/lifetime, house assignment,
visibility, scheduling and whole-frame parity remain outside this checkpoint.
Windows/Linux native support remains unverified.
