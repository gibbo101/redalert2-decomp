# RA2 1.006 voxel loader, flat poses and indexed raster migration

October 14, 2026. Ivalice / Apple Silicon macOS. This extends presentation
checkpoint `0e970d1`; [BASELINE_1006.md](BASELINE_1006.md) records the supplied-patch
lineage and completed private Windows transfer. Neither was repeated here.

**707 fresh original/native results pass on each engine**, including three stock
loader results, 128 poses, 192 matrix products, 192 lighting setups and 192 complete
256×256 indexed buffers. Both native ASan/UBSan replays pass. The recovered native
algorithms are unchanged. The runtime and prepared-data gates remain disc-only;
remaining profile migration and effective patched archive precedence are pending.
This is a research checkpoint, with milestone 19 still the gameplay checkpoint.

## Exact inputs and references

| Profile | Executable SHA-256 |
| --- | --- |
| Allied disc | `135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743` |
| Supplied RA2 1.006 patch output | `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f` |

Inputs are `private/disc-allied/game.exe` and
`private/official-1006-probe/game.exe`. Both embed 1.08; complete hashes select the
profiles. The latter remains byte-identical to the approved Windows copy.
This establishes supplied-patch lineage, not publisher authentication or pristine
status of the entire reported no-CD installation. No Windows observation was added.

Consulted [REFERENCES.md](REFERENCES.md)'s voxel and testing entries:
redalert2-recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439`,
`docs/voxels.md` (The path of one unit, The buffers, Following the image onto the
battlefield), `docs/testing.md` (original oracle and isolated inputs), and LICENSE.
YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88`, `FileFormats/VXL.h` supplied
runtime-tail/corner layout leads. The hypothesis was to locate the base loader,
actual Drive interface and raster dispatch, then compare their exact data and
bounded execution. YR addresses, HD/remaster modifications and pointer-host runtime
behavior were not adopted. The MIT scope excludes generated game code; YRpp headers
remain naming/layout references only. No upstream, header or lifted code was reused.

## Independently inspected mappings

Normalized prefixes supplied candidates. Actual callers, complete ranges, explicit
operands, RTTI and dispatch pointers establish the following research mappings:

| Boundary | Disc VA | Supplied 1.006 VA |
| --- | --- | --- |
| Complete original VXL loader | `0x70DBC0` | `0x719160` |
| Full Drive Draw_Matrix | `0x49FC20` | `0x4A0050` |
| Base locomotion pose | `0x53B0C0` | `0x53D030` |
| Relative zero-offset turret block | `0x6F4744..0x6F47B4` | `0x6FFC14..0x6FFC84` |
| Camera degree initializers | `0x70C7B0` / `0x70C7D0` | `0x717D50` / `0x717D70` |
| Camera initialization tail | `0x70D6DE..0x70D714` | `0x718C7E..0x718CB4` |
| Matrix product | `0x58DE30` | `0x591180` |
| Default light / section shade wrapper | `0x70CA10` / `0x70BB30` | `0x717FB0` / `0x7170D0` |
| Scratch reset | `0x70BC30` | `0x7171D0` |
| Bounds projection / flush and crop | `0x70BF20` / `0x70C340` | `0x7174C0` / `0x7178E0` |
| Raster state and dispatch | `0x70E3A0` | `0x719940` |
| Lit assembly dispatch 4 / 5 | `0x784180` / `0x7842A0` | `0x798C00` / `0x798D20` |
| Traversal / trig data | `0x7E36B0` / `0x7EA0E4` | `0x7F9E60` / `0x801DC4` |
| Section record / indexed scratch | `0xAC8848` / `0xACAE68` | `0xAE0DE8` / `0xAE3408` |
| Light angle and its actual initialization caller | `0x785CF0` / `0x510D29` | `0x79ACF0` / `0x511A29` |

`tools/verify_raster_mapping.py` checks **31 complete routines/blocks/ranges,
2,512 instructions, 15 referenced constant/table ranges and both selected dispatch
entries**. It checks the Drive interface's RTTI and slot 9, distinguishing it from
the similar Ship prefix. Body/turret fields remain +0x2E0/+0x2F8 in the inspected
pose operations. Camera initializer constants and stores are tied to the globals
consumed by the actual camera tail. The original light-angle caller establishes
the field that presentation-primitive migration had left unused/unassociated.
Consumed traversal, trig/scales, heading/degrees and light-angle data match exactly.

One instruction differs beyond relocation: disc `0x70DE06` uses `jl`, patched
`0x7193A6` uses `jb`, in the **optional embedded-palette pointer loop**. The verifier
accepts only these exact opcodes and preserves its relative branch target. The
executed profile passes UseContainedPalette=0, skipping that loop. There is no
claim about the optional palette path, malformed loader inputs or arbitrary section
counts. Nonflat pose branches and alternate raster dispatch are inspected metadata,
not executed parity claims.

`tests/raster_profiles.py` is explicit research metadata, never a blanket address
offset or runtime mapping. `RasterOracle` retains its disc-only constructor default;
the migrated CLI explicitly opts in. Composition and other descendants still reject
patched input. Unknown hashes and unmapped patched addresses fail closed.

## Executed outputs and audits

The retained [RASTER.md](RASTER.md) domain executes unchanged original loader,
pose/lighting/project/generator/assembly/crop instructions on each engine:

