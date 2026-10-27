# Mission action4 Create Team recovery

The complete base dispatcher branch `6AEC7D..6AECB2` now has a readable
SDL-free implementation. It increments shared dword `A40774` with wrapping,
loads the prepared TeamType pointer at action+48, optionally calls child
`6BEC80` with argument zero, then rereads and decrements the live shared dword.
It returns true without inspecting the child result.

The live reread is material: the supplied child may rewrite `A40774`, and the
final decrement consumes that new value. A null TeamType skips the child but
retains both stores. A propagated native callback exception retains the earlier
increment because the original branch has no rollback path.

This recovers the dispatcher parent, not TeamType construction or the large team
creation child. Team member allocation, House ownership, mission/script setup,
placement, Techno membership and rendering remain supplied or absent. The same
global has other recovered loading/admission uses; this proof does not rename or
generalize those owners.

## Exact-base evidence

The target remains 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Fresh original-only evidence in
`private/boot-camp-20261018/create-team-action-fresh-a2/` contains24 complete
dispatcher calls and12 supplied nonnull child calls. Initial global values cover
zero, ordinary, sign-bit and unsigned-limit cases. Null/non-null TeamTypes and
child rewrites to zero/`0xFFFFFFFF` verify optional dispatch, wrapping and the
late live reread. Expectation SHA256 is
`28fe77c72d7b6c1b804a824ab224586547773a5e53e33cd08644115321677114`.

Normal, sanitizer and uncached replays each retain24 original hits and zero
misses. Original generation took0.003s and fresh native comparison0.010s.
Guarded fresh/normal/sanitizer/uncached invocations took
0.389s/8.196s/8.329s/8.728s; their replay drivers took0.214s/0.352s/0.753s.
The three replays ran concurrently, so the guarded wall figures include
inspection contention. Restricted-sandbox fresh-a1 exited with Unicorn SIGILL
before evidence and is preserved. Repair and total task wall time were not
measured. Local verification is not independent acceptance.

The final boundary passes all95 normal CTests, the15 mission CTests in both
normal and sanitizer builds, all36 mission Python guards and both normal and
sanitizer Boot Camp production checks. The SDL application builds; SDL smoke was
not rerun because runtime discovery is absent and the child creates no actors.
Exact identities and limitations are in ignored
`create-team-action-validation.json`.

```sh
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py \
  --audit private/boot-camp-20261018/create-team-action-fresh-a2.audit.json \
  tests/compare_mission_create_team_action.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/mission-create-team-action-vectors \
  --output private/boot-camp-20261018/create-team-action-fresh-a2

PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py \
  --audit private/boot-camp-20261018/create-team-action-replay-normal-a1.audit.json \
  tests/compare_mission_create_team_action.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/mission-create-team-action-vectors \
  --expectations private/boot-camp-20261018/create-team-action-fresh-a2/expected.json \
  --report private/boot-camp-20261018/create-team-action-replay-normal-a1.json
```

Use the sanitizer runner for its replay and `--uncached` for the recorded
uncached control. Unicorn remains research/test-only and original code never
enters the application.

## Boot Camp owner join

The actual Objective1 action4 record names TeamType `0B197B7C`. The bounded
owner validates that ID in the supplied map's TeamTypes list and its `4 GIs`/
`Other2` section fields, then binds one stable identity. That association and
the prepared action+48 pointer remain supplied startup boundaries.

`BootCampMissionWorld` runs the identity through the recovered parent. The
request observes shared counter1 and the final counter returns to zero. The
child callback records the request only; it does not create four GIs. Action4
no longer reaches the diagnostic effect callback. The later action17 parent
recovery removes the final diagnostic effect callback; its reveal child remains
supplied.

No runtime producer calls discovery, so ordinary play remains GI walking, Stop
and pause. Recover genuine discovery production/scheduling and the relevant child
effects before Objective1 can advance through ordinary SDL interaction.
