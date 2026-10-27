# Complete actor radar placement parent

See [subsequent event inspection](RADAR_PLACEMENT_EVENT_1006.md) for the corrected
63B5B0 name and local-player dependency boundary; constructor effects remain open.

The subsequent [permission recovery](RADAR_ACTOR_PERMISSION_1006.md) supersedes
the permission next-step below and replaces the supplied choice in the explicit
joined seam. Other effect and scheduling boundaries remain.

`RadarActorPlacement.hpp` recovers the complete677-byte6D8120..6D83C4 parent.
`BootCampRadarActors::placeMarker` explicitly composes it on the existing actual
GI/Building fields, shared map visibility predicate, original marker projection,
registration/removal/dirty callers and RadarStorage buckets/queue/drawing. This
is still an unscheduled dependency of sight/discovery for Boot Camp Day1's first
objective. No Walk tick, arrival, SDL input or mission condition adopts it.

## Exact evidence and semantics

The verifier checks4,485,392-byte supplied base SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`
before using addresses. It pins the complete parent and stock2F8 associations
(Infantry6D7A10, Building452220). Embedded1.08, supplied1.006 lineage, reported
no-CD provenance and unverified pristine authenticity remain distinct. No public
implementation or additional dependency was incorporated.

When373 and loadingA3D298 are both zero, the parent calls actual virtual48,
queries568140 and stores373 as the inverse of the result's low byte. It then
calls kind2C. Kind6 with an argument whose low byte is zero retains stored1A0/1A4;
other cases snapshot all three88 coordinate words and call631BA0 with clamp0.

The single2F8 argument is **a local status word initialized to zero**, adjacent to
but separate from the projected point. It is not a point argument. A nonzero
status and nonzero permission low byte enter63B5B0(mode5, packed Cell) if actor
flags14 bit2 is clear or signed secondary574 is negative. Both coordinates are
reread after preceding children, divided by256 with signed truncation and narrowed
to16-bit Cell words. Screen rectangle words are saved before this branch.

An out-of-screen point with nonzero permission calls virtual1AC(argument1),
55A740 with that returned identity, and, on a nonzero result low byte, snapshots
current88 and calls631BA0 with clamp1. Rectangle sums wrap at32 bits. Permission0
bypasses these children even for an offscreen point.

A registered actor whose point changed or whose permission is zero first calls
424 removal. The parent writes1A0, reads the live37B, then writes1A4. Only the
saved registration byte and nonzero permission control420 insertion. A callback
which leaves registration set therefore suppresses insertion; no native
assumption silently clears it. Complete stock registration children normally
perform their already verified late37B stores.

The late direct Owner/current-House equality gate precedes the flash calculation.
13C/144 are read twice under the original signed remaining-time gates, using the
saved frame and wrapped subtraction. Positive remaining time is divided by the
live rules90 divisor; remainder0 calls428 dirty. Divisor0/overflow are explicit
native refusals, never an invented divisor. The parent does not return a modeled
numeric value: the consumed effects and child calls are the proven interface.

596 isolated original sequences match the complete unchanged parent with supplied
children. They cover raw low-byte gates, status0/nonzero, argument0/1/256,
Building saved coordinates, screen edges and out-of-screen clamp, signed secondary
and flags14 gates, child mutations of coordinates/registration/Owner/timer,
registration changed between coordinate stores, signed timer wrap and remainders.
Ordered child/store traces, final fields, entered instruction spans, permitted
writes, immutable code/tables, caller stack/return and callee-saved registers are
checked. These proofs do not execute the complete permission/visibility children;
their effect probes are explicitly supplied. Original projection/marker/dirty/
refresh kernels keep their separate prior proof scopes and reusable expectations.

## Actual owners, lifetime and limits

The actual seam borrows GI ground position/current373/flags14/secondary574,
Building resident position/flags14/discovery state, marker37B/1A0/1A4, timers,
House association and actual Walk frame. Owner identity is resolved **late** from
the actual integer House key; it is not a snapshot taken before callbacks. A
Building574 field has supplied-1 startup; its writer/constructor is unrecovered.
The direct virtual48-to-owned-coordinate association also remains supplied.
The initial map visibility query uses BootCampVisibilityWorld's existing recovered
primary predicate on the same Cells/fallback. This query tests visibility; it is
not a mission discovery event and does not advance Objective1.

Actual checks project a GI's owned coordinates, register and draw through the
existing storage, move its diagnostic coordinate, remove the old marker before
inserting the new one, execute timer dirty and retire on permission0. The original
position is restored without stepping the controlled actor. Building argument0
and256 keep the stored point, register the private-dimension footprint and remove
it on refusal. Foreign identities refuse before mutation and the source world
remains isolated. Existing warm-clone/retire-before-destroy checks remain. Owners
must outlive all synchronous callbacks and active marker entries.

The actual checks supply permission1/0 and status0, screen geometry, projection
origins, flash divisor and startup. Permission2F8's complete algorithms, status
production,63B5B0 effects and the actual1AC/55A740 association still need joining.
The direct55A740 algorithm already exists separately as `nearbyCellPermitted`;
this does not prove its caller's Cell identity. Missing entered children refuse;
there is no rollback/atomic-command claim for this internal original parent.
No new executable read or app scheduling was added. Only Apple Silicon macOS is
tested, and local validation is not independent acceptance or whole-game fidelity.

## Commands and current evidence

```sh
./build.command
./test.command
build/native/boot-camp-walk-check private/official-1006-probe - private/boot-camp-20261020/radar-shape-dimensions-a1.bin
build/sanitize/boot-camp-walk-check private/official-1006-probe - private/boot-camp-20261020/radar-shape-dimensions-a1.bin

