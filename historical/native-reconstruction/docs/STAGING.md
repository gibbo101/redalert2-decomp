# Milestone 9: indexed unit staging and bounded shadow cache decisions

[STAGING_1006.md](STAGING_1006.md) verifies this retained domain on separately
hash-selected disc and supplied RA2 1.006 engines, with fresh protected receipts,
caller/input/write audits and both sanitizer replays. Runtime/data promotion remains
pending; its replay commands supersede the historical paths below.

[SHADOW_KEYS.md](SHADOW_KEYS.md) supersedes the heading-only shadow identity for
the healthy flat stock Track Rhino and verifies Foot dispatch. Shared ownership,
nonflat/status invalidation, lifecycle and full-frame parity remain open.

[VOXEL_CACHE.md](VOXEL_CACHE.md) supersedes the historical exact-matrix lit-part
cache with verified ordinary actor keys and successful wrapper/index reuse.
Runtime shadow identity, shared pool/lifecycle and full-frame parity remain open.

[UNIT_LIGHTING.md](UNIT_LIGHTING.md) supersedes the historical unit cell/house
lighting adapter with verified ordinary brightness and house-converter selection.
House initialization/lifetime and full actor/full-frame parity remain open.

[STATIC_LIGHT.md](STATIC_LIGHT.md) extends map lighting with one bounded static
source and immediate updates. Source lifecycle, unit/house association, visibility
and full-frame parity remain open; historical milestone limits below are retained.

[MAP_LIGHTING.md](MAP_LIGHTING.md) supersedes the direct ambient/elevation-to-alpha
adapter with verified ordinary cell lighting and separate visibility alpha. Source
actor creation, fog and unit/house association remain outside that claim. Historical
milestone limits below are retained for their original evidence.


October 12, 2026. Baseline: `78333ac` (committed milestone 8). Tested on Ivalice,
Apple Silicon macOS. The supplied Allied-disc base GAME.EXE is embedded version
`1.08`, image base `0x400000`, SHA-256:

`135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743`

Every oracle checks that complete hash before using addresses. This note supersedes
manual stencil assembly in [SHADOW_COLOR.md](SHADOW_COLOR.md) and independent
part-to-world blits in [COMPOSITION.md](COMPOSITION.md). Earlier pixel/pose/shadow
oracles remain required. Full actor, global cache pool and whole-screen parity
are not established.

## Result and architecture

`UnitStaging.cpp` assembles original lit body/turret/barrel buffers on a 256×256
indexed surface. Its one-shade converter uses the original theater palette,
TEMPERAT.PAL, independently of ISOTEM.PAL terrain lighting and UNITTEM.PAL player
colors. Parts use the original directional order and anchor (128,128). One final
world blit applies the selected player palette, supplied alpha and ordinary depth.
The body shadow follows that blit and samples the completed indexed staging plane.

`ShadowCache.cpp` implements the original wrapper/index's successful-allocation
choices: suppression, bypass, hot hit, signed sort/search, guarded miss, insertion
and subsequent cached draw. Native vectors hold logical RasterFrames; they do not
reproduce the original compressed allocation pool. The renderer's heading identity
and cache lifetime are bounded host policies, not complete actor key recovery.

Rendering remains SDL-free. SDL only displays the portable framebuffer and handles
prototype controls. Simulation is unchanged. No preparation file, dependency or
runtime executable-read scope is added. GAME.EXE remains hash-checked track data
only; research Unicorn execution is never part of the native application.

## Reference lead and original evidence

Consulted redalert2-recomp commit `eebcf725ef99f942a8f9a5e0437a8a6154d7d439`:
`docs/voxels.md` (Following the image onto the battlefield, Shadows, Cost),
`run_lift.py` HD_VOXEL_PATCHES and `docs/testing.md`. Its staging/remap description
and miss→render→cache→hit explanation supplied hypotheses. Those mostly YR/Steam/EA
addresses, cache-disabling patches and HD behavior are not stock base-disc evidence.
The MIT license/generated-game-code exclusion was checked; no code was incorporated.
See [REFERENCES.md](REFERENCES.md) and [THIRD_PARTY.md](../THIRD_PARTY.md).

