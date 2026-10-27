# Boot Camp deferred cleanup and ordinary Tag destruction

`MissionDeferredCleanup.hpp` recovers complete global deferred cleanup6ECF10.
`MissionTagDestruction.hpp` recovers Tag's deleting destructor6B42E0 and the
ordinary inactive-session path through complete6B39F0. Live views borrow the
existing deferred queue, Tag trigger links and three distinct registries. The
already recovered Tag44 broadcast binds at both destructor notification sites.
**Trigger destruction is still unjoined, so the Trigger-then-Tag queue produced
by RaiseEvent is not drained in the application. Discovery, scheduling, action
effects and objective progression remain pending; walking is unchanged.**

## Evidence and supplied boundaries

Exact supplied base: 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Only Apple Silicon macOS is tested. No
public/header/generated/lifted code, extracted data, dependency or application
executable read was added.

Original-only `private/boot-camp-20261018/tag-destruction-fresh-a7/{expected,report}.json`
contains **128 sequences /128 complete cleanup roots /96 complete Tag deleting
destructor and Tag destructor roots**. It also executes624 actual pointer searches,
96 actual Releases,96 base destructors,144 true and248 false inactive predicates.
The fixture supplies384 negative RTTI results,192 calls into the separately
recovered expiration root,96 frees and48 zero Releases. Native comparisons cover
1,088 selected ordered vector stores and complete logical owner state. This does
not claim native instruction widths or a complete original-read trace.

The verifier fingerprints eight complete ranges, the full72-byte Tag vtable and
the deferred vector dispatch table. Every top-level root retains instruction/
write/ABI/stack/callee-saved checks, immutable code/tables and whole queue/Tag/
registry arenas. Initial vtables, queue/registry associations and heap identities
remain supplied. The native guard binds the real recovered Tag44 broadcast on
shared owners; original destructor evidence supplies expiration calls because
that root already has its own exact proof.

The active-session6B39F0 bookkeeping after the first expiration call remains an
explicit refusal. It depends on scenario/type/trigger/House records and counters
outside this bounded lifetime step. Generic cleanup's four RTTI comparisons and
free service remain supplied; Tag receives four negative results, so Object+7D
marking is not entered. Trigger deleting destruction is not inferred from Tag or
the older Overlay proof.

Normal, sanitizer and uncached-inspection replays
`tag-destruction-replay-{normal,sanitize,uncached}-a3.json` each reuse128 sequences
with zero misses and zero original executions. Fresh-a5/a6 are valid but superseded
runner identities from guard expansion. Failed audits fresh-a2/a3 are retained:
oracle bring-up used incorrect stack cleanup for supplied release/CRT hooks and
failed before expectation publication. The corrected a7 proof is independent;
those failures are not native mismatches or accepted evidence.

## Recovered behavior

- Cleanup reads the live queue count and backing. Active entries remain in place
  and advance the index. An inactive entry is removed at **every** matching slot
  before Release; each removal stores count before ordered shifts and preserves
  unused capacity tails.
- A zero Release skips RTTI and destruction. A nonzero Release performs four RTTI
  probes in order and stops on the first positive result; that path marks Object
  byte+7D before deleting-dtor dispatch. Tag's four results are negative.
- Destruction can append new entries. Cleanup consumes the resulting live queue
  without restarting or snapshotting it. Callback faults retain earlier removals
  and effects; no rollback claim follows.
- Ordinary Tag destruction broadcasts removal first, then reads the live trigger
  list and appends every remaining node in link order. Each append keeps existing
  growth/ownership/low-byte-success semantics.
- It removes only the first matching Tag from each of three distinct registries,
  preserving duplicates and tails. Registry count stores precede shifts. A second
  expiration broadcast follows those removals, then actual base destruction and,
  when the deleting word's low bit is set, free.
- The native deleting wrapper tests only that low bit. The portable projection
  does not expose original vtable words; original execution verifies their stores
  and actual base-vtable reset separately.

## Checks, costs and commands

Seven focused CTests per build and18 Python tests pass. The native guard covers
the active-session refusal after the first shared recovered broadcast and complete
ordinary shared-broadcast/base/free order. The existing walking SDL baseline is
retained at its prior scope; no broad/SDL rerun was needed. Local verification is
not independent acceptance, original gameplay observation or a completed objective.

Final original generation took0.077s. Normal/sanitizer/uncached replay drivers
took0.142s/0.224s/0.252s; native comparisons took0.005s/0.048s/0.005s. Focused
CTest commands took0.26s/0.39s and Python0.25s. Additional build, repair and
unavailable costs are recorded in private `tag-destruction-validation.json`.

```sh
./build.command
./test.command
./run.command --boot-camp-walk
# Current player capability remains selection/walking/Stop/pause.
build/native/mission-tag-destruction-vectors --guards
build/sanitize/mission-tag-destruction-vectors --guards
env DEVELOPER_DIR=/Library/Developer/CommandLineTools PYTHONHASHSEED=0 \
  PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/mission-tag-destruction-next.audit.json \
  tests/compare_mission_tag_destruction.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/mission-tag-destruction-vectors \
  --expectations private/boot-camp-20261018/tag-destruction-fresh-a7/expected.json \
  --report private/mission-tag-destruction-next.json
# Sanitizer: substitute build/sanitize and fresh report/audit names.
# Uncached inspection control: add --uncached before --audit, retaining originals.
# Fresh only for changed original dependencies: omit expectations/report and use
# --output private/mission-tag-destruction-new-fresh in the authorized Mac-host
# JIT context.
```

Next recover actual Trigger deleting destruction and its Tag-list detachment, then
drain the Trigger-then-Tag queue produced by shared RaiseEvent without leaving or
reusing destroyed links. Bind that complete lifetime to production mission owners;
then recover genuine discovery/building dispatch and encountered scheduling/actions
for objective Tag043BD15C. No workers, Windows actions or runtime executable-read
expansion. Full base RA2/YR remains incomplete.
