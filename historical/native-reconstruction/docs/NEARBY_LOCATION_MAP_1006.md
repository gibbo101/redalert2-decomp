# Nearby destination search on shared Cells

The later [zero-point Unit caller join](UNIT_NEARBY_SCATTER_1006.md) executes this
search and actual Cell destination effects. Its separate proof does not promote
Cell dispatch, Advance6/Process or runtime displacement. This note retains the
standalone search proof and its original boundary.

`nearbyLocationOnMap` joins complete original nearby destination enumeration and
selection to actual direct-Cell permission, rectangle/Cell admission, center
projection and table square root. It borrows one map/slot/fallback owner and live
Cell level/flags/occupation/overlay/type/speed inputs. This separate unwired entry
chooses a candidate Cell; it does not find a route, command a Unit or advance it.
Base Red Alert 2 first, then Yuri's Revenge remain incomplete.

## Exact target and composition

The supplied private executable is 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 lineage and reported no-CD provenance remain distinct;
pristine authenticity is unverified. Its fingerprint was checked before inspection.
The existing verified local file made the authorized Windows copy unnecessary.

The original executes complete `5502E0 -> 55A740 / 550CF0 -> 478760 / 6A6A50 ->
548070 / 4BA410` in one guest. There are no substituted admission, permission,
projection or square-root decisions, no API shims and no modified instructions.
The proof's non-default zone resolver and burrowability branches are not entered:
zone is -1 (including caller normalization of 65535), and burrowability is zero.
Those are the actual required Unit zero-point caller arguments; that Unit caller
itself is not executed by this proof.

The existing policy now lives once in `sim/NearbyLocationPolicy.hpp`, with the
original `nearbyLocation` facade forwarding to it. The map adapter uses reference
views, not copied level/flag projections. The saved Cell remains the same object
across rectangle and projection lookups, including repeated fallback mutation.
Dimension0 is borrowed from the same permission-shape field used by children;
dimension1, frame and sentinel also remain borrowed. No actor/map/type owner or
floor cache is duplicated. Constructing the view makes no queries. Temporary
Cell-to-view associations are local and contain only references.

Preserve duplicate radius 0 candidates, original ring/edge order, append-before-
projection and the 24-entry limit, failed projections retained in that limit,
independent repeated final projection and stable preferred/other partition.
Frame selection uses signed remainder with no RNG. Distances wrap the signed
squared dword before the original table sqrt, including negative inputs; ties
remain first-wins. The previous broad policy proof still covers its supplied
service/late frame/target mutation and general numeric profiles.

Children retain direct permission without an extra lookup; X-outer/Y-inner signed-
word rectangle offsets, immediate shared fallback forwarding, overlay-before-
speed4 refusal, selected low occupation bytes/masks and original wall/land0 rules.
Zero/unordered land speeds reject ordinary ground admission; negative nonzero
speeds pass. Projection ignores Z, repeats source lookups, reads current Cell
levels/bridge flags and returns raw candidate words after independent lookups.
No telemetry performs a floor query or warms fallback/lazy state in advance.

## Evidence and limits

Canonical: `private/map-depth-1006/nearby-location-map-v1/`.
**327 complete original searches** match normal, ASan+UBSan and uncached replays.
There are 10,014 direct permission calls, 6,603 complete rectangles, 5,949 actual
Cell admissions, 2,631 projections and 415,577 separate projection map lookups.
Both returns of permission/rectangle/Cell admission execute. All 32 radii run;
retained 24 occurs four times at the common enumeration exit. There are 1,440
retained candidates, with 1,226 preferred and 214 nonmatching final projections.
Actual table roots total 257: 223 positive, 8 zero and 26 negative. Execution covers
1,091 distinct instructions across seven complete ranges, not every inspected
branch. These synthetic original executions are not original-game observations.

Compare ordered parent lookup, direct permission, rectangle, complete Cell child,
projection/map lookup and fallback-store events; full child arguments, returned
points/table-root values and all final projected Cell records. Original whole
arenas/unmodeled Cell/fallback bytes, slot/type/registry/speed/shape/frame/sentinel/
code/table inputs and caller registers/stack/canaries are guarded. Four incoming
native rounding modes retain caller settings. No native machine-store-order,
FP exception-flag, original-game observation or startup/global-lifetime claim.

