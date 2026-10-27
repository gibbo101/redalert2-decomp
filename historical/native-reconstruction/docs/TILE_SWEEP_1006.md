# Supplied RA2 1.006 tile usage and image sweep

Current evidence update: [LAND_CHARACTERISTICS_1006.md](LAND_CHARACTERISTICS_1006.md)
records new-target relinking and a changed map fixture-decoder identity. Fresh
`private/map-depth-1006/sweep-v3/` repeats all 129 results and both replays on that
decoder; commands/results equal v2. Older sets remain historical. This changes
no recovery kernel/runtime claim; checkpoint counts/times below retain their dates.

October 15, 2026, after `aac7e6e`. This joins the recovered Cell selector and
loaded-image children inside their complete usage/load parent. It is an unwired
prerequisite of the same terrain-aware Foot/world crossing and cliff capability;
it does not change the playable prototype or complete original map preparation.

## Identity and references

Executed engine: `private/official-1006-probe/game.exe`, 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Both this file and `private/windows-baseline-20261014/game.exe` were rehashed and
still match. Embedded 1.08, supplied 1.006 lineage and reported no-CD modifications
remain separate provenance; pristine authenticity is unverified. No new transfer,
Windows action, mounted-media requirement or executable modification occurred.

Consulted [REFERENCES.md](REFERENCES.md), pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` `docs/voxels.md`/LICENSE and YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` `IsometricTileTypeClass.h` and
`MapClass.h`, including CellIteratorReset/Next declarations. Hypothesis: the actual
map iterator and tile parent control usage, variant reduction and image lifetime
before Cell preparation. Recomp supplies no verified base algorithm; YR names/
layouts are leads only. Exact base inspection/execution establishes the mapping.
Recomp's authored-code license excludes generated game code; YRpp has no license
file in the pinned snapshot. No upstream/header/generated/lifted code or extracted
table was incorporated in native source; existing THIRD_PARTY boundaries suffice.

## Executed boundary

Eleven complete ranges / **926 instructions** execute unchanged:

| Original root | Scope |
| --- | --- |
| `0x52B2E0` | Complete usage/variant/count/load/release parent |
| `0x55A550`, `0x55A490` | Actual map iterator reset and advance |
| `0x4767A0`, `0x638840` | Actual Cell selector and XOR generator step |
| `0x5293D0`, `0x52B560` | Actual GetImage and lazy TMP loading |
| `0x52E3D0`, `0x63CC80`, `0x63CDF0`, `0x77F110` | Actual color builder, interpolation, scale and FTOL |

[TileSweep.cpp](../src/assets/TileSweep.cpp) supplies readable C++ in the assets
layer. Stable Cell/primary/type chains, pointer-table construction, original
pattern/direction tables, initial RNG/cache state, successful file/heap/vector
services, a fixed-zero clock and diagnostic logging remain supplied. Initial
prepared colors execute the original color builder before the parent. This does
not establish original construction, allocation/ownership/lifetime, archive/file
I/O, timer/message-pump behavior or RMG gameplay. The separate usage reset
`0x52B650` is inspected but is not executed or implemented by this checkpoint.

## Preserved behavior

A nonzero low force byte skips usage traversal and preserves the incoming iterator
and usage values. The parent never clears usage itself. Otherwise reset to
`x=1, y=width, remaining=width-1, slot=width*512+1`. Advance returns the old pointer
entry after changing the cursor, including the terminal null. Within a diagonal,
increment X, decrement Y/remaining and subtract 511 slots. At its end swap X/Y,
use `(oldY-width+oldX-1)&1` to select the next diagonal and set remaining to
width-1 or width-2. Traversal stops at the first null, not a host rectangle bound.

Tile 65535 or signed tile >= primary count falls back to ClearTile. Native negative
indices are refused rather than reproducing out-of-bounds pointer access. A valid
type with remaining count <=1 bypasses both GetImage and the selector. A fallback
always invokes the selector, even at count one. For a valid multi-variant type,
GetImage may load immediately. A present selected subheader's raw flags `&4`
forces variant `(CellFlags>>13)&1`; null images/subheaders or clear bit 2 invoke
the actual selector, including first-use RNG/cache initialization. Preserve the
selector's signed-word coordinate behavior and complete RNG/cache consumption
from [TILE_VARIANTS_1006.md](TILE_VARIANTS_1006.md).

Reduce the raw result by signed remainder only when it exceeds remaining count-1.
Follow that many next links and increment the selected type's uint32 usage with
wrap. Do not always reduce, reinitialize usage or substitute a coordinate hash.

