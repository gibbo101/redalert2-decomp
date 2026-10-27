# Building bounds and frame invalidation

Complete6AA090 now composes complete Building+124/450DD0, actual coordinate
getter453C70, complete Tactical projection6A29D0 and the existing complete
6A3020 dirty-region registration/union/intersection kernels. It exposes an
explicit, unscheduled operation on the existing Renderer and Objective1 Structure
owners. This removes another empty-object assumption from frame recovery, needed
before genuine sight redraws can accompany ordinary Boot Camp progression.
It does not enable live sight, arrival, frame clearing or Objective1 completion.

## Original evidence

The exact supplied base executable is4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. `verify_frame_invalidation.py` fingerprints
it, pins Building vtable79CBBC slots2C/A8/124 and the Infantry RTTI association,
and checks complete instruction ranges. New ranges are6AA090(236B/79instructions),
450DD0(302B/89),6A29D0(306B/106),453C70(43B/17),453C40(6B/2),509800(6B/2)
and77F110(61B/20). The existing redraw verifier pins6A3020 and its rectangle
children, growth dispatch and initializer. The oracle executes these parents and
children unmodified. Type bounds45E290 and allocation6ACBE0 are supplied services.
The complete Type bounds routine is inspected separately; it is not recovered.

6AA090 scans the live Object registry, calls RTTI first, accepts only kind6, then
reads raw byte75. It does not test7D or74. Each accepted actor calls its bounds
child; only afterward are the current screen-offset globals loaded. Strict,
wrapped signed overlap rejects edge touching, with no rectangle normalization.
Registration receives the original relative rectangle by value and flag0, rather
than the translated overlap rectangle. After registration returns, the same
actor's75 is cleared even if the dirty queue refused insertion/allocation. The
next iteration reloads live count/backing. Duplicate identities stay duplicates.

450DD0 calls actual+A8 even on a cache hit. That getter subtracts128 from raw88
X/Y with wrapping and preserves Z; it is not the foundation-center getter. The
cache keys are that coordinate and the saved Tactical originB0/B4. There is no
extra validity bit. A hit returns existing bounds. A miss calls6A29D0 and then
Type45E290, ignoring projection's boolean while retaining its output. The parent
stores coordinate keys, saved origin keys, and the translated Type rectangle in
that order: nine ordered owner stores. A Type service changing origin does not
change the keys saved before its call. Initial cache fields remain supplied.

6A29D0 preserves the same wrapped integer products/sums, signed divisions,
53-bit toward-zero height arithmetic,728 threshold,0.5 and FTOL low32 behavior as
the separately verified frame predicate. It first writes world X/Y, loads the
late origin, then writes relative X/Y: four ordered output stores. Its boolean
uses inclusive margins-360..width+360 and-180..height+180, with wrapping and
short-circuited dimension loads. Output survives a false return. Native FP scopes
restore host rounding; FP status flags and callbacks that alter FP state are
outside this fixture. Finite height scale0<scale<=1 is the tested boundary.

525 joined cases compare ordered RTTI/flag/registry/origin reads, actual parent
entries, projection/cache stores, supplied mutations, dirty-region stores and
redraw clears, plus final caches and every queue capacity-tail entry. They cover
signed extrema, height727/728/729, exact cache hits and individual key changes,
raw flags, duplicates, late count/backing/origin/offset/position changes, strict
edge touching, queue containment/growth/refusal and clearing after failed growth.
Caller stack, callee-saved registers, immutable code/vtable/literals and unrelated
arena bytes are audited. The existing allocator preserves full capacity tails;
allocation itself, input records/registries and inherited0E7F FP state are supplied.
This is bounded parent composition, not constructor, image-bound, full-frame or
arbitrary callback/lifetime fidelity proof.

Private original expectations: `private/frame-invalidation-20261019/fresh-a3/`.
A1 failed its fixture audit because repeated queue growth exceeded the declared
single-growth allowance. A2 caught a wrong non-Building fixture dispatch address;
it was corrected to the independently verified Infantry509800 leaf/vtable. These
attempts remain failed at their true scope. A3 passes all525 comparisons. No
native numerical mismatch was observed. Replays select `--expectations`, validate
original transitive Python/environment/code/input identity, and recompute current
native results and source/binary identity. Native-only edits require no new
original answers. Original results are never inferred from native pass/fail.

