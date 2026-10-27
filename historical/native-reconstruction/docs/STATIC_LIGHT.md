# Milestone 11: one static light source

[STATIC_LIGHT_1006.md](STATIC_LIGHT_1006.md) adds independently mapped and executed
RA2 1.006 coverage for the retained 2,574-result domain, both sanitizer replays
and scoped caller/input/write audits. Runtime/data promotion remains pending;
the historical disc evidence below retains its identity.

[VOXEL_CACHE.md](VOXEL_CACHE.md) supersedes the historical exact-matrix lit-part
cache with verified ordinary actor keys and successful wrapper/index reuse.
Runtime shadow identity, shared pool/lifecycle and full-frame parity remain open.

[UNIT_LIGHTING.md](UNIT_LIGHTING.md) supersedes the historical unit cell/house
lighting adapter with verified ordinary brightness and house-converter selection.
House initialization/lifetime and full actor/full-frame parity remain open.

October 12, 2026. Baseline: `8fd8981` (committed milestone 10). Tested on Ivalice,
Apple Silicon macOS. The Allied-disc base GAME.EXE is embedded version `1.08`,
image base `0x400000`, SHA-256:

`135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743`

Each oracle checks the entire hash before using addresses. No YR or retail-patch
equivalence is assumed. This note extends [MAP_LIGHTING.md](MAP_LIGHTING.md) with
bounded source creation, immediate activation/deactivation and terrain converter
decisions. It corrects the earlier unknown counter/threshold interpretation:
**the gate is graphics detail, not elapsed time or a simulation frame.**
Fog, whole building initialization, house assignment and whole-frame parity remain open.

## What works and what is supplied

The prototype accepts one healthy, placed stock **INGALITE**, an invisible 1x1
light-emitting building. Alternatively, `--light-demo` places that supplied type
two cells east of the demonstration Rhino; it never rewrites the map or installation.
L immediately toggles the source. `--detail 0..2` selects the original graphics
detail input, default 2. The source can be active at detail 0/1 but contributes no
cell updates there. Resetting the tank retains light state.

`StaticLight.cpp` implements type-value conversion, inactive source construction,
idempotent active-state changes, original affected-cell order/inclusion, and
terrain converter tint/shade decisions. `MapLighting.cpp` retains the recovered
cell arithmetic. The renderer updates the visited cells and invalidates its terrain
image; indexed voxel shapes and shadow caches survive the change. Simulation is
unchanged and SDL-free; all these presentation routines are SDL-free too.

Runtime requires five explicit INGALITE light settings, `Image=GALITE`,
`InvisibleInGame=yes` and GALITE `Foundation=1x1`. The supported map record has
health 256 and a valid supplied cell. Multiple emitters, other emitting types,
map emitter-type overrides and a second demonstration source are refused.
Structures still enter the existing conservative route-exclusion adapter, so a
placed emitter can change the demonstration spawn. Neither original occupation
nor building health/power/house lifecycle is reconstructed by this integration.

The demonstration placement, map health/location prefix, initial activation and
L control are **host adapters** around recovered source operations. Whole-terrain
invalidation is a **host redraw/cache adapter**; the original redraw notification
is recorded by the oracle, not implemented. Applying current-cell tint to the
selected named player converter remains an **actor/house association adapter**.
Visibility alpha remains the fully visible 127 host policy. No original game
observation was made; native previews are integration QA only.

## Reference lead and exact-binary evidence

Consulted redalert2-recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439`, LICENSE,
`docs/voxels.md` and the `src/runtime/hdvox.c` header. Its render-chain material
provided no verified static-source formula. YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88`, `LightSourceClass.h`,
`GameOptionsClass.h`, `BuildingClass.h` and `BuildingTypeClass.h` supplied naming
and layout hypotheses only. Our base addresses, fields and numeric behavior were
independently recovered below. No upstream or generated game code was incorporated.
See [REFERENCES.md](REFERENCES.md) and [THIRD_PARTY.md](../THIRD_PARTY.md).

