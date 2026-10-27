# Boot Camp shared resident owners and Building coordinates

Visibility now traverses the same mutable primary/elevated heads and Next records
as Infantry membership. The registry contains five actual GIs and the two supplied
objective Buildings, with no dummy Building Walk/Drive record. Live sight/arrival
scheduling and Objective1 remain disabled.

## Exact coordinate recovery

Target: `private/official-1006-probe/game.exe`, 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Original instructions/data are unmodified.

Building vtable `79CBBC+48` selects complete `444080..4440D4`; Infantry vtable
`7A3540+48` selects common `5D4E40`. The Building override calls complete height
`458940..45897D` with byte argument zero, rereads the type pointer and calls
complete width `458930..45893E`, then loads raw actor88 coordinates. It shifts
each dimension left7, subtracts128 and adds it to the corresponding raw X/Y
with wrapped32 arithmetic, preserving raw Z. This is not the common raw getter.

Width loads typeC78 and indexes the dword table at7CFC70. Height uses the table
at7CFCC8, adding one only when both its low-byte argument and type1214 are nonzero.
The proof inspects and freezes88-byte spans at each table (22 selected indices).
No table values are embedded in tracked source or added to application reads.
The native helper borrows supplied spans and refuses reached out-of-span indices.
Production uses explicitly supplied art dimensions instead of reading those
executable tables; original foundation-enum/INI/constructor association is open.

`BuildingCoordinates` preserves height(0), width, raw-point order and the original
wrapped arithmetic. The mixed closest-resident proof executes complete471660,
actual Building/Infantry coordinate virtuals, both Building type helpers and
complete4BA410/77F110 numeric children. Its additional full568520 roots execute
the visibility parent through that same chain in one guest. Discovery virtual180
is an explicit supplied leaf in this proof; complete discovery has its separate
[Building](BUILDING_DISCOVERY_1006.md) and [Unit](UNIT_DISCOVERY_1006.md) evidence.
Do not call this one joined original proof of discovery/Tag/mission effects.

## Shared production ownership

`BootCampMissionWorld` owns each stable Structure record's raw88, Next30,
flag14 and supplied foundation dimensions alongside its existing discovery state.
`structureResident` returns borrowed fields and the actual mission actor identity.
The read-only state accessor supports complete source snapshots. Destruction of
an objective Tag does not destroy its Structure owner.

`BootCampWalkWorld` supplies the two objective anchor-Cell placements on its actual
`InfantryMembershipCell` heads. `PreparedInfantryWalk::registerBuildingResident`
registers only borrowed actor fields/identity for predecessor traversal and kind6
search; it creates no Walk, Drive, command or admission object. It rejects
conflicting ids and identity/Next/coordinate aliases. Cell insertion/removal still
refuses a Building as the acting mover. Ordinary Infantry admission still refuses
any other resident; no occupied-Cell or Building collision branch was widened.

`BootCampVisibilityWorld` no longer owns private resident coordinate/Next copies or
inserts its own structure list. Its services borrow the actual membership heads,
GI object Next/flag14/raw coordinates and Building fields/coordinate override.
GI flag14 is a supplied startup byte, distinct from onMap7D and active32D.
The standalone `CellVisibilityState` resident fields remain available to recovery
fixtures; this production composition does not read them. Kind6 search returns
the same Building identity from those same heads, including behind a GI.
Binding performs no resident/map/floor query. Foreign identities refuse.

Visibility dispatch now calls the actual GI's common discovery or the existing
Building wrapper. In an explicit native sight composition, initialized player
sight discovers one GI. After ordinary walking and an explicit later sight call,
three GIs and the two objective Buildings have been discovered (five successful
notifications total); the objective text action has one recorded request. The
prior count of two omitted GI residents. These are native composition observations,
not observations of a running original game or completed mission actions.

Native owner checks exercise Building flag14 changes, actual identity, passive
Building predecessors during GI remove/insert and both first/later kind6 hits.
All eight ordinary movement directions demonstrate old-head removal/new-head
placement as seen by closest-resident traversal. Refused controls do not mutate
source heads, Next, flags, coordinates, dimensions, Cells/fallback or Houses.

The discarded arrival preview still reaches Process26/52, discovery1/0 and
position Cell queries3/2. It checks initialized heads, all GI resident fields
and both Building owners before copying the selected actor into its disposable
world. Changed Building residents refuse without mutation. No source-bound
callbacks are copied. This remains an initialized-only preview, not a general
warm clone. Structure construction, raw88 origin/Z, anchor membership, dimensions,
radio/type startup, GI startup, clearance, route, controls and scheduling are
supplied. Other map structures are not registered by this bounded join.

