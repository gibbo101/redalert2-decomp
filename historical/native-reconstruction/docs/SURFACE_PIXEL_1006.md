# Stock surface pixels and mark/refresh composition

`SurfacePixel.hpp` recovers complete base774220 SetPixel with actual ordinary
BSurface lock/bpp/pitch/width/unlock algorithms. `SurfaceMarkPixelsBinding` joins
it below the existing6324A0 mark rebuild and634030 zero-mode parent, reusing their
single kernels and the same surface width fields. Independent surface pixel and
lock owners are borrowed, not mirrored geometry. This is a separate unwired
software-surface composition. Original radar surface construction/association is
not yet recovered; coverage and production SDL image refusals remain.

## Recovered writer and ownership

The writer copies point X/Y before calling lock. Stock411370 increments lockC with
wrapping, saves buffer14 before its queries, reads bytes10 for X, then calls pitch.
Stock4113C0 calls width7C before reading the late bytes10 for width*bpp. The lock
address wraps saved buffer + saved bpp*X + pitch*Y. The native view and explicit
width callback preserve this ordering. In the joined proof width7C is the same
actual refresh getter used by the mark parent, with no extra width query while
binding or obtaining the pure view.

A nonnull lock queries bytes10 again. Exactly2 writes the color's low word;
every other value writes its low byte. This differs from the mark palette's
independent format selection (palette format exactly1 reads a byte, otherwise a
word). Zero, negative and3/4 surface formats retain the original byte-store branch
when the computed address has valid backing. Upper color bits never contaminate
the stored value. Unlock4112F0 decrements lockC with wrapping; its return is ignored
and the writer returns true low-byte. A null lock returns false and **does not
unlock**, retaining the incremented depth and skipping the post-lock format query.

Neither writer nor stock lock clips X/Y against width/height. Negative coordinates
and coordinates outside the logical surface can still write valid supplied prefix/
suffix storage. Native backing guards protect host memory without changing that
rule. Byte and numeric16-bit backing use explicit little-endian stores, including
odd addresses and partial numeric-word writes. The existing `FillSurface` can be
borrowed through `surfacePixelView`; its fields and fill kernel are unchanged.

The null allocation profile is explicit and limited to a computed zero address.
A null base with a nonzero computed address, ambiguous byte/word storage and stores
outside supplied backing refuse. Bounds/refused width callbacks may follow a lock
increment; no rollback is claimed. Full arbitrary virtual surfaces, pointer aliases,
fault compatibility, device/DirectDraw behavior and original allocation/destruction
are not recovered. Allocation presence/offset/backing/geometry remain supplied.

The mark binding obtains a pure stable pixel view of the already selected receiver,
uses the actual entry's point and forwards the saved color by value. Its view borrows
that receiver's existing width directly, with separate bpp/offset/pixels/lock owners.
The optional entry probe can perform authored diagnostic mutations before the
writer copies X/Y, matching the guest's entry hook. Pixel-store/lock observers make
no gameplay queries or mutations. With no probe the join adds no extra service.
Construction performs no view/width query; its immovable scope restores the previous
pixel callback on normal exit or exception. View lifetime/startup and the stock
BSurface virtual24 association stay explicit; this is not a claim that original
radar surfaces were BSurface. Copy8/C0/CC/663D30 and nonzero632000 remain supplied.

## Original evidence and regressions

Exact supplied executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD and unverified pristine remain
distinct. Identity is checked before addresses; complete pixel and stock child
spans, original BSurface virtual associations and parent/mark spans are inspected.
Original instructions remain unchanged and execute only in research-only Unicorn.

All300 fresh standalone calls match low-byte returns, complete pixel backing,
ordered lock/pixel stores and final depth. They include244 actual unlocks and56
actual null-lock returns with no unlock. All544 bpp queries,300 lock/pitch/width
calls and the complete writer execute, with no supplied child interceptions. Cases
cover byte/word backing, all initial alignments, formats-3/-1/0/1/2/3/4, upper color
bits, negative/outside coordinates, wrapped products and lock extrema.

