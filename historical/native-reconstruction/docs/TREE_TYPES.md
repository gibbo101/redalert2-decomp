# Milestone 16: stock static tree types and image reload decisions

The separately hash-selected supplied 1.006 migration is recorded in
[SCENERY_1006.md](SCENERY_1006.md). This note preserves the original disc evidence.

October 14, 2026. Baseline 8b90481. Ivalice / Apple Silicon macOS.
Base Allied-disc GAME.EXE, embedded 1.08, image base 0x400000, SHA-256:
`135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743`.
The original oracle checks that hash before addresses. Runtime original executable
reads remain track data only; no original instructions execute in the game.
[PROPS.md](PROPS.md) extends this checkpoint with ordinary props and raw SHP bodies;
the omitted-prop and format-3-only limits below are historical.

## Result and provenance

The original mp03t4.map has **531 ordinary trees across 22 types**. All are now
presented with their original body/shadow images. All **28 supplied TREE01..28
images** were tested against unchanged original draws before enabling that range.
TREE29/30 are in the owned rules list but their temperate images are absent from
this installation; they remain explicitly unsupported. No replacements were downloaded.
The remaining 42 terrain entries include signs, traffic lights, a pole, headstones
and eight alternate/animated Tiberium trees. They remain omitted. General actors,
occupation/pathfinding, animation/damage and whole-frame fidelity are incomplete.

The native asset boundary keeps one image per type and every map placement;
rendering still uses the recovered [SCENERY.md](SCENERY.md) kernels. **T** cycles
all tree placements; **H** returns to the Rhino. Registry storage, case folding,
static-layer scheduling and camera controls remain native adapters.

