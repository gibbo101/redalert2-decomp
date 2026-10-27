# Stock Techno threat and production actor ownership

Complete6D3E50 threat calculation and4532F0 Building getter now live in the
SDL-free `TechnoThreat.hpp`. The exact stock Infantry/Building vtables both select
6D3E50. `BootCampWalkWorld::composeActorThreat` binds that calculation to the
existing shared GI type and actual mission Building owners through an explicit,
unscheduled entry. House threat-grid and diplomacy callers remain unjoined.

## Recovered behavior and associations

Type virtual80 is called first and its returned identity is saved. Null returns
zero without kind, Building getter, rules or type598 reads. Otherwise kind2C runs.
For kind6, the first signed Building564 getter must be positive to select the
special branch. The routine then samples signed rulesBE8, calls the same Building
getter again and returns the low32 product interpreted as signed. It neither
saturates nor clamps. Non6 or nonpositive564 returns the saved type's signed598.

The native kernel retains the two getter calls and the rules sample between them.
No effects or concurrent mutation are inferred for these stock read-only getters.
The complete original Building getter is simply its signed field564 load. Its
startup, semantic name and gameplay writer are not recovered here. No YR layout
or meaning is applied to this base routine as evidence.

The verifier independently pins actual stock type80 thunk6C12C0, type84 getters
506950/453C60 and kind2C getters509800/453C40. The original proof executes these
children instead of supplying their results. Their Infantry/Building type fields
are respectively5A8/418 and kind results15/6. Initial actor/type/vtable/rules
associations remain supplied; this is not original constructor/startup recovery.

## Owned Boot Camp seam

Five GIs borrow one signed type598 value. The two objective Buildings borrow their
existing stable BuildingType records and new signed field564 on their actual
StructureOwner sight/effect state. No actor is copied into the calculation.
RulesBE8 is an explicit borrowed argument, with no inferred configuration name.
The supplied `ThreatPosed` key/default0 association initializes type598 for GIs
and Buildings; original INI order/defaults/mapping are not claimed as recovered.
Building564 starts at supplied0 until its real writer is reconstructed.

Clones copy these logical values with the existing independent world/type owners.
Native owner checks alter the shared GI type, consume actual Building564/type,
exercise signed wrapping and a live rule, then verify warm isolation and continued
use after source destruction. No new gameplay command, scheduler, visibility
mutation or grid rebuild is introduced. Existing explicit sight/image refusals
remain. This removes a supplied threat-value dependency for the coming grid join;
it does not complete diplomacy or Boot Camp Objective1.

## Exact verification

Target:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08/supplied1.006/reported no-CD/unverified pristine remain distinct.
Complete79-byte parent,7-byte Building getter and all stock type/kind roots plus
vtable associations are fingerprinted. Original instructions are unmodified;
Unicorn is research/test-only and no executable runtime read was added.

All3,053 fresh original sequences match. They include3,044 parent/type-thunk,
1,237 Building getter,1,521 Building type/792 Building kind and1,523 Infantry type/
794 Infantry kind calls. Signed full-width values cover null type, nonpositive564,
negative/masked/wrapped products, direct getter and deterministic random inputs.
Every callable audit checks caller stack/callee-saved registers, rejects all
non-stack CPU writes, preserves code inputs and verifies the whole arena/padding
and rules global. Expected results come only from original registers, not a native
calculation or a Python formula. No live-original gameplay observation is claimed.

Canonical original-only expectations:
`private/boot-camp-20261018/actor-threat-fresh-a1/expected.json`, SHA256
`9a6ad766bfe89c4a2dfefb3f67ea8227b04ccbddf2a34724da70ea114b6d7aab`.
Original execution0.282s/native comparison0.025s. Both full builds, normal152/152
and sanitizer151/151 CTests, both production owner checks,45 Python tests and24
guarded normal/sanitizer/uncached replays pass. Replays cover threat plus prior
House grid/diplomacy/MakeAlly/scans/discovery/waypoint services with current
source/runner/input/receipt guards; no native result caching or whole inventory
refresh. The rebuilt actual106-tick SDL walking selection/movement/Stop/preview/
drawing check passes with objectives disabled. It is not whole-frame fidelity or
original whole-chain acceptance. Prior owned-tank SDL was not rerun for this seam.

The first normal Python invocation used nonexistent `test_unit_discovery`.
Its failed log is retained; the corrected `test_unit_discovery_evidence` invocation
and all normal replays pass in `actor-threat-validation-normal-a2.json`. The earlier
owner/CTest successes remain in normal-a1 rather than being rerun. No original or
native comparison failed, and no identity check was bypassed or result relabeled.

Normal/sanitizer configuration13.111s/14.868s and builds13.689s/15.832s;
CTests1.92s/14.85s. Exact commands/owner/replay/Python costs are in the private
`actor-threat-build-...-a1.json` and `actor-threat-validation-...-a1.json` records,
with corrected normal-a2 as above. Receipt:
`private/boot-camp-20261018/actor-threat-receipt-a1.json`. SDL, repair and task-wall
costs unavailable. No caching or closed finalizer rerun. Local verification is
not independent acceptance. Only Apple Silicon macOS is tested.

## Reproduce and continue

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
./test.command
build/native/boot-camp-walk-check private/official-1006-probe
build/sanitize/boot-camp-walk-check private/official-1006-probe
./run.command --boot-camp-walk

# Choose new private audit/report names; keep previous originals immutable.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/NEW-ACTOR-THREAT.audit.json \
  tests/compare_techno_threat.py --exe private/official-1006-probe/game.exe \
  --native build/native/techno-threat-vectors \
  --expectations private/boot-camp-20261018/actor-threat-fresh-a1/expected.json \
  --report private/NEW-ACTOR-THREAT.json
```

Use the sanitizer runner or `--uncached` before the driver for other profiles.
Fresh originals use a new `--output` directory and authorized research-only JIT.
No new ordinary SDL control is added by the explicit threat seam.

Next join actual grid rebuild to this threat child and actual actor/House/map
owners, preserving saved reverse traversal/live backing and original tables.
Required map/redraw/type/image effects, startup/session and action37 adoption
remain open, as do Team/audio/live scheduling/UI/ordinary SDL Objective1 acceptance.
Both games and Objective1 remain incomplete. No public code, dependency, worker,
Windows action or runtime executable-read expansion was added.
