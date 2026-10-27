# Supplied RA2 1.006 Unit image selection and drawing state

[UNIT_METADATA_1006.md](UNIT_METADATA_1006.md) corrects the earlier nondeployer
label to **nonharvester** (`+0xBA6`) from actual base INI association. Fresh
source-matched type/caller receipts now use `type-harvester-v1/` and
`caller-harvester-v1/`; the earlier receipts below remain unchanged.

October 15, 2026, after `a9d3edd`. **20,442 fresh original/native cases** and
normal/ASan/UBSan replays pass. The changed caller also has a fresh **9,167-case**
regression, including its nested Unit/Object gate, and both replays. This is a
prerequisite checkpoint in the continuing healthy Rhino drawing delivery. Runtime
remains at [milestone 20](CROSSING_1006.md); these new image decisions are unused
by Renderer. It is not a completed new observable milestone or full-frame proof.

## Exact identity and reference hypothesis

Both private supplied engines were rehashed: `private/official-1006-probe/game.exe`
and the approved `private/windows-baseline-20261014/game.exe` are byte-identical,
4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 patch lineage and user-reported no-CD provenance are
separate facts. Pristine authenticity is not established. No source install or
Windows state changed; no new executable transfer was needed.

Consulted pinned redalert2-recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439`,
`docs/voxels.md` (unit path/final staging) and LICENSE, and pinned YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88`, `TechnoClass.h`, `ObjectClass.h`,
`HouseClass.h`, `UnitTypeClass.h` and `Timer.h`. Hypothesis: a disguise/timer/owner
predicate selects original versus alternate presentation. These are reference
leads, not a base-game address, layout or arithmetic authority. In particular,
the signed/wrapped timer comparisons and modulo phase below were recovered from
our exact base executable. No upstream/header/generated or lifted code was copied.

## Inspected and executed boundaries

`tools/verify_unit_type_visibility.py` adds seven complete functions / **161
instructions**, two actual Unit slots, and four aligned constructor ranges /
**885 instructions**. It inherits the caller's 12 complete ranges / 892 instructions.
Only **eight selected constructor field blocks** execute; the four full constructors
are inspected, not executed or reconstructed. Supplied live registers at those
blocks remain explicit inputs.

| Complete selected function | Patched VA |
| --- | --- |
| Original-type visibility predicate | `0x6D8CE0` |
| Owner visibility helper | `0x4F52B0` |
| House alliance helper | `0x4E5540` |
| Signed observer cell-counter query | `0x47C300` |
| Alternate/display type getter | `0x709BB0` |
| Unit disguise byte leaf, slot `+0xC0` | `0x41B410` |
| Unit cell getter, slot `+0x1A4` | `0x5D51E0` |

Actual owner/alliance/counter/Unit-cell/map functions execute unchanged, including
in 2,048 full Unit DrawIt caller cases. Synthetic owner/observer/cell records and
the inherited immutable 512x512 table supply association/storage. They are not
original house/map construction or proof of runtime current-cell association.
The selected Unit getter always returns the supplied valid cell in these fixtures;
null-cell and invalid-map/fallback paths are not new executed coverage.

Layer/ground/brightness predicate/resource lookup, final VXL/SHP drawing, Foot
decoration and the active timer's `0x6CC020` decoration remain explicit services.
No final voxel pixels, compressed pool or complete decoration executes here.

## Recovered decisions

`src/render/UnitTypeVisibility.*` stays SDL-free:

- The selected constructor stores initialize disguise byte `+0x170` and phase
  origin `+0x174` to zero; timer `+0x184/+0x18C` to current frame / zero; drawing
  timer `+0x314/+0x31C` to current frame / zero; bridge `+0x79`, add-14 `+0x37C`,
  alternate type `+0x40C` and screen offset `+0x59E` to zero; flag house `+0x5B4`
  to -1. These are scoped stores, not verified post-construction stock state.
- Both timer decisions use duration unchanged for start exactly -1. Otherwise
  subtract start from frame with 32-bit wrapping, compare that signed elapsed
  value against signed duration **before** the remaining subtraction, and test
  the wrapped remainder for nonzero. A negative paused duration can therefore
  take the active branch. Do not replace this with positive-only time remaining.
- Owner visibility tests global mode `0xA3D298`: nonzero requires pointer identity
  with current house; zero tests either owner byte `+0x134/+0x135` for nonzero.
  Those bytes retain offset names; complete owner creation/semantics are open.
- An active disguise timer plus a false owner helper returns original type
  immediately. Otherwise the predicate queries owner again. For visible owner
  and nonzero disguise, it computes signed wrapped `(frame-origin+64) % 256`;
  phase 72..119 inclusive chooses alternate, all other phases choose original.
- The other branch calls the actual Unit cell getter **before** its second
  disguise check. That getter performs **two** actual coordinate map lookups.
  Undisguised actors still perform them. For disguise, the observer index selects
  a signed word at cell `+0xAC+2*index`; only a value greater than zero selects
  original. The sensor naming is a reference lead; this scoped signed query is
  what the executable proves. Fixtures use observer indices 0..23.
- Alliance checks current-house null first, then pointer identity, equal signed
  indices, index exactly -1, and the owner's `+0x5674` bit mask. The shift count
  uses x86 low five bits, including for other negative/large fixture indices.
