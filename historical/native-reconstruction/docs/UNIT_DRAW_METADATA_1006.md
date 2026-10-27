# Supplied RA2 1.006 depth and bridge drawing metadata

October 15, 2026, after `bd59b6e`. **3,330 fresh original/native results** and
normal/ASan/UBSan replays pass. Five exact base-engine field associations and
scoped constructor defaults are verified. This is another prerequisite in the
same healthy Rhino drawing delivery; the new reader remains unwired.

**Stock HTNK sets `TooBigToFitUnderBridge=true`.** The previous final-surface
checkpoint's `+0xBAE=0` domain therefore does not establish the full stock Rhino
decision. Do not wire that zero-field profile as if it were stock. Recover its
predicate/contact selection and conditional two-part surface draw first.

## Identity and references

Rehashed both `private/official-1006-probe/game.exe` and the previously approved
private Windows transfer `private/windows-baseline-20261014/game.exe`: both are
4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 patch lineage and reported no-CD provenance remain
separate facts; pristine authenticity is not established. Neither source install,
disc, Windows task nor system configuration changed. No new transfer occurred.

Consulted pinned recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439`,
`docs/voxels.md`/LICENSE, and YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88`, `TechnoTypeClass.h` and
`UnitTypeClass.h`. Hypothesis: the ZFudge and bridge-size settings feed the
already recovered depth/surface callers. Exact base strings, operands, getter
targets and stores verify the names below. YR layouts and recomp output are not
the oracle. No upstream/header/generated or lifted game code was incorporated;
no dependency or third-party notice changed.

## Selected fields and defaults

`tools/verify_unit_draw_metadata.py` reuses the complete parent inspection from
[UNIT_METADATA_1006.md](UNIT_METADATA_1006.md): five complete helpers / 462
instructions and six aligned complete parent ranges / 5,181 instructions. It adds
**eight aligned scoped blocks / 46 instructions**, exact key strings, byte/dword
operands, getter calls and constructor register-dataflow checks.

| Base field | Offset | Read / store | Scoped default | Supplied HTNK |
| --- | --- | --- | ---: | ---: |
| ZFudgeCliff | `+0xB5C` | `0x6DD5ED / 0x6DD601` | 10 | 10 |
| ZFudgeColumn | `+0xB60` | `0x6DD607 / 0x6DD61B` | 5 | 8 |
| ZFudgeTunnel | `+0xB64` | `0x6DD621 / 0x6DD635` | 10 | 13 |
| ZFudgeBridge | `+0xB68` | `0x6DD63B / 0x6DD655` | 0 | 0 |
| TooBigToFitUnderBridge | `+0xBAE` | `0x70AC5E / 0x70AC8F` | 0 | 1 |

The first four fields call `GetInt` at `0x50D7F0`; the byte field calls actual
`GetBool` at `0x50F410`. This suite executes the integer read/call/store blocks
with a read-only service that checks original section/key/fallback arguments and
returns supplied decoded integers. **Original GetInt parsing does not execute.**
No inference from native `std::stoi` establishes original text/overflow/hex behavior.

The bridge-size block executes actual GetBool on supplied hot decoded indexes,
with original CRC/hot-key/locale-zero helpers. Its intervening `sete` writes
unrelated type `+0xBA9` from supplied ZF. That exact byte write is guarded as an
original-only fixture assertion, not newly modeled full type behavior.

Actual constructor setup `xor ebx,ebx`, `mov ecx,10` and the five selected stores
execute as separate blocks. Inspection establishes unchanged ECX from `0x6DA211`
through the four depth stores and unchanged EBX through the Unit byte store.
There is no explicit later EBX assignment in the inspected Techno constructor;
EBX preservation across its omitted child calls remains an ABI boundary.
These are scoped defaults, not whole constructor execution/post-construction proof.

`src/assets/UnitDrawMetadata.*` keeps selected values and callback order separate
from text parsing and renderer integration. Its native file reader uses the
existing INI parser. The owned fixture decodes the previously selected private
rules export, supplies decoded values to the original blocks, and compares the
native reader's HTNK fields. This proves the selected field associations and
results on those inputs, not original text parsing, archive loading or full type
construction. It changes no current GameAssets/Renderer behavior.

