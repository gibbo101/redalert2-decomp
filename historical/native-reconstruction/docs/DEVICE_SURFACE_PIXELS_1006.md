# Device-surface locks and inherited pixels

Update: [software-source device copying](DEVICE_SURFACE_COPY_1006.md) now binds
first RadarStorage.copy8 to the actual terrain owner using recovered device locks.
Earlier copy-unbound statements below retain their historical scope.632700 and
production scheduling remain open.

Boot Camp Objective1's action37 House sight/radar refresh needs the first radar
surface to support its actual device contract. `DeviceSurfacePixels.hpp` recovers
complete4AAC80 Lock,4AAE40 Unlock and4AAC60/4AAC70 metadata getters. The existing
774220/7741D0 writer/reader now accept explicit virtual services through one shared
kernel; ordinary BSurface facades retain their original lock chain. No duplicated
pixel algorithm or BSurface lock substitution is installed on the device owner.

## Recovered behavior and native ownership

Lock checks both raw enable bytes, then device status before coordinate rejection.
Only lost HRESULT887601C2 requests Restore and another status query. Successful
recovery with positive saved depth preserves the original recursive Lock/increment/
Unlock/restore-depth ordering. At zero depth it initializes a108-byte local
27-word descriptor, requests OS Lock flags1, copies it, then stores wrapped
(bitcount+7)>>3 bytes, caps bit14 and buffer address. It increments wrapping depth,
queries pitch before format, and wraps address arithmetic. Negative coordinates
return null after status/recovery. A failed OS Lock returns null without copying.

Unlock recovery failure does **not** skip its decrement tail. Disabled enable bytes
also do not skip decrement/cleanup. Signed depth<=0 returns false; otherwise it
decrements, performs OS Unlock only at zero, ignores that HRESULT, and clears the
buffer address. Host recursion limit16 and entered service/backing guards refuse
unsafe native execution; they are not original clamps or rollback semantics.

`RadarStorage` now borrows its existing first owner's lock/format/address/video/
device/descriptor fields for these kernels. Explicit `setDisplayPixel` and
`getDisplayPixel` use its existing byte vector; second terrain backing is separate.
Native platform policy is enabled memory storage, healthy status, RGB565,
pitch=width*2, caps2040 and logical buffer address10000. Native Unlock validates the
mapping and releases no OS object. These are supplied platform services, not a
DirectDraw reconstruction. Device copy remains unbound. No live producer or SDL
radar scheduling was introduced; finish632700 remains supplied.

Actual mutable Day1 world checks write1234/read it back from the same first-buffer
pointer, verify little-endian bytes, reject negative coordinates through null Lock,
restore zero and relock. Full terrain RGB/projected pixels and sampled mission/
Walk/visibility state remain unchanged. Existing overlay removal/restoration,
full-map startup, warm clones and all eight GI journeys remain covered. This is
native owner evidence, separate from original-routine differential evidence.

## Exact original evidence and costs

The supplied executable remains4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD and unverified pristine
provenance remain distinct. Private complete inspection pins315-byte4AAC80,
154-byte4AAE40,4-byte4AAC60 and7-byte4AAC70, plus inherited89-byte774220 and
80-byte7741D0. Unchanged original instructions execute only in research Unicorn;
full arena, code/vtable/global inputs, caller ABI and permitted writes are guarded.

All477 direct sequences and335 inherited-pixel sequences match ordered stores,
returns, descriptor/backing digests and final depth. Coverage includes raw gates,
negative/extreme depth, recovery failures and recursion, wrapping formats/addresses,
negative coordinates, null-device supported paths, and mixed Lock/Set/Get/Unlock.
Platform status/restore/Lock/Unlock results and initial data are supplied fixtures.
Canonical original-only expectations under `private/boot-camp-20261020/`:

- `device-lock-fresh-a1/expected.json`:477 sequences; generation0.280s.
- `device-pixels-fresh-a2/expected.json`:335 sequences; generation0.378s.

Normal/sanitizer/inspection-uncached replays report477/335 hits and zero misses;
each executes current native code. Both rebuilt profiles also reuse300 writer,
300 reader,8 startup,950 copy/mark and940 complete coverage/refresh sequences.
The latter covers both refresh branches with shared software pixels.30 Python
checks,190 normal/189 sanitizer CTests and both actual Day1 owner checks pass.
Broad CTests take2.52/13.64s. Separate edit/build/repair/task and actual-owner times
are unavailable. Details/hashes: `private/boot-camp-20261020/device-pixels-receipt-a1.json`.
No unchanged original matrix was regenerated. Local verification is not independent
acceptance. No unchanged SDL smoke ceremony was rerun for this unscheduled service.

The first inherited original attempt faults writing address42: successful Restore
followed by failed recursive OS Lock can clear address14 while retaining positive
depth. A subsequent nonzero coordinate yields a nonnull invalid address. Its failed
audit remains. The valid-backing matrix uses origin0 for this case, exercising the
inherited null return; a separate native guard verifies nonzero access refuses
without touching backing. Fault compatibility is not claimed. An old radar-pixel
replay also refuses because a prior milestone changed its oracle source; its two
failed replay audits remain. Current coverage/refresh expectations have matching
provenance and replay unchanged instead; no guard or receipt was bypassed.

## Commands and next work

```sh
./build.command
./test.command
./run.command --boot-camp-walk
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake --build build/native --target device-surface-pixels-vectors boot-camp-walk-check --parallel 6
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_device_surface_pixels test_device_pixel_access
# Use fresh private audit/report paths for every invocation.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/NEW-DEVICE-PIXELS.audit.json tests/compare_device_pixel_access.py \
  --exe private/official-1006-probe/game.exe --native build/native/device-surface-pixels-vectors \
  --expectations private/boot-camp-20261020/device-pixels-fresh-a2/expected.json \
  --report private/NEW-DEVICE-PIXELS.json
```

For direct locks use `compare_device_surface_pixels.py` with the direct expectations
above. Sanitizer uses `build/sanitize/device-surface-pixels-vectors`; `--uncached`
before the driver disables inspection reuse while explicitly retaining original
expectation reuse. Fresh original execution requires research JIT and a new output.

Next recover the relevant complete4AAF80/4AAFD0 first-device copy path using these
locks, then632700 buckets and actual House/coverage integration. Do not replace
them with BSurface virtuals or infer original initialization/scheduling. Ordinary
SDL Objective1, base RA2 and YR remain incomplete. Only Apple Silicon macOS is
tested. No external implementation, dependency, download, Windows action, worker,
system/Xcode/DRM change or runtime executable-read expansion was introduced.
