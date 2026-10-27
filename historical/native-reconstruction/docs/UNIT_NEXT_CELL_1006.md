# Ordinary Unit next-Cell early paths

The later [admission/Process join](GROUND_DRIVE_ADMISSION_PROCESS_1006.md)
executes these required early paths inside complete Process with actual gates
and supported admission results. Production mutable map/membership and runtime
adoption remain open. This standalone proof retains its original boundary.

After `96b8e3a`, the required warning-mode early paths of Unit virtual +4B8
match **567 fresh scenarios / 613 complete original calls**, with normal and
ASan/UBSan replays. The new SDL-free helper is **unwired**. This removes one
dependency for Rhino movement integration; it does not implement crushing,
warning delivery, occupied movement or playable gates. Full base RA2, then
Yuri's Revenge, remain incomplete. No workers were used.

## Identity and reference boundary

Both supplied private engines are 4,485,392 bytes / SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`:
`private/official-1006-probe/game.exe` and
`private/windows-baseline-20261014/game.exe`. Fresh execution uses the first.
Embedded 1.08, supplied 1.006 lineage and reported no-CD modifications remain
distinct; pristine authenticity is unverified. The authorized Windows copy was
already present. No transfer, Windows action or source-install change was needed.

Pinned YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88`, `FootClass.h`
TryCrushCell, supplied a naming lead. The base Unit vtable and inspected caller
establish the actual +4B8 association and preparation's warning=1 argument.
YR names/addresses are not base behavior evidence. No YRpp license file was
found. Retained recomp snapshot `eebcf725ef99f942a8f9a5e0437a8a6154d7d439`
has no Git metadata; its MIT text covers its authored tools/docs, excludes
original/lifted code and retains stale The Movies wording. No upstream/header/
generated/lifted code, table or dependency was incorporated.

## Recovered boundary

The complete root is `0x705160..0x7053E8`; its return type is void. The oracle
does not compare leftover EAX as a meaningful return value. Complete word map
lookup, coordinate getter and two unpromoted ability predicates execute without
instruction patches or substituted child answers.

- Target lookup always precedes type/ability checks. Its signed word `y*512+x`
  combined index is bounded after combination. A missing slot forwards the
  same fallback identity and immediately stores its queried coordinates.
- Target flag 0x100 enables the layer decision. Any nonzero actor +79 selects
  the elevated layer without querying actor coordinates. Otherwise the actual
  +48 coordinate getter executes, then X/Y are divided toward zero by256 and
  truncated to words for the current-Cell lookup. No floor-shift substitution.
- After that lookup, the retained target's signed byte level plus4 is compared
  with the current Cell's signed byte level. The addition is an integer addition,
  not a byte wrap. Target/current may be the same fallback record; its rewritten
  coordinates and identity must survive. Other target flag bits do not enable
  this branch by themselves.
- Type+AF3 is Crusher. Any nonzero value bypasses ability 17. With zero Crusher
  the actual two promotion predicates both execute on supplied 0.0 state and
  return false, causing an early exit before warning or occupation inspection.
  This is a specialization to unpromoted state, not general ability recovery.
- With Crusher and warning's low byte nonzero, only the selected occupation
  byte's low five bits are tested: primary +124 or elevated +128. Zero returns
  before warning 476920 and resident traversal, even when bit5 or higher bits
  are set and resident pointers are nonnull. Primary and elevated selection
  must remain distinct. No reservation or occupation write occurs here.

`sim/UnitNextCell` borrows canonical logical Cell/slot/fallback/type identities
from `UnitAdmissionWorld`, rather than making independent queried Cell copies.
The separately supplied actor location/bridge byte and unpromoted state are
not recovered initialization. Trace observers are read-only. Invalid ownership,
missing canonical records, crusher warning0/list branches and selected nonzero
low-five warning delivery are refused. Unsupported paths do not become successful
callbacks. A refusal can follow an earlier fallback coordinate store, preserving
the already executed lookup; callers must not treat exceptions as gameplay.

## Evidence and remaining integration

Current proof: `private/map-depth-1006/unit-next-cell-v2/`. All six complete
allowed ranges enter: 300 inspected instructions, 132 distinct executed.
The actual root enters 613 times, map lookup 1,011, coordinate getter 398 and
ability/promotion children 95 each. Selected instruction entries record 417
primary and 101 elevated tests; the other 95 calls exit after ability. There
are 344 ordered fallback stores and 613 complete actor/type/Cell arena checks.
Caller ESP, return address, callee-saved registers, stack tail, immutable
code/dispatch/constants/map slots and unselected fallback fields are checked.

Coverage includes raw nonzero crusher/bridge/warning bytes, warning upper bytes,
all signed-byte level combinations in the selected edge set, INT_MIN/MAX and
negative division edges, word truncation, sparse/out-of-range combined indexes,
repeated shared fallback sequences, ignored nonselected occupation and deliberately
invalid resident pointers. These are diagnostic fixtures, not original-game
observations. No warning, list or crushing child is entered or claimed.

v1 remains an exploratory historical receipt. v2 adds the transitive Targeting
header to its source manifest and a regression requiring complete native header
coverage. All v1 command/result/label records survive unchanged. No old receipt
was rewritten to match changed source identities.

Both builds and complete native/Python regressions pass. CMake registration
requires fresh unit-admission-v4, movement-gate-v5 and terrain-runtime-map-v17
proofs and both replays; earlier command/result projections are unchanged.
The map retains all 13,515 selected Cells / 255 source slices. Other current
proof identities remain unchanged without original reexecution. Closing evidence
and timings are private under the `next-cell-*` prefix.

The arm64 SDL application remains byte-identical to `96b8e3a`; its existing
injected-event terrain regression passes again. This does not test the unwired
helper, OS pointer/keyboard input, original-game timing or whole-frame parity.
Only Apple Silicon macOS is tested; local development dependencies remain.

Next join nonzero admission results to complete preparation/Process, preserving
distinct first/second admission handling and retained route tails. Then bind
actual admission/gates/required next-Cell behavior to the production mutable map
and membership before runtime adoption and a blocked-move/gate SDL scenario.
Keep renderer preparation immutable and previews isolated. General pathfinding,
combat, AI/economy/campaigns/multiplayer/audio/saves and YR remain later work.

## Reproduction

```sh
./build.command
./test.command
build/tools-env/bin/python -B -m unittest discover -s tests -p 'test_*.py'
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

# Fresh original execution needs the authorized host Unicorn JIT context.
# Choose an unused ignored directory; do not overwrite historical evidence.
build/tools-env/bin/python -B tests/compare_unit_next_cell.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/unit-next-cell-fresh-local

build/tools-env/bin/python -B tests/compare_unit_next_cell.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/unit-next-cell-v2/expected.json \
  --report private/map-depth-1006/unit-next-cell-v2/local-native-replay.json
build/tools-env/bin/python -B tests/compare_unit_next_cell.py \
  --exe private/official-1006-probe/game.exe \
  --native build/sanitize/unit-next-cell-vectors \
  --expectations private/map-depth-1006/unit-next-cell-v2/expected.json \
  --report private/map-depth-1006/unit-next-cell-v2/local-sanitize-replay.json

./run.command --terrain-demo
```

Select Rhino; G/right-click moves, Q/E turns the body, A/D turns the turret,
S finishes the committed track then stops, and R resets. These controls, direct
routes/clearance and runtime admission remain host adapters. Native runtime
executable reads, private data formats and source installations are unchanged.
