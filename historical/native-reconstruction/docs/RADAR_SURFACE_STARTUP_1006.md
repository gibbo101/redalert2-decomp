# Radar surface startup caller

This dependency supports Boot Camp Objective1's action37 alliance change, whose
House sight/coverage effects reach radar refresh. It joins complete630A00 to the
previously recovered complete4AA4A0 initializer using existing `RefreshSurface`
geometry owners. It adds no player-visible capability or live arrival scheduling.

## Recovered order and remaining services

`initializeRadarSurfaces` borrows the exact first1218/second121C pointers and
rectangle1498/origin11EC/11F0 fields. Nonpositive initial width or height returns
without mutation or queries. The entered path saves the old second receiver,
clears rectangle Y then X, deletes old second with argument1 and clears its field,
then releases/clears color1238 and bitmap1270 in order. It calls630B70 with both
rectangle arguments aliased to the actual1498 record; scratch is distinct.

Width then height are queried from the rebuilt second through actual4112C0/
4112D0. Width is stored before the height query and reread afterward. Returned
size is centered within140x108 only when smaller, preserving signed division
and wrapped subtraction/addition even for extreme diagnostic geometry. Origins
are read at their actual late positions. Old first is deleted/cleared,36 bytes
are allocated, then the saved second is queried height-before-width for the
actual4AA4A0 arguments(width,height,1). First1218 is stored, cleared with color0,
and632700 is called last. Host null allocation/owner/missing-service cases refuse
where original invalid dereferences would otherwise occur; no rollback is claimed.

The native joined fixture borrows first width/height directly from the existing
`RefreshSurface`. The single initializer now accepts a record with borrowed fields,
so it does not create/copy a second geometry representation. Its existing owning
record remains supported and keeps all160 prior original results unchanged on
rebuilt normal/sanitizer runners. This native-only binding change required no
regeneration of those original answers.

Projection/build630B70 remains supplied. Destruction, buffer/object/descriptor
allocation, device creation/description, virtual clear18 and finish632700 remain
explicit supplied services. No native pixel-storage backend, original projection
algorithm, original destruction/device code, caller-to-refresh frame composition,
startup asset loading or runtime adoption is claimed. DSurface/BSurface identity
from [SURFACE_STARTUP_1006.md](SURFACE_STARTUP_1006.md) remains intact. This does
not turn two-software-surface proofs into actual radar startup evidence.

## Original evidence and checks

Exact supplied target:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Complete630A00 is361 bytes, SHA256
`f9259b2f62274188d38732fcd5d40ad6fe87a3790538e026f34810ab8f092c17`.
No new public-reference code/dependency/runtime executable read was used.

All304 complete roots match ordered parent/child stores, named service arguments,
actual stock getter traces, shared geometry and final state. They include132 early
returns and172 complete initializer entries,688 getters,194 supplied deletions,
194 buffer releases,136 creation and91 description calls. Original instructions
are unmodified. Full-arena unchanged bytes, declared immutable code/globals/tables,
caller stack and callee-saved registers remain audited. Actual allocation/device
leaves retain the supplied-result scope of the earlier initializer proof.

The matrix covers all16 old-resource presence masks on entered paths, signed
origin/size extremes,140/108 boundaries, descriptor allocation failure/null device
outputs, capability overrides and wrapping pixel-size arithmetic. Original A1's
176 roots passed; review found that its entered cases did not span all old-resource
masks. A2 appends128 entered cases, retaining all earlier commands/labels/outputs
exactly. It is canonical; A1 remains an accurately scoped earlier receipt. No
failed original comparison was accepted or source/receipt guard weakened.

Canonical originals:
`private/boot-camp-20261020/radar-startup-fresh-a2/expected.json`.
Fresh original generation.225s/native comparison.023s/driver.573s. A1 and early
build/edit/repair/task wall costs were not separately instrumented. Focused
normal/sanitizer/reuse check costs and identities are recorded in
`private/boot-camp-20261020/radar-startup-checks-a1.json` and
`private/boot-camp-20261020/radar-startup-receipt-a1.json`.
Five Python checks, two focused CTests/profile, three304-hit/zero-miss joined
replays and two160-hit/zero-miss old-initializer replays pass. Joined replay wall
was.412/.357/.808s (normal/sanitizer/uncached); old replay wall.257/.331s.
Sanitizer configure8.954s/build1.393s, Python.182s and CTest invocations.222/.205s.
Application/owner hashes retain the prior SDL scope; no runtime source or GUI
capability changed. Verification is local, not independent acceptance or
whole-frame fidelity.

## Commands and next integration

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake -S . -B build/native
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake --build build/native --target radar-surface-startup-vectors surface-startup-vectors --parallel 6
build/tools-env/bin/ctest --test-dir build/native -R '^(radar-surface-startup|surface-startup)-domain$' --output-on-failure
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_radar_surface_startup test_surface_startup
# Explicit supported original reuse; choose new private paths each time.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/NEW-RADAR-STARTUP.audit.json tests/compare_radar_surface_startup.py \
  --exe private/official-1006-probe/game.exe --native build/native/radar-surface-startup-vectors \
  --expectations private/boot-camp-20261020/radar-startup-fresh-a2/expected.json \
  --report private/NEW-RADAR-STARTUP.json
```

For sanitizer use `build/sanitize/radar-surface-startup-vectors`; for the inspection
control add `--uncached` before the driver. Fresh generation substitutes new
`--output` for expectations/report and requires research-only Unicorn JIT.
The original identity includes executable/oracle/input/environment dependencies;
current native sources/runner remain separately validated. Replays report actual
hits/misses and always execute native comparisons. No cache framework was added.

Next recover630B70's actual projection/build path and bind a native storage
backend with the relevant DSurface pixel/lock contract, then connect the shared
production coverage/House/actor owners for the entered action37 chain. Native
platform services may replace the operating-system device; reimplementing
DirectDraw is not the goal. Ordinary SDL first-objective transition and the
remaining mission effects still need acceptance. App commands remain
`./build.command`, `./test.command`, `./run.command --boot-camp-walk`.
Both games remain incomplete; only Apple Silicon macOS is tested. No workers,
Windows actions, downloads, transfers, publication or system changes occurred.
