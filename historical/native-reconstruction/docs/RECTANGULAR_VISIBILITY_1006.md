# Rectangular visibility traversal

Complete6A7820 now traverses the actual Boot Camp map and calls the existing
Cell shroud/fog drawing effect on the retained Renderer alpha plane through an
explicit synchronous seam. This closes another entered6A3EF0 dependency before
phase1/full-frame integration needed for tutorial structure presentation. It does
not schedule frames, sight, arrival, discovery or Objective1. Its final animation
pass41F5E0 and the sibling41F1C0 remain required supplied effects; their registry,
image and alpha-combination effects are next. No queue reset or surface swap.

## Exact original proof

Target: supplied4,485,392-byte executable, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Complete6A7820 is894 bytes/249 instructions,
SHA256 `ff62a6b84d9f2c0ac5950ccada0e4a615ed8d8fd9250739dc22258b4e8a8a26a`.
The verifier fingerprints before using addresses and pins all entered spans.

1,068 complete roots execute actual vector/coordinate constructors437690/41B630,
affine591380, FTOL77F110, projection6A27A0, subtraction6AC850 and both41FDF0
intersections. They compare ordered query/draw/animation arguments and identities,
late mutations, final fields, immutable code, unrelated arena, caller stack and
saved registers. There are1,068 initial coordinate queries,33,968 permission
queries,23,485 Cell lookups/projections,46,970 intersections,349 visibility draw
requests and1,068 animation tails. **Map lookup/permission and both drawing
children are named supplied services in this original proof.** Separately verified
kernels and actual native owner composition retain their separate evidence scopes;
this is not a nested-original whole-frame or pixel proof, nor an original-game
observation. Cell/raster proofs remain in CELL_VISIBILITY_DRAW_1006.md.

Initial input is wrapped(origin + requested position - viewport position), with
float32 stores before the existing affine transform. Its output uses FTOL's low32
then clamps each signed coordinate to at least zero; Z is fixed zero. The initial
full-coordinate map query's **returned Cell point** supplies the traversal start,
with wrapped16 X-minus2 and unchanged Y. It is not replaced with the input point.
Requested dimensions are read after that query. Cached row count is height/15+17;
column count is width/60+4, signed division toward zero and wrapped32 sums. The
terrain-present global is queried even for nonpositive extents. When entered,
rows interleave offsets(row/2,(row+1)/2), and each column increments X/decrements Y
with16-bit wrapping. Nonpositive column counts have no observable row effects.
An execution bound refuses positive traversals above1,048,576 Cell visits.

Each raw permission result uses its low byte. An admitted Cell is looked up
before projection. Projected world coordinates come from the traversal point:
`((component*256+128)/256)*256`, not a usual Cell center. Negative components
therefore shift toward zero. The projection uses Z0 and late origins are subtracted;
X subtracts30, Y does not subtract15. A60x30 rectangle uses that X and relativeY
plus viewportY. The first intersection's first operand is this diamond and its
second is the current requested rectangle. The second intersection's first
operand is the viewport. Preserve this operand order under wrapping. Only a
positive clipped result draws the saved Cell identity. Its screen point uses
current viewportX/Y. The caller's original requested-rectangle identity is always
forwarded to41F5E0 afterward, including terrain absent or zero iterations.

Cases cover negative/division-boundary dimensions, raw low-byte permissions,
word extrema and row/column wraps, negative-center projection, finite/cancellation/
large matrices, float32 and FTOL low32/clamp boundaries, wrapped/nonzero clips and
late request/origin/viewport/terrain mutations. Current native is compared against
unchanged original-only answers using supported explicit reuse.

## Actual owners and supplied boundaries

`BootCampVisibilityWorld::drawVisibilityRectangle` binds full-coordinate lookup,
word lookup and the existing recovered full-map diamond permission to the actual
map/table/Cells/shared fallback. The common `cellAtIndex` retains table resolution,
fallback point effects and query counters for both existing word and new full-
coordinate paths. Full lookup computes the index from full signed quotients before
word truncation of a fallback point; it does not truncate before indexing.

`Renderer::drawVisibilityRectangle` borrows its actual origin/viewport and the same
supplied planar inverse coefficients used by its existing viewport producer. Both
callers share one immutable matrix association; the recovered affine kernel is
unchanged. Original matrix initialization, camera controls/recalculation cadence,
height scale/startup and terrain-global presence association remain supplied.
The existing FTOL low32 consumer is factored into one shared helper and its636
parent/probe plus688 joined-matrix original answers are replayed with current native.
Neither earlier proof is relabeled as this rectangle proof.

