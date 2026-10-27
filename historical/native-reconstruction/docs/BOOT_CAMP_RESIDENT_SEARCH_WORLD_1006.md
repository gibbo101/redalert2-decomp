# Boot Camp Cell resident-search ownership

The recovered base `4717B0` kind-6 search now has an explicit production-owner
adapter over the actual Boot Camp Infantry map. `BootCampWalkWorld` owns one
`CellResidentKind6State`, initializes it through the recovered selected
scenario-loop setter projection, and exposes a focused SDL-free composition
seam. This does not schedule complete Infantry update-position or position
effects during walking.

## Owned behavior

`PreparedInfantryWalk::cellIdentity` resolves a coordinate through the existing
mutable `PreparedWalkMap` and returns that actual `MapCellInput` identity.
`PreparedInfantryMembership` accepts only identities in its owned Cell table.
The search then:

1. returns before reading the Cell head while the recovered enable byte is zero;
2. reads the selected actual `InfantryMembershipCell::head` when enabled;
3. resolves each list value to the actual `InfantryWalkState` object identity;
4. obtains the live `object.kind` for each visited actor;
5. reads the live `object.next` only after a non-kind-6 actor; and
6. returns the first actual actor identity whose kind is 6.

Foreign Cell, head and `Next` identities are refused. The adapter reports kind
and `Next` query counts for focused verification and does not mutate the world.
Binding and Cell-identity lookup make no resident queries.

The actual Day 1 owner initializes the recovered state to one. Its starting
player-GI Cell has the real GI record at the primary head; a focused owner check
observes one kind query, one final `Next` read and no kind-6 result. The prepared
owner check separately proves disabled isolation, first and later hits, actual
actor identity, live `kind/Next` values and foreign-Cell refusal.

## Refreshed exact evidence

The three affected exact fixtures now set the recovered resident global to one
and give every entered Cell an explicit empty primary head. They invoke the
actual complete search without a kind or `Next` callback because the head is
null. This changes the fixture association from image-initial zero to the
recovered initialized state while retaining empty-resident behavior.

Fresh accepted receipts are:

- `private/boot-camp-20261018/update-position-e1-fresh-a6/`: 64 complete
  `500AA0` calls and 448 actual mission queries; expectation SHA256
  `e460f8a3fa4a213c4adbc9d8ee3e24779d308c5c3acadfb1667f8fd6a9e072c8`;
- `private/boot-camp-20261018/position-effects-e1-fresh-a5/`: 64 complete
  `4C7220` calls, 32 entered complete `6C2B40` tails and 256 actual mission
  queries; expectation SHA256
  `78354a4a45cd9ccce7919c054511c5060eefef85901cc8c1a37aa194c4822019`;
- `private/boot-camp-20261018/update-position-effects-e1-fresh-a3/`: 64
  complete joined parents, 32 entered children/tails and 576 actual mission
  queries; expectation SHA256
  `84f7538f92e067126b5fac39d5d2e6bdd89b159436e6babed41b227a43199529`.

Normal, sanitizer and uncached replays retain 64 hits and zero misses for all
three receipts. Fresh original generation took 0.029, 0.032 and 0.071 seconds.
The nine replays were run concurrently and each elapsed about 13.6 seconds, so
those wall times include contention and are not a cache-efficiency comparison.
The immutable audits are named `*-resident-replay-{normal,sanitize,uncached}-a1`
under `private/boot-camp-20261018/`.

The complete application rebuild and all 110 CTests pass. Normal and sanitizer
prepared/Boot Camp owner checks pass. A fresh 106-tick host-display SDL smoke
passes actual selection, movement, drawing, pause, moving-retarget refusal,
Stop, repeated order and deselection; its receipt is
`private/boot-camp-20261018/resident-search-sdl-a1/`. It still reports objectives
disabled and therefore proves runtime regression only, not that the new search
or complete update-position chain is scheduled.

## Limits and next integration

The scenario-loop prefix proof establishes the selected store and callers, not
complete original scenario startup. Calling its recovered setter from the Boot
Camp owner is an explicit reconstruction association. The owner search is a
focused seam; `BootCampWalkWorld::step`, arrival and SDL Objective 1 do not call
the complete `500AA0 -> 4C7220 -> 6C2B40` chain.

That chain still needs one explicit Boot Camp composition over the actual GI,
actual current and target Cells, and this actual resident adapter. Kind-2 and
kind-1 searches, alternate query `508530`, map association `548070`, position
child `6C2990`, dirty effect `47BB30`, locomotor ownership and other named
effects remain supplied boundaries. Prove shared actor-field identity and
refusal isolation in that composition before scheduling Cell crossing or
arrival. Runtime movement and its SDL behavior remain unchanged here.

## Reproduce

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/native/prepared-infantry-walk-check
DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/native/boot-camp-walk-check private/official-1006-probe

env DEVELOPER_DIR=/Library/Developer/CommandLineTools PYTHONHASHSEED=0 \
  PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/boot-camp-20261018/update-position-e1-resident-replay-next.audit.json \
  tests/compare_infantry_update_position_e1.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/infantry-update-position-e1-vectors \
  --expectations private/boot-camp-20261018/update-position-e1-fresh-a6/expected.json \
  --report private/boot-camp-20261018/update-position-e1-resident-replay-next.json
```

Use the matching position-effects or joined driver/runner/receipt for the other
proofs. Use the sanitizer runner for sanitizer replay, and add `--uncached` for
the control. Every audit and report destination must be new.
