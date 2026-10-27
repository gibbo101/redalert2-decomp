# House map sight refresh scans

The later [production mixed sight join](BOOT_CAMP_HOUSE_MAP_SIGHT_1006.md) uses
pure live Owner/current-House getters alongside pointer-field bindings. Its fresh
1,238-sequence proof retains every original projection below. The explicit
production seam reaches actual GI/Building sight/visibility/post-sight owners;
mutable diplomacy and ordinary scheduling remain unjoined.

Separate SDL-free `HouseMapRefresh.hpp` implements the complete `49E000` sight
removal and `49DE00` sight addition scans called by MakeAlly. It borrows one live
actor registry, per-actor flags/Owner/position/range, current House and rules flag.
The two existing recovered House predicates run as actual children in the proof.
Virtual kind/type/sight/image services, post-sight54A550 effects and initial
associations remain supplied. MakeAlly/production diplomacy remain unjoined.

## Recovered scan behavior

Both roots save the signed count once, visit slots in ascending order, and
reread the registry backing each iteration. Null slots and nonzero actor byte76
skip. Initial virtual2C kind6 plus a nonzero low-byte skip argument skips before
House queries. Kind queries at later decisions remain separate calls.

Actual4F52B0 selects local ownership by House flag134/135 when mode is zero and
by current-House identity otherwise. A local actor needs nonzero byte373 before
sight dispatch. Its four arguments are all zero. A nonlocal actor is queried
again for kind6, then the late rules142B byte and actual4E5540 alliance predicate
are tested. This branch dispatches `(0, secondArgument, 0, null)` and skips the
later type/image path. The signed second argument is preserved without narrowing.

Removal otherwise queries virtual80 and type byteADD, calling virtual3B0 only
when that returned type's byte is nonzero. A local removal also takes this path
after virtual41C. Addition has an additional late kind6 branch: virtual80 type
byte534 and another actual local-House query select forced virtual418 arguments
`(0, 0, 1, currentHouse)`. That branch also skips later image work. Other addition
paths use type byteADD and virtual3AC. The returned type identity is retained even
if virtual80 changes the actor's type; the selected type's fields remain live.
No invented semantic name is assigned to either type flag.

Every entered addition sight callback is followed by post-sight54A550 with a
**copy** of the actor's late+88 coordinates, inner radius0, wrapped `range1F4+3`
and final flag0. The point/radius are sampled after virtual418; the next virtual80
sees mutations made by post-sight. Removal has no post-sight call. The API keeps
both scans in one kernel without flattening these differences.

## Kernel reuse and supplied boundaries

The simulation header has no rendering/SDL dependency. Its House service bindings
in the research runner call the existing `unitOwnerTypeVisible` and
`unitOwnerAlliedToCurrent` implementations in `render/UnitTypeVisibility.cpp`.
Those unchanged scalar functions were independently recovered earlier; this
avoids a second House policy implementation. Actual original4F52B0/4E5540 execute
unchanged in this new proof, including signed indices and x86 mask shifts.

Actor/type views borrow stable field lifetimes without queries or copies. Sight,
kind, type, image and post-sight callbacks may change live fields/backings; binding
itself may not. Seven supplied diagnostic mutation modes exercise late flags,
Owner/House/rules changes, saved count/live backing, returned type identity, point/
range snapshots and following-slot eligibility. They are not original-game
observations or recovered effect implementations. Normal composition still needs
actual sight/post-sight/map/visibility ownership and complete MakeAlly integration.

Null slots are supported. Null Owners requiring a dereference, foreign identities,
undersized backing and missing entered services are explicit native refusals.
Callbacks needed only on skipped branches are not required. Refusal does not
promise rollback. Initial registries, House/type/actor records, vtables, service
associations, rule/global construction and lifetime are supplied. Fixture `R0` is
a void-call completion marker, not an original EAX return-value claim.

## Exact-base evidence and commands

The executable is 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD and unverified pristine
authenticity remain distinct. Complete spans are `49E000..49E10B`,
`49DE00..49DFFE`, `4F52B0..4F52E3` and `4E5540..4E557E`. The verifier pins
selected operands and complete span hashes before any original execution. All
instructions within these roots/House children execute unchanged; named virtual
and54A550 leaves are intercepted at explicit boundaries.

All1,238 fresh original sequences match:632 removal and606 addition roots,
3,781 actual local-House and1,185 actual alliance children,6,043 supplied kind,
3,063 type,677 removal-sight,1,280 addition-sight/post-sight,946 removal-image and
472 addition-image callbacks. Original caller stack/saved registers, code, globals,
full arena including padding, ordered event traces and mutable projections are
audited. Separate House/type/actor backing regions retain distinct addresses.

Canonical original-only expectations:
`private/boot-camp-20261018/house-map-refresh-fresh-a1/expected.json`, SHA256
`2e33d241edc11c1a000cb37988883ad730ca723ec15a579540bfe3739ebc5e08`.
Fresh original generation took0.607s. Normal/sanitizer/uncached new-family and prior
House eligibility/threat replays retain the original identities/receipts. Final
checks, runner hashes and elapsed costs are in `house-map-refresh-receipt-a1.json`
and the opening handoff. Local verification is not independent acceptance,
complete MakeAlly effects, an original whole-chain proof or ordinary objective
completion. No cache or closed finalizer rerun was added.

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
./test.command
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  -m unittest test_house_map_refresh

# Use new private audit/output names; preserve canonical originals.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py \
  --audit private/boot-camp-20261018/house-map-refresh-fresh-NEW.audit.json \
  tests/compare_house_map_refresh.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/house-map-refresh-vectors \
  --output private/boot-camp-20261018/house-map-refresh-fresh-NEW

PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py \
  --audit private/boot-camp-20261018/house-map-refresh-replay-NEW.audit.json \
  tests/compare_house_map_refresh.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/house-map-refresh-vectors \
  --expectations private/boot-camp-20261018/house-map-refresh-fresh-a1/expected.json \
  --report private/boot-camp-20261018/house-map-refresh-replay-NEW.json
```

Recorded replay names use `house-map-refresh-replay-{normal,sanitize,uncached}-a1`.
Use the sanitizer runner for its replay and put `--uncached` before the driver for
the control. Prior-family names are `map-refresh-prior-{threat,alliance}-replay-...`;
they retain `house-threat-fresh-a3`/`house-alliance-fresh-a1` with their respective
runners. Exact invocation arrays are preserved in the private validation receipt.

Next recover MakeAlly's per-Techno target/reference handling, then compose the
actual parent/House/map/threat/sight dependencies on shared owners, validate full
warm preview isolation, and continue Team/audio/scheduling/UI and ordinary SDL
objective acceptance. The unchanged app retains its walking scope via
`./run.command --boot-camp-walk`; live objectives and production diplomacy remain
disabled/request-only. Both games are incomplete; only Apple Silicon macOS is
tested. No public/YR/recomp implementation, dependency or runtime executable read
was added. Unicorn remains research/test-only.
