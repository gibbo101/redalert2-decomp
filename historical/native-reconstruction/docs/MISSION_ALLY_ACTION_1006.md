# Mission action37 Make Ally recovery

The complete base dispatcher branch `6AE382..6AE3BE` now has a readable SDL-free
implementation. Value `-1` returns true without House lookup. Every other signed
value is forwarded to the House resolver, then the alliance child is called in
strict mutual order: current House to resolved House, followed by resolved House
to current House. Both calls receive announce byte zero, and the branch returns
true without inspecting child results.

This recovers the dispatcher parent, not the large House mutation child.
House lookup `4ED760`, `House::MakeAlly` `4E5660`, House construction and action
value association remain named supplied boundaries. No diplomacy, threat, UI,
announcement or movement-gate effect is claimed from the parent proof alone.

## Exact-base evidence

The target remains 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Fresh original-only evidence in
`private/boot-camp-20261018/ally-action-fresh-a2/` contains 54 complete dispatcher
calls. Six signed values cover `-1`, ordinary, negative and signed-limit inputs;
current and resolved House identities independently cover null, distinct and
aliased owners. There are 45 supplied lookups, 90 ordered supplied alliance-child
calls and nine exact missing-value returns. Expectation SHA256 is
`8e33f830cb28cc9ad5cf35b0a8e1879b9e685f6b4b9d00928a61ef4f5c8afb1c`.

Normal, sanitizer and uncached replays each retain 54 original hits and zero
misses. Original generation took 0.009s and the fresh native comparison 0.010s.
Guarded fresh/normal/sanitizer/uncached invocations took
0.329s/0.214s/0.294s/0.737s. The restricted-sandbox a1 attempt exited with
Unicorn SIGILL before evidence and is preserved. Repair and total wall time were
not measured. Local verification is not independent acceptance.

The final boundary passes all 93 normal CTests, the 13 mission CTests in both
normal and sanitizer builds, all 30 mission Python guards and both normal and
sanitizer Boot Camp production checks. The SDL application builds; SDL smoke was
not rerun because no runtime producer invokes discovery and this request has no
player-visible output. Exact identities and the corrected isolated-Python
invocation are recorded in ignored `ally-action-validation.json`.

```sh
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py \
  --audit private/boot-camp-20261018/ally-action-fresh-a2.audit.json \
  tests/compare_mission_ally_action.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/mission-ally-action-vectors \
  --output private/boot-camp-20261018/ally-action-fresh-a2

PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py \
  --audit private/boot-camp-20261018/ally-action-replay-normal-a1.audit.json \
  tests/compare_mission_ally_action.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/mission-ally-action-vectors \
  --expectations private/boot-camp-20261018/ally-action-fresh-a2/expected.json \
  --report private/boot-camp-20261018/ally-action-replay-normal-a1.json
```

Use the sanitizer runner for the sanitizer replay and `--uncached` for the
recorded uncached control. Unicorn remains research/test-only and original code
never enters the application.

## Boot Camp owner join

The actual Objective1 record is kind37, mode0, value13, four zero arguments and
waypoint token `A`. `BootCampMissionWorld` now runs it through the recovered
parent. The bounded owner explicitly supplies value13 as the player-House lookup;
the action's current House is Other2. It records calls `Other2 -> Player` and
`Player -> Other2`, both without announcement, before the later speech action.

The production owner does not yet execute `4E5660` behavior. It does not alter
alliance masks or feed diplomacy into movement, targeting, combat, threat or UI.
This preserves the verified parent order without substituting a partial child for
the original side effects. Action37 no longer reaches the diagnostic callback.
The later action17 parent recovery leaves its reveal child supplied.

No runtime producer calls discovery, so ordinary play remains GI walking, Stop
and pause. Next recover another encountered effect and the genuine discovery
producer/schedule. The complete House alliance child must be recovered before
Objective1's diplomacy effect is treated as gameplay state.
