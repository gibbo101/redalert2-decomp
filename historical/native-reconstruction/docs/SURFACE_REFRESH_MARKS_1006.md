# Surface refresh bitmap and actor marks

`render/SurfaceRefreshMarks.hpp` recovers complete6324A0..632612 and explicitly
joins it to634030's zero-mode finish callback through `SurfaceRefreshMarksBinding`.
The single existing refresh parent/getters are reused unchanged. The separate
composition borrows actual logical surfaces, bitmap storage, buckets/backings,
entries, actor/House fields and scheme/palette registries. It remains unwired to
coverage, production map scans and SDL. Copy8, actorC0/CC, resolver663D30 and surface
pixel24 remain named supplied services; this is not yet original raster output.

## Recovered ordering and mutable ownership

The initial first1218 is saved. Its height80 executes before width7C on the same
saved surface, rereading its table for the second query even if1218 was changed.
The clear length is wrapped signed width*height, signed truncating division by8,
then wrapped+1. It is not rounded-up unsigned pixel area: products-8..-15 clear
zero bytes, and-1..-7 clear one. Actual code clears groups of four bytes followed
by byte tails. Bitmap1270 is read after the dimension queries and is not cached
for subsequent entries. Native bounds refuse clears outside supplied backing.

The parent traverses all256 bucket records, each24 bytes in the original. It
rereads the1254 holder/root per bucket, saves that bucket's signed count and entry
backing, and skips nonpositive counts. Entries advance16 bytes. Later changes to
the root, current bucket's count or backing do not replace a saved traversal.
Changes to the saved backing's contents remain visible. The native owner uses
stable spans and explicit counts, with a4096-entry host bound after clear/bucket
reads. Neither backing/count bound is an original clamp or rollback guarantee.

For each entry the current surface pointer and entry actor are read before width7C;
x/y are read afterward. The bit index wraps width*y+x to signed32 bits. Its byte
index is arithmetic signed shift by3, while its mask uses the low three bits.
Negative indexes can access a legitimately supplied prefix before the logical
bitmap origin; they are not clamped to zero. Duplicate bits suppress the entire
actor/color/pixel path, across buckets as well as within a bucket. The bit is
stored immediately before any Owner or actor virtual queries. A later fault does
not undo it. Initial bitmap bytes outside the clear and all unrelated padding
remain untouched.

An entered mark saves the scheme selected from the actor's direct Owner1B4 and
that House's15F40 index before actorC0. If C0's low byte is nonzero, CC(0) is called:
a nonnull first result causes a second CC(0), and the second House/index selects
from the late global scheme registry. The two calls must not be collapsed. A null
first result invokes663D30 with fixed receiver7EBFC4 and EDX1. Otherwise the initial
saved scheme is retained even if Owner/registry changed during C0. Its mutable
palette/index fields remain late reads. Null/out-of-range consumed owners, schemes
and backing indexes explicitly refuse in the native representation.

Scheme330 indexes palette30C's174 data: format4 exactly1 reads an unsigned byte;
**every other** format reads an unsigned little-endian word. Final pixel24 receives
the late1218 receiver, the original borrowed entry point and the selected value.
If a callback changed that entry's coordinates after admission, drawing sees those
late coordinates while the earlier bitmap admission remains unchanged. Pixel return
status is ignored. Pixel/table association and actual raster stores remain supplied.

The scoped parent binding allocates its replacement before installation, performs
no queries, is immovable, and restores the previous finish callback on ordinary
exit or exception. The mark owner must outlive the binding. It adds no scheduling,
startup or renderer policy. Pure field views and the optional bitmap store observer
must not make gameplay queries or mutate the logical world.

## Original evidence and limits

Executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD and unverified pristine remain
distinct. Hash checking precedes address use. Complete6324A0, existing634030 and
stock geometry spans are verified; original instructions remain unmodified.

