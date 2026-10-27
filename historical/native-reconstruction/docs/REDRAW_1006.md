# Supplied RA2 1.006 redraw requests and dirty regions

The later [GI Mark binding](BOOT_CAMP_MARK_REDRAW_1006.md) now uses the argument-
zero request on the actual shared Tactical owner. Use its explicit current-native
reuse command after native-only edits; the historical driver's mixed source
guard below intentionally retains its original scope. Frame consumers/clearing
remain unjoined. The older unwired wording below describes its checkpoint.

October 14, 2026, following actor checkpoint `796af52`. **17,272 fresh original/
native results**, normal and ASan/UBSan replays pass. These are redraw request and
queue kernels; caller/frame scheduling and runtime integration remain open. The
moving-Rhino/scenery crossing is not complete.

## Identity, references and inspection

Only `private/official-1006-probe/game.exe`, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`,
4,485,392 bytes, is accepted. Embedded version 1.08, supplied 1.006 patch lineage,
byte equality with the approved private Windows copy and user-reported no-CD
provenance are retained separately. This is not pristine authenticity. Disc proof
is separate. No source installation, Windows state or original instruction changed.

Consulted pinned YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88`
`ObjectClass.h` (MarkForRedraw/NeedsRedraw), `TacticalClass.h` (RegisterDirtyArea/
Redrawing), `MapClass.h` and `DisplayClass.h`, plus redalert2-recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` `docs/voxels.md` and LICENSE.
Hypothesis: actor/map redraw requests and tactical dirty-region storage are
separate from the recovered drawing gate. These names are leads; exact base-binary
inspection/execution below establishes behavior. No upstream/header/generated or
lifted game code was incorporated.

`tools/verify_redraw.py` pins **eight complete ranges / 528 instructions**:

| Routine | Address |
| --- | --- |
| Object redraw request, Unit/Terrain slot +0x12C | `0x5D36E0` |
| Map redraw request | `0x4E09A0` |
| Wrapping byte increment | `0x55ACC0` |
| Dirty-region registration | `0x6A3020` |
| Asymmetric rectangle union | `0x45EFE0` |
| Rectangle intersection (previously recovered) | `0x41FDF0` |
| Queue initializer | `0x6A22F0` |
| Empty-rectangle initializer (previously recovered) | `0x6E2FE0` |

The actual queue vtable `0x7AC4C4` has growth at +8 -> `0x6ACBE0`. Its allocator
is a supplied service, not executed original heap code. The complete initializers
execute; atexit is a checked service. The native queue models defined metadata and
entry fields, not original vector construction/destruction/heap ownership.

## Preserved behavior

`src/render/Redraw.*` has no SDL dependency:

- Object's redraw byte changes to 1 only from zero, then calls map request with
  argument zero. An already nonzero redraw byte causes no request or write.
- Map requests set tactical +0xD7D=1 when Tactical exists, even for argument zero.
  A nonzero argument writes map mode unless it is already 2, then increments
  map +0x1154 modulo 256. Mode 2 does not suppress the increment. These field
  operations do not establish complete frame scheduling or mutex semantics.
- Registration preserves signed/wrapped intersection, containment flag policy
  and ordered removals. Removal shifts subsequent live entries and leaves the old
  tail uncleared. Input flags retain their byte on append; merging normalizes OR
  to 0/1. Invalid-size incoming rectangles are not silently discarded.
- Partial overlaps compete by signed low-32-bit union area strictly less than
  both separate summed area and the current best. Equal areas keep the first
  candidate. No wider arithmetic or general rectangle-union library is substituted.
- Union preserves the extra right/bottom pixel and its asymmetry. The loop's area
  estimate starts with the old rectangle; final merge starts with the incoming
  rectangle. Containment/overlap does not imply commutative union dimensions.
- Full storage grows only when ownership/capacity and positive growth permit it.
  The supplied growth service receives capacity+growth and preserves the complete
  old capacity. Failure leaves the append absent. Count increments before the five
  entry stores. Invalid native counts, overflowed capacity and missing allocation
  service are safety refusals, not original malformed-input behavior.

Entries have three original padding bytes. The oracle audits write extents and
full arena/metadata guards but comparisons cover **defined rectangle/flag fields**,
including capacity tails and ordered writes. No native parity for uninitialized
padding, real allocations or their failure side effects is claimed.

## Verification and commands

Private evidence: `private/traversal-1006/redraw/{expected,report}.json`,
`native-replay-report.json` and `sanitize-report.json`. Source/inspection/engine/
receipt identities must match; fresh receipts cannot overwrite existing proof.
There are **17,273 audited roots** (including the empty initializer):

| Group | Results |
| --- | ---: |
| Initial queue fields | 1 |
| Every counter byte, map modes and Tactical presence | 7,168 |
| Every redraw byte and idempotence | 3,072 |
| Signed/wrapped union and invalid extents | 2,048 |
| Containment flags, overlap, touching and empty regions | 2,916 |
| Capacity/ownership/growth/failure | 432 |
| Ordered removal, tail, best merge and wrapped arithmetic | 1,536 |
| Multiple deletes and stable ties | 99 |
| **Total** | **17,272** |

Actual request/rectangle instructions execute unchanged. Comparison includes
defined final fields and ordered external writes. Callable guards check registers,
ESP, return address, caller stack and full object/metadata/arena boundaries.

```sh
./build.command
./test.command
build/tools-env/bin/python tools/verify_redraw.py --exe private/official-1006-probe/game.exe
build/tools-env/bin/python tests/compare_redraw.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/traversal-1006/redraw/expected.json \
  --report private/traversal-1006/redraw/NEW-NATIVE-REPLAY.json
# Add --native build/sanitize/redraw-vectors for sanitizer replay.
build/tools-env/bin/python tests/test_redraw_evidence.py
# Fresh execution requires the authorized Apple Silicon host JIT context:
build/tools-env/bin/python tests/compare_redraw.py \
  --exe private/official-1006-probe/game.exe --output private/traversal-1006/NEW-REDRAW
```

Seven new evidence guards, native domain guards, all **202 Python tests**, normal/
sanitizer CTest and source audit pass. Runtime remains unchanged; no new SDL run or
full-frame claim accompanies this checkpoint. Previous owned/SDL evidence retains
its own scope.

## Accounting and continuation

Fresh CLI: 2.916 s total / 2.427 s original / 0.200 s native. Normal replay: 0.181 s
native; sanitizer: 0.331 s native. Python discovery: 0.729 s; normal/sanitizer CTest:
0.19/0.20 s. Builds succeeded, but separate elapsed build and inherited whole-delivery
costs are unavailable. No failed parity attempt or playtest repair occurred.

Next execute the static redraw request caller at `0x6A4350`: visible-cell regions,
reverse dirty-region requests, full-viewport/edge requests and actual static scan
linkage. This is an inspected-only lead here. The outer frame scheduler, camera
inversion, final Unit DrawIt and host surface/cache ownership remain distinct
dependencies. Then integrate and exercise the reproducible moving crossing with
actual SDL input/rendering. No extra worker or Windows action is needed.
