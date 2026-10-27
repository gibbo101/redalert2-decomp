# Supplied RA2 1.006 bridge-size surface selection and split pixels

October 15, 2026, after `212b881`. **3,264 fresh original/native results** and
normal/ASan/UBSan replays pass. The complete final Unit root now executes with
nonzero `TooBigToFitUnderBridge`, actual first-contact getter, the conditional
two-part draw and actual RGB565 pixels under both depth gradients. This closes
the selected surface-branch gap exposed by stock HTNK metadata. The new helper
remains unwired; this is a prerequisite checkpoint in the same healthy Rhino
drawing delivery, not a new observable gameplay milestone.

## Exact engine, references and scope

Exact engine: `private/official-1006-probe/game.exe`, 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Fresh generation and both replays recheck this identity. Both supplied engine
copies were rehashed equal at the preceding metadata checkpoint. No transfer or
Windows action occurred here. Embedded 1.08, supplied 1.006 patch lineage and
reported no-CD provenance remain separate facts; pristine status is not established.
No source installation/disc, sibling project or system configuration changed.

The same pinned recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439`,
`docs/voxels.md`/LICENSE, and YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88`, `TechnoTypeClass.h`,
`UnitTypeClass.h`, Techno/Surface declarations supply bridge-size and final-draw
leads. Exact base metadata, instructions and fresh execution verify the decisions;
no YR layout/address or recomp behavior was adopted. No upstream/header/generated
or lifted code was incorporated, and no dependency was added.

`tools/verify_unit_surface_split.py` retains the final-surface inspection's
**23 complete ranges / 1,741 instructions**, including complete root
`0x6FF3E0..0x6FF67F`, and adds complete first-contact getter
**`0x636E20..0x636E30`, 16 bytes / four instructions**. It checks the three
24-byte gradient descriptors at `0x7CE168`. The preceding Foot-depth verifier
checks the actual cell predicates selected by the nested cases. Original
instruction bytes are unchanged.

The actual contact getter loads actor `+0xCC`, then array element at the supplied
signed index; this root always passes zero. A valid initialized pointer array is
supplied even when its first element is null. Original allocation, count/capacity
and contact association/lifetime are not recovered. Contact kind is a read-only
service; the nonnull contact's `+0x418` type and type byte `+0x1357` read execute.
Those fields retain offset names. Map lookup/records remain the preceding
Foot-depth fixture's supplied immutable domain. Depth values are supplied on
each query; this suite does not nest actual Foot/base depth into the split path.

## Preserved native behavior

`src/render/UnitSurfaceSplit.*` adds an SDL-free wrapper around the unchanged
zero-field final wrapper. This preserves its earlier exact source identities.

- If type byte `+0xBAE` is zero, skip every extra predicate/contact query.
- Otherwise call `0x6CF670` and test its low byte. If nonzero, call `0x6CF9D0`;
  a zero dword result selects splitting immediately and skips contact lookup.
- Otherwise obtain first contact **before** testing actor dword `+0x494`.
  Splitting then requires nonzero actor field, nonnull contact, contact kind 6
  and nonzero contact-type byte `+0x1357`. Preserve short circuits and low bytes.
- Perform the existing layer/flags/owner/house selection once. Split only when
  the resulting decision is true and signed dirty height is **greater than 16**.
  Predicate/contact queries still happen for short, zero or negative heights.
- Upper source/destination height is `height-16`. Query depth then source bounds;
  draw with wrapped depth minus 5 and gradient **0**, without querying actor
  gradient. Then advance source and destination Y by upper height with dword wrap.
  Set both heights to 16, query depth and source bounds **again**, and draw with
  gradient **2** and the second returned depth. Keep brightness, clip and extra.
- Other cases use the prior gradient/depth/bounds sequence and one final draw.

The new bounded `blitUnitTopGradient` implements original descriptor 0 only.
After linked clipping and relative clip-origin adjustment, its initial depth is
`uint16(32768-clippedTop)+z`, then decreases by one per row. Nonzero source index
writes color only for strict candidate-less-than-stored-depth; depth remains
unchanged. Alpha/palette selection uses the existing recovered numeric kernel.
Descriptor 2 continues through unchanged `blitUnit`. This is not a general
gradient/ramp renderer, bridge gameplay, converter construction or frame proof.

