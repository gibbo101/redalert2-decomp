# Complete nonzero radar pixel and refresh caller

`SurfaceRadarPixel.hpp` recovers complete632000 through63249C ret4 and verifies
it beneath the existing634030 nonzero caller. This separate unwired rendering
parent preserves projection, bucket selection, color/flash decisions, saved table
calls and dirty stores. Floor/discovery/House/type/color/resolver/pixel child effects
remain explicit named services; the next composition must replace them with actual
recovered children before production/runtime adoption.

## Target, arithmetic and ownership

Exact supplied base: `private/official-1006-probe/game.exe`,4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Addresses apply only to this fingerprint.
No public implementation, dependency or runtime executable read was added.

A null current House skips all fields/queries. Otherwise the actual stock rect78
getter supplies geometry; signed half-open comparisons use wrapped rectangle ends.
X/Y saved after the geometry call feed projection, but bucket selection, candidate
matching, service point arguments and final dirty accumulation read the borrowed
point later. Do not replace those late reads with the saved projection coordinates.

Projection uses the original53-bit/toward-zero FP profile and the inspected float
and double.5 constants. It divides by float scale1484, subtracts148C/adds1494,
forms sum/difference in order, multiplies.5/adds.5, and executes signed-qword FTOL
before word truncation/sign extension and coordinate*256+128. Invalid qword
conversions retain low-word0. Finite nonzero float scale is the explicit native
numeric domain; zero/nonfinite scales refuse. Host rounding restores on return and
exceptions. No convenience rounding, floor or host long-double model is substituted.

The two discovery queries independently reread modeB263D8 after the floor call.
Their flags are retained across later callbacks. Bucket `(x-5*y)&255` uses the late
point, then retains its count/backing while reading each actor/X/Y live. Hidden
admission uses direct Owner/local-House; type80/byte1FF and current-House/object
alliance have their original short circuits. Only an accepted matching entry selects
an actor; a rejected or nonmatching last actor does not become a selection.

Actor color saves Owner before C0, calls CC only once if C0's low byte is nonzero,
and uses raw scheme.index330 on null color House. This differs from6324A0's palette
lookup and repeated CC path. House55E9/EA/EB bytes pack through852FB8..CC shifts.
Terrain darkening retains16-bit right shifts,8-bit left truncation and full-word
repacking; all counts mask to5 bits, including negative/extreme supplied shifts.

Flash uses start13C/remaining144 and wrapped frame-start, strict elapsed comparison,
signed division by rules90, signed modulo-two equal1, then a late Owner/current
identity comparison. Zero divisor explicitly refuses when actually entered; skipped
flash does not read rules. Flash complements the full dword before the pixel child.

No-actor dim samples second28 then darkens; hidden/non-dim draws0. Ordinary copy
saves first's table before second28, then reloads first's receiver for the saved
setter24. Surface and table identities remain independent. The caller ignores the
setter result. Late point/screen offsets feed dirty1208, which initializes1x1 when
either old dimension is nonpositive. Existing rectangles extend left/top normally,
but right/bottom use the recovered conditional+2 extension. Arithmetic wraps and
all four final dwords store in order. The service observer must remain passive.

Views borrow actual caller records; binding them must not query the world. Initial
actors, surfaces, buckets, House colors, scale/offsets, timers, shift configuration,
frame/rules and scratch remain supplied. Invalid owners/backing, excessive bucket
traversal and unsupported numeric inputs refuse without a rollback claim. Services
and borrowed owners must outlive calls. No original construction, scheduling,
map/image state, production coverage or in-game observation follows from fixtures.

## Differential verification

All2,409 sequences match complete ordered traces and final point/dirty/surface/
association/global/bucket/entry/owner/timer/shift/scheme fields. There are1,389
standalone entries and1,020 complete634030 nonzero parents, collectively13,629
actual632000 entries,13,594 stock rect calls and26,488 actual FTOL calls. Entered
child-service counts and full identities remain in the private receipt.

