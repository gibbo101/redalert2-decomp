# Boot Camp Object Tag expiration and RaiseEvent composition

`MissionTagObjectExpiration.hpp` recovers the complete base Object expiration
callback for a Tag subject and composes it with the existing Tag RaiseEvent and
Tag44 broadcast on shared owners. Actual typed Infantry/Building callbacks inherit
this Object prefix through additional overrides; those complete chains are not
established by this proof.
See [the later waypoint join](MISSION_WAYPOINT_EXPIRATION_1006.md) for the verified
vtable targets and explicit base-Object recipient scope. The composition closes
the persistence1/count1 case where
RaiseEvent deliberately skips direct owner detachment: the later Object registry
broadcast clears that owner exactly once. **Deferred queue drain and actual Tag
destruction remain unjoined. Discovery, scheduling, action effects and objective
progression remain pending; walking and objective status are unchanged.**

## Evidence and supplied boundaries

Exact supplied base: 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Only Apple Silicon macOS is tested. No
public/header/generated/lifted code, extracted data, dependency or application
executable read was added.

Original-only `private/boot-camp-20261018/object-expiration-fresh-a2/{expected,report}.json`
contains **324 sequences /333 complete Object5D3BD0 roots**. The unmodified
original performs144 matching Tag counter decrements and Object+34 clears, plus35
Object+30 link splices. Native selected logical assignments match those ordered
stores. This does not claim native instruction widths or a complete original-read
trace.

The verifier fingerprints all59 bytes of5D3BD0 through its `ret 8`. Each root
keeps instruction/write/ABI/stack/callee-saved checks, immutable code and whole
owner arenas. Native guards reject an associated subject that differs from the
recipient binding. Observer faults propagate after any earlier ordered effects;
there is no rollback claim. Initial Object/Tag/opaque-link associations and the
Object registry itself remain supplied.

The preserved failed audit
`private/boot-camp-20261018/object-expiration-fresh-a1.audit.json` records the
initial57-byte inspection range. It failed before original execution because the
complete callback is59 bytes. Corrected fresh-a2 is a new original-only proof;
the failed audit is not a behavioral mismatch or an accepted result.

Normal, sanitizer and uncached-inspection current-native replays
`object-expiration-replay-{normal,sanitize,uncached}-a1.json` each reuse324
sequences with zero misses and zero original executions. Original and native
sources, exact executable, expectation file and rebuilt runner identities remain
separate. The shared-owner native composition check covers both persistence1 and
persistence0, actual Trigger destruction, Tag broadcast, Object detachment/link
splice, map/logic/Cell cleanup and deferred append ordering. It does not drain
that queue.

## Recovered behavior

- Object+34 and Object+30 are independent references. If Object+34 equals the
  expired Tag, the callback decrements Tag+2C with wrapped32-bit arithmetic and
  then clears Object+34.
- Independently, when the low byte of `removed` is nonzero and Object+30 equals
  the expired Abstract identity, Object+30 is replaced with the expired record's
  **live** +30 link. Upper bytes of the full removal word do not enable this
  splice. A null subject identity does not splice.
- Repeated callbacks after Object+34 detachment do not decrement again. The
  independent +30 splice can still occur according to its live values.
- The shared composition preserves RaiseEvent ordering: Trigger event/actions and
  destruction precede Tag44 broadcast; broadcast recipient/map/logic/Cell effects
  precede appending the Tag. The deferred queue contains the destroyed Trigger,
  then the Tag.
- With persistence1/count1, direct detachment is skipped and Object broadcast
  decrements/clears the owner. With persistence0, direct detachment happens first;
  the broadcast sees a cleared Object+34 and does not decrement twice.

## Checks, costs and commands

Six focused CTests per build and15 Python tests pass. The existing walking SDL
baseline is retained at its prior scope; no broad/SDL rerun was needed for this
internal dependency. Local verification is not independent acceptance, original
gameplay observation or a completed objective.

Original generation took0.025s. Normal/sanitizer/uncached replay drivers took
0.157s/0.322s/0.278s; their native comparisons took0.006s/0.120s/0.006s.
Focused check, build, manual repair and complete task-wall measurements are
recorded where available in private `object-expiration-validation.json`; missing
measurements remain explicit.

```sh
./build.command
./test.command
./run.command --boot-camp-walk
# Current player capability remains selection/walking/Stop/pause.
build/native/mission-tag-object-expiration-vectors --guards
build/native/mission-tag-expiration-world-check
build/sanitize/mission-tag-object-expiration-vectors --guards
build/sanitize/mission-tag-expiration-world-check
env DEVELOPER_DIR=/Library/Developer/CommandLineTools PYTHONHASHSEED=0 \
  PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/mission-object-expiration-next.audit.json \
  tests/compare_mission_tag_object_expiration.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/mission-tag-object-expiration-vectors \
  --expectations private/boot-camp-20261018/object-expiration-fresh-a2/expected.json \
  --report private/mission-object-expiration-next.json
# Sanitizer: substitute build/sanitize and fresh report/audit names.
# Uncached inspection control: add --uncached before --audit, retaining originals.
# Fresh only for changed original dependencies: omit expectations/report and use
# --output private/mission-object-expiration-new-fresh in the authorized Mac-host
# JIT context.
```

Next recover the complete deferred drain6ECF10 and actual Tag virtual destruction
`7AC700+20 -> 6B42E0 -> 6B39F0` on the same owners. Preserve repeated queue removal
before Release/destruction and do not infer Tag lifetime from the older Overlay-only
proof. Then bind production mission owners and recover genuine discovery/building
dispatch plus encountered scheduling/actions for objective Tag043BD15C. No workers,
Windows actions or runtime executable-read expansion. Full base RA2/YR remains
incomplete.
