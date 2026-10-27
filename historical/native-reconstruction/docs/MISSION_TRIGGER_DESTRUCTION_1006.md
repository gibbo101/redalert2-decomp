# Boot Camp Trigger destruction and complete Tag lifetime order

`MissionTriggerDestruction.hpp` recovers the complete Trigger deleting destructor
6EDBA0 and Tag pointer-expiration recipient6B4040. It joins the existing deferred
cleanup and ordinary Tag destructor on the same queue and registry owners. A native
shared-owner check now drains a destroyed Trigger followed by its Tag without
retaining or requeueing the freed Trigger. **Production mission owners, discovery,
scheduling, action effects and objective progression remain unjoined; walking and
objective status are unchanged.**

## Evidence and supplied boundaries

Exact supplied base: 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Only Apple Silicon macOS is tested. No
public/header/generated/lifted code, extracted data, dependency or application
executable read was added.

Original-only `private/boot-camp-20261018/trigger-destruction-fresh-a1/`
contains **256 sequences**:144 Tag pointer-expiration calls,112 Trigger deleting
destructor calls and16 combined deferred-cleanup calls. Those combined calls also
execute16 Tag deleting/destructor roots. The proof executes464 actual pointer
searches,128 actual base destructors,32 inherited Releases,32 inherited frees and
1,136 selected ordered stores. Generic expiration dispatch is supplied144 times;
128 generic RTTI results are supplied at the inherited cleanup boundary. Native
comparisons cover complete logical queue, Tag and registry owner state. This does
not claim native instruction widths or a complete original-read trace.

The verifier fingerprints complete6EDBA0 (287 bytes), complete6B4040 (131 bytes),
the full72-byte Trigger vtable and all inherited cleanup/Tag destruction ranges and
tables. Every top-level root retains instruction/write/ABI/stack/callee-saved
checks, immutable code/tables and whole queue/Tag/registry arenas. Initial vtables,
queue/registry associations and heap identities remain supplied.

There are four physical registries. Trigger destruction removes from `A40AA0`,
`AC0CB0` and `AC0D48`; Tag destruction removes from `AC0CB0`, `AC0D48` and
`ABFE48`. The two middle registries are shared owners. Modeling six independent
registries would miss the actual lifetime composition and is forbidden.

Complete generic kind-38 expiration beyond the recovered Tag6B4040 recipient
remains a named boundary. The current composition dispatches that recovered Tag
effect when the Trigger expires. Unrelated kind-38 recipients, initial recipient
associations, active-session Tag bookkeeping and production mission ownership
remain supplied. No discovery/action/runtime behavior is inferred from lifetime
cleanup.

Normal, sanitizer and uncached-inspection replays
`trigger-destruction-replay-{normal,sanitize,uncached}-a1.json` each reuse256
sequences with zero misses and zero original executions. The expectation SHA256 is
`fc30fdff36535f9b4bc84c064386a2dc386239538fa3414eda0f4c8b54ec3f7d`.

## Recovered behavior

- Tag6B4040 first clears Type+24 when it matches the expired identity. It then,
  independently, replaces matching FirstTrigger+28 with the expired Trigger's live
  +28 link. The `removed` argument is ignored.
- After those comparisons, a null Type sets destroyed byte+34 to1 and appends the
  Tag to the live deferred queue. Therefore a missing Type schedules the Tag even
  when the expired identity matches neither field. Stores and append effects keep
  original order.
- Trigger6EDBA0 broadcasts expiration with removal1, removes only the first matching
  Trigger from each of its three registries, destroys its base and frees only when
  the deleting word's low bit is set. Duplicates and capacity tails remain.
- Combined cleanup removes every queued Trigger duplicate before Release and
  destruction. Trigger expiration then detaches Tag.FirstTrigger. Later Tag
  destruction sees a null trigger list, so it does not append the freed Trigger.
  Cleanup consumes the live Tag entry and all four shared registries drain.
- Faults propagate after prior ordered effects. No rollback or transactional
  cleanup claim follows.

## Checks, costs and commands

Nine focused mission CTests per build and21 related Python tests pass. Native
normal and sanitizer guards cover isolated pointer expiration, deleting destruction
and the shared Trigger-then-Tag lifetime world. The existing walking SDL baseline
is retained at its prior scope; no broad/SDL rerun was needed. Local verification
is not independent acceptance, original gameplay observation or a completed
objective.

Original generation took0.086s. Normal/sanitizer/uncached replay drivers took
0.164s/0.247s/0.521s; native comparisons took0.007s/0.053s/0.007s. Other final
check costs and unavailable measurements are recorded in private
`trigger-destruction-validation.json`.

```sh
./build.command
./test.command
./run.command --boot-camp-walk
# Current player capability remains selection/walking/Stop/pause.
build/native/mission-trigger-destruction-vectors --guards
build/native/mission-tag-lifetime-world-check
build/sanitize/mission-trigger-destruction-vectors --guards
build/sanitize/mission-tag-lifetime-world-check
env DEVELOPER_DIR=/Library/Developer/CommandLineTools PYTHONHASHSEED=0 \
  PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/mission-trigger-destruction-next.audit.json \
  tests/compare_mission_trigger_destruction.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/mission-trigger-destruction-vectors \
  --expectations private/boot-camp-20261018/trigger-destruction-fresh-a1/expected.json \
  --report private/mission-trigger-destruction-next.json
# Sanitizer: substitute build/sanitize and fresh report/audit names.
# Uncached inspection control: add --uncached before --audit, retaining originals.
# Fresh only for changed original dependencies: omit expectations/report and use
# --output private/mission-trigger-destruction-new-fresh in the authorized Mac-host
# JIT context.
```

Next bind this complete lifetime chain to production mission owners. Then recover
genuine discovery/building dispatch and encountered scheduling/action effects for
objective Tag043BD15C. No workers, Windows actions or runtime executable-read
expansion. Full base RA2/YR remains incomplete.
