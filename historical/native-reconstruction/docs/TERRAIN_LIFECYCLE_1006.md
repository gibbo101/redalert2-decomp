# RA2 1.006 ordinary occupation, lifecycle and layer migration

October 14, 2026. Ivalice / Apple Silicon macOS. Baseline: `896c0ec`.

**17,340 fresh results pass independently on each engine**, and all four native
ASan/UBSan replays pass. Complete outputs and commands equal the retained disc
expectations. This migrates the bounded domains in [OCCUPATION.md](OCCUPATION.md)
and [LIFECYCLE.md](LIFECYCLE.md); it adds no gameplay or native numeric changes.
Prepared/runtime inputs remain disc-only. Construction, original map loading,
visibility, global traversal, resources, locomotor clearance and full-frame parity
remain outside the claim. The entire native-game objective remains incomplete.

## Identity and reference boundary

| Engine | SHA-256 |
| --- | --- |
| Allied disc, embedded 1.08 | `135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743` |
| Supplied RA2 1.006 patch output, embedded 1.08 | `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f` |

The patched engine still equals the privately transferred Windows engine. Its
supplied-patch lineage and the user's report of installed no-CD modifications stay
separate from publisher authenticity. No Windows game observation was performed.
Source installations/discs and Outpost 2 remain untouched. No DRM/launcher/media
check enters the native runtime, which reads executable track data only.

Revisited [REFERENCES.md](REFERENCES.md) milestone 18–19 entries and YRpp commit
`b22f1860dd7b100cad57123d4ca5d459b9020d88`: `ObjectClass.h` Mark, Limbo/Unlimbo,
GetYSort/LastLayer; `ObjectTypeClass.h` foundation; `TerrainTypeClass.h` occupation
and foundation metadata; `TerrainClass.h`, `CellClass.h` membership and
`DisplayClass.h` Submit/Remove. These are vocabulary/dispatch hypotheses, not
base RA2 behavior. This snapshot lacks an incorporation license; no headers were
copied. Pinned redalert2-recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439` and
pcrecomp `8f4aa77aaf9e70f486a0fbc6b39a7ee14ae4fda1` remain research/tooling leads,
not occupation/lifecycle oracles. Their authored MIT work does not license original
or generated game code. No upstream code was incorporated.

## Inspected mappings

`tools/verify_terrain_lifecycle_mapping.py` checks **56 complete selected ranges /
3,033 instructions**, encoded bytes, every changed operand and relative branches.
No instruction-shape change was found in these ranges. The local profile records
**190 new explicit mappings**, including unchanged service identity, rather than
applying a displacement. Inherited projection initializers and vector-constructor
ranges are also checked by the composition/raster verifiers before patched runs.
Inspection of unexecuted resource/status paths is not executed behavioral parity.

| Boundary | Disc VA | Supplied 1.006 VA |
| --- | --- | --- |
| Terrain occupation mark / unmark | `6D8A60` / `6D89C0` | `6E38F0` / `6E3850` |
| Terrain Mark / Object Mark | `6D8950` / `5CC6A0` | `6E37E0` / `5D4160` |
| Cell insertion / removal | `473730` / `473920` | `473B30` / `473D20` |
| Map insertion / removal | `547EB0` / `5482B0` | `54AB70` / `54AF70` |
| Terrain Unlimbo / Limbo | `6D9940` / `6D9290` | `6E47D0` / `6E4120` |
| Object Unlimbo / Limbo | `5CBDD0` / `5CBC40` | `5D3890` / `5D3700` |
| Type ground adjustment / foundation | `6DA9C0` / `6DA740` | `6E5850` / `6E55D0` |
| Display Submit / Remove | `4996D0` / `499720` | `499A40` / `499A90` |
| Sorted layer insertion | `532A90` | `534980` |
| Layer storage / RTTI table | `83A888` / `789870` | `852578` / `79E868` |
| Ground height threshold | `A5AA88` | `A72F40` |

Actual Terrain/TerrainType/Layer RTTI and selected virtual slots are verified.
TerrainType foundation is slot **+0x90**; +0x9C is another method. The real aligned
INI block establishes the Foundation key/parser, +0x268 index and +0x288 pointer
with 40-byte stride. All 22 foundation enum names/indices/string pointers match.
Startup executes the original foundation and neighbor initializers, asserting the
1x1 row and all eight ordered neighbors. Ground-adjustment return addresses are
mapped explicitly so event filtering cannot silently omit the second call.

Terrain's +0x54 height predicate consumes the separately inspected threshold via
relative-height +0x1B0. That fixture input is retained. No claim is made for an
incidental +0x2FC lookup beyond the established table; its resource/status branch
is skipped by the ordinary actor fixture.

## Executed comparisons and audits

| Per-engine results | Count | Compared boundary |
| --- | ---: | --- |
| Occupation, membership and Mark | 13,472 | Every low mask/flag pair, signed word coordinates, ordered stores/list operations, modes, all 51 types and 565 placements |
| Layers | 1,860 | Signed wrapped sort keys/ties, growth success/failure, all five records, full capacity tails, stale registrations and duplicates |
| Type adjustment | 559 | Signed edges and a changing second ground-height result |
| Lifecycle | 1,449 | State/loading/permission gates, pre-rejection removal effects, neighbors, projection, repeated operations and complete-map sequence |
| **Total** | **17,340** | Both engines match native and historical disc outputs |

The lifecycle vectors execute **4,580 root lifecycle calls**, including **1,695**
place/remove/restore calls across all 565 actors and 13,515 cells. Across both
suites, **20,471 callable roots per engine** audit caller stack canaries, ESP,
callee-saved registers and now the return-address slot. Existing actor/type/cell/
scenario/tactical/input/map-table arenas, full layer tails, ordered writes/services
and freed-buffer canaries are preserved. The new image-write guard permits only
lazy foundation fields and the selected layer arena, whose fields/sizes/order have
an additional audit: **11,161 image writes per engine**. Startup initializer calls
are separate from that callable-root count and write guard.

Original instructions execute unchanged in isolated Unicorn memory. Height,
permission, no attached animation, visibility/redraw/logic/cleanup and allocator
outcomes remain the explicit services documented in the original notes. Original
lookup/getter/Mark/list/layer/projection/resize/search operations execute. Native
storage and projection/height callbacks remain adapters. No broader original
constructor, resource lifetime, global scheduling or locomotor permission is inferred.

## Evidence, commands and timings

Protected private receipts, exports and expectations:

```text
private/migration/{allied-disc,supplied-ra2-1006}/{occupation,lifecycle}/
private/migration/terrain-lifecycle-checkpoint-verification.json
private/patch-inspection/terrain-lifecycle-1006-mapping.json
```

Fresh runs refuse existing receipts. Replay checks engine/profile/suite, sources,
exporter/cell-exporter, all exported inputs, retained render/raster data and the
exact fresh receipt/expectation fingerprint. Sanitizers may use their own runner
hash; source/input identities must still match. Replay cannot replace fresh evidence.
Historical expectations remain preserved. All proprietary data/research is ignored.

```sh
./build.command
./test.command --data-dir "$PWD/private/game"
build/tools-env/bin/python tests/test_terrain_lifecycle_profiles.py
build/tools-env/bin/python tools/verify_terrain_lifecycle_mapping.py \
  --disc private/disc-allied/game.exe --patched private/official-1006-probe/game.exe
