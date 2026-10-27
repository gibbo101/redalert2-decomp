# Existing frame depth and alpha clear/scroll

The shared region kernel now also recovers complete alpha4110B0; see
[FRAME_TERRAIN_REQUESTS_1006.md](FRAME_TERRAIN_REQUESTS_1006.md). Original depth
and plane proofs below retain their independent scope and are replayed against
current native; no frame scheduling follows from the explicit composition.

Complete775D60/410C50 and776160/411050 now share one readable native plane
kernel on the Renderer’s existing depth and alpha backing. These are entered
children of6A45A0: full stationary initialization clears depth then alpha, and
camera displacement scrolls/clears exposed strips in that same order. They are
needed before adopting the original frame protocol for Boot Camp structures.
The dispatcher, surface swaps, remaining draw children and frame/sight/arrival/
Objective1 scheduling remain incomplete and off. This is a frame dependency,
not an accepted tutorial transition or whole-game completion.

## Original evidence and numeric behavior

The exact supplied executable is4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. The verifier fingerprints both complete
1,011-byte scrolling bodies, both57-byte clear bodies and the previously
recovered stock BSurface fill/clipping/lock/pitch children. Each original root
executes at its own original address; none is redirected or instruction-patched.

The scroll reads offset10 and width28 before checking displacement. Division
by2 and width is signed and truncates toward zero. A displacement whose absolute
X exceeds width or whose absolute Y exceeds height requests a full surface fill
with the low16 color bits, then writes base24=32768. **It retains offset10.**
Equality with a dimension enters ordinary scrolling, not that fallback.

Horizontal scrolling first writes raw wrapped32 `offset+2*dx`, then normalizes
through the common backing with one lower-bound addition and one end subtraction,
writing offset again. It clears one or two physical columns through actual
ordinary surface fill. Saved old column/width and late width/height reads after
an earlier fill remain separate. Negative and positive crossings use different
strip ordering; do not replace them with a linear memmove or modulo operation.

Vertical scrolling recomputes the signed row from the current horizontal offset,
subtracts dy from signed base24 with wrapping, writes the raw new offset and its
single-wrap normalized value, then clears one or two physical spans. The spans
use the same original bit1 prefix/dword-pairs/conditional-tail pattern as7761C0.
An unprefixed one-word span writes nothing. That span kernel is now shared with
the existing depth refresh, whose unchanged607 original answers are replayed.
Low16 color bits are replicated in dwords, including when the original argument
has nonzero upper bits. No lock is taken for direct vertical span writes.

The two full-clear wrappers load height before width, build `(0,0,width,height)`,
mask the color and call the current surface’s rectangle-fill slot. They do not
change offset10 or base24. The actual existing fill kernel is reused through a
new borrowed geometry/lock/backing view; the old owning facade uses the same
kernel. No copied pixel buffer or second rectangle-fill algorithm is introduced.

The accepted native profile uses positive bounded scroll dimensions, a nonnull
common allocation without32-bit address-space wrapping, relative fields/ranges
below2GiB and backing-safe stores. Signed negative intermediate offsets identify
the original pointer-below-begin branch in this normalized representation. Empty
full-clear dimensions retain the original fill early return. INT32_MIN scroll,
invalid division, unsafe backing/custom surfaces and fault compatibility refuse.
The shared span retains its existing1,048,576-word bound. Refusal may follow
originally ordered fields/writes; no rollback is claimed for unsupported inputs.
Callbacks borrow owners synchronously; store traces are observational.

## Proof and actual owners

1,804 complete original roots compare26,215 ordered pixel stores and6,869
ordered offset/base stores, rectangle/color requests, stock lock stores, final
fields and full backing hashes. Each depth/alpha routine runs separately. Cases
cover all quadrants, exact dimension equality and oversized fallback, offsets at
ring edges, odd/even row widths, two backing alignments, one-word omissions,
full clears/empty dimensions, low-word color masking and wrapped signed bases/
lock counters. Native byte backing and numeric-word backing both match. These
are authored probes with actual original children, not original-game observations.
Code/vtable/caller stack/return/callee-saved/whole-arena guards pass.