Nine native checks per mode cover borrowed ownership/no binding queries, pointer
permission without extra lookup, entered burrow/zone refusals, split bindings,
negative frame remainder and unrelated exception/FP restoration. Eight Python
checks protect malformed input, source/data/executable/receipt identities and
scope. Native malformed-memory domains and projection bounds retain explicit
safety refusals, not original results or rollback. Unsupported calls may already
have consumed world effects; future previews must discard the entire call.

Parent `nearby-location-v3` freshly retains every v2 command/label/output across
306 complete original policy calls, with all three replays. The prior parent scope
still has supplied decision services; it is not relabeled as a joined-world proof.
The closing inventory has 188 records: 184 earlier records unchanged, 2 refreshed
policy records and 2 new map records. No earlier closed finalizer/receipt is rerun
or rewritten. The opening handoff records full regressions and timings.

Initial Cells, occupation/overlay/type/registry/speed inputs, map shape, frame,
sentinel and associations remain supplied. Entered burrowability is refused;
non-default zone resolution remains an explicit supplied service in the child
helper, absent in this adapter's tested profile. These are not original startup
or owned-world membership/construction. No Unit/Cell Scatter, Advance6, Process,
production owned map, full preview, drawing or SDL join is added. Existing runtime
Scatter/Advance6 guards stay intact. The playable two-Rhino app remains identical;
no new SDL acceptance is claimed. Only Apple Silicon macOS is tested; local
verification is not independent acceptance.

No upstream source/header/generated/lifted output, extracted table, dependency or
runtime executable-read expansion was incorporated. Existing private render data
is reused by the test runner for the already recovered sqrt table. Proprietary
originals/assets/disassembly/results/binaries stay ignored and unshipped. Existing
[reference/license limits](REFERENCES.md) apply. Installations/discs/Outpost2 remain
read-only; no workers, Windows transfers, downloads or system/DRM changes occurred.

## Build and reproduce

```sh
./build.command
./run.command --owned-demo
./test.command
PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  -m unittest discover -s tests -p 'test_*.py'

env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake -S tests/nearby_location_map \
  -B build/nearby-location-map -DCMAKE_BUILD_TYPE=RelWithDebInfo \
  -DCMAKE_OSX_ARCHITECTURES=arm64 -DCMAKE_PREFIX_PATH=/opt/homebrew
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/nearby-location-map --parallel 6
build/tools-env/bin/ctest --test-dir build/nearby-location-map --output-on-failure
build/nearby-location-map/nearby-location-map-vectors --guards
# Repeat in build/nearby-location-map-sanitize with Debug and RA2_SANITIZE=ON.

# Fresh original execution needs the authorized host Unicorn JIT context.
# Choose unused private audit/output paths; never overwrite canonical evidence.
PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/map-depth-1006/nearby-map-new-audit.json \
  tests/compare_nearby_location_map.py \
  --exe private/official-1006-probe/game.exe \
  --native build/nearby-location-map/nearby-location-map-vectors \
  --output private/map-depth-1006/nearby-map-new
# Replay: replace --output with --expectations
# private/map-depth-1006/nearby-location-map-v1/expected.json --report NEW_JSON.
# Sanitizer: select its runner. Uncached: add --uncached before the driver.
```

The standalone project stays outside the app/legacy CTest graph. Keep sources and
runners fixed during guarded generation/replays; never rerun closed finalizers.
Six-case and targeted pilots preceded canonical generation. The first full pilot
correctly rejected missing capacity coverage: its supplied permission diamond
excluded enough candidates to leave 20. Geometry was corrected and original state
at the common enumeration exit now asserts retained 24 across all exit sites.
No algorithm/result/instruction or coverage requirement was weakened. Earlier
attempts remain private/superseded. Full manual review/repair time was not measured.

Next execute the actual zero-point Unit Scatter caller through this search and
actual destination effects, then Cell dispatch, complete Advance6/Process effects,
production owned actors and full discarded previews/warm renderer isolation.
Actual SDL acceptance still precedes enabling displacement. Keep the initialized-
zero 852998/AD04C0 findings and actual Drive head+40 distinct from destination+34;
Advance's height global and complete caller effects remain open. General routes,
combat, economy, AI, campaigns, multiplayer, audio, original saves and YR stay open.
