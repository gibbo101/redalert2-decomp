# Supplied RA2 1.006 complete Unit world and shadow join

October 15, 2026, after `c3c2b78`. The new readable
`src/render/UnitVoxelShadowWorld.*` helper binds the complete Unit/staging/depth/
final-world root to the complete shadow child, with four independent indexes
sharing one supplied compressed pool. Actual original children execute within
one unchanged Unit root. This helper remains unwired; the observable runtime
remains [the moving Rhino crossing](CROSSING_1006.md). It is a prerequisite in
the same moving/turning/current-cell-light drawing delivery, not a new milestone.

## Identity and reference hypothesis

Exact supplied engine: `private/official-1006-probe/game.exe`, 4,485,392 bytes,
SHA256 `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
The approved private Windows copy was rehashed to the same identity in this
continuation. Embedded 1.08, supplied 1.006 lineage and reported no-CD provenance
remain separate; pristine authenticity is not established. Source installations/
discs, Windows and the sibling project were not modified. No system change or
additional executable transfer was needed.

Consulted [REFERENCES.md](REFERENCES.md)'s pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439`, `docs/voxels.md` Shadows/cache
and LICENSE, plus YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88`,
Techno/Foot/TechnoType/Surface declarations. Hypothesis: the complete Unit root's
Foot shadow forwarding can use the recovered shadow parent and share its pool
with three lit indexes, preserving post-final flags/stencil and saved-dirty
cleanup. Exact base instructions and execution decide it. No upstream/header/
generated or lifted game code was incorporated; no dependency/notice was added.
The reference MIT grant excludes generated game-derived code.

## Complete boundary and preserved behavior

Unit root `0x6FF690` calls Foot shadow forwarding `0x4C9A40` at `0x700580`.
That actual wrapper forwards to `0x6D21E0`; successful cold requests execute
fresh raster, snapshot, signed index append and recursive cached world drawing.
Warm requests draw the compressed snapshot, while bypasses execute the raw
world span. Actual lit/cache/staging, ordinary Foot/base depth, stock split final
surface and byte cleanup execute in the same Unit call. There is no supplied
shadow draw in this new fixture. Existing earlier oracle sources remain frozen.

The native helper binds the already verified Unit/world and shadow helpers.
It derives shadow depth/gradient from the same immutable map/type/base inputs
used by lit/final drawing. Ordinary Track forwarding is already performed by
the Unit helper; do not apply the Foot offset a second time. Body/turret/barrel
indexes are type +0x214/+0x228/+0x250; shadow is the separate +0x23C index.
All four share the supplied pool. Preserve independent hot/sorted/capacity state.

The shadow child sees restored world/staging flags and the composed byte stencil.
Its cached draw can enlarge the global dirty rectangle. The Unit caller still
clears the **saved pre-shadow dirty region**, retaining the updated rectangle
and bytes outside that saved region. NoShadow, DisableShadowCache, lit disable,
key gating and the actor predicate remain distinct decisions. Predicate changes
select the original high-bit key/stencil behavior. Frame-zero HVA, model-before-
flatten geometry, recursive lookup, raw bypass's lack of dirty union, flags
0x2001/gradient 2, selector slots, strict depth reads and half mask retain
[SHADOW_VOXEL_WORLD_1006.md](SHADOW_VOXEL_WORLD_1006.md)'s exact scope.

The new scoped original fixture copies only our own earlier Unit setup, expands
preservation/write/input/type-after checks to four indexes and declares the raw
converter's four-byte +0x17C scratch output. It distinguishes raw-shadow generic
world copies from lit-world copies. Those assertions do not replace original
instructions. Full cached/fresh shadow, final and staging selector/surface/span
instructions execute. Code-only allowlists retain all complete inspections.

Loaded one-section body and one-frame supplied HVA, healthy Track/ground/ramp-zero,
identity global/no half scale, zero Z-shape, ordinary 53-row house palette,
stock depth metadata 10/8/13/0 and bridge-size flag 1 bound the claim. Synthetic
map/contact/planes/palette/camera/type/actor records, source assets/prepared
numeric tables, successful heap and sufficient pool remain supplied. Tile
bounds write twelve checked zero bytes into the original caller stack; base
brightness/visibility/height/house/predicate services remain bounded as in the
prior Unit/world profile. Matched planes/contained clips/loaded-body requirements
and native pool failures are safety guards, not original malformed-input claims.

## Evidence and reproduction

**152 fresh original/native results including eight resets** pass, with normal
and ASan/UBSan replays. Forty cold complete draws, forty warm redraws, sixteen
reverse signed-key/clipping draws and forty-eight cell-depth/stencil/raw-bypass/
NoShadow/cleanup draws cover every body heading plus a black staging palette.
Both identity and supplied nontrivial camera inputs execute. Color/depth/alpha,
pre-shadow stencil/request, post-cleanup bytes/dirty state, complete normalized
pool/cursor and all four index states match. Depth and alpha remain unchanged.

The receipts record **306 checked roots / 120 successful guarded
allocations**, 144 actual Unit roots, 144 actual Foot shadow entries,
208 shadow-parent entries, 82 fresh shadow renders, 4,913 compressed
shadow spans, 786 raw shadow spans, 220,725 checked zero Z-shape bytes and
344,255 bounded padded encoder reads. Both stock final-copy gradients execute;
196,179 color pixels change across supplied fixture planes. These are execution
counts, not additional independent comparisons or whole-frame fidelity.

Caller stack/return/callee-saved registers, declared image writes, actor/other
heap/old pool/planes/arguments, four-index type-after preservation, heap/capacity
canaries, padded reads and restored surface locks retain scoped audits. Ordered
native/original writes and full actor arenas/ownership are not claimed.
Receipts are under `private/unit-draw-1006/unit-shadow-world-v1/`; exact transitive
source/input/inspection identities and expectation fingerprints are checked.
Previous Unit/world, cached-shadow and complete-shadow normal/sanitizer runner
hashes and receipt source entries remain unchanged; their replays stay eligible.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/python tools/verify_unit_voxel_shadow_world.py \
  --exe private/official-1006-probe/game.exe
build/tools-env/bin/python tests/compare_unit_voxel_shadow_world.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/unit-draw-1006/unit-shadow-world-v1/expected.json \
  --report private/unit-draw-1006/unit-shadow-world-v1/NEW-REPLAY.json
# Add --native build/sanitize/unit-voxel-shadow-world-vectors for sanitizer replay.
# Fresh original execution needs authorized host JIT access, a NEW --output
# directory and no --expectations. Never overwrite accepted receipts.
./run.command --crossing-demo
```

