# RA2 1.006 indexed staging and shadow-index migration

October 14, 2026. Ivalice / Apple Silicon macOS. This extends shadow/color
checkpoint `3c32f05`. [BASELINE_1006.md](BASELINE_1006.md) records supplied-patch
lineage and the completed private Windows transfer; neither was repeated here.

**2,600 fresh original/native behavior cases plus three protocol resets pass on
each engine.** Both native ASan/UBSan replays pass. Native algorithms are unchanged.
Runtime and prepared-data gates remain disc-only pending remaining profile and
archive-precedence migration. Milestone 19 remains the gameplay checkpoint; this
verifies the retained [STAGING.md](STAGING.md) domain, not complete actor, compressed
pool, lifetime or whole-frame parity.

## Identity and reference hypothesis

| Research profile | Executable SHA-256 |
| --- | --- |
| Allied disc | `135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743` |
| Supplied RA2 1.006 patch output | `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f` |

Inputs are `private/disc-allied/game.exe` and
`private/official-1006-probe/game.exe`. The latter remains byte-identical to the
approved Windows copy at `private/windows-baseline-20261014/game.exe`. Both embed
1.08; full hashes select profiles. Supplied-patch lineage does not authenticate the
publisher or establish pristine status of the full installation reported to contain
no-CD modifications. No Windows gameplay/frame observation was added.

Consulted [REFERENCES.md](REFERENCES.md)'s staging/final-composition/cache leads:
redalert2-recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439`, `docs/voxels.md`
(Following the image onto the battlefield, Shadows, Cost), `docs/testing.md` and
LICENSE. Hypothesis: locate actual byte Convert initialization, indexed dispatch,
dirty bounds and shadow-index calls on our patched engine, then execute the retained
domain. Its YR/Steam/EA addresses, HD changes and replacement host behavior are
leads only. The MIT scope excludes generated game code; no upstream, unlicensed
header or generated/lifted code was incorporated.

## Inspected mappings

`tools/verify_staging_mapping.py` checks **11 instruction ranges / 1,416
instructions**, plus actual RTTI/dispatch. Changed operands have explicit mappings,
internal branches preserve relative targets and remaining instruction bytes agree.
No opcode difference was found in these ranges; this is inspection evidence,
not parity for unexecuted branches or external services.

| Boundary | Disc VA | Supplied 1.006 VA |
| --- | --- | --- |
| Complete Convert constructor | `0x483430..0x4838D1` | `0x483650..0x483AF1` |
| Complete selected byte initializer branch | `0x4838E0..0x483D44` | `0x483B00..0x483F64` |
| Complete closest-color search | `0x5FAC40` | `0x6031B0` |
| Complete RGB distance / RGB-to-HSV | `0x634250`, `0x6342A0` | `0x63CFB0`, `0x63D000` |
| Selected indexed span | `0x4860F0` | `0x486310` |
| Dirty-union block | `0x6C7329..0x6C7430` | `0x6D1F09..0x6D2010` |
| Complete successful shadow wrapper | `0x6C7600` | `0x6D21E0` |
| Comparator / binary search | `0x6CECF0`, `0x6CED20` | `0x6D98D0`, `0x6D9900` |
| Original qsort plus two local helpers | `0x76D2E0` | `0x781D46` |
| Convert / indexed blitter / BSurface vtables | `0x788F70`, `0x78950C`, `0x785EF8` | `0x79DF70`, `0x79E50C`, `0x79AEF8` |

Range ends are exclusive. The initializer continues into word-surface handling at
`0x483D44 -> 0x483F64`. That entry is explicit metadata; the newly inspected range
and executed staging domain cover its byte branch only. Complete word initialization
is not migrated by this checkpoint.

Similar RGB-distance and comparator candidates were resolved through actual
closest-color and wrapper operands. RTTI selects ConvertClass, BlitTransXlat<uint8>
and BSurface. Indexed slot 1 selects the listed span; BSurface bpp slot 28 selects
`0x4113B0` in both engines. No general address displacement is assumed.
`tests/staging_profiles.py` adds 52 explicit mappings to inherited shadow/composition/
raster metadata; inherited mapping verifiers also run for patched research. Full
render/snapshot/cached-draw entries used as fixture services do not acquire
implementation parity from their mappings.

## Executed boundary and audits

| Passing results per engine | Count |
| --- | ---: |
| Complete one-shade byte converters | 12 |
| Dirty unions, including empty/tie/signed bounds | 518 |
| Complete clipped indexed surfaces | 128 |
| Complete final RGB565/depth surface copies | 128 |
| Complete assembled unit/staged-shadow/world surfaces | 128 |
| Successful shadow wrapper/index decisions and state | 1,686 |
| Protocol resets | 3 |
| **Total results / behavior cases** | **2,603 / 2,600** |

Assembled cases retain all 32 body bins, independent turret headings, original part
order and two supplied viewport/depth/alpha profiles. Original stock VXL loading,
pose, lighting, rasterization, staging, shadow projection and final surfaces execute
unchanged instructions. Palette/alpha/depth, actor/type records and index storage
are explicit fixtures. File/heap, type queries and render/snapshot/cached-blit
services in the decision fixture remain supplied. Original compressed snapshots,
failure/eviction and complete actor integration are excluded. STAGING.md details
the retained domain and services.

Per engine, **5,305 callable roots**, **903 isolated blocks** and **403 guarded
allocations** are audited, including setup/inherited calls. Callable checks preserve
return address, caller stack beyond consumed arguments, ESP and callee-saved
registers. Convert permits only converter fields, guarded allocations and the
declared registry count/slot; palettes, surface and other registry metadata stay
unchanged. Indexed/final copies preserve source, rectangles, converter/heap and
applicable depth/alpha/palette inputs. Temporary locks on all four established
surfaces must restore zero counts.

Dirty union permits three stack-local words and the 16-byte dirty rectangle,
checking stop EIP, unchanged ESP, other locals and caller guard. Staged shadow
restricts reset/queue/flush scratch/crop stores, preserving model, matrices, offset
and assembled stencil; its lock returns to zero. Shadow wrapper preserves actor/
type/model/vtable and unrelated prior allocations, allowing index, current entries
and new guarded allocations. These are bounded original-fixture caller/input/write
audits, **not ordered native/original writes, full actor arenas, original heap
ownership or lifetime/frame parity**.

TEMPERAT.PAL remapping, first weighted-Manhattan tie, nonzero-to-zero erasure,
128-pixel anchor, dirty-union extra edge pixel, single world blit followed by
shadows, signed sort/hot behavior and -1 bypass retain their recovered meaning.
No native arithmetic or cache decision changed.

## Evidence and reproduction

Fresh expectations, receipts, exports and buffers remain ignored under:

```text
private/migration/allied-disc/staging/
private/migration/supplied-ra2-1006/staging/
```

Fresh execution refuses existing expectations/receipts. Replay pins exact engine/
profile, oracle/mapping sources, exporter, assets, retained data and expectation
fingerprint; it cannot replace fresh evidence. Ten synthetic profile/evidence guards
pass, including a live-selector check against mislabeled receipts. Both initial
full runs matched outputs but overwrote the engine-profile label with a viewport
case integer. Their receipts are preserved unchanged in each profile's
`staging-rejected-profile-label/` with `REJECTED.txt`; they are rejected evidence,
not relabeled or accepted. Corrected fresh original runs produced accepted receipts.

Native inputs retain disc raster data
`f357f3b4d7b048b7f65d7a43f4f96a41e6c21b5974bb1340d7fd98e92abcd8a3`
and render data
`50d2876e6bf8a3b9d535a1843ef93f41109b7021a15e1dbacb47aaa881389c6d`.
Patched research requires explicit `--native-data-exe` disc identity. Three VXLs,
VPL, TEMPERAT.PAL and ISOTEM.PAL remain hash-pinned supplied assets. This does not
promote patched archive precedence or prepared/runtime inputs.

```sh
./build.command
./test.command --data-dir "$PWD/private/game"
build/tools-env/bin/python tests/test_staging_profiles.py
build/tools-env/bin/python tools/verify_staging_mapping.py \
  --disc private/disc-allied/game.exe --patched private/official-1006-probe/game.exe
