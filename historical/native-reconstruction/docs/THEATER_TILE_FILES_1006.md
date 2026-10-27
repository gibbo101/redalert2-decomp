# Supplied RA2 1.006 loaded theater tile associations

October 15, 2026, after `19d8b1c`. This extends the absent-image projection in
[THEATER_TILE_INPUTS_1006.md](THEATER_TILE_INPUTS_1006.md) with nonlazy loaded
file/type/alternate bindings and actual [TMP preparation](TILE_IMAGE_1006.md).
It is an unwired prerequisite of the same map-depth crossing/cliff capability.

## Identity and references

Executed engine: `private/official-1006-probe/game.exe`, 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Every run verifies that identity. Embedded 1.08, supplied 1.006 lineage and
reported no-CD changes remain distinct provenance; pristine authenticity is
unverified. The approved private Windows copy matched at the earlier checkpoint.
There was no new Windows action/transfer. The native runtime never executes this
engine or depends on mounted media, SafeDisc or a Windows launcher.

Consulted [REFERENCES.md](REFERENCES.md), pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` `docs/voxels.md`/LICENSE and YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` `IsometricTileTypeClass.h` and
`MapClass.h`. Hypothesis: complete theater loading associates filename requests,
loaded TMP pointers and alternate type chains before Cell preparation. Recomp
supplies no verified base theater algorithm; YR names/filename warning are leads.
Exact base instructions/execution establish the behavior. No reference/header/
generated/lifted code was incorporated; no new THIRD_PARTY entry.

## Executed boundary and preserved behavior

`assets/TheaterTileFiles.*` calls the retained selected type/set preparation and
TMP helper. File-cache responses and decoded INI values are caller-supplied.
Portable vector indices replace original type links; image references remain
file-relative. The original execution nests **six complete ranges / 2,168
instructions**: complete theater loader `0x529870`, actual type constructor
`0x528EE0`, color builder `0x52E3D0`, interpolation `0x63CC80`, scaling
`0x63CDF0` and FTOL `0x77F110`. The combined verifier also pins five inherited
lazy/consumer ranges (eleven ranges / 2,323 instructions total); those five have
zero entries in this nonlazy fixture and are not additional executed proof.

Original INI results, base type construction, file-cache/raw image return, successful
heap, sufficient vector storage/clear, graphics and timers remain supplied services.
No original instruction is patched. The new allocation/file-return/filename/vector
service boundaries check their relevant sites/arguments; inherited broader services
retain the earlier projection's scope. This is not execution of original archive,
INI parsing, file-cache implementation or full type/resource lifetime.

Preserve these associations:

- File stems concatenate the supplied prefix, a minimum-two-digit 1-based tile
  number, then no suffix for primary or `a`, `b`, ... for successive alternates.
  Stock prefixes include hyphens (`W-a-`); native ASCII prefix length <=16 and
  character refusals are safety boundaries, not original parser parity.
- Theater 0/1/2 first requests `.TEM`/`.SNO`/`.URB`. If absent and the supplied
  **NonMarbleMadness value is nonzero**, request `.MMT`/`.MMS`/`.MMU`. This includes
  its default 65535. Do not substitute a generic `.TMP` fallback.
- A primary type exists even when its image is absent. Stop at the first missing
  alternate; do not skip gaps. Primary and alternates share the primary index and
  set base; all-type registration includes alternates in creation order.
- Next links follow contiguous alternates. Variant counts descend along that
  chain: primary N, first alternate N-1, ... last 1. The bounded native profile
  refuses chains beyond base plus `a`..`z`; original signed-byte overflow is outside
  the tested domain. This count does not select a Cell variant.
- The original final MarbleMadness/NonMarbleMadness set-to-tile remap visits
  **primary types only**. Alternates retain supplied raw values. Selected flags/
  defaults remain those in the preceding theater-input note.
- Cached images bind with ownership byte zero and no lazy filename. Type dimensions
  come from header low bytes; reference relocation uses the full signed dimension
  product and adjusts nonzero unsigned references only below the image base.
  Repeated binding leaves already-relocated references intact. The native supported
  relative-reference/dimensions domain is the earlier TMP helper's domain.
- Actual color preparation runs after each successful binding, preserving every
  13-pair ramp and prior numeric rules. Full heap/vector ownership is not reproduced.

## Verification and commands

**135 fresh original/native results**, normal and ASan/UBSan replays:
128 deterministic synthetic scenarios across three theater extension pairs;
three loaded supplied clear/cliff/slope scenarios; three repeated-cache binding
scenarios; and the full supplied temperate INI projection with its 838 primary
types, three supplied images loaded and all other file responses deliberately
absent. Temperate bytes served under synthetic snow/urban names are fixture
responses, not evidence for genuine snow/urban assets or runtime support.

Compare ordered filename requests, primary/all-type membership, normalized next
links, remaining counts, selected type/header fields, relocated references and
every color word. Actual counts: 135 theater entries, 1,557 type constructors,
609 color builders, 28,990 interpolation, 2,230 scale and 93,660 FTOL entries;
1,215,754 guest stores and 38,647 supplied service calls. Caller return/ESP/stack/
registers, immutable headers/globals, allocation bounds, unmodeled type bytes,
image bytes after normalization and vector/registry capacity tails are guarded.
Full selected-field write order or all memory read order is not claimed.

Receipts: `private/map-depth-1006/theater-files-v1/{expected,report}.json`,
`native-replay.json`, `sanitize-replay.json`. Executable/source/inspection/INI/TMP
identities are checked before and after runs. Failed setup attempts produced no
accepted receipt; their corrections/timings are retained privately.

```sh
./build.command
build/tools-env/bin/ctest --test-dir build/native --output-on-failure
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'

# Fresh original execution requires the authorized Mac host JIT context.
# Choose an unused private output directory.
build/tools-env/bin/python tests/compare_theater_tile_files.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/theater-files-new

# Replay does not execute original instructions.
build/tools-env/bin/python tests/compare_theater_tile_files.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/theater-files-v1/expected.json \
  --report private/map-depth-1006/theater-files-v1/replay-new.json
# Add --native build/sanitize/theater-tile-file-vectors for sanitizer replay.
```

Cell usage/variant selection (`0x52B2E0`, `0x4767A0`), including its first-use RNG
table, remains separate. Broader map initialization `0x54B2E0/0x54FDA0/0x54EBD0`,
directions/speeds, contact/construction and unsupported branch guards still precede
runtime prepared Cell to Foot/world integration and actual SDL level crossing /
parked cliff `(51,72)`, elevation 4. No runtime source changed; neutral fields
remain and no new SDL playtest is claimed. Complete original file/INI/archive
association, lazy/animated paths, ownership/lifetime and whole-frame parity are open.
Only Apple Silicon macOS is tested. Locally verified is not independent acceptance
or a completed map-depth delivery. Full base RA2 then YR remains active/incomplete.
