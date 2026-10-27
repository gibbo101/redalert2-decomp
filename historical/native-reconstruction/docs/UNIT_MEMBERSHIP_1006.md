# Unit map and Cell membership

Later [occupied Cell recovery](OCCUPIED_CELL_1006.md) joins actual recalculation
in a separate profile. This earlier supplied-service domain has fresh v5 proof
with unchanged v4 commands/results/labels. The scopes below remain historical.

Current continuation: [UNIT_DISCOVERY_1006.md](UNIT_DISCOVERY_1006.md) joins actual
visibility/discovery in a separate profile. This earlier supplied-service domain
has fresh `unit-membership-v4` proof and both replays with unchanged v3 commands,
results and labels after extension hooks/vector additions. Statements below
retain the original checkpoint scope. Helpers remain unwired.

After `cc9c8b7`, complete ordinary Unit map/Cell insert/remove, stock lazy
foundation, Object/Techno/Foot Mark and occupation execute together with actual
shared map/floor children. **594 fresh sequences / 3,743 complete calls** match
native C++, followed by normal and ASan/UBSan replays. This is a recovery
checkpoint; the new SDL-free helper remains unwired. Complete base RA2, then
Yuri's Revenge, remain incomplete. No independent acceptance or frame parity is
claimed.

## Identity, references and domain

