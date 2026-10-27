# Surface refresh parent and geometry getters

`render/SurfaceRefresh.hpp` implements complete base634030..6340E1 in a separate,
unwired rendering kernel. It borrows live surface pointers, virtual-table identities
and modeB263D8, with explicit per-entry rectangle scratch. Actual ordinary geometry
getters411290/4112C0/4112D0 are also recovered. Copy virtual8 and effects632000/
6324A0 remain named supplied services. This does not yet replace the terminal
coverage callback, enable production image effects, or advance ordinary Boot Camp
Objective1. Both games remain incomplete.

## Recovered control and identity

The mode global is read once before callbacks. In mode zero the parent saves
first1218, obtains second121C's table, and saves the first surface's original table
before the first getter. It calls second.rect78 with the first stack rectangle.
Then it rereads second121C and the saved first surface's current table, calls that
surface's rect78 with the second stack rectangle, and retains both returned pointer
identities. The final virtual8 uses the saved original first **table**, the late
first1218 **receiver**, destination rectangle result, late second121C, source
rectangle result,0,1. The copy slot is read at dispatch, so changing the saved table's
slot differs from replacing the saved surface's table. Finally6324A0 receives the
original context. Neither rectangle is copied by value between callbacks.

Actual411290 confirms that virtual78 consumes only one output pointer and returns
that pointer. The earlier0/1 and subsequently pushed surface/rectangle values are
retained arguments for virtual8, not additional rect78 arguments. Original caller
ESP checks with actual rect78 enforce this five-argument copy ABI. The supplied
copy's return is ignored. Actual rect78 reads width/height before storing0,0,width,
height; width7C and height80 read signed fields4/8. Geometry and their stock vtable
association remain supplied initialization, not a recovered surface constructor.

Nonzero mode obtains width from first1218, rereads first1218 and its table, obtains
height, and saves both results. Traversal is Y outer/X inner, with signed nonpositive
skips; later changes to mode, surface pointers, tables or dimensions do not change
the saved branch/dimensions. Each pixel callback receives the same borrowed stack
point after fresh x/y stores. Its remaining two rectangle words retain incoming
scratch. Changes to point x/y by a supplied callback are overwritten on the next
visit.6324A0 is not called on this branch. Original632000's ret4 and6324A0's ret
were additionally inspected; their bodies were not executed in this proof.

The native API deliberately models stable logical objects/tables rather than guest
addresses. Named callbacks may change borrowed owners; the caller retains their
lifetimes. Missing entered services/surfaces/tables refuse. Positive dimensions
with product greater than1,048,576 refuse after both dimension queries, before
traversal. This is a host work bound, not an original geometry rule, clamp or
rollback. Exceptions propagate. Nonpositive width has no callback-visible loop
work even with a very large positive height. Caller return-register residue is not
an exposed native result; the recovered entry is used as a void effect.

## Exact original proof

Supplied executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD and unverified pristine remain
distinct. The verifier checks identity before addresses, complete parent/getter
spans and BSurface slots78/7C/80. Unchanged original instructions execute in an
isolated research-only Unicorn guest; the shipped application executes none.

All1,012 fresh complete parents match ordered callback arguments, logical surface/
table/returned-rectangle identities, scratch and final owner state:256 zero-mode
and756 nonzero-mode calls. Actual getters execute224 rect,378 width and378 height
calls. There are256 supplied copy/finish pairs and4,536 supplied pixel callbacks.
Diagnostic virtuals additionally cover null/alternate/other-stack rectangle returns,
partial output stores, saved table-slot replacement, shared surface aliases and
callback mutations at both getters, copy, dimensions and the first pixel. These
are authored probes, not original-game observations or proof of actual copy/pixel/
finish behavior. Initial stack words, context, geometry, tables and mode are supplied.

Stack/callee-saved/return-address/input-code and whole arena/padding guards remain
active. Only inspected instructions and named supplied leaves may enter. Original
expectations contain register/memory/service projections from the guest, not native
outputs. Source/runner/input/receipt guards remain unchanged; no new cache was added.

Canonical original-only expectations:
`private/boot-camp-20261019/surface-refresh-fresh-a1/expected.json`, SHA256
`d9d855cf87e201d8e6e3bdd2eafafb852c2a68e5acf6b8e6e890f65caa75a806`.
Original generation.514s/native comparison.029s. Eleven Python checks, three focused
CTests in each profile and nine guarded normal/sanitizer/uncached replays pass.
Those replays cover this parent, existing surface fill and stock Techno coverage.
An attempted fill replay rejected an older source identity before native/original
execution; the failure is preserved. The eligible `surface-fill-fresh-a3` receipt
then passed under a new report name; successful checks were not repeated.

CMake reports configure+generate15.1s/16.2s; process wall/build/repair/task wall costs
were not separately measured. Both-profile native preflight.247s. Exact check
commands/times, source/runner hashes, logs and retained SDL/owner binary hashes are
in `private/boot-camp-20261019/surface-refresh-receipt-a1.json`. No comparison mismatch,
whole inventory refresh or closed finalizer rerun occurred. This is local
verification, not independent acceptance. Application and owner binaries retain
the previous106-tick SDL walking baseline; no runtime source changed or GUI reran.
Only Apple Silicon macOS is tested.

## Reproduce and continue

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake -S . -B build/native
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake --build build/native --target surface-refresh-vectors --parallel 6
build/tools-env/bin/ctest --test-dir build/native -R '^(surface-refresh|surface-fill|stock-techno-coverage)-domain$' --output-on-failure
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_surface_refresh test_surface_fill test_stock_techno_coverage
# Use new private names; do not replace canonical expectations or receipts.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/NEW-SURFACE-REFRESH.audit.json tests/compare_surface_refresh.py \
  --exe private/official-1006-probe/game.exe --native build/native/surface-refresh-vectors \
  --expectations private/boot-camp-20261019/surface-refresh-fresh-a1/expected.json \
  --report private/NEW-SURFACE-REFRESH.json
```

Use the sanitizer runner or `--uncached` before the driver for the other profiles.
Fresh proof uses a new `--output` instead of expectations/report and research-only
JIT. Application entry points remain `./build.command`, `./test.command` and
`./run.command --boot-camp-walk`; this recovery adds no control or visible behavior.

Next recover entered6324A0/632000 and actual surface-copy effects/associations,
then join refresh/redraw and required House-power services to stock coverage.
Production actor/House/13C owners, startup/scale, full warm clones and map-scan
caller still precede removing the runtime image refusal. Diplomacy/action37,
UI/session/Team/audio/scheduling and ordinary SDL Objective1 stay open.

Pinned unlicensed YRpp `Surface.h` was consulted only for naming/signature
hypotheses; base instructions and execution independently establish the ABI and
getters. No header/public/generated/lifted game code was incorporated, and no
new dependency, download, worker, Windows action or runtime executable read added.
