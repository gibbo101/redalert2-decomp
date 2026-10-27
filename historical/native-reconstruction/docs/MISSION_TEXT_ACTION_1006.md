# Mission action11 Text Trigger recovery

The later [color/localization join](MESSAGE_TEXT_LOOKUP_1006.md) verifies complete
action11 with actual color/duration/lookup/CRT children in one original guest.
Production color now uses the exact private table. Message insertion/display
remain supplied; the historical dispatcher-only receipt below is unchanged.

The later [found-label lookup](STRING_LOOKUP_1006.md) supersedes the supplied
key-passthrough localization below in the Boot Camp owner. It has a separate
3,224-sequence original proof and immutable user-CSF association; this historical
288-sequence dispatcher proof retains its supplied localization child. Color,
message-list insertion and live objective display remain open.

The complete base dispatcher branch `6AE2FF..6AE381` now has a readable SDL-free
implementation. It preserves the color-child call for empty keys and, for
nonempty keys, the rules delay load, `* 900.0` under the original toward-zero FP
state, low-EAX duration, localization child and seven-argument message insertion.
The dispatcher returns true on both paths.

This is exact orchestration around three named children. Color-table lookup
`6715D0`, localization/fallback `6F9EC0`, message-list insertion `5B4DA0`, scenario
startup and rules loading remain supplied. The authored CSF reader is not labeled
as the original localization routine, and no original UI or SDL drawing is
claimed.

## Exact-base evidence

The target remains 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Fresh original-only evidence in
`private/boot-camp-20261018/text-action-fresh-a3/` contains 288 complete dispatcher
calls: four scenario color bytes, six delay values, three supplied color pairs
and four inline keys. All 288 call the color child; 216 nonempty keys execute the
actual `77F110` x87 FTOL helper and supplied localization/display children; 72
empty keys take the exact early return. Expectation SHA256 is
`878b8fb52bc903e51004002e3d6c030a91c113589a5f83aff0d908de92f68ae8`.

Normal, sanitizer and uncached replays each retain 288 original hits and zero
misses. The supplied `.6` `MessageDelay` becomes 539, because the binary double
product is rounded toward zero before the signed-qword conversion. Replacing this
with host-default arithmetic would produce 540 and is incorrect for this target.

The restricted-sandbox fresh attempt exited with Unicorn SIGILL before evidence.
Fresh-a2 then executed originals but caught a native trace label emitted before
the child calls. Both audits are preserved; fresh-a3 rebuilt the runner and
regenerated the proof after that fixture repair. Original generation took 0.068s;
the final native comparison took 0.013s. Guarded normal/sanitizer/uncached replay
invocations took 0.241s/0.330s/0.955s. Repair and total wall time were not
measured. Local verification is not independent acceptance.

```sh
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py \
  --audit private/boot-camp-20261018/text-action-fresh-a3.audit.json \
  tests/compare_mission_text_action.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/mission-text-action-vectors \
  --output private/boot-camp-20261018/text-action-fresh-a3

PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py \
  --audit private/boot-camp-20261018/text-action-replay-normal-a2.audit.json \
  tests/compare_mission_text_action.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/mission-text-action-vectors \
  --expectations private/boot-camp-20261018/text-action-fresh-a3/expected.json \
  --report private/boot-camp-20261018/text-action-replay-normal-a2.json
```

Use the sanitizer runner for the sanitizer replay and `--uncached` for the
recorded uncached control. Unicorn remains research/test-only and original code
never enters the application.

## Boot Camp owner join

`BootCampMissionWorld` validates the actual first action record:
kind11, mode4, key `MISSION:Objective1`, four zero arguments and waypoint token
`A`. It reads the supplied rules `AudioVisual/MessageDelay`, runs the recovered
kernel and records one owned request before action4. Production checks require
selector1, style `0x4046` and duration539. Scenario alternate-color byte0,
selector-to-color token1 and key-passthrough localization are explicit supplied
startup/presentation inputs.

Action11 no longer reaches the diagnostic action callback. The later Create Team
recovery now includes action17 parent forwarding; its reveal child remains supplied. The
owner still refuses before mutation when that
remaining-effect service is absent. No runtime producer calls discovery, and SDL does not
draw the request, so ordinary play remains GI walking/Stop/pause without visible
Objective1 progress.

Next recover another encountered effect and the genuine discovery producer and
schedule. Localization/color handling and SDL objective/message presentation need
their own verified joins before the request is described as player-visible.

Normal and sanitizer production-owner checks pass. The final normal build passes,
including the SDL application, and all 92 normal CTests pass; the 12 mission CTests
pass in both builds and all 27 mission Python guards pass. No SDL smoke was rerun
because ordinary input still cannot produce discovery or draw this request.
