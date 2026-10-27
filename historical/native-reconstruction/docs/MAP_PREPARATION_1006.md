# Supplied RA2 1.006 ordinary map cell preparation

Current evidence update: [LAND_CHARACTERISTICS_1006.md](LAND_CHARACTERISTICS_1006.md)
records new-target relinking and a changed map fixture-decoder identity. Fresh
`private/map-depth-1006/map-preparation-v2/` repeats all 65 results and both replays
on that decoder; commands/results equal v1. Older receipts remain historical.
No recovery kernel/runtime claim changes; checkpoint counts/times below retain
their original dates.

October 15, 2026, after `6e4210c`. This recovers the ordinary two-pass map
cell-preparation parent, nesting actual Cell recalculation and lighting over
evolving shared state. It is an unwired prerequisite of the same terrain-aware
Foot/world crossing and cliff capability. The playable prototype is unchanged.

## Identity and reference hypothesis

Both local supplied engines were rehashed: `private/official-1006-probe/game.exe`
and the approved private Windows copy `private/windows-baseline-20261014/game.exe`
are 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 lineage and reported no-CD modifications remain
separate provenance; pristine authenticity is unverified. No new transfer or
Windows action occurred. The native app never executes this binary.

Consulted [REFERENCES.md](REFERENCES.md), pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` `docs/voxels.md`/LICENSE and YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` `MapClass.h`, `CellClass.h` and
`IsometricTileTypeClass.h`. Hypothesis: complete map preparation has ordered
passes whose shared Cell changes cannot be inferred from isolated child results.
Exact base inspection and execution establish the bounded behavior below. Recomp
is no original-behavior oracle; YR names are leads. Its authored-code license does
not cover lifted game output, and the pinned YRpp snapshot has no license file.
No upstream/header/generated/lifted code or extracted table was incorporated;
no dependency or THIRD_PARTY notice was added.

## Executed boundary

`verify_map_preparation.py` pins **29 complete ranges / 3,050 instructions**,
including inherited input ranges. Twenty-four roots are entered in this suite;
the five inherited reader/constructor/remap roots have no entries here.

| Root | Executed scope |
| --- | --- |
| `0x54B2E0..0x54B555` | Complete parent, transient list empty, no tags/overlays |
| `0x55A490` | Actual iterator; the parent inlines both resets |
| `0x476BA0` | Actual resource child, overlay -1 early return zero |
| `0x472540` and inherited children | Complete ordinary Cell recalculation, LAT, empty passability, permission, lookup and resident/null TMP consumers |
| `0x4790F0`, `0x479440`, `0x5383C0`, `0x51FC50`, `0x51FC60`, `0x77F110` | Actual lighting installation, numeric calculation, normalization, getters and conversion |
| `0x529590` | Actual palette-disabled factory early-null branch |
| `0x491620` | Actual direction initializer; its eight packed words supply the fixtures |

[MapPreparation.cpp](../src/assets/MapPreparation.cpp) keeps the parent in the
assets layer. Lighting is a callback into the presentation layer; recalculation
is another explicit callback. The differential fixture binds those callbacks to
the recovered native children. Map/pointer-table/type/image/buffer construction,
land mapping, float32 speeds, LAT settings, scenario lighting and initial fields
remain supplied. The original transient list is empty; overlay/tag/wall/resource
and occupant branches, sources, palette allocation/converter association/lifetime,
bridge/zone construction and full startup are outside this profile. Original
instructions execute unchanged; no API service replaces a nested algorithm here.

## Preserved behavior and guards

Finish the first complete iterator pass before any lighting/recalculation. Every
visited Cell receives `flags &= 0xFFCFFFFF`. Reset, then visit again: clear Cell
`+0x30`, install lighting with original arguments `(0,65536,0,1000,1000,1000)`,
clear flag `0x20000`, call the resource child with zero, then recalculate with level
override **-1**. The original resource sum returns zero for this supported profile.
The native helper returns the final normalized iterator instead. Preserve the
terminal-null advance on both passes and stop at the first null.

Recalculation queries the evolving shared Cell state, including earlier LAT and
level stores. Retain the saved original type pointer across LAT changes, actual
permission/fallback effects, cliff query order and selected buffer store order
from [MAP_CELL_PREPARATION_1006.md](MAP_CELL_PREPARATION_1006.md). Lighting occurs
before recalculation, so its inputs use the incoming Cell level. Converter is
actually null with palette disabled; native fixture storage does not establish
original palette/cache ownership. All eight direction words come from executed
initialization, not an assumed PE file table: their destination is BSS.

