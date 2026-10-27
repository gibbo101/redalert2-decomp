# RA2 1.006 lit voxel-cache migration

October 14, 2026. Ivalice / Apple Silicon macOS.

This checkpoint verifies the retained ordinary body/turret key and successful
lit-cache domain from [VOXEL_CACHE.md](VOXEL_CACHE.md) on separately selected disc
and supplied patched engines. Native C++ algorithms, prepared files and runtime
gates remain unchanged. Full actor, compressed pool, failure/eviction/lifecycle
and whole-frame parity remain outside the claim. This is an intermediate migration
checkpoint; the complete 1.006 transition remains the next capability delivery.

## Identities and references

| Original engine | SHA-256 |
| --- | --- |
| Allied disc, embedded 1.08 | `135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743` |
| Supplied RA2 1.006 patch output, embedded 1.08 | `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f` |

Both are PE32/i386 at image base `0x400000`. The supplied patched engine equals
the approved private Windows copy. [BASELINE_1006.md](BASELINE_1006.md) records
patch lineage and no-CD provenance; this does not certify a pristine installation
or YR equivalence. All original execution is hash-pinned, private research-only
Unicorn, outside the native runtime.

Consulted redalert2-recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439`,
`docs/voxels.md` (The path of one unit, Cost) and LICENSE, plus YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88`, `TechnoClass.h`, `FootClass.h`
and `TechnoTypeClass.h`. Key-based reuse, cache disabling and method names supply
hypotheses only. Independently locate the body/turret key blocks and complete
lit/index dispatch on the exact patched engine, then execute the retained bounded
domain. No upstream/header/generated code was incorporated. See
[REFERENCES.md](REFERENCES.md).

## Inspected boundaries

`tools/verify_voxel_cache_mapping.py` checks **eight ranges / 654 instructions**,
all encoded operand differences, two jump tables, two INI strings and the actual
Unit brightness slot and wrapper sort/search caller. `voxel_cache_profiles.py`
adds **30 explicit mappings**, retaining its inspected ancestor mappings. No
installer label or blanket address displacement selects code.

| Boundary | Disc VA | Supplied 1.006 VA |
| --- | --- | --- |
| Body key block | `0x6F42F1` | `0x6FF7C1` |
| Turret key block | `0x6F445B` | `0x6FF92B` |
| Complete lit wrapper | `0x6C7120` | `0x6D1D00` |
| Complete sort/search wrapper | `0x6CEC70` | `0x6D9850` |
| Complete status helper, healthy branch only executed | `0x6CDB10` | `0x6D86F0` |
| Complete turret Facing getter | `0x4B8700` | `0x4B8BE0` |
| DisableVoxelCache loader association | `0x6D2E8A` | `0x6DDA6A` |
| TurretOffset loader association | `0x6D2DE1` | `0x6DD9C1` |

The actual wrapper call at `0x6C727C → 0x6D1E5C` resolves an ambiguous common
sort/search prefix. The wrapper ends immediately after its final `ret 0x24`, at
`0x6C75EC → 0x6D21CC`; the following five-entry jump table is data, checked
separately. The status helper's nine-entry table is at `0x6CDC1C → 0x6D87FC`.
The Facing getter includes the continuation after its first return and ends after
the second return at `0x4B8799 → 0x4B8C79`. Unit RTTI and its `+0x3F8` slot
select the previously verified brightness-effect helper.

Historical loader references `0x6D2E8B` and `0x6D2DE2` are operand locations,
not instruction starts. Aligned blocks verify the actual DisableVoxelCache byte
store at type `+0xB5A` and TurretOffset dword store at `+0x63C`. Full INI parsing,
alternate predicate/status methods and unexecuted allocation branches are excluded.

## Execution and audit scope

Preserve uint32 wrapping, five frame bits and zero-offset turret mask
`0xFFFFFC1F`; lookup precedes model validity. Cacheable lit misses render then
append without recursive hit. Hot lookup precedes sorting, signed sort/search
retains its original decisions, successful growth clears hot, and `-1` bypass
never inserts. Native storage remains logical frames rather than the original pool.

| Retained behavior per engine | Results |
| --- | ---: |
| Actual body/turret key blocks | 1,934 |
| Complete healthy lit wrapper/index decisions | 2,484 |
| Selected owned cached buffers and crops | 300 |
| Owned disabled-cache buffers and crops | 12 |
| **Behavior cases** | **4,730** |
| Protocol resets | 13 |
| **Protocol results** | **4,743** |

