# Infantry Mark and membership on production map owners

The later [membership discovery join](INFANTRY_MEMBERSHIP_DISCOVERY_1006.md)
replaces the application's GI notification no-op under the original Cell gate.
Its new142-case proof uses actual visibility/discovery; the285-case checkpoint
below retains its supplied children and original scope. Actual recalculation is
joined separately; arrival/sight/objective progression remain incomplete.


This removes a map/list integration blocker for Boot Camp Day 1 GI walking.
`PreparedInfantryMembership` borrows the existing `MutableUnitMap`, actual
actor coordinates/Mark bytes/Walk/Next records and caller-owned Cell heads,
occupation words and House slots. **Boot Camp remains static.** Complete Walk
Process on these owners, E1 inputs, animation/drawing and ordinary SDL walking
remain to join; discovery/scheduler/actions still precede the first objective.
This is an internal checkpoint, not a delivered playable lesson.

## Recovered behavior and ownership

Before address work the supplied base executable was rehashed:4,485,392 bytes,
SHA256 `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Actual Infantry7A3540/InfantryType7A3A78/
Walk7AEAD8 dispatch is independently checked on that binary. Public/YR names
establish no behavior. No public/header/generated/lifted code, extracted table,
dependency or application executable read is added.

Complete Foot Mark4C2E60, map insertion54AB70/removal54AF70 and Cell
insertion473B30/removal473D20 execute together. Infantry uses its own lazy
foundation50A000: flagA411A0, originA4117C and sentinelA41180, distinct from
Unit's globals. Object's fallback initializer5D4470 and bounded foundation
copy482E10 also execute. The ordinary single-Cell geometry is shared; its
ownership and initializer dispatch are not inferred from tanks.

**Both Cell parents explicitly bypass occupation and eligibility for Infantry
kind15.** Insert473C7A/473C7E and remove473D8E/473D91 branch directly to their
returns. They never call41B470,508410 or5084A0. The initial proof's requirement
that those children execute was wrong; the coverage guard stopped it before
native comparison or receipt creation. Inspection and an independent coverage
diagnostic identified the bypass. The native shared kernel now preserves it.
Actual Infantry occupation remains in Walk's head transfer, already recovered
in [WALK_HEAD_1006.md](WALK_HEAD_1006.md), rather than being doubled by Mark.

`MembershipPolicy.hpp` holds one map/list algorithm used by the existing Unit
API and a borrowed view. `FootMarkView` similarly shares the existing Mark
kernel without copying/synchronizing actor74. The production binding:

- Borrows actual coordinates, Next, bridge79, Mark/redraw/limbo/special bytes,
  type/House/image associations and the same mutable map/fallback/floor cache.
  Binding performs no lookup, floor query or mutable field write.
- Borrows caller-owned primary/elevated Cell heads, occupation words and House
  slots. All future admission/head/Process consumers must use those same records.
  No copied actor/Cell, dummy Drive, second map or second movement algorithm.
- Preserves list oddities, raw alternate bytes, saved Cell-center words before
  floor, independent visibility centers, notification order and late slot reload.
  Missing late slots forward the saved point into the actual shared fallback.
- Keeps explicit `occupy`/`release` children on those owners for Walk binding;
  membership does not call them. Native checks exercise their shared fields;
  this membership proof does not establish their complete Process caller.
- Refuses split slot/table associations and aliased actor/Walk/Next owners.
  Map geometry/backing storage, actor records, foundation, numeric services and
  borrowed inputs must outlive the immovable binding. Clones need fresh views
  and callbacks. Initial associations/records are supplied, not E1 initialization.

Visibility, Infantry notification6C2440, recalculation472540, special-event and
atexit effects remain named supplied services. Notification mutations are
diagnostic ordering tests, not gameplay observations or recovered discovery.
The safe combined map-index domain remains explicit; unsupported actor kinds
and nonstock foundations are not generalized. Low-level service failures retain
preceding writes; no rollback claim follows.

## Proof, regressions and cost

Canonical original-only receipts:
`private/infantry-walk-20261018/membership-fresh-a2/{expected,report}.json`.
**285 sequences /501 complete original roots** match current C++. Actual entries
include351 Foot Marks,201/193 map insertions/removals,210/202 Cell insertions/
removals and340 Infantry foundation calls. There are2,124 selected stores and
zero eligibility/Infantry occupation entries. The matrix covers list profiles,
raw bytes, separate cold/warm foundations, type gates, repeated complete Mark,
occupation/House preservation across heights and flags, notification changes,
late slot replacement/removal and word/full-coordinate/fallback distinctions.

The unmodified guest code, dispatch/cast/numeric inputs, ABI/saved registers,
caller stack, selected stores and remaining arenas are guarded. Original
expectations are saved before native comparison. Current native source/runner
identities are separate from immutable original provenance. Normal/sanitizer/
uncached `membership-replay-*-a2.json` each report285 hits, zero misses and zero
original execution. No native results are cached.

`prepared-infantry-membership-check` covers actual shared Mark/list/occupation
owners, cold binding, two distinct actors, explicit occupation separation,
late notification/slot changes, saved center words, split/aliased-owner refusal
and clone isolation. Current native regression receipts preserve4,263 Unit Mark
sequences,594 Unit membership sequences,645 Infantry Mark sequences and165
command/Walk route sequences in both builds. Unit membership uses the actual
current v5 original receipt. Stale v3 was correctly rejected before execution;
no guard was relaxed or historical receipt relabeled. Its uncached v5 replay
also passes. Thirteen focused CTests per build and109 Python tests pass.
No broad capability closure or new SDL run is claimed; preview behavior did not
change. Local verification is not independent acceptance or frame fidelity.

Measured original generation1.099s, fresh native comparison0.071s; replay drivers
0.610s/5.475s/1.621s normal/sanitizer/uncached. Unit Mark replays0.255s/0.466s;
Unit membership0.302s/3.135s/1.083s including uncached; Infantry Mark0.216s/0.290s;
route0.329s/1.005s. Concurrent execution makes these costs nonadditive. CTest
bodies0.22s/0.92s; Python91+18-test bodies1.354s/0.274s. Earlier successful runner
builds5.79s/6.14s were followed by additional rebuilds whose full elapsed costs
were not measured. CMake reported final generation8.6s/8.2s. Preserved build
failures were new-target discovery, missing OpenSSL include propagation and a
missing PreparedData include. A Python invocation named a nonexistent test
module; the corrected invocation passes. First proof failed coverage, not an
original/native mismatch. Inspection/manual repair and total task-wall costs are
unavailable. `membership-validation.json` records private identities and failures.

## Reproduce and continue

```sh
./build.command
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/native --parallel 6 \
  --target prepared-infantry-membership-check infantry-membership-vectors
