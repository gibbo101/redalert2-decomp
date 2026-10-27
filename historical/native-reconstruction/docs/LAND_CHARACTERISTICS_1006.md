# Supplied RA2 1.006 land-characteristic assignment

October 15, 2026, after `9f10723`. This recovers the land-speed/Buildable
assignment parent needed by ordinary Cell passability preparation. It is unwired;
the playable renderer and neutral Foot inputs are unchanged. This is a prerequisite
of the same terrain-aware crossing/cliff capability, not a new playable milestone.

## Identity, references and boundary

Exact supplied engine: `private/official-1006-probe/game.exe`, 4,485,392 bytes,
SHA256 `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
The approved private Windows copy has the same identity. Embedded 1.08, supplied
1.006 lineage and reported no-CD modifications remain separate provenance;
pristine authenticity is unverified. No Windows action, transfer, executable
modification, source-install or system change occurred.

Consulted [REFERENCES.md](REFERENCES.md), pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` `docs/voxels.md`/LICENSE and YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` `RulesClass.h`
(`Read_LandCharacteristics`) and `GeneralDefinitions.h` (`LandType`, `SpeedType`).
Hypothesis: original rules loading supplies the per-land float32 speeds consumed
by ordinary Cell passability. Exact base calls, pushed key strings and table
stores establish the mapping; YR offsets do not. Recomp is no original-behavior
oracle. No upstream/header/generated/lifted code or binary table was incorporated;
existing license boundaries and THIRD_PARTY notices remain sufficient.

`verify_land_characteristics.py` pins the complete base parent
**`0x64D610..0x64D847`, 568 bytes / 178 instructions**, its twelve section names,
key associations and upper-bound constant. The complete parent executes unchanged.
Section presence `0x50C9B0`, double INI results `0x50E3A0`, boolean INI results
`0x50F410` and initial table records are explicit services/fixtures. The double
return service supplies x87 registers directly; it does not execute or claim
original numeric text parsing. The root's return address, ESP, callee-saved
registers, immutable inputs, table padding/tail, selected ordered stores, FPCW
and final empty x87 stack are guarded. Services check receiver, caller and defaults.

[LandCharacteristics.cpp](../src/assets/LandCharacteristics.cpp) is SDL-free and
lives in assets. It accepts supplied INI callbacks and initial records. Original
static initialization, actual parser, rules layering, whole startup/pathfinding,
allocation/lifetime and runtime association remain open. Missing native callbacks
are refused before any calls/stores; that is a safety guard, not original failure
behavior. The native function returns void; the original parent always returns
low-byte one in this tested boundary.

## Preserved decisions

Visit Clear, Road, Water, Rock, Wall, Tiberium, Beach, Rough, Ice, Railroad, Tunnel
and Weeds in that order. An absent section preserves its entire incoming record,
including Winged and Buildable. The original uses twelve **36-byte** records at
`0x850EA0`; native storage models fields, not padding or original global ownership.

For a present section, process Hover, Foot, Track, Wheel, then force Winged to
float32 one, then process Float, Amphibious and FloatBeach, then Buildable. Each
numeric read uses default double one. If the first value is less than one **or
unordered**, read the same key again and store that second result without another
comparison. Otherwise store one. Preserve duplicate callback consumption and
interleaved stores; caching the first read or using a generic min operation changes
the behavior. No lower clamp is imposed. Buildable uses default zero and stores
the returned low byte; synthetic noncanonical service bytes are not original
GetBool parser evidence.

The parent does not set FP rounding. Strict native compilation preserves the
supplied caller mode for the double-to-float32 store and leaves it unchanged.
Tests supply all four rounding modes with 53-bit x87 precision. They do not
establish the startup caller's actual FP mode or all x87 precision/exception-state
behavior. Signed zero, subnormals, overflow, infinities and quiet NaNs are covered;
30 consumed double patterns occur in every tested mode. Native fixture code
restores its host FP mode separately from the production helper.

The actual passability loads in [MAP_CELL_CHILDREN_1006.md](MAP_CELL_CHILDREN_1006.md)
read `0x850EA8 + land*36`: this loader associates that offset with **Wheel**,
not Foot. The existing child suite's eleven supplied scalar speeds describe that
column. Future native binding must select it from these records. The twelfth
record is still assigned here; it does not expand the child suite's land domain.

## Evidence and reproduction

**196 fresh original/native results**, plus normal and ASan/UBSan replays:
128 seeded shared-table cases, 64 focused numeric/rounding/presence cases, and
four supplied owned-rules projections, one per mode. Owned INI values are decoded
by a host fixture reader; original parser equivalence is unclaimed. All selected
final fields and complete ordered INI-request/store events match as SHA256 digests.
Counts: 196 audited actual parents, 26,125 supplied INI calls and 15,921 original
table stores. Initial record bits, missing sections, noncanonical presence values,
unchanged padding/tails, changed second reads and all four rounding modes are covered.

Current receipts: `private/map-depth-1006/land-v2/{expected,report}.json`,
`native-replay.json`, `sanitize-replay.json`. v1 remains historical after added
service-return/x87-stack guards; v2 was freshly executed, and its commands/results
are identical. Engine, inspection, relevant source, rules and runner fingerprints
are checked before/after runs. Eight Python evidence guards and one native service
guard target are included.

```sh
./build.command
build/tools-env/bin/ctest --test-dir build/native --output-on-failure
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
# Use README's sanitizer configuration, then:
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

