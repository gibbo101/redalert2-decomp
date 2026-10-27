# Bounded initial registration and effective supplied prototype inputs

Current runtime/preparation status: [PROMOTION_1006.md](PROMOTION_1006.md). The
bounded prototype now selects the supplied 1.006 dataset by default, with distinct
source-matched prepared files. Historical checkpoint gates/commands below preserve
their original evidence scope and do not describe the current runtime gate.

October 14, 2026. Ivalice / Apple Silicon macOS. Baseline: `5c6e3c2`.

The opt-in initial-temperate reader registers supplied archives in the recovered
request order and records physical provenance. **317 source queries pass per engine
on decoded-index original fixtures**, with both native sanitizer replays. Only
`game.exe` and `rules.ini` differ among these selected disc/patched inputs. This
does not establish original encrypted parsing, complete startup/file/cache lifetime
or whole-game parity. Preparation/runtime gates remain disc-only; the application
still defaults to its legacy registration during coordinated promotion.

## Identity and implementation boundary

| Engine | SHA-256 |
| --- | --- |
| Allied disc, embedded 1.08 | `135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743` |
| Supplied RA2 1.006 patch output, embedded 1.08 | `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f` |

The patched identity still matches the approved Windows transfer. Supplied patch
lineage and user-reported no-CD modifications remain separate from authenticity.
No Windows action or original-game observation occurred. Reference use follows
[ARCHIVES_1006.md](ARCHIVES_1006.md), [ARCHIVE_SEQUENCE_1006.md](ARCHIVE_SEQUENCE_1006.md)
and [REFERENCES.md](REFERENCES.md); no new upstream/header/generated code was reused.

`AssetStore::Registration::InitialTemperate` is an explicit research/preparation
mode in `src/assets/Archive.cpp/.hpp`. It requests language, descending available
expansions, RA2/cache/local, later-startup archives and first-temperate archives.
Loose files override archive reads. Nested requests resolve through already
registered archives; successful native registrations append. Source metadata records
the containing physical file, nested archive start and physical body start.
Returned slices retain their physical offset in the shared read-only file buffer.

Host boundaries: ASCII case folding, immutable native vectors/storage, sorted root
map/movie enumeration, initial temperate-only registration and omission of absent
movie data. Missing required conquer/cameo/maps/multi families are refused. Other
theaters, later reloads, failure/growth, original file/cache ownership and original
OS enumeration are outside this reader. No media/authentication/launcher checks
enter the native app. Both exact images' initial previous-theater value is inspected
as -1 through the explicit `7C396C` / `7D88DC` data mapping.

For both supplied datasets, the reader registers 13 archives:

```text
language, ra2, cache, local, conquer, cameo, maps01, multi,
generic, temperat, tem, isotemp, isogen
```

Cameo comes from LANGUAGE.MIX. Cache/local/conquer and the five theater archives
come from RA2.MIX. Maps01/multi are top-level supplied files. All 316 selected
archive members resolve to their recorded physical file slice; game.exe is loose.
No new extracted asset copy is required for the reader.

## What the original fixtures verify

`tests/compare_archive_effective.py` pins every root source file before collecting
the registry and verifies the same files after comparisons. The native inspector
supplies decoded MIX indexes; original list insertion and Offset execute unchanged
on those fixture indexes. Native source ordinal, physical offset and length must
match original lookup. Each chosen slice's SHA-256 independently matches bytes read
directly from the pinned physical source file. Original loose Open decisions execute
with explicit raw/file services. Complete original stage routines also record
requests; their retained request sequence must equal native registered names.

This is **decoded-index original-fixture evidence**. It is not original encrypted-
header/decryption/SHA authentication parity or a full original nested-file open.
Constructor/cache/directory/format/allocator/palette/display services remain supplied.
Native-decoded indexes and available nested names are fixture inputs, not independent
original parser outputs. Keep that distinction when assessing fidelity or promotion.

Each engine has 317 queries: the chosen map, rules/art/voxel/palette/theater inputs,
all selected unique TMP filenames and all supported TREE01..28/23 prop images.
There are 316 archive queries and one loose query. Lookup/file fixtures execute
319 audited roots / 19,821 audited guest writes; stage fixtures execute four roots /
3,174 writes. Inherited caller/register/stack/input/write audits apply, with a
separate bounded index arena large enough for ISOTEMP's 1,035 records.

Private receipts:

```text
private/patch-inspection/effective-disc-prototype.json
private/patch-inspection/effective-1006-prototype.json
private/patch-inspection/effective-disc-prototype-sanitize.json
private/patch-inspection/effective-1006-prototype-sanitize.json
```

The two sanitizer replays pin engine, complete reader/oracle/source closure, all
source-file hashes and the original receipt fingerprint. They execute no originals.
The 315 unchanged input hashes and the separate original rules-difference analysis
support bounded data migration; they do not expand the gameplay claim.

Because Archive.cpp/.hpp changed, both archive families were freshly rerun on both
engines: 5,344 primitive results plus 688 stage results per engine, their separate
84 original-only assertions and all four sanitizer replays. New receipts are in
`private/migration/{allied-disc,supplied-ra2-1006}/archive-registration-refresh/`
and `archive-sequence-registration-refresh/`. Historical receipts are preserved;
their older source identities must not be relabeled as current.

Four authored nested/expansion/language/loose/provenance tests and two replay guards
pass. Case-variant ambiguity is exercised only on filesystems that can create distinct
case variants; Ivalice's case-insensitive APFS aliases them. Native/sanitizer synthetic
and owned integration and both actual 170-frame SDL regressions pass. These SDL
checks still use the retained disc/runtime policy, not promoted patched gameplay.

## Commands and next work

```sh
./build.command
./test.command --data-dir "$PWD/private/game"
build/native/archive-inspect private/official-1006-probe --prototype-inputs mp03t4.map \
  > private/ordered-1006-prototype.txt
build/tools-env/bin/python tests/test_archive_effective_profiles.py
# Fresh original fixture run, authorized Mac Unicorn JIT context, fresh private path:
build/tools-env/bin/python tests/compare_archive_effective.py \
  --exe private/official-1006-probe/game.exe --data-dir private/official-1006-probe \
  --report private/effective-1006-fresh.json
# After README's sanitizer build; new report path, no original execution:
build/tools-env/bin/python tests/replay_archive_effective.py \
  --exe private/official-1006-probe/game.exe --data-dir private/official-1006-probe \
  --native build/sanitize/archive-inspect \
  --expectations private/patch-inspection/effective-1006-prototype.json \
  --report private/effective-1006-sanitizer-replay.json
```

Next: coordinate explicit patched preparation profiles, numeric-data/runtime gates
and this initial reader policy; preserve exact old and new data identities. Run
applicable numeric, owned and real SDL checks on promoted inputs before claiming
that the 1.006 prototype runs. Then resume the planned ground-layer traversal/draw
eligibility work. Full reconstruction remains incomplete. All proprietary files,
manifests and research stay ignored. Source installs/discs and Outpost 2 are untouched.
