# Infantry bookkeeping for tutorial House transfer

The first tutorial Team's next Script20/13 must transfer its four existing GIs to
the player. That transfer must preserve the original House accounting, rather than
just changing an owner pointer. `HouseInfantryAccounting.hpp` now reconstructs
four complete-to-return E1 accounting paths and their counter children. Explicit
native integration exercises removal/addition on the same GI/Type/mission House
owners used by the application. No ownership transfer or live scheduling is yet
implemented by this checkpoint.

## Exact original scope

Supplied base:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. No public authored implementation, generated
game code, new dependency or runtime executable read was incorporated.

1,136 original sequences execute unchanged complete-to-return4ED440/4ED610/
4EA800/4EA970 E1 paths, actual491C50/491CB0 counters, actual70C490 history and
actual509800 kind getter. All complete parent instruction spans and their switch
tables are inspected/pinned, but other actor branches are not reconstructed.
E1 Object kind is15, distinct from its Type kind16 used by recruitment. Parent
entries:208/208/212/212; counter decrement484/increment436; history128; kind672.
Type80/Type40 queries, map67C150, vector resize8 and initial associations remain
supplied services/inputs. This proof is neither original startup nor complete
Techno6CD940/Infantry4CA7D0/Team Script20 transfer.

The original origin is `private/team-house-20261019/fresh-a1/expected.json`.
The verifier checks the exact executable, complete instruction boundaries, E1
vtable association and switch targets. The fixture checks caller stack, callee
registers, immutable code/tables, ordered service requests/stores and the entire
unrelated arena, including both old and replaced vector backings.

## Recovered order and numeric behavior

- 4ED440 calls map67C150 before querying actor kind, then Type80/Type40 and
 decrements House5480's indexed counter for E1. The second argument does not
 affect this E1 branch; the map child is required, never silently skipped.
- 4ED610 queries kind, bypasses registration for any nonzero actor5C1 byte, or
 queries Type/index and increments5480.
- 4EA800 writes actor324=0 even when Type202 suppresses further accounting.
 Otherwise it queries kind, decrements House234, then queries the Type/index
 again and decrements5440.
- 4EA970 writes actor324=1 before the same Type202 gate. It queries kind and
 the Type/index before incrementing234, increments5440, then independently
 increments historyA70 when the signed index is below signed historyCount1270.
 A failed5440 resize does not suppress history. No saturation is invented.

Complete491C50/491CB0 save the old signed capacity. An index at/above capacity
requests `(index+10,0)` from virtual resize8 and tests only its low byte. Failure
returns0 without zeroing or counter arithmetic. Success rereads live capacity
and backing while zeroing the newly added range, then increments/decrements the
indexed uint32 value with wrapping and rereads the returned value. The old
backing may be replaced. Negative indexes, overflowed allocation requests and
unowned backing access are outside the native supported domain and refuse.
Actual70C490 performs a signed index/count comparison and a wrapping history
increment only when admitted. Negative history counts produce no store for the
supported nonnegative indexes.

Coverage includes all four parents, both direct counter roots, inside/outside
capacity, low-byte resize results0/1/0x100/-1, old/new backing, signed integer
extremes, raw Type202/actor5C1 bytes0/1/128/255 and signed history limits.
Diagnostic Type/kind callbacks mutate the same borrowed index/total/Type gate
before late reads. These mutations test ordering; they are not gameplay events.

## Shared native owners and supplied boundaries

Each actual `UnitDiscoveryHouse` now owns its234 total,5440/5480 vectors and A70
history. GI324/5C1 and E1 Type202/index live on the existing `InfantryWalkState`
and `InfantryWalkType`. Supplied map startup seeds counts from the actual map's
Infantry records and rules index list; this is not a recovered constructor,
original initialization order or original allocation/capacity claim. Stock324=1,
5C1=0, Type202=0 and history capacity512 likewise remain supplied.

The synchronous borrowed adapter rebuilds spans/callbacks for each invocation.
Its host allocation service uses owned vectors with a bounded512-slot policy;
it does not purport to reconstruct the allocator. No callbacks or borrowed spans
are stored on a clone. Existing House clones copy counter/history values onto
independent backing. The source-mutation snapshot now covers all vector data,
metadata and new actor fields, not just vector object bytes.

