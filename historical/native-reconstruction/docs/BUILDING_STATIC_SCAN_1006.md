# Static Building drawing traversal

The later [Building request caller](BUILDING_REDRAW_REQUESTS_1006.md) now verifies
and composes6A4100. This scan checkpoint retains its separate original proof.

Complete6A9F60 now scans the existing Boot Camp Structures using their shared
Type/Building bounds and immutable loaded SHP backing. This is the Building
traversal called by static frame child6A4100, needed for original Building drawing
and ordinary sight/objective refresh. It remains explicit and unscheduled.
Building+FC drawing is a required supplied child, not a pixel implementation;
SDL still uses Building markers. Runtime frame consumption, live sight/arrival
and Objective1 remain incomplete. Both games remain incomplete.

## Original behavior and verification

The supplied target is4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Complete6A9F60 is300 bytes/98 instructions;
complete41FDF0 is289B/107. Actual Building453C40 and Infantry509800 RTTI children
also execute. Building vtable79CBBC confirms RTTI and bounds124=450DD0. The exact
binary pins FC=43A200, but that child is not executed in this oracle.

The parent first intersects dirty and clip rectangles through actual41FDF0. It
then visits the live8525AC/8525B8 registry in forward order, rereading backing per
entry and count after each entry. RTTI2C must equal6. Nonzero actor5B7 skips only
when live globalA40D13 is zero; the global is not read for zero actor5B7. There is
no redraw75, marked74 or onMap7D gate in this parent. Bounds/drawing children may
add their own gates; do not move those gates into this scan.

Viewport X/Y are saved before bounds124. Signed wrapped translated bounds use
strict overlap comparisons against the saved intersection, without an invented
positive-dimensions prefilter. A match copies the then-live clip into a separate
stack rectangle and forwards `(copy, raw32 force, 0)` to Building+FC. Its result
is ignored. The same actor redraw75 clears after the child returns, even when the
child writes that byte. Do not truncate force to a low byte at this parent or
reuse the dirty intersection as the child's clip. Preserve the separate clip
copy: child mutation cannot reach the caller's input. There is no queue clearing.

400 original sequences include raw kind/hidden/bypass/redraw bytes, empty/negative
counts, duplicate entries, live count/backing changes, offset mutation during
bounds with saved-offset behavior, late clip mutation, child-local clip mutation,
post-draw redraw writes, full32 force, edge touching, reversed/empty/wrapped
rectangles and seeded cases. Original counts include443 supplied bounds calls,
324 supplied drawing calls,522 Building and130 Infantry RTTI entries. The complete
parent and intersection execute unchanged. Original stack/callee-register,
code/vtable and unrelated arena bytes are audited. Bounds and drawing services
remain supplied in this proof; their separately verified algorithms and actual
native owner composition retain their distinct scopes.

`private/building-static-20261019/fresh-a1/` contains the initial valid400-case
profile. A2 strengthens the original child service with an explicit stack-copy
identity check and clip mutation, requiring a genuinely new original-source key;
its current expectations are `fresh-a2/expected.json`. The interim A2 native
comparison predates a native-vector-only local-copy mutation edit; final normal/
sanitizer replays use rebuilt runners. Both final profiles explicitly reuse400
original answers with zero misses, always rerunning current native commands and
recording independent source/binary identities. Native verdicts are not cached.

## Existing owners and supplied boundaries

`BuildingStaticObject` borrows the same `FrameInvalidationObject` type/redraw/
bounds view. `BootCampMissionWorld::buildingStaticRegistry` reuses the existing
invalidation registry and Structure5B7 field already exposed for radar, not a
second actor or hidden flag. Its bounds service can use the same Renderer cache,
actual Type demand getters and read-only AssetStore/SHP backing. No persistent
callback points into a cloned or destroyed world; obtain fresh synchronous views
for each owner. Registry association/startup and file/heap/decoder services retain
the existing supplied boundaries. The host owns stable Structures for each call.

The actual-owner test verifies forward traversal of both Objective1 structures,
original SHP/Type/Building bounds, required drawing-child refusal without redraw
clear, raw force256 and zero third argument, hidden/bypass behavior, repeated
redraw0 drawing, clear after a child writes255, warm clone/source destruction and
unchanged Cell/frame queues and source mission. Its drawing callback records
requests; it neither draws original pixels nor synthesizes objective progress.
Missing entered services and foreign slots refuse. No actor destruction during
these synchronous callbacks is admitted by the application owner profile.

All208 normal and207 sanitizer CTests,12 focused Python evidence checks,
normal/sanitizer actual-owner checks, test.command and the ordinary SDL256tick
regression pass. Left/right captures are byte-identical to the preceding getter
milestone's already inspected frames. Local validation is not independent
acceptance. Only Apple Silicon macOS is tested. No dependency/code incorporation,
asset shipment, runtime executable-read expansion or Windows/system/Xcode/DRM
action was introduced.

Evidence, source/runner hashes and accounting are recorded in
`private/building-static-receipt-a1.json`. Generation for final original profile
.152s; initial native build21.97s, owner integration build22.40s, sanitizer build
45.58s, normal owner7.49s, SDL8.41s; final CTests3.40/21.46s. Other measurements
and unavailable manual/repair/total wall costs are recorded in the receipt;
concurrent costs are nonadditive. One preconfiguration build request failed with
no target rule, then normal build.command configured/built the new target. It
was a build invocation failure, not an original/native mismatch.

## Commands and next work

```sh
./build.command
./test.command
build/native/boot-camp-walk-check private/official-1006-probe
build/sanitize/boot-camp-walk-check private/official-1006-probe
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest \
 tests/test_building_static_scan.py tests/test_building_image.py \
 tests/test_building_type_bounds.py

# Fresh private audit/report names; rebuilt current native always executes.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
 tools/run_evidence.py --audit private/NEW.audit.json \
 tests/compare_building_static_scan.py \
 --exe private/official-1006-probe/game.exe \
 --native build/native/building-static-scan-vectors \
 --expectations private/building-static-20261019/fresh-a2/expected.json \
 --report private/NEW.json
# Substitute build/sanitize/building-static-scan-vectors for sanitizer replay.
./run.command --boot-camp-walk
./run.command --boot-camp-walk-smoke-test private/NEW-SDL
```

Next recover complete Building+FC43A200 and its entered ordinary10C drawing child
on these same owners, then the remaining static/frame dependencies including
6A4100 under complete entered6A45A0 and inspected0/1/map/2 dispatch.43A200 context
inspection shows clip mutation, visibility gates, projection and ordinary10C or
special470 dispatch; that inspection is not an executed parent proof. Static
6A4100 inspection resembles the existing Terrain request caller; verify before
reusing it. Private inspection: `private/frame-children-20261019-inspect-a1/`.
Do not bind an isolated frame reset or enable live sight/arrival/objectives before
complete entered paths. No workers or new runtime executable reads.
