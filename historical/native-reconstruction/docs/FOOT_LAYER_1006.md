# Foot coordinate layer and actual world queries

`src/sim/FootLayer.hpp` adds a separate **unwired** Object/Foot coordinate-layer
dependency for Unit Scatter. Both complete roots now execute with actual nested
Foot/Drive/Object coordinates, map/Cell floor arithmetic and conditional map
lookup. This does not join the earlier Scatter parent or change playable movement.
Keep every Scatter/Advance6/Process/world/runtime refusal until its caller and
ownership integration is verified. Base RA2 first, then Yuri's Revenge remain
incomplete.

## Target and boundary

The private supplied executable is 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage and reported no-CD provenance remain separate;
pristine authenticity is unverified. No transfer or new executable is needed.

| Complete routine | Address | Verified association |
| --- | --- | --- |
| Foot coordinate-layer wrapper | `4CC4B0..4CC4CC` exclusive | Actual Unit vtable slot+B8 |
| Object coordinate-layer decision | `5D52F0..5D53C7` exclusive | Actual Foot negative-index child |
| Foot secondary coordinates | `4CA6F0..4CA7CE` exclusive | Actual Unit slot+4C |
| Drive secondary coordinates | `49FDB0..49FE21` exclusive | Actual interface slot+18 at Drive+4 |
| Object coordinate getter | `5D4E40..5D4E61` exclusive | Actual Unit slot+48 |
| Map/Cell floor and coordinate lookup | `55A280`, `4706C0`, `548000` | Complete existing recovered algorithms |

The existing `FootCoordinates.*`, `MapFloorHeight.*` and `MapCoordinateCell.*`
implementations are reused without changes. Original Drive/Foot zero-sentinel
initializers execute separately with caller/write guards. Actor/Drive/registry/
Cell associations, slots, flags, both height globals and initial lazy floor/template
records remain supplied; complete construction/startup is not recovered here.
No new public source/header/generated/lifted output, table or dependency is used.
Existing [reference/license boundaries](REFERENCES.md) apply. Exact base execution
establishes the behavior; YR declarations/recomp output are not the oracle.

## Preserved decisions and order

- A nonnegative signed registry byte returns 0 from Foot without bridge, coordinate,
  floor or global queries. Negative indices forward the original flag to Object;
  the nested secondary getter forwards but does not consume that flag.
- Save the raw bridge79 byte, query secondary coordinates and copy the returned
  point. Query that point's floor first, then independently query the actual
  actor88 location's floor. Do not substitute one coordinate/floor result for both.
- Reread bridge79. When zero, compare wrapped signed `actorFloor-pointFloor` to
  wrapped signed `3*globalA72F40` with strict greater-than. Only that branch queries
  map548000 at the **saved secondary point**, returning 1 when flags140 bit100 is set.
- When the lookup bit is absent, reread globalA72F40. Other entered paths retain
  their original single global read. Reread bridge79 again and, when nonzero,
  return 0 only if wrapped signed `pointFloor-actorFloor` exceeds the threshold.
  Otherwise return the originally saved raw byte, including values 2..255.
- Floor uses global850C40 separately from threshold globalA72F40. Lazy cached
  height/scale/planes survive later changes to the live globals. Keep full signed
  division before wrapped combined map indexing, repeated fallback-coordinate
  stores and shared fallback identity. Bind without prewarming/querying the map.
- The Drive getter uses **head at Drive+40**, not Move_To destination+34.
  Its COM interface is at Drive+4, so the original instructions address it as +3C.
  All-three-zero head falls back to actor88; if that result is also zero, Foot
  invokes the actual Object coordinate getter. Nonnegative registry coordinates
  use signed-word centers with Z0. Older parameter/docs calling the getter source
  a destination do not authorize binding it to the Move_To destination.

The native query view borrows the live actor/map through named callbacks and owns
no mirrored actor, Drive or map. Missing required services are explicit native
safety refusals; no original error/rollback parity is claimed. Five native guard
checks include the no-service indexed bypass, missing binding, saved-point/raw-byte
behavior, conditional early return and wrapped threshold. A callback-only changing
threshold probe checks the native reread; it is not an original-game observation.

## Original evidence and limits

Canonical: `private/map-depth-1006/foot-layer-v2/`.
**2,296 sequences / 3,643 complete top-level layer calls**, plus two separately
checked original sentinel initializers, match normal/ASan+UBSan/uncached replays.
The layer calls comprise 2,410 Foot and 1,233 direct Object entries; 2,242 Foot calls
reach Object, giving 3,475 Object/secondary-coordinate entries. There are 6,950
actual map/Cell floor calls, 1,038 conditional coordinate lookups, 3,307 Drive getter
calls and one actual Object-coordinate fallback. All signed registry indices,
all 256 result bytes and all 21 ramps execute. There are 611 distinct executed
parent/child instructions; this is not every branch of every inspected child.
Object exits include 925 return 1, 815 return 0 and 1,735 saved-byte paths.

