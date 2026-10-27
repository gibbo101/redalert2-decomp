# Ordinary Building Cell lighting on shared owners

Complete43A5E0 now borrows the existing complete548070 lookup and the actual
renderer ambient owner in the explicit Boot Camp ordinary-drawing composition.
This removes its supplied constant Cell-light callback. It is a dependency of
Building pixels and frame consumption needed for Boot Camp discovery/Objective1
presentation. Final draw requests remain requests:6D1510 pixels, other frame
children, live sight/arrival and objective scheduling are still open. Base RA2
and Yuri's Revenge remain incomplete; only Apple Silicon macOS is tested.

## Field identity and recovered behavior

Cell `+10A` is a signed ambient-light word. It is not terrain height. This agrees
with the existing recovered map-light stores and unit-light consumers described
in [MAP_LIGHTING_1006.md](MAP_LIGHTING_1006.md) and
[UNIT_LIGHTING_1006.md](UNIT_LIGHTING_1006.md). Earlier Building notes and the
callback name `cellHeight548070` mislabeled the field; it is now
`cellLight548070`. The ordinary parent already treated the value as lighting and
retained the correct numeric behavior. Its real height1B8/projection6A2970 paths
are separate and unchanged. Legacy oracle fixture names remain unchanged so that
valid original expectations do not require regeneration for a native name fix.

Exact supplied executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Complete548070 is56 bytes/18 instructions
through ret4 at5480A5. Its two signed16 input words produce `y*512+x`; only that
linear index is checked against0..262143. There are no independent X/Y bounds.
A nonnull entry returns its exact Cell, even if aliased or its stored point differs
from the query. A hole or invalid index writes the packed query to the one shared
fallback's24 word pair, then returns that fallback. The ordinary parent reads the
returned Cell's signed10A word and adds the late Type11FC where applicable.

The native binding reuses `revealAreaMapCell`; no second lookup implementation or
Cell table was created. `buildingCellLight` unpacks the original words, performs
the lookup, then resolves the actual returned Cell's ambient field. Missing
ambient service refuses before lookup. A fallback service may consume the shared
fallback after its point store; an unsupported renderer association refuses
without inventing a numeric value. Entered fallback mutation is not rolled back.

## Joined original evidence

1,004 original sequences execute complete43A5E0 together with actual548070,
41B320,6A2870,5D4800,6A2970 and FTOL. The corpus retains932 parent cases and adds72
boundary/alias/hole/signed-light cases. It covers main/auxiliary/alternate/timer
requests, repeated lookups on the same fallback, signed extremes, linear-index
aliasing, child mutations and the existing retained-versus-late owner behavior.
There are1,140 actual lookups and1,140 final child-service requests. Lookup
identity, stored point, fallback stores, signed ambient read, ordered parent
reads/writes and all15 final draw arguments are compared. Full table/code/vtable
inputs, caller stack/registers, unrelated actor arena and unrelated fallback
bytes are audited. Initial table associations and light words remain fixture
inputs. Other image/partner/timer/frame/foundation/final-pixel services retain
the parent proof's supplied boundaries. This is not a full pixel or frame proof.

Original answers:
`private/building-cell-light-20261019/fresh-a1/expected.json`.
The new driver declares its own scope instead of modifying the prior original
parent driver. Normal/sanitizer each reuse1,004 new plus932 unchanged original
parent answers,1,936 hits/zero misses; affected native runners always execute.
No native pass/fail is cached and no unchanged original matrix was regenerated.
Original generation took1.79s. Original expectation provenance stays separate
from current native validation and actual-owner integration.

## Actual application owners

`BootCampVisibilityWorld::buildingAmbient` uses its existing canonical table,
query counters and shared fallback. It holds no duplicate ambient state.
`Renderer::buildingAmbient` borrows its existing `mapLights_` record, checking the
supplied map-index/stored-point association before reading and narrowing ambient
as a signed word. GI/terrain lighting and Building queries share that same record.
Scenario light initialization, source associations, static-light lifecycle and
renderer registry association retain their existing supplied boundaries. The
renderer has no original fallback-light owner; that entered case explicitly
refuses. A fixture can supply a fallback field without claiming runtime support.

The existing static/visibility/ordinary owner test now binds both recovered
asset selection and actual map/renderer lighting. It verifies both Objective1
structures, main/auxiliary requests, live ambient mutation to-32768, clone/source
destruction, source/Cell-redraw-queue isolation and missing/fallback refusal.
The new field is not added to another Cell representation or precomputed as a
Building-specific cache. No new runtime executable read, original runtime code,
public dependency, Windows/system/Xcode/DRM action or proprietary shipment occurs.

## Reproduce

```sh
./build.command
./test.command
build/native/boot-camp-walk-check private/official-1006-probe
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest \
  tests/test_building_cell_light.py tests/test_building_ordinary.py \
  tests/test_building_image_selection.py tests/test_building_image.py
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/NEW.audit.json \
  tests/compare_building_cell_light.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/building-cell-light-vectors \
  --expectations private/building-cell-light-20261019/fresh-a1/expected.json \
  --report private/NEW.json
```

Use new private audit/report paths. For parent regression, substitute
`tests/compare_building_ordinary.py`, `build/native/building-ordinary-vectors` and
`private/building-ordinary-20261019/fresh-a1/expected.json`. Sanitizer replays use
runners under `build/sanitize/`, with the same explicit reuse. Build them with
`env DEVELOPER_DIR="${DEVELOPER_DIR:-/Library/Developer/CommandLineTools}" build/tools-env/bin/cmake --build build/sanitize --parallel 6`,
then run that profile's CTests and `boot-camp-walk-check`. Fresh generation uses a
new `--output private/NEW` instead of `--expectations/--report`; Unicorn remains
research/test-only. Try existing GI play with `./run.command --boot-camp-walk`.
No new Building pixels or objective success are enabled by this seam. Next recover
complete entered6D1510 and its actual children on these same owners; its null-image
return alone does not complete drawing. Local checks are not independent acceptance.

## Validation and costs

213 normal and212 sanitizer CTests,16 focused Python guards, actual normal/
sanitizer owners and SDL256tick regression pass. The horizontal captures match
the preceding inspected GI frames byte-for-byte; no Building pixel comparison is
implied. The focused Cell-light CTest also covers missing-owner refusal before
fallback mutation, negative-X linear-index aliasing and a hole updating fallback.
After strengthening that test, only its runner and affected checks were rebuilt/
replayed; unchanged owner/SDL coverage was retained.

Original generation1.79s; final integrated native build15.75s, sanitizer42.74s,
normal owner5.69s, sanitizer75.39s, normal test.command10.31s, sanitizer CTests17.16s
and SDL9.60s. Concurrent costs are nonadditive. An initial test-fixture compile
failed because generated setup landed in the guard branch instead of the vector
branch; its40.88s attempt is preserved. The initial manually transcribed byte pin
used an equivalent but different CMP encoding and was corrected to the exact
inspected bytes before original execution. No original/native mismatch occurred.
Final focused guard build/replay costs, output hashes and unavailable repair/
manual-inspection/total-turn costs are recorded in
`private/building-cell-light-receipt-a1.json`. Local validation is not independent
acceptance.