## Evidence and checks

Canonical original expectations:
`private/boot-camp-20261018/building-coordinate-fresh-a2/expected.json`, SHA256
`a93d841b71b5b5f00dbaed6af4c48a63717a9fd7053f20ad1f36a93fbc371972`.
1,034 cases include594 complete Building coordinate calls,616 actual width calls,
726 height calls,616 closest-resident calls,198 common coordinate calls,
528 complete numeric/signed-conversion pairs and88 complete visibility parents.
The88 discovery virtual calls remain supplied. Ordered helper calls, coordinate
output stores, selected identities and fallback assignments match native.
Cases cover22 table indices, raw byte arguments, extreme/wrapping coordinates,
primary/elevated selection, ignored identities, inactive/unrelated flag bits,
mixed competition, first-wins ordering and fallback/level filtering. Original
caller stack, callee-saved registers, input tables/code/arenas and writes are guarded.

Normal/sanitizer/uncached-inspection replays pass1,034/1,034 with zero misses.
All946 earlier coordinate/closest projections retain identical commands, labels
and outputs; the finalized receipt adds88 full visibility roots. The older a1
receipt is retained and not relabelled. No whole-inventory refresh or closed
finalizer ran. Existing affected-family replays retain their original identities;
2,500 old sequences per rebuilt runner retain zero misses:360 position-discovery,
80 joined position/sight,128 mask,192 visibility-change,48 Walk/position,
1,600 admission and92 Walk journeys. Final reports are
`resident-owner-{position,sight}-{native,sanitize}-a1.json` and
`resident-owner-{mask,change,walk-position,admission,walk}-{native,sanitize}-a2.json`.

Full normal/headless-sanitizer builds pass;116 normal CTests,115 sanitizer CTests
and1,353 Python tests pass. The final coordinate-domain Python check also passes.
Final owner checks are `resident-owner-normal-a6.log` and
`resident-owner-sanitize-a3.log`. Actual106-tick SDL selection/movement/drawing/
pause/refusal/Stop/repeated-order/deselection acceptance is `resident-owner-sdl-a2/`;
arrival drawing was visually inspected. Final guards use full Building resident-state
equality. The SDL report retains objectives disabled and
`original_fidelity_from_this_smoke:false`. Local source/runner/log identities are recorded in
`resident-owner-receipt-a1.json`. Local verification is not independent
acceptance, original-game observation or a whole-frame/game fidelity claim.

Fresh finalized generation took0.495s; full driver1.725s, comparison0.038s.
Normal/sanitizer/uncached replay drivers took0.634/0.796/1.167s, comparisons
0.021/0.149/0.023s. Concurrent CTests took5.00/6.44s; Python61.110s. Builds,
host permission latency, SDL and manual repair wall costs were not separately
measured. The first owner check retained an obsolete structure-only discovery
count; the corrected check explicitly verifies three discovered GI records.
One sanitizer mask replay passed comparison but its outer guard correctly
rejected changing source/runner identity during concurrent work; its final replay
uses a new audit after builds and edits stopped. No guard was bypassed.

## Reproduce and next integration

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
./test.command
build/native/boot-camp-walk-check private/official-1006-probe
build/sanitize/boot-camp-walk-check private/official-1006-probe

env PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/residents-next.audit.json \
  tests/compare_building_coordinates.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/building-coordinates-vectors \
  --expectations private/boot-camp-20261018/building-coordinate-fresh-a2/expected.json \
  --report private/residents-next.json

./run.command --boot-camp-walk
```

Use fresh audit/report paths, the sanitizer runner for sanitizer replay, or
`--uncached` before the driver for inspection control. Fresh original execution
uses `--output private/NEW-DIRECTORY` instead of expectations/report and requires
private Unicorn JIT permission. Preserve every identity/input/runner/receipt guard.

Next implement a complete warm/discarded owner clone, including resident identities,
mutable Cells/fallback/Houses, Building/GI discovery/mission/Tag state and renderer
isolation. Join required entered caller/effect paths and ordinary SDL discovery
before live sight/arrival scheduling. Mission text/audio/reveal/alliance/team
requests still need their actual effects; Objective1 and both full games remain
incomplete. No workers, Windows actions, downloads, public/YR/recomp code,
dependencies or runtime executable-read expansion were used.