## Accounting and continuation

Fresh driver/original/native time: **1335.806/1291.513/0.229 s**.
Normal replay driver/native: **43.493/0.083 s**;
sanitizer replay: **45.787/2.696 s**. Normal/sanitizer builds take
**3.890/7.460 s**, normal/sanitizer test drivers **0.990/1.780 s**, the Python driver
**1.480 s**, and SDL **2.970 s**. Builds, **372 Python tests**, **16 normal /
15 sanitizer CTests**, source/diff/local-link audits and the existing SDL crossing
pass. SDL records 79 samples / 78 updates, 22 occluded samples / maximum 150
hidden pixels, selection/right-click, no trails, bypass, clipping and pan return.
The occluded PNG was visually inspected. It checks existing runtime, not this
unwired helper or original whole-frame fidelity; the app remains arm64.

Private start/attempts/closing records retain accounting. Full inherited delivery
and initial build elapsed are unavailable. The first pilot's direct bypass hit
an older lit-only generic world-surface assertion. The new scoped fixture checks
that raw shadow call separately, while executing unchanged original instructions.
The five-result pilot then passes. No native numeric correction was needed in
this join. No original instruction patch, worker, evidence cache, gameplay repair
or source/system/Windows change occurred. Contended harness times are not FPS.

Next nest the ordinary DrawIt/visibility/current-cell-light caller around this
complete child, then wire the runtime and accept the reproducible moving/turning/
lighting crossing. Full actor/map/type/pool/converter construction and ownership,
pitch invalidation, allocation/failure/eviction/lifetime, alternate status/ramps,
decorations, scheduling/camera/fog/UI and whole-frame fidelity remain open. Only
Apple Silicon macOS is tested; locally verified recovery is not independent
acceptance. Full base RA2 then Yuri's Revenge remains active and incomplete.
