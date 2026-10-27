# Base RA2 MIX primitives and bootstrap verification

October 14, 2026. Ivalice / Apple Silicon macOS. Baseline: `2b05ab8`.

**5,344 fresh original/native results pass independently on each engine**, with
both native ASan/UBSan replays. This checkpoint replaces unsigned-map MIX lookup
with the original signed midpoint search and retains duplicate index records.
It establishes bounded plaintext parsing, bootstrap requests and optional-output
lookup contracts. It does **not** establish complete startup archive order or
promote patched assets/prepared data/runtime gates. The complete-game goal remains
incomplete.

## Identity and references

| Engine | SHA-256 |
| --- | --- |
| Allied disc, embedded 1.08 | `135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743` |
| Supplied RA2 1.006 patch output, embedded 1.08 | `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f` |

The patched engine equals the approved private Windows transfer. Supplied patch
lineage, user-reported no-CD modifications and publisher authenticity remain
separate claims. No Windows action or original-game observation occurred here.
The native app still reads only hash-checked executable track data; archive
research executes unchanged instructions solely in private Unicorn tests.

Consulted [REFERENCES.md](REFERENCES.md) and pinned YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88`: `MixFileClass.h`, `CCFileClass.h`
and `FileSystem.h`. List, file and bootstrap declarations supplied names/layout
hypotheses, independently checked on both base engines. YR behavior/addresses were
not adopted. This checkout lacks an incorporation license; no header code was
copied. Pinned recomp/pcrecomp remain tooling/reference leads; local recomp
`docs/RECON.md` is absent. No generated or upstream game code was incorporated.
Existing OpenRA MIX format attribution in [THIRD_PARTY.md](../THIRD_PARTY.md) is
retained; encryption remains the existing format adaptation.

## Independently inspected mappings

`tools/verify_archive_mapping.py` checks **11 complete ranges / 935 instructions**,
explicit changed operands, relative branches, CRC table, bootstrap filename
strings and actual constructor dependency-vtable slots.

| Boundary | Disc VA | Supplied 1.006 VA |
| --- | --- | --- |
| Complete base bootstrap | `5150E0` | `515C90` |
| Complete MIX constructor | `591FA0` | `5952F0` |
| List initializer / signed comparator | `591E40` / `591F80` | `595190` / `5952D0` |
| Complete MIX Offset / unlink | `592750` / `592870` | `595AA0` / `595BC0` |
| CRC/padding / block helper | `493C50` / `493E20` | `493FC0` / `494190` |
| CCFile Exists / Open | `468DC0` / `468E40` | `4691A0` / `469220` |
| ASCII CRT uppercase | `781764` | `7961E4` |

Receipt: `private/patch-inspection/archive-1006-mapping-v3.json`. Earlier receipts
preserve earlier tool identities. Later startup, language and theater candidates
under `private/patch-inspection/` remain leads, not accepted mappings.

## Recovered boundary

- MIX constructors append successful archives before the list tail; lookup visits
  earliest registered archives first. Signed int32 IDs determine midpoint binary
  search. Equal IDs return the original midpoint record, retaining index order.
- Successful plaintext old/new headers store sign-extended int16 counts, body size,
  flags and file origin. Native safety guards refuse negative counts, unsorted
  signed indexes and out-of-body entries; they do not reproduce original
  malformed-file allocation/failure behavior.
- Null/missing filenames leave optional outputs unchanged. Successful Offset writes
  archive, length, cached output zero, relative offset, then cached pointer or
  file-backed absolute offset. Cached-pointer addition wraps at uint32. File origin
  is added only if the offset output exists.
- Bootstrap checks `expand99.mix` down through `expand00.mix`, then requests
  `ra2.mix`, `cache.mix`, `local.mix`. `baseMixBootstrapNames` is tested by the vector
  runner; AssetStore does not yet use it.
- Separate original-only Open assertions establish close-first and loose-first
  read decisions; write bit 2 goes directly to raw open. Exists tests an existing
  handle first, archive membership next, raw existence last. Exists order must not
  be used as Open precedence.

Production changes are in `src/assets/Archive.cpp/.hpp`. Optional-output contract
and bootstrap tests in `tests/archive_vectors.cpp` do not establish a native
file/cache/OS lifecycle implementation.

## Executed evidence and audit scope

| Group | Results per engine |
| --- | ---: |
| ASCII filename CRC/padding | 512 |
| Plaintext old/new/checksum-flag metadata and records | 96 |
| Complete bootstrap request order | 128 |
| Lookup across archives, duplicates, signed extremes, all output masks | 4,096 |
| Null / missing filenames | 256 / 256 |
| **Total native/original results** | **5,344** |

There are **84 additional original-only assertions** per engine: constructor open/
allocation failures, negative counts with allocator refusal, and Open/Exists
service decisions. They are not counted as native differential parity.

Each profile records **10,139 callable roots / 403,943 audited guest writes**.
Calls check return/EIP/ESP, callee-saved registers, caller stack, permitted guest
stores and immutable fixture inputs. Lookup compares ordered optional-output
writes. Constructor guards check node/heap edges. Supplied stream/heap/file/service
`mem_write` calls have separate explicit bounds and are not captured by guest-write
hooks. Do not claim full ordered constructor writes, native arena parity, original
heap/file ownership, SHA authentication, encrypted-parser parity or locale branches.

Fresh fixtures/expectations/receipts stay in
`private/migration/{allied-disc,supplied-ra2-1006}/archive/`; replay checks source,
engine, fixture and expectation identities and refuses replacing fresh evidence.
All outputs and separate observations equal across engines. Five synthetic evidence
guards, eight new native assertions, build, sanitizer synthetic/owned checks,
owned load/render checks and both 170-frame window-server SDL regressions pass.
These integration checks do not prove original full-frame fidelity.

The first disc attempt failed because a translated full-constructor block crossed
an isolated insertion stop. Flushing that translated range fixes the harness without
changing original bytes. The rejected directory
`private/migration/allied-disc/archive-rejected-stop-boundary/` has no accepted
receipt. Fresh corrected runs generated the evidence above.

## Reproduce and continue

Current reader-source identities use the fresh sibling receipts described in
[EFFECTIVE_ASSETS_1006.md](EFFECTIVE_ASSETS_1006.md); older receipts remain historical.

```sh
./build.command
./test.command --data-dir "$PWD/private/game"
build/tools-env/bin/python tests/test_archive_profiles.py
build/tools-env/bin/python tools/verify_archive_mapping.py \
  --disc private/disc-allied/game.exe --patched private/official-1006-probe/game.exe
# Fresh original execution: authorized Mac Unicorn JIT context, new private directory.
build/tools-env/bin/python tests/compare_archive.py \
  --exe private/official-1006-probe/game.exe --output-dir private/archive-fresh-1006
# Native sanitizer replay after README's sanitizer build; use a fresh report path.
build/tools-env/bin/python tests/compare_archive.py \
  --exe private/official-1006-probe/game.exe --native build/sanitize/archive-vectors \
  --expectations private/migration/supplied-ra2-1006/archive-registration-refresh/expected.json \
  --report private/archive-sanitizer-replay.json
```

Next: verify sequencing of language, bootstrap, later startup and first temperate
theater archives, including nested requests and effective patched assets. Preserve
the fixed AssetStore registration adapter until that evidence is accepted. Then
coordinate preparation/runtime promotion and applicable original/native/SDL
regressions. No source installation, disc, Outpost 2 or system tools changed.
