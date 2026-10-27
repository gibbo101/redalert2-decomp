# Linked surface clipping — supplied base

`clipSurfacePair` recovers complete775190..77535E and reuses the existing complete
41FDF0 null-adjustment intersection. This is a separate rendering dependency,
not yet wired to copy8, generic transfers, coverage refresh or the SDL application.

The supplied executable is `private/official-1006-probe/game.exe`, 4,485,392 bytes,
SHA256 `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage and reported no-CD provenance remain distinct;
pristine authenticity remains unverified. Addresses apply only to this identity.
No public implementation/reference code or new dependency was incorporated.

## Recovered behavior

Equal initial widths and heights select linked clipping. Destination negative
origins move the source origin and shrink both rectangles, then destination right/
bottom edges are clipped. Source negative origins then move the destination and
shrink both, followed by source right/bottom clipping. This branch uses bounds
width/height and ignores bounds origins. Preserve signed comparisons, wrapped
32-bit additions/subtractions, sequential stores and failed-call mutations.

Unequal initial sizes select two independent actual41FDF0 intersections. Each
requested rectangle is the clip argument and its bounds the input argument;
reversing these is unsafe with wrapped arithmetic. All four destination words
are stored before the source intersection. No scaling or equal-size repair is
performed. Both branches return true only when both final widths/heights are
strictly positive. The caller owns four distinct stable records. Aliasing is an
explicit native refusal before any write; original alias behavior is not claimed.
Store observers are passive. No clipping or transfer policy was added to SetPixel.

## Verification and commands

Canonical fresh proof:
`private/boot-camp-20261019/surface-clip-fresh-a3/expected.json`, SHA256
`5b22576d6d2f4d130c45e9935b0822d307813e7468510092c38ba190017c8828`.
All4,625 original roots and3,966 actual intersection children match ordered writes,
result byte and all four final rectangles. Cases cover independent negative edges,
ignored bounds origins, rejected/empty dimensions, unequal sizes and signed
extremes. The oracle audits every entered instruction, caller stack/callee-saved
registers, immutable code/bounds, permitted writes and the entire private arena.
Original instructions are neither patched nor replaced. No screenshot/fidelity
or original gameplay observation claim follows.

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake -S . -B build/native
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake --build build/native --target surface-clip-vectors
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_surface_clip
build/tools-env/bin/ctest --test-dir build/native -R '^surface-clip-domain$' --output-on-failure
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py --audit private/boot-camp-20261019/surface-clip-local.audit.json tests/compare_surface_clip.py --exe private/official-1006-probe/game.exe --native build/native/surface-clip-vectors --expectations private/boot-camp-20261019/surface-clip-fresh-a3/expected.json --report private/boot-camp-20261019/surface-clip-local.json
```

For fresh execution, use a new audit and replace `--expectations ... --report ...`
with `--output private/boot-camp-20261019/surface-clip-local-fresh`; never overwrite
a closed receipt. Fresh Unicorn execution needs host JIT permission. Sanitizer
uses `build/sanitize`; `--uncached` before the driver disables inspection reuse
while retaining all original/source/runner/receipt guards.

Fifteen Python checks, four focused CTests per profile and12 guarded replays pass
(clip/fill/pixel/mark-pixels, normal/sanitizer/uncached). Existing fill/pixel/mark
outputs are retained. Original generation .723s/native comparison .069s;
configure7.896s/8.845s and build2.028s/1.891s. Other measured check costs are in
`private/boot-camp-20261019/surface-clip-receipt-a1.json`; task/repair wall time was
not measured. A1 sandbox JIT exit132 produced no proof. A2 passed; correcting the
driver description changed source identity, so fresh A3 was generated and all
final replays use A3. No comparison mismatch or algorithm repair occurred.

## Remaining integration

Next join actual774F00 blitter selection and434AE0/434B40/7753B0 clip/lock/transfer,
using this single helper. Preserve transparent/opaque byte/word selection, low-byte
flag behavior, same-surface double locks, failure cleanup and transfer direction.
Alpha/depth planes and CRT overlap handling require their own explicit scopes and
proofs. Do not replace all transfers with memmove. Surface construction/association,
actor C0/CC/resolver663D30, nonzero632000 and production coverage owners remain
open. Existing application/owner hashes retain the earlier106-tick walking SDL
baseline; no runtime adoption or new SDL acceptance was performed here.
Build/run/test entry points remain `./build.command`, `./run.command
--boot-camp-walk`, `./test.command`. Ordinary SDL Objective1 and both games remain
incomplete; no runtime executable-read expansion or Windows action was added.
