# Building Type bounds from original SHP metadata

Complete45E290 now calculates Building Type bounds using signed original SHP
metadata, complete frame accessor45ED50, rectangle constructor42BCD0, secondary
release45E920 and the existing45EFE0 union algorithm. The existing Objective1
BuildingType owners retain the cache. The explicit application seam now composes
original image metadata -> Type cache -> Building cache -> Renderer dirty queue.
This replaces supplied test rectangles on that seam, a dependency of ordinary
Boot Camp sight redraws and the first objective. Runtime frame/sight scheduling
remains off; the application still draws Building markers, not recovered Building
sprites. A bounds proof is not a whole-frame or playable objective proof.

## Evidence and behavior

Exact supplied executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. The verifier pins complete45E290
(1,189B/370 instructions),45E920(51B/15),45ED50(108B/36),42BCD0(32B/10) and
45EFE0(240B/95).45E290 includes its final loop-tail jump after earlier returns;
a first-return slice would miss most of the routine. The BuildingType vtable
79D1F8's9C/C0 slots resolve to458CE0/45E790. Those image getters include demand
loading and are explicit supplied services here. CRT heap781D3B is also supplied.
All other listed parents/children execute unmodified in the oracle.

The parent compares cache11EC to the live empty-rectangle sentinel; a different
cache returns immediately without image queries. Null primary image returns the
sentinel without updating the cache. Otherwise it saves the primary signed16
frame count and dimensions, unions frame rectangles from both primary and
optional secondary images, optionally includes auxiliary11CC's frame0, subtracts
primary width/2 and height/2 with signed truncation, then stores cache X/Y/W/H in
order. Coordinates, dimensions and counts are signed16; union and centering use
wrapped32 arithmetic. Original union's extra1 on expanding right/bottom edges is
preserved by the existing shared kernel. No replacement bounding-box model was
introduced. The original inlined frame reads are H/W/Y/X, while45ED50 reads
X/Y/W/H. Borrowed views preserve both orders and the live count rereads beneath
saved loop bounds.

The secondary release decision is saved from TypeB98 before getterC0. If that
getter returns an image and the saved pointer was null, complete45E920 checks
nonzero byte13E2 and the current B98. It calls free on that current identity,
then clears B98 and byteB9C in order. It does not clear13E2. Thus getter/free
mutations can affect the later auxiliary pointer, flags and released identity;
primary dimensions remain saved. The native API requires an explicit heap service
when this path enters. It does not pretend to own or free application ShpImage
objects through an original heap implementation.

45ED50 compares unsigned index against a sign-extended signed16 count. Its
32-bit `index*24` displacement wraps before header lookup. INT_MIN therefore
aliases frame0 in the tested arena when the negative count admits that unsigned
index. The first native comparison incorrectly treated it as a vector index;
that failed attempt is preserved. The corrected accessor resolves wrapped
metadata offsets before checking the native backing. Offsets into unmodeled
header words/pixels or outside the borrowed backing refuse explicitly. This
is not an arbitrary guest-memory implementation. Ordinary parent loop indices
and auxiliary index0 are covered; positive count backing must actually exist.

369 original/native cases comprise355 synthetic/cache/width/count/union/release/
mutation cases and14 cases from the two supplied Objective1 SHPs: one complete
parent plus each of six frames per image. Raw signed headers agree with the
existing ShpImage decoder before use. The producer emits header inputs, never
native expected answers. The original oracle receives these exact inputs and
produces expectations independently. Caller stack, callee-saved registers, code/
vtable immutability and unrelated Type/image arena bytes are audited. Ordered
header reads, cache/release writes, service calls and returned rectangles match.
Tested backing has3 or6 frames, with an enforced fixture limit32; runtime metadata views borrow existing
ShpImage arrays, retaining the existing authored reader's own bounds. Null images,
negative/zero counts, zero/reversed rectangles, signed16 extrema, full32 cache values and supplied sentinel values, raw flags and late child mutations retain their scopes.

Original expectations and the first failed native comparison are under
`private/building-type-bounds-20261019/fresh-a1/`; the expanded six-frame source
profile is `fresh-a2/`. A1's original generation was valid, but its initial native
comparison failed on wrapped-index handling. It was subsequently replayed after
the native correction. A2 extends the original fixture/protocol with actual
six-frame inputs and passes369 cases. Do not relabel A1's failed comparison as
successful or use its old dependency identity as a current receipt.

## Existing owners, inputs and limits

