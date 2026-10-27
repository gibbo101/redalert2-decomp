# Supplied RA2 1.006 ordinary Unit model-loading protocol

October 15, 2026, after `1781c87`. **2,391 fresh original/native comparisons**
and normal/ASan/UBSan replays pass. The complete original model root executes in
the ordinary UnitType/nonzero-Turret/TurretCount-zero domain, with actual kind,
multiple-turret and VXL section getters. File, heap, parser and construction
services remain supplied. The new portable helper is **unwired**; this is another
prerequisite in the healthy Rhino drawing delivery, not a new gameplay milestone.

## Identity and reference leads

Rehashed both `private/official-1006-probe/game.exe` and the approved private
Windows copy `private/windows-baseline-20261014/game.exe`. Both are 4,485,392
bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 patch lineage and reported no-CD modifications
remain separate facts; pristine authenticity is not established. The transfer
was already complete. No new transfer, Windows action, source-install/disc write
or system change occurred.

Consulted pinned recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439`,
`docs/voxels.md` and LICENSE, plus YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88`, `ObjectTypeClass.h`,
`TechnoTypeClass.h` and `UnitTypeClass.h`. The names LoadVoxel, Main/Turret/Barrel
and ImageFile suggested a type-level loading protocol. Exact base strings,
root operands, actual UnitType vtable and execution verify the associations below.
YR layouts/addresses and generated recomp code are not the oracle. No upstream,
header, generated or lifted game code was incorporated; no dependency or notice
changed. The inspected recomp MIT grant excludes generated game code.

## Complete root and selected protocol

`tools/verify_unit_models.py` pins **four complete routines / 836 instructions**:

| Routine | Patched range |
| --- | --- |
| Model-loading root | `0x5D6730..0x5D72A6` |
| Actual UnitType kind slot `+0x2C` | `0x70B5E0..0x70B5E5` |
| Multiple-turret predicate | `0x6DF680..0x6DF68D` |
| VXL section getter | `0x719860..0x719881` |

The root is completely decoded from its aligned entry through its return;
execution covers the selected branch. It reads a supplied image-base string at
type `+0x1C8`, type Turret byte `+0xAAB` and count `+0x704`. The actual kind leaf
returns 40 and the actual predicate tests signed count >0. These fixtures use
count zero and Turret one. They do not prove Image initialization, Image INI
loading, stock count/offset defaults or whole type construction.

`src/assets/UnitModels.*` uses resource tokens and callbacks, with no SDL, guest
CPU or Windows runtime dependency. It recovers the following decisions:

- Open base `.VXL`; test availability's low byte. Missing body sets failure.
  A present VXL destroys/frees the previous VXL, allocates and constructs its
  replacement, then stores the returned record. A null record or nonzero error
  byte sets failure. Construction sees the previous type slot until that store.
- For each present VXL, open its `.HVA` without a separate availability query,
  destroy/free/replace the previous HVA, and inspect its error byte. A valid HVA
  obtains VXL section zero and passes section dword `+0x0C` to the supplied
  association service. Preserve file cleanup order. The body VXL file stays
  alive until the root's final cleanup.
- Continue later loading even after failure. The ordinary turret is
  `%sTUR.VXL/HVA`, stored at `+0xB8/+0xBC`; barrel is `%sBARL.VXL/HVA`, stored
  at `+0xC0/+0xC4`. Body uses `+0xB0/+0xB4`. Missing optional VXL files do
  **not** set failure or clear existing records. Preserve repeated kind/count
  queries and the original order of destruction, allocation, stores and cleanup.
- On failure, destroy/free/zero nonnull body VXL/HVA and ordinary turret VXL/HVA.
  **The ordinary failure branch retains the barrel records and all four caches.**
  Retained barrel records can be previous records or newly loaded records.
- On success, initialize the maximum from body section zero's first dimension,
  then scan all body sections' three unsigned dimension bytes. Repeat the section
  getter whenever the candidate is greater than **or equal to** the current
  maximum. Clamp to at least eight and store `+0x1BC` before cache cleanup.
- Free each cache pointer, including null, in `+0x214/+0x228/+0x23C/+0x250`
  order. For each, zero dwords at relative 0/4/8, byte at `+0x0C`, then dword at
  `+0x10`; preserve the intervening three padding bytes. Native record layout is
  portable and does not claim original heap or padding layout.

The native boolean return reports the modeled success/failure decision; it is
not a claim about the original root's return register. Empty/overlong image names,
path separators/colon/NUL, absent Turret and nonzero turret counts are native
domain/safety refusals, not recovered malformed-input behavior. Services and
observers must not mutate type inputs; exception unwinding/ownership is unverified.

## Fixtures, original execution and remaining services

