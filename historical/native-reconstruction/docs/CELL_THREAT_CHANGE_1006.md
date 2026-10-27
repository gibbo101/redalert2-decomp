# Cell threat changes during tutorial GI ownership transfer

The first Day1 Team's Script20/13 needs to hand its four existing GIs to the
player. The discarded actual-owner transfer diagnostic now reaches the ownership
store after completing the old threat removal on the existing map/House grids.
It refuses **before** that store because Walk still borrows startup House index,
speed and human/control references. No partial clone is adopted, and Script20,
live Team AI, arrival/sight and SDL objective scheduling remain off.

## Recovered algorithms

`src/sim/CellThreatChange.hpp` reconstructs complete476B20,4E5DC0,4E5500 and
4F52F0, reusing the existing complete54E370 projection from `HouseThreat.hpp`.
476B20 snapshots both Cell+24 words before projection, saves the result and delta,
and traverses House slots forward. It rereads the count and backing each iteration,
skips null slots and direct index30 equality, then queries control and alliance.
An uncontrolled House bypasses alliance lookup but still receives the update.
Mode zero normalizes134-or135 to0/1; nonzero mode returns raw134. Alliance tests
self-index equality before the index-1 bypass, then masks the shift to five bits.

4E5DC0 negates negative deltas with32-bit wrapping. INT_MIN therefore stays
negative. Each of nine entries uses arithmetic right shift with a masked count,
wrapped slot arithmetic and wrapped add/subtract. Every arithmetic store precedes
a separate zero store if the result is negative. Repeated stencil slots observe
earlier stores; zero delta still clamps initially negative grid entries. There is
no widened accumulator, positive-only magnitude or saturation to INT_MAX.

Native bounds and identity checks refuse invalid owned memory; this is not
original fault parity. The optional store observer records already-performed
stores for diagnostics. Diagnostic registry/Cell mutations test live rereads and
the saved projection; they are supplied harness effects, not observed gameplay.

## Shared owners and explicit boundaries

`BootCampMissionWorld` owns persistent House pointer backing/count/span, pointing
to its existing canonical Houses. Numeric map order, initial count/allocation,
flags, masks and grid startup remain supplied. No copied House or transient
registry mirror is introduced. Clone construction copies retained slots/count,
rejects foreign backing/identities and remaps pointers to clone-owned Houses;
existing grid/score owners remain shared with the explicit rebuild entry.
These slots use whole-House identity; the older rebuild/score adapter uses the
same House's indexAlliance subobject identity. The adapters do not conflate them.

The private transfer entry borrows complete548000 lookup over the actual mutable
map table and shared fallback, then resolves that Cell identity to its stored
words and calls476B20. It resets the actual GI threat400 only after the update.
The flags14&4 alternative and later effects remain unbound/refused. Stencil words
are lent explicitly for one call. No runtime executable read, configuration
expansion, scheduler or new game dependency was added.

Actual-owner checks run before recruitment and after the real sixth Team tick.
They seed threat400=598 and existing grids1000, clear alliance masks on disposable
owners, and use an **authored alias stencil**. Only the projected grid word of
each non-owner House changes, reaching zero after nine subtractions; the old
House stays unchanged. Mark3/tagged discovery, actual Team references and Tag
count survive; ownership remains old. A subsequent call after source destruction
writes the clone-owned grids through its remapped registry. These are native
ownership checks, not a joined complete original transfer proof or stock-stencil
production acceptance. The616 earlier transfer expectations retain their supplied
map/threat-service scope.

## Original evidence and commands

Exact supplied base:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Complete inspected spans are476B20:122,
4E5DC0:106,4E5500:50,4F52F0:35 and54E370:48 bytes. The research driver reads the
hash-pinned stock stencil at7D9FA0/7D9FC4; extracted numbers stay private. Some
commands explicitly replace those data tables with authored alias/shift profiles.
Original instructions are unchanged, including every child; no lifted code or
public implementation was incorporated.

Canonical origin: `private/transfer-cell-threat-20261020/fresh-a2/expected.json`.
All1,204 comparisons match ordered grid writes, final grids, helper low bytes,
caller ABI, immutable code/tables/globals and the entire private arena. Coverage
includes signed extrema/INT_MIN, overflow/clamping, zero delta, stock and alias
stencils, masked shifts, null/duplicate House slots, control/alliance/index gates,
signed projection and six live count/backing/saved-Cell mutation diagnostics.
The earlier1,198 passing a1 results retain their narrower scope. A2 adds those
six diagnostics and their final registry/Cell projections; it is a new generation,
not a relabeled receipt. Original expectations contain no native answers.

```sh
./build.command
./run.command --boot-camp-walk
./test.command
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  -m unittest test_cell_threat_change

# Replay current native against canonical originals; use a fresh report/audit name.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/cell-threat-next.audit.json \
  tests/compare_cell_threat_change.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/cell-threat-change-vectors \
  --expectations private/transfer-cell-threat-20261020/fresh-a2/expected.json \
  --report private/cell-threat-next.json
```

Use `build/sanitize/cell-threat-change-vectors` and distinct outputs for sanitizer
replay. Fresh generation replaces `--expectations/--report` with
`--output private/cell-threat-fresh-NEW` and needs research JIT permission.
The comparator verifies the exact executable, complete original Python closure,
environment, immutable origin receipt and exact commands. Native source/runner
identity is separate and current native always executes. No native pass/fail is
cached. Current broader checks and measured costs are in opening HANDOFF and
`private/transfer-cell-threat-20261020/validation-a1/`.

Next rebind Walk and membership House references before owner1B4, audit selection
and palette consumers, then join new threat/registration/sight/wrapper children
and actual Script20 House lookup. Ordinary SDL objective acceptance and initial
instructions remain required. Both games remain incomplete; only Apple Silicon
macOS is tested. Local verification is not independent acceptance or whole-frame
fidelity.
