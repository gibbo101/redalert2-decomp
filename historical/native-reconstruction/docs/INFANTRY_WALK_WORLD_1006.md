# Infantry Walk on shared production owners

This joins a movement dependency for Boot Camp Day 1's first lesson.
`PreparedInfantryWalk` connects the existing ordinary Infantry/Foot commands and
complete queued Walk Process to the same actual actor, map, Cell, membership,
occupation, admission and floor owners. **Boot Camp remains static.** Real E1
inputs, animation/drawing, encountered unsupported movement children and ordinary
SDL walking remain to integrate. Discovery/scheduler/actions still precede the
first objective; this internal checkpoint is not a playable lesson.

## Ownership and recovered scope

The supplied base executable was freshly checked before using addresses:
4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity are distinct. Existing independently recovered base
algorithms are composed; no public/header/generated/lifted game code, new
dependency, extracted table or application executable read is incorporated.

`InfantryWalkState` owns actual Foot/Object/Facing/Walk fields, all24 route words,
independent retry/wait records, target and interface references. The House owner
is stored once beside the mission fields. The caller also owns type, House,
foundation, clock/globals, RNG and numeric inputs. `PreparedInfantryWalk` owns
associations and callbacks only, borrowing the existing `MutableUnitMap` and one
extra Cell span for heads/occupation/House/registry fields. It is immovable; all
borrowed owners and backing storage must remain stable and outlive it. A clone
must bind fresh callbacks and actor/Cell references. Construction performs no
map/floor/numeric queries and does not warm lazy state.

The composition shares the existing kernels for:

- Infantry501CE0 -> Foot4C8030 -> Walk Move_To/Stop, target/interface ownership,
  only-head route clears and original timer/padding stores.
- Complete Process71DFF0 -> Movement_AI71E220, retry/refill, live Infantry503190
  admission and508980 speed, head71F590 release/selection/claim, interpolation,
  crossing and arrival with the actual null Infantry command.
- Foot Mark4C2E60, map54AB70/54AF70, Cell473B30/473D20 and distinct Infantry
  foundation50A000. Both Cell parents skip Infantry occupation/eligibility;
  Walk head transfer owns the separate subcell claims.
- Coordinate548000, word548070, map floor55A280 and Cell floor4706C0 over the
  same mutable Cells,100 prepared plane doubles, shared fallback and lazy cache.
  Actual fallback stores are observed after each write without another lookup.

Preserved details include raw movement/bridge/late arrival bytes, actor76 shared
between Mark and arrival, signed levels/division, staged original math, Facing
clock, all queue tails, low-byte occupation with retained upper bytes, House
slots, repeated lookups and ordered selected stores. Bridge fixtures supply
coherent actor bridge79, height and Cell flags0x300. The earlier ground-on-0x100
fixture correctly entered an unsupported admission continuation in both engines;
its failed audit is retained. No refusal was relaxed to make the proof pass.

Named route4C3000, target coordinates410290, visibility568140/5683C0,
notification6C2440/500AA0, recalculation472540, dirty47BB30, animation504740,
atexit and atomic service effects remain supplied. Initial startup/type/House/
scenario associations, caller scratch and RNG seeding are supplied. Route service
writes the actual24-word queue; it is not recovered pathfinding. Notification
mutations diagnose late reads, not observed gameplay. Moving/non-null retarget48C,
failed routes, special8, entered nonzero admission, other residents, overlays,
JumpJet and earlier entered-child exclusions remain explicit refusals. Low-level
service faults retain preceding writes; no transactional rollback is claimed.

## Evidence and validation

Canonical original-only expectations and receipt:
`private/infantry-walk-20261018/world-fresh-a2/{expected,report}.json`.
**92 sequences /4,061 complete original roots** include3 initializers,
3,776 Process roots and282 initial Mark/occupation/order/explicit Stop roots.
Actual nested children include109 admission/head selections,1,047 speed calls,
537 Marks,308/220 map and Cell insertions/removals,124 dirty effects and103
arrival notifications. There are33,860 selected stores. All80 ordinary journeys
clear their target; six Stop cases retain then finish committed heads. Six late
notification cases retain their targets and skip the final Mark as recovered.
All eight directions, speeds16/32/64, two-Cell journeys, signed levels, coherent
bridges, subcell starts, full RNG, queue tails and floor/fallback digest are covered.

