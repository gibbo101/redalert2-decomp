# Red Alert 2 native reconstruction

[Original Boot Camp](docs/BOOT_CAMP.md) now has a bounded GI walking checkpoint.
Run `./build.command`, `./test.command`, then `./run.command --boot-camp-walk`.
The current workspace has the private message-color data prepared. For a fresh
setup with the exact supplied base target, run the preparation command in
[objective text lookup](docs/MESSAGE_TEXT_LOOKUP_1006.md) before starting Boot Camp.
LMB selects the player GI; RMB moves over nearby flat ground; S stops; Space
pauses. Original Infantry/Foot/Walk movement is verified against isolated original
routines. The actual map now also owns shared visibility Cells, the exact private
mask table and both Objective1 structures. Both recovered Techno sight directions
compose through reveal-area and the existing mission owner on those same Cells;
repeated and moved-spread checks reach Objective1. Startup, direct routes, sight
scheduling and sprite presentation remain supplied or approximate. **Walking
does not automatically invoke sight yet, so objective transitions remain pending.**
The exact arrival sight-order suffix and complete old-sight removal are now
recovered, along with both Cell visibility counter branches. Shared-world sight
composition now includes the complete post-sight mask refresh as an explicit
unscheduled seam. The mission-transition child is now identified with the prior
recovered Commence kernel, and all four suffix children compose explicitly. The
complete parent/crossing audit and production wiring remain; see
[INFANTRY_SIGHT_SCHEDULE_1006](docs/INFANTRY_SIGHT_SCHEDULE_1006.md).
The static `--boot-camp-preview` remains available. Commands, evidence and limits
are in [BOOT_CAMP_VISIBILITY_WORLD_1006](docs/BOOT_CAMP_VISIBILITY_WORLD_1006.md),
[BOOT_CAMP_WALK_1006](docs/BOOT_CAMP_WALK_1006.md) and [HANDOFF](docs/HANDOFF.md).
Exact post-sight behavior and evidence are in
[POST_SIGHT_REFRESH_1006](docs/POST_SIGHT_REFRESH_1006.md).
The complete unscheduled suffix composition and500AA0 inspection are in
[BOOT_CAMP_ARRIVAL_SIGHT_SUFFIX_1006](docs/BOOT_CAMP_ARRIVAL_SIGHT_SUFFIX_1006.md).
Fresh complete position/update-position proofs now execute the recovered
normal/elite E1 null-target selector, actual map lookup, zero-mask cloak prefix
and overlay-mismatch dirty prefix in one original-code guest. The chain remains
unscheduled; parent sight/map ownership and the exact Cell-crossing producer
still precede runtime Objective1 effects. See
[INFANTRY_UPDATE_POSITION_EFFECTS_E1_1006](docs/INFANTRY_UPDATE_POSITION_EFFECTS_E1_1006.md).
Only Apple Silicon macOS is tested; base RA2/YR remain incomplete.

[Movement beside overlays](docs/PREPARATION_NEIGHBOR_1006.md) now also passes
the alternate200-tick resident-displacement scenario. Preparation's noncrushable
neighbor lookup is separate from strict traversal guards; general pathfinding
and crushable/overlay traversal remain incomplete.

[Two-tank resident displacement](docs/OWNED_SCATTER_SDL_1006.md) now works in
`./run.command --owned-demo`: either Rhino is commandable, and recovered Scatter/
nearby decisions can move the other tank aside. The bounded SDL check covers
actual arrival, vacated-Cell entry and later independent commands. Direct routes,
controls and scheduling remain supplied; some timings still enter unsupported
terrain and stop the prototype. Build with `./build.command`; reproduce with
`./run.command --owned-scatter-smoke-test private/try-scatter-sdl`.
Current evidence and limitations are in [HANDOFF](docs/HANDOFF.md).
Earlier unwired/guarded entries below describe their checkpoint scopes.

[Admission over actual prepared owners](docs/BORROWED_UNIT_ADMISSION_1006.md)
now shares one recovered policy with the legacy APIs and observes live mission,
list, occupation, terrain, Drive and target records without refresh copies.
The separate binding is differentially verified and remains unwired. The playable
two-Rhino baseline and runtime Scatter/Advance6 guards are unchanged. Current
commands, receipts, caching and next integration are in [HANDOFF](docs/HANDOFF.md).
Earlier entries below describe their checkpoint scopes.

[Complete Advance with terminal targets](docs/ADVANCE_TERMINAL_SCATTER_1006.md)
now joins movement, admission/Scatter and actual Cell/Foot target checks, clears
and return flow in one kernel:292 scenarios/317 original calls match. Mission
effects remain supplied. This entry is unwired; Process, production ownership,
previews/drawing and SDL displacement remain next. The playable two-Rhino baseline
keeps runtime Scatter/Advance6 refused. Current verification, limitations and
commands are in [HANDOFF](docs/HANDOFF.md). Earlier entries below retain their
checkpoint scopes.

[Advance result6 dispatch](docs/ADVANCE_CELL_SCATTER_1006.md) now has an isolated
original block proof through actual Cell/Unit/nearby destinations: 160 blocks and
287 Unit calls. It distinguishes queued candidate checks from the final Drive-head
lookup, retains the raw stack word and verifies the separate stock divisor 104.
This remains unwired and is not complete Advance or Process; the two-tank demo
and runtime Scatter/Advance6 guards remain unchanged. See [HANDOFF](docs/HANDOFF.md).

[Cell dispatch through zero-point Unit Scatter](docs/CELL_NEARBY_SCATTER_1006.md)
now joins actual nearby search and Cell destinations for distinct actors, including
shared type aliases. Fresh original proof matches 128 sequences/141 Cell calls and
262 nested Unit calls; all 258 zero-point dispatches preserve RNG and queued mission.
The entry remains unwired: Advance6/Process/owned-world/full-preview/drawing/SDL
joins still precede runtime displacement. The two-commandable-Rhino demo is
unchanged. Current evidence, commands and limits are in [HANDOFF](docs/HANDOFF.md).

[Zero-point Unit Scatter](docs/UNIT_NEARBY_SCATTER_1006.md) now joins the actual
nearby search and Cell destination effects on shared actor/Drive/map/fallback
records. It preserves the borrowed type speed, signed source/alternate bytes and
frame selection without RNG or mission2 queuing. The separate entry stays unwired;
Cell dispatch/Advance6/Process/owned-world/full-preview/drawing/SDL joins remain
open. Current proof totals and limits are in the [handoff](docs/HANDOFF.md).

[Nearby destination search on shared Cells](docs/NEARBY_LOCATION_MAP_1006.md)
now joins actual permission, rectangle/Cell admission and projection in 327 complete
original searches. The standalone policy retains all 306 earlier outputs. This
unwired destination search adds no runtime movement; actual Unit Scatter and
Advance6/Process/owned-world/preview/SDL joins remain next.

[Nearby Cell admission](docs/NEARBY_CELL_ADMISSION_1006.md) now matches 2,372
complete original calls, covering rectangle admission, its actual Cell child and
permission from a Cell pointer. Zone resolution stays supplied; the required Unit
caller skips it. These separate unwired dependencies preserve runtime guards.
The next join is the nearby search with actual admission/permission/projection.

[Nearby destination search](docs/NEARBY_LOCATION_1006.md) now matches 306 complete
original calls, including candidate order, repeated projection, frame selection
and wrapped distances. This unwired dependency retains supplied admission/query
services. Advance6 needs the zero-point Scatter branch; its caller/world/preview/
SDL joins remain open. The playable two-Rhino baseline is unchanged.

[Cell-to-Unit Scatter](docs/CELL_UNIT_SCATTER_WORLD_1006.md) now joins complete
resident dispatch to actual Unit Scatter/world queries and destinations on
distinct actor records. Later admission sees earlier commands. Original proofs
and native ownership checks are recorded in [HANDOFF](docs/HANDOFF.md). This
separate unwired entry adds no runtime movement; Advance6/Process/owned-world/
preview/SDL joins and their guards remain open.

[Unit Scatter world queries and Cell destinations](docs/UNIT_SCATTER_WORLD_1006.md)
now match 477 sequences / 708 complete Scatter calls plus 63 direct projection calls,
with normal/sanitizer/uncached replays. Actual mission 7 Cell destinations retain
all 24 queue words. This separate unwired entry installs destinations without route
search or later movement; Cell dispatch/Advance6/Process/world/preview/SDL joins
remain open. The playable two-Rhino baseline and runtime guards stay unchanged.

[Foot coordinate-layer recovery](docs/FOOT_LAYER_1006.md) now joins the actual
coordinate/floor/map children in 2,296 sequences / 3,643 top-level original layer
calls. This separate unwired dependency preserves raw bridge bytes and ordered
queries; the playable baseline and Scatter/Advance6 guards remain unchanged.

[Ordinary destination effects](docs/UNIT_DESTINATION_1006.md) now join the complete
Unit/Foot roots to actual Drive commands/guards, Cell center/floor/map queries,
vector clearing and retained interface ownership in 819 sequences / 1,833 top-level
original calls. This separate helper is unwired; it installs destinations without
pathfinding or later movement and does not promote the earlier Scatter callback.
The playable two-Rhino baseline and Scatter/Advance6 guards are unchanged.

[Unit Scatter control policy](docs/UNIT_SCATTER_1006.md) now matches 1,622 complete
original parent calls, including actual eligibility, RNG, bearing, mission queuing
and retained Drive interface ownership. World queries, pathfinder and destination
effects remain supplied. The helper is unwired; Scatter/Advance6 stay refused.

[Inclusive RNG ranges](docs/RANDOM_RANGE_1006.md) now preserve original rejection
sampling and consumption in 7,011 complete original calls. This unwired Scatter
dependency changes no playable behavior; Unit Scatter and Advance6 stay guarded.

[Cell resident snapshot/dispatch](docs/CELL_SCATTER_1006.md) now matches 998
fresh original calls and normal/sanitizer/uncached replays. This unwired dependency
keeps heap and member Scatter effects supplied; Unit Scatter and Advance6 remain
refused in the playable demo. Current evidence and next joins are in the handoff.

[Commands, full previews and SDL curve admission](docs/OWNED_ADVANCE_RUNTIME_1006.md) now join the
original result7 continuation to both actual actors in `--owned-demo`. Original
command/Process/finalization/drawing comparisons and separate warm route/clearance
isolation checks pass. Actual SDL input reaches a actual result7 interaction with a moving resident on the
stock map, retains the curve and later arrives. The SDL factory explicitly opts
in; low-level construction defaults stay guarded. Advance6/scatter remain refused.
Current evidence and limitations are in the opening handoff.

Current status: [opening handoff](docs/HANDOFF.md). The bounded
[recovery-method assessment](docs/RECOVERY_METHOD_ASSESSMENT_20261016.md) records
compiler-toolchain limits, a partial inventory and measured verification overhead.

[Two commandable Rhinos](docs/OWNED_TERRAIN_RUNTIME_1006.md) now run in the opt-in
`./run.command --owned-demo` on one shared mutable terrain world. Select either
tank, RMB to move, Ctrl-RMB to append, Shift-RMB to aim, Q/E to turn its body,
A/D its turret, S to stop and R to reset. This runtime has no mirrored Simulation
or Drive. Controls, direct routes, clearance and scheduling remain supplied
policies. The opening handoff records original-routine and native SDL evidence;
base RA2 and Yuri's Revenge remain incomplete. The older `--resident-demo` keeps
its second tank inspection-only.

Earlier entries below describe their checkpoint states. Runtime/SDL gates that
were open there are closed only within the new bounded profile above.

