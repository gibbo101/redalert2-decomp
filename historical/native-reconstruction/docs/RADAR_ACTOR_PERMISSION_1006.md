# Infantry and Building radar permission/status

See [subsequent event inspection](RADAR_PLACEMENT_EVENT_1006.md) for the corrected
63B5B0 name and local-player dependency boundary; constructor effects remain open.

`RadarActorPermission.hpp` recovers complete Infantry6D7A10..6D7BF5 and
Building452220..452388. `BootCampRadarActors::markerPermission` borrows existing
actor/type/House/visibility owners; `placeMarkerWithPermission` joins the result
and status word into the preceding complete placement parent, existing marker
callers, actual storage and drawing. This removes the supplied parent permission
choice in that explicit seam. It is still unscheduled, beneath the sight and
discovery work needed for Boot Camp Day1 Objective1; it advances no mission.

## Evidence and preserved behavior

Exact supplied base:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
The verifier fingerprints before addresses, pins both complete spans and stock2F8
associations, and pins actual4F52B0/4E5540/7133A0/713420 plus1.0/2.0 constants.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain separate. No public implementation/new dependency
was incorporated, and original execution is test-only Unicorn.

Infantry reads typeAA6, actor325, then typeAA7 in that order. AA6/325 refuse;
AA7 accepts without changing status. Actual local-House4F52B0 then returns the
truth of current373, again preserving status. Nonlocal handling saves1B0 height,
repeats the veteran/elite interval calls and type lookup, and treats veteran277
as applying to elite too, with elite289 as its additional alternative. These are
not the distinct sight271/283 or speed26C/27E fields.

Primary568140 is followed by the independentB263D8 mode read only when its low
byte is nonzero. Session flags bit1000 alone permits secondary5683C0; its nonzero
low byte bypasses the ordinary mission/height/promotion/primary early return.
Otherwise mode1B8!=2, height>=-20 and absent promotion/primary shortcut return
true without changing status. The remaining path calls2FC; its zero low byte
refuses. Directed current-to-Owner4E5540 then precedes late tests of the saved
promotion/visibility booleans. Only the encountered nonallied branch writes
status2 for height<-20, or1 otherwise. Most true returns write no status.

Building uses direct type418/AA6/AA7 and the same local/373 gates. It calls
height458940(argument0), reloads type for width458930, and saves wrapped
`(dimension<<8)-256` offsets. After a nonzero first568140 it takes a fresh raw88
snapshot and queries the offset point; modeB263D8 is read only after both results
have nonzero low bytes. Its ordinary bypass uses mode1B8, numeric byte5BD==15,
byte5B7 and that primary result. The remaining2FC/alliance path writes status1
only when nonallied and neither live5B7 nor the saved primary flag is set. It
never calls Infantry height/promotion/secondary helpers.

635 fresh original sequences execute both complete parents plus the unchanged
stock local/alliance/veterancy leaves. Entry traces contain609 local,196 alliance,
670 veteran and526 elite calls. Raw byte gates, preserved nonzero status, mode/
House identity, NaN/infinity and promotion boundaries, -21/-20 height boundary,
visibility low bytes/short circuits, session secondary gate, numeric Building
flags, wrapped dimensions and child mutations of Owner/type/coordinates/flags
are covered. Ordered child/status stores, results, allowed original stores,
immutable code/tables, entered spans, caller stack/return and callee-saved
registers are checked. Height1B0,2FC, coordinate visibility and dimension children
are supplied probes here; their original effect code is not silently credited.
The preceding placement/marker/visibility proofs keep their separate scopes.
There is no single joined original proof of this entire application interaction.

## Actual composition and supplied boundaries

Actual GI325 and typeAA6/AA7/277/289 have supplied zero startup; actual GIs reuse
the existing position owner's1B8, current373, veterancy118, coordinates88 and House.
Building type fields share its existing type owner, and1B8/5BD/5B7 live on the
existing Structure state with supplied zero startup.1B8 is distinct from Mission98.
Building dimension callbacks borrow the existing supplied foundation dimensions;
the original type enum/table/loader association is still unverified.

Both visibility queries use the existing BootCampVisibilityWorld predicates on
the actual Cells/fallback. Local-House and directed alliance reuse the existing
recovered kernels on the actual House fields. Actor/Type references, the Owner
read before the late current-House read and callbacks stay live; no snapshot of
another world or host-distance policy replaces them. Callback construction makes
no game query. Foreign identities refuse before field changes.

