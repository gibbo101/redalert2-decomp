# Supplied RA2 1.006 combined actor traversal and secondary coordinates

October 14, 2026. Following `9f9d507`, the complete bounded per-frame caller now
executes with actual nested ordinary Unit eligibility and Foot/Drive secondary
getters in the original oracle. **6,225 fresh original/native results** and
normal/ASan/UBSan replays pass. Runtime integration and the moving crossing remain
open; this is a prerequisite checkpoint, not a completed observable delivery.

## Identity and references

Only the supplied patch engine is accepted, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`,
4,485,392 bytes, at `private/official-1006-probe/game.exe`. The approved private
Windows copy is byte-identical. Embedded version 1.08, supplied 1.006 lineage and
user-reported no-CD provenance are separate facts; pristine authenticity is not
established. Disc proof remains separate. No original file or Windows state changed.

Revisited REFERENCES.md's pinned redalert2-recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` `docs/voxels.md`/LICENSE and YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` `FootClass.h`, `ObjectClass.h`,
`TechnoClass.h`, `DriveLocomotionClass.h` and `GeneralDefinitions.h` naming leads.
Hypothesis: stock construction supplies the ordinary drawing branch and Foot
secondary coordinates come from either the indexed pool or actual locomotor.
Exact base-binary inspection/execution establishes the tested result. No upstream,
header, generated or lifted game code was incorporated.

## Recovered boundary

`tools/verify_actor_traversal.py` pins **five complete routines and five scoped
blocks / 156 additional instructions**, constructor call links and Drive RTTI:

| Routine | Address | Scope |
| --- | --- | --- |
| Foot secondary getter | `0x4CA6F0` | Complete, all signed-byte indices |
| Drive secondary getter | `0x49FDB0` | Complete, actual COM interface at base+4 |
| Drive sentinel initializer | `0x49F600` | Executes, establishes zero coordinate |
| Foot sentinel initializer | `0x4C2870` | Executes, establishes zero coordinate |
| Abstract initializer | `0x40FF10` | Complete, with explicit supplied services |

Scoped Object/Techno/Foot stores establish only drawing flag inputs, special
state `+0x370=0` and secondary index `+0x574=-1`. Abstract clears the low three
flag bits, Object ORs 2, Techno ORs 1 and Foot ORs 4. Upper allocation bits remain
unchanged: the entire byte is not universally fixed at 7. This is **not complete
Unit construction**. Call-chain and zero-register inspection support these stores;
the fixture executes the selected blocks with caller/stack/write guards.

Native `src/sim/FootCoordinates.*` is SDL-free. A nonnegative index loads signed
word X/Y from the pool and returns `(x*256+128, y*256+128, 0)`. A negative index
queries the locomotor. Drive returns its destination unless all three components
are zero, then returns current actor coordinates. If Foot still receives zero,
it invokes the actor coordinate getter. Foot's second argument is unused. Missing
indexed entries or locomotor callbacks are native safety refusals.

The combined oracle uses actual Unit/Drive vtables, coordinate/type methods,
secondary getters, Unit/Object eligibility, outer world projection and Unit
DrawBehind's type=1 no-op. Healthy static Terrain is skipped by the dynamic caller.
Inverse camera, map predicate, tactical projection, final DrawIt and extras remain
explicit services. The existing five-layer duplicate/order/clip behavior is retained.
No dynamic redraw scheduling, final rendering or full-frame claim is made.

## Evidence and reproduction

Private receipts: `private/traversal-1006/actors/{expected,report}.json`,
`native-replay-report.json` and `sanitize-report.json`. Source/inspection/engine/
receipt identities are checked; rebuilt native runners are allowed. Original code
is unchanged. Audits cover **6,230 callable roots and 1,280 scoped blocks**,
ordered visible/redraw/clip writes and service events, fixture arenas/tails and
root registers/ESP/return guards.

| Cases | Count |
| --- | ---: |
| Scoped constructor fields, every input byte | 256 |
| Every nonnegative index, signed-word edge coordinates | 3,200 |
| Every negative index, Drive sentinel and Foot fallback | 1,024 |
| Empty combined caller | 1 |
| Nested Unit state/force/projection | 864 |
| Combined map/context gates | 96 |
| Duplicate/order/shared-clip/state scenarios | 768 |
| Dense scans: 575 synthetic static Terrain actors and one Unit | 16 |
| **Total** | **6,225** |

The dense fixtures are synthetic; they are not the map's 565 supplied placements.

```sh
./build.command
./test.command
build/tools-env/bin/python tools/verify_actor_traversal.py \
  --exe private/official-1006-probe/game.exe
build/tools-env/bin/python tests/compare_actor_traversal.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/traversal-1006/actors/expected.json \
  --report private/traversal-1006/actors/NEW-NATIVE-REPLAY.json
# Add --native build/sanitize/actor-traversal-vectors for sanitizer replay.
build/tools-env/bin/python tests/test_actor_traversal_evidence.py
# Fresh execution requires the authorized Apple Silicon host JIT context:
build/tools-env/bin/python tests/compare_actor_traversal.py \
  --exe private/official-1006-probe/game.exe \
  --output private/traversal-1006/NEW-ACTOR-ORIGINAL
```

Seven new Python evidence guards, native safety guards, all **195 Python tests**,
normal/sanitizer CTest and source audit pass. No new SDL crossing was performed;
runtime is unchanged. Earlier patched owned/SDL evidence retains its own scope.

## Accounting and next dependency

Fresh CLI: 5.704 s total, 4.353 s original generation, 0.292 s native. Normal replay
native comparison: 0.296 s; sanitizer: 0.444 s. Normal/sanitizer CTest: 0.07/0.34 s;
Python discovery: 0.783 s. Builds completed successfully; separate elapsed build
and inherited whole-delivery measurements are unavailable. No failed new parity
attempt or playtest repair occurred. The continuation inherited the implementation
and fresh receipts, then checked completed build handles and replayed both runners.

Continue redraw scheduling from exact-binary leads `0x5D36E0`, `0x4E09A0`,
`0x6A3020` and the static scan callers. Those leads are not recovered evidence in
this checkpoint. Then integrate ordinary traversal and exercise moving Rhino/
scenery occlusion with actual SDL rendering/input. Camera inversion, final actor
DrawIt, UI/extras, general lifetime/scheduling, other actor branches and whole-frame
parity remain open. No extra worker or Windows action is needed.
