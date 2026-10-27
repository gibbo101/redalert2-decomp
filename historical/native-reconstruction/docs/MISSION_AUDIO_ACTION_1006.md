# Mission action19 sound and action21 speech recovery

The complete base dispatcher branches `6AE961..6AE980` and
`6AEAD3..6AEAED` now have readable SDL-free implementations. Action19 forwards
the signed stored index to child `713DB0` with panning `0x2000`, raw float32
volume bits `0x3F800000` and the null dispatcher-local controller. Action21
forwards its signed stored index to child `7158C0` with mode2 and parameter `-1`.
Both branches return true without inspecting child results.

This recovers the two dispatcher parents, not either audio child. Index
construction, audio startup/state, mixing, playback, timing and SDL integration
remain supplied or absent. Public names identify action19 as Play Sound Effect
and action21 as Play Speech, but the exact operands and call order come from the
supplied base executable.

## Exact-base evidence

The target remains 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Fresh original-only evidence in
`private/boot-camp-20261018/audio-action-fresh-a2/` contains14 complete
dispatcher calls: seven action19 sound-child calls and seven action21
speech-child calls. Signed values cover ordinary, negative and signed-limit
inputs. Expectation SHA256 is
`ae07d5676de5128a03ae0e3301a298e3c68a0b6c57cc6ff6e1574f1927460128`.

Normal, sanitizer and uncached replays each retain14 original hits and zero
misses. Original generation took0.002s and fresh native comparison0.010s.
Guarded fresh/normal/sanitizer/uncached invocations took
0.385s/0.303s/0.426s/0.819s. Restricted-sandbox fresh-a1 exited with Unicorn
SIGILL before evidence and is preserved. Repair and total wall time were not
measured. Local verification is not independent acceptance.

The final boundary passes all94 normal CTests, the14 mission CTests in both
normal and sanitizer builds, all33 mission Python guards and both normal and
sanitizer Boot Camp production checks. The SDL application builds; SDL smoke was
not rerun because runtime discovery is absent and no audio service consumes the
requests. Exact identities and limitations are in ignored
`audio-action-validation.json`.

```sh
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py \
  --audit private/boot-camp-20261018/audio-action-fresh-a2.audit.json \
  tests/compare_mission_audio_action.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/mission-audio-action-vectors \
  --output private/boot-camp-20261018/audio-action-fresh-a2

PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py \
  --audit private/boot-camp-20261018/audio-action-replay-normal-a1.audit.json \
  tests/compare_mission_audio_action.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/mission-audio-action-vectors \
  --expectations private/boot-camp-20261018/audio-action-fresh-a2/expected.json \
  --report private/boot-camp-20261018/audio-action-replay-normal-a1.json
```

Use the sanitizer runner for its replay and `--uncached` for the recorded
uncached control. Unicorn remains research/test-only and original code never
enters the application.

## Boot Camp owner join

The actual Objective1 action19 record names `HealCrate`; its zero-based position
in the supplied base `sound.ini` SoundList is292. The actual action21 record
names `Mis_T1_DrillSearg03`; its zero-based position in the supplied base
`eva.ini` DialogList is247. The ignored extracted files retain source hashes
`0bae2956...bf6f5` and `b4716e8c...f144b`. This token-to-index association is a
supplied startup boundary, not a recovered loader.

`BootCampMissionWorld` runs both indexes through the recovered parents and
records their exact child requests. The child callbacks do not play sound or
speech. Action19 and action21 no longer reach the diagnostic effect callback.
The later action17 parent recovery leaves its reveal child supplied. The
owner still refuses before mutation without that remaining-effects service.

No runtime producer calls discovery and no audio service consumes these requests,
so ordinary play remains GI walking, Stop and pause. Recover Reveal Around
Waypoint and genuine discovery production/scheduling before Objective1
can advance through ordinary SDL interaction.