Original instructions execute unchanged. Inspected code/table identity, ABI,
callee-saved registers, stack, exact allowed writes, remaining actor/Cell arena
and map slots are guarded. This is an ordered selected-store/state comparison,
not an exhaustive read trace or whole-game/frame proof. Original answers are
saved before native comparison and their provenance remains separate from
current native sources/runner identity.

`world-replay-{normal,sanitize,uncached}-a3.json` each report92 reuse hits,
zero misses and zero original execution. Current C++ executes every replay;
no native result cache is used. `--uncached` disables inspection reuse only.
Two native diagnostic repairs (raw byte output and missing fallback-store events)
used the saved originals, without regeneration. Fresh a2's original receipt is
valid; its first native comparison/audit correctly failed and remains preserved.

`prepared-infantry-walk-check` verifies cold binding, two distinct actor/Walk/
queue/timer owners, shared Cell and live House owners, command/Stop behavior,
independent clone bindings, foreign/aliased/split-owner refusals and retained
writes on entered nonzero admission. Its deliberately supplied numeric helper
is used only for ownership checks, never as fidelity evidence. Rebuilt normal/
sanitizer membership replays retain285 sequences /501 roots with zero originals.
Fourteen focused CTests per build and109 Python tests pass. No broad capability
closure or new SDL run is claimed; application behavior is unchanged. Local
verification is not independent acceptance. The prior attachment retry remains
completed in `private/boot-camp-20261018/sdl-observations.json`.

Measured a2 original generation15.115s. Final normal/sanitizer/uncached driver
replays0.605s/2.467s/4.240s (native0.043s/1.832s/0.045s); membership0.450s/5.282s.
Concurrent execution makes costs nonadditive. Focused CTest bodies0.23s/1.02s;
Python109-test body2.016s. Timed grouped rebuilds15.05s/16.36s include successful
runner builds then a new-target discovery failure after CMake regeneration;
the subsequent new-check builds took1.84s/1.79s. Earlier failed builds used a
wrong reader argument/Facing aggregate and had a multichar output literal; the
corrected builds passed. Other build, manual inspection/repair and total task
wall costs are unavailable. The first original fixture failure took8.599s and
produced no expectations. Private `world-validation.json` retains costs,
identities and failed-attempt scopes. No cache framework was added. The wrapper
now explicitly guards the existing `--map-data` input; its mutation test passes.

## Reproduce and continue

```sh
./build.command
./test.command
./run.command --boot-camp-preview # Static checkpoint; walking still refused.

# Focused checks after CMake has configured the new targets.
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/native --parallel 6 \
  --target infantry-walk-world-vectors prepared-infantry-walk-check infantry-membership-vectors
build/native/prepared-infantry-walk-check
env PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_infantry_walk_world test_infantry_membership test_inspection_reuse

# New private audit/report names; executes current native, zero originals.
env DEVELOPER_DIR=/Library/Developer/CommandLineTools PYTHONHASHSEED=0 \
  PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/infantry-walk-world-next.audit.json tests/compare_infantry_walk_world.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/infantry-walk-world-vectors \
  --render-data private/derived/ra2-1006/render-data.bin \
  --raster-data private/derived/ra2-1006/raster-data.bin \
  --direction-data private/derived/ra2-1006/direction-data.bin \
  --subcell-data private/derived/ra2-1006/infantry-subcell-data.bin \
  --map-data private/derived/ra2-1006/map-runtime-data.bin \
  --expectations private/infantry-walk-20261018/world-fresh-a2/expected.json \
  --report private/infantry-walk-world-next.json
# Sanitizer: substitute build/sanitize/infantry-walk-world-vectors and new paths.
# Uncached control: add --uncached before --audit; originals still reused.
# Fresh original proof only when its dependencies change: omit expectations/report,
# use --output private/infantry-walk-world-new-fresh and a new audit path, in the
# authorized read-only Mac-host JIT research context. Never run originals in app.
```

Next bind real E1 inputs and the existing Boot Camp scene to these owners,
recover encountered retarget/route-failure children, and join animation/drawing
and ordinary SDL walking. Then recover actual discovery, scheduling and actions
for the first objective. Keep original setup/scheduler and supplied controls/
routing/presentation distinctions explicit. Retain two-tank regressions. No
workers, Windows actions, new dependencies or runtime executable reads. Full-game
goal stays active; base RA2/YR remain incomplete. Only Apple Silicon macOS is tested.
