# RA2 1.006 flat Unit shadow-key migration

October 14, 2026. Ivalice / Apple Silicon macOS.

**2,204 fresh protocol results pass on each engine**, including 129 complete masks/
crops. Both ASan/UBSan native replays pass; outputs equal the retained disc suite.

This checkpoint verifies the retained flat Unit seed/default, complete Foot
forwarding and selected owned shadow-mask domain from [SHADOW_KEYS.md](SHADOW_KEYS.md)
on separately hash-selected disc and supplied patched engines. Native algorithms
and prepared/runtime gates remain unchanged. Full actor, nonflat/status/airborne
behavior, original compressed pool/lifetime and whole-frame parity remain excluded.
This is an intermediate checkpoint toward the complete 1.006 baseline delivery.

## Identities and references

| Original engine | SHA-256 |
| --- | --- |
| Allied disc, embedded 1.08 | `135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743` |
| Supplied RA2 1.006 patch output, embedded 1.08 | `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f` |

Both are PE32/i386 at image base `0x400000`; the patched engine equals the
approved private Windows copy. [BASELINE_1006.md](BASELINE_1006.md) retains patch
lineage and no-CD provenance. This establishes neither a pristine installation
nor YR equivalence. Original execution remains private research-only Unicorn.

Consulted redalert2-recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439`,
`docs/voxels.md` (The path of one unit, Shadows, Cost) and LICENSE, plus YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88`, `Drawing.h`, `FootClass.h`,
`Interfaces.h`, `LocomotionClass.h`, `ObjectTypeClass.h`, `TechnoTypeClass.h`
and `GeneralDefinitions.h`. Names and interface/key descriptions supply leads.
Hypothesis: independently locate the exact patched Unit seed/default and Foot/
Drive dispatch, then compare the retained flat domain. No upstream/header/generated
code was incorporated. See [REFERENCES.md](REFERENCES.md).

## Inspected boundaries

`tools/verify_shadow_key_mapping.py` checks **13 ranges / 261 instructions**,
encoded operand differences, eight ordered SpeedType names, three INI associations
and actual Unit/Drive/Foot/parser dispatch. The profile adds **36 explicit mappings**
to its independently inspected staging ancestors. No blanket displacement or
installer/version label chooses addresses.

| Boundary | Disc VA | Supplied 1.006 VA |
| --- | --- | --- |
| Unit body-to-shadow extraction | `0x6F4327` | `0x6FF7F7` |
| Unit type/point seed and matrix call | `0x6F4D03` | `0x7001D3` |
| Crusher-dependent SpeedType default | `0x6FF65A` | `0x70ABEA` |
| Complete Foot shadow dispatcher | `0x4C94F0` | `0x4C9A40` |
| Complete Drive point / predicate | `0x53B250` / `0x53B570` | `0x53D1C0` / `0x53D4E0` |
| Unit model/cache/section caller, inspected | `0x6F5086` | `0x700556` |
| Complete enum parser / name getter, inspected | `0x482CC0` / `0x482D00` | `0x482F20` / `0x482F60` |
| Complete SpeedType INI helper, inspected | `0x46C000` | `0x46C400` |
| SpeedType / Crusher / BalloonHover associations | `0x6D03D8` / `0x6D2524` / `0x6D25A6` | `0x6DAFB8` / `0x6DD104` / `0x6DD186` |

The parser has several similar code prefixes. Actual SpeedType INI dispatch at
`0x46C042 → 0x46C442` selects `0x482CC0 → 0x482F20`. Its referenced table
`0x7BE9DC → 0x7D38A8` establishes Track=1 and Wheel=2 independently on both
engines. The Drive interface `0x78B4D4 → 0x7A04CC` has checked RTTI offset 4;
slots `+0x20/+0x28/+0x30` select predicate/matrix/point. Complete Drive matrix,
base pose and height conversion retain earlier verified ancestor ranges.

BalloonHover needs the full association beginning at `0x6D25A6`, not the historical
store fragment beginning at `0x6D25BA`. The read/call, intervening argument pushes
and field store at `+0xB1A` are inspected together. Full type constructors/INI
initialization, alternate predicates and original game observations remain excluded.

## Executed domain and guards

Preserve ten-bit extraction even from body key -1; Track/Wheel/BalloonHover keep
that seed, while tested alternate metadata packs five point-y-minus-16 bits.
Flat Drive packing and screen additions wrap at 32 bits. Crusher changes only
SpeedType sentinel -1: true gives Track=1, false Wheel=2. Foot requires a present
locomotor and predicate byte exactly 1, adjusts its copied location and forwards
all ten other arguments unchanged. Runtime remains healthy, flat, ground-relative
height-zero stock Track HTNK; metadata tests do not enable other locomotors.

