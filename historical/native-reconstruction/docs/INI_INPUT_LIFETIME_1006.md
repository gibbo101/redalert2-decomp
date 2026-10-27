# Original INI input ownership and source links

[INI_RECORDS_1006.md](INI_RECORDS_1006.md) completes the linked node/list/entry
construction and insertion dependency separately. Index growth and complete
merge/parser remain open; this lifetime proof retains its original scope.

`src/assets/IniInputLifetime.cpp` recovers complete buffer construction438380,
buffer cleanup438410, source attachment69B050 and pipe cleanup69B010.
226 original sequences compare ordered stores, callback identities/arguments,
constructor result and all supplied owner fields. Downstream dispatch is tested
both as a named supplied service and through the actual original69B050 child.
Heap allocation/free remain supplied; neither this proof nor the separate native
read composition recovers the complete INI parser or scenario startup.

## Recovered lifetime order

The buffer constructor writes null data0, the saved signed size4 and owned8=0.
For a strictly positive size it calls allocation, writes its result and sets
owned8=1 even if allocation returned null. Negative/zero sizes skip allocation.
Cleanup tests the raw ownership byte for nonzero, calls free even on null data,
then clears data, size and ownership in that order. Callback changes do not
replace these saved arguments or suppress the following stores. Heap semantics
and exhaustion effects beyond the supplied return remain outside this proof.

Attachment returns immediately when the current source equals the supplied
source identity. For a different nonnull source, its existing downstream pipe
first receives virtual Attach(null); the supplied source's downstream field is
then cleared. The old source is read late, after that callback, and its downstream
field is cleared. Finally the receiver stores its new source and the supplied
source points downstream to the receiver. Do not snapshot the old source before
the child or replace the final saved-argument write with a reread of source4.

Pipe cleanup installs base dispatch before any child. It sets the current
source's downstream to the current downstream; then it rereads downstream and
source for virtual Attach(source). Finally it clears its own downstream before
source. This splices an ordinary chain around the removed pipe. The virtual
child can enter the recovered attachment algorithm. Self aliases, disconnected
links and callback/store mutation preserve actual ordered behavior rather than
being normalized into an assumed valid chain. Native missing allocation/free/
attachment services refuse when entered; no no-op child substitutes are installed.

The portable asset layer stores native identities and a base-dispatch state,
not an original vtable address. `IniInputPipeOwner` is limited to these recovered
link fields; it is not a reconstructed file class or parser-owned lifetime yet.

## Binary evidence and boundaries

Exact executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD and unverified pristine
provenance remain separate. Fingerprinting precedes address use.

| Complete span | Bytes / instructions | SHA256 |
| --- | --- | --- |
|438380|45 /16|`163f7403197996a680344cd0531c601f429114808a28a247b2d75b2e645c565b`|
|438410|40 /14|`fbf51a46cc576656bced65be6528534cb8265cdfeca4349232c386577bc0bfd5`|
|69B050|67 /26|`20f9ca753ece2a2e94d4931d65f5b1aa6d4ca704a3866532b5abe737ac18c2a4`|
|69B010|50 /22|`62e2afcfd2a2a4235d93a959cdb3757007566a269356e2e4d2118db2229395de`|

The verifier also checks actual INI/base pipe virtual slot4 targets. Original
instructions remain unchanged. Caller stack/return/callee-saved registers,
immutable routine/vtable inputs and complete supplied arena preservation are
checked. Only constructor's returned owner identity is meaningful here; native
void APIs do not invent promises about incidental EAX values on cleanup/attach.
The two dispatch profiles are recorded separately in authored inputs: supplied
callbacks have no unclaimed attachment effects; actual callbacks execute the
complete recovered child. Heap allocation/free remain supplied in both profiles.

Tests cover signed size extremes, zero and ordinary4096-byte buffer requests,
allocation failure, null/nonzero data, raw ownership0/1/128/255, repeated calls,
eight linked/alias graph shapes, five source identities, heap/virtual callback
mutation and deferred post-store mutation. Full owner arena checks include raw
padding and unrelated supplied fields. Actual parent parser50BC30, heap/CRT,
file startup, source stream initialization and list/index/entry construction
remain unjoined. Existing input306 and enumeration818 proofs keep their own
supplied-child scopes.