`BootCampBuildingExpirationType::imageBounds` lives on the existing Type owner
shared by its Structures. `structureTypeImageBounds` resolves actual Type418
identity before calling the recovered parent. Clone value-copy retains its cache;
no separate Type mirror or persistent callback is stored. Current initial zero
cache/sentinel and null image associations are supplied startup. Borrowed image
views/providers are synchronous; their backing must outlive each call. Nonnull
secondary/auxiliary identities require explicit resolving/lifetime services.

The stock Temperate file associations for the two Objective1 images are supplied
and checked read-only through the existing AssetStore/ShpImage readers. Primary
images are supplied as loaded; secondary and auxiliary absence are supplied for
this stock composition. Full theater naming, Type image registration, demand
loading, allocation/free ownership, constructor state and cache invalidation
writers are not recovered by these bounds tests. No additional runtime executable
read is introduced. The authored SHP reader remains authored format code; this
change does not reclassify decoding or original animation/frame selection.

The same actual-owner tests now verify two independent original-image Type caches,
corresponding Building caches and dirty registration. Warm clones survive source
destruction; camera changes invalidate Building caches while retaining Type caches
without calling image getters again. Source Types/world/mission stay unchanged.
The earlier supplied32x40 rectangle test remains useful refusal/ordering coverage,
with its original supplied scope. Separate original Type and invalidation proofs
are not a combined original full-frame execution or independent acceptance.

The comparison reruns `building-type-assets` on every invocation and guard check.
Original reuse keys include the exact current emitted header commands/labels,
executable, complete original Python/environment dependencies and code inspection.
Current native input-producer binary/full asset fingerprints are recorded
separately; changing a native producer with identical emitted inputs does not
invalidate original answers. Input changes do. Source assets/producer output
must remain stable during the run. Current native answers are always recomputed.
Both profiles explicitly reuse369 Type plus525 prior invalidation expectations,
894 hits/zero misses per profile. No prior invalidation matrix is regenerated.

Normal/sanitizer actual owners, broad native tests, Python evidence guards and
SDL interaction results/costs are recorded in `private/type-bounds-receipt-a1.json`.
Actual-owner checks retain eight-direction GI movement. SDL retains horizontal
movement, Stop/repeated orders and selection; it does not invoke the unscheduled
bounds/frame seam.
Only Apple Silicon macOS is tested. No worker, new public code/dependency,
download, Windows, system/Xcode or DRM action was used. Both games and ordinary
Boot Camp objective completion remain incomplete.

Next recover the required loaded/demand image-getter paths and remaining static
frame children under complete entered6A45A0, retaining the inspected
0 ->1 -> map virtual40 ->2 caller protocol. Bind no isolated queue/dirty reset tail.
Tutorial sight/objective acceptance remains the integration target.

## Reproduce

```sh
./build.command
./test.command
env DEVELOPER_DIR="${DEVELOPER_DIR:-/Library/Developer/CommandLineTools}" \
 build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/native/boot-camp-walk-check private/official-1006-probe
build/sanitize/boot-camp-walk-check private/official-1006-probe
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest \
 test_building_type_bounds test_frame_invalidation
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
 tools/run_evidence.py --audit private/type-bounds-next.audit.json \
 tests/compare_building_type_bounds.py --exe private/official-1006-probe/game.exe \
 --native build/native/building-type-bounds-vectors \
 --asset-producer build/native/building-type-assets --data-dir private/official-1006-probe \
 --expectations private/building-type-bounds-20261019/fresh-a2/expected.json \
 --report private/type-bounds-next.json
# Substitute sanitizer runners/producer and fresh report/audit names for sanitizer replay.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
 tools/run_evidence.py --audit private/type-invalidation-next.audit.json \
 tests/compare_frame_invalidation.py --exe private/official-1006-probe/game.exe \
 --native build/native/frame-invalidation-vectors \
 --expectations private/frame-invalidation-20261019/fresh-a3/expected.json \
 --report private/type-invalidation-next.json
./run.command --boot-camp-walk
./run.command --boot-camp-walk-smoke-test private/type-bounds-sdl-next
```

Always use fresh report/audit paths. Proprietary header inputs, expectations,
inspection dumps, previews, binaries and receipts remain private/ignored.
Original A2 generation.170s; measured builds/checks/replay costs and unavailable
manual/repair/total wall costs are in the private receipt. Concurrent costs are
nonadditive. Existing duplicate ra2_render linker warning remains nonfatal.
