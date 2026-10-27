# Shared refresh on native device-backed radar storage

## Actual Boot Camp actor/House marker services — 2026-10-19 UTC

`BootCampRadarActors` now scopes the existing stock RadarActorsBinding over
actual GIs, the two existing Buildings, their existing type owners, and the
mission's shared Houses. It supplies pure borrowed views, not actor/House copies.
Construct it before RadarRefreshBinding, pass its `world()` into that binding,
and destroy the refresh binding first. All owners, schemes, palettes and probes
must outlive entered calls. The adapter owns its probe callbacks, so default or
temporary probe arguments do not dangle. Copy/move is disabled.

Owner queries read the actual GI mission Owner or Building discovery Owner each
time. Infantry alternate410 is an owned logical House handle, remapped by its
stable key rather than a cached pointer. Houses use the existing index/alliance,
human/control and current-House identities. New House RGB55E9 and scheme15F40
fields live beside those same fields. Infantry170, timer13C/144 and type1FF have
persistent fields on their existing owners. Building170 reuses the expiration/
mission-target field; its timer belongs to the existing Structure state and
its type1FF to the actual BuildingType. Type flag resolution checks the returned
owned type, without querying unrelated Buildings' type fields.

These new fields have explicitly supplied zero startup, alternate=-1 and timer
start=-1/remaining0. No original constructor, INI-to-color/palette association or
writer is recovered by adding storage. The adapter requires the actual Walk tick
reference and checks the actual player House at binding. House scheme lookup and
all actor callbacks restore on scope exit/fault; earlier bitmap/pixel effects
are not rolled back. Foreign actors, Houses and types refuse without accepting
equal-looking values or dereferencing foreign memory. Public/recomp/YR code,
new runtime executable reads and new dependencies were not introduced.

The actual Day1 owner test now draws mixed GI/Building markers through both
complete refresh branches with the actual map/discovery/floor/device storage.
It checks palette-backed zero-mode output, packed House RGB nonzero output,
live Owner/alternate170/410, distinct directed alliance masks, type1FF filtering,
Building CC-null and shared LightGrey resolver, raw scheme index versus palette
pixel, timer flash and a phase change after the actual Walk clock advances.
An invalid type on an unentered Building must not affect drawing. Alias checks
cover the actual House fields, Infantry type/timer, Building timer and reused170.
Warm clones preserve the new values; fresh bindings on the clone draw after
source destruction and the source world stays unchanged. Constructor probes,
callback restoration and foreign-identity checks retain their separate scopes.

Marker positions, the three-entry bucket population, palette/scheme records,
RGB/index values, test alliance mutations and flash divisor1 are controlled test
inputs. This is actual-owner rendering integration, not recovered marker
placement, scenario palette startup, coverage scheduling or an SDL radar. Walking,
arrival and ordinary Objective1 remain unchanged. This closes actor-child ownership
needed by radar refresh before genuine tutorial sight/effects scheduling.

The historical2,835-row actor origin correctly refused replay because
`original_radar_map_pixels.py` and `original_surface_radar_pixel.py` no longer match
its recorded original source identities. Its failed audit is preserved; no old
receipt was relabeled, guard bypassed or unchanged matrix regenerated. The later
current940-row coverage/refresh origin includes the stock actor/color/alliance/
resolver children and both refresh branches, and is explicitly reused on rebuilt
normal/sanitizer runners. Those are existing separate original kernel scopes;
the new Day1 owner join has native integration evidence, not a fresh original
whole-world proof. Costs, commands, hashes and failures are recorded under
`private/boot-camp-20261020/radar-actors-owner-a1/`.

Next recover/join actual marker placement and coverage callers on this same map,
storage and actor/House owners; preserve supplied startup/palette boundaries and
complete remaining original caller/late-byte work before live sight/arrival wiring.
Base RA2/YR and ordinary Boot Camp Objective1 remain incomplete. Local verification
is not independent acceptance.


## Actual Boot Camp map/visibility binding — 2026-10-19 UTC

