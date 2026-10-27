# Live Building redraw decision before the Tactical frame

Complete6AA180 now has a readable native implementation and an explicit query
on the existing Renderer and Boot Camp Structure owners. This is the frame's
first decision before its phase branches. Recovering it removes a supplied
empty-Building-list assumption from the path toward consuming genuine sight
redraws and delivering ordinary Objective1. No runtime frame/reset/sight schedule
has been bound by this change.

## Original evidence and recovered behavior

Exact supplied executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain separate. The verifier pins complete6AA180(383
bytes/129 instructions), Building virtual+A8/453C70(43 bytes/17 instructions)
and actual FTOL77F110(61 bytes/20 instructions), plus Building vtable79CBBC+A8
and the original0.5 literal. All three routines execute unmodified in the oracle.

The Building+A8 getter subtracts128 from the raw88 X/Y with32-bit wrapping and
preserves Z. It is distinct from foundation-center getter444080; substituting
that previously recovered getter here would be incorrect. The new method lives
beside that getter in `sim/BuildingCoordinates`, with its own evidence boundary.

`buildingRedrawInFrame` saves wrapped world rectangle edges from the supplied
Tactical origin, then scans the live Building registry. It tests bytes7D,75,74
in that order, short-circuiting on zero and accepting any nonzero value. It calls
the coordinate child only after all gates pass. Each next iteration rereads
countA40B08 and backingA40AFC. Count<=0 skips the backing; duplicates preserve
identity. The first accepted Building returns immediately. Native service bounds
and lifetime refusals do not imply that the original safely accepts null slots.

The inlined projection preserves wrapped products and sums, signed half division
and /256. Height uses53-bit toward-zero arithmetic, adds one at Z>=728, adds the
actual0.5 and uses FTOL's low EAX before wrapped Y subtraction. All four rectangle
edges are inclusive, including zero-width/height rectangles. Bounds are not
normalized. Origin changes inside a child do not change the saved edges. Native
FP scopes restore host rounding on return/refusal; FP status flags are untested.

553 new original calls include492 actual453C70 entries. Ordered count/backing/
gate reads, coordinate calls, supplied mutations and final low-byte decisions
match current native. The original guard checks code, vtable, coefficient/literal,
saved registers, caller stack and unrelated arena bytes. Fixtures cover all raw
gate exits, duplicate actors, signed/wrapped coordinate and origin extrema,
height727/728/729, inclusive edges, count growth/shrink, backing replacement,
later actor flag/coordinate changes and saved-origin behavior. Mutations are
explicit supplied child-boundary probes;453C70 itself remains unchanged.

The tested registry fixture has three stable actors with counts-1..3 and finite
positive height scales<=1. Missing native count/backing/coordinate services
refuse when needed. The original fixture supplies initial owners/registry and
inherited0E7F FP state. This is not constructor, registry-startup, arbitrary
callback/lifetime or full-frame fidelity proof.

## Existing application owners

`BootCampMissionWorld::buildingFrameRegistry()` returns synchronous references
to the existing Objective1 Structure owners. Their existing onMap7D and raw88
position are borrowed; new marked74/redraw75 fields live on the same existing
Structure sight record and copy through the existing clone path. Startup1/0 for
these fields and map-key registry order/association are supplied. Their original
production writers and registry construction remain open. No duplicate Building
or persistent scan snapshot was introduced.

`Renderer::buildingRedrawPending` uses its actual viewport origin and existing
height scale. This is an explicit unscheduled read-only seam. Actual-owner checks
dirty the first/second existing structure, exercise raw gates, camera clipping,
live position changes and fresh registry binding after warm-clone/source
destruction. Queries retain actual Cell queue count/dirty flag, source fields and
mission state. No arrival, synthetic discovery or recorded child request is used
as objective progress. Callers must obtain fresh borrowed views from each clone;
views do not outlive their synchronous owner.

Both builds and owner checks pass, as do204 normal/203 sanitizer CTests, six
focused Python tests, test.command and SDL256-tick movement/drawing regression.
The SDL run verifies the retained interaction; it does not schedule this new
query or prove original frame fidelity. Both profiles explicitly reuse553 new
frame decisions plus1,034 unchanged foundation/closest/discovery answers:
1,587 hits/zero misses each. Native results and identities are recomputed; no
unchanged original matrix was regenerated. Local verification is not independent
acceptance. Only Apple Silicon macOS is tested.

Next compose complete entered6A45A0 paths in the actual0/1/map-callback/2 protocol,
recovering entered static invalidation6AA090 and other required children on the
existing owners before runtime queue clearing. Its6A3020 child already has a
recovered dirty-region kernel; preserve that queue's actual ownership/order.
Do not bind isolated count/flag reset tails or substitute a phase3 invocation for
the original caller. Live sight/arrival/Objective1, base RA2 and YR remain
incomplete; the full goal stays active. No workers, public code/dependency,
download, runtime executable-read expansion or Windows/system action was added.

## Commands and costs

```sh
./build.command
./test.command
env DEVELOPER_DIR="${DEVELOPER_DIR:-/Library/Developer/CommandLineTools}" \
 build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/native --output-on-failure
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
build/native/boot-camp-walk-check private/official-1006-probe
build/sanitize/boot-camp-walk-check private/official-1006-probe
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest \
 test_building_frame_redraw test_building_coordinates
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
 tools/run_evidence.py --audit private/building-frame-next.audit.json \
 tests/compare_building_frame_redraw.py \
 --exe private/official-1006-probe/game.exe \
 --native build/native/building-frame-redraw-vectors \
 --expectations private/building-frame-20261019/fresh-a1/expected.json \
 --report private/building-frame-next.json
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
 tools/run_evidence.py --audit private/building-coordinates-next.audit.json \
 tests/compare_building_coordinates.py \
 --exe private/official-1006-probe/game.exe \
 --native build/native/building-coordinates-vectors \
 --expectations private/boot-camp-20261018/building-coordinate-fresh-a2/expected.json \
 --report private/building-coordinates-next.json
# Substitute sanitizer runners and fresh output/audit names for sanitizer replay.
./run.command --boot-camp-walk
./run.command --boot-camp-walk-smoke-test private/building-frame-sdl-next
```

Fresh original generation.158s; current receipts/logs/identities and measured
build/check/replay costs are in `private/building-frame-receipt-a1.json`.
Build/configuration, SDL, manual inspection/edit/review and total task wall were
not fully measured; concurrent times are nonadditive. An initial patch context
miss applied no edits and was corrected. No numerical or test mismatch occurred.
The existing duplicate-static-library linker warning remains nonfatal. All
proprietary inputs, disassembly, expectations and captures remain ignored.