The actual-owner test composes full and flagged dirty6A3EF0 rectangle requests
through this traversal, the actual masks and original SHROUD/FOG bytes into the
existing alpha vector. It requires positive alpha stores/mask queries and one
animation request per rectangle, retaining the original request identity. Existing
assertions require unchanged colors/depth, locks, dirty slots/capacity tails,
Cell queues and source world. The animation tail is recorded as a pending effect;
it is not a no-op implementation adopted by the runtime. Runtime scheduling is
off. Initial visibility, map/startup and cache boundaries retain their prior scope.

No parallel map/Cell/alpha representation, original runtime execution or new
runtime executable read is introduced. No public authored code/dependency or
proprietary content is shipped. Both games remain incomplete; only Apple Silicon
macOS is tested. Local verification is not independent acceptance or whole-frame
fidelity. Preserve genuine sight/arrival and mission-effect gates to Objective1.

## Commands

```sh
./build.command
./test.command
build/native/boot-camp-walk-check private/official-1006-probe
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest \
  tests/test_rectangular_visibility.py tests/test_tactical_viewport.py \
  tests/test_tactical_viewport_matrix.py
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/NEW-rectangle.audit.json \
  tests/compare_rectangular_visibility.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/rectangular-visibility-vectors \
  --expectations private/rectangular-visibility-20261019/fresh-a1/expected.json \
  --report private/NEW-rectangle.json
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/NEW-viewport.audit.json \
  tests/compare_tactical_viewport.py \
  --exe private/official-1006-probe/game.exe --native build/native/tactical-viewport-vectors \
  --expectations private/tactical-viewport-20261019/fresh-a1/expected.json \
  --report private/NEW-viewport.json
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/NEW-viewport-matrix.audit.json \
  tests/compare_tactical_viewport_matrix.py \
  --exe private/official-1006-probe/game.exe --native build/native/tactical-viewport-matrix-vectors \
  --expectations private/viewport-matrix-20261019/fresh-a1/expected.json \
  --report private/NEW-viewport-matrix.json
env DEVELOPER_DIR="${DEVELOPER_DIR:-/Library/Developer/CommandLineTools}" \
  build/tools-env/bin/cmake --build build/sanitize --parallel 6
# Substitute build/sanitize runners for sanitizer checks. No SDL target there.
./run.command --boot-camp-walk
./run.command --boot-camp-walk-smoke-test private/NEW-SDL
```

Choose unused output names. Explicit `--expectations` checks original executable,
transitive oracle/input/environment and receipt identities, always executes current
native, and reports actual hits/misses. Fresh generation substitutes
`--output private/NEW` for expectations/report; Unicorn remains research/test-only.
See FRAME_TERRAIN_REQUESTS_1006.md and CELL_VISIBILITY_DRAW_1006.md for retained
alpha/caller/mask comparisons. Walking remains the existing playable mode; these
new explicit drawing dependencies are unscheduled.

## Validation and next work

Original generation17.203s; its first original/native comparison passed. An initial
local input-domain check excluded the generator's own default height80; corrected
before generation. A stale private validation-script matrix-expectation path was
corrected before comparisons; no original expectation or scope was changed. The
new vector target explicitly uses strict rounding/no contraction, then replays
unchanged originals. Four evidence guards cover domain/executable/receipt/scope and
native-only reuse versus original invalidation. Native guards cover missing
children, unconditional animation for absent terrain and the execution bound.

Current totals/costs, source and delivery identities are in HANDOFF and
`private/rectangular-visibility-receipt-a1.json`; successful guarded replays retain their true scopes. Setup diagnostics remain
in the task transcript. Initial/focused builds,
strict-runner rebuilds, manual inspection/repair and total wall time are unmeasured.
Concurrent costs are nonadditive. No unchanged original matrix was regenerated.
Next recover complete41F1C0/41F5E0, their actual alpha-animation registry/cache/table
owners and remaining entered phase1 effects, then actual0/1/map-callback/2 on the
same owners before frame/reset wiring. Do not substitute an empty supplied registry
or a drawing request for recovered startup/scheduling or a tutorial transition.
