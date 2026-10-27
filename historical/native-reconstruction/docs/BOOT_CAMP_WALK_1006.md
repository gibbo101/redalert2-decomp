# Boot Camp Day 1 walking checkpoint

[Recruited GI House rebinding](INFANTRY_HOUSE_REBIND_1006.md) now retargets
Walk/membership index, speed and control references at the actual owner1B4 store,
without rebuilding the world. Selection and temporary palettes follow current
ownership. The discarded actual-GI transfer completes new threat/registration/
radio-slot lookup, then guards Infantry+414 (actual503C00), not arrival sight418.
No partial clone is adopted or live Team/Script20/arrival/SDL objective enabled.
Next recover the complete entered503C00/4C6F10 path and actual children, then bind
existing radar424/420 owners and the wrapper before Script20 lookup/scheduling.
New-route Team permission6BA990 remains guarded; committed-head owner tests do
not prove general recruited-GI routing. Startup/palette policies remain supplied.


The later [membership discovery binding](INFANTRY_MEMBERSHIP_DISCOVERY_1006.md)
replaces the GI notification no-op on actual owners under the Cell parent's
original predicate. The broad "discovery not enabled" wording below remains
historical for structure/sight/objective progression; conditional GI membership
discovery now executes. Arrival/sight scheduling and ordinary objectives remain off.


`./run.command --boot-camp-walk` now selects and moves the player GI on the
original Day 1 map using the existing recovered Infantry/Foot/Walk algorithms.
RMB issues a bounded direct route, S stops after the committed head, and Space
pauses the host schedule. Idle repeated orders work. The other four original GI
records retain independent state and placement. **Discovery, mission actions and
objective transitions are not enabled.** This removes the movement integration
blocker for the first lesson; it does not complete that lesson.

GI facing correction: [GI_SPRITE_FACING.md](GI_SPRITE_FACING.md) fixes the
map-facing to screen-sprite direction mismatch, including horizontal travel.
Ready/Walk now use the observed GI image ordering; phase and original drawing
remain supplied. The actual-map eight-direction checks and expanded horizontal
SDL regression pass.

## Ownership and supplied boundaries

`BootCampWalkWorld` is an SDL-free scenario association in `ra2_scenarios`.
It owns one prepared terrain/map, five distinct actual Infantry/Walk records,
House/type/clock/RNG records and stable per-actor targets. `PreparedInfantryWalk`
borrows those same owners for commands, Process, admission/speed, Mark,
list/occupation, floor and arrival. Drawing consumes their actual placement and
Facing; there is no dummy Simulation, mirrored Drive or second movement policy.
The borrowed assets/mission must outlive the immovable scenario owner.

The original map's player record supplies Cell57,89, subcell4 and facing64.
The recovered subcell-offset initializer yields192,192; initial height is the
map's level2 times104, so the actual starting coordinate is14784,22976,208.
The stock E1/GI type and Walk locomotor are checked. Existing `internalSpeed`
converts Speed4 to10. The aligned supplied-base reader at6DCC01..6DCC41 was
inspected; the earlier disc address6D2021 is not valid evidence for this binary.
This inspection and the journeys below do **not** recover the full E1 constructor,
country/House loading or original scenario startup.

Startup fields, Guard/Return missions, country multiplier1, Foot speed association,
seed, named visibility/notification/recalculation/animation effects and the
five-Process/clock schedule remain supplied. The host advances one tick about
every67ms; slow hosts do not reproduce the original campaign scheduler. Selection,
picking, camera, UI, direct routing, rectangle foundation clearance and obstacle
masks are host adapters. Routes are at most23 Cells, diagonal first, restricted
to supported flat equal-level land without overlays/tubes/bridges or other actors.
Moving non-null retarget refuses before changing state; S finishes the committed
head. No original pathfinding, general crowd interaction or failed-route recovery
is claimed. Unexpected entered-child faults still propagate, not rollback.

The explicit terrain policy defers attached Cell tags without executing them;
`MissionDefinition` retains their definitions. It also accepts only map resource
`Value` overrides over rules defaults. Other resource keys and all tubes still
refuse, and old callers keep both default refusals. These are input associations,
not recovered tag attachment/actions or full resource/type startup.

GI SHP Ready/Walk triples come from original art. Frame direction/phase, palette,
unlit sprite blending, layering and shadows are temporary presentation. Structure
markers are not building actors. There is no fog, audio, combat or mission effect.
The static `--boot-camp-preview` remains available. Only Apple Silicon macOS is
tested; no whole-frame, whole-game or independent acceptance claim follows.

## Original and native verification

Exact supplied base:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. No new dependency, public/header/generated/
lifted code, proprietary data in Git or runtime executable read was added.

The unchanged world oracle/runner additionally match **10 sequences /995 complete
original roots** with speed10, subcell192,192, level2, all eight two-Cell directions
and two committed-head Stop cases. Canonical original-only receipts:
`private/boot-camp-20261018/e1-fresh-a1/{expected,report}.json`.
This is a translated flat-map fixture with supplied route/startup/services,
not execution of the actual Boot Camp startup or original campaign observations.
ABI/code/table/arena/write guards and selected ordered stores, final state,
queues/floor/RNG remain those of the existing world oracle. See
[INFANTRY_WALK_WORLD_1006.md](INFANTRY_WALK_WORLD_1006.md) for its exact scope.