All950 fresh mark/refresh sequences also match, including475 complete zero-mode
parents and4,484 actual774220/lock/pitch/unlock calls. Actual bpp executes8,968
calls and width11,699. All prior mark diagnostic scenarios are retained with
alternating1/2-byte surface formats, four initial alignments and independent extreme
lock depths; complete pixels from both surfaces and ordered stores are compared.
No supplied pixel24 executes. C0/CC/resolver/copy remain supplied (4,484/3,234/
1,078/475 calls). The guest shares actual geometry/entries/bitmap/actor/House/
scheme/palette owners through the whole parent/child/pixel composition. Full arena/
padding, stack/callee-saved/return/input-code and entered-instruction guards stay
active. Fixture mutations are authored probes, not original-game observations.
No whole-frame, original surface-startup or ordinary objective claim follows.

Original-only expectations:

- `private/boot-camp-20261019/surface-pixel-fresh-a1/expected.json`, SHA256
  `9258371f89e98970e7b8efb370cfa88125987e5f91e7999f55568944984118e0`.
- `private/boot-camp-20261019/surface-mark-pixels-fresh-a2/expected.json`, SHA256
  `79b3790e46c3f677a1c202385bbde1dfde9319bd07be2e3562f04d9655157128`.

Original generation.081s/13.616s; native comparison.015s/.058s. Nineteen Python
checks, five focused CTests/profile and12 guarded normal/sanitizer/uncached replays
pass. Replays cover both new proofs, the rebuilt legacy mark runner retaining all
950 previous supplied-pixel outputs, and unchanged surface fill. The common native
mark fixture has a compile-time pixel variant; there is no second mark algorithm.
Existing original/source/input/runner/receipt guards are retained without relabeling
old evidence. No new cache/whole inventory refresh/closed finalizer rerun occurred.

The first joined proof failed its pending-return guard on sequence1: the derived
oracle did not process the nested width return4113C8 inside stock pitch. A bounded
diagnostic found identical arena/globals and the pending return. Only derived-oracle
bookkeeping changed; complete fresh A2 execution has its own source identity. Failed
A1 audit is preserved. No original/native comparison mismatch or native repair
occurred. Local verification is not independent acceptance.

Configs7.344s/9.000s; target builds4.901s/4.679s. Both-profile preflight checks
measured.012s/.152s/.176s/.370s. Other measured commands/checks, sources/runners and
retained SDL/owner hashes are in
`private/boot-camp-20261019/surface-pixels-receipt-a1.json`. Repair/task wall are
unavailable. Application/owner binaries retain the prior106-tick walking SDL baseline;
no runtime source changed or GUI reran. Only Apple Silicon macOS is tested.

## Commands and next integration

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake -S . -B build/native
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake --build build/native --target surface-pixel-vectors surface-mark-pixels-vectors surface-refresh-marks-vectors --parallel 6
build/tools-env/bin/ctest --test-dir build/native -R '^surface-(pixel|mark-pixels|refresh-marks|refresh|fill)-domain$' --output-on-failure
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_surface_pixel test_surface_mark_pixels test_surface_refresh_marks test_surface_refresh test_surface_fill
# Choose new private audit/report paths.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/NEW-MARK-PIXELS.audit.json tests/compare_surface_mark_pixels.py \
  --exe private/official-1006-probe/game.exe --native build/native/surface-mark-pixels-vectors \
  --expectations private/boot-camp-20261019/surface-mark-pixels-fresh-a2/expected.json \
  --report private/NEW-MARK-PIXELS.json
```

The primitive uses `compare_surface_pixel.py`, `surface-pixel-vectors` and its A1
expectations above. Use sanitizer runners or `--uncached` before the driver for
other profiles; fresh proof uses a new `--output` instead of expectations/report
with research-only JIT. Public commands remain `./build.command`, `./test.command`,
`./run.command --boot-camp-walk`. This recovery adds no gameplay control.

Next recover actual copy8 and surface associations, stock actor/resolver effects
and the nonzero632000 path; then join refresh/redraw/required House power to
coverage. Production actor/House/13C/refresh owners, startup/scale, full warm
previews and map-scan caller precede runtime image adoption. Diplomacy/action37,
ordinary SDL Objective1 and both games remain incomplete. No public/YR/recomp/
generated/lifted code or dependency was incorporated, no worker/Windows action/
download used, and no runtime executable-read expansion added.