[Scheduled movement previews](docs/OWNED_SCHEDULED_PREVIEW_1006.md) advance both
actual actors on a discarded world copy, using the same explicit schedule as live
stepping. Warm simulation and renderer isolation checks accompany original
Process/drawing comparisons. Selected-actor runtime routing and SDL acceptance
remain next; the resident demo's second tank is still inspection-only.

[Per-actor orders](docs/OWNED_ORDERS_WORLD_1006.md) add bounded routes, stops and
deferred body turns over the shared world's actual records. Original command,
later Process and complete drawing evidence is recorded in the opening handoff.
The subsequent scheduled-preview note records isolation; runtime/SDL adoption
remains open. The resident demo still has one commandable tank.

[Independent turret commands](docs/OWNED_TURRET_WORLD_1006.md) now match original
requests/automatic updates on both real actors through complete Process and shared
drawing. Controls and target lifetime remain adapters; preview/runtime/SDL adoption
remain open.

[Stable two-Unit command ownership](docs/OWNED_COMMAND_WORLD_1006.md) adds an
SDL-free shared world owner, separate command/turret/wait records and cloned
preview isolation. It remains unwired; the resident demo still has one commandable
mover and one inspection-only Unit. The opening handoff records verification and
the remaining command, preview and SDL gates.

[Selected ordinary Drive stores](docs/GROUND_DRIVE_STORES_1006.md) now match
594 original scenarios /11,026 complete Advance calls, including the recovered
zero-head/driving-byte edge case. [Guarded inspection reuse](docs/INSPECTION_REUSE.md)
is available for verification; original execution and comparisons still run.

[Two-Process ownership](docs/OWNED_UNIT_PROCESSES_1006.md) now checks
genuine independent Process calls against both original actors in one guest,
with fresh original and native/sanitizer state and complete drawing comparisons.
The public binding has canonical distinct-address evidence; runtime/SDL
acceptance remains open. The resident demo's second tank remains inspection only.

[Moving-resident Process callers](docs/MOVING_RESIDENT_PROCESS_1006.md) now
match 163 fresh scenarios /964 complete original ticks, with normal and sanitizer
replays. The separate entry preserves result2 wait/retry and recursive preparation
arguments1/1. It remains unwired: genuine per-actor Process and shared mutable
membership still precede second-tank commands. The opening handoff records the
full regression, evidence and remaining supplied boundaries.

[Moving and turning Unit admission](docs/MOVING_UNIT_ADMISSION_1006.md) now
matches 3,666 fresh isolated original calls, with normal and sanitizer replays.
It preserves actual Facing/Drive activity, heading/bearing/distance decisions
and ordered result2 promotion. The helper remains unwired: its Process caller
effects and independent moving actor owners still precede second-tank commands.
The playable resident demo below retains one mover and one inspection-only tank.

[Owned movement and two-Unit drawing](docs/OWNED_UNIT_WORLD_1006.md) connects the
live mutable map, resident membership and Process to both tanks' complete drawing.
Try `./build.command` then `./run.command --resident-demo`: select the mover and
press G, or right-click the parked tank to test occupied-target refusal. Selecting
the parked tank is inspection only and clears mover command selection. Q/E turns
the mover's body, A/D its turret, S stops after its active track, and R resets.
Direct routing, picking, clearance, camera and frame scheduling remain host
policies. Base RA2 and Yuri's Revenge remain incomplete. The handoff records the
joint original-routine proof, native/SDL checks and remaining supplied behavior.

Earlier progress entries below describe their checkpoint states.

[Shared posed world drawing](docs/SHARED_GROUND_WORLD_1006.md) extends explicit
actor/type/global ownership through complete body/turret/barrel and world/shadow
pixels on prepared Cells. The helper remains unwired pending the live owned
movement/membership join and SDL parked drawing/selection.

[Shared two-actor staging](docs/SHARED_UNIT_STAGING_1006.md) separates each
actor's staging byte from global scratch and type-owned voxel indexes. The
helper remains unwired pending complete live world/shadow drawing; the SDL
demo still has one Unit.

[Shared owned movement and a parked Unit](docs/OWNED_UNIT_RESIDENT_1006.md) now
match original Mark/membership/discovery/occupation/recalculation and Process
on one map. The extension is explicit in the recovery driver; the SDL demo
still has one Unit pending separate parked drawing/selection acceptance.

[Stationary Unit admission now joins complete Process](docs/GROUND_DRIVE_RESIDENT_PROCESS_1006.md):
137 fresh results / 1,192 original ticks, with both replays. A separate native
entry preserves the original occupied-Unit retry behavior. It remains unwired;
shared resident membership and drawing/selection still precede a playable
two-Unit scenario. The existing one-Unit terrain demo passes unchanged.

[Terrain admission is enabled in the native demo](docs/RUNTIME_ADMISSION_1006.md).
Actual Unit entry decisions now share the mutable map and live membership;
the stock zero-speed target (74,41) is refused through SDL right-click input.
The complete queue survives between ticks and previews stay isolated. Existing
crossing/ramp/stop/turn/cliff checks pass. This remains one Unit with direct-route,
control and clearance adapters; stationary residents and general pathfinding are
not implemented. Run `./run.command --terrain-demo` or the documented smoke test.
Earlier entries below describe their checkpoint states.

[Admission on owned mutable Cells](docs/OWNED_UNIT_ADMISSION_1006.md) now joins
the production map and live Unit membership effects: **228 fresh results / 17,960
original Process ticks**, with normal/sanitizer replays. It preserves live
occupation/list reads, ordered writes and independent clone storage. This new
binding is not enabled in the demo yet; queue retention and input association
still precede runtime adoption. The existing SDL terrain demo passes. The profile
has one Unit and no other residents; playable gates/general collision remain open.

[Admission through complete Process](docs/GROUND_DRIVE_ADMISSION_PROCESS_1006.md)
now matches **221 fresh original sequences / 13,708 ticks**, with normal and
sanitizer replays. It joins actual gates, supported admission results and the
Rhino's required next-Cell path, preserving different first/second failure
handling and retained queue tails. The new entry remains unwired; production
map/membership integration and blocked-move/gate SDL acceptance come next.
The existing terrain demo passes again. Earlier progress entries below retain
their checkpoint scopes; this does not complete base RA2 or Yuri's Revenge.

[Unit next-Cell recovery](docs/UNIT_NEXT_CELL_1006.md) verifies the Rhino's
required warning-mode early paths: 567 fresh scenarios / 613 original calls
and both replays. Target/layer queries still run before the crusher check;
only the selected layer's low five occupation bits control the warning test.
The helper remains unwired; nonzero admission handling and production-map joins
still precede runtime adoption. The playable terrain demo remains unchanged.

[Result-bearing gate checks](docs/GROUND_DRIVE_GATE_PROCESS_1006.md) now join
complete original Process/preparation/Advance: 297 fresh sequences / 13,048 calls
and both replays. Waiting gates return before turning or committing a route.
The new entry remains unwired; admission results and next-Cell effects still
precede runtime adoption. The rebuilt SDL terrain demo passes its existing checks.

[Ordinary Unit admission](docs/UNIT_ADMISSION_1006.md) now matches 2,391 fresh
original scenarios / 3,619 calls, including rejection, stationary occupants,
gates, elevation and occupation decisions. The helper remains unwired; runtime
adoption needs a result-bearing preparation/Process join. The playable demo is
unchanged.

The [gate evidence correction](docs/MOVEMENT_GATE_1006.md) fixes the provisional
Terrain kind 21 tag to the actual 36 (`0x24`) and verifies 603 original kind returns.
All 2,074 gate results and the native application behavior remain unchanged;
current proof is movement-gate-v3. Unit admission and gate runtime adoption remain
open. This corrects evidence; it adds no playable gate capability.

[Movement gate recovery](docs/MOVEMENT_GATE_1006.md) identifies the older supplied
“reservation” call as gate interaction. Complete gate/alliance/animation/mission
helpers match 2,074 fresh original results and both replays. The helper is unwired;
admission and the complete failure caller still precede runtime adoption. The
playable terrain demo below is unchanged.

[Native Unit membership](docs/RUNTIME_MEMBERSHIP_1006.md) is now wired into the
terrain demo: moving, stopping and turning the Rhino updates recovered Mark,
Cell lists, discovery, occupation and occupied recalculation. Each simulation
owns its mutable map; previews and copies leave live and renderer state unchanged.
The production binding matches **6,652 isolated original movement ticks**, with
normal/sanitizer replays and actual SDL event checks for selection, move, stop
and body/turret turning.

Try `./run.command --terrain-demo` or `--parked-cliff-demo`. All 13,515 selected
prepared Cells match the original parent projection. Direct routing/clearance,
controls, initial actor/type/House records, admission/reservation and missions
remain supplied adapters. This is not full startup/frame parity. Only Apple
Silicon macOS is tested; complete base RA2, then YR, remain incomplete.

Earlier checkpoint entries below describe the scope before runtime adoption;
[RUNTIME_MEMBERSHIP_1006.md](docs/RUNTIME_MEMBERSHIP_1006.md) records the current
binding, ownership, evidence, reproduction commands and remaining boundaries.

[Occupied Cell recovery](docs/OCCUPIED_CELL_1006.md) now joins actual resident
recalculation, LAT/TMP and occupied passability into Unit Mark/membership:
796 standalone results and 367 sequences / 1,921 calls match the original, with
both replays. Ordered intermediate writes and shared list/fallback state are
preserved. Helpers remain unwired pending the complete Process join; the playable
terrain demo is unchanged. Earlier notes retain their checkpoint scopes.

[Unit visibility/discovery recovery](docs/UNIT_DISCOVERY_1006.md) now joins actual
visibility, discovery notification and mission queuing into Mark/membership:
560 fresh sequences / 3,376 calls, plus 884 child/initialization results and both
replays. Occupied-Cell recalculation remains supplied; helpers stay unwired until
the complete Process join. The playable terrain demo is unchanged.

[Unit membership recovery](docs/UNIT_MEMBERSHIP_1006.md) joins complete Mark,
map/Cell membership, stock foundation and occupation with actual shared floors:
594 fresh sequences / 3,743 calls and both replays pass. Visibility/notification/
occupied-Cell recalculation remain services; helper unwired. The playable terrain
demo is unchanged. Earlier Mark/occupation notes below retain checkpoint scopes.

[Unit Mark recovery](docs/UNIT_MARK_1006.md) verifies complete Object/Techno/Foot
wrappers with actual getters, Drive layer and redraw children: 4,263 fresh
sequences / 11,667 calls and both replays. Map membership remains a supplied
service; actual membership/occupation integration is next. The helper is unwired.

[Unit occupation recovery](docs/UNIT_OCCUPATION_1006.md) now matches 2,142 fresh
original sequences / 9,060 calls, including actual floor queries, signed threshold
wrapping and asymmetric elevated-field marking. Both replays pass. The helper is
unwired; complete Unit Mark/membership remains next before movement integration.

Historical checkpoint notes below retain their scope at the time of recovery.


[Live movement through complete Unit drawing](docs/MOVING_UNIT_WORLD_1006.md)
now matches **228 fresh original results / 867 movement ticks / 92 complete draws**.
The same actor supplies location, height, Facing and stored ramps to body/turret/
barrel drawing; shadows retain their separate current-Cell queries. Nonzero
translation/pivot, interpolation, warm reuse and positive/negative heights are
covered. The helper remains unwired. Runtime promotion and actual SDL terrain
crossing/parked-cliff acceptance remain next; complete base RA2 then YR remain
incomplete. Earlier checkpoint scopes follow.


