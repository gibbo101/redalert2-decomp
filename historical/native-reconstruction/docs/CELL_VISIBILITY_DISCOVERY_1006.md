# Cell visibility discovery projection

The subsequent [radar notification recovery](RADAR_CELL_NOTIFICATION_1006.md)
joins6328F0 to the existing dirty queue in an explicit actual-owner scope and
composes with Cell redraw. Isolated earlier receipts retain their stated scopes.

Current follow-up: [MISSION_WAYPOINT_DISCOVERY_1006.md](MISSION_WAYPOINT_DISCOVERY_1006.md)
joins the actual waypoint/visibility caller and corrects notification to read the
selected Cell+24 independently of the scan point. All64 original projections
below remain through current normal/sanitizer/uncached replays. The historical
unjoined statements below describe this earlier checkpoint.

Base `0x568520` now has a readable SDL-free implementation of the object
discovery projection that follows a Cell visibility change. It is a dependency
of the first Boot Camp objective, but it is deliberately not a destination or
movement trigger. Techno sight, reveal-area mutation and the Cell visibility
parents still precede production scheduling.

## Exact boundary

The supplied executable is 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and pristine
authenticity remain distinct. Original instructions execute only in the private
research fixture; the application never reads or executes the executable.

`tools/verify_cell_visibility_discovery.py` pins five complete ranges:

| Base range | Recovered role |
| --- | --- |
| `568520..5685EA` | Seven-Cell visibility-change projection |
| `471660..47175A` | Closest active primary resident |
| `5D4E40..5D4E61` | Object coordinate copy |
| `4BA410..4BA47E` | Table square root child |
| `77F110..77F14D` | Original integer conversion child |

The verifier also finds exactly six direct calls to `568520`: `499F87`,
`49A0B4`, `49A331`, `49A59C`, `55A397` and `55A46E`. The first four are in the
map/display Cell visibility family. The latter two belong to the complete-map
visibility pass at `55A300`; that pass supplies the current House and notification
byte one when Cell byte120 becomes `FE`.

Separate inspection identifies the ordinary sight chain but does not promote it
to recovered behavior. Techno virtual `6D5C30` stores the last sight coordinates,
range and height at `+1E8/+1F4`, then calls reveal-area parent `54A110`. That
parent can reach the Cell visibility family and ultimately this projection.
Action17 child `6B0670` also calls `54A110`, while its later branch calls the
complete-map pass `55A300`. These relationships establish a visibility producer;
they do not establish a movement-arrival producer or authorize either unrecovered
parent in the native runtime.

## Recovered behavior

The routine reads the starting Cell's packed signed-word coordinates and visits
exactly seven positions, incrementing both words with wrap after every visit.
Its upper level is `1,3,5,7,9,11,13`. A Cell is admitted when its signed level byte
is inclusively between `upper-2` and `upper`.

Every position uses the actual map slot or the one shared fallback Cell. A miss
updates the fallback Cell's packed coordinate immediately. On an admitted Cell:

1. Nonzero argument3 calls Cell notification `6328F0` with that Cell coordinate.
2. Actual `471660` searches the primary head (`+E4`) at point `(0,0)`, with null
   ignored identity. It keeps only flag14 bit0 residents, uses the low byte of
   each coordinate, table square root and original integer conversion, and keeps
   the first resident on equal distances.
3. A selected resident receives virtual `+180 DiscoveredBy(argument2)`.

The native service boundary preserves actual/fallback Cell identity and uses the
existing recovered closest-resident kernel. Cell notification and the selected
object's discovery mutation remain named effects so this kernel can be tested
without pretending the unrecovered visibility parents are active.

## Evidence and limits

Private fresh evidence lives at
`private/boot-camp-20261018/cell-visibility-discovery-fresh-a5/`. Its 64 complete
calls execute 164 closest-resident roots, 143 coordinate/sqrt/conversion chains,
143 supplied `DiscoveredBy` calls and 87 supplied Cell notifications. Cases cover
both inclusive level boundaries, rejected signed extremes, all seven positions,
fallback reuse, notification zero/one, empty/one/two-member lists, inactive
members, low-byte distance wrapping, nearest selection and first-wins ties.

Expectation SHA256 is
`d3ee5f77a008f23f9859d0164db968e25fda8d9cd99d6ac77d05b4683450ed49`.
Normal, sanitizer and uncached replays each retain 64 hits and zero misses:

- `cell-visibility-discovery-replay-normal-a2.json`
- `cell-visibility-discovery-replay-sanitize-a2.json`
- `cell-visibility-discovery-replay-uncached-a2.json`

The final Apple Silicon build including the SDL application passes, as do all97
normal CTests, all1,305 Python tests,22 focused sanitizer CTests and direct normal/
sanitizer Boot Camp production-owner checks. SDL smoke was not rerun because the
new kernel has no production input, drawing or interaction path.

The restricted-sandbox attempts `fresh-a1/a2` ended with SIGILL before producing
a receipt. Unrestricted `fresh-a3` stopped before original execution because the
fixture lacked its exact-address override; `fresh-a4` stopped at the first trace
because it read ECX instead of the routine's saved ESI Cell. Both fixture errors
were repaired before the accepted fresh run; no failed answer was accepted.

This does not recover `6D5C30`, `54A110`, the four Cell visibility parents,
visibility flags/counters, sight timing, E1 Sight startup, structure construction/
membership, shroud/fog drawing, action17 child effects or player-visible objective
progress. The Boot Camp runtime remains GI walking, Stop and pause. No Windows
action, download, runtime executable read or public/generated/lifted code was
introduced. Only Apple Silicon macOS is tested.

## Reproduce and next integration

```sh
./build.command
./test.command

env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  PYTHONHASHSEED=0 PYTHONPATH=tests:tools \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/cell-visibility-next.audit.json \
  tests/compare_cell_visibility_discovery.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/cell-visibility-discovery-vectors \
  --expectations private/boot-camp-20261018/cell-visibility-discovery-fresh-a5/expected.json \
  --report private/cell-visibility-next.json
```

Fresh original execution needs the authorized Mac-host JIT context and a new
private destination. Add `--uncached` for the inspection-reuse control or select
the sanitizer runner for a sanitizer replay.

Next recover the bounded stock-E1 path through Techno sight `6D5C30` and the
relevant `54A110`/Cell visibility branch. Preserve actual sight coordinates,
range, height, call flags and visibility-change gating. Then insert the two real
mission structures into the shared Cell/object ownership and let ordinary SDL
movement produce discovery. Do not call this kernel from arrival or host distance.
