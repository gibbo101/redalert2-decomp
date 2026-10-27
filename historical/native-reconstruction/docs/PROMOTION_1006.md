# Supplied RA2 1.006 native prototype promotion

October 14, 2026. Ivalice / Apple Silicon macOS. Implemented from checkpoint
`6227b8a`. The existing bounded map/scenery/Rhino scenario now runs with the
supplied patched dataset and matching prepared numeric inputs. `run.command`
prefers that prepared folder. This completes the selected baseline migration;
it does not complete RA2 or establish original whole-frame/game parity.

## Sources and runtime boundary

| Profile | Engine SHA-256 | Default prepared directory |
| --- | --- | --- |
| Retained Allied disc, embedded 1.08 | `135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743` | `private/derived` |
| Supplied 1.006 patch output, embedded 1.08 | `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f` | `private/derived/ra2-1006` |

The patched engine remains byte-identical to the approved private Windows copy.
Supplied patch lineage and the user's reported no-CD modifications are recorded
separately from publisher authenticity in [BASELINE_1006.md](BASELINE_1006.md).
No new Windows action, executable transfer or original-game observation was needed.

`GameAssets` explicitly selects `AssetStore::Registration::InitialTemperate`.
It resolves GAME.EXE, checks its complete hash, selects source-specific default
prepared paths, and requires each supplied/prepared override to match that same
source. Unknown engines, altered/truncated files and mixed profiles fail closed.
The general AssetStore default and historical research exporters retain their
legacy policy; they are not silently changed or relabeled.

The initial reader's archive ordering/provenance evidence and its host boundaries
remain exactly those in [EFFECTIVE_ASSETS_1006.md](EFFECTIVE_ASSETS_1006.md): 13
registered archives, loose-first reads, nested resolution, sorted host enumeration,
missing optional movies and temperate-only startup. The 317-query decoded-index
original-fixture audit remains narrower than original encrypted parsing/full
nested-open/startup parity. Of these selected input hashes, 315 match across
profiles; only GAME.EXE and RULES.INI differ. Relevant stock rules inputs were
checked earlier; this does not enable all patched gameplay or custom profiles.

The runtime still reads executable track metadata/data only, after hashing;
original code is never executed. Direction, normal/sqrt, raster and trigonometric
data are prepared separately. Explicit patched mappings follow the independently
inspected movement, presentation and raster profiles; normal pointers are followed
in the selected image, without applying a second relocation. No universal address
shift or version-string inference is used. Simulation arithmetic is unchanged.
No new upstream/header/generated game code or dependency was incorporated.

## Prepared and decoded data evidence

| Patched file | Bytes | Complete-file SHA-256 |
| --- | ---: | --- |
| direction-data.bin | 16,464 | `41d862df192849730d7ccec27f31cd8fe344ec6ade4f15ef7324a4e9243cd38a` |
| render-data.bin | 69,944 | `afccee17250dcb5fe08c7da2183d530d22c2380c8c98d253f5f5b1847ba1d032` |
| raster-data.bin | 41,312 | `0feb5f4985519e5432ed5d464a8d1e3e5877e8e3cabe3d71bd7f9f3c7c9d435b` |

The old files remain unchanged. For each pair, the 32-byte source hash in the
40-byte header differs correctly and every payload byte matches. Native
`prepared-data-check` explicitly serializes every decoded Drive descriptor/track,
direction field, normal/sqrt field and raster/trigonometry field without struct
padding: **131,956 bytes match bit-for-bit**. This is a data/decoder proof, not
an independent original-behavior oracle.

`check_prepared_profiles.py` passes **38 checks** on normal and ASan/UBSan runners:
exact preparation/source headers, decoded equality, each mixed-file combination,
truncation/corruption and unknown engines. `check_prepared_runtime.py` passes
**five application checks per dataset**: automatic selection, explicit matching
paths with equal output, and each mismatched override refused before output.
Synthetic preparation/profile/receipt guards are also retained.

## Original evidence replay and integration

`tests/replay_promoted_data.py` checks the original fresh receipt and expectation
fingerprint, exact engine/profile, recorded oracle/native sources, mapping tools,
prepared inputs, all asset/explicit/synthetic fixture hashes, and input identities
before/after execution. It runs **180,573 cached original results per profile per
pass** through the current native runners: first retained data, then source-matched
promoted data. Normal and ASan/UBSan builds both pass for both profiles. The count
includes three staging resets and fourteen voxel/shadow resets, and excludes Facing
and archive families. These are cached original expectations from the independently
executed profile suites, not new original execution or additional independent cases.

A normal strict legacy replay first rejected a changed exporter binary hash.
The historical validators and their rejection remain intact. The content replay
uses the existing unchanged fixture files directly: no exporter runs. Historical
exporter hashes remain in the fingerprinted original receipts; current runner
hashes are recorded separately. Every recorded fixture/source hash must match,
and unaccounted identity fields are refused. This preserves eligible original
expectations across a native rebuild without claiming the exporter binary is
unchanged. Four synthetic guards cover fixture mutation, receipt tampering,
cross-engine substitution and content replay without the historical exporter.

Private complete numeric replays:

```text
private/migration/promoted-patched-normal-v3/
private/migration/promoted-disc-normal/
private/migration/promoted-patched-sanitize/
private/migration/promoted-disc-sanitize/
```

