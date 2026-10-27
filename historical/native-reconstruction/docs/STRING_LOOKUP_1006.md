# Found-label localization lookup

The later [action11/color/localization join](MESSAGE_TEXT_LOOKUP_1006.md) adds
same-guest caller evidence and replaces the Boot Camp color token with the actual
private-table result. The standalone lookup receipt below retains its scope.
Message insertion/display and live objective progression remain open.

Boot Camp objective requests now resolve their key through a readable recovered
lookup and carry text decoded from the user's `ra2.csf`. This unblocks the text
payload needed for the first objective's eventual message display. Requests are
still recorded on the discarded mission owner; live sight, objective progression
and message display remain disabled. No supplied game text is tracked in Git.

## Recovered algorithm and explicit boundaries

`StringLookup.hpp` implements base `6F9EC0` through its found-label and null-label
returns, with complete CRT binary search `782025` and comparator `781F20`'s
locale-zero branch. The optional output is cleared before testing the label
pointer. Search uses the lower middle for even ranges, preserving duplicate
selection. Comparison folds only ASCII A-Z, compares unsigned bytes and stops
at NUL. It does not inherit the host's locale or sort order.

On a match, the optional extra slot is loaded using the label index and stored
before the index is read again for the text slot. An output pointer may alias
that index, a text slot or an extra slot. The implementation and proof retain
these dword stores and their order. Guest pointer slots are modeled as uint32
words; immutable native strings are resolved separately by a supplied association.

The missing-label branch beginning `6F9F22` allocates/formats/logs fallback text;
it is not recovered and the native entry explicitly refuses it. Nonzero CRT
locale, original CSF loading/sorting, startup registry ownership and message-list
insertion `5B4DA0` remain unjoined. The null-label return's static address is an
opaque result in the proof, never dereferenced by the application.

`PreparedStringLookup` owns the existing authored CSF v3 decoder's table, bounded
ASCII label views, indices and immutable UTF-8 payloads. The decoder lowercases
labels, making its map order valid for this bounded comparator association.
Labels over31 bytes or outside ASCII refuse at preparation; missing, empty-table
and ambiguous/multivalue requests refuse. No original loader or multi-string
selection claim follows. UTF-16 decoding/UTF-8 presentation and slot construction
are supplied adapters. Extra CSF metadata is retained by the reader but unused
when the application passes a null optional output.

`BootCampMissionWorld` requires a shared immutable lookup owner. Its recovered
action11 calls this lookup rather than returning the key as text. The request
recorder owns a payload copy; clones share only the immutable prepared table and
retain independent request state. Local checks cover real CSF resolution and
warm queued/drained clones continuing after source destruction. This composition
is native evidence over separately verified action11 and lookup roots, not a
fresh original proof of the entire dispatcher/localization/display chain.
Color mapping and message-list insertion/presentation remain supplied.

## Exact original evidence

Supplied base target: `private/official-1006-probe/game.exe`, 4,485,392 bytes,
SHA256 `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Fingerprint and instruction associations
are checked before execution. No original instructions are patched.

Canonical original-only expectations:
`private/boot-camp-20261018/string-lookup-fresh-a2/expected.json`, SHA256
`72713588435f46e60ca125f99b4d825628e04ef1fc34c985e47e3c8a235a6193`.
All3,224 sequences match normal and sanitizer runners, plus normal and
uncached-inspection expectation replays (3,224 hits/zero misses each). The fresh
guest enters lookup2,884 times, actual bsearch3,060 times and actual comparator
7,823 times. Search/comparison are never replaced with supplied callbacks.

Cases cover0..16 records, unique/duplicate labels, mixed-case queries, misses in
direct search, null-label returns, unsigned-byte comparison and every output
alias category. Ordered lookup/search/comparison/output traces, final indices
and all slot words match. Bounds/missing-label refusal and embedded NUL behavior
have native guards. Synthetic CSF tests cover case selection, UTF-8 content,
temporary-input lifetime and ambiguous/missing payload refusal. Those native
tests do not independently prove original loader behavior.

Guest checks retain callee-saved registers, return address, caller-stack guards,
immutable code/globals and full arena contents except the selected output word.
The direct CRT root is cdecl (caller retains argument slots); the lookup root
uses its actual `ret8`. Locale0, label registry and slot values are supplied
fixtures, not recovered startup state. Missing fallback and nonzero locale are
outside the entered proof. Unrealistic alias fixtures test ordered machine
behavior; they are not observations of ordinary gameplay.

The fresh-a1 audit caught an incorrect harness assumption that direct CRT search
cleaned its arguments. It remains preserved as failed. The repaired local cdecl
audit preserves all write/input/register/stack guards without modifying shared
oracle behavior. A native guard also had its expected `Z` versus `[` sign
corrected: folded `z` sorts after `[`. Fresh-a2 uses final sources and runners.

Original generation took2.373s; fresh native comparison0.086s. Final driver
elapsed times were2.881s fresh,0.303s normal replay,0.454s sanitizer replay and
0.385s uncached-inspection replay. No original execution or native results were
cached. Identity-checked original expectations were reused.

## Integration checks and remaining work

Full normal/sanitizer builds,117 normal/116 sanitizer CTests,1,358 Python tests
and both private-data owner checks pass. Ten retained affected families,
including prior action11, replay4,638 original sequences per current runner,
zero misses. Their original scopes remain unchanged; this is not fresh execution
of those old roots or independent acceptance. Exact20 replay commands are in
`private/boot-camp-20261018/string-lookup-replay-commands-a1.json`.

Actual106-tick SDL selection/move/pause/refusal/Stop/repeated-order/deselection
passes at `private/boot-camp-20261018/string-lookup-sdl-a1/`; arrival image
inspected. Its discarded warm arrival at source tick2 still preserves live
owners and framebuffer. No objective or text display is enabled by this smoke.
Presentation, routing and scheduling retain their existing supplied scope.

Normal/sanitizer owner elapsed times:3.35/5.90s. CTest times:1.87/7.89s;
`test.command` total2.96s. Python suite29.260s. The20-command replay batch took
29.363s. Build, SDL, host approval, total repair/manual-review and clone-only
costs were not separately measured. Private build/check logs and
`string-lookup-receipt-a1.json` retain current local identities; no whole inventory
or closed finalizer was rerun. Local verification is not independent acceptance.

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
./test.command
build/native/boot-camp-walk-check private/official-1006-probe
DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/sanitize/boot-camp-walk-check private/official-1006-probe

env PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/string-lookup-next.audit.json \
  tests/compare_string_lookup.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/string-lookup-vectors \
  --expectations private/boot-camp-20261018/string-lookup-fresh-a2/expected.json \
  --report private/string-lookup-next.json

./run.command --boot-camp-walk
./run.command --boot-camp-walk-smoke-test private/NEW-DIRECTORY
```

Use fresh audit/report destinations. For fresh original generation replace
`--expectations`/`--report` with `--output private/NEW-DIRECTORY`. Use the
sanitizer runner for sanitizer replay; add `--uncached` for the inspection control.
Unicorn remains a research/test dependency, never an application runtime.

Next recover the encountered color/message-list effects and verify their entered
caller composition before ordinary SDL objective text. Remaining audio/reveal/
alliance/Team effects and genuine live scheduling still gate Objective1. Both
full games remain incomplete; goal active. No workers, Windows actions, transfers,
downloads, new runtime executable reads or system/Xcode/DRM changes were used.
No public/YR/recomp code or new dependency was incorporated.