# Fresh original execution requires the authorized Mac host JIT context.
# Choose an unused private destination.
build/tools-env/bin/python tests/compare_land_characteristics.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/land-new
build/tools-env/bin/python tests/compare_land_characteristics.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/land-v2/expected.json \
  --report private/map-depth-1006/land-v2/replay-new.json
# Add --native build/sanitize/land-characteristic-vectors for sanitizer replay.

# Unchanged playable scenario:
./run.command --crossing-light-demo
# Select Rhino; G/right-click moves, L toggles light, R resets.
```

Both builds, **477 Python tests**, **28 normal / 27 sanitizer CTests**, source/
diff/local-link audits pass. Adding the new target relinked earlier runners.
Twenty earlier source sets replay retained expectations on current runners. The
map fixture decoder also changed identity: its dependent tile-sweep/map-preparation
receipts correctly rejected reuse. Fresh **sweep-v3 (129)** and
**map-preparation-v2 (65)** results and both replays replace their current evidence;
their commands/results equal the historical sets, which remain untouched. This
is fresh decoder-bound evidence, not relabeling or weakened guards. Current prior
coverage consists of 24 source/runner sets; the private retention ledger identifies
the twenty retained and four refreshed normal/sanitizer receipts separately.

No runtime change/new SDL playtest for this unwired input helper. Only Apple
Silicon macOS is tested; local verification is not independent acceptance. The
initial whole-rules fixture read rejected non-INI narrative lines; permitting
valueless host entries corrected fixture preparation. A linear exploratory xref
scan also stopped early at embedded data and was repeated with skip-data enabled;
aligned complete-root inspection, not that scan, establishes the routine. Pilot
and completed numeric evidence have no original/native mismatch. Private land
start/attempts/verification/closing records retain timings, the fixture refusal,
receipt guard refusal, fresh refreshes and inherited/unavailable active-delivery
measurement. No worker, evidence cache or gameplay repair.

Fresh land driver/original/native: **1.514/1.174/0.069 s** (CLI 1.648 s).
Normal/sanitizer replay CLI: **0.493/0.883 s**. Initial/final normal build:
8.697/7.975 s; sanitizer 12.871 s. CTest CLI normal/sanitizer: 1.287/2.705 s;
Python CLI 1.710 s (477 tests, 0.530 s). The prior-runner audit/replays took
130.570 s through the expected decoder refusal, including twenty completed
replays. Fresh sweep/map-preparation CLI: 6.365/10.267 s. Overlapping checks and
the current refreshed replays are recorded separately in the private timing logs;
these numbers are not original-game performance measurements.

## Next capability dependency

Retain the ordinary Cell parent and loaded tile/type/variant evidence. Verify
remaining relevant startup/constructor/branch inputs, including usage reset and
initial state, and bind this Wheel column without assuming original INI parsing.
Bridge parent inspection shows connection-record work; zone construction is
deferred pathfinding unless an actual drawing input dependency is established.
Do not promote neutral fields by inferring effects from inspected callers.
Then join prepared Cell fields to Foot depth and retained Unit/world drawing,
followed by actual SDL level crossing and parked cliff `(51,72)`, elevation 4.
Contact/map/actor/heap/cache lifetime, scheduling/camera/fog/UI and whole-frame
parity remain open. Full base RA2, then YR, remains active and incomplete.
