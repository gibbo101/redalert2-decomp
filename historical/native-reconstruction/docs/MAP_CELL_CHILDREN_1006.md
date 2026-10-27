# Supplied RA2 1.006 Cell connectivity and empty passability

October 15, 2026, after `b187701`. `assets/MapCellChildren.*` recovers complete
LAT tile-connectivity decisions, ordinary no-overlay/no-occupant passability,
map permission and pointer lookup. These are prerequisites of the same crossing/
cliff map-depth delivery. They remain unwired; no runtime field is promoted here.

## Identity and reference hypothesis

Exact supplied base engine: `private/official-1006-probe/game.exe`, 4,485,392 bytes,
SHA256 `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`,
equal to the approved private Windows copy. Embedded 1.08, supplied 1.006 lineage
and reported no-CD modifications remain separate; pristine authenticity is
unverified. The app never executes this binary. No new transfer or Windows action.

Consulted [REFERENCES.md](REFERENCES.md)'s pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439`, `docs/voxels.md`/LICENSE and
YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88`, `CellClass.h`, `MapClass.h`
and `IsometricTileTypeClass.h`. Hypothesis: actual LAT and passability children
can replace the supplied child behavior in the next complete recalculation join.
YR vocabulary does not establish base offsets or semantics; exact instructions
and execution decide them. No upstream/header/generated or lifted game code was
incorporated. No dependency or THIRD_PARTY notice was added.

## Inspected and executed scope

`verify_map_cell_children.py` checks seven complete ranges / **828 instructions**,
the actual tile image slot via inherited input inspection and double threshold
0.01. Original roots and children execute unchanged, without API services:

| Root | Scope |
| --- | --- |
| `0x471D10..0x47249A` | Complete LAT, supplied tile-set globals/direction offsets |
| `0x478F40..0x4790E9` | Complete passability, no overlay and occupant head zero |
| `0x55A660..0x55A737` | Complete map permission, elevation byte gate and actual cell lookup block |
| `0x548070..0x5480A8` | Actual map pointer lookup and fallback coordinate store |
| `0x42ADD0..0x42ADF9` | Actual signed-word addition leaf |
| `0x5293D0..0x5293F6`, `0x5293A0..0x5293CB` | Actual resident/null image getter and ensure-image path, lazy-load byte zero |

The registry, records, fallback, geometry, fifteen tile-set globals, eight
direction offsets and float32 land speeds are fixture inputs. Their original
construction/INI/theater assignment is not established. The LAT native kernel
models numeric/stored state; the original's final resident/null image checks have
no mutations in this profile. Native code has an explicit output registry guard.
Lazy image loading, overlay/occupant dispatch, allocation/ownership and original
initialization order remain outside the claim.

Preserve sequential tile-set stages: later stages see earlier tile stores.
Endpoints use wrapped additions and signed comparisons, with separate -1 guards
where the original has them. Four cardinal queries set connectivity mask bits in
order 0/2/4/6; each group has its own compatible ranges/singleton. Slope 1..4
queries ordered pairs 6/2, 0/4, 2/6, 4/0. A zero neighbor slope sets a bit;
zero mask falls back using the other range's base and the full slope byte, including
zero/alternate byte values. Compare the final tile to the initial value for the
return even when intermediate writes occurred. Do not rename globals from YR leads
before the base theater loader is verified.

Map lookup uses signed `y*512+x`, including aliases and bounds/null fallback.
Fallback lookup stores the requested packed coordinate without resetting its
other fields. Permission's elevation argument tests its low byte; signed cell
level and nonzero ramp can adjust the strict diamond bounds. Geometry arithmetic
wraps at 32 bits before signed comparisons. Empty passability first checks map
permission: outside returns 7; land 2 returns 4, land 6 returns 3. Other supplied
float32 land speeds return 0 only when greater than the original double 0.01;
equal/less/unordered return 6. The latter includes the tested NaN input. No native
float arithmetic replaces original simulation arithmetic.

Caller return/ESP/callee-saved registers, stack tail, exact allowed writes,
immutable map/type/pointer/direction/global/speed tables, all unmodeled actor/
neighbor/fallback bytes and selected ordered stores are audited. Lookup events
include the permission routine's inlined lookup block. They are not an assertion
that permission calls the separate getter. No original instructions are patched.
Native table/fallback/registry/speed-domain refusals are safety guards, not original
malformed-input parity. Full memory read order is not compared.

## Evidence and reproduction

**5,888 fresh original/native results**, normal and ASan/UBSan replay pass:
2,048 sequential group/range/mask LAT cases, 256 slope cases, 2,048 complete
permission cases and 1,536 empty passability cases nesting actual permission.
The 30-result pilot also passes. Cases include overlapping/absent ranges, signed
endpoints, coordinate aliases/wrap/missing pointers, zero/alternate slopes,
strict geometry bounds, elevation byte gates, float32 values around 0.01, signed
zero, subnormal, infinities and NaN. These are synthetic fixtures, not original
whole-map initialization or observed gameplay.

Counts: 5,888 audited roots / 12,322 selected stores / 16,581 lookup events.
Actual entries: 2,304 LAT, 3,584 word additions, 13,568 separate map getters,
2,011 resident image getters / 1,147 ensure-image calls, 3,584 permission and
1,536 passability roots. Counts describe executed scope, not fidelity percentages.

Receipts: `private/map-depth-1006/cell-children-v1/{expected,report}.json`,
`native-replay.json`, `sanitize-replay.json`. Engine, inspection, relevant sources,
runner and expectation fingerprints are checked before/after each run.

```sh
./build.command
build/tools-env/bin/ctest --test-dir build/native --output-on-failure
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
# Fresh isolated original execution: authorized Mac host JIT context;
# choose a fresh, unused private output directory.
build/tools-env/bin/python tests/compare_map_cell_children.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/cell-children-new
build/tools-env/bin/python tests/compare_map_cell_children.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/cell-children-v1/expected.json \
  --report private/map-depth-1006/cell-children-v1/replay-new.json
