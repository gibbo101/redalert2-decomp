# Waypoint discovery through actual Tag and Trigger dispatch

The separate waypoint chain now joins actual6C2440 ->6B3DF0 ->6ED740/6E6050/
6ED830, persistence,6ED990,5D4430 and null47A460. It keeps shared actor/House/
Cell/fallback/Tag/Trigger/queue identities through the existing kernels. All108
original sequences match. Action effects, expiration broadcasting, allocation,
notification/redraw/refresh and startup retain supplied boundaries. No ordinary
Objective1 completion or production waypoint reveal claim follows.

## Packed location and production correction

Discovery's globalAC0148 value is passed as the packed Cell location argument to
Tag RaiseEvent. Its force argument is zero and source is null. The legacy native
`UnitDiscoveryWorld::tagContext` name remains to preserve older driver identities;
it carries this signed32 storage, cast back to raw32 location at the bridge.
It must not be treated as the pulse's force flag. The original proof explicitly
checks all five arguments at6B3DF0 entry, including nonempty values whose low byte
would otherwise force Trigger registration and skip event queries.

`WaypointTaggedDiscovery.hpp` borrows an existing discovery binding, actual Tag
slot and object identity. It refreshes the native pointer-presence projection,
scopes the world callback to that owner, then calls the same Unit/Building
kernels and Tag RaiseEvent. Prior callbacks restore on normal returns, early
rejection and exceptions. Restoration is not a rollback claim for actor/Tag
mutations already reached. Foreign/ambiguous bindings refuse; no owner or House
copy, scheduler or alternate mission engine is introduced.

Boot Camp now adopts this same bridge for its existing explicit structure-
discovery path. Its supplied AC0148/ABFE28 association selects the empty Cell
sentinel; initialization supplies that raw value instead of a zero pseudo-context.
The old adapter forwarded context into force and separately substituted empty
location; the new adapter forwards actual location with force0. A nonempty
production association remains refused because its Cell Tag owner is not bound.
The existing `tagServices.notifyExpired` already calls actual native expiration
broadcasting, so adoption retains it. Actual expiration is NOT part of this new
isolated original join. The former duplicate callback/wrapper is removed.

Warm clones retain the supplied location association and rebind Tag/object
references to their own owners. Private-data checks retain actual action requests,
Tag expiration, Trigger-before-Tag deferred order, message drawing/expiry and full
source/renderer isolation. These owner checks remain native composition evidence,
not one original-game or whole-mission proof. Live scheduling remains disabled.

## Shared-state original proof

Target4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD and unverified pristine
provenance remain distinct. Exact-base waypoint/object and Tag/Trigger/event
inspections compose; original instructions execute unmodified in research-only
Unicorn. No public/YR/recomp code, new dependency or runtime executable read.

Canonical expectations:
`private/boot-camp-20261018/waypoint-tag-fresh-a1/expected.json`, SHA256
`76d90e93a404c0cd6cfc3b433e72eae3a3f8e5461cce3698466788aef3085fb8`.
108 roots comprise84 ordinary/24 disabled calls.96 base scenarios are retained
with explicit Tag policy;12 additional cases exercise executing/suppression guards,
single-instance persistence1 and empty-location paths at actual tagged discoveries.
These cases supply coherent12 or1 initial Object Tag references/instance count.

Actual child calls include168 area passes,14,726 visibility changes,29,452 masks,
1,780 Cell-discovery roots,2,023 closest selections,429 common/333 Building
discovery calls,335 Building/96 common coordinate getters,15 Tag calls,
12 RegisterEvent,12 event roots,29 House resolvers,8 FireActions,7 Trigger
Destroy,5 Object assignments and2 Cell clears. One persistent event stores its
occurred bit and enters ResetTimers without a timer-kind child. Queue append
order and all8 backing slots match. No heap growth or Building activation enters.
Supplied leaves record8 actions,3 action-driven Owner changes,7 expiration calls,
1,381 notifications,1,780 redraws and16 refreshes. Action results/mutations are
explicit diagnostic inputs, not recovered action implementations.

The Tag Cell lookup shares the actual fixed-map table/fallback with waypoint,
visibility and masks. Nonempty misses update fallback.point before the actual
null Cell Tag clear; its later discovery effects see that same point. This is
not a private substitute Cell or a precomputed destination. The empty sentinel
bypasses that lookup. T telemetry identifies Tag map queries independently of
existing P/C/G/V/M/Q consumers.

Ordered query/fallback/coordinate/discovery/Tag/event/action/store traces and
complete mutable projections match after each root:17 visibility/Cell Tag records,
34 actors/Object Tag slots, both Houses, Tag instances/executing, Trigger destroyed/
occurred and deferred count/full backing. Caller stack/return/preserved registers,
code/tables/globals/type/vtables and all unselected arena/padding remain guarded.
Queue headers are separately guarded outside the arena. Only named writes are
permitted. Foundation/mask/spread inputs and House/scenario/Tag startup remain
supplied. Null Cell Tag clears do not establish nonnull Cell association behavior.
This is isolated binary-derived evidence, not full-frame or whole-game fidelity.

## Validation and measured cost

Both full builds pass.137 normal/136 sanitizer CTests pass in5.77s/16.56s;
1,434 Python tests pass in29.200s. New108, previous96 waypoint-object and1,010
standalone Tag sequences pass normal/sanitizer/uncached replays with zero misses,
explicit current source/runner identities and no original execution during reuse.
Older closed finalizers remain closed;44 tracked prior runners are hash-identical.
Application and both private-data owner checks are rebuilt and revalidated.
Historical Tag runner comparisons and new runner identities are separate inventory
entries, not silently carried-forward native results.

Both private-data owner checks pass. Rebuilt actual SDL106-tick selection/move/
pause/Stop/repeated-order/deselection and discarded warm-preview acceptance passes;
arrival image inspected. Live objectives remain disabled. Injected isolated-clone
stock objective text remains diagnostic:468 glyph/1,121 fill stores, not ordinary
completion. Only Apple Silicon macOS is tested. Local checks are not independent
acceptance.

Fresh original generation70.470s, driver72.370s, native comparison0.268s. No
failed original run or proof repair occurred. Exact replay commands/costs,
source/runner hashes, inventories, owner/SDL outputs and logs are private in
`waypoint-tag-replay-commands-a1.json`, `waypoint-tag-runner-inventory-a1.json`
and `waypoint-tag-receipt-a1.json`. Build/review/approval/GUI/tool and private-owner check costs were not
separately measured. No cache was added; immutable inspection/expectation reuse
retains source/runner/input/receipt guards and uncached controls.

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
./test.command
DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
build/native/boot-camp-walk-check private/official-1006-probe
build/sanitize/boot-camp-walk-check private/official-1006-probe
./run.command --boot-camp-walk

env PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/waypoint-tag-next.audit.json \
  tests/compare_mission_waypoint_tag.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/mission-waypoint-tag-vectors \
  --expectations private/boot-camp-20261018/waypoint-tag-fresh-a1/expected.json \
  --report private/waypoint-tag-next.json
```

Use new audit/report paths. Sanitizer selects its runner; uncached inspection
control puts `--uncached` before the driver. Fresh original replaces expectations/
report with `--output private/NEW-DIRECTORY` and requires local JIT access.

Next join actual expiration/mission action effects on these owners, then production
waypoint/reveal binding and full warm discarded-preview isolation. Ordinary live
sight/arrival/clock-before-producers, Team/alliance/audio and SDL Objective1
acceptance remain open. Both full games incomplete; goal active. No workers/
Windows actions/transfers/downloads/publication/system/Xcode/DRM changes.
