# Ordinary Terrain occupation and cell membership — milestone 18

[TERRAIN_LIFECYCLE_1006.md](TERRAIN_LIFECYCLE_1006.md) adds independently mapped,
freshly executed disc/1.006 occupation and lifecycle profiles, protected receipts,
both sanitizer replays and scoped return-address/image-write audits. Its replay
paths supersede the historical paths below; runtime/data promotion remains pending.

[LIFECYCLE.md](LIFECYCLE.md) extends this checkpoint with ground Unlimbo/Limbo,
neighbor counters, projection and layer registration/removal. It supersedes direct
Mark preparation and the separate scenery sort below. Construction/storage,
global draw/update traversal, visibility, clearance and whole-frame parity stay open.

October 14, 2026. Ivalice / Apple Silicon macOS. Base RA2 first.

This milestone recovers ordinary static Terrain occupation, linked cell membership
and Object/Terrain Mark decisions. It prepares those states for the **565 supported
scenery placements**. It does not recover locomotor clearance, original pathfinding,
global actor scheduling or complete construction/Unlimbo/lifecycle. Conservative
route exclusions remain active. [PROPS.md](PROPS.md) still defines drawing scope.

## Identity and references

All addresses below belong to the user's Allied-disc GAME.EXE, embedded **1.08**,
image base `0x400000`, SHA-256:
`135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743`.
The runtime never executes original instructions and reads GAME.EXE **track data
only**. No new runtime executable tables or dependency were added.

Consulted [REFERENCES.md](REFERENCES.md) and pinned YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88`, `ObjectClass.h`,
`ObjectTypeClass.h`, `TerrainTypeClass.h` and `CellClass.h`. Names and offsets
supplied the hypothesis that static terrain shares Object marking and a cell list,
with separate temperate/snow masks. All implemented operations were independently
located in this base executable. No YR address or behavior was imported. That
snapshot has no incorporation license; no header code was incorporated.
The pinned recomp/tooling references supply no original occupation oracle.

| Original routine/data | Exact base address | Tested boundary |
| --- | --- | --- |
| Terrain vtable | `0x79827C` | Occupation, foundation and Mark dispatch |
| Terrain mark/unmark occupation | `0x6D8A60` / `0x6D89C0` | Complete routines, ordered byte stores |
| Terrain Mark / Object Mark | `0x6D8950` / `0x5CC6A0` | Complete ordinary no-attached-animation decisions |
| Object redraw / word-cell getter | `0x5CBC20` / `0x41B320` | Complete routines, queue boundary and coordinate conversion |
| Map insert/remove | `0x547EB0` / `0x5482B0` | Complete ordinary ground-relative-zero, 1x1 path |
| Cell insert/remove | `0x473730` / `0x473920` | Complete Terrain linked-list and occupation operations |
| Object foundation / TerrainType getter | `0x5CC9B0` / `0x6DA740` | Actual foundation dispatch and copying |
| Foundation initializer | `0x6D9ED0` | Actual startup initialization |
| Foundation name getter/table | `0x469E80` / `0x7BC950` | Inspected name-to-index mapping; metadata asserted |
| TerrainType vtable | `0x798490` | Actual type/foundation/height getters |

## Recovered operations

`TerrainOccupation.cpp` belongs to the SDL-free simulation library. Logical member
IDs and `std::map` storage replace original pointers/map storage as a host boundary;
they preserve the tested state transitions and event order.

Coordinates divide signed 32-bit X/Y by **256 toward zero**, then truncate to signed
16-bit cell coordinates. Z does not affect occupation-mask selection. Scenario
theater `+0x838 == 1` alone selects type snow mask `+0x27C`; every other value
selects temperate `+0x278`. Both masks initialize to **7**, as inspected in the
original type constructor. The type INI loader reads `TemperateOccupationBits` and
`SnowOccupationBits`; native INI parsing/storage remains a host boundary.

Both occupation routines perform the map lookup **even with mask zero**. Low mask
bits **1, 2, 4** select Cell `+0x124` low-byte bits **4, 8, 16**, in that order.
Mark ORs each selected bit; unmark clears it. Each selected bit produces a byte
store even when the value already matches. High mask bits are ignored; high flag
bytes remain unchanged. There are **no reference counts**: removing one overlapping
actor clears its selected bits even if another actor remains.

Ordinary Terrain reports type ID **0x24**. Insertion prepends to the ground head
`Cell +0xE4`, or alternate head `+0xE8`, except when a nonnull head's **NextObject
equals the inserted actor**. This unusual guard is retained; it is not a general
duplicate search. Raw insertion of the current head can create a self-link. The
native prepared path uses valid absent members, and native traversal refuses
cyclic lists outside that profile. Removal handles head/middle/tail, clears the
removed actor's Next only when found, and unmarks occupation **even when absent**.
Visible-cell service occurs before occupation during insertion.

Object state bytes are onMap `+0x74`, needsRedraw `+0x75`, limbo `+0x76`:

- Nonzero limbo rejects every tested mode without changing those fields.
- Modes **1/3** accept only off-map actors, store onMap=1 and request redraw.
- Mode **0** accepts only on-map actors and stores onMap=0.
- Mode **2** accepts only on-map actors whose needsRedraw is zero.
- Other modes reject in the ordinary no-attached-animation profile.

Redraw stores needsRedraw=1 and calls map redraw service with zero only when the
existing byte is zero. Noncanonical nonzero bytes remain unchanged. Accepted
Terrain Mark always obtains cell coordinates; modes 1/3 insert and mode 0 removes,
then request cell redraw. Mode 2 has neither membership operation.

The original foundation initializer produces `(0,0), (32767,32767)` for its first
row at `0xAA7F18`. The name table maps **1x1 to index 0**; the type loader uses a
40-byte stride. This mapping is inspected original evidence, and initialization,
metadata and actual foundation dispatch are exercised in the oracle. Complete
INI/foundation loading and pointer ownership are not claimed: the test supplies
the valid 1x1 pointer, and runtime retains the existing Foundation=1x1 guard.

## Differential evidence

```sh
./build.command
build/tools-env/bin/python tests/compare_occupation.py \
  --exe private/disc-allied/game.exe \
  --expectations private/migration/allied-disc/occupation/expected.json
