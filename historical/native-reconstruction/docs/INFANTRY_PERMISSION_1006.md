# Infantry permission and persistent Boot Camp actor state

This recovery unblocks live Boot Camp sight by fixing one shared actor field.
The previous preview stored sight's active byte32D separately from the actual
Infantry byte consumed by admission. Sharing the byte exposed the previously
refused permission branch on the next movement admission. That branch is now
recovered; live arrival sight remains disabled pending the Cell/discovery join
identified below.

## Original algorithm and evidence

The supplied executable is 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. No original instructions are changed.

Complete Infantry admission503190 first preserves its existing registry, Foot
terrain and elevation decisions. Nonzero actor32D with loadingA40774 equal zero
then calls direct-Cell permission55A740 with the actual target Cell and byte1.
There is no extra map lookup. Permission success continues to the existing
overlay/list/speed/occupation decisions. Denial invokes Infantry vtable2F4,
which resolves to complete Foot4C8CA0; a false low-byte result returns7 before
those later decisions.

Foot4C8CA0 tests active32D, queries the actual dynamic type through
6C12C0 -> Infantry506950, and returns true for nonzero typeAA0 or late actor32C.
Otherwise it queries actual Mission594770 and accepts mission4. Only afterward
it reads Team4C4 and conditionally calls6BA990. Initial zero32D returns false
without queries. Preserve this order and the live late field reads. The native
helper refuses an entered unbound Team child rather than guessing its result.
The Team predicate remains supplied in the original test fixture.

Pinned complete ranges:

| Root | Bytes | SHA256 |
| --- | ---: | --- |
| Infantry503190 | 2221 | `28fb452d22b3f5238f05154429cb9aeea976f5dc43a2883da0e7959ec4e61b42` |
| Permission55A740 | 175 | `2f6e2d12a42eb3ee7ab57173269c38cba15023ef9d4e097e80abb21180b2f5ee` |
| Foot4C8CA0 | 89 | `433aa7d379fd25fcb7922ef4c47580710d83f313d3ee788a8de121c899c9e5f7` |

The new complete original fixture executes 66 Infantry roots: 61 actual direct
permission calls, 27 complete Foot override calls, and two supplied nonnull Team
calls. Cases cover direct permission success/denial, raw flag/type/Team results,
mission4 short circuit, loading/zero-active bypasses, signed Cell/ramp/height
geometry and retained speed-zero/NaN/negative/occupation tails. Existing actual
Foot/registry/neighbor/House children remain joined. ABI, declared immutable
inputs and the entire actor/type/House/registry/Cell arena retain their audits.
The inactive standalone Foot entry is inspected and native-tested; the admission
caller naturally bypasses that entry when actor32D is zero.

Canonical original-only receipt:
`private/boot-camp-20261018/infantry-permission-fresh-a3/`.
Expectation SHA256:
`b5bf95ac8f11476be7167f79534fa1ad92437f04bd3bc4cc54cac3bec813061d`.
Normal/sanitizer/uncached-inspection replays all pass66/66. Original generation
was0.148s and fresh driver0.451s. Replay driver times were0.260/0.268/1.276s;
native comparisons alone were0.012/0.077/0.008s. Attempt a1 diagnosed a missing
Infantry506950 getter in the new fixture's inspected ranges; a2 passed directly,
and a3 records the guarded canonical run. Failed attempts retain their scopes.

## Production ownership correction

`PreparedInfantryWalk` now binds direct permission to the actual target
`MapCellInput`, the shared permission shape and the existing
`nearbyCellPermitted` kernel. Binding makes no queries. The override borrows the
actual actor32D/32C/Team and typeAA0/mission records. Other residents, overlays,
hostile weapon queries and unbound Team effects keep their prior refusals.

Boot Camp sight removal, addition, the position tail and movement admission now
borrow the one `InfantryWalkState::flag32d`. The previous duplicate sight field
is gone. The bounded host startup explicitly supplies1 to that shared byte;
low-level record defaults stay0. Startup authenticity is not claimed.

Position fields228/208/34/1B8/418/454/456/77/59A/59C now persist per actor.
Flag373 borrows the existing discovery record's current373 byte.
The scratch global is owned once per Boot Camp world. Bridge79 comes from actual
ground state, and the locomotor predicate consumes the actual Walk owner's raw
moving byte. The per-call token, copied bridge and reset temporary state are gone.
Other initial type/field associations remain supplied.

The discarded owner preview can advance two actual consecutive arrival callbacks
on the same disposable graph. The first clears59A/59C/scratch; the next observes
those zeros rather than resetting them. Its second sight update removes old
sight before adding new sight. The original single-callback proof retains its
scope; this repeated production-owner composition is native integration evidence.
Source actor/order/mission/visibility/persistent state remains unchanged. Preview
still requires initialized source tick/position, validates the actual Cell target
and bounds notification count and Process calls; it is not a warm-world clone.

## Regression and current capability

Full normal and sanitizer builds pass. Current checks pass114 normal CTests,
113 sanitizer CTests and1,347 Python tests (1.96s/8.08s/45.41s). Both private-data
Boot Camp owner checks pass, including eight directions, Stop/repeated orders,
refusal isolation and the new persistent callback sequence. A focused native
ownership check verifies late32C/Team reads after callbacks, early query bypasses
and missing-Team refusal; it does not claim original diagnostic mutation behavior.

The affected original expectations are reused unchanged: all1,600 standalone
admission sequences/2,660 roots and92 production Walk journeys/4,061 roots pass
normal and sanitizer comparisons. These old inputs retain their original active-
byte profiles. They do not substitute for the new66 entered-permission roots.

Fresh actual host-display SDL input/drawing passes at
`private/boot-camp-20261018/infantry-permission-sdl-a2/`:106 ticks, selection,
movement, pause, refused retarget, Stop, repeated order and deselection. The report
retains `objectives_enabled: false`. Build, manual repair and total interactive
wall costs were not instrumented. Verification is local, not independent acceptance.

## Reproduce

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
./test.command
build/native/boot-camp-walk-check private/official-1006-probe
./run.command --boot-camp-walk

env PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/infantry-permission-next.audit.json \
  tests/compare_infantry_permission.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/infantry-admission-vectors \
  --expectations private/boot-camp-20261018/infantry-permission-fresh-a3/expected.json \
  --report private/infantry-permission-next.json
```

Choose fresh private audit/report paths. For sanitizer replay substitute
`build/sanitize/infantry-admission-vectors`; for inspection control add
`--uncached` before the driver. New original execution uses a fresh `--output`
instead of expectations/report and requires Unicorn JIT permission. Retain all
executable/source/environment/runner/input/receipt guards.

## Next actual live-sight dependency

The preview still supplies Cell12C flags as zero. Actual reveal/change sets
Cell+12C mask0x10. Exact position-tail6C2C09 tests that bit; when set,6C2C1C calls
Infantry vtable180 -> Techno6C2440 with current player HouseA35DB4, before dirty
47BB30. That child is not joined here. Recover it and bind the actual shared
visibility12C/140 fields rather than hiding the branch behind supplied zeros.
Then integrate complete arrival effects on live owners and validate ordinary
SDL discovery and required mission action children. Arrival notification remains
no-op; no objective success, visible fog, action effects, whole-frame fidelity
or full-game reconstruction is claimed. No workers, Windows actions, downloads
or new runtime executable reads were used.
