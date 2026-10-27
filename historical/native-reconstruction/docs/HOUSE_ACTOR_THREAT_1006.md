# House grid joined to stock actor threat

`HouseActorThreat.hpp` scopes complete House grid4F3420/Cell projection54E370
around the actual recovered stock Techno threat6D3E50 and Building getter4532F0.
It borrows the same actor/type/rules owners and delegates to the existing single
kernels. This is a separate verification composition, not production adoption.
Object Cell virtual1A4 remains supplied here. Actual map children, production grid
ownership, diplomacy/action37 and Boot Camp Objective1 remain open.

## Ownership and recovered ordering

The binding replaces only `HouseThreatWorld::threat2A0` while it lives. It restores
the prior callback at destruction, including nested bindings and exception unwind.
Construction validates required accessors but performs no actor/world queries.
The actor service factory and field accessor must provide pure borrowed views;
they must not synchronize, query a map or copy logical state. The caller keeps
the services, rule, actors, types and stencil arrays alive. Stable composition
owners cannot be copied or moved. Binding is a host adapter, not original startup.

Grid clearing, saved reverse traversal/live registry backing, raw active flags,
positive threat admission, repeated kind queries, stored-Cell Owner filtering,
Building Cell branch, ordered stencil stores and wrapped-add/negative-zero behavior
remain in `HouseThreat.hpp`. Stock threat retains saved type identity, null-type
bypass, signed positive564 test, two Building getter calls, intervening rulesBE8
sample and low32 multiplication. The original instructions for the stock type80
thunk, type84 getters and kind2C getters now execute from inside the grid proof.
Neither a second threat formula nor a mirrored actor is introduced.

Original tables remain private research inputs passed explicitly to the vector
runner. Nothing reads another executable range at runtime, ships extracted data,
or enables a new game command. Existing production threat and SDL walking scope
from [TECHNO_THREAT_1006.md](TECHNO_THREAT_1006.md) remain unchanged.

## Evidence

Exact supplied base executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08/supplied1.006 lineage/reported no-CD/unverified pristine remain distinct.
The verifier composes the existing grid/table and stock threat/type/kind pins.
Original instruction bytes are unmodified; Unicorn remains research/test-only.

All743 fresh complete grid roots match. Actual calls include1,814 threat/type80,
1,170 Building getters,830 Building type/2,297 Building kind,984 Infantry type/
1,524 Infantry kind and1,304 projections. There are557 supplied Cell1A4 calls;
no threat2A0 or kind2C call is intercepted. Initial records, type/rule associations,
House/session startup, registry population and the Cell callback remain supplied.
The callback's late flag/Owner/Cell mutations are diagnostics, not gameplay
observations. Stock getter execution counts are audited separately from the
ordered parent/type/kind trace because the getter is a pure field load.

Cases cover shared type identities, repeated actors, null types, signed field/rule
limits and wrapped products, raw active bytes, mode/alliance/Owner filtering,
negative signed-word projection and near-edge stencils. The inherited oracle
checks caller stack/registers, code/tables, all arena/padding outside the permitted
grid writes, global registry/mode/invalid Cell words and unchanged rule pointer.
Expected grid contents come from original memory, not a native or Python formula.

Canonical original-only expectations:
`private/boot-camp-20261018/grid-actor-fresh-a1/expected.json`, SHA256
`920d931c44899d66ce92e45484ee0f4fabbaa84eb69039695dc10e3d6dd0b953`.
Original execution28.098s/native comparison0.055s. Both targeted builds,4 focused
CTests per profile,16 Python tests and12 guarded normal/sanitizer/uncached replays
pass. Replays cover this join, stock threat, legacy grid/score/projection and
joined diplomacy, retaining prior originals with explicit current source/runner
identities. No guard was bypassed or old receipt relabeled. No comparison failed.

Normal/sanitizer configuration8.281s/10.636s and targeted builds1.733s/1.599s.
Check/command costs are in `grid-actor-build-*-a1.json` and
`grid-actor-validation-*-a1.json`. Receipt:
`private/boot-camp-20261018/grid-actor-receipt-a1.json`. Repair/task wall costs are
unavailable. No new caching, whole inventory refresh or closed finalizer rerun.
Application/owner binaries retain their previous hashes and106-tick SDL walking
scope; this research-only binding adds no drawing/input change, so SDL was not
rerun. Local verification is not independent acceptance or whole-chain gameplay.

## Reproduce and continue

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake -S . -B build/native
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake --build build/native --target house-actor-threat-vectors --parallel 6
build/tools-env/bin/ctest --test-dir build/native --output-on-failure -R '^(house-actor-threat|techno-threat|house-threat|house-diplomacy)-domain$'
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_house_actor_threat test_techno_threat test_house_threat test_house_diplomacy
# New audit/report names preserve the existing original receipt.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/NEW-GRID-ACTOR.audit.json \
  tests/compare_house_actor_threat.py --exe private/official-1006-probe/game.exe \
  --native build/native/house-actor-threat-vectors \
  --expectations private/boot-camp-20261018/grid-actor-fresh-a1/expected.json \
  --report private/NEW-GRID-ACTOR.json
./run.command --boot-camp-walk
```

Use the sanitizer runner for its replay or `--uncached` before the driver for a
control. Fresh original proofs use a new `--output` directory and authorized
research-only JIT. Normal project entry points remain `./build.command`,
`./test.command` and `./run.command`.

Next join actual Object current-Cell5D51E0/repeated548000 lookups to the Building
branch on borrowed map/fallback owners, then production House/grid/table ownership
without runtime executable-read expansion. Required map/redraw/type/image effects
still precede diplomacy/action37 adoption. Startup/session/Team/audio/scheduling/
UI/ordinary SDL Objective1 remain open. Both games and Objective1 are incomplete.
No public code, dependencies, downloads, workers or Windows actions were added.