Actual checks cover local discovery/type/325 gate precedence and unchanged status,
warm type/325 retention, local permission -> complete placement -> drawing, and
325 refusal -> retirement. Nonlocal GI status2 and Building status1 compose into
the parent's actual packed-Cell/mode5 request boundary and shared marker/footprint
owners;2FC low-byte refusal retires them. Height and2FC values and the visibility
effect recorder in these checks are explicitly supplied. The source world stays
unchanged. A recorded63B5B0 request is not a visibility mutation or objective event.
No tick/arrival/SDL path invokes this seam.

The placement seam also now uses the already recovered `buildingCoordinates`
virtual48 kernel instead of its former supplied raw-coordinate association:
height0, width, raw88, wrapped center offsets. Infantry retains the common raw
getter association. This reuses existing recovery; foundation initialization is
still supplied and no executable table/read was added. Previous original parent
expectations remain valid because only current native child composition changed.

Still unjoined: Object1B0/5D4810 with floor/bridge and late-Z reads, complete
2FC/6D7C00 with its current-House Cell counter lookup, and63B5B0 mutation effects.
Native bindings refuse missing entered height/2FC children; local early branches
need neither. Session flags/startup, initial type bytes, House associations,
geometry/origins/divisor and invocation schedule remain supplied. Only Apple
Silicon macOS is tested. Local validation is not independent acceptance or a
whole-game fidelity claim; base RA2 and Yuri's Revenge remain incomplete.

## Reproduce

```sh
./build.command
./test.command
build/native/boot-camp-walk-check private/official-1006-probe - private/boot-camp-20261020/radar-shape-dimensions-a1.bin
build/sanitize/boot-camp-walk-check private/official-1006-probe - private/boot-camp-20261020/radar-shape-dimensions-a1.bin

# Explicit original-only reuse; current native always runs. Choose fresh outputs.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
 --audit private/actor-permission-next.audit.json tests/compare_radar_actor_permission.py \
 --exe private/official-1006-probe/game.exe \
 --native build/native/radar-actor-permission-vectors \
 --expectations private/boot-camp-20261020/actor-permission-fresh-a1/expected.json \
 --report private/actor-permission-next.json
# Repeat with build/sanitize/radar-actor-permission-vectors and fresh paths.
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest tests/test_radar_actor_permission.py
./run.command --boot-camp-walk
```

Previous domains/origins and exact reuse commands remain in
[RADAR_ACTOR_PLACEMENT_1006.md](RADAR_ACTOR_PLACEMENT_1006.md) and its child notes.
197 normal and196 ASan+UBSan CTests,49 focused Python tests, `./test.command`
and both actual-owner profiles pass. Each profile explicitly replays6,976
original sequences with6,976 hits and zero misses:635 permission,596 placement,
396 registration,334 buckets,271 projection/dirty,940 coverage and3,804 copy.
Standard tests3.946s; sanitizer CTest18.481s; owners2.766/48.780s. Permission
replay.455/1.154s; focused Python1.370s. No build/comparison/check failure.
Fresh original generation took.334s. A subsequent native-only explicit late
Owner-before-current read reused the same635 expectations. Current profile logs,
audits, reports and measured check costs live in
`private/boot-camp-20261020/actor-permission-final-{native,sanitize}-a1/`;
source/binary hashes and limitations are recorded by
`private/boot-camp-20261020/actor-permission-receipt-a1.json`.
Build/configuration/inspection/edit/preflight/total turn durations were not
instrumented. Concurrent costs are not additive. No SDL ceremony is repeated for
unscheduled services, and no unchanged original matrix is regenerated.

## Next blocker

Exact-build inspection shows both stock2FC slots select6D7C00. It returns false
for null current House; otherwise it calls actual virtual48, Map548000, rereads
the current House's signed index30, then complete47C2E0. The latter tests a signed
word at Cell7C+index*2 for positivity. The existing global counter130, count13C
and primary/secondary flags do **not** represent these per-House words. Recover
and bind that storage/lookup on the same Cell owners rather than substituting
another visibility predicate. Object5D4810 also needs its complete floor/bridge
wrapper composition; current inspection only begins it. Both are hypotheses here.

Retain complete E1 position/sight, other Cell-crossing producer and63B5B0 effect
requirements before production wiring. Do not convert this explicit seam into a
synthetic arrival/discovery shortcut or mission success.
