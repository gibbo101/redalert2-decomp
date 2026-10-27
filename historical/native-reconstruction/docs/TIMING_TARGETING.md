# Milestone 3: skirmish pacing and destination bearings

[DRIVE_1006.md](DRIVE_1006.md) records the separately hash-selected supplied RA2
1.006 profile and fresh comparisons on both engines. This note retains its disc
addresses/evidence; native prepared/runtime inputs remain disc-only.

[CURVES.md](CURVES.md) supersedes the curved-track limitation below. The timing,
bearing and target-lifetime boundaries documented here remain current.

October 10, 2026, Ivalice / Apple Silicon macOS. Baseline: milestone 2 commit
`cd17eb8`. The source is the same supplied Allied-disc base RA2 GAME.EXE:

`135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743`

The embedded version is still recorded literally as 1.08. All address-based research
and data preparation check the complete hash first. No YR address or replacement
engine behavior is used as an original-behavior oracle.

## Result and boundaries

The SDL host now uses the recovered **foreground skirmish timer policy**, replacing
the fixed 15 Hz accumulator. The default speed is slider position 3, with bracket
keys or `--speed 0..6` selecting the original range. Position 6 is uncapped.
The timer starts afresh for each simulation update; overdue time is not replayed
as a burst of catch-up updates.

An idle turret now aims toward the movement destination through the original
quantized coordinate-to-bearing calculation. A busy turret finishes its current
turn before accepting a new bearing, as before. Shift-right-click uses the same
bearing calculation with an explicit manual-control override.

This is not a reconstructed whole-game scheduler, mission system or input layer.
Network pacing, campaign timing, original foreground-loss handling, destination
actor lifetime and match-wide update ordering remain outside the implementation.
The native clock source, display refresh and pause/resume policy are host adapters.
Original RA2.INI user preferences are not imported; CLI/default speed selection
belongs to this prototype.

## Recovered timing

| Evidence | Base VA |
| --- | --- |
| Game options constructor, default delay 3 | `0x5D0D80` |
| Slider conversion `delay = 6 - position` | `0x4CF4C4..0x4CF4CB` |
| Options GameSpeed field | `0xA28738` |
| Session type (5 is the skirmish branch) | `0xA255A8` |
| Skirmish frame timer setup | `0x53DEF2..0x53DF16` |
| Coarse clock helper | `0x68F980` |
| Frame timer start / duration | `0x821CB0` / `0x821CB8` |
| Full original frame wait | `0x53E660` |
| Remaining-time prefix | `0x53E660..0x53E697` |
| timeGetTime / Sleep imports | `0x785520` / `0x7851E0` |

The session-type meaning is confirmed in the base binary: `0x513435` selects
value 5, and `0x652B79..0x652B90` maps value 5 to `GUI:SkirmishGame`. The default
delay 3 is inspected constructor evidence, not a separately executed constructor test.

The clock helper returns `uint32(timeGetTime()) >> 4`, not milliseconds multiplied
by 60/1000. One clock quantum is therefore **16 ms**. The remaining-time calculation
uses signed wrapped 32-bit subtraction and a start=-1 sentinel, matching the
existing timer convention. Raw rollover/sentinel cases are compared separately;
no repaired Windows clock-wrap behavior is claimed.

| Slider position | Delay quanta | Nominal quantum span |
| ---: | ---: | ---: |
| 0, slowest | 6 | 96 ms |
| 1 | 5 | 80 ms |
| 2 | 4 | 64 ms |
| 3, default | 3 | 48 ms |
| 4 | 2 | 32 ms |
| 5 | 1 | 16 ms |
| 6, fastest | 0 | Uncapped |

These are quantized timer spans, **not measured original frame rates**. Start phase,
processing time, Sleep behavior and rendering affect actual intervals. For example,
a frame starting at 7 ms with delay 3 becomes eligible at clock boundary 48 ms,
not at 55 ms. Work already beyond that boundary requires no wait.

The original skirmish wait passes the number of remaining *coarse ticks* directly
as Sleep's *millisecond* argument and repeatedly checks the timer. The native host
retains that wait hint while continuing to service SDL input. It renders every simulation update, including uncapped mode; while waiting it
refreshes the camera/UI at roughly 16 ms intervals as a native host adaptation. Uncapped simulation is therefore
machine-dependent and must not be advertised as original full-game throughput.

A speed change affects the next frame timer, preserving the already active wait.
Native pause freezes updates; resume discards the old timer and allows a fresh
update without backlog. This pause/menu behavior is explicitly a host policy.
Campaign/session-0 forcing of delay 2 was inspected in the adjacent original branch,
but is not implemented or counted as a tested campaign scheduler.

## Recovered bearing and turret branch

| Evidence | Base VA |
| --- | --- |
| Object-to-object bearing helper | `0x5CAC70` |
| Quantized atan-like helper | `0x4BA120` |
| Stored 4,097-entry float32 angle table | `0x7FC114` |
| Float32 slope step following the table | `0x800118` |
| Float32 positive / negative half-pi | `0x78BF94` / `0x78BF98` |
| Binary64 pi / half-pi / angular scale | `0x788158` / `0x786630` / `0x786628` |
| Full Unit turret routine | `0x6F03D0` |
| Destination-object pointer in Unit/Foot | `+0x494` |

