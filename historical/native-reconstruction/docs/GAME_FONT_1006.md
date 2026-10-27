# Original stock font ownership

`GameFont` owns immutable user-supplied ordinary `fonT` records and binds the
already recovered SDL-free message metrics to them. Successful base431040 ->
431150 ->431EC0 and subsequent4314B0/431690/431710 consumers match52 fresh
original sequences. This is an unwired dependency for objective text; message
insertion, glyph drawing and live objective scheduling remain incomplete.

## Input and recovered scope

Exact supplied base executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. The verifier checks original instruction
ranges, metric dispatch tables and the USER32/SetRect import association.

User-supplied `GAME.FNT` is nested in `private/official-1006-probe/ra2.mix`,
offset120161760,1,584,195 bytes, SHA256
`ec8d6d85db3eedf5a862cc6ffb87bfad4c77279dd946bc2d30879ad9140c8d3f`.
The private research copy is `private/boot-camp-20261018/game-font-research-a1.bin`;
archive resolution is recorded in `message-font-archive-a1.log`. No font payload,
extracted table or executable is tracked. The comparison driver checks font
identity before and after fresh execution and every replay; it does not rely on
`run_evidence.py` recognizing the additional `--font-file` input.

Ordinary `fonT` handling reads a28-byte header then65,536 little-endian word
indices. It retains all six header fields, the separate count of nonzero indices,
and the declared glyph-count times stride dword product. Glyph allocation/read
size uses the declared count, not the nonzero-index count or maximum index.
Each nonzero word selects glyph `(index-1)*stride`; the first byte is its width.
Trailing file bytes are ignored. The constructor supplies tab interval64 and
spacing1 and takes line height from the loaded definition.

Fallback creation allocates columns*rows+2 bytes, copies the indexed `X` width,
and inverts its columns*rows following bytes. The last allocation byte remains
untouched. When `X` is absent, the entire allocation remains untouched. Explicit
supplied allocator fill is retained rather than replaced with zero. The immutable
owner is noncopyable/nonmovable so its metric callbacks keep stable associations;
callers should move an owning pointer if needed.

The owner accepts bounded, valid ordinary files. It refuses the alternate `FoNt`
range format, truncation, indices outside owned glyph storage, allocations above
64MiB and wrapped fallback dimensions. These are host bounds/refusals, not claims
that the original loader validates malformed files the same way. File/heap APIs,
SetRect, allocation success and untouched heap fill remain supplied. Failed file/
allocation branches, destruction and original global font selection/startup are
not reconstructed or proved. The native owner does not reproduce a raw guest
constructor object layout. It adds no runtime executable read or original-code
execution to the application.

## Evidence and checks

Canonical `private/boot-camp-20261018/game-font-fresh-a1/expected.json`, SHA256
`9469f5c21b91ba57633b44c8f523cd10f8db38a557383072665b5cbcb8704596`.
Four stock-font cases vary supplied heap fill. Forty-eight synthetic cases cover
zero/nonzero row and column dimensions, zero/multiple declared glyphs, absent/
present `X`, repeated indices and nonzero counts differing from declared counts.
Each case compares all six fields, nonzero count, complete index/glyph/fallback
hashes and four UTF-16 strings through actual measurement, fitting and wrapper
roots. Prior metric evidence retains its broader control-character/alias scope.

The guest executes52 constructors,52 loaders,52 fallback roots,416 measurement,
208 fitting and208 width-wrapper roots. Only named file/heap/SetRect leaves are
supplied; no loader/fallback/metric instruction or answer is replaced. Caller
stack, return, callee-saved registers, code/tables/IAT, vtable/name and unowned
arena storage are guarded. Allocated logical records and resulting metric values
are compared; this does not claim full raw constructor store-order parity.

Normal/sanitizer/uncached-inspection replays each retain52 hits/zero misses.
Both current metric runners retain all6,177 older sequences with zero misses.
Both builds,120 normal/119 sanitizer CTests and1,371 Python tests pass. Native
malformed/truncated-input and fallback-tail guards and Python identity/scope/
receipt guards pass. The application and both owner-check binaries remain
hash-identical to the7e01e4b checkpoint receipt; prior SDL evidence retains its
scope and was not rerun. There is no new application behavior. Local verification
is not independent acceptance or original UI/frame fidelity.

Original generation64.704s; native comparison0.035s, driver65.249s. Three new
replays and two older metric replays together took3.14s. Normal/sanitizer builds
19.36/32.23s, CTest1.25/7.26s (`test.command` total1.92s), Python30.008s test time/
45.55s shell elapsed. An earlier native build took14.72s before rebuilding the
final vector output. Repair/manual-review/approval overhead was not separately
measured. No caching mechanism was added; existing identity-checked original
expectations and immutable inspections were reused.

Private evidence/commands/logs and local source/runner receipt:
`private/boot-camp-20261018/game-font-*`. Disassembly is under `font-owner-*` and
`font-load-*`. No public/YR/recomp or copied CRT source/new dependency was used.

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
./test.command
DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/sanitize --parallel 6

env PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/game-font-next.audit.json \
  tests/compare_game_font.py \
  --exe private/official-1006-probe/game.exe \
  --font-file private/boot-camp-20261018/game-font-research-a1.bin \
  --native build/native/game-font-vectors \
  --expectations private/boot-camp-20261018/game-font-fresh-a1/expected.json \
  --report private/game-font-next.json

./run.command --boot-camp-walk
```

Use fresh report/audit paths. Replace expectations/report with
`--output private/NEW-DIRECTORY` for fresh original execution; use the sanitizer
runner or `--uncached` for respective replay controls. Exact completed replay
commands are in `game-font-replay-commands-a1.json`. Unicorn is research/test-only.

## Next integration

Recover complete message insertion5B4DA0 with its buffers/list/heap ownership,
recursive continuation, lifetime and sound child, then join actual metric callers
and glyph drawing using the stable font owner. The existing runtime continues to
record objective requests only. Live sight/arrival and remaining mission effects
still gate Boot Camp Objective1; neither game is complete. Goal active. No workers,
Windows actions/transfers, downloads or system/Xcode/DRM changes were used.
