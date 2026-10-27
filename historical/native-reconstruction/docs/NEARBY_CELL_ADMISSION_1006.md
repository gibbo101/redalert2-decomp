# Nearby destination Cell admission

`assets/NearbyCellAdmission.hpp` adds the complete original rectangle admission
`550CF0`, its Cell policy `478760`, and direct-Cell permission `55A740`. These are
separate unwired dependencies for the initialized-zero Unit Scatter destination
search. They do not search routes, command actors or enable runtime displacement.
Base Red Alert 2 first, then Yuri's Revenge remain incomplete.

## Exact target and recovered behavior

The existing supplied executable is 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 lineage and reported no-CD provenance remain distinct;
pristine authenticity is unverified. Its fingerprint was checked before inspection.
The existing local file made the authorized Windows copy unnecessary; no transfer
occurred. Original assets, executables, disassembly and evidence stay private.

The complete ranges are `478760..4788C3`, `550CF0..550DBE` and
`55A740..55A7EF` (exclusive ends): 278 inspected instructions. Preserve:

- Cell speed type 4 returns true before zone, level, occupation, overlay or speed
  queries. Otherwise zone -1 bypasses `54F8F0`. Other values call that named
  supplied resolver with the Cell's actual position pointer, movement zone and
  raw alternate dword. A mismatch returns before later Cell reads. This root
  does not normalize 65535 to -1; its nearby-search caller does that separately.
- Explicit level must match signed base level, or base+4 when flag100 is present.
  Matching base with flag100 requires a nonzero alternate low byte. Elevated
  occupation is selected only with flag100 and level -1 or base+4.
- Read only the selected occupation field's low byte. First ignore byte applies
  mask E0; second applies mask 5F, in that order. Remaining bits reject admission.
  No resident list traversal occurs in this root.
- Overlay -1 bypasses the registry. A null or non-wall type keeps Cell land.
  Walls permit movement zones 2/3/8; zones 1/4 require crushable. Accepted walls
  substitute land0. Other wall cases reject before the land-speed query.
- Original speed indexing combines signed land*9+speed with dword wrapping.
  Preserve valid aliases rather than independently constraining speed to 0..8.
  The FP comparison rejects equal-zero or unordered values unless elevated
  occupation was selected. Negative finite values and either infinity pass.
  Do not replace this with positivity or the other passability root's 0.01 test.
- Rectangle X is outer, Y inner. Nonpositive dimensions perform no Cell queries
  and return true. Add offsets as signed words, use the combined signed y*512+x
  slot lookup, and immediately forward missing-slot fallback coordinate stores.
  Disallowed overlay rejects before Cell admission, even for speed type4. Stop
  at the first rejection; otherwise every Cell invokes the complete child with
  both ignore bytes zero. Each iteration rereads the borrowed origin.
- Direct permission reads the supplied Cell's stored position, signed level and
  slope without any map lookup. A nonzero elevation byte enables the slope/level
  adjustment. Diamond geometry wraps at dword width before signed strict bounds.
  It must not be replaced with `mapCellPermitted`, which adds a Cell lookup.

`NearbyAdmissionCell` borrows `MapCellInput`, both occupation fields and overlay
index. Types and land-speed bits are borrowed spans. Binding makes no queries or
copies of world state. An optional observer records actual child entry/return;
it must remain observational. Missing services, split Cell bindings and invalid
registry/speed accesses are native safety refusals, not original malformed-input
results or rollback. The speed guard requires the combined signed index within
the borrowed span; pathological scaled-address aliases outside that domain are
refused. Entered calls can already have consumed queries or mutations;
future previews must discard the entire unsupported call.

## Differential evidence and boundaries

Canonical: `private/map-depth-1006/nearby-cell-admission-v1/`.
**2,372 complete original top-level calls** match normal, ASan+UBSan and uncached
replays: 1,684 direct Cell calls, 169 complete rectangle calls and 519 direct
permission calls. Rectangles enter another 609 actual Cell calls: 2,293 total.
All 278 inspected instructions execute. These are scoped synthetic original
executions, not original-game observations or a fidelity percentage.

