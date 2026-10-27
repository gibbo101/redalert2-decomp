# Boot Camp update-position ownership preview

The newer [persistent-owner note](INFANTRY_PERMISSION_1006.md) supersedes the
local temporary fields below: actor32D is now shared with admission, position
fields/scratch persist across callbacks, and bridge/Walk are actual owners. The
preview supports a bounded consecutive-arrival sequence and still commits nothing.
Cell12C and the newly identified discovery child remain supplied/unjoined.

The complete bounded `500AA0 -> 4C7220` composition now has an explicit
discarded preview over a disposable Boot Camp owner graph. It copies the
initialized player GI order state, rebinds the selected target to the
corresponding clone Cell, and advances actual recovered Walk Process until the
selected-head notification schedules update-position. Current/target Cells,
primary resident lists, mission and visibility owners remain shared within the
clone. The preview commits none of its mutable effects.

## Composition and ownership

The preview requires an actual player-GI Cell order. It binds:

- parent and child coordinates to the one actual `ActorGroundState::position`;
- parent target `+494` to the selected mutable-map `MapCellInput`;
- three direct parent lookups plus three complete current-Cell getter projections
  to actual mutable Cell identities; every getter performs and retains both
  recovered full-coordinate queries;
- all three kind-6 calls to the initialized actual Cell-head/GI `kind/Next`
  adapter;
- all eleven mission calls to the actual GI mission record;
- parent and child on-map fields to the one actual GI byte;
- target-kind 11 only after validating the actual Cell owner; and
- the entered child permission calls to recovered `mapCellPermitted` with the
  actual Day 1 permission shape and Cell table; and
- Mission Commence, sight removal, sight addition and post-sight refresh on one
  cloned GI/mission/visibility owner graph.

The coordinate target, current Cell and target Cell remain distinct identities.
The preview supplies stable local ownership for alternate target, locomotor,
bridge/type/footprint/effect flags and the two cleared state bytes. Kind-2 and
kind-1 searches, Cell `+EC`, alternate query and Cell `+12C`/object fields remain
named supplied boundaries. The position child uses the recovered bounded
`6C2990` prefix on the actual current Cell; map associations use actual recovered
Cell lookup ownership; dirty dispatch uses the recovered bounded `47BB30` prefix.
The sight children reach the recovered reveal/change/discovery/mask/redraw
kernels through the clone's shared visibility owner. Every mutation is confined
to the disposable graph.

## Actual Day 1 result

At the player GI start `(57,89)` with an accepted actual target Cell `(59,89)`,
the disposable Walk reaches its selected head at `(58,89)` on Process call 26
and dispatches notification kind 2 exactly once. At that callback the preview
observes:

- 11 actual mission queries;
- three direct parent Cell lookups, three current-Cell getters, six nested
  current full-coordinate lookups and one supplied Cell-value query;
- three initialized kind-6 searches and zero GI kind/`Next` queries: exact
  arrival order has already executed `Mark(0)`, so current and target primary
  lists are empty at the callback;
- two supplied kind-2 and two supplied kind-1 queries;
- one actual target-owner/kind validation and one actual target-coordinate
  query;
- one supplied locomotor-owner predicate;
- one actual call each to Mission Commence, sight removal, sight addition and
  post-sight refresh, producing one reveal-area add, 383 mask calls, 282 redraws
  and final sight range 5/active state;
- one recovered alternate selector, two actual coordinate-to-Cell-point queries,
  three actual effect Cell bindings and one scratch store;
- one actual permission query, because the same actor byte `+32D` that enabled
  sight is already set when the tail reaches its conditional second query; and
- one recovered position-prefix call, two actual map associations and one
  recovered dirty prefix call on the same actual Cell while retaining actor byte
  `+32D = 1`.

The actual Day 1 Cell `(58,89)` is permitted. Exact binary inspection and fresh original
differential tests establish that the first successful permission result bypasses
the vtable `+468` active-placement predicate and joins `4C792B`. In initially
disabled cases, the entered `6C2B40` tail queries permission again and stores
actor byte `+32D = 1`. In the actual enabled Day 1 preview it preserves that
shared byte and skips the conditional second query. Both continue through the
position child, two map associations and dirty effect.
The preview reaches that complete bounded continuation on the scheduled clone owners.
The position Cell's supplied initialized cloak-generator mask is zero, so
recovered `6C2990` returns before its actor predicate and global traversal.
The dirty Cell has overlay `-1`, so recovered `47BB30` returns at its first gate
before reading the player GI resident.

Its mutable state bytes, mission/timer fields, sight fields, visibility Cells and
scratch belong to the disposable graph. Normal and sanitizer owner checks verify
that live Walk state, mission state, visibility state, Cells, target and time are
unchanged. A nonplayer request refuses before any preview work.

The full application rebuild, all 113 normal CTests, all 112 SDL-disabled
sanitizer CTests and 1,342 Python tests pass. The focused owner check passes
under normal and sanitizer builds. A fresh 106-tick host-display SDL
regression passes selection, movement, drawing, pause, refusal, Stop, repeated
order and deselection at
`private/boot-camp-20261018/walk-update-position-schedule-sdl-a1/`. Its report retains
`objectives_enabled: false`; it proves unchanged runtime behavior only.

## Exact evidence, limits and next recovery

The strengthened child and joined fixtures each execute 80 fresh complete original calls: the
retained 64-case corpus plus 16 actual-map permission-success cases around Day 1
Cells `(57..60,89..92)`. The joined proof now includes the complete parent
coordinate children and target Cell/floor ownership. Canonical receipts are
`private/boot-camp-20261018/position-effects-e1-fresh-a10/` and
`private/boot-camp-20261018/update-position-coordinate-children-e1-fresh-a3/`. Their
expectation SHA256 values are respectively
`c21f49f5f4b472ad01991dbe48f7cdaa4e2debec16075d53cdf3b8733300c60a` and
`fd506fc88c32dd1774d80d45466f2c2c62be2b23638e50c3bff82691084e49c4`.
Normal, sanitizer and uncached replays pass for both. The newer joined sight
receipt is
`private/boot-camp-20261018/update-position-sight-children-e1-fresh-a5/` with
expectation SHA256
`97469dad5f194049a21234fe09e4f29c355182d4d53c6bc1d6c73489fd77ebf2`.
It executes all three first sight children in 80 roots and complete post-sight in
two roots; normal, sanitizer and uncached replays pass. The disposable-owner
preview is scheduled native integration evidence and commits no result. Exact
producer inspection is recorded at
`private/boot-camp-20261018/walk-update-position-schedule-a1.json` and in
`WALK_UPDATE_POSITION_SCHEDULE_1006.md`.

Production arrival scheduling still requires a joined original
`Walk -> 500AA0` root and its post-callback late-byte behavior. The entered cloak
effect and resident-bearing dirty branch remain outside the actual zero-mask/
no-overlay Day 1 preview path. Runtime walking, SDL Objective 1 and existing
sight scheduling remain unchanged.

## Reproduce

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
build/native/boot-camp-walk-check private/official-1006-probe

DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/sanitize \
  --target boot-camp-walk-check --parallel 6
build/sanitize/boot-camp-walk-check private/official-1006-probe
```
