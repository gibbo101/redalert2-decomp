# Original linked INI records

[INI_INDEX_1006.md](INI_INDEX_1006.md) now recovers the entered index
construction/growth/lookup dependency on these typed record pointers. Complete
merge/removal, actual Entry/Section destruction and parser remain unjoined.

`src/assets/IniRecords.cpp` recovers complete node construction40E160,
insertion40E180, node scalar cleanup40E1D0, base-list construction490E80,
entry-list construction510BB0, list scalar cleanup510C20 and entry construction
510B60.463 original two-call sequences compare ordered stores, return identities,
free arguments and the complete supplied owner arena. Heap free remains supplied;
text, index construction/growth, merge/replacement and scenario startup remain
unjoined. This is an asset-layer dependency, not live mission/observer adoption.

## Shared native representation

`IniEntryLink` now has a mutable previous8 pointer and symbolic node dispatch,
while retaining the next/name fields used by recovered enumeration. `IniRecordList`
contains the two stable sentinels; `IniRecordEntry` contains that same link and
borrowed text/comment fields plus three32-bit metadata fields. Native dispatch
states express the observed base/derived transitions without embedding original
vtable addresses or executing original code. Owners must remain at stable native
addresses while linked; copying/rebinding populated storage is outside this proof.

The existing count/key algorithms still read the same links. Their behavior and
818-answer original provenance are unchanged; current native comparisons rerun
after the header change. A separate native observer composition now constructs
both records and their sentinels with these kernels, inserts zeta then alpha
before the tail, and enumerates that order into existing observer identities.
The Section head/count/index projection and record-loader child remain supplied
in that composition. No original-composed full observer/parser proof is claimed.

## Recovered order and ownership

Node construction clears next then previous, then installs base dispatch, leaving
unrelated name/metadata untouched. It does not repair old neighbors. Insertion
first detaches the candidate only when both its next and previous links are
nonnull. It updates the previous neighbor's next with the saved next identity,
then rereads both candidate links for the other neighbor store. It clears previous
before next. It then saves the anchor's next, writes candidate previous/next,
rereads anchor next for its back-link, and finally writes anchor next. These
stores must not be collapsed into container operations; aliases and mutations
can make their ordering observable. Original null-candidate writes and unsafe
late-null dereferences refuse in native code, retaining prior stores.

Both list constructors initialize the head and tail nodes, install base-list
dispatch and insert the tail after the head.510BB0 additionally installs entry-
list dispatch last. This produces an empty head->tail chain with null outer links.
The shared helper retains each constructor's complete observed store sequence.

Node scalar cleanup installs base dispatch before detaching, tests only the low
bit of its flags for supplied free, and returns the original owner identity.
List scalar cleanup installs base dispatch, repeatedly reads head.next and
unlinks members that have both links, then cleans up the tail followed by head.
It never invokes member destructors or deletes entries. Only its own low-bit
free is entered. Native traversal is bounded by the supplied physical member
domain; exhausted/cyclic unsupported traversal refuses instead of silently
continuing or claiming success. Missing entered free services refuse.

Entry construction borrows seven caller fields. It captures value before its
first stores, clears links, then writes value/name, inline-comment/comments and
metadata20/1C/24 in the original order, installing entry dispatch last. Arguments
are read at their recovered saved/late points. The two argument-mutation cases
show that a single upfront snapshot would change results. It does not duplicate,
parse or free strings/comments; those parent/CRT lifetimes remain unjoined.

## Exact evidence

Executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD and unverified pristine
provenance stay distinct. The verifier fingerprints before address use.

| Complete span | Bytes / instructions | SHA256 |
| --- | --- | --- |
|40E160|17 /6|`8741680ba09bfc0972c82d2bb1e1add81614021396fe36ba06a2bfcd91008e4a`|
|40E180|75 /26|`214a0a07ec38bfa75cf4f8ac68a903a098527fe5ed82200facf9d7fd5b083d58`|
|40E1D0|69 /26|`2e3b256ba70d6cd3bc773a9409a06f655358b7e4717b5757afae797e610fc3ad`|
|490E80|105 /40|`bbc063c499c9ff9ca56bd7f8dd3176bcd7fb75c920104694d3878f64ae67baf8`|
|510BB0|111 /41|`048fa67241285ef7211b24ca7b221a89d6217d49d794999ebebb5b19ff3a3658`|
|510C20|179 /68|`87dc68d70244f21ab91aba1b6f296c1bc7aaca209335da485e19b5903072369b`|
|510B60|68 /20|`d9aa5bef7a969bc9fe25ee8d53acf651cfe0d8f8cb67016ece1009dd4abb35f6`|

