# Boot Camp shared visibility world

[Rectangular visibility traversal](RECTANGULAR_VISIBILITY_1006.md) now resolves
both full-coordinate and word queries through this same table/shared fallback,
then draws the existing actual Cell masks/alpha effect. Invocation and the
animation tail remain explicit; discovery/objectives are not produced.

The later [Cell shroud/fog drawing](CELL_VISIBILITY_DRAW_1006.md) borrows this
same Cell/table/fallback/mask/scenario/House owner for complete475520 and actual
Renderer alpha effects. It remains explicit and unscheduled; drawing produces
no discovery or objective transition. Startup visibility fields retain their
supplied provenance.

The subsequent [SpecialFlags recovery](SCENARIO_SPECIAL_FLAGS_1006.md) binds
default Cell/sight/waypoint calls to the existing scenario first dword. Its
FogOfWar bit is loaded from the actual map and is disabled in both training maps.
Explicit snapshot overrides and supplied local-refresh effect boundaries remain;
no tick/arrival/SDL sight scheduling or objective transition is enabled.

The bounded Boot Camp owner gives the recovered Cell visibility-mask,
visibility-change and resident-discovery kernels one shared mutable Cell record
and the two actual Objective1 structures. The later
[Techno sight composition](BOOT_CAMP_SIGHT_WORLD_1006.md) extends this owner
through reveal-area in both directions. The SDL tick path still does not schedule
sight.

## Exact data and ownership boundary

The supplied executable is 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and pristine
authenticity remain distinct. The application does not read this executable for
visibility data and never executes original code.

`tools/prepare_visibility_data.py` reads the exact 256-byte signed result table
at base VA `7AC3BC` without executing the binary. It writes the ignored artifact
`private/derived/ra2-1006/visibility-data.bin` outside the source installation.
The 296-byte format is:

- eight-byte `RA2VIS1\0` header;
- the 32-byte source executable SHA256;
- 256 signed mask-result bytes.

The prepared artifact SHA256 is
`13b168f8b583febb048b4144aaff207398503bb9470cf89a17693b389abdabb8`;
the embedded table SHA256 is
`2a5a40e39bae9655c359008c5894a2c1082e012ff04cdd78ebc168644546f8f1`.
The loader checks size, complete artifact hash, embedded source identity and
header before exposing the table. Preparation refuses an unknown executable,
the source path, every destination inside the source installation and a
different existing output.

`BootCampVisibilityWorld` owns one `CellVisibilityState` for every actual mutable
Boot Camp map Cell plus one shared fallback. The same object supplies fields to
`6A8D40`, `499FC0` and `568520`; no visibility Cell is copied between kernels.
Binding inserts structure `1019675` at Cell `(71,92)` and structure `1019676` at
its actual mission Cell into primary resident lists without issuing a map query.
Both residents borrow the matching records in `BootCampMissionWorld`.
The visibility owner is destroyed first, so that borrowed mission owner remains
alive for every synchronous callback.

Initial primary/secondary bytes, flags and counter are a supplied zero-state
startup adapter. Resident active flags, list linkage and coordinate association
are also supplied from the actual mission placements and shared Cells. The actual
player House association comes from the mission.
The direct Cell reveal interface refuses other Houses before visibility changes.
The later [owned sight House selection](BOOT_CAMP_SIGHT_HOUSES_1006.md) admits
owned noncurrent Houses at the upper reveal-area boundary, preserving recovered
mask/predicate/rules resolution and rejecting foreign addresses. Redraw, local refresh
and Cell notification are counted named effects; no renderer or UI behavior is
claimed. Closest-resident square root remains supplied through `std::sqrt`.
Each relevant Cell has one resident, so this bounded discovery result does not
depend on choosing between competing resident distances.

## Bounded composition check

The production-owner check explicitly reveals Cell `(70,91)`. Mask calculation
runs in primary then secondary mode over the shared Cells. Ordinary Cell change
stores both result bytes as `FE`, decrements the counter to `-1`, leaves low
`flags12c` as `18`, leaves low `flags140` as `02`, requests one redraw and calls
the discovery parent. On its second diagonal Cell, the recovered signed level
window admits the actual structure at `(71,92)` and dispatches its existing
`DiscoveredBy`/mission chain.

The check observes two mask calls, one redraw, one discovery-parent call, one
selected resident and no fallback store. The actual Objective1 Tag/Trigger then
produces its existing text, Create Team, trigger-control, alliance, speech,
sound and Reveal Around Waypoint requests. A foreign-House call is separately
refused before queries or mutation. This is an explicit focused invocation of
the production owner, not a recovered frame schedule.

The mask and Cell-change headers changed to alias the shared record, so both
accepted exact-oracle suites were replayed against rebuilt runners. Normal,
sanitizer and uncached runs retain all 128 mask cases and all 96 Cell-change
cases with zero misses. Accepted expectation hashes remain:

- mask: `6f26657a53b4d3635ab6ed2873d10298162f25d9297f4befa6b6a61a50c1804b`;
- Cell change: `33996ff417f7ec45212e3f6db53e34426966207eb14d2b815a1e8ccf09323483`.

The complete normal build took 13.96 seconds. The sanitizer configuration and
full rebuild took 6.36 and 59.31 seconds. Five focused sanitizer CTests passed in
0.29 seconds; direct Boot Camp owner checks passed in both builds. All 103 normal
CTest cases, all 1,322 project-local Python tests and both 170-frame host-display
SDL smoke tests pass. The first full Python discovery attempt used system Python
and failed at import because the research packages are project-local; no test
body failed, and the documented environment passed. The first sandboxed SDL
attempt had no display; the same binaries passed both host-display runs.

## Limits

Ordinary Techno sight is not scheduled from the SDL tick path. There is no
shroud/fog drawing, redraw/refresh presentation, action17 child reveal effect,
objective text/audio/team creation effect or scenario continuation. Startup of
the visibility fields and the invocation schedule remain supplied. This native
integration reuses separately verified original kernels; it is not a new
whole-chain original execution or whole-frame fidelity proof. Only Apple Silicon
macOS is tested.

## Reproduce and next integration

```sh
python3 tools/prepare_visibility_data.py \
  --exe private/official-1006-probe/game.exe
./build.command
./test.command
build/native/boot-camp-walk-check private/official-1006-probe
build/sanitize/boot-camp-walk-check private/official-1006-probe

env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  PYTHONHASHSEED=0 PYTHONPATH=tests:tools \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/cell-visibility-mask-next.audit.json \
  tests/compare_cell_visibility_mask.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/cell-visibility-mask-vectors \
  --expectations private/boot-camp-20261018/cell-visibility-mask-fresh-a1/expected.json \
  --report private/cell-visibility-mask-next.json
```

Use the analogous Cell-change command from
[CELL_VISIBILITY_CHANGE_1006.md](CELL_VISIBILITY_CHANGE_1006.md). Add
`--uncached` before the comparison driver for the inspection control, or select
the sanitizer runner for the sanitizer replay.

Both Techno sight directions and complete post-sight refresh are now composed on
this owner through explicit unscheduled seams. Next recover or bound mission
transition594C50, inspect complete500AA0 and other crossing producers, and only
then bind the verified schedule to runtime.
