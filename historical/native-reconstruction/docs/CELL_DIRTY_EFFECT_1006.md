# Cell dirty-effect ordered early returns

## Live GI crossing binding — 2026-10-19

Boot Camp now binds `PreparedInfantryWalk::dirty` to this existing kernel on
the actual mutable Cell attributes and primary resident record. The recovered
Walk crossing parent already performs removal, placement, height update,
insertion and current-Cell lookup before the callback. It now executes the
recovered dirty gates instead of a supplied no-op. The discarded arrival preview
uses the same private adapter. Shared fallback identity and clone rebinding are
retained; no duplicate Cell representation or new executable read is introduced.
This removes one movement dependency before live sight/Objective1 integration.

Current normal and ASan/UBSan owner checks verify the live overlay/data/slope/
flags/resident fields, all five exits, explicit refusal of the unrecovered
resident effect, fallback, clone isolation and source destruction. All eight
actual two-Cell GI journeys require a dirty callback on the current Cell after
actual GI insertion. These are native integration checks. The existing complete
Walk-parent original proof intercepts the dirty child; the separate64-case
dirty proof checks that child. Neither is a combined original Boot Camp proof.
Both current native profiles explicitly reuse all64 original answers with zero
misses; no unchanged original answers were regenerated.

The actual256-tick SDL smoke passes with objectives still disabled, including
rightward/leftward walking, Stop and repeated orders. Both horizontal captures
were inspected. The first sandboxed SDL attempt failed before display creation;
the display-authorized retry passed. Animation selection/phase, redraw scheduling,
arrival/sight and Objective1 remain incomplete; this callback does not discover
structures or synthesize progress. The old unscheduled wording below describes
the earlier checkpoint, superseded only for this live crossing callback.

Current logs, costs and hashes: `private/gi-crossing-dirty-receipt-a1.json`.
Use the replay commands below with reports named `private/gi-crossing-dirty-...`.
Actual-owner checks:

```sh
build/native/boot-camp-walk-check private/official-1006-probe
build/sanitize/boot-camp-walk-check private/official-1006-probe
./run.command --boot-camp-walk
./run.command --boot-camp-walk-smoke-test private/gi-crossing-dirty-sdl-new
```

Complete base `47BB30..47BC7A` is pinned, with all five ordered early-return
paths translated into `applyCellDirtyEffectPrefix`. This closes the dirty call
reached by the ordinary Boot Camp update-position tail for its actual Cell. It
does not recover the resident-bearing effect after those gates.

## Recovered behavior

The supplied executable remains 4,485,392 bytes with SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
The exact routine checks, in order:

1. Cell overlay field `+44` must equal 126;
2. overlay data byte `+11E` must be at least 48;
3. slope byte `+11C` must be zero;
4. Cell flags `+140` must not contain `0x20000`; and
5. primary resident head `+E4` must be nonnull.

Failure at any gate returns without writes or child calls. Passing every gate
with a nonnull resident enters object traversal, allocation and effect logic;
the native kernel refuses that path explicitly.

The Boot Camp discarded update-position preview binds the final dirty identity
to the same actual mutable Cell returned by the two recovered `548070`-equivalent
lookups. At `(57,89)`, the Cell owns the player GI resident but has overlay `-1`,
so original `47BB30` returns at the first gate and never reads the resident.
The preview records the exact Cell identity and `Overlay` exit while preserving
all live Walk, mission, visibility and Cell state.

The strengthened complete `4C7220` and joined `500AA0` receipts also execute
this complete range in the same guest as the selector, map and cloak child. Each
has 48 entered overlay exits. The standalone receipt remains the broader
five-gate proof.

## Evidence and limits

Canonical private evidence is
`private/boot-camp-20261018/cell-dirty-effect-fresh-a2/`. Its 64 fresh complete
calls cover every early return. The original executes the overlay/data/slope/
flags/head gates 64/50/38/25/12 times. Expectation SHA256 is
`4e18a148bf9744b7559acd949a1827637a3fef882e969e190efbb3c507fca52d`.
Normal, sanitizer and uncached replays each retain 64 hits and zero misses.

The complete project rebuild and all 111 CTests pass. A fresh 106-tick actual
host-display SDL regression passes selection, movement, drawing, pause, refusal,
Stop, repeated order and deselection at
`private/boot-camp-20261018/cell-dirty-effect-sdl-a1/`. Its report retains
`objectives_enabled: false`; it proves unchanged runtime behavior only.

This is recovered behavior plus an actual-owner native composition. It is not
production scheduling or an observation from a running original game. The
resident-bearing branch, parent sight/map effects and the Cell-crossing caller
schedule remain open. No runtime executable
read or proprietary data was added.

## Reproduce

```sh
./build.command
./test.command

env DEVELOPER_DIR="${DEVELOPER_DIR:-/Library/Developer/CommandLineTools}" PYTHONHASHSEED=0 \
  PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/cell-dirty-effect-next.audit.json \
  tests/compare_cell_dirty_effect.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/cell-dirty-effect-vectors \
  --expectations private/boot-camp-20261018/cell-dirty-effect-fresh-a2/expected.json \
  --report private/cell-dirty-effect-next.json
# Use build/sanitize/cell-dirty-effect-vectors for sanitizer replay.
# Add --uncached for an inspection-cache control. Use new private path names.
```