# Existing fresh evidence: native replay only, no original execution.
build/tools-env/bin/python tests/compare_occupation.py \
  --exe private/official-1006-probe/game.exe \
  --native-data-exe private/disc-allied/game.exe \
  --expectations private/migration/supplied-ra2-1006/occupation/expected.json
build/tools-env/bin/python tests/compare_lifecycle.py \
  --exe private/official-1006-probe/game.exe \
  --native-data-exe private/disc-allied/game.exe \
  --native build/sanitize/lifecycle-vectors \
  --expectations private/migration/supplied-ra2-1006/lifecycle/expected.json \
  --report private/migration/supplied-ra2-1006/lifecycle/sanitize-replay-report.json
./run.command --light-demo
```

For fresh execution on a checkout without receipts, omit --expectations and use
the authorized Mac JIT context. For disc replay select the disc executable and
allied-disc expectation folder. README provides the sanitizer build commands.

| Seconds, disc / patched | Occupation | Lifecycle |
| --- | --- | --- |
| Original generation | 8.08 / 8.44 | 22.48 / 22.56 |
| Native comparison | 0.28 / 0.21 | 0.73 / 0.69 |
| Whole fresh CLI | 10.16 / 9.87 | 24.39 / 25.24 |
| Whole sanitizer CLI | 0.75 / 1.49 | 2.33 / 3.18 |

Engines ran concurrently. Checkpoint identity/equality/mapping verification took
**2.31 s**. Earlier inherited delivery time was not measured. No independent review
or acceptance is claimed. One private probe syntax error was fixed before execution;
inspection caught missing Foundation string/parser operands and an extra helper
NOP before acceptance. No full comparison failed and no native playtest repair was
needed. Sandbox SDL had no displays; both **170-frame** regressions passed with
window-server access. Build, synthetic/import/preparation and owned-data rendering/
lighting/scenery/profile checks pass. Only Apple Silicon macOS is tested.

Next: original archive precedence, effective patched inputs and coordinated
prepared/runtime promotion. Complete migration delivery requires applicable full
verification and real SDL rendering/input on the promoted data. Planned ground-layer
draw traversal/eligibility and mixed actor integration follow that boundary. The
prototype, conservative routing, fixed visibility, static-layer caching and host
controls remain explicitly bounded; full-game and whole-frame fidelity are open.
