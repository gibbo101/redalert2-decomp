# Red Alert 2 original-target recovery

The active project reconstructs readable C/C++ for the exact user-supplied base
RA2 executable before a later native Mac adaptation. It is incomplete.

Root `src/recovered/` holds the accepted, exactly matching recovered source;
current counts (regions, matched body bytes, padding, remaining scaffold and
matched bytes per hour) are generated into [status](docs/STATUS.md). Most
original code is still scaffold. Regions are matched intervals, not certified
original functions or a playable-game claim.

| Path | Purpose |
| --- | --- |
| `src/recovered/` | Canonical accepted recovered C/C++, tracked in Git |
| `manifests/` | Source hashes, recorded options, bindings and frozen provenance identities |
| `tools/original_target/`, `tests/` | Active authored build/acceptance tools and synthetic tests |
| `docs/` | Active process, generated status, handoff; `docs/history/` batch records |
| `historical/native-reconstruction/` | Preserved native source, CMake, scripts, tests, tools and docs |
| Ignored `private/`, `build/` | Legitimate game/compiler inputs, byte scaffolding, experiments and outputs |

Navigate by [supported source purpose](docs/RECOVERED_SOURCE_INDEX.md).
Read [status](docs/STATUS.md), [handoff](docs/HANDOFF.md) and
[build setup](docs/ORIGINAL_TARGET_BUILD.md). Configure private inputs in
`private/original-target.local.json` and select a Python with the dependencies in
`requirements-research.txt` through `RA2_PYTHON`. Then:

```sh
./test.command
./run.command       # verify input/source hashes; does not launch the game
./build.command     # fresh compile, strict extent checks, assemble/link/package
```

The fresh build consumes tracked root sources, using their recorded VC6 options
under local Wine (plain Wine 11.18 by default, CrossOver supported). It executes no ignored authored scripts
and reruns no candidate-search matrix. Private input paths are configurable;
clang selection honors `DEVELOPER_DIR` through `xcrun`, or an explicit assembler.
No download or installer is part of the build.

Complete packaged reference size: **4,485,392 bytes**, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Raw linker output differs. Packaging retains original headers, file padding and
overlay after checking every logical payload and the complete zero virtual tail.
Exact output still relies on substantial original-byte scaffolding.

The recovery goal is active and incomplete. Native adaptation
and Yuri's Revenge remain later work. See [provenance](THIRD_PARTY.md); this local
migration grants no rights to proprietary material and publishes nothing.

Day-to-day recovery uses the iteration tools in
[build setup](docs/ORIGINAL_TARGET_BUILD.md#iteration-tools): Ghidra seeding,
scored instruction diffs, bulk seed sweeps and a vtable class inventory. The
loop and the completion criteria are in
[the process](docs/ORIGINAL_TARGET_PROCESS.md); earlier batch records are in
[docs/history/](docs/history/).
