# Mission text through owned insertion and pixels

The actual base action11 path now has a differentially verified join through
color, found-label localization, insertion, expiry and ordinary message drawing.
`MissionMessagePresentation.hpp` adapts the existing UTF-8 `MissionTextRequest`
onto the stable `OwnedMessagePresentation`; it uses the same recovered insertion/
list/node/text/glyph kernels. Boot Camp has not adopted this adapter yet, so its
application path still records requests only. No visible SDL claim follows.

## Arguments, strings and supplied boundaries

Action11's actual seven insertion arguments map to null prefix, identifier0,
localized UTF-16 body, signed color, flags4046, raw duration dword and silent0.
The adapter preserves the duration bit pattern when passing signed lifetime;
it does not clamp negative/wrapped values. It refuses a nonzero prefix token,
identifier or trailing token in the ordinary action11 profile. UTF-8 decoding is
an authored host association for `PreparedStringLookup`, not recovered CSF loading.
It preserves scalar values, surrogate pairs and embedded NUL without normalization
and refuses truncated/overlong/invalid/surrogate UTF-8 before insertion. The
recovered text algorithms retain their original first-NUL behavior.

The proof uses actual `6ADAE0` action11 dispatch, `6715D0` signed-byte color,
`6F9EC0` found-label lookup, `782025` CRT search, `781F20` locale-zero comparison,
`77F110` x87 conversion and actual `5B4DA0`. Its receiver is the original fixed
global list `A3DC70`, not a substituted display callback. Actual constructors
install7ADCCC, then expiry and ordinary list/node/text/glyph routines consume the
same records. Original instructions and immutable tables are never modified.
Fixture label/slot registries and UTF-16 payloads, color tables, rules/scenario/
clock/style/font/surface initialization remain supplied. Named heap/time/audio/
surface/IME/fill/line leaves retain prior scope. Fill requests are traced no-ops;
text pixels are real, background rasterization is not proved. There is no focus/
editor/cursor branch in this ordinary action profile.

## Exact evidence

Exact supplied executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Composed verifiers fingerprint the target
and inspect all entered ranges/tables before execution. Private GAME.FNT remains
SHA256 `ec8d6d85db3eedf5a862cc6ffb87bfad4c77279dd946bc2d30879ad9140c8d3f`,
checked before/after fresh execution and every expectation replay.

Canonical expectations:
`private/boot-camp-20261018/mission-message-fresh-a1/expected.json`, SHA256
`8b545d4edbe24e46533e49690468ae4f35035b0ac8b90183463baa7d3872b883`.
All123 shared sequences match snapshots after every action. Actual guest counts:
270 action11/color calls,267 found-label lookups,458 insertions including recursive
wrapping,186 expiry updates,375 ordinary list draws,315 entered chain traversals,
749 node/message-consumer calls and2,118 glyph calls. Empty keys still execute
color while bypassing duration/localization/insertion. Cases cover signed color
results, duplicate/case-varied labels and slot indexes, UTF-16 control/Unicode/
embedded-NUL payloads, wrapping/capacity removal, mode3/4 typewriter controls,
signed/wrapped lifetime and clock boundaries, expiry and later insertion/drawing.

The native fixture invokes the production composition owner, actual color/search/
action kernels and adapter. Each action compares return, all availability words
and text slots, complete live-node fields/padding/logical links, focus identities,
list/mode/clock, mutable font/pixel state and ordered accumulated sound/fill request
values. Addresses become live-chain ordinals. Freed raw allocations/heap identities,
unentered IME/editor fields and full lower read/write traces are not projections
of this proof; their earlier bounded proofs retain separate scopes. This is not
raw heap/store/fault/alias parity or original startup. Original stack/return/
callee-saved state, code/tables/IAT, global list and all four private arenas are
guarded against unexpected writes. Supplied action inputs are prepared before
per-call guards; no original write is hidden by that preparation.

The shared original fixture now has explicit list receiver and guarded extension
hooks for this caller. Consequently the old242-sequence proof was freshly
regenerated at `private/boot-camp-20261018/message-pipeline-refresh-a2/expected.json`,
SHA256 `8c9d763305fbb5a6f5263264c413b601af78f80d3d6e2b189ea7ee864a8fde6e`.
Every command/projected output equals the earlier fresh-a1 result; identities and
receipts remain separate. The earlier receipt was not relabeled or bypassed.
Both new123 and refreshed242 sets pass normal/sanitizer/uncached replays with
zero misses. No closed finalizer was rerun.

Both builds,128 normal/127 sanitizer CTests and1,407 Python tests pass. Application
and20 prior runners remain hash-identical to the ownership receipt, retaining
closed evidence/SDL scope. Fresh new original generation32.779s, native0.033s,
driver33.354s; refreshed prior original26.438s, native0.061s, driver27.246s. All
commands, identities, counts and build/replay/check costs are private in
`mission-message-receipt-a1.json` and `mission-message-replay-commands-a1.json`.
Repair/review/approval costs were not separately measured; no proof repair was
needed. Local verification is not independent acceptance. No runtime executable
read, cache, dependency, public/YR/copied CRT/lifted code or proprietary tracked
content was added. Originals remain read-only; no Windows or system/DRM changes.

## Commands and next integration

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
./test.command
DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
env PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  -m unittest discover -s tests -p 'test_*.py'

env PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/mission-message-next.audit.json tests/compare_mission_message.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/mission-message-vectors \
  --font-file private/boot-camp-20261018/game-font-research-a1.bin \
  --expectations private/boot-camp-20261018/mission-message-fresh-a1/expected.json \
  --report private/mission-message-next.json

./run.command --boot-camp-walk
```

Use new private audit/report paths. Substitute sanitizer or insert `--uncached`
before the driver for controls. Fresh original execution uses `--output` with a
new private directory instead of expectation/report, and needs research JIT
permission. To replay the refreshed old family, use `compare_message_pipeline.py`,
`message-pipeline-vectors` and the refresh-a2 expectation path above.

Next adopt the owner and adapter in Boot Camp mission state and its full warm
world/renderer previews, preserving source isolation and source-destruction
continuation. Then recover required fill/line raster children or explicitly bound
their adapter scope and verify ordinary SDL visible objective text. Live sight/
arrival and remaining mission effects still gate Objective1. Both games remain
incomplete; the goal stays active. No workers, Windows actions/transfers or downloads.
