# Building discovery override — supplied base target

Objective-structure discovery now calls the actual Building override around the
existing common discovery algorithm. This corrects a previously omitted wrapper;
it does not enable live sight, arrival scheduling or Boot Camp Objective1.

## Identity and recovered behavior

Target: `private/official-1006-probe/game.exe`, 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Original instructions are unmodified.

The exact Building vtable `79CBBC` selects `180 ->448FE0`, distinct from the
Infantry common discovery entry. `tools/verify_building_discovery.py` pins this
association, Mission getter/queue and activation slots, complete wrapper bytes
`448FE0..4490AE` and complete radio predicate `636F10..636F35` (ends exclusive).

The wrapper calls complete common `6C2440` first and returns false immediately
on rejection. On success, it reads loadingA40774. When zero, it saves Owner,
reads BuildingTypeB90 and writes saved Owner1B4, then rereads Owner and writes
Owner18D=1. It always rereads Owner for Owner144=1. It calls the complete radio
predicate, then conditionally reads live House control, current-or-queued Mission
and the separate queuedA0 word. Its alternate branch calls radio again and may
read House control again. Preserve these duplicate queries and both Mission18
gates; an uncontrolled Owner equal to discoverer has a distinct activation path.

Radio636F10 saves signed actorD0 once. Nonpositive counts return false without
reading actorCC; positive counts scan dwords in order and return on the first
nonnull identity without dereferencing it. Native storage exhaustion refuses only
when the missing element would actually be read. An early nonnull entry can
accept even when the supplied count exceeds the bound span.

`discoverBuilding` reuses `discoverUnit`; no common algorithm was duplicated.
House Building fields follow the six existing aggregate fields, preserving old
fixture initialization. Complete common Techno/Object/House/Mission/QueueMission
execute in the same original guest. Optional Tag effects and Building activation
`4426D0` remain explicitly supplied leaves in diagnostic cases. The production
adapter has no activation callback: entering that child refuses.

## Production ownership and supplied boundaries

`BootCampMissionWorld` now calls the wrapper for its two objective structures,
retaining persistent House addresses and actual common discovery state. Each
structure owns a supplied empty radio vector/count and a supplied typeB90 value
from its numeric rules `[BuildingTypes]` declaration. Original type registry/INI
startup and original Building construction/foundation/radio initialization are
not recovered by this association. Do not call that numeric key a verified
original runtime registry index. Missing/duplicate type associations refuse.
The bounded neutral-owner/player-discoverer path does not enter activation.

The owner check verifies the expected House1B4/18D/144 writes after the existing
Tag/mission composition. House snapshots and initialized-preview guards now
include those fields; they cannot silently reconstruct changed House state as
cold. This remains initialized-only discarded preview coverage, not general warm
cloning. Shared visibility/movement resident lists and actual Building coordinate
virtual `444080` still need their own recovery/integration. No dummy Walk or
Drive record is added for a Building.

## Evidence and validation

Canonical original expectations:
`private/boot-camp-20261018/building-discovery-fresh-a2/expected.json`, SHA256
`69f6b2b4c8d5a9e4da096994d35f70d9042a3886632409ad897a6cb10d7bc405`.
816 sequences contain3,984 complete Building roots,2,944 actual radio calls and
290 explicitly supplied activation calls. Cases cover loading, repeated current/
other/null discovery, raw discovered bytes, mode/control, current/queued Mission18,
negative/zero/empty/all-null/early/late radio links, extreme type values and a
supplied Tag callback that changes Owner before the wrapper's late reads.
Ordered actor/House writes and final fields match native. Complete caller stack,
callee-saved registers, instructions/inputs and unselected arenas are guarded.

Normal/sanitizer/uncached-inspection replays pass816/816 with zero misses.
Reports: `building-discovery-{native,sanitize,uncached}-a1.json` under that folder.
The old common driver's combined source identity required a fresh884-result
receipt at `building-common-fresh-a1/`; commands/labels/outputs exactly match
`shared-visibility-discovery-fresh-a1/`. Neither original receipt was relabelled.
Normal/sanitizer/uncached common replays pass. Both rebuilt runners also retain
360 position-discovery and80 joined position/sight outputs using unchanged
original expectations. No whole-inventory refresh or closed finalizer ran.

Full normal/sanitizer builds pass;115 normal CTests,114 sanitizer CTests and
1,351 Python tests pass. Both private-data owner checks pass, retaining Process26/
52 discovery1/0 and position queries3/2 with source isolation. Actual106-tick SDL
input/drawing/pause/refusal/Stop/repeated-order/deselection acceptance is at
`building-sdl-a1/`; arrival drawing was visually inspected. It retains
`objectives_enabled:false` and `original_fidelity_from_this_smoke:false`.
Local source/runner/log hashes are recorded in `building-owner-receipt-a1.json`.
The sanitizer configuration is headless; SDL acceptance uses the normal app.
These are local checks, not independent acceptance or original-game observations.

Fresh finalized Building generation took4.772s; full driver6.221s, comparison
0.041s. Normal/sanitizer/uncached replay drivers took0.312/0.584/2.004s,
comparisons0.021/0.255/0.029s. CTest took1.02s normal/5.41s sanitizer;
Python37.716s. Build/host approval/
SDL/manual repair wall costs were not separately measured. The first successful
Building receipt a1 predates the finalized frozen-type input guard and driver
cleanup; a2 is canonical. An explicit py_compile attempt hit the host cache
sandbox, and Pillow was unavailable; checks ran with `-B` and the SDL PPM was
converted using existing `sips`. No dependencies/system settings were changed.

## Reproduce and next capability

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
./test.command
build/native/boot-camp-walk-check private/official-1006-probe
build/sanitize/boot-camp-walk-check private/official-1006-probe

env PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/building-next.audit.json \
  tests/compare_building_discovery.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/building-discovery-vectors \
  --expectations private/boot-camp-20261018/building-discovery-fresh-a2/expected.json \
  --report private/building-next.json

./run.command --boot-camp-walk
```

Use a fresh audit/report path. Select the sanitizer runner, or put `--uncached`
before the driver for inspection control. Fresh original execution uses
`--output private/NEW-DIRECTORY` instead of expectations/report and requires
private Unicorn JIT permission. Keep all identity/runner/input/receipt guards.

Next recover Building coordinate dispatch, then join visibility resident heads/
Next with actual mutable membership without widening Infantry admission. Complete
warm/discarded ownership, required entered effects and ordinary SDL discovery
must precede live scheduling. Mission requests still do not implement text/audio/
reveal/alliance/team effects; Objective1 and both full games remain incomplete.
No public/YR/recomp code, dependencies or runtime executable reads were added.
