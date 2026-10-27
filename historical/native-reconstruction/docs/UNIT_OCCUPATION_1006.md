# Unit occupation writes on actual map floors

[UNIT_MEMBERSHIP_1006.md](UNIT_MEMBERSHIP_1006.md) subsequently joins these actual
occupation/floor children with complete Mark/map/Cell/foundation. Visibility/
notification/recalculation remain services and runtime remains unwired.

[UNIT_MARK_1006.md](UNIT_MARK_1006.md) subsequently verifies the complete Mark
wrappers with membership effects still supplied. The checkpoint below retains its
earlier scope; actual shared membership/occupation/Process integration remains open.

After `1b382a2`, complete Unit occupation mark/unmark matches **2,142 fresh
sequences / 9,060 calls**, followed by normal and ASan/UBSan replays. This is a
recovery checkpoint toward original movement marking. The helper is unwired;
Object/Techno/Foot Mark, membership, admission and reservation effects still need
their own verification and join. The existing terrain demo is preserved. Complete
native base RA2, then Yuri's Revenge, remain incomplete.

## Identity and references

Both supplied executables rehash equal at 4,485,392 bytes / SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`:
`private/official-1006-probe/game.exe` and the already authorized
`private/windows-baseline-20261014/game.exe`. Embedded 1.08, supplied 1.006
lineage and reported no-CD changes remain distinct provenance; pristine
authenticity is unverified. This checkpoint needs no new Windows action/transfer.

Pinned YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88`, `UnitClass.h`
MarkAllOccupationBits/UnmarkAllOccupationBits, `ObjectClass.h` virtual declarations
and `CellClass.h` occupation comments supplied naming leads. Hypothesis: the Unit
virtuals mutate Cell occupation at different height/bridge gates. Actual base
vtable slots and isolated execution decide behavior; YR addresses are not used.
No YRpp license file was found, and no header code was incorporated. Retained
recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439` LICENSE was checked: MIT
covers its own tools/docs, excludes lifted/original game code, and retains stale
The Movies wording. It supplied no occupation algorithm. No upstream/header/
generated/lifted code, extracted table, new dependency or runtime executable read.

## Recovered boundary

`sim/UnitOccupation` is SDL-free and contains only the occupation virtuals.
`tools/verify_unit_occupation.py` pins complete ranges:

| Base routine | Range | Instructions |
| --- | --- | ---: |
| Unit mark, vtable `0x7ADDF8+0xE8` | `0x707980..0x7079DE` | 30 |
| Unit unmark, slot `+0xEC` | `0x7079E0..0x707A33` | 27 |
| Actual coordinate Cell lookup | `0x548000..0x548068` | 36 |

The existing complete map-floor, Cell-floor and FTOL children execute in the
same guest. Six entered ranges contain **458 instructions**; the eight-range
allowlist also retains unused relative-height/Cell-center roots from the floor
suite, for 506 inspected instructions total. Initial map/Cell/global/occupation
records, lazy plane template, level height and height threshold remain supplied.
Threshold initialization and an actor/Cell startup association are not recovered.

Each virtual first obtains and saves the Cell pointer, then independently queries
map floor at the coordinate. After floor returns, it reads threshold `0xAD057C`
and coordinate Z. Floor plus threshold wraps to 32 bits before signed comparison.

- Mark selects `Cell+0x128` only when boundary <= Z **and** `Cell+0x140` has bit
  `0x100`. Otherwise it selects `+0x124`.
- Unmark selects `+0x128` whenever boundary <= Z, without testing that flag.
- The selected dword is read, bit `0x20` is set/cleared in its low byte, then the
  whole dword is stored. Upper bytes and other bits survive. A repeated operation
  still writes; these bits have no reference count.
- The saved Cell identity survives subsequent queries. Actual map lookups use
  full signed division before a wrapped combined index; a miss retains the shared
  fallback record and its ordered word-coordinate stores.

The C++ observer reports logical dword assignments after field updates; native
machine instruction/store width is not claimed. The original write hook verifies
actual aligned four-byte stores and rejects other widths/offsets in that region.

## Evidence and limits

Current proof: `private/map-depth-1006/unit-occupation-v2/`. V1 predates the final
region-wide write-width check and remains historical; its commands/results/labels
equal v2. The fresh run makes 63 additional original floor-boundary discovery
calls, so there are **9,123 audited complete roots**, 9,123 actual map/floor
queries and occupation dword stores, and 17,782 actual FTOL entries. There are
1,454 elevated mark stores and 2,845 elevated unmark stores, including discovery.

The compared domain covers all 21 ramps, signed level bytes, actual floor
boundaries, signed threshold/addition overflow, bridge-bit asymmetry, arbitrary
upper occupation/flag bits, repeated operations, warm lazy floor state and live
height changes, full-coordinate aliases/fallback, and four incoming native FP
modes with restoration. Ten malformed/domain refusals are native safety checks,
not original malformed-input fidelity.

Forty-eight sequences use explicitly **diagnostic supplied mutations** at floor
entry/return. They change coordinates, threshold or the saved Cell flag to verify
saved identity and delayed reads. There are 768 supplied scalar writes. They do
not demonstrate that an original floor routine changes those inputs in gameplay.
Other sequences execute unmodified map/floor children without those mutations.
Return/ESP/callee-saved/caller-tail, block/write allowlists, immutable table/code/
global inputs, complete Cell arenas, fallback state, named queries, ordered
occupation stores and final lazy-state digests are checked. Full memory-read or
native internal machine-write order is not claimed.

Object/Techno/Foot Mark and map/Cell membership have inspection leads, not new
execution evidence: Unit `+0x11C` dispatches to Foot `0x4C2E60`, then Techno
`0x6C2550` and Object `0x5D4160`. Foot mode 2 skips the parent; accepted other
modes query layer, and layer 2 selects map insert/remove. The map/Cell roots have
Unit-specific type/foundation/visibility dependencies beyond earlier Terrain
proof. Recover these actual associations before replacing runtime callbacks or
joining occupation into complete Process. Do not infer Unit membership from
the earlier static Terrain tests or activate bridge gameplay from these fields.

Both full builds, **768 Python tests, 54 normal / 53 sanitizer CTests** pass.
Actual SDL terrain regression passes unchanged: 78-update level crossing,
44-update ramp with 29 tilted / one ramp-lag / 23 positive-height samples, and
parked cliff Z416/depth-52 with 153 visible / 886 rejected pixels. These are native
integration checks, not original frame parity or newly wired occupation behavior.
The arm64 app hash remains
`61731c8f45379c83107b8b73e85848e65523ba7558245b5c256ce6b0c4f63617`.

Closing source/privacy/AST/link/receipt audit:
`private/map-depth-1006/unit-occupation-closing-audit.py` and JSON. Current
inventory is **102 replay records / 6,430 source entries**, recursively 6,696
checked; **98 prior records unchanged without reexecution**, 450 Python ASTs.
Final link/source-candidate counts are recorded in the private audit.

The CMake/source inventory changed, so the broad runtime projection proof was
freshly regenerated as `private/map-depth-1006/terrain-runtime-map-v4/`, with both
replays. All 13,515 selected Cells and 255 input slices retain v3 outputs/inputs;
old receipts are not relabeled. The first refresh used `private/game`, which lacks
the patched prepared ramp data, and stopped before original execution. The
correct existing directory is `private/official-1006-probe`. No failed result was
accepted or original instruction patched.

Measured build **10.604 s**, sanitizer build **13.778 s**, test-command **2.373 s**,
Python wall **2.305 s** (unittest0.758), sanitizer CTest wall **6.176 s**. Fresh
occupation CLI/original/native **6.371 / 5.284 / 0.187 s**; normal replay
**0.978 / 0.162 s**, sanitizer **7.165 / 5.854 s**. Refreshed runtime original
**13.808 s**, CLI **21.165 s**. Actual SDL **2.980 s**. Independent checks ran
concurrently. Full inherited delivery/research and aggregate failed-attempt times
are unavailable. No workers, cache infrastructure, source-install/disc/outpost2
writes, DRM/system changes or publication.

## Reproduce and continue

```sh
./build.command
./test.command
PYTHONDONTWRITEBYTECODE=1 build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

# Fresh original execution needs the authorized Mac host JIT and a new destination.
build/tools-env/bin/python tests/compare_unit_occupation.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/unit-occupation-new
build/tools-env/bin/python tests/compare_unit_occupation.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/unit-occupation-v2/expected.json \
  --report private/map-depth-1006/unit-occupation-v2/replay-new.json
# Add --native build/sanitize/unit-occupation-vectors for sanitizer replay.

./run.command --terrain-demo
./run.command --parked-cliff-demo
```

Select Rhino, G crosses the fixed ramp, R resets, Q/E turns, A/D aims, S finishes
the committed track and stops; right-click uses bounded approximate picking and
direct routing. Only Apple Silicon macOS is tested. Next complete ordinary Unit
Mark/membership and its required shared Cell associations, join actual occupation
into movement, then rerun move/stop/turn SDL acceptance. Combat, economy, AI,
campaigns, multiplayer, audio, original saves and YR remain later work.