## Separate native read composition

`ini-input-lifetime-vectors --guards` joins these lifetime kernels with the prior
buffered input and line reader: allocate an8-byte buffer, attach a source, read
`x\n`, observe EOF on the next call, then free/unlink. One buffer backing feeds
the read and one pipe/source identity feeds attachment and byte service. Heap
and byte I/O remain supplied. It also checks chain splicing through actual native
attachment and missing-allocation refusal. This is native ownership/integration
coverage, not original-composed full parser/startup evidence or new playability.

## Reproduce

```sh
./build.command
./run.command --boot-camp-walk
./test.command
DEVELOPER_DIR=${DEVELOPER_DIR:-/Library/Developer/CommandLineTools} \
 build/tools-env/bin/cmake --build build/native \
 --target ini-input-lifetime-vectors -j 6
build/native/ini-input-lifetime-vectors --guards
PYTHONPATH=tools:tests PYTHONHASHSEED=0 build/tools-env/bin/python -B \
 tools/run_evidence.py --audit private/NEW-ini-lifetime.audit.json \
 tests/compare_ini_input_lifetime.py --exe private/official-1006-probe/game.exe \
 --native build/native/ini-input-lifetime-vectors \
 --expectations private/ini-construction-20261020/lifetime-fresh-a1/expected.json \
 --report private/NEW-ini-lifetime.json
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest \
 test_ini_input_lifetime test_ini_input test_ini_enumeration
```

Use build/sanitize and distinct audit/report paths for sanitizer replay.
Original dependencies must match for a reuse hit; current native always reruns.
No native verdict is cached. Research JIT is needed only for a new generation,
using a new private `--output` instead of `--expectations`/`--report`.

Canonical226 answers:`private/ini-construction-20261020/lifetime-fresh-a1/expected.json`,
SHA256`a751a038c401a78ff3c22fddf78728e2ce0117d1c9a1cfd23f4feaac1343b10c`.
Fresh original generation took0.067s. No failed generation occurred in this family.
Earlier constructor/merge/list/index disassembly remains inspected leads only;
several broad candidate spans extend into subsequent routines and are not proofs.

## Next entered dependencies

Recover actual linked Section/Entry constructors, insertion/unlink and CRC-index
construction/growth, then complete merge/replacement50E5F0 and parser50BC30.
Initially-nonempty parsing merges; initially-empty parsing constructs records
inline. Neither can be replaced with decoded sorted-map fixtures. Persistent
observer/Type/Rules/FP ownership and entered Tag/base lifetime children precede
actual exhausted tick8/teardown. AC0C18/Neuron startup and transferred-GI movement
including6BA990 remain open before genuine Team/arrival/sight/SDL objectives.
No runtime executable-read growth, workers, new public code/dependency or live
scheduling. Only Apple Silicon macOS is tested; both games/full goal incomplete.

## Current validation and cost

Normal/sanitizer each pass12 focused CTests and replay4,282 original sequences
(226 new lifetime plus4,056 prior input/INI/observer/Team sequences). Every
replay reports actual hits/zero misses and runs current native.40 Python tests
pass. No broad SDL rerun for this unwired dependency; local verification is not
independent acceptance, whole-game fidelity or a newly playable capability.

Normal/sanitizer focused builds6.558/7.402s; CTest processes1.165/1.088s;
sanitizer configure16.442s; Python process0.798s. Lifetime replay processes
0.969/0.591s. Other family timings and logs are retained in
`private/ini-construction-20261020/lifetime-validation-a1/`; script:
`private/ini-construction-20261020/lifetime-validate.py`. Initial normal configure/
build, inspections, edits and total wall time were not separately measured.
Concurrent durations are not additive. Receipt:
`private/ini-input-lifetime-receipt-a1.json`.