`BootCampVisibilityWorld::refreshRadar` now scopes the existing recovered
RadarMapBinding over the actual MutableUnitMap table, fallback, level-height and
lazy floor cache, and the existing CellVisibilityState fields. The caller must
already own a RadarRefreshBinding on those exact refresh/radar service objects
and select the actual current player House identity. Foreign associations refuse
before drawing/map effects. The method is explicit and unscheduled; neither
walking, arrival, a visibility change nor SDL calls it automatically.

The shared Cell owner now has independent `count13c`, with supplied zero startup;
it is not aliased to `counter130` or `maximum134`. Copy/assignment and warm world
clones preserve it. Flags12C/count13C come from the existing visibility Cell;
flags140/position/height/ramp come from its actual terrain Cell. Pure field
resolution reuses MutableUnitMap's canonical slot/pointer validation and verifies
the terrain-flag alias. A foreign or split Cell refuses instead of introducing a
mirror. Missing terrain/discovery lookups update the same mutable fallback
position and synchronize its visibility point and diagnostic bookkeeping.
Floor queries use the map's existing lazy cache, including its legitimate writes.
No cache or fallback effects are discarded on return/fault.

The actual Day1 owner check now refreshes device-backed RadarStorage with real
floor and discovery children, with no supplied floor/discovery answer executing.
Diagnostic changes to the actual shared12C and independent13C fields select
ordinary, hidden and dim output over the full image. The test checks exact
fallback point agreement, warm clones with nonzero13C, source destruction,
foreign player-House refusal before queries and no source-world mutation. World
snapshots now include every visibility Cell and fallback field, closing an older
isolation-check omission. Actor/mission state is retained during these draws.

This new test has empty actor buckets. Actor marker generation/type/color/timer/
House palette associations, coverage callers, initial13C writers and production
scheduling are still open. Current-House selection is an explicit checked host
association, not recovered original startup/global ownership. The earlier
controlled map-service test below keeps its narrower evidence scope. Full image
buffer checks do not establish original whole-frame fidelity.

The unchanged coverage/refresh, ordinary Cell change and mask original-only
expectations are explicitly reused against both rebuilt profiles. They verify
their existing kernels separately; this new actual-owner join has native
integration evidence, not a fresh original whole-world proof. Current commands,
hashes, costs and any failed attempts are recorded under
`private/boot-camp-20261020/radar-map-owner-a1/`. No original answers were
regenerated and no unchanged SDL check was repeated. This closes the actual map/
visibility association needed by radar/coverage effects before genuine Boot Camp
sight scheduling; it does not advance Objective1. Next join actual actor/House
marker owners and coverage callers using this same storage and map binding.
Base RA2/YR remain incomplete. Local verification is not independent acceptance.


The shared refresh binding now retains the recovered first-surface device copy8
when explicitly requested, and inherited GetPixel/SetPixel use the actual
receiver's device lock/format/unlock callbacks. Software records retain their
existing facade. This joins existing recovered kernels; it recovers no new
original routine and makes no new original whole-composition fidelity claim.

This removes a software-only assumption before production House/coverage refresh
can be joined into the Boot Camp sight path. Ordinary SDL sight scheduling,
arrival and Objective1 remain unchanged and incomplete.

## Owners and behavior

`RadarStorage` exposes stable borrowed CopySurface adapters for its actual first
and second geometry, formats, lock fields and pixel allocations. Existing device
copy uses these same adapters. Startup invalidates them before destroying or
replacing the corresponding surface. The bitmap view borrows the actual startup
allocation, including during the finish callback. No allocation or geometry is
mirrored. Surface references and scale references bind the actual storage fields.
Adapters returned by the resolver must not be retained across startup replacement.

`RadarRefreshSurfacePolicy::retainCopy` is an explicit pure table-metadata choice.
A missing retained copy refuses before installing refresh callbacks. Default
software callers remain unchanged. Pixel services resolve from the actual
receiver, independently of the saved pixel entry-table identity. Both original
stock tables use inherited774220/7741D0; those routines call the receiver's lock,
format and unlock virtuals. Alternate records require all three callbacks.
Format and unlock remain late reads of that stable receiver's callbacks.

