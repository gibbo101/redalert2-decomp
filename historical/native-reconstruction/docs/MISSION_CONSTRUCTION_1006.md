# Team Tag, Trigger and Script construction

Successor: [TEAM_ADMISSION_1006.md](TEAM_ADMISSION_1006.md) now recovers the
admission child on actual owners through an explicit read-only seam. AddMember,
recruitment selection and execution remain unjoined. This note's original child
expectations keep their constructor-only scope.

The first-objective Team now constructs its actual map-associated Tag, Trigger
and Script on the existing mission owner. This closes child construction in the
[first-transition blocker list](FIRST_DAY1_TRANSITION.md). It does not recruit
infantry, execute script commands or enable live SDL objective scheduling.

## Evidence

Exact supplied base:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. The verifier checks this before addresses.

| Complete routine | Bytes | Instructions | SHA256 |
| --- | ---: | ---: | --- |
| Tag6B3870 | 380 | 118 | `be23d6470f27c1367fd7ee5746e5d9dbad1ff74dd99a665d040dd27fcf7b7cd5` |
| Trigger6ED220 | 402 | 119 | `de97665ce824d6ac2bfa8175fade6bee1f4615c3eaead0724e26230515f4e1e9` |
| Script668730 | 148 | 40 | `775ebba3d63e81bd8b8a42b60518fe55b659881cbc95be857699259907befa49` |

291 sequences compare ordered stores, child calls, final fields and physical
registry backings. They execute381 Trigger,119 Tag,119 Script,619 base40FF10
and378 ResetTimers6ED680 entries. Tag calls actual Trigger/base/reset code;
heap allocation/resize and the uninitialized timer scratch are supplied services.
The oracle supplies the latter at ResetTimers entry ESP-8; this is not recovered
initialization. Caller stack, saved registers, code and unrelated arena bytes are
audited. No original instruction executes in the application.

Coverage includes null Types, empty/two-Trigger lists, reversed output links,
raw permission bytes, difficulty outside0..2, independent registry growth/skip,
low-byte resize truth, late count/backing/Type/list mutations, base flag masking,
actual reset or event7 skip, and the adopted Team child arguments. Unsafe null
Trigger allocation/child results would dereference null at6B39D4; native guards
refuse that domain rather than silently omitting a link. These refusals are safety
checks, not original behavior claims.

Original-only expectations are immutable at
`private/team-children-20261019/fresh-a2/expected.json`. Prior factory382 and
Team-constructor386 answers keep their original supplied child scopes. There is
no nested-original entire action4 -> factory -> Team -> all children/member proof.
Current native composition and actual-owner checks are separate evidence.

## Readable algorithms and shared owners

`MissionConstruction.hpp` reuses the existing base initialization/registry append
kernels through typed borrowed views. Trigger construction preserves ordered
field initialization and three registry appends, then calls recovered ResetTimers
on its actual fields. Enabled9F and difficulty permission9C..9E use raw-byte truth;
out-of-range difficulty bypasses that permission check. Tag construction keeps its
saved input Type and reads the live linked-list successor after each Trigger
constructor, prepending each result. Script construction registers a real record
with cursor-1; it executes no script command.

The mission owner reads Tag07CABA4C, Trigger07CAA20C and Script07B0C37C from the
supplied map associations. Friendly Fire event7/action2 remains unexecuted and its
unsupported action callback refuses. Four physical registries share the same
count/backing owners as Objective1 cleanup: primaryA40AA0, sharedAC0CB0/AC0D48
and TagABFE48. Tag/Trigger construction uses their exact append order. Script
owns839900 separately. Fixed capacity16, typed host heap, Type/permission parsing,
House/startup fields and zero timer scratch are explicit native adapters.

The Trigger-control consumer now projects each slot from the actual live primary
registry and borrows its count. The old five-record mirror would omit the newly
constructed Friendly Trigger and retain removed records; it is gone. Tests verify
six live controls before Objective1 cleanup and five afterward, including the
Friendly Trigger, plus independent pending/cleaned clones after source destruction.
The four registry counts are6/8/7/2 after construction and initial Tag expiration,
and5/7/6/1 after original Objective1 cleanup. Children remain retained; general
Team/Script/child destruction and populated member cleanup are not claimed.

## Commands and reuse

```sh
./build.command
./run.command --boot-camp-walk
./test.command

PYTHONHASHSEED=0 PYTHONDONTWRITEBYTECODE=1 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/NEW-mission-construction.audit.json \
  tests/compare_mission_construction.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/mission-construction-vectors \
  --expectations private/team-children-20261019/fresh-a2/expected.json \
  --report private/NEW-mission-construction.json
```

Sanitizer uses `build/sanitize/mission-construction-vectors`. A changed original
oracle/input/environment requires a fresh `--output private/NEW-origin` instead
of expectations/report and host Unicorn JIT access. Native-only changes reuse
original answers and always execute current native. Related replays are recorded
with exact commands in `private/team-children-20261019/validation/*-costs.json`.
Their expectation sources are Team-construction fresh-a4, factory fresh-a1 and
Trigger-control `private/boot-camp-20261018/trigger-control-fresh-a2/expected.json`.

## Validation and costs

230 native/229 ASan/UBSan CTests,12 focused Python guards, both actual-map owner
checks and256-tick desktop SDL acceptance pass. Each final build reuses291 new,
386 Team,382 factory and900 Trigger-control answers:1,959 hits/zero misses,
always current native. The SDL report retains right-frame6/left-frame2, ordinary
selection/move/Stop/repeated orders/pause/refusal checks and objectives disabled.
This smoke does not prove animation or original whole-frame fidelity.

Final original generation.394s; repair builds46.728/26.300s; native tests4.670s,
sanitizer18.942s; SDL5.615s. Initial builds50.673/48.122s, initial owner checks
8.529/81.740s, suites7.352/22.861s, Python.716s and SDL5.769s. Repair comparison
commands including wrappers cost.571/.480s(new),.327/.444s(Team),.348/.418s(factory)
and.422/.445s(control), normal/sanitizer respectively. Concurrent costs are
nonadditive. Final owner checks cost6.290/80.770s; exact commands are in
`validation/owners-repair-costs.json`.
Early focused/configure/integration builds, manual inspection/repair and total
wall time were not measured. Both fresh-a1/a2 origins passed and retain separate
scopes; a2 includes corrected dependency accounting/adopted null Tag link.
The live-registry repair reran all affected current-native checks without new
original answers. No final validation failed. Logs/audits/source/runner hashes:
`private/team-children-20261019/` and `private/team-children-receipt-a1.json`.

## Next lesson dependency

Complete membership admission6B8DC0 and AddMember6B8CC0 are inspection leads on
the exact base, not verified implementations. Establish the actual recruiting
caller for the four already placed Other2 E1s, then script execution/ownership
transfer. Do not hardcode a four-unit spawn or wire AddMember without its caller.
Persistent sight/arrival, initial instructions and entered alliance/audio effects
still precede the first authentic player-driven transition. Existing native
presentation/startup adapters remain explicitly supplied; unrelated general
rendering recovery is not a prerequisite without an entered lesson dependency.
Only Apple Silicon macOS tested; local verification is not independent acceptance.
