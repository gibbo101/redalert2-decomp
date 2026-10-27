# Original INI enumeration and section index

[INI_INDEX_1006.md](INI_INDEX_1006.md) adds actual Section reserve/contains and
key-index construction/append/lookup, separately rechecking existing Section
value/find. Typed fields/backing are shared; merge/parser/startup stay unjoined.

[INI_RECORDS_1006.md](INI_RECORDS_1006.md) now recovers node/list/entry
construction and insertion on these same mutable links. The current native
observer composition uses those kernels; its index/head/count projection and
record loader remain supplied. The historical818-answer scope below is retained.

[INI_INPUT_1006.md](INI_INPUT_1006.md) recovers the entered byte/line boundary
separately. Actual text/list/index construction and duplicate/replacement behavior
remain open; this does not change the enumeration proof below.

`src/assets/IniEnumeration.cpp` now recovers complete count50CB00, key50CE00,
hot predicate511260, find511280 and borrowed-value511090 over shared section
index/cache and linked-entry owners.818 original sequences match selected ordered
stores, return identities and final fields. Actual zero-state493FC0/494190 CRC
runs inside the original parents and separate CRC calls. Native uses the existing
zlib dependency with the recovered padding and no case folding. No executable
reads, original code, new public implementation or dependency was added.

This is decoded INI ownership and lookup, not the original text parser or actual
scenario startup. CRT qsort is a supplied child. A separate native composition
passes linked entry order into the recovered observer-definition caller; it is
not an original-composed complete observer/scenario proof.

## Recovered representation and order

The section index has backing, signed count4, raw sortedC and hot-entry pointer10.
Each index entry holds a32-bit CRC and a distinct Section pointer. Section30 is
its signed key count; Section18 points into a linked list. Key lookup walks
next4 while checking previous8 and returns the final node's nameC. It does not
sort the key names. The decoded list's construction/order is still supplied.
The existing native `Ini::section()` sorted map cannot substitute for these owners.

Name CRC uses raw bytes up to NUL, not uppercase or a host locale. Complete
four-byte chunks use standard reflected CRC32. A remainder appends its length
byte and repeats the first byte of that remainder until the padded chunk has
four bytes. Native reconstructs only the returned zero-state CRC; original
streaming scratch mutations are not exposed as a general streaming API. The
verifier independently checks every original table word against polynomial
0xEDB88320; no extracted table is shipped.

Find511280 returns null immediately for count exactly0. Otherwise it invokes
qsort only when sortedC is zero. The sort gets saved backing/count arguments;
after it returns, the owner clears hot10 then sets sortedC=1, and searches late
backing/count. Search compares CRCs as signed32, using count/2 (upper middle for
even ranges). It returns an entry identity without installing it as hot. The
hot predicate tests the pointed entry's CRC, including a detached cached entry.
A negative already-sorted count reaches the signed search exit; an unsorted
negative count would supply an unsafe huge qsort length and is refused natively.

Borrowed-value511090 first checks count==0, then accepts a matching hot entry.
Otherwise it sorts/searches and installs a match as hot before returning that
current entry's Section-pointer slot. Missing results use the shared fallback
slot, not a fabricated empty Section. Native preserves a borrowed reference to
that slot. Actual fallback startup remains supplied.

Count50CB00 returns0 on null name, otherwise hashes before reading count. It
performs the first lookup/install, then repeats live count/hot/backing lookup
before dereferencing the Section and returning its signed30 field. A count change
after the first hot store can therefore select the fallback. Do not collapse
the two lookups or snapshot the Section early.

Key50CE00 similarly obtains the section through the hot/find and borrowed-value
paths. It compares the requested index with Section30 as signed32, without an
extra lower-bound clamp, then walks saved next pointers with wrapped decrement.
Null head/next/previous/name outcomes remain distinct. Native bounds traversal by
the supplied physical owner domain; unsupported cycles/unsafe pointer domains
refuse instead of emulating billions of iterations. Ordinary finite/sentinel lists
and negative indices that terminate at a missing link are included in the proof.

## Evidence and explicit services

Exact executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD and unverified pristine
provenance are separate. Fingerprinting precedes address use.

| Complete span | Bytes / instructions | SHA256 |
| --- | --- | --- |
|50CB00|193 /71|`5bef46ee8e61c21c33c82b5e96746a0c6972399577ba73603a7fa382a556db77`|
|50CE00|205 /77|`f7bc241e68f08682fe2e040f10a01b23e16b2048136e43222513fd1a213fe650`|
|511260|27 /11|`b4be17007c7a21c076634259b8a92af8be05edf2bc1bf564fc6a09cd1ca7ac20`|
|511280|121 /54|`d05019c8d5537ea7687101cbff4aa11ac53fffa68fa67fbd3c6bcb948c98a4ff`|
|511090|149 /66|`62fd9f6c6d9a78298773515073cae6a1bff08070ab0622e236221c88617b0387`|
|493FC0|457 /180|`f6a3f603d9966e0d3f4167ff99a2a665a090e8a52d0c93e417163faffb346a67`|
|494190|55 /24|`f1c550b9d6750dc2db6f100dde3a5e82e024aa044e057021cf0519be59c200de`|

