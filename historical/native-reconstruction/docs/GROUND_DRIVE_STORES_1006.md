# Ordinary Advance: selected ordered Drive stores

The native ordinary Advance now exposes an optional Drive-store observer without
changing the earlier default diagnostic streams. **594 fresh scenarios /11,026
complete original Advance calls** match normal and ASan/UBSan builds, including
**22,752 selected Drive stores**. This closes the missing observer boundary found
by the [private two-Process pilot](OWNED_UNIT_PROCESSES_1006.md); it does not enable
commands for Unit1 or establish every machine-store order.

## Exact target and recovered correction

The target remains the supplied private `game.exe`, 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 lineage and reported no-CD provenance remain distinct;
pristine authenticity is unverified. Addresses below apply only to this target.
Existing reference/license boundaries in [REFERENCES.md](REFERENCES.md) apply.
No upstream/generated/lifted code or original data was incorporated.

The original terminal branch clears head/driving only when **at least one of the
three head coordinates is nonzero**. An already zero head skips those stores and
retains the driving byte; a Z-only head still enters the clear. The native kernel
previously cleared the driving byte unconditionally. All 40 supported ordinary
transforms now have both zero-head and Z-only-head regressions:80 additional
scenarios retain the 514 legacy scenarios. The new differential suite compares
the retained byte, subsequent inactive call and final state, as well as stores.

When entered, head-clear order is **X -> Y -> driving byte -> Z**, followed by
track=-1 and index=0. The original sites are:

| Instruction | Drive field | Width |
| --- | --- | --- |
| `4A2139` | head X `+40` | dword |
| `4A2141` | head Y `+44` | dword |
| `4A2149` | driving `+63` | byte |
| `4A214D` | head Z `+48` | dword |
| `4A2153` | track `+58` | dword |
| `4A215A` | terminal index `+5C` | dword |
| `4A1F98` | ordinary index `+5C` | dword |
| `4A1FA9` / `4A2633` | accumulator `+4C` | dword |

All nine sites actually execute in the fresh suite. The observer also exposes
inactive accumulator clears. Actor stores and existing query/service events stay
in the same stream, so a comparison checks their relative order with these Drive
stores. This is selected-store evidence, not a trace of every internal write.

## Evidence and limits

[GroundDriveAdvance.cpp](../src/sim/GroundDriveAdvance.cpp) adds the stores at the
actual native assignments. `GroundDriveAdvanceServices::driveStore` is optional
and separate from actor stores and preparation's admission observer. The vector
runner's `--drive-stores` selects the new stream; its default protocol is unchanged.
[verify_ground_drive_stores.py](../tools/verify_ground_drive_stores.py) retains the
complete Advance/children inspection and pins the nine instruction sites. The
original oracle checks instruction address, destination offset and width for each
selected write. It executes unchanged original instructions, with the existing
arena, caller-stack/register, immutable input and instruction checks.

`private/map-depth-1006/ground-drive-stores-v1/` contains `expected.json`,
`report.json`, `native-replay.json` and `sanitize-replay.json`. Fresh generation
cost 16.458s, native comparison 0.102s and driver 18.202s; normal/sanitizer replay
drivers cost 3.066s /5.019s. These are verification costs, not game performance.
Changed-source family refresh and SDL status are recorded in the opening HANDOFF.

The new private distinct-address two-Process trace separately matches 320 Process
ticks /36 complete interleaved draws in both native builds, including 6,443 selected
actor/shared/Drive stores, 2,243 logged coordinate/floor/word queries and 163 gate/
admission/supplied failed-route results. Actor1 reaches actual Advance2 once,
first-preparation2 thirteen times, six wait stores and both supplied failed-route
options. This new run uses no experimental inspection reuse. Its complete data,
private binding, runners and comparisons are under
`private/map-depth-1006/drive-store-candidate/`; it remains exploratory, with no
canonical two-Process proof or runtime promotion. The old closed pilot is unchanged.

Initial actor/type/House/map/queue/padding and named Mark/occupation/notification
services retain the scopes of [GROUND_DRIVE_ADVANCE_1006.md](GROUND_DRIVE_ADVANCE_1006.md)
and [MOVING_RESIDENT_PROCESS_1006.md](MOVING_RESIDENT_PROCESS_1006.md). Domain guards
and unsupported Advance/scatter/sound refusals remain. No new runtime executable
read, original execution in the application, Windows action or source-installation
write occurs. Only Apple Silicon macOS is tested. Base RA2 then YR remain incomplete.

## Reproduction

```sh
./build.command
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/ctest --test-dir build/native --output-on-failure
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

# Fresh original execution needs authorized Mac host JIT and a NEW private output.
build/tools-env/bin/python -B tests/compare_ground_drive_stores.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/ground-drive-stores-new

build/tools-env/bin/python -B tests/compare_ground_drive_stores.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/ground-drive-stores-v1/expected.json \
  --report private/map-depth-1006/ground-drive-stores-v1/replay-new.json
# Add --native build/sanitize/ground-drive-advance-vectors for a sanitizer replay.

./run.command --resident-demo
```

The resident demo retains one commandable mover and one inspection-only parked
Unit. Canonical independent Process ownership, joined refusals/clone/rebind/preview
checks, separate turret commands, both actors on nonflat terrain and actual SDL
selected-actor move/stop/turn/reset acceptance still precede Unit1 commands.