| Inspected/executed base evidence | VA |
| --- | --- |
| Unit staging setup and anchor | `0x6F422E..0x6F42B3` |
| Staging surface/converter creation | `0x6FF370..0x6FF419` |
| Theater palette filename/load/6-bit expansion | `0x519290..0x51950A` |
| Staging palette global / surface / converter | `0x820130` / `0xAB8064` / `0xAB8068` |
| Full Convert constructor / blitter initialization | `0x483430` / `0x4838E0` |
| Closest-color search / RGB distance | `0x5FAC40` / `0x634250` |
| Blitter selection / indexed span | `0x485880` / `0x4860F0` |
| Part flags remove supplied mask | `0x6C71E6..0x6C71F4` |
| Uncached dirty union / cached equivalent | `0x6C7329..0x6C742A` / `0x6C7ECD..0x6C7FE2` |
| Empty dirty initializer / current dirty rectangle | `0x6EEF00` / `0xAB7EF0` |
| Final Unit surface-copy routine / ordinary draw block | `0x6F3F10` / `0x6F4034..0x6F41A0` |
| Complete surface copy / indexed part wrapper | `0x434A00` / `0x49EF70` |
| Actor final dispatch, restore, shadow, staging clear | `0x6F4C56..0x6F50C5` |
| Full shadow wrapper / render / cached draw | `0x6C7600` / `0x6C7C30` / `0x6C7DF0` |
| Signed index comparator / binary search / original qsort | `0x6CECF0` / `0x6CED20` / `0x76D2E0` |
| Original compressed snapshot, inspected only | `0x68F720` |
| NoShadow / DisableShadowCache INI field stores | `0x6D272B` / `0x6D2ED1` |

The theater record at `0x785B98` supplies TEMPERAT for `%s.PAL`; the original loader
expands its 6-bit channels into global `0x820130`. UNIT%s.PAL is loaded separately
into `0x820D30`. This association is inspected filename/caller evidence, not a full
executed theater initialization or house assignment. The owned TEMPERAT.PAL hash is
`5903b69868b84f494cfbb4e7100398015ef9775b37726019a0d7b5fb6cb33b55`.
Raw references, probes and disassembly remain ignored under private/presentation9/.

## Consequential recovered behavior

The single-shade byte converter sets map[0]=0. For indices 1–255, it searches all
256 destination colors using:

`2*abs(Ra-Rb) + 4*abs(Ga-Gb) + 3*abs(Ba-Bb)`

Only strictly smaller distance updates the winner, so the first palette entry
wins a tie. Same-palette conversion can map duplicate colors to earlier indices.
This is weighted Manhattan distance, not squared Euclidean distance or identity.

The part call's 0x2800 is a mask to **remove**. The voxel wrapper ORs 0x800 into
its ordinary flags, then removes that mask; healthy indexed staging therefore
selects flags **0**. It skips source zero but writes remap[index] for every nonzero
source, even when the result is zero. That write erases an earlier staged pixel.
The byte span ignores world depth; depth/alpha apply only to the final unit image.

A nonempty dirty rectangle expands left/top normally. Extending right/bottom adds
one extra pixel to that dimension; equal edges add none. An empty current rectangle
uses the new rectangle directly; an empty new rectangle preserves nonempty current
bounds. Final placement is `world + dirty.origin - (128,128)`. Its assembled height
controls the flat scanline depth phase, so ordinary bounding-box union is insufficient.
The complete original 0x434A00 surface-copy path matches the native flat blit,
including linked clipping and nonzero clip origins, for the tested unscaled domain.

Shadow wrapper gates run before lookup: nonzero actor +0x1B8 (semantic name still
unrecovered), type NoShadow +0xB48, or nonzero first model byte suppress drawing.
Key is signed int32; **-1 bypasses**. Absent cache or DisableShadowCache +0xB5B
forces that bypass. A bypass renders directly even when the rebuild flag is false.

Cacheable lookup first checks the hot entry. Otherwise it sorts dirty entries by
signed key with the original comparator/qsort, resets hot, and binary-searches.
A failed search leaves an existing hot entry intact if no sort occurred. A hit
uses flags 0x2001 and brightness 1000. A cacheable miss returns without rendering
when build is disallowed. An allowed miss renders with deferred blit, snapshots,
appends and recursively looks up/draws the new entry. Capacity begins at ten and
doubles; successful reallocation clears hot. The native implementation preserves
these observable key/state/dispatch decisions, using readable vector storage.

## Differential verification

`tests/original_staging.py` extends the existing hash-pinned PE/VXL/BSurface fixture.
The **complete Convert constructor**, actual blitter initialization/selection,
indexed surface wrapper and final surface-copy routine execute unchanged original
instructions. Allocation/registry storage are bounded successful fixtures; original
RGB/HSV/search/span and BSurface methods execute. Dirty union executes its isolated
uncached block; cached equivalence is inspection evidence.

Assembled cases run original poses, lighting and full rasterization for three owned
stock parts, original part order, real indexed blits, dirty union, staged-stencil
shadow projection/plot/crop, complete final RGB565 surface copy and shadow world
blit. Body headings cover all 32 bins, with independent turret headings including
boundary offsets. Two supplied viewport/depth/alpha profiles compare entire planes.
The final palette/alpha/depth are explicit fixture inputs; full house/map-light
integration is not verified by these cases.

