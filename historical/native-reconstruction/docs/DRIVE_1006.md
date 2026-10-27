# RA2 1.006 Drive, curves, timing and targeting migration

October 14, 2026. Ivalice / Apple Silicon macOS. This extends the identity/Facing
checkpoint committed as `291e30b`; [BASELINE_1006.md](BASELINE_1006.md) records the
successful supplied-patch materialization and approved private Windows transfer.
This is a bounded research-profile migration. The application and prepared inputs
still select the retained disc profile; presentation/lifecycle and effective asset
precedence require migration before patched runtime promotion or milestone 20.

## Exact inputs and reference leads

| Profile | SHA-256 |
| --- | --- |
| Allied-disc GAME.EXE | `135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743` |
| Supplied RA2 1.006 patch output | `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f` |

The patched input is `private/official-1006-probe/game.exe`, byte-identical to the
approved Windows engine. Both embed version 1.08. Hashes and supplied-patch lineage,
not version strings or upstream addresses, select the profile. Sources remain
read-only; no patch materialization, transfer or original-game launch was repeated.

Consulted [REFERENCES.md](REFERENCES.md)'s binary/class and testing entries,
redalert2-recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439`, `docs/testing.md`
(original versus lifted execution and evidence boundaries), and pinned YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88`, `DriveLocomotionClass.h` for interface
vocabulary. Hypothesis: locate Drive by RTTI and virtual slots, then independently
inspect the patched caller/data graph and execute the existing bounded domain.
Reference gameplay, YR offsets and replacement host timing are not our oracle.
The existing MIT/generated-game-code exclusion and YRpp no-incorporation boundary
remain in force. No upstream code, header or generated output was incorporated.

## Inspected mappings and duplicate-data resolution

Normalized instruction prefixes produced leads only. The patched binary contains
both Drive and Ship implementations with similar routines and duplicate streams.
The `DriveLocomotionClass` RTTI complete-object locator specifies interface offset
4, and that interface's process/Move_To/Stop_Moving slots select the first family.
The other vtable links to `ShipLocomotionClass`; it is not selected for the Rhino.
Actual Drive preparation/advance operands point to transition table `0x7A0180`
and raw descriptors `0x7A00A0`. Those six descriptors point to the first streams.
A byte match alone did not decide which copy to accept.

| Boundary | Disc VA | Supplied 1.006 VA |
| --- | --- | --- |
| Drive interface vtable | `0x78B4D4` | `0x7A04CC` |
| Move_To / Stop_Moving | `0x49FA00` / `0x49FAC0` | `0x49FE30` / `0x49FEF0` |
| Full Process / advance / preparation | `0x4A01C0` / `0x4A0BD0` / `0x4A2240` | `0x4A05F0` / `0x4A1000` / `0x4A2670` |
| Track coordinate/facing transform | `0x4A4310` | `0x4A4740` |
| Current speed / percentage setter | `0x4C95C0` / `0x4C2910` | `0x4C9B10` / `0x4C2DF0` |
| Type speed / INI numeric block | `0x6CE2B0` / `0x6D2021..0x6D2061` | `0x6D8E90` / `0x6DCC01..0x6DCC41` |
| Full Unit turret update | `0x6F03D0` | `0x6FB890` |
| Bearing / slope helper | `0x5CAC70` / `0x4BA120` | `0x5D2730` / `0x4BA600` |
| Coarse clock / complete wait | `0x68F980` / `0x53E660` | `0x69A430` / `0x540960` |
| Skirmish setup block | `0x53DEF2..0x53DF16` | `0x54000E..0x540032` |
| Transition / raw descriptors | `0x78B188` / `0x78B0A8` | `0x7A0180` / `0x7A00A0` |
| Frame counter | `0xA2894C` | `0xA40D2C` |

`tests/movement_profiles.py` lists explicit fixture addresses. It has no general
relocation offset. `tools/verify_movement_mapping.py` checks **22 complete ranges /
5,571 instructions**, including the full Process/advance/preparation/turret/wait
ranges and the isolated loader/slider/setup blocks. It checks instruction shape,
relative internal branches, address consistency, fixture-profile operands and
remaining encoded bytes. The skirmish setup's local stack slot moves from +0x38
to +0x14; this is recorded separately from address changes. Referenced external
routines and unexecuted branches do not acquire parity from structural similarity.

Nine constant/table ranges match byte-for-byte, including bearing/table step,
square root, reciprocal/arrival constants, stop cap and conversion control word.
All 64 transition entries, six raw descriptors' index fields and **269 points
including terminators** match. The patched stream VAs are `0x79EA60`, `0x79EB80`,
`0x79ED00`, `0x79EF98`, `0x79F170`, `0x79F458`. The native test runner uses the
retained hash-checked disc executable explicitly via `--native-data-exe`; each
patched run independently rechecks these table/mapping identities before execution.
Its derived direction file remains the verified disc file. No mixed profile has
been enabled in the application, data readers or preparation tools.

## Executed evidence and audit scope

Fresh unchanged-original runs pass on **each engine**:

| Suite | Comparisons | Boundary |
| --- | ---: | --- |
| Movement | 30,608 | 144 flat straight-drive traces and speed conversions |
| Curves | 48,240 | 304 traces, every direction pair, stops, replacements and Passive guard |
| Timing/targeting | 29,627 | Clock remaining/waits, bearings/bin boundaries and turret sequences |
| **This migration slice** | **108,475** | All matched |

