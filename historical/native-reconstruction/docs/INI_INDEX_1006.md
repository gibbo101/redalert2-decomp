# Original INI index construction, growth and lookup

`src/assets/IniIndexStorage.cpp` recovers complete key-index constructor510CE0,
append510D00, Section reserve5111D0, key contains/value/find510DD0/510E70/511150
and Section contains510FF0. The same typed kernel is separately checked against
existing Section value/find511090/511280.1,456 original two-call sequences compare
ordered stores, borrowed identities, heap/sort arguments and complete supplied
owner arenas. Heap and CRT sorting remain supplied; merge/removal, parser and
scenario startup remain unjoined. No actual mission/observer adoption follows.

## Two actual index instantiations

The original stores CRC plus an Entry* or Section* in an eight-byte x86 record.
`IniIndexStorage` borrows backing/count4/capacity8/sortedC/hot10/fallback. Traits
retain the two actual typed payloads and existing `IniSectionIndexEntry` owners.
No old section enumeration algorithm or record representation was replaced.
Wrapped allocation sizes and slot displacement use the original eight-byte
stride even when a native pointer makes the C++ record larger. Runtime code
neither reads new executable bytes nor executes original code.

Constructor510CE0 clears backing, count, capacity, sorted byte and hot pointer
in that order, preserving fallback. It does not free old backing. Its original
call context is a key index; native Section startup is still supplied/unjoined.
Append is verified on the key instantiation and explicit reserve on Section;
the common implementation does not prove additional original caller associations.

## Growth and append order

Reserve refuses a negative signed increment without children/stores. Otherwise
it requests `(capacity + increment) * 8` with wrapped32 arithmetic. Null allocation
returns false without publication/free. A nonnull result copies positive live
count entries, one key then value at a time. Source backing is reread for each
iteration; the source slot is retained across its destination-key store, and
its value is read afterward. Loop count is read again after that pair. It then
frees the late current backing and reads capacity after free, adds the saved
increment and publishes backing, saved capacity and null hot in that order.
Sorted flag is retained. Allocation/free callback effects and alias backing are
observable and must not be normalized into host-container growth behavior.

Append compares wrapped count+1 with capacity as signed32. If growth is needed,
zero capacity chooses increment10; nonzero capacity chooses itself, including
the negative-increment refusal. After growth it loads current count/backing and
stores the late input key. It rereads count/backing and the input pointer for the
value store. It computes count+1 afterward, clears sorted and finally stores that
saved new count. A sorted-byte store mutation must not replace the saved count.
A no-growth append retains the hot pointer. Input key/value are borrowed live
fields, not an upfront snapshot.

All original slot addresses wrap32 displacement before physical resolution.
The supplied INT_MIN-count append cases wrap to slots0 then1. Native guards
refuse missing heap/sort children and access beyond supplied physical backing.
Logical capacity and actual fixture backing remain distinct: tests with unusual
counts/capacities describe the bounded supplied arena, not original heap safety
or a claim that an allocator provides more memory than requested.

## Lookup, cache and explicit services

Contains returns false for count exactly0, otherwise accepts a matching hot
record even with a negative count. A cold lookup sorts only when the raw sorted
byte is zero. Qsort receives saved backing/count and the actual comparator
identity, then hot is cleared before sorted=1. Search reads the live query,
count and backing after those stores. It compares signed32 CRCs and chooses the
upper middle for an even positive count. Contains installs a match as hot;
find returns a record identity without installing it. Value returns a borrowed
payload-pointer slot, including the shared fallback slot; match stores are
followed by a late hot-pointer read. Unsafe disappeared-hot value references
refuse. The key and Section fallback slots remain distinct.

CRT qsort is supplied signed-CRC sorting with stable equal-key permutation in
both fixtures. Comparator addresses511300/511380 and arguments are checked,
but the original CRT sorter/comparator/permutation is not executed or proven.
Duplicates retain their actual supplied physical order. Heap allocation/free
are likewise checked named services, not recovered CRT implementations.

## Exact evidence

Executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD and unverified pristine
provenance remain distinct. Fingerprinting precedes address use.

| Complete span | Bytes / instructions | SHA256 |
| --- | --- | --- |
|510CE0|19 /8|`c7afa1ea30e0db51090a1443582dc7826a96a2b78ce603f943571a6121e2e1d4`|
|510D00|199 /81|`fb794c1d780106d538adbdf77190ca1fa102cc14091437b14d28e88604f97120`|
|5111D0|134 /56|`8f184c4f527f6d29ba8819b76fe7bf52d15cb2551631872e218ca98128d7753d`|
|510DD0|151 /71|`2138c27edc74a0a845364a310edc6ed6a8edf0ca2c17cd337f268bb2b9cdb4d7`|
|510E70|149 /66|`55fd661ce93d0515a5eeea7756944459c8428308d5dedbd08631830b337365eb`|
|511150|121 /54|`4166b2a0a55fade073e9ae1084d96eea2aed31a74c4695083b0ccb95614a5121`|
|510FF0|151 /71|`7b7d91644d7f2e8bc1bc15d5eec8aae1b171d3bf0b3440300ba4cefb4fe5bf86`|
|511090|149 /66|`62fd9f6c6d9a78298773515073cae6a1bff08070ab0622e236221c88617b0387`|
|511280|121 /54|`d05019c8d5537ea7687101cbff4aa11ac53fffa68fa67fbd3c6bcb948c98a4ff`|

