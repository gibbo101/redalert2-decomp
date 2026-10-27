# Supplied RA2 1.006 ordinary Unit DrawIt caller

[UNIT_METADATA_1006.md](UNIT_METADATA_1006.md) corrects the provisional
`simpleDeployer` name below: base `+0xBA6` is **Harvester**, established by its
actual INI key/call/store. The zero-field domain remains; fresh source-matched
caller/type receipts are `caller-harvester-v1/` and `type-harvester-v1/`.

[UNIT_TYPE_VISIBILITY_1006.md](UNIT_TYPE_VISIBILITY_1006.md) extends this checkpoint
with 20,442 fresh type/owner/timer/scoped-constructor cases and both replays.
The caller now supports its original timer decision with a supplied decoration;
the predicate/alternate-type children execute in the new nested fixture. Its
changed sources have fresh 9,167-case receipts at `caller-state-v1/`, with both
replays. The inactive-timer and supplied-type-predicate limits below describe this
earlier checkpoint. Full constructor/type loading, final children and runtime
wiring remain open.

October 15, 2026, following `49df1e2`. **9,167 fresh original/native results** and
normal/ASan/UBSan replays pass. This is a prerequisite recovery checkpoint toward
the next healthy Unit drawing delivery. The new caller is not wired into Renderer;
milestone 20's moving crossing and its explicit host policies remain current.

## Identity and reference hypothesis

Only the supplied patched engine is accepted: SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`,
4,485,392 bytes, `private/official-1006-probe/game.exe`. It remains byte-identical
to the approved private Windows copy. Embedded 1.08, supplied 1.006 patch lineage
and reported no-CD provenance remain separate facts; pristine authenticity is not
established. No source installation or Windows state changed.

Consulted the pinned redalert2-recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439`
`docs/voxels.md` (unit path/final staging) and LICENSE, plus pinned YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88`, `UnitClass.h`, `FootClass.h`,
`TechnoClass.h`, `UnitTypeClass.h` and `TechnoTypeClass.h`. Hypothesis: a Unit wrapper
selects voxel/SHP drawing and lighting before the already recovered composition.
Names/layouts supplied leads only. Exact base-binary inspection/execution below
establishes the tested behavior. No upstream/header/generated or lifted code was
incorporated. YR declarations do not determine base RA2 addresses/signatures.

## Complete inspected ranges and executed boundary

`tools/verify_unit_draw_caller.py` pins **12 complete ranges / 892 instructions**
and actual Unit vtable slots, including `+0x10C`, `+0x1A0`, `+0x1B0`, `+0x4D8`
and `+0x4DC`:

| Routine | Patched address |
| --- | --- |
| Complete Unit DrawIt caller | `0x700E70` |
| Screen registration | `0x6AA510` |
| Object relative-height wrapper | `0x5D4810` |
| Coordinate and word-cell map lookup | `0x548000`, `0x548070` |
| Coordinate-to-word-cell getter | `0x41B320` |
| Unit visibility wrapper / complete Object gate | `0x6FF350`, `0x5D34E0` |
| Rectangle intersection / empty initializer | `0x41FDF0`, `0x6E2FE0` |
| Actor coordinate getter / Unit type leaf | `0x41B270`, `0x70A2D0` |

The entire root caller executes in the explicit ordinary domain: type byte
`+0xBA6=0`, actor bridge byte `+0x79=0`, flag house `+0x5B4=-1`, timer start
`+0x314=-1` and duration `+0x31C=0`, and no coordinate-cell flag `0x100`.
The provisional `simpleDeployer` name follows a reference lead; this checkpoint
does not recover its alternate behavior or establish complete stock construction.
Inspection of other branches is not executed parity for them.

The actual nested coordinate getters, height wrapper, map lookups, screen registry,
Unit/Object visibility and clip code execute unchanged. The 512x512 lookup table
is a supplied immutable fixture whose entries all reference one synthetic cell;
it is not original map construction or real current-cell association. Layer query,
ground height, brightness predicate, original-type visibility, alternate-type
query, final voxel/SHP draws, resource lookup and Foot decoration remain explicit
read-only services. This proves caller selection/order/arguments, not their child
implementations, house creation or complete Unit rendering.

## Preserved behavior

`src/render/UnitDrawCaller.*` has no SDL dependency:

- Shared resource initialization tests only flag bit 0, preserves upper bits and
  writes the bit before lookup, then stores the lookup result even if null. The
  native resource record models fields, not ownership or loading/lifetime.
- The screen Y subtracts signed actor byte `+0x59E`, wrapping at 32 bits. Nonzero
  byte `+0x37C` adds 14 to the main draw point. Foot decoration keeps the earlier
  point without the 14 adjustment. Coordinate-to-word-cell lookup precedes layer
  query; layer exactly 5 returns before registration, lighting, drawing or Foot.
- Screen registration refuses count exactly 500 and points outside inclusive
  `[-32,width+32]` / `[-32,height+32]`, using wrapped additions. Accepted writes
  are actor, origin-adjusted X, origin-adjusted Y, then incremented count. Other
  entries/capacity tails remain unchanged. Native counts outside 0..500 are safety
  refusals; no original malformed-count behavior is claimed. Native entries use
  opaque actor IDs and value points; fixture comparison translates the isolated
  original actor pointer to the same ID. Original actor ownership is not modeled.
- Ground/height lookup occurs before coordinate-cell lookup. In this ordinary
  lighting domain the resulting height does not change brightness. The two later
  word-cell lookups remain distinct: flags/predicate come from the first, signed
  ambient from the second. Ambient, optional -500 and ExtraUnitLight wrap, retaining
  [UNIT_LIGHTING_1006.md](UNIT_LIGHTING_1006.md) arithmetic. Final effects inside
  child drawing are outside this caller boundary.
- The visibility predicate consumes its low byte. A zero result queries alternate
  type with argument 1. Body drawing requires secondary byte exactly `0xFF`, not
  any negative index. A voxel type additionally needs a nonnull model; SHP does
  not use that model check. The seven dword arguments are point X/Y, rectangle
  X/Y/width/height and brightness; no YR-only extra argument is assumed.
- Original type `+0x5AC` is restored with an actual store even when no temporary
  type change occurred, then Foot decoration is called. Missing bodies and indexed
  secondary state do not suppress that restoration/decoration. The nested gate
  retains its previously verified clearing, projection failure and empty-clip
  behavior; a successful gate can invoke this caller even with an empty rectangle.

Other actor/type/status profiles are refused explicitly. The inherited light-cell
coordinate safety domain is +/-1,048,576 leptons; original fixture coordinates here
map to valid table entries. Neither native guards nor synthetic input records are
evidence for original constructors, malformed-input behavior or stock state.

## Evidence and reproduction

Current receipts: `private/unit-draw-1006/caller-v3/{expected,report}.json`,
`native-replay.json` and `sanitize-replay.json`. Fresh/replay validation pins exact
engine/profile, inspection, oracle/native sources and original receipt/fingerprint;
rebuilt native runners are allowed with their new hashes recorded separately.
Fresh runs refuse existing original evidence. No original instruction is modified.

| Matching cases | Count |
| --- | ---: |
| Registry margins/capacity/origin wrap | 490 |
| Every valid registry count | 501 |
| Signed/wrapped dimensions and capacity tails | 1,024 |
| Every resource flag/offset/add-14 byte | 256 |
| Layer/secondary/type/model and distinct Foot point | 3,840 |
| Nested ordinary brightness and wrapped extra | 1,008 |
| Complete caller with wrapped points/clips/registry | 1,024 |
| Actual visibility gate with nested caller/registry | 1,024 |
| **Total** | **9,167** |

**9,168 callable roots** include the empty initializer. Audits cover original caller
ESP/return/callee-saved registers, bounded service arguments/writes, ordered external
stores/events, complete original fixture arenas, registry capacity tails and immutable map
table. The original shared resource and selected actor type stores have exact
allowed widths/values. No heap allocation, compressed pool or final surface executes
in this oracle; it makes no pixel/frame parity claim.

```sh
./build.command
./test.command
build/tools-env/bin/python tools/verify_unit_draw_caller.py \
  --exe private/official-1006-probe/game.exe