The shadow decision oracle executes **all of 0x6C7600**, its original comparator,
qsort and binary search. Explicit services return a supplied type, record render
arguments, provide a successful snapshot identity, and record cached-blit flags
and brightness. A successful allocator supplies index growth; original index/state
writes and recursive lookup execute. This verifies decisions and index ordering,
not original snapshot pixel encoding, pool eviction or failure recovery. Model
suppression uses a supplied header byte. Original instruction bytes are never patched.

| Matching original/native behavior | Cases |
| --- | ---: |
| Complete one-shade converters (owned, duplicate, ties, random palettes) | 12 |
| Original dirty unions (empty, ties, extension, signed positions) | 518 |
| Complete clipped transparent/remapped indexed surfaces | 128 |
| Complete final surface-copy RGB565/depth planes | 128 |
| Complete assembled unit/staged-shadow/world planes | 128 |
| Full successful shadow wrapper/index decisions and state | 1,686 |
| **Behavior cases** | **2,600** |

Three additional reset commands initialize independent cache sequences. Thus the
runner reports 2,603 protocol results. Cache sequences cover INT32 endpoints,
negative keys, hits without build permission, missed disabled builds, each gate,
absent/disabled cache, repeated keys and capacity growth. All match. Final depth
planes remain unchanged. Existing movement and presentation/raster/composition/
shadow-color suites were rerun and pass.

```sh
./build.command
./test.command --data-dir "$PWD/private/game"
build/tools-env/bin/python tests/compare_staging.py --exe private/disc-allied/game.exe
build/native/presentation-check private/game build/staging
# Instrumented native replay after the sanitizer build in README:
build/tools-env/bin/python tests/compare_staging.py \
  --exe private/disc-allied/game.exe --native build/sanitize/staging-vectors \
  --expectations private/staging/expected.json --report private/staging-sanitize-report.json
```

Exports refuse source-tree destinations, symlinks and differing existing data.
Owned inputs, complete buffers, commands and original expectations stay ignored
under private/staging/. Reports private/staging-report.json and
private/staging-sanitize-report.json pin source/input/table/native hashes; cached
replay also pins the expectations file. ASan/UBSan native/owned-data checks and
both new staging and retained shadow/color expectation replays pass. There are
123 synthetic C++ checks, two disc-reader tests and seven preparation/export tests.
The final SDL 170-frame input regression and real-clock smoke pass on this Mac.
Native previews are integration QA only; no original-game capture was performed.

## Remaining adapters and next measurements

Native staging clears all 65,536 bytes each draw. The original initializes once,
then clears its saved dirty area after shadows. Logical pixels match when no other
actor shares or contaminates staging; shared actor scheduling is not recovered.
NoShadow/DisableShadowCache named overrides are read for the bounded HTNK profile;
absent values use native false defaults rather than a verified full type constructor.
Alternate ShadowIndex/UseTurretShadow profiles are refused, not implemented.

The renderer uses the flat heading identity to partition its single-frame body
shadow cache, keeps it per renderer, and owns logical pixel vectors. Full actor key
seeds (animation, ramp, height/type/locomotor contributions), cross-actor sharing,
invalidation, compressed snapshot layout, global pool eviction and allocation/
snapshot failure recovery remain unverified. An already cached key reuses its
original build's stencil even when the turret later changes, matching the tested
wrapper contract; whole-actor invalidation could affect that behavior. Lit parts
retain the exact-matrix/frame host cache. Nonidentity/animated/rocking poses,
special draw/status branches and general shadow selection are outside this profile.

The next recommended bounded milestone is **map lighting inputs**: trace original
map ambient/tint/height-to-alpha and LightSources at the chosen flat cells, and
verify those inputs before changing the current host lighting adapter. House-ID
palette association and full actor cache keys can follow independently.

When Windows testing is available, record executable hash, map/cell/elevation,
player color, resolution/pixel format and RDP versus console session. Capture a
stationary Rhino with a fixed body while cycling turret headings; repeat with a
cold cache, return to prior headings, pan away/back, and change camera position.
Compare shadow masks/part overlap/palette pixels and log cache key/invalidation
calls. This distinguishes wrapper reuse from actor/pool invalidation. Compare flat
cells with different map lighting and a cliff to constrain the remaining lighting
and depth/status integration. Screenshots alone do not establish routine fidelity.
Windows/Linux support, full-frame parity, pathfinding, combat, AI, campaigns,
multiplayer, audio, saves and Yuri's Revenge remain unclaimed/deferred.