## Existing owners and remaining boundaries

The existing `StructureSightState` now holds its render cache beside raw redraw75.
`buildingInvalidationRegistry` borrows those same Objective1 Structure records,
using supplied map-key registry association/order. The complete original fixture
also includes actual non-Building RTTI entries; this production view currently
contains the two existing Buildings only. It does not recover registry creation.
A fresh synchronous borrowed view is required after cloning; no provider/view
may outlive its owners. Bounds providers preserve the existing raw coordinate
owner and use Renderer camera, height scale and logical viewport dimensions.

`Renderer::buildingBounds` requires an explicit Type image-bounds service on a
miss. No original Building SHP bounds are invented: the application still draws
building markers, and these tests explicitly supply a32x40 rectangle. Missing
Type bounds refuse before cache mutation. Warm cache hits need no Type service.
`Renderer::invalidateBuildings` uses the existing dirty-region kernel on one new
persistent queue in the existing Renderer. Host initial count0/growth10/owned
allocation and vector resizing are supplied allocation/startup policy. It does
not consume or clear this queue and is not called by ordinary SDL ticks/drawing.
The separate Cell redraw owner is retained, not duplicated or reset.

Actual-owner tests exercise raw7D/74 bypass, missing Type refusal, relative queue
registration, translated-overlap refusal, cache reuse, camera/position misses,
warm clone/source destruction, retained queue containment and source/Cell queue/
mission isolation. Normal and sanitizer validation, original replay, broader
native checks and SDL regression results/costs are recorded in the private
receipt linked from HANDOFF. Local validation is not independent acceptance.
Only Apple Silicon macOS is tested. No new runtime executable reads, public code,
dependency, download, workers, Windows or system/Xcode/DRM action was introduced.
Base RA2/YR and ordinary Boot Camp Objective1 remain incomplete.

Next recover Type45E290's actual image bounds and required static-frame children
on existing owners, then complete entered6A45A0 paths under the inspected
0 ->1 -> map virtual40 ->2 caller protocol before any frame/Cell queue reset.
Do not schedule an isolated reset tail or substitute phase3. Keep the tutorial
transition as the acceptance target; this explicit seam alone does not deliver it.

## Reproduce

```sh
./build.command
./test.command
env DEVELOPER_DIR="${DEVELOPER_DIR:-/Library/Developer/CommandLineTools}" \
 build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/native/boot-camp-walk-check private/official-1006-probe
build/sanitize/boot-camp-walk-check private/official-1006-probe
build/tools-env/bin/ctest --test-dir build/native --output-on-failure
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest \
 test_frame_invalidation test_building_frame_redraw
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
 tools/run_evidence.py --audit private/frame-invalidation-new.audit.json \
 tests/compare_frame_invalidation.py --exe private/official-1006-probe/game.exe \
 --native build/native/frame-invalidation-vectors \
 --expectations private/frame-invalidation-20261019/fresh-a3/expected.json \
 --report private/frame-invalidation-new.json
# Substitute the sanitizer runner and fresh report/audit names for sanitizer replay.
# Reuse unchanged predicate expectations after rebuilding its native runner:
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
 tools/run_evidence.py --audit private/frame-predicate-new.audit.json \
 tests/compare_building_frame_redraw.py --exe private/official-1006-probe/game.exe \
 --native build/native/building-frame-redraw-vectors \
 --expectations private/building-frame-20261019/fresh-a1/expected.json \
 --report private/frame-predicate-new.json
# Existing dirty-region coverage, with current native results:
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
 tools/run_evidence.py --audit private/frame-redraw-new.audit.json \
 tests/compare_membership_current.py --family redraw \
 --exe private/official-1006-probe/game.exe --native build/native/redraw-vectors \
 --expectations private/traversal-1006/redraw/expected.json \
 --report private/frame-redraw-new.json
./run.command --boot-camp-walk
./run.command --boot-camp-walk-smoke-test private/frame-invalidation-sdl-new
```

All expectations, audits, binaries, captures and inspection dumps remain private
and ignored. Commands need fresh report/output paths. The live interactive mode
retains existing movement/facing behavior; it does not invoke this new explicit
frame operation or establish original animation/frame fidelity.
