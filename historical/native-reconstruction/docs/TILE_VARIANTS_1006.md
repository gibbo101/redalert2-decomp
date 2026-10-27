# Supplied RA2 1.006 Cell variant selection and RNG step

The later [inclusive range recovery](RANDOM_RANGE_1006.md) adds signed range and
rejection behavior over this same raw generator. Seeding/scenario association and
Unit Scatter remain open. The checkpoint below retains its original raw-step scope.

October 15, 2026, after `039bedf`. This is an unwired prerequisite of the same
terrain-aware Foot/world crossing and cliff capability. It follows
[loaded theater bindings](THEATER_TILE_FILES_1006.md); it does not yet execute
their parent usage/load sweep or initialize the complete runtime map.

## Identity and references

Executed engine: `private/official-1006-probe/game.exe`, 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Every fresh/replay driver checks that identity. Embedded 1.08, supplied 1.006
lineage and reported no-CD modifications are separate provenance facts; pristine
authenticity remains unverified. No new Windows action/transfer was needed.

Consulted [REFERENCES.md](REFERENCES.md), pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` `docs/voxels.md`/LICENSE and YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` `CellClass.h` and `Randomizer.h`.
Hypothesis: original Cell variation uses persistent first-use state and a shared
generator, so replacing it with a host coordinate hash would change both choices
and generator consumption. Recomp supplies no verified base selector algorithm;
YR names/state layout are leads. Exact base instructions/execution establish the
mapping and behavior; no YR address is inferred for base RA2. No upstream/header/
generated/lifted code was incorporated; no new THIRD_PARTY entry.

## Executed boundary

Three complete ranges / **165 instructions** execute unchanged:

| Original root | Scope |
| --- | --- |
| `0x4767A0` | Complete Cell variant selector, including first-use table |
| `0x638840` | Actual 250-word XOR generator step |
| `0x5293D0` | Actual resident/null, nonlazy GetImage child |

`sim/OriginalRandom.*` provides only the generator step on supplied state; it is
SDL-free. `assets/TileVariants.*` implements the selector with a supplied generator
callback, pattern/direction tables, initial cache state, signed-word coordinates,
sub-tile byte, remaining count and stable resident/null image header. No API
service substitutes for the nested generator or image getter. Seeding, original
global/scenario association/lifetime, lazy image loading, parent count reduction/
usage tracking and map/runtime association are not recovered by this boundary.

The small pattern at `0x7D2B90` and eight neighbor pairs at `0x7D2BD0` are read
from the exact private executable for fixture inputs and hash-checked by the
verifier. No extracted table is embedded in tracked native code. Future runtime
integration must prepare/identify these inputs privately, preserving the existing
runtime executable-read boundary; this helper does not broaden that boundary.

## Preserved behavior

The generator's nonzero first byte returns zero and leaves its state unchanged.
`disabled` is a descriptive native name, not a recovered source identifier.
Otherwise XOR table[next1] with table[next2], store at next1, return that full
uint32 value, advance both indices and reset each at 250. Native active indices
must be 0..249; invalid-state refusals are safety guards, not original error parity.
Seeding and other RNG methods remain open.

When the variant cache byte is zero, set it to one and fill 64 words with -1.
For each index in order, draw `next() & 7`; reject a candidate matching any of
the eight already-visible neighbor words, retrying up to **64 attempts per cell**.
Store the final candidate even when that retry bound is reached. Neighbor
addresses are linear `index + dy*8 + dx` with one +/-64 adjustment, not separate
two-dimensional wrapping. A nonzero cache byte, including 2/255, stays unchanged
and avoids all initialization draws. A disabled generator still consumes calls:
the tested cold all-zero return sequence invokes it **4,033 times**.

Initialization precedes both small-set decisions and later null-image returns.
With sub-tile zero, use the raw signed-word cell coordinates without querying an
image or normalizing them. With nonzero sub-tile, a null image returns zero after
initialization. For a stable present image the original calls GetImage three times;
the fixture executes those calls and compares complete output state. Subtract
sub%columns from X and sub/columns from Y with word wrapping, then divide the
signed wrapped words by columns/rows **toward zero** and store words again.
Supported present dimensions for this normalization are 1..255; native zero/
unsupported-dimension refusals are safety guards.

Signed remaining count <=4 selects the supplied 4x4 pattern by low two coordinate
bits; larger counts select the initialized 8x8 table by low three bits. Return
the raw pattern word; do not reduce it by remaining count here. The parent does
that separately. Exact callback consumption and full state matter, even when
the returned value is zero.

## Evidence and commands

**320 fresh original/native results**, normal and ASan/UBSan replays: 64 generator
sequences and 256 selector cases (64 cold / 192 warm). Include index ties/wrap,
full uint32 words, disabled bytes, small/large signed count boundaries, signed-word
coordinate edges, sub-tile wrap, zero-sub bypass, and resident/null headers. Compare
raw results, every RNG/cache state word and the exact generator call count.
Counts: 17,175 audited roots, 256 actual selectors, 150,049 actual generator entries
and 450 actual image getters. The complete state is compared by serialized-word
digests; this is not a claim for every memory access or write order.

Caller return/ESP/stack/registers, immutable actor/type/image/table inputs, generator
disabled/padding bytes and allowed state-write ranges are guarded. No original
instruction is patched. Receipts: `private/map-depth-1006/variant-v1/`
`expected.json`, `report.json`, `native-replay.json`, `sanitize-replay.json`.
Source/inspection/executable identity is checked before and after runs.

```sh
./build.command
build/tools-env/bin/ctest --test-dir build/native --output-on-failure
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'

# Fresh original execution requires the authorized Mac host JIT context.
# Choose an unused private output directory.
build/tools-env/bin/python tests/compare_tile_variants.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/variant-new

# Replays do not execute original instructions.
build/tools-env/bin/python tests/compare_tile_variants.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/variant-v1/expected.json \
  --report private/map-depth-1006/variant-v1/replay-new.json
# Add --native build/sanitize/tile-variant-vectors for sanitizer replay.
```

Continue actual parent usage/load sweep `0x52B2E0`, wider initialization
`0x54B2E0/0x54FDA0/0x54EBD0`, remaining direction/speed inputs and runtime branch
guards before joining prepared Cell fields to retained Foot depth/Unit/world
drawing. Require actual SDL level crossing and parked cliff `(51,72)`, elevation 4,
at capability integration. No runtime source changed and no new SDL test is
claimed for this unwired prerequisite. Map/actor/contact/heap/cache lifetime,
pathfinding, scheduling/camera/fog/UI and whole-frame parity remain open. Only
Apple Silicon macOS is tested. Locally verified is not independent acceptance;
full base RA2 then YR remains active/incomplete.
