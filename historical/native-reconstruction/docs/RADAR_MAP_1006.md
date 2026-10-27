# Shared terrain floor and radar discovery

`RadarMapBinding` composes complete55A280/4706C0 floor height with both complete
568140/568280 discovery queries below632000 and its nonzero634030 caller.
Actual stock surface reads/writes/locks remain joined. The binding borrows one
canonical `MapFloorHeightWorld` table/fallback, the actual `MapCellInput` position,
level, ramp and flags140, separate flags12C/count13C references, and one shared
lazy floor cache. It owns only callbacks; there is no second Cell table or
persistent terrain/visibility mirror. It remains unwired to gameplay.

The subsequent actor composition corrected an association error in this initial
binding: `MapCellInput::flags` is Cell140, not12C (see the selected constructor
projection in `original_map_cell_inputs.py`). Its original synthetic consumed-field
proof passed, but that did not establish the intended production field binding.
The current API borrows12C separately and takes140 from terrain, with a regression
that deliberately makes them disagree. The later actor receipt records rebuilt
old-domain replays and a fresh complete composed proof; the earlier receipt remains
historical. No runtime adopted the incorrect association.

## Evidence boundary

The supplied executable is4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity stay distinct. `verify_radar_map_pixels.py` reuses complete
range/constant checks for floor, discovery, pixel/caller and stock surface
children. No original instruction is patched. No original code is executed in
the application; Unicorn is research/test-only.

Floor55A280 uses full signed X/Y division by256 followed by a wrapped combined
index and the live map table count. The binding requires the complete262144-slot
world used by discovery. Discovery separately projects signed height and word
coordinates before combined indexing. Neither is replaced by the other's lookup.
Both immediately update the same canonical fallback position. A pure field view
provides independent flags12C/count13C from the selected Cell owner; flags140
comes directly from its actual terrain record. Neighbor3 uses the selected
stored point, including a preceding fallback write, with word wrapping.

Actual floor height retains signed level multiplication/wrapping, low coordinate
bytes, finite ramp arithmetic,53-bit/toward-zero FP behavior and the independent
height/scale/plane lazy bits. The same cache is reused across every pixel in a
complete refresh. Live level-height changes do not reset cached height/scale/
planes; discovery's divisor is a separate owner and is never aliased to it.
The original parent stores the floor result as Z before its independent discovery
mode reads. Diagnostic mutations at named boundaries remain explicit supplied
effects; they are not original-game observations.

Construction validates only table/fallback/service associations, makes no map,
floor or borrowed-field queries, and warms no lazy state. Previous floor and
both discovery callbacks restore on scope exit, including faults. Owners and
the binding must remain alive and immovable for the scope. Unsupported ramps,
nonfinite cache states and invalid discovery division retain existing refusals.
No new safety guard is represented as original crash emulation.

## Verification

The fresh composed corpus contains2,619 sequences: all2,409 prior parent scenario
inputs extended with actual floor state, plus210 full refresh cases covering all
21 ramps and independent/upper lazy flags. Supplied initial level/ramp records,
finite template state, height globals and scheduled live-height changes exercise
negative levels, wrapping, warm reuse and distinct Cells/fallback. Pixel hashes,
ordered logical traces, both discovery results, final canonical fallback and
bitwise serialized lazy state are compared against isolated original execution.

The original harness checks all entered instruction ranges, allowed writes,
immutable table/inputs, caller stack/return/callee-saved registers, entire private
Cell arenas and fallback bytes outside the selected coordinate store. Lazy
writes are counted and width/range checked; native initializer store order and
all native machine reads/writes are not asserted. Initial allocation, Cell/global
associations, direction3 and cache template remain supplied, not recovered startup.

The old floor and parent families are replayed only after their source/receipt
identities pass. Normal, sanitizer and uncached controls retain explicit rebuilt
runner identities. Inspection reuse does not cache original execution or native
results. No historical complete inventory or closed finalizer is rerun.

All2,619 fresh sequences match, including1,230 complete634030 callers,15,764
actual55A280/4706C0 calls,30,100 discovery calls,3,000 neighbor/word lookups,
12,138 pixel reads,15,764 writes and234,027 audited lazy stores. Twenty-three
Python checks, five domain CTests per build and15 normal/sanitizer/uncached
family replays pass. The unchanged4,279-sequence floor expectations retain their
original identity; old parent expectations retain their own unchanged identities.
Fresh original generation53.709s/native comparison.255s; final configurations
9.503/8.309s and builds6.483/6.341s. Earlier builds, preflight and individual
checks/replays have private timings; task/repair wall and unrecorded inspections
are unavailable. No build, original or comparison failure occurred. The first
build invocation duplicated the new target; final A2 explicitly rebuilt the old
discovery runner too, before original proof and guarded replays.

Current exact receipts, results and timings are recorded in the opening handoff
and `private/boot-camp-20261019/radar-map-receipt-a1.json`. All proprietary inputs,
outputs, audits and receipts remain ignored. Local verification is not independent
acceptance, a whole-frame fidelity claim or a new playable capability.

## Remaining integration

The application and SDL owner binaries retain their prior106-tick walking
baseline; this change has no runtime/GUI adoption or rerun. House/local/alliance,
type, actor C0/CC, scheme resolver and other initial records remain supplied in
this composition. Next bind those already recovered services to shared actor/
House/registry owners. Stock count producers/surface startup/coverage/redraw/
power and production warm/scan remain open. Diplomacy/action37, ordinary SDL
Boot Camp Objective1, base RA2 and Yuri's Revenge remain incomplete.

No worker, Windows action/transfer, download, DRM/system change, public code or
new dependency was introduced. No runtime executable read was added. Existing
pinned public references remain hypotheses; no upstream/generated/lifted code
or proprietary table was incorporated. Native cache initialization reuses the
existing authored geometric construction; no new THIRD_PARTY notice is needed.

## Commands

```sh
./build.command
./test.command
./run.command --boot-camp-walk
# The new composition remains a separate recovery profile.
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake \
  --build build/native --target radar-map-pixels-vectors
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/boot-camp-20261019/radar-map-replay-new.audit.json \
  tests/compare_radar_map_pixels.py --exe private/official-1006-probe/game.exe \
  --native build/native/radar-map-pixels-vectors \
  --expectations private/boot-camp-20261019/radar-map-pixels-fresh-a1/expected.json \
  --report private/boot-camp-20261019/radar-map-replay-new.json
```

Use new destinations. For fresh original execution, replace `--expectations` and
`--report` with `--output private/boot-camp-20261019/NEW`; original execution needs
host JIT permission. Sanitizer replay uses `build/sanitize/radar-map-pixels-vectors`;
`--uncached` before the comparison script disables inspection reuse. The private
checks record retains every exact affected-family command and elapsed time.