build/native/prepared-infantry-membership-check
env PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_infantry_membership test_infantry_mark test_walk_route

# New private audit/report paths; current native executes, zero originals.
env DEVELOPER_DIR=/Library/Developer/CommandLineTools PYTHONHASHSEED=0 \
  PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/infantry-membership-next.audit.json tests/compare_infantry_membership.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/infantry-membership-vectors \
  --render-data private/derived/ra2-1006/render-data.bin \
  --expectations private/infantry-walk-20261018/membership-fresh-a2/expected.json \
  --report private/infantry-membership-next.json
# Sanitizer: build/sanitize/infantry-membership-vectors, separate outputs.
# Uncached inspection control: --uncached before the driver.
# Fresh originals only for genuinely changed dependencies: omit expectations/
# report, use --output private/infantry-membership-new-fresh and a new audit in
# the authorized Mac-host JIT context. Never overwrite canonical receipts.

env PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/unit-membership-next.audit.json tests/compare_membership_current.py \
  --family membership --exe private/official-1006-probe/game.exe \
  --native build/native/unit-membership-vectors \
  --expectations private/map-depth-1006/unit-membership-v5/expected.json \
  --report private/unit-membership-next.json
# --family mark uses unit-mark-vectors and unit-mark-v2/expected.json instead.
```

`./run.command --boot-camp-preview` remains static content/selection with an
explicit RMB refusal. `./test.command` remains the broad native entry point at
playable integration. Next connect complete Walk commands/Process, admission/
speed and head occupation to these same production owners, then E1 inputs and
animation/drawing/SDL. Recover encountered retarget/failed routes rather than
substituting success. Genuine discovery/scheduler/actions still precede the first
objective. Only Apple Silicon macOS is tested; base RA2/YR remain incomplete.