# Add --native build/sanitize/map-cell-child-vectors for sanitizer replay.
```

Both builds, **404 distinct Python tests**, **20 normal / 19 sanitizer CTests**,
source/diff/local-link audits and both replays pass. Six previous input/recalculation/
complete caller-world normal/sanitizer runner hashes and recorded source entries
remain identical; their accepted receipts are retained. No SDL test was repeated
for this unwired prerequisite. Actual SDL checks remain required at the complete
map-depth capability delivery. Only Apple Silicon macOS is tested; local
verification is not independent acceptance.

Fresh driver/original/native **4.798/4.036/0.181 s**, CLI **4.90 s**. Normal
replay CLI **0.78 s**, native **0.163 s**. Builds **7.48/13.31 s**, Python CLI
**2.33 s**. Private attempts/closing/logs retain sanitizer/CTest times and unavailable
start/inherited elapsed measurements. The exploratory arena allocation was enlarged
to include the full pointer table before pilot execution; pilot/full evidence pass
on the first execution. No worker/new evidence cache/source-install/system/Windows
change or transfer occurred.

## Continue the same capability

Nest these actual children inside the complete ordinary recalculation root,
then verify theater tile/type/default/shift and map initialization order before
using prepared cells in Foot depth. Preserve earlier receipts without relabeling
them as a joined original call. Then retain the Unit/world drawing chain and
exercise the SDL level crossing and parked cliff `(51,72)`, elevation 4.
Runtime still supplies neutral tile/contact fields. Overlay/bridge/tube/contact
construction, map/actor lifetime, ownership, pathfinding, camera/fog/scheduling and
whole-frame fidelity remain open. Full base RA2 then YR remains incomplete.
