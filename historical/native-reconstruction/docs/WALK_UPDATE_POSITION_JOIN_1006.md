# Joined Walk arrival, position and sight proof

This internal checkpoint unblocks the original Boot Camp movement lesson's live
sight integration. It executes one original root through the previously separate
Walk and Infantry position/sight chains. It does not enable Objective 1 or add a
new playable capability.

## Executed scope

The private supplied executable is 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Its embedded1.08, supplied1.006 lineage and reported no-CD provenance remain
distinct; pristine authenticity is unverified.

`tests/original_walk_update_position.py` inherits the accepted complete position
fixture without changing its source or original receipts. Its new root is
`71DFF0 -> 71E220 -> 71F196 -> 500AA0 -> 4C7220 -> 6C2B40`.
All calls execute in one guest with one actor, one Walk interface, and shared
Cell/type/House/mission/sight owners. Actual vtables dispatch the callback with
argument2. Mark0, location/Cell stores and head transfer precede the child;
head is zero and the supplied Mark has cleared actor74 at callback entry.

Forty-eight complete roots cover planar arrival distances0/1/16, sight initially
active/inactive, permission flag32D initially enabled/disabled, and four late-byte
profiles. The ordinary profile preserves `(7D,76,7A)=(1,0,0)`. Three explicitly
supplied **post-child diagnostic mutations** select off-map7D=0, byte76=255 or
byte7A=128. They are not claimed as original child effects or gameplay observations.
Instruction observations verify the late-read prefixes at71F19F/71F1AA/71F1B5;
only ordinary returns reach the final Mark1. Diagnostic returns skip it.

Each root executes the complete Commence594C50, sight removal6D5E90, sight
addition6D5C30 and post-sight54A550. Totals include144 complete current-Cell
getters,432 full-coordinate map lookups,48 target center/floor chains,48 complete
position/tail/selector/cloak-zero-mask/dirty-overlay-exit chains and13,776 supplied
mask plus13,776 supplied redraw calls. Reveal54A110 remains a supplied leaf
(36 calls). Mark, occupation, floor, initial empty resident lists, associations
and initialization remain supplied. This does not prove their original mutation
implementations or initial-world construction.

The native runner invokes the same `processSelectedWalk` movement kernel with
the complete `updateInfantryPositionE1WithEffects` composition as its synchronous
notification service. It reuses the existing child fixture through an optional
caller seam. Its child and movement share the actual `ActorGroundState::position`
and on-map byte; no second movement algorithm or copied callback actor is used.
All child query/result traces, final movement/flags, all24 queue words, callback
count and ordered Mark/release/occupy/child/return events match the original.
Original late instruction observations are checked independently; the native
runner does not pretend to execute original instruction addresses.

The bounded scene ends at `(15040,22976,208)`, Cell58,89, with actual Cell target
59,89. Interpolation at distance17+, next-subcell preparation, general terrain,
nonnull combat targets, nonzero cloak/resident dirty effects and frame scheduling
are outside this new fixture. Existing separate movement proofs retain their
scope. All nonmutable shared-arena bytes, inspected Walk code/tables, declared
child inputs, caller stack and preserved registers are audited.

## Receipts and costs

Canonical originals: `private/boot-camp-20261018/walk-position-join-fresh-a3/`.
Expectation SHA256:
`29a53b5b70ebdc6e61d6c213add8bbe086836808fc8b34dae12f590abdadf31a`.
Normal/sanitizer/uncached reports and audits use
`private/boot-camp-20261018/walk-position-join-{normal,sanitize,uncached}-a3.*`.
All48 roots pass each replay. Generation took3.93s, fresh driver4.57s;
normal/sanitizer/uncached replays took0.50/0.67/7.01s. Native comparisons alone
took0.010/0.178/0.010s. Uncached inspection is the dominant replay overhead.
Original outputs are reused explicitly; native outputs are always rerun.

The affected standalone child runner retains all80 original outputs on both
normal and sanitizer replays at `walk-position-join-parent-{normal,sanitize}-a1`.
No old original matrix was regenerated. Full application and sanitizer builds
pass;113 normal CTests,112 sanitizer CTests and1,345 Python tests pass. Measured
suite times were2.58s/8.68s/32.82s. Both private-data Boot Camp owner checks pass.
Build and manual review/repair wall costs were not instrumented.

Attempt a1 exposed a native trace newline error and a missing fresh receipt-mode
field. Those attempts remain diagnostic; no receipt was edited or relabeled.
a2 passed before final fixture-domain tightening; a3 freshly executes the changed
original source and is canonical. No independent acceptance is claimed.

## Reproduce

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
./test.command

env PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/walk-position-next.audit.json \
  tests/compare_walk_update_position.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/walk-update-position-vectors \
  --render-data private/derived/ra2-1006/render-data.bin \
  --raster-data private/derived/ra2-1006/raster-data.bin \
  --direction-data private/derived/ra2-1006/direction-data.bin \
  --expectations private/boot-camp-20261018/walk-position-join-fresh-a3/expected.json \
  --report private/walk-position-next.json

./run.command --boot-camp-walk
```

Choose fresh audit/report paths. For sanitizer replay use
`build/sanitize/walk-update-position-vectors`; for the inspection control add
`--uncached` before the driver. Fresh original execution uses `--output` with a
new private directory instead of `--expectations/--report` and requires Unicorn's
JIT permission. Receipts guard executable, original-source/environment/input,
prepared-data and native-source/runner identities. Do not bypass invalidation.

## Next integration and runtime limits

`BootCampWalkWorld` still installs a no-op arrival notification. Its existing
scheduled disposable preview and prior106-tick SDL acceptance remain the runtime
baseline; this change edits test/build support only and performs no new SDL
acceptance. Objective1 remains disabled. No Windows actions, downloads or new
runtime executable reads were made.

Next bind the complete composition to persistent production actor/sight/mission
owners, review the current preview's per-call `SuppliedState` and its Cell-value,
kind1/kind2 and locomotor boundaries, and test repeated arrivals/Stop/refusals on
those same owners. Preserve state that must survive callbacks instead of silently
resetting it on each call. Then validate ordinary SDL sight/discovery and required
mission child effects before claiming the actual first objective transition.
Do not synthesize success from arrival or recorded action requests. This joined
proof closes the original caller-execution gap; it does not close live ownership,
mission effects, drawing, or whole-game fidelity.
