# Supplied RA2 1.006 per-frame traversal checkpoint

October 14, 2026. This is a prerequisite of the moving-Rhino/scenery crossing
delivery, not its completion. Readable C++ now reproduces the bounded original
two-pass caller. **2,808 fresh original/native scenarios**, normal and ASan/UBSan
replays pass. The runtime does not yet call this kernel: combined execution with
the subsequently recovered ordinary Unit eligibility, redraw-region scheduling
and their integration remain dependencies. See UNIT_VISIBILITY_1006.md.

## Identity and references

Only the supplied patch engine is accepted:

```text
private/official-1006-probe/game.exe
SHA256 e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f
4,485,392 bytes; embedded version 1.08
```

The approved private Windows copy is byte-identical. Supplied patch lineage and
the hash identify this profile; user-reported no-CD provenance is preserved.
This is not a claim of pristine publisher authenticity. Disc evidence is retained
separately. No Windows task, installation, original instruction or system setting
was changed here.

Consulted pinned redalert2-recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439`
`docs/voxels.md` (The path of one unit) and LICENSE, plus YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` `ObjectClass.h`, `FootClass.h`,
`TechnoClass.h` and `GeneralDefinitions.h`. These supplied type/DrawBehind/
DrawExtras/flag naming hypotheses. Exact base-binary tables and execution below
establish the tested behavior. Actor flag initialization is still supplied, not
verified by these headers. No upstream, generated or lifted game code was copied.

## Inspected and executed boundary

`tools/verify_dynamic_traversal.py` pins four complete additional ranges:

| Routine | Address | Coverage |
| --- | --- | --- |
| Per-frame traversal caller | `0x6A93F0` | Complete caller executes in the bounded profiles below |
| Techno DrawBehind | `0x6C3B30` | Complete routine inspected; actual Unit type=1 no-op exit executes |
| Unit type leaf | `0x70A2D0` | Actual leaf executes |
| World projection | `0x6A27A0` | Actual routine executes; original scale initializers also execute |

These total **1,113 instructions**; the verifier also inherits the nine-range
Terrain visibility inspection. Unit RTTI and actual slots +0x2C/+0x48/+0x4C/
+0xFC/+0x104/+0x108 are checked. Fixtures retain original Unit `0x7ADDF8` and
Terrain `0x7AD3CC` vtables. The actual shared coordinate getter executes.

The entire caller runs unchanged, with nonnull, immutable layer collections.
Only Unit actors taking the Foot flag branch and Terrain actors taking its type
branch are admitted. Non-Foot Techno, animation/other-object branches and nonempty
auxiliary drawing collections are refused by the native API. The original caller
writes visible before its null test; null fixture slots are therefore excluded,
not treated as an original safe skip.

Explicit services in both implementations:

- Inverse-camera matrix transform returns supplied float32 vectors. Matrix
  construction/inversion is not recovered here; all actual caller inputs, stores,
  conversion and wrapping still execute and are compared.
- Foot +0x4C secondary getter, whose returned coordinates this caller discards.
  Its locomotor/indexed-destination behavior remains open.
- Map rejection predicate, complete +0xFC eligibility, and DrawExtras. The real
  virtual dispatch reaches each service. Eligibility may alter the shared clip
  rectangle, and these supplied mutations are part of the ordered expectations.
- Actor flags, coordinates, animated/crumbling bytes and healthy construction are
  fixture inputs, not a new constructor/animation/lifecycle recovery claim.

Terrain eligibility was independently recovered in TERRAIN_VISIBILITY_1006.md;
this new caller oracle deliberately supplies it to isolate traversal. It does not
claim original Unit eligibility or final rendering from those earlier results.

## Recovered caller behavior

- Three inverse-camera calls use wrapped integer expressions converted through
  float32 stores under original round-toward-zero. The first input is
  `(origin.x + width/2, origin.y - height, 0)`; the second is
  `(origin.x + 2*width, origin.y + height/2, 0)`; the third is
  `(origin.x - width, origin.y + height/2, 0)`. Half division truncates toward zero.
  The third Y reuses the second input's saved local. It is not simply height.
- World lower bounds are truncated first X/Y. Extents double the truncated
  second-X-minus-first-X and third-Y-minus-first-Y, with 32-bit wrapping. Tests
  preserve lower-inclusive/upper-exclusive comparisons without normalizing bounds.
- Each of five layers is visited forward in the first pass. Every visit clears
  visible, including duplicates. Foot actors test world bounds, call +0x4C, then
  conditionally call the map predicate when scenario bit `0x1000` is set.
