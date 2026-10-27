# Boot Camp Tag event dispatch and retirement

`MissionTag.hpp` joins complete Tag RaiseEvent to the existing borrowed Trigger
registration/timer/action traversal, actual Trigger Destroy, Object tag assignment,
null Cell tag clearing and a shared deferred-delete queue. Views borrow live
Tag/type/list/trigger/reference/count/backing owners; there is no second mission
simulation or runtime default change. This removes another caller dependency for
the first objective's discovery tag. **Expiration broadcasting, delete-queue drain,
genuine discovery, scheduling and action effects remain unjoined; the tutorial
does not advance yet.** Do not bind a no-op notification in the application.

## Exact evidence and boundaries

Supplied base:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Only Apple Silicon macOS is tested.
Pinned YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88` TagClass/TagTypeClass
names supplied leads only; YR layout/addresses are not base evidence. No license
file was found; no public/header/generated/lifted code, extracted table, new
dependency or application runtime executable read was incorporated.

Original-only `private/boot-camp-20261018/tag-fresh-a1/{expected,report}.json`
contains **1,010 sequences /1,277 complete top-level original roots**. Current
normal/sanitizer/uncached-inspection `tag-replay-*-a2.json` each retain1,010 hits/
zero misses/zero originals. Complete child calls include2,016 RegisterEvent,
1,587 FireActions,1,434 Trigger Destroy,577 Object assignments,653 Cell clears,
635 actual word lookups and156 timer resets. All8,761 selected ordered stores
match native logical assignments, including189 fallback-point stores. Native
machine write widths/all original reads are not claimed.

`verify_mission_tag.py` hash-pins full6B3DF0..6B3F81,6ED990..6ED9EB,
5D4430..5D4460,47A460..47A4D9 and548070..5480A7, the existing Trigger/event/
persistence/House roots and vector growth dispatch. The original executes
unchanged instructions. Each root retains instruction/write/ABI/stack/callee-
saved checks, immutable code/tables/globals/map slots and complete owner arenas.

The action dispatcher6ADAE0, allocation40CD40 and expiration broadcast6ECB90
are named supplied services with checked ABI/arguments. There are1,587 action,
261 allocation and716 expiration calls. Diagnostic effects mutate policy/list/
references/flags, relocate vector backing or reset count to establish late reads;
they are not recovered action/heap/notification behavior. Map slots/Cell associations,
startup and caller scratch remain supplied. The fixture actually executes word
lookup/fallback writes, but does not join a production map/mission owner.

The first native comparison failed at persistence1/one instance: a mistaken
direct-detachment assumption was corrected to the original branch. Generation
had already saved original-only expectations/receipt. All later repairs and
additional native guards reused those originals; no origin was relabeled or
regenerated. Failed `tag-fresh-a1.audit.json` and its native stdout remain.
`tag-validation.json` records successful current identities and the failure scope.

## Behavior that must survive integration

- A nonzero executing byte returns false without writes. Otherwise the first
  trigger is saved, executing becomes1, and the current trigger's next link is
  read after registration/actions/destruction. Do not snapshot the whole list.
- The persistent argument is true only for exact policy2. Original SETE DL
  retains the policy's upper24 bits in the pushed word. Only the low force/
  persistent bytes gate the Trigger child; raw upper bits remain observable.
  The Tag type/policy is read again after successful registration and for the
  next trigger; a callback can change later decisions.
- Policy0 fires actions, destroys the trigger and requests direct detachment.
  Policy1 with exactly one instance fires/destroys but **skips direct detachment**;
  with any other count it requests detachment without firing/destruction.
  Policy2 fires without destruction/detachment. Other policies do neither.
  A fired branch returns true regardless of the FireActions result.
- Executing clears before detachment/notification. Matching nonnull Object tag
  assignment decrements its old counter and clears its pointer. An unrelated
  owner is preserved. A non-sentinel Cell pair always looks up/clears that Cell's
  current Tag, even when unrelated to this Tag. Null Cell assignment stores null
  even if already empty. Signed counters wrap as32-bit words. General nonnull
  Cell tag installation remains outside this entry.
- Full Object assignment supports null, replacement and same-tag remove/reinsert:
  old decrement/clear precede incoming pointer/store/increment. Do not collapse
  same-tag writes or alias unrelated references.
- Trigger Destroy stores byte2C=1 before enqueue attempts, including repeated
  calls. It shares the deferred vector with the Tag. Queue admission uses signed
  count/capacity, ownership byte, positive growth, wrapped requested capacity and
  low-byte allocation success. After growth it reloads count/backing; count store
  precedes slot store. Failed growth does not undo destroyed/reference writes,
  and duplicates are retained. Invalid host backing refuses explicitly rather
  than emulating an original invalid memory access.
- If any trigger was destroyed, RaiseEvent calls expiration with flag1, then
  attempts to append the Tag. It does **not** set Tag byte34 itself; this is not
  the separate Tag Destroy6B3CC0 root. Later broadcast/drain must use the actual
  owning registry and references. Callback faults propagate, with no rollback.

The Trigger destroyed view is now mutable so the same actual field serves its
entry check and Destroy; rebuilt normal/sanitizer replays preserve all381 earlier
Trigger sequences /678 roots without regenerating them. The event kernel and
walking/runtime sources are unchanged.

## Verification and cost

Four focused CTests per build and12 Python tests pass. New native guards cover
executing/no-query bypass, missing allocation/notification services, owner/object
identity mismatch, same-tag/wrapped counts and synchronous notification reentry
after executing clears. The reentry is native composition coverage, not a new
complete-original nested-callback proof. Existing current-runner381 Trigger
replays pass in both builds. No broad/SDL rerun for this internal dependency;
the prior walking SDL baseline retains its separate scope. Local verification is
not independent acceptance, original gameplay observation or lesson completion.

Original generation2.248s. Final normal/sanitizer/uncached drivers0.217s/0.376s/
0.759s; native comparison0.038s/0.147s/0.035s. Normal/sanitizer focused CTests
0.07s/0.22s; Python0.070s. Costs overlap. Configure/build, implementation/repair,
failed-comparison and total task-wall costs are not separately available. The
native-only repair/replay command took0.949s including a rebuild. An incidental
parallel metadata read ran before its report was ready; it affected no proof.
No cache framework or unchanged original matrix was added.

## Commands and next join

```sh
./build.command
./test.command
./run.command --boot-camp-walk
# Walking/Stop/pause remain the player capability; objectives are pending.
build/native/mission-tag-vectors --guards
build/sanitize/mission-tag-vectors --guards
env DEVELOPER_DIR=/Library/Developer/CommandLineTools PYTHONHASHSEED=0 \
  PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/mission-tag-next.audit.json tests/compare_mission_tag.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/mission-tag-vectors \
  --expectations private/boot-camp-20261018/tag-fresh-a1/expected.json \
  --report private/mission-tag-next.json
# Sanitizer: substitute build/sanitize and new report/audit names.
# Uncached inspection: add --uncached before --audit; original answers reused.
# Fresh only when original dependencies change: omit expectations/report, use
# --output private/mission-tag-new-fresh in the authorized Mac-host JIT context.
```

Next replace the named expiration broadcast/drain boundary and bind actual mission
Tag/Trigger/owner/Cell records, then genuine discovery/building dispatch and
encountered scheduler/actions. Objective tag043BD15C is on drill-sergeant
CAARMY04(71,92)/CAARMY01(69,96); GI selection uses tag0A71735C/event33. No
destination test or synthetic success can replace discovery. No workers, new
Windows action or runtime read; full base RA2/YR remains incomplete.

Private inspections provide the next lead, not proof: Tag virtual6B42D0 returns
kind44. Generic expiration6ECB90 can clear global833680/833684 (the latter calls
498F10); the non-AbstractType kind44 switch traverses AC0C5C/countAC0C68, then
map559D80(tag,1) and logic53E110(tag,1). Those children/recipient dispatch and
actual deferred drain6ECF10/Tag destructor must be joined before claiming native
lifetime completion. The current fixture supplies the whole broadcast explicitly.