- The display-type getter always queries alliance first. It returns original
  actor type `+0x5AC` only for alliance true and argument **low byte** zero;
  otherwise it returns `+0x40C`. The DrawIt caller's argument 1 always selects
  `+0x40C`, but still performs the house query.
- The complete ordinary drawing caller now accepts these timer values and calls
  its timer decoration only after Foot decoration. Layer exactly 5 returns
  before either. Earlier nondeployer/nonbridge/no-flag and ordinary cell-light
  guards remain. Active decoration itself is a supplied boundary.

The native scoped-default helper returns typed field values, not original object
layout or heap ownership. Original block write order/width/value and untouched arena
bytes are audited; native object layout/store order is not claimed for that helper.
Full stock HTNK type loading, `+0xBA6`/voxel/model metadata, construction services,
disguise creation/lifetime, observer setup, fog and discovery remain dependencies.

## Evidence and reproduction

Accepted private receipts: `private/unit-draw-1006/type-state-v1/` and
`private/unit-draw-1006/caller-state-v1/`, each with `expected.json`, `report.json`,
`native-replay.json` and `sanitize-replay.json`. Earlier caller-v3 evidence retains
its earlier source identity; it was not relabeled after the caller dependency change.

| New matching cases | Count |
| --- | ---: |
| Owner helper flags/mode/current identity | 250 |
| Alliance helper indices, shift wrapping and sentinels | 1,936 |
| Display getter low argument byte and house query | 640 |
| Eight scoped constructor blocks across clocks | 139 |
| Signed phase window and owner/disguise paths | 10,764 |
| Wrapped timer comparison before subtraction | 2,662 |
| Duplicate cell getter and signed observer counters | 672 |
| Full caller timer after Foot/layer-5 skip | 1,331 |
| Full caller with actual nested type/house/cell selection | 2,048 |
| **Total** | **20,442** |

**20,304 callable roots** and **1,112 constructor blocks** are audited. Complete
caller ESP/return/callee-saved guards, immutable fixture arenas/table, allowed
external writes, registry capacity tails and ordered service/write events remain
enforced. Predicate/house routines perform no fixture/image writes. Original
instructions are unchanged. Receipts pin exact engine, original/source inspection,
all relevant native/oracle sources and original fingerprint; rebuilt runners are
recorded separately. Eight new receipt/runner guards pass.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/python tools/verify_unit_type_visibility.py \
  --exe private/official-1006-probe/game.exe
build/tools-env/bin/python tests/compare_unit_type_visibility.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/unit-draw-1006/type-state-v1/expected.json \
  --report private/unit-draw-1006/type-state-v1/NEW-REPLAY.json
# Add both for the sanitizer replay:
# --native build/sanitize/unit-type-visibility-vectors
# --caller-native build/sanitize/unit-draw-caller-vectors
# Fresh original execution requires authorized Mac host JIT context:
build/tools-env/bin/python tests/compare_unit_type_visibility.py \
  --exe private/official-1006-probe/game.exe --output private/unit-draw-1006/NEW-TYPE
build/tools-env/bin/python tests/compare_unit_draw_caller.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/unit-draw-1006/caller-state-v1/expected.json \
  --report private/unit-draw-1006/caller-state-v1/NEW-REPLAY.json
./run.command --crossing-demo
```

Normal/sanitizer builds, CTest, all **224 Python tests**, source/diff audits,
headless crossing and actual SDL crossing pass. SDL mouse selection/right-click
and 79 samples / 78 updates retain 22 occluded samples, 150 maximum hidden pixels,
fresh final/no trail, bypass, offscreen/partial clipping and camera return. Those
checks demonstrate unchanged milestone 20 integration, not use of the new kernel.
Broad milestone-20 numeric/surface suites were not repeated for this unused
checkpoint. Only Apple Silicon macOS is tested; no Windows task was contacted.

## Accounting and next dependency

Fresh new generation: 6.094 s driver / 5.351 s original / 0.256 s native. New
normal/sanitizer replay: 0.737/0.969 s driver, 0.229/0.442 s native. Fresh caller
regression: 2.418 s driver / 1.991 s original / 0.183 s native; replays 0.441/0.647 s
driver. CTest totals: 0.06/0.31 s; Python discovery 0.350 s. Actual SDL crossing
took 1.321 s with authorized desktop access. Initial normal/sanitizer build and
headless crossing elapsed measurements are unavailable. No accepted fresh run
failed. A harmless `crossing-check --help` probe treated `--help` as a data path
and refused it; the documented data/output invocation passed. An inspection lead
started inside an instruction; it was discarded, and complete aligned constructor
inspection plus explicit block-boundary validation was used before execution.
No game playtest repair was needed. First inherited continuation clock: 05:08:21
UTC; the private checkpoint records the closing time. Full inherited delivery
elapsed is unavailable. No new caching or coordination infrastructure was added.

Next recover the selected HTNK type/model metadata and ordinary voxel child
dispatch `0x6FF690`, nesting the established numeric/key/staging/surface routines
where appropriate. Integrate only after those supported boundaries are verified.
Keep moving/turning past scenery and changing current-cell light as the observable
delivery. Full constructor/ownership, Foot/timer decorations, outer scheduling,
camera inverse, fog/UI and whole-frame parity remain separate open work. The full
base RA2/YR goal remains active and incomplete. This is a locally verified recovery
checkpoint, not independent acceptance.
