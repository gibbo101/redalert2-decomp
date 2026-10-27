# Supplied RA2 1.006 ordinary Unit draw eligibility

October 14, 2026. Following per-frame caller checkpoint `0b0bae6`, **5,318 fresh
original/native results** and normal/ASan/UBSan replays pass for the ordinary Unit
wrapper and complete nested Object draw gate. It is not yet connected to runtime
traversal; the moving crossing delivery remains open.

## Identity, references and boundary

Only `private/official-1006-probe/game.exe`, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`,
4,485,392 bytes, is accepted. Embedded version is 1.08. It is byte-identical to the
approved private Windows transfer; supplied 1.006 lineage and user-reported no-CD
provenance do not establish pristine authenticity. Disc proof is separate.

Revisited REFERENCES.md's pinned redalert2-recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439`, `docs/voxels.md` and LICENSE;
YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88`, ObjectClass/UnitClass/
TechnoClass signature leads. Exact base-binary inspection/execution establishes
behavior. No reference, generated or lifted game code was incorporated.

`tools/verify_unit_visibility.py` pins two complete additional routines / **217
instructions**, and inherits the previous actual Unit/Terrain dispatch checks:

| Routine | Address | Executed domain |
| --- | --- | --- |
| Unit +0xFC wrapper | `0x6FF350` | Actor byte +0x370 is zero |
| Nested Object draw gate | `0x5D34E0` | Complete routine on actual Unit type |

Original Unit vtable `0x7ADDF8`, +0xA8 coordinate getter `0x41B270`, nested +0x48
getter `0x5D4E40`, type leaf `0x70A2D0` and final +0x10C slot `0x700E70` are
checked. Actual coordinate/type methods execute. Tactical projection `0x6A29D0`
and final DrawIt are supplied services, not recovered by this evidence.

Native `drawOrdinaryUnitIfVisible` refuses nonzero +0x370 before callbacks or
mutations. The wrapper's alternate state, other Object subclasses, construction
and stock field initialization remain open. All state/service inputs are explicit
fixtures, not observed gameplay. No installation, original instruction or system
setting changed. Original data and expectations remain ignored/private.

## Recovered behavior

- The ordinary Unit wrapper supplies third=0 to Object, discarding its caller's
  third argument. Force is forwarded; Object reads its low byte.
- With bypass=0/context present, redraw must be nonzero unless forced; limbo must
  be zero even when forced. Null context/nonzero bypass skips these gates. The
  on-map byte is not read. Do not reuse Terrain's additional on-map test.
- Accepted gates clear redraw before coordinates/projection. Projection failure
  invokes the actual Unit type leaf and returns false with bounds unchanged.
- Successful projection intersects caller bounds with the viewport through the
  recovered signed/wrapped sequence and writes all four words. It makes no
  render-dimensions call and does not reject an empty intersection.
- Screen coordinates adjust after clipping. Bounds may alias the viewport, as in
  the actual per-frame caller; native viewport is a live reference so adjustments
  see the same updated rectangle. DrawIt executes even for empty bounds, then the
  gate returns true. Final DrawIt remains a supplied service.

The kernel reuses independently recovered `intersectDrawBounds`; added signed
arithmetic wraps explicitly at 32 bits.

## Evidence and reproduction

Private evidence: `private/traversal-1006/unit-visibility/expected.json`, fresh
`report.json`, `native-replay-report.json`, `sanitize-report.json`. **5,319 audited
roots** include the existing shared harness's empty-rectangle initializer, not an
extra Unit behavior claim. Coverage: 3,240 state/bypass/context/force/projection
combinations, 2,048 clipping/wrapping/live-alias cases and 30 explicit empty/touching/
alias cases. Comparisons include return byte, redraw, both rectangles, ordered
byte/dword mutations and coordinate/projection/type/draw events. Original registers,
ESP/return/caller guards, permitted writes and the full fixture arena/tails agree.

```sh
./build.command
./test.command
build/tools-env/bin/python tools/verify_unit_visibility.py \
  --exe private/official-1006-probe/game.exe
build/tools-env/bin/python tests/compare_unit_visibility.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/traversal-1006/unit-visibility/expected.json \
  --report private/traversal-1006/unit-visibility/NEW-NATIVE-REPLAY.json
# Add --native build/sanitize/unit-visibility-vectors for sanitizer replay.
build/tools-env/bin/python tests/test_unit_visibility_evidence.py
# Fresh original execution requires the authorized Apple Silicon host JIT context:
build/tools-env/bin/python tests/compare_unit_visibility.py \
  --exe private/official-1006-probe/game.exe \
  --output private/traversal-1006/NEW-UNIT-VISIBILITY-ORIGINAL
```

Replays execute no original code and require source/inspection/engine/receipt
identities. Fresh receipts cannot overwrite proof. Seven new Python guards and
native special-state refusal checks pass. Full Python discovery is **188 tests**;
normal/sanitizer CTest pass. Patched owned presentation passed in this continuation's
preceding traversal checkpoint. No additional full SDL crossing was run/claimed.

## Accounting and continuation

Fresh Unit CLI: 1.880 s total / 1.005 s original / 0.103 s native. Normal replay:
1.108 s total / 0.097 s native; sanitizer: 1.179 s total / 0.163 s native. Python
discovery: 0.533 s; normal/sanitizer CTest: 0.06/0.32 s. Separate build/whole-
continuation elapsed measurements are unavailable. No failed Unit parity attempt
or playtest repair occurred. An initial documentation patch failed its context
check and was reapplied without changing research evidence. The preceding local
Git write needed host context because .git is read-only in the workspace sandbox;
the authorized retry committed successfully.

Traversal source identities now cover relevant code files without the whole
CMake file, so unrelated target additions do not invalidate that proof. No caller
algorithm changed. Fresh **2,808** scenarios and sanitizer replay were generated
under `private/traversal-1006/dynamic-v2/`: 4.668 s total / 3.753 s original /
0.285 s native, 0.473 s sanitizer native. Earlier `dynamic/` receipts remain the
historical `0b0bae6` snapshot, never overwritten or relabeled.

Next verify stock Unit flags/+0x370 and the secondary Foot getter, execute a
combined caller with nested Unit eligibility, recover required redraw-region
scheduling, then integrate and exercise a reproducible Rhino/scenery crossing with
actual SDL input/rendering. UI/extras, camera inversion, animated Terrain, dynamic
lifetimes, general frame order and whole-frame parity remain open. This checkpoint
is locally verified progress, not independent acceptance or a completed milestone.
The full native game/YR goal remains active.
