# Tactical viewport producer on the actual renderer camera

Later production update: [matrix composition](TACTICAL_VIEWPORT_MATRIX_1006.md)
joins the existing recovered591380 kernel. The636 parent/probe cases below
retain their original scope and unchanged expectations.

Complete base6A9170 now produces the renderer's viewport origin and the Cell
redraw view. This removes the supplied origin arithmetic between Boot Camp's
camera and its recovered sight/Cell redraw path, before live Day1 sight and
Objective1 integration. The inverse matrix, camera controls/quantization/zoom,
frame scheduling and queue consumption remain explicit supplied/open boundaries.

## Evidence and behavior

Exact supplied executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage and reported no-CD provenance are separate;
pristine authenticity remains unverified. The verifier pins complete6A9170
(289 bytes/83 instructions) and actual77F110 FTOL(61 bytes/20 instructions).
The complete parent and FTOL execute unmodified in636 original calls. Inverse
591380 is a checked supplied probe using the caller's actual result buffer;
matrix construction/transform is not recovered by this proof.

`render/TacticalViewport.hpp` preserves eight ordered owner stores, including
initial center copies to B0/B4 before half-dimension subtraction. Signed halves
truncate toward zero and subtraction wraps32bits. Origin-minus60/minus30 passes
through float32 stores before the inverse callback, with Z0. The returned Z is
ignored. FTOL's low32 result is used, then signed-divided by256; converting
directly to signed32 or clamping would differ. NaN, infinity and out-of-signed64
results have low32 zero. Width and height are reread after the callback for
`width/60+2` and `height/15+4`, with wrapping sums. Inherited0E7F FP behavior is
the tested environment; the native scope restores host rounding on success and
refusal. x87 status/exception flags are not compared.

636 cases cover wrapped signed center/dimension extrema, float32 quantization,
all signed division boundaries, finite64/low32 behavior, NaN/infinity/subnormal
output bits, ignored Z, post-callback dimension changes and seeded full-width
inputs. The oracle checks ordered stores/inputs, full unrelated arena bytes,
allowed code ranges, code/center immutability, caller stack and saved registers.
Original-only expectations: `private/tactical-viewport-20261019/fresh-a1/expected.json`.
Both normal and ASan/UBSan comparisons explicitly reuse636 answers with zero
misses, plus349 unchanged Cell-redraw answers:985 hits/profile. No old original
matrix was regenerated. Original and current native identities remain separate.

## Actual owner integration

`Renderer` now owns the produced viewport fields beside its existing camera.
Projection, picking and terrain drawing use that origin through the existing
`viewportOrigin` path. `cellRedrawView()` exposes the same logical dimensions
and origin for synchronous world/Cell redraw composition. This is not a second
map or persistent mirrored viewport on the simulation owner. Recalculation on
camera/dimension changes is a host cache policy, not original frame cadence.
The inverse callback retains the authored planar transform; its matrix inputs
and visible-Cell region fields remain approximate. SDL picking, zoom and center
rounding are still host controls.

Actual renderer/world checks bind its321x241 viewport at zoom1.5 to the existing
GI Cell and shared redraw queue. Centered drawing queues that Cell; a far pan
at the next actual world tick stamps its frame without queue insertion; returning
at zoom2 appends the same actual Cell identity while preserving the prior entry.
Cloning/source isolation, existing warm-renderer checks and ordinary eight-way
GI movement pass. No queue is cleared to manufacture acceptance.

Both full builds,202 normal/201 sanitizer CTests, four Python evidence guards,
`test.command` and the actual256-tick SDL selection/walking/drawing/Stop/repeat
regression pass. Local acceptance is not independent or whole-frame fidelity.
Arrival/sight scheduling and ordinary Objective1 remain off. Only Apple Silicon
macOS is tested; both base RA2 and Yuri's Revenge remain incomplete.

## Frame consumer leads and next work

Exact-binary inspection of complete6A45A0 spans3288 bytes/904 instructions.
It calls recovered static redraw6A4350 at6A4D5C, resets Cell countE0 at6A4DFA,
calls dynamic traversal6A93F0 at6A4EED, and clears TacticalD7D at6A5264.
These are inspection leads, not a recovered/executed frame-parent proof. The
count reset and final flag clear occur at different points around other children;
do not move either clear to sight requests or bind an isolated tail as a frame.
Private inspection: `private/tactical-frame-20261019-inspect-a1/`.

Next pin the actual frame dispatch/arguments and recover an entered complete
ordinary path with existing shared queue/renderer owners and recovered children.
Then finish live movement/sight and mission effects needed for actual SDL
Objective1. No worker, Windows/system action, public implementation, extracted
table or new runtime executable read was introduced.

## Commands and costs

```sh
./build.command
./test.command
env DEVELOPER_DIR="${DEVELOPER_DIR:-/Library/Developer/CommandLineTools}" \
 build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/native/boot-camp-walk-check private/official-1006-probe
build/sanitize/boot-camp-walk-check private/official-1006-probe
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
 tools/run_evidence.py --audit private/tactical-viewport-next.audit.json \
 tests/compare_tactical_viewport.py \
 --exe private/official-1006-probe/game.exe \
 --native build/native/tactical-viewport-vectors \
 --expectations private/tactical-viewport-20261019/fresh-a1/expected.json \
 --report private/tactical-viewport-next.json
# Substitute the sanitizer runner and new outputs for sanitizer replay.
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_tactical_viewport
./run.command --boot-camp-walk
./run.command --boot-camp-walk-smoke-test private/tactical-viewport-sdl-next
```

Original generation.121s. Actual owner checks4.62/59.56s normal/sanitizer;
CTest wrappers2.40/17.60s. Full costs, source/binary/expectation hashes and logs:
`private/tactical-viewport-receipt-a1.json`. First native build failed on a new
test's field-name typo, repaired before accepted checks. Build/configuration,
SDL, manual inspection/edit/review and total task wall were not fully measured;
concurrent costs are nonadditive. Failed and successful logs retain their scopes.
