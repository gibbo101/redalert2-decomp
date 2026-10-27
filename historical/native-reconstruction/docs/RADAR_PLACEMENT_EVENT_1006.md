# Placement status event: inspection and local-player boundary

This narrows the remaining dependency for original Boot Camp Day1 sight and
position integration. `RadarActorPlacementServices::radarEvent63B5B0` replaces
the misleading `visibility63B5B0` name. Its signature, query order and effects
are unchanged. No runtime schedule or original instruction was changed.

## Evidence

Fingerprint checked before addresses: supplied base4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Complete63B5B0..63B694 is229 bytes/82 instructions, SHA256
`8a46a7df8a5207de78544bbdaa14449479aafe7fe8a1ed4fc4edfe9b9735f9d7`.
This is **inspection**, not a new original-execution differential proof.
Private disassembly and inspection metadata remain under
`private/boot-camp-20261020/placement-event-inspect-a1/`.

The parent selects a16-byte table entry by its mode. A nonzero entry byte enables
iteration of the live AB67EC/AB67F8 list, comparing matching record types. It
subtracts stored20/22 coordinates with word wrapping, computes distance through
4BA410/77F110, rereads the list and record type, narrows the distance to a signed
word and compares against the selected entry threshold. A close match returns
false. Otherwise it requests64 bytes through782017; on success it calls63B6C0
with mode and packed Cell, then returns true even if allocation failed. The
placement caller ignores this return. The constructor prefix stores type and
Cell, reads frame and screen geometry, and calls radar projection631470. The
complete constructor and its effects are **not recovered or verified here**.
Do not infer fog mutation or mission success from the former callback name.

## Local player branch and remaining work

The independently recovered/differentially checked stock2F8 local-House branch
returns truth of current373 without touching status. Complete placement starts
status at zero. Therefore this local branch never enters63B5B0, and does not
require nonlocal height1B0 or per-House Cell7C eligibility2FC. Actual-owner tests
now install throwing height/2FC probes with mode2 and elite veterancy to verify
that the local branch still bypasses them and preserves a nonzero status.
Existing actual local placement -> drawing checks observe no event request.

This does **not** establish that every actor touched by sight is local: enemy
structures, other residents and other schedules need their own entered-path
coverage. Do not enable live sight based on this local proof. Next trace the
actual position/sight caller effects and their touched actor identities, composing
the now-available local marker branch where entered. Recover nonlocal branches
when that concrete interaction enters them, while preserving refusal for missing
children. Full Cell-crossing scheduling, state-changing effects and ordinary SDL
Objective1 acceptance remain required. No new executable runtime read, Windows
action, download or dependency was introduced. Both games remain incomplete.

## Verification

Both normal and sanitizer profiles rebuild affected runners, run three focused
radar domain CTests and the actual Boot Camp owner check, and explicitly reuse
635 permission plus596 placement originals with zero misses. Current native
runs each time; original parent/effect-probe provenance is unchanged. No new
original matrix or SDL ceremony is needed for this name/test-only refinement.
Commands, durations and logs:
`private/boot-camp-20261020/placement-event-{native,sanitize}-a1/costs.json`.
Build/edit/inspection/total wall cost uninstrumented; concurrent costs not additive.
Only Apple Silicon macOS is tested; local verification is not independent acceptance.

```sh
build/tools-env/bin/cmake --build build/native --target boot-camp-walk-check radar-actor-placement-vectors radar-actor-permission-vectors --parallel 6
build/tools-env/bin/ctest --test-dir build/native --output-on-failure -R 'radar-actor-(permission|placement|markers)-domain'
build/native/boot-camp-walk-check private/official-1006-probe - private/boot-camp-20261020/radar-shape-dimensions-a1.bin
```

Repeat with `build/sanitize`. Original-result reuse commands remain in
[RADAR_ACTOR_PERMISSION_1006.md](RADAR_ACTOR_PERMISSION_1006.md) and
[RADAR_ACTOR_PLACEMENT_1006.md](RADAR_ACTOR_PLACEMENT_1006.md); choose fresh
reports/audits and the current runner.