The actual-owner check removes a recruited-domain Other2 GI's registered/active
counts and adds the corresponding counts/history to the player House on a
disposable clone. It verifies original field effects, the still-unchanged actor
owner, independent source/player state and another clone's survival after source
destruction. Its map67C150 child is a supplied recorder. This test does not call
the accounting sequence a completed transfer, mutate the live SDL world or
manufacture objective success. Future transfer must call these kernels at their
original positions among the remaining children, not invoke this diagnostic as
an alternative to6CD940.

## Reproduction and reuse

```sh
./build.command
./test.command
build/native/boot-camp-walk-check private/official-1006-probe
./run.command --boot-camp-walk
PYTHONHASHSEED=0 PYTHONDONTWRITEBYTECODE=1 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/NEW-house-infantry.audit.json \
  tests/compare_house_infantry_accounting.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/house-infantry-accounting-vectors \
  --expectations private/team-house-20261019/fresh-a1/expected.json \
  --report private/NEW-house-infantry.json
PYTHONHASHSEED=0 PYTHONDONTWRITEBYTECODE=1 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tests/test_house_infantry_accounting.py
```

Use new private audit/report paths. Sanitizer substitutes
`build/sanitize/house-infantry-accounting-vectors`. Reuse explicitly reports1,136
hits/zero misses while still executing the current native comparisons/guards.
Changes to relevant executable/original oracle/input/environment identities
require a fresh private `--output` origin; native-only changes reuse originals.
No native verdict is cached and originals were generated once. An initial
inspection guard caught a two-byte-short counter range before generation; the
range now includes the complete final ret4. No original failure was bypassed.

Validation logs/commands/costs are in `private/team-house-20261019/validation-a1/`;
receipt `private/house-infantry-accounting-receipt-a1.json`. Local validation is
not independent acceptance or original-game observation. Only Apple Silicon
macOS is tested; base RA2 and Yuri's Revenge remain incomplete.

## Current validation and measured costs

238 native/237 ASan/UBSan CTests, four new and39 prior Python guards, both
actual-owner checks and256-tick desktop SDL input/drawing pass. The actual owner
checks cover shared counters, source isolation and clone/source destruction.
The SDL receipt explicitly retains right-frame6/left-frame2, ordinary controls
and disabled objectives. Screenshots do not establish original frame fidelity.
Each current build replays1,136 new accounting plus3,796 prior Team/resident/E1
sequences:4,932 hits/zero misses. All current native comparisons run. The old66
permission origin remains excluded at its previously documented identity mismatch;
no old receipt was relabeled or regenerated.

Original generation.550s; native build48.601s; sanitizer configure17.012s/
build50.770s; owners7.081/92.233s; CTests10.523/7.335s; new Python guards.221s;
new accounting replay1.197/.498s; SDL12.655s. Prior audited replays.264-2.917s,
including E1 Walk1.652/1.245s. Concurrent build/check costs are nonadditive and
include host load; they do not establish a performance regression. Initial
configure/focused build, prior39 Python guards, inspection/repair and total wall
time are unmeasured. The source change to shared House/GI storage required
rebuilding its dependents. No running proof inputs were changed. Sanitizer SDL
app is not built. These checks are local verification, not independent acceptance.

## Next transfer integration

Reuse complete4ED760 (`findHouseAllianceCountry`), these accounting kernels,
existing ordinary target/destination and sight children where their actual
entered domains match. Recover the bounded complete6CD940/4CA7D0 E1 path and
its remaining entered children, including actual408/6155E0 effects, map67C150,
6D7C80 registry reference cleanup and the surrounding map/threat/refresh effects.
Keep startup and supplied adapters explicit; do not require recovery of unentered
branches merely because the parent contains them. Then join command20 on the
same owners and verify real player control before enabling scheduling. Arrival/
sight, initial instructions and the other requirements in
[FIRST_DAY1_TRANSITION.md](FIRST_DAY1_TRANSITION.md) still apply.
