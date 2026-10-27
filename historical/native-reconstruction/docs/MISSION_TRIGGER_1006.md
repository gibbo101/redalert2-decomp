# Boot Camp trigger caller recovery

`MissionTrigger.hpp` borrows live trigger/type/country/event/action links,
timer words and event-mask owners for complete ResetTimers, RegisterEvent and
FireActions roots. It reuses `missionEventOccurred`; no second mission simulation,
scenario initializer or application default changes. This removes a caller
dependency between discovery/selection pulses and the first Boot Camp objective.
**Tag lifetime/detachment, discovery production, scheduling and action effects
remain unjoined; no lesson transition is delivered by this change.**

## Evidence and scope

Exact supplied base:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Only Apple Silicon macOS is tested.
Pinned YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88` TriggerClass/TEventClass
declarations supplied naming leads only. YR layout/addresses are not base
evidence; no license file was found. No public/header/generated/lifted code,
extracted table, dependency or runtime executable read was incorporated.

Original-only `private/boot-camp-20261018/trigger-fresh-a1/{expected,report}.json`
contains **381 sequences /678 complete top-level original calls**. Current
normal/sanitizer/uncached-inspection `trigger-replay-*-a2.json` each have381 hits/
zero misses/zero originals. Expectations/fresh receipt precede comparison and
remain unchanged after native-only guard additions. Original/native identities
are separate; original Python closure, commands, executable, interpreter and
dependency versions stay guarded. `trigger-validation.json` records artifacts.

`verify_mission_trigger.py` fingerprints complete base6ED680..6ED73D,
6ED740..6ED821 and6ED830..6ED895; actual event6E6050, persistence6E6CF0/6E6D50,
House4ED760 and dispatch tables are independently checked. Original instructions
are unchanged. Only action dispatcher6ADAE0 is substituted: its exact thiscall
arguments/return/stack are checked. Supplied callbacks change type/House/list
links, enabled/destroyed or saved Cell words to test late reads. These diagnostic
effects are not recovered actions or gameplay observations.

Each root checks ESP, return/caller guard, callee-saved registers, instruction
ranges, immutable code/table/globals and the complete original arena. All3,504
selected original timer/mask dword stores match native logical assignment order;
this does not claim all native machine stores or all original reads. The original
enters1,178 event calls,2,022 House lookups,2,962 first/2,804 second persistence
helpers,289 timer resets and64 supplied action calls. Initial records, registry,
lists and scratch remain supplied. Local verification is not independent acceptance.

## Recovered behavior

RegisterEvent tests raw enabled/destroyed once at entry. Only the low force byte
bypasses conditions. It visits every event after a false result, skips remembered
conditions, and preserves x86 `1 << (index &31)` aliasing. An unremembered event
first resolves the live trigger type's country. Pulse events4/33 additionally
perform their own later House lookup even though its result is unused. Calls are
not deduplicated; event semantics remain those in [BOOT_CAMP.md](BOOT_CAMP.md).

With a nonzero low persistent byte, happened/remembered events call persistence
helpers. In bounded4/13/33/47,4/33 are remembered and13/47 are not. The current
event's next link is read after the child. Aggregate success, including forced/
empty lists, conditionally resets timers. Other entered conditions/persistence
helpers refuse. Cached unsupported events can skip evaluation with persistence off.

ResetTimers has no enabled/destroyed gate. Kind13 reads live frame and wrapped
low32 `value*15`, then stores start, scratch padding, remaining and cleared mask
in that order. All timer events share one timer; the last duration wins. Direct
ResetTimers reads scratch at entry ESP-8. The complete RegisterEvent fixture's
nested reset can inherit the earlier actual `&persistent` argument pointer in
that slot. This ABI association is supplied explicitly, not zero padding or a
fabricated portable pointer. Production callers must supply their padding boundary
until joined. Entered random timer51 refuses; other non-timer kinds are skipped.

FireActions tests enabled/destroyed only at entry. It reloads the trigger type's
country for each action, calls the supplied dispatcher with actual object/trigger
and the same saved packed Cell words, ORs nonzero low-byte results, and rereads
the current action's next link. A child disabling/destroying the trigger or
returning false does not stop traversal. Callback faults propagate; no rollback
is promised. Borrowed bindings make no queries; null/first matching House identity
is preserved.

## Checks and costs

Three focused CTests per build (content/event/trigger) and nine Python tests pass.
Existing925 event results replay in normal/sanitizer builds without regeneration.
Native guards cover missing services, unsupported random timer/persistence,
low-byte force, wrapped duration, empty-action query bypass and propagated faults/
retained writes. No movement/application/drawing source changed: the prior actual
SDL baseline in [BOOT_CAMP_WALK_1006.md](BOOT_CAMP_WALK_1006.md) keeps its scope.
No broad/SDL rerun is claimed for this unwired dependency.

Fresh originals0.375s; native comparison0.025s; full driver0.712s. Final normal/
sanitizer/uncached drivers0.187s/0.350s/0.536s (native0.012s/0.141s/0.010s).
Focused CTests0.04s/0.33s; Python0.027s; final two runner rebuilds2.12s together.
Costs overlap. Earlier configure/build, implementation/repair and total task-wall
costs are unavailable. A test-count floor and range ending inside a three-byte
early return were corrected before generation. No original/native comparison
failed. No cache framework or unchanged original matrix was added.

## Reproduce

```sh
./build.command
./test.command
./run.command --boot-camp-walk
# Player capability remains walking/Stop/pause, without objectives.
build/native/mission-trigger-vectors --guards
build/sanitize/mission-trigger-vectors --guards
env DEVELOPER_DIR=/Library/Developer/CommandLineTools PYTHONHASHSEED=0 \
  PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/mission-trigger-next.audit.json tests/compare_mission_trigger.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/mission-trigger-vectors \
  --expectations private/boot-camp-20261018/trigger-fresh-a1/expected.json \
  --report private/mission-trigger-next.json
# Sanitizer: substitute build/sanitize runner and new report/audit names.
# Uncached inspection: add --uncached before --audit; originals still reused.
# Fresh originals only if dependencies change: omit expectations/report and use
# --output private/mission-trigger-new-fresh in authorized Mac-host JIT context.
```

Next actual Tag6B3DF0 registration/fire, destruction/deferred-delete and owner/
Cell detachment. Objective tag043BD15C belongs to CAARMY04(71,92)/CAARMY01(69,96),
not nearby Friendly Destroyed structures. Its persistence0 path cannot skip
lifetime children. Then recover genuine discovery/building dispatch and encountered
action/scheduler effects before ordinary SDL first-objective completion. No
destination test/synthetic success/hardcoded walkthrough. No workers, Windows
actions or runtime reads; full base RA2/YR goal remains incomplete.
