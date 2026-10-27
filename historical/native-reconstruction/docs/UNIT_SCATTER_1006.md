# Unit Scatter control policy

The later [world/Cell destination join](UNIT_SCATTER_WORLD_1006.md) uses this same
policy through structural borrowed views. Fresh parent proof
`private/map-depth-1006/unit-scatter-v2/` retains every v1 command, label and output
with normal/sanitizer/uncached replays. The world entry is a separate proof with
actual children; the supplied-service scope of this original parent suite remains
unchanged. Runtime Scatter/Advance6 stay refused.

`scatterUnit` is an SDL-free, **unwired** recovery of the original Unit Scatter
parent in the ordinary Drive profile. It joins actual mission/type eligibility,
Facing, bearing, inclusive RNG, mission queuing and successful Drive interface
ownership. Coordinate/map/layer/level/bounds/admission/projection, pathfinder and
**destination effects remain explicit supplied services**. It does not move a
Unit or establish Advance6, Process, owned-world, preview, drawing or SDL behavior.
Keep the existing Scatter/Advance6 runtime refusals. Base RA2 first, then Yuri's
Revenge remain incomplete.

## Exact target and scope

The private supplied executable is 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage and reported no-CD provenance remain distinct;
pristine authenticity is unverified. The complete parent is
`7072D0..7078E7` exclusive, including final `ret0C` at7078E4.
The original root is void; no EAX return-value parity is claimed.

Original execution includes actual 6C12D0 eligibility, virtual mission/type/kind,
5950D0 mission-control address selection, Facing, bearing/table/FTOL, 6388A0 RNG
and QueueMission594CB0. The native implementation reuses existing Facing,
Targeting, OriginalRandomRange and UnitDiscovery code. Initial records, numeric
and neighbor data, mission-control bytes and global/scenario associations remain
supplied; no construction/startup claim follows.

Successful original Drive QI, smart-interface assignment, GetClassID, AddRef and
Release execute unchanged. Ordinary Drive's actual class identifier differs from
the parent's excluded identifier. Native logical ownership models this one
verified identity and retained positive references; it is not a general COM
implementation. Original atomic imports are serviced at their unchanged targets
with real increment/decrement operations. They are named research shims, not
no-ops or original Windows API execution. The original global counter store
precedes each atomic instance-counter update. Both ordered changes are compared,
including wrapped global counts, rather than checking final equality alone.
Acquisition failures, other locomotor classes and destruction are outside the
profile. Native missing-service/reference guards and release during C++ exceptions
are safety behavior, not original error or rollback parity.

## Preserved behavior

- Eligibility reads virtual mission up to three separate times, rejecting0/6/16,
  then rejects IsTrain at type+AA0. This is the complete6C12D0 guard, not707950.
  Mission getter uses queuedA0 when raw98==-1. Mission-control5950D0 separately
  selects raw98*32, including the supplied entry before the normal array for -1.
- Acquire only after eligibility; retain the interface through the parent and
  release on every entered early/late return. Control+9 or ignoreMission must
  permit the operation; rotation, destination/ignoreDestination and actor+5C8
  can stop it. Nonzero-point policy additionally consumes control+7, Unit+5B9,
  destination/+599 and the target+228 one-in-four RNG decision.
- The zero-coordinate branch calls a supplied pathfinder with 14 actual arguments,
  distinct current/zero/output Cell buffers and fixed caller policy flags. The
  MOV AL bridge argument retains the upper bytes of signed Y/256 as caller
  padding. A selected result reaches destination(flag1) **without QueueMission**.
  The pathfinder's returned destination is authored, not recovered route search.
- Nonzero-point bearing points away from the borrowed coordinate. Round its
  wrapped16-bit heading to eight directions, then add random0..2 minus1 and mask7.
  Preserve the separate1..4 draw and rejection consumption. A diagnostic service
  mutation of the borrowed point reaches the parent's actual later Facing branch;
  that mutation is an ordering experiment, not an observed gameplay event.
- Signed /256 precedes word truncation. Retain repeated coordinate calls and the
  current-Cell lookup before layer. Projection Z is wrapped height*4 when signed
  current level plus returned layer byte is nonzero; otherwise zero. Foot layer
  is a supplied service here: its actual4CC4B0/5D52F0 path must not be simplified
  to actor+79. Admission level is a different supplied query.
- Scan at most eight wrapped neighbor Cells. Lookup precedes bounds, then level
  precedes admission; only admission0 qualifies. Retain the first free Cell.
  With the ordinary zero sentinel, projection equality and flags140 bit100 select
  a preferred Cell. Otherwise finish the scan and fall back to the first free.
  **Both local candidate Cells initialize to zero, not the global sentinel.**
  With supplied nonzero sentinels, the surprising selection of zero is preserved.
