# Actor radar marker insertion and removal

The subsequent [actor caller composition](RADAR_ACTOR_MARKERS_1006.md) now
recovers the six registration/removal/dirty wrappers and6328D0 on these same
owners. The final next-caller section below records the earlier inspection;
complete6D8120 placement and scheduling still remain open.

`RadarMarkerBuckets.hpp` joins complete631910/631AF0 to stock dynamic marker
vector634E40/634F50/634BC0, rectangle411290, Infantry/Building kind509800/453C40,
dirty632620/point resize and the existing CRT783290 transfer algorithm. The actual
Boot Camp adapter lends existing GI/Building/House owners; RadarStorage owns the
same256 buckets used by both drawing branches, plus the preceding shared bitmap/
dirty-point vector. This removes the manually populated bucket boundary from the
actual-owner check. It is an explicit unscheduled composition, not a live radar.

The lesson dependency is original marker production beneath radar refresh on the
sight/discovery path to Day1 Objective1. Actor footprint/placement callers and
scheduling must still be joined; these explicit calls do not discover a structure,
advance arrival or complete an objective. Base RA2 and YR remain incomplete.

## Identity and recovered behavior

Exact supplied base:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Fingerprinting precedes addresses. Embedded1.08, supplied1.006 lineage, reported
no-CD provenance and unverified pristine authenticity remain distinct. Exact
complete spans, stock virtual associations and CRT branch tables are pinned;
original instructions execute unchanged only in research Unicorn. No external
authored/generated/lifted code or new dependency was incorporated.

631910 obtains and saves all four rectangle words before its bounds decision.
Out-of-bounds stock Buildings return without stores or dirty/queue effects.
Other actors clamp x then y using wrapped rectangle sums, then store actual
actor1A0 followed by1A4. In-bounds insertion does not write those fields. The
bucket is `(uint32(x)-uint32(y)*5)&255`. Duplicate actor/x/y returns before Owner
comparison, allocation or refresh. Its fourth word is ignored for equality.

The current House identity is saved before the direct Owner1B4 comparison.
Player-owned actors prepend; others append. Both preserve the raw ownership and
positive-growth gates. Successful prepend uses the existing overlap transfer
algorithm, moving aligned logical dwords backward, then writes actor/x/y/actor
and increments count. Append increments count before those entry writes.
Failed/disabled growth still calls632620 and sets14D5=1. The child and parent
dirty stores remain separate; duplicates bypass both. Stock kind getters return
constant15/6; their association is independent of supplied constructor state.

634E40 initializes **only the first three words** of every newly allocated slot.
Its fourth word retains supplied heap contents until overwritten or copied.
Resize copies all four words of every old **capacity** slot, including inactive
tails, then preserves release/backing/capacity/ownership/count-clamp order.
Null allocation restores valid1 but preserves prior backing/capacity/count/owns.
The null-external-argument profile is exactly the parent call profile. Complete
634BC0 clears count first, releases only owned backing, retains external pointers
and clears owns/capacity. Native heap allocation/content remains supplied.

Complete634F50 searches count rather than capacity and ignores valid. It compares
only actor/x/y.631AF0 decrements count before shifting all four words forward,
keeps inactive tails, then invokes the actual dirty producer and sets14D5. A
missing match skips those effects. Native guards refuse missing/foreign owners
and out-of-backing or excessive entered work; they are execution bounds rather
than recovered clamps, rollback or a replacement movement policy.

`SurfaceMarkEntry::trailer` can now retain the repeated logical actor identity
on a64-bit host. The former `padding` name was misleading: older drawing fixtures
retained opaque numeric sentinels there, and those consumers still ignore it.
Native structure sizes are not original binary layouts. `SurfaceMarkBucket`
retains count plus capacity/growth/valid/owns on the same record read by drawing.
The shared overlap transfer was factored within `SurfaceCopy.hpp`; its existing
surface-copy wrapper still uses the same alignment/direction/dword/tail logic.

## Actual owners and lifetime

`BootCampRadarActors::markerServices` maps kinds, Owner and clamped1A0/1A4 to the
actual existing GI/Building/House owners. New coordinate fields have explicitly
supplied zero startup; no constructor or automatic writer is inferred. The
adapter makes no game query at construction. Foreign identity resolution refuses.
RadarStorage supplies native allocation and empty initial buckets, owns all
backing, and shares those bucket references with existing mark/pixel refresh.

The actual Day1 check inserts nonplayer then player GI at one controlled point,
verifies prepend/duplicate/trailer identity, draws both refresh modes, removes
the player to expose the nonplayer, and removes the final marker to restore the
actual terrain. It verifies inactive tails, offscreen Building bypass, actual GI
clamp stores and aliasing, foreign refusal and unchanged source world. Warm-clone
values persist. Active identities are explicitly removed before their old owner
dies, then the surviving clone is explicitly inserted/drawn/removed. This is
verified retirement/rebinding, not an automatic radar-storage cloning algorithm.
Owners must outlive their active entries and scoped callbacks; inactive tails are
retained and never resolved by drawing.

