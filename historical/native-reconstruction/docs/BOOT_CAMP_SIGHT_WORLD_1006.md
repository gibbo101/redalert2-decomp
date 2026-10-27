# Boot Camp Techno sight composition

The bounded Boot Camp world now composes both recovered Techno sight directions
through complete reveal-area and the shared production visibility Cells. This is
an explicit integration seam only: the Walk arrival callback and SDL tick do not
invoke it yet.

## Shared ownership

The supplied executable is 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Original code remains confined to private research fixtures. The application
does not read or execute the executable.

`BootCampVisibilityWorld` now passes its one `CellVisibilityState` table directly
through reveal-area `54A110`, visibility mask `6A8D40`, Cell change `499FC0` and
resident discovery `568520`. `RevealAreaCell` aliases that shared record; no
logical Cell is copied. The owner also binds recovered spread/height tables,
actual map diamond dimensions, stock level height, current player House and the
private hash-checked mask-result table.

Each GI has separate active sight, height increase, last coordinates and last
range fields beside its existing Walk actor. Current coordinates and veterancy
are borrowed from that actor. E1 Sight and SIGHT ability membership come from the
user-supplied rules, as does VeteranSight. Enabled/country bytes and initial
zero sight fields remain supplied startup associations.

The explicit `composeSight(id)` seam performs complete old-sight removal
`6D5E90` followed by complete update `6D5C30`. Removal reaches reveal-area with
final child argument one and increments old Cell counters. Addition reaches it
with final child argument zero and decrements new Cell counters. Both directions
use the same House, Cells, fallback, resident records and mission structures.

Structure discovery reuses the `UnitDiscoveryActor` already owned by
`BootCampMissionWorld`. Repeated Cell projections therefore stop at recovered
field `+373`. Tag expiration updates the actor's supplied has-Tag view before a
later structure discovery, so the second objective structure becomes discovered
without firing the expired objective event again. Repeated discovery after the
deferred objective cleanup also stops at that actor state rather than consulting
retired Tag lifetime records.

## Integration acceptance

The production-owner check starts with the actual player GI at `(57,89)`:

1. First sight decrements its center Cell to `-1` without discovering Objective1.
2. A same-position composition removes then adds the same spread; the center
   returns to `-1` rather than accumulating another decrement.
3. Walking to reachable Cell `(66,92)` does not change sight, proving the runtime
   schedule remains off.
4. Explicit composition there restores old-only `(57,89)` to zero, decrements
   new-only `(66,92)` to `-1`, discovers both actual objective structures and
   fires Objective1 once.

The shared aliases changed the rebuilt exact runners. Normal, sanitizer and
uncached replays retain zero misses for 96 Techno sight calls, 96 removal calls,
48 reveal-area calls, 192 Cell-change calls and 128 mask calls. The direct owner
check passes in normal and sanitizer builds. These are separate original-kernel
proofs plus native composition acceptance, not a whole-chain original execution.
All 105 normal CTests and 1,328 project-local Python tests pass. The existing
actual SDL walking smoke passes selection, movement, drawing, pause, refusal,
Stop, repeated order and deselection over 106 ticks; it still reports objectives
disabled because scheduling is intentionally off. The first restricted SDL run
had no display, and the first host retry correctly refused its already-created
output directory. After the final mission-owner adjustment, the rebuilt fresh
`sight-world-sdl-a3` run is accepted.

## Limits and next integration

`composeSight` is not called by `step()`, the arrival callback or SDL. The
recovered argument-2 arrival suffix also contains a supplied `+1D4` mission
transition and the now separately recovered `54A550` post-sight effect. `+1D4`
is now identified with the prior exact Mission Commence kernel; all four children
compose through an explicit shared-owner seam but remain unscheduled.
Initial sight invocation, Cell-crossing sight producers,
redraw/fog presentation and objective UI/audio/team effects remain open.

Next recover a bounded complete500AA0 E1 path and inspect Cell-crossing callers.
Then bind the complete arrival schedule and accept actual SDL movement-driven
Objective1 progress.