# Fresh evidence already exists here; replay without original execution:
build/tools-env/bin/python tests/compare_staging.py \
  --exe private/official-1006-probe/game.exe \
  --native-data-exe private/disc-allied/game.exe \
  --expectations private/migration/supplied-ra2-1006/staging/expected.json
# For instrumented replay after README's sanitizer build, add:
# --native build/sanitize/staging-vectors
# --report private/migration/supplied-ra2-1006/staging/sanitize-report.json
./run.command
```

On a checkout without receipts, omit `--expectations` for fresh original execution
in the authorized Mac Unicorn JIT context. Both sanitizer replays pass without
diagnostics. Current source/receipt/engine/data/native identities and cross-engine
outputs pass `private/patch-inspection/verify-staging-checkpoint.py`, recorded in
`private/migration/staging-checkpoint-verification.json`. Mapping receipt:
`private/patch-inspection/staging-1006-mapping.json`. Discovery/disassembly/probes
remain private; no instruction bytes are patched or copied into tracked code.

Fresh affected **disc** regressions pass in
`private/migration/disc-staging-regressions-v2/`: 3,257 unit-light, 4,743 lit-cache,
2,204 shadow-key, 420 scenery, 808 props and 1,128 terrain-type results, including
protocol/reset commands. The initial regression workspace is preserved; its cache
suite lacked legacy relative staging assets. Preparing local exports and rerunning
in v2 passed. Full assembled draws also revealed locks on existing depth/alpha
surfaces; fixture audit declarations were corrected, with no native algorithm change.

Build, native/sanitizer synthetic checks, import/preparation guards, owned-data
checks and both 170-frame SDL regressions pass. Native integration is not original
input/timing/frame parity. Source installations, media, Outpost 2, Windows task and
system configuration are untouched. Only Apple Silicon macOS native support is
tested. Map/static/unit light, cache, scenery, occupation/lifecycle and archive
precedence migration precede runtime/data promotion and milestone 20. Controls/
routing/clearance, visibility, scheduling, actor/house/cache lifetime, nonflat/status
branches and whole-frame parity remain adapters or open.