- QueueMission2(arg0) precedes final lookup and destination(flag1) in the nonzero
  path. Mission19 suppresses the queue writes but not the later destination call.
  Later parent calls retain queue state, full RNG state and interface ownership.

## Evidence and limits

Canonical proof: `private/map-depth-1006/unit-scatter-v1/`.
**1,063 authored sequences /1,622 complete original parent calls** match normal,
ASan+UBSan and uncached replays. Execution covers 832 distinct parent/child
instructions. This does not claim every branch/instruction of every inspected
range. There are 1,205 actual acquisitions/GetClassID/release pairs,
1,611 RNG calls, 1,032 QueueMission calls, six pathfinder calls and 1,036 supplied
destination calls. Every logged query, raw RNG draw/post-step indices, selected
mission and lifetime stores, sequence-final 250 generator words and logical final
state match. Repeated sequences include 512 retained calls and both RNG index wraps.

The original harness checks complete actor/type/Drive/point/RNG/Cell arenas,
immutable code/data/dispatch, caller stack/registers/canaries and allowed/computed
RNG, mission and global counter stores. Supplied services initialize diagnostic
map records and return bounded authored bounds/admission/projection/pathfinder
results. Destination callbacks log calls without implementing effects. No native
machine-write-order, original pathfinder/admission caller/world effects, movement
or original-game observation claim is made.

**1,000 Python tests, 67 normal / 66 sanitizer legacy CTests, `./test.command`,
both standalone builds and four native guard checks per mode pass.** The new
runner is outside the application/legacy CTest graph and must be compared
separately. All 172 prior replay records retain exact identities; two new records
give 174. The application remains byte-identical at SHA256
`419aac6d0fbcbd33b0fe042ec57c03e508547f1fa3bc3d1971945fda1e3d2ecc`.
Earlier SDL acceptance is retained by identity; no new SDL acceptance is claimed.
Only Apple Silicon macOS is tested. Local verification is not independent acceptance.

Original generation took 2.785s; native comparison 0.128s. Guarded wrapper times
were fresh 6.593s, normal 0.432s, sanitizer 0.724s and uncached 0.531s. These are
verification costs, not game performance or a controlled speedup. Full manual
review/repair time was not measured. Initial pilots caught an undersized Facing
inspection range; build preparation caught a nonexistent source entry and a
missing file-reader linkage. Repairs and pilot evidence remain private. No
original instruction/result, runtime exclusion or earlier proof was relaxed.

## Build, try and reproduce

```sh
./build.command
./run.command --owned-demo
# Existing two-Rhino movement; Scatter/Advance6 remain refused.
./test.command
PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  -m unittest discover -s tests -p 'test_*.py'

env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake -S tests/unit_scatter -B build/unit-scatter \
  -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_OSX_ARCHITECTURES=arm64
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/unit-scatter --parallel 6
build/unit-scatter/unit-scatter-vectors --guards
# Sanitizer: build/unit-scatter-sanitize, Debug and -DRA2_SANITIZE=ON.

# Fresh original execution requires authorized host Unicorn JIT and NEW paths.
PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/map-depth-1006/unit-scatter-new-audit.json \
  tests/compare_unit_scatter.py --exe private/official-1006-probe/game.exe \
  --native build/unit-scatter/unit-scatter-vectors \
  --output private/map-depth-1006/unit-scatter-new

PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/map-depth-1006/unit-scatter-try-audit.json \
  tests/compare_unit_scatter.py --exe private/official-1006-probe/game.exe \
  --native build/unit-scatter/unit-scatter-vectors \
  --expectations private/map-depth-1006/unit-scatter-v1/expected.json \
  --report private/map-depth-1006/unit-scatter-try.json
# Use the sanitizer runner for its replay; --uncached before the driver supplies
# the inspection-reuse control. Never rerun closed finalizers.
```

Next join actual coordinate/layer/map/admission consumers and destination7053F0
with the parent, then enclosing Advance6/Process, Cell dispatch, owned-world,
preview/drawing and SDL before enabling Scatter. Zero-point pathfinder success
needs its own proof or an explicit refusal. Initial records, direct routes,
controls, clearance and scheduling remain supplied. General pathfinding, combat,
economy, AI, campaigns, multiplayer, audio, original saves and YR remain open.
Private originals/assets/research/expectations/binaries stay ignored and unshipped.
No new external source/header/dependency or runtime executable-read expansion is
introduced. Existing reference/license boundaries apply. Source installations/
discs and Outpost2 remain read-only. No workers, Windows actions/transfers,
downloads, publication or system/Xcode/DRM changes occur in this checkpoint.
