# Zero-point Unit Scatter on shared Cells

The subsequent [Cell dispatcher join](CELL_NEARBY_SCATTER_1006.md) now reaches
this zero-point entry with distinct actors and shared type aliases. The refreshed
`unit-nearby-scatter-v2` retains all 157 previous commands/labels/outputs;9 native
guards per mode include explicit refusal of entered non-Track nonzero Unit
admission. Nearby Cell speed handling remains separate. Earlier Cell-unjoined
statements below describe this note's original checkpoint; Advance6/Process/
owned-world/preview/drawing/SDL and runtime gates remain open.

`scatterUnitWithNearbyOnMap` joins the complete zero-point Unit Scatter caller to
actual nearby destination search, permission, rectangle/Cell admission, projection
and ordinary Cell destination effects on one borrowed map/fallback. It installs a
destination; route generation and later movement remain open. This separate entry
is unwired. The playable two-Rhino baseline remains unchanged, with runtime
Scatter/Advance6 still refused. Base RA2 first, then Yuri's Revenge remain incomplete.

## Exact target and ownership

The supplied executable is 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 lineage and reported no-CD provenance remain distinct;
pristine authenticity is unverified. The fingerprint was checked before inspection.
An existing verified local file made the authorized Windows copy unnecessary.

The same original guest executes complete Unit 7072D0 -> nearby 5502E0 -> actual
55A740/550CF0/478760/6A6A50/548070, then actual Unit/Foot/Drive Cell destination
children. It retains the actual actor/Drive addresses, mission, targets, queues,
reference ownership, map/slots/fallback and floor cache. No instruction patches or
substituted search/admission/permission/projection/destination decisions are used.
The inherited atomic import service and copied temporary destination timer-padding
input remain supplied research boundaries; this is not original startup or OS execution.

The native shared Scatter composition now takes an explicit borrowed type+5A4
input and search binding. The previous nonzero-point facade forwards to the same
composition and retains its zero-point refusal. The new adapter binds the complete
nearby map implementation using that composition's actual map/fallback/permission
owner. Cell level/flags, occupation and speed tables stay borrowed. It constructs
no copied world, renderer, actor or Drive and makes no prewarming queries.

Preserve source X/Y signed division by 256 before word truncation. The alternate
dword retains the upper bytes of signed Y/256 and replaces only AL with actor+79.
The real type+5A4 supplies speed; it is not hard-coded to Track. Original arguments
are zone-1, movement-zone0, 1x1, overlay0, match1, burrow0, allowbridge1, separate
zero target and skip0. Caller and search empty-Cell sentinels are separately
supplied zero globals in this proof. The zero target selects by frame, consuming
no RNG, distance sqrt or QueueMission. In particular, this branch never queues
mission2. Current movement head+40 remains distinct from destination+34.

Destination effects retain mission7's queue-head bypass, all 23 tail words, vector
ownership, reference changes, ordered target/Drive/timer writes and actual Cell
center/floor/cache consumption. Initial actor/type/House/Cell/overlay/speed/shape/
frame/sentinel records and associations, direct routes and timer padding stay
supplied. The bound admission records are research projections, not the production
mutable world. Moving residents, special destination missions, owned disposal and
bridge-adjusted commands keep their existing refusals. Unsupported calls may have
consumed effects; future previews must discard the entire owner.

## Verification boundary

Fresh exact-original execution matches **157 sequences / 178 complete Unit calls**,
including 173 nearby searches, 83,638 direct permission calls, 72,108 rectangles and
actual Cell admissions, 536 projections, 96,078 projection map lookups and 134 actual
Cell destination calls. Search returns 39 empty / 134 nonempty results; both
permission and Cell admission returns execute. There are 2,124 distinct executed
instructions across the composed ranges, not every inspected branch. No RNG,
QueueMission or table-sqrt call is entered. Canonical proof: `private/map-depth-1006/unit-nearby-scatter-v1/`.
The 157-case pilot matched original/native outputs but its final identity guard
correctly rejected source/runner edits during generation. It remains private and
superseded; canonical runs freeze all sources and runners. No result, instruction,
algorithm or guard was weakened. Native guard development also corrected a missing
supplied fallback association in its fixture. Full manual review/repair time was
not measured; guarded invocation and comparison costs are recorded privately.

Checks compare ordered caller/search/permission/rectangle/Cell/projection/map/
fallback queries and returns, full child arguments, actual destination stores,
references, all queue words, retained positions/head/Drive state, final Cell fields,
floor cache and all RNG words. Original full arenas/unmodeled fields, fallback
bytes, slots, type inputs, code/tables, globals, stack/canaries and caller registers
are protected. All four incoming native FP modes are checked. Independent late
speed reads and exception cleanup are separately covered by native guards.

This does not establish every native machine store, FP exception flags, original
startup/global lifetime, original-game observations, independent acceptance or
whole-frame fidelity. The Cell dispatcher still needs this zero-point binding;
Advance6/Process effects, production owned actors, full discarded previews/warm
renderer isolation and actual SDL acceptance precede runtime displacement.
Global8529D0 and complete Advance6 caller effects remain open. Never substitute a
nonzero away point for Advance's initialized-zero852998 input.

No upstream code/header/generated/lifted output, table, dependency or runtime
executable-read expansion is added. The test runner reuses existing private
render data; this caller does not enter its sqrt binding. Existing
[reference/license limits](REFERENCES.md) apply. Proprietary files/research/results/
binaries remain ignored and unshipped. Installations/discs/Outpost2 stay read-only.
No workers, Windows operations/transfers, downloads, publication, system/Xcode/DRM
changes or push. Only Apple Silicon macOS is tested.

## Reproduce

```sh
./build.command
./run.command --owned-demo
./test.command
PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  -m unittest discover -s tests -p 'test_*.py'

env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake -S tests/unit_nearby_scatter \
  -B build/unit-nearby-scatter -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_OSX_ARCHITECTURES=arm64 -DCMAKE_PREFIX_PATH=/opt/homebrew
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/unit-nearby-scatter --parallel 4
build/tools-env/bin/ctest --test-dir build/unit-nearby-scatter --output-on-failure
build/unit-nearby-scatter/unit-nearby-scatter-vectors --guards
# Repeat in build/unit-nearby-scatter-sanitize with RA2_SANITIZE=ON.

# Fresh original execution requires the authorized host Unicorn context.
# Always select new ignored audit/output paths. Never overwrite closed evidence.
PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/map-depth-1006/unit-nearby-new-audit.json \
  tests/compare_unit_nearby_scatter.py \
  --exe private/official-1006-probe/game.exe \
  --native build/unit-nearby-scatter/unit-nearby-scatter-vectors \
  --output private/map-depth-1006/unit-nearby-new
# Replay: replace --output with --expectations
# private/map-depth-1006/unit-nearby-scatter-v1/expected.json --report NEW_JSON.
# Sanitizer: select its runner. Uncached: add --uncached before the driver.
```

The standalone checks remain outside the app/legacy CTest graph. General routes,
combat, economy, AI, campaigns, multiplayer, audio, original saves and YR remain open.
Never rerun this or any earlier closed finalizer.