| Original evidence | Base VA |
| --- | --- |
| Light-type multiply/add/FTOL block | `0x45A1D0..0x45A1E1` |
| Related visibility/intensity/tint loader stores, inspected | `0x45A193..0x45A2BC` |
| Complete source constructor | `0x5352D0` |
| Complete activate / deactivate | `0x5355D0` / `0x5355F0` |
| Complete immediate affected-cell update | `0x535660` |
| Complete cell calculation / numeric installation | `0x479040` / `0x478CF0` |
| Complete ordinary terrain converter factory / clamp-mask helper | `0x5276A0` / `0x536630` |
| Building source creation/activation block | `0x442B3F..0x442BD6` |
| Actual building coordinate getter / foundation width and height | `0x443E10` / `0x4585B0`, `0x4585C0` |
| GameOptions constructor / default detail write | `0x5D0D80` / `0x5D0DF6` |
| Detail slider direct store, inspected | `0x4CF598..0x4CF5C5` |
| Graphics detail / lighting-enabled byte | `0xA2874C` / `0x7CA258` |
| Source array / count | `0xA5642C` / `0xA56438` |
| Map cell-pointer array field | `0x81A800 + 0x138` |
| ISOTEM.PAL filename, load and 6-bit expansion, inspected | `0x527CA4..0x527D0E` |

Source fields: intensity `+0x24`; tint `+0x28/+0x2C/+0x30`; minimum detail
`+0x34`; XYZ `+0x38/+0x3C/+0x40`; radius `+0x44`; active byte `+0x48`.
Building type fields: radius `+0xBC8`; intensity `+0xBCC`; tints
`+0xBD0/+0xBD4/+0xBD8`; foundation index `+0xC78`.
The actual 1x1 foundation entry is index 0. Building main vtable is `0x787BBC`.

The source constructor writes minimum detail **2** and active false. The options
constructor also writes detail **2** at `+0x14`; the slider stores its position
directly. Those original callers establish the gate's meaning. The old map-light
Python fixture names `clock`/`activation` retain their positional numeric protocol;
they mean graphics detail/minimum detail, not timers.

The terrain factory pushes palette globals `0xA55928` and `0x820130`. Inspected
theater loading constructs `ISO%s.PAL` with the temperate suffix `TEM`, loads
768 bytes into `0xA55928` and shifts channels left two. The second palette is
TEMPERAT.PAL, established in [STAGING.md](STAGING.md). This is inspected filename/
caller evidence, not executed full theater initialization or palette ownership.
The native scalar palette routine retains explicit all-entry affected flags;
the complete LightConvert constructor and its palette/lifetime wiring are not
verified by the factory decision suite.

## Consequential operations

Light-type decimals use `truncate(binary64 value * 1000 + 0.1)` in the recovered
round-toward-zero context. This differs from map Ambient/tint conversion by 100.
Stock INGALITE settings become radius **5000**, intensity **200**, RGB contributions
**(50,50,10)**. Negative `-0.15` becomes **-149**. Preserve the bias and operation
order; nearest rounding or a generic decimal parser shortcut changes outputs.
The original building block skips source creation when integer intensity is zero.

The tested 1x1 getter centers XY at `cell * 256 + 128`. Source Z is retained from
the building location; runtime supplies cell elevation times 104 as an actor-location
adapter. Cell falloff ignores that Z. Constructor registration executes against
a supplied source array with room; allocation/growth/failure lifetime is not recovered.

Activate/deactivate first check the existing byte. Repeating its current state is
a no-op. A real transition writes the byte before recalculating cells. This slice
implements **immediate mode 0**, used by the inspected building activation calls.
Deferred mode 1 queue/time budget, destruction, intensity changes and power/house
lifecycle are deferred.

Affected cells are visited Y-major, then X-major. Center cell is source XY divided
by 256 toward zero; search radius is `visibility / 256 + 1`. The traversal bounds
coordinates to 0..511, consults map membership and tests original table sqrt
followed by integer truncation against visibility. **Do not prefilter by squared
radius:** the table result can visit cells just outside the mathematical circle.
The separate cell-light calculation still performs its own recovered squared-radius
test. Stock placement at (35,86), Z=416, updates **1,201** supplied map cells.

The ordinary factory's existing neutral `(1000,1000,1000)` converter fast path
precedes quantization. Other channels clamp to 0..1000 and mask to multiples of
128/64/32 at detail 0/1/2. Quantized sum below **2000** selects **27** shade rows;
otherwise **53**. At detail 2 the supplied map tint `(1000,1000,860)` becomes
`(992,992,832)` for terrain. Unit converters keep their separate explicit 53-row
host profile. Native value-keyed palette storage does not establish original shared
converter ownership, refcounts, allocation or cache invalidation.

The native domain is finite light decimals within +/-10, radius 1..32767, XY within
+/-2^20, valid detail 0..2 and non-overflowing signed squared distances. Map-light
numeric bounds still apply. Arbitrary mods, invalid radii, large overflowing world
coordinates and alternate lighting are outside the claim. Strict FP compilation
and scoped host-state restoration remain required.

