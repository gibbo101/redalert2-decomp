# Supplied RA2 1.006 ordinary Unit base depth on prepared Cells

October 15, 2026, after `352beef`. **131 fresh original/native scenarios /
9,561 base-depth queries** match after actual shared map/floor finalization.
Actual Cell lookup and TMP dimension/image getters replace the earlier zero-size
service in this new D profile. Earlier Foot/world/G/F profiles keep their stated
boundaries. The new helper is not wired into gameplay; runtime depth remains
neutral pending complete Foot/Unit drawing and actor-height association.

## Identity and reference hypothesis

Supplied engine: 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`, in
`private/official-1006-probe/game.exe`; the approved Windows private copy at
`private/windows-baseline-20261014/game.exe` has the same identity. Embedded
1.08, supplied 1.006 patch lineage and reported no-CD changes remain separate
provenance; pristine authenticity is unverified. No Windows/transfer/source-install/
system action, worker or new dependency was introduced. Runtime never executes
original code or reads additional executable tables for this helper.

Consulted [REFERENCES.md](REFERENCES.md), pinned YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` `TechnoClass.h`
GetZAdjustment, `FootClass.h`, `ObjectClass.h` height declarations and the earlier
Cell/TMP leads. Hypothesis: ordinary base depth uses absolute height, heading-
selected Cell ramps/flags/overlays and real TMP size before Foot's type adjustment.
Exact base instructions/execution determine the result. YR names remain leads;
recomp `eebcf725ef99f942a8f9a5e0437a8a6154d7d439` `docs/voxels.md` is surrounding
context, not an oracle. Existing MIT/generated-code exclusion, stale license text
and YRpp no-license notes apply. No upstream/header/generated/lifted code or
extracted table was incorporated; THIRD_PARTY.md and existing notices are unchanged.

## Recovered decisions

[UnitBaseDepth.cpp](../src/render/UnitBaseDepth.cpp) projects the **kind-1,
nonharvester, special-state-zero Unit branch** of complete root
`0x6CFEA0..0x6D050C`. Original Unit height/coordinate/kind slots, Facing current,
height-pixel/FTOL, actual map lookup and resident TMP getter/dimensions execute.
[verify_unit_base_depth.py](../tools/verify_unit_base_depth.py) combines
48 allowed complete ranges / 4,327 inspected instructions; **41 ranges / 4,025
instructions enter** in the new suite. Alternate Unit/contact/harvester paths,
null map-pointer returns and actor construction remain outside the profile.

Preserve these ordered decisions:

1. Convert signed **absolute Z** to pixels with the supplied scale; signed Z>=728
   adds one before +0.5 and qword FTOL/low-dword return. Negate with 32-bit wrap.
   Query word map coordinates only afterward: full signed division by 256 toward
   zero, then word truncation.
2. If the current Cell has a ramp, fetch south, east and southeast before checking
   their overlays. The **first occupied overlay gates later ones**, even when it
   is not rock. A rock returns base + supplied rock adjustment - 1.
3. Read Facing six times and fetch neighbors in offsets **+1,-1,0,-4,+3,-3**
   from its rounded eight-direction bin. Any neighbor ramp selects the neighbor
   adjustment; otherwise the current ramp selects the current-ramp adjustment.
4. Preserve repeated Facing queries and cardinal selection of one three-Cell
   group. A current or selected Cell flag `0x10000` suppresses dimensions.
5. For each selected Cell, tiles **255 and 65535** select the supplied default tile
   with subtile zero. Otherwise use the actual tile and subtile byte. Run actual
   TMP dimensions, including extra-Y correction and signed wrapping. First output
   height **strictly above 36** returns base-2; otherwise finish at base-1.

Initial adjustment globals are -1/-1/3. Tests also supply distinctive -7/9/23
values to distinguish equal-valued stock exits; this is diagnostic input, not
stock configuration. Scale, absolute actor Z, Facing/tick, default tile and actor/
type records remain supplied. Native FP scopes restore host rounding; strict
compilation preserves 53-bit/toward-zero arithmetic. Full signed height and word
coordinate boundaries are compared; no alternative fixed-point model was imposed.

