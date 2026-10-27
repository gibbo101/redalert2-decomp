# Original Infantry speed joined to queued walking

`infantrySpeed` replaces the supplied per-tick speed in a separate complete
queued Walk diagnostic. It borrows the same percentage written by preparation/
arrival and keeps the existing admission, head, interpolation and Stop kernels.
This unblocks the speed dependency of Boot Camp Day 1 walking. **The preview is
still static; production GI movement and objective progression are not delivered.**

## Recovered behavior and evidence boundaries

The exact supplied executable was rehashed before address use:4,485,392 bytes,
SHA256 `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. All inspections/receipts stay ignored in
`private/infantry-walk-20261018/`. No public/header/generated/lifted code, new
extracted data, dependency or application executable read was incorporated.

Complete original Infantry508980 and Foot4C9B10 execute unchanged, with actual
type6C12C0/506950, base-speed6D8E90, House4F5A20, promotion6D7910/7133A0/713420
and conversion77F110 children. Base RTTI and dispatch independently identify
InfantryType vtable7A3A78 and kind16 (50AF60), selecting country float+128.
Infantry body kind15 (509800) skips the Unit-only5B4 half-speed branch. This is
an Infantry API; it does not generalize that body/type assumption to other actors.

The readable portable algorithm preserves:

- Query type, save House/country float as double, query base speed through type
  again, multiply base by the saved House value and then late actor470. Convert
  to an integer before testing promotion0. Do not combine all multipliers.
- Promotion's repeated veteran/elite/type queries and short-circuit order. The
  veteran interval is `[1,2)` and elite is `>=2`; unordered values pass neither.
  Ability26C is inherited at elite, with elite27E as the alternate. Only an actual
  true result reads rules598 and performs the additional integer conversion.
- Multiply the resulting integer by late actor468 and convert again. The joined
  Walk binds the actual percentage, without copying or clamping it.
- The raw actor5C3 byte is read after Foot returns. When nonzero, read actor5A8
  directly, rather than making another virtual type query. TypeC0B selects
  `speed-speed/3`; its zero branch selects `speed+speed/2`. Division truncates
  toward zero; final dword arithmetic wraps, including negative values.
- FTOL stores a signed64 integer and the caller consumes its low32 bits.
  Nonfinite/out-of-signed64 conversions produce the low zero dword of the x87
  indefinite integer, not signed32 saturation. Oracle calls enter with x87
  control0E7F (53-bit/toward-zero). Portable code restores the host rounding mode;
  other original entry-control states/FP exception flags are not claimed proved.

The standalone fixture keeps live actor/type/country/rules fields, selected
query-time diagnostic mutations, selected conversion results and final raw bits.
Those mutations are adversarial ordering checks, not gameplay observations.
Initial associations/records and startup are supplied. Native guards cover live
owner changes, repeated access, missing entered rules and host FP restoration.

`walk-queued-vectors ... --speed` is an explicit mode of the existing fixture.
It consumes actual admission and speed, borrowing existing actor percentage and
House/type/Cell identities. The original composition executes the actual speed
root rather than intercepting a return value. Legacy Q and admission-only A
inputs retain their earlier services/output/guards. The supplied parity map,
floor/Mark/notification/destination/reset, initial actor/type/country/rules/RNG and
queue remain diagnostic boundaries. No production map, resident-list maintenance,
commands, original route finding, animation/drawing or SDL join is inferred.
Nonzero admission continuations, special8 and entered head effects still refuse.

## Verification and measured costs

Canonical standalone originals: `speed-fresh-a2/expected.json` and immutable
original-only `report.json`. **579 sequences /891 complete Infantry roots** match
normal/sanitizer/uncached replay (`speed-replay-*-a1.json`). This includes actual
891 Foot/House/base/promotion calls,2,188 type queries and2,105 conversions.
Signed extremes, flag-dependent division, country float32, NaN/infinity/negative
zero, conversion boundaries and live late reads are covered. The immutable
original receipt remains valid despite the first native comparison failing.

Canonical complete composition: `walk-speed-fresh-a2/expected.json` and immutable
original-only `report.json`. **121 sequences /3,592 complete original Process
roots plus three initializers** match. Actual child counts include121 admissions,
1,353 speed/Foot/House/promotion calls,49 speed bonuses,202 head/release/claim
calls,1,353 active interpolations and81 Stops. Selected ordered stores/services,
final state, all24 route words and full RNG state match. The current
`walk-speed-replay-{normal,sanitize,uncached}-a2.json` each reports121 reuse hits,
zero misses and zero original execution. Standalone replay reports579 hits/zero
misses. Native results are never cached.

Current rebuilt legacy queued `queued-replay-{normal,sanitize}-a4.json` retains
all580 sequences /1,557 Process roots; admission-only
`walk-admission-replay-{normal,sanitize}-a3.json` retains199 sequences /2,093
Process roots. Earlier unrelated receipts retain their scopes. The87 focused
Python tests and eight mission/Walk/Infantry CTests per build pass. Original code,
dispatch, input bits, source/runner/data/receipt identity, ABI/caller stack and
remaining arena guards remain. Local verification is not independent acceptance;
no broad capability closure, SDL acceptance or whole-frame claim is added.

Standalone original generation0.570s. Normal/sanitizer/uncached replay0.136s/
0.363s/0.296s; native comparison0.011s/0.170s/0.013s. Initial attempt a1 failed
before execution because the fixture lacked its explicit actual-address mapping
(wrapper0.358s). Corrected a2 saved all original answers, then failed on the
native extra virtual type query (wrapper0.877s). That native-only repair reused
the saved originals, without relabeling the failed audit or original receipt.

Joined generation12.437s; complete comparison12.956s (wrapper13.083s).
Normal/sanitizer/uncached replay0.604s/1.421s/2.846s; native comparison0.103s/
0.859s/0.054s. The earlier successful a1 wrapper14.424s remains preserved.
Adding the input-bit helper to the original-source guard required genuine new
a2 generation; commands and original result streams are identical. The old
receipts were not upgraded or overwritten. Subsequent native-only changes reuse
eligible answers.

Native configure5.810s/build1.333s, repair rebuild0.588s; sanitizer configure
5.491s/build5.732s. Joined initial rebuild3.123s; final normal/sanitizer rebuild
2.380s/2.574s. Python87 tests1.536s (wrapper1.882s); CTest0.11s/0.70s
(wrapper0.314s/0.762s). Costs overlap and are nonadditive. Manual implementation/
repair and total task-wall times were not recorded. Private
`speed-validation.json` and `walk-speed-validation.json` record hashes, timings,
failed attempts and scope. No new cache framework or unchanged full original
matrix was introduced.

## Reproduce and next integration

```sh
./build.command
build/native/infantry-speed-vectors --guards
env PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_infantry_speed test_walk_speed

