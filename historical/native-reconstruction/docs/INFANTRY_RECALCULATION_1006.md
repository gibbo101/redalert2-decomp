# GI movement recalculation on the actual Boot Camp map

This removes a supplied callback used by ordinary Day1 GI Mark/removal/insertion.
`BootCampWalkWorld` now calls `PreparedInfantryMembership::recalculate` on the
Cell identity reloaded by the existing membership parent, after list/notification
work. It composes the existing complete472540/LAT/resource/permission chain with
occupied478F40 and updates the existing four-/ten-byte map buffers. There is no
second terrain map, Cell list, actor owner or movement algorithm. Initial Mark
uses the same binding; warm clones rebuild callbacks against their own owners.
This advances the movement effects needed before production sight/discovery can
be scheduled. It does not activate sight or complete an objective.

## Original behavior and scope

The supplied executable was fingerprinted before inspecting addresses:4,485,392
bytes, SHA256 `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Complete478F40 compares the resident kind
only against Building6 and Terrain36 before following Object+30. Actual Infantry
vtable7A3540 slot2C dispatches complete509800, returning15. Infantry therefore
continues through the primary list without reading Building/type/House/mission
fields. Existing Unit/Building/Terrain behavior, intermediate stores and permission/
overlay/land/speed early exits are retained. Alternate lists remain unvisited.

`verify_infantry_passability.py` pins the dispatch, complete kind leaf and exact
default branch in addition to the existing complete parent inspection.
160 new original sequences cover one-to-eight Infantry, mixed Unit/Building/
Terrain order, raw type bytes, permission, overlay and float32 speed gates.
The original fixture executes the actual parent and kind leaves, audits ABI,
allowed blocks/stores, unchanged arenas and immutable inputs. Current normal/
ASan+UBSan runners match ordered kind queries and passability assignments.
Initial actor/type/House/Cell/scenario/geometry/speed records remain supplied.
This is not an original full Boot Camp Process/Mark/recalculation composition or
an original animation/frame proof. Existing complete parent/child proofs retain
their individual scopes; native composition alone does not enlarge them.

The actual Infantry adapter refuses an encountered non-Infantry resident rather
than inventing its type/House inputs. The shared low-level passability kernel
still supports verified Unit/Building/Terrain records. Permission/overlay early
exits can bypass an otherwise unsupported list, as in the original. Mixed-list
native tests and safety refusals are distinct from original fault emulation.
The temporary per-call passability views read current actual head/Next/kind fields;
they do not own persistent gameplay state. Existing unrecovered animation/tube/
shadow-casting recalculation branches keep their guards.

## Reuse and validation

Original-only160-case provenance is immutable at:
`private/boot-camp-20261020/infantry-passability-fresh-a1/expected.json`.
Normal/sanitizer replays explicitly select that source, report160 hits/zero
misses and run current native. No native result/pass-fail is cached. Both profiles also explicitly reuse285
unchanged Infantry membership sequences/501 roots with current rebuilt runners,
zero misses; that fixture retains its supplied recalculation callback and proves
only its original membership scope. Total1,229 hits/profile across these three
separate scopes, not a combined original interaction proof.

The existing `compare_membership_current.py` adds only the resident-Cell family
needed here. It validates the old receipt against its actual mixed identity,
checks original inspection and all listed nonnative source identities separately,
then compares all784 unchanged resident-Cell results against each rebuilt runner.
The old strict comparator/origin is unchanged. Both replays report784 hits/zero
misses, with current C++/runner hashes separate. It has no native input producer.
Its new malformed-input check and original-source/native-source separation are
covered by Python tests. The older occupied-cell-v2 proof is preserved at its
historical scope: a listed original Python dependency has changed, so it was
not silently relabeled or regenerated. The new160 cases establish the required
Infantry branch independently.

`prepared-infantry-membership-check` verifies live head/Next, passability-before-
observer, selected buffer bytes/tails, permission short-circuit, cyclic-list/
unbound-kind refusal, fallback return and warm clone isolation. The actual
Boot Camp eight-direction check salts departure/destination buffer bytes after
command admission: real movement must replace them with actual Cell passability/
level values. Existing Stop/repeated orders/refusal/other-actor/clone tests remain.
Normal/sanitizer checks pass. Broad201 normal/200 sanitizer CTests and
`./test.command` pass; the later stronger owner assertions are rerun in both
profiles. Twelve focused Python tests pass. Local verification is not independent
acceptance.

Actual SDL selection/move/pause/retarget-refusal/Stop/repeated-order/deselection
and horizontal right/left drawing pass256ticks. Both captured moving frames were
visually inspected. Evidence stays private at
`private/boot-camp-20261020/infantry-recalc-sdl-a1/`.
Startup visibility is still supplied until the existing visibility owner exists;
notify/special-event/redraw/arrival/animation callbacks retain their boundaries.
Runtime sight, ordinary Objective1 and both full games remain incomplete.

Original generation.130s; fresh outer audit1.235s. Normal/sanitizer160-case native
comparisons.011/.439s;784-case comparisons.046/2.008s. Broad CTest2.50/15.53s;
focused Python.149s. Build/config/owner/SDL/inspection/edit/repair/total wall costs
were not instrumented. Concurrent costs are not additive. One initial compilation
failed because fixed-extent spans require explicit construction; repaired before
owner/SDL acceptance. No failing comparison was accepted. Exact identities/logs/
measurements are in `private/boot-camp-20261020/infantry-recalc-receipt-a1.json`.
No public code/dependency, new runtime executable read, worker, Windows action,
transfer, download, system/Xcode/DRM change or proprietary tracked file was added.
Only Apple Silicon macOS is tested.

## Reproduce and continue

```sh
./build.command
./test.command
./run.command --boot-camp-walk
build/native/prepared-infantry-membership-check
build/native/boot-camp-walk-check private/official-1006-probe
build/sanitize/prepared-infantry-membership-check
build/sanitize/boot-camp-walk-check private/official-1006-probe

