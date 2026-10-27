# Supplied RA2 1.006 decoded overlay map loading

October 15, 2026, after `43e3655`. This prerequisite continues the same
terrain-aware Foot/world crossing and parked `(51,72)`, elevation 4 capability.
The complete reader now associates supplied decoded bytes with registry slots
and Cells. Temporary Overlay construction/placement effects remain supplied;
the helper is unwired. This is a locally verified checkpoint, not a completed
playable milestone or independent acceptance. Full base RA2 then YR is incomplete.

## Identity and references

Both private supplied engines freshly rehash to 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 lineage and reported no-CD changes remain separate
provenance; pristine authenticity is unverified. The approved Windows transfer
was already complete. No new transfer, Windows/source-install/system action,
worker, external code or dependency is part of this checkpoint.

Consulted [REFERENCES.md](REFERENCES.md), pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` `docs/voxels.md`/LICENSE and YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` `OverlayClass.h`,
`OverlayTypeClass.h`, `CellClass.h` and `MapClass.h`. Hypothesis: raw map bytes
select registry slots directly, while loader order and special data restoration
precede Cell recalculation. Exact base execution verifies the bounded reader
below. YR declarations remain leads, recomp is not an oracle and no upstream,
header, generated or lifted code was incorporated. Existing format notices in
[THIRD_PARTY.md](../THIRD_PARTY.md) remain applicable.

## Executed boundary

[MapOverlayLoading.cpp](../src/assets/MapOverlayLoading.cpp) implements the
complete parent around explicit decoded-stream, section, storage, heap and
temporary-constructor services. The full-map permission is distinct from the
visible/elevation permission used by other Cell helpers.

| Complete original range | Executed boundary |
| --- | --- |
| `0x5DB670..0x5DBA27` | Complete map overlay reader |
| `0x54AAB0..0x54AAF5` | Full-map signed-word diamond permission |
| `0x548070..0x5480A8` | Cell lookup/fallback position store |
| `0x49F430..0x49F450` | Buffer dimensions constructor |
| `0x4113B0..0x4113B4` | Buffer bytes per pixel |
| `0x4113C0..0x4113CE` | Buffer pitch through actual width getter |
| `0x4112C0..0x4112C4` | Buffer width |
| `0x5DD150..0x5DD25F` | Image getter in resident/no-demand domain |
| `0x6ECF10..0x6ED02C` | Transient cleanup with empty collection |

All nine complete ranges / **491 inspected instructions** are entered. Actual
buffer slots +0x70/+0x74/+0x7C and OverlayType +0x9C are identity-checked.
No original instructions are changed. Complete temporary Overlay constructor
`0x5DA7D0..0x5DA8CF`, 67 instructions, is **inspection only** here. It calls
Object construction, identity, transient registration, centered Cell-to-world
conversion and Object Unlimbo `0x5D3890`; those placement effects are not proof
from this reader.

Preserve these decisions:

- Version <=1 skips both sections but still calls cleanup. Section results <=0
  skip that pass. Compressed input capacities are **512000** and **256000**;
  each decoded pass visits **512 by 512**, Y-major.
- Types precede data. Missing type bytes and byte 255 skip. Every other byte
  directly selects that registry slot; numeric INI keys are not used.
- Query the image before testing CellAnim, crate filtering or permission. A
  missing image and animation skips. Nonzero filter and crate byte skips.
- Full-map permission requires `x+y > width`, `x-y < width`, `y-x < width`,
  `x+y <= low32(width+2*height)` with signed comparisons and signed-word
  coordinates. This is not a screen/visible-rectangle test.
- Look up Cell and save OverlayData before allocation of 0x9C. Successful
  allocation calls temporary construction with type, Cell position and **-1**.
  Indices **0x18, 0x19, 0xED, 0xEE** look up Cell again and restore saved data,
  including after failed allocation.
- Each data read starts with zero. Write every permitted Cell even if no overlay
  was created; short reads therefore write zero. Finish with transient cleanup.

Native missing-service/invalid-index/lazy-image refusals are safety boundaries.
Lazy image loading, nonempty transient cleanup, original LCW/INI parsing, base/type
startup, original heap/ownership/lifetime and complete Overlay construction and
placement remain outside this proof. Selected native records are projections.

## Evidence and fixture reproduction