Per engine, **5,611 callable roots**, **4,285 blocks**, **70 guarded allocations**
and **2,168 explicit supplied-service writes** are checked, including inherited
loader/pose/light/raster calls. Body-block checks verify its actual 48-byte pose
copy with nonzero source locals and preserve unrelated stack bytes. Turret checks
permit only its facing-output/key locals and preserve actor/type/vtable inputs.
Wrapper calls audit return address, consumed arguments versus caller stack, ESP,
callee-saved registers, heap canaries and immutable model/other-index allocations.
Only the current entry allocation is mutable. Python snapshot/render service
writes are checked explicitly because Unicorn guest-write hooks do not see them;
prior logical snapshot IDs and unrelated snapshot bytes remain unchanged.

Successful heap/free, healthy virtual predicates/type/house queries, render
rectangle, logical snapshot identity and cached-blit recording remain supplied
services. Owned buffer cases run actual original poses, lighting and rasterization
before the wrapper selects a logical snapshot. Entire 65,536-byte indexed buffers
and six crop fields compare. These checks do not establish ordered native/original
writes, actual compressed encoding/pool ownership, failure/destruction, full Unit
draw, runtime actor lifetime or whole-frame fidelity. Runtime stays one-frame
stock HTNK, healthy/flat/Track only; animated and alternate profiles remain refused.

## Evidence and commands

Protected profile evidence lives under:

```text
private/migration/allied-disc/voxel-cache/
private/migration/supplied-ra2-1006/voxel-cache/
```

Fresh runs refuse existing receipts/expectations. Replay pins the full executable
and profile, oracle/mapping sources, both exporters, exported identities, retained
render/raster files and expectations fingerprint; it cannot replace original
receipts. The raster exporter now supplies three VXLs/VPL explicitly, avoiding the
historical reliance on assets already present in `private/staging/assets`.
Staging palette exports are recorded separately in the same inventory; this cache
suite consumes only the four VXL/VPL files. Ten synthetic profile/evidence guards
pass. Earlier disc evidence remains preserved and is never relabeled patched.

```sh
./build.command
build/tools-env/bin/python tests/test_voxel_cache_profiles.py
build/tools-env/bin/python tools/verify_voxel_cache_mapping.py \
  --disc private/disc-allied/game.exe --patched private/official-1006-probe/game.exe
# Fresh original execution, only where no receipts exist:
build/tools-env/bin/python tests/compare_voxel_cache.py \
  --exe private/official-1006-probe/game.exe \
  --native-data-exe private/disc-allied/game.exe
# Current identity-checked replay, without original execution:
build/tools-env/bin/python tests/compare_voxel_cache.py \
  --exe private/official-1006-probe/game.exe \
  --native-data-exe private/disc-allied/game.exe \
  --expectations private/migration/supplied-ra2-1006/voxel-cache/expected.json
# After README's sanitizer build, add:
# --native build/sanitize/voxel-cache-vectors
# --report private/migration/supplied-ra2-1006/voxel-cache/sanitize-report.json
./run.command --light-demo
```

Patched research still explicitly retains native disc table inputs. Render data:
`50d2876e6bf8a3b9d535a1843ef93f41109b7021a15e1dbacb47aaa881389c6d`.
Raster data:
`f357f3b4d7b048b7f65d7a43f4f96a41e6c21b5974bb1340d7fd98e92abcd8a3`.

The initial two complete attempts were rejected when a mapping-tool description
changed during execution; no receipts were saved. The corrected fresh runs use
frozen sources. Timing collection began after those attempts: earlier original
wall time and inherited implementation time were not measured. Native replay
measurements are in the private profile `*-timing.json` files; they include
identity, mapping/export checks and native execution. No new cache infrastructure
was introduced. Build/native/owned-data checks and both 170-frame SDL regressions
exercise retained integration; no playtest defect was found or repair required.

The next focused checkpoint is shadow-key migration, then related scenery/type/
prop and occupation/lifecycle profiles, archive precedence and consistent prepared
inputs. Promote the runtime only after that coherent delivery passes its applicable
original/native and real SDL checks. Only Apple Silicon macOS is tested.
