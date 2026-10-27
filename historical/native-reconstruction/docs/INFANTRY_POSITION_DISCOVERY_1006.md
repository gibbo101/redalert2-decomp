# Infantry revealed-Cell position discovery — supplied base target

The bounded complete `4C7220 -> 6C2B40` position-effects composition now reaches
existing `discoverUnit` through the actual Infantry dispatch. This closes the
revealed-Cell child gap; it does not enable live arrival, sight or Objective1.

## Identity and recovered ordering

Target: `private/official-1006-probe/game.exe`, 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage and reported no-CD provenance are distinct;
pristine authenticity remains unverified. Original instructions are unchanged.

`tools/verify_infantry_position_discovery.py` reuses the complete parent and
[Unit discovery](UNIT_DISCOVERY_1006.md) inspections, independently checks Infantry
vtable `7A3540` slots `180 -> 6C2440`, `16C -> 594770`, `1D0 -> 594CB0`, and pins
these caller operations:

- `6C2BF0` reads actor373 after the possible active32D store.
- Nonzero373 jumps directly to `6C2C22`, skipping the first map lookup.
- Otherwise `548070` at `6C2C04` gets the Cell; `6C2C09` tests byte12C bit0x10.
- Only if set does `6C2C12` read current player HouseA35DB4 and dispatch slot180.
- Both paths then perform a separate late `548070` at `6C2C2C` and dirty47BB30.

The native kernel preserves this order with an optional discovery service. A
missing service is refused only when dispatch is entered. Already-discovered
actors still dirty the Cell and need no discovery service or first tail lookup.
The vector composition borrows `UnitDiscoveryActor.current373` directly for the
position actor, with the same discovery actor/type/House/mission graph used by
its child. No second discovery algorithm was added.

Actual complete Techno6C2440, Object5D4230, House4F52F0, Mission594770 and
QueueMission594CB0 execute in the original guest. For the current House, discovery
sets actor373, owner5668/5669, then owner13C when actor372 is zero. An uncontrolled
House with Mission14 queues15 and clears queuedA4. Null actor34 supplies coherent
null Tag state; no Tag effect is entered. This tests the Infantry association
independently of the earlier Unit-vtable proof.

## Evidence and regression scope

Canonical original-only expectations:
`private/boot-camp-20261018/position-discovery-fresh-a3/expected.json`, SHA256
`865f0eb8c9c12b166dbf8ef488d6bfc6bd8d43364667456707f39930c74f3d86`.
All360 complete4C7220 roots match native. They contain180 complete6C2B40 tails,
36 complete discovery entries,6 complete QueueMission calls and780 actual map
lookups. Cases vary on-map, unrelated/revealed12C bits, raw zero/nonzero373,
Mission2/14/19, human control and raw actor372. Preset discovered bytes exercise
late skip behavior; this is not a consecutive-arrival original proof.

Normal/sanitizer/uncached-inspection replays each retain360 hits and zero misses.
Receipts are `position-discovery-{normal,sanitize,uncached}-a1.json` under
`private/boot-camp-20261018/`. Rebuilt normal/sanitizer runners also retain all80
old position-effects,80 joined sight-parent and48 joined Walk roots using their
unchanged original expectations, without regenerating originals.

Full normal/sanitizer builds pass;114 normal CTests,113 sanitizer CTests and
1,349 Python tests pass. Both private-data Boot Camp owner checks pass. Fresh
host-display SDL input/drawing/pause/refusal/Stop/repeated-order/deselection
acceptance runs106 ticks at `position-discovery-sdl-a1/`; arrival drawing was
visually inspected. Its report explicitly retains `objectives_enabled:false`
and `original_fidelity_from_this_smoke:false`. This is local verification, not
independent acceptance or original-game observation.

Fresh original generation took0.407s; full fresh driver1.142s. Normal/sanitizer/
uncached replay drivers took0.702/0.814/3.739s, comparisons alone0.008/0.067/0.006s.
Concurrent CTest runs took3.24s normal and8.96s sanitizer; Python suite29.75s.
Build/SDL/manual-edit wall cost was not separately instrumented. Failed a1 had a
missing test-source path before execution; a2 passed but predates explicit caller
instruction guards. Neither is the canonical receipt. No closed finalizer ran.

## Commands and remaining integration

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
./test.command

env PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/position-discovery-next.audit.json \
  tests/compare_infantry_position_discovery.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/infantry-position-effects-e1-vectors \
  --expectations private/boot-camp-20261018/position-discovery-fresh-a3/expected.json \
  --report private/position-discovery-next.json

./run.command --boot-camp-walk
```

Use a fresh audit/report path, sanitizer runner for sanitizer replay, or
`--uncached` before the driver for inspection control. Fresh original execution
uses `--output private/NEW-DIRECTORY` instead of expectations/report and requires
private Unicorn JIT permission. Retain all source/input/runner/receipt guards.

Next bind actual shared Cell12C/140 and House state across Walk, visibility and
mission owners, including actor34/Tag presence and actual actor373. The disposable
position preview still supplies zero12C and live arrival remains disabled.
Membership visibility predicates must borrow actual fields instead of constant
visible callbacks before claiming live fog. Validate discarded-preview isolation,
repeated arrival, full entered caller effects and ordinary SDL discovery before
runtime adoption. Mission action requests alone are not completed effects.

Initial records/associations, null Tag, direct route, controls, schedule and
presentation remain supplied. No public/YR/recomp code or behavior was used for
this join; no new dependency or runtime executable read was added. Private inputs,
receipts and images remain ignored; source installations remain untouched.
