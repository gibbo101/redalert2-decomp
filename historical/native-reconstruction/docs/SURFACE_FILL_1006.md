# Software surface rectangle fill

`src/render/SurfaceFill.hpp` recovers complete base774390/7743C0 for ordinary
nonnull one- and two-byte BSurface allocations. All751 fresh original calls match
return low byte, complete backing bytes, ordered byte/word/dword stores and final
lock depth. This is a separate render dependency; message consumers still record
fill requests and the application has no newly visible objective text.

## Evidence and behavior

Exact supplied target:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. `verify_surface_fill.py` checks this
identity, eleven complete instruction ranges and actual BSurface vtable79AEF8
slots4/5/23/24/28/29/30/31. No original instruction is replaced; no API stub is
entered. Unicorn remains test-only. Code/disassembly/receipts stay private.

The ordinary wrapper774390 obtains surface bounds and passes the requested
rectangle as clip and those bounds as fill to7743C0. The extended caller first
rejects nonpositive fill sizes, obtains bounds, intersects clip/bounds, constructs
the translated fill using clip X/Y plus fill X/Y, then intersects again. Actual
41FDF0 uses signed comparisons and wrapped dword additions/subtractions with
width/height rectangles, distinct from the font's inclusive-edge intersection.
Optional output adjustment pointers are null in this caller and remain out of scope.
Actual453E40 and435560 construct the rectangle and copy its starting point.

The original BSurface methods compute pitch as width*bpp, increment lock depth,
and return buffer+X*bpp+Y*pitch. The selected store path is chosen once using the
initial pointer alignment; odd pitches do not choose a new path on later rows.
One-byte fills replicate only the low byte. Two-byte fills on initially odd
addresses replicate only the low word. On initially dword- or word-aligned
addresses, paired stores use `(color<<16)|color`, preserving contamination from
upper color bits; single stores use the low word. The word-aligned path writes
its leading word on every row. Actual unlock decrements lock depth with wrapping.
Native little-endian byte stores and the optional store observer preserve each
original store's offset, width and value without relying on host alignment.

`FillSurface` borrows mutable backing with supplied dimensions/bpp/lock depth and
a byte offset relative to a logically aligned allocation. Geometry/allocation/
initial pixels are supplied, not original surface construction. Other pixel
formats and out-of-backing stores refuse. Null locks, arbitrary pointer aliases,
custom virtual surfaces, surface allocation/destruction and fault compatibility
are not recovered. Refusal may follow writes/lock changes; no rollback is claimed.

The pinned unlicensed YRpp `Surface.h` was used only for slot-name hypotheses.
Exact-base RTTI independently locates BSurface79AEF8 and DSurface7A0BE4.
DSurface has different fill slots4AB4F0/4AB520; bounded inspection shows its
software fallback calls7743C0 at4AB70F. That wrapper and its DirectDraw/recovery/
lock services have NOT been differentially verified here. The actual message
surface/startup association is still open. Do not infer that the original message
UI used BSurface, or silently substitute this fixture for its supplied fill leaf.
No public/YR/recomp code, new dependency or runtime executable read was added.

## Verification and costs

Canonical original expectations:
`private/boot-camp-20261018/surface-fill-fresh-a3/expected.json`, SHA256
`d7aa3ff5ab72ee549925745aac0b776c487bd2c037c7441e2145e74577a2804f`.
751 calls include716 ordinary wrappers,751 extended roots,1,470 intersections,
703 actual locks/unlocks and complete original pitch/bounds/bpp helpers. Cases
cover both formats, all four initial alignments, odd/even pitch, narrow and paired widths,
upper color bits, clipping/translation/empty edges, wrapped lock depth and
bounded extreme rectangle rejection. These are isolated original-routine tests,
not live game observations or whole-frame fidelity.

Every call guards code/vtable/rectangles, caller stack/return/callee-saved
registers and unrelated arena/padding. Normal/sanitizer/uncached replays each
retain751 original hits/zero misses; source/binary/input/receipt/runner identities
remain explicit. A1/A2 are preserved; A3 refreshed after verifier/driver cleanup and has
identical commands/outputs. No original/native result cache was added.

Both full builds and129 normal/128 sanitizer CTests pass. All1,410 Python tests pass in31.409s, including three new evidence tests
covering input/scope/receipt/source guards. All23 prior application/
message/owner runners are hash-identical, preserving closed original and SDL
baseline scopes without rerunning their finalizers. No runtime source changed,
so there is no new SDL acceptance claim. See the private checkpoint receipt for
Python discovery outcome, exact command records and identities.

Fresh A3 original execution0.484s; CTests1.67/10.32s. Driver/replay costs are in
the private reports. Build/repair/review/approval overhead was not separately
timed. Prior original expectations remain immutable; no new cache was warranted.
Local verification is not independent acceptance.

## Commands and next integration

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
./test.command
DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

env PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/surface-fill-next.audit.json tests/compare_surface_fill.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/surface-fill-vectors \
  --expectations private/boot-camp-20261018/surface-fill-fresh-a3/expected.json \
  --report private/surface-fill-next.json

./run.command --boot-camp-walk
```

Use new audit/report paths. Select the sanitizer runner or add `--uncached`
before the driver for controls; fresh execution replaces expectations/report
with `--output private/NEW-DIRECTORY` and requires the local Unicorn JIT permission.

Next verify the relevant message-surface wrapper/association or explicitly choose
a temporary native software-surface policy, then join actual raster fill to
message drawing and preserve full warm clone/source isolation. Ordinary SDL
clock/update/drawing and visible objective-text acceptance follow. Cursor lines,
startup layout/color ordering/audio and live sight/arrival/effects still have
their separate gates; Boot Camp Objective1 and both games remain incomplete.