Native missing callbacks, unsupported tags/overlays, invalid cell references and
iterator geometry are refused. Inherited child safety guards remain. These are
safety boundaries, not original malformed-input parity or evidence that a normal
owned map has no unsupported branches. Runtime neutral tile/flags/tube/cliff/contact
inputs remain in place until relevant construction/associations are established.

## Evidence and reproduction

**65 fresh original/native results** and normal/ASan/UBSan replays pass. Sixty-four
synthetic shared maps cover sequential LAT changes, cliff modes 0/1/2, null/present/
invalid TMPs, levels/flags/light settings/speeds and early-null holes. One fixture
uses all **13,515 native-decoded owned map records** and 838 supplied types with
**every image deliberately absent**. That case verifies full iteration/light/
buffer sequencing, not real loaded-map metadata fidelity. The three-case pilot
also passes after executing the actual direction initializer.

Compare every selected Cell/light field, both complete buffers, final iterator
and fallback position, ordered child/query/store events and visits. Counts: 66
audited roots (65 parents plus direction initialization), 29,970 iterator entries,
14,920 recalculation/resource/lighting/numeric/normalization/factory entries each,
568 LAT and 14,920 empty passability/permission entries, and 2,352,515 audited guest
stores. Caller stack/registers, immutable tables/geometry/registry/scenario inputs,
unmodeled Cell/fallback bytes and buffer capacity tails are checked. Events cover
selected stores and query/child order, not full memory access order. No full
construction, allocation/ownership, map startup or whole-frame parity follows.

Receipts: `private/map-depth-1006/map-preparation-v1/{expected,report}.json`,
`native-replay.json`, `sanitize-replay.json`. Engine, inspection, sources, render
data, map and native fixture decoder identities are checked before/after runs.
The decoder fingerprint is a fixture identity; native decompression is not an
original decoder oracle. Eight Python evidence guards and a native domain target
protect these boundaries.

```sh
./build.command
build/tools-env/bin/ctest --test-dir build/native --output-on-failure
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
# Sanitizer configuration is in README; then:
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

# Fresh original execution requires the authorized Mac host JIT context.
# Choose an unused private destination.
build/tools-env/bin/python tests/compare_map_preparation.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/map-preparation-new

# Replay executes native code only, against protected original expectations.
build/tools-env/bin/python tests/compare_map_preparation.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/map-preparation-v1/expected.json \
  --report private/map-depth-1006/map-preparation-v1/replay-new.json
# Add --native build/sanitize/map-preparation-vectors for sanitizer replay.

# Current playable scenario, unchanged by this helper:
./run.command --crossing-light-demo
# Select Rhino; G/right-click moves, L toggles light, R resets.
```

Both builds, **469 Python tests**, **27 normal / 26 sanitizer CTests**, source/
diff/local-link audits pass. All 22 prior source/runner sets retain their identities
(704 source entries, coalesced within each set); earlier receipts are retained,
not fresh original execution. No runtime change/new SDL playtest is claimed for
this unwired prerequisite. Actual SDL remains required at capability integration.
Only Apple Silicon macOS is tested; this is locally verified, not independently
accepted or a completed map-depth/game milestone.

Fresh driver/original/native: 10.036/8.450/0.156 s (CLI 10.123 s). Normal/sanitizer
replay CLI: 2.518/2.889 s, native 0.132/1.596 s. Initial/final normal build:
6.996/5.394 s; sanitizer build 8.228 s. CTest CLI normal/sanitizer: 1.547/2.422 s;
Python CLI 1.942 s (469 tests, 0.350 s). Prior identity retention: 1.468 s.
Some checks overlapped. Private map-init start, attempts, verification and closing
records preserve inherited work and unavailable full active-delivery measurement.
Pre-pilot corrections include verifier import setup, the BSS direction-table
assumption and fixture registry capacity. Pilot/full evidence have no native
mismatch. No workers, evidence cache, gameplay repairs, source-install/system/
Windows changes or new transfer occurred.

## Remaining initialization and capability acceptance

Separate inspection, not execution: buffer root `0x5499C0` calls this cell parent,
bridge preparation `0x54FDA0`, then zone preparation `0x54EBD0`. Loaded-map caller
`0x49CFD0` separately resets tile usage at `0x52B650`, later calls the tile sweep
and level scan `0x56A8A0`. Bridge records/zones, usage reset/seeding/global lifetime,
remaining speed/table inputs and relevant construction/unsupported-branch guards
remain dependencies. Do not infer their effects from this parent.

Then join prepared Cell fields to retained Foot predicates/depth and Unit/world
drawing, followed by actual SDL level crossing and parked cliff `(51,72)`, elevation
4. Map/actor/contact/heap/cache lifetime, original pathfinding, scheduling/camera/
fog/UI and whole-frame parity remain open. Full base RA2, then YR, remains active
and incomplete.
