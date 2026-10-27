# Scenario waypoint getter and reveal caller

Complete base663180 now has a readable SDL-free implementation in
`src/sim/ScenarioWaypoint.hpp`. A separate original proof joins that actual
getter to complete6B0670. The production action17 child remains recording-only;
no live terrain reveal, mission progression or runtime executable read is enabled.

## Recovered behavior and host view

663180 reads a packed dword at scenario+632+index*4, writes it to the supplied
output address and returns that exact address. Index arithmetic wraps32 bits;
there is no original waypoint-count bounds check. The source is unaligned.
The full source dword is read before the output store, including when output
partially overlaps source. Packed X/Y remain signed16-bit values.

The native byte-span view bounds supplied records and refuses unsupported
addresses/output sizes. It preserves wrapped byte offsets and little-endian
values, including negative indexes whose resulting offsets are in supplied
storage and high-bit indexes that wrap back to that storage. It does not impose
an invented positive waypoint-index check. Read-before-write is retained for
partial aliases. Native bytes do not claim original atomic/fault/concurrent-store
parity. `scenarioWaypoint` is the authored packed-word-to-Cell convenience adapter.
Scenario construction, map INI loading and actual startup associations remain
separate; this dependency does not prepare a new runtime scenario owner.

The joined caller uses the single prior `revealMissionWaypoint` kernel and the
new getter on supplied scenario bytes. The three548070 lookups/flags/level and
54A110 effects retain the supplied scope from
[MISSION_WAYPOINT_REVEAL_1006.md](MISSION_WAYPOINT_REVEAL_1006.md). Its disabled
House early return, signed height/wrapped center/Z, repeated query order and late
global reloads retain their original projections. The old separate proof's
supplied waypoint-pointer profile remains unchanged; no receipt was relabeled.

## Exact-original evidence

Supplied target4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD and unverified pristine
authenticity remain distinct. `verify_scenario_waypoint.py` composes the exact
399-byte caller verifier and pins all five getter instructions663180..663193.
Unmodified originals execute only in research/test Unicorn. No public/YR/recomp
code, dependency, extracted tracked data or executable-read expansion was added.

Fresh canonical expectations:
`private/boot-camp-20261018/waypoint-lookup-fresh-a1/expected.json`, SHA256
`063da9f335dbe63080bf4bcadf971f6e30598b44000a250c587136c342482fb4`.
All1,374 sequences match:40 complete direct getters and1,334 complete reveal
callers, including1,119 actual getter calls,2,725 supplied Cell queries and2,158
supplied reveal calls. Direct tests cover wrapped indexes and source-equal,
source-minus1/source-plus1/source-plus3 and separate outputs. They compare the
returned pointer normalized to the same owner and the entire4KiB backing, not
just the requested packed word. Their final R1 token is fixture success; D carries
the actual returned pointer offset. Joined cases retain all prior1,327 inputs
and add seven explicit signed/wrapping indexes. Disabled cases do not enter getter.

Original code/arena/caller stack/return/callee-saved guards remain active. Direct
getter calls permit only the four output bytes and compare all unrelated arena
bytes; no instruction is patched or replaced. The joined fixture executes all
five getter instructions and verifies the actual scratch output through the
complete caller. Named map/reveal callbacks and diagnostic late mutations remain
supplied. This is routine evidence, not original-game observation or independent
acceptance. Unsupported addresses/fault paths remain outside the native domain.

Both full builds pass. All132 normal/131 sanitizer CTests pass in1.69s/13.60s;
all1,419 Python tests pass in30.368s. The new Python guards cover input/binary,
scenario/alias inventory and receipt scope/trace/changed-original rejection.
An initial fixture-only tamper test targeted a disabled case with already-identical
R1; it was corrected to tamper a direct getter row before final checks/proofs.
No implementation change or failed original comparison was required.

New1,374-case and prior1,327-case proofs each retain normal/sanitizer/uncached
replay hits with zero misses.29 prior application/runners/checks remain hash-
identical, retaining closed original/owner/SDL scopes. No SDL/private-data check
or closed finalizer was rerun for this unwired dependency. Fresh original0.547s,
fresh driver1.363s. Exact commands/hashes/replay costs are in
`waypoint-lookup-receipt-a1.json` and `waypoint-lookup-replay-commands-a1.json`.
Build/repair/review/approval/tool-dispatch costs were not separately measured.
No new cache was added; existing inspection and receipt guards remain unchanged.

## Commands and next integration

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
./test.command
DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

env PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/waypoint-lookup-next.audit.json \
  tests/compare_mission_waypoint_lookup.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/mission-waypoint-lookup-vectors \
  --expectations private/boot-camp-20261018/waypoint-lookup-fresh-a1/expected.json \
  --report private/waypoint-lookup-next.json
```

Use new audit/report paths. Sanitizer selects its runner; uncached control puts
`--uncached` before the driver. Fresh original generation replaces expectations/
report with `--output private/NEW-DIRECTORY` and requires Unicorn JIT access.
The canonical fresh comparison used the settled sanitizer runner; both native
runners subsequently replay against the same original expectations.

Next join existing actual reveal-area/visibility kernels to this caller on shared
map/House/scenario owners, then production action17 and full warm preview
isolation. Team creation/alliance/audio effects and ordinary arrival/discovery
remain separate gates before live Objective1 acceptance. Both games incomplete;
goal active. No workers/Windows actions/transfers/downloads/system/DRM changes.
