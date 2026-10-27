# Waypoint visibility through Unit and Building discovery

Separate waypoint proof now reaches complete common6C2440 and Building448FE0/
636F10 with actual mixed coordinate virtuals5D4E40/444080/458930/458940, through
the existing single waypoint/area/change/mask/Cell-discovery kernels. All96
original sequences match. It is not yet a production waypoint action. Tag event,
Building activation, Cell notification, redraw and refresh remain supplied leaves.

## Actual shared state

`WaypointResidentDiscovery.hpp` supplies a small borrowed-identity dispatch join.
Each selected resident resolves to its existing mutable `UnitDiscoveryActor` and
optional Building services, using one `UnitDiscoveryWorld` for shared Houses.
Missing/null or duplicate selected identities refuse. It does not create actors,
copy House maps, schedule visibility, or implement another discovery algorithm.
The existing complete `discoverUnit`/`discoverBuilding` kernels retain their scope.
Initial class/vtable association and registry membership remain supplied.

The proof uses34 distinct resident records on the17 shared Cell/fallback identities.
Odd actor identities select actual Building coordinates and discovery; even
identities select common raw coordinates and Unit discovery. Two vtable layouts
bind actual getter/Mission/QueueMission/discovery/activation slots. Both kinds
share House addresses, type/foundation inputs and repeated visibility visits.
Type-table spans are read privately from the hash-checked executable by the
research driver, passed explicitly to the native research runner and frozen in
original input guards. They are neither embedded in Git nor newly read at runtime.

Repeated discovery sees previous actor373/374, mission queue and House writes.
Current-House duplicate refusal occurs before Object/House/Building children.
Uncontrolled discovery reaches the actual Mission getter/QueueMission chain.
Successful Building discovery retains saved Owner/type writes and late Owner
rereads, loading bypass and duplicate radio/control queries. A supplied Tag
callback changes an Owner in one joined case; later common/Building writes use
that actual changed Owner. It is a diagnostic callback, not a recovered mission
mutation. No Building activation was entered in this joined proof; activation
remains supplied and the older standalone cases retain their separate scope.

## Original proof and identities

Exact target4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD and unverified pristine
provenance remain distinct. The verifier composes independently inspected exact-
base waypoint/discovery/Building-coordinate/Unit-and-Building-discovery ranges,
retaining only entered complete discovery ranges in the execution allowlist.
Original instructions remain unmodified and execute only in research Unicorn.
No public/YR/recomp code, dependency or runtime executable-read expansion.

Canonical expectations:
`private/boot-camp-20261018/waypoint-objects-fresh-a1/expected.json`, SHA256
`52493631034c29591979ca586ad7611615c7a005242eab2758739d73b2d3b032`.
96 roots include72 ordinary/24 disabled,144 area passes,9,550 visibility changes,
19,100 masks,1,604 Cell-discovery roots and1,715 closest-resident calls.
75 actual Building and96 actual common coordinate getters execute; each Building
getter reaches both foundation children.169 common discovery calls include73
Building wrapper roots;16 Object discovery,18 House control,6 Mission getter,
3 QueueMission and16 radio roots execute. Supplied effects record3 Tag calls
with one Owner mutation,1,317 notifications,1,604 redraws and16 refreshes.
Activation count is zero.169 dispatches are calls, not169 successful discoveries.

Ordered lookup/fallback/counter/mask/coordinate/discovery/query/store/Tag traces
match. Every root also compares complete mutable visibility projection plus all34
actor owner/discovery/queue fields and both Houses' discovery/Building fields.
Caller stack/return/preserved registers, instructions, numeric/foundation tables,
globals/type/vtables and unselected arena/padding remain guarded. Only named
visibility/fallback/actor/House writes are allowed. Residency/Next/flags/raw
coordinates/type associations are immutable guarded startup inputs. Notification,
redraw and refresh only record; their real side effects and late global mutations
remain unverified. This is isolated binary-derived evidence, not observation of a
running original game, complete mission behavior or whole-frame fidelity.

## Checks, reuse and costs

Both full builds pass.136 normal/135 sanitizer CTests pass in8.04s/10.45s;
1,431 Python tests pass in29.821s. New96, previous96 waypoint-discovery,
816 standalone Building-discovery and1,034 mixed-coordinate cases retain normal/
sanitizer/uncached replays with explicit current runner/source identities and zero
misses. All replay controls avoid original execution. Closed finalizers are not rerun.

The application and both private-data owner-check binaries are hash-identical to
the preceding checkpoint. Its106-tick actual SDL input/drawing baseline, inspected
arrival and warm-owner checks retain scope; no new SDL run is claimed. Live
objectives remain disabled. Isolated injected-clone objective text remains
diagnostic. Other prior runners retain their recorded hash scope; the inventory
separately refreshes a sanitizer Building runner against an older historical
receipt, without claiming that its earlier rebuild occurred in this checkpoint.

Fresh original generation46.295s, full driver47.940s, native comparison0.174s.
No fresh proof failure or repair occurred. Exact commands/replay costs, sources,
runners, retained/updated hashes and logs are in private
`waypoint-objects-replay-commands-a1.json`, `waypoint-objects-receipt-a1.json`
and `waypoint-objects-runner-inventory-a1.json`. Build/review/approval/GUI/tool
costs were not measured separately. No new cache was added; inspection/expectation
identity and source/runner/input/receipt guards remain active. Local checks are
not independent acceptance.

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
./test.command
DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
./run.command --boot-camp-walk

env PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/waypoint-objects-next.audit.json \
  tests/compare_mission_waypoint_objects.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/mission-waypoint-objects-vectors \
  --expectations private/boot-camp-20261018/waypoint-objects-fresh-a1/expected.json \
  --report private/waypoint-objects-next.json
```

Use new report/audit paths. Sanitizer selects its runner; uncached inspection
control puts `--uncached` before the driver. Fresh original replaces expectations/
report with `--output private/NEW-DIRECTORY` and requires local JIT access.

Next join actual recovered Tag/Trigger/mission effects through the same chain,
then production waypoint/reveal owners with full warm discarded-preview isolation.
Remaining sight/arrival scheduling, clock-before-producers, Team/alliance/audio
and ordinary SDL Objective1 acceptance remain open. Both games incomplete; goal
active. Only Apple Silicon macOS is tested. No workers/Windows actions/transfers/
downloads/publication/system/Xcode/DRM changes.
