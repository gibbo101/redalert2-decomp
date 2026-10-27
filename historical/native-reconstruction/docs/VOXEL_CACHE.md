# Milestone 13: ordinary lit voxel keys and successful cache reuse

[VOXEL_CACHE_1006.md](VOXEL_CACHE_1006.md) verifies this retained domain on separately
hash-selected disc and supplied RA2 1.006 engines, with protected fresh receipts,
scoped caller/input/heap/supplied-write audits and both sanitizer replays. Runtime/
data promotion remains pending; its replay commands supersede historical paths.

[SHADOW_KEYS.md](SHADOW_KEYS.md) supersedes the heading-only shadow identity for
the healthy flat stock Track Rhino and verifies Foot dispatch. Shared ownership,
nonflat/status invalidation, lifecycle and full-frame parity remain open.

October 14, 2026. Baseline: `311d65e` (milestone 12). Tested on Ivalice,
Apple Silicon macOS. Allied-disc GAME.EXE, embedded version `1.08`, image
base `0x400000`, SHA-256:

`135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743`

Every oracle verifies the complete hash before using addresses. No YR or retail
patch equivalence is assumed. This note supersedes the exact-matrix/frame lit-part
host cache in [RASTER.md](RASTER.md) and [STAGING.md](STAGING.md). The runtime
shadow key remains its separately labeled adapter. Shared ownership, original
compressed storage, failures/eviction and full actor/full-frame parity remain open.

## Result

`VoxelCache.cpp` models the original Unit body/turret key blocks and healthy lit
wrapper's successful lookup, sorting, rendering and insertion decisions. Renderer
keeps three logical indexed-frame caches for the one stock Rhino's parts. A warm
key reuses its first built indexed pixels and crop rather than comparing matrices.
The stock zero-offset turret and barrel reuse their images across body turns;
the body has a separate heading key. Lighting and house color remain final-blit
inputs and do not invalidate those indexed images.

`DisableVoxelCache` is read from the supplied HTNK rules. A diagnostic render API
can also bypass the lit cache; ordinary game controls do not expose this API.
Animated HTNK HVA files now fail explicitly because actor animation/key timing is
unrecovered. The stock body, turret and barrel each have one identity frame.
Nonzero TurretOffset and multiple VXL sections remain unsupported.

Rendering and simulation remain SDL-free. There is no dependency/preparation-table
addition. Runtime GAME.EXE reads remain hash-checked **track data only**, never
original instruction execution. No upstream or generated code was incorporated.

## Reference and exact-base evidence

Consulted redalert2-recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439`,
`docs/voxels.md` (The path of one unit, Cost) and LICENSE. Its key/miss/hit chain
and cache-disabling discussion supplied hypotheses, not stock behavior. Its HD
patches and predominantly YR addresses are excluded. YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88`, `TechnoClass.h`, `FootClass.h`
and `TechnoTypeClass.h` supplied caller/field naming leads. No header implementation
was copied; its absence of an incorporation license remains respected.
See [REFERENCES.md](REFERENCES.md) and [THIRD_PARTY.md](../THIRD_PARTY.md).

| Exact original evidence | VA |
| --- | --- |
| Unit main vtable | `0x798C90` |
| Body key block | `0x6F42F1..0x6F4327` |
| Turret key block | `0x6F445B..0x6F44AB` |
| Complete lit wrapper | `0x6C7120` |
| Healthy render / cached draw | `0x6C7900` / `0x6C7DF0` |
| Index sort/search wrapper / signed comparator | `0x6CEC70` / `0x6CECF0` |
| Original qsort / binary search | `0x76D2E0` / `0x6CED20` |
| Snapshot service, implementation excluded | `0x68F720` |
| DisableVoxelCache string / actual loader cross-reference | `0x7E0BC8` / `0x6D2E8B` |
| TurretOffset string / actual loader cross-reference | `0x7E0C0C` / `0x6D2DE2` |

The type stores DisableVoxelCache at `+0xB5A` and TurretOffset at `+0x63C`.
INI association is inspected evidence; full INI parsing/type initialization is not
executed by the oracle. Missing bool values retain the bounded native false default.
Raw disassembly/probes remain ignored under `private/voxel-cache/`.

## Recovered decisions

Body key is -1 if the supplied locomotor key is -1. Otherwise:

```text
body = (uint32(locomotorKey) << 5) | (uint32(HVAFrame) & 31)
turret = (uint32(body) & 0xFFFFFFE0) | voxelHeading(turretFacing)
if TurretOffset == 0: turret &= 0xFFFFFC1F
```

Turret also propagates body -1. Operations wrap at 32 bits; signed left-shift
overflow is avoided in C++. Existing 32-bin render-heading ties are preserved.
For the recovered flat locomotor and stock frame zero, body key is `bodyBin << 5`
and turret/barrel key is `turretBin`. This intentionally permits cross-body reuse
despite differing intermediate matrix float bits. Higher locomotor bits survive
the zero-offset mask; this does not establish arbitrary ramp/status key creation.

