# Actual Infantry membership discovery

This removes the no-op GI notification reached by ordinary Boot Camp membership
insertion. The actual existing Infantry/House/mission records now receive the
recovered Techno discovery call when the Cell parent's real predicate allows it.
It advances the original movement effects required before live sight scheduling
can discover Objective1 structures. It does not create an objective transition.

## Recovered association and current binding

Before address inspection the supplied base executable was hashed:4,485,392 bytes,
SHA256 `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD and unverified pristine
authenticity remain distinct. No public code or YR behavior supplied this finding.

Complete Cell insert473B30 evaluates primary568140, then secondary5683C0 only
when primary's low byte is zero. When either succeeds,473C58 reads live session
modeA3D298: zero bypasses notification. When both fail, the mode load is skipped.
On the notifying branch473C61 reads current HouseA35DB4 and dispatches the actual
Infantry vtable7A3540 slot180 to6C2440. The same vtable's Mission16C/1D0 slots
resolve to594770/594CB0. `verify_infantry_membership_discovery.py` independently
pins these on base RA2 alongside the complete existing membership/discovery
ranges. This is not an inference from Unit or Yuri's Revenge dispatch alone.

`UnitMembershipServices` adds optional live getters at those exact boundaries;
existing scalar diagnostic profiles retain their behavior. Boot Camp binds the
getters to the existing mission owner's discovery mode/current House, then calls
`discoverInfantry` with that exact House and the actual actor's discovery record.
The existing default method still uses current House. The explicit-argument API
preserves known/null discoverers and refuses foreign House ids or incoherent
nonnull GI Tags; foreign-id refusal is a native safety boundary. Original null
and repeated semantics remain in the shared recovered `discoverUnit` kernel.
No copied actor or new House/session owner was introduced. Visibility predicates
also read that same mission session mode; overrideA3D548 remains supplied zero.

The callbacks are bound before initial Mark. At that startup point visibility
still uses the prior supplied true result until the actual visibility owner is
constructed; session mode0/current-player association are supplied startup, not
recovered initialization. Later membership reads actual visibility. A conditional
GI discovery producer is now present through Mark; this does **not** activate
arrival174/500AA0, add/remove-sight, reveal-area or structure/objective discovery.
Ordinary visible training Cells with session0 still bypass notification.

## Original proof and actual-owner checks

142 new sequences execute562 complete original roots, plus11 stock numeric/
direction roots. They join complete Infantry Foot Mark, map insert/remove, Cell
insert/remove, actual primary/secondary predicates and Techno/Object/House/
Mission discovery. Counts include288 Marks,284 map insertions,278 removals,
284 Cell insertions,284 primary/72 secondary predicates,248 discovery parents
and45 QueueMission entries. Both Houses, modes0/1/-1, heights, visibility flags,
raw control/discovery bytes, mission/current/queued values, repeated Marks and
alternate heads are covered. Initial actor/type/House/map/registry/FP records,
null Tags, atexit and recalculation callback remain supplied in this fixture.
The prior actual recalculation binding retains its separate proof scope.

The new oracle subclasses the existing authored Infantry fixture and reuses the
shared Unit discovery observation/House-arena audit methods on identical logical
fixture addresses. It executes Infantry's own vtable/foundation/Mark parents;
no Unit Mark substitutes for Infantry. Guest instructions/dispatch/input arenas,
allowed blocks and selected writes, ABI/caller stack/saved registers, House
capacity tails, shared fallback and ordered observations are audited. The native
`D` vector profile borrows the existing prepared mutable map, membership and floor
owners, adds actual visibility/discovery children, and preserves all prior `U`
profiles. This is a bounded joined proof, not full original Boot Camp Process,
sight scheduling, original startup or rendering fidelity.

Canonical original-only expectations:
`private/boot-camp-20261020/infantry-discovery-fresh-a1/expected.json`.
Current normal/sanitizer comparisons each explicitly reuse142 with zero misses.
The same profiles separately reuse285 unchanged Infantry membership sequences
and594 Unit membership sequences after the shared kernel change:1,021 hits/
zero misses per profile. Current native comparisons always execute; no native
pass/fail is cached and original-only receipts remain immutable.

Native-only late-getter tests mutate mode/House from visibility callbacks and
verify load/notification omission/order. The exact original load instructions
are inspected; the142 original sequences hold those globals fixed within each
root, so callback-driven global mutation is not a differential claim here.
Actual Boot Camp owner checks use the actual GI and mission Houses, poison unused
scalar snapshots, exercise both Cell gates/repeated notification, preserve source
worlds, rebind warm clones and continue after source destruction. Null-Tag GI
discovery must leave Objective1's text/Trigger state untouched. The prior salted
Cell-buffer/eight-direction/Stop/repeated-order/refusal regressions remain.

Broad201 normal/200 ASan+UBSan CTests, test.command,12 focused Python tests and
both rebuilt actual-owner checks pass. Actual SDL selection/move/pause/refusal/
Stop/repeated-order/deselection and horizontal sprite drawing pass256ticks.
Both captured horizontal moving sprites were visually inspected.
This is local verification, not independent acceptance. Initial visibility,
route/schedule/presentation and other named effects retain supplied boundaries;
ordinary Objective1 and both complete games remain unachieved. No worker, new
runtime executable read, Windows action/transfer/download or system/Xcode/DRM
change occurred. Only Apple Silicon macOS is tested.

Original generation2.793s/fresh outer3.980s;142-case native/sanitizer comparisons
.040/3.162s. Native CTest3.00s, test.command outer4.152s, actual normal owner5.920s;
sanitizer CTest20.89s (outer20.954s), actual sanitizer owner57.307s. Other replay costs and exact hashes/logs
are in `private/boot-camp-20261020/infantry-discovery-receipt-a1.json`.
Build/config/inspection/edit/total wall costs were not instrumented; concurrent
costs are not additive. No failed build or original/native comparison was accepted.

## Reproduce and continue

```sh
./build.command
./test.command
./run.command --boot-camp-walk
build/native/boot-camp-walk-check private/official-1006-probe
build/sanitize/boot-camp-walk-check private/official-1006-probe
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest \
 tests/test_infantry_membership_discovery.py tests/test_infantry_membership.py \
 tests/test_infantry_walk_world.py

