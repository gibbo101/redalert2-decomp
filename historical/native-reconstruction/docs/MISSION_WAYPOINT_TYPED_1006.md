# Waypoint discovery with typed Tag-expiration recipients

The separate complete waypoint/discovery/Tag/Trigger chain now reaches generic
Tag44 broadcast and actual Infantry501CB0/Foot4C8460 and Building449E40 through
the shared Radio/Techno/Object parents. All108 original sequences match, including
seven broadcasts through119 Infantry and119 Building recipients. This closes the
previous base-Object-only association in the research join. Production still uses
its separately supplied Object-prefix recipients; live objectives remain disabled.

## Shared fields and corrected stock virtual

`bindMissionInfantryTagExpiration` and `bindMissionBuildingTagExpiration` borrow
the existing field views and capture service bindings with their explicit external
lifetimes. Binding reads no gameplay fields and makes no queries. The subject,
flags and actor owners must outlive recipients. Clones must rebind these callbacks;
copying a callable does not clone its owners. Foreign Tags and late bit0-set
subject flags refuse before inherited writes. Exceptions retain preceding effects.

`MissionExpirationOwnerView` borrows either a pointer reference or pure accessors
to a live logical identity field. Discovery's integer House handle and expiration's
pointer comparison now refer to the same Owner. No copied Owner is synchronized
before or after callbacks. Accessors must only read/write that field, without
queries, observers or gameplay services. The normal pointer API remains supported.
Its clear precedes byte372 as before; old source/runner proofs are replayed with
new explicit identities. Direct guard cases check external writes, copied views,
null stores and missing-accessor rejection.

The fixture's34 distinct actors share their actual Tag slots, resident Next,
mission98/queuedA0, byte372, House owners and radio counts/backings between
discovery and expiration. Each has independent inherited/typed fields and seven
backings. The actual visibility map, Cells, shared fallback and packed Cell words
are also borrowed by Foot destinations and generic map expiration. No second map
or actor snapshot is substituted during broadcast. Returned recipient bindings
are exercised after their binding scope ends, including foreign-Tag/late-flag
refusals and a late live Owner change.

A1 exposed an association the earlier isolated typed proof had supplied: stock
Tag+48 is410260, not common Object5D4E40. The actual35-byte routine copies globals
839CA8/AC/B0 to the caller's coordinate output and returns that output pointer.
The verifier fingerprints the complete root and stock Tag vtable target. This join
executes it unmodified119 times; native services read the same supplied live
global-coordinate owner. Tag+88 has deliberately different coordinates, so an
Object-position substitution fails. Global startup values remain supplied. This
does not broaden runtime executable reads.

An optional non-mutating `missionRead` observer marks the existing inline Mission
getter at its actual entry, only when494 matches. It cannot run gameplay services
or mutate fields. It records the same getter trace as discovery; the getter's
algorithm and late field reads are unchanged.

## Exact original evidence and supplied boundaries

Target4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD and unverified pristine
provenance remain distinct. Only Apple Silicon macOS is tested. No public/YR/
recomp implementation, dependency or runtime executable read was added.

Canonical original-only expectations:
`private/boot-camp-20261018/waypoint-typed-fresh-a3/expected.json`, SHA256
`873809640a7ec5518c84bd8adf43cdf0d4171d94f8ba4366fc1b90092f60685c`.
108 complete roots comprise84 enabled and24 disabled cases. They execute15 Tag
roots,12 RegisterEvent/event roots,8 action traversals,7 Trigger retirements,
7 broadcasts,238 complete inherited Techno/Radio/Object calls,238 passenger unlink
calls,602 pointer searches,119 Foot/Infantry and119 Building calls,119 stock Tag
coordinate calls,119 health ratios and119 secondary Tag-kind dispatches. There
are18 supplied nested callbacks,238 supplied retry-range/target calls and119
supplied strength/animation calls. Discovery includes1,780 Cell roots,2,023 closest
selections,429 common and333 Building discovery roots; visibility/map/fallback
and later House/mission effects are compared on the same owners.