- Actual coordinates/projected pixels minus origin use inclusive X margins
  `[-360, surfaceWidth+360]`, Y `[-180, surfaceHeight+180]`. Accepted Foot actors
  set visible, call DrawBehind, then +0xFC with the full force dword and third=0.
- Terrain must be animated or crumbling to enter this dynamic branch. It tests
  world bounds, always calls the map predicate, sets visible and calls +0xFC with
  third=0. Healthy static Terrain is handled by the separate recovered static pass.
- A second forward pass visits visible actors with flag bit 1. Foot +0x4C repeats;
  its map check additionally requires nonnull context and zero bypass. Coordinates
  and projection are recomputed before margins and DrawExtras. Visible persists
  even when the extras map/screen checks reject.
- Every eligible call shares the original viewport rectangle. It receives neither
  a fresh per-actor copy nor the static pass's clipping policy. Native FP state is
  restored on normal and exceptional exits.

## Evidence and reproduction

The original `private/traversal-1006/dynamic/` receipts retain the `0b0bae6`
checkpoint. Current source identities use fresh `private/traversal-1006/dynamic-v2/`
expectations/report and sanitizer replay; see UNIT_VISIBILITY_1006.md for the source
identity refinement and timings. **2,811 audited roots**
include three scale initializers. All scenarios compare final visibility, final
shared rectangle, ordered visibility writes and service/virtual-call events.
Audits check callee-saved registers, ESP, return address, caller guards, permitted
original writes and configured actor/type/layer/tactical arenas including tails.
Services write only their declared stack results or supplied viewport mutations.

Coverage includes 960 flag/scenario/context/bypass/map/force combinations, 81
Terrain gate combinations, 48 world boundaries, 294 screen/height boundaries,
128 inverse-input float/wrap cases, 256 inverse-output truncation/wrap cases,
1,024 five-layer duplicate/shared-clip cases, an empty scan and 16 dense scans of
575 synthetic static Terrain actors plus one Unit. These are synthetic traversal
fixtures, not original map placement or completed moving-frame observations.

```sh
./build.command
./test.command
build/tools-env/bin/python tools/verify_dynamic_traversal.py \
  --exe private/official-1006-probe/game.exe
build/tools-env/bin/python tests/compare_dynamic_traversal.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/traversal-1006/dynamic-v2/expected.json \
  --report private/traversal-1006/dynamic-v2/NEW-NATIVE-REPLAY.json
# Add --native build/sanitize/dynamic-traversal-vectors for ASan/UBSan replay.
build/tools-env/bin/python tests/test_dynamic_traversal_evidence.py
# Fresh original execution requires the authorized Apple Silicon host JIT context:
build/tools-env/bin/python tests/compare_dynamic_traversal.py \
  --exe private/official-1006-probe/game.exe \
  --output private/traversal-1006/NEW-DYNAMIC-ORIGINAL
```

Fresh runs refuse existing original receipts. Replays execute no original code,
check exact source/inspection/engine/receipt identities and separately record the
native runner hash. Seven Python evidence guards and native CTest domain/FP guards
pass. Full Python discovery has **181 tests**. Normal/sanitizer CTest and the
patched owned-data presentation check pass. Research dependencies stay test-only.

## Delivery accounting and remaining work

Inherited committed work: promotion `9effefd`, bounds/eligibility `9194568` and
static pass `227b720`. Current fresh CLI took 4.050 s total: 3.302 s original,
0.280 s native. Normal replay used 0.273 s native; sanitizer replay 0.410 s native.
Python discovery took 0.400 s; normal/sanitizer CTest reported 0.04/0.33 s. Build,
owned-check and whole-continuation elapsed times were not separately instrumented
and are unavailable. No independent reviewer accepted this local checkpoint.

Failed attempts were bounded: the initializer write guard initially named
`0xABE558` rather than inspected `0xABE550`; a generated boolean token was refused
by the native integer parser; differential case zero exposed the third inverse
input's reused Y local. Guards/serialization/C++ were corrected and fresh execution
then passed; none of those attempts produced accepted receipts. No original bytes
were patched and no cache infrastructure was introduced.

Runtime traversal was deliberately not changed at this prerequisite boundary.
Actual SDL input/rendering was exercised at the inherited committed static-pass
delivery and has not been repeated for this unused kernel. The full crossing
delivery still requires nested Unit eligibility execution and relevant redraw scheduling,
stock field initialization/secondary getter verification, native integration and
a reproducible moving crossing with actual SDL input/rendering. Camera inversion,
UI/extras, alternate actors, dynamic invalidation/lifetime and whole-frame original
parity remain outside this evidence. Continue the same delivery and keep the
full-game/YR goal active.
