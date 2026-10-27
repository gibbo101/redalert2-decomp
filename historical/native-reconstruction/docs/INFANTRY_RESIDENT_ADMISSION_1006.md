# Friendly Infantry admission and the actual Team activation tick

Successor: [TEAM_SCRIPT_1006.md](TEAM_SCRIPT_1006.md) now completes the sixth
explicit tick's50/70 command. The earlier sixth-tick refusal below is historical;
command20 at the seventh tick is the current guard.

This closes the demonstrated anchor blocker for the first Day1 objective Team.
The fifth explicit Team-AI tick now completes activation and near regroup on the
four actual Other2 GIs. It queues Guard5 and clears their destinations/routes.
The next active-Script tick refuses before mutation. No live scheduler, Script
command effect, House transfer or SDL objective transition is enabled here.

## Evidence and algorithm

Exact supplied base:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. No public implementation was incorporated.

Complete503190 now admits an explicitly bound ordinary friendly E1 resident
continuation. Preserve its repeated live mission queries, special-mission and
Type-byte gates, resident kind query, object-to-House alliance call, second kind
query and raw Walk Is_Moving low byte. Stationary Infantry increment the local
count; self does not. Follow each live next link after the child. After terrain
speed and occupation-bit5 decisions, an allied fully occupied Cell returns6 when
that count is exactly3, otherwise2. Count4 must not be treated as count3. Empty/
self-only callers retain their previous behavior and unbound residents refuse.

518 unchanged complete original calls compare ordered queries and final results,
with whole-arena, code/input, stack and register guards. Children include complete
House4E5580 (81 bytes), E1 kind509800 (6), owner6C7430 (7), mission594770 (18),
and Walk71DEA0 (10). Infantry switch data and virtual associations are pinned.
The COM interface is at Walk+4:71DEA0 reads interface+30, the existing owner's
Walk+34 raw byte. No additional locomotor state or host movement inference is used.
Existing Foot/map/registry/House/direct-permission children retain their scopes.

Cases cover zero through four other residents, reordered/self-containing lists,
mission0/5/12/25, raw moving0/1/128/255, mixed moving/stationary counts, primary/
elevated lists, allied distinct Houses including index33, speed lookup indexes and occupation
results. Actual argument-shaped input also joins direct permission before the
resident path. Its associations and neighbor fixture remain supplied; it is not
an original production constructor or full nested-original Team activation proof.
Original origin: `private/infantry-resident-20261019/fresh-a5/expected.json`.

## Actual owners and boundaries

Private diagnostic inspection identifies mover1, resident3, Cell6699 `(71,94)`,
level2, ramp0, flags3, land7, occupation4, owner6; arguments are direction-1,
level-1, previous null and consult1. All four actual Team GIs have mission12,
null destinations and stationary Walks. Admission returns0 and leaves the anchor
a Cell, allowing the existing regroup composition to complete. Source/player
isolation, cloned activation and clone survival after source destruction are
checked separately from original expectation provenance.

`PreparedInfantryWalk` binds the existing GI, mission, House, Cell, next-link,
occupation and Walk owners. Stock null transport588 and zero TypeC10/C11/C14
startup are explicitly supplied fields. Original construction/INI initialization
is not established. Nonnull transport, entered special missions/demolition,
non-Infantry residents, hostile residents, overlays and weapon queries still
refuse. Cloning a nonnull transport refuses rather than retaining a foreign
pointer. This is bounded friendly admission, not general collision/pathfinding.

`tickObjectiveTeamRecruitment()` now permits the verified initial fifth tick;
the prior diagnostic boolean and pre-fifth-tick refusal are removed. Four
recruitment ticks remain one slot per tick. Active Script execution still has its
existing pre-mutation guard. `step()` and SDL invoke none of these AI ticks.
[TEAM_COHESION_1006.md](TEAM_COHESION_1006.md)'s earlier activation refusal is
historical evidence superseded by this joined path, not erased.

Next recover entered active-Team Script advancement/target-clear and command50,
then command20's actual House/member effects. Retain the other arrival/sight,
initial scheduling and action-effect requirements in
[FIRST_DAY1_TRANSITION.md](FIRST_DAY1_TRANSITION.md). No hardcoded Team fill,
objective success, new runtime executable reads or workers.

## Reproduce

```sh
./build.command
./test.command
build/native/boot-camp-walk-check private/official-1006-probe
./run.command --boot-camp-walk
PYTHONHASHSEED=0 PYTHONDONTWRITEBYTECODE=1 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/NEW-infantry-resident.audit.json \
  tests/compare_infantry_resident.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/infantry-admission-vectors \
  --expectations private/infantry-resident-20261019/fresh-a5/expected.json \
  --report private/NEW-infantry-resident.json
PYTHONPATH=tools:tests build/tools-env/bin/python -B tests/test_infantry_resident.py
```

Use fresh private report/audit paths; substitute
`build/sanitize/infantry-admission-vectors` for sanitizer. Reuse explicitly selects
518 hits/zero misses and still runs current native. Original executable/oracle/
input/environment changes invalidate reuse; native-only changes do not. No native
pass/fail is cached. Logs, failures, prior smaller origins and costs remain under
`private/infantry-resident-20261019/`; delivery receipt is
`private/infantry-resident-receipt-a1.json`.

The old66-case permission origin is not counted: its compare_unit_admission.py
hash differs from the current transitive original dependency. Strict replay
refuses it. No old receipt is relabeled and no unchanged legacy matrix was
regenerated. The new complete caller matrix includes the actual direct-permission
then resident path. Initial sandbox JIT failure, the incorrect `header` keyword,
and the nested receipt parser-depth repair are preserved at their true scopes.
Expanded mixed/elevated coverage has a new origin; the earlier485/486 scopes stay
intact. Local verification is not independent acceptance or an original-game
observation. Only Apple Silicon macOS is tested; both games remain incomplete.

## Validation and cost

236 normal/235 ASan/UBSan CTests and36 focused Python guards pass, as do both
actual Boot Camp owner checks and the256-tick desktop SDL input/drawing check.
SDL retains right-frame6/left-frame2 and objectives disabled. Current native and
sanitizer runners each replay518 new resident +306 regroup +369 recruitment
schedule +562 readiness +202 recruitment +237 membership +330 Team admission
+291 child construction +386 Team construction +10 E1 Walk sequences:3,211 hits,
zero misses. Each native comparison runs; the excluded old66-case permission
receipt has a recorded refusal, not a cache hit.

Final original generation1.994s; current resident replay.501/2.161s; full native
build13.533s; sanitizer configure15.550s/build19.999s; owner4.646/88.549s;
CTest2.102/6.185s; Python.342s; E1 replay.942/2.546s. Other relevant audited
replays.272-.462s. Concurrent costs are nonadditive. Initial/focused and guard
repair rebuilds, desktop SDL success, manual inspection/repair and total wall
time were not instrumented. The initial guard fixture borrowed its world before
adding resident1, causing map::at; registering both owners before binding fixes
that fixture. App/owner inputs did not change during its running sanitizer check.
The initial sandbox SDL attempt has no display and is preserved; the successful
desktop attempt uses normal macOS SDL, without changing system configuration.
