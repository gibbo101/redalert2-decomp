# Boot Camp Building expiration owners

The two production objective Buildings now bind actual Radio/Techno/Building Tag
expiration and stock null-target/availability/pending/getter kernels. Discovery,
mission cleanup and discarded full-world arrival previews use these same owners.
This replaces the earlier supplied Object-prefix recipients. Live objectives are
still disabled; reveal action17 remains request-only. Both games and Boot Camp
Objective1 remain incomplete. Only Apple Silicon macOS is tested.

## Ownership and boundaries

`BootCampBuildingExpiration` is an immovable context with five independent fixed
backings/counts: Radio,390,3A8,3C0 and53C. Discovery reads the same Radio slots
that expiration clears; availability reads the actual53C count54C. Mission98,
queuedA4 and Owner borrow the existing discovery actor. Building type418 uses a
stable type registry, shared with discovery's indexB90. Health and positive type
Strength come from the supplied full-health map/rules association. Other initial
fields/type flags/session/retry padding and original scenario construction remain
supplied. The stored zero animation threshold is not an admitted rules recovery:
animation lookup is unbound and the entered branch refuses.

`MissionExpirationPointerView` borrows either a pointer field or pure logical
read/write accessors. Copying a view copies its binding. Storing another view's
value requires explicit pointer conversion; this matters for the middle-passenger
splice. Object link30 and passenger traversal now borrow the actual logical
resident Next, rather than synchronizing a separate pointer. Tag diagnostic
handle-2 is not an admitted map resident. House index0 is valid; null Owner maps
to-1. Walk identity callbacks resolve existing GI records and rebind on clones.
They make no map/floor/gameplay queries. Entered GI passenger links remain refused.

Warm clones create fresh views/services, copy record values and remap all known
pointers, including inactive backing tails, types, Houses and Tag identities.
Logical resident Next values retain their handles. No external callback is copied.
Raw foreign pointers (including GI pointers in expiration backings) refuse cloning;
this is not general object-graph ownership. Full-world tests snapshot the new
Building fields before discarded previews. Source ownership and warm renderer
storage remain isolated. These are host ownership guarantees, not recovered
original allocation or startup behavior.

House power, service208/238, weapon/release, RNG retry, control associations and
animation/deeper children remain unbound. Entered children throw after earlier
stores; no rollback is claimed. Null-target scope is retained. No new runtime
executable read, public/YR/recomp code, dependency or Windows action was added.

## Evidence

Exact supplied base executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct.

No fresh original instructions were needed for this native ownership change.
All33 guarded normal/sanitizer/uncached replays pass against existing immutable
original-only expectations, with zero reuse misses. Families:136 waypoint Building,
108 typed waypoint,1,621 Building services,871 typed expiration,448 Techno,
324 Object,488 generic expiration,108 Object waypoint expiration,816 Building
discovery,96 waypoint objects and108 waypoint Tag sequences. These families are
not independent gameplay samples and overlap. Original source/input/receipt and
rebuilt runner guards are retained. New native headers have supplemental source
hashes in the production receipt; legacy driver source lists remain unchanged.
The production allocation/binding graph itself has native ownership tests, not a
new original whole-chain proof or gameplay observation.

All143 normal/142 sanitizer CTests and1,452 Python tests pass. Both private-data
owner checks pass. Added checks cover copied logical views, actual Object and
middle passenger stores, target/pending/queued fields, shared Radio clearing,
vector compaction with retained tails, type/House0/Tag remapping, foreign-tail
refusal, explicit service/RNG/animation refusal after earlier writes, source
destruction, full Walk GI identity rebinding and discarded typed arrival writes.

The rebuilt application passes actual SDL select/move/draw/pause/refusal/Stop/
repeated-order/deselection at106 ticks. Arrival image inspected. This retains the
existing walking scope; it does not demonstrate ordinary objective completion or
original frame fidelity. The first sandboxed SDL attempt could not enumerate
displays; the distinct host-display A2 attempt passed. No closed finalizer rerun.

Inventory:44 of71 previously tracked binaries are unchanged;27 have explicit
rebuilt identities. Full builds took32.593s normal/37.485s sanitizer, overlapping.
CTest suite times2.33s/12.72s (outer2.676s/12.783s), Python35.107s (outer41.215s),
private owner checks1.556s/25.497s. The first27 replays took85.634s in sequence;
remaining replay/SDL commands and costs are in the receipt. No cache added.
Earlier full-build A1 overload ambiguity and a cyclic diagnostic fixture are
retained as failed attempts, not relabeled successes. Focused build/repair/total
task-wall costs and SDL elapsed cost were not measured.

Private receipts:
`private/boot-camp-20261018/production-building-receipt-a1.json`,
`production-building-runner-inventory-a1.json`,
`production-building-validation-a1.json`,
`production-building-replays-a1.json`,
`production-building-extra-replays-a1.json`, and `production-building-sdl-a2/`.
Local verification is not independent acceptance.

## Commands and next gate

```sh
./build.command
./test.command
build/native/boot-camp-walk-check private/official-1006-probe
build/sanitize/boot-camp-walk-check private/official-1006-probe
build/native/mission-techno-tag-expiration-vectors --guards
./run.command --boot-camp-walk
./run.command --boot-camp-walk-smoke-test private/NEW-SDL-DIRECTORY

env PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/NEW-OWNERS.audit.json \
  tests/compare_mission_waypoint_building_services.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/mission-waypoint-building-services-vectors \
  --expectations private/boot-camp-20261018/waypoint-building-fresh-a1/expected.json \
  --report private/NEW-OWNERS.json
```

Use fresh output/audit paths; substitute the sanitizer runner and use `--uncached`
before the driver for inspection controls. Exact33 replay commands are retained in
the private manifests. Next compose actual waypoint reveal onto production
visibility/map/resident owners, retaining startup and unbound-child refusals.
Require full warm isolation and ordinary SDL objective acceptance before enabling
live discovery/mission scheduling. Keep the active reconstruction goal open.