The scenarios cover null current/signed geometry rejection, all draw branches,
late state changes at12 service boundaries, actor eligibility and skipped entries,
retained list count/backing, independent saved table/late receiver, channel shift
extrema, timer wrapping/signed division, subnormal/negative scale, signed-word/
indefinite projection and asymmetric wrapped dirty union. Supplied callback
mutations are diagnostic probes, not observed game behavior. Named child effects
and initial data are not relabeled as recovered behavior.

The original oracle runs unchanged instructions in research-only Unicorn and guards
inspected spans/constants, stack/callee-saved state, allowed writes, the whole arena
and expected globals. The first attempt produced original expectations but found a
native mismatch in the caller scratch's third word: the original caller initializes
only X/Y, and the oracle had inherited a previous call's private stack value333.
The native fixture explicitly supplied zeroed scratch. OriginalA2 explicitly seeds
that scratch before the root, then all results match. A1 expectations/audit and
comparison stdout remain private; they are not accepted or reused as A2. No parent
algorithm repair was needed. A guard's numeric example was corrected before A1
execution, with extra native/sanitizer rebuild elapsed unavailable.

Thirteen Python checks, three focused CTests per profile and nine guarded
normal/sanitizer/uncached family replays pass. Prior complete refresh and resolved
zero-mode refresh projections remain unchanged. No complete inventory or closed
finalizer was rerun. Canonical expectation:
`private/boot-camp-20261019/surface-radar-pixel-fresh-a2/expected.json`, SHA256
`52fed53f55529e1debf83f16be4ed8dceb79f82188a554902a91a3f38d3309d6`.

OriginalA2 generation15.702s/native comparison.090s; A1 generation15.598s before
its comparison failure. Configuration7.765s/9.628s and initial builds3.359s/2.700s;
extra guard-only rebuilds, task wall and repair wall were not measured. Other
preflight/check/replay costs and hashes are in
`private/boot-camp-20261019/surface-radar-pixel-receipt-a1.json`. App/owner hashes
retain the earlier106-tick SDL walking baseline; no runtime/GUI adoption or rerun.
Local verification is not independent acceptance or whole-frame fidelity.

Preliminary next inspection only:
`private/boot-camp-20261019/radar-pixel-children-inspection-a1.txt` identifies stock
BSurface79AEF8 slot28 as7741D0 and inspects568280 through its returns. The former
uses the already recovered stock lock/format/unlock chain; the latter calls476AC0.
Those spans include trailing instructions and are not complete proofs.

## Commands and next integration

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake -S . -B build/native
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake --build build/native --target surface-radar-pixel-vectors
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_surface_radar_pixel
build/tools-env/bin/ctest --test-dir build/native -R '^surface-radar-pixel-domain$' --output-on-failure
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py --audit private/boot-camp-20261019/radar-pixel-local.audit.json tests/compare_surface_radar_pixel.py --exe private/official-1006-probe/game.exe --native build/native/surface-radar-pixel-vectors --expectations private/boot-camp-20261019/surface-radar-pixel-fresh-a2/expected.json --report private/boot-camp-20261019/radar-pixel-local.json
```

Use fresh private audit/report paths. Fresh originals replace expectations/report
with a new `--output` directory and need host Unicorn JIT permission. Sanitizer
runner is under `build/sanitize`; `--uncached` before the driver disables only
immutable inspection reuse. Original executions and native results are not cached.

Next compose actual floor/discovery/House/type/actor/resolver/pixel children on
shared owners.568280 and surface28 need complete recovery/verification; existing
55A280/568140/4F52B0/4E5580/C0/CC/663D30/24 must retain their caller contexts and
existing refusals. Stock surface startup/association, coverage/redraw/power,
production owned/warm/scan and diplomacy/action37 remain open. Ordinary SDL Boot
Camp Objective1 and both games remain incomplete; goal active. Existing walking:
`./build.command`, `./run.command --boot-camp-walk`; broader tests `./test.command`.
No workers, Windows actions, downloads, publication or runtime-read expansion.
