# Foot, Infantry and Building Tag expiration

Separate SDL-free entries now recover complete Foot4C8460, Infantry501CB0 and
Building449E40 for nonnull Tag subjects with Abstract flags14 bit0 clear. They
reuse the actual Radio/Techno/Object expiration chain, passenger/control cleanup
and pointer search. All871 original sequences /1,071 complete top-level calls
match. Waypoint broadcast recipient adoption and live mission objectives remain
open; this change does not alter the application.

## Borrowed owners and ordering

`MissionTypedTagExpiration.hpp` borrows the existing Techno parent, live typed
references, counts/backings and record/type/map associations. Registry lookup is
pure field binding, not a gameplay query. Services may mutate live owners; later
original reads remain late. Exceptions propagate after preceding writes, without
a rollback promise. The same fields are not duplicated between inherited layers.

Foot calls Techno first. It clears matching4C4, conditionally clears team580
using signed health6C and globalA40D04, then rereads580 before dispatching the
positive-health team's recipient588 virtual28. That nested dispatch remains a
named supplied child. Removed low-byte-nonzero link4C8 adopts the subject's live
4C8; a matching inherited1B0 invokes supplied6D6E50(null), followed by498 cleanup.
The self-subject team clear exists in the algorithm but is unreachable for the
distinct Tag/actor fixture associations.

For matching494, actual Mission594770 uses98 unless -1, then queuedA0. Mission8,
kind15, typeC08 and the destination's flags14 bit1/7D/positive health can retain
490/494; otherwise490 clears before494. The flags14 bit0-set Object coordinate/
discovery branch is excluded by the Tag profile. Matching4BC calls actual common
coordinates5D4E40, signed-divides X/Y by256 and truncates to words, then calls
actual548070 over the existing map/fallback. It stores4B8 before clearing4BC.
Both Foot lists remove all duplicate matches, retaining count-before-shifts and
backing tails. Their wrappers start49C/478:4A0/47C are backing pointers, not vtables.

Infantry calls actual Foot, then rereads and clears matching5A8. Diagnostic nested
services can install that match before the final read. Building calls Techno,
clears438/440/41C/4D4/4E8 and conditionally computes actual5D4540 health ratio.
Health6C is saved before supplied virtual84 returns a live strength+A0 reference.
The supplied FP profile is53-bit/toward-zero; native `OriginalRounding` restores
host rounding on return and exception. Equal or unordered ratio/late rules1368
comparison selects damaged1, not a positivity test. The live type418 animation
byte at1158 or1168 gates named44CA60 effects; those effects remain supplied.

Actual secondary-interface40FFB0 reaches Tag6B42D0, returning44. Building's kind4
factory-only early-return branch is therefore unreachable for this subject API,
not a recovered general factory expiration. Matching418 and three4C0/4C4/4C8
fields then clear; Building53C removes only the first match. Stock Infantry kind
is15; stock Building kind is6. Both stock Mission getters and expiration targets
are fingerprinted independently on the exact base executable.

## Original proof and limits

Target4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD and unverified pristine
provenance remain distinct. Only Apple Silicon macOS is tested. No public/YR/
recomp implementation, dependency or runtime executable read was added.

Verifier fingerprints complete Foot619, Infantry42 and Building362-byte spans,
the inherited roots, Mission/kind/coordinate/map/ratio/secondary-interface children
and relevant stock vtable targets. Research-only Unicorn executes original
instructions unmodified. Original mutable arenas, selected ordered stores, ABI,
stack/registers, code/tables/vtables/globals and untouched padding are guarded.
Native store traces describe logical assignments, not host instruction widths.

Canonical original-only expectations:
`private/boot-camp-20261018/typed-expiration-fresh-a3/expected.json`, SHA256
`5595432f6f0aa9f974e24f4adf492e53b32645bdfb24ccf6a7317c65912f080e`.
The871 sequences retain448 parent sequences, add256 Foot/Infantry sequences,
160 Building sequences and7 FP boundaries. There are270 Foot calls, including135
Infantry calls,167 Building calls,256 Mission getters,144 coordinate/map calls
(48 normal/96 fallback),74 nested callbacks,4 retained Infantry destinations,
135 health ratios and90 animation callbacks (42 ordinary/48 damaged). Actual
secondary Tag-kind dispatch executes167 times. Diagnostic strength mutation
modes1/2 execute32 times each. Inputs cover raw removal low bytes, negative/zero/
positive health, independent team global/health clears, sparse/fallback maps,
signed coordinate extremes, duplicate lists/tails, repeated calls, NaN/infinity/
equal FP boundaries and late callback-driven field/type/threshold changes.
These service mutations are oracle inputs, not observed gameplay effects.

All448 parent expectation rows retain their exact earlier token projections
before the new TYPED suffix, checked with both expectation hashes in
`typed-expiration-parent-projection-a3.json`. This does not relabel old originals.

Nested virtual28,6D6E50,84 association,44CA60, inherited named virtual/RNG/deeper
services, startup/record/type/map associations, FP profile and uninitialized
retry-local padding remain supplied. Kind4 factory and bit0-set Object-subject
paths are outside scope. No waypoint/production join, original-game observation,
independent acceptance, whole-frame or whole-game fidelity is claimed.

## Verification, costs and continuation

Both full builds pass.140 normal/139 sanitizer CTests pass in4.66s/15.63s;
1,443 Python tests pass in29.988s. Normal/sanitizer/uncached871-case replays each
have zero misses and execute no original instructions. Driver costs are
0.476s/2.495s/1.074s; native comparisons0.060s/2.039s/0.062s. Fresh original
generation takes2.195s. Costs overlap and exclude some startup; complete build,
manual repair and total task-wall costs were not measured. No cache added.

The retained a1 original generation failed comparison because the oracle put
vtables at backing-pointer fields4A0/47C. Correcting the fixture to wrappers49C/
478 produced passing a2, then a3 added independent team-clear/coverage guards.
Native behavior required no correction for that mismatch. Earlier attempts and
audits stay private with their own identities; a3 alone is canonical here.

All63 prior tracked app/runner/check binaries are hash-identical, preserving
their prior owner/106-tick SDL scope. Two new runners have separate identities.
No new GUI acceptance or closed finalizer rerun. Private receipt/inventory:
`typed-expiration-receipt-a3.json`, `typed-expiration-runner-inventory-a3.json`.

```sh
./build.command
./test.command
./run.command --boot-camp-walk
build/native/mission-typed-tag-expiration-vectors --guards
env PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/typed-expiration-next.audit.json \
  tests/compare_mission_typed_tag_expiration.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/mission-typed-tag-expiration-vectors \
  --expectations private/boot-camp-20261018/typed-expiration-fresh-a3/expected.json \
  --report private/typed-expiration-next.json
# Substitute build/sanitize runner; add --uncached before the driver for the
# inspection control. Choose fresh audit/report paths on every invocation.
```

Next join actual typed recipients into waypoint/discovery/Tag broadcast on shared
owners. Current production base-Object recipient associations do not acquire typed
fidelity from these isolated roots. Close required named effects, production
reveal owners, full warm preview isolation and ordinary SDL objective gates before
claiming live mission progress. Both games and Boot Camp Objective1 remain
incomplete; goal active. No workers, Windows actions or runtime-read expansion.
