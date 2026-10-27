# Supplied RA2 1.006 FireAngle and ordinary Techno placement

[UNIT_BARREL_1006.md](UNIT_BARREL_1006.md) now verifies the nonneutral pose/cache
prerequisite exposed below, including stock settled pitch and independent part
cache states. Placement-to-drawing lifecycle/invalidation and runtime integration
remain open. The earlier pending-pose statements retain this checkpoint's scope.

October 15, 2026, after `69e277a`. **1,588 fresh original/native comparisons**
and normal/ASan/UBSan replays pass. The complete Techno placement wrapper now
executes with actual Facing/type/kind children. Its stock case joins scoped
FireAngle defaults/missing-key reads and two actual Facing constructors to the
wrapper and subsequent pitch samples. The new SDL-free helper remains unwired.

**Stock HTNK's tested settled barrel facing is 14336, not the neutral 16384
supplied by the earlier voxel fixture.** The ordinary drawing delivery must now
carry that pitch through pose/cache handling before runtime integration. No
whole placement, whole actor construction, rendered-pixel or frame parity is
established by these numeric/protocol results.

## Identity and reference hypothesis

Both privately supplied engines were rehashed before relying on addresses:
`private/official-1006-probe/game.exe` and
`private/windows-baseline-20261014/game.exe`, 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 patch lineage and reported no-CD provenance remain
separate facts; pristine authenticity is not established. No new Windows action,
transfer, source installation/disc write or system change occurred.

Consulted pinned recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439`,
`docs/voxels.md`/LICENSE, and YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88`, `ObjectClass.h`,
`TechnoClass.h`, `TechnoTypeClass.h` and `Facing.h`. The initialization/facing
leads suggested where to test the earlier neutral-pitch assumption. Exact base
key bytes, call/store operands and execution establish FireAngle and the sequence
below. No YR layout/arithmetic or upstream/header/generated code was incorporated.
The inspected recomp MIT grant excludes generated game code. No new dependency
or third-party notice was needed.

## Complete inspected and executed boundary

`tools/verify_unit_placement.py` pins **10 complete ranges / 488 instructions**,
the actual Unit dispatch slots and **two aligned FireAngle field blocks**.
The parent/helper inspection in [UNIT_MODEL_INPUTS_1006.md](UNIT_MODEL_INPUTS_1006.md)
also pins complete type constructors/loaders and INI helpers.

| Routine | Exact patched range |
| --- | --- |
| Complete Techno Unlimbo wrapper, 210 instructions | `0x6C4610..0x6C48C4` |
| Facing SetDesired / SetCurrent | `0x4B8A30..0x4B8B0E` / `0x4B8B10..0x4B8BD9` |
| Facing Current / remaining timer | `0x4B8BE0..0x4B8C78` / `0x453EB0..0x453ECB` |
| Default / rate Facing constructors | `0x4B89D0..0x4B89EB` / `0x4B89F0..0x4B8A23` |
| Type wrapper / actual Unit type leaf | `0x6C12C0..0x6C12C7` / `0x705020..0x705026` |
| Actual Unit kind leaf, returns 1 | `0x70A2D0..0x70A2D5` |

The original FireAngle constructor store at `0x6D9D68` writes full integer **8**
to type `+0x3A0`. The read/call/store block at `0x6DCFDF` requests rules/type-ID
`FireAngle` and stores EAX back to that field. Its present integer decoding is a
read-only service with checked section/key/fallback arguments; actual GetInt runs
the missing-key path against a supplied decoded HTNK section. Supplied stock
rules omit FireAngle, so the scoped default remains 8. Art-file comments are not
the authority for this association or its numeric units. Native text and present
integer parsing remain host behavior, not recovered original parsing.

The complete wrapper executes in **Unit kind 1**. Base Object placement is a
service supplying its result and post-state; input requested coordinates and
actor coordinates deliberately can differ. Map, house, cell/visibility effects,
height divisor and other type/actor records are supplied fixtures. The outer
Unit/Foot placement wrappers, actual map registration, allocation/ownership,
loading, permission and house initialization remain outside this claim.

## Preserved orchestration and arithmetic

`src/sim/TechnoPlacement.*` keeps those service boundaries explicit:

- Divide requested signed X/Y by 256 toward zero, then truncate to signed word
  cells. Query the first bridge byte and store actor `+0x32D` **before** base
  placement, including rejection. Base result consumes its low byte. A successful
  call with on-map byte zero returns true before facing and later work.
- Reset the selected presentation service, pass actor coordinates and wrapped
  `+0x1F4 + 3` to the map service, query actual type, conditionally register its
  effect and call the owner placement service in that order.
- Set body facing from the direction argument's **low byte shifted left eight**.
  Set barrel current facing to 16384, query type again, then request desired
  facing `uint16(16384 - (uint8(FireAngle) << 8))`. The full type integer stays
  unchanged; only this use narrows it. Preserve original Facing timer/step
  arithmetic, signed rates, paused start -1 and wrapping clocks.
- Write actor `+0x3EC=1`, then `+0x3F0=0`, query actual Unit kind 1, call the
  selected two-argument visibility service, then unconditionally clear `+0x190`.
  The next predicate consumes its low byte before its conditional notification.
  The kind-15 branch is inspected but not an enabled native profile.
- Divide **requested Z**, not actor Z, by the supplied positive height divisor.
  Store the low byte of ten times the quotient to `+0x378`. Query the bridge a
  second time; only a zero low byte clears `+0x373`. Signed coordinates, wrapped
  addition and low-byte gates are tested independently.