[Floor-relative Unit shadow drawing](docs/GROUND_UNIT_HEIGHT_1006.md) now matches
52 fresh complete original draws, including positive heights, zero boundaries,
raw/cached shadows and clipping. The extra pixel belongs to the stencil Y origin;
Foot's world point remains separate. The earlier 43-draw profile also has fresh
unchanged results. Both entries remain unwired and lit body state remains flat/
settled. Complete moving-actor body/turret/barrel drawing still precedes terrain
runtime promotion and actual SDL crossing/parked-cliff acceptance.

[Prepared-map movement and pose](docs/PREPARED_DRIVE_STATE_1006.md) now joins
finalized Cells, actual height/ramp writers, complete ordinary Drive movement and
both body/shadow poses: 6,652 fresh original movement ticks / 13,304 pose calls.
Stored body ramps and current-Cell shadows can differ; fractional Z retention
also produces positive relative heights. Complete drawing must cover those live
states before runtime promotion and SDL crossing/cliff acceptance. The demo is
unchanged; complete base RA2 then Yuri's Revenge remain incomplete.

[Terrain-aware ordinary Drive Process](docs/GROUND_DRIVE_PROCESS_1006.md) now
matches 194 fresh sequences / 28,552 complete original Process calls and both
replays. Complete preparation, queued turns/track consumption, actual floor/speed
children and stored ramp observation execute together. Live fallback identity,
second-Cell admission and queries before rejected non-Passive switches are
preserved. Initial records, route finding and occupation/mission effects remain
supplied. The helper is unwired; prepared-map/body/drawing integration and actual
SDL terrain crossing/parked-cliff acceptance remain next. The playable demo is
unchanged. Earlier checkpoint scopes follow.

[Committed ordinary Drive Advance on terrain](docs/GROUND_DRIVE_ADVANCE_1006.md)
now matches 514 fresh sequences / 10,866 complete original calls and both replays.
Actual location/floor children preserve committed height updates, fractional
movement without floor resampling, endpoint credit and ordered marking/Cell
queries. Initial track/map/type state and Mark/notification effects stay supplied;
Process, prepared-map/body/drawing integration and runtime promotion remain next.
The helper is unwired and the playable demo is unchanged.

[Drive location/floor placement](docs/GROUND_MOVEMENT_PLACEMENT_1006.md) now
matches 1,108 fresh exact-engine results and both replays. Complete Foot/Object
setters and two aligned Advance blocks preserve same-Cell marking suppression,
cross-Cell call order and SetHeight(0). Candidate/parent context and Mark effects
remain supplied; the complete movement/drawing join and runtime promotion remain
open. The helpers are unwired and the demo is unchanged.

[Stored-ramp Drive body pose](docs/DRIVE_BODY_POSE_1006.md) now matches 3,201
fresh exact-engine results and both replays: initialized quaternions, three-tick
ramp interpolation, rocking and ordered heading/cache-key decisions. Actual
Unlimbo/changed-ramp children feed the body consumer in selected cases. The helper
is unwired; original placement/movement callers and joined terrain-aware gameplay
remain next. Build/run/test commands and evidence limits are in the linked note.

[Actor height and Drive ramp state](docs/ACTOR_GROUND_STATE_1006.md) now match
1,696 fresh exact-engine results and both replays. The relative-height setter and
initial/changed-ramp writers are recovered; complete placement/movement callers
and body-pose integration remain open. Helpers are unwired and the demo is unchanged.

[Prepared ground Unit/shadow drawing](docs/GROUND_UNIT_WORLD_1006.md) now matches
87 fresh exact-engine results, including 43 complete draws on all 21 current-Cell
ramps and the supplied map. Actual floor height, Drive pose and repeated shadow
points reach lit/shadow pixels, cache/pool state and cleanup. The helper is unwired;
lit locomotor state remains supplied flat/settled. Actor height placement and ramp
updates still precede terrain-aware gameplay. Existing demo:
`./run.command --crossing-light-demo`.

Entries below retain their earlier checkpoint scopes.

[Current-ramp Drive shadow pose](docs/DRIVE_SHADOW_POSE_1006.md) now matches
3,904 fresh original results across all 21 ramps, heading boundaries, slope timers,
rocking and null/wrapped cache keys. Actual original Cell and Facing children
execute. The helper is unwired; complete shadow/height integration still precedes
terrain-aware runtime drawing.

[Stock ramp/Cell geometry](docs/RAMP_GEOMETRY_1006.md) now derives level height
104 and both tilt angles through verified original table math, then initializes
all 21 shadow matrices. Both distinct original numeric chains and exhaustive
table-bin/sign checks match. The helper remains unwired; Drive ramp pose/key
and actor-height integration remain next.

[Ramp shadow matrix initialization](docs/VOXEL_RAMP_SHADOW_1006.md) now matches
all 21 matrices from 44 fresh complete original initializer calls, across four
native FP modes. Angle globals remain supplied and the helper is unwired;
Drive ramp pose/key and actor-height integration remain next.

[Prepared-map complete lit Unit drawing](docs/PREPARED_UNIT_WORLD_1006.md) now
matches 129 fresh exact-engine results, including 111 complete draws through
actual Foot/base/TMP depth and final RGB565 pixels. A separate 2,445-query suite
verifies full-coordinate Cell lookup and shared fallback identity. Current Cells
must be flat; neighboring ramps are supported. Actor height remains supplied and
shadow pixels are outside this proof. The helper is not wired into gameplay;
ramp shadow initialization and floor-to-actor associations precede runtime promotion.
Try the existing playable baseline with `./run.command --crossing-light-demo`.

[Prepared-map Foot depth](docs/PREPARED_FOOT_DEPTH_1006.md) now matches 6,848
fresh complete depth/gradient queries, including parked-cliff and traffic-light
crossing inputs. Actual Foot predicates, type/Drive leaves, Unit base and TMP
dimensions execute together. Actor Z remains supplied; Unit-world/runtime depth
integration and original placement/update association remain next.

[Ordinary Unit base depth](docs/UNIT_BASE_DEPTH_1006.md) now matches 9,561
fresh exact-engine queries after shared map/floor finalization, with 4,529 actual
TMP dimension calls. Heading/ramp/overlay/flag decisions and retained missing-image
scratch are recovered. Actor height/initial state remains supplied; the helper is
not yet wired into gameplay. Complete Foot/Unit depth integration remains next.

[Map finalization with actual floor height](docs/RESIDENT_FLOOR_1006.md) now
matches 268 fresh exact-engine scenarios, including 816 nested floor queries and
a height-dependent wall-owner change. The new profile reads the shared Cell after
recalculation; earlier supplied-height proofs retain their scope. Initial global/
type/actor records remain supplied. The helper is not wired into the application;
terrain-aware unit depth/crossing remains next. Existing playable demo:
`./run.command --crossing-light-demo`.

[Cell and map floor height](docs/MAP_FLOOR_HEIGHT_1006.md) now have 4,279 fresh
exact-engine sequences / 13,382 matching queries, including all 20 ramps, lazy
state reuse, map aliases/fallback and actor-relative subtraction. Initial global/
map/actor state remains supplied; the helper is unwired. Prepared-map terrain
depth and crossing/cliff integration remain next; the existing demo is unchanged.

[Overlay-bearing map finalization](docs/RESIDENT_FINALIZATION_1006.md) now joins
the later two-pass parent to actual shared resource/Cell/LAT/passability/TMP,
lighting and wall-owner children. Thirty-five fresh exact-engine scenarios and
both replays pass, including all 13,515 map positions / 660 decoded overlays in
three cliff-mode fixtures. Initial terrain/type/actor/height inputs remain supplied;
the helper is unwired and runtime depth stays neutral. Terrain-aware crossing/
cliff integration remains incomplete. The existing demo is unchanged:
`./run.command --crossing-light-demo`.

[Wall ownership](docs/MAP_WALL_OWNER_1006.md) verifies the later map pass's
nearest eligible building selection and nested Cell-target distance/getters:
637 fresh exact-engine results and both replays. Terrain height and actor/house
construction remain supplied. The helper is unwired; overlay-bearing map-parent
integration and terrain-aware crossing/cliff depth remain next.

[Resident overlay preparation](docs/RESIDENT_OVERLAY_1006.md) now nests actual
Cell/LAT/passability/TMP children inside shared reader/placement/wall/resource
updates. Nine fresh original/native scenarios and both replays pass, including
all 660 supplied-map overlays; a targeted constructed-null-image probe also passes.
The later map parent and Foot/world/runtime depth integration remain next.

[Shared resident Cell recalculation](docs/RESIDENT_CELL_1006.md) joins actual
LAT, overlay classification, passability, permission and TMP reads on mutable
Cell state: 784 fresh exact-engine cases and both replays pass. Affected earlier
map proofs are freshly regenerated with unchanged outputs. Shared overlay
placement/map-parent wiring and terrain-aware crossing/cliff remain next;
the playable baseline and neutral runtime depth are unchanged.

[Initialized resource map inputs](docs/RESOURCE_MAP_INPUTS_1006.md) now feed
constructor/INI-derived records into shared overlay preparation. Nine fresh
original/native scenarios and both replays include all 660 supplied-map overlays.
Original phases are separately audited with an explicit record-transfer boundary;
startup ordering, actual Cell recalculation and runtime integration remain open.

[Resource type inputs](docs/RESOURCE_TYPES_1006.md) verify construction,
numeric-key lists and INI/Image association in 1,261 fresh exact-engine cases and
both replays, including all four supplied rules entries. Base/parser/color/vector/
animation/heap services remain supplied. The helper is unwired; shared Cell/map
preparation still precedes runtime promotion. Try the existing crossing with
`./run.command --crossing-light-demo`.

[Shared overlay resource updates](docs/OVERLAY_MAP_RESOURCES_1006.md) bind the
decoded reader/placement/lifetime/wall path to actual resource classification and
neighbor updates. Nine fresh exact-engine scenarios and both replays include all
660 supplied-map overlays. Resource records remain explicit diagnostic inputs;
original initialization and Cell terrain/passability recalculation still precede
runtime integration. The playable baseline remains unchanged.

[Shared overlay map preparation](docs/OVERLAY_MAP_PREPARATION_1006.md) joins the
decoded reader, temporary base construction, ordinary/wall placement, wall updates,
retirement and cleanup on shared Cells. Ten fresh exact-engine scenarios include
all 660 supplied-map overlays / 13,515 Cells, with normal and sanitizer replays.
Resource/Cell recalculation effects remain services and runtime wiring is pending;
terrain-aware crossing/cliff integration remains the active capability.

[Wall construction and shared update](docs/OVERLAY_WALL_CONSTRUCTION_1006.md)
join constructor/Unlimbo/Mark with actual wall-update children on shared Cells:
1,560 fresh exact-engine cases and both replays. Owner/neighbor effects now
execute together; base lifetime, decoded reader and actual Cell effects remain
separate boundaries. Fresh affected placement/lifetime suites pass. The helper
remains unwired; the terrain-aware crossing/cliff capability is still incomplete.

[Wall connections and update](docs/MAP_WALL_UPDATE_1006.md) add 4,640 fresh
exact-engine results and both replays. Actual connection/damage-removal decisions,
shared five-Cell update order and passability-dependent map notifications now have
a readable native projection. Image bounds/queues/lookup/Cell recalculation remain
services; wall placement/constructor/reader nesting and runtime are pending.
The same terrain-aware crossing/cliff capability remains incomplete.

