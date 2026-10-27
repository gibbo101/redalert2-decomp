# Cell resident search in radar terrain colors

Tutorial purpose: Objective1 action37 needs the real House sight/coverage/radar
chain. Complete471760 now supplies the resident decision below complete4712C0,
631250 and630B70. This removes one supplied child from that chain; it does not
schedule sight, complete an objective or add an SDL capability.

## Recovery and owners

`src/sim/CellResidentSearch.hpp` borrows primaryE4/secondaryE8 heads and reuses
`CellResidentKind6State`/`CellResidentKind6Services`. There is no second mutable
Cell/actor world. A zero scenario gate returns without querying residents.
Otherwise only the selector's low byte chooses the secondary list;256 and
0xffffff00 choose the primary list. The requested kind is the complete signed
32-bit argument. Each resident's virtual kind is queried before comparing;
a match returns that exact identity without reading Next. Mismatches read the
live Next link. Empty lists need no services. Missing entered kind/Next services
refuse. Stable finite lists remain the supported domain; no cycle policy is
invented. The earlier complete4717B0 kind6 helper and its callers stay unchanged.

Exact supplied target:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage and reported no-CD provenance are distinct;
pristine authenticity is unverified. Complete471760 is73 bytes/30 instructions,
SHA256 `109abad9e6cbc6937c0fd51bae3d49998934cbb22f6d842ff7da5b147c91ad90`.
`tools/verify_cell_resident_search.py` pins that range and its field/call/return
associations before executing addresses. No public code or dependency was added.

The standalone original runs288 roots,445 kind queries and341 Next reads.
Cases cover disabled/noncanonical gate bytes, both distinct lists, empty lists,
first/late/duplicate/absent matches, selector upper bits and signed kind extremes.
The kind virtual is explicitly supplied; constructors, list ownership/startup and
real object-kind provenance are not recovered by these cases. Complete guest
arena/code/gate inputs remain immutable; unexpected stores, caller stack changes
and callee-saved register changes refuse.

The existing native color fixture now binds the recovered search to its borrowed
resident identity, rather than returning the authored boolean directly. A new
original composition actually executes471760 beneath4712C0 in254 sequences:
350 search/color roots,20 supplied kind calls,48 terrain joins and24 projection
joins. It retains480 RGB and480 projected pixel writes and the existing image/
variant/scale children. Ordered color stores and complete output backings match.
Overlay5DD000, classifier5DC0B0 and installation52B560 remain supplied in this
fixture; resident construction, type/image/brightness inputs remain authored.
`compare_radar_resident_color.py` gives this stronger chain its own provenance.
The older254 supplied-resident answers are preserved and replay unchanged on both
rebuilt native profiles. They retain their original weaker evidence scope.

## Actual-map inspection and remaining integration

A read-only native probe of the existing BootCampWalkWorld Day1 owner reports
7,659 Cells,214 tile indexes (including65535),225 occupied overlay slots and no
current flag100 Cells. It uses the actual PreparedTerrainMap/MutableUnitMap input
association; it is not an original-game observation or proof of startup state.
Private source/output:
`private/boot-camp-20261020/boot-radar-input-probe.cpp` and
`boot-radar-input-probe-a1.txt`.
Overlay families include0/2,83..101,127..138 and168..177. Consequently the overlay
child cannot be skipped to draw the complete actual map. PreparedTerrainMap still
discards raw TMP Data after metadata preparation and retains only reduced overlay
records. Retain/bind that file provenance on the existing owners, bind the already
recovered resource classifier, then recover the entered5DD000 image/color branches.
Do not substitute an authored color or a guessed resident result in production.

Actual630A00 aliased startup, native storage and relevant first-DSurface semantics
still precede production House/coverage/actor/SDL integration. Keep supplied
primary tile selection/variant startup and theater brightness boundaries explicit.
There is no new runtime executable read or original-code execution in the app.
Both games and ordinary SDL Objective1 remain incomplete; only Apple Silicon
macOS is tested. No workers, Windows actions, downloads, transfers or system
changes occurred. Local verification is not independent acceptance.

## Verification and commands

Normal and sanitizer domain checks pass for resident-search, existing kind6,
Cell colors, terrain and projection. Five focused Python checks pass. Standalone
and composed normal/sanitizer/uncached-inspection replays each report288/254 hits
and zero misses respectively. The uncached control disables inspection caching;
it still explicitly reuses original results and reruns current native code.

Canonical originals under `private/boot-camp-20261020/`:
`resident-search-fresh-a1/expected.json`, `radar-resident-fresh-a1/expected.json`.
Fresh original/native/driver costs are.032/.018/.393s and2.207/.041/2.633s.
Normal replay driver costs are.178/.254s; other measured costs and report hashes
are in `resident-search-receipt-a1.json`. Initial inspection/edit/configure/build/
repair/task wall costs were not separately instrumented. Prior app hashes retain
prior SDL scope; no GUI or whole-frame acceptance was performed for this internal
change.

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake -S . -B build/native
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake --build build/native --target cell-resident-search-vectors cell-radar-color-vectors radar-terrain-vectors --parallel 6
build/tools-env/bin/ctest --test-dir build/native -R '^(cell-resident-search|cell-resident-kind6|cell-radar-color|radar-terrain|radar-projection)-domain$' --output-on-failure
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_cell_resident_search test_cell_radar_color
# Select fresh audit/report paths. No native pass/fail is cached.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/NEW-RESIDENT.audit.json tests/compare_cell_resident_search.py \
  --exe private/official-1006-probe/game.exe --native build/native/cell-resident-search-vectors \
  --expectations private/boot-camp-20261020/resident-search-fresh-a1/expected.json \
  --report private/NEW-RESIDENT.json
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/NEW-RADAR-RESIDENT.audit.json tests/compare_radar_resident_color.py \
  --exe private/official-1006-probe/game.exe --native build/native/cell-radar-color-vectors \
  --terrain-native build/native/radar-terrain-vectors \
  --expectations private/boot-camp-20261020/radar-resident-fresh-a1/expected.json \
  --report private/NEW-RADAR-RESIDENT.json
```

For sanitizer choose runners under `build/sanitize/`; add `--uncached` before
the driver for inspection control. Fresh generation uses a new `--output` instead
of expectations/report and needs research-only Unicorn JIT. Existing app commands
remain `./build.command`, `./test.command`, `./run.command --boot-camp-walk`.
