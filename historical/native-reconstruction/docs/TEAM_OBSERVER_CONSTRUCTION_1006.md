# Team observer construction — supplied base

`TeamObserverConstruction.cpp` now reconstructs complete observer41C5C0,
AbstractType410580, existing Abstract40FF10, primary-Team setter41DF90 and
registry initializer4D2D90.473 original/native sequences match ordered stores and
final fields, including calls to the existing complete weight callbacks on the
newly constructed records. These are explicit construction diagnostics. Actual
scenario observer loading/association and Team teardown remain unjoined.

## Ownership and order

One owned `TeamObserverType` retains its base fields, identifier/name buffers,
weight/minimum/maximum doubles, counters and distinct primary/secondary Team
Type identities. Its `weight()` view borrows those same doubles/counters. It
creates no duplicate callback state and does not represent the observer as a Tag.

The existing40FF10 kernel initializes Abstract fields and interface projections.
410580 then clears the first identifier byte,3D and first display-name byte,
projects AbstractType interfaces and copies a bounded24-byte identifier plus NUL.
Its48-byte display-name copy reads the just-stored identifier, with zero padding
and a final NUL. Empty-name pointer60 is separate from those buffers. Null input
uses an explicit formatted-name CRT service; no native pointer is truncated into
an original32-bit generated name. Aliased source buffers are read after preceding
stores, not eagerly snapshotted before construction.

Base registration inA40928 precedes observer field initialization. The derived
constructor writes98/A8=-1, stores the three double low words before their high
words (all become1), initializes flags/counters/pointers, projects derived
interfaces, clears eight condition words, then appends toA3D260. Both registries
use the existing shared registration kernel: low-byte resize truth, wrapped
capacity addition, late count/backing, count-before-slot store and untouched tails.
An unsuccessful base append does not abort derived initialization/registration.
Neither registry is an alias or a copy of the other.

41DF90 writes only primary Team TypeDC. Secondary TypeE0 and objectD8 remain
distinct. The static initializer resetsA3D260 backing/capacity, writes valid12=1,
allocated13=0, projects its interface, sets increment20=10 and count16=0, then
registers the exit service. It does not destroy/free an old backing or prove that
later scenario startup leaves the registry empty. Missing services/bounds refuse
with prior stores retained, never synthetic rollback.

Construction alone does not load a definition, establish scenario membership,
parse Rules, select an AI team, run a Team destructor or schedule gameplay.
Native diagnostics supply physical registry capacity/backing, formatting/heap
services and fields. Actual original CRT formatting/copy, vector resizing and
atexit effects are not recovered by this checkpoint. The C++ bounded copy
implements their supplied fixture contract; actual original parent copies remain
executed in the guest. No public/generated/lifted implementation or runtime
executable read was added.

## Original evidence

Exact supplied binary:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD and unverified pristine
provenance remain separate. The verifier fingerprints before addresses:

| Complete span | Bytes / instructions | SHA256 |
| --- | --- | --- |
|41C5C0|296 /70|`eb18c4b15164962c66f79b4746bb01d40f7cff22d77539e9ebda6a155c7f09fa`|
|410580|340 /110|`a5bd51911eca1705a70dceb80647a7254c3d26a314a337872ae49a9f843f91fc`|
|40FF10|71 /16|`63479e6cf1aa1e0855b7e0d25e4349a259d9c93a8cc7043431c4855f05e9b169`|
|41DF90|13 /3|`4be51d3074333d49f06e4f6314b3f3a87833b5e6d58ecbacc24414f5a9ccb86f`|
|4D2D90|61 /12|`70b4e11c5f635214bc454f9d6f885090e7180e65d2ab1b7e6044aa11188bbe2a`|

The oracle executes those unchanged complete spans and existing41DFB0/41E070.
CRT sprintf/strncpy, vector resize and atexit are supplied named services, with
calling convention/arguments checked; no instruction patches. Original code
performs both constructor registry appends, field stores and rep copies. Selected
ordered stores, unrelated arena/registry bytes, code/constants/vtable inputs,
caller stack/return and callee-saved registers are checked. Callback FP controls
remain supplied nearest/toward-zero in the existing finite53-bit profile; actual
caller FP startup is still unjoined.

