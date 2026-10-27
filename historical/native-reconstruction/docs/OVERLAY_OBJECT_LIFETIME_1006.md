# Supplied RA2 1.006 temporary Overlay base construction and cleanup

October 15, 2026, after `76036ee`. This continues the same terrain-aware
Foot/world crossing and parked `(51,72)`, elevation 4 capability. The new suite
joins actual Abstract/Object construction, ordinary Overlay placement, retirement
and nonempty cleanup/Overlay destruction. These base constructor and retirement
roots supersede the inspection-only boundary in the earlier placement suite.
The helper remains unwired and is not yet nested into the decoded map reader.
This is a locally verified checkpoint, not a completed playable capability or
independent acceptance. Full base RA2 then YR remains incomplete.

## Identity and references

Both supplied private engines freshly rehash to 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 lineage and reported no-CD changes remain separate
provenance; pristine authenticity is unverified. The approved Windows transfer
was already complete. No new Windows/transfer/source-install/system action,
worker, dependency or upstream code is part of this checkpoint.

Consulted [REFERENCES.md](REFERENCES.md), pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` `docs/voxels.md`/LICENSE and YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` `AbstractClass.h`, `ObjectClass.h`,
`OverlayClass.h`, and the earlier Overlay/Cell/Map declarations. Hypothesis:
temporary Overlay actors need ordered base registrations and retirement-queue
cleanup before the decoded reader can share their actual Cell placement effects.
Exact base execution establishes the bounded behavior below. YR names remain
leads and recomp is not an oracle. No upstream/header/generated/lifted code was
incorporated; no new third-party notice is required.

## Executed boundary

[OverlayObjectLifetime.cpp](../src/assets/OverlayObjectLifetime.cpp) adds typed
selected base records and explicit services. It reuses the separately verified
ordinary loaded placement implementation without changing its source. The native
records are portable projections, not original ABI layouts. The opaque embedded
resource tag is normalized to a supplied native handle; no original pointer is
compiled into the native implementation.

| Additional complete actual range | Executed behavior |
| --- | --- |
| `0x40FF10`, 71 bytes | Abstract selected defaults and low flag bits |
| `0x5D22E0`, 529 bytes | Object defaults and four ordered registrations |
| `0x405BF0`, 18 bytes | Embedded resource tag and three zero words |
| `0x5D4E90`, 124 bytes | Retirement and queue append |
| `0x5D3700`, 389 bytes | Object Limbo, already-limbo rejection domain |
| `0x6ECF10`, 284 bytes | Nonempty inactive-object cleanup |
| `0x5D4F10`, 11 bytes | Inactive predicate |
| `0x4100B0`, 8 bytes | Actual Release returning one |
| `0x40CDF0`, 38 bytes | First-equal pointer search |
| `0x5DC300`, 167 bytes | Actual Overlay destructor |

Together with the twelve placement/identity children, **22 complete ranges /
1,847 inspected instructions** are entered unchanged. Constructor return pointers
and inspected actor/type/registry dispatch are guarded.

Abstract construction clears low flag bits 0–2 and preserves remaining flag bits
and bytes. Object construction sets selected zero/one/255/-1 defaults, copies the
supplied invalid-world position and initializes two embedded resource records.
Each resource tag is stored before its three zero words. Four global collections
register in order; each append stores count before slot. Full storage grows only
when owned or capacity zero, with positive increment and nonzero **low byte** of
the supplied growth result. Only after registrations does flag bit 1 become set.

The existing actual Overlay constructor then stores type/identity, registers the
Overlay, tests invalid coordinates and executes loaded placement. Actual retirement
performs optional tag detach, removed-byte-one pointer expiration, the actual
already-limbo Object Limbo rejection, active=0 and retirement-queue append.
Persistent non-limbo retirement is explicitly refused by the native helper.

Cleanup retains active entries. For an inactive actor, it removes **all** matching
retirement-queue duplicates before destruction, preserving capacity tails. Actual
Release returns one; four RTTI comparisons are supplied negative for this
Overlay-only domain. The actual Overlay destructor announces expiration, removes
**one** Overlay-registry occurrence, executes the actual already-limbo Object
Limbo rejection, clears type and calls supplied base destruction/free. No claim
that base registrations have been destroyed follows from that service boundary.