## Differential evidence and reproduction

`original_static_light.py` executes unchanged original instructions in hash-pinned
isolated x86 memory. No instruction bytes are patched. Source construction includes
the base constructor and registration. Complete activation, deactivation, immediate
update, actual membership/lookup helpers, sqrt, cell calculation and numeric
installation execute. Map/cell pointers and the flat-height getter are fixtures.
Cell installation's converter factory returns null to isolate numeric writes;
the redraw callback is record-only. It does not establish original rendered output.

The factory executes separately with an existing neutral pool entry, successful
allocator and LightConvert constructor recorder. Original clamp/mask, lookup,
shade decision and registry code run; constructed palette pixels/allocation lifetime
are excluded. The building block executes the actual coordinate getter, foundation
helpers, source constructor and activation, with explicit building/type/location
fields and successful allocation. It does not execute complete building creation.
Numeric tests use supplied doubles, not original INI parsing; they invalidate the
input-load translation cache and check the stop address after prior sqrt/source calls.

| Matching original/native cases | Count |
| --- | ---: |
| Actual type numeric blocks, decimal neighbors | 779 |
| Complete ordinary factory decisions | 1,524 |
| Complete source constructors | 128 |
| Complete immediate activation/deactivation updates | 128 |
| Owned stock rules type | 1 |
| Owned building blocks, detail 0/1/2 | 3 |
| Zero-intensity building skip, detail 0/1/2 | 3 |
| Owned complete-map activate/deactivate/no-op | 3 |
| Numeric repeatability after source calls | 5 |
| **Total** | **2,574** |

All match. Complete-map cases hash all **13,515 cell numeric records**, plus
affected-cell visit order. Random cases vary signed contributions, missing cells,
source placement/elevation, detail, lighting enable, radial boundaries and active
state. These compare fields/order at the stated boundary; they are not a complete
actor-arena/ordered-write audit or whole-game parity claim.

```sh
./build.command
./run.command --light-demo
./run.command --light-demo --detail 1
./test.command --data-dir "$PWD/private/game"
build/tools-env/bin/python tests/compare_static_light.py --exe private/disc-allied/game.exe
build/native/presentation-check private/game build/static-light
# After the headless sanitizer build in README:
build/tools-env/bin/python tests/compare_static_light.py \
  --exe private/disc-allied/game.exe --native build/sanitize/static-light-vectors \
  --expectations private/migration/allied-disc/static-light/expected.json \
  --report private/migration/allied-disc/static-light/sanitize-report.json
```

The 145 synthetic checks, disc/export tests, 13 owned map/CLI checks, owned renderer
checks and ASan/UBSan replay pass. Light toggles restore the full native frame,
preserve vehicle coverage/simulation and reuse shadow shapes. Low detail and zero
integer intensity leave pixels unchanged. Existing original suites remain passing.
These are integration checks alongside the original comparisons, not substitutes.

Reports are `private/static-light-report.json` and
`private/static-light-sanitize-report.json`. Owned research copies/expectations stay
under `private/static-light/`, disassembly/probes under `private/lights/`, and native
previews under `build/static-light-*`. Reports/expectations pin the original, render
data, owned inputs, oracle source and native runner. All remain ignored.
No new dependency/preparation table or runtime GAME.EXE access is added: the app
reads hash-checked track data only and never executes original instructions.

## Next bounded question and original measurements

Recover the Rhino's **cell-to-house converter association** and invalidation as it
crosses this source's radius. Verify the actual converter selected and updated fields
with a bounded healthy actor/type/house fixture; preserve the source/cell/pixel oracles.
Keep visibility fixed and leave general dynamic lighting and fog for separate slices.

When Windows is available, pin its executable and record graphics detail, map/light
cell, radius/settings, health/power, house, resolution/pixel format and console versus
RDP session. Toggle one INGALITE with the Rhino stationary, then move it across the
radius and back. Log source `+0x24..+0x48`, detail global, ordered cell visits,
cell `+0x104..+0x114`, selected terrain/house converters and redraw calls; capture
lossless RGB565 and alpha separately. Repeat after panning and at detail 0/1/2.
This resolves actor/converter/cache and visibility integration; screenshots alone do not.

Windows/Linux, full-frame parity, original UI, scenery, general pathfinding, combat,
AI, campaigns, multiplayer, audio, original saves and Yuri's Revenge remain deferred.