[Loaded wall placement](docs/OVERLAY_WALL_PLACEMENT_1006.md) adds 2,000 fresh
exact-engine results and both replays: wall write order, loaded permission,
owner assignment and eight wrapped neighbor increments. The wall connection/
redraw parent remains a supplied service; constructor/reader/runtime integration
is pending. Shared-source changes have fresh ordinary placement-v4/lifetime-v3
proofs. This continues the same incomplete terrain-aware crossing/cliff capability.

[Temporary Overlay base construction and cleanup](docs/OVERLAY_OBJECT_LIFETIME_1006.md)
adds 3,681 fresh exact-engine results and both replays. Actual Abstract/Object
construction, retirement and nonempty cleanup/Overlay destruction now join
ordinary placement. Heap/broadcast/RTTI/base destruction and Cell effects remain
services. The helper is unwired and not yet nested into the reader; terrain-aware
crossing/cliff integration remains incomplete. Earlier inspection-only labels
below retain their historical suite scope.

[Ordinary temporary Overlay placement](docs/OVERLAY_PLACEMENT_1006.md) adds
1,180 fresh exact-engine results and both replays. Constructor/Mark/Object Unlimbo
and identity counter children verify Cell write order and retirement requests.
Base construction, resource/recalculation and retirement effects remain services;
walls/bridges/animation and reader/runtime integration are still pending. This
continues the same incomplete terrain-aware crossing/cliff capability.

[Decoded overlay map loading](docs/OVERLAY_LOADING_1006.md) adds 1,111 fresh
exact-engine results and both replays. The complete reader verifies registry-slot
selection, full-map permission, type-before-data order and special data restoration.
The tracked private-fixture tool reproduces the owned decoded input. Parsing,
image availability and temporary Overlay placement effects remain supplied; the
helper is unwired. Terrain-aware crossing/cliff integration remains incomplete.

[Overlay registry and INI inputs](docs/OVERLAY_TYPES_1006.md) add 1,349 fresh
exact-engine results: selected constructor defaults, duplicate/none resolution,
list ordering and overlay INI decisions. The complete list parent also executes
on all 243 supplied rules entries. Base construction/parsing, image/heap services
and map-pack loading remain supplied or pending; these helpers are unwired.
This continues the same terrain-aware crossing/cliff capability.

[Overlay Cell decisions](docs/OVERLAY_CELLS_1006.md) add 6,795 fresh exact-engine
results and normal/sanitizer replay: resource classification/update, empty overlay
passability and complete Cell recalculation with actual classification/permission/
passability children. Preserve early-path level/height and buffer order, distinct
zero/0.01 speed predicates, signed resource ranges and remainder-based frames.
That suite supplies type/default/INI/registry/loading inputs; the preparation parent
still refuses overlays and these helpers remain unwired. This is another
prerequisite of the same map-depth crossing/cliff capability, not a completed gameplay milestone. Current ordinary
regressions are Cell attributes/preparation v4, map-preparation-v5 and resident-map-v4.

[Resident map preparation](docs/RESIDENT_MAP_1006.md) now binds the recovered
parent to shared native Cell/LAT/passability/permission/TMP children and the verified
Wheel speeds. **51 fresh original/native results** and both replays include all
13,515 supplied records with 268 resident primary images. Scenario callers are
inspected separately: loaded Cells are revisited before and after actor loading.
The fixture deliberately omits overlays/actors/palette allocation and supplies
initial/type/table state. The helper remains unwired; terrain-aware Foot/world
crossing and cliff integration is still incomplete. No new gameplay/frame fidelity
claim follows. Recovery commands and limits are in the linked note.

A bounded native C++20/SDL3 prototype: load an original base Red Alert 2 map,
render its original terrain and one Rhino heavy tank, select it, independently
turn its body/turret, and move across unobstructed level ground.

[Land-characteristic assignment](docs/LAND_CHARACTERISTICS_1006.md) now verifies
ordered INI-result consumption, capping and float32 stores in all four supplied
rounding modes: 196 fresh original/native results and both replays. Original text
parsing and initial table state remain supplied; this helper is unwired. It also
establishes that ordinary empty-cell passability reads the Wheel speed column.

[Ordinary map cell preparation](docs/MAP_PREPARATION_1006.md) now verifies the
two-pass parent with actual shared-state Cell recalculation and lighting: 65 fresh
original/native results and both replays. The owned-record fixture deliberately
has no loaded images; construction, bridge/zone preparation and runtime Cell-to-Foot
integration remain pending. This prerequisite leaves the playable prototype unchanged.

[Tile usage and image sweep](docs/TILE_SWEEP_1006.md) now joins the actual map
iterator, selector/RNG and lazy TMP/color children: 129 fresh original/native
results and both replays, including usage traversal over all 13,515 decoded map
records. File/heap/construction/initial RNG state remain supplied. Broader map
preparation and Cell-to-Foot depth integration are pending; this helper is unwired.

[Cell tile variants and the RNG step](docs/TILE_VARIANTS_1006.md) now verify
first-use table initialization, generator consumption and signed sub-tile
coordinates: 320 fresh original/native results and both replays. Initial RNG/cache
state and original tables remain supplied; seeding/lifetime and broader map
initialization are pending. The parent is now verified above; this helper is unwired.

[Loaded theater associations](docs/THEATER_TILE_FILES_1006.md) now verify ordered
filename/marble fallback requests, primary/alternate links and loaded TMP color
preparation: 135 fresh original/native results and both replays. INI/file-cache/
heap/vector services remain supplied; Cell variant selection and broader map
initialization are pending. This helper is unwired and leaves runtime fields neutral.

[Loaded TMP preparation](docs/TILE_IMAGE_1006.md) verifies the lazy image loader,
selected metadata and all 26 color-ramp words per present sub-tile: 390 fresh
original/native results and normal/sanitizer replays, including supplied clear,
cliff and slope images. File/heap/vector services remain supplied; complete
theater file/type/variant association and map initialization are pending. This
assets-only prerequisite leaves runtime neutral tile/contact fields in place.

[Initial map geometry](docs/MAP_GEOMETRY_1006.md) now verifies initial cell
creation, buffer numeric/fill inputs and visible-rectangle bounds: 1,067 fresh
original/native results and normal/sanitizer replays. Original creation produces
13,515 cells for the supplied 80x85 map. Heap/zone/light/graphics services remain
supplied; complete map loading and loaded-image/type association are pending.
This preparation checkpoint leaves runtime neutral fields in place.

[Selected theater tile inputs](docs/THEATER_TILE_INPUTS_1006.md) now verify the
General set-number to tile-base associations, ordered index shifts and selected
type defaults: 481 fresh original/native results and both replays, including all
838 supplied temperate primary types with images deliberately absent. This also
corrects the Cell guard's provisional `morphable` name to `shadowCaster`; affected
Cell suites have fresh v3 receipts. Loaded-theater/full initialization and
Foot integration remain pending; selected initial geometry is verified above.
No new playable capability is claimed here.

[Decoded map-cell inputs](docs/MAP_CELL_INPUTS_1006.md) now have 537 fresh
exact-patched results and normal/sanitizer replay, including the original reader
over all 13,515 supplied map records. This is a prerequisite for map-depth
initialization; it adds no playable feature and leaves neutral runtime tile/contact
fields in place pending original map initialization/association. Commands and limits are in
the linked note.

[Ordinary Cell recalculation](docs/MAP_CELL_ATTRIBUTES_1006.md) adds 2,816 fresh
results and both replays with actual resident TMP/index children. LAT/passability
remain supplied services; original map-depth initialization and runtime wiring
are still pending. This is another prerequisite of the same crossing/cliff work.

[Cell connectivity and empty passability](docs/MAP_CELL_CHILDREN_1006.md) now
add 5,888 fresh results and both replays, including actual map permission/lookup
children. The complete recalculation join follows below; original map
initialization order remains pending and the playable renderer is unchanged.

[Complete ordinary Cell recalculation](docs/MAP_CELL_PREPARATION_1006.md) now
nests those actual children in 1,536 fresh results and both replays, including
different post-connectivity tile metadata. Theater/type/map construction and
runtime association remain pending; neutral runtime fields are retained.

The current patched renderer uses the [complete healthy Unit drawing chain](docs/UNIT_CALLER_WORLD_1006.md):
ordinary visibility/DrawIt, current-cell brightness, settled stock barrel pitch,
body/turret/barrel staging and compressed caches, final world surfaces and shadows.
Run `./run.command --crossing-light-demo`, select the Rhino, then press **G** or
right-click to move; **L** toggles the host-placed light and **R** resets the tank.
The native scenario checks movement through changing cell light, scenery occlusion,
cache reuse/bypass, clipping and no trails. Camera, visibility, actor/map initialization,
pool ownership/lifetime and UI remain bounded host policies; whole-frame parity is open.
The complete join passes 56 fresh exact-binary cases and normal/sanitizer replay;
79,978 eligible earlier original results replay per build. These scoped comparisons
and actual SDL checks do not establish original whole-frame fidelity.
Build with `./build.command`; run owned-data regressions with
`./test.command --data-dir "$PWD/private/official-1006-probe"`.

The checkpoint descriptions below retain their historical scope. Statements that
these helpers are unwired or that runtime uses flat barrel pitch are superseded
by the current integration note above; their original evidence is unchanged.

Milestone 20 delivers a [moving Rhino/scenery crossing](docs/CROSSING_1006.md).
Run `./run.command --crossing-demo`, select the Rhino, press **G** to move past
the traffic light, and **R** to reset. It uses recovered ordinary static/dynamic
traversal and Unit eligibility on the supplied 1.006 dataset. Actual SDL input,
79 sampled frames, partial/offscreen clipping and no-trail checks pass. This is
native integration evidence; original whole-frame/input/scheduler parity is open.

