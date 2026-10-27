# Viewport composition with the existing affine transform

The actual Renderer viewport now uses the existing recovered point-transform
kernel below complete6A9170. This closes a supplied child on the camera/Cell
redraw path needed for live Boot Camp sight and Objective1. It does not enable
sight, clear frame queues or complete a playable lesson.

## Recovered composition and remaining boundaries

Exact supplied executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Complete6A9170(289 bytes),591380(120
bytes) and77F110(61 bytes) execute unmodified in one original call. No child
probe substitutes for the transform or FTOL in this proof.

`TacticalViewportMatrix.hpp` composes the existing viewport parent and
`voxelTransform`; it creates no second viewport owner or alternate numerical
kernel. The transform retains the original row-specific multiply/add order,
53-bit toward-zero intermediate operations and final float32 stores. Parent
wrapping, signed dimension halves, float32 input stores, FTOL low32 extraction
and signed division remain unchanged. Nested FP scopes restore host rounding,
including observer exceptions. Exception/status flags are not compared.

The Renderer supplies float32 planar matrix coefficients256/60 and256/30
instead of its former authored double-division callback. Original matrix
initialization/association, camera quantization, zoom and recalculation cadence
remain supplied. This does not establish the original inverse-camera matrix.
Projection/picking and the Cell redraw view retain the same existing origin
owner. Complete dynamic traversal still has its prior supplied inverse callback;
this change makes no new claim about that separate profile.

688 joined original calls compare ordered viewport stores, transform input and
output float32 bits, final owner fields, unchanged matrix/center/dimension/code
inputs, unrelated arena bytes, caller stack and saved registers. Original entry
counts are688 viewport,688 transform and1,376 FTOL. Inputs include wrapped signed
centers/dimensions, identity/planar/cancellation/large matrices, finite float32
extrema, subnormals, signed zero and float32 overflow under toward-zero. Matrix
NaN/infinity inputs and alternative FP environments are outside this profile.
Both current native profiles explicitly reuse688 new answers and636 unchanged
parent/probe answers:1,324 hits/zero misses per profile. The old probe expectations
remain unchanged and retain their separate scope; no old original matrix was
regenerated. Native results and current native identities are always recomputed.

The actual Renderer owner check additionally compares a supplied1024x720 camera
at317,-923 against the joined original's six fields:-195,-1283,-48,-39,19,52.
Existing center/pan/zoom -> actual GI Cell/queue tests retain frame stamping,
clipping, prior entries and source isolation. Ordinary eight-direction walking,
Stop/repeated orders and refusal checks remain. Full normal/sanitizer builds,
203 normal/202 sanitizer CTests, eight focused Python tests, test.command and
actual SDL256-tick input/drawing acceptance pass. Both horizontal captured
frames were inspected after lossless PPM-to-PNG format conversion. These are
local checks, not independent acceptance or original whole-frame fidelity.

## Actual frame caller: inspected, not recovered

The verifier now pins complete4E0B30..4E0C4F(288 bytes/92 instructions), SHA256
`7e13a6bd5b35ed3e71fda9248902b9124204bb807b191ede0981fa5c65d7ba42`.
The complete caller saves current surface83995C, replaces it with839964, invokes
mouse-global839C68 virtual40(surface,0), then reads and clears the actual map's
mode+C. It invokes complete6A45A0 in phases0,1,2. Map virtual40 runs between
phases1 and2. Each phase reloads the Tactical receiver83996C and surface839964;
do not replace them with one receiver/surface snapshot across child calls.

Only the low byte of each of two uninitialized stack words is written: mode!=0
for the shared full argument, and mode==2 for the intermediate map virtual40
argument. The complete words are forwarded. Preserve or explicitly bound their
upper bytes in an executed caller fixture; inspection does not justify silently
normalizing all forwarded words to0/1. The inherited table entries7A6520/24/28
pin4E0B30/6A12D0/4E0C50 respectively. Runtime receiver construction and the
complete intermediate child are not established by these table facts.

After phase2 the caller conditionally invokes mouse virtual40 with surface839948
and1, clears its pending byte, optionally draws globalA40EEC, calls message
5B5B30 on fixedA3DC70, handles two more optional UI branches, calls mouse
virtual3C(surface,0), invokes map virtual44 and restores its saved surface.
These are ordered inspection leads, not an executed complete dispatcher proof.

Earlier complete6A45A0 inspection remains valid: static6A4350 precedes Cell
countE0 clear6A4DFA; dynamic6A93F0 occurs later, and finalD7D clear6A5264 occurs
after additional children. Phase0 and phase1 return before the final dirty clear.
No isolated tail reset or invented frame cadence has been bound to runtime.
Private inspection records: `private/viewport-matrix-dispatch-inspection-a1.json`
and `private/tactical-frame-20261019-inspect-a1/4e0b30.txt`.

Next recover the complete entered frame paths with their actual phase protocol,
live owners and entered children, retaining the existing shared queue. Then
finish the remaining live movement/sight and mission effects needed for ordinary
SDL Objective1. Arrival/sight/Objective1 remain off. No worker, Windows/system
action, public implementation, extracted table or runtime executable-read
expansion was introduced. Only Apple Silicon macOS is tested. Base RA2 and YR
remain incomplete; the full goal stays active.

## Commands, reuse and costs

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
 test_tactical_viewport_matrix test_tactical_viewport
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
 tools/run_evidence.py --audit private/viewport-matrix-next.audit.json \
 tests/compare_tactical_viewport_matrix.py \
 --exe private/official-1006-probe/game.exe \
 --native build/native/tactical-viewport-matrix-vectors \
 --expectations private/viewport-matrix-20261019/fresh-a1/expected.json \
 --report private/viewport-matrix-next.json
# Substitute sanitizer runner and new output/audit names for sanitizer replay.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
 tools/run_evidence.py --audit private/viewport-parent-next.audit.json \
 tests/compare_tactical_viewport.py \
 --exe private/official-1006-probe/game.exe \
 --native build/native/tactical-viewport-vectors \
 --expectations private/tactical-viewport-20261019/fresh-a1/expected.json \
 --report private/viewport-parent-next.json
./run.command --boot-camp-walk
./run.command --boot-camp-walk-smoke-test private/viewport-matrix-sdl-next
```

Fresh original generation.170s. Current cost records, source/binary/expectation
identities and logs are in `private/viewport-matrix-receipt-a1.json`. Build,
configuration, SDL, review/inspection/editing and total task wall were not fully
measured; concurrent costs are nonadditive. PPM image viewing initially refused
the unsupported format; lossless PNG conversion enabled inspection. No code or
differential mismatch occurred. Proprietary inputs and private outputs stay ignored.
