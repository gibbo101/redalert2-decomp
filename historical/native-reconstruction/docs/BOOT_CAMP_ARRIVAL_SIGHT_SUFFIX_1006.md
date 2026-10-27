# Boot Camp arrival sight suffix composition

The four already verified children of Infantry update-position's argument-2
suffix now compose in their exact order on the actual Boot Camp GI and shared
visibility owner. This remains an explicit verification seam. Walk arrival and
SDL do not call it because complete `500AA0` contains substantial effects before
and after the suffix that are only inspected.

## Mission Commence reuse

Infantry vtable slot `+1D4` points to base `594C50`. This is the same complete
Mission Commence routine already recovered in `movement_gate_policy::commence`,
not a new supplied child. The pinned range is 92 bytes / 25 instructions with
SHA256 `c2c6d647d7e9a13a8609a404ce06b328bdd46c15c3ea161ff5c9b41a48a62c1a`.

When queued mission `+A0` is `-1`, it returns false without mutation. Otherwise
it copies `+A0` to current mission `+98`, clears `+A0`, clears status `+A8`, stores
the current tick at timer start `+B0`, copies the supplied opaque stack word to
timer padding `+B4`, clears timer remaining `+B8`, stores the tick at `+AC`,
clears queued byte `+A4`, and returns true. Width and order remain exact.

`PreparedInfantryWalk::commence` now applies that single kernel through the
existing borrowed admission view, so it mutates the same mission/timer records
used by movement. The refreshed movement-gate proof has 2,074 results / 2,494
complete original calls, including 479 entries to `594C50`. Fresh expectation
SHA256 is `5ef36cc8ba0a6d1446e31b10b373797811e9e1131a8165e172d53f85c6047612`;
normal and sanitizer replays pass. The actual Day1 player GI has no queued
mission at this seam, so the integration check verifies the exact no-mutation
path on its live fields.

All 106 CTests, 1,328 project-local Python tests, normal/sanitizer Boot Camp
owner checks and the rebuilt 106-tick host-display SDL smoke pass. The accepted
SDL receipt is `private/boot-camp-20261018/arrival-suffix-sdl-a1/`; the smoke
confirms the still-unwired player path remains unchanged.

## Shared suffix composition

`BootCampWalkWorld::composeArrivalSight` calls the recovered interior schedule,
which dispatches:

1. Mission Commence `594C50`;
2. sight removal `6D5E90(0,0,0,0)`;
3. sight addition `6D5C30(0,0,0,0)`;
4. post-sight refresh `54A550(current coordinates,0,lastSightRange+3,0)`.

All callbacks borrow the actual GI, sight fields, tick/padding values and one
Boot Camp visibility owner. The exact-zero child argument boundary is enforced.
For stock E1, the check produces one addition, no removal on first sight, the
205-Cell post-sight radius-8 refresh and the established shared Cell `(63,89)`
mask/redraw mutation.

## Complete-parent inspection and limit

Complete base `500AA0..501CA8` is 4,617 bytes / 1,441 instructions with 182 call
sites and SHA256 `d9144d32fcf31d627c658ea4bcaf19f109d55ea5a8e8854c6026363b6215fbc2`.
Argument 2 enters Infantry-specific type, target, occupation, animation, map and
other effect branches before reaching `501B69`. After post-sight returns, the
parent performs another coordinate lookup and additional interface/type/map
checks through either return at `501C89` or `501CA6`. Those branches have not
been executed as one bounded original E1 path.

The composed suffix therefore must not replace `arrivalNotification(2)`. It does
not prove which pre-suffix branches the Boot Camp GI takes, the post-suffix effect,
initial sight scheduling or whether other Cell-crossing producers exist. Runtime
walking and Objective1 progression remain unchanged.

Next recover a bounded complete argument-2 E1 path through `500AA0`, including
the post-suffix tail, and inspect other Cell-crossing callers. Only then bind the
arrival callback and run movement-driven SDL Objective1 acceptance.
