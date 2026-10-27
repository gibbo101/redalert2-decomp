# Supplied RA2 1.006 loaded wall placement

October 15, 2026, after `54043af`. This continues the same terrain-aware
Foot/world crossing and parked `(51,72)`, elevation 4 capability. The native
placement projection now handles the complete ordinary **loaded wall Mark**
branch around explicit wall-update/Cell/lifetime services. It remains unwired;
wall constructor/Unlimbo and decoded-reader nesting are not part of this suite.
This is a locally verified prerequisite, not a completed playable milestone or
independent acceptance. Full base RA2 then YR remains incomplete.

## Identity, references and chosen map

Both supplied private engines retain SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`,
4,485,392 bytes. Embedded 1.08, supplied 1.006 lineage and reported no-CD changes
remain separate provenance; pristine authenticity is unverified. The approved
Windows transfer was already complete. No new Windows/transfer/source-install/
system action, worker, dependency or upstream code is part of this checkpoint.

Consulted [REFERENCES.md](REFERENCES.md), pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` `docs/voxels.md`/LICENSE and YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` `OverlayClass.h`,
`ObjectClass.h`, `CellClass.h` (`CanThisExistHere`, `GetNeighbourCell`, wall owner)
and earlier OverlayType/Map declarations. Hypothesis: loaded wall placement has
different write order and neighbor/owner effects from the ordinary nonwall path.
Exact base execution verifies the decisions below. YR declarations remain leads,
recomp is not an oracle and no upstream/header/generated/lifted code was copied.

Manifest-checked owned `mp03t4.map`/rules host decoding identifies **95 walls**:
45 CAFNCB, 23 CAFNCW and 27 CAKRMW. It also identifies 471 resource overlays,
36 rocks and 58 low-bridge pieces, totaling 660. These low-bridge indices are
83/85/86/214..217/227/229, with Road land in the host-decoded rules; they do not
select the special long-bridge construction ranges. This is input inventory,
not executed original initialization or a full low-bridge gameplay claim. The
shared reader/Cell join must still verify effects on those actual supplied inputs.

## Executed boundary

[OverlayPlacement.cpp](../src/assets/OverlayPlacement.cpp) adds
`markLoadedMapWall`, sharing the existing base Mark implementation. The Cell
projection now also carries supplied position, wall owner and neighbor counter.
It remains a portable selected record, not an original ABI. The ordinary nonwall
helper retains its existing guards and behavior.

| Complete actual range | Executed behavior |
| --- | --- |
| `0x5DA970`, 3,251 bytes | Complete Overlay Mark, ordinary loaded wall branch |
| `0x5D4160`, 206 bytes | Actual base Object Mark |
| `0x41B320`, 61 bytes | Signed coordinate division/word getter |
| `0x5D36E0`, 24 bytes | Actual redraw flag transition |
| `0x4718B0`, 1,116 bytes | Complete Cell permission, loaded-true path |
| `0x476AC0`, 86 bytes | Actual neighbor getter with word wrapping |
| `0x5DC2E0`, 6 bytes | Actual Overlay kind getter |

**Seven complete ranges / 1,359 inspected instructions** execute unchanged.
Complete wall-update parent `0x475960..0x475D56`, **310 instructions**, is
**inspection only**; its connection/redraw/recalculation effects remain a service.

Base Mark mutations occur before Overlay rejection, including modes 0/2 and
slope rejection. The first lookup uses actor coordinates divided by 256 toward
zero and truncated to words. Slope above four rejects except index 0xB2. With
nonzero loading, actual Cell permission `(1, null, null)` returns true immediately
before inspecting Cell contents. Native loading zero, missing/nonwall/animated/
land-9 types and early special indices are refused before mutation.

Wall placement stores **data zero before overlay index**, unlike ordinary
placement. Call wall update with byte one. If placement flag differs from -1,
store the supplied current-owner index after that service. Then visit directions
0..7 in their supplied order, recomputing from the **Cell position**, adding words
with wrapping and incrementing each returned Cell's byte +0x122 with wrapping.
Aliased/self neighbors are incremented repeatedly. Finally request current-Cell
recalculation with -1, clear actor onMap, set limbo and request retirement.
Wall-update service mutations are retained; placement does not rewrite index or
data afterward. Loading skips the alternate map-zone update calls.

## Evidence and remaining services

Current receipts: `private/map-depth-1006/overlay-wall-placement-v1/` with fresh
expected/report and normal/ASan/UBSan replays. **2,000 fresh original/native cases**:

- 288 base Mark gates and nonplacement mutations;
- 1,200 slope/index/update/owner/loading and final recalculation decisions;
- 512 signed coordinates, supplied directions, wrapping, aliases and byte overflow.

Counts: 2,000 audited outer/Overlay/base Mark entries, 1,718 word getter,
1,720 redraw, 1,058 permission, 8,464 neighbor and 1,775 kind entries;
**17,080 ordered selected guest stores**, **16,847 supplied service calls**.
Compare complete selected actor/nine-Cell state, lookup count and ordered
query/store/service digests. Caller stack/register/return address, immutable
type/global/direction records and nonselected actor/Cell bytes pass.

Lookup results/aliasing/directions, absence of attached animation, redraw queue,
wall-update effects, current owner/placement globals, final Cell recalculation
and retirement remain supplied. The wall-update fixture optionally changes data,
removes the overlay and sets a counter to 255 to expose parent write order; these
are diagnostic effects, not recovered wall connections. No original wall
connection/redraw/ownership lifecycle, constructor/reader nesting, map startup,
runtime integration or whole-frame parity follows.

The shared source/record change has **fresh** ordinary placement-v4 (1,180) and
object-lifetime-v3 (3,681) original comparisons and both replays. Commands/results/
labels equal the prior suites; old receipts remain historical and are never
relabeled. All other source/runner identities and the decoder remain current.
Coverage audit: **42 sets / 898 source entries**.

## Verification and reproduction

Both builds, **546 Python tests**, **34 normal / 33 sanitizer CTests**, source/
diff/local-link audits pass. Actual rebuilt SDL baseline passes selection/right-
click, 79 samples/78 updates, changing light, culling/clipping/cache bypass/pan
return and no trails. The captured occluded frame was inspected. This is existing
native baseline evidence, not new wall integration or original-frame fidelity.
Only Apple Silicon macOS is tested.

Fresh wall driver/original/native 2.092/1.481/0.072 s, CLI 2.267 s; normal/
sanitizer replay CLI 0.733/0.997 s. Fresh ordinary placement/lifetime CLI
0.955/15.034 s. Builds 9.612/10.748 s; Python CLI 2.172 s (unittest 0.405 s),
test.command 2.148 s, sanitizer CTest 3.789 s and SDL 2.527 s. Independent
checks/replays ran concurrently where possible. The initial oracle attempt
stopped on an omitted kind getter in its allowlist (1.604 s); adding the actual
inspected getter resolved it before evidence was saved. No original/native
mismatch, failed build/test or gameplay repair. Full active-delivery/initial
continuation elapsed unavailable; private logs retain all measured runs.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
# Fresh original execution needs the authorized host JIT context and unused output.
build/tools-env/bin/python tests/compare_overlay_wall_placement.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/overlay-wall-placement-new
build/tools-env/bin/python tests/compare_overlay_wall_placement.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/overlay-wall-placement-v1/expected.json \
  --report private/map-depth-1006/overlay-wall-placement-v1/replay-new.json
# Add --native build/sanitize/overlay-wall-placement-vectors for sanitizer replay.
# Earlier suites now use overlay-placement-v4 and overlay-object-lifetime-v3.
./run.command --crossing-light-demo
# Select Rhino; G/right-click moves, L toggles light, R resets.
```

Continue actual wall connection/update dependencies, wall constructor/Unlimbo
dispatch and shared decoded-reader/Cell/resource/recalculation state. Complete
overlay-bearing map resource/wall-owner effects, then prepared Cell/TMP-to-Foot/
base-depth and Unit/world integration. Require actual SDL level crossing and
parked cliff before capability completion. Runtime depth fields remain neutral.
Full parser/defaults/actor/contact/cache/heap lifetime, scheduling/camera/fog/UI/
pathfinding and whole-frame parity remain open; special long-bridge/vein gameplay
is deferred beyond the chosen map's required placement domain.
