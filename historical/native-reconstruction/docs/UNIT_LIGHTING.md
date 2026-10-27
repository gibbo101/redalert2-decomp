# Milestone 12: ordinary Rhino cell and house lighting

[VOXEL_CACHE.md](VOXEL_CACHE.md) supersedes the historical exact-matrix lit-part
cache with verified ordinary actor keys and successful wrapper/index reuse.
Runtime shadow identity, shared pool/lifecycle and full-frame parity remain open.

[UNIT_LIGHTING_1006.md](UNIT_LIGHTING_1006.md) extends this bounded domain to the
supplied RA2 1.006 engine with fresh evidence on both profiles and explicit
RGB565 initializer/caller/input/heap inspection. Runtime/data promotion remains
pending; preserve the historical disc evidence below.

October 14, 2026. Baseline: `219a3e2` (committed milestone 11). Tested on
Ivalice, Apple Silicon macOS. Allied-disc GAME.EXE, embedded version `1.08`,
image base `0x400000`, SHA-256:

`135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743`

Every original oracle verifies the full hash before using addresses. No YR or
retail patch equivalence is assumed. This note supersedes the current-cell tint /
normalized terrain brightness / all-entry player-converter adapter described in
[STATIC_LIGHT.md](STATIC_LIGHT.md) and [MAP_LIGHTING.md](MAP_LIGHTING.md).
Full actor draw, house initialization/lifetime, weather and whole-frame parity
remain outside the claim.

## Result

The healthy flat Rhino uses its coordinate-derived cell's **unnormalized ambient**
plus rules **ExtraUnitLight** for final blit brightness. Final colors come from the
owning house's ColorScheme converter, independently of that cell's normalized tint.
Ordinary house converters use neutral RGB, 53 shade rows and a distinct affected
palette mask. The prototype keeps a supplied named-color registry for its single
logical house. CLI/C color assignment remains a host policy; original house IDs,
creation and the original paired one-row/53-row scheme registry are not reconstructed.

`UnitLighting.cpp` contains the recovered portable inputs/selection/converter
operations. `GameAssets` requires explicit `[AudioVisual] ExtraUnitLight` and retains
the supplied double. Renderer quantizes it and owns the house converters separately
from terrain converters. Local static-light toggles change cell brightness and
terrain colors without recreating the unit palette or its indexed geometry/shadow.
Simulation remains unchanged and SDL-free. No new dependency or derived data file
is added. Runtime GAME.EXE reads remain hash-checked **track data only**.

## Reference and original evidence

Consulted redalert2-recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439`,
`docs/voxels.md`, Following the image onto the battlefield, and LICENSE. Its
house-palette / final-lighting separation supplied a hypothesis; its mostly YR
addresses and HD patches are not our oracle. YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88`, `TechnoClass.h` GetDrawer,
`ConvertClass.h`, `RulesClass.h` ExtraUnitLight and `ScenarioClass.h` supplied
naming/caller leads. No upstream, header or generated code was incorporated.
See [REFERENCES.md](REFERENCES.md) and [THIRD_PARTY.md](../THIRD_PARTY.md).

| Exact-build evidence | VA |
| --- | --- |
| Actual ExtraUnitLight multiply / FTOL block | `0x63D76E..0x63D779` |
| Rules ExtraUnitLight store / field | `0x63D779`, `+0x1418` |
| Actor location-to-cell getter | `0x41B320` |
| Unit caller selecting that getter | `0x6F59FB..0x6F5A12` |
| Ordinary Unit brightness block | `0x6F5B21..0x6F5B8C` |
| Actual map cell lookup | `0x5453B0` |
| Complete actor brightness-effects helper | `0x6CCDF0` |
| Effects/final draw dispatch, inspected | `0x6F4C28..0x6F4C94` |
| Final house / scheme / converter selection block | `0x6F4013..0x6F4034` |
| Complete original ordinary blitter selection | `0x485880` |
| Complete ColorScheme converter recreation | `0x65A9A0` |
| Complete palette remap / LightConvert construction | `0x65A4F0`, `0x5368F0` |
| Full scalar palette update / ordinary unit span | `0x536B30`, `0x488650` |
| Theater scheme input block, inspected | `0x519605..0x519627` |
| Scheme 1/53-row load calls, inspected | `0x63EE52..0x63EE7B` |
| House scheme affected mask | `0x7DC228` |
| Alternate global converter update, inspected | `0x51FEF0` |