## Evidence and supplied services

Current receipts: `private/map-depth-1006/overlay-object-lifetime-v2/`, containing
expected/report and normal/ASan/UBSan replays. **3,681 fresh original/native cases**:

- 1,584 construction/placement/retirement/optional cleanup cases;
- 1,320 retirement/tag/growth/duplicate/cleanup cases;
- 768 cleanup cases, all 256 active masks with multiple actors and capacity tails;
- nine identity absence/wrap/invalid-position cases.

Growth results 256 and 257 distinguish full-word from low-byte success. Compare
complete selected actor/base/Cell state, identity counter and placement global,
all six registry counts/capacities/ownership/slots, freed-service counts and
ordered event digests. Counts: **16,494 outer audits**, 6,345 Overlay/Abstract/
Object/identity constructor entries, 6,342 counter, 12,690 resource constructors,
11,886 retirement, 16,778 Object Limbo, 2,229 cleanup, 11,036 inactive predicate,
4,892 Release/Overlay destructor and 20,134 search entries. Each ordinary placement
child enters 5,286 times. There are **505,647 ordered selected guest stores** and
**105,643 supplied service calls**.

Caller stack/register/return address, immutable type/input/global records,
nonselected actor bytes, registry capacity tails, allowed vtable-store values
and constructor return pointers pass. v1 predates the explicit vtable/return
guards and remains historical; v2 is fresh evidence for the final guarded source.

Heap/vector growth and allocation/free, full pointer-expiration broadcasts
`0x6ECB90`, tag detach internals `0x435FB0`, RTTI and base Object destructor
`0x5D2530` remain supplied. Cell lookup, resource `0x476BA0`, recalculation
`0x472540`, redraw and absence of attached animation remain services. Placement
retains the ordinary loaded nonwall/nonbridge/no-CellAnim and special-index guards.
Full base/type/startup/parser/ownership lifetime, alternate placement, decoded
reader nesting, runtime integration and whole-frame parity remain open.

## Verification and reproduction

Both builds, **539 Python tests**, **33 normal / 32 sanitizer CTests**, source/diff/
local-link audits pass. All prior 38 source/runner sets and decoder remain current;
the final source/runner audit covers **40 sets / 856 source entries**. Actual rebuilt
SDL baseline passes selection/right-click, 79 samples/78 updates, lighted crossing,
culling/clipping/cache bypass/pan return. This is existing native integration,
not new overlay-lifetime/runtime or original-frame fidelity. No new screenshot
inspection was performed. Only Apple Silicon macOS is tested.

Fresh v2 driver/original/native: 14.871/14.147/0.069 s, CLI 15.004 s. Normal/
sanitizer replay CLI 0.768/2.483 s. Initial normal build 6.831 s, guard rebuild
8.028 s, sanitizer build 11.201 s; Python CLI 2.505 s (unittest 0.672 s),
test.command 2.203 s, sanitizer CTest 5.148 s and actual SDL 2.332 s. Earlier
successful runs/timings remain private. No original/native mismatch, failed
build/test or gameplay repair occurred. Full active-delivery and initial
continuation elapsed remain unavailable.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
# Fresh original execution needs the authorized host JIT context and unused output.
build/tools-env/bin/python tests/compare_overlay_object_lifetime.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/overlay-object-lifetime-new
build/tools-env/bin/python tests/compare_overlay_object_lifetime.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/overlay-object-lifetime-v2/expected.json \
  --report private/map-depth-1006/overlay-object-lifetime-v2/replay-new.json
# Add --native build/sanitize/overlay-object-lifetime-vectors for sanitizer replay.
./run.command --crossing-light-demo
# Select Rhino; G/right-click moves, L toggles light, R resets.
```

Continue map-required wall/bridge placement, then nest the decoded reader and
Cell/resource/recalculation children on shared state. Complete overlay-bearing
map resource/wall-owner effects before prepared Cell/TMP-to-Foot/base-depth and
Unit/world integration. Require actual SDL level crossing and parked cliff before
capability completion. Runtime depth fields remain neutral. Parser/defaults/actor/
contact/cache/heap lifetime, scheduling/camera/fog/UI/pathfinding stay open.
