# Boot Camp mutable Cell target ownership

Accepted Boot Camp walking orders now retain the selected mutable map
`MapCellInput` as Infantry `target494`. The former host-owned `Coord` copy has
been removed. This closes the target-owner mismatch below the recovered bounded
Infantry update-position composition without scheduling that composition.

## Ownership and coordinates

`BootCampWalkWorld::move` still applies the supplied direct-route policy first.
On acceptance it resolves the destination through `PreparedWalkMap::coordinate`,
recovers the exact owner through `PreparedWalkMap::attributes`, and passes that
owner's `MapCellInput` to the existing Infantry destination kernel. The pointer
therefore has the same stable lifetime as the production mutable map.

The target identity service accepts only addresses of `MapCellInput` records in
that mutable map and returns the canonical map-record index plus one. It refuses
the fallback, prepared-map twins, copied Cells and unrelated pointers. The
coordinate service applies recovered `mapCellCenterHeight` to that same owner,
including its live level, slope and shared floor state. Binding performs no map
or floor query; an accepted order performs the existing destination lookup and
coordinate query.

This matches the established Cell-target ownership used by the recovered Unit
destination world. It also supplies the real kind-11 target identity required by
the bounded `500AA0` path, while the kind result itself remains inside that
unscheduled fixture.

## Verification

The focused owner check issues all eight accepted two-Cell starting directions.
For each order it proves:

- `target494` equals the selected entry of the mutable map's 512-wide pointer
  table;
- the target's stored word coordinates equal the selected Cell;
- the destination X/Y are the selected Cell center;
- moving-retarget refusal preserves the same pointer and all sampled live state;
- arrival clears the target through the already recovered destination path.

Normal and sanitizer checks pass on the supplied patched installation. The
rebuilt 106-tick host-display SDL smoke passes selection, movement, drawing,
pause, moving-retarget refusal, Stop, repeated orders and deselection. Receipt:
`private/boot-camp-20261018/cell-target-sdl-a2/`. The first sandboxed SDL attempt
could not acquire a display and produced no receipt; it is not an application
failure. Measured owner checks were 2.42s normal and 9.74s sanitizer.

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
build/native/boot-camp-walk-check private/official-1006-probe
build/sanitize/boot-camp-walk-check private/official-1006-probe
./run.command --boot-camp-walk-smoke-test private/boot-camp-cell-target-next
```

## Evidence boundary and next gate

No original executable was run for this ownership-only integration. It reuses
the already recovered Cell destination/center behavior and exact immutable
Infantry expectations; it is native owner verification, not a new claim about
Day 1 startup or whole-game behavior. The supplied direct route, frame schedule,
controls and presentation remain unchanged.

The `A40958` resident-search global in the complete bounded update-position
fixture still has image-initial-zero supplied state. Establish its Day 1 startup
setter/caller association and then verify resident traversal against actual
mutable Cell membership before scheduling `500AA0 -> 4C7220 -> 6C2B40` in the
walking tick or arrival path.
