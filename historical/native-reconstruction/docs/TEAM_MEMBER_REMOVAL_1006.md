# Team member removal on the handed-over tutorial GIs

Complete6B8FB0 now removes actual GIs from the existing tutorial Team through an
explicit unscheduled seam. This is the member-unlink child needed by the eighth
Team tick's exhausted-Script destructor. Four handed-over GIs can be removed,
cloned and retained as player actors with their real Tags; one released GI then
finishes an ordinary one-Cell move through the production command/tick path.
The actual Team destructor and eighth tick are still guarded. No live discovery,
Team/arrival/sight scheduling or ordinary SDL objective transition is enabled.

## Recovered algorithm

`TeamMemberRemoval.hpp` borrows the Team, Foot and TaskForce fields. It first
writes Foot5A2=1, even for a Foot belonging to another Team, which then returns
true without other effects. On the matching Team it compares the actual Object
Tag with Team70, reads the House and conditionally calls4F52F0 and5D4430(null).
House-control truth uses the low byte. In particular, a player-controlled GI's
Tag is retained; unlinking does not imply Tag removal.

Slot-1 scans TaskForce Type entries. Each query saves the current TaskForce
before virtual84, compares its late inline entry, then reads that saved owner's
live signed count on a nonmatch. Later iterations and the final count test
reread the live Team Type/TaskForce. The scan's signed count test and final
unsigned slot/count comparison are distinct. Even a nonpositive initial count
sets the auto slot to zero; a negative count can consequently decrement slot0.
Counter decrements wrap. Native guards refuse beyond the six actual fields;
the original would otherwise write past this bounded Team allocation.

The chain scan preserves predecessor, saved successor and leader-seen state.
When found, it splices the actual link, clears Foot4C8/4C4, writes9C=-1, clears
498/22C, decrements Team48 and subtracts the queried threat from the live Team4C.
Traversal stops once it has both removed the member and seen another leader.
A matching Foot absent from the chain still has its Team pointer cleared; the
TaskForce count update precedes this scan and is not conditional on finding it.

Resume414(null,1) is gated by live loading, on-map7D,37D,76 and the low byte of
the caller's suppression argument. If no other leader was seen, it reads the
late Team head, promotes that actor and clears Cell34. Finally7E then7D become1.
The meaningful return is low-byte1. Keep this order and the independently live
fields; do not replace removal with pointer clearing or an STL-list erase.

## Exact-original evidence and scope

Exact supplied base:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD and unverified pristine
provenance remain distinct. Complete6B8FB0 is526 bytes/167 instructions, SHA256
`a9b3497c3190255f6b59249de5baec47ec6fefe40efefc234d2ca8c9c35f32ad`.
The verifier fingerprints before addresses. No external code/dependency or
runtime executable read was added and original instructions are never modified.

465 original/native sequences execute the unchanged complete parent. Named
House-control, Tag setter, type84, threat and resume children are supplied and
traced in this oracle. Earlier child originals and native owner composition keep
their separate scopes; this is not an original-composed complete Team teardown.
The fixture audits ordered stores/requests, all unrelated arena bytes, immutable
code/vtable/global inputs, caller stack/return and callee-saved registers.

Coverage includes head/middle/tail/missing members, reversed chains, raw leader
masks, foreign-Team early return, nullable Type/TaskForce, explicit/auto slots,
signed scan/unsigned final counts, signed extrema and wrapped totals, raw control/
resume gates, and five supplied mutations of TaskForce count/association, threat
subtotal, late head and Tag. Canonical expectations:
`private/team-teardown-20261020/removal-fresh-a3/expected.json`, SHA256
`a334cbfd666a15831d9710e9b2c20e41f66daa2ecf4fa03763f01700c84cb294`.

Attempt a1 caught the unsupported slot6/negative-count write outside the six
count fields; it remains a failed fixture/domain attempt, not a passing behavioral
comparison. The corrected465-case a2 passed. Correcting the new driver's inherited
scope description changed its original-source provenance, so a3 is the canonical
fresh origin; a2 remains unchanged. No existing original family was regenerated.
Canonical generation.191s/native comparison.054s/full driver.540s. Native-only
owner changes reuse original expectations and always run current native.