Coordinates, geometry, palettes/colors/indexes, initial bitmap state, startup and
diagnostic House/visibility inputs remain controlled. Full actor placement,
Building footprint/typeC78 selection, registration37B, dirty queue consumption,
refresh timing and live sight/SDL scheduling remain open. No app tick, movement,
arrival or objective callback adopts these services. No screenshot or self-
consistent native test is used to claim original frame/game fidelity.

## Verification and costs

334 fresh sequences match763 complete top-level original calls, including487
insertions,164 removals and112 direct vector/find/clear calls. They enter332
actual dirty roots,125 marker resizes,180 stock finds,64 clears and30 CRT moves.
Corpora cover player/nonplayer precedence, duplicates, raw flags/valid, external/
owned/empty backing, failed/disabled growth, clamped coordinates/extremes,
offscreen Buildings, direct shrink/clear, four-word capacity/inactive tails,
repeated complete cycles and late surface/House/Owner mutations. The heap and
initial records/probes are supplied; all named algorithmic children execute
original code. Guards check entered spans, caller stack/return/callee-saved
registers, immutable inputs, allowed writes, ordered arena stores and full arena/
backing digests. This does not prove every possible input/native access width.

194 normal/193 ASan/UBSan CTests,20 Python checks and both actual-owner profiles
pass. Both rebuilt profiles reuse334 new,271 coordinate/dirty,940 coverage/refresh
and3,804 surface-copy expectations:5,349 hits/profile, zero misses. These retain
separate proof scopes; no original matrix was regenerated after native changes.
New original generation1.159s. Broad builds31.099/39.961s, CTest driver wall
5.954/14.796s. Owner-test repair builds10.156/10.010s, final owners4.168/45.210s.
Python body3.654s. Configuration/inspection/edit/preflight/total task wall is
unavailable; concurrent durations are not additive.

The first owner preflight and both A1 owner profiles failed an older assertion
that assumed an empty dirty queue. The new marker composition correctly retains
entries on the shared queue. Both running profiles finished before the test-only
repair changed checks to prior-count-plus-additions; originals were reused.
Failed A1 logs/costs remain at their true scope. A1 CTests passed and their inputs
were unaffected by that later owner-test source repair. No comparison guard was
weakened or receipt relabeled. Source/binary hashes, commands, costs and failures:
`private/boot-camp-20261020/marker-buckets-receipt-a1.json`.
Initial receipt assembly referenced a nonexistent sanitizer SDL application;
that profile is headless. The corrected receipt hashes its actual runners and
the native SDL application, without attempting to build an unavailable target.

Only Apple Silicon macOS is tested. Local verification is not independent
acceptance. No new executable/runtime read, Windows/download/publication/system/
Xcode/DRM action, source-installation change, dependency or proprietary tracked
content was introduced. No SDL ceremony was repeated for unscheduled services.

## Next production caller

Private hash-checked inspection identifies stock Infantry registration6D74D0,
removal6D7500 and dirty6D7530, with late37B stores after their child returns.
Building451800/451860/4518C0 iterate live footprint vectors selected by6328D0
from typeC78. Stock tables map420/424/428 to those distinct families. These are
inspected hypotheses, not yet complete differential/native implementations.

Complete placement6D8120..6D83C4 additionally uses discovery,2F8 permission,
screen geometry, original projected coordinates, registration37B and repeated
timer reads/flash update. Recover/join those actual callers on these same owners
before invoking marker placement from sight or SDL. Keep full-path dependencies
explicit; do not manufacture registration, discovery or objective success.

## Reproduce

```sh
./build.command
./test.command
build/native/boot-camp-walk-check private/official-1006-probe - private/boot-camp-20261020/radar-shape-dimensions-a1.bin
build/sanitize/boot-camp-walk-check private/official-1006-probe - private/boot-camp-20261020/radar-shape-dimensions-a1.bin

# Explicit original-only reuse; choose new report/audit paths each time.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
 --audit private/marker-buckets-next.audit.json tests/compare_radar_marker_buckets.py \
 --exe private/official-1006-probe/game.exe \
 --native build/native/radar-marker-buckets-vectors \
 --expectations private/boot-camp-20261020/marker-buckets-fresh-a1/expected.json \
 --report private/marker-buckets-next.json
# Repeat with build/sanitize/radar-marker-buckets-vectors and fresh paths.
PYTHONPATH=tools:tests build/tools-env/bin/python -m unittest tests/test_radar_marker_buckets.py

# Existing walking checkpoint; no new live radar or objective transition.
./run.command --boot-camp-walk
```

Affected prior commands use `tests/compare_radar_marker_placement.py` with
`marker-helpers-fresh-a1/expected.json` from20261020;
`tests/compare_coverage_radar_refresh.py` with
`coverage-radar-refresh-fresh-a1/expected.json` from20261019; and
`tests/compare_surface_copy.py` with `surface-copy-fresh-a3/expected.json` from
20261019. Each explicitly supplies `--expectations` and new `--report`/`--audit`
paths, as recorded in the private A2 replay artifacts. Original expectation
provenance remains separate from current native validation.