The coordinate getters supply source and destination X/Y. Z does not participate
in this bearing calculation. The original converts the deltas to float32, divides
to obtain a slope, truncates an index using its stored step, reads the angle table
or its saturation value, applies quadrant corrections, then applies the stored
half-pi offset and angular scale. The final integer is narrowed to 16 bits.

This preserves original table quantization and numeric constants. It is **not**
`atan2` rounded to a 65,536-angle circle. Representative original results from
origin to (256,0), (0,256), and (-256,0) are 16383, 32767, and 49153 respectively;
to (256,-256) the table gives 8315. These are recovered behavior examples, not new
rounding choices. The zero vector also follows the original helper's defined path.

`OriginalMath.hpp` shares the existing scoped round-toward-zero policy and restores
the host FP environment. Strict compiler settings and float32 stores remain intact.
The native helper accepts coordinate differences up to 2^20 leptons per component;
this safely bounds its integer conversion and exceeds the prototype's map domain.
It does not claim faithful behavior for arbitrary overflowing/non-game coordinates.

The full turret routine is compared with no combat target, a normal non-spinning
Rhino turret, no locked weapon, and an optional destination object providing
coordinates. On an idle turret, a destination requests its bearing; without one,
the turret requests the body's current facing. An existing turn finishes first.
Target movement, target changes and temporary target removal are covered.

The prototype represents that destination as an optional coordinate. It installs
it on a movement command and clears it on stop or arrival before the turret update.
Those lifetime rules are **host integration**, not a recovered mission/actor system.
Manual aim overrides automatic aiming until the next movement command. Curved
track selection, combat target priority and weapon behavior remain deferred.

## Keep executable access limited to track data

The runtime still reads only hash-checked **track data** from GAME.EXE and never
executes original instructions. The new angle table is prepared ahead of time by:

```sh
python3 tools/prepare_direction_data.py --exe private/disc-allied/game.exe
```

This standard-library Python tool reads the source executable without modifying it
and writes `private/derived/direction-data.bin`. It refuses unknown executable hashes,
outputs inside the source installation's directory tree, and replacement of different
existing output. Repeating the command for identical data is safe. No original code
is executed by preparation. The derived file is user-owned content and must never
be tracked or distributed.

The 16,464-byte data file includes a format marker, the source hash, the angle table
and its numeric constants. The native reader validates its full SHA-256:

`26cad37f9cab1e7fe290113a2c9322968637489a9c2aad65aa0150ae548f29e6`

This prevents substituted/corrupt table data from silently acquiring the recovery
claim. The default path is relative to the project working directory; `run.command`
sets that directory. Use `--direction-data /absolute/path/to/direction-data.bin`
when launching the native executable elsewhere. The file is already prepared here.

## Differential verification

`tests/compare_timing_targeting.py` checks the executable hash and then compares:

| Group | Comparisons | Oracle boundary |
| --- | ---: | --- |
| Timer remaining | 756 | Original prefix, including sentinel and wrap arithmetic |
| Frame wait | 616 | Original slider/setup blocks plus complete skirmish wait routine |
| Bearings | 6,361 | Complete original bearing/helper chain, axes, zero and seeded map coordinates |
| Lookup boundaries | 12,294 | Inputs around every lookup bin and saturation boundary |
| Turret updates | 9,600 | Complete original Unit routine across 80 changing-target sequences |
| **Total** | **29,627** | All matched |

Original instruction bytes are not patched. Object-coordinate/weapon queries are
explicit fixture services. Timing tests substitute **timeGetTime and Sleep** with a
deterministic virtual clock and intercept the presentation wait service; the
statistics timer is preinitialized. These Win32 services are test doubles only,
not native-game dependencies. They verify requested waits and timer decisions,
not Windows scheduler accuracy, OS sleep jitter or original wall-clock recordings.

The report at `private/timing-targeting-report.json` records the source and native
hashes, seed, case counts and substituted service inventory. The previous 30,608
movement and 16,598 facing comparisons remain regression requirements.

```sh
build/tools-env/bin/python tests/compare_timing_targeting.py \
  --exe private/disc-allied/game.exe
./test.command --data-dir "$PWD/private/game"
./run.command --speed 3 --timing-smoke-test
```

The SDL event smoke uses the actual host scheduler with a deterministic late-clock
fixture and exercises selection, movement destination, manual turret input, speed
keys, pause/resume and rendering. The real-clock smoke runs the normal loop for
about a second and checks update counts against the recovered clock-quantum bound.
Its measured throughput describes this Mac prototype only.

## Original-game observations still useful

To validate integration beyond these routine boundaries, record the exact original
executable hash, skirmish map, resolution/renderer options, foreground state and
slider position. Capture at least ten seconds for positions 0–5 with a fixed scene;
measure update intervals against an independent clock and distinguish simulation
updates from repeated display frames. Repeat with increased scene load to check
how work time changes pacing. Position 6 needs separate uncapped/load measurements.

For turret integration, issue a Rhino move on flat terrain, change the destination
while it turns, stop mid-cell, and observe when its destination is cleared and when
the turret returns to body facing. Those observations constrain the actor/mission
lifetime adapter; they do not replace the arithmetic oracle. No such original-game
recording or pixel-parity claim was made in this milestone.