Binding construction performs no gameplay, surface, lock, format or floor query.
Resolvers must be pure and stable during entered calls. Scoped bindings restore
callbacks on exit/fault; prior pixel/bitmap effects are not rolled back. Startup
must not destroy a receiver while a call is executing. Device loss, OS allocation,
initialization and zero alpha/depth policy retain their supplied boundaries.

## Verification scope

The actual mutable Day1 map test now enters both complete634030 branches on
RadarStorage. It checks full terrain/display equality after zero-mode copy, then
one controlled marker on an actual GI identity with the shared bitmap. Nonzero
refresh checks every device pixel for ordinary, hidden and dim terrain branches.
Device-lock entry counts distinguish these paths from a software facade.
Repeated zero-mode refresh, callback restoration, source/world isolation, foreign
geometry refusal and startup after entered refresh cover ownership/lifetime.
These checks pass with normal and ASan/UBSan builds.

**House identity, floor/discovery answers, actor-mark placement, palettes and
schedule in this new storage test are controlled diagnostic inputs.** They do not
prove the production House/Cell/actor association, coverage invocation, original
marker placement, original startup or live sight. Mission, Walk, visibility and
terrain state are checked for unintended mutation. No SDL radar was added, and
no unchanged SDL acceptance was repeated.

Existing identity-checked original-only expectations are replayed against rebuilt
native runners: coverage/refresh940, copy/mark950, device copy390, device locks477,
inherited device pixels335 and startup8 sequences, in each profile. These provide
separate original evidence scopes; their union is not a fresh original execution
of the new Day1 storage composition. No original answer or native pass/fail was
regenerated/cached. No new executable/file read, public code or dependency added.
Exact supplied executable remains4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Only Apple Silicon macOS is tested.

## Commands

```sh
./build.command
./test.command
./run.command --boot-camp-walk
build/native/boot-camp-walk-check private/official-1006-probe - private/boot-camp-20261020/radar-shape-dimensions-a1.bin
build/sanitize/boot-camp-walk-check private/official-1006-probe - private/boot-camp-20261020/radar-shape-dimensions-a1.bin
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/NEW-DEVICE-REFRESH.audit.json tests/compare_coverage_radar_refresh.py \
  --exe private/official-1006-probe/game.exe --native build/native/coverage-radar-refresh-vectors \
  --expectations private/boot-camp-20261019/coverage-radar-refresh-fresh-a1/expected.json \
  --report private/NEW-DEVICE-REFRESH.json
```

Actual-map integration also replays the unchanged shared Cell kernels:

```sh
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/NEW-RADAR-VISIBILITY.audit.json tests/compare_cell_visibility_change.py \
  --exe private/official-1006-probe/game.exe --native build/native/cell-visibility-change-vectors \
  --expectations private/boot-camp-20261018/cell-visibility-both-fresh-a1/expected.json \
  --report private/NEW-RADAR-VISIBILITY.json
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/NEW-RADAR-MASK.audit.json tests/compare_cell_visibility_mask.py \
  --exe private/official-1006-probe/game.exe --native build/native/cell-visibility-mask-vectors \
  --expectations private/boot-camp-20261018/cell-visibility-mask-fresh-a1/expected.json \
  --report private/NEW-RADAR-MASK.json
```

Use new report/audit destinations. The comparison explicitly reports reuse hits
and misses and runs current native output/guards. Substitute the sanitizer runner
for its separate replay. Other exact family commands, costs, hashes and failures
are retained in `private/boot-camp-20261020/device-refresh-a1/` and its receipt.
No new original JIT/Windows action or runtime executable read is needed.

Next finish actual actor/House marker associations and coverage callers using
this same storage, recovered refresh and actual map binding, then verify the
composition before scheduling effects. Do not replace missing producers with synthetic
objective success or arrival-distance checks. Base RA2 and YR remain incomplete.
