# Device copy from the owned software terrain surface

Boot Camp Objective1's action37 House sight refresh needs terrain copied into the
first radar surface before marks/actors can be refreshed. `DeviceSurfaceCopy.hpp`
now expresses complete4AAF80 on its stock4AAFD0 association and the complete
**software-source path** through4AAFD0. It calls the single existing774F00 copy,
clip and blitter kernels with actual destination device locks. Hardware-source
copying remains an entered refusal; this is not a DirectDraw implementation.

## Behavior and existing owners

The wrapper queries source bounds before destination bounds.4AAFD0 checks all four
bounds/region sizes before the stock source84 kind query. BSurface411310 returns
low byte0, selecting the software fallback. Both enable bytes are then checked;
only lost HRESULT887601C2 causes Restore/status recheck and positive saved-depth
Lock/increment/Unlock/depth-restoration. Recovery failure returns false before
copying. The fallback calls774F00 with the original first flag and second flag1.
It retains that child's low-byte result. The first flag's low byte still selects
transparency; second flag does not alter the stock software child's behavior.

The shared `CopySurface` adapter now supports explicit format/pitch/Lock/Unlock
virtuals. Empty callbacks retain its ordinary software chain. Device destinations
borrow the existing lockC, unsigned format10, logical address14, video19, device1C
and descriptor20; no device BSurface lock is substituted. The corresponding signed
integer view legally aliases the same format bits for the existing borrowed pixel
view. Every actual format/pitch/lock/unlock uses its device callback. Backing reads/
writes, clipping, transfer loops and little-endian stores remain single kernels.
Optional device entry observers record recursive lock calls and do not implement
platform or gameplay effects.

`RadarStorage` firstTable.copy8 now binds these algorithms to its actual first
owner and actual second terrain owner. It refuses foreign destinations/sources or
missing rectangles. Views/callbacks are synchronous locals over the immovable
storage owner. Native memory status, RGB565 pitch/descriptor and allocation remain
supplied platform policy. Alpha/depth planes remain zero in this composition.
Finish632700 and production House/coverage scheduling remain unjoined.

The actual mutable Day1 test invokes **firstTable.copy8**, copies the full owned
terrain buffer, requires exact first/second pixel equality and the same first
allocation pointer, and reads a copied word through the actual device pixel path.
Original terrain RGB/pixels and sampled mission/Walk/visibility state stay unchanged.
Both normal and ASan/UBSan checks pass, retaining full-map overlay removal/restore,
image sharing, warm clones and eight GI journeys. This is native integration
coverage, not evidence that the original game ran this Day1 startup scenario.

## Original evidence and reuse

Exact supplied executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD and unverified pristine
provenance remain distinct. Inspection pins75-byte4AAF80,1,303-byte4AAFD0 and
3-byte411310 plus existing device/software-copy children. The complete4AAFD0 span
is inspected, but its hardware branch is neither implemented nor executed here.
The guest's original virtual tables/instructions remain unchanged; only isolated
OS status/Restore/Lock/Unlock results and initial records are supplied.

All390 original sequences match ordered queries/stores, low-byte returns, complete
descriptors and both backing digests. They execute390 wrappers/regions,378 source
kind queries,242 fallback copies,234 transfer/preparation roots,236 device locks,
176 device unlocks and98 Restore calls. Cases cover raw enable/transparency bytes,
zero/negative dimensions, clipping, unequal regions, contiguous and row transfers,
independent source/destination formats1/2/3, signed depth extrema, nested healthy/
recovering depths and platform failure. Full guest arena, permitted writes, code/
global/vtable/table inputs, stack/callee-saved/return ABI and instruction-span
guards remain. No original execution occurs in the app.

Canonical original-only expectations:
`private/boot-camp-20261020/device-copy-fresh-a1/expected.json`.
Fresh original generation0.992s; native comparison0.022s. Normal/sanitizer/
inspection-uncached replays each reuse390 originals with zero misses and rerun
current native code. Both profiles also reuse prior477 locks,335 inherited pixels,
3,804 software copies,642 refresh-copy parents,950 copy/marks,940 complete
coverage/refresh and8 startup sequences. The old startup origin retains its
original unbound-copy fixture scope; replaying its unchanged startup outputs does
not relabel it as an original device-copy proof.

Full native builds,191 normal/190 sanitizer CTests,28 Python checks and both actual
Day1 owner checks pass. CTests take5.55/17.02s; Python3.654s. Separate build/edit/
repair/task and actual-owner elapsed costs were not measured. No original test or
native comparison failure occurred for this milestone. Initial receipt assembly
requested a nonexistent sanitizer app; the existing sanitizer profile builds test
runners, so receipt hashes those and the normal app instead. Local verification is not
independent acceptance. No unchanged original matrix, complete inventory or closed
finalizer was regenerated. No unchanged SDL smoke was repeated for this unscheduled
service. Exact reports/hashes/costs:
`private/boot-camp-20261020/device-copy-receipt-a1.json`.

## Commands and next integration

```sh
./build.command
./test.command
./run.command --boot-camp-walk
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake --build build/native --target device-surface-copy-vectors boot-camp-walk-check --parallel 6
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_device_surface_copy
# Each invocation needs a new private audit/report path.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/NEW-DEVICE-COPY.audit.json tests/compare_device_surface_copy.py \
  --exe private/official-1006-probe/game.exe --native build/native/device-surface-copy-vectors \
  --expectations private/boot-camp-20261020/device-copy-fresh-a1/expected.json \
  --report private/NEW-DEVICE-COPY.json
```

Sanitizer runner: `build/sanitize/device-surface-copy-vectors`. `--uncached` before
the driver disables inspection reuse while retaining explicit original-answer
reuse. Fresh original execution uses a new output directory and research-only JIT.

Next recover632700 bucket initialization, then join actual production House/
coverage/actor refresh before scheduling mission effects. Preserve private table
provenance and the existing executable-read boundary. First-device copy is now
bound only inside the explicit radar service. No radar panel, live sight/arrival,
ordinary Objective1 or whole-frame claim follows; base RA2 and YR remain incomplete.
Only Apple Silicon macOS is tested. No worker, Windows action, download, public
implementation/dependency, system/Xcode/DRM change or runtime executable-read
expansion was introduced.
