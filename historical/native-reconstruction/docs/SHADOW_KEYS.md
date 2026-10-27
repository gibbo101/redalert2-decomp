# Milestone 14: flat Unit shadow keys and Foot dispatch

[SHADOW_KEYS_1006.md](SHADOW_KEYS_1006.md) verifies this retained domain on separately
hash-selected disc and supplied RA2 1.006 engines, with fresh protected receipts,
scoped caller/input/heap/point-write audits and both sanitizer replays. Runtime/data
promotion remains pending; its replay commands supersede historical paths.

October 14, 2026. Baseline: `fa6a773` (milestone 13). Tested on Ivalice,
Apple Silicon macOS. Allied-disc GAME.EXE, embedded `1.08`, image base
`0x400000`, SHA-256:

`135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743`

Every oracle checks the complete hash before addresses. This note supersedes the
heading-only runtime shadow identity in [STAGING.md](STAGING.md) and
[VOXEL_CACHE.md](VOXEL_CACHE.md), for the healthy flat stock Rhino only. Original
compressed storage, shared ownership, invalidation/lifecycle, nonflat/status
branches and full-frame parity remain open. No YR build equivalence is assumed.

## Result and original evidence

`ShadowKeys.cpp` recovers the Unit seed transformation followed by the flat Drive
shadow matrix's key packing. Renderer uses that identity around the existing
verified shadow-wrapper/cache and mask/blit kernels. Stock Track HTNK uses
`key = (bodyBin << 11) | bodyBin`, independent of turret heading and low body-frame
bits. This is a bijective replacement of the old heading-only identity for this
single-frame actor; no visible stock-frame change is expected from renaming keys.

The complete Foot shadow dispatcher checks locomotor presence and eligibility,
adds its screen offset with 32-bit wrapping, and forwards the other arguments
unchanged. The native flat profile supplies the recovered Drive predicate 1 and
zero ground-relative Shadow_Point, retaining the existing world placement.

Consulted redalert2-recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439`,
`docs/voxels.md` (The path of one unit, Shadows, Cost) and LICENSE; YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88`, `Drawing.h` key commentary,
`FootClass.h`, `Interfaces.h`, `LocomotionClass.h`, `ObjectTypeClass.h`,
`TechnoTypeClass.h` and `GeneralDefinitions.h`. Shadow interfaces and type/key
names were hypotheses. Exact-base callers, default branches and enum names were
independently recovered. No upstream/header/generated code was incorporated.
See [REFERENCES.md](REFERENCES.md) and [THIRD_PARTY.md](../THIRD_PARTY.md).

| Exact-base evidence | VA |
| --- | --- |
| Unit body-to-shadow seed extraction | `0x6F4327..0x6F4346` |
| Unit type/point seed and actual shadow matrix call | `0x6F4D03..0x6F4DC9` |
| Complete Drive Shadow_Matrix / base pose | `0x4A00D0` / `0x53B160` |
| Complete Drive shadow predicate / point | `0x53B570` / `0x53B250` |
| Complete Foot shadow dispatcher | `0x4C94F0` |
| Unit shadow model/cache/section selection, inspected | `0x6F5086..0x6F50B5` |
| Unit SpeedType default block | `0x6FF65A..0x6FF678` |
| SpeedType enum parser/table, inspected | `0x482CC0` / `0x7BE9DC` |
| SpeedType / Crusher / BalloonHover loader stores, inspected | `0x6D03EC` / `0x6D2538` / `0x6D25CE` |

Type fields: SpeedType `+0x5A4`, Crusher `+0xAF3`, BalloonHover `+0xB1A`,
ShadowIndex `+0x6F8`. Unit final call selects type body model `+0xB0` and shadow
index `+0x23C`. Those model/cache/section associations are inspected caller
evidence, not execution of the full Unit renderer. Native retains body section 0,
as already bounded in SHADOW_COLOR.md. Raw disassembly is ignored under
`private/voxel-cache/next-*shadow*` and `next-*speed*` / `next-unit-track-flag.txt`.

## Consequential branches

The earlier body key supplies a ten-bit shadow seed:

```text
seed = (bodyKey >> 5) & 1023
if BalloonHover or SpeedType == Track(1) or SpeedType == Wheel(2):
    input = seed
else:
    input = (seed << 5) | ((Shadow_Point.y - 16) & 31)
flat Drive output = (input << 11) | voxelHeading(bodyFacing)
```

Original arithmetic shift plus mask is equivalent to the native unsigned shift
plus mask for those ten bits. All packing uses uint32 wrapping. The general
point-dependent branch and the direct Track/Wheel/BalloonHover branch are tested
with explicit metadata and flat matrices; this does not implement their other
locomotors, airborne behavior or alternate actor placement. Body key -1 is masked
to seed 1023 here; blindly propagating lit -1 would differ from the original block.
Drive tilt/timer invalidation can independently force -1 and remains excluded.

