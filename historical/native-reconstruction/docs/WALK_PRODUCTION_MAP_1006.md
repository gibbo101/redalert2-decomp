# Walk fields on the production map and Infantry Mark dispatch

Walk now borrows live Cell level/flags instead of requiring its own value Cell.
`PreparedWalkMap` binds those views, coordinate/word lookups and floor queries to
the existing `MutableUnitMap`. This removes a production GI integration obstacle
without a dummy Drive, another map or another movement algorithm. Exact base
Infantry Mark dispatch also matches the existing Mark kernel. **Boot Camp remains
static: actual GI ownership/membership, animation/drawing, SDL walking and the
first objective transition are not delivered by this internal checkpoint.**

## Map ownership and preserved movement

`WalkMovementCellView` contains references to the actual signed-byte level and
flags plus an opaque binding identity. Lookup callbacks return the view by value;
this copies associations, not field values. All existing Walk preparation,
interpolation, crossing and arrival still use the single movement kernel.
Admission and dirty callbacks receive that same view. No query/store order,
arithmetic, queue, retry, command, refusal or application default was changed.

`assets/WalkCellView.hpp` adapts a `MapCellInput` without copying it. The existing
queued and committed movement diagnostics now use actual `MapCellInput` fields.
They preserve their supplied parity/old-new lookup policies; they are not suddenly
original production-world or terrain proofs.

`PreparedWalkMap` borrows the same map owner used by the two-tank application:

- It owns no Cells, attributes, occupation, fallback, floor cache or actors.
  Construction creates an identity index without querying or warming the map.
- World coordinates use the existing full signed-division/wrapped-index root;
  word coordinates use the existing signed-word lookup. Neither substitutes
  independent X/Y bounds or an extra Cell lookup. Misses use the actual common
  fallback and call the supplied association observer after its point is stored.
- Floor queries use that map's actual lazy floor state and Cell fields. Returned
  views remain live after later lookups, including when two misses alias fallback.
- Admission/dirty consumers can recover the exact attributes owner with no query.
  Foreign identities and views assembled from different owners refuse.
- The stable map must outlive the binding/views. Clones need fresh bindings;
  callbacks/identities from the source must not be copied onto a clone. This adds
  no rollback promise, actor association or original startup claim.

`prepared-walk-map-check` exercises these properties on `MutableUnitMap`, including
cold construction, signed-coordinate aliases, shared fallback/observer order,
foreign/mixed-owner refusals, clone isolation and an actual movement crossing.
The crossing changes the old Cell during the next lookup and checks the late
bridge decision; a copied level would produce a different result. These are
native binding checks, distinct from exact-original evidence.

## Actual Infantry Mark verification