The Renderer now retains depth/alpha offset10 and base24 beside its existing
vectors and stock locks. `clearFramePlanes` and `scrollFramePlanes` explicitly
run depth before alpha using FFFF/007F. `refreshFrameDepth` and the previously
recovered Cell depth pass borrow those same offsets afterward. Startup/base/
allocation/stock surface association and invocation remain supplied. No new
runtime executable reads or original-code execution are added. Unicorn remains
research/test-only.

The actual queued-GI owner check now reaches its existing900-word Cell diamond,
then scrolls both actual planes, requires changed depth pixels and exact persistent
offset/base values, clears both planes and verifies that those fields survive.
It checks a subsequent ordinary depth refresh begins at the retained offset.
Color pixels, locks, cache references, Cell queue slots/count/tails, source owners
and clone bindings remain protected. This is native integration, not a newly
rooted nested-original whole frame or independent acceptance.

Remaining drawing children do not all consume nonzero plane scroll/base state.
Do not schedule these methods as a complete camera implementation, infer complete
pan fidelity or use them to justify an isolated queue reset. The current native
terrain-cache/display adapter retains its supplied scope; original frame
construction, swaps and composition remain separate work. Base RA2 and Yuri’s
Revenge remain incomplete; only Apple Silicon macOS is tested.

## Build, reuse and try

```sh
./build.command
./test.command
build/native/boot-camp-walk-check private/official-1006-probe
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest tests/test_frame_plane.py
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/NEW.audit.json \
  tests/compare_frame_plane.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/frame-plane-vectors \
  --expectations private/frame-plane-20261019/fresh-a1/expected.json \
  --report private/NEW.json
env DEVELOPER_DIR="${DEVELOPER_DIR:-/Library/Developer/CommandLineTools}" \
  build/tools-env/bin/cmake --build build/sanitize --parallel 6
# Substitute build/sanitize runners for sanitizer comparisons and owner checks.
./run.command --boot-camp-walk
./run.command --boot-camp-walk-smoke-test private/NEW-SDL
```

Choose unused private audit/report/capture names. Original executable/oracle/
transitive Python/environment/command/receipt identities remain separate from
current native sources and binary; explicit `--expectations` always runs current
native and reports actual hits/misses. Fresh scope uses `--output private/NEW`
instead of expectations/report and needs authorized host JIT access. Unchanged
original fill/frame/TMP matrices retain their own documented explicit reuse and
provenance; never cache native verdicts or relabel their receipts.

## Current validation and cost

Normal and sanitizer profiles each reuse7,453 original answers with zero misses:
1,804 plane roots,751 fill roots and4,898 retained frame/Building roots. Each also
replays424 historical composition answers. Every replay runs the current native
binary; unchanged original answers were not regenerated.220 normal and219
sanitizer CTests,31 focused Python guards, both actual-owner checks and the
256-tick ordinary SDL selection/movement/drawing regression pass. Horizontal GI
capture hashes remain unchanged. Local verification is not independent acceptance.

Fresh original generation succeeded on its first attempt in1.866s. Final builds
took83.398s normal/80.598s sanitizer; owner checks10.699s/84.709s; CTest entry
points10.124s/24.844s; Python4.074s; SDL7.430s. Plane replays took1.558s/.847s,
fill replays.468s/.550s and historical composition8.671s/7.015s. Concurrent costs
are nonadditive. Initial focused build, manual inspection/repair and total
milestone wall time were not measured. Full commands, timings, source/runner
hashes and immutable expectation identity are retained in
`private/frame-plane-receipt-a1.json`; individual logs/audits are under
`private/frame-plane-20261019/validation/`. Fresh expectations are
`private/frame-plane-20261019/fresh-a1/expected.json`.

Next complete the remaining entered6A45A0 children and the actual
0/1/map-callback/2 protocol on these owners, including remaining nonzero-offset/
base consumers, before production wiring. Phase3 or isolated queue-reset tails
cannot substitute for that protocol. Genuine sight/arrival and mission effects
remain separate gates to the first playable Boot Camp objective.

No workers, Windows/transfer/download/system/Xcode/DRM change, public authored
code/dependency or proprietary shipment. The full reconstruction goal stays active.
