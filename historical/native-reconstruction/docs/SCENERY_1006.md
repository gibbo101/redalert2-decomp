# RA2 1.006 ordinary scenery, tree and prop migration

October 14, 2026. Ivalice / Apple Silicon macOS.

**2,356 fresh results pass independently on each engine**, with all six native
ASan/UBSan replays passing and outputs equal to each other and the retained disc
suites. This checkpoint migrates the retained healthy static Terrain/SHP and type/reload
boundaries from [SCENERY.md](SCENERY.md), [TREE_TYPES.md](TREE_TYPES.md) and
[PROPS.md](PROPS.md). Native algorithms and runtime/prepared-data gates remain
unchanged. Original file loading, actor scheduling, visibility, allocator/converter
lifetime, alternate animation/damage and whole-frame parity remain outside the claim.
It is an intermediate checkpoint toward the complete supplied 1.006 delivery.

## Identities and references

| Original engine | SHA-256 |
| --- | --- |
| Allied disc, embedded 1.08 | `135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743` |
| Supplied RA2 1.006 patch output, embedded 1.08 | `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f` |

Both are PE32/i386 at image base `0x400000`. The patched executable equals the
approved private Windows copy. [BASELINE_1006.md](BASELINE_1006.md) records patch
lineage and the user's no-CD provenance; this is not a pristine-installation or
YR equivalence claim. Runtime instruction execution remains absent; Unicorn is
private research only. No Windows action was required for this checkpoint.

Consulted [REFERENCES.md](REFERENCES.md)'s milestone 15–17 entries: OpenRA
`e7e9e4ad270221d7fb9725b348c75504d48c1ebd`,
`OpenRA.Mods.Common/SpriteLoaders/ShpTSLoader.cs`,
`OpenRA.Mods.Common/FileFormats/RLEZerosCompression.cs` and COPYING;
YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88`, `TerrainClass.h`,
`TerrainTypeClass.h`, `ObjectClass.h`, `ObjectTypeClass.h`, `FileFormats/SHP.h`
and `Surface.h`. Format/type vocabulary supplies leads. Hypothesis: independently
locate the patched healthy caller, actual selected spans and type/reload decisions,
then compare the retained valid-image domain. The existing licensed GPL SHP reader
adaptation retains its notices; no new upstream/header/generated game code was
incorporated. Reference rendering is not an original-behavior oracle.

## Inspected boundaries and real patch changes

`tools/verify_scenery_mapping.py` verifies **14 aligned ranges / 1,564 instructions**,
encoded operand differences, three theater extensions, actual Terrain/TerrainType
RTTI/slots and selected raw/RLE converter span tables. Its local profile adds
**42 explicit mappings** to independently inspected unit-light ancestors. Raw
BSurface/selection, coordinate/height conversion and full RGB565 Convert/LightConvert
retain the earlier complete ancestor inspection. No blanket displacement selects
addresses.

| Boundary | Disc VA | Supplied 1.006 VA |
| --- | --- | --- |
| Complete healthy Terrain draw | `0x6D8B00` | `0x6E3990` |
| Complete SHP wrapper | `0x49EA80` | `0x49EEA0` |
| Compressed BSurface dispatch | `0x434F80` | `0x4350C0` |
| Complete compressed blitter selection | `0x485B40` | `0x485D60` |
| RLE alpha/color/depth-write span | `0x48BC60` | `0x48BE80` |
| RLE half-shadow/depth-write span | `0x48A4A0` | `0x48A6C0` |
| Raw alpha/color/depth-write span | `0x489000` | `0x489220` |
| Raw half-shadow/depth-write span | `0x4878C0` | `0x487AE0` |
| Terrain strength prefix | `0x6DA7A0` | `0x6E5630` |
| Complete theater image reload | `0x6DA5D0` | `0x6E5460` |
| Complete `_makepath` | `0x76E780` | `0x7831F0` |
| Z getter / object image forwarding | `0x5CCD40` / `0x5CACF0` | `0x5D4800` / `0x5D27B0` |

The actual Terrain body/shadow calls resolve an ambiguous SHP search to the
patched wrapper. **Its prologue and cleanup differ.** Patched code checks a null
shape before accessing it, rearranges valid-input loads/pushes and delays the EBX
pop. The temporary-surface destructor pointer changes from stack +0x60 to +0x64
to account for that delayed pop. Valid-input stack meanings converge at
`0x49EAB3 → 0x49EEDE`; 1,189 shared-body bytes have complete operand/control-flow
checks. Separately reviewed fingerprints cover all 51/62 prologue and 24/24
cleanup bytes. This is complete selected-wrapper inspection with explicit changed
regions, not whole-wrapper opcode equality. Null-shape behavior is inspection
only; retained tests use valid images. Do not relabel that difference as parity.

Actual Terrain table `0x79827C → 0x7AD3CC` selects draw +0x10C, coordinates +0x1A0,
Z +0x1B8 and object image forwarding +0x68. TerrainType table
`0x798490 → 0x7AD5E0` selects the strength loader at +0x64. Constructed compressed
body/shadow fields +0x158/+0x114 select the original RLE depth-write tables; raw
body/shadow +0xBC/+0x54 select the separately checked raw tables. The oracles
assert actual constructed identities before executing drawing.

## Executed domain and audit boundaries

Preserve crop/canvas origins, source-zero transparency, signed light/height inputs,
strict depth less-than and color/depth writes, raw clipped-height versus RLE
crop-height phases and RGB565 half mask `0x7BEF`. Strength -1 alone defaults to
TreeStrength. Reload preserves same-theater/force/theater/ownership guards, original
TEM/SNO/URB filenames, free/load decisions and ordered image/ownership stores.
Native runtime remains temperate/healthy/static only.

| Retained suite per engine | Results |
| --- | ---: |
| Healthy caller, compressed tree/synthetic surfaces and converters | 420 |
| Strength/reload and all 28 owned ordinary tree images | 1,128 |
| All 23 ordinary props and synthetic raw surfaces | 808 |
| **Total** | **2,356** |

Per engine, **6,405 callable roots**, **76 blocks** and **996 guarded allocations**
are checked across the three suites. Caller roots audit return address, ESP, callee-saved registers and caller guard;
shape/crop/location, palettes, actor/type/cell records, existing heap inputs and
unrelated surface fields remain immutable. Permitted draw stores are the color/
depth planes, converter +0x17C and temporary surface lock counts; locks restore.
Successful allocations retain canaries. The strength prefix has its own open-frame
contract: stops with ESP at input stack -0x20C, ESI=type and EBP=INI, preserving
caller inputs/guards and allowing the nested argument/return pushes down to -0x214.
Reload compares ordered type writes/service events and immutable record segments.
These are bounded original-fixture audits, not full actor arenas or full ordered
native/original drawing-store parity.

The alpha-table factory at `0x41E3E0` reuses by shade count and increments
+0x20004, or appends one new table to the supplied registry with spare capacity.
Converter construction now explicitly permits that reference-count field, the
new registry slot and count while preserving existing entries/table data. Original
heap/registry growth/failure/destruction is not recovered by this fixture.

Two initial full runs (16.53 s disc / 17.84 s patched) stopped when the new audit
correctly rejected unaccounted 27-row alpha registration. No expectations/receipts
were accepted. Short probes also caught a vtable read using the disc address, a
prefix allowance missing nested pushes and a reload root still using its disc VA.
All were fixture corrections before accepted full evidence, with no original
instruction modification. The first synthetic guard test attempts caught generated
import/name/path typos; corrected tests pass. A private receipt-verifier string/Path typo also failed once
before correction; it executed no originals. No native playtest repair occurred.

## Evidence and reproduction

Protected per-engine receipts, expectations, synthetic images and export inventories:

```text
private/migration/{allied-disc,supplied-ra2-1006}/{scenery,terrain-types,props}/
```

Fresh execution refuses existing receipts. Replay validates engine/profile/suite,
oracle/mapping sources, exporter/assets, render data, synthetic fixtures and exact
expectation fingerprint, and cannot replace original receipts. Exported inputs
remain retained disc research inputs; archive precedence and patched promotion
remain pending. Historical disc expectations remain intact. Ten profile/evidence
guards execute no original code. Only Apple Silicon macOS is tested.

```sh
build/tools-env/bin/python tests/test_scenery_profiles.py
build/tools-env/bin/python tools/verify_scenery_mapping.py \
  --disc private/disc-allied/game.exe --patched private/official-1006-probe/game.exe