SpeedType default -1 becomes **Track=1 when Crusher is true**, otherwise **Wheel=2**;
an existing explicit type is preserved. Original enum strings/table independently
establish those numeric names. Stock HTNK has explicit Crusher=yes and no SpeedType
override, so it takes the direct Track branch. The false-default Crusher and
BalloonHover constructor stores and INI associations were inspected; complete
constructors/INI parsing are excluded. `unitSpeedTypeDefault` belongs to the asset
boundary. Runtime accepts Track and rejects other type profiles/BalloonHover rather
than silently apply this stock profile to unsupported units.

Foot returns without drawing for absent locomotor or predicate byte other than
**exactly 1**. It copies the supplied location, obtains Shadow_Point, adds both
components with low-32-bit wrapping, then calls the shadow wrapper. All ten other
forwarded arguments are checked unchanged by the original recorder. Real flat
Drive returns predicate 1 and point (0,0) with supplied ground-relative actor
height zero. Ground-relative height is separate from map-elevation world Z.

## Differential verification

`original_shadow_keys.py` runs actual Unit seed blocks, complete flat Drive matrix
and base pose. A supplied zero-ramp map cell and virtual point result isolate that
boundary. Matrix float32 bits and keys compare. The actual Unit type-default block
runs on supplied fields. Complete Foot tests supply virtual predicate/point results
and record the final wrapper; four additional cases run the actual flat Drive
predicate/point and original height conversion with only actor height zero supplied.
No original instruction bytes are patched.

Owned cases run original body VXL loading, shadow poses, occupied-column plotting
and crop calculation against supplied indexed stencils. The original successful
shadow wrapper selects a logical snapshot identity. Native uses the recovered keys,
the actual ShadowCache and native mask rasterizer on misses. Complete masks and six
crop fields match, including warm reuse with changed stencils. This verifies the
combined stated boundaries, not compressed snapshots or full actor invalidation.

| Matching original/native behavior | Cases |
| --- | ---: |
| Unit seed branches and flat Drive keys/matrix bits | 1,502 |
| Actual Crusher-dependent Unit SpeedType default block | 24 |
| Complete Foot with real flat Drive predicate/point | 4 |
| Complete Foot with supplied virtual results and forwarding recorder | 544 |
| Selected owned cached shadow masks and crops | 129 |
| **Behavior cases** | **2,203** |

One reset gives **2,204 protocol results**. Signed endpoints, heading ties,
body-frame bit removal, branch metadata, default sentinels, absent locomotors,
noncanonical predicate bytes and wrapped screen additions are included. Owned
sequences cover every body bin and repeated bins/stencils. All match, including
ASan/UBSan replay. Complete actor memory-arena/ordered-write audits are not claimed.

```sh
./build.command
./run.command --light-demo
./test.command --data-dir "$PWD/private/game"
build/tools-env/bin/python tests/compare_shadow_keys.py --exe private/disc-allied/game.exe
# After the headless sanitizer build in README:
build/tools-env/bin/python tests/compare_shadow_keys.py \
  --exe private/disc-allied/game.exe --native build/sanitize/shadow-key-vectors \
  --expectations private/shadow-keys/expected.json --report private/shadow-key-sanitize-report.json
```

Reports: `private/shadow-key-report.json`, `private/shadow-key-sanitize-report.json`.
Expectations: `private/shadow-keys/expected.json`. Protected owned exports reuse
`private/staging/assets/`. Reports pin executable/native/tables/owned inputs/oracle
source; replay pins expectations too. Original files/research remain ignored.
No dependency/prepared table is added; runtime GAME.EXE reads remain track data
only. Simulation stays SDL-free and unchanged. Unicorn remains research-only.

Native tests cover key differences/branches, type default, wrapped Foot placement,
eligibility, cache bypass/type disabling, NoShadow suppression and unchanged stock
frames. Unsupported type profiles fail explicitly. SDL and sanitizer checks pass;
native previews remain integration QA only. Only Apple Silicon macOS is tested.

## Open work and next measurements

Full Unit shadow prechecks, actor altitude/status/bridge offsets, nonflat matrices,
Drive tilt/timer invalidation, animated actors, alternate shadow selection, shared
type ownership and original compressed cache/pool lifetime remain open. Key naming
alone does not establish those systems or whole-frame parity.

The next bounded presentation slice is **one original map terrain object and its
SHP image**. Recover the asset format and ordinary placement/palette/depth draw for
one stock tree already recorded in the map, before expanding scenery or animation.
Keep flat movement and voxel/light/cache oracles unchanged. Omitted objects still
retain the conservative route-exclusion policy; original occupation/pathfinding
needs separate recovery.

When Windows is available, pin executable/hash, stock HTNK type/defaults, cell and
elevation, headings, house color, pixel format and console/RDP session. Log body
key, extracted seed, SpeedType/Crusher/BalloonHover, Shadow_Point, shadow matrix key,
type model/cache/ShadowIndex and Foot location before/after adjustment. Sweep all
body bins with a fixed turret, then revisit bins with changed turret/stencil and
after panning. Add separate bridge/height/rocking observations to constrain the
excluded branches. Lossless masks/crops and recorded keys resolve more than
screenshots alone. No original-game capture or Windows runtime claim is made here.

The full-game goal remains incomplete. Scenery, pathfinding, combat, economy, AI,
campaigns, multiplayer, audio, original saves and Yuri's Revenge remain later work.