# New audit/report paths; current native code runs, original code does not.
env DEVELOPER_DIR=/Library/Developer/CommandLineTools PYTHONHASHSEED=0 \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/infantry-speed-next.audit.json tests/compare_infantry_speed.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/infantry-speed-vectors \
  --expectations private/infantry-walk-20261018/speed-fresh-a2/expected.json \
  --report private/infantry-speed-next.json

env DEVELOPER_DIR=/Library/Developer/CommandLineTools PYTHONHASHSEED=0 \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/walk-speed-next.audit.json tests/compare_walk_speed.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/walk-queued-vectors \
  --render-data private/derived/ra2-1006/render-data.bin \
  --raster-data private/derived/ra2-1006/raster-data.bin \
  --direction-data private/derived/ra2-1006/direction-data.bin \
  --subcell-data private/derived/ra2-1006/infantry-subcell-data.bin \
  --expectations private/infantry-walk-20261018/walk-speed-fresh-a2/expected.json \
  --report private/walk-speed-next.json
```

Use sanitizer runners under `build/sanitize/`; add wrapper `--uncached` for the
inspection control. Deliberately fresh originals use a new `--output` instead
of expectations/report and require the approved host research context. Preserve
all original receipts. Entry points remain `./build.command`, `./run.command`,
`./test.command`; `./run.command --boot-camp-preview` remains a static preview.

Next join ordinary E1 commands and mutable production actor/type/map ownership,
then animation/drawing and ordinary SDL walking. Recover encountered nonzero
admission continuations explicitly. Actual discovery/action scheduling still
precedes first-objective success; never synthesize waypoint success. No workers,
Windows actions, downloads or system changes occurred. Full base RA2/YR remains
incomplete; only Apple Silicon macOS is tested.