The next drawing checkpoint now verifies the [ordinary Unit DrawIt caller and
screen registry](docs/UNIT_DRAW_CALLER_1006.md): 9,167 fresh exact-patched results,
including the actual visibility gate nested around it, with normal/sanitizer replay.
That new kernel remains unwired while stock inputs and child dispatch are recovered.
[Unit image selection and scoped constructor fields](docs/UNIT_TYPE_VISIBILITY_1006.md)
now add 20,442 fresh original/native cases and both replays, with actual nested
owner/alliance/cell decisions and the original drawing-timer branch. The caller
has a fresh 9,167-case regression after that change. Full stock construction,
voxel child dispatch and runtime wiring remain open.
[Selected HTNK metadata and boolean values](docs/UNIT_METADATA_1006.md) add
9,138 fresh original/native results and both replays. The base type field formerly
called `simpleDeployer` is verified as **Harvester**. The native asset loader now
uses original first-byte boolean decisions and guards the ordinary voxel/turret
profile. The affected caller/type regressions have fresh source-matched receipts;
full type construction and voxel child dispatch remain open.
[Foot lit-part forwarding](docs/FOOT_LIT_1006.md) adds 2,263 fresh exact-patched
results and both replays, including actual Drive offsets and nested Techno cache
dispatch. Its native helper remains unwired pending complete Unit voxel drawing.
[Healthy Unit voxel caller](docs/UNIT_VOXEL_DRAW_1006.md) now adds 3,200 fresh
original/native scenarios and both replays, executing the complete root with
actual Drive/Foot/matrix/cache-precheck children. It preserves warm-image pose
decisions and later shadow key/stencil selection. Final drawing/surface services
remain supplied; caller/runtime integration is still open.
[Final Unit surface wrapper](docs/UNIT_SURFACE_1006.md) adds 5,602 fresh
original/native results and both replays, including actual house selection,
healthy layer dispatch and complete ordinary final surface/RGB565 pixels.
Field construction remains supplied; the helper is unwired.
[Foot depth and gradient](docs/FOOT_DEPTH_1006.md) add 5,952 fresh exact-patched
results and both replays, with all five complete cell predicates and actual
healthy base depth nested into final surface pixels. Stock field/map association
and runtime wiring remain open.
[Stock drawing metadata](docs/UNIT_DRAW_METADATA_1006.md) adds 3,330 fresh
results and both replays. HTNK enables `TooBigToFitUnderBridge` and uses
Cliff/Column/Tunnel/Bridge values 10/8/13/0. Its [nonzero surface-selection and
split draw](docs/UNIT_SURFACE_SPLIT_1006.md) now add 3,264 fresh results and both
replays, including actual contact reads and both depth gradients' RGB565 pixels.
Original integer parsing, full type/model construction and complete child/runtime
integration remain open; the new helpers are unwired.
[Ordinary Unit model loading](docs/UNIT_MODELS_1006.md) adds 2,391 fresh
original/native protocol comparisons and both replays. Actual kind/count/section
getters execute inside the complete root; filename requests, missing optional
parts, failure cleanup and ordered cache reset are verified. File/allocator/parser
services, Image/default construction and runtime wiring remain open.
[Model image/count/offset inputs](docs/UNIT_MODEL_INPUTS_1006.md) now add 4,322
fresh original/native results and both replays, including actual ReadString/trim/
bounded-copy and missing integer fallbacks. Supplied HTNK resolves HTNK/0/0;
patched asset naming and stock guards use this result. Present integer decoding,
text/index construction, neutral actor fields and full drawing integration remain open.
[Scoped actor drawing state](docs/UNIT_DRAWING_STATE_1006.md) adds 2,347 fresh
original/native results and both replays: Facing constructors, status-timer
decisions and selected initial fields. Constructor barrel facing is zero; the
existing voxel fixture's neutral pitch still requires verified placement/type
initialization. This new helper remains unwired.
[FireAngle and ordinary placement](docs/UNIT_PLACEMENT_1006.md) add 1,588 fresh
original/native results and both replays, including actual stock initialization
followed by the complete Techno wrapper. The tested stock barrel settles at
facing 14336; the current flat-barrel presentation remains approximate pending
the nonneutral pose/cache path. Base placement/map/house effects remain supplied.
[Nonneutral barrel pose and cache decisions](docs/UNIT_BARREL_1006.md) now add
5,379 fresh complete-root results and both replays, superseding that pending pose
boundary. Stock pitch, every pitch bin and independent part-cache states match.
The drawing helper remains unwired; pitch-driven cache invalidation and complete
child integration remain open. Runtime still uses the earlier flat barrel pose.
[Staged voxel part rendering](docs/VOXEL_PART_1006.md) adds 342 fresh complete
wrapper/raster results and both replays. Actual light, optional HVA geometry,
projection and flush produce matching full indexed buffers and forwarding events.
Blitter selection/final staging copy remain services; this helper is unwired.
[Raster-to-staging integration](docs/VOXEL_PART_STAGING_1006.md) now adds 242 fresh
results and both replays with actual byte-converter selection and indexed copies.
The ordinary cache parent clears `0x2800` before the part call, selecting zero
flags for staging. Both raster/staging buffers match; the full Unit/cache join
and runtime wiring remain open.
[Compressed voxel snapshots and cached staging](docs/VOXEL_SNAPSHOT_1006.md)
add 584 fresh original/native results and both replays. Original row encoding,
partial pool failures and the complete cached byte-copy path match, including
actual stock raster-to-snapshot-to-cached staging pixels across all headings.
The Foot/cache parent is not nested by these fixtures; runtime wiring remains open.
[Nested Foot/cache staging](docs/FOOT_VOXEL_STAGING_1006.md) now joins that parent
to actual raster, compressed snapshot and cached drawing: 732 fresh results
including six resets, with normal/sanitizer replay. Cold/warm full-buffer/pool
and index states match for all three parts and headings. Sufficient supplied
pool/heap and healthy records remain explicit; the helper remains unwired pending
Unit/depth/shadow/final-surface integration.
[Complete Unit-to-staging integration](docs/UNIT_VOXEL_STAGING_1006.md) adds
286 fresh results including 20 resets and both replays. Actual Unit/Foot/cache/
raster/snapshot/cached children, independent part indexes, bounds and byte cleanup
now execute together. Full composed stencil/pool/index and post-clear state match.
The extracted Foot/Techno boundary has fresh 732-result receipts and both replays;
584 prior snapshot results also replay. This helper remains unwired pending actual
depth/final-surface/shadow children; the playable crossing remains unchanged.
[Joined Unit staging, depth and world pixels](docs/UNIT_VOXEL_WORLD_1006.md)
adds 284 fresh results including twelve resets and both normal/sanitizer replays.
Actual Foot/base depth and stock conditional split/RGB565 surfaces now execute
inside the complete Unit root. Full color/depth/alpha, stencil, pool and cache
states match under the bounded supplied map/plane profile. Shadow remains a
service; this helper remains unwired pending shadow and caller integration.
[Compressed Unit shadow drawing](docs/CACHED_VOXEL_SHADOW_1006.md) adds 160
fresh original/native cases and both replays, preserving world dirty bounds,
clipped RLE transparency and strict RGB565 depth reads. This child remains
unwired; actual fresh shadow rendering/cache-parent nesting is next.
[Complete shadow cache and world drawing](docs/SHADOW_VOXEL_WORLD_1006.md)
now joins actual fresh render, compressed snapshot, recursive cache hit and raw/
cached world spans: 402 fresh results including three resets and both replays.
All parts/headings, signed-key growth, frame-zero HVA, stencil/prechecks/bypass,
world pixels, pool and index state match. The helper remains unwired; nest it
in the complete Unit/world root with a fourth index before caller/runtime wiring.
[Complete Unit drawing and shadows](docs/UNIT_VOXEL_SHADOW_WORLD_1006.md)
now nests that actual shadow child inside the Unit/staging/depth/final-world root:
152 fresh results including eight resets and both replays. All four indexes share
the supplied pool; full pixels/stencil/cleanup/pool/index state matches. The helper
remains unwired pending ordinary DrawIt/current-cell-light caller integration and
the moving crossing acceptance; the existing playable renderer is unchanged.
[Terrain draw eligibility and bounds](docs/TERRAIN_VISIBILITY_1006.md) now have
9,364 fresh supplied-1.006 comparisons and normal/sanitizer replay. The
[static scenery scan](docs/STATIC_TRAVERSAL_1006.md) adds 3,292 scenarios and now
uses the original reverse layer order on that dataset.
[Per-frame Unit/Foot/Terrain traversal](docs/DYNAMIC_TRAVERSAL_1006.md) adds 2,808
fresh two-pass caller scenarios and both replays. It is now integrated on the patched profile;
[ordinary Unit draw eligibility](docs/UNIT_VISIBILITY_1006.md) adds 5,318 fresh
results and both replays. [Combined caller and secondary coordinates](docs/ACTOR_TRAVERSAL_1006.md)
add 6,225 fresh results and both replays, including actual nested Unit eligibility
and Foot/Drive getters. [Redraw requests and dirty regions](docs/REDRAW_1006.md)
add 17,272 fresh results and both replays. The [static request caller](docs/STATIC_REDRAW_1006.md)
adds 1,172 fresh nested results and both replays; its full-viewport branch is used
by the patched scenery rebuild. All seven suites replay 45,451 recorded original
results per build. Whole-viewport rebuilding remains a host policy; complete Unit
DrawIt, outer frame scheduling and actor ownership remain open.

**Working on Ivalice / Apple Silicon macOS 26.6.2.** The executable is arm64.
Windows and Linux are design targets, not tested platforms. This is an engine
reconstruction, not an OpenRA mod. No original executable runs inside the game.
The native runtime reads supplied local files and needs no mounted disc, original
Windows launcher or SafeDisc driver. Disc import is an optional preparation step.
The existing no-CD Windows builds are research/observation targets with separately
recorded hashes and modifications; they do not run inside the native app.

The user supplied patches targeting **RA2 1.006 / YR 1.001** and prefers them for
future recovery. The supplied RA2 patch has now been completely materialized:
its engine exactly matches the privately copied Windows engine. Facing plus bounded
Drive/curves/timing/targeting pass **125,073 comparisons on each engine**.
[Presentation primitives](docs/PRESENTATION_1006.md) now pass **8,568 cases /
312,208 values on each engine**. [Voxel loader/pose/raster profiles](docs/RASTER_1006.md)
now pass **707 results on each engine**, including 192 complete indexed buffers
per engine and both sanitizer replays. [World/TMP/unit composition](docs/COMPOSITION_1006.md)
passes **424 fresh results on each engine**, including complete color/depth surfaces
and both sanitizer replays. [Shadows and player colors](docs/SHADOW_COLOR_1006.md)
pass **9,812 fresh results on each engine**, with bounded caller/input/write audits
and both sanitizer replays. [Indexed staging and shadow-index profiles](docs/STAGING_1006.md)
pass **2,600 fresh behavior cases plus three resets on each engine**, with both
sanitizer replays. [Ordinary map lighting and visible alpha](docs/MAP_LIGHTING_1006.md)
pass **17,510 fresh results on each engine**, with both sanitizer replays and
bounded caller/input/write audits. [Static-source profiles](docs/STATIC_LIGHT_1006.md)
pass **2,574 fresh results on each engine**, with both sanitizer replays and
scoped audits. [Ordinary unit lighting](docs/UNIT_LIGHTING_1006.md) passes
**3,257 fresh results on each engine**, including complete house palettes/surfaces,
RGB565 constructor inspection, bounded audits and both sanitizer replays.
[Lit voxel-cache keys/reuse](docs/VOXEL_CACHE_1006.md) passes **4,743 fresh protocol
results on each engine** (4,730 behavior cases plus 13 resets), with both sanitizer
replays and scoped caller/input/heap/supplied-write audits. [Flat Unit shadow keys/
Foot dispatch](docs/SHADOW_KEYS_1006.md) passes **2,204 fresh protocol results per
engine** (2,203 behavior cases plus one reset), including complete masks/crops, both
sanitizer replays and scoped audits. [Ordinary scenery, trees and props](docs/SCENERY_1006.md)
pass **2,356 fresh results on each engine**, with both sanitizer replays and explicit
SHP wrapper patch differences. [Ordinary occupation/lifecycle and layers](docs/TERRAIN_LIFECYCLE_1006.md)
pass **17,340 fresh results on each engine**, with all four sanitizer replays,
ordered-write/arena/caller audits and equality to retained disc expectations.
[MIX primitives and bootstrap requests](docs/ARCHIVES_1006.md) pass **5,344 fresh
results per engine**, both sanitizer replays and 84 separate original-only
assertions. [Later-startup and theater requests](docs/ARCHIVE_SEQUENCE_1006.md)
pass **688 fresh results per engine**, both sanitizer replays and independently
inspected language/bootstrap bridge ordering. Effective patched inputs now have
an [initial reader and private source audit](docs/EFFECTIVE_ASSETS_1006.md):
**317 queries per engine on decoded-index original fixtures**, both sanitizer
replays, and only game.exe/rules.ini differ. The [coordinated native promotion](docs/PROMOTION_1006.md)
now runs that supplied 1.006 dataset, with source-matched prepared inputs and
**180,573 original expectations replayed per profile/pass** on normal and sanitizer
builds. Both profiles pass actual SDL input/rendering checks. These are scoped
original expectations and native integration, not whole-game or whole-frame parity.
See [1.006 evidence and commands](docs/BASELINE_1006.md),
[Drive migration and regression commands](docs/DRIVE_1006.md),
[baseline transition](docs/PATCH_BASELINE.md) and
[mike-gaming original-game research](docs/WINDOWS_TESTING.md).

