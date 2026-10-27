# Original message font measurement and fitting

The first objective's message insertion calls431690 for prefix width and431710
to fit text before allocating/storing a line. The complete multiline measurement
4314B0, width wrapper431690 and prefix fitter431710 now have readable SDL-free
implementations in `MessageFontMetrics.hpp`. These are dependencies for original
objective text layout, not a displayed message or completed tutorial capability.
No host font/layout engine replaces their behavior.

## Recovered behavior

Traversal uses UTF-16 code units, including unpaired surrogate andFFFF units;
it stops at the first NUL. Absent text differs from an empty terminated string.
The saved primary font supplies word indices, wrapped dword glyph addresses and
unsigned first-byte widths. A zero index or computed zero glyph pointer uses the
live fallback; an absent fallback contributes no glyph advance. The native view
borrows those records and resolves glyph bytes by their logical dword address.
It does not load a font or map guest memory in the application.

Dimensions and spacing retain signed dword wrapping. Tab advance adds the tab
interval then subtracts the signed remainder, preserving negative intervals and
positions. Zero divisor and the original signed-division overflow explicitly
refuse only when entered. Measurement has a supplied host traversal bound of
1,048,576 visits; exhaustion refuses rather than changing wrapping policy.

Measurement treats9 as tab,10/13 as line breaks and32 as a saved word boundary.
A break following CR does not add another line. Tab/missing-glyph branches do not
update maximum width. Word wrapping preserves the saved maximum and rewind
position, including boundaries retained across explicit line breaks. First-glyph
overflow can add a line; it is not repaired to a more familiar layout policy.
The saved line height, glyph-count reset and exact late traversal are retained.

Successful measurement stores optional width then height. Absent-primary/text
returns false and stores height then width. Output aliasing and omitted pointers
are retained. Width wrapper431690 uses its second argument as both limit input
and width-output storage. Prefix fitting increments consumed units even for
missing glyphs and line breaks, checks signed width overflow before max-character/
line-break stops, and retreats to prior whitespace only when requested. An
overwide first character can return zero; no forced progress is invented.

## Original evidence

Exact supplied base:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Exact fingerprints, instructions and the
measurement control-character dispatch tables are checked before execution.

Canonical `private/boot-camp-20261018/message-font-fresh-a1/expected.json`, SHA256
`768b874820b9ea8fa989355a58f84b05cd4fa28ae84aa93c66b483687f458067`.
All6,177 fresh sequences match native results and ordered index/glyph/fallback/
output traces. The guest enters measurement1,814 times, width wrapper907 times
and prefix fitter4,363 times; wrapper calls execute actual measurement. There
are no replaced children, patched instructions or supplied width/fit answers.

Fixtures cover null/empty text and font, all optional-output patterns and alias,
tabs/CR/LF/CRLF/CRCR, spaces/missing/zero-width glyphs, negative spacing and limits,
max-character and non-byte word-wrap flags, UTF-16 units, embedded NUL, signed
dimension overflow, zero stride and computed-zero glyph pointers. Initial font
objects, indices, widths, fallback and text backing are supplied fixtures. This
does not verify a loader, stock glyph metrics, a message-list owner or drawing.

Original checks guard caller stack/return/callee-saved registers, code/dispatch
tables and the whole arena except the selected output words. All other writes
refuse. Normal/sanitizer/uncached-inspection replays each retain6,177 original
hits and zero misses; no original execution or native result is cached. Replay
receipt/input/oracle/environment guards retain separate native runner identities.

Both full builds,119 normal/118 sanitizer CTests and1,367 Python tests pass.
Native fault/NUL guards and Python provenance/scope corruption guards pass.
Application and both private owner-check binary hashes are identical to the
prior `37d7bb9` checkpoint receipts. Their existing106-tick SDL/owner evidence
remains at its original scope; those unchanged checks were not rerun. No font
algorithm is scheduled by the application yet. Local verification is not
independent acceptance or original UI/frame fidelity.

Fresh original generation took1.835s; native comparison0.102s (2.266s driver
elapsed). Normal/sanitizer/uncached replays took0.316/1.034/0.397s; their batch
took2.251s. Full builds10.33/14.67s, CTest1.23/9.37s (`test.command` total2.21s),
Python29.532s. Repair/manual-review/approval costs were not separately measured.
An initial target-only build ran before CMake knew the new target and failed;
the normal entry point configured and built it successfully. No caching was added.

Private evidence: `private/boot-camp-20261018/message-font-*`, including the fresh
expectations, three comparison audits/reports, build/check logs, command manifest
and `message-font-receipt-a1.json` with local source/runner/evidence identities.

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
./test.command
DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/sanitize --parallel 6

env PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/message-font-next.audit.json \
  tests/compare_message_font.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/message-font-vectors \
  --expectations private/boot-camp-20261018/message-font-fresh-a1/expected.json \
  --report private/message-font-next.json

./run.command --boot-camp-walk
```

Use fresh report/audit destinations. Replace expectations/report with
`--output private/NEW-DIRECTORY` for fresh original execution; use the sanitizer
runner or add `--uncached` for the respective replay controls. Exact commands are
in `message-font-replay-commands-a1.json`. Unicorn remains research/test-only.

## Next integration

The user-supplied `GAME.FNT` resolves from nested data in `ra2.mix`,1,584,195 bytes,
SHA256 `ec8d6d85db3eedf5a862cc6ffb87bfad4c77279dd946bc2d30879ad9140c8d3f`.
Archive receipt and private font-name/xref candidates are recorded. Candidate
loader sites4322A7/432C9E reference that name and store the selected font at84E9E8;
this is inspected navigation evidence, not loader recovery or startup execution.
The first linear xref scan stopped on embedded data; the second uses skip-data
and retains candidate status. An unrelated broad private-file search was stopped;
it supplies no evidence. No original font content is tracked in Git.

Next recover the actual font file/owner association and message insertion's text
buffers, list/heap effects, recursive continuation, lifetime and sound child.
Then join these metrics to the actual caller and drawing consumer. Live sight/
arrival and remaining mission effects still gate Objective1. Both full games
remain incomplete; goal active. No workers, Windows actions, downloads, new
runtime executable reads, dependencies or system/Xcode/DRM changes were used.
No public/YR/recomp/CRT code was incorporated.