# Use new report/audit destinations. This explicitly reuses original answers.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
 tools/run_evidence.py --audit private/infantry-passability-next.audit.json \
 tests/compare_infantry_passability.py \
 --exe private/official-1006-probe/game.exe \
 --native build/native/occupied-cell-vectors \
 --expectations private/boot-camp-20261020/infantry-passability-fresh-a1/expected.json \
 --report private/infantry-passability-next.json
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
 tools/run_evidence.py --audit private/infantry-recalc-resident-next.audit.json \
 tests/compare_membership_current.py --family resident \
 --exe private/official-1006-probe/game.exe \
 --native build/native/resident-cell-vectors \
 --expectations private/map-depth-1006/resident-cell-v2/expected.json \
 --report private/infantry-recalc-resident-next.json
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
 tools/run_evidence.py --audit private/infantry-recalc-membership-next.audit.json \
 tests/compare_infantry_membership.py \
 --exe private/official-1006-probe/game.exe \
 --native build/native/infantry-membership-vectors \
 --render-data private/derived/ra2-1006/render-data.bin \
 --expectations private/infantry-walk-20261018/membership-fresh-a2/expected.json \
 --report private/infantry-recalc-membership-next.json
# Substitute build/sanitize runners and distinct report/audit destinations.
# Fresh SDL smoke requires a new private destination and display access:
./run.command --boot-camp-walk-smoke-test private/infantry-recalc-sdl-next
```

Next establish membership's real visibility-gate/notification-argument association
and bind recovered Infantry discovery6C2440 on the same mission/House/actor owners;
finish other actually entered movement effects before live arrival/crossing sight.
Do not convert arrival or a recorded request into synthetic discovery/objective
success. Viewport/queue consumption and required mission children still precede
ordinary SDL Objective1, then Day1's remaining lessons/completion and Day2.