Earlier partial attempts remain in sibling folders; they have no complete summary.
The unchanged Facing runner hashes still match their pinned normal (both engines)
and patched sanitizer receipts; Facing received no new execution. The archive
families additionally pass **5,344 primitive + 688 stage results per engine/build**
through their unchanged strict validators. Effective-source audits pass **317 queries
per engine/build** through their unchanged validator. These are native replays;
their original-only assertions remain prior evidence. Receipts are under
`private/migration/promotion-archive-replays/` and `promotion-effective-*.json`.

Native synthetic/import/preparation/profile tests, owned light/cache/scenery
checks and headless sanitizer integration pass. The scenario still loads 13,515
cells, 266 templates and 565 scenery actors / 30 types with 4,520 neighbor
contributions. Body/turret/barrel retain one HVA frame each. Both actual **170-frame
SDL regressions pass on each dataset**, exercising selection, independent turns,
movement, waypoints, retargeting, scenery inspection, player colors, pause/speed and
reversible light. The preferred patched launcher passes real-clock speed 3: **21
updates in 1,002 ms**. This is host pacing/integration evidence. Both diagnostic
still/curved native frames match across datasets; the still was inspected. They do not
establish original screenshots or full-frame fidelity. No playtest repair was needed.

## Try and reproduce

```sh
./build.command
./run.command                         # prefers private/official-1006-probe
./run.command --light-demo
./test.command --data-dir "$PWD/private/official-1006-probe"
./test.command --data-dir "$PWD/private/game"   # retained profile
# Explicit overrides / RA2_DATA_DIR continue to work:
./run.command --data-dir "$PWD/private/game"
```

Preparation requires legitimate supplied files and refuses source-install writes.
Default outputs are selected by the verified hash; old data is not overwritten:

```sh
python3 tools/prepare_direction_data.py --exe private/official-1006-probe/game.exe
python3 tools/prepare_render_data.py --exe private/official-1006-probe/game.exe
python3 tools/prepare_raster_data.py --exe private/official-1006-probe/game.exe
python3 tests/check_prepared_profiles.py --disc private/disc-allied/game.exe \
  --patched private/official-1006-probe/game.exe
python3 tests/check_prepared_runtime.py --data-dir private/official-1006-probe
build/tools-env/bin/python tests/test_promoted_replay.py
# Existing private profile expectations required; choose a fresh output directory:
build/tools-env/bin/python tests/replay_promoted_data.py \
  --exe private/official-1006-probe/game.exe --disc private/disc-allied/game.exe \
  --output-dir private/migration/promotion-repeat
# Add --native-dir build/sanitize after README's headless sanitizer build.
# Repeat with --exe private/disc-allied/game.exe for the retained profile.
```

Fresh original evidence on a checkout without receipts still uses the separate
`compare_*.py` research commands and authorized Mac Unicorn JIT context. Historical
research CLI defaults deliberately retain disc fixture inputs; their
`runtime_profile_promoted: false` describes those receipts, not today's GameAssets
policy. Never rewrite them as promoted/fresh evidence.

## Delivery cadence trial and remaining work

This delivery inherited the already committed subsystem/profile/archive recovery
and uncommitted initial preparation work. Full inherited delivery elapsed time,
earlier build/check costs and this continuation's first build/owned/SDL wall times
were not instrumented; no precise total is claimed. Complete replay summaries
record measured elapsed and per-suite native times; concurrent runs can contend.
Measured complete CLIs (both passes): **170.30 s patched normal, 173.61 s disc
normal, 229.74 s patched sanitizer and 223.44 s disc sanitizer**. Archive replay
timing is separate. No cache infrastructure was added.

Failed attempts: the initial edit patch had a stale context and applied no changes;
the first strict numeric replay rejected the changed exporter hash; a first content
replay used the movement verifier filename for presentation and correctly rejected
its identity before that suite; an effective-reader command omitted required
`--native` and executed nothing. These are preserved/corrected tooling attempts,
not accepted original evidence. No numeric mismatch, sanitizer diagnostic or SDL
playtest repair occurred in accepted runs. Process inventory was unavailable in the
sandbox; confirmed command handles supplied progress/completion instead.

The trial reduced unnecessary original re-execution by validating immutable fixture
content and replaying both table profiles, while preserving strict historical
checks and separate receipts. Several minutes of tree/prop serialization/replay
remain a measurable cost. This is a committed delivery candidate after local
verification, not independent review/acceptance. Continue the full-game goal.

Next observable capability: **correct moving-Rhino/scenery drawing traversal in a
reproducible crossing/occlusion scenario**. First recover patched ground-layer
traversal and Terrain draw eligibility, including ordered visits, redraw/visibility
transitions, stable ties and skipped actors. Then integrate mixed actors. Dynamic
invalidation and source ownership remain dependencies. The current immutable
terrain/scenery layer and subsequent tank draw remain host policies.

Other unchanged limits: controls/direct routing, conservative footprint clearance,
spawn/house assignment, visibility, actor/cache ownership, alternate terrain and
nonflat/animated poses. Combat, economy, AI, campaigns, multiplayer, audio, original
saves and YR remain later work. Only Apple Silicon macOS is tested. Source installs,
discs, Windows copies and Outpost 2 were untouched. Proprietary files, previews,
executables, research and receipts stay ignored; no public release occurred.