Coverage includes null/empty/1/23/24/49-byte names, ID/display-source aliasing,
raw retained base flag bits, both registries' success/refusal/growth, full return
words0/1/256/257/-1, wrapped growth, live source/backing/count mutation, copied-ID
mutation before the display copy, null/two primary Types, success/failure callback
composition and static initialization followed by construction.25 Python tests
include new matrix/domain, row and provenance/scope tests. Current native source
changes are separate from immutable original expectation provenance.

Canonical original answers:
`private/team-observer-construction-20261020/fresh-a1/expected.json`, SHA256
`ba150d4a1f009b9c5b7180859934d876a5f19b9d1645e2212a846dbaceda1d33`.
Before fresh generation, the native static-initializer fixture was corrected to
allocate a zero-filled backing when its old pointer was null, rather than copy
its abandoned initial array. Initial builds/that fixture correction were not
separately timed. Fresh-a1 passed; no failed original attempt or relabeled receipt.
A later native-only fixture-comment correction used those same original answers.

## Reproduce and cost

```sh
./build.command
./run.command --boot-camp-walk
./test.command
DEVELOPER_DIR=${DEVELOPER_DIR:-/Library/Developer/CommandLineTools} \
 build/tools-env/bin/cmake --build build/native \
 --target team-observer-construction-vectors -j 6
PYTHONPATH=tools:tests PYTHONHASHSEED=0 build/tools-env/bin/python -B \
 tools/run_evidence.py --audit private/NEW-observer-construction.audit.json \
 tests/compare_team_observer_construction.py \
 --exe private/official-1006-probe/game.exe \
 --native build/native/team-observer-construction-vectors \
 --expectations private/team-observer-construction-20261020/fresh-a1/expected.json \
 --report private/NEW-observer-construction.json
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest \
 test_team_observer_construction test_team_observer_weight test_team_destruction
```

Sanitizer replay uses build/sanitize/team-observer-construction-vectors and fresh
report/audit paths. Normal/sanitizer each pass5 focused CTests and explicitly
replay2,170 original sequences:473 observer construction,386 Team construction,
580 observer weight,266 destruction and465 unlink. All hits/zero misses/current
native; no existing originals were regenerated or native pass/fail cached.
25 Python tests pass. This is an unwired internal dependency: broad actual-world
and SDL acceptance were not rerun, and visible controls/drawing retain their
prior scope. Only Apple Silicon macOS is tested. Local verification is not
independent acceptance or a complete teardown/game-fidelity claim.

Fresh generation.477s. Final focused builds2.721/3.278s, CTests.459/.605s,
sanitizer configure21.491s, Python process.415s. Normal/sanitizer replay driver
processes.580/.682s(new construction),.391/.442s(Team construction),.286/.380s
(weights),.352/.388s(destruction),.762/.413s(unlink). Initial normal configure/
build, native edit/repair, inspection/review and total wall time were not measured
separately. Some commands overlap; durations are not additive. Commands/logs/costs:
private/team-observer-construction-20261020/validate.py,validation-a1/.
Receipt:private/team-observer-construction-receipt-a1.json.

Next recover original definition enumeration/loading and actual Team Type lookup,
then bind persistent observer/Rules owners and caller FP state before teardown.
Private41D540 enumeration and41D7E0 per-record parser inspections are leads only.
Original vtable79B780+64 points to41D7E0; section names are indirect through
79B748/79B74C. The first raw string-immediate scan found no candidates; that is
not evidence of no loader. Initial inspection started a second span in the middle
of an instruction; INI-load-inspection-a2.txt restarts at the known41D7E0 entry,
but its complete endpoint/children still require recovery. Do not treat either
inspection as execution/startup proof. Then finish entered Tag/base lifetime
children, exhausted teardown and transferred-GI movement including6BA990 before
genuine scheduling. AC0C18/Neuron startup remains open; no workers/live objectives/
partial clone adoption/runtime executable-read growth. Both games remain incomplete.