`walk-e1-replay-{normal,sanitize,uncached}-a1.json` each have10 hits/zero misses/
zero original execution. Current rebuilt runners also retain all92 prior world
sequences /4,061 roots and285 membership sequences /501 roots. Originals were
not regenerated for native-only changes; original receipts remain immutable.
The first membership replay invocation used an unsupported `--map-data` option;
its failed audit is retained. Corrected `walk-membership-replay-{native,sanitize}-a2`
commands pass. No comparison guard was weakened or receipt relabeled.

`boot-camp-walk-check` passes on the real assets in normal and sanitizer builds:
eight accepted starting directions, exact initial Cell/subcell/floor, arrival,
Stop/retained head, repeated/return orders, independent other GIs, rejected moving/
non-player/extreme/blocked/too-long orders with unchanged sampled live owners,
and default/deferred-tag/Value-only/tube policy boundaries. All82 normal /81
sanitizer CTests,1,266 Python tests and `./test.command` pass. The first broad Python
run caught a missing transitive `MembershipPolicy.hpp` in the old owned-Advance
manifest; the declaration was repaired and the full run passed.

Actual SDL injected events through ordinary handlers pass select/move/draw,
pause, moving-retarget refusal, Stop and repeated orders/deselection in106 ticks.
Receipt/images: `walk-sdl-a2/` under the same private directory. Arrival is
15296,22976,208; Stop on the return route ends at15040,22976,208, then another
ordinary order reaches the starting Cell. Separate screenshot-grounded native
mouse/keyboard use verifies selection box, changed position, pause, Stop and
blank deselection. `walk-gui-a1/` records runner identity and observations.
Both existing two-tank ordinary and Scatter SDL regressions pass. These are
native integration observations, not original gameplay or drawing fidelity.

Measured fresh original generation3.968s (wrapper6.593s); E1 driver replays
1.840s/1.381s/5.296s normal/sanitizer/uncached. World replays1.204s/3.306s/5.605s.
Broad builds30.79s/37.85s; normal/sanitizer asset checks1.59s/13.69s. Passing full
Python body30.806s (driver34.85s); `./test.command`5.75s, sanitizer CTests13.69s.
GI SDL smoke2.65s; ordinary two-tank smoke15.11s. Concurrent costs are not additive.
The GUI attachment alone reported1152.1632s; its later screenshot/input calls
returned in seconds. Do not attribute that delay to original execution or repeat
an already successful attachment. Earlier test fixtures incorrectly expected Z0
and used a clearance radius that blocked all routes; failures/repairs are retained.
Other continuation/manual implementation/repair and total goal-wall costs are
unavailable. Private `walk-validation.json` records artifacts, costs and limits.
No cache framework or unchanged original matrix was added.

## Reproduce

```sh
./build.command
./test.command
./run.command --boot-camp-walk
# LMB player GI; RMB nearby flat ground; S Stop; Space pause; arrows/wheel/H camera.
# Use a new private output name for each smoke run.
./run.command --boot-camp-walk-smoke-test private/boot-camp-walk-try
build/native/boot-camp-walk-check private/official-1006-probe
build/sanitize/boot-camp-walk-check private/official-1006-probe

# New report/audit names. Current native execution; reuse immutable originals.
env DEVELOPER_DIR=/Library/Developer/CommandLineTools PYTHONHASHSEED=0 \
  PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/boot-camp-e1-next.audit.json tests/compare_boot_camp_walk_inputs.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/infantry-walk-world-vectors \
  --render-data private/derived/ra2-1006/render-data.bin \
  --raster-data private/derived/ra2-1006/raster-data.bin \
  --direction-data private/derived/ra2-1006/direction-data.bin \
  --subcell-data private/derived/ra2-1006/infantry-subcell-data.bin \
  --map-data private/derived/ra2-1006/map-runtime-data.bin \
  --expectations private/boot-camp-20261018/e1-fresh-a1/expected.json \
  --report private/boot-camp-e1-next.json
# Sanitizer: substitute build/sanitize runner and new report/audit names.
# Uncached inspection control: add --uncached before --audit; originals still reused.
# Fresh originals only when their dependencies change: omit expectations/report,
# use --output private/boot-camp-e1-new-fresh in the authorized Mac-host JIT context.
```

Next recover the actual discovery producer and the encountered trigger/timer/
action chain for Day1's first objective. Selection eligibility or arrival alone
must not synthesize success: inspected mission data attaches objective completion
to discovery of tagged base structures. Retarget/failed routes and original
Infantry animation/drawing remain explicit recovery gaps as lessons require them.
Retain existing tank scenarios. No workers, new Windows action or runtime read.
Full-game goal stays active; base RA2 and YR remain incomplete.