Both supplied copies rehash equal at 4,485,392 bytes / SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`:
`private/official-1006-probe/game.exe` and
`private/windows-baseline-20261014/game.exe`. Embedded 1.08, supplied 1.006
lineage and reported no-CD changes remain distinct; pristine authenticity is
unverified. No new Windows action/transfer, download, source-install/disc/outpost2
write, DRM/system change or publication.

Pinned YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88`,
`ObjectClass.h` GetFoundationData/occupation/DiscoveredBy declarations,
`CellClass.h` AddContent/RemoveContent and `MapClass.h` AddContentAt/RemoveContentAt
supplied naming leads. Hypothesis: Unit membership requires its own foundation,
visibility and occupation path beyond static Terrain. Exact base vtables,
inspection and execution decide behavior. YR names/addresses and replacement
behavior are not base evidence. No YRpp license file found. Retained recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` LICENSE grants MIT for its own work,
excludes original/lifted game code and retains stale The Movies wording. No
upstream/header/generated/lifted code, extracted table, new dependency or runtime
executable read was incorporated.

The domain is Unit kind 1, nonnull supplied UnitType and Drive (actual layer 2),
stock single-Cell foundation, four canonical fixture Cells including the shared
fallback, and supplied initial actor/type/house/tactical/table/global records.
Other linked-list nodes are stable supplied identities. Object/Unit lazy flags
retain upper bits; already-initialized lists are supplied stock values. Heap/
atexit effects, visibility predicates, actor notification and Cell recalculation
are explicit services. Special byte is zero. Bridges are not enabled for gameplay.

Map parents read a table slot before checking its combined signed index. Native
membership refuses out-of-table indices **before that read**. It does not reject
negative individual word coordinates when their combined index is valid.
Full-coordinate occupation lookups remain distinct from map membership's word
coordinates; their aliases and shared fallback are tested. Malformed/cyclic input
refusals are native safety checks, not original error fidelity.

## Actual chain and preserved behavior

`tools/verify_unit_membership.py` inspects **30 complete ranges / 1,636
instructions**. **28 ranges / 1,588 instructions** enter; the retained unused
relative-height and Cell-center roots remain outside this join's execution.

| Added routine | Base entry |
| --- | --- |
| Map insert / remove | `0x54AB70` / `0x54AF70` |
| Cell insert / remove | `0x473B30` / `0x473D20` |
| Object foundation / UnitType foundation | `0x5D4470` / `0x5D5D90` |
| Bounded foundation copy / Unit eligibility | `0x482E10` / `0x41B470` |

The earlier [Mark](UNIT_MARK_1006.md) and [occupation](UNIT_OCCUPATION_1006.md)
roots and actual getter/redraw/map/floor/FTOL children run in the same guest.

- Map entry rejects a null actor, then tests type byte `+0x205` and actual layer
  2 before foundation work. The Object wrapper initializes its separate fallback
  sentinel before two type queries. UnitType initializes `(0,0), (32767,32767)`;
  each cold flag/list write precedes its supplied atexit registration. The actual
  32-slot copy terminates at this list's sentinel. Other copy counts/truncation,
  null-type wrapper use and cleanup execution are not newly verified.
- Word foundation addition and combined signed indexing precede slot selection.
  Null slots skip Cell work and recalculation. After Cell work, the parent reloads
  the slot; replacement selects the new Cell, removal writes the original word
  point into the shared fallback before recalculation with `-1`.
- Unit Cell insertion prepends only if the head is null or `head->next != actor`.
  This is neither a general duplicate search nor a `head == actor` test. Next
  precedes head stores, and the alternate byte selects `+0xE8` versus `+0xE4`.
- Insertion saves Cell-center X/Y before actual floor at `(128,128)`, calls the
  first visibility service, and only on low-byte false recomputes the center and
  calls the second. Notification runs when both are false or the live global gate
  is nonzero. Notification precedes live eligibility `+0x5A0` and the copied actor
  coordinates passed to actual occupation.
- Removal clears Next only when found. It still invokes eligible unmark on a
  list miss. There are no reference counts. Actual occupation preserves its
  saved-Cell identity, independent floor query, delayed threshold/flag/Z reads,
  signed wrapping, asymmetric bridge gate and repeated whole-dword assignments.
- Foot mode 2 still bypasses all parents and membership. Accepted other Mark
  modes preserve image/owner/coordinates probes, on-map/redraw stores, repeated
  coordinates and actual map dispatch. The existing renderer layer adapters are
  not reinterpreted by the membership layer-2 result.

`sim/UnitMembership` owns only portable logical records and operations. Callbacks
bind recovered native occupation/floor and supply the unrecovered services.
The test binding immediately forwards fallback coordinates and table changes
between native record views. No original instructions are modified. Logical
selected writes and named calls are compared; full native machine-write/read
ordering, padding or allocator representation is not claimed.

## Evidence and reproducibility

Current proof: `private/map-depth-1006/unit-membership-v3/`. V1 has the earlier
552-sequence schema before the explicit notification-mutation field and fallback
identity parameter. Its matching results and replays remain historical. V2 adds the 42 diagnostic
sequences; v3 tightens region-wide selected-store width auditing. V2/v3 commands,
outputs and labels match, and the original 552 outputs/labels remain unchanged.
No receipt is relabeled.

The current run audits **10,802 selected stores**, 2,180 actual Object/Unit
foundation/copy calls, 1,150 calls to each map parent, 1,420 Cell inserts / 1,524
removes, 1,082 occupation marks / 1,153 unmarks, 4,290 actual Cell-floor calls and
7,252 FTOL entries. Services: 1,419 first / 636 second visibility calls, 798 actor
notifications, 2,020 recalculations and 351 atexit registrations. Return low byte
where defined, ESP/callee-saved/caller tail, block/write allowlists, dispatch/code/
table identity, immutable inputs, complete Cell/actor/type/house/locomotor/tactical
arenas, ordered selected writes/calls and final lazy-state digests are audited.

Forty-two sequences apply **supplied diagnostic notification mutations** to actor
coordinates/eligibility or the current map slot. They verify delayed reads,
replacement and fallback reload. They are not observations of original-game
notification effects. Other sequences use unchanged records at that service.
Ten native malformed/domain refusals are checked separately.

Both builds, **782 Python tests, 56 normal / 55 sanitizer CTests** pass. Actual SDL
terrain crossing/ramp/cliff checks pass unchanged: 78-update crossing; 44-update
ramp with 29 tilted, one stored-ramp lag and 23 positive-height samples; parked
Z416/depth-52/gradient2/153 visible/886 rejected pixels. The helper is not wired
into these checks. App hash remains
`61731c8f45379c83107b8b73e85848e65523ba7558245b5c256ce6b0c4f63617`.

Broad source/CMake inventory changes have fresh `terrain-runtime-map-v6` proof
and both replays, retaining all 13,515 selected Cell outputs and 255 input slices.
Closing receipt/source/privacy/AST/link audit and measured timings are recorded
in `private/map-depth-1006/unit-membership-closing-audit.py` / JSON. No workers or
caching infrastructure; full inherited delivery/research elapsed is unavailable.
The audit checks **106 replay records / 6,580 source entries**, recursively 6,846;
**102 prior records unchanged without reexecution**, 458 Python ASTs and 848
local links. Native/sanitizer builds took **12.671 / 11.186 seconds**, Python wall
3.101 (unittest0.669), test-command 2.909 and sanitizer CTest wall 6.359. Fresh v3
CLI wall 10.185, replays 1.200/3.397; runtime refresh original 14.181 / CLI 26.273,
replays 7.907/14.577; actual SDL 5.227. Independent checks ran concurrently.
The existing harmless duplicate static-library linker warning remains; no
sanitizer diagnostic.
The final audit-only edit also passes focused evidence guards and fresh/replay
proof. Two pre-acceptance harness failures (4.255 / 8.488 seconds) corrected an invalid
generated map point and an incorrectly chosen native refusal point. No failed
result was accepted or original instruction patched. V2 adds the explicit
diagnostic cases after v1 passed, with both independently generated.

```sh
./build.command
./test.command
PYTHONDONTWRITEBYTECODE=1 build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
build/tools-env/bin/python tests/compare_unit_membership.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/unit-membership-new
build/tools-env/bin/python tests/compare_unit_membership.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/unit-membership-v3/expected.json \
  --report private/map-depth-1006/unit-membership-v3/replay-new.json
# Fresh execution needs authorized Mac host JIT; use a new private destination.
# Add --native build/sanitize/unit-membership-vectors for sanitizer replay.
./run.command --terrain-demo
./run.command --parked-cliff-demo
```

Select Rhino, G crosses the ramp, R resets, Q/E turns, A/D aims and S finishes
the committed track and stops. Picking/direct routes/clearance remain host
approximations. Only Apple Silicon macOS is tested. Recover actual visibility
`0x568140/0x5683C0`, notification `0x6C2440`, occupied-Cell recalculation
`0x472540` and their required associations before joining mutable membership into
complete Process, then runtime move/stop/turn acceptance. Initial construction,
admission/reservation/mission, general pathfinding, combat/economy/AI/campaigns/
multiplayer/audio/original saves/YR remain later.
