# Supplied RA2 1.006 Foot lit-part forwarding

October 15, 2026, after `1cbc04b`. **2,263 fresh original/native results** and
normal/ASan/UBSan replays pass. This is a prerequisite checkpoint for the same
healthy Rhino drawing delivery. The new helper is unused by Renderer; the
observable capability remains [milestone 20's crossing](CROSSING_1006.md).

## Identity and reference hypothesis

Rehashed `private/official-1006-probe/game.exe` and the approved private Windows
copy `private/windows-baseline-20261014/game.exe`: both are 4,485,392 bytes,
SHA256 `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 patch lineage and user-reported no-CD provenance
remain separate facts. Pristine authenticity is not established. No Windows task,
source installation, disc or system configuration changed.

Consulted redalert2-recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439`,
`docs/voxels.md` and LICENSE, and YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88`, `FootClass.h`, `TechnoClass.h`,
`LocomotionClass.h` and `Interfaces.h`. Hypothesis: Foot obtains a locomotor
screen offset before the Techno lit-part/cache child. Exact base instructions
establish the nine-argument signature; YR's ten-argument declaration was not
adopted. No upstream/header/generated or lifted code was incorporated.

## Complete boundaries and semantics

`tools/verify_foot_lit_draw.py` pins these aligned complete ranges:

| Boundary | Patched range | Instructions | Coverage |
| --- | --- | ---: | --- |
| Foot lit wrapper | `0x4C9880..0x4C9924` | 60 | Executed complete |
| Actual Drive zero Draw_Point | `0x53D4D0..0x53D4E0` | 6 | Executed complete |
| Matrix-copy helper | `0x58FE10..0x58FE26` | 10 | Inspected only |

Actual Unit vtable `0x7ADDF8 +0x3D8` selects Foot `0x4C9880`; actual Drive
interface `0x7A04CC +0x2C` selects `0x53D4D0`. Foot calls Techno `0x6D1D00`.
The Foot wrapper copies twelve matrix dwords inline before querying the optional
locomotor and copies the input point to a local. Nonnull actor `+0x564` queries
interface `+0x2C`, then adds its returned X/Y with 32-bit wrapping. All other
arguments are forwarded unchanged; the root returns with `ret 0x24`. Actual
Drive writes two zero dwords in order and returns the output pointer.

`src/render/FootLitDraw.*` models portable values, opaque model/cache identities
and read-only callbacks. Matrix copies preserve raw NaN payloads, infinities and
signed zero. Inputs and rectangles are immutable in this domain. No pointer
aliasing, object-layout, ownership or callback-mutation equivalence is claimed.

## Evidence and reproduction

| Fresh matching results | Count |
| --- | ---: |
| Actual Drive zero output and ordered two-dword writes | 81 |
| Complete Foot null/actual Drive/supplied offset, wrapping | 486 |
| Raw matrix bits and all forwarded arguments | 1,024 |
| Nested cache resets | 8 |
| Actual Foot and Techno cache hit/miss/bypass/invalid protocol | 664 |
| **Total** | **2,263** |

Audits cover **1,591 standalone callable roots**, **668 nested roots including
retained cache setup**, 242 supplied forwarding-point writes and 659 supplied
cache-service writes. Roots enforce caller stack/return/callee-saved guards,
immutable input arenas and allowed writes. The nested cases execute actual Foot,
optional actual Drive and the complete actual Techno lit-cache child together.
Healthy actor/type/model records and bounded render/snapshot/heap services remain
supplied. No new original voxel raster pixels, compressed pool or full Unit child
execute here. The inherited cache inspection reads the retained disc executable;
all new execution is patched-only. Receipts pin both inspection identities,
relevant sources, the exact engine and original expectation fingerprint.

Accepted receipts: `private/unit-draw-1006/foot-lit-v1/{expected,report}.json`,
with `native-replay.json`, `sanitize-replay.json` and `crossing-sdl/`.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/python tools/verify_foot_lit_draw.py \
  --exe private/official-1006-probe/game.exe
build/tools-env/bin/python tests/compare_foot_lit.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/unit-draw-1006/foot-lit-v1/expected.json \
  --report private/unit-draw-1006/foot-lit-v1/NEW-REPLAY.json
# Add --native build/sanitize/foot-lit-vectors for a sanitizer replay.
# Fresh original execution requires the authorized Mac host JIT context:
build/tools-env/bin/python tests/compare_foot_lit.py \
  --exe private/official-1006-probe/game.exe --output private/unit-draw-1006/NEW-FOOT
./run.command --crossing-demo
```

Normal/sanitizer builds and CTest, **238 Python tests**, source/diff audits and
actual SDL selection/right-click crossing pass. The unchanged crossing retains
79 samples / 78 updates, 22 occluded samples / 150 maximum hidden pixels, clear
endpoints, fresh final/no trails, cache bypass, clipping and camera-return checks.
That SDL result verifies existing native integration, not the unused new helper
or original whole-frame parity. Broad unrelated suites were not repeated.
Only Apple Silicon macOS is tested.

## Accounting and next dependency

Fresh generation: 7.448 s driver / 6.580 s original / 0.091 s native; external
elapsed 7.58 s. Normal/sanitizer builds: 4.25/5.09 s. Replays: 1.708/1.999 s
external, 0.047/0.376 s native. CTest totals: 0.17/0.94 s. Python discovery:
0.508 s, external 1.31 s. Actual SDL: 2.264 s. Checks sometimes contended; no
FPS claim. This continuation began 05:38:56 UTC; the private checkpoint records
closing time and elapsed interval. Full inherited delivery time is unavailable.

The first fresh comparison rejected a missing offset trace after Unicorn had
translated an uninstrumented Drive leaf. Installing one permanent code hook
before execution fixed observation; original instructions/native behavior were
unchanged. Nested raw arguments were normalized to unsigned dwords for comparison.
A syntax probe initially attempted a macOS bytecode-cache write outside writable
roots; rerunning with `PYTHONPYCACHEPREFIX=$PWD/build/pycache` passed. No game
playtest repair, new cache infrastructure, worker or Windows action was needed.

Next execute complete ordinary Unit voxel child `0x6FF690`, nesting the verified
Foot forwarding and established pose/key/cache/staging/shadow/surface boundaries,
then wire drawing caller/type decisions into moving/turning/current-cell light.
Alternate-body metadata, multiple turrets, full construction/ownership, decoration,
outer scheduling, camera/fog/UI and whole-frame parity remain separate open work.
Full base RA2/YR stays active and incomplete. This is locally verified work,
not independent acceptance or a new observable gameplay milestone.
