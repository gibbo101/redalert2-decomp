# Supplied RA2 1.006 overlay registry and INI inputs

October 15, 2026, after `b2ade29`. This is a prerequisite checkpoint for the
same terrain-aware Foot/world level crossing and parked-cliff capability.
It adds readable C++ overlay construction, identity resolution, list ordering
and overlay-specific INI decisions. These helpers remain unwired; decoded map
overlay loading and the overlay-bearing map preparation parent are still pending.
This is not a completed playable milestone or independent acceptance.

## Identity and references

Both supplied private engines are 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 lineage and reported no-CD modifications remain
separate provenance; pristine authenticity is unverified. The already approved
Windows transfer was complete before this checkpoint. No new Windows action,
transfer, source-install change, system selection or DRM experiment occurred.

Consulted [REFERENCES.md](REFERENCES.md), pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` `docs/voxels.md`/LICENSE and YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` `OverlayTypeClass.h`,
`ObjectTypeClass.h`, `TiberiumClass.h` and `RulesClass.h`. Hypothesis: map overlay
bytes must be associated through the constructed registry, whose defaults and
INI decisions affect Cell recalculation. Recomp supplies no verified base overlay
algorithm; YR declarations are naming leads, not a base behavior oracle. No
upstream/header/generated/lifted code or extracted table was incorporated.

## Recovered boundary

[OverlayTypeInputs.cpp](../src/assets/OverlayTypeInputs.cpp) separates the
selected type projection from base construction, parsing, file/animation services
and heap ownership. Original object padding, vtables and addresses are not native
storage or runtime dependencies.

| Complete original root | Verified behavior |
| --- | --- |
| `0x5DC5A0..0x5DC6F2` | Overlay constructor, actual identity child, selected defaults, registry append and first equal pointer index |
| `0x5DCF70..0x5DCFF3` | Case-insensitive supplied CRT comparisons, none sentinels, first matching ID, allocation and actual nested constructor |
| `0x64C010..0x64C07A` | Supplied entry enumeration/string reads and actual nested resolver/constructor |
| `0x5DCAA0..0x5DCD41` | Complete overlay INI root, with supplied base INI/parser/image/animation services |
| `0x40FFD0..0x40FFF5` | Identity initialization with loading global zero |

These five executed complete ranges contain **374 inspected instructions**.
Complete ObjectType constructor `0x5D57F0..0x5D5A77` and INI root
`0x5D7810..0x5D7BCF` add **428 inspected instructions**, but are **inspection
only**. They are services in this oracle. Do not claim their original defaults,
string/parser behavior, registration or other side effects were executed.

Constructor behavior:

- DamageLevels and Strength start at one. NoUseTileLandType and DrawFlat start
  at byte one; other overlay flags, land and CellAnim start at zero. ArrayIndex
  starts at -1. Selected inherited flag stores remain ordered after identity.
- Append increments count before writing the new slot. Afterwards the index is
  the **first equal pointer**, including when that pointer already occurs in the
  registry. Failed append does not prevent that search.
- Full storage grows only when owned or capacity zero, and growth is positive.
  The low byte of the growth result controls success. Native invalid-storage,
  null-member, unsupported capacity-wrap and dishonest growth-service refusals
  are safety boundaries, not original malformed-input behavior.
- Resolver compares `<none>` then `none`, then registered IDs in order. Failed
  allocation returns null. Original heap/growth and CRT locale are supplied.
- List success depends on a positive entry count, even when all values are empty,
  none sentinels or fail allocation. It tests the supplied GetString return, not
  the buffer's first byte. An explicitly nonzero read with an empty buffer still
  reaches the resolver.

INI behavior:

- Base false returns immediately. Land, Strength, Wall, Tiberium, Crate,
  CrateTrigger, Explodes and Overrides are read from the main section, in order.
  Current byte defaults are preserved and returned values store their low byte.
- CellAnim retains the pointer saved before the read when its return is zero;
  a nonzero return invokes the supplied resolver, including a null result.
- DamageLevels and **DemandLoad** come from the art section named by Image.
  YRpp's `ImageLoaded` field label does not override the executable's DemandLoad
  key. After these reads, a nonzero Tiberium byte sets Armor to 6, and changes
  zero Land to 5. Other land values survive.
- When both Theater and DemandLoad are zero, request Image plus `.SHP` and store
  the supplied result, including null. Path/file/cache semantics stay supplied.
- NoUseTileLandType, IsVeinholeMonster, IsVeins, ChainReaction, DrawFlat, IsARock
  and IsRubble are read afterward, in that order. Image loading is not moved to
  the end or silently omitted.