build/tools-env/bin/python tests/compare_unit_draw_caller.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/unit-draw-1006/caller-v3/expected.json \
  --report private/unit-draw-1006/caller-v3/NEW-NATIVE-REPLAY.json
# Add --native build/sanitize/unit-draw-caller-vectors for sanitizer replay.
build/tools-env/bin/python tests/test_unit_draw_caller_evidence.py
# Fresh execution requires authorized Apple Silicon host JIT context:
build/tools-env/bin/python tests/compare_unit_draw_caller.py \
  --exe private/official-1006-probe/game.exe --output private/unit-draw-1006/NEW-ORIGINAL
./run.command --crossing-demo
```

Seven new evidence guards, eight native profile/count refusals, separate native
live-entry/capacity-tail checks, normal/sanitizer
CTest and all **216 Python tests** pass. The actual existing SDL crossing still
passes (79 samples / 78 updates, 150 maximum hidden pixels). The new kernel remains
unused by runtime, so that SDL result validates unchanged integration only. Broad
milestone 20 replays retain their scope; they were not repeated for this unused
kernel. Only Apple Silicon macOS is tested.

## Accounting, rejected attempt and next dependency

The first isolated fixture passed 8,143 cases in 2.58 s CLI; its receipts remain in
`private/unit-draw-1006/caller/` with their earlier source identities. Adding the
nested gate changed fixtures/sources and required fresh original execution. The
first nested comparison rejected a missing original type-leaf trace event on
projection failure. Native already emitted the correct event; the oracle hook was
added after inspecting the actual leaf. No accepted receipt was saved for that
attempt. Its 2.51 s failure log remains in build/. No native behavior was changed
to hide a mismatch. The final nested generation passed: 2.67 s CLI, 2.102 s original
generation and 0.184 s native comparison. Normal/sanitizer replay costs are recorded
in their immutable-scope receipts. No game playtest repair was needed.

Initial normal build: 3.78 s; adding domain guards: 4.80/4.78 s normal/sanitizer;
nested runner builds: 1.98/1.01 s. CTest CLI: 0.20/0.78 s. Existing SDL crossing:
2.41 s. Python discovery and final replay costs are in build logs. The first
recorded continuation clock is 04:52:13 UTC; the private checkpoint receipt records
the end/elapsed interval after commit. Full inherited milestone elapsed is
unavailable. This checkpoint inherits milestone 20 and earlier numeric/surface
recovery; it does not introduce caching infrastructure or extra workers.

Next verify the supported Rhino's actual constructor/type metadata and visibility/
house associations, then execute the relevant ordinary voxel child dispatch and
integrate this caller inside the existing gate. Retain the crossing and current-cell
light scenario as the observable delivery, with nested original evidence before
claiming new runtime fidelity. Original full Unit DrawIt children, Foot decoration,
outer frame scheduling, actor construction/ownership/lifetime, camera inverse, fog
and UI remain distinct open boundaries. Full base RA2 and YR remain incomplete;
the goal stays active. No Windows action is needed.