The main Unit vtable is `0x798C90`. Actor virtual `+0x1A0` selects `0x41B320`;
its `+0x2C0/+0x2C4` are depth/gradient, not brightness. Original pushes before
those virtual calls prepare subsequent surface-blit arguments. Avoid treating them
as virtual-call parameters. Interface vtables preceding the main table have
nonzero object offsets and are not interchangeable.

Original final lookup is actor `+0x1B4` → house `+0x15F40` → global scheme pointer
array `0xA9E9E4` → scheme `+0x30C` converter. Runtime models that selection with
portable registry indices, not original memory layouts or guest pointers.
Raw probes/disassembly are ignored under `private/unit-light/`.

## Numeric behavior

ExtraUnitLight uses `truncate(binary64 value * 1000)` with **no +0.1 bias**.
The supplied `.2` becomes **200**. Binary64 decimal representation and recovered
rounding remain consequential: `-0.15` becomes **-149**, not an assumed -150.
Native code scopes/restores round-toward-zero and retains strict compilation.
The numeric oracle runs the actual loader block, not original INI string parsing.

Actor cell coordinates divide signed X/Y leptons by 256 toward zero, then narrow
to signed words. The unit brightness block reads signed cell ambient `+0x10A`,
not normalized terrain `+0x10C`. If cell flags `+0x140 & 0x10000` and actor virtual
`+0x54` returns false, it subtracts **500**, then adds rules ExtraUnitLight with
32-bit wrap. This flag/predicate's semantics remain unnamed. The complete effects
helper preserves input normally; actor `+0xD8 & 2` returns 2000 for input ≤1500,
otherwise 500. These branches are tested; the runtime healthy profile supplies
zero flags and does not instantiate those status systems.

For spawn (33,86), elevation 4, ambient 1112 plus extra 200 gives unit brightness
**1312**. With the demo INGALITE two cells east, it becomes **1491**. Local source
RGB contributions affect terrain normalization/converters, but do not become
ordinary house-converter tint. Ordinary theater initialization supplies UNITTEM.PAL,
TEMPERAT.PAL and RGB **1000/1000/1000**. Full tested scheme recreation preserves
that neutral tint when the two original alternate-light selectors are inactive.

The house affected mask excludes indices **240–254**, retaining 255 and all other
entries. Excluded entries use the existing converter's early neutral ramp. Player
remap still replaces only 16–31. The full constructor/update comparisons verify
complete 53×256 RGB565 tables, including the excluded entries.

Unit brightness may exceed 2000. The actual span clamps negative input to zero,
calculates `brightness * 261 / 2048`, and caps its bin at **254**. Existing alpha
row division by 32258 remains unchanged. Native composition now accepts positive
brightness through 65535; arbitrary overflowing span multiplication is excluded.
All 256 alpha values are tested at each selected brightness, including 2200/65535.
Recovered coordinate bounds are ±2^20 leptons; numeric-load inputs are finite ±10.
The isolated brightness helper tests full signed-word ambient and int32 extra
wrap; this does not broaden supported runtime rules/actor profiles.

## Verification

`tests/original_unit_light.py` executes unchanged hash-pinned original instructions.
Numeric tests supply a double through an existing original load instruction,
invalidate its translated cache and check both stop boundaries. The coordinate
getter, ordinary brightness block, actual map lookup, effects helper, house lookup
and blitter selection execute. Map pointer storage, actor/type/house records and
the unnamed virtual predicate are explicit fixtures. Full Unit draw is excluded.

