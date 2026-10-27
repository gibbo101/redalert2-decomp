# Supplied RA2 1.006 Foot depth on prepared map Cells

October 15, 2026, after `f77b3c6`. This checkpoint binds the established Foot
predicates, type factors, Drive/null depth and gradient to actual ordinary Unit
base depth on the same finalized Cell/TMP records. The helper is not wired into
gameplay; runtime depth remains neutral. Unit-world drawing and floor-to-actor
absolute/relative-height association remain required before terrain-aware runtime
promotion. Full base RA2 then Yuri's Revenge remain incomplete and active.

## Identity and references

Both supplied private engines are 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`, at
`private/official-1006-probe/game.exe` and
`private/windows-baseline-20261014/game.exe`. Embedded 1.08, supplied 1.006
lineage and reported no-CD changes remain separate provenance; pristine
authenticity is unverified. The approved Windows copy already exists. No new
Windows/transfer/source-install/system action, worker or dependency was introduced.

Consulted [REFERENCES.md](REFERENCES.md), pinned YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` `FootClass.h`,
`TechnoClass.h`, `TechnoTypeClass.h` and `CellClass.h`, and the earlier exact-base
field/default associations in [UNIT_DRAW_METADATA_1006.md](UNIT_DRAW_METADATA_1006.md).
Hypothesis: the prepared Cell tile/land/tube/level/flag records must feed the full
Foot predicates before actual Unit base depth. Exact base instructions/execution
determine the association and result. YR declarations are leads; recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` `docs/voxels.md` is surrounding
context, not an oracle. Existing MIT/generated-code exclusions, stale license text
and YRpp no-license notes remain. No upstream/header/generated/lifted code or
extracted table was incorporated; existing third-party notices are unchanged.

## Joined calculation

[PreparedFootDepth.cpp](../src/render/PreparedFootDepth.cpp) uses the established
Foot arithmetic/predicates and [UnitBaseDepth.cpp](../src/render/UnitBaseDepth.cpp).
It projects current shared Cell records: position `+0x24`, tile `+0x38`, land
`+0xEC`, tube `+0x116`, signed level `+0x11B` and flags `+0x140`. Views are keyed
by record identity, preserving the map's one shared mutable fallback Cell.
Requested coordinates are not distinct fallback records. Observers remain read-only;
stable Cell storage and immutable actor/type inputs are required during a call.

The wrapper retains ordered type/predicate calls, low-32-bit signed products,
signed maximum, wrapped base-plus-maximum-plus-Drive result, optional fourth type
query and actual ordinary Unit base. Actual Drive returns depth zero / gradient
two; absent Drive returns the wrapper's zero / two. All five Foot predicates,
their actual coordinate/Cell/map/type leaves and resident TMP dimensions execute
unchanged in the original guest. Predicate coordinate reads use full signed /256
before word truncation. Initial bridge byte is zero and tube registry count is
zero; this does not enable tunnels, bridges or their construction.

[verify_prepared_foot_depth.py](../tools/verify_prepared_foot_depth.py) combines
**61 complete allowed ranges / 5,037 inspected instructions**, including the Unit
type tail dispatch and checked `+0x80/+0x84` slots. Original stack, returns,
callee-saved registers, immutable actor/type/map/type/image/overlay/global inputs,
code and permitted fallback-coordinate writes are guarded. All other fallback
bytes remain unchanged. Complete memory-read order and original heap ownership
are not claimed.

The E fixture runs actual shared map/floor finalization, then complete Foot depth
and gradient queries on those same records. Native prepares its own records;
no original final state is transferred. Earlier snapshots provide scenario inputs
only and their receipts/hashes are checked. Earlier D/F/G and supplied-map Foot/
world profiles retain their historical scope.

Absolute actor Z, Facing/tick, type factors, tile-base/default/invalid-coordinate
globals and height scale remain supplied. Owned cliff/crossing queries use
supplied level-times-104 Z; this is **not original actor placement or an update**.
Stock HTNK factors are 8/13/10/0; synthetic signed-edge factors are diagnostic
inputs. Other actor/type/occupant/tag/bridge associations and full startup order
remain open. No runtime executable-read boundary expanded; simulation stays SDL-free.

## Missing-image boundary

The standalone Unit base root leaves its dimension scratch uninitialized when
an image is missing, and the complete Foot caller first executes other predicates
on that stack. Its scratch value cannot be replaced by the standalone test's
supplied seed. E therefore refuses missing images **when dimensions are requested**
and does not compare an invented nested initial scratch value. A missing image
that is never consulted is not relevant to this calculation. The standalone D
suite retains its explicitly supplied scratch and missing-image tests.

Native missing-image and nonzero supplied-scratch refusals are safety boundaries,
not original malformed-input behavior. Other unavailable map/type/tile bindings
also remain explicit guards. No alternate Unit, harvester, bridge, non-Drive
locomotor, tunnel construction or original caller-scratch parity is claimed.

## Evidence and reproduction

The main suite matches **67 fresh original/native scenarios / 6,848 complete depth
queries and 6,848 gradient queries**. **53 ranges / 4,720 instructions enter**;
there are 13,764 audited roots, 24,240 actual type queries, 51,088 coordinate
queries, 56,659 Facing queries, 20,544 Cell predicate calls and **5,132 base-phase
TMP dimension calls**. Half the queries use actual Drive and half a null Drive.
The shared parent executes 67 times, with 44,769 actual resource/Cell/passability/
permission/light entries each and 285 actual floor queries.

A separate seven-map / 56-query original/native/sanitizer audit exercises tile
predicate outputs 0/1/2, cliff predicate outputs 0/1/2, flag-0x100 false/true,
nonzero bridge-factor selection, fallback and Drive/null calls. Tunnel predicate
stays zero under the empty registry, and this focused audit's mask-0x400 result
stays false. Broader predicate domains retain their earlier separate tests.

Fresh/normal/sanitizer receipts are retained under
`private/map-depth-1006/prepared-foot-depth-v1/`. The closing handoff records final
counts, entered ranges, focused branch coverage, current prior-suite identities,
SDL checks and timings. The main fixture includes three owned map inputs under
different cliff modes and synthetic heading/flag/height/fallback/FP/wrapping cases.
Owned map queries cover parked `(51,72)`, elevation 4 and the traffic-light
crossing's Cells `(86..93,101)`. Compare parent state/buffers/cursor/ordered traces,
then each depth, gradient, fallback coordinate and cumulative ordered query/store
digest. Original instructions remain unchanged.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

# Fresh execution needs the authorized Mac host JIT context and a new directory.
build/tools-env/bin/python tests/compare_prepared_foot_depth.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/prepared-foot-depth-new
build/tools-env/bin/python tests/compare_prepared_foot_depth.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/prepared-foot-depth-v1/expected.json \
  --report private/map-depth-1006/prepared-foot-depth-v1/replay-new.json
# Add --native build/sanitize/resident-map-finalization-vectors for sanitizer replay.

# Existing playable integration; the new helper remains unwired.
./run.command --crossing-light-demo
```

Select the Rhino; G/right-click moves, L toggles the host light, R resets. This
native SDL scenario does not establish original frame fidelity or exercise the new
depth helper. Only Apple Silicon macOS is tested; Windows/Linux builds are unverified.

Next bind this calculation into the established Unit/world path, then resolve the
floor-to-actor absolute/relative-height associations and initial/global/type
boundaries needed by runtime. Actual SDL level crossing and parked cliff remain
acceptance scenarios before depth promotion. Full startup/ownership/cache/visibility/
pathfinding/scheduling/frame parity and full RA2/YR remain open. This checkpoint is
local verification, not independent acceptance or a new playable milestone.

Concrete runtime boundaries are still visible in
[Renderer.cpp](../src/render/Renderer.cpp): `unitDepthCells_` contains neutral
fields, missing map entries return null, and caller ground height/base depth use
`sim.elevation*104`. The new shared resident preparation has not been added to
GameAssets. Replacing only the final numeric callback would leave these map and
actor associations unresolved.