# Headless ASan/UBSan build is in README:
build/tools-env/bin/python tests/compare_occupation.py \
  --exe private/disc-allied/game.exe --native build/sanitize/occupation-vectors \
  --expectations private/migration/allied-disc/occupation/expected.json \
  --report private/migration/allied-disc/occupation/sanitize-replay-report.json
```

**13,472 original/native results pass**:

| Cases | Boundary |
| ---: | --- |
| 8,192 | Every low mask 0..7 and initial flag byte 0..255, mark/unmark, snow/temperate paths and preserved high flag bytes |
| 722 | Signed division boundaries, int32 extrema and signed-word wrapping |
| 512 | Seeded high masks, coordinates, flags and other theater values |
| 1,536 | Complete raw Cell insertion/removal, finite multi-member lists, duplicate guard, absent member and alternate heads |
| 576 | Complete Object/Terrain Mark modes, canonical/noncanonical state bytes, limbo and redraw guards |
| 192 | Complete Mark through Map/list insertion/removal, overlap and missing members |
| 612 | All 51 supported supplied stock type-mask inputs, three theater values and four accepted modes |
| 1,130 | Every one of 565 selected map placements inserted and removed |

Tests compare **final member/head/flag states and ordered actor, head, byte-store,
lookup, visibility and redraw events**. Hooks audit permitted write address/size;
full actor/type/scenario/cell/map-table arenas remain unchanged outside allowed
fields. Caller-owned stack canaries, final ESP and callee-saved EBX/ESI/EDI/EBP are
asserted. Actual original instructions execute unchanged; no instruction patches.
Reports pin executable, oracle/test sources, owned rules/art/map and native runner;
replay also pins cached expectations. Seed is `0x52413138`.

`original_occupation.py` supplies services at the following boundaries:

- Map lookup `0x5453B0` records packed signed-word coordinates and returns the fixture cell.
- Attached-animation query `0x40DC20` returns none.
- Flat cell height `0x4702C0` returns zero; world ground height `0x556F20` returns actor Z. Ground/bridge byte is zero. Positive height threshold global `0xA5AA88=104` is supplied, not newly recovered.
- Visibility `0x564DE0` returns visible and records its arguments; global `0xA255A8=0` suppresses visibility side effects.
- Cell redraw `0x472140` and map redraw queue `0x4DFEE0` record arguments/events. Actual Object redraw executes.
- Cold foundation cleanup registration `0x76DF1A` succeeds as cdecl CRT atexit.

Actual Terrain/Object/Map/Cell routines, word coordinates, layer/height predicates,
type getters, foundation dispatch/copy and startup initializer execute. The test
does not replace these with native formulas. Supplied services bound the claim;
screen/redraw effects and original global scheduling remain unverified.

Private evidence: `private/occupation/` contains research/disassembly, owned exports
and expectations. Reports are `private/occupation-report.json` and
`private/occupation-sanitize-report.json`. None is tracked or shipped.

## Runtime integration and remaining boundaries

`GameAssets` prepares map-cell storage and 565 healthy scenery member states using
the guarded stock type masks, cell-center coordinates and elevation ×104. Recovered
Mark mode 1 then populates heads, flags and dirty state. `ra2-inspect` reports member
and marked-cell counts. Owned-data tests remove/restore every member, check duplicate
Mark rejection and retain conservative route exclusions. These checks prove native
integration only. They do not establish original constructor/Unlimbo, occupation
ordering across map loading, dynamic actors or locomotive permission to enter cells.

Rendering still uses its immutable static-layer adapter. No scenery destruction or
editor control is exposed. Global render/update ordering, original redraw queue and
invalidation, off-map/bridge/alternate-height actors, visibility, lifecycle and
full-frame parity remain open. No new Windows/Linux support is claimed.

For a future original-game integration observation on mike-gaming, use this exact
installation/build and a private map with two healthy ordinary Terrain actors in
one cell. At debugger breakpoints on `0x473730`/`0x473920` and `0x6D8A60`/`0x6D89C0`,
record actor identity/Next, selected ground/alternate head and Cell +0x124 before and
after each operation; log ordered writes and visibility/redraw calls. Separately
record Drive's clearance result for neighboring cells before and after removal.
This connects the recovered membership to actual map-load/removal and locomotor
integration. A screenshot cannot establish either. Windows remains unavailable;
no such observation is claimed here.
