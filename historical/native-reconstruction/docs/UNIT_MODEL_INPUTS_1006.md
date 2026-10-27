# Supplied RA2 1.006 Image, turret count and offset inputs

October 15, 2026, after `ce464a3`. **4,322 fresh original/native results** and
normal/ASan/UBSan replays pass. Exact base Image/count/offset associations and
scoped defaults now resolve supplied HTNK inputs to **HTNK / 0 / 0**. The patched
GameAssets reader uses this result to choose its bounded part names and reject
unrecovered image/count/offset profiles. The complete model-loading protocol and
new Unit drawing callers remain unwired; this is a prerequisite checkpoint in
the same healthy Rhino drawing delivery.

## Identity and reference hypothesis

Exact supplied engine: 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`,
`private/official-1006-probe/game.exe`. The approved private Windows copy remains
the matching baseline. Embedded 1.08, supplied 1.006 patch lineage and reported
no-CD provenance remain separate facts; pristine authenticity is not established.
No new transfer, Windows task/source-install/disc write or system change occurred.

Consulted pinned recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439`,
`docs/voxels.md`/LICENSE, and YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88`, `ObjectTypeClass.h` ImageFile and
`TechnoTypeClass.h` TurretCount/TurretOffset. The hypothesis was that the type
image chooses model stems and art sections while count/offset select ordinary
versus alternate drawing. Exact base operands, strings, selected stores and
execution verify the associations below. No YR address/layout, header code,
generated recomp output or other upstream code was adopted. No new dependency
or third-party notice was needed; generated game code is outside the inspected
recomp MIT grant.

## Recovered fields and original boundaries

`tools/verify_unit_model_inputs.py` reuses the aligned complete parent/helper
inspection in [UNIT_METADATA_1006.md](UNIT_METADATA_1006.md). It adds **four
complete routines / 483 instructions** and **11 aligned scoped blocks**:

| Routine | Exact patched range | Execution |
| --- | --- | --- |
| ReadString | `0x50E9A0..0x50EB33` | Complete, decoded hot/missing index fixtures |
| Byte trim | `0x6EEF10..0x6EEF76` | Actual nested routine |
| CRT bounded byte copy | `0x7823D0..0x7824CD` | Actual nested routine |
| GetInt | `0x50D7F0..0x50D9C2` | Actual missing-entry fallback branches only |

The complete integer routine is inspected, but **present integer text decoding
does not execute**. The present-value scoped cases use a read-only service with
checked section/key/fallback arguments. No decimal/hex/overflow/CRT scanning
claim follows from these cases. Missing entries use the actual routine, including
CRC setup, and preserve the complete signed fallback word.

| Field | Exact base association | Scoped default / stock result |
| --- | --- | --- |
| Image | Rules `Image`, ObjectType `+0x1C8`; type-ID section `+0x24` | Fixed 25-byte ID-field copy / HTNK |
| TurretCount | Rules `TurretCount`, `+0x704` | 0 / 0 |
| TurretOffset | Art `TurretOffset`, `+0x63C`; **Image-named section** | 0 / 0 |

The Image constructor block copies all 25 bytes, including padding after NUL,
from the supplied type-ID field. It is not a string normalization operation.
The preceding AbstractType ID construction does not execute here. The copy block
also executes four original vtable stores; their order/values are checked as
original-only assertions, without claiming native vtables or whole construction.
Count/offset execute actual zero-register setup and selected constructor stores.
Aligned parent inspection finds no intervening explicit EBX assignment; EBX
preservation across omitted constructor children remains an ABI boundary.

ObjectType's selected Image read first copies the previous string to a separate
parent-frame fallback buffer, then calls actual ReadString with capacity 25.
Its field-address instruction and post-push-EDI read block execute separately
with supplied live registers/frame. Integer read/call/store blocks execute in
the original rules-then-art order. The art section is the newly read Image,
including an empty result; it is not unconditionally the type ID.

## Exact decoded-string behavior

`src/assets/UnitModelInputs.*` keeps this boundary separate from INI text/index
construction and runtime resource loading:

- Invalid/null name/output conditions or signed capacity below two return zero
  without changing the output. Native valid-span/name flags model this bounded
  fixture boundary; arbitrary malformed pointers are not supported.
- A missing/null decoded entry selects the supplied fallback. A present empty
  string is still a present value. If both value and fallback are null, write
  only output byte zero and return zero; the remaining bytes stay unchanged.
- Otherwise perform bounded NUL-padded copying, force the last output byte to
  zero, trim, and return the resulting byte length. Capacity truncates before
  trimming. Output padding and all unchanged bytes are compared, not just text.
- The original trim tests **unsigned bytes <=32**, including control bytes.
  It copies the first nonblank suffix, including its terminator, down to the
  beginning, then retains the **old first-nonblank pointer** as a live guard in
  the trailing loop. Do not replace it with a general whitespace trim. For example,
  decoded `"  A   "` yields `"A "` in a sufficiently large buffer because that
  old pointer becomes NUL before the last space is removed. High-bit bytes are
  preserved as nonblank. Stale output bytes after the moved terminator remain
  observable and are included in comparisons.

Native source/destination aliasing is outside this immutable-input interface.
The existing native INI text parser still strips comments/normalizes text and
the integer reader still uses its existing host parser. They do not become
original parser implementations merely by calling the recovered decoded-string
helper. The owned stock fields are absent, so their original fallback paths can
be verified without claiming general text parsing.

## Evidence, runtime use and limitations

| Fresh matching scenarios | Count |
| --- | ---: |
| Byte values, bounded copy/trim and padding | 1,280 |
| Leading/trailing lengths and live old-pointer guard | 961 |
| Missing records, null/invalid arguments, short/negative capacities, fallbacks | 288 |
| Arbitrary decoded bytes and bounded truncation | 512 |
| Fixed constructor byte copies and scalar defaults | 256 |
| Image read, integer field associations and actual missing fallbacks | 1,024 |
| Owned HTNK decoded absences/native reader | 1 |
| **Total** | **4,322** |

There are **3,050 audited callable roots**, including nine inherited CRC setup
calls, and **5,892 scoped blocks**. **4,066 actual ReadString calls**, **1,026
actual missing GetInt calls**, **1,024 supplied present integer calls** and
**14,362 guarded type stores** are recorded. Complete roots check return address,
ESP, caller tail, callee-saved registers, immutable decoded indexes/fallbacks and
bounded output writes. Scoped blocks check ESP/local-frame bounds, outer guard,
complete arena/global-INI snapshots and exact scalar/default/vtable writes.
Execution outside declared routines/blocks is refused; no instruction is patched.
Final string bytes are compared; native internal byte/dword store widths and
aliasing are not claimed equivalent to the CRT's implementation.

Current receipts: `private/unit-draw-1006/model-inputs-v5/`, both replays and actual
SDL. Successful pre-wiring v3 and pre-API-refinement v4 receipts remain preserved
with their earlier source identities.
Final receipts also pin GameAssets source, but do not make native SDL an original
whole-frame oracle. The unchanged earlier model protocol replays **2,391 results
on each build**, using `models-v3/post-inputs-*-replay.json`, without fresh original
execution or changed expectation identities.

Patched-only GameAssets reads these inputs, requires case-insensitive HTNK image,
zero count/offset, and derives body/TUR/BARL names. Other profiles are safety/domain
refusals. The disc path retains its earlier offset check and names. Actual file/
VXL/HVA parsing and ownership are still the existing bounded native adapters;
the complete [model protocol](UNIT_MODELS_1006.md) is not wired. Full type/actor
construction, neutral status inputs, nested drawing children and frame parity
remain open.

Normal/sanitizer builds, **290 Python tests**, **9 normal / 8 sanitizer CTest
checks**, source/diff/link audits and owned-data inspection/presentation checks
pass. Native model guards now also test five unsupported input profiles, stock
acceptance and an Image-selected art section. Actual patched SDL selection/right-
click crossing passes: 79 samples / 78 updates, 22 occluded samples / maximum 150
hidden pixels, no trails, bypass, clipping and pan return. This validates native
integration only. Only Apple Silicon macOS is tested.

## Commands, accounting and next work

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/python tools/verify_unit_model_inputs.py \
  --exe private/official-1006-probe/game.exe
build/tools-env/bin/python tests/compare_unit_model_inputs.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/unit-draw-1006/model-inputs-v5/expected.json \
  --report private/unit-draw-1006/model-inputs-v5/NEW-REPLAY.json
# Add --native build/sanitize/unit-model-input-vectors for sanitizer replay.
# Fresh original execution requires authorized Mac host JIT context:
build/tools-env/bin/python tests/compare_unit_model_inputs.py \
  --exe private/official-1006-probe/game.exe --output private/unit-draw-1006/NEW-MODEL-INPUTS
./run.command --crossing-demo
```

