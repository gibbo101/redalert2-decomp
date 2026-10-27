# Infantry arrival sight schedule

The exact argument-2 interior suffix of Infantry update-position `500AA0` now
has a readable SDL-free implementation. It preserves the ordered mission
transition, old-sight removal, new-sight addition and post-sight map call. This
is an internal scheduling boundary: the complete `500AA0` parent and all four
children remain separate, and the application does not invoke this kernel yet.

## Exact boundary

The supplied executable is 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and pristine
authenticity remain distinct. Original instructions execute only in the private
research fixture; the application never reads or executes the executable.

`tools/verify_infantry_sight_schedule.py` pins the 103-byte / 34-instruction
interior range `501B69..501BCF` and the Infantry vtable associations:

| Slot | Exact base target | Role at this boundary |
| --- | --- | --- |
| `+174` | `500AA0` | complete parent, still supplied |
| `+1D4` | `594C50` | mission transition child, supplied |
| `+41C` | `6D5E90` | remove old sight, supplied |
| `+418` | `6D5C30` | add current sight, already recovered separately |

The block calls `+1D4`, then `+41C(0,0,0,0)`, then `+418(0,0,0,0)`. It next
copies current coordinates and calls supplied `54A550` with arguments
`(coordinates, 0, signed32(lastSightRange + 3), 0)`. The wrapping addition is
preserved. The return from `+1D4` is ignored.

The entry is intentionally interior. Inspection proves that `500AA0` dispatches
arguments other than `2` to a different tail and that its argument-2 path reaches
this suffix after many unrelated Infantry effects. Those earlier branches and
effects were not executed by this fixture and are not claimed as recovered.

## Evidence and limits

Fresh private evidence is under
`private/boot-camp-20261018/infantry-sight-schedule-fresh-a2/`. Sixty-four
unmodified interior executions cover arbitrary signed coordinates and last-range
values including both `+3` wrap edges. Every sequence produced one call to each
supplied child in exact order. Expectation SHA256 is
`a3be6f2490ad672d3e1c4216b5688e4ab7c9b40e2a56a14516f60d5f4e3f1931`.

Normal, sanitizer and uncached replays each retained 64 hits and zero misses.
Fresh original generation took 0.006 seconds. Final replay elapsed times were
0.150 seconds normal, 0.398 seconds sanitizer and 0.275 seconds uncached. The
first restricted attempt produced no receipt because Unicorn could not execute
there; the accepted `fresh-a2` run used the authorized host JIT context.

This does not recover the complete `500AA0` parent, mission transition `594C50`,
initial sight state, shroud drawing or redraw presentation. Sight removal,
visibility removal/increment and post-sight `54A550` are now recovered separately
and composed through explicit unscheduled seams. This proof does not establish
whether Cell crossings have another sight producer. No production callback is
wired, so ordinary SDL walking still does not reveal terrain or advance
Objective1. No Windows action, download, runtime executable read or public/
generated/lifted code was introduced. Only Apple Silicon macOS is tested.

## Reproduce and next integration

```sh
./build.command
./test.command

env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  PYTHONHASHSEED=0 PYTHONPATH=tests:tools \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/infantry-sight-schedule-next.audit.json \
  tests/compare_infantry_sight_schedule.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/infantry-sight-schedule-vectors \
  --expectations private/boot-camp-20261018/infantry-sight-schedule-fresh-a2/expected.json \
  --report private/infantry-sight-schedule-next.json
```

Mission transition `594C50` is now identified with the already recovered exact
Commence kernel, and all four children compose through an explicit shared-owner
seam. Next recover a bounded complete `500AA0` parent path and inspect other
Cell-crossing producers. Wire
`arrivalNotification(2)` only after those entry paths and effects are supported.