Original routines run unchanged. Only scalar free is a supplied child. Caller
stack/return/callee-saved registers, immutable routines/text and full supplied
arena preservation are checked. Deferred post-store mutations happen at the next
instruction boundary; caller-argument mutations affect actual consumed stack
slots. Insert's incidental EAX is not given a native return contract. All other
roots compare their returned owner identity. No public implementation/header or
new dependency was incorporated.

Cases cover all seven roots, eight ordinary/disconnected/alias graph shapes,
six node identities, all36 insertion anchor/candidate pairs per graph, repeated
calls, raw free flags0/1/2/128/255, nullable text/comment fields and signed metadata
extremes. Mutation cases vary link/anchor stores, late free effects and saved/late
constructor arguments. Native guards cover null insertion, missing free, bounded
cleanup, actual constructor/insertion order and preserved member identity.

Canonical463 answers:`private/ini-construction-20261020/records-fresh-a1/expected.json`,
SHA256`33e67d69071862e34c42572c67ec75a4058cbdbe824161fa3c7a46dfa398a09f`.
Fresh original generation took0.150s; the first generation passed. During setup,
the verifier rejected a list-cleanup span missing the last2 bytes of its ret4;
the endpoint was corrected before generation. An initial new-target build was
requested before configure completed and failed with no target. The same live
configure handle then completed, and the next build passed. The failed and successful build logs are retained. The setup verifier failure
was reported in tool output but not separately saved. No failed original proof
was relabeled.

## Reproduce

```sh
./build.command
./run.command --boot-camp-walk
./test.command
DEVELOPER_DIR=${DEVELOPER_DIR:-/Library/Developer/CommandLineTools} \
 build/tools-env/bin/cmake --build build/native \
 --target ini-record-vectors ini-observer-composition -j 6
build/native/ini-record-vectors --guards
build/native/ini-observer-composition
PYTHONPATH=tools:tests PYTHONHASHSEED=0 build/tools-env/bin/python -B \
 tools/run_evidence.py --audit private/NEW-ini-records.audit.json \
 tests/compare_ini_records.py --exe private/official-1006-probe/game.exe \
 --native build/native/ini-record-vectors \
 --expectations private/ini-construction-20261020/records-fresh-a1/expected.json \
 --report private/NEW-ini-records.json
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest \
 test_ini_records test_ini_enumeration
```

Use build/sanitize and fresh audit/report paths for sanitizer replay. Reuse is
explicit and dependency checked; current native always runs. No native verdict
is cached. New generation requires research JIT and a fresh private `--output`
in place of `--expectations`/`--report`.

## Next entered dependencies

Recover CRC-index construction/growth and key-index lookup/removal, then complete
50E5F0 merge/replacement and50BC30 parser including entered Section/Entry/CRT
lifetime children. Empty loading constructs records inline; nonempty loading
merges and preserves/transfers comment fields. Do not substitute a sorted map or
ignore either initial-registry path. Persistent observer/Type/Rules/FP ownership
and entered Tag/base lifetime children precede actual exhausted tick8/teardown.
AC0C18/Neuron startup and transferred-GI movement including6BA990 remain open
before genuine Team/arrival/sight/SDL objectives. No runtime executable-read
growth, workers, live scheduling or new playability; base RA2/YR/full goal remain
incomplete. Only Apple Silicon macOS is tested.

## Current validation and cost

Normal/sanitizer each pass13 focused CTests and replay4,745 original sequences
(463 new records plus4,282 prior input/INI/observer/Team sequences), all hits/
zero misses/current native.43 Python tests pass. The changed native link header
and observer composition were rebuilt. No unchanged original matrix was
regenerated and no broad SDL rerun was needed for this unwired layer. Local
verification is not independent acceptance or a whole-game claim.

Normal/sanitizer focused builds8.284/9.628s, CTest processes0.589/1.709s;
sanitizer configure19.533s; Python process0.773s. Record replay processes
0.793/0.593s. Other timings/logs are retained in
`private/ini-construction-20261020/records-validation-a1/`; script:
`private/ini-construction-20261020/records-validate.py`. Initial configure/build,
failed setup/build, inspection/edit/repair and total wall costs were not
separately measured. Concurrent durations are not additive. Receipt:
`private/ini-records-receipt-a1.json`.