Milestone 19 prepares **565 ordinary scenery actors** through recovered ground
placement/removal and layer registration. **3,868 new original/native results
pass**, including a **1,695-call whole-map place/remove/restore sequence**. Drawing
uses the registered scenery order and projected coordinates. Construction/storage,
immutable-layer rebuilding, visibility and mixed tank/scenery scheduling remain
host boundaries or open; clearance stays conservative. See
[lifecycle evidence and limits](docs/LIFECYCLE.md).

Milestone 18 prepares **original occupation and cell membership for 565 scenery
placements**. **13,472 new original/native results pass**, including complete
ordinary Object/Terrain Mark decisions, ordered cell/member writes, signed
coordinates and all supported map placements. `ra2-inspect` reports these states.
Route exclusions remain conservative; locomotor clearance/pathfinding, global
scheduling and complete actor lifecycle remain open. See
[occupation evidence and boundaries](docs/OCCUPATION.md).

Milestone 17 renders **565 ordinary scenery placements across 30 map types**:
531 trees plus 34 signs, traffic lights, headstones and a pole. All **23 supplied
ordinary prop images** are checked against original draws, including SIGN03..06
raw bodies and compressed shadows. **808 new original/native results pass**,
including complete color/depth surfaces with actual 27/53-row converters.
Press **P** to inspect props, **T** for all scenery, **H** for the Rhino.
Alternate/animated terrain, actor occupation/ordering/lifecycle and whole-frame
parity remain open. See [prop and raw-SHP evidence](docs/PROPS.md).

Milestone 16 renders **531 original trees across 22 map types**. All 28 supplied
ordinary tree images have been checked against original draws. **1,128 new
original/native results pass**, including complete theater-image reload decisions,
ordered type writes and signed strength defaults. Snow/Urban filenames are verified;
runtime presentation remains temperate only. See [tree type evidence](docs/TREE_TYPES.md).

Milestone 15 draws all **27 original TREE01 placements** in the selected map,
using the original SHP body and shadow frames, terrain lighting and depth writes.
**420 new original/native results pass**, including complete healthy Terrain calls,
compressed SHP color/depth surfaces and ordinary LightConvert tables. Press **T**
to inspect successive trees; **H** returns to the Rhino. Other scenery, original
actor ordering/lifecycle and whole-frame parity remain open. See
[scenery evidence](docs/SCENERY.md).

Milestone 14 recovers **flat Unit shadow keys and Foot shadow dispatch**.
**2,203 new original/native behavior cases pass** (2,204 protocol results),
including 129 complete selected masks/crops. The stock Rhino's Track branch is
verified through its Crusher-dependent type default. Nonflat/status branches,
shared pool/lifecycle and whole-frame parity remain open. See
[shadow key evidence](docs/SHADOW_KEYS.md).

Milestone 13 replaces the matrix-based lit-part cache with **original actor keys
and successful cache reuse**. **4,730 new original/native behavior cases pass**
(4,743 protocol results), including 312 complete selected voxel buffers and crops.
The stock zero-offset turret/barrel reuse images across body turns. Shared pool,
actor lifetime and whole-frame parity remain open. See
[voxel cache evidence](docs/VOXEL_CACHE.md).

Milestone 12 separates **unit brightness from house colors**. The Rhino uses cell
ambient plus rules ExtraUnitLight and its house's neutral-tint ColorScheme converter.
**3,257 new original/native cases pass**, including every supplied named-color
converter and 182 complete clipped color/depth surfaces. The stock spawn brightness
is 1312, or 1491 near the demo light. Local source tint affects terrain separately.
House creation/assignment, converter lifetime, visibility and full-frame parity remain open.
See [unit and house lighting evidence](docs/UNIT_LIGHTING.md).

Milestone 11 adds one stock invisible **INGALITE** source, immediate reversible
activation/deactivation and original terrain converter decisions. **2,574 new
original/native cases pass**, including source construction, cell visit order,
all 13,515 map-cell records, 1,524 converter decisions and zero-intensity skips.
Use `./run.command --light-demo` and press L. Stock sources require graphics
detail 2; `--detail 1` demonstrates the recovered gate. Demo placement, full actor/house
initialization, fully visible alpha and redraw/cache ownership remain explicit adapters.

Milestone 10 replaces the direct map-light-to-alpha formula with original integer
cell-light inputs and separate visibility alpha. **17,510 new original/native cases
pass**, including every supplied map cell, overlapping source kernels, tint
normalization, eight complete alpha buffers and 96 complete lit color/depth surfaces.
The tested map has no emitting buildings; milestone 11 extends its explicit source
kernel to one healthy placed INGALITE. Other emitter profiles are refused.

Milestone 9 assembles body/turret/barrel on an original indexed staging surface,
then makes one final world blit. **2,600 new original/native behavior cases pass**,
including 128 complete staged unit/shadow/world surfaces and 1,686 successful
shadow wrapper/cache decisions (plus three test-protocol resets). The theater
palette remap, dirty bounds, source-zero transparency and shadow miss/hit/bypass
flow are recovered; milestones 13/14 extend flat lit/shadow keys; shared pool lifetime remains open.

Milestone 8 adds original occupied-column shadows and player ColorScheme ramps:
**9,812 original/native cases pass**, including complete shadow masks and clipped
RGB565/depth surfaces. Use `--player-color DarkBlue` or C to change the tank's color.
Milestone 7 adds recovered ordinary world projection, TMP depth and final unit
composition: **424 original/native cases pass**, including complete RGB565/depth
surfaces. Units now read terrain depth without writing it; terrain accepts ties,
and barrel/turret painting order follows original direction rules.
Milestone 6 replaced cube triangles with original indexed voxel span rendering.
**192 complete 256×256 section buffers match the original**, alongside 128 pose
cases, 192 matrix products and 192 full lighting setups. The original 32-bin render
headings and lookup-table camera rotations are preserved. Simulation retains its
finer facing angles. Earlier **125,073** movement/timing comparisons and **8,568**
presentation cases (312,208 values) still pass.
General light actor lifecycle, fog, special/status depth branches, shadow actor selection,
house initialization/assignment, zoom/UI and cache lifetime remain adapters; this is not
whole-screen parity.
Routing and controls remain bounded adapters too.
See [static-source evidence](docs/STATIC_LIGHT.md),
[map-light input evidence](docs/MAP_LIGHTING.md), [indexed staging/cache evidence](docs/STAGING.md),
[shadow and player-color evidence](docs/SHADOW_COLOR.md),
[composition evidence](docs/COMPOSITION.md), [voxel raster evidence](docs/RASTER.md), [presentation evidence](docs/PRESENTATION.md), [curved tracks](docs/CURVES.md),
[timing and targeting](docs/TIMING_TARGETING.md), [movement](docs/MOVEMENT.md),
[original identity](docs/RECOVERY.md), [public reference workflow](docs/REFERENCES.md),
and the [handoff](docs/HANDOFF.md).

## Try the prepared prototype on this Mac

```sh
cd /Volumes/Lesalia/Code/redalert2-native
./build.command
./run.command
# One original invisible light near the Rhino; L toggles it:
./run.command --light-demo
# Reproducible moving Rhino / traffic-light crossing (supplied 1.006 only):
./run.command --crossing-demo
```

`run.command` prefers the already prepared `private/official-1006-probe` folder,
falls back to `private/game`, and honors `--data-dir` or `RA2_DATA_DIR`. The verified
GAME.EXE hash selects matching direction/render/raster defaults: `private/derived/ra2-1006`
for the supplied patch, `private/derived` for the retained disc. Mixed source overrides
are refused. Both sets are already prepared. Double-clicking `run.command` in Finder launches it from Terminal.
It remains a development build and requires the installed Homebrew libraries.

Or supply another legitimate installation explicitly:

```sh
./run.command --data-dir "/absolute/path/to/owned/RA2"
# Equivalent:
RA2_DATA_DIR="/absolute/path/to/owned/RA2" ./build/native/redalert2-native
```

The default map is `mp03t4.map`, an original 80×85 temperate multiplayer map with
13,515 cells. The prototype creates one demonstration Rhino near waypoint 0;
it does not instantiate that map's match, houses, other units or triggers.
Terrain, healthy static TREE01..28 and ordinary prop images are visible. The eight
alternate/animated Tiberium trees, other objects and overlays remain omitted.
Original object/overlay locations, including drawn scenery,
retain conservative route exclusions; locomotor clearance/pathfinding remains unrecovered.

| Control | Action |
| --- | --- |
| Left-click Rhino | Select; clicking elsewhere deselects |
| Right-click | Direct route to the clicked cell center, up to 23 pending cells; yellow marker shows the endpoint |
| Ctrl + right-click | Append a waypoint to the pending route |
| Shift + right-click | Aim the turret independently |
| Q / E | Request a 45-degree body turn; finish the active track before turning |
| A / D | Manual 45-degree turret turn; next move restores automatic following |
| S | Finish the active track using the original capped stop speed |
| Arrow keys / mouse wheel / + and − | Pan / zoom |
| H / R | Center on tank / reset prototype |
| T / P | Cycle the camera through all ordinary scenery / props only |
| G (crossing demo) | Order the selected Rhino through the fixed crossing; R resets |
| [ / ] | Slower / faster game speed, positions 0–6; 6 is uncapped |
| C | Cycle supplied rules.ini named color schemes; default DarkRed |
| L | Toggle the one static light, if present; source updates require detail 2 |
| Space / Escape | Pause / quit |

Controls and direct-route selection are temporary and displayed in the window.
Color selection is a host adapter rather than an original house assignment. Choose
a named scheme at launch with `./run.command --player-color DarkBlue`; names are
case-insensitive and unknown names fail. Remap affects only palette indices 16–31.
One healthy stock INGALITE in Structures is supported without changing the map;
other emitters, multiple emitters and map emitter-type overrides fail explicitly.
Placed structures retain conservative route exclusions and can change the demo spawn.
`--light-demo` supplies placement and initial activation as a host demonstration.
Graphics detail defaults to 2; use `--detail 0` or `--detail 1` for the recovered
lower-detail terrain tint masks and stock-source gate. The light's active state
can remain ON while detail prevents its contribution. R resets only the tank.
The route takes diagonal cells first, then the remaining axis; it does not search
for detours. The drive chooses original curves from those queued directions.
Waypoints define direction changes, not mandatory intermediate stops. Retargeting
a moving stock Rhino finishes its committed track, which can span two cells,
before following the new route. This non-passive Unit behavior is checked against
the original process. Clearance previews the actual curved motion with a sampled
footprint. Slopes, different elevations, omitted objects, overlays and unsupported
terrain are rejected. A rejected order leaves the existing move active.
Without manual aim, the turret aims at the movement destination; after the
coordinate target clears, it follows the body through the recovered update. Manual aim overrides that following until another move command.

Game speed defaults to 3. Set it at launch with `./run.command --speed 5`.
The recovered skirmish timer uses 16 ms quanta; its nominal speed-3 span is 48 ms.
Actual throughput depends on processing and host scheduling. Every simulation update is presented; the camera/UI also refreshes during waits.
There is no overdue simulation catch-up burst.

## Build dependencies

Tested: Apple clang 21.0.0, Command Line Tools, CMake 4.4.4, SDL 3.4.2, OpenSSL
3.6.1, LZO 2.10, and the macOS SDK zlib interface. No Xcode license was accepted
and system-wide tool selection was not changed. `build.command` honors an existing
`DEVELOPER_DIR`, otherwise uses the installed Command Line Tools for that process.

