# Milestone 4: ordinary curved tracks and changed orders

[DRIVE_1006.md](DRIVE_1006.md) records the separately hash-selected supplied RA2
1.006 profile and fresh comparisons on both engines. This note retains its disc
addresses/evidence; native prepared/runtime inputs remain disc-only.

October 10, 2026, Ivalice / Apple Silicon macOS. Baseline: milestone 3 commit
`0e6eb78`. The oracle is the supplied Allied-disc base RA2 GAME.EXE, embedded
version `1.08`, preferred image base `0x400000`, SHA-256:

`135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743`

Every address-based test and runtime table read checks the full hash. No YR
addresses, replacement-engine behavior or original-game recordings were used.
This note supersedes the straight-only and cell-boundary-redirect limitations in
[MOVEMENT.md](MOVEMENT.md) and [TIMING_TARGETING.md](TIMING_TARGETING.md).
Their numeric, timer and targeting evidence remains applicable.

## Result

The SDL-free drive core follows the original ordinary cardinal/diagonal and
45/90-degree curved tracks. It selects a descriptor from two queued directions,
consumes the corresponding one or two route cells, advances original point
coordinates and body facings, and preserves interpolation and arrival credit.
The turret still uses its independent recovered update and destination bearing.

A stock Rhino has `Passive=false`. When an order changes during a curve, it
**finishes the committed curve before following the replacement route**. The
original has a mid-curve switch path, but its Unit-type guard rejects non-passive
units. The native core also implements and tests the enabled branch using a
controlled Passive=true fixture. That does not claim full passive-unit gameplay.

The profile remains a healthy, unpromoted Rhino on flat empty ground with neutral
speed multipliers and a supplied direction queue. Short/special tracks, ramps,
blocked-cell reactions, occupation, pathfinding and mission integration are absent.

## Binary evidence

| Item | Base-game VA |
| --- | --- |
| Full drive Process / advance / preparation | `0x4A01C0` / `0x4A0BD0` / `0x4A2240` |
| Ordinary transition selection | `0x4A3BB3` |
| Unsupported-pair straight fallback | `0x4A3BCB` |
| Consume two / one queued directions | `0x4A415C` / `0x4A4187` |
| Track-switch decision / commit | `0x4A1730` / `0x4A18A3` |
| Unit/Passive guard | `0x4A187F..0x4A189D` |
| Coordinate/facing transform | `0x4A4310` |
| Transition descriptors / raw-track descriptors | `0x78B188` / `0x78B0A8` |
| Unit class-ID return of 1 | `0x6FED40` |
| Passive INI loader / key string | `0x6FF7A8` / `0x7E2B98` |
| Constructor clears Passive | `0x6FF089`, `0x6FF0A3` |

The ordinary transition index is `first * 8 + second`. Each of its 64 entries
occupies 12 bytes: normal raw-track byte at +0, short-track byte at +1, exit facing
at +4 and flags at +8. A zero normal-track byte falls back to `first * 9`.
Without a second queued direction, preparation uses the first direction again.

Flags 1/2/4 retain the original coordinate swap/reflections and matching facing
transforms. Flag 8 selects a two-cell endpoint and consumes two queued directions;
otherwise preparation consumes one. Original coordinates and point facings are
read from the owned executable, not generated from an analytic curve.

A raw descriptor at `0x78B0A8 + 16 * raw` contains the point-stream pointer,
jump index, entry index and cell/occupation index. The loaded ordinary streams are:

| Raw | Shape | Points including terminator | Jump | Entry | Cell |
| ---: | --- | ---: | ---: | ---: | ---: |
| 1 | Cardinal straight | 24 | -1 | 0 | -1 |
| 2 | Diagonal straight | 32 | -1 | 0 | -1 |
| 3 | Cardinal to diagonal, 45 degrees | 55 | 37 | 12 | 22 |
| 4 | Cardinal to cardinal, 90 degrees | 39 | 26 | 11 | 19 |
| 5 | Diagonal to diagonal, 90 degrees | 62 | 45 | 15 | 31 |
| 6 | Diagonal to cardinal, 45 degrees | 57 | 44 | 16 | 27 |

The cell index is retained as metadata, but original occupation effects are not
implemented. Short raw tracks 7–10 and special tracks 11–13 are outside this
milestone; reading the short-track selector does not mean that path is implemented.

At a stored jump index, the original can select a new descriptor from the current
exit direction and first remaining queued direction. An eligible switch adjusts
the endpoint by that direction, consumes it, and resumes at the next track's
stored entry index. The empty-cell fixture exercises the admission branch before
the Unit/Passive guard. Other admission outcomes remain unrecovered.

