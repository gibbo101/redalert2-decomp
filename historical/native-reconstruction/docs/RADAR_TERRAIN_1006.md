# Radar terrain traversal joined to projection

Tutorial purpose: Boot Camp Objective1 action37's alliance effect needs shared
House sight/coverage/radar effects. This recovers complete631250's terrain RGB
traversal and composes it under complete630B70 on the same Map and RGB backing.
Per-Cell color selection4712C0 remains supplied. This is not original terrain
color provenance or a new playable/SDL capability.

## Shared owners and recovered behavior

`RadarTerrainFields` borrows existing iterator cursor, widthF0/originF8,
minimum-sum1494, pointer slots and the same RGB1238 span used by projection.
A position accessor borrows the actual `MapCellInput` record rather than building
a second radar Cell world. The bounded profile requires this Map and the global
Map to be the same owner. It reuses `resetTileSweepCursor`,
`advanceTileSweepCursor` and `intersectFillRect`; no replacement iterator or
intersection implementation was added. Projection's existing color service binds
this parent directly; there is no RGB copy between stages.

631250 initializes both local RGB triples to zero, resets this Map's iterator,
then advances the global Map before reading global F0/F8. It retains the wrapped
`2*F8-F0+1` offset once per call. Each returned Cell uses signed-word X/Y;
X+Y below the live1494 field skips both intersection and the color child.
Otherwise it forms the two-pixel strip `(X-Y-offset, Y-minimum+X, 2, 1)` and
intersects with the requested region. Empty intersection skips the child.

The output index uses the source width and clipped X/Y, and is saved before
4712C0. RGB storage is read after that child. A strip starting at regionX-1
writes only the second RGB triple; a strip starting at regionX+width-1 writes
only the first; otherwise both triples are written in order. Each triple has a
16-bit pair store followed by its third byte. Traversal continues through the
first null entry, preserving the advance on that terminal call. Initial color
locals persist between iterations. This parent does not clear the RGB buffer.
The joined projection's nonzero update byte may first replace an empty region;
standalone631250 does not perform that replacement.

The native fixture borrows `MapCellInput` positions and the existing cursor type.
The original executes the actual reset/advance/intersection and all projection/
stock lock/FTOL instructions, without patches. Per-Cell4712C0 results are explicit
authored first/second RGB triples, not recovered tile/overlay colors. Initial
slots, positions, dimensions/origins, source/region, existing7x5 BSurface and
scale.5 remain supplied. Native host missing-owner/service/storage/unterminated
traversal refusals replace invalid host accesses; no original rollback is claimed.
A short-storage guard verifies that earlier writes survive a later refusal.

## Evidence and limits

Exact supplied target:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain separate. Complete631250 is420 bytes, SHA256
`b573f332f39eb8c1de56eb3fe46ce849a67bf77282d68b10708eec72a0831e36`.
The verifier pins this parent, reset/advance/intersection and the prior complete
projection family. No public implementation, new dependency, lifted/generated
code or runtime executable read was introduced.

All88 complete roots pass:44 standalone and44 joined projection calls, with
598 iterator advances including terminal nulls,342 actual intersections,
186 supplied color-child calls,664 ordered RGB stores and871 projected pixel
stores. The joined cases also execute132 stock getters and44 lock/unlock pairs.
Explicit left/right/full-strip cases retain respectively2/2/4 RGB stores in both
modes. Other cases cover widths2/3/5/8, first/interior holes, empty maps, minimum
sum rejection, signed-word coordinate extremes, partial/empty regions and seeds.

The oracle audits the full Map and arena, immutable Cells/pointer slots/source/
code/constants/virtual table, caller stack and callee-saved registers. RGB/pixel
store order and final whole-backing digests match. Iterator visits include the
cursor after each actual advance; individual cursor-store order is audited in
the original but is not a separate native ordered-store comparison. This does
not claim original map construction, Cell ownership, initial geometry, actual
Boot Camp asset colors, startup aliasing, DSurface/device behavior, frame fidelity
or independent acceptance.

Canonical originals:
`private/boot-camp-20261020/terrain-fresh-a1/expected.json`.
Fresh generation2.823s/native.029s/driver3.257s. Final normal/sanitizer/uncached
replays each report88 hits/zero misses; wall.451/.685/1.243s. Four new and three
prior Python checks pass; two focused CTests/profile pass. Refusal checks cover
missing owner, missing Cell, missing entered color child, short backing with
retained effects, plus successful empty and complete writes. Native-only guard
improvements reused the same eligible originals. Initial inspection/edit/configure/
build/task/repair wall costs were not separately instrumented. No failed proof
was accepted. Checks: `private/boot-camp-20261020/terrain-checks-a2.json`.
Receipt: `private/boot-camp-20261020/terrain-receipt-a1.json`.
App/owner binary hashes retain prior SDL scope; no runtime/GUI adoption occurred.

## Commands and next integration

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake -S . -B build/native
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake --build build/native --target radar-terrain-vectors --parallel 6
build/tools-env/bin/ctest --test-dir build/native -R '^radar-(terrain|projection)-domain$' --output-on-failure
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_radar_terrain test_radar_projection
# Explicit supported original reuse; choose new report/audit paths.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/NEW-TERRAIN.audit.json tests/compare_radar_terrain.py \
  --exe private/official-1006-probe/game.exe --native build/native/radar-terrain-vectors \
  --expectations private/boot-camp-20261020/terrain-fresh-a1/expected.json \
  --report private/NEW-TERRAIN.json
```

Use `build/sanitize/radar-terrain-vectors` for sanitizer; add `--uncached` before
the driver for the inspection control. Fresh generation selects new `--output`
instead of expectations/report and needs research-only Unicorn JIT. Normal app
commands remain `./build.command`, `./test.command`, `./run.command --boot-camp-walk`.

Next recover actual4712C0 color selection from the existing Cell/tile/image/
overlay owners, then join actual630A00 startup/aliased projection with native
storage and relevant first DSurface lock/pixel semantics. Shared production House/
coverage/actor integration and actual ordinary SDL first-objective acceptance
remain open. Do not adopt authored color triples or turn this composition into a
claim of terrain fidelity. Both games remain incomplete; only Apple Silicon macOS
is tested. No workers, Windows actions, transfers, downloads or system changes.