Together with the separately verified 16,598 Facing results, the migrated movement
family totals **125,073 comparisons per executable profile**. These are bounded
state/case comparisons, not whole-game fidelity or original Windows recordings.
The native algorithms require no change: original truncation/float32 interpolation,
seven-unit accumulator, stop credit, committed stock Rhino curves, destination
bearings, no-combat turret branch and skirmish 16 ms clock policy are preserved.

The existing flat-world map/admission/occupation/getter/mission services remain
explicit fixtures; the pathfinder returns no route and tests supply queues. Timing
uses deterministic timeGetTime/Sleep and a presentation-wait recorder. Complete
original Drive, original arithmetic/helpers and complete turret/wait routines run;
no instructions are patched. The numeric speed/setup tests execute named blocks,
not full INI parsing or global match scheduling. [MOVEMENT.md](MOVEMENT.md),
[CURVES.md](CURVES.md) and [TIMING_TARGETING.md](TIMING_TARGETING.md) retain their
domains and service boundaries.

Both profiles now audit root return addresses, caller-owned stack after consumed
arguments, ESP, callee-saved registers, twelve fixture-edge canaries and emulated
stores into read-only image sections. Drive reuses a consumed argument slot;
argument-slot immutability is not asserted. Isolated timing/speed blocks are not
whole callable ABI tests. Full actor/type/cell arenas and ordered native/original
writes remain outside this movement suite's comparison. Lifecycle/occupation's
stronger audits are retained independently and are not silently weakened.

Fresh evidence is isolated under `private/migration/{allied-disc,supplied-ra2-1006}/`
with `movement`, `curves` and `timing-targeting` subfolders. Each has `expected.json`
and `report.json`; original historical disc reports/expectations are preserved.
Reports pin both executable inputs, native runner, prepared direction data where
used, mapping tool and oracle sources. Source/input changes during a run reject
its evidence. Cached replay verifies the fresh report's expectation fingerprint
and source/profile/data identities, then runs native vectors only. Replays write
separate reports and never replace the fresh receipt. Sanitizer replay is native
regression evidence, not a second original execution.

Seven synthetic guard tests cover unknown hashes, explicit patched selection, the
retained disc default, unmapped addresses, native data identity, stale/tampered
cached evidence and original-receipt preservation. Other Oracle users still default
to the disc-only gate; opting into a movement profile does not migrate a presentation/lifecycle subclass.

## Reproduce and try it

```sh
./build.command
./test.command --data-dir "$PWD/private/game"
./run.command
build/tools-env/bin/python tests/test_movement_profiles.py
build/tools-env/bin/python tools/verify_movement_mapping.py \
  --disc private/disc-allied/game.exe --patched private/official-1006-probe/game.exe
build/tools-env/bin/python tests/compare_movement.py \
  --exe private/official-1006-probe/game.exe --native-data-exe private/disc-allied/game.exe
build/tools-env/bin/python tests/compare_curves.py \
  --exe private/official-1006-probe/game.exe --native-data-exe private/disc-allied/game.exe
build/tools-env/bin/python tests/compare_timing_targeting.py \
  --exe private/official-1006-probe/game.exe --native-data-exe private/disc-allied/game.exe
# Retained original regressions: use --exe private/disc-allied/game.exe,
# without --native-data-exe or --expectations.
# After README's headless sanitizer build, for example:
build/tools-env/bin/python tests/compare_curves.py \
  --exe private/official-1006-probe/game.exe --native-data-exe private/disc-allied/game.exe \
  --native build/sanitize/movement-vectors \
  --expectations private/migration/supplied-ra2-1006/curves/expected.json \
  --report private/migration/supplied-ra2-1006/curves/sanitize-report.json
```

Use the authorized Mac JIT context for original Unicorn execution. Native replay
requires no original execution. Mapping outputs refuse overwrites; choose a fresh
private/build output path if recording another mapping report. Private discovery,
operand/RTTI inspection and mapping evidence remain in `private/patch-inspection/`.
No proprietary code/data, disassembly, environments or binaries are tracked/shipped.

All 108,475 patched expectations also pass on ASan/UBSan native vectors without
diagnostics. The retained 424-case composition oracle passes after the shared
flat-depth fixture change. Build, native synthetic/import/preparation tests, owned
render/light/scenery checks and both 170-frame SDL regressions pass on disc inputs.
These native/SDL checks establish integration only.

The visible prototype is unchanged: original map/terrain/scenery/Rhino, selection,
turns, bounded unobstructed movement and its existing lighting/caches still work on
retained inputs. Direct routes/clearance, input, target lifetime, visibility, scene
scheduling and full-frame integration remain adapters or open. This checkpoint
adds no pathfinding, combat or Windows/Linux native support and makes no new
original-game observation claim. Sources and Outpost 2 remain untouched.

The subsequent [PRESENTATION_1006.md](PRESENTATION_1006.md) checkpoint verifies
the lighting/palette/depth primitives. Next migrate remaining raster/composition/
light/cache/scenery/occupation/lifecycle profiles, preserving their stronger audits,
then establish original asset precedence
and matching prepared inputs. Patched native integration and runtime promotion
follow those checks. Ground-layer traversal/draw eligibility remains milestone 20;
YR 1.001 follows base RA2.