Complete base INI inspection associates +0x1FD with **Crushable**, +0x1FF with
RadarInvisible, +0x200 with Selectable, +0x202 with Insignificant and +0x9C with
Armor. This supplies vocabulary; those base reads/defaults are not executed here.
The older [overlay Cell suite](OVERLAY_CELLS_1006.md) retains its supplied numeric
`flag1FD` API and historical receipts. +0x205 stays numerically named here.

## Executed evidence and supplied inputs

Current private receipts: `private/map-depth-1006/overlay-inputs-v3/`.
**1,349 fresh original/native results** compare the return, complete selected
type projection, registry count/capacity/all capacity slots, ID/image strings,
and ordered selected stores/comparisons/requests. The corpus includes:

- 384 constructor cases with duplicate pointers, owned/borrowed/full storage,
  growth rejection and low-byte results;
- 768 complete INI cases with supplied base success/failure, retained defaults,
  mixed byte values, signed numeric patterns, resource-land and image/animation
  branches;
- 192 list/resolver cases with repeated case variants, sentinel names, empty
  values, allocation failure, growth and 31-byte identifiers;
- four explicit empty/negative-count/nonzero-empty-buffer cases, plus all **243
  host-decoded owned-rules list entries** supplied in enumeration order to the
  complete original list parent.

Counts: 1,349 audited outer calls; 1,114 constructor and identity entries, 768 INI
entries, 1,525 resolver entries and 197 list entries. Compare **38,856 ordered
selected guest stores** and **50,488 supplied service calls**. Original code is
unchanged. Caller stack/register/return address, declared service ABI/arguments,
record bytes outside the projection, registry capacity tails, key strings and
loading global are guarded. No complete read-order or original heap claim.

The base constructor service sets ID/image strings and preserves deliberately
varied supplied numeric base fields. Base INI returns a supplied result. INI
key/value parsing and enumeration, land parsing, CRT ASCII comparisons, path
creation, image/animation results, allocation and growth are explicit services.
The 243-entry fixture proves the constructed list association for those supplied
entries. It does **not** prove original text parsing/layering/startup, complete
base defaulting, map OverlayPack parsing or raw map byte-to-Cell association.
Do not assign map names using numeric INI keys; the list starts at key 1.

v1 predates the nonzero-empty-buffer case and final field vocabulary/inspection
guards. v2 precedes the explicit saved-CellAnim read. These receipts stay
historical. v3 freshly executes the current sources; it has identical commands
and results to v2. No old result is relabeled.

## Reproduction and next dependency

Both builds, **508 Python tests**, **30 normal / 29 sanitizer CTests** and both
new replays pass. All 32 earlier source/runner sets remain identity-current;
the final audit covers **34 sets / 742 source entries** and unchanged decoder
identity. Source/diff/local-link audits pass. Actual rebuilt SDL baseline passes
selection/right-click, 79 samples/78 updates, lighted crossing, culling/clipping,
cache bypass and pan return. This is existing native integration evidence, not
new overlay/map-depth integration or original-frame parity.

Fresh v3 driver/original/native: 16.653/15.956/0.064 s, CLI 17.044 s; normal/
sanitizer replay CLI 0.493/1.890 s. Final normal/sanitizer builds 7.640/7.062 s;
Python CLI 1.029 s, test.command 1.234 s, sanitizer CTest 2.599 s and SDL 2.741 s.
Private overlay-input timing/continuation/coverage/closing files retain all
intermediate runs. No original/native mismatch or gameplay repair. Full active
delivery/initial continuation-start elapsed measurements remain unavailable.
Only Apple Silicon macOS is tested.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

# Fresh execution requires the authorized host JIT context. Use an unused output.
build/tools-env/bin/python tests/compare_overlay_type_inputs.py \
  --exe private/official-1006-probe/game.exe \
  --rules private/map-depth-1006/resident-fixture-v1/rules.ini \
  --output private/map-depth-1006/overlay-inputs-new
build/tools-env/bin/python tests/compare_overlay_type_inputs.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/overlay-inputs-v3/expected.json \
  --report private/map-depth-1006/overlay-inputs-v3/replay-new.json
# Add --native build/sanitize/overlay-type-input-vectors for sanitizer replay.

./run.command --crossing-light-demo
# Select Rhino; G/right-click moves, L toggles light, R resets.
```

Continue decoded overlay loading/Cell association, needed base defaults and the
overlay-bearing map parent's resource/wall-owner effects. The inspected map
reader remains a lead, not executed evidence. Then verify prepared Cell/TMP
inputs through actual Foot/base-depth branches, wire Unit/world drawing and
require actual SDL level crossing plus parked `(51,72)`, elevation 4. Runtime
tile/tube/contact/depth inputs remain neutral. Original base construction/INI,
actor/contact/heap/cache lifetime, scheduling/camera/fog/UI, pathfinding and
whole-frame parity remain open. Full base RA2 then YR remains active/incomplete.
