# Supplied RA2 1.006 boolean values and selected HTNK metadata

October 15, 2026, after `a49d769`. **9,138 fresh original/native results** and
normal/ASan/UBSan replays pass. The affected caller/type families have fresh
**9,167 / 20,442** results and both replays. This corrects a provisional field
name and supplies another prerequisite for the ordinary Unit drawing integration.
It is not a new observable gameplay milestone. Milestone 20's crossing remains
the current drawing capability; complete Unit DrawIt/voxel child wiring is open.

## Identity and reference correction

The supplied patched engine and approved private Windows transfer were rehashed:
`private/official-1006-probe/game.exe` and
`private/windows-baseline-20261014/game.exe`, 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 patch lineage and user-reported no-CD provenance
remain separate facts. Pristine authenticity is not established. No Windows task,
source installation, disc or system configuration changed.

Consulted the pinned redalert2-recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439`, `docs/voxels.md` and LICENSE, and
YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88`, `ObjectTypeClass.h`,
`TechnoTypeClass.h`, `UnitTypeClass.h` and `CCINIClass.h`. Hypothesis: type flags
choose ordinary voxel/turret branches and default through INI reads. Header names
are leads, not evidence for base RA2 offsets. No reference/header/generated or
lifted code was incorporated; no new dependency or third-party code was added.

**Base type byte `+0xBA6` is Harvester.** Its loader pushes the exact base-engine
`"Harvester"` string, calls actual GetBool and stores AL to that field. The former
`UnitDrawType::simpleDeployer` name was wrong and is now `harvester`. Earlier
zero-field caller results remain evidence for their recorded inputs; they did not
establish the provisional name. `SimpleDeployer` exists as a separate string;
neither its field nor its behavior is assigned by this recovery.

## Inspected and executed boundaries

`tools/verify_unit_metadata.py` pins five complete helpers / **462 instructions**,
six aligned parent loaders/constructors / **5,181 instructions**, the boolean jump
tables, CRC table, type ReadINI slots and selected field operands/key pushes.
The parent loaders and constructors are inspected in full, but **only the selected
read/call/store and constructor blocks execute** with supplied live registers.
These tests do not execute full type construction or its intervening services.

| Boundary | Patched VA |
| --- | --- |
| Complete GetBool | `0x50F410..0x50F590` |
| Complete CRC / byte CRC | `0x493FC0`, `0x494190` |
| Complete final hot-key helper | `0x510DD0` |
| Complete uppercase, executed locale-zero path | `0x7829D3` |
| UnitType ReadINI / constructor, inspected | `0x70AB40`, `0x70A600` |
| TechnoType ReadINI / constructor, inspected | `0x6DAF60`, `0x6D9B40` |
| ObjectType ReadINI / constructor, inspected | `0x5D7810`, `0x5D57F0` |

| INI field | Type byte | Read / actual GetBool call / store |
| --- | --- | --- |
| rules Harvester | `+0xBA6` | `0x70ABB6 / 0x70ABC5 / 0x70ABD0` |
| art Voxel | `+0x206` | `0x5D7B50 / 0x5D7B62 / 0x5D7B6B` |
| rules Turret | `+0xAAB` | `0x6DC024 / 0x6DC039 / 0x6DC05B` |
| rules HunterSeeker | `+0xAF2` | `0x6DD0EA / 0x6DD0F9 / 0x6DD0FE` |
| rules BalloonHover | `+0xB1A` | `0x6DD186 / 0x6DD195 / 0x6DD1AE` |

Actual GetBool, CRC, hot-key and uppercase instructions execute unchanged, including
inside the scoped loader calls. Decoded section/key indexes with matching hot
entries and CRT locale mode zero are fixtures. Cold search/sorting, allocation,
the original text parser and nonzero locale modes remain outside the claim.
The Voxel block uses its actual global art-INI address; its record is supplied.
Turret's byte read and push/call are separate blocks to avoid executing an
unrelated intervening store. Other skipped setup before final stores is explicit.

## Preserved semantics and runtime use

`iniBooleanValue` consumes only the first decoded byte. Locale-zero ASCII
uppercase makes `0/F/N` false and `1/T/Y` true, case-insensitively. Other bytes,
empty/missing values and tested null records return the **fallback low byte
unchanged**, including noncanonical values such as 127 or 255. A recognized first
byte ignores the entire suffix: `Nonsense` is false and `Totally` is true.
Leading whitespace at this decoded boundary is unrecognized. All 256 first bytes
are tested; high bytes retain fallback in the tested locale-zero mode.

`Ini::boolean` applies that value decision after the existing native text parser.
That parser's trimming, comments, key folding and duplicate handling remain host
format behavior; these comparisons do not prove original text parsing. Existing
HTNK Passive/cache/shadow booleans now use the same first-byte decision, retaining
their prior native missing-value defaults. Those call-site defaults are not newly
recovered by the generic GetBool tests.

