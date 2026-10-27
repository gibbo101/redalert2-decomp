# GI sprite facing correction

The Boot Camp GI previously walked backward across the screen because its
simulation-facing sector was used directly as the Ready/Walk SHP direction.
The supplied GI image orders its eight directions screen N,NW,W,SW,S,SE,E,NE.
Simulation facing starts at map north (screen NE) and increases clockwise.
`render/GiSpriteDirection.hpp` now translates the rounded sector with
`(7 - sector) & 7`. Both Ready and Walk use this translation, and static preview
uses the mission record's facing rather than always showing direction0.

This is an authored presentation correction based on inspected original image
frames and the existing verified simulation bearing. The original Infantry
frame-selection routine, sector-boundary quantization, phase/speed/palette/depth/
shadow behavior remain unrecovered or supplied. No simulation, movement, facing
interpolation or original numeric routine was changed. No original expectation
was regenerated; a native image observation does not establish original drawing
fidelity. The actual assets remain private and the source installation read-only.

Private evidence: `private/boot-camp-20261019-facing/` contains an eight-direction
contact sheet from the supplied GI Ready/Walk frames and route/bearing/screen
vectors. Exact supplied engine identity remains4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`;
this correction uses existing prepared bearing data, not new executable reads.
The contact sheet is asset evidence, not execution of original rendering code.

The existing actual-map owner test now checks the displayed direction after each
of its eight real two-Cell GI journeys. It passes normal and ASan/UBSan builds.
The SDL smoke retains selection/move/pause/retarget refusal/Stop/repeated order/
deselection coverage, adds a rightward horizontal trip and leftward return,
requires sprite directions6/2 during moving draws, captures both, and completes
in256 ticks. `sdl-a2/report.json` records success. Both captured frames were
visually inspected; they face in the direction of horizontal travel. The first
sandboxed launch failed before SDL display initialization; its log is retained.
The display-authorized run passed without changing system settings.

```sh
./build.command
./run.command --boot-camp-walk
# Close/relaunch an existing application process to use the rebuilt renderer.
# A fresh private output directory is required for each smoke invocation.
./run.command --boot-camp-walk-smoke-test private/gi-facing-sdl-new
build/native/boot-camp-walk-check private/official-1006-probe
build/sanitize/boot-camp-walk-check private/official-1006-probe
```

Only Apple Silicon macOS is tested. No new dependency, download, Windows action,
system/Xcode/DRM change or runtime executable-read boundary was introduced.
This fixes presentation; ordinary Objective1, base RA2 and YR remain incomplete.