| Results per engine | Count | Compared output |
| --- | ---: | --- |
| Successful stock VXL loads | 3 | Section dimensions/normal encoding, scale/base matrix bits, eight corner bits, length-prefixed compressed spans for every column |
| Body/turret/camera poses | 128 | All 36 float32 words; original heading key checked |
| Camera/pose products | 192 | All 12 float32 words |
| Complete section light setups | 192 | All 256 shade slots |
| Complete indexed section buffers | 192 | Full-buffer SHA-256, six crop fields, traversal, 24 projected-corner words |
| **Total** | **707** | All compared results match |

The supplied HTNK body/turret/barrel each have one section. All 32 render bins,
boundary ties/wrap, reverse views and fractional translations remain covered;
all **eight traversal choices** are asserted. Loader metadata excludes opaque
fixture pointers and names not retained by the original runtime layout.

**2,499 callable roots** per engine check final ESP, return address, callee-saved
registers, stack beyond consumed arguments, permitted output/field/stack writes
and immutable inputs. **640 turret/camera blocks** check stop EIP, unchanged ESP,
permitted writes, caller-stack guards and immutable actor inputs. The loader's
**12 bounded fixture allocations** have guard bytes and live-allocation write checks;
file reads are separately checked against allocated blocks/stack. Pose/render calls
preserve the loaded heap. No service callbacks occur during pose/render execution.

File open/read/seek/close and successful allocation/free remain supplied research
services; original allocator/failure/lifetime behavior is not recovered. These are
bounded write/input/caller audits, not ordered native/original write parity or a
complete actor-arena audit. Original bytes are unchanged. The x87 test context
remains 0x0E7F, with original table arithmetic, float32 stores and traversal retained.

Native `raster-vectors` now accepts an explicit render-data path and emits loader
metadata in addition to its previous protocol. This removes the hidden relative
render-file dependency for this suite; its legacy one-argument default remains
for unmigrated callers. No shipped native algorithm or asset reader changed.

## Evidence, reproduction and remaining work

Fresh protected assets, buffers, expectations and receipts are under:

```text
private/migration/allied-disc/raster/
private/migration/supplied-ra2-1006/raster/
```

Receipts pin exact engines, native runner, oracle/profile/evidence/mapping sources,
prepared raster/render files, all four supplied assets and expectation fingerprint.
Native replay checks the fresh receipt and identities, and records that it executed
no original instructions. Fresh runs refuse existing expectations/receipts;
replays cannot replace them. **Seven synthetic guards pass**, alongside the eight
retained presentation guards. Historical `private/raster/` evidence is preserved.

Native inputs deliberately retain the verified disc raster file
`f357f3b4d7b048b7f65d7a43f4f96a41e6c21b5974bb1340d7fd98e92abcd8a3`
and render file
`50d2876e6bf8a3b9d535a1843ef93f41109b7021a15e1dbacb47aaa881389c6d`.
Patched research requires the disc engine's explicit --native-data-exe identity;
fresh primitive/raster mapping checks verify all consumed table associations.
The four exported assets must match their retained supplied hashes. Original archive
precedence and consistent patched prepared-source promotion remain separate work.

```sh
./build.command
./test.command --data-dir "$PWD/private/game"
build/tools-env/bin/python tests/test_raster_profiles.py
build/tools-env/bin/python tools/verify_raster_mapping.py \
  --disc private/disc-allied/game.exe --patched private/official-1006-probe/game.exe
# Fresh original execution, once per profile evidence folder:
build/tools-env/bin/python tests/compare_raster.py \
  --exe private/official-1006-probe/game.exe \
  --native-data-exe private/disc-allied/game.exe --data-dir private/game
# Existing evidence replay; after README's sanitizer build:
build/tools-env/bin/python tests/compare_raster.py \
  --exe private/official-1006-probe/game.exe --native-data-exe private/disc-allied/game.exe \
  --native build/sanitize/raster-vectors \
  --expectations private/migration/supplied-ra2-1006/raster/expected.json \
  --report private/migration/supplied-ra2-1006/raster/sanitize-report.json
# Disc replay uses its own engine and allied-disc paths.
./run.command
```

Original execution requires the established authorized Mac JIT context. SDL tests
need a desktop context; an initial restricted run passed headless checks but could
not open a display. The desktop rerun passes both **170-frame SDL regressions**.
Both native builds, owned-data renderer/light/scenery checks and sanitizer synthetic
checks pass. A first original run matched outputs but failed its receipt check
because a frame digest overwrote the local executable-digest variable. Renaming it
and repeating original execution produced the final passing receipts.

Inherited disc-suite regressions use a separate
`private/migration/disc-raster-regressions/` workspace, preserving historical outputs.
Ten suites in its `run-report.json` plus a separate terrain-type run pass: 424
composition, 9,812 shadow/color, 2,603 staging, 4,743 lit-cache and 2,204 shadow-key
protocol results; 17,510 map-light, 2,574 static-light, 3,257 unit-light, 420 scenery,
808 props and 1,128 terrain-type results. This guards
the shared loader/pose fixture without promoting descendant addresses to 1.006.

Next migrate composition, then light/cache/scenery/occupation/lifecycle profiles;
establish effective patched archive precedence and consistent prepared inputs before
runtime promotion. Ground-layer traversal/eligibility remains milestone 20.
Routing/clearance, controls, visibility, scheduling, actor/house/cache lifetime,
nonflat/animated poses and whole-frame integration remain adapters or open.
No gameplay, full-frame, native Windows/Linux or YR parity is claimed. No proprietary
files or copied original code are tracked; source installations and Outpost 2 are
untouched. The full native-game goal remains active and incomplete.
