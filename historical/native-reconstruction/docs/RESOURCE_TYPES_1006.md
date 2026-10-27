# Supplied RA2 1.006 resource type inputs

October 15, 2026, after `e486515`. Readable native resource construction, INI
orchestration and numeric-key list loading pass **1,261 fresh original/native
cases** and both replays. Helpers remain unwired; terrain-aware Foot/world
crossing and parked `(51,72)`, elevation 4, plus the full RA2/YR goal remain
incomplete. This is local verification, not independent acceptance.

## Identity and references

Both private engines were rehashed: 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 lineage and reported no-CD changes remain separate
provenance; pristine authenticity is unverified. No new Windows/transfer/source
install/bypass/driver/security/system action occurred.

Consulted [REFERENCES.md](REFERENCES.md), recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` `docs/voxels.md`/LICENSE and
YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88` `TiberiumClass.h`,
`OverlayTypeClass.h`, `CellClass.h`. Hypothesis: original defaults/list/Image
association must supply actual classifier ranges, frames and values. YR names
are leads; exact base execution decides. Recomp's MIT covers authored tools/docs,
not generated/lifted output; its stale The Movies license text remains noted.
No upstream/header/generated/lifted code or extracted table was incorporated;
no new dependency or THIRD_PARTY notice is needed.

## Recovered control flow

[ResourceTypeInputs.cpp](../src/assets/ResourceTypeInputs.cpp) separates selected
records from base type/parser/CRT/color/animation/vector/heap services.
Complete executed roots: constructor `0x6E89A0` (446 bytes, 109 instructions),
INI `0x6E8D30` (669 bytes, 184), list `0x6E8FF0` (170 bytes, 67): **360
instructions / three roots**. Base `0x410580`/`0x4107E0` add 211 inspection-only
instructions and remain supplied. INI/debris-clear virtual slots, comma delimiter
and six Image switch entries are checked against the pinned image.

Preserve ordered low/high word percentage-default stores of 0.1, selected logic
resets and supplied frame copies. `+0x104` and `+0x120` stay untouched. Primary
registry count becomes the index before append; count increments before slot.
Growth accepts only the low byte of the service result. Debris clear precedes
append to a deliberately unnamed secondary registry; its gameplay role is open.

INI stores Spread, SpreadPercentage, Growth, GrowthPercentage, Value, Power,
Color, then debris, then Image. Base false returns immediately. Debris uses comma
alone and any nonzero read length, including negative. Its vector/animation
helper effects remain supplied; calls, branches and ordering execute.

Image -1 preserves pointer/frame/image/slope counts. Image 2 selects overlay
slot 27 and 12 frames/images, retaining slopes. Images 3/4 select slots 127/147;
all other values select 102. These latter branches set eight slopes and 12
frames/images. Preserve wrapped uint32 Image+1 selection. `mapResourceInputs()`
uses the chosen overlay's **stored index**, not its registry slot.

The list parses the numeric key through a CRT service. A key below current count
selects an existing record without renaming; otherwise it constructs the read
value. Nonpositive string-read results skip the row. Child INI false is ignored;
list returns true even for nonpositive count. Native guards reject negative
existing indices, null allocation and unsafe storage/capacity instead of claiming
malformed-input parity.

## Boundaries and verification

The real-number service supplies a binary64 consumer-store result. The oracle
directly injects an extended x87 register value. Finite values, signed zeros,
subnormals, infinities and NaN payloads exercise this boundary. **Signaling-NaN
transfers are emulator diagnostics, not proof of original parser/CRT or physical
x87 exceptional conversion semantics.** First comparison failed at case 505:
native invented a quieting rule while injection plus Unicorn preserved bits.
The unsupported rule was removed; no broader hardware NaN claim follows.

The owned-list case executes all four supplied rules entries: Riparius, Cruentus,
Vinifera, Aboreus. Parsing, named-color results and animation handles are supplied.
Base defaults/INI, vector/heap ownership, parser startup, economy/growth/spread,
full lifetime and runtime association remain open. `mapResourceInputs()` has
native guard tests; shared overlay records are still diagnostic in the earlier
suite. This is not complete startup or whole-frame fidelity.

Fresh receipts: `private/map-depth-1006/resource-inputs-v2/`. Corpus: 384 constructor,
768 INI, ten successful Image edges, 96 lists, two nonpositive counts and one
owned four-entry list. **474 constructor / 974 INI / 99 list entries**, **24,438
selected guest stores / 17,558 supplied calls** compare in ordered digests.
Full selected object/registry state, capacity slots/tails, caller/return/registers,
instruction allowlist, immutable overlay/type/frame/global inputs, nonselected
object bytes and x87 stack balance pass. Full memory-read order is not claimed.

Both replays including ASan/UBSan pass. Closing unchanged-identity inventory:
**52 sets / 1,288 source entries**. Both builds, **581 Python tests**, **39 normal /
38 sanitizer CTests**, source/diff/local-link audits pass. Actual rebuilt moving-
light SDL crossing passes 79 samples/78 updates, brightness 1450..1512, selection/
right-click, occlusion/clipping/culling/cache bypass/pan/no trails; converted
occluded frame inspected. Existing integration only, not new helper/runtime or
original-frame proof. Only Apple Silicon macOS is tested.

Driver/original/native **15.023/14.599/0.059 s**, CLI 15.149 s; replays CLI
0.957/2.999 s. Final builds 6.611/8.136 s; Python CLI 2.704 s (unittest 0.698 s),
test.command 2.667 s, sanitizer CTest 4.910 s, SDL 2.670 s. Earlier inherited
builds/probes and failed 15.236 s comparison remain logged privately. Checks
overlap; full inherited/active-delivery elapsed is unavailable. Patch-context and
fixture-whitespace errors were caught before execution. Pillow was unavailable
for capture conversion; macOS sips succeeded. No gameplay repair/cache added.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
# Fresh execution needs the authorized Mac host JIT context and unused output.
build/tools-env/bin/python tests/compare_resource_type_inputs.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/resource-inputs-new
build/tools-env/bin/python tests/compare_resource_type_inputs.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/resource-inputs-v2/expected.json \
  --report private/map-depth-1006/resource-inputs-v2/replay-new.json
# Add --native build/sanitize/resource-type-input-vectors for sanitizer replay.
./run.command --crossing-light-demo
# Select Rhino; G/right-click moves, L toggles light, R resets.
```

Continue initialized resource records in shared reader/placement/classifier updates,
then complete Cell recalculation/LAT/passability/TMP and overlay-bearing map parent.
Verify prepared Cell/TMP-to-Foot/base-depth and Unit/world, then actual SDL crossing
and parked cliff before promoting runtime depth. Depth remains neutral; full
startup/actor/cache/heap lifetime, scheduling/pathfinding/frame parity remain open.
