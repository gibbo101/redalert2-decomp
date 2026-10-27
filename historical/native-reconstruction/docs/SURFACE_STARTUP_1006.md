# Radar surface startup policy

This checkpoint supports Boot Camp Objective1's original action37 alliance effect:
its House sight/coverage updates eventually refresh the radar surfaces. It corrects
a startup assumption before connecting those shared owners to play. There is no
new player-visible capability, and live arrival/sight/Objective1 remain disabled.

## Actual surface kinds

The previous stock software copy/pixel proofs remain valid at their declared
supplied BSurface association. They do not establish original radar construction.
Exact base inspection now shows630A00 creates first1218 through4AA4A0, the
DSurface initializer;630B70 builds second121C as a BSurface with vtable79AEF8
and buffer child4382C0. The first allocation is36 bytes, the second32 bytes.
The inspected first allocation/call/store span is630B10..630B51; the second
initialization span is630CFD..630D34, followed by its121C store at630D35.
The full allocation/projection callers have not yet executed in a differential
fixture. Do not relabel the two-BSurface proofs as original startup evidence.

The pinned local YRpp `Surface.h` provided surface naming only; its Yuri's Revenge
constructor addresses were not applied to base RA2. No external authored code,
generated/lifted original code, dependency or runtime executable read was added.
All inspected instruction text remains private.

## Recovered initializer

`SurfaceStartup.hpp` implements complete base4AA4A0 (253 bytes) as portable C++.
`DeviceSurfaceStartup` owns logical fields; allocation, device creation and device
description are explicit platform callbacks. It does not reproduce DirectDraw,
load a Windows DLL or execute original code. An eventual native software/SDL
backend must implement the required storage contract through this boundary.
No such backend or radar runtime adoption is claimed here.

The initializer preserves:

- width/height, lock, bytes/pointer/flag resets and ordered descriptor association;
- the108-byte descriptor allocation, null-allocation return and both complete
  descriptor clears without zeroing the original object's untouched padding;
- size108, flags7, height/width stores, exact requested-byte equality to1,
  caps OR0x800 and the late forced-system-byte overwrite to0x2040;
- ignored creation/description return codes, output-surface null gating and
  descriptor reload/clear before description; and
- unsigned32 wrapping of `(bitCount + 7) >> 3` and video flag from caps bit14.

The C++ adapter validates an allocated descriptor's27-word extent and refuses
entered missing callbacks. Those are host memory/lifetime guards, not original
allocation/device-failure parity beyond the tested results. Supplied callbacks
and borrowed descriptor storage must remain alive. Observers report normalized
object/vtable/pointer identities, not raw guest pointers. Faults propagate with
preceding stores retained; the native guard checks that boundary. There is no
rollback or arbitrary callback mutation claim.

## Evidence

Exact supplied target:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. The complete initializer SHA256 is
`6e8e521094767be2c807288fc102e24edeef5e3a2d27a410999b81542faa69e4`.

All160 complete original roots match native ordered object/descriptor stores,
platform arguments, final fields and descriptor words. The original audit retains
all untouched arena bytes (including object padding), callee-saved registers,
caller stack and immutable inputs. Allocation/CreateSurface/GetSurfaceDesc are
explicit supplied leaves:160 allocations,128 creation calls and85 descriptions.
Supplied HRESULTs are failures even on nonnull output, checking the original's
ignored-result behavior. No original allocator/device instructions are claimed.
Cases cover extreme signed dimensions, raw0/1/2/255 requests, raw forced-system
bytes, failed allocations/null creation outputs, conflicting caps and wrapping
bit-count additions. The runtime reads no executable data for this work.

Canonical expectations:
`private/boot-camp-20261020/surface-startup-fresh-a1/expected.json`.
Fresh original generation.068s/native comparison.018s/driver.391s.
Normal/sanitizer/uncached replays explicitly use `--expectations`, each160 hits,
zero misses and fresh native execution; driver wall.232/.310/.344s.
Three Python input/provenance tests and both focused CTests pass. Sanitizer
configure9.185s/build.588s; Python.081s; CTest invocations.172/.279s.
Initial normal configure/build, inspection/edit/task/repair wall costs were not
instrumented. A truncated inspection span was corrected before original execution;
no failed original proof or weakened guard was accepted. No unchanged original
matrix, broad capability ceremony or closed finalizer was rerun. Verification is
local, not independent acceptance.

## Reproduce and next work

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake -S . -B build/native
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake --build build/native --target surface-startup-vectors --parallel 6
build/tools-env/bin/ctest --test-dir build/native -R '^surface-startup-domain$' --output-on-failure
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_surface_startup
# Fresh private output names for every invocation; this explicitly reuses originals.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/NEW-SURFACE-STARTUP.audit.json tests/compare_surface_startup.py \
  --exe private/official-1006-probe/game.exe --native build/native/surface-startup-vectors \
  --expectations private/boot-camp-20261020/surface-startup-fresh-a1/expected.json \
  --report private/NEW-SURFACE-STARTUP.json
```

Use `build/sanitize/surface-startup-vectors` for sanitizer replay, or `--uncached`
before the driver for the inspection control. Fresh original execution substitutes
new `--output` for expectations/report and requires research-only Unicorn JIT.
Provenance guards separate original dependencies from current native sources and
runner identities; native-only edits need rebuilt replay, not new originals.
No cache framework was added. Normal app commands remain `./build.command`,
`./test.command` and `./run.command --boot-camp-walk`.

Next connect the actual radar allocation/projection caller and native storage
backend to the existing shared coverage/radar owners. Preserve DSurface versus
BSurface association and pixel/lock semantics rather than guessing that both use
the software virtual table. Platform allocation/device implementation can be native;
rebuilding DirectDraw is not a project goal. Then validate the entered House-map/
action37 composition, required remaining mission effects and ordinary SDL first-
objective transition. Earlier discarded-preview requirements are not permanent
completion ceremonies. Only Apple Silicon macOS is tested; both games remain
incomplete. No workers, Windows actions, transfers, downloads or system changes.