Original instructions stay unchanged. Caller stack/return/callee-saved registers,
immutable routines/fallback slots and complete supplied owner arenas are checked.
Post-store mutation is deferred to the next instruction boundary. Authored query
and pointer inputs are independent mutable fields. Returns check low-byte bool,
constructor identity, found record identity or borrowed slot plus payload as
appropriate. No public implementation/header or new dependency was incorporated.

The1,456 sequences cover both lookup types, signed CRC extremes, cold/raw-sorted
states, detached/backing hot entries, equal CRCs, zero/negative counts, allocation
failure/alias backing, wrapped byte requests, repeated constructor/grow/append,
and heap/sort/copy/publication/input mutations. Negative-unsorted unsafe sorting
is excluded from original passing domains and refused natively.

Canonical:`private/ini-construction-20261020/index-fresh-a1/expected.json`,
SHA256`22515f3c2c4d726083aba486513a61e3e93e88f661e0815f5e187047fe39576c`.
Fresh original generation took1.125s. The first generation passed. A setup verifier
caught an append span missing the last2 bytes of ret8; the length was corrected
199 before original generation. That preflight error remains in tool output,
not a separately saved failed original audit. Initial configure/build and later
focused logs are retained privately.

## Native composition and reuse

The native guard constructs actual list/entry records, appends their CRC/pointer
pairs into the recovered key index and finds the same record while linked text
order remains zeta/alpha. Heap and sorting are supplied. Another check reserves
an actual Section-index backing and calls the existing Section-value kernel on
exactly those borrowed fields. These are native ownership/integration checks,
not original-composed full merge/parser/startup evidence. Missing allocation,
negative increment and unsupported physical slot guards are checked separately.

Normal/sanitizer each pass14 focused CTests and replay6,201 original sequences
(1,456 new plus4,745 prior input/record/INI/observer/Team sequences), all hits/
zero misses/current native.46 Python tests pass. No unchanged original matrix
was regenerated. No broad SDL rerun for this unwired dependency; local validation
is not independent acceptance or a whole-game claim. Only Apple Silicon macOS
is tested; both base RA2 and YR/full reconstruction remain incomplete.

## Reproduce

```sh
./build.command
./run.command --boot-camp-walk
./test.command
DEVELOPER_DIR=${DEVELOPER_DIR:-/Library/Developer/CommandLineTools} \
 build/tools-env/bin/cmake --build build/native --target ini-index-vectors -j 6
build/native/ini-index-vectors --guards
PYTHONPATH=tools:tests PYTHONHASHSEED=0 build/tools-env/bin/python -B \
 tools/run_evidence.py --audit private/NEW-ini-index.audit.json \
 tests/compare_ini_index.py --exe private/official-1006-probe/game.exe \
 --native build/native/ini-index-vectors \
 --expectations private/ini-construction-20261020/index-fresh-a1/expected.json \
 --report private/NEW-ini-index.json
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest \
 test_ini_index test_ini_records test_ini_enumeration
```

Use build/sanitize and distinct audit/report paths for sanitizer replay.
Original dependencies must match for reuse; current native always runs. No native
verdict is cached. Fresh generation requires research JIT and a new private
`--output` instead of `--expectations`/`--report`.

## Next merge/parser dependencies

Complete the entered lifetime children before joining actual merge replacement:
vtable7A3B9C points to Entry scalar destructor5109B0; Section7A3BA4 points to
510A60, which enters510850. These associations are fingerprinted inspection
leads only. private/ini-construction-20261020/merge-lifetime-leads-b2.txt retains
aligned candidates. Earlier b1 includes unrelated/misaligned candidates and is
not proof. The Entry destructor transfers to base-node cleanup after ordered
name/value/comment releases; it is not the unrelated pipe wrapper510B40.

Then recover complete50E5F0 including its inline key-index removal/compaction,
Section/Entry lifetime and allocation-failure outcomes, followed by50BC30 text
parser with initially-empty construction and initially-nonempty merge paths.
Persistent observer/Type/Rules/FP ownership and entered Tag/base lifetime children
precede actual exhausted tick8/teardown. AC0C18/Neuron startup and transferred-GI
movement including6BA990 remain open before genuine Team/arrival/sight/SDL
objectives. No workers, runtime executable-read growth, live scheduling or new
playability.

## Measured cost

Normal/sanitizer focused builds8.275/8.085s; CTest processes0.652/1.184s;
sanitizer configure13.534s; Python process1.161s. Index replay processes
0.949/0.634s. Other timings/logs:
`private/ini-construction-20261020/index-validation-a1/`; script:
`private/ini-construction-20261020/index-validate.py`. Initial configure/build,
preflight repair, inspection/edit and total wall costs were not separately
measured. Concurrent durations are not additive. Receipt:
`private/ini-index-receipt-a1.json`.
