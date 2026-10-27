# Building Type demand image getters

Complete458CE0 and45E790 now load primary/secondary image identities on the
existing Boot Camp BuildingTypes. The explicit existing-owner seam composes
read-only original SHP decoding -> demand getters -> Type bounds -> Building
bounds -> Renderer dirty queue. This is a dependency of original Building drawing
and Boot Camp's objective/sight refresh. It remains unscheduled: SDL still draws
Building markers, not recovered Building sprites; frame consumption, live sight,
arrival and Objective1 progression remain open. Neither game is complete.

## Evidence and exact behavior

Exact supplied base executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain separate. Complete pinned ranges are458CE0
(286B/64 instructions),45E790(397B/94),5D7BD0(74B/31),5D7C20(5B/2) and
77F110(61B/20). Vtable79D1F8 slots9C/C0 resolve to the two getters. The theater
transform reuses the existing recovered `applyObjectNewTheater` implementation;
5D7C20 writes filename byte1 to G. Original executable code is not used at runtime.

Primary returns its resident A4 or, with zero demand13E0, null without file
services. Empty13EB returns current A4. Otherwise it constructs file0, calls
cache override4691A0 with0, loads495230, stores A4 and sets ownedA8 on success.
Failure copies19 filename bytes and retries after the G transform. It stores
A4/ownedA8 before file1 cleanup, then cleans file0. Return rereads A4 after both
cleanup phases. Failed loads retain ownedA8. Filename mutation during first load
is visible to the fallback copy.

Secondary returns resident B98 or, with zero demand13E1, null. Empty basenameBF4
returns current B98. It makes basename+.SHP, transforms for live theater and
loads file0. On failure it changes byte1 to G and retries file1. It cleans file1
before storing B98/ownedB9C, unlike primary. On success it reads signed16 SHP
count, divides by2 with signed truncation, then lets nonzero1351 override with
wrapped137C+1. Duration defaults1; positive count uses Rules1178*900.0/count under
the original FP53/toward-zero state and actual FTOL low EAX. Ordered stores are
C8C=0, C90=count, C94=duration. It then cleans file0 and rereads B98. Both failures
retain B9C and animation fields. The native service boundary restores host FP
rounding; .6 with count3 yields179 in the verified original profile.

614 original cases execute complete parents/transform/FTOL without modification.
They cover raw gates, empty/resident names, first/fallback success/failure, repeats,
name/field/pointer mutations during load/header/cleanup, three base theaters and
-1, signed/odd/extreme frame counts, wrapped override, timing thresholds, NaN,
infinity and signed conversion limits. There are144 primary and506 secondary
entries,706 file loads,1,412 cleanup calls and2,557 ordered Type stores. The
oracle audits caller stack/callee-saved registers, unrelated Type/image arena and
immutable code/constants/table inputs. File construction/cache/read/cleanup,
CRT makepath/strncpy and loaded image/header identities are explicit services;
this is not recovery of original file I/O, allocation or SHP decompression.

Original expectations: `private/building-image-20261019/fresh-a1/expected.json`.
Both final native profiles explicitly reuse614 getter +369 unchanged Type bounds
+525 unchanged invalidation answers:1,508 hits/zero misses each. Current native
runners always execute; no native result is cached. The original identity covers
transitive Python/verifier sources, exact executable and environment; native
source/binary identities are recorded separately. The369/525 original scopes
retain supplied getter/Type services respectively: they are not a single joined
original frame proof. Actual-owner composition is current native validation.

## Owners and limits

`BootCampBuildingExpirationType::images` owns numeric getter fields and supplied
names. Secondary B98/B9C remain in the same existing `imageBounds` record, with
no duplicate state. `structureTypeImageState` exposes explicit supplied startup.
`structureTypeImageBoundsFromAssets` supplies synchronous file services through
the existing AssetStore/readShp. The same Type holds immutable shared image
backing: clones retain valid opaque image identities after source destruction;
secondary release removes only that clone's host ownership. No persistent
callback borrows another world's records. Resource ownership is an authored host
adapter, not the original heap or File lifecycle. File absence returns null;
malformed files refuse through the existing reader. Source files are unchanged.

Actual-owner checks load the two Objective1 SHPs using supplied stock Temperate
primary names and secondary basenames/flags. They verify independent resources,
recovered secondary theater substitution, timing, transient secondary release,
Type/Building cache misses, persistent dirty regions, warm clones/source
destruction, missing file/fallback and source isolation. Initial names, demand/
release flags, zero cache/sentinel, Rules timing, theater and AssetStore archive
policy remain supplied. Original Type construction/loading and stock associations
are not established by these tests. Decoder limits remain the existing ones.

Filename support is bounded to24 ASCII letters/digits/underscore/dot. An entered
primary fallback for length>=19 refuses because original strncpy19 does not
ensure termination, exposing an uninitialized stack suffix. First-load success
at those lengths remains supported. Missing services/foreign image identities
refuse explicitly; this is not a universal guest-memory or path implementation.

All207 normal and206 sanitizer CTests, eight focused Python evidence checks,
normal/sanitizer actual-owner checks, test.command and SDL256ticks pass. Current
horizontal PPM captures are byte-identical to the previously inspected Type-bounds
captures. The first integration compile exposed a test-only trivial-copy snapshot
assumption; explicit scalar/name/backing inspection replaces it. No original or
native comparison mismatch occurred. Private receipt:
`private/building-image-receipt-a1.json`. It records source/binary/output hashes,
measured costs and unavailable measurements. Local checks are not independent
acceptance; only Apple Silicon macOS is tested. No new public dependency, copied
implementation, runtime executable read, Windows/system/Xcode/DRM action or
asset shipment was introduced.

## Commands and next work

```sh
./build.command
./test.command
build/native/boot-camp-walk-check private/official-1006-probe
build/sanitize/boot-camp-walk-check private/official-1006-probe
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest \
 tests/test_building_image.py tests/test_building_type_bounds.py

# New private report/audit paths are required. Current native always runs.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
 tools/run_evidence.py --audit private/NEW.audit.json \
 tests/compare_building_image.py --exe private/official-1006-probe/game.exe \
 --native build/native/building-image-vectors \
 --expectations private/building-image-20261019/fresh-a1/expected.json \
 --report private/NEW.json
# Repeat with build/sanitize/building-image-vectors for sanitizer.
# The Type-bounds and invalidation notes retain their exact reuse commands.
./run.command --boot-camp-walk
./run.command --boot-camp-walk-smoke-test private/NEW-SDL
```

Next recover required static-frame children on these actual owners under complete
entered6A45A0 and inspected0/1/map/2 dispatch. Do not schedule an isolated reset
tail or enable sight/arrival/objectives before complete entered dependencies.
No workers or new runtime executable reads.
