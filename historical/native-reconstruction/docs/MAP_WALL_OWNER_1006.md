# Supplied RA2 1.006 wall ownership dependency

October 15, 2026, after `59e5b38`. This recovers the wall-owner child required by
the later two-pass map-preparation parent. The helper is **unwired**; the parent
join, prepared Cell-to-Foot/world depth, terrain-aware crossing and parked cliff
capability remain incomplete. Existing runtime depth stays neutral.

## Identity and references

Both supplied engines were freshly rehashed at the start of this turn:
`private/official-1006-probe/game.exe` and the approved private Windows copy
`private/windows-baseline-20261014/game.exe`, 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 lineage and reported no-CD changes remain separate
provenance. Pristine authenticity remains unverified. The approved copy already
existed; no new transfer or Windows action occurred. Runtime never executes it.

Consulted [REFERENCES.md](REFERENCES.md), pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` `docs/voxels.md`/LICENSE, and YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` `CellClass.h` SetWallOwner,
`AbstractClass.h` distance/owner/coordinate declarations and `HouseTypeClass.h`
WallOwner. Hypothesis: the later map parent assigns walls to nearby eligible
building owners, using actual coordinates and original numeric distance.
YR names are leads and recomp is no original-behavior oracle. Its authored-code
license excludes lifted output; the pinned YRpp snapshot has no license file.
No upstream/header/generated/lifted code or extracted table was incorporated;
no new dependency or THIRD_PARTY notice is needed.

## Executed boundary

[verify_map_wall_owner.py](../tools/verify_map_wall_owner.py) pins **ten complete
ranges / 266 instructions**, exact Building/Cell RTTI and actual virtual slots,
foundation-table and sqrt-table hashes. All ten roots enter the new suite.

| Base root | Scope |
| --- | --- |
| `0x4724A0..0x472532` | Complete Cell owner selection |
| `0x5D4C00..0x5D4CD4` | Complete distance root, restricted to nonnull Cell target |
| `0x47BA50` | Actual Cell coordinates, supplied terrain-height child |
| `0x444080` | Actual Building coordinates, actual foundation getters |
| `0x458930`, `0x458940` | Actual width/height table getters, height argument zero |
| `0x6C7420` | Actual Building house array-index getter |
| `0x47CF80` | Actual Cell kind 11 getter |
| `0x4BA410`, `0x77F110` | Actual table sqrt and qword truncation/low-dword return |

Actual dispatch: Building vtable `0x79CBBC` slots +0x38/+0x48; Cell vtable
`0x79DB04` slots +0x2C/+0x48. Neither is the Drive vtable. Base INI inspection
at `0x4F9793..0x4F97AB` associates the `WallOwner` key with house-type byte
`+0x1A7`; this is **inspection**, not executed house construction/INI evidence.
The selector obtains that byte through candidate +0x1B4, then house +0x34.
Owner indices come from that same house's +0x30.

[MapWallOwner.cpp](../src/assets/MapWallOwner.cpp) is a readable assets-layer
projection, independent of SDL and rendering. Distance accepts the recovered
table sqrt as a numeric service; the fixture binds the existing presentation
kernel. No new general engine or platform dependency is introduced.

## Preserved behavior

Absent overlay (-1) or a zero Wall byte returns without writing owner. A wall
initializes best distance to signed INT_MAX and selected owner to -1. Visit
buildings in registry order. Require active +0x7D, on-map +0x74 and the house
type's WallOwner byte, all **nonzero**, before distance. Only a strictly smaller
signed distance queries and replaces owner; ties keep the first. Store the
chosen owner, including -1 for an empty/ineligible registry, even if unchanged.
Native observers see the assigned owner before their callback.

For every distance, query Cell coordinates before Building coordinates. Cell
X/Y are signed words, multiplied by 256 with 128 added. Its Z comes from the
explicit terrain-height service. Building Y uses foundation height, then X uses
foundation width; adjust by dimension*128-128 with uint32 wrapping, preserving Z.
The fixture executes all 22 table positions, including the final zero-sized slot;
this does not establish a constructed stock type using that slot.

Subtract each coordinate with 32-bit wrapping, interpret signed, square in
53-bit FP, add X-square plus Y-square then Z-square, perform the original table
sqrt/float32 store, truncate to a signed qword and return its low dword. **84
actual numeric distances become negative** in the extreme-coordinate fixtures;
do not saturate them or use std::sqrt. **110 actual distances are zero.** The
test caller explicitly supplies x87 mode 0x0E7F (53-bit/toward-zero); the native
scope restores its host FP mode on success/exception. Original startup/caller FP
initialization and other incoming modes are not established here.

The target kind is Cell 11, so the distance root's building-target foundation
subtraction does not run. Null targets, that alternate branch, terrain height/
ramp calculation `0x4706C0`, original registry/type/house/Building construction,
owner lifetime and mutable service/registry behavior remain outside this profile.
The supplied Cell/actor/type/house storage is not original heap ownership.
Native invalid bindings, missing services and impossible sqrt outputs are safety
refusals, not original malformed-input behavior.

## Evidence and checks

`private/map-depth-1006/map-wall-owner-v2/` contains **637 fresh original/native
results** and normal/sanitizer replays. Earlier v1 remains historical; v2 adds
explicit binding/FP scope guards and measured numeric counters. Coverage:

