# Actor registration and Building radar footprints

The subsequent [complete placement parent](RADAR_ACTOR_PLACEMENT_1006.md)
now composes these callers on the actual owners. Its2F8 permission/status and
visibility effect children remain open; the final next-caller paragraph below
records this note's earlier inspection checkpoint.

`RadarActorMarkers.hpp` recovers complete Infantry6D74D0/6D7500/6D7530,
Building451800/451860/4518C0 and the shared complete6328D0 footprint selector.
`BootCampRadarActors::updateMarker` explicitly composes these callers with the
actual GI/Building fields, RadarStorage's existing22 shape vectors,256 marker
buckets and dirty bitmap/queue. No parallel actor or map representation is added.

This is another dependency of original marker placement/refresh beneath the
sight/discovery path to Boot Camp Day1 Objective1. These calls remain unscheduled;
they do not produce discovery, change Walk arrival, play instructions or satisfy
an objective. Base RA2 and Yuri's Revenge remain incomplete.

## Evidence and behavior

The supplied base executable is4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
The verifier fingerprints it before disassembly and pins all seven complete spans
and stock Infantry/Building420/424/428 virtual associations. Embedded1.08,
supplied1.006 lineage, reported no-CD provenance and unverified pristine
authenticity remain separate. No public implementation or new dependency is used.

Infantry insertion/removal reads1A4 then1A0 and forwards the actor and saved
coordinates. It stores37B=1/0 only after that child returns, even if the child
bypasses a duplicate/missing entry. Infantry dirty passes a pointer to actual
1A0/1A4 and never writes37B. The native callback lends references to these fields;
the dirty kernel now accepts that borrowed point without a snapshot. Existing
point callers retain their value type. Late width/height/queue reads remain live.

Building callers read type418 once, and6328D0 selects Map1274 plus typeC78*24.
The native selector guards indexes outside the owned22 vectors; this is an
execution bound, not an original clamp. Each iteration rereads the selected
vector's backing, count and current actor coordinates. Point additions wrap at
32 bits. A child can replace backing, grow/shrink count, or alter the coordinates
used by the next iteration. Changing typeC78 during a child does not reselect the
saved vector. The dirty caller builds a local point, so subsequent actor writes
do not change that invocation's point. Insert/remove store37B after the loop,
even when count is zero or negative; dirty leaves it unchanged.

The original fixture executes the seven parent/selector algorithms unchanged,
with supplied marker/dirty child probes.396 sequences cover all22 indexes,
negative/empty/one/eight-point counts, raw registration bytes, integer extremes,
child coordinate/count/backing/type/registration mutations and alias-versus-local
dirty points. Checked entry spans, allowed original stores, immutable code/tables,
caller stack, return and callee-saved registers accompany ordered child/store
traces and final fields. This is a caller proof with supplied effect children,
not an end-to-end original registration/drawing proof. The complete marker/dirty
children retain their separate previous proofs and reused original expectations.

## Actual composition and boundaries

Actual GI and Building owners retain37B with supplied zero startup. The existing
Building type owner retainsC78 with explicitly supplied index0; its original
loader and actual type association remain unrecovered. Actual-map checks use
the existing private original shape-dimension input and recovered632700 vectors;
no extracted dimensions enter tracked source or become a new app read.

The actual owner check inserts a GI through the complete caller, draws its marker
through the existing refresh, checks clone registration retention and explicitly
dirties/removes the old identity. Building insertion visits the actual selected
footprint; every in-bounds point appears in the same buckets consumed by drawing,
and removal retires every active entry for that Building. Foreign actor refusal
and source-world isolation remain. Footprint checks require the supplied private
dimensions; the default no-dimension check does not claim them. Existing direct
marker checks, inactive tails and explicit retire-before-destroy/rebinding remain.

Coordinates/geometry/palettes/colors, constructor state, Building index selection,
queue consumption, complete placement6D8120 and live sight/SDL scheduling are
still supplied or open. Cloned registration state alone does not recreate marker
buckets. Owners must outlive active entries and synchronous adapters. No new SDL
adoption or executable-read boundary is introduced. Only arm64 macOS is tested;
local validation is not independent acceptance or whole-game fidelity.

## Reproduce

```sh
./build.command
./test.command
build/native/boot-camp-walk-check private/official-1006-probe - private/boot-camp-20261020/radar-shape-dimensions-a1.bin
build/sanitize/boot-camp-walk-check private/official-1006-probe - private/boot-camp-20261020/radar-shape-dimensions-a1.bin

# Original-only reuse, always executing current native; use fresh report paths.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
 --audit private/actor-markers-next.audit.json tests/compare_radar_actor_markers.py \
 --exe private/official-1006-probe/game.exe \
 --native build/native/radar-actor-markers-vectors \
 --expectations private/boot-camp-20261020/actor-markers-fresh-a2/expected.json \
 --report private/actor-markers-next.json
# Repeat with build/sanitize/radar-actor-markers-vectors and fresh paths.
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest tests/test_radar_actor_markers.py
./run.command --boot-camp-walk
```

Prior child replay commands/origins remain in
[RADAR_MARKER_BUCKETS_1006.md](RADAR_MARKER_BUCKETS_1006.md). New and affected
current profile evidence is under
`private/boot-camp-20261020/actor-markers-final-{native,sanitize}-a1/`.
Fresh original generation took.120s. The first sandboxed original attempt ended
SIGILL132 before publication because Unicorn JIT lacked host access; the approved
retry passed. A native alias guard was then added and both profiles rebuilt,
reusing all396 original answers. No original instruction or expectation changed.
Build/configuration/edit/preflight/total turn wall costs were not instrumented;
per-check measured costs are in the private final profile costs files.
195 normal/194 ASan+UBSan CTests,43 focused Python tests, both actual owner
profiles and the standard `./test.command` pass. Each current profile replays
5,745 original sequences (396 new,334 buckets,271 helpers,940 coverage/refresh,
3,804 copy), all hits and zero misses. CTest driver wall2.922/16.852s; owner wall
5.039/45.253s. Full source/binary identities, costs and failed preflight scope:
`private/boot-camp-20261020/actor-markers-receipt-a1.json`. Concurrent durations
are not additive. The standard entry point also repeated cheap normal CTests
while validating its Python scripts; no SDL ceremony was repeated.

## Next complete caller

Finish complete6D8120..6D83C4 actor placement on these same owners: discovery568140,
stock2F8 permission (Infantry6D7A10/Building452220), screen/on-map/secondary574
branches and63B5B0, out-of-screen1AC/55A740, projection, removal/registration and
late timer/flash dirty calls. These remain inspected, not a recovered whole
caller. Do not wire a convenient suffix into sight or SDL. Keep the complete E1
position/sight schedule and other Cell-crossing producer requirements before
ordinary Objective1 progress; do not synthesize discovery or success.
