# Coverage writers below complete nonzero radar refresh

`CoverageRadarBinding` joins existing complete6C83F0/6C86F0 coverage to actual
634030/nonzero632000 on shared Cell/House/actor/surface owners. The new separate
composition remains unwired to production Boot Camp, House scans and SDL. It adds
no runtime executable read, dependency, public code or replacement gameplay.

The binding borrows the canonical `RadarMapWorld` table/fallback, installs actual
548070 lookup semantics for coverage and calls the single refresh/pixel kernels.
Coverage12C and13C must be the exact references returned by that world's discovery
view; distinct owners refuse when entered. Terrain140 remains independent. Pure
field views make no gameplay queries. Construction validates shared current-House,
mode and first/second-surface reference owners without invoking callbacks. All
three replaced callbacks restore on normal exit and unwind. Binding is immovable;
all referenced services, world and explicit scratch must outlive it.

The caller must install `RadarMapBinding` using this same `RadarMapWorld`; callback
closures cannot be inspected to prove that association at construction. The
original/native fixture does use one canonical table, terrain Cells, fallback,
lazy floor state and mutable12C/130/134/13C owners. There is no second Cell table,
copy-back operation, floor cache or actor/House mirror in the composition.

Coverage retains repeated privilege/Cell lookups, signed-word indexing, immediate
fallback-position stores, wrapped counters and separate12C flag stores. Actual
House188 clearing precedes complete refresh; supplied4E09A0(2) follows its return.
The native binding explicitly refuses an entered zero-mode refresh after any
preceding coverage stores; there is no rollback claim. Existing standalone
zero-mode copy/marks/pixel recovery remains available, but is not silently enabled
by this association. Host traversal, foreign-owner and all production refusals
remain. The new native guards check no-query binding, reference-owner mismatch,
Cell-field mismatch, ordinary restoration, unwind restoration and zero-mode refusal.

The proof reuses `StockTechnoCoverageBinding` for actual stock permission30C,
80->84/typeADE and Owner3C on the same Infantry/Building owners used by radar.
Infantry addition returns false; it is never forced through a supplied permission.
Building availability executes complete450360 with supplied ordinary health1,
count0, byte530 and zero type power/operational flags. Its House-power branch is
unentered here; the earlier stock-coverage proof retains its separate supplied
power-service scope. Unused fields of its borrowed view are supplied aliases,
not production-layout or startup claims. Scalar House/local/alliance and actual
6A2970/77F110 reuse the existing kernels, with authored .125 height scale.

## Evidence and limitations

Exact supplied target:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. The verifier composes the existing exact
coverage/stock/radar inspections; all entered instruction spans remain unchanged.
No public/YR/recomp implementation was incorporated.

All404 fresh sequences match ordered coverage stores/queries, radar child returns,
pixel and lock writes, dirty rectangles, full final arena/Cell/fallback projections
and lazy floor state. This includes217 removals/187 additions,284 actual634030
calls,3,408 actual632000/floor/discovery/write calls,2,115 pixel reads,60 stock
coverage type queries,84 Building/82 Infantry permissions and5,952 Owner queries.
Actual House calls:6,129 local/5,160 alliance; actual coverage map queries:6,412.
Early exits, empty/negative radius, signed count extremes and wrap, distinct flags,
permission, null/current Houses, word projection, negative coordinates and shared
fallback accumulation are included. Supplied state is diagnostic input, not
original-game observations or original initialization.

The original coverage instructions call Map8324E0's refresh directly. The original
radar context therefore lives at that same Map address; the harness neither
redirects ECX at the call nor copies another renderer's records into it. Default
standalone radar context remains unchanged. The borrowed point's consumed X/Y
are compared; its two unused stack words are omitted from this new projection,
not normalized into recovered state. Caller stack, callee-saved registers,
immutable inputs/code, ordered allowed writes and full arena padding remain
checked. Initial actor/type/House/table/surface/palette/registry associations and
records, redraw, stock startup/production warm/scan and ordinary SDL Objective1
remain supplied or open. This is neither a whole-frame nor whole-game proof.

Canonical original-only expectations:
`private/boot-camp-20261019/coverage-radar-stock-fresh-a1/expected.json`.
Fresh original28.138s/native.066s. Earlier244-sequence A2/A3 proofs used supplied
coverage permission/type leaves; they remain historical, not relabelled as this
404-sequence stock proof. Initial A1 stopped on the original coverage continuation
after refresh because the harness instruction classifier did not retain its parent
scope; repaired before accepting any comparison. Failed audit remains private.
The first legacy radar refresh matched all outputs but its outer source guard
rejected concurrent fixture edits, including transitive conditional includes.
The separate final frozen-source proof supersedes it; the rejected audit remains.

Final affected-family checks/receipts and exact cost/retention information appear
in the opening handoff and `private/boot-camp-20261019/coverage-radar-receipt-a1.json`.
Local verification is not independent acceptance. No whole inventory, closed
finalizer, Windows action, system change, transfer or download was performed.
Only Apple Silicon macOS is tested. Both games remain incomplete.

## Reproduce and next integration

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake -S . -B build/native
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake --build build/native --target coverage-radar-vectors --parallel 6
build/tools-env/bin/ctest --test-dir build/native -R '^coverage-radar-domain$' --output-on-failure
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_coverage_radar
# Choose new private audit/report destinations for each invocation.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/NEW-COVERAGE-RADAR.audit.json tests/compare_coverage_radar.py \
  --exe private/official-1006-probe/game.exe --native build/native/coverage-radar-vectors \
  --expectations private/boot-camp-20261019/coverage-radar-stock-fresh-a1/expected.json \
  --report private/NEW-COVERAGE-RADAR.json
```

Fresh generation substitutes a new `--output` for expectations/report, using
research-only Unicorn JIT. Replays still identify every source/runner/input and
execute the native runner. Use `build/sanitize/coverage-radar-vectors` or add
`--uncached` before the driver for the other profiles. Freeze all transitive source
inputs, including conditionally included fixture files, during each proof.
Application entry points remain `./build.command`, `./test.command` and
`./run.command --boot-camp-walk`; this milestone adds no new SDL control.

Next join both complete refresh branches on common stock actor/House/scheme/
surface owners, then stock surface startup and production mutable counter/actor/
House ownership, full discarded warm previews and the House-map scan caller.
Keep runtime coverage/image refusal until those joins and actual SDL acceptance.
Building power, redraw, diplomacy/action37 and mission progression remain open.