The second pass visits primary entries in supplied order, skips null primaries
and follows every alternate chain. Only nonzero lazy byte plus a nonempty filename
enters image handling. Keep/load when forced, usage is nonzero, or keep-RMG and
RequiredForRMG are both nonzero. Otherwise free a nonnull image regardless of its
ownership byte, then clear image/ownership. Dimensions and color ramps survive
release. Native storage uses owned local byte buffers and normalized offsets;
this is not original heap ownership recovery.

Reporting includes only loads in the second pass. Earlier usage-pass loads are
excluded even though their image/color state persists. Byte totals wrap uint32;
reported KiB interprets the wrapped total as signed and divides toward zero.
The wrapped summary is recovered by inspection and implemented directly; these
bounded small-file fixtures do not exercise a multi-gigabyte summary overflow.

Native width 2..255, consistent cursor/table geometry, positive selected variant
counts, present image dimensions, finite next chains and valid supplied references
are safety boundaries. Refusals are not original malformed-input behavior. The
normalization child retains its prior stricter present-dimension domain. No table
or executable-read runtime boundary was broadened.

## Evidence and commands

**129 fresh original/native results**, plus normal and ASan/UBSan replays:
128 synthetic parent cases cover cold/warm cache and active/disabled RNG, counts
1/2/3/5, subheader flag forcing, count reduction, noncanonical byte values, usage
wrap, early null, null primary, lazy/nonlazy images, stale colors, release and
force/RMG retention. One owned fixture uses all **13,515 native-decoded map
records**, **838 supplied primary types**, and three resident clear/cliff/slope
TMPs. Other images are deliberately absent/nonlazy/count-one; this is not a full
loaded-theater/map-construction proof. Original traversal reaches every record
and the terminal null; every usage store is compared in order.

Compare complete selected type/image/color state, full RNG/cache state and call
consumption, final normalized cursor, ordered visits/usage/releases/file requests,
load count and bytes. Counts: 573 audited callable roots (including initial color
preparation), 129 actual parents, 56 resets, 14,463 iterator entries, 2,331 selectors,
36,864 generator entries, 1,593 GetImage entries and 302 lazy loads. The run
audits 1,052,135 guest stores and 7,412 supplied service calls. Nested
preparation/color instruction entries are retained in the receipt. Caller return/
ESP/stack/registers, immutable cell/table/registry/global inputs, bounded type
writes, heap references/bytes, allocation tails and vector capacity tails pass.
No original instruction was patched. Full memory access/write order is unclaimed.

Current evidence: `private/map-depth-1006/sweep-v2/expected.json`, `report.json`,
`native-replay.json`, `sanitize-replay.json`. Source, engine, inspection, decoder,
map, INI and TMP identities are checked. v1 is historical after a readability-only
source edit; v2 is fresh execution, not relabeling, and its commands/results equal
v1. Eight Python receipt guards and a native domain guard target are included.

```sh
./build.command
build/tools-env/bin/ctest --test-dir build/native --output-on-failure
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
# Build sanitizer targets using README's headless sanitizer configuration.
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

# Fresh original execution requires the authorized Mac host JIT context.
# Choose a new, unused private destination.
build/tools-env/bin/python tests/compare_tile_sweep.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/sweep-new

# Replays do not execute original instructions.
build/tools-env/bin/python tests/compare_tile_sweep.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/sweep-v2/expected.json \
  --report private/map-depth-1006/sweep-v2/replay-new.json
# Add --native build/sanitize/tile-sweep-vectors for sanitizer replay.

# Existing playable scenario (unchanged by this checkpoint):
./run.command --crossing-light-demo
# Select Rhino; G/right-click moves, L toggles light, R resets.
```

The same capability continues: broader map preparation at
`0x54B2E0/0x54FDA0/0x54EBD0`, remaining direction/speed inputs and construction/
unsupported-branch guards precede Cell-to-Foot/world depth integration. Keep
runtime neutral tile/flags/tube/cliff/contact fields until those associations are
verified. Require actual SDL level crossing and parked cliff `(51,72)`, elevation
4, at runtime integration. No new SDL playtest is claimed for this unwired helper.
RNG seeding/global lifetime, actor/map/contact/heap/cache lifetime, pathfinding,
scheduling/camera/fog/UI and whole-frame parity remain open. Only Apple Silicon
macOS is tested. Locally verified checkpoint; independent acceptance and full base
RA2 then YR completion remain outstanding.
