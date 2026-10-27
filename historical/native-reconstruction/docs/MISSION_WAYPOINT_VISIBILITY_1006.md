# Waypoint reveal through Cell visibility changes and masks

Separate `MissionWaypointVisibility.hpp` now composes complete6B0670/663180/
548070/54A110 with actual62FCA0/499FC0, both counter children and6A8D40 masks.
It borrows one Cell table/fallback throughout. All96 original sequences match.
Redraw6AADD0, discovery568520 and refresh47BE00 remain supplied diagnostic
callbacks; production action17 is still recording-only. No live objective claim.

## Shared records and exact ordering

The composition reuses the existing recovered kernels; it does not copy Cells or
maintain separate visibility counters. The fixed-map table alias from
[MISSION_WAYPOINT_AREA_1006.md](MISSION_WAYPOINT_AREA_1006.md) remains enforced.
Map queries are distinguished as P for the waypoint caller, C/G for reveal-area,
V for visibility change and M for mask queries. Fallback stores forward immediately
through the same owner and observer, including mask neighbors overwriting its
point before later discovery. A later discovery join must read the actual Cell
point by identity, not substitute a saved candidate.

The first reveal pass's final argument0 selects actual decrement47C840; the
second's argument1 selects actual increment47C8A0. Preserve counter wrap/clamp,
ordered low-byte/full-word flag updates, primary then secondary mask queries,
signed table values truncated to bytes, notification/redraw/discovery order and
post-service flag rereads. Both passes and repeated offset aliases see earlier
writes. The legacy zero-only facade retains its prior refusal.

Initial scenario, House views, ranges/height scales, spread arrays, signed mask
result table, counters/maximums/mask bytes/flags and raw refresh-rule input remain
supplied. The original fixture explicitly associates83996C with fixed8324E0;
its scenario A3D290 also supplies waypoint bytes and the first dword consumed by
the late refresh-bit test. This is not recovered startup or a new interpretation
of that first dword. Native refreshRules is a supplied snapshot matching that
dword. Diagnostic leaf callbacks only record; late changes to this dword or
other global associations during real discovery are not verified here.

## Exact-original proof

Supplied target4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD and unverified pristine
authenticity remain distinct. The verifier composes the existing exact-base
waypoint/area/Cell-change/mask inspections, preserving numeric code and fixed-
map associations. Unmodified original instructions execute only in research
Unicorn, never in the application. No public/YR/recomp code, new dependency or
runtime executable-read expansion was added.

Canonical expectations:
`private/boot-camp-20261018/waypoint-visibility-fresh-a2/expected.json`, SHA256
`99b28b8615025dd8589872901e880215efd2c8f1494cb88a5a80c53ac885b8e4`.
96 roots comprise72 ordinary and24 disabled calls, executing72 waypoint getters,
171,338 map getters,144 reveal-area calls,9,550 wrapper/Cell-change calls,
4,775 decrements,4,775 increments and19,100 actual masks. Numeric children retain
288 height projections,12,856 table square roots and13,144 FTOL calls. Diagnostic
leaves record1,604 redraws,1,604 discovery requests and16 refreshes.

Every root compares ordered lookup/fallback/numeric/counter/flag/mask-byte/effect
traces and complete mutable projection for all17 aliased Cells/fallback: flags140,
flags12C, counter130 and primary/secondary bytes. Original caller stack/return/
callee-saved/code/table/global/arena guards permit only named Cell stores and
fallback-coordinate stores; maximums, level bytes and unrelated arena/padding stay
exact. Synthetic result tables are guarded supplied startup inputs, not copied
original tables in Git. Counters include signed extremes and negative maxima;
upper flag bytes, holes, fallback reuse and all original parent scenarios remain
covered. This is isolated routine evidence, not an original-game observation or
whole-frame/whole-mission fidelity. Local verification is not independent acceptance.

A1 remains a failed trace comparison: the oracle read mask mode from its consumed
stack argument at return, after original scratch reuse changed that slot. A2
captures mode at entry. The mask result and native recovered algorithms were not
changed to match the bad trace. Both receipts remain private and distinct.

Final native fixture guards additionally bound synthetic seeds/coordinates before
host array arithmetic. These guards are not new game constraints or original
fault parity. No original behavior changed; rebuilt final runners reuse A2 through
new a3 reports with explicit current source/runner identities. Earlier reports
retain their original identities; none are relabeled.

## Verification, cost and remaining gates

Both full builds and final new-target builds pass. Final134 normal/133 sanitizer
CTests pass in2.30s/7.60s. All1,425 Python tests pass in30.270s; the three affected
Python guards also pass after the oracle trace repair. Normal/sanitizer/
uncached final replays each retain96 hits/zero misses.35 previously tracked app/
runner/check binaries are hash-identical, retaining their closed owner/original/
106-tick SDL baseline scopes. This unwired dependency does not warrant rerunning
those closed finalizers/private-data/SDL checks. Live objectives remain disabled;
existing injected-clone objective text remains diagnostic only.

A2 original generation33.074s, driver33.816s, native comparison0.164s. Failed A1
original generation34.950s is retained as repair cost. Exact final replay commands,
source/runner hashes and other measured costs are in
`waypoint-visibility-replay-commands-a3.json` and
`waypoint-visibility-receipt-a3.json`. Build/review/approval/GUI/tool-dispatch and
non-execution repair costs were not separately measured. No new cache; immutable
inspection/original-expectation guards remain unchanged. Cached replays never
execute originals and are explicitly labeled as such.

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
./test.command
DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

env PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/waypoint-visibility-next.audit.json \
  tests/compare_mission_waypoint_visibility.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/mission-waypoint-visibility-vectors \
  --expectations private/boot-camp-20261018/waypoint-visibility-fresh-a2/expected.json \
  --report private/waypoint-visibility-next.json
```

Use new audit/report paths; sanitizer selects its runner and uncached control puts
`--uncached` before the driver. Fresh original replaces expectations/report with
`--output private/NEW-DIRECTORY` and requires local Unicorn JIT access.
`./run.command --boot-camp-walk` retains the current movement checkpoint.

Next join actual568520/resident/DiscoveredBy effects on the same Cell/House owners,
then production action17 and full warm discarded-preview isolation. Redraw/refresh
internals and original startup remain separate scopes. Ordinary live arrival,
clock-before-producers, Team creation/alliance/audio and Objective1 acceptance
remain open. Both games incomplete; goal active. No workers/Windows actions/
transfers/downloads/system/Xcode/DRM changes.