Before using addresses, the supplied base executable was rehashed:4,485,392 bytes,
SHA256 `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Private exploratory inspections are not
proof; the first inspection also included an unestablished table guess, which
the actual dispatch inspection supersedes. No guessed table enters the oracle.

The actual Infantry vtable7A3540 selects Foot Mark4C2E60, Object5D4160,
Techno6C2550, kind509800 (15), type tail6C12C0 ->506950 (actor+5A8),
image6D3E50, House6C7420, word coordinates41B320 and redraw5D36E0.
The nonnull Walk interface7AEAD8 selects layer71FAA0, returning2 with its actual
callee stack cleanup. Base cast40DC20 independently selects identity for kind15.
`tools/verify_infantry_mark.py` checks14 ranges,10 dispatch entries and the cast
data identity; Unit/YR naming is not the behavioral source.

The unchanged existing `UnitMark` implementation matches all three actual
Infantry roots. Foot mode2 bypasses its parents. Other modes retain limbo/on-map/
dirty gates, ordered image/owner/word-coordinate queries even on rejection,
special event13 after accepted Techno Mark, and the layer plus repeated coordinate
query before map insertion/removal. Infantry's own type and Walk dispatch execute
in the original guest; no tank type/Drive is substituted there.

Canonical original-only receipts:
`private/infantry-walk-20261018/infantry-mark-fresh-a1/{expected,report}.json`.
**645 sequences /921 complete original roots** match, including byte gates,
mode2 bypass, signed unknown modes, nullable type, image/House values, repeated
mark/unmark/redraw and full signed-coordinate/word boundaries. Actual child
counts include528 image/type/House queries,636 coordinate queries,108 Walk layer
calls and668 selected stores. Map insertion/removal (108 calls), special-event
effects (18), initial actor/type/House/Walk/Tactical records and supplied frame
dirty resets remain services/inputs. Actual Infantry membership, linked-list/
occupation/discovery/recalculation and its Walk caller join are **not** established.
No production GI startup, original gameplay observation or whole-frame claim.

The oracle guards unchanged code/dispatch/cast tables, ABI/callee-saved/caller
stack, selected writes and remaining actor/type/House/Walk/Tactical arena.
Expectations are saved before current-native comparison. Original identities
and receipt hashes are checked separately from rebuilt native source/runner
identities; native results are never cached. All normal/sanitizer/uncached Mark
replays have645 hits, zero misses and zero original execution. Current rebuilt
Unit regressions retain4,263 sequences /11,667 roots against their old receipt.

## Regression and costs

Normal/sanitizer `map-{route,queued,walk-admission,walk-speed,command-process,
arrival,movement}-*-a1` replays retain all165/580/199/121/251 sequences and380/624
arrival/committed roots. Route's uncached inspection control also retains165 hits
and zero misses. No old originals were regenerated or receipts relabeled for the
native-only view change. Eleven focused CTests per build and103 focused Python
tests pass. No broad capability closure or SDL rerun was needed; the application
and static preview behavior did not change. Local verification is not independent
acceptance.

Fresh Infantry Mark original generation0.201s; normal/sanitizer/uncached replay
driver times0.258s/0.397s/0.592s (native0.009s/0.114s/0.009s). Route replay driver
times0.426s/1.379s/3.223s. All seven walking-family wrapper totals4.576s normal /
8.182s sanitizer; concurrent work overlaps, so these are not task totals.
New map-check builds1.37s/1.38s; Mark runner relinks0.49s/0.56s. CTest bodies
0.13s/0.68s; the passing103-test Python body1.579s. Initial multi-target builds
were partially yielded and their full elapsed cost was not measured: make
regenerated CMake and built the three old targets, but needed a second invocation
to recognize the new target. One pre-generation Python check had an overstated
scenario-count floor; correcting it changed no original inputs or answers.
Total implementation, inspection, manual repair and task-wall costs are unavailable.
Private `map-validation.json` records identities, receipts, costs and failures.

## Reproduce and continue

```sh
./build.command
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/native \
  --target prepared-walk-map-check walk-queued-vectors unit-mark-vectors --parallel 6
build/native/prepared-walk-map-check
env PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_infantry_mark test_walk_route

# New report/audit names; execute current native against saved originals.
env DEVELOPER_DIR=/Library/Developer/CommandLineTools PYTHONHASHSEED=0 \
  PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/infantry-mark-next.audit.json tests/compare_infantry_mark.py \
  --exe private/official-1006-probe/game.exe --native build/native/unit-mark-vectors \
  --expectations private/infantry-walk-20261018/infantry-mark-fresh-a1/expected.json \
  --report private/infantry-mark-next.json

./test.command
./run.command --boot-camp-preview
```

For sanitizer replay, build/select `build/sanitize/unit-mark-vectors` with
`RA2_SANITIZE=ON`. Add `--uncached` before the comparison driver for an inspection
control. Fresh changed-original generation replaces expectations/report with
`--output private/NEW_DIRECTORY` and uses the authorized macOS-host Unicorn JIT.
Walk route and old-family exact replay arguments remain in `WALK_ROUTE_1006.md`
and current private audit `arguments` arrays; replace report/audit destinations.

The last command still runs the **static** preview. Next bind actual GI/E1
actor/type/timer/target/queue and Infantry membership/admission/occupation to this
same production map, sharing the existing policies. Recover encountered moving
retarget, route-failure and animation/drawing children before ordinary SDL walking.
Actual discovery/scheduler/actions still precede the first objective transition.
No new dependency, extracted data, runtime executable read, Windows action,
download, system change or cache framework. Only Apple Silicon macOS is tested;
the full-game goal remains active and base RA2/YR remain incomplete.