`UnitTypeMetadata` models five scoped zero defaults and their rules/art associations.
Original scoped stores establish zero for each, not complete post-construction
state or layout equivalence. The previously selected private stock INIs resolve
HTNK to **Harvester=0, Voxel=1, Turret=1, HunterSeeker=0, BalloonHover=0**.
Native GameAssets uses this helper and explicitly refuses the other profiles.
This is a supported-domain guard, not recovered alternate-profile behavior.
Model naming/loading, type Image overrides, multiple turrets, alternate body
selection, actual actor/type ownership and full voxel child dispatch remain open.

## Evidence and reproduction

| Matching new results | Count |
| --- | ---: |
| All first bytes and wrapped/default byte inputs | 3,072 |
| Prefix-only values, whitespace and every default byte | 3,072 |
| Missing/null section/key/record/string paths | 1,792 |
| Scoped type reads, actual GetBool and exact byte stores | 1,200 |
| Five scoped constructor zero stores | 1 |
| Owned HTNK decoded fields, not full text parsing | 1 |
| **Total** | **9,138** |

**7,942 callable roots / 2,656 scoped blocks** are audited. Standalone roots enforce
ESP, return address, caller-tail and callee-saved guards. Blocks enforce balanced
stack, caller guard, exact ordered external byte stores and unchanged surrounding
arenas/global-INI record. Whole fixture arenas remain unchanged except explicitly
allowed stores. The original instruction image is not patched; no API/child stub
replaces these selected routines. Successful hot indexes deliberately avoid writes
and allocation. Native storage/layout and full constructor ordering are not claimed.

Receipts and both replays: `private/unit-draw-1006/metadata-v1/`;
fresh affected families: `caller-harvester-v1/` and `type-harvester-v1/`.
Earlier receipts remain unchanged with their own source identities. All receipts
pin executable/profile, relevant source/inspection/owned-input hashes and original
expectation fingerprint. Rebuilt runners receive their own recorded hashes.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/python tools/verify_unit_metadata.py \
  --exe private/official-1006-probe/game.exe
build/tools-env/bin/python tests/compare_unit_metadata.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/unit-draw-1006/metadata-v1/expected.json \
  --report private/unit-draw-1006/metadata-v1/NEW-REPLAY.json
# Sanitizer replay adds --native build/sanitize/unit-metadata-vectors.
# Fresh original execution requires the authorized Mac host JIT context:
build/tools-env/bin/python tests/compare_unit_metadata.py \
  --exe private/official-1006-probe/game.exe --output private/unit-draw-1006/NEW-METADATA
build/tools-env/bin/python tests/check_unit_metadata_assets.py \
  --data-dir private/official-1006-probe
./run.command --crossing-demo
```

Normal/sanitizer builds and CTest, **231 Python tests**, source/diff audits, eight
owned-data override/guard checks, normal/sanitizer headless crossing and actual SDL
selection/right-click crossing pass. Crossing retains 79 samples / 78 updates,
22 occluded samples / 150 maximum hidden pixels, clear endpoints, fresh final/no
trails, bypass, offscreen/partial clipping and pan return. These are native
integration checks; they do not prove original whole-frame rendering or integration
of the still-unused type/disguise/drawing caller kernels. Broad unrelated numeric
suites were not repeated. Only Apple Silicon macOS is tested.

## Accounting and next dependency

New fresh generation: 1.543 s driver / 1.154 s original / 0.046 s native. Metadata
normal/sanitizer replay: 0.327/0.637 s driver. Fresh caller/type regressions:
2.613/6.255 s driver; 2.124/5.529 s original. Their normal/sanitizer replays pass.
Initial normal/sanitizer builds: 13.93/12.48 s; a native test-only rebuild: 3.16 s.
CTest totals 0.05/0.25 s, Python discovery 0.393 s. Owned overrides 1.21 s;
headless crossing 3.34/13.37 s, actual SDL 1.12 s. Checks sometimes contended;
these times are not FPS claims. Final include-only rebuilds took 11.15/8.58 s;
their CTest totals were 0.10/0.45 s. All six differential runner hashes stayed
unchanged, so their existing replays were retained. The private checkpoint records
the closing clock and inherited-work limits.

Two original-generation attempts failed before saving evidence: the byte-write
callback exposed upper source-register bits (the audit now masks by write width
and also verifies stored bytes), then the supplied INIs' annotation-only lines
were refused by the fixture decoder (allowing valueless entries fixes that supplied
boundary). A guessed byte-CRC extent was rejected by the aligned-range verifier
before execution and corrected from complete disassembly. No game repair was needed.
No extra worker/cache/coordinator infrastructure was added. Continuation began
05:19:56 UTC; inherited delivery time is unavailable.

Next recover the ordinary `0x6FF690` voxel child, including its actual Foot lit
wrapper `0x4C9880` rather than assuming direct Techno wrapper dispatch. Nest the
established key/pose/raster/staging/shadow/surface kernels at verified boundaries,
then wire the caller and type decisions into the same moving/turning/current-cell
light delivery. Full construction/ownership, decoration, outer scheduling, camera,
fog/UI and whole-frame parity remain separate work. Full base RA2/YR stays active
and incomplete. This is locally verified work, not independent acceptance.