Consulted the pinned OpenRA `e7e9e4ad270221d7fb9725b348c75504d48c1ebd`,
`OpenRA.Mods.Common/SpriteLoaders/ShpTSLoader.cs` and COPYING, and YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88`, `TerrainTypeClass.h`.
OpenRA's SHP format interpretation remains the attributed GPL adaptation recorded
in THIRD_PARTY.md. YRpp offers type/property vocabulary only; its snapshot has no
incorporation license and no header code was reused. REFERENCES.md's terrain/SHP
entry guided the search. Original type/image code independently decides behavior;
no generated recompilation or copied game code is included.

## Recovered decisions and boundaries

| Exact-base evidence | Address |
| --- | --- |
| TerrainType constructor/default flags, inspected | 0x6DA3D0..0x6DA514 |
| ObjectType-success / Terrain strength-default prefix, executed | 0x6DA7A0..0x6DA7D9 |
| Complete theater-image reload, executed | 0x6DA5D0 |
| Original CRT name construction, executed | 0x76E780 |
| Supplied image-loader service | 0x592370 |
| Supplied successful free service | 0x76D2D5 |
| Theater extension records, stride 104 | 0x785BAC, 0x785C14, 0x785C7C |

`terrainStrengthDefault()` preserves the exact sentinel: strength **-1** selects
rules TreeStrength (+0xE1C); every other signed value is retained. The constructor
sets strength -1. After the successful base ObjectType INI fixture, the actual
Terrain prefix writes the fallback only when still -1. This fixes an explicit
Strength=-1 override that the earlier adapter incorrectly refused. Original INI
parsing and the complete type constructor/registry are not executed in this test.

`terrainImageReload()` preserves the complete original reload decisions:

1. Unless forced (original byte 0xA28933), requesting the previous theater
   (0x7C396C) skips the whole loop.
2. Each type without the theater-image flag (+0x1FC) is skipped.
3. Original _makepath combines the **type identifier at +0x24**, null drive and
   directory, and the selected TEM/SNO/URB extension. Identifier case is preserved.
4. A previous image is freed only when the ownership byte +0xA8 is nonzero **and**
   image pointer +0xA4 is nonnull.
5. Image pointer is cleared, ownership is cleared, the loader receives the filename,
   then its result is stored. A null loader result is still stored. The routine
   does not update the previous-theater global; the caller owns that state.

Do not substitute the generic Image field at +0x1C8 for the theater reload's ID.
Native filename length/character checks are bounded engineering guards, not recovered
original validation. Runtime uses the fresh temperate decision, required read-only
archive data and immutable native storage. It does not run the original global
registry/free/loader lifecycle. Snow/Urban **selection and naming** are verified;
their assets/rendering are not, so runtime presentation accepts temperate maps only.

The supported healthy static profile continues to require explicit stock rules,
Theater=yes, Foundation=1x1, strength above 1, two format-3 frames, no map type
section, no alternate Image, and false IsAnimated/SpawnsTiberium/IsVeinhole/WaterBound.
Default flag stores and named INI access sites are inspected base evidence;
the native INI parser and profile guards are integration adapters. Foundation and
occupation metadata do not replace conservative routing with original collision.

## Verification

`original_terrain_types.py` executes unchanged original instructions. Reload
fixtures supply a bounded array/type arena, previous theater, force flag, successful
free and image-loader returns (including null). The actual CRT name construction,
loop/guards and stores execute. Comparisons include **ordered free/load events,
ordered pointer/ownership writes and final identities**. Original arena canaries
assert no other type bytes change, and the previous-theater global remains intact.
These are bounded type arenas, not a full game heap or caller-stack audit.

`compare_terrain_types.py` uses the original complete Terrain caller and compressed
SHP drawing from milestone 15 for each owned tree. The oracle now preserves each
supplied canvas rather than supplying TREE01's 155×155 canvas for every type.
Each image gets eight placements covering four clipped edges, shifted clip origins,
fully outside output, different heights/depth ties and signed light extremes.
Additional cases run both frames with actual ordinary LightConvert tables.
Full little-endian RGB565 and depth planes compare as SHA-256 hashes.

| Boundary | Matching results |
| --- | ---: |
| Strength-default original prefix | 72 |
| Complete original theater-image reload | 384 |
| All owned trees through complete Terrain and both shape draws | 224 |
| All owned tree frames with original converters | 448 |
| **Total** | **1,128** |

The retained 420 TREE01 results were regenerated after the canvas fixture change
and still pass. Native integration separately checks 531 placements / 22 images,
inspection of every map type, body/shadow visibility, reversible light, house color
separation, repeated layers, tank/tree overlap, conservative routes and SDL T/H.
ASan/UBSan replay uses the identity-checked original expectations. Native previews
are QA only; no original-game captures or whole-frame comparison are claimed.

```sh
./build.command
./run.command                    # T cycles trees; H returns to Rhino
./test.command --data-dir "$PWD/private/game"
build/native/presentation-check private/game build/trees
build/tools-env/bin/python tests/compare_terrain_types.py --exe private/disc-allied/game.exe
# After README's headless sanitizer build:
build/tools-env/bin/python tests/compare_terrain_types.py \
  --exe private/disc-allied/game.exe --native build/sanitize/scenery-vectors \
  --expectations private/terrain-types/expected.json \
  --report private/terrain-types-sanitize-report.json
```

Protected exports reuse scenery-vectors' read-only export rules and now include
all 28 verified image names. Sources, symlinks and different replacements are
refused before any export writes. Expectations/assets: private/terrain-types/.
Reports: private/terrain-types-report.json and private/terrain-types-sanitize-report.json.
Reports pin original/native/render data, oracle sources and owned inputs; cached
replay also hashes the expectation file. Disassembly remains private/terrain/.
No new prepared executable table or dependency is introduced. Original installation
and outpost2-native remain untouched. Only Apple Silicon macOS is tested.

## Next work and original-game measurements

Next recover the remaining ordinary static terrain props and their frame/type
selection, before alternate animated terrain. Do not infer an animated profile
from the number of SHP frames, or assume all props share the healthy two-frame tree
profile. Then recover original occupation/foundation and actor scheduling needed
for faithful unit/scenery interactions; conservative route padding is still an adapter.

On future Windows testing, pin this executable/map and capture a small, broad tree,
a tall narrow tree and TREE28 at fixed detail, palette, height and resolution.
Log actor type/image pointers, selected frames, draw order and depth crops while
panning and moving a healthy Rhino behind/in front of each. Rebuild after a theater
change and log reload/free calls and ownership writes. These measurements settle
integration and lifetime questions beyond the isolated reload/draw boundaries;
screenshots alone cannot prove them. Windows setup remains deferred.
