# Supplied RA2 1.006 initial map geometry

October 15, 2026, after `0991d63`. This is a prerequisite of the same
terrain-aware Foot/world crossing and cliff capability. It does not wire map
fields into the renderer or establish complete original map preparation.

## Identity and references

Both supplied private engine copies were rehashed unchanged: 4,485,392 bytes,
SHA256 `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 lineage and reported no-CD modifications remain
separate provenance facts; pristine authenticity is unverified. The executable
is never run by the native application. No new Windows action or transfer.

Consulted [REFERENCES.md](REFERENCES.md)'s pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439`, `docs/voxels.md` and LICENSE,
and YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88`, `MapClass.h`
(CreateEmptyMap/SetVisibleRect and rectangle/buffer declarations). Hypothesis:
original Size/LocalSize initialization supplies the geometry consumed by the
previously verified map permission child. The recomp voxel note provides no
verified base map-creation algorithm; YR names are leads only. Exact base
instructions and execution decide the behavior. No reference/header/generated
or lifted game code was incorporated; no new THIRD_PARTY entry.

## Executed and inspected boundaries

`assets/MapGeometry.*` implements the selected initial creation, buffer numeric/
fill and complete empty-actor visible-rectangle arithmetic. The verifier pins
**eight complete ranges / 1,948 instructions**:

| Actual original root | Scope |
| --- | --- |
| `0x5484E0` | Complete CreateEmptyMap, empty 262144-entry table, reuse=1 |
| `0x5499C0` | Complete buffer initializer around supplied downstream services |
| `0x549AE0` | Complete SetVisibleRect, no actors |
| `0x41FDF0` | Actual rectangle intersection child |
| `0x47A450` | Actual packed Cell position setter |
| `0x470F10`, `0x40FF10`, `0x40FFD0` | Actual Cell/Abstract/null-scenario registration; selected Cell fields only |

Actual Map RTTI and vtable `0x7A593C` slots +0x70/+0x74 establish creation and
visible setters. Three additional complete ranges / 786 instructions are
**inspection only**: map INI caller `0x49CFD0`, LocalSize screen wrapper `0x630840`
and existing-cell reset `0x548490`. The reset traverses existing cells; it does
not create the geometry. The INI caller reads Size (default 1,1,50,50), resets,
then calls creation with reuse=1, level=0, rebuild=1. It later reads Level/Fill,
loads decoded records, performs `0x52B2E0`, reads LocalSize with full-map default,
and calls the screen wrapper. That wrapper calls SetVisibleRect before its
additional screen/radar work. Inspection does not establish execution of the
complete INI/decompression/theater/screen chain. In particular, `0x52B2E0` is
a tile selection/load sweep, not ordinary Cell recalculation.

Successful heap allocations and frees, graphics redraw, rectangle manager,
zone/light/preparation children `0x54B2E0/0x54FDA0/0x54EBD0`, vector clears,
`0x563D80` and `0x429A90` are explicit fixture services. They check callers,
receivers and arguments and return without broader effects. Those services must
not be interpreted as recovered map preparation. No original instruction is
patched. Original creation selects actual constructors/position setters and
optional actual buffer initialization, not replacements for those children.

## Preserved behavior

Creation copies Size then clears its x/y to zero. Both minimum cell bounds
are 1; both maxima are width+height-1. Diamond globals become width and
width+2*height. The creation traversal is Y-major, with y < 2*(width+height),
x < width+height+1, and four original inequalities:

```text
x+y > width
x-y < width
y-x < width
x+y <= width+2*height
```

Each selected constructor runs before its packed position store, pointer-table
link and level-byte store. Fallback construction follows preparation/redraw.
The native helper preserves the selected field-store sequence, including flags
&0xFF800000 and separate constructor-invalid coordinates. Cell allocation order,
selected final fields, pointer membership and selected-store hashes are compared.
Complete constructor fields, pointer-write/read ordering, heap ownership and
nonempty existing-table/reuse=0 behavior remain outside the projection.

Buffer capacity is the low 32 bits of (width+height+1)^2. Allocation requests
are wrapped capacity*4 and capacity*10. Only the first two bytes of each
four-byte record become 7 and 0; its other bytes retain supplied allocation
contents. The second buffer remains untouched at this boundary. Three subzone
capacities use the signed low-32-bit width*height*4 product divided toward zero
by 4, 16 and 64. Native numeric output preserves wrapping. Tested original
allocation sizes are bounded; malformed huge allocations/failures are not claimed.

Visible bounds intersect the requested rectangle with the full map using
original wrapped signed arithmetic. Then x/y become at least 2, width is capped
by full.width-x-2, and height by full.height-y-6. Negative final dimensions are
preserved. The assets-layer intersection is independent of render code, retaining
the assets/render dependency boundary. The resulting permission shape uses full
width and these four visible values; original permission consumption itself was
verified in [MAP_CELL_CHILDREN_1006.md](MAP_CELL_CHILDREN_1006.md).

Native creation accepts positive dimensions with width+height <=256, matching
the supported 512*512 table geometry. It requires an empty table and matching
caller-owned storage. Refusals for unsupported geometry, malformed buffer length,
forged positions, fallback aliasing and mismatched/nonempty storage are native
safety guards, not original malformed-input parity.

## Evidence and commands

**1,067 fresh original/native results**: 18 initial creation sequences, 24 buffer
sequences and 1,025 visible-rectangle cases. They include signed/wrapped edges,
level-byte boundaries, unnamed size-dependent global threshold 63/64, both buffer rebuild
choices, old buffer pointers and the supplied map's Size 0,0,80,85 / LocalSize
5,5,70,73. Actual creation produces **13,515 cells** for that map, matching the
separate original reader's record count. This does not prove the missing complete
map-load/loaded-image association. Normal and ASan/UBSan replay use the same
identity-checked expectations.

Current receipts: `private/map-depth-1006/geometry-v2/{expected,report}.json`,
`native-replay.json`, `sanitize-replay.json`. V1 completed successfully and remains
historical after the audit performance change; no evidence was relabeled.
The map, source and inspection identities are checked before/after runs. Caller
return/ESP/stack/registers, permitted image writes, immutable Map headers/globals,
unselected Map bytes, actual allocation bounds and cell/buffer capacity tails
are guarded. API allocation fills are supplied initialization, not guest writes.
Whole-frame fidelity and all read/write ordering are not claimed.

```sh
./build.command
build/tools-env/bin/ctest --test-dir build/native --output-on-failure
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'

# Fresh original execution requires the authorized Mac host JIT context.
# Choose a fresh unused private output directory.
build/tools-env/bin/python tests/compare_map_geometry.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/geometry-new

# These replays do not execute original x86 instructions.
build/tools-env/bin/python tests/compare_map_geometry.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/geometry-v2/expected.json \
  --report private/map-depth-1006/geometry-v2/replay-new.json
# Add --native build/sanitize/map-geometry-vectors for sanitizer replay.
```

Timing, final verification and remaining dependencies are recorded in the current
[handoff](HANDOFF.md). This locally verified checkpoint is not independent
acceptance or a completed map-depth capability. Runtime fields remain neutral;
no new SDL test is claimed for an unwired assets-only prerequisite. Loaded TMP/
type association, remaining directions/land-speed inputs and actual broader
initialization still precede Foot/world integration and actual SDL level crossing
and parked cliff `(51,72)`, elevation 4. Actor/contact/map/heap/cache lifetime,
pathfinding, scheduling/camera/fog/UI and whole-frame parity remain open. Only
Apple Silicon macOS is tested; full base RA2 then YR remains active and incomplete.