Converter cases execute complete scheme recreation, copy/ramp, LightConvert and
blitter construction plus scalar palette update. Heap/free and registry storage
are successful fixtures. A warm alpha map is generated by unchanged original
instructions; its lookup/refcounts execute. Full initial ColorScheme/house creation,
allocation failure, destruction and global lifetime are excluded.

Combined cases execute the original cell kernel, unit brightness/effects, selected
house-table identity and complete final surface copy. Source pixels, location,
depth and visibility are supplied. Full RGB565 and unchanged depth planes compare
by SHA-256. These are isolated combined boundaries, not an original full actor or
whole-frame run. No original-game recording or full actor-arena/ordered-write
audit is claimed.

| Matching original/native cases | Count |
| --- | ---: |
| Actual ExtraUnitLight numeric block, decimal boundaries/neighbors | 1,545 |
| Complete location-to-cell getter, signed/boundary coordinates | 256 |
| Ordinary brightness and complete effects helper | 630 |
| House converter / actual blitter selection with permuted identities | 512 |
| Owned ExtraUnitLight | 1 |
| Complete owned house converter tables, all 19 supplied names | 19 |
| Saturated brightness, all 256 alpha inputs per case | 109 |
| Combined cell/house complete color/depth surfaces, including 54 radius-crossing positions | 182 |
| Numeric repeatability after constructor/surface calls | 3 |
| **Total** | **3,257** |

All match; ASan/UBSan expectation replay also passes. Retained original suites,
native/owned-data and SDL regressions are recorded in [HANDOFF.md](HANDOFF.md).
Native integration checks verify unchanged palette identity across source toggles
and radius crossings, local tint separation, restored complete frames and unchanged
simulation/coverage/shadow reuse. Native previews are visual QA only.

```sh
./build.command
./run.command --light-demo
./test.command --data-dir "$PWD/private/game"
build/tools-env/bin/python tests/compare_unit_light.py --exe private/disc-allied/game.exe \
  --expectations private/migration/allied-disc/unit-light/expected.json
# After the headless sanitizer build in README:
build/tools-env/bin/python tests/compare_unit_light.py \
  --exe private/disc-allied/game.exe --native build/sanitize/unit-light-vectors \
  --expectations private/migration/allied-disc/unit-light/expected.json \
  --report private/migration/allied-disc/unit-light/sanitize-report.json
```

Reports: `private/unit-light-report.json`, `private/unit-light-sanitize-report.json`.
Expectations and protected read-only owned exports: `private/unit-light/`.
They pin executable/native/table/owned-input/oracle-source identities. Exports
reuse the existing source-path/symlink/different-content safeguards. No proprietary
assets, tables, executable instructions or raw research are tracked or shipped.

## Open work and original-game measurements

Named color assignment, converter storage/lifetime, healthy zero flags, fixed
visibility 127, demo source placement and terrain invalidation are explicit host
policies. Weather/alternate tint, bridges/elevated branches, sinking/other units,
status transitions, full draw ordering and original house initialization are open.
This milestone establishes ordinary input selection, not full actor invalidation.

Next bounded recovery: actor voxel cache-key construction and invalidation, retaining
these cell/house and existing raster/staging/shadow tests. Determine what keys depend
on body/turret heading, animation, type/locomotor state and how changes invalidate
shared entries before replacing the native matrix/frame caches.

When Windows is available, pin the exact executable/hash, map/cell/elevation,
player house/scheme, source settings, graphics detail, pixel format and RDP versus
console session. Move one healthy Rhino across the source radius and back, toggle
the source with the tank stationary, then pan away/back. Log actor coordinate getter,
cell +0x10A/+0x10C/+0x110..+0x114, rules +0x1418, final brightness, house/scheme/
converter identity and converter update calls. Capture RGB565 and visibility alpha
separately. Ordinary source intensity should change brightness without changing
house tint/identity; unexplained converter writes or pixels identify remaining actor,
weather or lifetime integration. Screenshots alone do not establish that boundary.

Only Apple Silicon macOS is tested. Full-game reconstruction remains active;
pathfinding, scenery, combat, economy, AI, campaigns, multiplayer, audio, original
saves and Yuri's Revenge remain subsequent work.
