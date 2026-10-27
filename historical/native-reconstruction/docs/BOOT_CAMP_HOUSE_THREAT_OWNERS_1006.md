# Production House threat-grid ownership

The explicit `BootCampWalkWorld::composeHouseThreatGrid` entry now rebuilds a
selected canonical mission House's grid using the five existing GIs, two existing
objective Buildings and actual mutable map/Cells/fallback. It reuses complete
grid4F3420/projection54E370, stock threat6D3E50/4532F0 and Object current-Cell5D51E0/
coordinate548000 kernels. Walking, SDL, MakeAlly and action37 do not schedule this
entry yet. Both games and Boot Camp Objective1 remain incomplete.

## Actual owners and supplied boundaries

Each canonical mission House has stable associated `HouseThreatState` storage:
0x4204 signed grid words, enemy54F0, count5504, score backing and a live score span.
Index30, mask5674 and flags134/135/13D are borrowed from the existing canonical
House, already shared by movement/discovery/visibility. There is no copied House
or synchronization pass. Grid startup zero, enemy-1, empty score allocation/count,
original construction/layout and future score population remain supplied. This
entry does not execute score/enemy updates or claim original heap initialization.

The seven-actor registry is the existing supplied scenario-order registry, with
separate live count/backing. GI flag76/onMap7D, mission Owner and stored454/456
words belong to existing mutable records. The latter remain supplied startup
values in `PositionState`; their original writer is still open. Do not substitute
cell450 or current coordinates to make a plausible threat map. Buildings borrow
their existing mission Owner/type/564 and resident coordinates. Their new onMap7D
starts at supplied1; unused stock Building454/456 words start at supplied0. These
are fields, not derived copies of visibility/occupation state.

`HouseThreatOwner` resolves logical Owner handles at the original late read.
Its getter only maps actual fields/identities and makes no gameplay/map query.
Legacy physical pointer bindings retain their behavior. The Building branch uses
two actual coordinate lookups on `MutableUnitMap::table` and its single fallback.
The full-table count association remains supplied262144. Coordinate lookup does
not enter the floor cache. All grid arithmetic, repeated kind queries, saved
threat, Owner filtering and ordered stores remain in the existing single kernels.

The caller explicitly lends eighteen private stencil words, rulesBE8 and invalid
Cell words for the duration of one call. No callback or input span is retained.
No configuration name/default for BE8 or original invalid-Cell initialization is
inferred. The application gains no file/executable/table read, prepared-data
format, automatic scheduler, command or UI. Research extracts remain ignored.

## Warm clones and checks

Mission clones copy every grid word and score/enemy/count value, retain uncounted
score tails/nulls, remap every nonnull score identity to the clone's canonical
House subobject, and rebuild score spans over independent backing. Foreign score
backing/identities refuse. Walk clones retain actual actor/type/map ownership and
rebuild callbacks; no source-bound function is copied. Stable House state cannot
be copied or moved independently. Refused clone construction never mutates its
source; this does not claim rollback for an entered grid failure after clearing.

Normal/sanitizer owner checks use an explicitly supplied private original stencil.
They exercise selected House-only writes, actual GI stored words versus current
position, changed Owner/alliance fields, Building Owner bypass/onMap7D/live rule,
Z-independent map lookup, full warm grid/score tails, remapped pointers, cloned
fallback writes, untouched source/floor cache, early foreign-House refusal,
foreign-score refusal and continued calls after source destruction. Existing full
warm movement/visibility/mission/message/renderer isolation checks also pass with
the expanded source snapshot. Without the optional private input the owner check
uses an authored zero-offset/shift stencil solely for ownership regression.
These native ownership checks are not a new original whole-production-chain proof.

## Original evidence and final checks

Exact supplied executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD and unverified pristine remain
distinct. No public/YR/recomp code or dependency was incorporated.

Two fresh changed-binding proofs retain all prior commands, labels and original
outputs. The joined vector uses the new logical live Owner accessor; the legacy
parent retains physical pointer bindings and its late mutation diagnostics.