This continuation started 07:20:16 UTC; the private checkpoint records closing
time. Full inherited delivery time is unavailable. Normal builds: 4.86/9.10/7.40 s;
sanitizer: 4.67/7.42/5.84 s. Final fresh external time: 4.84 s;
driver/original/native: **4.660/3.859/0.054 s**. Python discovery: 1.51 s;
final SDL: 2.33 s. Test/replay times are in private logs and checkpoint.
Concurrent checks sometimes contended; none of these are FPS measurements.

Two discarded attempts are retained: the initial selected Image block included
an extra parent push, so its supplied live-frame INI pointer was wrong (3.48 s).
Splitting field setup from the post-push frame fixed the fixture. The next private
INI reader refused valueless source lines (4.44 s); allowing those lines fixed
the research parser. Constructor results were also strengthened to read actual
stored scalar words rather than literal expected zeros before accepted evidence.
No native numeric mismatch or game playtest repair occurred. Fresh v4 was generated
after the runtime guard/source manifest change. Final v5 follows a review refinement
to carry the original signed capacity directly in the native API, rather than
mapping negative fixture capacities to an empty span; its negative cases now call
that signed interface directly. Neither earlier receipt was relabeled. No extra
workers, cache infrastructure, source/system or Windows changes were introduced.

Next verify remaining neutral actor/type fields, then nest actual Foot/base depth
and established caller/cache/raster/staging/shadow/final-surface children before
runtime drawing integration. Moving/turning past scenery while current-cell light
changes remains the observable delivery. Full base RA2 then YR is still active
and incomplete; this is local verification, not independent acceptance.
