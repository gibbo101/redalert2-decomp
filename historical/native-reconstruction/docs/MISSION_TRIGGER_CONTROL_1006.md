# Mission Trigger Enable/Disable actions

Complete base action kinds53 and54 now have readable native implementations and
an exact differential proof. Kind53 enables every live Trigger whose Type matches
the action target and then enters the already recovered ResetTimers routine.
Kind54 disables every matching live Trigger. The bounded Boot Camp mission owner
uses both actions on the four targets encountered in Objective1.

## Exact binary scope

The supplied executable is 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Pristine authenticity remains unverified. Addresses below apply only to this
identity.

| Address | Recovered behavior |
| --- | --- |
| `6ADAE0` / table `6AF754` | Complete action dispatcher and 117-entry jump table |
| `6AF1EA` | Kind53 branch and call to `6B1F10` |
| `6B1F10` | Complete Enable Trigger registry traversal |
| `6AF217` | Complete kind54 Disable Trigger traversal |
| `6EDB60` | Store Trigger byte `+40 = 1`, then tail-enter ResetTimers `6ED680` |
| `6EDB70` | Store Trigger byte `+40 = 0` |

Both actions return true when the target is null, the registry is empty or no
Type matches. The traversal rereads live count, backing, Trigger Type and target.
Enable also rereads scenario difficulty. Values0/1/2 respectively test nonzero
Type bytes `+9C/+9D/+9E`; other values bypass those gates. A matching accepted
Trigger stores enabled first, then ResetTimers performs its ordered timer stores.
Disable has no difficulty gate and never resets timers.

The exact implementation is `setMissionTriggerTypeEnabled` in
`src/sim/MissionTriggerControl.hpp`. Registry count/backing are borrowed live
owners. Invalid native backing refuses rather than reading host memory outside the
owned span. The inherited ResetTimers caller-stack scratch remains a supplied
callback because its producing caller has not been recovered.

## Differential evidence

`private/boot-camp-20261018/trigger-control-fresh-a2/` is original-only evidence:
900 complete dispatcher calls, split450 per action. Coverage includes null,
missing and matching targets; counts0/1/4; interleaved Type identities; difficulty
`-1/0/1/2/3`; zero, canonical and noncanonical nonzero permission bytes; and
kind13 present/absent. It executed80 enable stores,125 disable stores and128
ordered timer dword stores. Expectation SHA256 is
`cfcf586f5d4811ba0828e7188fb7aa945455d3ce243957f21f41fafa3a2d8e4c`.

Normal, sanitizer and uncached replays each report900 reuse hits, zero misses and
no original execution. Fresh original generation took0.214s; native comparison
0.037s. Replay comparisons took0.015s,0.320s and0.014s. Full guarded invocations
took0.892s,0.657s and0.936s for fresh, sanitizer and uncached respectively. The
scoped driver dependency closure avoids whole-repository source hashing. Local
verification is not independent acceptance.

`trigger-control-fresh-a1.audit.json` records the rejected first fixture. It used
an unmapped sentinel for the dispatcher's optional owner argument and therefore
failed before producing expectations. The repaired fixture supplies house, owner,
Trigger and location arguments and verifies ResetTimers scratch at its exact
inherited entry `ESP-8`; no guard was weakened.

```sh
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py \
  --audit private/boot-camp-20261018/trigger-control-fresh-a2.audit.json \
  tests/compare_mission_trigger_control.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/mission-trigger-control-vectors \
  --output private/boot-camp-20261018/trigger-control-fresh-a2

PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py \
  --audit private/boot-camp-20261018/trigger-control-replay-normal-a1.audit.json \
  tests/compare_mission_trigger_control.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/mission-trigger-control-vectors \
  --expectations private/boot-camp-20261018/trigger-control-fresh-a2/expected.json \
  --report private/boot-camp-20261018/trigger-control-replay-normal-a1.json
```

Use the analogous sanitizer runner and the recorded `--uncached` audit for the
other replays. Apple Silicon Unicorn requires execution outside the restricted
sandbox; it remains a research/test dependency and original code never enters the
application.

## Boot Camp production join

`BootCampMissionWorld` owns the actual target Triggers in action order:

| Trigger | Initial supplied state | Timer event | Objective1 action |
| --- | --- | --- | --- |
| `0922D5DC` | disabled | 220 | disable |
| `0922D40C` | disabled | 100 | enable |
| `08FABE0C` | disabled | 85 | disable |
| `09CA94AC` | disabled | 38 | enable |

All four actual records carry nonzero permission bytes for difficulties0/1/2.
The bounded runtime supplies difficulty0, so the result is invariant across the
three represented difficulties. It also supplies timer scratch0. The map names
their country `Americans` but has no same-named House; the owner explicitly binds
that country to the player House. Action53/54 do not inspect the House. These are
startup/caller associations, not recovered original initialization.

The four owners join the same three physical Trigger registries as Objective1's
Trigger. At this checkpoint discovery called recovered kinds53/54 and used the
explicit action-effects service for kinds11,4,17,19,37 and21. The later
[action11 recovery](MISSION_TEXT_ACTION_1006.md) removes kind11 from that service. Unknown or
unowned targets throw. At frame0 the real chain leaves enabled bytes `{0,1,0,1}`
and timer pairs `{-1,0}`, `{0,1500}`, `{-1,0}`, `{0,570}`. Draining the destroyed
Objective1 Trigger and Tag retains registry counts4/4/4/0 for the four live target
Triggers.

Normal and sanitizer `boot-camp-walk-check` pass this composition on the supplied
Day1 assets while retaining the walking checks. The application still has no
ordinary discovery producer and does not show objective progress. The remaining
effect, timer scheduling/firing, original difficulty/House startup and objective
UI remain supplied or unrecovered. No original observation, full mission or
whole-game claim follows.
