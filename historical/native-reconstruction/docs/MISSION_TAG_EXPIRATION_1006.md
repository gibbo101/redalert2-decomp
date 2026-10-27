# Boot Camp Tag expiration broadcast and map/logic cleanup

`MissionTagExpiration.hpp` recovers the Tag44 path of generic expiration and
its complete map, logic and nonnull-Tag Cell children. Views borrow live Tag
counters, Cell fields, map slots/fallback, registry counts/backing and globals.
The existing null Cell tag kernel is reused. This is an internal dependency of
the first discovery objective's one-shot Tag retirement. **RaiseEvent composition,
actual recipient effects, deferred drain/destruction, discovery, scheduling and
actions remain unjoined. Walking and objective status are unchanged.** No fixture
recipient/RTTI/selection service may silently become a runtime implementation.

## Evidence and supplied boundaries

Exact supplied base:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Only Apple Silicon macOS is tested.
No public/header/generated/lifted code, extracted data, dependency or application
executable read was added.

Original-only `private/boot-camp-20261018/expiration-fresh-a1/{expected,report}.json`
contains **488 sequences /990 complete top-level roots**. The unmodified original
executes433 generic6ECB90 calls,637 map559D80,462 logic53E110,961 Cell47A340,
586 null Cell47A460,681 packed-point searches42D120,637 pointer searches4D5B40
and2,954 actual Tag kind6B42D0 calls. Native selected logical assignments and
retained vector tails match all selected ordered original stores. This does not
claim native instruction widths or a complete original-read trace.

The verifier fingerprints all those roots, the switch tables, Tag kind dispatch,
the packed-point/pointer vector dispatch and relevant initializer instructions.
Each complete root keeps instruction/write/ABI/stack/callee-saved checks, immutable
code/tables/map slots and whole-owner arenas. Native guards reject missing backing,
invalid indices, missing services and entered positive AbstractType association.
Callback faults propagate; there is no rollback claim.

Named supplied services are CRT783CE4's negative Tag-to-AbstractType association
(433 calls), recipient virtual dispatch+28 (1,116 calls) and map498F10 selection
effects (145 calls). Their ABI, argument identities and caller return addresses
are checked. Diagnostic callbacks shrink/replace recipient backing, change Cells/
point count or rewrite globals to establish live reads; these are not recovered
gameplay effects. Initial Tag flags/Cell links/registries/map association remain
supplied. The generic entry is restricted to actual kind44 with Abstract flags14
bit1 clear and a negative AbstractType cast; other expiration kinds are outside
this API. Separate private40FF10 inspection shows its low-three-bit clear, but
startup/RTTI construction is not differentially recovered here.

Normal, sanitizer and uncached-inspection current-native replays
`expiration-replay-{normal,sanitize,uncached}-a1.json` each reuse488 sequences with
zero misses/zero original execution. Original generation is saved before native
comparison, and native/source/runner identities remain distinct from original
provenance. No proof comparison failed. An initial build requested the newly
added target before CMake regeneration and was repaired by configuring both
builds; this was a build discovery issue, not a behavioral mismatch.

## Recovered behavior

- Generic expiration first clears matching833680 and833684 globals. Clearing
  the second invokes498F10(0) after its null store. Callback rewrites are retained;
  the first global is not revisited. The negative RTTI query follows those effects.
- Tag44's recipient traversal reads live backing/count after each callback and
  advances its index without snapshotting/removing recipients. The caller's full
  removed word reaches recipients; map dispatch always receives1, even for a
  caller flag0. Logic ignores that flag.
- Map lookup uses the signed combined `y*512+x` of signed16-bit words, without
  independent X/Y bounds. Missing/out-of-range slots forward to one fallback and
  store the original packed pair there, including repeated stores.
- Map tagged-point traversal clears only matching Cell Tags, decrementing the
  actual wrapped counter before the null Cell tag store. It searches/removes
  using that Cell's **stored** point, which can differ from the lookup point.
  After a matching Cell it revisits the current index, even if search found none.
  A cleared unrelated Cell/Tag is not substituted for the selected identity.
- Fallback47A340 always follows the traversal. If its current Tag matches, it
  decrements/clears and searches the same map tagged-point vector. Its independent
  Cell+2C/+30 links clear when equal to the subject, even with an unrelated Tag.
  A nonnull Cell+28 does not enter the kind61 vector path for a Tag44 subject.
- The map's distinct866238 registry removes only the first matching Tag pointer.
  Logic866160 removes **every** matching pointer, revisiting after each removal.
  Both preserve unused tails; count stores precede ordered shifts. They never
  deduplicate another registry or shrink its backing as a side effect.

## Checks, costs and commands

Five focused CTests per build and12 Python tests pass. The existing walking SDL
baseline is retained at its prior scope; no broad/SDL rerun for this unwired
dependency. Local verification is not independent acceptance, original gameplay
observation or a completed objective. Prior Tag/Trigger/Event sources and runners
were unchanged; no old original matrix was regenerated.

Original generation0.975s; initial driver1.291s. Normal/sanitizer/uncached replay
drivers0.178s/1.614s/0.293s; native comparison0.030s/1.427s/0.029s. Builds1.03s/
1.49s after configuration (generation9.7s/8.7s); focused CTest bodies0.06s/0.29s;
Python0.101s. Costs overlap and exclude some host/tool startup. Implementation,
manual repairs and total task-wall costs are unavailable. Private
`expiration-validation.json` consolidates identities, costs and limitations.

```sh
./build.command
./test.command
./run.command --boot-camp-walk
# Current player capability remains selection/walking/Stop/pause.
build/native/mission-tag-expiration-vectors --guards
build/sanitize/mission-tag-expiration-vectors --guards
env DEVELOPER_DIR=/Library/Developer/CommandLineTools PYTHONHASHSEED=0 \
  PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/mission-expiration-next.audit.json \
  tests/compare_mission_tag_expiration.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/mission-tag-expiration-vectors \
  --expectations private/boot-camp-20261018/expiration-fresh-a1/expected.json \
  --report private/mission-expiration-next.json
# Sanitizer: substitute build/sanitize and fresh report/audit names.
# Uncached inspection control: add --uncached before --audit, retaining originals.
# Fresh only for changed original dependencies: omit expectations/report and use
# --output private/mission-expiration-new-fresh in the authorized Mac-host JIT context.
```

Next join actual recipient effects and Tag RaiseEvent, then deferred drain6ECF10
and actual Tag destructor dispatch7AC700+20 ->6B42E0/6B39F0 on shared mission
owners. Drain inspection shows repeated removal before Release/RTTI/destruction,
but its existing Overlay proof does not establish Tag lifetime. Preserve the
policy1/count1 direct-detachment bypass; broadcast cannot be replaced by that
earlier direct owner clear. Actual discovery/building dispatch and encountered
scheduler/actions still precede the first objective. No workers/Windows actions
or runtime read expansion. Full base RA2/YR remains incomplete.