Actual execution covers both returns of all three roots, all 256 occupation bytes
and both masks, primary/elevated selection, wall movement-zone/crushable decisions,
662 rectangle lookups, shared fallback/word wrap/combined-index aliases and exact
permission bounds. Speed comparison executes 738 positive, 24 negative, 16 zero
and 16 unordered outcomes. There are 135 supplied zone calls, including 10
explicit diagnostic mutations. The mutations change the borrowed Cell fields and
position, proving the caller consumes late values; they are not gameplay evidence.
All four incoming native rounding modes retain their caller setting.

Compare ordered lookup/fallback/child/service calls, arguments, return bytes and
all final projected Cell state. Original instructions are unchanged. The original
whole arenas, unmodeled Cell/fallback bytes, type/registry/slot/speed/geometry/code
inputs and caller stack/registers/canaries are guarded. Zone service effects are
explicit host shims at the unchanged target. No native machine-store-order or
original heap/startup/global-lifetime claim follows. Thirteen native ownership/
safety checks per build and eight Python evidence checks accompany the proof.

Initial Cells, occupation, overlays/type/registry/land speeds, map dimensions and
associations remain supplied. `54F8F0` is inspected but not recovered here; its
bridge/zone tables and children remain open. The actual Unit zero-point caller
uses zone -1 and does not enter it. Burrowability `47C200` is inspection only;
that Unit caller supplies zero. The existing nearby parent and complete projection
remain separate verified proofs, not a newly executed joined search. No Unit/Cell
Scatter, Advance6, Process, production owned map, preview, drawing or SDL join is
added. Every existing runtime guard stays intact.

The opening handoff records full regressions and a 186-record inventory preserving
all 184 earlier records unchanged. App identity is unchanged; no new SDL test is
claimed. Only Apple Silicon macOS is tested; local checks are not independent
acceptance. No upstream code/header/generated/lifted output, extracted table,
dependency or runtime executable-read expansion was incorporated. Existing
[reference and license boundaries](REFERENCES.md) apply.

## Build and reproduce

```sh
./build.command
./run.command --owned-demo
./test.command
PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  -m unittest discover -s tests -p 'test_*.py'

env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake -S tests/nearby_cell_admission \
  -B build/nearby-cell-admission -DCMAKE_BUILD_TYPE=RelWithDebInfo \
  -DCMAKE_OSX_ARCHITECTURES=arm64
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/nearby-cell-admission --parallel 6
build/tools-env/bin/ctest --test-dir build/nearby-cell-admission --output-on-failure
build/nearby-cell-admission/nearby-cell-admission-vectors --guards
# Repeat in build/nearby-cell-admission-sanitize with Debug and RA2_SANITIZE=ON.

# Fresh original execution needs the authorized host Unicorn JIT context.
# Choose unused private output/audit paths; do not overwrite the canonical proof.
PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/map-depth-1006/admission-new-audit.json \
  tests/compare_nearby_cell_admission.py \
  --exe private/official-1006-probe/game.exe \
  --native build/nearby-cell-admission/nearby-cell-admission-vectors \
  --output private/map-depth-1006/admission-new
# Replay instead: replace --output with --expectations
# private/map-depth-1006/nearby-cell-admission-v1/expected.json --report NEW_JSON.
# Sanitizer: select its runner. Uncached: add --uncached before the driver.
```

The standalone CMake project stays outside the app/legacy CTest graph and requires
no original asset or executable at runtime. Keep public sources and runners fixed
during guarded invocations. Never rerun closed finalizers. Initial compilation
caught an unavailable integer helper include; the local implementation now uses
explicit bit casts. Pilots preceded canonical generation and verified six basic
cases, then the full corpus and executed FP branches. No original instruction,
result or guard was relaxed. Full manual review/repair time was not measured.

Next join the complete nearby search with these actual children and existing
projection on one borrowed map/fallback. Keep required burrowability0/zone-1
scope explicit until other branches are recovered. Then execute the actual
zero-point Unit caller, Cell dispatch, complete Advance6/Process effects and
production owned actors, followed by full discarded previews, warm drawing
isolation and actual SDL acceptance before enabling displacement.