On a new Mac with Homebrew, install the missing development libraries yourself:

```sh
brew install sdl3 openssl@3 lzo
python3 -m venv build/tools-env
build/tools-env/bin/python -m pip install cmake==4.4.4
./build.command
```

Initial setup installed only the project-local Python environment; the Homebrew
libraries already existed. Milestones 5–18 add no dependencies. The generic CMake equivalent is:

```sh
cmake -S . -B build/native -DCMAKE_BUILD_TYPE=RelWithDebInfo \
  -DCMAKE_PREFIX_PATH=/opt/homebrew
cmake --build build/native --parallel 6
ctest --test-dir build/native --output-on-failure
```

CMake finds SDL3, OpenSSL Crypto, LZO2 and zlib. Set `CMAKE_PREFIX_PATH` for other
installations. `-DRA2_BUILD_SDL=OFF` builds only the headless libraries and tools.
There is no automatic dependency or game-content download in CMake.

## Import the supplied disc without running its installer

The user's Allied disc is ISO9660 on MODE1/2352 sectors. The importer also accepts
2048-byte ISO images. It opens the image read-only, copies a fixed set of files,
refuses overwrites, and records the source member paths and SHA-256 values.
It does not mount discs, install drivers, or execute Windows code.

The following has **already been done** here. For a fresh checkout, run once:

```sh
python3 tools/import_disc.py \
  "$HOME/Downloads/Command & Conquer - Red Alert 2 (USA, Europe) (Allied Disc).bin" \
  --output private/disc-allied
mkdir -p private/game
bsdtar -xf private/disc-allied/game1.cab -C private/game
cp -n private/disc-allied/multi.mix private/disc-allied/maps01.mix \
  private/disc-allied/game.exe private/game/
python3 tools/prepare_direction_data.py --exe private/disc-allied/game.exe
python3 tools/prepare_render_data.py --exe private/disc-allied/game.exe
python3 tools/prepare_raster_data.py --exe private/disc-allied/game.exe
python3 tools/prepare_visibility_data.py --exe private/official-1006-probe/game.exe
```

`game1.cab` is a standard Microsoft Cabinet containing `ra2.mix` and
`language.mix`. macOS bsdtar extracts it locally. Runtime requires `ra2.mix` and
`multi.mix` for the default map and the matching `game.exe` for its original drive
track tables. It handles nested/encrypted MIX indexes itself. The runtime hashes
and reads the executable as **data only**; it never maps or executes its code.
Direction, rendering and the supplied-patch visibility mask lookup tables are
prepared separately under ignored `private/derived/`, keeping runtime executable
access limited to track data. Use
`--direction-data`, `--render-data` and `--raster-data` to supply generated files from another
private location. Preparation refuses
to write within the source installation. Unknown executable versions fail closed. The supplied executable must remain
user-provided and outside any distribution. Source media are never modified.
Loose leaf files in a supplied folder override archive members for research/mod
inspection; the prepared `private/game` contains original top-level archives and the supplied
executable. No extracted asset override is needed.
The application uses the bounded initial archive registration described in
[EFFECTIVE_ASSETS_1006.md](docs/EFFECTIVE_ASSETS_1006.md), including descending
available expansion requests. This does not enable expansion gameplay. The supplied
1.006 dataset now has its own verified table profile and effective input audit; keep
it and its prepared files separate from the retained disc folder. Preparation and
verification commands are in [PROMOTION_1006.md](docs/PROMOTION_1006.md).

The Soviet and Yuri's Revenge images were located but not imported or used.
Yuri's Revenge remains the next engine family after base RA2 recovery, with its
own fingerprints and verification. No findings are silently shared between builds.

## Verification

Synthetic tests use no proprietary data:

```sh
./test.command
```

Owned-data tests load all map terrain and tank parts, rasterize them, then verify
normal/VPL/player-palette integration, shadows, independent headings, cliff and
tree occlusion, static tree lighting, selection, turns and movement through
injected SDL events. They also check unsupported scenery profiles and export guards:

```sh
./test.command --data-dir "$PWD/private/official-1006-probe"
build/native/ra2-inspect private/official-1006-probe mp03t4.map build/preview.ppm
build/native/presentation-check private/official-1006-probe build/presentation
build/tools-env/bin/python tests/check_unit_metadata_assets.py --data-dir private/official-1006-probe
# Milestone 20 moving scenery crossing (native integration; private diagnostics):
build/native/crossing-check private/official-1006-probe private/crossing-headless
build/native/redalert2-native --data-dir private/official-1006-probe \
  --crossing-smoke-test private/crossing-sdl
# Or a headless frame without opening a window:
build/native/redalert2-native --data-dir private/official-1006-probe --render build/preview.ppm
# macOS conversion for convenient viewing:
sips -s format png build/preview.ppm --out build/preview.png
```

For a real-clock smoke of the normal SDL loop:

```sh
./run.command --speed 3 --timing-smoke-test
```

For the independent original-routine oracles:

```sh
build/tools-env/bin/python -m pip install -r requirements-research.txt
build/tools-env/bin/python tests/compare_original.py \
  --exe private/disc-allied/game.exe
build/tools-env/bin/python tests/compare_movement.py \
  --exe private/disc-allied/game.exe
build/tools-env/bin/python tests/compare_timing_targeting.py \
  --exe private/disc-allied/game.exe
build/tools-env/bin/python tests/compare_curves.py \
  --exe private/disc-allied/game.exe
build/tools-env/bin/python tests/compare_presentation.py \
  --exe private/disc-allied/game.exe --data-dir private/game
# Raster fresh evidence exists on this checkout; replay it without original execution:
build/tools-env/bin/python tests/compare_raster.py \
  --exe private/disc-allied/game.exe --data-dir private/game \
  --expectations private/migration/allied-disc/raster/expected.json
build/tools-env/bin/python tests/compare_composition.py \
  --exe private/disc-allied/game.exe --data-dir private/game \
  --expectations private/migration/allied-disc/composition/expected.json
build/tools-env/bin/python tests/compare_shadow_color.py \
  --exe private/disc-allied/game.exe --data-dir private/game \
  --expectations private/migration/allied-disc/shadow-color/expected.json
build/tools-env/bin/python tests/compare_staging.py \
  --exe private/disc-allied/game.exe --data-dir private/game \
  --expectations private/migration/allied-disc/staging/expected.json
build/tools-env/bin/python tests/compare_map_light.py \
  --exe private/disc-allied/game.exe --data-dir private/game \
  --expectations private/migration/allied-disc/map-light/expected.json
build/tools-env/bin/python tests/compare_static_light.py \
  --exe private/disc-allied/game.exe --data-dir private/game \
  --expectations private/migration/allied-disc/static-light/expected.json
build/tools-env/bin/python tests/compare_unit_light.py \
  --exe private/disc-allied/game.exe --data-dir private/game \
  --expectations private/migration/allied-disc/unit-light/expected.json
build/tools-env/bin/python tests/compare_voxel_cache.py \
  --exe private/disc-allied/game.exe --data-dir private/game
build/tools-env/bin/python tests/compare_shadow_keys.py \
  --exe private/disc-allied/game.exe --data-dir private/game
build/tools-env/bin/python tests/compare_scenery.py \
  --exe private/disc-allied/game.exe --data-dir private/game \
  --expectations private/migration/allied-disc/scenery/expected.json
build/tools-env/bin/python tests/compare_terrain_types.py \
  --exe private/disc-allied/game.exe --data-dir private/game \
  --expectations private/migration/allied-disc/terrain-types/expected.json
build/tools-env/bin/python tests/compare_props.py \
  --exe private/disc-allied/game.exe --data-dir private/game \
  --expectations private/migration/allied-disc/props/expected.json
build/tools-env/bin/python tests/compare_occupation.py \
  --exe private/disc-allied/game.exe --data-dir private/game \
  --expectations private/migration/allied-disc/occupation/expected.json
build/tools-env/bin/python tests/compare_lifecycle.py \
  --exe private/disc-allied/game.exe --data-dir private/game \
  --expectations private/migration/allied-disc/lifecycle/expected.json
```

