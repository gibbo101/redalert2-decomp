# Owned House selection in Boot Camp sight

The production visibility owner now accepts any of its own stable sight House
addresses, then lets the existing complete54A110 reveal-area kernel select the
current House. It previously refused every nonplayer House before that recovered
selection could run. This is a prerequisite for the House map scan / MakeAlly
production integration, not that integration or ordinary Objective1 completion.

## Ownership and behavior

`BootCampVisibilityWorld::applyRevealArea` validates pointer membership before
any dereference, map query, diagnostic count or effect. Null, foreign, another
world's and destroyed-source identities refuse. Equal logical IDs do not confer
ownership. The direct `reveal(Cell, houseID)` interface still accepts only the
current player; this change applies to the upper reveal-area interface.

The existing reveal-area kernel resolves a mask alliance directly to the current
House, independently of rules142B. Otherwise it calls the existing independently
recovered4E5540 scalar implementation, `unitOwnerAlliedToCurrent`, preserving
same identity/equal country index, signed current-index sentinel and wrapped bit
selection. Predicate acceptance still requires rules142B. A remaining noncurrent
House returns without any Cell query or mutation. Only the resolved current
House can reach the production visibility-change/discovery children.

No new House or actor mirror is introduced. Clones already own independent
visibility Houses; the production check now includes their addresses, values and
reveal rules in full source-isolation snapshots. This does **not** unify the
separate movement, discovery and visibility House representations. Mutable
MakeAlly adoption still requires that shared ownership decision; synchronizing
three copies would not establish the original aliasing.

## Checks and original evidence

The normal and sanitizer Boot Camp owner checks cover:

- null/foreign pointer rejection before range validation and all state changes;
- owned nonallied no-query/no-effect return;
- zero-mask equal-country predicate with rules142B off and on;
- mask alliance with rules142B off;
- warm independent House addresses, cross-world pointer rejection, unchanged
  source owners and continued allied add/remove after source destruction.

Diagnostic country/mask/rules changes exercise bindings; they are supplied test
inputs, not original-game observations or recovered startup values.

The unchanged reveal-area and House map-scan runners retain48 and1,238 original
sequences respectively in normal, sanitizer and uncached guarded replays. The
map-scan proof includes actual4E5540 execution. These are retained original-kernel
proofs plus new native ownership checks, not a newly executed whole production
chain. Original executable identity remains4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`;
embedded1.08/supplied1.006/reported no-CD/unverified pristine remain distinct.
No unchanged originals were regenerated. No runtime executable reads, public
reference source, dependencies, Windows actions or workers were added.

Both focused CTests pass in each build. The rebuilt application passes the actual
106-tick SDL selection/move/drawing/pause/refusal/Stop/repeated-order/deselection
check at `private/boot-camp-20261018/sight-house-sdl-a2/report.json`.
`objectives_enabled` and `visible_objective_text` remain false. The restricted
first SDL attempt had no displays and remains in `sight-house-sdl-a1`; the host
retry uses a new output directory. The sanitizer application target is not
configured; the initial multi-target sanitizer build correctly stopped after
building the owner check. Applicable research targets were then built explicitly.
There is no sanitizer SDL claim.

Command timings, current source/runner identities and report hashes belong in
`private/boot-camp-20261018/sight-house-receipt-a1.json`. Owner checks took3.093s
normal /32.091s sanitizer; focused CTests0.185s/0.763s. Build, SDL invocation,
repair and total task-wall costs were not separately measured. No cache was
added and no whole inventory or closed finalizer was rerun. Local verification
is not independent acceptance.

## Reproduce and continue

```sh
./build.command
build/native/boot-camp-walk-check private/official-1006-probe
build/sanitize/boot-camp-walk-check private/official-1006-probe
./run.command --boot-camp-walk
./run.command --boot-camp-walk-smoke-test private/NEW-SIGHT-HOUSE-SDL
```

Saved-original replay (choose new audit/report paths each time):

```sh
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/NEW-SIGHT-HOUSE.audit.json \
  tests/compare_reveal_area.py --exe private/official-1006-probe/game.exe \
  --native build/native/reveal-area-vectors \
  --expectations private/boot-camp-20261018/reveal-area-fresh-a4/expected.json \
  --report private/NEW-SIGHT-HOUSE.json
```

For the actual House predicate/scan replay use `compare_house_map_refresh.py`,
`house-map-refresh-vectors` and `house-map-refresh-fresh-a1/expected.json`.
Use `build/sanitize` for sanitizer replay; put `--uncached` before the driver for
inspection control. Exact executed argument arrays and elapsed costs are in
`sight-house-validation-{normal,sanitize,uncached}-a1.json`.

Next bind the mixed GI/Building sight registry over current production actors,
including actual Building sight/type records and stock vtable associations;
retain supplied startup and refuse unsupported entered image effects. Then join
House ownership, threat-grid/map/redraw and entered notification effects before
adopting action37's two MakeAlly calls. Team/audio/scheduling/UI and ordinary SDL
objective acceptance remain open. Both games and Boot Camp Objective1 remain
incomplete. Only Apple Silicon macOS is tested.
