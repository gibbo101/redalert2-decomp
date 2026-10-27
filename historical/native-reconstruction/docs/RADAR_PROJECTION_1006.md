# Radar projection and resampling

Tutorial purpose: Boot Camp Objective1 action37's alliance change needs the
House sight/coverage/radar effects. This recovers the630B70 projection dependency
of the actual630A00 startup caller. It adds no SDL objective transition and does
not enable live arrival or sight scheduling.

## Algorithm and boundaries

`buildRadarProjection` expresses complete630B70 on borrowed region/source/output,
second121C surface, RGB1238/cache123C/1240, bitmap1270 and scale1484 fields.
A nonzero update byte replaces a nonpositive region with the source rectangle.
Absent RGB storage is allocated, cleared by ordered constructor byte stores,
stored in the map, then cleared again by dword/byte stores before cache dimensions
are assigned. Update then calls the explicit supplied631250 color service.

Absent second storage chooses dimensions within140x108 and stores the float32
scale before its BSurface factory and color-zero clear. Existing storage queries
width before height and retains its scale. The factory remains an explicit native
storage service: the fixture expresses the inline BSurface initialization and
4382C0 buffer constructor stores; the original actually executes those instructions.
Object/buffer allocation and clear are supplied leaves. This is not a DSurface
implementation or production storage adoption.

Resampling retains the original53-bit toward-zero FP profile, float32 scale,
steps, inverse area and coordinate spills. Inverse area uses the unspilled Y ratio
and spilled X step. The Y endpoint remains double through its row; the X endpoint
is spilled for the final overlap weight but converted before spilling for the
integer bound. RGB bytes accumulate separately with ordered multiply/add operations.
Channels add .5, convert through FTOL's signed-qword/low-dword behavior, clamp only
above255 and pack through the supplied original channel shifts. Pixel stores are
16-bit; stock lock/pitch/width/unlock children preserve their order. The optional
bitmap allocation/clear follows unlock; the output rectangle is stored last.
The host rounding mode restores on success and exceptions.

Unsafe/missing host storage/services and unsupported geometry refuse explicitly;
these are host safety boundaries rather than invented original failure semantics.
The differential fixture uses positive1..32 source dimensions, contained
nonnegative regions, existing7x5 or newly computed storage, scale.5 for existing
storage, RGB/bitmap presence combinations, raw update0/1/128/255 and two supplied
channel formats. Terrain RGB inputs, allocation results, clear effects, source
geometry/startup records and the initial FP profile remain supplied. The source
and region fixture records are distinct; actual startup aliasing/composition and
631250 terrain color generation remain next. No asset color provenance, device
behavior, complete startup, whole frame or original SDL observation is claimed.

## Evidence and commands

The exact supplied target is4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Complete630B70 is1,746 bytes, SHA256
`db3865b5813d588f0ca3a6b59cb1a736ec8b0f986547ff49d708a0b40fe9afad`.
Its alternate63123B tail is included. The verifier also fingerprints4382C0,
FTOL, stock children, scalars and relevant virtual associations. No public code,
new dependency, runtime executable read or original instruction patch was added.

The oracle audits the full arena against its ordered writes, unchanged declared
code/tables/globals/source, return address/caller stack and callee-saved registers.
Supplied services update the expected arena explicitly, separately from original
instruction writes. Final digests include entire RGB/pixel/bitmap backings, so
unchanged tails remain checked. Original and current native identities are separate.
Original reuse validates the original dependency closure and receipt; every replay
executes the rebuilt native runner and reports actual reuse hits/misses.

All70 complete original roots match79,518 ordered pixel stores,41,562 RGB
stores,1,271 bitmap stores and188 stock getter calls;52 color updates and11
initial clears remain supplied. Canonical original answers:
`private/boot-camp-20261020/projection-fresh-a1/expected.json`.
Fresh generation57.155s/native.061s/driver57.877s. Rebuilt normal/sanitizer and
uncached-inspection replays each report70 hits/zero misses and run the current
native comparison; wall.515/.673/1.235s. Three Python checks, one CTest/profile,
seven explicit refusal domains and successful caller-rounding restoration across
four modes pass. Final checks:
`private/boot-camp-20261020/projection-checks-a3.json`; scoped receipt:
`private/boot-camp-20261020/projection-receipt-a1.json`.

Initial inspection/edit/configure/build/task/repair wall costs were not separately
instrumented. A truncated FTOL inspection was corrected before proof; an initial
probe's missing instruction-pointer import was fixed before canonical generation.
A later replay orchestration tried an old audit path and was refused; originals
and earlier receipts remain preserved. The final stride-read timing change was
native-only and reused all70 eligible originals. No failed proof was accepted.
App/owner binary hashes retain prior SDL scope; no GUI rerun was needed for this
unwired header. Local verification is not independent acceptance.

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake -S . -B build/native
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake --build build/native --target radar-projection-vectors --parallel 6
build/tools-env/bin/ctest --test-dir build/native -R '^radar-projection-domain$' --output-on-failure
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_radar_projection
# Supported original reuse; choose fresh report/audit names.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/NEW-PROJECTION.audit.json tests/compare_radar_projection.py \
  --exe private/official-1006-probe/game.exe --native build/native/radar-projection-vectors \
  --expectations private/boot-camp-20261020/projection-fresh-a1/expected.json \
  --report private/NEW-PROJECTION.json
```

For sanitizer choose `build/sanitize/radar-projection-vectors`; for the inspection
control add `--uncached` before the driver. Fresh generation uses new `--output`
instead of expectations/report and needs research-only Unicorn JIT. App commands
remain `./build.command`, `./test.command`, `./run.command --boot-camp-walk`.
Both games remain incomplete; only Apple Silicon macOS is tested.
