# Moving and turning Unit residents in admission

`movingUnitAdmission` extends the same complete ordinary Unit admission root with
actual target, Facing, Drive, bearing, coordinate, distance and Drive +A4 children.
The original root is `703040`; the additional complete children are `4B8BE0`,
`5D4E40`, `4BA600`, `4BA410`, `77F110` and `4A4AC0`. This is a simulation helper
and differential driver, **not a runtime promotion**. The resident SDL demo still
has one commandable mover and one inspection-only parked Unit. Its existing
moving-resident, nonzero Advance and scatter refusals remain in force.

The exact proof, replays, regression refreshes and delivery state belong in the
opening [handoff](HANDOFF.md). The first eight-case pilot and first full proof
remain separate from the final proof; source/runner identities are never silently
upgraded. Native checks and SDL regressions establish integration, not original
gameplay observations or whole-frame fidelity.

## Decisions and arithmetic

The resident's flags mask `0x04` gates the activity path. A nonnull target skips both
Facing and Drive probes; otherwise actual Facing rotation can skip Drive IsMoving.
Drive IsMoving tests the complete destination sentinel first, then the complete
head sentinel, but compares only head X/Y against the actor's current position.
A head differing only in Z can therefore remain inactive. Do not substitute the
native `driving` boolean for this predicate.

An allied active Unit enters a distinct branch. Both current body Facings are
read independently, and the resident's opposite heading adds **0x7FFF** as a word.
Eight-direction rounding preserves shift, increment, shift and mask order.
Relative bearing uses float32 delta stores and the original arctangent table,
then the original half-pi subtraction, angle scale and FTOL. It binds the existing
`destinationDirection` arithmetic and private, hash-checked direction data rather
than host atan2. Its existing +/-2^20 X/Y difference bound remains explicit.

Matching rounded headings trigger two actual coordinate calls, resident before
mover. Distance uses signed wrapped X/Y/Z subtraction, squared terms added as
**(X squared + Z squared) + Y squared**, the actual table square root and FTOL's
qword-to-low-dword result. The comparison to 511 is signed. A nearby opposing Unit
whose relative bearing matches the mover's direction returns7 immediately. The
pilot's axis distances511 and512 produce actual integer results510 and512;
Euclidean host sqrt would change these intermediate results.

Otherwise, a nonzero live eligibility +5A0 byte precedes the actual Unit-kind
query and can promote the accumulated result to2. A zero byte instead calls
actual Drive +A4. That predicate preserves queue-range checks, transition record
selection, short/ordinary descriptor choice, rounded stored heading, queue-heading
comparison, nonzero matching jump index and the candidate's nonzero entry index.
The descriptor-zero jump field is zero, so it cannot pass the matching nonzero
index condition. No extracted descriptor table is compiled into the source.

A false Drive predicate retains the prior result; an active allied Unit is not
automatically a rejection. Result promotion remains ordered across residents.
Later stationary residents and the final zero/unordered terrain-speed rejection
still apply, even after result2. Earlier self-skip, shared fallback, primary versus
elevated lists, House/mission and occupation behavior remains in the shared root.
The earlier stationary entry retains its domain and traces.

## Ownership, evidence and limits

`UnitAdmissionMotionWorld` borrows explicitly associated actor records, stock
Drive/direction data and the recovered table-sqrt binding. Each actor supplies
its own coordinates, destination/head, Facing, eligibility, queue head, transition
index, sample index and short-track byte. There is no active-actor substitution or
runtime command owner in this helper. Initial records and associations are
supplied, not recovered construction, tick scheduling or moving map membership.

The original fixture initializes these records before its complete arena snapshot.
It executes the unchanged parent and children without admission callbacks or
instruction patches. Allowed-instruction/write checks, code/dispatch/numeric
inputs, complete actor/type/House/Drive/registry/Cell arena, fallback attributes,
callee-saved registers and caller stack remain audited. Ordered current-heading,
bearing, coordinate, distance and Drive-predicate observations join the earlier
full admission trace. Fresh original results are test expectations only.

The extension supports Unit-kind residents and ordinary descriptor indexes0..6.
Other restrictions of the earlier admission profile remain: loaded, unpromoted,
overlay-free, movement restriction -1, supplied directions/speeds/House/type and
empty passenger associations. Special descriptors, crushing, arbitrary kinds,
overlay paths and other earlier exclusions are not success services. Native
domain guards and rounding restoration are host policies rather than original
fault semantics. Only Apple Silicon macOS is tested.

The private supplied engine is4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage and reported no-CD provenance remain distinct;
pristine authenticity is unverified. The approved Windows copy already existed.
Existing recomp and YRpp references remain naming/ownership leads subject to the
license limits in [REFERENCES.md](REFERENCES.md); exact base execution decides
this behavior. No upstream, header, generated or lifted code, original table or
dependency is incorporated. No runtime executable-read expansion, worker, source
installation/disc/outpost2 write, Windows action, download or system/Xcode change.

## Reproduce and continue

```sh
./build.command
./test.command
build/tools-env/bin/python -B -m unittest discover -s tests -p 'test_*.py'
build/native/moving-unit-admission-vectors --guards

# Fresh original execution: authorized host Unicorn context, NEW private output.
build/tools-env/bin/python -B tests/compare_moving_unit_admission.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/moving-unit-admission-new
# Replay: add --expectations CURRENT_EXPECTED_JSON --report NEW_PRIVATE_JSON.
# Sanitizer replay: add --native build/sanitize/moving-unit-admission-vectors.
./run.command --resident-demo
```

Next recover the actual result2 preparation callers and nonzero Advance effects,
then join live moving/turning residents and genuine per-actor Process, queue,
Facing and turret owners on shared mutable Cells. Prove both original actor
addresses, their ordered Process calls and interleaved complete drawing before
enabling Unit1 commands and SDL acceptance. General pathfinding, construction,
combat, economy, AI, campaigns, multiplayer, audio, saves and Yuri's Revenge
remain incomplete. The full-game goal stays active.