All950 fresh complete sequences match:475 standalone child calls and475 complete
zero-mode refresh calls with actual6324A0 beneath them. Actual children execute
950 height,7,215 width and950 rectangle getters. Supplied boundaries receive4,484
C0 and pixel24 calls,3,234 CC calls,1,078 resolver calls and475 copy8 calls. The
original parent/child/getters run in the same guest;6324A0 is not intercepted.

Cases cover saved versus late surface identities, live root replacement, retained
bucket backing/count, entry actor/point mutation, bitmap/registry/Owner replacement,
mutable palette/index fields, repeated CC versus null fallback, duplicate admission,
negative indexes with prefix backing, wrapped dimension products, signed empty
counts and byte/non-byte palette formats. Ordered dword/byte bitmap stores and
service arguments, full bitmap values, final fields and logical identities match.
Caller stack/return/callee-saved, input-code and complete arena/padding guards remain
active. Fixture mutations are authored diagnostic probes, not game observations.
Initial records, all bucket/startup associations, heap and palette data are supplied.
No original whole-frame, real pixel-service or ordinary objective fidelity follows.

Canonical original-only expectations:
`private/boot-camp-20261019/surface-marks-fresh-a1/expected.json`, SHA256
`71d110fbe5e1f9c191d1cf45c7f18a53e6d212d0b0c160f38554712ee02d5cc7`.
Original generation11.277s/native comparison.051s. Fifteen Python checks, four
focused CTests per profile and nine guarded normal/sanitizer/uncached replays pass.
Replays cover this join, the prior refresh parent and stock Techno coverage without
changing their original projections or relaxing source/runner/input/receipt guards.

Configure9.461s/9.007s; target builds4.197s/3.309s. Exact commands, remaining check
times and identities are in
`private/boot-camp-20261019/surface-marks-receipt-a1.json`. Initial temporary native
preflight accidentally sent only the last command to its second profile due to
variable shadowing, then rejected the row count. Full sanitizer output was captured
and validated before original execution; no runtime/oracle source repair occurred.
That wrapper failure is retained in the tool transcript and documented in the receipt.
Preflight total/repair/task wall measurements are unavailable. No comparison mismatch,
new cache, whole inventory refresh or closed finalizer rerun occurred. Local
verification is not independent acceptance.

Application and owner hashes retain the previous106-tick SDL walking baseline.
No runtime source changed or GUI reran; this step adds no player control or visible
behavior. Only Apple Silicon macOS is tested. Both games and ordinary SDL Boot Camp
Objective1 remain incomplete. No public/YR/recomp/generated/lifted code was copied,
no dependency or runtime executable read added, and no worker/Windows action or
download used.

## Reproduce and next integration

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake -S . -B build/native
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake --build build/native --target surface-refresh-marks-vectors --parallel 6
build/tools-env/bin/ctest --test-dir build/native -R '^(surface-refresh-marks|surface-refresh|surface-fill|stock-techno-coverage)-domain$' --output-on-failure
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_surface_refresh_marks test_surface_refresh test_surface_fill test_stock_techno_coverage
# Choose new private audit/report paths.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/NEW-SURFACE-MARKS.audit.json tests/compare_surface_refresh_marks.py \
  --exe private/official-1006-probe/game.exe --native build/native/surface-refresh-marks-vectors \
  --expectations private/boot-camp-20261019/surface-marks-fresh-a1/expected.json \
  --report private/NEW-SURFACE-MARKS.json
```

Use the sanitizer runner or `--uncached` before the driver for other profiles.
Fresh proof uses a new `--output` instead of expectations/report and research-only
Unicorn JIT. Public entry points remain `./build.command`, `./test.command` and
`./run.command --boot-camp-walk`.

Next recover actual surface pixel24/copy8, entered actor virtuals/resolver and the
nonzero-mode632000 pixel path, then join refresh/redraw and required House power
to stock coverage. BSurface slot24 points to774220: its entry through the first
return was inspected only as a next-child lead, not a complete recovery/proof.
Production actor/House/13C and refresh owners, startup/scale, warm discarded clones
and map-scan caller still precede runtime image adoption. Diplomacy/action37 and
ordinary SDL Objective1 remain open. Preserve the existing runtime refusals.
