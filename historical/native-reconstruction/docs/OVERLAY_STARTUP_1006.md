# Nonlazy overlay image startup

Day 1 needs the original rock/wall/ore image headers as well as demand-loaded
bridge headers before its radar terrain path can support the Objective1
alliance/House sight effects. This change recovers the complete nonlazy image
policy on the existing overlay owners. It adds no arrival/sight schedule, radar
SDL adoption or objective transition.

## Recovered policy and evidence

`initializeOverlayImage` in `assets/OverlayImage.hpp` expresses complete5D7630,
465 bytes/140 instructions, SHA256
`abce7033f2409c78007ebf75d43b835340ce8fc4b8b186fb834fe55ab51eb1ee`.
The verifier fingerprints the supplied executable before using addresses:
4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage and reported no-CD provenance remain distinct;
pristine authenticity is unverified. No public/lifted/generated code is included.

The kernel borrows the existing OverlayTypeInputs/image Data/owned byte. It:

- Checks AlternateArcticArt1E1, theater1, owned0 and arcticInUse1E2. It appends A
  only when the first three conditions hold and1E2 is zero, truncates to24 bytes,
  copies the complete25-byte field in original order and sets1E2=1. Failed outer
  gating writes1E2=0; it does **not** remove an existing A suffix. A nonzero1E2
  preserves its exact byte when the outer gate succeeds.
- Builds imageName.SHP, then selects TEM/SNO/URB if Theater is nonzero. Otherwise
  NewTheater uses the recovered ASCII prefix substitution; theater-1 skips it.
  This differs from the demand getter: neither-flag startup has a defined SHP
  filename and is supported.
- Releases a nonnull image only when owned is nonzero, then clears image before
  owned, calls the cache service, and stores the returned image. The cache result
  stays owned0. Null results preserve field1BC. Success reads signed16 width and
  height, stores their signed maximum clamped to at least8 in1BC.

Portable CRT filename construction, cache/IO and heap release remain supplied
services. Supported names are nonempty ASCII alphanumeric/underscore, at most24
bytes, and the base three theaters (or-1 with Theater clear). Unsupported names,
theaters, missing services and inconsistent handle/Data refuse. Invalid host
header backing raises the Data range guard; it is not an original load failure.
Arctic/type field startup values and the complete5D7810 caller/INI associations
remain supplied or inspection-only. Runtime executable reads did not expand.

All588 original sequences match1,512 complete roots,1,944 makepath service calls,
1,512 cache calls,84 releases,111 Arctic renames and7,658 ordered owner writes.
The matrix covers noncanonical flag bytes, prior arctic state, every image/owned
combination, failed and successful repeated loads, name truncation, prefix/case,
both-flag precedence and signed16 extreme dimensions. The oracle checks the
whole guest arena, allowed writes, executable/constants, caller stack and saved
registers. Original instructions are unmodified; CRT/cache/free services are
explicit hooks at checked caller addresses. This is local differential policy
evidence, not original IO or whole-startup fidelity.

## Actual prepared-map binding

`PreparedTerrainMap::initializeOverlayImage` is an explicit entry point using the
same `overlayInputs`, `overlayImages` and `overlayImageOwned` as the demand getter.
AssetStore supplies file bytes and stable type-based native handles. Native shared
Data lifetime replaces heap freeing; this adapter does not recover the original
cache's global identity/deduplication or allocation behavior. No guessed startup
loop populates images during map construction.

The actual Day1 owner check explicitly loads type168 SROCK01.TEM, compares every
byte to the supplied installation, checks field1BC and owned0, then verifies the
demand getter borrows exactly the retained Data even with a later theater2 query.
On type83 it replaces the prior owned demand-loaded LOBRDG10.TEM with startup's
non-owned image on the same type. These are native owner/asset checks, separate
from original execution. Other map/actor/movement/clone/lifetime checks still pass.
Initial Arctic fields/maximum are supplied defaults; animation/type construction,
startup caller/order, original cache/IO and full rendering remain open.

## Validation, costs and continuation

Normal/sanitizer/inspection-uncached replays each reuse588 original answers with
zero misses and execute the current native runner. Existing280 demand,398 joined
radar-demand and366 standalone overlay-color answers replay unchanged on both
rebuilt profiles. Nineteen Python tests and eleven CTests/profile pass. App rebuilt;
no new SDL input/drawing/radar scheduling acceptance was performed. Prior GUI
receipts retain their historical hashes. Only Apple Silicon macOS is tested;
local verification is not independent acceptance.

Fresh generation/native comparison:0.228/0.026s. Normal/sanitizer/uncached driver
replays:0.197/0.338/0.308s. Actual Day1 normal/sanitizer checks:4.270/41.212s.
Receipt `private/boot-camp-20261020/overlay-startup-receipt-a1.json` records report
and runner identities; separate inspection/edit/configure/build/task/repair wall
costs are unavailable. No original mismatch or failed proof occurred.

Next bind the already-recovered resource classifier on actual Cell/type/resource
owners for the radar terrain path; resolve animation ownership only where entered.
Then compose630A00 startup/native storage/first-DSurface semantics before
production House/coverage/actor/SDL integration. Preserve primary-only variants,
default0 and brightness as supplied boundaries. Arrival/sight scheduling, ordinary
Objective1, base RA2 and YR remain incomplete. No workers, Windows actions,
transfers, downloads, system changes or new runtime executable reads.

## Commands

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake -S . -B build/native
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake --build build/native --target overlay-startup-vectors overlay-image-vectors cell-radar-color-vectors radar-terrain-vectors boot-camp-walk-check redalert2-native --parallel 6
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_overlay_startup test_overlay_image test_overlay_radar_color test_cell_radar_color test_radar_terrain test_radar_projection test_cell_resident_search
build/tools-env/bin/ctest --test-dir build/native -R '^(overlay-startup|overlay-image|overlay-radar-color|cell-resident-search|cell-resident-kind6|cell-radar-color|radar-terrain|radar-projection|overlay-type-input|resource-type-input|map-overlay)-domain$' --output-on-failure
build/native/boot-camp-walk-check private/official-1006-probe
# Select new audit/report paths on every invocation. Original answers only are reused.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/NEW-STARTUP.audit.json tests/compare_overlay_startup.py \
  --exe private/official-1006-probe/game.exe --native build/native/overlay-startup-vectors \
  --expectations private/boot-camp-20261020/startup-fresh-a1/expected.json \
  --report private/NEW-STARTUP.json
```

Use the same commands with existing `build/sanitize/` runners for sanitizers.
`--uncached` before the driver checks inspection without disabling explicit
original-answer reuse. Fresh generation uses a new `--output` instead of
expectations/report and needs research-only Unicorn JIT. Prior demand/color reuse
commands are in [OVERLAY_IMAGE_1006.md](OVERLAY_IMAGE_1006.md).
Entry points remain `./build.command`, `./test.command`,
`./run.command --boot-camp-walk`; this change adds no new visible gameplay.