# Reuse original answers explicitly; execute current native on every invocation.
# Use fresh report/audit paths; do not replace the origin or relabel a receipt.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
 --audit private/actor-placement-next.audit.json tests/compare_radar_actor_placement.py \
 --exe private/official-1006-probe/game.exe \
 --native build/native/radar-actor-placement-vectors \
 --expectations private/boot-camp-20261020/actor-placement-fresh-a1/expected.json \
 --report private/actor-placement-next.json
# Repeat with build/sanitize/radar-actor-placement-vectors and fresh paths.
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest tests/test_radar_actor_placement.py
./run.command --boot-camp-walk
```

Fresh original generation took.395s. Later native-only refusal guards reuse all
596 answers. No unchanged original matrix is regenerated. Final current native
and sanitizer artifacts/costs live under
`private/boot-camp-20261020/actor-placement-final-{native,sanitize}-a1/`;
source/binary identities and final scope are in
`private/boot-camp-20261020/actor-placement-receipt-a1.json`.
Build/configuration/inspection/edit/preflight/total turn costs were not instrumented;
per-check durations are recorded, and concurrent costs are not additive.
196 normal/195 ASan+UBSan CTests,46 focused Python tests, the standard
`./test.command` and both actual owner profiles pass. Each profile replays6,341
original sequences (596 parent,396 actor callers,334 buckets,271 helpers,940
coverage/refresh,3,804 copy), all hits and zero misses. Standard native tests took
3.693s; sanitizer CTest18.880s; actual owners5.150/46.624s. Both full builds
finished before adding the explicit parent-produced-marker drawing assertion;
the owner tests were then rebuilt separately. No comparison/build/check failed.
No SDL ceremony was repeated for these unscheduled services.

## Next dependencies

Hash-checked inspection shows complete Infantry2F8 reads typeAA6/AA7, actor325,
Owner4F52B0, current373,1B0, veterancy/type277/289, primary/secondary visibility,
mission1B8,2FC and directed alliance before writing status1/2. Building2F8 uses
AA6/AA7, Owner4F52B0/current373, dimensions458940/458930, two568140 calls,
modeB263D8, mission1B8, bytes5BD/5B7,2FC and alliance before status1. These are
inspected hypotheses, not recovered implementations. Reuse actual fields and
already proven predicates when recovering/joining those children.63B5B0 and
actual1AC permission association remain separately necessary.

Complete E1 position/sight scheduling and other Cell-crossing requirements still
precede ordinary Objective1 adoption. This parent must not become a synthetic
arrival/discovery shortcut. Base RA2, Yuri's Revenge and the full goal remain
incomplete.