## Evidence and reproduction

| Fresh matching results | Count |
| --- | ---: |
| Scoped register setup and five defaults | 1 |
| Integer keys/fallbacks/ordered stores and actual boolean | 1,024 |
| Every first byte inside actual bridge-size loader | 1,024 |
| Missing section/key/record/text fallback bytes | 1,280 |
| Supplied HTNK decoded inputs / native reader | 1 |
| **Total** | **3,330** |

There are **9,992 audited scoped blocks**, **13,316 checked integer-service
calls** and **3,329 original-only `+0xBA9` writes**. Eleven inherited CRC setup
roots also execute with caller guards. Blocks preserve balanced ESP/caller tail,
check exact ordered external byte/dword writes, protect the surrounding actor/type
arena and global INI fixture, and leave instruction bytes unchanged. Integer
services write no guest memory. Full constructor order, mutable callback/alias
behavior, heap ownership and model associations remain outside the claim.

Receipts: `private/unit-draw-1006/draw-metadata-v2/{expected,report}.json`,
`native-replay.json` and `sanitize-replay.json`. They pin engine/profile, complete
parent/scoped inspection, relevant sources, supplied rules and expectations;
rebuilt runner hashes are separate. Seven receipt guard tests pass. The earlier
`draw-metadata-v1/` receipt is preserved with its earlier inspection identity.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/python tools/verify_unit_draw_metadata.py \
  --exe private/official-1006-probe/game.exe
build/tools-env/bin/python tests/compare_unit_draw_metadata.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/unit-draw-1006/draw-metadata-v2/expected.json \
  --report private/unit-draw-1006/draw-metadata-v2/NEW-REPLAY.json
# Add --native build/sanitize/unit-draw-metadata-vectors for sanitizer replay.
# Fresh original blocks need the authorized Mac host JIT context:
build/tools-env/bin/python tests/compare_unit_draw_metadata.py \
  --exe private/official-1006-probe/game.exe --output private/unit-draw-1006/NEW-DRAW-METADATA
./run.command --crossing-demo
```

Normal/sanitizer builds, **8 normal / 7 sanitizer CTest checks**, **269 distinct
Python tests**, source/diff/link audits pass. The preceding Foot-depth checkpoint's
actual SDL input/crossing check in this continuation remains unchanged runtime
evidence: 79 samples / 78 updates, 22 occluded samples / 150 maximum hidden pixels,
no trails, bypass, clipping and pan return. No new SDL or whole-frame claim is
made for this unwired metadata reader. Broad unrelated numeric suites were not
repeated. Only Apple Silicon macOS is tested.

## Accounting and next work

Normal/sanitizer builds: **4.05/3.40 s**. Fresh v2 external: 2.53 s; detailed
generation/native/replay times are retained in the private receipts. Test command:
1.58 s; sanitizer CTest: 1.32 s (external 1.82 s). Python discovery: 0.934 s
(external 1.74 s). This checkpoint began 06:41:44 UTC; the private accounting
records closing time. Full inherited delivery time is unavailable. Checks
sometimes contended; these are not FPS measurements.

No build, differential or game-playtest failure occurred. An initial discovery
slice began inside a constructor instruction; only aligned complete-parent
disassembly was used for the verifier and execution. The successful v1 evidence
was not relabeled after strengthening EBX inspection and replacing an unverified
`+0xBA9` name; v2 was generated afresh and replayed. No worker/coordinator/cache
infrastructure, Windows action or source/system changes were introduced.

Next recover stock nonzero bridge-size selection, its contact getter domain and
conditional split final draw. Then verify model/neutral actor associations and
nest caller/cache/raster/staging/surface children before runtime wiring. Keep
moving/turning past scenery and changing current-cell light as the observable
delivery. Full construction/ownership, decorations, outer scheduling, camera/fog/UI
and frame parity remain open. Full base RA2/YR stays active and incomplete; this
is locally verified work, not independent acceptance or a new gameplay milestone.
