# Stock coverage with both complete radar refresh branches

`CoverageRadarRefreshBinding` joins complete stock6C83F0 addition and6C86F0
removal to both actual634030 branches: zero-mode774F00 copy then6324A0
marks/palette/pixels, and nonzero632000. These use one canonical Cell table,
fallback, mutable12C/130/134/13C fields, terrain140, actor/House/scheme records,
software surfaces, pixel allocations, format/width/lock fields and mark bitmap.
This is an unwired composition; no production/SDL adoption or runtime executable
read was added. See [RADAR_REFRESH_1006.md](RADAR_REFRESH_1006.md) and
[COVERAGE_RADAR_1006.md](COVERAGE_RADAR_1006.md) for the joined kernels.

## Ownership and scope

The new entry reuses `CoverageRadarBinding` for the actual Cell lookup and field
identity checks. It requires an existing `RadarRefreshBinding` over the exact
refresh and radar service objects, then replaces only the coverage refresh
callback with the shared complete refresh kernel. Foreign service associations
refuse before callback installation. Construction makes no gameplay queries.
All borrowed owners and the shared association must outlive the entry. Normal
exit and faults restore callbacks; preceding original effects are not rolled back.
The legacy nonzero coverage facade retains its explicit zero-mode refusal.

The caller binds the same map and stock actor services for coverage and rendering.
The fixture keeps actual8324E0 as the original renderer/map context; it does not
redirect the coverage caller or copy back a second map. House188 clearing precedes
refresh, and supplied4E09A0(2) redraw follows. Coverage flags12C/count13C remain
separate from terrain140. Mark House index15F40 remains separate from alliance30.

The diagnostic alternates addition/removal and refresh mode on retained owners,
with single-call controls. Each original stage has separate caller-stack, return,
callee-saved, immutable-input, full-arena and ordered allowed-write guards. No
owners, counters, pixels, bitmap, schemes or floor cache reset between stages.
The schedule is supplied, not original frame scheduling. The harness's new root
selection seam defaults to the old root for existing radar cases.

Actual stock permission30C, type80->84/Owner3C, Building availability450360,
House/height/map, copy/mark/pixel, floor/discovery, actor color/alliance and scheme/
locale-zero CRT children retain the prior evidence scope. Building's House-power
branch remains unentered; redraw, initial records/associations, zero alpha/depth
planes, startup and diagnostic schedule remain supplied. No public/YR/recomp code
or new dependency was incorporated. No malformed-pointer parity, rollback,
whole-frame fidelity or whole-game completion is claimed.

## Evidence and reproduction

Exact supplied base target:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Research-only Unicorn executes original
instructions in the test harness; the application executes none.

The matrix contains940 sequences: both initial modes across404 previous coverage
cases, plus132 shared-refresh cases with stock coverage state. It includes signed
ranges, early exits, add/remove orders, stock Infantry/Building permissions,
independent type flags, current/null House, format/alignment, lock-depth, palette,
House indexes, bitmap seeds and discovery/cache states. Final projections retain
all512 bitmap bytes plus coverage, actor/House/scheme, surface/pixel/lock, dirty
rectangle, map/fallback and ordered event state. Final nonzero-only stack-point
reporting words remain excluded as in the combined refresh proof; actual consumed
point traces remain checked. Old single-mode projections retain their old scope.

All940 fresh sequences match1,428 separately guarded coverage calls (702 add,
726 remove),856 actual refreshes (428/branch),428 copies/mark rebuilds,
1,257 mark pixel calls and5,136 nonzero pixel/floor/discovery/write calls,
including3,432 reads. A separate fresh132-sequence radar proof retains all prior
commands, labels and outputs exactly. Thirty-three Python checks and five focused
CTests in each normal/sanitizer profile and15 guarded normal/sanitizer/uncached
replays pass. Eligible prior2,835 actor,404 coverage and1,454 resolved-refresh
expectations retain their identity-checked projections on rebuilt runners.
Application/owner hashes retain the earlier106-tick SDL evidence; no GUI rerun
was needed for this unwired composition. Final replay/identity receipt:
`private/boot-camp-20261019/coverage-radar-refresh-receipt-a1.json`.
Canonical expectations:
`private/boot-camp-20261019/coverage-radar-refresh-fresh-a1/expected.json`.
Fresh original146.120s/native.179s; prior radar original20.764s/native.044s.
Configure8.061/8.685s, build12.675/10.801s (normal/sanitizer). Native940-row
preflight.823s; Python checks9.501s and CTest invocations.313/.566s. Initial
configure/build and earlier eight-test costs, task wall and repair wall were not
separately measured. No failed original comparison or guard bypass was accepted.
No new caching, whole-inventory or closed-finalizer run occurred.

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake -S . -B build/native
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake --build build/native --target coverage-radar-refresh-vectors --parallel 6
build/tools-env/bin/ctest --test-dir build/native -R '^coverage-radar-refresh-domain$' --output-on-failure
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_coverage_radar_refresh
# Use new private audit/report paths on every invocation.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/NEW-COVERAGE-RADAR-REFRESH.audit.json tests/compare_coverage_radar_refresh.py \
  --exe private/official-1006-probe/game.exe --native build/native/coverage-radar-refresh-vectors \
  --expectations private/boot-camp-20261019/coverage-radar-refresh-fresh-a1/expected.json \
  --report private/NEW-COVERAGE-RADAR-REFRESH.json
```

Fresh generation substitutes a new `--output` for expectations/report. Use the
sanitizer runner or `--uncached` before the driver for the other profiles. Freeze
all transitive sources throughout each proof/replay. Eligible original expectations
are reused only after identity/receipt/input checks; native results always rerun.
Application commands remain `./build.command`, `./test.command` and
`./run.command --boot-camp-walk`; this composition adds no gameplay control.

Next recover stock surface startup, then production mutable coverage/actor/House
owners, full warm discarded previews and House-map caller integration before
runtime radar/image adoption and actual SDL acceptance. Diplomacy/action37,
ordinary Boot Camp Objective1 and both games remain incomplete. Only Apple Silicon
macOS is tested. Local verification is not independent acceptance. No workers,
Windows actions, transfers, downloads, system changes or closed-finalizer reruns.