# Explicit original reuse, with new private report/audit names:
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
 tools/run_evidence.py --audit private/infantry-discovery-next.audit.json \
 tests/compare_infantry_membership_discovery.py \
 --exe private/official-1006-probe/game.exe \
 --native build/native/infantry-membership-vectors \
 --render-data private/derived/ra2-1006/render-data.bin \
 --expectations private/boot-camp-20261020/infantry-discovery-fresh-a1/expected.json \
 --report private/infantry-discovery-next.json
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
 tools/run_evidence.py --audit private/infantry-membership-next.audit.json \
 tests/compare_infantry_membership.py \
 --exe private/official-1006-probe/game.exe \
 --native build/native/infantry-membership-vectors \
 --render-data private/derived/ra2-1006/render-data.bin \
 --expectations private/infantry-walk-20261018/membership-fresh-a2/expected.json \
 --report private/infantry-membership-next.json
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
 tools/run_evidence.py --audit private/unit-membership-next.audit.json \
 tests/compare_membership_current.py --family membership \
 --exe private/official-1006-probe/game.exe \
 --native build/native/unit-membership-vectors \
 --expectations private/map-depth-1006/unit-membership-v5/expected.json \
 --report private/unit-membership-next.json
# Substitute sanitizer runners and new report/audit destinations.
./run.command --boot-camp-walk-smoke-test private/infantry-discovery-sdl-next
```

Next finish actually entered Mark/redraw, Walk animation and crossing dirty
children on the same owners and verify complete movement producers before
joining arrival/crossing sight. Do not implement unentered branches solely to
empty a callback list. Then join viewport/queue consumers and required mission
children for ordinary SDL Objective1, Day1 completion and Day2 progression.
