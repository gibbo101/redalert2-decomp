# House threat grid and enemy selection

Separate SDL-free `HouseThreat.hpp` now implements complete base grid rebuild
`4F3420`, score/enemy update `4EEBA0`, and signed Cell projection `54E370`.
They borrow live House/actor/registry/vector/grid fields. They remain unjoined to
MakeAlly and production diplomacy; action37 still records its ordered requests.
This advances the required children without treating an alliance-bit store as a
complete MakeAlly implementation.

## Grid rebuild

The routine clears exactly `0x4204` dwords at House+56D0, then traverses the
registry backward from wrapped `count - 1`. It saves that index rather than
rereading the count, but reads the live backing for every slot. Actor byte76 must
be zero and byte7D nonzero. Named virtual2A0 returns the signed threat value; the
positive result is saved across subsequent callbacks. Nonpositive values skip
kind/position services. Virtual2C is queried up to three times with independent
comparisons against 15, 1, and 2; it is not cached as one kind query.

That branch uses stored signed Cell words at actor+454. It rejects the invalid
Cell pair, projects through actual54E370, then reads the late Owner+1B4. Exact
owner identity always excludes. The mode-dependent flag134/135 predicate enables
the additional same-index/alliance-mask exclusions; null Owner passes. The other
branch calls named virtual1A4, consumes the returned record's Cell words at+24,
and projects them without those Owner/invalid-Cell exclusions. No RTTI class names
are inferred solely from the three numeric kind comparisons.

Each admitted contribution visits nine original offset/shift entries in order.
It masks the shift count as x86 does, adds the shifted saved threat with 32-bit
wrapping, and stores zero if the wrapped result is negative. This is not a wider
accumulator or saturation to INT_MAX. Repeated/aliased actors and reverse traversal
are preserved. The projection uses signed words divided by four toward zero,
then the recovered fixed grid stride and bias; direct projection accepts inputs
that are outside the grid's admitted stencil domain.

The two table arrays are read from the hash-checked executable by the **research
driver**, included in private command inputs, and passed explicitly to the test
runner. No extracted table contents or executable reads were added to the shipped
application. The API requires immutable table lifetimes; production data ownership
remains a future join. Virtual2A0/2C/1A4 implementations and initial actor/House/
registry/table associations remain supplied. Diagnostic callback modes test late
flag/Owner/invalid-Cell/registry/count reads, initial clearing, overflow and saved
threat values; they are not observed gameplay events.

## Score update and enemy selection

Complete4EEBA0 adds the supplied delta to **every** matching House entry, including
duplicates, with 32-bit wrapping. It then scans the saved backing/count, retaining
the first strictly greatest positive score among records with zero field13D that
are neither self, same-index nor already allied. Index-1 has no mask bit; other
indices use low-five-bit x86 shifts, including negative indices. It stores the
chosen House index at current+54F0 or-1 when none qualifies. This does not reuse
the grid's Owner-filter policy. Tied highest scores retain the earlier entry.

Pure field-view callbacks bind existing owners without queries or copies. Null
records that the original would dereference, undersized backing, and out-of-grid
stencil addresses are explicit native refusals, not original fault parity. A
null score target may be compared/updated; nonpositive null entries skip lookup.
Refusal after clearing or earlier updates is not rollback. No arbitrary physical
field/vector overlap, heap construction or production ownership claim is made.

## Evidence and reproduction

The target remains 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD and unverified pristine
authenticity are distinct. Fingerprinted complete spans are `4F3420..4F35E4`,
`4EEBA0..4EEC6C`, and `54E370..54E39F`, with table inspections at7D9FA0/7D9FC4.
Original instructions are unmodified. Only the three named virtual leaves are
supplied; projection runs actual original instructions in each admitted branch.

The final canonical original-only receipt is
`private/boot-camp-20261018/house-threat-fresh-a3/expected.json`, SHA256
`3d6a83d443ac5a1a5761a99d3bb8b19c81e83be30bc60e2dc373e73b9261be3a`.
All1,214 sequences
match, covering481 grid rebuilds,477 score/enemy updates,256 direct projections,
all256 active-byte/exclusion values, signed-word limits, wrapped additions,
registry aliasing/replacement, repeated kind queries, early exits and explicit
highest-score ties in both entry orders with/without earlier exclusion. Caller
stack, saved registers, code/tables, all mutable projections and arena padding
are audited. Grid output is losslessly encoded as its known default plus indexed
exceptions; the original oracle does not calculate expected grid/score results.

The earlier passing a1/a2 originals remain private. A2 corrected unverified class
labels to stored-Cell terminology. A3 strengthens highest-score tie and raw13D
selection coverage; neither silently relabels an old original receipt. The initial
preflight repaired an unmatched Python parenthesis and the three-byte RET extent
before any original execution. Final elapsed costs, expectations hash and runner
inventory are recorded in `house-threat-receipt-a1.json` and opening HANDOFF.
Local verification is not independent acceptance or a whole MakeAlly/game proof.

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
./test.command
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  -m unittest test_house_threat

# Use new private output/audit names; keep earlier originals immutable.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py \
  --audit private/boot-camp-20261018/house-threat-fresh-NEW.audit.json \
  tests/compare_house_threat.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/house-threat-vectors \
  --output private/boot-camp-20261018/house-threat-fresh-NEW

PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py \
  --audit private/boot-camp-20261018/house-threat-replay-NEW.audit.json \
  tests/compare_house_threat.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/house-threat-vectors \
  --expectations private/boot-camp-20261018/house-threat-fresh-a3/expected.json \
  --report private/boot-camp-20261018/house-threat-replay-NEW.json
```

Final new-family replay names are `house-threat-replay-{normal,sanitize,uncached}-a2`.
Use the sanitizer runner for its replay and put `--uncached` before the driver for
the control. Prior eligibility/lookup replay names are
`threat-prior-alliance-replay-{normal,sanitize,uncached}-a1`, retaining
`house-alliance-fresh-a1/expected.json` with `house-alliance-vectors`.
No original/native execution caching or closed finalizer rerun was added.

The later [map sight scans](HOUSE_MAP_REFRESH_1006.md) recover complete removal/
addition traversal separately, with named effect leaves still supplied.

Next join these actual dependencies into complete MakeAlly, recovering its map
services and per-Techno target/reference clearing, then shared production House
ownership/full warm preview isolation/Team/audio/scheduling/UI and ordinary SDL
objective acceptance. The unchanged application retains its recorded walking
scope: `./run.command --boot-camp-walk`. Both games and Boot Camp Objective1 remain
incomplete. No new platform support, live diplomacy or GUI acceptance is claimed.
