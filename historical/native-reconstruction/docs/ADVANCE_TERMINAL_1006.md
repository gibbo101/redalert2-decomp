# Advance terminal Cell target and return flow

A separate, unwired terminal entry now reconstructs the control flow from base
`4A2166` through its original return. It joins actual Cell coordinates/floor,
actor Cell words, Foot/Drive/registry coordinates, mission getter and target/queue
clears. **Notification174, mission414 and postCell490 effects remain named supplied
services.** This is an interior-block proof, not complete Advance, Process,
production ownership, original mission execution or runtime Scatter acceptance.
The existing `AdvanceNearbyScatterWorld.hpp` and playable app remain unchanged,
including their nonnull-terminal-target and runtime Scatter/Advance6 refusals.

The exact supplied executable is4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage and reported no-CD provenance remain distinct;
pristine authenticity is unverified. No Windows transfer occurred: the matching
local private file already existed. No original instructions were modified.

## Recovered operations and ownership

`sim/GroundDriveTerminal.hpp` borrows the actual `UnitDestinationView`, all24
queue words and live on-map/76/7A flags. Its entry follows terminal placement,
the first head clear and track=-1/index=0. Those entry associations, residual and
scratch/register context are supplied here. It adds no movement algorithm and
does not replace the existing single movement kernel.

`assets/AdvanceTerminalWorld.hpp` borrows actual target Cell identities, actor/
Drive, registry and mutable floor state. Binding makes no queries. It composes:

- Target virtual4C =410290 -> Cell virtual48 =47BA50 -> actual floor4706C0.
- Actor virtual1A0 =41B320: full signed division by256 before word truncation.
- A separate actor virtual4C =4CA6F0, using the existing Foot coordinate kernel.
  A nonnegative registry index selects that stored word point; otherwise Drive's
  **head+40**, or the actor location when it is zero, supplies coordinates. This
  corrects the prior inspection note's overly broad generic-wrapper description.
- Wrapped signed actor-query Z minus the **late Drive destination+3C**, wrapped
  absolute value and signed comparison **strictly less than twice8529D0**. In
  particular INT_MIN remains negative after wrapped absolute value. The Cell
  target's queried Z is not the height comparison operand.
- On acceptance, destination34/38/3C clears, then conditional head40/44/48 clear
  and byte63, followed by an unconditional byte63 clear. These duplicate writes
  and this ordering differ from the preceding head clear outside this entry.
- Notify2, then live on-map/76/7A reads. An eligible accepted target invokes
  actual4CD9B0 (490 then494 clears), queue head=-1 and actual594770 current-or-
  queued mission selection. Only the head changes; tails remain retained.
- Mission2 invokes the named supplied virtual414 service with0/1. Its nonzero
  byte result returns AL1 immediately. Otherwise the result-bearing supplied
  virtual490 service runs. Nonzero returns AL1; zero re-reads on-map. Off-map
  returns AL0 without storing the residual; on-map stores it before track<=-1
  returns AL0. A supplied effect resuming a positive track is explicitly refused
  after that store, rather than silently skipping movement continuation.

Missing entered services and non-Cell targets are explicit native refusals.
Refusals retain earlier committed effects; there is no rollback claim. Borrowed
flags and mission fields remain live across services. Initial nonzero head cases
and flag mutations are diagnostic boundary inputs, not original-game observations
or evidence that the preceding terminal placement produces those states.

## Differential evidence

Canonical `private/map-depth-1006/advance-terminal-v1/` contains **202 fresh original
blocks /202 native scenarios**, including196 actual target Cell/floor/actor-Cell
queries,187 Foot queries,156 accepted height checks,149 actual target/queue clears,
21 AL1 returns and181 AL0 returns.180 paths store the residual; one AL0 path skips
it after the supplied post service changes on-map. Six entered virtual414 effects
are supplied, not actual mission execution.630 distinct original instructions
execute. All target ramps0..20, signed Cell boundaries, wrapped Z/subtraction/
absolute/threshold, current/queued mission selection, raw nonzero effect returns,
late flags, retained queue tails, duplicate driving stores and four native FP
modes are covered. Stock divisor104 was separately recovered in
[ADVANCE_CELL_SCATTER_1006.md](ADVANCE_CELL_SCATTER_1006.md); the divisor and floor
height are explicit inputs in this suite, including diagnostic boundary values.

