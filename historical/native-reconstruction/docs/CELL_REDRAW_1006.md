# Sight Cell redraw queue

The later [viewport recovery](TACTICAL_VIEWPORT_1006.md) now provides the actual
Renderer camera origin/logical dimensions through complete6A9170, with a supplied
inverse-matrix child. Its explicit actual-world composition tests camera pan/zoom
against this same Cell queue. Frame consumption/reset and live sight remain off;
the older diagnostic-viewport-only wording below retains its checkpoint scope.

The subsequent [radar notification recovery](RADAR_CELL_NOTIFICATION_1006.md)
joins6328F0 to the existing dirty queue in an explicit actual-owner scope and
composes with Cell redraw. Isolated earlier receipts retain their stated scopes.

Complete `6AADD0..6AAF77` now has a readable implementation in
`render/CellRedraw.hpp`. The explicit Boot Camp sight composition can bind it
through `BootCampVisibilityWorld::withCellRedraw` to the existing actual Cells,
frame, floor and height-projection owners. This replaces the count-only redraw
boundary **inside that synchronous scope**. It is a dependency of original Day1
arrival sight/discovery; runtime walking, arrival callbacks and ordinary SDL
Objective1 remain unchanged.

## Exact evidence and ordering

The supplied executable is4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. `verify_cell_redraw.py` fingerprints it
before pinning the complete424-byte parent and its entered call associations.
Original center475D60 and height6A2970 are supplied probes in this isolated
parent fixture; their separate prior proofs are not relabelled as one joined
original proof. No upstream/generated/lifted implementation was used.

The parent returns before writes when loading8324EC is nonzero, Cell5C already
equals frameA40D2C, or both Cell12C bit8 and Cell138 are clear. Otherwise it
**stores the frame before obtaining center coordinates**, including when screen
clipping later rejects the Cell. Both apparent visibility projection branches
perform identical wrapped integer arithmetic. Each intermediate multiplication,
negation, addition, signed half and division by256 retains original semantics.
It saves the center Z but calls6A2970 with **zero**; projecting that saved Z would
be a behavior change.

OriginB0/B4 and the four global viewport words remain independent. Left/right
and bottom comparisons use wrapped sums; the top comparison is fixed-30.
Edges are inclusive. Inside the expanded screen bounds, countE0<799 inserts the
actual Cell identity atE4[count], then rereads/increments count. Count799/800
preserves every capacity tail and skips insertion. Both inserted and saturated
paths clear Cell138 and set ownerD7D. Offscreen/same-frame/loading paths retain
those bytes. Native negative queue indices refuse explicitly; this does not
claim original malformed-memory behavior.

349 complete original calls compare ordered child/store traces and final
frame/138/count/D7D plus **all800 queue slots**. Cases cover ordered gates,
signed extrema/wrapped projection, supplied center Z and diagnostic height,
clip boundaries, queue threshold and untouched capacity tails. The guest audits
entered instructions, allowed writes, code/input immutability, caller stack,
return address and callee-saved registers. Canonical original-only expectations:
`private/boot-camp-20261020/cell-redraw-fresh-a2/expected.json`, SHA256
`9b8fc0c974ac7c5607780113b2581148210f686efae3f74130a8ce66a444f444`.
A1 passed before stricter receipt-validation was added; a2 is canonical. Neither
origin was edited or relabelled. Fresh a2 original generation took.766s.

## Actual owner composition and limits

Each actual Cell now owns one persistent frame5C, explicitly initialized to-1.
Copy/assignment retains its value while preserving the existing borrowed terrain
flags140. BootCampVisibilityWorld owns one queue with800 logical identity slots,
count and dirty byte. Initial queue slots/count/dirty are supplied zeros. Warm
clones copy the full queue and retain logical identities on their corresponding
Cells; they never copy active callbacks.

`withCellRedraw(actualFrame, view, operation)` binds the existing change and
post-sight redraw callbacks for one synchronous operation. Center475D60 reuses
`mapCellCenterHeight` on the **same actual mutable Cell** and floor cache. Height
uses the existing `projectVisibilityHeight` and startup scale. Viewport/origin/
loading association is explicitly supplied by the caller; the actual owner test
uses wide diagnostic bounds. The default outside this scope retains the old
explicit request recorder. Nested scopes and cloning during an active scope
refuse; exceptions clear the scope without pretending to roll back game effects.

The actual arrival-sight check queues actual shared Cells, verifies their actual
frame stamps, checks same-frame post-sight suppression, preserves queue/tails in
warm clones and continues after source destruction. Source world isolation is
checked including queue and all Cell frame fields. These are current-native
integration checks, not original-game observations or independent acceptance.

No render-loop queue consumption/reset, actual SDL viewport/camera association,
new live sight/arrival scheduling or rendered fog fidelity is claimed. The queue
must not be cleared per request to hide saturation. Local refresh47BE00 and its
entered child effects, Cell notification, other arrival/map effects and touched
nonlocal actors still need concrete integration before live Objective1. Recorded
mission requests do not complete actions. No new runtime executable read,
Windows action, dependency, download, source-installation write or system change.
Only Apple Silicon macOS is tested; base RA2 and Yuri's Revenge remain incomplete.

## Reproduce

```sh
./build.command
./test.command
build/native/boot-camp-walk-check private/official-1006-probe - private/boot-camp-20261020/radar-shape-dimensions-a1.bin
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest tests/test_cell_redraw.py

# Reuse originals explicitly; current native always runs. Choose fresh outputs.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
 --audit private/cell-redraw-next.audit.json tests/compare_cell_redraw.py \
 --exe private/official-1006-probe/game.exe --native build/native/cell-redraw-vectors \
 --expectations private/boot-camp-20261020/cell-redraw-fresh-a2/expected.json \
 --report private/cell-redraw-next.json
# Repeat with build/sanitize/cell-redraw-vectors and fresh audit/report paths.
./run.command --boot-camp-walk
```

198 normal/197 ASan+UBSan CTests, `./test.command`, four focused Python tests
and both rebuilt actual-owner checks pass. Each profile explicitly reuses
349 redraw +192 visibility-change +64 post-sight =605 original sequences,
zero misses. Original generation.766s; standard tests4.694s, sanitizer CTest
28.901s, owners6.122/58.067s. Redraw replay.692/.641s; change33.514/13.109s;
post26.884/.725s; focused Python.159s. No comparison/build/check failure.
Commands/hashes/costs: `private/boot-camp-20261020/cell-redraw-receipt-a1.json`.
Unmeasured build/config/inspection/edit/preflight/total wall; concurrent costs
not additive. Preflighta1 ran the previous binary during build completion and
proves no new coverage; preflighta2/final profiles run the rebuilt check. No
unchanged original regeneration or SDL ceremony for this unscheduled service.

Final logs/commands/check costs are under
`private/boot-camp-20261020/cell-redraw-final-{native,sanitize}-a1/`.
Hashes and final verification counts belong to
`private/boot-camp-20261020/cell-redraw-receipt-a1.json`.
Build/configuration/inspection/edit/preflight/total turn costs were not separately
instrumented; concurrent durations are not additive. Initial owner preflighta1
ran the prior binary while the build was finishing; it is not evidence for the
new check. Rebuilt preflighta2 and the final profiles execute the new check.
No SDL ceremony is repeated for an unscheduled explicit service.