The original ignores a false TMP dimension return. A missing image leaves the
height output unchanged. Its local scratch word is not initialized by this root:
the test caller explicitly seeds it. Native `dimensionHeight` models that
supplied initial value and retains a preceding successful output across later
misses. This does not establish an original startup/caller value for the slot.
Do not replace it with a zero-height fallback or promote ambiguous missing-image
profiles into gameplay. Native binding/finite-scale/tile-index refusals are safety
guards, not original malformed-input parity.

## Shared preparation and evidence

The D profile first executes the actual F parent on the same mutable Cell/slot/
fallback/type/image/overlay records, then calls the actual base root repeatedly.
The native runner also finalizes its own shared records before depth queries;
there is no original-to-native final-state transfer. Historical F/G receipts
provide **scenario inputs only**. Resource initialization, decoded streams,
initial terrain/type/geometry/table records and original startup order retain
their earlier supplied/separate-phase boundaries.

`private/map-depth-1006/unit-base-depth-v1/` contains 32 inherited shared maps,
three owned-input maps and 96 synthetic maps. Owned maps include all 13,515
positions / 660 overlays under each cliff mode and queries at parked `(51,72)`,
elevation 4. Synthetic queries cover all heading bins, interpolated Facing,
signed timer/height/coordinate edges, ramps, overlay priority, flags, dimension
thresholds, extra heights, default tiles and missing images.

Counts: **9,693 audited calls** including 131 parents and direction initialization,
9,561 actual base/height/coordinate/kind/pixel entries each, **73,397 actual
Facing queries**, **4,529 base-phase TMP dimension calls**, 474 parent floor calls
and 47,585 actual resource/Cell/passability/permission/light entries each. Compare
the parent state/buffers/cursor/ordered trace hashes, then depth, retained scratch,
fallback position and cumulative ordered query/store digest after every query.
Original instructions are unchanged; actor/type/Cells/slot/type/image/overlay/
global inputs, caller ESP/return/registers/stack and permitted writes are guarded.
Fallback coordinates may change; its other bytes remain unchanged. Complete read
order and original heap ownership are not claimed.

The focused private `unit-base-depth-branches.py` audit records individual ordinary
exits and compares original/native/sanitizer outputs. The closing handoff records
its result, both main replays, affected earlier evidence, test counts and timings.
This is local verification, not independent acceptance or whole-frame parity.

## Reproduce and continue

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

# Use an unused private destination; original execution needs Mac host JIT.
build/tools-env/bin/python tests/compare_unit_base_depth.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/unit-base-depth-new
build/tools-env/bin/python tests/compare_unit_base_depth.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/unit-base-depth-v1/expected.json \
  --report private/map-depth-1006/unit-base-depth-v1/replay-new.json
build/tools-env/bin/python tests/compare_unit_base_depth.py \
  --exe private/official-1006-probe/game.exe \
  --native build/sanitize/resident-map-finalization-vectors \
  --expectations private/map-depth-1006/unit-base-depth-v1/expected.json \
  --report private/map-depth-1006/unit-base-depth-v1/sanitize-new.json

# Existing playable baseline; this does not use the new helper.
./run.command --crossing-light-demo
```

Next bind this actual prepared-map base result through Foot's predicates/type
adjustments and complete Unit/world drawing, and recover the required floor-to-
actor absolute/relative-height associations. Current test Z is supplied, not an
original placement/update result. Initial actor/type/occupant/tag/bridge state,
full startup/ownership/cache/visibility/pathfinding/scheduling remain open. Actual
SDL level crossing and parked cliff remain acceptance scenarios before runtime
depth promotion. Only Apple Silicon macOS is tested. Full base RA2 then Yuri's
Revenge remain incomplete and active.