This fails closed on any executable hash mismatch. It uses isolated x86 memory,
no original game process and no modified instruction bytes. Facing/movement
checks need no Windows API stubs. Timing tests explicitly substitute timeGetTime
and Sleep with a deterministic clock; these are research-only test doubles.
The movement/curve suites substitute explicitly listed flat-world services for map,
occupation, neighbor-cell and mission access; their movement arithmetic and turret routines run
unchanged. This does not verify original pathfinding, combat targets or full missions.
Unicorn requires executable/JIT memory and SDL requires the Mac window server;
a restricted automation sandbox can block them. Run these commands from a normal
Mac terminal or an authorized execution context. They passed in that context here.
The native application does not link Unicorn or Python.
The presentation suite executes complete lighting, scalar RGB565 palette and
depth-span routines plus a VPL lookup block, with no API stubs. It supplies
primitive inputs and does not establish full-renderer or original-image parity.
Its VPL research copy is exported to ignored `private/presentation/` read-only
from the installation; different existing data and source-tree writes are refused.
The raster suite executes the original VXL loader with file/heap fixtures, then
original pose, lighting and complete section drawing without service callbacks.
It compares full indexed buffers, corner bits and crop fields before world
composition. Its read-only research exports stay under `private/raster/assets/`;
source-tree destinations, symlinks and replacement of different data are refused.
The composition suite executes complete original unit/TMP buffer-surface draws,
with explicit data/getter/cache fixtures. It compares RGB565 and depth planes;
it does not establish whole-actor, lighting-source or whole-screen parity.
Its new disc/1.006 profiles use protected receipts/exports under
`private/migration/<profile>/composition/`. Fresh evidence already exists on this
checkout; `--expectations` replays it without original execution. Omit that option
only on a checkout without the fresh receipts. The patched profile requires
`--native-data-exe private/disc-allied/game.exe` to retain independently checked
disc inputs; [COMPOSITION_1006.md](docs/COMPOSITION_1006.md) has reproduction,
audit limits and mapping commands. Remaining descendant profiles stay disc-only.
The shadow/color suite compares integer HSV, the ColorScheme copy/ramp prefix,
flat shadow poses/offsets, complete occupied-column masks with explicit BSurface
stencils, and complete clipped shadow RGB565/depth surfaces. Its 9,812 cases include
all named colors and every RGB565 halving input. House palette assignment, full actor/cache lifetime and full-frame integration
remain outside that suite; the new staging suite extends the bounded integration.
Its read-only research exports stay under `private/shadow-color/assets/`. The
sanitizer command below replays the identity-checked cached original expectations
created by a normal oracle run; omit `--expectations` to run the original again.
The map-light suite executes the complete ordinary cell calculation/normalizer,
actual loader numeric conversion blocks and complete visible-alpha constructor.
Its 17,510 cases include every supplied map cell and full lit surfaces. Explicit
source records/detail inputs and a flat world-height getter isolate source arithmetic;
source actors, original INI parsing, fog and house association are not executed.
The eight alpha-buffer tests use successful allocation and original surface fills.
It exports original inputs read-only to `private/lighting/assets/`, and caches
identity-checked expectations at `private/lighting/expected.json` for sanitizer replay.
The static-source suite executes complete construction/activation/immediate updates,
actual membership/lookup helpers, cell numeric installation, a building creation
block and ordinary terrain factory decisions. Its 2,574 cases include detail gates
and zero-intensity skips. Map/cell pointers and flat height are fixtures; cell
installation uses a null converter, factory construction uses a recorder and redraw
is record-only. INI parsing, full actors, house association, converter pixels/lifetime
and deferred updates are excluded. Research copies/expectations stay ignored under
`private/static-light/`. [STATIC_LIGHT.md](docs/STATIC_LIGHT.md) records the boundaries.
`./test.command --data-dir ...` also runs 19 temporary map/CLI checks and SDL light
toggles. The temporary maps/rules are outside the supplied installation and removed
after the checks; native integration comparisons do not establish original pixels.
The unit-light suite executes the actual rules numeric block, coordinate getter,
ordinary brightness block/effects, house/scheme/blitter selection and complete
ColorScheme/LightConvert reconstruction with successful heap and a warm original
alpha registry. Its 3,257 cases include 182 complete color/depth surfaces and
brightness above 2000. Actor/house records, the unnamed predicate, visibility and
placement are fixtures; full Unit draw, house creation and lifetime are excluded.
Fresh disc/1.006 evidence uses `private/migration/<profile>/unit-light/`.
Existing receipts replay with `--expectations`; fresh execution refuses existing
receipts. Patched research requires explicit retained disc `--native-data-exe`.
[UNIT_LIGHTING_1006.md](docs/UNIT_LIGHTING_1006.md) records the full RGB565 initializer
inspection, two exporters, caller/input/heap audits and reproduction commands.
Historical `private/unit-light/` evidence is preserved; full actor/frame and runtime
promotion remain outside the claim.
The voxel-cache suite executes actual body/turret key blocks, the complete healthy
lit wrapper, signed comparator/qsort/search and successful index growth. Its 4,730
behavior cases compare dispatch/index state and 312 selected owned pixel buffers
and crop rectangles. Healthy virtual/type/house services, rendering/snapshot/cached
draw recording and logical snapshot storage isolate the wrapper; owned cases run
original pose/lighting/raster separately. Full actor, compressed pool, allocation
failure/eviction, runtime shadow identity and full-frame parity are excluded.
Research/expectations stay under `private/voxel-cache/`; protected owned exports
reuse `private/staging/assets/`. Animated HTNK is explicitly refused until its
actor animation/key timing is recovered.
The shadow-key suite runs actual Unit seed/type-default blocks, the complete flat
Drive shadow matrix and complete Foot forwarding. Its 2,203 behavior cases include
all seed branches with supplied metadata, 129 selected masks/crops and four Foot
calls through the real flat Drive predicate/point. Virtual point/map/actor-height
services and logical snapshot identities isolate the boundary. Stock HTNK defaults
to Track because Crusher=yes; other runtime type profiles are refused. Full actor
prechecks, nonflat/status invalidation, shared pool and full-frame parity remain
excluded. Research/expectations stay under `private/shadow-keys/`.
The staging suite runs the complete indexed Convert constructor and surface
blitters, the dirty-union block, complete assembled unit/staged-shadow surfaces,
and the full shadow wrapper with recorded render/snapshot/cached-blit services.
It verifies successful index growth, signed keys, hot hits, suppression and bypass,
not the compressed global pool or whole actor. Its disc/1.006 profiles use protected
exports and fresh receipts under `private/migration/<profile>/staging/`.
Existing evidence replays with `--expectations`; fresh execution refuses existing
receipts. Patched research requires explicit retained disc `--native-data-exe`.
[STAGING_1006.md](docs/STAGING_1006.md) records mappings, audit scope and commands.
The scenery suite executes complete healthy Terrain calls, the actual compressed
SHP wrapper/BSurface/RLE spans and ordinary LightConvert constructor. Its 420 results
compare forwarding, full color/depth planes and palette tables. Map/image/healthy
actor inputs, successful allocation and warm alpha-registry storage are fixtures;
combined calls execute both final shape draws. Full file-loader/actor lifecycle,
ordering, visibility and whole-frame parity are excluded. Protected owned exports
and per-profile identity-checked expectations stay under `private/migration/`. See
[SCENERY.md](docs/SCENERY.md) for clipping/depth rules and exact boundaries.
The props suite extends that boundary to all 23 supplied ordinary props, including
raw SHP bodies/shadows. Its 808 results compare complete Terrain and frame color/depth
surfaces, with original 27/53-row converters and synthetic clipping/depth/light
inputs. Actual raw spans execute; palettes/surfaces and healthy map/image/actor
records are isolation fixtures. Original occupation, actor scheduling/lifecycle,
file-loader ownership and whole-frame parity remain excluded. Exports/expectations
stay under `private/props/`; see [PROPS.md](docs/PROPS.md).

The occupation suite compares 13,472 complete Terrain mask, Cell membership and
Object/Terrain Mark results, including ordered writes/services, arena canaries,
caller stack and callee-saved registers. All 51 supported type inputs and 565 map
placements are exercised. Flat ground/visibility/redraw/lookup services and 1x1
foundation assignment are supplied; global scheduling, complete lifecycle and
locomotor clearance remain open. Fresh disc/1.006 expectations and exports stay
under ignored `private/migration/<profile>/occupation/`; historical evidence is
preserved. See [OCCUPATION.md](docs/OCCUPATION.md) and
[1.006 migration and replay](docs/TERRAIN_LIFECYCLE_1006.md).

The lifecycle suite checks 3,868 results, including 4,580 complete root lifecycle
calls and the 1,695-call full-map sequence. It checks all five layers, capacity tails,
ordered writes/services and caller/arena state. Height, Cell placement permission,
visibility/redraw/logic/global cleanup and allocation outcomes are supplied.
Construction, global traversal, dynamic invalidation and whole-frame parity remain
open. Fresh disc/1.006 research/expectations stay under
`private/migration/<profile>/lifecycle/`; historical `private/placement/` evidence
is preserved. See [LIFECYCLE.md](docs/LIFECYCLE.md) and
[1.006 migration and replay](docs/TERRAIN_LIFECYCLE_1006.md). Both suites refuse
existing fresh receipts and require explicit retained disc --native-data-exe for
patched research. Runtime/data promotion remains pending.

```sh
# Archive evidence guards and retained private original expectations:
build/tools-env/bin/python tests/test_archive_profiles.py
build/tools-env/bin/python tests/compare_archive.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/migration/supplied-ra2-1006/archive-registration-refresh/expected.json \
  --report private/archive-native-replay.json
# Sanitizers, headless (use the local CMake path if cmake is not on PATH):
build/tools-env/bin/cmake -S . -B build/sanitize \
  -DCMAKE_PREFIX_PATH=/opt/homebrew -DCMAKE_BUILD_TYPE=Debug \
  -DRA2_SANITIZE=ON -DRA2_BUILD_SDL=OFF
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
build/sanitize/ra2-inspect private/game mp03t4.map build/sanitize-preview.ppm
build/sanitize/presentation-check private/game
build/tools-env/bin/python tests/compare_presentation.py \
  --exe private/disc-allied/game.exe --native build/sanitize/presentation-vectors \
  --expectations private/migration/allied-disc/presentation/expected.json \
  --report private/presentation-sanitize-report.json
build/tools-env/bin/python tests/compare_raster.py \
  --exe private/disc-allied/game.exe --native build/sanitize/raster-vectors \
  --expectations private/migration/allied-disc/raster/expected.json \
  --report private/migration/allied-disc/raster/sanitize-report.json
build/tools-env/bin/python tests/compare_composition.py \
  --exe private/disc-allied/game.exe --native build/sanitize/composition-vectors \
  --expectations private/migration/allied-disc/composition/expected.json \
  --report private/migration/allied-disc/composition/sanitize-report.json
build/tools-env/bin/python tests/compare_shadow_color.py \
  --exe private/disc-allied/game.exe --native build/sanitize/shadow-color-vectors \
  --expectations private/migration/allied-disc/shadow-color/expected.json \
  --report private/migration/allied-disc/shadow-color/sanitize-report.json
build/tools-env/bin/python tests/compare_staging.py \
  --exe private/disc-allied/game.exe --native build/sanitize/staging-vectors \
  --expectations private/migration/allied-disc/staging/expected.json \
  --report private/migration/allied-disc/staging/sanitize-report.json
build/tools-env/bin/python tests/compare_map_light.py \
  --exe private/disc-allied/game.exe --native build/sanitize/map-light-vectors \
  --expectations private/migration/allied-disc/map-light/expected.json \
  --report private/migration/allied-disc/map-light/sanitize-report.json
build/tools-env/bin/python tests/compare_static_light.py \
  --exe private/disc-allied/game.exe --native build/sanitize/static-light-vectors \
  --expectations private/migration/allied-disc/static-light/expected.json \
  --report private/migration/allied-disc/static-light/sanitize-report.json
build/tools-env/bin/python tests/compare_unit_light.py \
  --exe private/disc-allied/game.exe --native build/sanitize/unit-light-vectors \
  --expectations private/migration/allied-disc/unit-light/expected.json \
  --report private/migration/allied-disc/unit-light/sanitize-report.json
build/tools-env/bin/python tests/compare_voxel_cache.py \
  --exe private/disc-allied/game.exe --native build/sanitize/voxel-cache-vectors \
  --expectations private/migration/allied-disc/voxel-cache/expected.json \
  --report private/migration/allied-disc/voxel-cache/sanitize-report.json
build/tools-env/bin/python tests/compare_shadow_keys.py \
  --exe private/disc-allied/game.exe --native build/sanitize/shadow-key-vectors \
  --expectations private/migration/allied-disc/shadow-keys/expected.json \
  --report private/migration/allied-disc/shadow-keys/sanitize-report.json
build/tools-env/bin/python tests/compare_scenery.py \
  --exe private/disc-allied/game.exe --native build/sanitize/scenery-vectors \
  --expectations private/migration/allied-disc/scenery/expected.json \
  --report private/migration/disc-unit-light-regressions-v2/private/scenery-sanitize-report.json
build/tools-env/bin/python tests/compare_terrain_types.py \
  --exe private/disc-allied/game.exe --native build/sanitize/scenery-vectors \
  --expectations private/migration/allied-disc/terrain-types/expected.json \
  --report private/migration/disc-unit-light-regressions-v2/private/terrain-types-sanitize-report.json
build/tools-env/bin/python tests/compare_props.py \
  --exe private/disc-allied/game.exe --native build/sanitize/scenery-vectors \
  --expectations private/migration/allied-disc/props/expected.json \
  --report private/migration/disc-unit-light-regressions-v2/private/props-sanitize-report.json
build/tools-env/bin/python tests/compare_occupation.py \
  --exe private/disc-allied/game.exe --native build/sanitize/occupation-vectors \
  --expectations private/migration/allied-disc/occupation/expected.json \
  --report private/migration/allied-disc/occupation/sanitize-replay-report.json
build/tools-env/bin/python tests/compare_lifecycle.py \
  --exe private/disc-allied/game.exe --native build/sanitize/lifecycle-vectors \
  --expectations private/migration/allied-disc/lifecycle/expected.json \
  --report private/migration/allied-disc/lifecycle/sanitize-replay-report.json
python3 tools/audit_source.py
```

Local reports, screenshots, binaries, recovered data and environments are ignored.
Source tests generate their small fixtures; they do not distribute extracted data.

## Scope and licensing

The app is silent. No general pathfinding, combat, AI, economy, campaigns,
multiplayer, original saves, YR support, or full original UI is implemented.
No public release or hosting was performed. Preserve [THIRD_PARTY.md](THIRD_PARTY.md)
and GPL-3.0-or-later [LICENSE](LICENSE) for the public-reference-informed code.
Game content must come from the user's legitimate installation and must never
be included in a source/binary distribution.
