# Team observer definition loading — supplied base

The per-record AITriggerTypes parser41D7E0 now has372 original/native
sequences, including actual Team Type lookup6BF260, TaskForce tech scan6B7140,
identifier trim6EEF10, signed64 FTOL77F110 and locale-zero comparison781F20.
`src/assets/TeamObserverInputs.cpp` handles definition text; SDL-free
`src/sim/TeamObserverTypes.hpp` handles the two Type queries. Records use the
existing `TeamObserverType` fields, without duplicate weight/counter state.
This is an explicit loading diagnostic, not scenario startup or live Team teardown.

## Recovered behavior and boundaries

The parser requests one decoded INI value by observer identifier and uses the
existing bounded512-byte copy/trim kernel. Commas alone delimit tokens; empty
fields are skipped. Required-field exhaustion returns false after any preceding
stores. Display names retain48 payload bytes. Identifier fields copy24 bytes,
then overwrite byte23 with NUL before the recovered trim: only23 payload bytes
survive. The trim retains its original shifted-buffer guard; conventional trim
would change behavior for some leading/trailing whitespace inputs.

Primary TeamDC, secondary TeamE0 and objectD8 are distinct. Team lookup compares
the identifier then description with live count/backing and returns the current
slot. Object lookup preserves Infantry/Unit/Aircraft/Building precedence. Owner
modes distinguish `<all>`, `<none>` and country-index results. Required tech text
and one later field are discarded. Optional omissions retain existing fields;
secondary TeamE0 is cleared only when its token exists. Flags use full32-bit
integer truth. Ordered stores and repeated late TaskForce queries are preserved.

The tech scan saves count/session, starts at0 and reads each Type55C. A level-1
with nonzero saved session resets the accumulator to11 even after a larger
preceding level: `[20,-1,5]` yields11 in that session. The parser saves signedB0
before a query and may query the live Team/TaskForce again before its B0 store.
Do not replace this with a maximum over a snapshot.

Weight/min/max parse doubles, call signed64 truncation, retain its low32 bits,
then zero-extend those bits into a double. Thus-1.2 becomes4294967295. Invalid or
out-of-range signed64 conversion produces indefinite with low word0. Native
conversion checks bounds before its cast. Actual FTOL executes in the oracle;
the caller's complete FP startup remains unjoined.

Condition bytes preserve unwritten tails. The original scanner reads mutable
strtok backing: trailing whitespace may advance to the token NUL, consume a byte
from the following field and continue into later raw fields. The native parser
retains this within its bounded scratch buffer; a read outside that buffer
refuses. The33rd pair is scanned/space-queried before being discarded, with no
conversion or store. Do not sanitize these behaviors into a new file format.

Decoded INI/string acquisition, strtok, strncpy, atoi/atof/isspace/pair-strtol,
country and other object lookup services remain supplied in the original proof.
Locale-zero comparison, Team lookup, TaskForce scan, trim and FTOL execute their
unchanged guest code. Native tests supply numeric/ctype services through host
fixtures; no CRT equivalence, nonzero locale or whole INI startup claim follows.
Registry ordering/membership, Type/TaskForce construction, Rules and actual FP
association remain supplied/unjoined. No public/generated/lifted code, dependency
or runtime executable read was added.

## Original evidence

The exact executable is4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Fingerprinting precedes address use.

| Complete span | Bytes / instructions | SHA256 |
| --- | --- | --- |
|41D7E0|1397 /412|`2bd2d2463852727af7cd9e53fdf57713f75850e2c089a0162e37af991c257b9d`|
|6BF260|97 /40|`78bef9e8f8e3a73e875a74601804591f52fa0ea757a8b01eac2b5c0368d7a295`|
|6B7140|65 /25|`b4f1c6f4d7bf5470406e4360eeb3f00839de14a85ef99dbe980f0ce606bc9758`|
|6EEF10|103 /52|`f74f2347897d673f5bbc099b5c39a5700ddc02520be3fc5828f03cb7c83c7ebc`|
|77F110|61 /20|`07bd49c746bc83042ad798de2b8a96fc76162b9f448d8844e741a707bbe2dfa0`|
|781F20|208 /85|`2b868025867e75d073225f7b3b271d8587cbb3f63d9b4921e7a53063987931f5`|

