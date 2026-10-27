# Cell resident snapshot and Scatter dispatch

Current structural-view refresh is `cell-scatter-v5`: all 998 original commands,
labels and outputs remain identical to v1, with all three replays. The later
[Cell-to-Unit join](CELL_UNIT_SCATTER_WORLD_1006.md) executes actual Unit Scatter
separately; the supplied member boundary described below belongs to this parent
proof. Current status and remaining runtime gates are in HANDOFF.

`scatterCellResidents` recovers the complete Cell snapshot/dispatch root and
its Techno cast, promotion predicates, ability3 and Unit/Building type children.
It is **unwired**. Member Scatter, vector growth and heap disposal remain named
supplied services. No Unit Scatter, Advance6, Process/world integration or new
SDL capability is established here. Existing Advance6/scatter refusals remain.
Base RA2 first, then Yuri's Revenge remain incomplete.

## Exact target and behavior

The private supplied executable is 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 lineage and reported no-CD provenance remain distinct;
pristine authenticity is unverified. Addresses apply only to this target.
No runtime executable-read expansion, external code or dependency is introduced.
The existing reference/license boundaries in [REFERENCES.md](REFERENCES.md) apply.

The complete Cell root is `476920..476ABC`, including final `ret 10h` at 476ABA.
Original Unit vtable `7ADDF8+15C` points to 7072D0; that Unit body is inspected
only and remains unexecuted by this suite. Do not replace it with a successful
no-op to enable Advance6.

Preserve these decisions and ordering:

- Select the primary head at Cell+E4 or elevated head at +E8, including the initial
  load when the elite prepass is skipped. Reload that selected head before the
  separate snapshot traversal. Next is member+30.
- When ignoreDestination is zero, the prepass stops at the first actual Techno
  whose veterancy is at least 2. The result is cached before callbacks.
  The actual cast table recognizes kinds 1/2/6/15; execution here uses Unit1,
  Building6 and null-cast Terrain36. Kinds 2/15 remain table inspection only.
- Grow capacity by ten, interpreting only AL of the supplied growth result.
  Failed growth skips that member's store but still reads its live Next. Retain
  the snapshot across later callbacks that mutate live heads or Next links.
- Every dispatch candidate still executes the actual cast. Cached elite,
  ignoreDestination or rules+1431 bypass the remaining eligibility checks.
  Otherwise require Techno, then ability3 or signed House+194 >= rules+10B4.
  ignoreMission does not supply that bypass; both control bytes are forwarded
  independently and unchanged to the member callback.
- Veteran means 1 <= value < 2; elite means value >= 2. Unordered comparisons are
  false. Ability3 preserves repeated veteran/elite/type queries and the actual
  veteran/elite type bytes, including inherited veteran ability for elites.
- Borrow the same coordinate object through every callback. Later supplied
  coordinate mutation is visible. Dispose retained owned guest storage after
  dispatch. Native storage uses ordinary C++ vectors; allocator internals and
  allocation-failure parity are not claimed.

Native missing-service/association and cycle guards are safety refusals, not
recovered original error behavior. The public standalone runner bounds lists to
32 members, types/Houses to two each and kinds to 1/6/36.

## Evidence and limits

Canonical evidence is `private/map-depth-1006/cell-scatter-v1/`:
**998 fresh complete Cell calls**, with normal, ASan+UBSan and uncached replays.
All **2,492 selected snapshot stores** and logged queries/callbacks/native final
logical state match. Actual execution covers 241 distinct original instructions;
all 11 declared root/child entries execute. Ability3 returns false 248 / true 78;
veteran false 286 / true 144; elite false 1,804 / true 136. The root is void: no EAX
return-value parity is claimed.

The original harness preserves unchanged code/input/dispatch ranges, caller
stack/registers/canaries and whole Cell/member/type/House/rules/heap arenas.
Only the selected snapshot instructions may write the guest heap. Heap growth
40CD40, disposal 781D3B and member+15C callbacks remain explicit services:
1,348 growth, 852 release and 2,268 member calls. Their implementation, member
movement/mission/pathfinder effects and initial associations are supplied.

Coverage includes raw control bytes, separate layer lists, promotion boundaries
and NaN, signed House thresholds, 0..32-member snapshots, growth failures and full
returns whose AL differs, borrowed signed coordinates, and seeded heterogeneous
ordered lists. Diagnostic service mutations clear lists, change late rules/type/
House/veterancy inputs, cut Next during growth, alter the coordinate, or promote
a member after prepass to reach late elite ability. These are supplied experiments
that establish ordering, not original-game observations or recovered promotion.

The earlier 168 replay records retain exact source/runner/receipt/expectation
identities. Adding the normal/sanitizer records gives 170. The application remains
byte-identical to the preceding accepted build, SHA256
`419aac6d0fbcbd33b0fe042ec57c03e508547f1fa3bc3d1971945fda1e3d2ecc`.
No new SDL acceptance is claimed. 985 Python tests, 67 normal/66 sanitizer legacy
CTests and `./test.command` pass. Both new standalone builds pass.
This nested vector runner must be compared separately; it is not a registered
CTest in the application build graph. Only Apple Silicon macOS is tested;
local verification is not independent acceptance.

Original generation took 1.499s and native comparison 0.060s. Guarded wrapper
times were 8.261s fresh, 4.692s normal, 4.843s sanitizer and 4.783s uncached.
These are verification costs, not game performance or a controlled speedup.
Full repair/manual-review time was not measured. A wrong verifier address, an
incorrect late control-argument association and bypassed ability fixtures were
caught before closure; failures/repairs remain private and are not final proof.

## Reproduce and try

```sh
./build.command
./run.command --owned-demo
# Existing two-Rhino movement; Advance6/scatter still refused.
./test.command
PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  -m unittest discover -s tests -p 'test_*.py'

env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake -S tests/cell_scatter -B build/cell-scatter \
  -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_OSX_ARCHITECTURES=arm64
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/cell-scatter --parallel 6
# Sanitizer: build/cell-scatter-sanitize, Debug and -DRA2_SANITIZE=ON.

# Fresh original execution requires the authorized host Unicorn JIT context.
# Always use new private output/audit paths.
PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/map-depth-1006/cell-scatter-new-audit.json \
  tests/compare_cell_scatter.py --exe private/official-1006-probe/game.exe \
  --native build/cell-scatter/cell-scatter-vectors \
  --output private/map-depth-1006/cell-scatter-new

PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/map-depth-1006/cell-scatter-try-audit.json \
  tests/compare_cell_scatter.py --exe private/official-1006-probe/game.exe \
  --native build/cell-scatter/cell-scatter-vectors \
  --expectations private/map-depth-1006/cell-scatter-v1/expected.json \
  --report private/map-depth-1006/cell-scatter-try.json
# Use the sanitizer runner for its replay; --uncached before the driver supplies
# an inspection-reuse control. Never rerun closed finalizers.
```

Next recover actual Unit Scatter and its required locomotor/mission/RNG/neighbor
admission dependencies, then enclosing Advance6/Process and shared owned-world,
preview/drawing/SDL joins. General pathfinding, combat, economy, AI, campaigns,
multiplayer, audio, original saves and YR remain open. Initial construction,
controls/routes/clearance/scheduling remain supplied. No full-frame/startup or
whole-game fidelity follows. Private originals/assets/research/results/binaries
stay ignored and are not shipped. Source installations/discs and outpost2 stay
read-only; no workers, Windows actions/transfers, downloads, publication or
system/Xcode/DRM changes occur.