The original runs with an immutable supplied type arena except declared output
fields, positive section counts (one through six), valid descriptor arrays and
supplied error bytes. The actual VXL getter reads those arrays; their parsing,
allocation and construction are not original execution in this suite. File
objects, availability, CRT filename formatting, allocation/destruction, VXL/HVA
constructors and HVA association are bounded services. No actual filesystem or
Win32 API executes in the oracle. Actual optional filenames and call arguments
are checked before the services return.
Constructor services return the supplied allocated token; full constructor
results and allocation ownership remain outside the claim.

A null VXL followed by a valid HVA would dereference through a null descriptor
record; these fixture combinations are refused rather than hidden by a null
getter stub. Invalid nonnull VXL records can still have supplied descriptor arrays;
this is a protocol fixture, not a claim about a real failed parser's allocation.
Numbered turrets, nonturret alternate images, aircraft, arbitrary invalid records,
real allocation failure consequences and actual stock construction remain open.

| Fresh matching scenarios | Count |
| --- | ---: |
| Every existing-part mask and file-availability mask | 512 |
| Every allocation mask, with empty/full prior records | 128 |
| Every parser-error mask, with empty/full prior records | 128 |
| High-bit availability values and low-byte decisions | 343 |
| Every dimension byte on each of three axes | 768 |
| Multi-section maxima, names, cache words/flags and ordering | 512 |
| **Total** | **2,391** |

There are **20,628 actual section getter calls**, **10,219 actual kind calls**,
**5,437 actual count predicates**, **50,364 ordered type stores**, **116,875
supplied service calls** and **21,895 guarded host stack writes**. Every callable
root checks original ESP, return address, caller tail and callee-saved registers.
Execution outside the declared original routines/services is refused. Original
writes are restricted to declared type fields and stack scratch; complete arena
snapshots protect other fields, descriptors, cache padding and capacity records.
Host service writes are restricted separately to bounded filename stack outputs.
No instruction bytes are modified. Traces compare constructor-visible old slots,
ordered services/stores, filenames, getter calls and final records, not just values.

## Reproduction and delivery checks

Current receipts: `private/unit-draw-1006/models-v3/{expected,report}.json`,
`native-replay.json` and `sanitize-replay.json`. They pin the exact engine/profile,
complete inspection and relevant source identities. Rebuilt runner hashes are
recorded separately. Earlier successful v1 evidence is preserved with its original
source identity; it is not relabeled as the strengthened result.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/python tools/verify_unit_models.py \
  --exe private/official-1006-probe/game.exe
build/tools-env/bin/python tests/compare_unit_models.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/unit-draw-1006/models-v3/expected.json \
  --report private/unit-draw-1006/models-v3/NEW-REPLAY.json
# Add --native build/sanitize/unit-model-vectors for sanitizer replay.
# Fresh original execution requires the authorized Mac host JIT context:
build/tools-env/bin/python tests/compare_unit_models.py \
  --exe private/official-1006-probe/game.exe --output private/unit-draw-1006/NEW-MODELS
./run.command --crossing-demo
```

Normal/sanitizer builds, nine native model profile/path guards, **283 Python
tests**, **9 normal / 8 sanitizer CTest checks**, source/diff/link audits and
actual SDL input/crossing pass. SDL retains 79 samples / 78 updates, 22 occluded
samples / maximum 150 hidden pixels, no trails, cache bypass, partial/offscreen
clipping and camera return. This checks the existing milestone 20 runtime; the
new helper remains unwired. Broad unrelated numeric suites were not repeated.
Only Apple Silicon macOS is tested; no whole-frame or full-game parity claim.

## Accounting and next work

This continuation inherits the previous model discovery starting 07:01:34 UTC;
the private checkpoint records closing time. Full inherited delivery time is
unavailable. Timed normal builds took 5.02 s and 3.18 s after the input fix;
sanitizer builds took 6.54/2.19 s plus 3.55 s configuration. Fresh final external
driver time was 7.37 s; detailed driver/original/native costs were
**7.116/6.648/0.078 s**. Other replay/check/SDL timings are in the private logs and
checkpoint. These measurements sometimes contended and are not FPS measurements.

No original/native numeric mismatch occurred. A direct unittest module invocation
used the wrong import path; running the script/discovery passed. After strengthening
fixtures, the first native runner refused high-bit unsigned availability inputs
because its input field was signed. That discarded attempt took 7.01 s. Correcting
the test protocol to uint32 and generating fresh v3 evidence fixed it without
changing model-loading behavior. An earlier successful v1 was strengthened after
review to defer the native type-slot assignment until after constructor callbacks,
matching the original store order; v3 compares the old slot explicitly. No game
playtest repair, extra workers or cache infrastructure was introduced.

Next verify Image/count/offset defaults and required neutral actor/type inputs,
then combine the established caller, voxel/cache/raster/staging/shadow/final
surface and Foot depth children before runtime wiring. Keep moving/turning past
scenery while current-cell light changes as the observable delivery. Full type/
actor construction, ownership, decorations, outer scheduling, camera/fog/UI and
whole-frame parity remain open. Full base RA2 then YR stays active and incomplete.
This is locally verified work, not independent acceptance.
