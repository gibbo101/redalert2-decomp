# Current-ramp Drive shadow pose and cache key

October 15, 2026, after `a421c1c`. `driveShadowPose` now projects the complete
base pose/key getter and Drive timer/rocking wrapper using all 21 original-initialized
ramp matrices. **3,904 fresh original/native results** and normal/ASan/UBSan
replays pass. Actual original full-coordinate map lookup, Facing, table-copy and
Z rotation execute without replacement services. This helper remains unwired;
the prepared Unit-world current-ramp-zero guard is still required until its actual
shadow consumers and actor-relative height are joined. Complete base RA2 then
Yuri's Revenge remain active and incomplete.

## Identity, references and inspected boundary

Both supplied private engines remain 4,485,392 bytes / SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 lineage and reported no-CD modifications remain
separate provenance; pristine authenticity is unverified. No new Windows action,
transfer, source-installation/system change, dependency or worker.

Consulted [REFERENCES.md](REFERENCES.md), pinned YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` `DriveLocomotionClass.h`,
`LocomotionClass.h`, `Matrix3D.h` shadow/timer declarations and recomp snapshot
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` `docs/voxels.md` Shadows / MIT
LICENSE. Hypothesis: ramp selection belongs in the base getter, while Drive
invalidates cache identity for an unfinished slope transition or rocking.
Exact base inspection/execution decides the behavior. YR declarations are leads;
recomp is not an oracle. Existing license boundaries remain: no YRpp license file
found; recomp's MIT excludes generated/lifted code and its stale The Movies scope
is recorded. No upstream/header/generated/lifted code or extracted table incorporated.

[verify_drive_shadow_pose.py](../tools/verify_drive_shadow_pose.py) pins five
complete selected ranges / **254 instructions**, already inspected as flat ancestors:

| Root | Executed scope |
| --- | --- |
| `0x4A0500`, 178 bytes | Complete Drive timer/rocking wrapper and output copy |
| `0x53D0D0`, 240 bytes | Complete base current-ramp matrix/heading/key getter |
| `0x718D60`, 28 bytes | Copy the selected 12-dword ramp matrix |
| `0x4B8BE0`, 153 bytes | Actual settled/dynamic Facing getter |
| `0x548000`, 104 bytes | Actual full-coordinate Cell lookup/fallback stores |

The profile also pins the prior 41 numeric/matrix/CRT regions. In the same guest,
one pair of actual stock geometry chains and the complete matrix initializer run
before pose queries. Native uses `stockRampGeometry` and `voxelRampShadowMatrices`
with the unchanged private prepared artifacts. No neutralized nonflat table,
original instruction patch, synthetic guest instruction or numerical stub.

## Recovered behavior and boundaries

The base getter copies actor X/Y/Z, runs full signed coordinate lookup and uses
Cell byte `+0x11C` to select `0xAF8608 + 48*ramp`. It queries body Facing, rounds
to the original 32 visual bins and rotates the copied matrix about Z using a
float32 `(bin-8)*headingStep` and original table trig/component stores. This is a
shadow pose; it does not establish body tilt or ramp locomotion.

Null or -1 cache-key pointers still build that pose and query Facing once.
A cacheable key receives **two ordered writes**: first
`((uint32(key)<<6)+ramp)<<5`, then the result OR a **second actual Facing query's**
32-bin heading. Preserve wrapped unsigned packing, the repeated query and the
intermediate store; do not apply the old flat-key helper to a nonflat Cell.

Drive reads slope duration, start and remaining words from its supplied interface
record. Zero duration gives fraction one. Otherwise, start -1 keeps remaining;
an active timer compares signed wrapped tick-minus-start with remaining before
subtracting or clearing it. Subtract remaining from duration with low-dword wrap
and divide the signed result by duration. A fraction **not equal to one** forces
key -1. With fraction one, either absolute rocking float at or above the original
double threshold **0.005** also forces -1. The float nearest 0.005 lies below that
double; its next float above crosses the gate. The wrapper still calls the base
getter after invalidation and copies its complete result. Null keys omit stores.

Native map/Facing services are read-only observers in this profile; key-store
callbacks expose actual store order. The fixture supplies actor/locomotor/Facing/
timer/global tick and sparse map/storage records. Native maps the existing
`MapCellInput::slope` to the original ramp byte and uses `mapCoordinateCell`, with
resident hits, signed aliases and shared fallback mutation. This is not loaded-map
or original actor construction/ownership proof. Only the stock initialized matrix
table is joined here; arbitrary alternate tables, aliasing and mutable callbacks
are outside this verification. Nonfinite rocking, missing services and unsupported
ramps/matrices are native safety refusals, not original malformed-input parity.

The existing Unit caller/Foot/shadow-cache/raster/staging/final-copy consumers are
not joined in this profile. Floor-relative height, actor placement/update, original
startup ordering, complete memory-read order, heap/cache ownership and runtime/
whole-frame fidelity remain open. Existing prepared Unit-world and earlier flat
world receipts retain their guards and original scopes. Runtime binary reads and
prepared data formats are unchanged; simulation remains SDL-free.

## Verification and reproduction

Receipts: `private/map-depth-1006/drive-shadow-pose-v1/`. Cases cover every stock
ramp and 32-bin heading, quantization boundaries, null/-1/extreme wrapped keys,
signed timer edges/wraparound, both rocking components at nearby threshold floats,
dynamic Facing and full-coordinate resident/fallback lookup. Native incoming FP
modes cycle across cases; six identical poses each run under four modes (24 results).
Every native call restores the incoming mode. Compare all twelve matrix dwords,
final key/fallback position and ordered map/ramp/Facing/key-write events.

The original executes **2,596 Drive wrappers / 3,904 base getters**, 3,904 actual
map/table-copy calls, 6,329 Facing calls, **5,477 key writes** and 136 fallback
stores. There are 3,925 audited root calls including numeric setup. Guards check
code/block bounds, exact dispatch/hash, return/ESP/callee-saved registers/caller
stack, immutable matrix/code/inputs and permitted output/key/fallback writes.
Entire actor/locomotor arena and nonselected fallback bytes remain unchanged.
Nine malformed/nonfinite/domain native commands are separately refused.

Fresh CLI/original/native: **4.346/3.321/0.069 s**. An initial fixture build used
vector operations on the map's span and then the wrong native field name `ramp`;
both compile failures were fixed to use owned pointer storage and existing `slope`.
One premature compare launch found the missing unbuilt runner; it executed no
original code or accepted expectations. The first completed fresh comparison passes.
Closing build/test/accounting is in [HANDOFF.md](HANDOFF.md).

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

# Fresh original execution needs authorized Mac host JIT and a new private output.
build/tools-env/bin/python tests/compare_drive_shadow_pose.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/drive-shadow-pose-new
build/tools-env/bin/python tests/compare_drive_shadow_pose.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/drive-shadow-pose-v1/expected.json \
  --report private/map-depth-1006/drive-shadow-pose-v1/replay-new.json
# Add --native build/sanitize/drive-shadow-pose-vectors for sanitizer replay.

./run.command --crossing-light-demo
```

The demo remains the existing playable baseline; this helper is not enabled there.
Only Apple Silicon macOS is tested. Next join the actual Drive pose/key and
floor-relative height through Unit/shadow consumers on prepared Cells, then recover
floor-to-actor placement/update. Actual SDL level crossing and parked `(51,72)`,
elevation 4 remain acceptance scenarios before depth promotion. This checkpoint
is locally verified, not independent acceptance or a new playable capability.
