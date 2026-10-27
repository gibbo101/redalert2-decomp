# Visibility notification to radar dirty points

Complete6328F0 now has a readable implementation in
`render/RadarCellNotification.hpp`. `RadarStorage::notifyCell` joins it to the
existing first surface, RGB dimensions, float32 scale, bitmap and1258 dirty-point
queue. `BootCampVisibilityWorld::withRadarNotifications` binds the actual568520
notification callback synchronously around existing sight/discovery calls. This
removes another recorded-only effect beneath original Boot Camp Day1 arrival
sight. Runtime arrival, live fog and ordinary SDL Objective1 remain unchanged.

## Evidence and exact behavior

The supplied base is4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. `verify_radar_cell_notification.py`
fingerprints before addresses, pins complete430-byte6328F0..632A9D, actual
41FDF0 intersection and77F110 conversion, and checks the direct associations.
No public/generated/lifted code or new dependency was used.

Null first1218 returns without queries. Signed-word Cell coordinates produce
wrapped logical X=`origin148C - y + x`, Y=`y - origin1494 + x`. Ordinarily the
logical rectangle is2x1. X=-1 clamps to0 with width1; X=`2*mapWidth100-1`
retains X with width1. The actual intersection child clips against
`(0,0,rgbWidth123C,rgbHeight1240)`. Both live first-surface width7C and height80
are queried **even if the clipped rectangle is empty**.

For positive clipped width/height, four independent float32-scale loads multiply
left/right/top/bottom under the original53-bit/toward-zero profile. Actual FTOL
low-dword semantics apply, including nonfinite/overflow indefinite values. Left
and top subtract1 and clamp below0; right and bottom add1 and clamp against the
saved surface sizes. Logical sums and +/-1 adjustments wrap before comparisons.
Dirty-point calls occur row-major: Y outer, X inner. Empty ranges make no calls.
The native kernel refuses unbound entered children and execution rectangles
above65,536 pixels or4,096 per dimension; this is a native bound, not original
malformed-state behavior.

672 complete original calls execute the parent, actual intersection and actual
FTOL. Surface getters and632620 dirty effects are explicit supplied probes here.
Cases cover null surface, signed Cell extremes, edge rectangles, clipping,
zero/negative surface/RGB dimensions, wrapped origins/map width, fractional/
negative/zero/NaN/infinite float32 scales and ordered dirty points. The guest
checks entered code, immutable whole map/surface/point arena, immutable code,
allowed writes, caller stack/return and callee-saved registers. This parent does
not mutate the arena when its effect children are supplied recorders.

Canonical original-only expectations:
`private/boot-camp-20261020/cell-notify-fresh-a2/expected.json`.
Expectation SHA256: `08a5bcd046fa5b15f2f63f51713cd053e4bb7f5b37e311dd99dd45c84e6854d7`. Fresh original generation
took0.205s.
A1 failed inspection before original execution: its FTOL range included a trailing
padding byte after the return. A2 pins the complete return-ending61-byte range.
No failed result was accepted, original instruction changed or receipt relabelled.
The existing271-sequence coordinate/dirty proof retains its separate scope;
there is no claim of a single original root through notification and allocation.

## Actual ownership and composition

`RadarStorage::notifyCell` borrows its actual first surface, RGB dimensions and
scale;632620 uses its existing single bitmap/dirty vector/14D5 owner. It creates
no second queue or mirror. Map width comes from the actual MutableUnitMap. Radar
origin148C/1494 association remains explicitly supplied by the caller; the actual
map check uses the same full-map origin as the previous radar fixture. Surface
backend, allocations, original startup and queue-consumption schedule remain
supplied or unjoined.

The scope binds `discovery.notifyCell` to that native storage, preserving the
selected Cell's actual stored coordinates from the existing recovered discovery
kernel. It can compose with the preceding scoped Cell redraw kernel on one
arrival-sight call. Outside the scope the prior explicit notification recorder
remains. Nested notification scopes and cloning during either active visibility
effect scope refuse. Exceptions release the binding without claiming to roll
back game effects. Warm clones retain their own Cell/world state and must bind
explicitly to the external storage for a later call.

The actual-owner test composes arrival -> sight/change -> discovery notification
-> original notification algorithm -> existing bitmap/dirty-point producer,
alongside actual Cell redraw. Every produced point is inside the actual first
surface and marked in the shared bitmap. Repeated Cell requests do not grow the
queue after their bits are set. The test also covers nested/active-clone refusal,
exception cleanup, warm rebinding/source destruction and source-world isolation.
A controlled initial bitmap clear is test setup, not recovered initialization.
Notification preserves display pixels: queueing work is not proof of drawing.

These are local native integration checks, separate from the isolated original
proof. No original-game observation or independent acceptance is claimed. No SDL
ceremony is repeated for an unscheduled explicit effect. No Windows action,
download, system change, source-installation write or runtime executable read.
Only Apple Silicon macOS is tested; base RA2 and Yuri's Revenge remain incomplete.

## Reproduce and next work

```sh
./build.command
./test.command
build/native/boot-camp-walk-check private/official-1006-probe - private/boot-camp-20261020/radar-shape-dimensions-a1.bin
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest tests/test_radar_cell_notification.py tests/test_cell_redraw.py

# Explicit original reuse; current native always runs. Choose fresh outputs.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
 --audit private/radar-cell-notify-next.audit.json tests/compare_radar_cell_notification.py \
 --exe private/official-1006-probe/game.exe --native build/native/radar-cell-notification-vectors \
 --expectations private/boot-camp-20261020/cell-notify-fresh-a2/expected.json \
 --report private/radar-cell-notify-next.json
# Repeat with build/sanitize/radar-cell-notification-vectors and fresh paths.
./run.command --boot-camp-walk
```

199 normal/198 ASan+UBSan CTests, `./test.command`, eight focused Python tests
and both rebuilt actual-owner profiles pass. Each profile explicitly reuses
672 notification +349 redraw +271 coordinate/dirty +192 visibility change +64
post-sight =1,548 original sequences with zero misses. Original generation.205s;
standard tests3.538s, sanitizer CTest24.113s, owners3.432/50.487s. Notification
replay.567/.519s; change29.156/5.924s; post4.623/.652s; focused Python.095s.
Exact commands, all replay costs and hashes:
`private/boot-camp-20261020/cell-notify-receipt-a1.json`. Build/config/inspection/
edit/preflight/total wall uninstrumented; concurrent costs not additive. Fresha1
failed span inspection before original execution; corrected canonicala2 passes.
No build/comparison/native-check failure, unchanged original regeneration or SDL
ceremony for these unscheduled services.

Final commands/logs/check durations:
`private/boot-camp-20261020/cell-notify-final-{native,sanitize}-a1/`.
Final source/binary/input/result hashes and counts:
`private/boot-camp-20261020/cell-notify-receipt-a1.json`.
Build/configuration/inspection/edit/preflight/total wall were not instrumented;
concurrent durations are not additive. No unchanged original matrix is regenerated.

Next finish the entered local refresh47BE00/47BE60 and identify which remaining
position/membership effects the actual bounded player arrival enters. The inspected
47BE00 projects seven diagonal Cells, clears flag140 bit0x400000 on admitted
height slices, then calls47BE60; those mutation/destruction effects are not
implemented by the old counter-only refresh callback. Rule/schedule gates still
matter: do not invoke an unentered effect just to complete a service list.
Join actual viewport/queue consumers and required mission effects before live
arrival/ordinary SDL Objective1 acceptance; do not synthesize objective success.
