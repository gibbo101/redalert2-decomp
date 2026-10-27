# Production mixed House map sight scans

The later [shared House integration](BOOT_CAMP_SHARED_HOUSES_1006.md) supersedes
the separate movement/visibility House ownership described at this checkpoint.
Its remaining effect/scheduling gates still apply.

The explicit `BootCampWalkWorld::composeHouseMapSight` seam now calls complete
49E000 removal /49DE00 addition over the five existing GIs and two existing
objective Buildings. It reaches actual Techno sight/removal, reveal-area,
visibility-change/discovery and post-sight on the production owners. It is not
scheduled by walking, SDL, MakeAlly or action37. Both games and Boot Camp Objective1
remain incomplete; only Apple Silicon macOS is tested.

## Owners and supplied initialization

The stable registry contains actual GI addresses and actual mission StructureOwner
addresses, in supplied scenario order. There is no copied actor. Count and live
backing are separate persistent owners. Warm clones preserve slot order/nulls,
remap every actor and rebind the span; foreign actors/backings refuse. Binding
makes no map/floor/visibility queries. Original logic-registry construction and
membership beyond these seven owned actors are not claimed.

Building sight state now belongs to the same StructureOwner as discovery, Tag
expiration and resident membership. Position88 and byte373/Owner use the existing
resident/discovery fields. Building type lookup borrows the actual type418 and
stable expiration type registry. Type resolution occurs only at the entered
virtual80/type child, so byte76 skips do not validate or read a foreign type.
That early-exit boundary has explicit native coverage. Type Sight530 is supplied from user rules; these
two types have no promoted sight abilities, and an entered override is refused at
construction until its loader is supported. Flag76, enabled32D, veterancy, country
byte and initial sight records remain supplied startup. The GI sight state keeps
its prior values and borrows its existing enabled/coordinate/veterancy fields.

Type bytes534/ADD retain supplied zero defaults with no inferred semantic names
or recovered stock-default claim. The forced-current-House534 path is implemented
by the actual scan/sight kernels and tested with a diagnostic input. Entered image
virtual3AC/3B0 remains explicitly unbound and throws after any earlier effects;
there is no rollback guarantee. This seam must not be enabled as ordinary play
until required type initialization/image effects and the remaining callers are
recovered and accepted.

The House scan now accepts pure logical Owner/current-House getters alongside
raw pointer-field bindings. These getters resolve existing handles live, without
queries or mirrored pointer fields. Saved counts, live slots/Owner/current House,
separate kind/type queries, strict branch order, signed forwarded argument and
late point/range snapshots remain in the single scan kernel. Mode/flags borrow
the mission House records; alliance/index borrow existing visibility Houses.
These are still separate from movement Houses: **mutable diplomacy is not yet
unified**, and this checkpoint does not synchronize copies to claim aliasing.
Legacy arrival sight wrappers retain their exact-zero-argument restriction.

## Evidence

The exact supplied executable remains4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08/supplied1.006/reported no-CD/unverified pristine are distinct.
`tools/verify_boot_camp_sight.py` fingerprints it before pinning stock tables:
Infantry7A3540 and Building79CBBC, slots2C/80/84/418/41C. Complete inspected
kind/getter roots select15/6, the common type thunk and respective type fields
5A8/418. Both stock sight directions reach6D5C30/6D5E90. This is inspected
association evidence, not original scenario construction or whole-chain execution.
Receipt: `private/boot-camp-20261018/mixed-sight-vtables-a1.json`.

Changing the live-Owner binding produced1,238 fresh original scan sequences:
632 removals/606 additions, with actual3,781 local-House/1,185 alliance calls.
All prior commands, labels and original projections are retained exactly. The
fresh runner exercises getters for both actor Owner and current House, including
existing diagnostic callback mutations. Canonical original-only expectations:
`private/boot-camp-20261018/mixed-sight-fresh-a1/expected.json`, SHA256
`dec657e8b17164412ca91692c475f6c3115c54e103feb5a15ecb6efb72e78322`.
Fresh originals took0.639s; native comparison0.043s. The supplied sight/image/
post-sight callbacks in that proof retain their prior scope; production composition
is separately checked natively, not relabeled as a new original whole chain.

Normal/sanitizer owner checks cover actual coordinate/discovery/type identity,
three local sight/post-sight dispatches, Building skip/removal, forced-current
addition, image refusal, null/foreign registry slots, warm source isolation and
continuation after source destruction. Full snapshots include all new sight/type/
registry/rule/discovery owners. Existing discarded arrival/message/renderer tests
also pass. Diagnostic Owner/byte/type inputs are not gameplay observations.

Five focused CTests pass in each build. Thirteen focused Python tests pass. The
first invocation also named nonexistent `test_post_sight_refresh` and failed at
import; the corrected invocation and failed log both remain private. Fifteen
guarded normal/sanitizer/uncached replays pass across House map scans, Techno sight,
removal, reveal-area and post-sight. Existing expectations remain identity-checked;
no unchanged originals or whole inventory/closed finalizers were rerun.
The rebuilt application passes actual106-tick SDL walking acceptance in
`private/boot-camp-20261018/mixed-sight-sdl-a2/report.json`; objectives and visible
objective text remain disabled. This does not prove original whole-frame fidelity.

Exact commands, costs and source/runner/report hashes belong in
`private/boot-camp-20261018/mixed-sight-receipt-a1.json` and
`mixed-sight-validation-{normal,sanitize,uncached}-a1.json` (corrected normal replay
and Python invocation in `mixed-sight-validation-normal-a2.json`). Final owner
snapshot-strengthening checks have separate timings. Initial build, SDL, repair
and total task-wall costs were not measured. No caching was added. Local checks
are not independent acceptance. No public/YR/recomp code, new dependency, runtime
executable reads, workers, Windows actions or system changes were added.

## Reproduce and continue

```sh
./build.command
build/native/boot-camp-walk-check private/official-1006-probe
build/sanitize/boot-camp-walk-check private/official-1006-probe
./run.command --boot-camp-walk
```

The scan is exercised by the owner check, not an ordinary SDL control. Research
replay with fresh private destinations:

```sh
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/NEW-MIXED-SIGHT.audit.json \
  tests/compare_house_map_refresh.py --exe private/official-1006-probe/game.exe \
  --native build/native/house-map-refresh-vectors \
  --expectations private/boot-camp-20261018/mixed-sight-fresh-a1/expected.json \
  --report private/NEW-MIXED-SIGHT.json
```

Use the sanitizer runner or put `--uncached` before the driver as appropriate.
Fresh originals require a new `--output` directory instead of expectations/report
and authorized research-only JIT. `./test.command` remains the broad test entry.

Next unify shared House index/mask/flags across movement, discovery and visibility;
bind actual threat-grid/map/redraw and entered MakeAlly notifications. Recover
required type/image initialization/effects, then adopt action37's two calls.
Team/audio/live sight scheduling/UI and ordinary SDL Objective1 acceptance remain
open; no runtime gate was removed here.
