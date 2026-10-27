# Building image selection on shared owners

[Building Cell lighting](BUILDING_CELL_LIGHT_1006.md) supersedes the earlier
Cell-height label below:10A is signed ambient. The actual shared-map lookup and
renderer light owner now compose explicitly; final pixels/scheduling remain open.


Complete `44C5A0` now selects and demand-loads the ordinary Building image on the
existing Boot Camp Structure and Type owners. This removes the supplied image68
callback from the explicit static -> visibility -> ordinary asset-aware drawing
composition. It is a dependency of original Building drawing and frame consumption
needed for Boot Camp discovery/Objective1 presentation. Requests still stop before
the final pixel child; this does not schedule frames, sight, arrival or objectives.
Both games remain incomplete. Only Apple Silicon macOS has been tested.

## Recovery and evidence

The supplied executable is 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain separate. The complete dispatcher is48 bytes/12
instructions, ending in either virtual tail jump. Building vtable79CBBC slot68
selects44C5A0; BuildingType79D1F8 slots9C/C0 select458CE0/45E790.

It reads signed-width stage42C first. Zero skips the5B4 byte entirely. Otherwise
any nonzero5B4 selects primary9C; zero selects secondaryC0. It then reads the live
Type418 and tail-dispatches with that exact Type receiver, preserving the child's
result. No fallback from a null primary result to secondary is invented. Each
selected getter retains its own separately recovered demand/fallback policy.

639 original sequences execute this unmodified dispatcher together with complete
458CE0/45E790, actual theater/generic transforms and FTOL. They extend the existing
614 getter cases with25 stage/flag combinations, including signed extremes and
raw byte values0/1/2/128/255. Ordered actor reads prove short-circuit behavior;
child receiver, caller stack/callee-saved registers, immutable code/vtables and
unrelated arena bytes are audited. Getter traces compare file-service traversal,
ordered stores, signed header/timing handling, mutations and repeated calls.
The legacy fixture `op` field identifies the source getter case; the actual
selected path is always determined by stage/flag, in original and native runs.

File/CRT/heap services, decoded SHP identities and initial actor/Type records remain
supplied. These are isolated binary differential tests, not original-game
observations or whole-frame fidelity evidence. Actual-owner composition is a
separate current-native check; no joined original43A5E0-to-pixels claim is made.

Original answers live privately at
`private/building-image-selection-20261019/fresh-a1/expected.json`. Replays
explicitly reuse the original answers and execute the current native runner;
native pass/fail is never cached. Each final profile also reuses614 unchanged
getter answers as regression coverage. The scopes remain separate.

## Existing owners and boundaries

`StructureSightState::image5b4` is supplied startup on the existing actor; stage42C
and Type418 already have owners. No replacement actor or Type is introduced.
`structureImageFromAssets` resolves the late actual Type and uses the existing
primary/secondary demand getters. A synchronous host adapter now serves both
selection and Type bounds, using the existing read-only AssetStore/SHP reader and
Type-owned immutable image backing. Names, demand flags, theater, Rules timing,
cache override and file/heap/decoder implementation remain supplied.

`drawStructureOrdinaryFromAssets` binds actual selection and image header access
before invoking the existing ordinary parent. Competing image/count callbacks
refuse. Header access resolves the saved image identity across owned Types rather
than imposing an extra current-actor Type query. The low-level child-service API
remains available for isolated tests. Cell548070/height10A, partner/timer effects,
animation454 association, final6D1510 pixels and special43ABD0 remain unjoined.
Changed Type-to-foundation association still refuses at the original foundation
query; no stale dimensions or fabricated18-animation array is introduced.

Actual-owner checks cover cold loads on both Objective1 Types, secondary-only
selection, primary selection with raw flag128, resident reuse without duplicate
allocation, first/fallback absence, live Type reassociation/foreign Type refusal,
clone/source destruction and source/Cell-queue isolation. Static/visibility/
ordinary traversal uses the asset-aware entry point on the existing renderer and
owner caches. Separate low-level tests retain missing-child, late-Type and
animation-association refusal coverage.

## Reproduce

```sh
./build.command
./test.command
build/native/boot-camp-walk-check private/official-1006-probe
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest \
  tests/test_building_image_selection.py tests/test_building_image.py \
  tests/test_building_ordinary.py
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/NEW.audit.json \
  tests/compare_building_image_selection.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/building-image-selection-vectors \
  --expectations private/building-image-selection-20261019/fresh-a1/expected.json \
  --report private/NEW.json
```

Use a new private audit/report path. For unchanged getter regression, use
`tests/compare_building_image.py`, `build/native/building-image-vectors` and
`private/building-image-20261019/fresh-a1/expected.json`. Use sanitizer runners
from `build/sanitize/` for the same explicit-reuse commands. Rebuild with
`env DEVELOPER_DIR="${DEVELOPER_DIR:-/Library/Developer/CommandLineTools}" build/tools-env/bin/cmake --build build/sanitize --parallel 6`,
then run its CTests and actual-owner check. Fresh generation uses a new
`--output private/NEW` instead of `--expectations/--report`; Unicorn remains
research/test-only. No unchanged original matrix needs regeneration here.

Try the current GI scene with `./run.command --boot-camp-walk`; it continues to
use the existing approximate Building presentation. This dispatcher is an
explicit dependency seam and does not enable new pixels or objective success.
The next work is actual Cell10A lookup and complete entered6D1510 on these same
owners, followed by remaining frame children before production scheduling.

## Validation and measured costs

Normal/sanitizer each pass639 selection +614 unchanged getter replays with1,253
hits/zero misses,212/211 CTests, actual-owner checks and12 focused Python guards.
The existing SDL256tick interaction regression passes; its horizontal captures
are byte-identical to the preceding inspected frames. This preserves existing
GI presentation coverage without claiming Building pixels. Local validation is
not independent acceptance. Evidence and hashes:
`private/building-image-selection-receipt-a1.json`.

Original generation took.251s. Final native build34.52s; sanitizer build32.64s
and final up-to-date confirmation9.62s. Final normal owner4.65s, sanitizer76.14s,
normal test.command3.48s, sanitizer CTests17.04s and SDL5.97s. Concurrent costs
are nonadditive. Early compile failed because the Type accessor was const-only;
a mutable exact-identity accessor fixes that without creating another owner. A
launch attempted before the new runner existed performed no original execution.
Pre-final-build normal checks were repeated after build completion. Those attempts
and unavailable repair/manual-inspection/total-turn costs are retained in the
private receipt. No original/native comparison mismatch occurred.