The oracle checks selected ordered stores/calls, unrelated arena/globals,
immutable code/constants, caller stack/return, callee-saved registers and empty
x87 stack. Matrix coverage includes missing/partial/optional tokens, skipping
empty fields,512-byte bounds, all four object lookup outcomes, signed country
results, weight edges/NaN/Inf, hex whitespace/high bytes/tails/33rd pair, full32
boolean truth, late backing/Type/count/session mutations and repeated parsing.
Empty, negative and single-entry registry/TaskForce counts are explicit cases.

Canonical372 answers:
`private/team-observer-loading-20261020/fresh-a2/expected.json`, SHA256
`a9ff3363d1fc031f6cd38f1f798b69886b07762df1e55d3beb40bbc5de79a74f`.
Prior fresh-a1 contains344 genuine originals but its comparison failed on the
23-byte identifier truncation. Native-only repair replay-a2 failed on whitespace
crossing the token terminator; native mutable-buffer repair replay-a3 passed344
hits/zero misses. Expanded counts and stronger oracle assertions required a fresh
372 generation. Fresh-a2 comparison failed only because native fixture output
printed negative registry count as signed decimal. A fixture-only unsigned32
serialization fix passed replay-a4 with372 hits/zero misses. All failed attempts
retain their actual scope and failed audits; no receipts were relabeled.

## Reproduce

```sh
./build.command
./run.command --boot-camp-walk
./test.command
DEVELOPER_DIR=${DEVELOPER_DIR:-/Library/Developer/CommandLineTools} \
 build/tools-env/bin/cmake --build build/native \
 --target team-observer-loading-vectors -j 6
PYTHONPATH=tools:tests PYTHONHASHSEED=0 build/tools-env/bin/python -B \
 tools/run_evidence.py --audit private/NEW-observer-loading.audit.json \
 tests/compare_team_observer_loading.py \
 --exe private/official-1006-probe/game.exe \
 --native build/native/team-observer-loading-vectors \
 --expectations private/team-observer-loading-20261020/fresh-a2/expected.json \
 --report private/NEW-observer-loading.json
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest \
 test_team_observer_loading test_team_observer_construction test_team_observer_weight
```

For sanitizer replay use `build/sanitize/team-observer-loading-vectors` and fresh
report/audit paths. Reuse requires matching original dependencies; current native
is always rebuilt/run. No native verdict is cached.

## Validation and cost

Normal/sanitizer each pass6 focused CTests and explicitly replay2,542 originals:
372 loading,473 observer construction,386 Team construction,580 weights,266
Team destruction and465 unlink. All hits/zero misses/current native;28 Python
tests pass. This unwired internal layer does not justify a broad actual-world/SDL
rerun. Existing gameplay keeps its prior scope. Only Apple Silicon macOS is
tested; local validation is not independent acceptance or whole-game fidelity.

Fresh expanded generation2.326s. Final normal/sanitizer builds2.203/5.595s,
CTest processes.725/.862s, sanitizer configure15.964s, Python process.511s.
Normal/sanitizer replay processes.345/.780s(loading),.509/.575s(observer
construction),.456/.525s(Team construction),.344/.425s(weights),.425/.434s
(destruction),.414/.447s(unlink). Earlier344 generation/replays, initial builds,
inspection, edits/repairs and total wall time were not separately measured.
Some commands overlap; durations are not additive. Logs/script/costs remain in
private/team-observer-loading-20261020/validate.py and validation-a1/.
Receipt:private/team-observer-loading-receipt-a1.json.

## Next dependencies

[Definition enumeration41D540](TEAM_OBSERVER_DEFINITIONS_1006.md) now has390
original parent sequences and separate native constructor/parser composition.
Actual INI count/key/index/cache and scenario binding remain open. Mode1's null-record store
has an unsafe original domain; refuse it rather than silently skip the store.
Complete that caller and actual persistent registry/Type association, Rules/FP
startup, entered Tag/base lifetime children and exhausted tick8 before teardown
adoption. AC0C18/Neuron associations remain open. Verify transferred-GI movement,
including entered6BA990, before genuine Team/arrival/sight/SDL objectives. No
partial clone adoption, workers or runtime executable-read growth. Both games
and the full reconstruction goal remain incomplete.