The guard reads UnitType +0xBA4. The base INI loader ties that field to `Passive`,
and its constructor clears the field. Those naming/default facts are inspected
binary evidence; the whole type constructor/INI loader is not an executed oracle.
The runtime reads the supplied HTNK key with default false. The supplied original
rules leave the Rhino non-passive; this is not a smoothing preference to override.

## Differential verification

`tests/original_curves.py` extends the existing isolated flat-world movement
fixture. It executes the full original drive process, its original preparation
and advance routines, and the full no-target turret update. It adds one explicit
neighbor-cell service at `0x4766C0`, using the original initialized direction
offsets. The map, admission, occupation, getters and mission services retain the
boundaries documented in MOVEMENT.md and the complete report callback inventory.
The original pathfinder returns no route; these tests supply the queue directly.
Original instruction bytes are unchanged.

Each update compares integer X/Y/Z, descriptor, point index, accumulator, driving
state, body/turret facings, rotation flags, current track endpoint X/Y, and the first
four remaining queue entries. The arm64 vector runner calls the runtime drive core.

| Group | Comparisons |
| --- | ---: |
| All 64 direction pairs, including unsupported pairs | 7,680 |
| Stops on each valid curved descriptor, early/middle/late | 17,280 |
| Replaced routes around jump points, Passive false/true | 19,200 |
| Mixed routes, reversals and repeated transitions | 3,120 |
| Fractional-speed interpolation and stopping | 960 |
| **Total, 304 traces** | **48,240** |

All comparisons pass. Branch instrumentation confirms both one/two-cell queue
consumption, unsupported-pair fallback, the Passive guard, and actual switch
commits. The previously established facing, movement, timing and targeting suites
also pass: **125,073 original/native comparisons in total**. These are state/case
comparisons, not a count of independently recovered systems or complete games.

```sh
build/tools-env/bin/python tests/compare_curves.py --exe private/disc-allied/game.exe
```

`private/curves-report.json` records source/native hashes, case counts, branches
and fixture services. `private/curves/` contains local probes, disassembly and
diagnostic vectors. None of those files may be tracked or distributed. Research
uses Unicorn; the native game reads only track data from GAME.EXE and executes none
of it. The six point streams and 64 descriptors are checked before native use.

## Input and clearance adapters

Right-click targets the clicked cell center. A temporary direct route takes
diagonal cells first, then the remaining axis; it never searches for a detour.
Ctrl-right-click appends a waypoint to the remaining queue. There may be at most
23 pending directions, in addition to an already committed track. The yellow
marker shows the final destination. A curve may pass through a waypoint's cell
without passing through its exact center; waypoints supply direction changes,
not mandatory intermediate stops.

Before accepting an order, the host previews the actual drive on a copy, including
the committed active track. It samples the resulting motion at intervals no larger
than 16 leptons and checks four footprint corners at +/-0.25 cell. Existing map
rules reject slopes, elevation changes, omitted objects/overlays and unsupported
terrain. This is conservative sampled clearance, not original collision/footprint
code. A failed preview or an overlong route leaves the existing command intact.
The preview is limited to 4,096 updates and must reach the requested endpoint.

S uses the recovered capped stop speed and finishes the active track; a curve can
span two cells. Q/E similarly defer the manual body turn until that track finishes.
Manual turn timing, route construction, queue replacement, target lifetime and
input controls are explicit native adapters. The routine oracle verifies what the
original drive does with the supplied commands, not how the original input/path/
mission systems produce them.

Native checks cover off-axis destinations, waypoint append, queue bounds, blocked
curve footprint and rejected-order preservation. Owned-data integration loads the
original streams and follows a curved waypoint route. A 170-frame SDL smoke checks
real event handling, a 90-degree curve and a replacement order that retains the
Rhino's committed curve. ASan/UBSan checks cover native tests, owned-data rendering
and all 48,240 cached curve comparisons. Rendered previews are visual QA only.

## Remaining evidence and next work

No full original-game observation or pixel-parity claim accompanies this milestone.
To test the remaining command/mission boundary, record this exact executable hash
and issue a stock Rhino move across level terrain with a 45/90-degree route bend.
Record coordinates/headings per update if available; issue replacement/stop orders
before, near and after the bend's jump index. Measure when the queue changes, which
endpoint remains committed, and when the turret target clears. This separates
drive behavior already compared here from unrecovered input and mission timing.
Screen captures alone cannot establish lepton-level or queue parity.

A useful next bounded milestone is original voxel lighting/palette treatment and
terrain/unit occlusion, keeping movement oracles unchanged. If movement continues
first, recover blocked-cell admission/occupation and short-track selection before
claiming obstacle navigation. General pathfinding, ramps, combat, AI, economy,
campaigns, multiplayer, saves, audio and Yuri's Revenge remain deferred.