`private/map-depth-1006/overlay-loading-v1/` contains **1,111 fresh original/native
results**, followed by normal and ASan/UBSan replays: 1,024 seeded geometry cases,
72 focused boundaries and 15 complete reader scenarios. These cover old versions,
nonpositive sections, all byte indices, image/animation/crate gates, allocation
failure, EOF defaults, types-absent/data-present, no permitted positions, all four
restoration indices and the owned map. Counts:

- 1,111 audited outer calls, 15 parent entries;
- 1,051,189 permission, 55,408 lookup and 1,951 image-getter entries;
- 12 buffer constructors, 37 entries per getter, 15 cleanup entries;
- 95,277 ordered selected guest stores and 3,410,414 supplied service calls.

Compare complete selected Cells/fallback, stream cursors, allocation attempts and
ordered request/store digests. Caller stack/register/return address, declared
service arguments, immutable type/table/geometry/key/scratch/global inputs and
nonselected record bytes are guarded. No complete read-order claim follows.

[prepare_overlay_loading_fixture.py](../tools/prepare_overlay_loading_fixture.py)
reads manifest-hash-checked owned map/rules slices. Its bounded Format80 adapter
follows our existing host GameAssets reader; it is not original decompression
evidence. It requires a new ignored private output separate from inputs, rejects
path/symlink escapes and never changes source files. The resulting two streams
each have 262144 bytes: **660 active overlays**, **600 nonzero data bytes**,
**243 types** and **13,515 Cells**. A separate native IsoMap decoder check confirms
the Cell set. All type images are explicitly supplied resident; crate flags and
registry enumeration are host-decoded. The constructor service deliberately
writes index and `(index*13+seed)&255` to expose restoration/order; these are
fixture effects, not recovered placement. The tracked tool reproduces the prior
fixture byte for byte. Receipts retain the original fixture identity.

Both builds, **525 Python tests**, **31 normal / 30 sanitizer CTests**, source,
diff and local-link audits pass. **36 current evidence sets / 772 source entries**
include the unchanged prior 34 sets and decoder identity. Actual rebuilt SDL
baseline passes selection/right-click, 79 samples/78 updates, lighted crossing,
culling/clipping/cache bypass/pan return; the captured occluded frame was inspected.
This is existing native integration evidence, not new overlay/depth integration
or original-frame parity. Only Apple Silicon macOS is tested.

Fresh driver/original/native 106.843/106.119/0.140 s; CLI 107.007 s. Normal/
sanitizer replay CLI 0.743/10.054 s. Initial normal/sanitizer builds 17.930/7.874 s;
guard-target rebuilds 5.770/4.796 s. Final test.command 1.177 s, sanitizer CTest
2.122 s, full Python suite 0.339 s measured by unittest, SDL 4.291 s. A small
earlier original/native probe passed in 9.883 s. Preparation safety tests first
failed three assertions and one setup path check due to macOS `/var` versus
`/private/var`; resolving the test root fixed them. No original/native mismatch
or gameplay repair occurred. Private timing/coverage records retain intermediate
runs. Full active-delivery and initial continuation elapsed remain unavailable.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

# First prepare manifest-backed slices with tools/prepare_resident_map_fixture.py
# as documented in RESIDENT_MAP_1006.md, then choose unused private outputs.
build/tools-env/bin/python tools/prepare_overlay_loading_fixture.py \
  --fixture-dir private/map-depth-1006/resident-fixture-v1 \
  --output private/map-depth-1006/overlay-reader-owned-new.json
# Fresh original execution requires the authorized host JIT context.
build/tools-env/bin/python tests/compare_map_overlay_loading.py \
  --exe private/official-1006-probe/game.exe \
  --fixture private/map-depth-1006/overlay-reader-owned-new.json \
  --output private/map-depth-1006/overlay-loading-new
build/tools-env/bin/python tests/compare_map_overlay_loading.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/overlay-loading-v1/expected.json \
  --report private/map-depth-1006/overlay-loading-v1/replay-new.json
# Add --native build/sanitize/map-overlay-loading-vectors for sanitizer replay.

./run.command --crossing-light-demo
# Select Rhino; G/right-click moves, L toggles light, R resets.
```

Next recover actual temporary Overlay construction/Object Unlimbo/Cell placement
effects and overlay-bearing map resource/wall-owner effects. Then verify prepared
Cell/TMP inputs through actual Foot/base-depth branches and wire Unit/world
drawing. Require actual SDL level crossing and parked cliff before capability
completion. Runtime map-depth fields stay neutral; base parsing/defaults, actor/
contact/cache/heap lifetime, scheduling/camera/fog/UI/pathfinding and whole-frame
parity remain open.