## Actual owners and next lesson dependency

`BootCampMissionWorld` binds the actual Team and supplied map-to-TaskForce E1
association. `BootCampWalkWorld` binds the actual GI/House/type/threat/Tag and
mission owners. The existing Infantry mission-resume body is factored into one
synchronous helper shared with House transfer; it is not a second resume path.
New persistent9C/498/22C/5A2/37D fields have supplied startup and live on the same
Infantry record. Clone remapping handles the new owned pointer fields and refuses
foreign pointers. TaskForce/type startup remains supplied, not original INI code.

The actual check starts after seventh-tick20/13, seeds owned498/22C/9C on the same
GIs, clones/destroys the source and removes all four in a nontrivial order. It
checks each count/threat decrement, cleared fields, retained player/Tag/Guard,
unchanged Script cursor and still-constructed Team, plus source isolation. A warm
clone retains the released actors, and one completes a neighboring-Cell production
move. This is native integration, not original movement-trace or live SDL proof.
No Team links are cleared outside the recovered removal kernel.

Next complete the actual exhaustion caller6B7D7A ->6B807A ->virtual20/6BE740 ->
6B7770 and its other entered children before enabling tick8. The private inspection
finds complete6B7770..6B79D7 (616 bytes), the deleting wrapper, matched-Type global
recipient callbacks41DFB0/41E070, active-session removal, conditional Tag6B3CC0,
broadcast6ECB90, five physical registry removals, optional Type deletion and base
40FF90/free781D3B. These are inspection leads, not recovered effects. Reuse this
actual unlink child and existing broadcast/vector owners; do not supply no-op
recipients, clear Team links to bypass permission, or synthesize objective success.
Then verify ordinary released-GI control and genuine discovery/arrival/Team
scheduling/remaining objective effects. Base RA2 and YR remain incomplete.

## Reproduce

```sh
./build.command
./run.command --boot-camp-walk
./test.command
build/native/boot-camp-walk-check private/official-1006-probe
build/sanitize/boot-camp-walk-check private/official-1006-probe
PYTHONPATH=tools:tests PYTHONHASHSEED=0 build/tools-env/bin/python -B \
 tools/run_evidence.py --audit private/NEW-team-removal.audit.json \
 tests/compare_team_member_removal.py --exe private/official-1006-probe/game.exe \
 --native build/native/team-member-removal-vectors \
 --expectations private/team-teardown-20261020/removal-fresh-a3/expected.json \
 --report private/NEW-team-removal.json
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_team_member_removal test_team_membership test_team_command20
```

Use the sanitizer vector runner with fresh report/audit paths. Full commands and
costs are in `private/team-teardown-20261020/validate.py` and `validation-a1/`.
Only Apple Silicon macOS tested; sanitizer SDL app is not built. Local validation
is not independent acceptance, whole-frame/game fidelity or ordinary objective
completion. Startup, route/schedule and presentation boundaries remain supplied
or approximate. No workers, Windows actions or runtime-read expansion.

## Current validation and costs

252 normal/251 sanitizer CTests,56 focused Python tests, both actual-owner checks
and256-tick desktop SDL pass. Each profile covers36,949 distinct original
sequences:465 removal,237 retained membership and36,247 prior dependencies, all
reuse hits/zero misses and always current native. Normal also has a final465-case
canonical a3 replay after the scope-description correction; the earlier a2 replay
retains its own original-source identity. Existing originals were not regenerated.
The SDL check retains right6/left2 facing and ordinary selection/movement/Stop/
repeated orders/pause/refusal/drawing; objectives remain disabled and it does not
exercise live Team removal. The released-GI move is separate native owner evidence.

Builds22.054/33.070s, CTests3.718/8.430s, actual owners36.317/115.241s,
Python2.587s and SDL9.982s. Canonical original generation.191s/native.054s/driver
.540s; removal replay drivers1.036/.470s. The final normal canonical replay takes
0.168s (native comparison included in its report). Checks overlap and durations
are not additive. Initial configure/fixture build/repair/edit/inspection/review,
initial owner run, targeted move-check rebuild and total wall time were not
separately measured. Commands/costs and preserved attempts remain in the private
lane. Receipt: `private/team-member-removal-receipt-a1.json`.
