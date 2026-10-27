# Target tokens, registry resolution and Techno cast

`src/sim/TargetReference.hpp` recovers complete6B54A0 construction,6B5910
resolution and40DC20 cast. The resolver also uses an authored specialization of
actual compiled781D46/781E9A/781EE8 sorting and41BA10 signed-key comparison.
This is a dependency of MakeAlly's per-Techno target clearing, needed for Boot
Camp Objective1's action37. It remains separate from production ownership;
action37 is still request-only and live objectives remain disabled.

## Behavior and ownership

Construction retains all three padding bytes. Null stores tag0 then value0.
Kind11 stores tag11 and encodes the signed packed Cell words as `X+1000*Y`.
Other kinds store tag52 before querying the secondary interface at object+4;
that query passes its receiver on the stack, not in ECX. The returned ID replaces
only the value, so callback changes to the tag survive. Kind and ID are supplied
named virtual services. Cell binding is a pure borrowed view.

Resolution rejects tags other than52 without inspecting the registry. Count0
bypasses even a populated cache and casts the fallback object. Any nonzero count
checks the cached entry first, before testing the sorted byte. The cache can
refer to stable old/alternate backing or a detached owned entry. A cache hit can
therefore bypass a dirty registry. A missed dirty registry runs the actual sort
algorithm, rereads count, clears cache and stores sorted1 in that order. Signed
binary search saves the chosen entry in cache before casting its object. A
selected null or non-Techno object returns null without falling back. Missing or
nonpositive sorted searches cast the fallback. Late kind callbacks can change
registry/count/cache/token/objects; the selected object identity stays saved.

The cast calls kind exactly once for a nonnull object and accepts only kinds
1,2,6,15. The specialized sort retains original comparison order and complete
entry/duplicate ordering rather than using `std::sort`: size<=8 repeatedly moves
the first strict maximum to the end; larger ranges use a middle-to-low pivot,
`<=` left and `>=` right scans and the original signed byte-distance partition
choice. Pending ranges retain the original30-slot bound. Comparison telemetry
is read-only; it is not a replaceable comparison policy.

All state is borrowed, including the live backing span and fallback pointer.
Objects, tokens and entries have separate stable owners. Native pointers stay
native; there is no guest-memory runtime or lifted code. Host entry layout differs
from the guest's eight bytes: swaps preserve logical whole entries, not arbitrary
physical overlap. The domain excludes overlapping token/object/registry storage,
foreign/dangling identities and guest pointer wrapping. Sorting refuses negative
entered counts, backing overruns, pending overflow and extents above0x0fffffff
entries so signed guest byte-distance arithmetic remains nonwrapping. Positive
search also checks its backing. Missing entered services refuse; skipped services
are unnecessary. Refusal makes no rollback promise. Initial records, registries,
association/lifetime and virtual effects remain supplied.

## Exact original evidence

Supplied executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD and unverified pristine
authenticity remain distinct. Complete spans:
`6B54A0..6B5505`, `6B5910..6B59D3`, `40DC20..40DC48`, `41BA10..41BA31`,
`781D46..781E99`, `781E9A..781EE7`, `781EE8..781F13`.
The verifier fingerprints the whole executable, every complete span and both cast
tables, and pins selected ABI/ordering operands. No public/YR/recomp code or
new runtime executable reads were added. Unicorn remains research/test-only.

All1,279 fresh original sequences/3,107 top-level calls match. Actual execution
includes2,561 resolver,370 constructor,1,993 cast,685 qsort,1,972 short-sort,
21,088 swap and75,954 comparator calls. Supplied kind/ID callbacks occur2,221/261
times. Callback traces include cache identity/sorted/count before kind dispatch,
tag before ID, and exact comparison indexes/keys. Full final token/padding/object/
backing/cache/fallback state is compared. Original caller stack, preserved
registers, instructions/tables, instruction writes and immutable arena bytes are
audited. Eight diagnostic mutation modes exercise late reads and saved identities;
they are supplied experiments, not observations from a running original game.

Canonical original-only expectations:
`private/boot-camp-20261018/target-reference-fresh-a1/expected.json`, SHA256
`18f6bf59af132ac658614925ddaef2a969f6cfdb1d3b6e6dfff2ff5758ebab88`.
New/prior House map/threat/alliance normal/sanitizer/uncached replays retain their
canonical original receipts with current native/source identities. Exact commands
and timing are in `target-reference-validation-{normal,sanitize,uncached}-a2.json`.
Final focused receipt is `target-reference-receipt-a1.json`. Two earlier prior-family
replay attempts were safely rejected for reused audit names; canonical files were
not changed. Successful attempts use fresh `target-reference-check-...-a2` paths.
An initial automatic approval review misread a no-running-jobs status as a ban;
retry succeeded after checking actual AGENTS authorization. No bypass was used.

## Build, test and reuse

Run from the project directory. Normal comparison selects original reuse explicitly;
only use the fresh command when the original dependency/input guard requires it.

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
./test.command
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  -m unittest test_target_reference

PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py \
  --audit private/boot-camp-20261018/target-reference-replay-NEW.audit.json \
  tests/compare_target_reference.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/target-reference-vectors \
  --expectations private/boot-camp-20261018/target-reference-fresh-a1/expected.json \
  --report private/boot-camp-20261018/target-reference-replay-NEW.json

# Fresh original execution, only when needed; use new audit/output names.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py \
  --audit private/boot-camp-20261018/target-reference-fresh-NEW.audit.json \
  tests/compare_target_reference.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/target-reference-vectors \
  --output private/boot-camp-20261018/target-reference-fresh-NEW
```

For sanitizer replay select `build/sanitize/target-reference-vectors`; for an
uncached inspection control put `--uncached` before the driver. Neither replay
caches native results or executes originals. Both builds and147 normal/146
sanitizer CTests pass, plus16 focused Python tests. The application/normal Boot
Camp owner retain their prior binary hashes, so prior106-tick SDL walking scope
is retained; there is no new GUI/whole-chain/objective acceptance. The sanitizer
build rebuilt common targets; its broad CTests and relevant original replays pass.
No whole-inventory refresh or closed finalizer was run.

Measured fresh originals5.305s, native comparison0.129s; sanitizer build76.915s.
Normal full-build, repair and total task-wall times were not captured. Per-command
replay/unit/regression timing stays in the private receipt. No caching was added.
Next compose MakeAlly's actual target scan and stock null-target services using
these borrowed records, then actual parent/House/map/threat/sight effects on
production owners. Team/audio/scheduling/UI and ordinary SDL objective acceptance
remain open. Try current movement with `./run.command --boot-camp-walk`; its
supplied startup/routing/scheduling/presentation limitations are unchanged. Both
games and Boot Camp Objective1 remain incomplete; only Apple Silicon macOS tested.