| Retained behavior per engine | Results |
| --- | ---: |
| Unit seed branches and flat Drive keys/matrix bits | 1,502 |
| Crusher-dependent Unit SpeedType default | 24 |
| Complete Foot with real flat Drive predicate/point | 4 |
| Complete Foot with supplied virtual results/forwarding recorder | 544 |
| Selected owned masks/crops | 129 |
| **Behavior cases** | **2,203** |
| Protocol reset | 1 |
| **Protocol results** | **2,204** |

Per engine, **1,457 callable roots**, **3,545 blocks**, **eight guarded allocations**
and **785 supplied point writes** are checked. Key blocks audit ESP, their caller
guard and unrelated locals; actor/type/cell/
locomotor/interface records and existing heap inputs stay immutable. SpeedType
permits only its four-byte field store. Complete Foot calls audit return address,
caller-owned stack, ESP/callee-saved registers and input records/location. Supplied
point writes have explicit bounds, since Unicorn guest-write hooks do not observe
Python mem_write services. The wrapper/loader/pose/mask/crop paths retain ancestor
caller/input/heap checks. Ordered native/original writes and full actor arenas are
not compared. Logical snapshot identity and successful allocator services remain
supplied; original snapshot encoding, ownership/failure/eviction and lifetime are open.

An initial short probe correctly rejected an overly narrow matrix-output allowance:
the caller pushes its key pointer before calculating the output address, so the
actual 48-byte output begins at stack `+0x160`, not `+0x164`. The guard was corrected
from inspected instructions before fresh full generation. No original bytes were
patched. A private receipt-verifier filename typo failed once and was corrected;
it executed no originals and required no regeneration. Selected cases compare entire 65,536-byte masks and six crop fields,
including warm reuse across changed stencils. This establishes the stated bounded
routine domain, not complete Unit rendering or full-frame fidelity.

## Evidence and reproduction

Protected receipts/expectations/export inventories:

```text
private/migration/allied-disc/shadow-keys/
private/migration/supplied-ra2-1006/shadow-keys/
```

Fresh execution refuses existing receipts. Replay validates exact engine/profile,
oracle/mapping sources, both exporters/assets, retained render/raster files and
expectation fingerprint, and cannot replace original receipts. The raster exporter
supplies the body VXL explicitly; the historical shared export dependency is removed.
The recorded export inventory is broader than the one body VXL consumed here.
Earlier disc evidence is preserved. Ten synthetic profile/evidence guards pass.
Current receipt/source/native/input and cross-engine/retained-disc equality are
recorded in `private/migration/shadow-keys-checkpoint-verification.json`, generated
by `private/patch-inspection/verify-shadow-key-checkpoint.py`. Mapping receipt:
`private/patch-inspection/shadow-key-1006-mapping.json`. Sanitizer replays took
**3.18 s per engine**, including preparation/mapping/identity checks, in parallel.

```sh
build/tools-env/bin/python tests/test_shadow_key_profiles.py
build/tools-env/bin/python tools/verify_shadow_key_mapping.py \
  --disc private/disc-allied/game.exe --patched private/official-1006-probe/game.exe
# Current native replay; no original execution:
build/tools-env/bin/python tests/compare_shadow_keys.py \
  --exe private/official-1006-probe/game.exe \
  --native-data-exe private/disc-allied/game.exe \
  --expectations private/migration/supplied-ra2-1006/shadow-keys/expected.json
# After README's sanitizer build, add:
# --native build/sanitize/shadow-key-vectors
# --report private/migration/supplied-ra2-1006/shadow-keys/sanitize-report.json
./run.command --light-demo
```

On a checkout without receipts, omit `--expectations` for fresh original execution
in the authorized Mac JIT context. Patched research explicitly retains native disc
table inputs. No preparation table/dependency or runtime executable read is added.

Fresh original generation took **39.80 s disc / 42.19 s patched**; native result
comparison took **0.047 s / 0.048 s**. Whole fresh CLI time was **41.46 s / 44.26 s**
with the engines running in parallel. Timing is recorded in fresh reports (`original_generation_seconds`,
`native_comparison_seconds`) and private `fresh-timing.json` / replay timing files.
Original generation includes fixture initialization and expectation construction;
whole CLI time also includes mapping/preparation/export/identity checks. Parallel
engine runs can contend for CPU. Inherited implementation/complete delivery wall
time remains unavailable; do not infer it from these partial measurements. Native
runtime is unchanged; the build/owned-data/both 170-frame SDL checks completed at
the preceding cache checkpoint still cover this same native build. Complete applicable
coverage on promoted inputs remains required at the final migration delivery.

Next: related scenery/type/prop profiles, then occupation/lifecycle, archive precedence
and consistent prepared/runtime promotion. Only Apple Silicon macOS is tested.
