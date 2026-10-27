# Unit Object, Techno and Foot Mark

[UNIT_MEMBERSHIP_1006.md](UNIT_MEMBERSHIP_1006.md) subsequently joins actual map/
Cell/foundation/occupation with these complete wrappers. Its visibility/notification/
recalculation effects remain services and the helper is unwired. The checkpoint
below retains its own earlier scope and receipts.

After `11b8349`, complete Unit-kind Object/Techno/Foot Mark matches **4,263 fresh
sequences / 11,667 calls**, followed by normal and ASan/UBSan replays. Actual
kind/cast, image/type/owner/coordinate, nonnull Drive layer and Object/map redraw
children execute. Map insert/remove and special-event effects remain named
services. The SDL-free helper is unwired; actual membership/occupation/Process
integration remains next. Complete native base RA2, then Yuri's Revenge, remain
incomplete. This is local routine evidence, not independent or whole-frame parity.

## Provenance and bounded domain

Both supplied executable copies rehash equal at 4,485,392 bytes / SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`:
`private/official-1006-probe/game.exe` and the already authorized private Windows
copy. Embedded 1.08, supplied 1.006 lineage and reported no-CD changes remain
distinct; pristine authenticity is unverified. No new Windows action/transfer,
download, source-install/disc/outpost2 write, DRM/system change or publication.

Consulted pinned YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88`,
`ObjectClass.h`, `TechnoClass.h`, `FootClass.h`, `UnitClass.h` virtual declarations,
and retained recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439` reference/license
context. Hypothesis: Unit's Mark wrapper and membership layer differ from static
Terrain. Actual base vtable, routines and execution decide behavior. YR/replacement
behavior is not the oracle. No YRpp license file found; recomp's MIT grant excludes
lifted/original game code and retains stale The Movies wording. No upstream/header/
generated/lifted code or extracted table incorporated. Inspection hashes the cast
tables without copying their bytes into tracked source. No new dependency or
runtime executable read; `ra2_sim` remains SDL-free and independent of rendering.

Initial actor/type/house/nonnull Drive/tactical records are supplied. Kind is
actual Unit 1; Drive's actual layer getter returns 2. The protocol suite permits
a null supplied Unit type for image's zero return; this does not establish a valid
null-type input to the actual membership parent, which dereferences type. Special
state may be nonzero only with the explicit event service; its effects are not
recovered. Row coordinates, limbo/special bytes and optional redraw resets are
supplied inputs, not recovered frame updates. Other actor kinds, locomotors and
the null-locomotor COM error path remain outside scope.

## Actual chain and preserved behavior

`tools/verify_unit_mark.py` pins **14 complete ranges / 274 instructions**,
including the type getter's complete virtual tail dispatch. Every range enters.

| Routine | Base entry |
| --- | --- |
| Unit +0x11C → Foot Mark | `0x4C2E60` |
| Techno Mark | `0x6C2550` |
| Object Mark | `0x5D4160` |
| Techno cast / image numeric getter | `0x40DC20` / `0x6D3E50` |
| Owner / signed word Cell coordinate getters | `0x6C7420` / `0x41B320` |
| Foot layer / actual Drive layer | `0x4CA130` / `0x4A47E0` |
| Unit kind / type tail / Unit type getter | `0x70A2D0` / `0x6C12C0` / `0x705020` |
| Object / map redraw request | `0x5D36E0` / `0x4E09A0` |

- **Foot mode 2 immediately returns true.** It skips Object's limbo/on-map/dirty
  checks, Techno's event, layer queries and membership. Do not substitute Terrain
  Mark or direct Object Mark for this Unit virtual.
- Object rejects nonzero limbo. Its direct mode 2 accepts only on-map, clean
  actors, then requests redraw. Other modes query kind and the actual techno
  cast; Unit kind 1 retains the same pointer.
- The image, owner and coordinate queries occur in that order, even if a later
  mode/on-map gate rejects the call. Image obtains the type through the actual
  tail dispatch; null returns zero, Unit type returns `+0x598`. Owner dereferences
  the supplied house then `+0x30`. Coordinates divide full signed X/Y by 256
  toward zero before truncating each result to a word. Their return values and
  repeated coordinates are observed; do not remove unused queries.
- Modes 1/3 write on-map `+0x74=1` only from zero, then invoke redraw. Mode 0
  writes zero only from nonzero. Other modes reject after the probes. Redraw's
  virtual is still invoked when already dirty, but only zero dirty state writes
  `+0x75=1` and calls map redraw(0). The actual map child writes tactical dirty
  when present and leaves map mode/counter unchanged for mode 0.
- Accepted Techno Mark tests the live special byte `+0x370` after the parent and
  calls event 13 when nonzero. Event effects/return are supplied/ignored.
- Accepted non-mode-2 Foot Mark queries the layer, then obtains coordinates again
  when layer is 2. Modes 1/3 call map insert; mode 0 calls remove. The on-map and
  redraw stores and special event precede these membership services.

`sim/UnitMark` exposes the three distinct roots and named service boundaries.
Callbacks are required only when reached; Foot mode 2 and rejected limbo can run
without them. Native redraw binding reuses `requestMapRedraw` in the test harness;
the simulation library does not depend on `ra2_render`. Native stores are logical
field assignments; physical native instruction/store order is not claimed.

## Verification and remaining work

Current proof: `private/map-depth-1006/unit-mark-v2/`. V1 predates replacing the
inspection tool's table-byte comparison with a hash; commands/results/labels are
unchanged. No original instruction was modified or failed expectation accepted.
Coverage includes all three roots, modes 0..4 and signed extremes/unknown modes,
nonzero byte gates, dirty/on-map combinations, type-null/image/owner values,
tactical-present/absent, full signed coordinate/word boundaries, repeated cycles
and explicitly supplied dirty resets. Thirteen malformed/domain refusals are
native safety checks, not original malformed-input fidelity.

The fresh run has **11,667 audited complete roots**, 4,756 actual cast/image/owner
calls, 5,274 actual coordinate getters, 518 actual Foot/Drive layer calls, 958
redraw virtual calls, 669 actual map redraw calls, and 2,737 selected byte stores.
There are 518 supplied membership and 441 supplied event calls. Return low byte,
ESP/callee-saved/caller-tail, block/write allowlists, code/dispatch/cast-table
identity, immutable input state, full actor/type/house/locomotor/tactical arena,
ordered named queries/services, selected byte stores and final state are audited.
Full memory-read/native internal write order is not claimed.

Actual membership still needs its own Unit-specific dependencies. Inspection-only
next leads: map insert/remove `0x54AB70` / `0x54AF70`, Cell insert/remove
`0x473B30` / `0x473D20`, Unit occupation eligibility `0x41B470` reads `+0x5A0`,
and UnitType +0x90 selects `0x5D5D90`, whose lazy single-Cell foundation is
`(0,0), (32767,32767)`. The Object foundation wrapper, lazy flags/atexit and list
copy, visibility predicates/notifications, linked-list mutation, actual occupation
and recalculation need the shared guest join. These are inspected leads, not
execution evidence. Earlier Terrain proof does not establish Unit membership.
Do not wire partial membership or reinterpret existing renderer layer adapters
from this Mark protocol alone.

Both builds, **775 Python tests, 55 normal / 54 sanitizer CTests** pass; the final
inspection-only edit also passes focused evidence guards and fresh/replay proof.
Actual SDL terrain crossing/ramp/cliff regression passes unchanged, with the same
78-update crossing, 44-update ramp (29 tilted / one lag / 23 positive-height
samples) and parked Z416/depth-52/153 visible/886 rejected pixels. These are native
integration checks, not newly wired Mark behavior. App hash remains
`61731c8f45379c83107b8b73e85848e65523ba7558245b5c256ce6b0c4f63617`.

Broad source-inventory changes have fresh `terrain-runtime-map-v5` proof and both
replays; all 13,515 selected Cell records, commands and 255 input slices retain v4
outputs/inputs. Old receipts are historical, not relabeled. Closing source/privacy/
AST/link/receipt audit: `private/map-depth-1006/unit-mark-closing-audit.py` / JSON.
Inventory: **104 replay records / 6,484 source entries**, recursively 6,750 checked;
**100 prior records unchanged without reexecution**, 454 Python ASTs. Final link/
source-candidate counts are retained in that private audit.
No workers or caching infrastructure. Full inherited/research delivery time is
unavailable. Independent checks ran concurrently.

Measured builds **13.581 / 14.453 s**, test-command **3.348 s**, Python wall
**3.360 s** (unittest1.100), sanitizer CTest wall **8.833 s**. Fresh Mark
CLI/original/native **3.081 / 2.521 / 0.069 s**; normal replay **0.391 / 0.059 s**,
sanitizer **1.257 / 0.290 s**. Runtime refresh original **13.993 s**, CLI
**26.240 s**, normal/sanitizer replay **4.862 / 11.605 s**. SDL **5.678 s**.
The existing harmless duplicate static-library warning remains; no sanitizer
diagnostic. No failed execution attempt occurred in this checkpoint.

```sh
./build.command
./test.command
PYTHONDONTWRITEBYTECODE=1 build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
build/tools-env/bin/python tests/compare_unit_mark.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/unit-mark-new
build/tools-env/bin/python tests/compare_unit_mark.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/unit-mark-v2/expected.json \
  --report private/map-depth-1006/unit-mark-v2/replay-new.json
# Fresh original needs the authorized Mac host JIT; use a new private destination.
# Add --native build/sanitize/unit-mark-vectors for sanitizer replay.
./run.command --terrain-demo
./run.command --parked-cliff-demo
```

Select Rhino, G crosses the ramp, R resets, Q/E turns, A/D aims, S finishes the
committed track and stops. Picking/direct routes/clearance remain approximate.
Only Apple Silicon macOS is tested. Actual shared membership/occupation/Process
join and move/stop/turn SDL acceptance come next; startup, actor construction,
admission/reservation/mission effects, combat/economy/AI/campaigns/multiplayer,
audio/original saves/YR remain open.
