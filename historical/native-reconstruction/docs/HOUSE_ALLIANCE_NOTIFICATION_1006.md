# House alliance notification parent

`HouseAllianceNotification.hpp` recovers complete base4EC5E0 on borrowed live
House/rules/session/registry fields. It is a separate unscheduled entry, not yet
bound to MakeAlly or Boot Camp action37. This replaces the assumption that the
notification is merely presentation with an inspected and executed diplomacy
coordinator. Recursive MakeAlly/MakeEnemy and session virtual4 remain named
supplied children in this proof; their effects are not claimed as recovered here.

## Ordered behavior

The parent saves rules byte111D before checking the saved nonnull session through
virtual4. Only AL of that result matters. A successful session predicate enables
the traversal regardless of the rule; otherwise the saved rule decides. A session
callback's change to rules111D does not change the already saved decision.

The outer House registry traversal skips null entries and byte13D. In mode0,
either134 or135 makes a House local; nonzero mode uses134 alone. Eligible nonlocal
Houses receive byte191=1 before the inner traversal. No semantic name or startup
value for191 is inferred. Each inner eligible nonnull/non13D House receives
MakeEnemy when local, otherwise MakeAlly, with announce0. Self pairs, duplicate
entries and repeat stores are preserved; there is no extra identity/alliance
precheck in this parent. Child kernels must supply their own real eligibility.

The saved outer House survives callback changes. Both inner and outer traversal
consume live count/backing after child calls, including growth/shrink/replacement;
mode/flags are reread for each entered predicate. Bindings are pure field views,
not copies or synchronization. Missing entered callbacks and out-of-backing
registry access refuse. A refusal after191 stores preserves earlier writes; no
rollback or original fault parity is claimed. The optional191 observer is test
telemetry and must not mutate gameplay state.

## Exact evidence

Executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08/supplied1.006/reported no-CD/unverified pristine are distinct.
`verify_house_alliance_notification.py` fingerprints the whole file and complete
4EC5E0..4EC6DB span, including saved rule/session AL,191 store, both child call
sites and live count reload. No executable instruction is modified.

All1,102 fresh original parent sequences match ordered native traces and final
mutable state. The originals enter996 session queries,496 supplied MakeAlly and
308 supplied MakeEnemy calls. Coverage includes all256 raw values for each
exclusion/local flag, null and aliased slots, self pairs, negative/empty counts,
low-byte session results0/1/255/256/257/high-bit/full-mask, both mode policies,
cached rules and diagnostic late count/backing/flag changes. These mutations are
research fixtures, not observed gameplay. Caller stack/callee-saved registers,
allowed original writes, immutable code, whole private arena/padding and globals
are audited. Initial associations and child effects remain supplied.

Canonical original-only expectations:
`private/boot-camp-20261018/alliance-notify-fresh-a1/expected.json`, SHA256
`7cf5e958145364607e00a74e539c5d7a3df2ccb58ef7ebe85701f7191cdb9102`.
Fresh originals0.245s/native comparison0.027s. Five focused normal and five
sanitizer CTests,20 focused Python tests and12 guarded normal/sanitizer/uncached
replays pass across notification, MakeAlly, threat and mixed House scans. Existing
original expectations retain their identities; native results are never cached.
App/Boot Camp owner hashes retain the prior shared-House SDL scope. No runtime
code changed or new GUI acceptance is claimed from this unwired parent.

The first targeted build in each profile failed because CMake had not yet been
reconfigured for the new target; configuration and both builds then passed.
No original comparison failed. Initial configuration/build times and repair/task
wall costs were not measured; final per-command costs are in the private
`alliance-notify-validation-{normal,sanitize,uncached}-a1.json` records. Receipt:
`private/boot-camp-20261018/alliance-notify-receipt-a1.json`. No whole inventory,
closed finalizer, caching, Windows actions, new dependency or runtime executable
read. Local verification is not independent acceptance. Only Apple Silicon macOS
is tested; both games and Boot Camp Objective1 remain incomplete.

## Reproduce and next integration

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
./test.command
./run.command --boot-camp-walk
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  -m unittest test_house_alliance_notification

# New private audit/report paths; do not overwrite prior proof records.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/NEW-NOTIFY.audit.json \
  tests/compare_house_alliance_notification.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/house-alliance-notification-vectors \
  --expectations private/boot-camp-20261018/alliance-notify-fresh-a1/expected.json \
  --report private/NEW-NOTIFY.json
```

Use the sanitizer runner or `--uncached` before the driver for the other profiles.
Fresh originals use a new `--output` directory and authorized research-only JIT.
There is no new ordinary SDL control for this unscheduled entry.

Recover MakeEnemy4E5A70 and required entered children before composing actual
recursive diplomacy. Bind threat-grid/map/redraw/type/image effects on shared
production Houses/actors, then adopt both action37 calls. Session startup,
Team/audio/live scheduling/UI and ordinary SDL Objective1 acceptance remain open.