The lit wrapper forces key -1 when cache is absent or type disabling is set.
Lookup precedes VXL/HVA pointer validity: a warm hit still draws with unavailable
model pointers, while an invalid miss or bypass draws nothing. A hit calls cached
draw; -1 renders directly without snapshot/insertion. Healthy staging removes mask
0x2800 from ordinary flags and uses indexed flags zero, as recovered in STAGING.md.

A cacheable miss renders immediately, snapshots and appends. Unlike the shadow
wrapper, it does **not** recursively hit the newly inserted entry. Its index stays
unsorted, and an existing hot entry survives append unless capacity grows. A hot
hit skips sorting. Other lookups sort by signed int32, clear hot and binary-search;
a failed search preserves hot if no sort occurred. Capacity starts at ten and
doubles on successful growth, clearing hot. Native vectors preserve these logical
decisions; their storage is not the original compressed allocation pool.

## Differential verification

`original_voxel_cache.py` extends the hash-pinned staging/raster fixture. It runs
the actual key blocks, complete lit wrapper, signed comparator, original qsort,
binary search and index writes. Explicit healthy virtual predicates/type/house
queries, rendered rectangle, snapshot identity, cached-draw recorder and successful
allocator isolate the tested boundary. No original instruction bytes are patched.
Full Unit draw, flags/status systems and actor memory-arena/ordered-write audits
are not claimed.

Owned cases execute original flat poses, lighting and complete section rasterization,
then the original wrapper decides which logical snapshot to select. Native misses
run the real native rasterizer. Full 65,536-byte selected buffers and six crop
fields compare; warm hits retain the first build's pixels and crop. Separate supplied
indices isolate the three part caches. Snapshot encoding/pool behavior is fixture
supplied, not recovered by these comparisons.

| Matching original/native behavior | Cases |
| --- | ---: |
| Actual body/turret key blocks, boundaries and signed wrapping | 1,934 |
| Complete healthy lit wrapper/index decisions and state | 2,484 |
| Selected owned cached buffers and crops | 300 |
| Owned disabled-cache buffers and crops | 12 |
| **Behavior cases** | **4,730** |

Thirteen protocol resets initialize independent sequences, giving **4,743** results.
Wrapper sequences cover signed endpoints, growth, misses/hits/hot state, absent
or disabled caches and unavailable models. Owned sequences cover all 32 body bins,
independent turret bins, body-turn reuse and return to prior keys. All match,
including ASan/UBSan replay. Retained original suites are recorded in HANDOFF.md.

```sh
./build.command
./run.command --light-demo
./test.command --data-dir "$PWD/private/game"
build/tools-env/bin/python tests/compare_voxel_cache.py --exe private/disc-allied/game.exe
# After the headless sanitizer build in README:
build/tools-env/bin/python tests/compare_voxel_cache.py \
  --exe private/disc-allied/game.exe --native build/sanitize/voxel-cache-vectors \
  --expectations private/voxel-cache/expected.json --report private/voxel-cache-sanitize-report.json
```

Reports: `private/voxel-cache-report.json`, `private/voxel-cache-sanitize-report.json`.
Expectations: `private/voxel-cache/expected.json`. Protected read-only exports reuse
`private/staging/assets/`; source destinations, symlinks and differing replacements
are refused. Reports pin executable/native/tables/owned inputs/oracle source; replay
also pins expectations. All original content and derived research remain ignored.

Native checks cover hot-before-validity, miss/append/growth differences, warm frames,
three-part counters, fixed-turret/body-turn reuse, return, bypass, rule disabling,
source/color isolation and explicit animated-HTNK refusal. Both SDL regressions and
real-clock smoke pass. Previews are integration QA only, not original observations.

## Remaining boundaries and next measurements

Caches remain per renderer/part for one healthy stock actor, using logical uncompressed
frames. Cross-actor/type sharing, original compressed snapshots/global pool,
allocation failures, eviction/destruction, runtime shadow key construction, actor
invalidation, animated/rocking/ramp/height/pitch states and complete draw prechecks
remain open. The cache contract above is recovered; all lifecycle behavior is not.
Named house assignment, visibility, camera zoom, input/UI and direct routes retain
their existing host policies. Full-frame parity is unverified.

Next bounded slice: **flat actor shadow-key construction and dispatch**. Trace
the Foot shadow caller, locomotor key and type ShadowIndex in this exact base build,
then verify key transformation and draw arguments before replacing the runtime's
heading-only shadow identity. Preserve lit/raster/staging/color/light oracles.

When Windows is available, pin executable/hash, map/cell/elevation, house/scheme,
detail, pixel format and console versus RDP. Hold a Rhino turret fixed, turn its
body through all 32 bins, then repeat in reverse order; independently sweep the
turret and return to old headings. Log key inputs/outputs, per-part index identity,
hit/miss/snapshot dispatch, sorted/hot state and selected pixel/crop hashes. Repeat
after source/color changes, panning away/back and adding a second identical tank.
This separates verified key-based reuse from unknown shared ownership/invalidation.
Screenshots alone cannot settle that boundary. Original-game captures remain absent.

Only Apple Silicon macOS is tested. Scenery, pathfinding, combat, economy, AI,
campaigns, multiplayer, audio, original saves and Yuri's Revenge remain subsequent
work; the active full-game goal is incomplete.
