# Committed infantry Walk movement

This internal dependency unblocks Boot Camp Day 1 infantry movement. It is not
yet connected to the static preview: initial/next subcell selection, arrival,
ordinary command preparation, speed/occupation, animation and production-map
binding remain to be joined. Do not substitute tank Drive or synthesize tutorial
success. Selection/action scheduling and genuine discovery still precede the
first objective transition. See [BOOT_CAMP.md](BOOT_CAMP.md).

## Identity and recovery

Supplied `private/official-1006-probe/game.exe` was freshly fingerprinted:
4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage and reported no-CD provenance remain separate;
pristine authenticity is unverified. Private inspections/receipts live under
`private/infantry-walk-20261018/`.

Pinned YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88`
`WalkLocomotionClass.h`/`LocomotionClass.h` provide naming/layout hypotheses only.
No identified license; no headers/code incorporated. Its YR constructor address
does not apply to base. Base GUID7A1FA0 independently leads to constructor71DE00,
ILocomotion table7AEAD8 and IPersist table7AEBA0. Actual Infantry table7A3540
supplies dispatch identities, checked by the verifier. No new public code,
extracted table, runtime executable read or dependency is added.

`processCommittedWalk` implements complete interface Process71DFF0 paths through
Movement_AI71E220 with a selected nonempty head and integer planar distance>=17.
The Walk destination/head and raw34/35/36 bytes are distinct from Drive records.
Actor coordinates/marked74/bridge79, body Facing, immobilized3FC, percentage468
and57A/5A1 bytes are borrowed. Existing Foot location/height, Facing, bearing and
quantized sqrt/sine/cosine algorithms are reused. The simulation code has no
SDL, asset-loading or rendering dependency; numeric services are supplied.

Preserved behavior includes processing35 entry/exit, reallyMoving36, signed
immobilization, percentage stores, speed-before-5A1 clear, repeated coordinates,
immediate body turn, actor-Cell query before raw coordinate reread, signed
heading minus3FFF, separate sine-Y/cosine-X conversion, signed /256 and word
truncation, same-Cell marked-byte save/restore, and crossing Mark/placement/
old-Cell/new-Cell/bridge/height/Mark/current-Cell/dirty order. Bridge levels are
signed bytes and the comparison subtracts4 in widened signed arithmetic. Raw
moving34 is returned, not reallyMoving36. Both paths clear57A. Host FP rounding
is restored even on native refusal; entered service faults retain prior writes.
There is no rollback claim.

The supplied immutable radians-per-facing scalar is computed as the prepared
direction pi / -32767 under round-to-nearest. Its double bits independently
match original79B620. It is not the renderer's heading-step scalar. Numeric
tables remain in existing private hash-checked prepared data. Initial actors,
type/Facing/global associations, selected subcell, speed, Mark, floor, map lookup
and dirty effects remain supplied. Diagnostic Mark mutations test late reads;
they are not gameplay observations or recovered occupation behavior.

## Verification and cost

Canonical `fresh-a1/expected.json`/receipt match **624 complete original roots**,
616 actual active interpolations,408 crossing dirty effects,1,160 Mark calls and
7,261 selected stores. Coverage includes cardinal/diagonal/quantization headings,
negative coordinates and speed, zero speed, raw bytes, signed immobilization,
bridge levels/flags, nested Mark mutations and active Facing timers. Actual
numeric/Facing/coordinate/location/height children execute unchanged; only named
services are intercepted. ABI, callee-saved registers, caller return/tail, code/
tables and every other arena byte are audited. Opaque Facing upper words/timer
padding are excluded from value comparison. Selected traces are not an exhaustive
read or whole-actor store proof. Original instructions are not patched.

Normal and ASan/UBSan `replay-*-a1.json` execute current native code against those
immutable originals; source/input/runner/receipt guards remain. Original identity
and current native-source identity are separate, allowing eligible native repairs
without regenerating original answers. Four native guards cover missing head,
arrival refusal/FP restoration, missing speed with preceding stores retained,
and immobilization/raw moving return. Four Python evidence tests and the three
focused mission/Walk CTests pass in normal and sanitizer builds. This unwired
checkpoint does not require unchanged original matrices, broad regression or new
SDL acceptance; the previous static preview/two-tank evidence retains its scope.
Local verification is not independent acceptance or original-frame fidelity.

Measured driver costs: fresh1.60s (original1.296s/native0.028s), normal replay0.241s
(native0.017s), sanitizer replay0.346s (native0.095s). Wrapper/tool wall samples
include separate overhead and are not additive. Focused CTests0.13s/0.30s and
Python tests0.028s. Build, manual repair and total task wall were not separately
timed. The initial range-verifier failure exposed four incomplete byte extents;
aligned disassembly fixed extents without patching original instructions. Early
exploratory unaligned dumps are not proof. No new cache framework was justified.

## Reproduce

```sh
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/native --target walk-movement-vectors --parallel 6
build/native/walk-movement-vectors --guards
env PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_walk_movement

# Use new private report/audit names; executes current native code, zero originals.
env DEVELOPER_DIR=/Library/Developer/CommandLineTools PYTHONHASHSEED=0 \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/walk-next.audit.json tests/compare_walk_movement.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/walk-movement-vectors \
  --render-data private/derived/ra2-1006/render-data.bin \
  --raster-data private/derived/ra2-1006/raster-data.bin \
  --direction-data private/derived/ra2-1006/direction-data.bin \
  --expectations private/infantry-walk-20261018/fresh-a1/expected.json \
  --report private/walk-next.json
# Separate sanitizer replay: build/sanitize/walk-movement-vectors.
# Fresh originals, only if original/proof dependencies change: omit expectations/
# report and use --output private/walk-new-fresh; new audit name, authorized Mac
# host JIT context. No Wine/original execution is added to the native application.
```

Public application entry points remain `./build.command`, `./test.command` and
`./run.command --boot-camp-preview`. That preview still explicitly refuses RMB
walking. Next recover arrival/subcell handling and ordinary Walk preparation,
then join the existing production map and actual SDL controls before claiming a
playable first lesson. Only Apple Silicon macOS is tested.