The oracle executes those unchanged complete routines. Qsort arguments and its
comparator address511380 are checked, but sorting is a named supplied service
with signed CRC order and stable equal-key permutation in both fixtures. This
is not original CRT sorting/permutation fidelity. Duplicate-search results retain
the actual tested physical order; equal-key original qsort behavior remains open.
Decoded Section/index/list records, strings, fallback and startup are supplied.
Selected cache stores/order, unrelated arena/global preservation, immutable code/
CRC table/inputs, caller stack/return and callee-saved registers are checked.
Separate CRC roots have an explicit scratch-only write set and restore that test
scratch before whole-arena comparison.

Cases cover count/key/value/find/hot roots, empty/single/full/negative counts,
raw sorted0/1/128, cold/hot/detached entries, duplicate CRCs and signed extremes,
null/empty/case/high-byte/NUL/padding names, ordinary/reordered/missing linked
records, null names, signed index extremes, repeated calls, qsort mutation of
live backing/count/flag and post-store mutation of hot/count/Section fields.
Native guard checks cover missing sort and bounded cyclic traversal.

Canonical818 answers:private/ini-enumeration-20261020/fresh-a2/expected.json,
SHA256`0e97aaa41a77139dc169fd74471ebb2699ae5ec8eda908f6a2adaca543f47bd4`.
The first generation failed its arena check at case750: the oracle injected a
hot-pointer mutation inside Unicorn's pre-write hook, then the original store
overwrote it. The corrected oracle defers post-store mutations until the next
instruction boundary. Fresh-a2 generation/comparison passed; fresh-a1 failed audit
and the diagnostic are retained. Initial build requested an as-yet ungenerated
new target before CMake completed; the same configure handle was polled to its
successful completion before rebuilding. A Python test's copied field count was
corrected10 from9. No original code patch or failed-attempt receipt relabeling.
A later native-only hot-pointer guard change reuses the unchanged818 answers.

## Native observer composition

`ini-observer-composition` uses one authored decoded Section/list/index owner,
passes recovered count/key services to the recovered observer enumeration caller,
and loads the existing two observer identities in `zeta, alpha` order. This order
differs from lexical sort. It verifies one cold-sort call, retained hot cache,
repeated key access and caller mode9C stores despite false supplied record-loader
returns. The record-loader service in this composition remains supplied; the
separate observer constructor/parser composition retains its prior evidence.
Actual text/list/index construction and persistent scenario owners are not adopted.

## Reproduce

```sh
./build.command
./run.command --boot-camp-walk
./test.command
DEVELOPER_DIR=${DEVELOPER_DIR:-/Library/Developer/CommandLineTools} \
 build/tools-env/bin/cmake --build build/native \
 --target ini-enumeration-vectors ini-observer-composition -j 6
build/native/ini-observer-composition
PYTHONPATH=tools:tests PYTHONHASHSEED=0 build/tools-env/bin/python -B \
 tools/run_evidence.py --audit private/NEW-ini-enumeration.audit.json \
 tests/compare_ini_enumeration.py \
 --exe private/official-1006-probe/game.exe \
 --native build/native/ini-enumeration-vectors \
 --expectations private/ini-enumeration-20261020/fresh-a2/expected.json \
 --report private/NEW-ini-enumeration.json
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest \
 test_ini_enumeration test_team_observer_definitions test_team_observer_loading
```

Sanitizer uses build/sanitize runners and fresh audit/report paths. Current native
always reruns; originals are explicitly reused only with matching dependencies.
No native verdict is cached. Costs and final focused results are recorded below.

## Validation and cost

Normal/sanitizer each pass10 focused CTests and replay3,750 original sequences:
818 INI enumeration plus the previous2,932 observer/Team construction/loading/
weight/destruction/unlink sequences. All hits/zero misses/current native;34 Python
tests pass. Native linked-order observer composition is included in both profiles.
This unwired dependency does not warrant broad world/SDL repetition; visible
playability retains prior scope. Only Apple Silicon macOS is tested. Local
verification is not independent acceptance or whole-game fidelity.

Fresh-a2 generation.637s. Final normal/sanitizer builds9.655/8.365s, CTest
processes1.444/1.567s, sanitizer configure21.050s and Python process.671s.
Replay processes1.006/.781s(INI),.468/.513s(observer enumeration),.529/.484s
(parser),.471/.564s(observer constructor),.440/.517s(Team constructor),
.356/.529s(weights),.466/.509s(destruction),.437/.548s(unlink). Earlier normal
configures/builds, failed oracle/diagnostic, edits/repairs, inspection and total
wall time were not separately measured. Durations may overlap and are not
additive. Logs/script/costs:private/ini-enumeration-20261020/validate.py and
validation-a1/. Receipt:private/ini-enumeration-receipt-a1.json.

## Next binding requirements

Recover actual decoded INI text/index/list producers and relevant duplicate/
replacement behavior before binding a real scenario. Do not replace original
linked order with sorted-map order or declare a registry empty from fixtures.
Then persistent observer/Type/Rules/FP association and entered Tag/base lifetime
children precede exhausted tick8/teardown. AC0C18/Neuron startup remains open.
Transferred-GI movement including6BA990 precedes genuine Team/arrival/sight/SDL
objectives. No workers, partial clone adoption or runtime executable-read growth.
Both base RA2 and YR/full reconstruction remain incomplete.
