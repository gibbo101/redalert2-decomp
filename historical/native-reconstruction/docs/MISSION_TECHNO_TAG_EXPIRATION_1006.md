# Shared Radio and Techno Tag-expiration parents

Separate SDL-free kernels now recover complete636BA0 and6D2D10 for a nonnull
Tag subject with Abstract flags14 bit0 clear. They call the actual existing
Object5D3BD0 prefix and new complete passenger unlink468A70/control468120 kernels.
All448 original sequences /634 top-level calls match. This advances the inherited
expiration chain required by stock Infantry and Buildings; it does not yet join
Foot4C8460, Infantry501CB0, Building449E40 or waypoint broadcast recipients.
Live Boot Camp objectives remain disabled; the application is unchanged.

## Borrowed owners and recovered ordering

`MissionTechnoTagExpiration.hpp` contains views of existing Object/Radio/Techno
fields, list counts/backings and passenger links. No owner, pointer list or state
is mirrored. The caller owns associations, callback lifetimes and backing spans.
Binding performs no game queries. Named store observers remain non-mutating;
service callbacks can mutate live owners, with later original reads retained.
Exceptions propagate after any preceding effects; no rollback is promised.

- Radio calls Object expiration first, then visits its signed count of connection
  slots. A matching subject with nonzero removal **low byte** becomes null.
  It does not compact, change count, clear unmatched entries or touch unused tails.
- Removed subjects are unlinked from the passenger chain before Techno's other
  clears.468A70 removes the first matching head or later node, forwarding the
  subject's live +30 link without clearing that link. Null/missing heads return.
  A supplied host traversal bound refuses malformed cycles; original termination
  for malformed cyclic lists is not claimed.
- Techno clears23C and20C independently. For matching228, removal0 calls the
  supplied subject-owner virtual and then **rereads** actor1B4. An equal owner
  skips the target-change block. The portable code sequences these operations
  explicitly rather than relying on C++ operand evaluation order.
- The target-change block retains wrapped signed frame-minus-start/remaining
  arithmetic, inactive start=-1, the strict remaining>10 threshold and session0
  guard. Range(4,8) remains a named supplied service. After it returns, the caller
  rereads frame and stores timer148, supplied local padding14C, then duration150.
  No timer or RNG arithmetic is substituted inside that service.
- SetTarget370 precedes predicate1E4; a nonzero low-byte predicate calls1E0 and
  then kind2C. Only kind2 and live mission98==25 clear wordA8 then byte5BA.
  Independent22C and owner1B4 clears follow; the latter also clears byte372.
- PredicateC0, conditional queryCC(1) and matching action400 precede eight25C
  references and27C. Removal0 preserves3F8/1B0/control cleanup, while removal1
  clears matching3F8 and1B0 and calls actual control468120 when230 is nonnull.
  That child clears24 then28 only when24 matches, and returns low byte1 on all
  paths; its return is explicitly checked in the independent original roots.
- Service238 ->68A560 precedes a **live**208 ->6E24C0 lookup, then384/108 clears.
  Both deeper service implementations remain supplied. A diagnostic first-service
  mutation can cancel the second and install a late matching384 reference.
- The paired vectors are independent. Find the first matching3A8 key, remove that
  index from390 only if admitted by its own count, search3A8 again and remove its
  first match. Then remove the first3C0 match. Preserve count-before-shift stores,
  full backing tails and unequal counts. Duplicate keys are not all removed.

## Exact original proof and supplied boundaries

Target4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD and unverified pristine
provenance remain distinct. Only Apple Silicon macOS is tested. No public/YR/
recomp source, new dependency or runtime executable read was added.

The verifier fingerprints complete Object59, Radio75, Techno810, unlink65,
control24 and pointer-search38-byte roots plus the actual search vtable. Original
instructions execute unmodified in research-only Unicorn. Radio/Techno virtual
receiver association is supplied; these are direct parent calls, not a stock
Infantry/Building vtable dispatch proof. Abstract flag bit0-set Object coordinate/
Cell-discovery admission is explicitly refused by the native API; this proof is
for the nonnull Tag subject profile, not general pointer expiration.

