# Admission over actual prepared owners

`BorrowedPreparedUnitAdmission` is a separate, unwired admission binding over
the production prepared membership, map and actual Unit/Drive records. It has
no refresh copies. The existing value-world API and the borrowed binding execute
one typed implementation of terrain/admission, moving-resident, gate and
next-Cell decisions. This is a dependency checkpoint, not Process/Scatter
adoption or a new playable capability.

## Owners and identity

| Consumer | Actual owner |
| --- | --- |
| Mission and House | Membership-bound `UnitDiscoveryActor`, including its actual owner field |
| Next and primary/elevated heads | `PreparedUnitMembership::membership` actor/Cell records |
| Occupation words | `PreparedUnitMembership::occupation` |
| Signed level, ramp, flags, land, point | Mutable `MapCellAttributes::input` |
| Position, destination, head, body, track/index, eligibility, queue head | Exact membership-bound `GroundDriveProcessState` |
| Target494 | Explicit per-actor `UnitDestinationState` additional owner |
| Registry, House index/allies, speed bits, direction words, tick | Explicit shared supplied records |

Admission Cell IDs translate explicitly to the prepared membership's Cell IDs;
they do not replace its head storage. Target494 reads the actual pointer each
time. Actor associations map to their explicit IDs; Cells map to a non-actor
identity (-2). Null remains -1; unknown targets refuse. Admission destination1B0
is a distinct supplied field, not Drive destination or target494.

The binding checks exact Drive/mission addresses, distinct actor/Cell owners and
the complete slot association without floor/coordinate/permission queries or
lazy initialization. It is immovable. All referenced records, containers, Drive
data and the lvalue numeric service must outlive it and retain stable storage.
Rebind over clone-owned records; do not copy its callbacks or reference maps.
Full production clone/preview adoption remains unimplemented.
The extra destination record also provides timer530/558 storage for the later
caller join; admission does not consume or verify those timers here. Building
gate actors remain outside this prepared binding's Unit-only profile.

Missing-slot lookup forwards through prepared membership exactly once, before
the read-only admission fallback event. Map, membership and visibility fallback
points change immediately. No trace callback performs synchronization. Saved
numeric Cell words are explicit values so later fallback writes cannot turn a
saved point into a live alias. Gate/next-Cell fallback uses the same forwarding.

## Exact original evidence

Target: `private/official-1006-probe/game.exe`, 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Existing base703040/4C8730 and actual
moving children are reused; no new original address or upstream behavior is
assumed. No external code, headers, extracted table or dependency is incorporated.

Canonical: `private/map-depth-1006/borrowed-unit-admission-v3/`.
**187 scenarios /241 original calls /1,020 distinct instructions** match native.
Root codes0/1/2/5/6/7 and terrain codes0/7 execute. Distinct resident Drive/body/
target/House fields, occupation/speed, signed heights/ramps, mission-target
decisions, saved words and repeated shared fallback are covered. The root mover
is actor0; resident actor1's actual children execute. This is not complete
Process1 or a complete two-Process proof. Three additional original fixture
actors remain unchanged and unreachable; they are not native substitutes.
Initial records/associations, type restrictions and numeric inputs stay supplied.

Current normal/sanitizer replays and a fresh control with inspection reuse
disabled retain every command, label and output. Original arenas, instructions,
ordered events, registers/stack and immutable numeric data retain the existing
oracle audits. New ownership checks exercise post-binding owner changes, exact
addresses, no-query binding, retained lazy floors, single fallback forwarding and
five malformed-association refusals. These native checks complement original
execution; they do not independently establish original behavior.

The refactor freshly retains all earlier direct legacy projections:

| Family | Scenarios | Original calls |
| --- | ---: | ---: |
| Stationary admission | 2,391 | 3,619 |
| Moving admission | 3,666 | 3,666 |
| Gate interaction | 2,074 | 2,494 |
| Next-Cell early paths | 567 | 613 |

All four pass current normal/sanitizer replays. Source lists now include the
newly exposed header/numeric dependencies; tests traverse the quoted include
closure. Historical receipts and closed finalizers are unchanged. This is not a
refresh of the former 204-record gameplay inventory or all downstream families.
Full affected-family closure remains due at the production Process integration.

Audits, source/runner identities, commands, projections, costs and limitations:
`private/borrowed-admission-candidate-20261017/`. Guarded final fresh/normal/
sanitizer/control wall times are 1.327s/0.514s/11.427s/1.787s. Fresh generation is
0.738s and its native comparison0.129s. These are bounded test costs. The four
legacy final generations report 21.520s aggregate original generation; concurrency
is at most two original-test processes. They do not measure total task wall time
or game performance. Build wall time and manual review/repair time are unmeasured.
Narrower proofs remain at their own identities. One regression run caught a
missing transitive fingerprint; two final attempts refused a nonexistent source
path before original execution. Repairs and failed audits remain recorded.

1,133 Python tests, 67 normal/66 sanitizer root CTests, both new standalone
ownership CTests and `./test.command` pass. The rebuilt app passes the existing
1,573-frame actual SDL input/drawing workflow; its arrival image was inspected.
This rechecks the existing ordinary0/2/7 two-Rhino baseline. Runtime Scatter/6
remains refused. Local verification is not independent acceptance, an original
game observation or whole-frame fidelity. Only Apple Silicon macOS is tested.

## Reproduce

```sh
./build.command
./test.command
./run.command --owned-demo

DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake \
  -S tests/borrowed_unit_admission -B build/borrowed-unit-admission \
  -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_PREFIX_PATH=/opt/homebrew
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake \
  --build build/borrowed-unit-admission --parallel 6
build/tools-env/bin/ctest --test-dir build/borrowed-unit-admission --output-on-failure
# For the sanitizer variant use another build directory, Debug and -DRA2_SANITIZE=ON.

# Fresh original execution requires the authorized Mac host research context.
# Choose new private output/audit paths for every invocation.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/try-borrowed.audit.json \
  tests/compare_borrowed_unit_admission.py \
  --exe private/official-1006-probe/game.exe \
  --native build/borrowed-unit-admission/borrowed-unit-admission-vectors \
  --output private/try-borrowed
# For strict current-source replay replace --output with:
# --expectations private/map-depth-1006/borrowed-unit-admission-v3/expected.json
# --report private/try-borrowed-replay.json
# Use a new audit; select the sanitizer runner for that replay.
# An independent fresh control adds --uncached before the driver.
```

Whole-generation cache reuse remains limited to the eight reviewed drivers in
[ORIGINAL_RESULT_REUSE.md](ORIGINAL_RESULT_REUSE.md). This small new driver uses
strict receipts and fresh controls; it does not opt into that cache.

Next generalize the existing Cell/Unit/Advance/Process compositions to borrow
these same owners, then prove Process0 -> Process1 -> interleaved complete draws
-> later Process on distinct addresses. Full discarded command previews, warm
renderer/storage/association isolation and actual SDL displacement still precede
runtime adoption. Positive routing remains separate: destination assignment is
not movement, and any supplied direct-route phase must be explicit outside the
recovered roots. Preserve every entered child refusal, including mission7 null
destination handling. Base RA2, Yuri's Revenge and the full-game goal remain open.
