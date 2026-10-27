# Wall damage and removal in the Cell parent

`damageMapWall` reconstructs complete Cell475FE0 over the existing mutable
`MapWallCell` and wall-update services. It uses the existing wall-update and
inclusive RNG kernels; no duplicate map, movement algorithm or runtime binding
is introduced. This is the removal dependency called by Unit notification, not
a delivered tank-crushing interaction.

## Original evidence and behavior

The supplied private base executable was rehashed before using addresses:
4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Original instructions are unmodified.

The whole-text field search uses executable sections with explicit skip-data
handling, then aligned function inspection. Its candidates are not behavioral
proof by themselves. It finds the Unit notification path at6FF28A..6FF30B:
actual Crusher/ability17 and overlay Crushable tests lead to a sound request,
Cell475FE0(-1), flag59F clearing and a float32 velocity increment. That enclosing
Unit caller, sound and velocity continuation are **inspected only** here.
The Cell parent itself does not test Crushable: it requires overlay+278 Wall.
Do not replace that distinction with an unconditional overlay clear.

Complete Cell475FE0..4763CF performs:

- Absent overlay or a zero Wall byte returns false without bounds or map queries.
- Damage -1 bypasses the random admission. Otherwise, signed damage below
  strength+274 enters actual inclusive6388A0(0,strength) only when supplied global
  A40774 is zero. A result greater than or equal to damage returns false.
- Shadow bounds precede overlay bounds. The original inline asymmetric union
  matches the existing recovered union kernel. This caller subtracts **only Y**
  camera offset before its dirty notification; the ordinary wall updater subtracts
  both coordinates.
- Damage data+11E adds16 with byte wrap, preserving its low nibble. At the
  penultimate stage with more than two levels, directions0,2,4,6 query neighbors.
  Matching Wall overlays with data below16 recursively receive damage200.
- The original late stage/nibble tests decide whether to return false after the
  data mutation or remove. Removal clears owner+50, overlay+44, then data+11E,
  in that order. Recalculation(-1), zone0, zone2 and map notification follow.
- Existing complete wall updates execute on directions0,6,4,2, in that order.
  Pointer-expiration notification then precedes eight ordered neighbor queries
  and wrapping neighbor-byte+122 decrements. Aliased Cells remain shared.

Levels+270 and strength+274 agree with the existing base `OverlayTypeInputs`
reader. Borrowed type fields and the global remain live references, and binding
makes no queries. Missing services refuse when entered. There is no transaction:
the native late-recalculation fault check retains the preceding owner/overlay/
data clears. Production command rejection/preview protection is not widened.

## Verification and limits

Canonical evidence is `private/crushing-consumer-20261018/fresh-a3/`, its adjacent
audit, and strict `replay-normal-a3.json`/`replay-sanitize-a3.json` with audits.
**514 scenarios execute624 original damage calls**, including110 recursive calls,
366 removal returns,46 inclusive RNG calls,34 draw attempts and four rejection
retries. The current native runner matches return values, final selected Cell
fields, ordered diagnostic query/store events and complete selected RNG state.
Both replays execute current C++ and zero original instructions, retaining exact
source/binary/input/receipt identities.

Coverage includes all256 initial damage bytes, signed level extremes, damage -1,
negative/zero/positive thresholds, disabled RNG bytes0/255, the original
INT_MAX-width RNG bypass, shared lookup aliases, signed-word coordinate wrap,
recursive damage and actual downstream wall-update/removal/zone-order branches.
The diagnostic `D` prefix has six integers before the existing `U` stream:
damage, levels, strength, global bypass, RNG disabled byte and supplied RNG seed.
The old `C`/`U` streams retain their format. Seven native guards cover live type
changes, query-free binding, entered missing services and propagated late faults.

Initial Cells/types, map association/lookup policy, supplied RNG state, occupant
records, bounds/camera, dirty queue, zone notifications, pointer-expiration
broadcast and recalculation effects remain supplied. The parent and its actual
recursive wall/RNG children execute unchanged; those services are not recovered
world behavior. The inline union is observed as a diagnostic event, not an
original function call. Original arena/input/callee-register/return-address/
caller-tail and selected-write guards remain. The fourth neighbor reuses the
consumed root argument slot as scratch; it is not the protected caller tail.
This is not an exhaustive field-read proof or an original-game observation.

Failed a1 retained an overly narrow oracle routing guard for the already inspected
word-addition child42ADD0. Failed a2 rejected the consumed argument scratch slot.
Both are retained; neither is relabeled or repaired by modifying original code.
An intermediate sanitizer fixture was stale after an overlapping source edit;
the source was touched without changing bytes, both fixtures rebuilt, and both
guard runs passed before the canonical proof. Current identities are recorded.

The arm64 app rebuild,68 root CTests and1,206 Python tests pass. Applicable native
sanitizer replay and guards pass. No unchanged original matrix, closed finalizer,
whole-inventory refresh or new SDL run is needed or claimed for this unwired
dependency. Earlier two-tank/positive-neighbor gameplay and SDL receipts retain
their scopes; local verification is not independent acceptance or frame fidelity.
Current costs and receipt hashes are in HANDOFF and the adjacent private validation.

## Reproduce and continue

```sh
./build.command
./test.command
./run.command --owned-demo
build/native/map-wall-update-vectors --damage-guards
build/sanitize/map-wall-update-vectors --damage-guards

# Fresh execution requires the authorized Mac host research/JIT context.
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/wall-damage-NEW.audit.json \
  tests/compare_map_wall_damage.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/map-wall-update-vectors --output private/wall-damage-NEW

# Retained-original replay always executes current native code.
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/wall-damage-replay-NEW.audit.json \
  tests/compare_map_wall_damage.py \
  --exe private/official-1006-probe/game.exe \
  --native build/sanitize/map-wall-update-vectors \
  --expectations private/crushing-consumer-20261018/fresh-a3/expected.json \
  --report private/wall-damage-replay-NEW.json
```

Focused builds use `cmake --build build/native --target map-wall-update-vectors
--parallel 4` and the corresponding `build/sanitize` directory, under the existing
`DEVELOPER_DIR` environment. Next join the actual Unit notification caller and
relevant velocity/Unit tick behavior, then the production mutable map and drawing
invalidation, before permitting ordinary SDL wall traversal. Startup, routing,
controls and scheduling remain supplied; commands predict zero future ticks.
Base RA2/YR and the whole game remain incomplete. Only Apple Silicon macOS is
tested. No new upstream/generated/lifted code, assets, executable reads,
dependencies, Windows actions, downloads or system changes are introduced.
