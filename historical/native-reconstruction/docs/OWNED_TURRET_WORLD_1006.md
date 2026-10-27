# Independent turret commands on the owned world

This extension exercises `OwnedUnitWorld::turnTurret` and `updateTurret` on the
same two distinct membership-bound actors used by complete Process and shared
ground drawing. The application remains unchanged: Unit1 in the resident demo is
inspection-only. Current accepted counts and receipts belong in the opening
[HANDOFF.md](HANDOFF.md).

## Original boundary

The exact supplied executable is 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 lineage and reported no-CD provenance remain separate;
pristine authenticity is unverified. `verify_owned_turret_world.py` fingerprints
that file before inspecting these actual addresses:

| Routine | Address |
| --- | --- |
| Complete ordinary Unit turret update | `0x6FB890` |
| Facing SetDesired | `0x4B8A30` |
| Facing current heading | `0x4B8BE0` |
| Facing rotating predicate | `0x4B8C90` |
| Object-to-object bearing | `0x5D2730` |
| Actual coordinate getter | `0x5D4E40` |
| Quantized angle child | `0x4BA600` |
| Original integer conversion | `0x77F110` |

These are base-binary addresses, independently checked against this fingerprint;
older disc-profile addresses must pass their explicit mapping. No YR/recomp
behavior supplies the result. No instructions are patched.

The supported parent has no combat target and a normal nonspinning turret.
An active turn finishes first. An idle turret requests its destination's bearing
or its body's current heading. Two original actor addresses and Drives remain
distinct throughout initialization, Process, turret operations and complete
interleaved draws. Neither actor is executed at the other's address.

The original actor's weapon-slot and disabled-weapon children remain named
supplied services. Static coordinate targets are explicit fixture records;
other-actor targeting invokes that other actor's actual coordinate getter.
Target association/lifetime is scoped to the turret operation and restored before
Process/drawing. This does not recover mission ownership of destination objects
or drawing's contact relationship. Initial Facing/rate/type/House/visibility,
temporary timer padding and the supplied tick schedule retain their earlier scope.

Manual override is a prototype policy: a wrapped delta requests original
SetDesired, and the host skips automatic targeting until released. It is not an
original input/mission policy. Current-heading and rotating queries still execute
the actual original routines. Signed difference, IDIV-before-IMUL interpolation,
16-bit wrap, interrupted turns and retained timers remain the recovered arithmetic.

## Evidence and isolation

The authored input schedule takes only commands/labels from the retained
two-Process-v3 receipt, pins that input file's hash, and executes new original
results. Earlier expected outputs are never used to supply a turret, pose, actor,
map, cache or pixel. The new C++ fixture actually calls the existing world owner.
Process selected-store/query/return comparisons and complete draws retain their
earlier projections, with both actors' current/rotating/manual/turning views added.

Every isolated turret call checks caller stack, callee-saved registers, immutable
code/type/vtable/Drive inputs, both full actor arenas and permitted writes. The
original timer-padding and `+599` stores are retained privately. Those internal
stores are not a native ordered-store proof; the current native owner has no
combat-target `+599` record. Native comparison covers the exposed Facing values,
both actors' Process/map state, control views and complete draw outputs.

No two-mover runtime promotion follows from this evidence. Independent route,
stop and pending-body-turn commands, complete scheduled preview and renderer
isolation, selected-actor routing and actual SDL acceptance remain required.
Unsupported Advance6/7 aftermath, scatter and earlier route exclusions remain
explicit refusals. Base RA2 and Yuri's Revenge are incomplete.

## Reproduction

```sh
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake -S tests/owned_turret_world \
  -B build/owned-turret-world -DCMAKE_BUILD_TYPE=RelWithDebInfo \
  -DCMAKE_OSX_ARCHITECTURES=arm64 -DCMAKE_PREFIX_PATH=/opt/homebrew
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/owned-turret-world \
  --target owned-turret-world-vectors --parallel 6
# Sanitizer: use build/owned-turret-world-sanitize, Debug and -DRA2_SANITIZE=ON.

PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/unit-draw-1006/turret-new.audit.json \
  tests/compare_owned_turret_world.py \
  --exe private/official-1006-probe/game.exe \
  --native build/owned-turret-world/owned-turret-world-vectors \
  --output private/unit-draw-1006/turret-new
# Fresh original execution requires the authorized host Unicorn JIT context.
# Replay: replace --output with --expectations CURRENT_EXPECTED_JSON
# --report NEW_PRIVATE_JSON; use a new audit. For sanitizer use its runner.
# --uncached before the driver disables immutable inspection reuse only.
```

Only Apple Silicon macOS is tested. The dedicated project leaves the application,
legacy runners and runtime executable-read boundary unchanged. Original files,
results, binaries, logs and environments stay ignored. No workers, Windows
actions/transfers, downloads, source-install/disc/outpost2 writes, system/Xcode/DRM
changes or publication are part of this checkpoint.
