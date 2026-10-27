# Actual GI ability and queued mission during recruitment

The discarded actual-GI House transfer now completes its stock503C00 resume
path, including actual promotion/ability16, TypeB00 and the existing QueueMission
on the GI's mission record. Stock Return12 queues Guard5; raw Guard5 still
returns without that queue. Both reach the next existing radar-removal guard.
This closes the ability16 dependency preceding Script20's transfer of the four
GIs during Day1's first objective. No partial transfer is adopted and no live
Script20, Team, arrival, sight or SDL objective scheduling is enabled.

## Algorithm and owners

`TechnoAbility.hpp` reconstructs complete6D7910 with the complete7133A0 veteran
and713420 elite predicates. Veteran is1<=value<2; elite is value>=2. Ordered
comparisons reject quiet NaN. If both predicates fail, Type is never queried.
Otherwise the original virtual80 ->6C12C0 -> virtual84 ->506950 selects the Type.
That identity stays saved across another veteran query and the later elite
query. A true veteran byte at26C+index succeeds; elite inherits that byte or its
27E+index byte. Raw nonzero bytes return1, not their original value. Original
32-bit offset arithmetic wraps; the borrowed owner refuses addresses outside
its supported fields. There is no unrelated abilities system or startup model.

The diagnostic observer follows the original predicate/query/read boundaries.
It can mutate live veterancy, actor Type or selected Type bytes. After the Type
query, changing the actor's Type does not change the saved Type used by that
invocation. Repeated predicates are not replaced with one cached rank. Caller
ability arguments are immutable in this proof; no cross-thread or arbitrary
caller-stack mutation behavior is claimed.

Actual Boot Camp uses the GI's existing veterancy118 and Type owner. Its persistent
27C/28E fields are supplied Rules-to-Type initialization from GUARD_AREA tokens.
The exact executable's18-name table independently identifies index16 as
GUARD_AREA. The6DD241..6DD255 INI slice identifies TypeB00's DefaultToGuardArea
key. That slice and key association are inspected, not complete original Type
construction/INI recovery. The ordinary default0 and authored INI/token parser
remain supplied startup. Existing TypeC11/C14 fields are borrowed directly;
House194 and the other nonstock resume paths remain guarded.

The production resume uses its existing queueUnitDiscoveryMission implementation
on the actual mission owner. The new proof independently executes original
594CB0 with second argument0 under the complete503C00 parent and compares ordered
A0 then A4 stores. Guard/Area Guard/Patrol/Wait/Selling retain the parent/queue bypasses. Other
QueueMission branches retain their separate [discovery proof](UNIT_DISCOVERY_1006.md);
this matrix does not regenerate those originals. No Commence execution or mission scheduling is
implied by writing a queued mission.

## Verification boundaries

All addresses use the supplied4,485,392-byte base executable, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. No public authored code, dependency,
Windows action or new runtime executable read was added.

3,320 fresh original sequences execute complete ability/promotion/Type/queue
children either directly or under complete503C00 and the bounded actual-Walk
Foot composition. They cover threshold neighbors, signed zero/subnormal/infinity/
quiet-NaN veterancy, raw veteran/elite bytes, inherited elite abilities, selected
indices0/5/16/17, all previously supported raw mission choices, real queued-field
stores, early returns/reentry and three mutation kinds at eight query positions.
Exact instruction spans, immutable code/constants/input fields, private arena,
caller stack/registers and final owners are guarded. Actual QueryInterface,
reference lifetime and zero-percentage code remains joined from the prior proof.

Atomic APIs, initial actor/type/House records, mission-control bytes, House-control
results, unrelated named children and diagnostic mutations remain supplied in
this fixture. It does not execute complete House transfer or the original Type
constructor/parser. Floating-point exception-status/signaling-NaN behavior is not
proved. Prior speed/sight and separate mission-control evidence retain their
own scopes; new standalone offset tests do not broaden their runtime bindings.

Actual-world checks separately retain real Team/Tag links and source isolation.
Stock Return queues5 before radar refusal. On discarded clones, veteran ability
or DefaultToGuardArea produces5 for a real Team member or11 without a Team.
These tests change existing owned fields, never clear a Team or synthesize one.
Warm cloning copies the same Type fields; no new actor/type mirror is introduced.
These are native integration checks, not original full-transfer acceptance.

Canonical originals: `private/resume-ability-20261020/fresh-a1/expected.json`,
SHA256 `d24744096f43913ca6ae44db58d29d4322058b8f400b392737fa87eca41c8066`.
The comparator explicitly separates original expectations from current native
identities, selects reuse and records actual hits/misses. It declares the actual
dependency closure; unrelated source changes do not freeze or invalidate a run.
Current native and native guards always execute; no native verdict is cached.

```sh
./build.command
./run.command --boot-camp-walk
./test.command
PYTHONPATH=tools:tests PYTHONHASHSEED=0 build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/resume-ability-next.audit.json \
  tests/compare_infantry_resume_ability.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/infantry-resume-ability-vectors \
  --expectations private/resume-ability-20261020/fresh-a1/expected.json \
  --report private/resume-ability-next.json
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_infantry_resume_ability
build/native/boot-camp-walk-check private/official-1006-probe
```

Use fresh audit/report paths and the sanitizer runner for sanitizer reuse.
Generate new originals only for changed original dependencies/inputs/environment,
using a new `--output` folder and permitted research JIT access. Current command
logs, costs and limitations are in HANDOFF and the private validation driver.
Only Apple Silicon macOS is tested; sanitizer SDL app is not built. Existing
startup/route/presentation/15Hz scheduling remain supplied boundaries. There is
no new ordinary tutorial transition or whole-frame/game claim. Local verification
is not independent acceptance. Next bind existing actual radar424/420 owners and
the transfer wrapper before Script20 House lookup/scheduling and first-objective
SDL acceptance; never leave marker buckets borrowing destroyed cloned actors.