## Evidence and reproduction

| Fresh matching results | Count |
| --- | ---: |
| Low-byte, predicate/contact and split decisions | 1,920 |
| Extreme wrapped rectangles and repeated depth returns | 512 |
| Actual cell predicates nested before contact/surface | 512 |
| Actual complete final surface/RGB565 pixels | 320 |
| **Total** | **3,264** |

**3,264 new roots**, five inherited/setup roots and one inherited alpha block are
audited. There are **1,456 actual contact getter calls**, 532 supplied contact-kind
calls and 3,660 final-child invocations. Of those, **456 actual surface calls**
occur in 320 pixel cases: 136 with gradient 0 and 320 with gradient 2; the remaining
3,204 children capture arguments. **2,563 original RGB565 spans** execute, changing
22,379 fixture color pixels. Full color/depth hashes match; source/palette/alpha/
depth/actor/type/contact/cell arenas stay unchanged and lock counts end zero.
Caller ESP, return address, callee-saved registers, stack tail, allowed writes and
heap inputs are guarded. Pixel viewports are contained in destination surfaces;
extreme rectangles are forwarding cases. Mutable callbacks/aliasing, ownership,
nonordinary blitter pixels and whole-frame behavior remain outside the domain.

Receipts: `private/unit-draw-1006/surface-split-v1/{expected,report}.json`,
`native-replay.json`, `sanitize-replay.json`, `crossing-sdl/`. Engine/profile,
inspection, relevant sources and expectation fingerprints are checked, with
separate runner hashes. Seven new receipt guards pass. Unchanged earlier surface
and Foot-depth sources replay **5,602 and 5,952** original results on both current
builds; reports are named `post-split-*-replay.json` in their original receipt
directories. No earlier expectation or accepted fresh receipt was overwritten.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/python tools/verify_unit_surface_split.py \
  --exe private/official-1006-probe/game.exe
build/tools-env/bin/python tests/compare_unit_surface_split.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/unit-draw-1006/surface-split-v1/expected.json \
  --report private/unit-draw-1006/surface-split-v1/NEW-REPLAY.json
# Add --native build/sanitize/unit-surface-split-vectors for sanitizer replay.
# Fresh original execution needs the authorized Mac host JIT context:
build/tools-env/bin/python tests/compare_unit_surface_split.py \
  --exe private/official-1006-probe/game.exe --output private/unit-draw-1006/NEW-SPLIT
./run.command --crossing-demo
```

Normal/sanitizer builds, **8 normal / 7 sanitizer CTest checks**, **276 distinct
Python tests**, source/diff/link audits and actual SDL selection/right-click
crossing pass. SDL retains 79 samples / 78 updates, 22 occluded samples / 150
maximum hidden pixels, no trails, bypass, clipping and camera return. It verifies
the unchanged runtime, not integration of the new helper. Broad unrelated
numeric suites were not repeated. Only Apple Silicon macOS is tested.

## Accounting and continuation

Normal/sanitizer builds: **4.76/4.77 s**. Fresh driver/original/native:
**26.382/25.840/0.063 s**, external 26.48 s. Normal/sanitizer replays:
1.026/1.573 s driver, 0.072/0.660 s native. CTest totals 0.09/0.44 s; test command
0.54 s. Python discovery 0.376 s (external 0.87 s). Actual SDL **2.33 s**.
This checkpoint began 06:50:21 UTC; private accounting records closing time.
Full inherited delivery time is unavailable; contended check times are not FPS.

Two fresh attempts failed before accepted evidence: the inherited initializer
entered the permanent hook before its derived field existed; guarded lookup fixes
that fixture initialization. The next completed original generation but native
input refused Python `True`/`False` text; integer serialization fixes the protocol.
The third fresh run passes without native numeric changes. No game playtest
repair, cache/worker/coordinator work, Windows action or source/system change.

Next verify model and neutral actor/type associations, then combine this wrapper
with actual Foot/base depth and established caller/cache/raster/staging children
before runtime wiring. Keep moving/turning past scenery and changing current-cell
light as the observable delivery. Full construction/ownership, decorations, outer
scheduling, camera/fog/UI and frame parity remain open. Full base RA2/YR stays
active and incomplete; this checkpoint is locally verified, not independently
accepted or a new gameplay milestone.