| Proof | Fresh sequences | Original seconds | Native seconds | Canonical directory under private/boot-camp-20261018 |
| --- | ---: | ---: | ---: | --- |
| Complete grid/threat/Object Cell/map | 806 | 36.684 | 0.089 | owned-grid-fresh-a1 |
| Legacy grid/score/enemy/projection | 1,214 | 12.603 | 0.071 | owned-grid-parent-fresh-a1 |

Expected SHA256 values are respectively
`37113b08c555d6b29e86473cf2b276b6b1a3b747e82973e9e4e6ba3f5afed1a7` and
`e759e0d9eb7c3abfd922bb0ab035d99ae2c182b92de7fb9c256c0258a6c18a04`.
The unchanged projections are recorded in `owned-grid-prior-projections-a1.json`.
Existing complete original instruction/write/stack/arena/table audits stay active;
initial associations/probes retain each subsystem's documented supplied scope.

Both full builds,154 normal/153 sanitizer CTests, both owner checks,48 Python
tests and27 guarded normal/sanitizer/uncached replays pass. Replays cover joined
map/grid, prior grid/threat, stock threat, legacy grid/score, diplomacy/MakeAlly/
MakeEnemy, coordinate lookup and actor ground state. Rebuilt actual SDL walking
passes106 ticks with objectives/text disabled; it does not establish original
whole-frame fidelity or live grid/diplomacy adoption. The unrelated owned-tank
SDL profile was not rerun. Local verification is not independent acceptance.

The first SDL attempt failed before drawing because the sandbox could not access
macOS displays; the separate display-enabled A2 passes. The first normal replay
batch used nonexistent `house-make-enemy-fresh-a1`; corrected A2 uses the existing
`make-enemy-fresh-a1`. Six successful normal A1 replays were retained, not rerun.
Both failed attempts remain private. No original/native comparison mismatch,
identity bypass, receipt relabeling or closed finalizer rerun occurred.

Normal/sanitizer builds17.188s/16.754s; full CTests1.99s/10.84s; sanitizer owner
39.726s. Exact commands and remaining measured checks are in the build/validation/
replay records. Normal owner/SDL/repair/task-wall costs are unavailable. No caching
or whole inventory refresh was added. Receipt:
`private/boot-camp-20261018/owned-grid-receipt-a1.json`.

## Reproduce and next integration

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
./test.command
# Optional third argument: private SHA-prefixed eighteen-word research stencil.
build/native/boot-camp-walk-check private/official-1006-probe private/boot-camp-20261018/owned-grid-stencil-a1.txt
build/sanitize/boot-camp-walk-check private/official-1006-probe private/boot-camp-20261018/owned-grid-stencil-a1.txt
./run.command --boot-camp-walk
# Choose fresh audit/report names; do not overwrite original receipts.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/NEW-OWNED-GRID.audit.json \
  tests/compare_house_actor_threat_cells.py --exe private/official-1006-probe/game.exe \
  --native build/native/house-actor-threat-cells-vectors \
  --expectations private/boot-camp-20261018/owned-grid-fresh-a1/expected.json \
  --report private/NEW-OWNED-GRID.json
```

For the parent proof use `compare_house_threat.py`, `house-threat-vectors` and
`owned-grid-parent-fresh-a1/expected.json`. Use the sanitizer runner or put
`--uncached` before the driver for other profiles. Fresh original generation uses
a new `--output` directory and authorized research-only JIT. The stencil file was
prepared only by the hash-checking research `verify_house_threat.table_values`;
it is not a shipped asset or an application read path.

Next recover/bind the remaining map scan image/type effects and redraw/UI/session
services, then join actual score/grid/map effects into production diplomacy and
action37. Score population, Building7D and stored454 writers/startup remain open;
do not silently infer them from coordinates or other flags. Team/audio/live
scheduling/UI/ordinary SDL Objective1 acceptance still remain. Only Apple Silicon
macOS is tested. No worker, Windows action, download or runtime read was added.
