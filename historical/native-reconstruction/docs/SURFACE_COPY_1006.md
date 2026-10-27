# Stock software surface copy and refresh join

`SurfaceCopy.hpp` recovers774F00 copy8,434AE0 wrapper, ordinary434B40 transfers
with alpha8315B4/depth839C6C both zero,7753B0 clip/lock preparation, selected byte/
word blitters and their783290 CRT overlap child. `SurfaceCopyBinding` associates
this entry below the existing634030 zero-mode parent on the same borrowed surface
geometry, pixels and lock depths. This is a separate software-surface composition;
production refresh/startup and actual copy followed by actual6324A0 are not joined.

## Identity and evidence boundaries

The supplied base executable is `private/official-1006-probe/game.exe`,4,485,392
bytes, SHA256 `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain separate. Addresses only apply to this identity.
The verifier checks the complete parent/wrapper/preparation/stock children and
blitters, instruction spans and embedded branch tables of the CRT child, original
virtual associations and gradient3 record. No public implementation or dependency
was incorporated. Original instructions remain unchanged and research-only.

Allocation/geometry/stock association and entry state are supplied. Only explicit
stock rect/format/pitch/width/lock/unlock children are composed; arbitrary virtual
surfaces, construction/destruction, DSurface/DirectDraw and hardware behavior are
not claimed. Alpha/depth planes refuse when entered after preparation, retaining
already performed locks. There is no exception rollback. Backing faults and host
span/row execution bounds also refuse explicitly. Null-base nonzero lock addresses
retain the existing refusal. Full backing views carry logical allocation alignment;
partial overlapping host subspans are not an original-allocation association.

## Recovered ordering

774F00 queries source then destination bounds, copies both input rectangles and
calls the single [775190 helper](SURFACE_CLIP_1006.md). Only the **first** flag's low
byte selects transparent versus opaque; the second flag is unused. Exactly1
bytes-per-pixel chooses the byte blitter; all other values select the word blitter.
434AE0 queries source then destination bounds again.434B40 copies source bounds/
rectangle and7753B0 rejects nonpositive dimensions before clipping again.

Preparation resets its outputs, preserves strict signed wrapped overlap tests,
and marks reverse only for an overlapping same-surface copy with earlier source
Y, or equal Y and earlier source X. It translates rectangle origins by bounds
origins, locks destination first and source second. A failed destination lock
returns without unlocking. A failed source lock unlocks destination once, leaving
the failed source lock increment. Same-surface locks occur twice on one owner.
Actual411370/pitch/unlock are shared with774220; there is no second lock algorithm.

Transfer queries destination format and pitch, repeats destination pitch then
source pitch when the byte-width matches, and uses a single span only if pitches
also match. That span's signed count is the minimum of wrapped source/destination
areas. Otherwise it queries source then destination pitch and uses minimum height
but **source width** per row, including unequal-size copies. Reverse rows negate
pitches and separately query source/destination pitches to reach their respective
last rows. Successful cleanup unlocks destination then source; unlock results are
ignored. The return byte is true. Input rectangles remain unchanged at copy8.

Transparent byte/word entries skip zero source values and advance forward inside
each span, including the reverse wrappers. Opaque forward entries perform ordered
unaligned dword moves followed by byte tails, even on overlap. Opaque reverse
entries call783290: it chooses backward movement only for a higher overlapping
destination pointer, aligns destination with byte stores, then performs dword
stores and byte tails in the selected direction. Do not substitute universal
`memmove` or backward transparent traversal. Backing guards preserve explicit
little-endian byte/numeric-word behavior independently of host alignment.

`SurfaceCopyBinding` makes no queries during construction and resolves stable
borrowed owners only when copy8 is entered. Owner geometry must be the exact
receiver/source geometry, and its pixel width must borrow that same field. Binding
restores the previous callback on normal exit and faults. This is an explicit
software association, not evidence that original radar startup constructed BSurface.

## Fresh proofs and regressions

All3,804 standalone original calls match full pixel backing, query order, ordered
pixel/lock stores and low-byte return, including all eight forward/reverse entries
and2,884 actual CRT calls. There are7,280 locks,7,264 unlocks and23,508 actual pitch/
width queries. Cases include clipping failures, unequal dimensions, contiguous and
row copies, both formats, independent source format/pitch, all four alignments,
transparent zero suppression, low-byte flags, wrapped lock depth and null-lock
cleanup. Opaque overlap sweeps include1..80 pixels and both byte/numeric-word owners.

All642 complete zero-mode refresh parents match the same records through actual
copy8 and stock transfers, including repeated geometry queries and finish after
copy failure. Finish6324A0 is explicitly supplied in this proof. Existing mark
proofs still use supplied copy8: no combined copy-plus-actual-finish claim follows.
All300 fresh pixel and950 fresh mark/refresh sequences retain every earlier original
output after the shared-lock refactor. Complete caller stack/callee-saved/code/
input/write/arena guards remain active. Probes are authored fixtures, not original
in-game observations or whole-frame fidelity evidence.

Canonical private expectations:

- `surface-copy-fresh-a3/expected.json`: SHA256
  `3de6c41e81b3ccaa3a3c414048e72706be6d01735ef33ee08f2eb89e8303af97`.
- `surface-refresh-copy-fresh-a2/expected.json`: SHA256
  `27a945c60595edb4cb8b82e66ebf5731e0c5003f4d84815452904e45f292eee2`.
- `surface-copy-factor-surface-pixel-fresh-a1/expected.json`: SHA256
  `d7a245d4f9e88cc129dc03f4c1296535775ce31287187b6bb4fb25a9dd552dbb`.
- `surface-copy-factor-surface-mark-pixels-fresh-a1/expected.json`: SHA256
  `89879db9c2c15f3d9f8a8a67798d840ab0c167cc423967f06e2fb3a924889f76`.

All paths above are under `private/boot-camp-20261019/`. Final rebuilt runner
replays retain explicit current source/runner identities. Thirty-one Python checks,
eight focused CTests per profile and24 guarded normal/sanitizer/uncached replays
pass. No old closed finalizer or entire inventory was rerun. App/owner hashes retain
prior106-tick SDL walking scope; no runtime/SDL adoption or new GUI run here.

Original generation10.960s/1.677s and native comparison.199s/.047s for copy/parent;
shared-lock pixel/mark originals.070s/13.676s. Final configurations6.823s/9.155s,
fixture builds3.741s/3.499s. First build costs, preflight/check/fresh/replay costs
are retained in `private/boot-camp-20261019/surface-copy-receipt-a1.json`.
Task/repair wall was not measured. Inspection preflight caught CRT spans ending
inside instructions (branch-table zero entries overlap operands); corrected before
original execution. Copy A1 comparison caught the mistaken flag-number inspection
hypothesis: actual output used transparent stores, proving the first flag controls
it. The native selection and cases were corrected and complete fresh A2 passed;
the failure remains private. Inspection gradient data was then changed to hash-only
metadata so numeric extracted data stays private; fresh copyA3/parentA2 and six
final replays use that final source identity and retain all A2/A1 outputs. No
expectation was relabeled or bypassed.

## Build, replay and next work

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake -S . -B build/native
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake --build build/native --target surface-copy-vectors surface-refresh-copy-vectors
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_surface_copy test_surface_refresh_copy
build/tools-env/bin/ctest --test-dir build/native -R '^surface-(copy|refresh-copy)-domain$' --output-on-failure
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py --audit private/boot-camp-20261019/surface-copy-local.audit.json tests/compare_surface_copy.py --exe private/official-1006-probe/game.exe --native build/native/surface-copy-vectors --expectations private/boot-camp-20261019/surface-copy-fresh-a3/expected.json --report private/boot-camp-20261019/surface-copy-local.json
```

Use a new audit/report name on every run. The parent driver is
`tests/compare_surface_refresh_copy.py`, runner `surface-refresh-copy-vectors`,
with the parent expectations above. Fresh execution replaces `--expectations ...
--report ...` with a new `--output private/...` directory and needs host Unicorn
JIT permission. `--uncached` before the driver disables inspection reuse while
retaining identity/receipt guards. Sanitizer profile is `build/sanitize`.

Next join actual copy and actual6324A0/pixels in one complete refresh on the same
owners; then recover actorC0/CC/resolver663D30, nonzero632000 and original surface
startup association. Coverage refresh/redraw/House power, production owners/warm
clones/map-scan caller, diplomacy/action37 and ordinary SDL Objective1 remain open.
Entry points remain `./build.command`, `./test.command`, and
`./run.command --boot-camp-walk`. Both games remain incomplete. No worker, Windows
action, download or runtime executable-read expansion was introduced.