Compare every logged bridge/coordinate/floor/global/map query and return,
ordered fallback stores, each layer result, final fallback coordinates and every
bit of the complete lazy floor cache. Original arena/Cell/registry/Drive/actor,
immutable code/data/dispatch/slot/global inputs, registers/stack/canaries are
checked. No native machine-store-order claim follows. The 533 explicit bridge
mutations at the first actual floor return are diagnostic ordering experiments,
not original instructions, recovered effects or gameplay observations. The whole
arena permits only those declared diagnostic mutations. Other original actor and
Cell records remain unchanged. Native services execute the existing recovered
map/floor/coordinate algorithms; no supplied floor/layer result replaces them.

**1,014 Python tests, 67 normal / 66 sanitizer legacy CTests, `./test.command`, both
standalone builds and five native guard checks per mode pass.** This runner is
outside the app/legacy CTest graph and must run separately. All 176 earlier replay
records retain exact identities; two new records give 178. The app remains
byte-identical at SHA256
`419aac6d0fbcbd33b0fe042ec57c03e508547f1fa3bc3d1971945fda1e3d2ecc`.
Earlier SDL acceptance is retained by identity; no new SDL acceptance is claimed.
Only Apple Silicon macOS is tested. Local verification is not independent acceptance.

Original generation took 10.282s; native comparison 0.150s. Guarded wrapper times:
fresh 10.933s, normal 21.738s, sanitizer 28.141s, uncached 21.732s. Replay wrappers ran
concurrently with regression checks; these are verification costs under contention,
not game performance or a controlled speedup. Full manual review/repair time was
not measured. The v1 pilot passed original comparisons; review found a replay-only
helper-name typo before replay. V2 corrects that name, retains identical commands/
labels/outputs and has fresh final source identities and successful replays.
V1 and all earlier closed proofs remain untouched. No result or original code was
relaxed. Pilots/closure/preflight remain private in
`private/map-depth-1006/foot-layer-candidate/`; never rerun closed finalizers.

## Build, run and reproduce

```sh
./build.command
./run.command --owned-demo
# Existing two-Rhino controls: LMB select; RMB move; Ctrl-RMB append;
# Shift-RMB aim; Q/E body; A/D turret; S stop; Space pause; R reset.
./test.command
PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  -m unittest discover -s tests -p 'test_*.py'

env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake -S tests/foot_layer -B build/foot-layer \
  -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_OSX_ARCHITECTURES=arm64
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/foot-layer --parallel 6
build/foot-layer/foot-layer-vectors --guards
# Sanitizer: build/foot-layer-sanitize, Debug and -DRA2_SANITIZE=ON.

# New paths only. Fresh original execution requires authorized host Unicorn JIT.
PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/map-depth-1006/foot-layer-new-audit.json \
  tests/compare_foot_layer.py --exe private/official-1006-probe/game.exe \
  --native build/foot-layer/foot-layer-vectors \
  --output private/map-depth-1006/foot-layer-new

PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/map-depth-1006/foot-layer-try-audit.json \
  tests/compare_foot_layer.py --exe private/official-1006-probe/game.exe \
  --native build/foot-layer/foot-layer-vectors \
  --expectations private/map-depth-1006/foot-layer-v2/expected.json \
  --report private/map-depth-1006/foot-layer-try.json
# Select the sanitizer runner for that replay; --uncached before the driver
# provides the inspection-reuse control. Never rerun closed finalizers.
```

Next join actual Scatter coordinate/layer/map/admission consumers and the separate
Unit destination dependency. Recover or explicitly refuse entered mission7/16
Cell policy and the zero-point pathfinder. Then Cell dispatch, Advance6/Process,
shared owned records, full discarded previews, drawing and SDL acceptance precede
enabling Scatter. Direct routes, controls, clearance, frame scheduling, initial
records and named services remain supplied. General pathfinding, combat, economy,
AI, campaigns, multiplayer, audio, original saves and YR remain open. No startup/
full-frame/whole-game claim follows. No workers, Windows actions/transfers,
downloads, publication, system/Xcode/DRM changes or runtime executable-read expansion.
Source installations/discs and Outpost2 remain read-only; private originals/assets/
research/expectations/binaries remain ignored and unshipped.
