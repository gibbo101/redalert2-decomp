# Building expiration target and pending mission services

Separate SDL-free Building expiration now calls actual stock null-target setting,
availability, pending mission restoration and simple getters on the same borrowed
actor fields. All1,621 original sequences /2,571 top-level calls match. This adds
750 service/caller sequences and retains all871 earlier typed sequences. It does
not adopt these services in waypoint recipients or production, and live objectives
remain disabled. Both games and Boot Camp Objective1 remain incomplete.

## Ownership and ordering

`MissionBuildingTarget.hpp` borrows actor/type/Owner references; it owns no
mirrored gameplay state. Count54C is the same actual count used by Building's53C
vector. Pending9C is distinct from queuedA0; queuedA4 is a separate byte. Registry
binding is pure field access. Named service callbacks may mutate fields, and
subsequent original reads remain late. Exceptions propagate after prior writes;
there is no rollback promise.

Complete450360 availability preserves signed count54C/word3FC/countC6C, health
nonzero rather than positive, initial type flags1217/11FE and the late type418
reread for1206/actor59C. Supplied House4E8330 returns a double. Actual threshold
79A708 is1.0; unordered/NaN takes the low-power branch, then rereads count54C.
It does not recheck health after the callback. No arithmetic model is substituted.

Complete6C5070 calls supplied weapon-index virtual2B8 first, then permission350
with the same null target and exact signed index, returning its low byte. Fixed
stock vtable associations remain guarded. These terminal weapon effects are not
recovered here.

The null-target path of6C9AF0 always clears byte404 first. Equal-null228 returns
immediately without clearing310 or consulting attachment25C. Otherwise228 clears,
then supplied68A490(service238,null) runs if the service exists. Only a late-null
228 clears310. A live25C and zero permission result cause releaseF0 on the late
attachment, followed by unconditional25C clearing even if release replaces it.
Complete440450 for requested=null invokes availability unless Mission98 is19,
then this actual base clear. The general nonnull target path is excluded by the
API; its self/map/Infantry handling is not silently modeled as clearing.

Complete594D80 saves pending9C; if it is not-1, stores98, then9C=-1, thenA4=0.
6CD880 restores first and reads late22C before the Building setter. A nonnull22C
is explicitly refused after those mission stores, without rollback. Actual stock
453C60 type getter,5950E0 pending predicate,41B410 raw byte170 and41B2E0 null query
replace their earlier supplied services in this separate fixture. Other named
inherited effects, including virtual400, remain supplied.

## Exact original evidence

Target4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Only Apple Silicon macOS is tested.
No public/YR/recomp code, dependency or runtime executable read was added.

Verifier fingerprints complete service spans, inherited roots, threshold and
stock Building vtable79CBBC associations. Research-only Unicorn executes original
instructions unmodified. Existing checked-call machinery guards ABI, stack,
registers, mutable arena versus expected writes, input code/tables/vtables/globals
and untouched padding. The authored x87 double-return helper and its transitive
source closure are identity-checked. Native store traces represent logical stores,
not host instruction widths.

Canonical original-only expectations:
`private/boot-camp-20261018/building-services-fresh-a1/expected.json`, SHA256
`761e8e532f3b9c74986bfb0638fcec0aeb547972f0758939278dda4faf42d38c`.
A1 passed fresh original/native comparison. A2 adds native API/lifetime/refusal
checks and fixture admission guards, then replays the saved originals under their
unchanged source identities and separately records rebuilt runner identities.
No failed original attempt is relabeled. The initial Python input roundtrip found
an invalid supplied service identity before original execution; that fixture was
corrected before A1.

Original counts include487 Building expiration calls (167 retained/320 newly
joined),512 Building setters,692 base clears,836 availability calls,290 permission
wrappers,246 pending restores,186 resumptions,350 type getters,242 pending
predicates,350 disguise getters and242 null queries. Supplied callbacks execute
439 power,338 service-clear,290 weapon-index/permission and139 release calls.
Coverage includes repeated operations, equal-null exits, signed limits, zero and
negative health, low-byte returns, NaN/equal/infinite thresholds, independent
pending/queued fields, late type/count/target/attachment changes and caller stores.
These diagnostic mutations are supplied inputs, not original gameplay observations.

All871 prior typed rows retain every original token before the new SERVICES
snapshot, with both receipt hashes in `building-services-parent-projection-a2.json`.
All67 previously tracked app/owner/runner binaries are hash-identical;2 new runners
have separate identities in `building-services-runner-inventory-a2.json`.
The prior owner and106-tick SDL scope is retained by identity; no new GUI acceptance
or closed finalizer rerun. Local verification is not independent acceptance.

House power,68A490,weapon leaves,releaseF0,earlier virtual/RNG/animation/nested
effects, initial records/type/map/FP/padding associations remain supplied. General
nonnull targets, Object-subject/factory-kind4 expiration, waypoint adoption,
production recipients/reveal, full warm isolation and ordinary objective completion
remain outside this milestone. No whole-frame or whole-game fidelity follows.

## Verification and commands

Both full builds pass. Final142 normal/141 sanitizer CTests pass in1.83s/10.90s;
1,449 Python tests pass in31.330s (outer process37.716s). Verification receipts
also retain outer CTest process costs2.688s/10.948s.
New1,621/prior871 families pass normal/sanitizer/uncached replays with zero misses
and no original execution. Fresh generation took4.077s. New replay driver costs
were0.618s/4.451s/1.289s, including native comparisons0.119s/3.993s/0.121s.
Concurrent costs overlap. Full build, manual repair and total task-wall costs were
not measured. No cache was added.

```sh
./build.command
./test.command
./run.command --boot-camp-walk
build/native/mission-building-expiration-services-vectors --guards
env PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/building-services-next.audit.json \
  tests/compare_mission_building_expiration_services.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/mission-building-expiration-services-vectors \
  --expectations private/boot-camp-20261018/building-services-fresh-a1/expected.json \
  --report private/building-services-next.json
# Substitute build/sanitize runner; add --uncached before the driver for the
# inspection control. Always choose fresh audit/report paths.
# Fresh original proof: replace --expectations/--report with --output pointing
# to a new ignored directory; research-only Unicorn requires JIT permission.
```

Next join these services into the shared typed waypoint recipient chain, then
close remaining required effects and production recipient ownership/reveal/full
warm preview/ordinary SDL objective gates. Preserve live-objective refusals.
