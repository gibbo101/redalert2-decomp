# GI Mark redraw on the shared Tactical owner

This removes an entered movement/startup effect before live Boot Camp Day1
sight and Objective1 integration. Production GI Mark now reaches the recovered
map redraw argument-zero path on the same Tactical `+D7D` byte already owned by
the Cell redraw queue. It does not enable sight, structure discovery, objective
progress or original frame scheduling.

## Behavior and ownership

Exact supplied executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain separate. Existing base inspection pins complete
Object/map redraw `5D36E0`/`4E09A0`; see [REDRAW_1006.md](REDRAW_1006.md) and
[INFANTRY_MEMBERSHIP_1006.md](INFANTRY_MEMBERSHIP_1006.md). No new address-derived
runtime data, dependency or public code was introduced.

`requestMapRedrawZero` extracts the already recovered argument-zero path:
nonnull Tactical gets byte1 at `+D7D`, null Tactical produces no write. No map
mode or counter field is read or written. The existing general redraw function
uses this same helper before its unchanged nonzero-mode branch. Boot Camp binds
the helper to `BootCampVisibilityWorld`'s actual `CellRedrawQueue::dirtyD7D`;
there is no mirrored redraw byte or new map/Tactical representation.

The visibility owner is now constructed before initial GI Mark. Its constructor
does not invoke resident services. Startup Mark retains its prior supplied true
visibility callbacks, followed by binding the actual visibility queries. This
is still a portable startup association, not original constructor/loader order.
Its actual GI redraw stores now dirty the existing Tactical owner without
inventing Cell redraw queue entries. Clones preserve that queue and rebind Mark
to the cloned owner. No frame consumer/clear policy was invented: actor `+75`
and Tactical `+D7D` stay dirty until a verified consumer is integrated.

Inspection of destination/reset callers also shows that animation4DC is gated
by actor `flag5C3`/`reset5CC`. Both remain supplied zero for this ordinary stock
profile, and existing walking/Stop/repeated-order/eight-direction tests complete
with an explicit refusing animation callback. The former silent no-op is gone.
A forced actual Stop/reset test proves refusal after the original `5CC=0` store;
it is not an original animation proof or a rollback promise. Complete504740,
sequence timers/selection and drawing phase remain unrecovered. They are not a
prerequisite for the currently tested zero-gate path; recover them when an
entered lesson/interaction needs them. Renderer phase remains approximate.

## Evidence and limits

Both current normal and ASan/UBSan profiles explicitly replay17,272 original
redraw cases plus285 Infantry and594 Unit membership sequences:18,151 reuse
hits/profile, zero misses. `compare_membership_current.py --family redraw`
extends the existing adapter only for the changed kernel: it validates the
untouched historical receipt, exact binary inspection and every recorded
original Python dependency, then runs all current native commands. Current
native/build/runner/adapter identities stay separate. No original generation,
receipt relabeling or cached native result was used. Separate parent/child
proofs do not establish a combined original Boot Camp journey.

Actual-owner checks cover initial dirty state/no Cell queue append, actor-before-
Tactical store, raw nonzero actor gating, repeated clear/request, source isolation,
warm clones/source destruction and no synthetic mission progress. The ordinary
eight-direction journeys and256-tick actual SDL interaction retain movement,
horizontal drawing, Stop and repeated-order coverage. Local verification is not
independent acceptance or full rendering fidelity. Arrival/sight remain off.

Costs, hashes, logs, actual completed checks and unavailable measurements live
in `private/gi-mark-redraw-receipt-a1.json`. Original generation cost is zero;
replay costs are measured separately from builds and owner checks. Only Apple
Silicon macOS is tested. Base RA2 and Yuri's Revenge remain incomplete.
Actual owner checks took6.45/73.73s normal/sanitizer; CTest wrappers3.09/18.10s.
Redraw replay comparison took.304/.395s. Both full builds,13 focused Python
tests, `test.command`,201 normal/200 sanitizer CTests and SDL256ticks pass.
Build/SDL/manual-review/total task wall costs were not separately measured;
concurrent costs are nonadditive. No build, comparison or SDL attempt failed.

## Reproduce

```sh
./build.command
./test.command
env DEVELOPER_DIR="${DEVELOPER_DIR:-/Library/Developer/CommandLineTools}" \
 build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/native/boot-camp-walk-check private/official-1006-probe
build/sanitize/boot-camp-walk-check private/official-1006-probe
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
 tools/run_evidence.py --audit private/gi-mark-redraw-next.audit.json \
 tests/compare_membership_current.py --family redraw \
 --exe private/official-1006-probe/game.exe \
 --native build/native/redraw-vectors \
 --expectations private/traversal-1006/redraw/expected.json \
 --report private/gi-mark-redraw-next.json
# Substitute build/sanitize/redraw-vectors and new outputs for sanitizer replay.
# Infantry/Unit membership replay commands remain in their subsystem notes.
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest \
 test_infantry_membership test_redraw_evidence
./run.command --boot-camp-walk
./run.command --boot-camp-walk-smoke-test private/gi-mark-redraw-sdl-next
```

Next bind the actual viewport/queue consumers and finish the remaining entered
movement/sight producers and mission children before ordinary SDL Objective1.
Retain explicit refusals and recovered shared-owner kernels.
