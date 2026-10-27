# Mission action17 Reveal Around Waypoint parent recovery

The complete base dispatcher branch `6AE588..6AE5B4` now has a readable
SDL-free implementation. The shared dispatcher first reads the second call
argument and replaces a nonnull object with null when byte `+0x7D` is zero.
Action17 then calls child `6B0670` with the action as `this` and the original
first, filtered second, third and fourth arguments in order. Its low return
byte is returned unchanged.

This recovers the parent only. Child `6B0670`, interpretation of action value
`6` as a waypoint, House visibility changes, map shroud/fog mutation, redraw
and player-visible reveal remain supplied or absent. `MissionRevealObjectArgument`
makes the inherited byte `+0x7D` input explicit instead of assuming a native
object layout.

## Exact-base evidence

The target remains 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Fresh guarded evidence in
`private/boot-camp-20261018/reveal-action-fresh-a6/` contains nine complete
dispatcher calls and nine supplied child calls. It covers null, inactive and
active object arguments, distinct forwarded dwords, unsigned limits and child
results whose high bytes differ. Expectation SHA256 is
`5110a60b1780afc5ccfdb56817982ffa9dc38f773c483f67dcabd3b37bfae909`.

Final normal, sanitizer and uncached replays each retain nine hits and zero
misses. Original generation took0.001s; the fresh native comparison took0.031s.
Replay driver times were0.003s/0.097s/0.003s and guarded totals were
0.312s/0.446s/0.871s. The guarded fresh call took0.435s. A restricted-sandbox
direct fresh attempt exited with
Unicorn SIGILL before evidence; a corrected pre-final fixture and direct fresh
receipts remain private. Local verification is not independent acceptance.

```sh
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py \
  --audit private/boot-camp-20261018/reveal-action-fresh-a6.audit.json \
  tests/compare_mission_reveal_action.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/mission-reveal-action-vectors \
  --output private/boot-camp-20261018/reveal-action-fresh-a6
```

Use the sanitizer runner for its replay and `--uncached` for the recorded
uncached control. Unicorn remains research/test-only and original code never
enters the application.

The capability boundary passes all96 normal CTests,20 sanitizer tests selected
by the mission filter,39 mission Python guards, both normal/sanitizer Boot Camp
production checks and the full native build including the SDL application. SDL
smoke was not rerun because no runtime producer invokes discovery and the reveal
child has no presentation effect.

## Boot Camp owner join

The actual Objective1 record is `17,0,6,0,0,0,0,G`. The bounded mission owner
validates it and runs the recovered parent with the actual action, Other2 House,
structure1019675, Trigger state and packed fallback Cell `0x7FFF7FFF` identities.
It records one child request for waypoint token6. Object byte `+0x7D` and the
child result1 remain supplied native inputs. The child records only; it does not
reveal terrain or alter visibility.

All ten actions encountered by the Objective1 Trigger now have recovered parent
orchestration, so production discovery no longer needs a diagnostic effects
callback. No runtime producer invokes discovery. Genuine structure discovery
scheduling, child effects, actor creation, visible text/audio/reveal, timer
firing and objective UI remain before ordinary SDL Objective1 progress.
