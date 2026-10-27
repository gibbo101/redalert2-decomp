# Actual Walk interface during GI recruitment

The discarded actual-GI House transfer now completes its ordinary Foot resume,
including the actual nonnull Walk interface query/predicate, positive-zero
percentage update and delayed local Release. Empty destination refill also
completes. The next entered boundary is the mission-control lookup in503C00;
a raw Guard5 mission bypasses that lookup and reaches the separate radar-removal
guard. No partial clone is adopted. Live Script20/Team/arrival/sight/SDL objective
scheduling remains off. This closes the stock Walk query guard in
[INFANTRY_MISSION_RESUME_1006.md](INFANTRY_MISSION_RESUME_1006.md), not the whole transfer.

## Recovered behavior

`WalkMissionResume.hpp` binds the same Walk and existing global/instance reference
words already used by Foot destinations. The exact IPiggyback query454C70 ->
71FE90/71FAB0/53D2B0 returns the logical Walk+18 interface, increments the global
word before the instance counter, and keeps the local alive across later Foot
effects. The Foot kernel releases it after percentage4C2DF0;71FEE0/71FDF0/53D270
again modify global before instance. There is no temporary locomotor/actor copy.
The retained ordinary profile requires a positive instance count and refuses
deleting Release. Original atomic API calls are supplied test services; this
SDL-free single-thread core preserves their arithmetic and ordering.

Complete71FBA0 first queries Walk IsMoving71DEA0, which returns raw moving34.
Only when its low byte is zero does the predicate read pointer38; a nonnull
pointer then requires **the existing inProcessing35 byte** to be zero for true.
The IPiggyback pointer is Walk+18, so its relative+1D is Walk+35, not+45. The
native getter borrows this existing byte, including its actual Process writer.
Pointer38 has supplied null startup, with no recovered constructor/writer or
retained-locomotor ownership. Positive predicate/unstacking still refuses. World
cloning refuses any nonnull38 until those owners can be retained/remapped safely.
Predicate tests can inspect nonnull logical identity without dereferencing it.

Complete4C2DF0's positive-zero argument path writes percentage468 low dword then
46C high dword. The new helper preserves both stores rather than substituting a
new arithmetic/clamping model. It supports that exact zero argument only; it
makes no general setter, FP-state or whole-program equivalence claim. A diagnostic
mutation between the words verifies late state, and reference mutation during
percentage verifies that Release occurs afterward and rereads live counters.

4C8B00's complete early-return profiles now use actual target494 and persistent
count4AC: nonnull target returns immediately; otherwise only count==0 returns.
Negative count is not treated as empty. Nonzero backing/shift/reappend effects
remain guarded. Count4AC startup is explicitly supplied on the actual Foot owner.
No destination, Team, tag, locomotor or processing byte is cleared to force success.

The Foot kernel shares its one implementation across the earlier supplied
E_NOINTERFACE/null-local fixture and this actual-Walk composition. Named query,
predicate and Release services preserve the local lifetime. Native unsupported
children release the acquired local before propagating refusal; that cleanup is
native transaction safety, not a claim about original exception behavior.
Reentry with nonzero59D still returns before acquiring any interface. Ordinary
577, pending488, entered animation418, retained1B0 and special29/controller408
boundaries retain their previous guards. Missing mission-control data has an
explicit refusal; no zero-filled replacement table is supplied.

## Verification and provenance

Addresses require the supplied4,485,392-byte base executable, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD and unverified pristine
authenticity remain separate. The new verifier pins24 routine ranges, exact
Walk/E1 vtable associations, IID identity and immutable tables. No original
instruction is patched and no new runtime executable read is added.

4,356 sequences compare actual unchanged query/predicate/reference/percentage
code beneath complete503C00 and bounded4C6F10, plus direct complete predicate
calls. They cover all moving-byte values, raw processing flags, retained-pointer
truth, instance-count bounds, wrapped global counts, early/reentry paths and
originally tested mission choices. Direct positive-predicate results do not prove
successful Foot unstacking. Supplied atomic APIs, startup, mission-control,
ability/queue and unrelated named children remain explicit. The new empty-refill
proof uses actual4C8B00; the earlier fixture's supplied refill remains separate.
Original code/inputs/arena, ordered writes/queries, final fields and caller ABI
are checked. The actual-world transfer test additionally checks percentage zero,
restored existing reference counts, actual59D, retained Team/Tag and source
isolation before/after sixth-tick recruitment, warm clone/source destruction and
nonnull38 clone refusal. Actual-world checks are native ownership evidence.

Fresh canonical origin: `private/walk-resume-20261020/fresh-a3/expected.json`,
SHA256 `8df064f129428114c311a2eba3cf880dc2d3c2d7b00020ddc629c180687034d3`.
Earlier1,930 absent-interface expectations are unchanged. Originals and their
receipts remain immutable and separate from current-native validation. Every
native/sanitizer comparison explicitly selects supported replay and reports hits/
misses. No native pass/fail is cached. Failed attempts retain their actual scope.

```sh
./build.command
./run.command --boot-camp-walk
./test.command
PYTHONPATH=tools:tests PYTHONHASHSEED=0 build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/walk-resume-next.audit.json \
  tests/compare_walk_mission_resume.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/walk-mission-resume-vectors \
  --expectations private/walk-resume-20261020/fresh-a3/expected.json \
  --report private/walk-resume-next.json
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest \
  test_walk_mission_resume test_infantry_mission_resume
build/native/boot-camp-walk-check private/official-1006-probe
```

Use a fresh audit/report name and `build/sanitize/walk-mission-resume-vectors`
for sanitizer replay. Fresh generation uses `--output` with a new private folder
instead of expectations/report; Unicorn requires permitted host JIT on this Mac.
No unchanged original generation is required for native-only changes.
Commands/costs/results are retained in `private/walk-resume-20261020/validate.py`
and `validation-a1/`, summarized in opening HANDOFF. Only Apple Silicon macOS is
tested; sanitizer SDL app is not built. Existing SDL controls/presentation/schedule
remain supplied boundaries. This is a tutorial recruitment dependency, not a new
playable transition, whole-frame fidelity or complete game. Local verification
is not independent acceptance. Next recover/bind actual mission-control inputs,
entered remaining503C00 children, then existing radar424/420 and transfer wrapper
on the same owners before Script20 and ordinary objective scheduling.