# After fresh receipts exist: native replay, no original execution.
build/tools-env/bin/python tests/compare_scenery.py \
  --exe private/official-1006-probe/game.exe \
  --native-data-exe private/disc-allied/game.exe \
  --expectations private/migration/supplied-ra2-1006/scenery/expected.json
# Repeat with compare_terrain_types.py / terrain-types and compare_props.py / props.
# For sanitizer replay, add --native build/sanitize/scenery-vectors and a separate
# --report private/migration/supplied-ra2-1006/scenery/sanitize-replay-report.json.
./run.command --light-demo
```

On a checkout without receipts, omit --expectations for fresh original execution
in the authorized Mac JIT context. Patched research requires explicit retained disc
native data. No runtime executable-read/table/dependency boundary changed. Source
installations, mounted media and Outpost 2 remain untouched.

Accepted original generation took **16.37 / 17.19 s** for scenery,
**38.34 / 39.90 s** for tree types and **21.31 / 21.96 s** for props
(disc / patched). Native comparisons took **8.70 / 8.68 s**, **31.64 / 31.72 s**
and **30.20 / 30.32 s** respectively. Whole fresh CLIs took **26.75 / 29.24 s**,
**72.67 / 75.68 s** and **55.74 / 56.29 s**. Engines ran in parallel and can
contend for CPU. Sanitizer replays including mapping/export/identity checks took
**11.81 / 15.40 s**, **42.18 / 43.53 s** and **36.54 / 36.96 s** respectively.
The checkpoint verification took **9.70 s**. Reports and separate
fresh/sanitize timing files retain the precise values. Earlier implementation and
complete inherited delivery time were not measured. No native C++ source changed;
the preceding build/owned-data/real SDL checks still cover this same native build.
Complete verification on promoted inputs remains required at the delivery boundary.
This committed checkpoint has not received independent review/acceptance.

Verification receipt: `private/migration/scenery-checkpoint-verification.json`,
created by `private/patch-inspection/verify-scenery-checkpoint.py`. Mapping receipt:
`private/patch-inspection/scenery-1006-mapping.json`. Private disassembly/discovery
remains under `private/patch-inspection/`. None is tracked or distributed.

Next: occupation/lifecycle profiles, original archive precedence and consistent
prepared/runtime promotion, followed by full applicable verification including real
SDL rendering/input on promoted data. Then planned actor traversal/drawing integration.