Whole mutable arenas, selected ordered stores, typed references/counts/backings/
tails and final discovery/Tag/Cell/House state match. Original instructions are
unmodified in research-only Unicorn. Code/tables/vtables/globals, ABI, caller
stack/return/preserved registers, immutable maps and untouched bytes are guarded.
The nested Techno retry local is explicitly supplied at its actual stack offset.
Original callback removal words are checked against the caller's full EDX, whose
low byte is1; the existing portable Tag callback carries a byte. These entered
effects depend on the low byte. Unspecified register-high-byte preservation by
the portable Tag caller is not claimed. The earlier typed direct proof retains
its broader raw-word inputs under separate identity-checked replays.

RTTI/selection/action/activation/notification/redraw/refresh, expiration target/
retry/predicate/nested/strength-association/animation effects and initial startup/
record/type/FP/global-coordinate associations remain supplied. Current Tag profile
has flags14 bit0 clear and kind44, excluding Object-subject discovery and Building
kind4 factory branches. The diagnostic nested callback installs a late5A8 match;
it is an oracle input, not an observed gameplay effect. Initial nonnull control/
other deeper services not entered here retain their earlier separate proof scopes.
No original gameplay observation, independent acceptance, full-frame or whole-game
fidelity follows from this bounded join.

## Failed attempts, regression closure and cost

A1 stopped on uninspected410260, exposing the incorrect stock Tag coordinate
association. A2 executed roots but failed its positive nested-dispatch coverage
guard; its supplied health policy made the broadcasting Tag records zero-health.
A3 adds positive-health coverage and completes original generation, then fails
native comparison at a missing Mission-getter trace. A4 adds only that native
non-mutating observation and passes replays against the saved A3 original-only
expectations. The failed audits remain failed; they are not relabeled as passing.
No rerun of original execution is hidden behind A4 reuse.

Both full builds pass; final141 normal/140 sanitizer CTests pass in2.40s/12.61s.
All1,446 Python tests pass in33.278s before the native-only trace repair; Python
sources are unchanged by that repair. Final new108 and prior448 Techno/871 typed
families pass normal/sanitizer/uncached replays with zero misses and no original
execution.61 prior binaries, including application/owner checks, are unchanged;
four expiration runners rebuilt and two joined runners have new identities.
Prior owner/106-tick SDL scope is retained by app/check identity. No new GUI
acceptance or closed finalizer rerun is claimed.

Successful original generation140.720s. Final new replay driver costs are
1.193s/3.002s/12.533s; native comparisons0.291s/2.065s/0.277s. Replays reuse108
original results each; the uncached control disables inspection reuse only. Costs
overlap and exclude some startup; complete build/manual repair/task-wall costs
were not measured. No new cache was added. Private receipt/inventory:
`waypoint-typed-receipt-a4.json`, `waypoint-typed-runner-inventory-a4.json` under
`private/boot-camp-20261018/`.

```sh
./build.command
./test.command
./run.command --boot-camp-walk
build/native/mission-waypoint-typed-vectors --guards
env PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/waypoint-typed-next.audit.json \
  tests/compare_mission_waypoint_typed.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/mission-waypoint-typed-vectors \
  --expectations private/boot-camp-20261018/waypoint-typed-fresh-a3/expected.json \
  --report private/waypoint-typed-next.json
# Substitute build/sanitize runner; add --uncached before the driver for the
# inspection control. Choose new audit/report paths for every invocation.
```

Next close required stock getter/target effects and production Building recipient
ownership, then production reveal/full warm isolation and ordinary SDL objective
gates. Private `waypoint-typed-next-stock-services-a3.txt` inspects stock type84,
predicateC0/1E4, queryCC and target370 entries; it is not a completed child proof.
Both games and Boot Camp Objective1 remain incomplete; goal active. No workers,
Windows actions or runtime executable-read expansion.
