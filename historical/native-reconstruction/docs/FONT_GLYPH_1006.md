# Original font glyph drawing

`src/render/FontGlyph.hpp` recovers complete base `4318E0` and its actual inclusive
rectangle intersection child `432000`. All 363 fresh original calls match native
return X, complete surface hashes and ordered index/bitmap reads and pixel stores.
This is an unwired rendering dependency. Message text, surface binding, objective
presentation and original frame/UI fidelity remain incomplete.

## Input and behavior

The exact supplied target is 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. `verify_font_glyph.py` fingerprints it
before inspecting complete instruction ranges and the USER32 SetRect import.
No public/YR/recomp code, new dependency or runtime executable read was added.

The renderer borrows immutable primary indices/glyph bytes and fallback bytes,
plus mutable 16-bit surface backing and explicit drawing state. Stock GAME.FNT
ownership stays in `GameFont`; no glyph payload or extracted data is compiled.
The primary definition supplies bitmap height; drawing-state row-byte stride
and destination pitch remain independent. Destination pitch counts pixels.
Spacing, tab origin, clip rectangle, color and associations remain supplied.

Tabs use the low 16 bits of the code and signed remainder of wrapped
`X + tab - origin`, returning wrapped `X + tab - remainder`. Faulting division
explicitly refuses. Ordinary codes use word indices and dword stride arithmetic.
Missing index/computed-null glyph selects fallback and XORs the chosen color with
`0x5555`, even for an explicit override. Only the low color word reaches pixels.
Absent fallback or destination returns the incoming X, without width/bitmap reads.
A present fallback with absent primary and bound destination reaches an original
null row-owner dereference; the native implementation explicitly refuses it.

Glyph rectangles and clipping are inclusive. Rejected glyphs still advance by
width plus spacing. Full containment uses the fast path; partial clipping skips
top rows and checks horizontal coordinates per pixel. Bits are consumed high to
low. A zero bitmap byte skips eight pixels before testing remaining width. The
original inner loop visits at least one byte for a nonzero row count, including
zero-width glyphs; this is retained. Unset bits preserve prior pixels, row padding
and all unrelated surface storage. Row/column/advance arithmetic wraps as dwords.

The rectangle helper preserves signed comparison order, sequential copy then
clamp order, and `{0,0,-1,-1}` rejection output. Glyph proofs exercise the actual
child with distinct local rectangles. A native guard additionally covers whole
record aliasing; no differential overlapping-record or raw-EAX upper-byte claim
is made. Consumers use the original low-byte Boolean result.

## Evidence and limits

Canonical `private/boot-camp-20261018/font-glyph-fresh-a1/expected.json`, SHA256
`30e38137331308f0fe776eb10fa62397c099deb41c48357e0df58fd8dff2b6d6`.
The guest executes 363 complete glyph roots and 173 complete intersection roots.
Only USER32 SetRect is replaced, with its supplied coordinate-copy behavior;
no glyph/intersection instruction or output is replaced. Initial font/bitmap/
surface records and allocation fill are supplied fixtures. Twelve cases use
actual private GAME.FNT data; its loader has separate existing proof and is not
executed in this glyph guest. Stock file SHA256 is
`ec8d6d85db3eedf5a862cc6ffb87bfad4c77279dd946bc2d30879ad9140c8d3f`;
the driver checks it before/after execution and each replay explicitly.

Cases cover widths 0/1/7/8/9/15/16/17/24, zero/all/mixed bytes, clipping/rejection/
one-pixel edges, negative positions, independent row strides, fallback/absence,
color overrides, wrapping advances, high code bits and signed tabs/origins.
Every call checks ordered index/glyph/fallback reads and 16-bit stores, complete
32x24 surface backing, untouched font/input/arena, stack/return/callee-saved
registers, original code and IAT. This is not full heap/raw-object/UI parity.

Host spans refuse out-of-bounds byte/pixel access, missing byte services, missing
primary row ownership and more than 65,536 rows. These are safety/work bounds,
not recovered validation. A refusal may retain preceding pixel writes; a native
guard verifies that partial effect. The original wider/unmapped/faulting cases
are not repaired or advertised as supported. Surface binding, RGB conversion,
UTF-16 text iteration/typewriter, message-node drawing, live sight and production
objective scheduling remain open. No player-visible behavior changed.

Normal/sanitizer/uncached-inspection replays each retain363 hits and zero misses.
Both builds,123 normal/122 sanitizer CTests and1,383 Python tests pass. Sanitizer
reconfiguration triggered a broader rebuild; saved original expectations retain
all52 stock-loader,6,177 metric,450 insertion and606 expiry sequences on rebuilt
sanitizer runners. No old original matrix was regenerated. Normal application,
owner and older message/font runner hashes remain unchanged. The rebuilt sanitizer
owner passes its full private Boot Camp command/clone/warm isolation check
(22.94s elapsed). Exact identities are in the private receipt.

Local verification is not independent acceptance. Existing SDL evidence is
retained only for the unchanged application behavior; no visible-text SDL
acceptance has occurred. Detailed checks, runner/source identities and costs are
in the private `font-glyph-receipt-a1.json` and replay manifest. Original generation
took 0.385s, native comparison 0.023s and fresh driver 0.730s. Earlier fixture-test
repairs (Boolean command spelling and expected case count) occurred before fresh
evidence; a later native guard strengthened partial-write coverage and rebuilt
runner replays retain the same originals. Final source review also restored the
late spacing read and saved pre-width bitmap height; final rebuilt normal/
sanitizer/uncached replays and glyph domain checks retain the same originals. Normal/sanitizer CTests took3.14/11.71s; Python test time52.444s. The sanitizer
and four older-family replay batch took9.428s. Build wall times, repair/manual review
and approval overhead were not separately measured. No cache mechanism was added;
existing identity-checked expectations and inspection reuse are retained.

## Commands and next integration

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
./test.command
DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/sanitize --parallel 6

env PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/font-glyph-next.audit.json tests/compare_font_glyph.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/font-glyph-vectors \
  --font-file private/boot-camp-20261018/game-font-research-a1.bin \
  --expectations private/boot-camp-20261018/font-glyph-fresh-a1/expected.json \
  --report private/font-glyph-next.json

./run.command --boot-camp-walk
```

Use fresh report/audit destinations. Replace expectations/report with
`--output private/NEW-DIRECTORY` for original execution; select the sanitizer
runner or add `--uncached` before the driver for replay controls. Private
`font-glyph-replay-commands-a1.json` records completed commands.

Next join complete text iteration `431CC0` to this single glyph kernel, recover
surface binding `4320B0`/`432150` and caller `432350`, then RGB/alignment `5FE1B0`,
text consumer `600830` and node `6F1620`. The complete inspected node/glyph/text
excerpts are private `message-drawing-*`; the excerpt starting `431850` begins
mid-instruction and must not be treated as an entry. Then compose action11/font/
list/expiry/drawing over production owners, warm discarded previews and actual
SDL text acceptance. Live sight/arrival and remaining effects still gate Boot
Camp Objective1. Both full games remain incomplete; goal active.