- 3 early/empty paths, 48 separately labeled selector-only cases with a supplied
  distance child for INT_MIN/INT_MAX/tie/gate edges.
- 330 actual coordinate/foundation/distance cases covering all table positions,
  signed-word Cell positions, exact co-location and vertical distances.
- 256 randomized registry/wrapped-coordinate/noncanonical-byte profiles.

637 audited parent calls, 633 actual nested distance/Cell/Building/foundation/
kind/sqrt/FTOL entries each, 536 owner queries, 512 selected owner stores and
735 supplied height or diagnostic-distance calls. Compare returned owner and
ordered distance results/getter/service/store events. Original instructions are
unchanged; isolated height/diagnostic-distance services intercept calls explicitly.
Every block must be inside inspected code or a declared service. Caller return
address, stack beyond consumed arguments, callee-saved registers, immutable
candidate/type/house/registry/table data, nonselected Cell bytes and registry
capacity tail are checked. Only Cell owner may change outside stack scratch.
No full memory-read-order, original allocator or whole-frame claim follows.

Adding the assets object relinked earlier runners, including the map decoder.
Fresh decoder-bound **sweep-v4 (129), map-preparation-v7 (65), resident-map-v6
(51)** proofs retain identical commands/results/labels and both replays; older
receipts stay historical. Other eligible expectations are replayed against the
rebuilt normal/sanitizer runners. Closing inventory/timings are recorded below.

Closing [HANDOFF.md](HANDOFF.md) and private `wall-owner-coverage.json` inventory:
**60 sets / 1,748 source entries**, all source/runner/expectation and retained
decoder hashes current. All 58 earlier sets replay against rebuilt runners;
the two new replays pass. Both builds, **609 Python tests**, **43 normal / 42
sanitizer CTests**, source/diff/local-link checks pass. Local verification has
not received independent acceptance. Only Apple Silicon macOS is tested.

Actual rebuilt SDL moving-light crossing passes 79 samples / 78 updates,
brightness 1450..1512, selection/right-click, occlusion, clipping/culling, cache
bypass, pan and no trails. Summary and inspected occluded frame are identical to
the previous baseline. This checks existing native integration, not new wall
runtime use or original-frame fidelity; diagnostics stay in `wall-owner-sdl/`.

Final driver/original/native **1.129/0.707/0.031 s** (CLI 1.311 s), replays
**0.415/0.438 s** CLI. Changed-decoder fresh CLIs **7.098/10.489/33.158 s** for
sweep/ordinary parent/resident parent. All fresh/replay work took **156.462 s**
inside its driver (CLI 156.497 s); individual retained commands/times are in
`wall-owner-verification.json`. Reviewed builds **19.434/10.907 s**; Python
CLI **2.349 s** (unittest 0.667 s), test.command **2.355 s**, sanitizer CTest
**4.254 s**, SDL **2.373 s**. Independent commands overlap; full inherited/active
delivery elapsed is unavailable. The closing identity-audit interval is recorded
in the handoff and private frozen audit.

Failed attempts remain recorded: first build **13.879 s** used a nonexistent
loader name; first original CLI **0.543 s** lacked that failed runner; next
original CLI **0.928 s** stopped at fixture validation of the original table's
zero-sized final slot, before producing expectations. Loader and fixture guards
were corrected, then v1 passed (**0.981 s** CLI). Review added an invalid-overlay
guard, explicit FP-domain wording and measured counters; fresh v2 has unchanged
commands/results/labels. No original/native mismatch occurred. No gameplay
repair, evidence-cache infrastructure, Windows/source install/system change or
worker was introduced. Two guessed reference paths were corrected through file
search; the cached recomp directory has no independent Git metadata, so its
existing recorded snapshot pin is used rather than the parent Git HEAD.

## Reproduce

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

# Fresh destination required; original execution needs the Mac host JIT context.
build/tools-env/bin/python tests/compare_map_wall_owner.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/map-wall-owner-new
build/tools-env/bin/python tests/compare_map_wall_owner.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/map-wall-owner-v2/expected.json \
  --report private/map-depth-1006/map-wall-owner-v2/replay-new.json
build/tools-env/bin/python tests/compare_map_wall_owner.py \
  --exe private/official-1006-probe/game.exe \
  --native build/sanitize/map-wall-owner-vectors \
  --expectations private/map-depth-1006/map-wall-owner-v2/expected.json \
  --report private/map-depth-1006/map-wall-owner-v2/sanitize-new.json

./run.command --crossing-light-demo
```

Select the Rhino; G/right-click moves, L toggles the host-placed light, R resets.
This existing native scenario does not exercise the new unwired wall helper.

## Next dependency

Join the actual overlay-bearing two-pass parent `0x54B2E0` with shared resource/
resident Cell/lighting/wall-owner children. Preserve wrapped resource sum return,
all first-pass flag clears before second-pass work, resource before recalculation,
and the **post-recalculation** overlay read before wall-owner assignment. Keep
empty transient list/no-tag bounds explicit; retain original ordinary guards.
Supply and audit required building/house/height associations without presenting
them as recovered initialization. Then bind prepared Cell/TMP into Foot/base-depth
and Unit/world before runtime depth promotion and actual SDL crossing/parked
`(51,72)`, elevation 4. Full startup/actors/visibility/pathfinding/frame fidelity,
complete base RA2 and Yuri's Revenge remain open. No workers are requested.