The original block runs unchanged with actual child dispatch. Entry EAX/EBP/ESI,
local13/residual and a manufactured caller frame/saved registers are supplied.
The actual epilogue/ret4 restores that frame; this is not a full-root prologue/ABI
proof. Declared writes, whole actor/Drive/Cell/registry arena, unrelated stack,
saved registers, code/tables and input globals are guarded. Selected ordered
actor/Drive stores, query/service streams, AL return, all queue words, flags and
complete final floor-cache/plane state match. Original x87 entry remains supplied
53-bit/toward-zero. Native FP mode is preserved. Every native machine store and
FP exception flags are not compared.

Normal, ASan+UBSan and uncached guarded replays pass.1,079 Python tests,10 focused
native order/refusal checks per mode, standalone CTests,67 normal/66 sanitizer
legacy CTests, app build and `./test.command` pass. The198-record closure retains
all196 previous source/runner/expectation/receipt identities and adds two replay
records. No parent refresh is needed because no existing source was changed.
Never rerun closed finalizers or rewrite closed receipts. The app remains
`419aac6d0fbcbd33b0fe042ec57c03e508547f1fa3bc3d1971945fda1e3d2ecc`.

Original generation/comparison took0.677s/0.027s. Guarded invocation timings and
read-only inventory validation are recorded under
`private/map-depth-1006/advance-terminal-candidate/`. These measure verification
cost, not game performance. Full manual review/repair time was unmeasured. One
CTest invocation initially named a nonexistent sanitizer directory; its log is
retained separately and the actual `build/sanitize` suite passed. No behavior or
guard was weakened to pass the tests. Local verification is not independent
acceptance. Only Apple Silicon macOS is tested; no new SDL or frame-fidelity claim.

## Commands and next integration

```sh
./build.command
./run.command --owned-demo
./test.command
PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  -m unittest discover -s tests -p 'test_*.py'
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake -S tests/advance_terminal -B build/advance-terminal \
  -DCMAKE_BUILD_TYPE=Debug -DCMAKE_OSX_ARCHITECTURES=arm64
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/advance-terminal --parallel 4
build/tools-env/bin/ctest --test-dir build/advance-terminal --output-on-failure
build/advance-terminal/advance-terminal-vectors --guards
# Sanitizer: separate build/advance-terminal-sanitize with -DRA2_SANITIZE=ON.

# Fresh originals require authorized host Unicorn and NEW private destinations.
build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/map-depth-1006/terminal-NEW-audit.json \
  tests/compare_advance_terminal.py --exe private/official-1006-probe/game.exe \
  --native build/advance-terminal/advance-terminal-vectors \
  --output private/map-depth-1006/terminal-NEW
# Replay: replace --output with --expectations
# private/map-depth-1006/advance-terminal-v1/expected.json --report NEW_JSON.
# Select the sanitizer runner as needed; --uncached goes before the driver.
```

Next join this result-bearing continuation to complete Advance without duplicating
movement or silently changing the legacy void entry's scope. Preserve all173 old
commands/labels/output projections in fresh changed-source proofs at new paths.
Keep actual mission414/postCell490 recovery versus supplied services explicit;
do not infer their gameplay effects from their supplied test returns. Then join
complete Process on the same actors/Drives/map, production mutable membership,
discarded full scheduled previews/warm drawing and actual SDL displacement before
runtime Scatter/Advance6. All prior special actor/mission/bridge/pathfinder/disposal
refusals remain. No whole-game startup, original UI observation, frame fidelity or
playable displacement claim follows. Base RA2 first, then YR remain incomplete.

No new upstream source/header/generated/lifted code, dependency, extracted data or
runtime executable read is added. Existing recovered portable coordinate/floor/
mission-getter algorithms are reused. Original files, private research/evidence and
binaries remain ignored/unshipped; installations/discs/Outpost2 stay read-only.
Unicorn remains research/test-only. No workers, Windows actions/transfers,
downloads, publication, system/Xcode/DRM changes or push.