- Query cell once. A nonnull result gets the value, stores `+0x400`, passes that
  value to the kind service, then passes its result to cell association. A null
  result retains `+0x400`. Projection uses actor coordinates and stores `+0x1A0`
  then `+0x1A4`; owner default replaces `+0x114` only when exactly -1.

Names containing offsets retain unverified semantic labels. Ordered scalar
stores are part of native comparison. Actual original Facing writes are bounded
and counted; native object layout, angle padding and unused timer dword writes
are not claimed equivalent. The native positive-divisor refusal is a safety/domain
guard, not original divide-by-zero/negative-divisor behavior. No callback-mutation
or arbitrary-pointer aliasing equivalence is claimed.

## Stock pitch and existing presentation limit

The combined stock case executes the original FireAngle default/missing read and
actual body/barrel initializers before complete placement. With frame 100,
barrel rate 768 and FireAngle 8, actual subsequent Current calls return:

| Clock delta | Facing |
| --- | ---: |
| 0 | 16384 |
| 1 | 15360 |
| 2 | 14336 |
| 3 | 14336 |
| 10 | 14336 |

These are raw original angle units, not a degrees conversion. The earlier
[neutral voxel root](UNIT_VOXEL_DRAW_1006.md) supplied 16384 and remains valid for
its recorded inputs; it did not prove settled stock pitch. The runtime's current
flat barrel pose is now a specifically identified presentation approximation.
Recover the nonneutral pose/cache path before using this new placement state
to claim stock drawing fidelity. No firing/elevation behavior is enabled here.

## Evidence and reproduction

| Fresh comparisons | Count |
| --- | ---: |
| Scoped FireAngle default/read/store, present and missing | 162 |
| Every FireAngle low byte and three clocks | 768 |
| Base acceptance, on-map and bridge/predicate byte gates | 144 |
| Existing facings, wrapped coordinates/fields and signed heights | 512 |
| Owned HTNK decoded absence/default | 1 |
| Actual stock initialization, complete wrapper and pitch samples | 1 |
| **Total** | **1,588** |

**8,559 callable roots**, **328 scoped blocks**, **18,531 bounded actual Facing
writes**, **12,633 actual scalar writes** and **1,329 supplied stack writes** are
audited. **83 actual missing GetInt calls** and **81 supplied present integer
calls** are recorded. Complete roots guard return address, ESP, caller tail and
callee-saved registers. Execution allowlists, actor-write bounds, whole fixture
arenas, immutable global inputs and metadata store widths/order are checked.
No original instruction is modified. Receipts pin executable, inspection, native/
oracle sources, owned rules, original expectations and each rebuilt runner.

Current receipts: `private/unit-draw-1006/placement-v3/`, both replays and SDL.
Accepted v1/v2 remain separate with their earlier fixtures/source identities;
neither was relabeled. Earlier drawing-state expectations replay **2,347 results
on each current build**, with `post-placement-*-replay.json`; that is cached
original evidence, not additional fresh execution.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/python tools/verify_unit_placement.py \
  --exe private/official-1006-probe/game.exe
build/tools-env/bin/python tests/compare_unit_placement.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/unit-draw-1006/placement-v3/expected.json \
  --report private/unit-draw-1006/placement-v3/NEW-REPLAY.json
# Add --native build/sanitize/unit-placement-vectors for sanitizer replay.
# Fresh original execution requires authorized Mac host JIT context:
build/tools-env/bin/python tests/compare_unit_placement.py \
  --exe private/official-1006-probe/game.exe --output private/unit-draw-1006/NEW-PLACEMENT
./run.command --crossing-demo
```

Normal/sanitizer builds, **304 Python tests**, **9 normal / 8 sanitizer CTest
checks**, four native divisor-domain refusals and source/diff/link audits pass.
Actual unchanged SDL selection/right-click crossing retains 79 samples / 78
updates, 22 occluded samples / maximum 150 hidden pixels, fresh final/no trails,
bypass, clipping and pan return. SDL verifies existing milestone 20 integration;
it does not execute the new native helper or prove original frame parity. Only
Apple Silicon macOS is tested. Unchanged unrelated families were not regenerated.

## Accounting and next work

Continuation began 07:55:19 UTC; private accounting records closing time. Full
inherited delivery time is unavailable. Normal builds: 7.46/3.27 s; sanitizer:
7.42/1.64 s. Final fresh external/driver/original/native costs:
**4.97/4.879/4.001/0.051 s**. Normal/sanitizer replay external: 0.93/1.15 s.
test.command: 1.23 s; sanitizer CTest external/internal: 1.67/1.21 s; final Python
discovery external/internal: 1.03/0.414 s. Checks may contend; no FPS claim.
SDL time is in the private receipt.

A preliminary complete-range check rejected a guessed SetDesired endpoint that
excluded its later early-return branch; full aligned inspection corrected it
before original execution. Its elapsed measurement is unavailable. No build,
comparison or game-playtest failure occurred. V1 took 5.21 s externally; v2
(5.04 s) refined the decoded fixture to an existing section/missing key; v3 joins
the actual stock initializers. No accepted receipt was overwritten. No game
repair, workers, cache infrastructure, Windows/source/system changes occurred.

Next recover the ordinary nonneutral barrel pose/cache decisions, then combine
actual Foot/base depth with the established caller/cache/raster/staging/shadow/
final-surface children before runtime wiring. Complete construction/ownership,
outer Unit/Foot placement, decorations, scheduling, camera/fog/UI and whole-frame
parity remain open. Full base RA2 then YR remains active and incomplete; this is
locally verified work, not independent acceptance or a new gameplay milestone.
