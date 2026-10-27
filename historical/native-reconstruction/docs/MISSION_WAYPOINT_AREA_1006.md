# Waypoint reveal through actual map and reveal-area

A separate SDL-free composition now joins complete6B0670 to actual663180,
548070 and complete54A110 with its numeric children. All96 original sequences
match shared Cell/fallback state and ordered queries/flag writes/reveal requests.
The production action17 child is still recording-only; final visibility children
remain supplied in this proof. No live terrain reveal or objective is enabled.

## Composition and fixed-map identity

`MissionWaypointRevealArea.hpp` reuses the single waypoint and reveal kernels.
Its waypoint callback reads supplied scenario bytes; its Cell callback borrows
actual flags140/level11B from the same map owner used by reveal-area. The new
`revealAreaMapCell` facade invokes the existing lookup kernel with P telemetry,
including immediate fallback coordinate stores. Reveal-area's existing C/G paths
retain their prior scope and ordering. No duplicate map or raster algorithm.

The fixed6B0670 receiver8324E0 makes its map+138 table the very same pointer
storage as global832618. Exact54A110 instructions54A43B and54A4AB load those
respective views; 54808B loads map+138. The new composition therefore requires
one shared primary/secondary table. It refuses separated tables when entered.
This restriction belongs to this fixed-map caller. The older generic reveal-area
fixture's supplied distinct receiver/table profile remains valid and unchanged.
The Boot Camp visibility owner already uses one table for both views, but this
new caller has not yet been bound to its production ownership.

House bindings identify views of the same logical House without querying the map.
Scenario startup, House association, rules/scale and spread arrays remain supplied.
The caller retains signed-height/word arithmetic, repeated map queries, saved
point/height and two full reveal passes with final arguments0 then1. Both passes
see the same mutable flag words and fallback; second-pass writes observe first-
pass clears. Entry-disabled House returns without invoking map/reveal services.
The older caller's independent live-global mutation proof retains separate scope;
this fixture does not mutate rules/House/scale during visibility callbacks.

## Exact-original evidence

Supplied target4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD and unverified pristine
authenticity remain distinct. `verify_mission_waypoint_area.py` composes the
existing exact waypoint/reveal verifiers and pins548070 plus the static-table
associations. Originals execute unmodified in research-only Unicorn, never in
the application. No public/YR/recomp code or new dependency/runtime read.

Canonical private expectations:
`private/boot-camp-20261018/waypoint-area-fresh-a2/expected.json`, SHA256
`deefa361c424f6c4b844ad8d658be75471bb1b44f4a02e168390011770d9ff20`.
96 roots comprise72 ordinary calls and24 disabled calls. They execute72 actual
waypoint getters,192 map getters,144 reveal-area roots,288 height projections,
12,856 table-square-root and13,144 FTOL calls, with9,550 supplied62FCA0 requests.
Compare full shared flags/fallback and ordered P/C/G lookup/fallback/height/
distance/write/reveal traces plus low-byte return. Cases vary table holes/full
fallback, bridge flags100/400, signed/wrapped heights and centers, range/clamp,
height admission, scale and disabled-House bypass. Spread tables are synthetic
fixtures, not recovered gameplay startup or a whole-map observation.

The original fixture uses the actual8324E0 map receiver. Caller stack/return/
callee-saved/code/table/global/arena guards permit only actual Cell flag writes
and fallback-coordinate stores. All unrelated arena/fallback bytes remain exact.
Named final62FCA0/49A0F0/House-predicate services remain supplied; ordinary this-
caller paths do not enter fog or the predicate. No visibility-counter/discovery
or whole-frame fidelity claim follows. Local verification is not independent
acceptance, and native domain refusals do not prove original fault parity.

A1 is preserved as a failed fixture comparison: it incorrectly separated native
primary/secondary tables while the actual static map aliases them. A2 fixes the
fixture and explicitly guards the alias in native composition/verifier. The
recovered arithmetic/reveal kernels were not changed to fit the fixture.

## Verification and costs

Both full builds and final new-target builds pass. All133 normal/132 sanitizer
CTests pass in5.36s/9.89s; all1,422 Python tests pass in28.919s. Both private-data
Boot Camp owner checks pass. New96 and prior48-case reveal-area families pass
normal/sanitizer/uncached replays with zero misses. The earlier waypoint-only
binaries are unchanged. Scoped inventory retains28 unchanged records and seven
new/rebuilt records, including app/owner/reveal runners; exact hashes are private.

The rebuilt application passes the106-tick actual SDL selection/move/pause/
retarget-refusal/Stop/repeated-order/deselection and warm message preview checks:
`private/boot-camp-20261018/waypoint-area-sdl-a1/`. Arrival image inspected. Its
receipt retains objectives_enabled:false and visible_objective_text:false for
live gameplay. Separate diagnostic injected-clone text still records468 glyph/
1,121 fill stores and is not objective completion. No closed finalizer was rerun.

Fresh A2 original7.572s; driver8.010s. Exact replay commands, identities and
remaining measured costs are in `waypoint-area-replay-commands-a2.json` and
`waypoint-area-receipt-a2.json`. Build/repair/review/approval/GUI/tool-dispatch
costs were not separately measured. No new cache; existing identity guards remain.

## Commands and next integration

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
./test.command
DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
build/native/boot-camp-walk-check private/official-1006-probe
build/sanitize/boot-camp-walk-check private/official-1006-probe

env PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/waypoint-area-next.audit.json \
  tests/compare_mission_waypoint_area.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/mission-waypoint-area-vectors \
  --expectations private/boot-camp-20261018/waypoint-area-fresh-a2/expected.json \
  --report private/waypoint-area-next.json

./run.command --boot-camp-walk
./run.command --boot-camp-walk-smoke-test private/NEW-SDL-DIRECTORY
```

Use new audit/report/output paths. For sanitizer choose its runner; for uncached
put `--uncached` before the driver. Fresh original replaces expectations/report
with `--output private/NEW-DIRECTORY` and requires Unicorn JIT access.

Next join actual62FCA0/Cell-change/mask/discovery effects on these same Cells and
House owners, then production action17 and full warm preview isolation. Keep
ordinary arrival/discovery, Team creation/alliance/audio and live Objective1
acceptance separate remaining gates. Both games incomplete; goal active.
No workers/Windows actions/transfers/downloads/system/Xcode/DRM changes.