Canonical original-only expectations:
`private/boot-camp-20261018/techno-expiration-fresh-a4/expected.json`, SHA256
`afaaa37ad3cfa6d4b6354bb8cbffb4dc8196f29dbc336b65e71c84b2830a3564`.
There are40 direct Radio,498 Techno,48 unlink and48 control top-level calls.
Children total538 Object/Radio,301 unlinks,178 controls and777 pointer searches.
Original stores include232 Radio slot clears,107 later-node/6 head unlinks,
68 ordered timer triples,162 owner/byte372 pairs,48 wordA8/byte5BA pairs and
60 control pairs. Wrapped Tag decrement/Object detachment and independent link
splices are verified through the same existing Object kernel.

The448 sequences cover raw removal words0/1/2/255/256/257/FFFFFF00/FFFFFFFF,
negative/zero/full counts, both Tag subjects, signed timer/frame extremes,
unequal paired counts, duplicates, retained tails and repeated calls. Diagnostic
services exercise37 owner mutations,14 range-driven frame changes and58 late
service/field mutations. A separate mode replaces key backing/counts before the
later scans. These are deliberate oracle inputs, not observed gameplay effects.

Whole mutable arenas and selected ordered logical stores match after every call;
ABI, return address, caller stack, preserved registers, immutable code/tables/
vtables/globals and untouched arena/padding bytes are guarded. Native stores are
logical assignments, not a claim about host instruction widths or all original
reads. Named virtuals, Range(4,8),68A560/6E24C0, initial flags/House/owner/list
associations and uninitialized retry-local padding remain supplied. The32-bit
removal word reaches the parent unchanged; low-byte conditions remain explicit.
No original-game observation, independent acceptance or whole-game claim follows.

## Verification, cost and continuation

Both full builds and final target rebuilds pass.139 normal/138 sanitizer CTests
pass in0.44s/7.55s;1,440 Python tests pass in28.865s. Final normal/sanitizer/
uncached replays each reuse448 sequences with zero misses and no original
execution. Drivers take0.182s/0.292s/0.522s, native comparisons0.017s/0.089s/0.017s.
Fresh original generation0.680s. Costs overlap and exclude some host startup;
complete build/manual repair/task-wall costs were not measured. No cache added.

Earlier a1/a2/a3 proofs retain their distinct earlier fixture/source identities;
a4 is canonical after adding late-read mutations and the control return check.
No original/native behavioral comparison failed. Initial C++ fixture mixed-auto
and Python scenario-count assertion errors were repaired before the first proof.
The a1 C++ build log is retained.61 prior app/runner/check binaries are hash-
identical. Prior original/owner/106-tick SDL receipts retain only their existing
scope; no new GUI or stock typed callback acceptance is claimed. Older finalizers
were not rerun. Private receipt/inventory are `techno-expiration-receipt-a4.json`
and `techno-expiration-runner-inventory-a4.json` under the same private directory.

```sh
./build.command
./test.command
./run.command --boot-camp-walk
build/native/mission-techno-tag-expiration-vectors --guards
env PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/techno-expiration-next.audit.json \
  tests/compare_mission_techno_tag_expiration.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/mission-techno-tag-expiration-vectors \
  --expectations private/boot-camp-20261018/techno-expiration-fresh-a4/expected.json \
  --report private/techno-expiration-next.json
# Substitute build/sanitize runner; add --uncached before the driver for the
# inspection control. Choose new report/audit paths for every invocation.
```

Next recover Foot4C8460 and actual typed override continuations, join their
recipients/services to discovery/Tag broadcast, then close production reveal/
full warm isolation and ordinary SDL objective gates. Private
`typed-expiration-next-inspect-a1.txt` contains the next parent inspection; it
is not a completed Foot/Building proof (the Building has multiple returns).
Both games and Boot Camp Objective1 remain incomplete. No workers/Windows actions.
