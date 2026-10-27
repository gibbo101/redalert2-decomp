# Ordinary Infantry and shared Foot destinations

The diagnostic Infantry order now reaches the recovered Walk Move_To/Stop through
the same Foot destination kernel used by tanks. This recovers the target,
reference and timer dependency of Day 1's initial GI movement order. **The Boot
Camp application remains a static preview; production GI walking and the first
objective transition are not delivered.** The earlier Walk command/Process proof
retains its separate scope; this proof does not execute Process.

## Recovered scope

The supplied executable was rehashed before inspection:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Private inspections and receipts are in
`private/infantry-walk-20261018/`.

Complete original Infantry501CE0..50246F executes for the ordinary non-JumpJet,
nontransport profile, including its early returns. Actual House getter6C7430,
House control4F52F0, mission594770 and Walk IsMoving71DEA0 execute unchanged.

- House control returns raw House134 when globalA3D298 is nonzero; otherwise it
  returns boolean134-or135. The parent queries it twice on continuing paths.
  Human-controlled actor5AC values27..30 return before locomotor access.
- Walk IsMoving returns raw moving34. A moving/non-null parent order enters
  current-Cell admission478760 and potentially48C/504AE0. Those children remain
  explicitly refused here. Null parent orders and direct Foot commands retain
  committed-head handling; no stopped-state surrogate is used for Walk.
- Same-target, human, actor5C3 and typeC0D/C00 guards control animation4DC `(7,0,0)`.
  The animation effect remains supplied. Mission7/current or queued transport
  branches refuse. Ordinary continuation writes route4D0=-1 and retains23 tails.
- The exact base INI reader6DD40F..6DD428 associates typeB44 with `JumpJet` at
  7F7610. This is independently inspected/pinned naming evidence. E1 startup/type
  initialization is **not** recovered by supplying B44=0 in these fixtures.

Complete Foot4C8030..4C8217 now uses borrowed490/494/598/5A1, timer530/558 and
reference words, independently of Drive/Walk representation:

- Clear490 and store494 before successful retained-interface acquisition.
  GlobalA6EB14 changes before the instance atomic count; retain/class/release
  ordering is preserved. Positive retained references are required. Failure,
  destruction and the host atomic implementation remain outside the profile.
- Walk's base vtable7AEBA0 has GetClassID71F900 at+0C and returns GUID7A1FA0.
  Locomotor interface7AEAD8 is Walk+4; its+0C is Link_To_Object, **not** GetClassID.
  QI thunk71FE90 ->71FAB0 ->53D2B0 and actual AddRef/Release execute. Walk and
  Drive each differ from Foot's timer-special GUID7A1F80.
- Nonzero598 clears and skips coordinate/Move_To calls. Otherwise the coordinate
  dispatch consumes the **late** target494, after QI/class processing. Coordinate
  output Y aliases the timer-padding temporary. The by-value point then reaches
  the existing Walk command and its actual guards/bridge conversion.
- Null Infantry kind15 calls Walk Stop, then stores494=null again. Walk Stop
  retains a committed head and its raw movement bytes; an empty head resets even
  when already stopped. Actual reset508750 executes; animation `(27,0,0)` remains
  supplied. Tanks keep their distinct Drive Stop through the same Foot kernel.
- Clear5A1, read tick/delay, store wait558 start/padding/remaining word by word,
  reread tick, then store retry530 start/padding/zero word by word. A mutation
  after the first wait store cannot alter its already-read delay, but can alter
  the second tick. No struct assignment or cached single clock replaces this.

`FootDestination.hpp` owns this single SDL-free algorithm and interface lifetime.
`UnitDestination.hpp` binds the existing Drive behavior without replacing its
outer policy. `InfantryDestination.hpp` binds Walk and the ordinary Infantry
parent. No second actor/map/locomotion engine or new application default is added.
Refusals can follow earlier primitive stores; callers must discard unsupported
command transactions. There is no rollback claim.

## Evidence, reuse and limits

Canonical original-only receipt: `destination-fresh-a2/{expected,report}.json`.
**439 sequences /707 complete root calls** match:287 Infantry roots and420 direct
Foot roots. Actual children include655 Foot calls,327 Walk Move_To,176 Stops,
479 QI/class lifetimes and235 mission queries. Normal/sanitizer/uncached replays
`destination-replay-*-a2.json` each report439 original reuse hits, zero misses and
zero original execution. Native results are always executed.

Coverage includes raw House/control/movement bytes, early returns, equal and
distinct targets, suspended paths, command guards, all24 queue words, null
Stop/retained Z-only heads, signed clocks/delays and wrapped global references,
late targets/suspension, independent timer reads and Walk bridge projection.
ABI/callee-saved/return/caller-tail checks, whole owner-arena checks, selected
ordered stores and immutable code/table/input guards remain. Injected mutations
at named service/consumer boundaries are diagnostics, not game observations.

Coordinate output410290, map548000 and animation4DC effects, initial associations,
type/House/actor/global records and skipped-coordinate scratch remain supplied.
This new fixture does not join actual Cell center/floor. The earlier tank proof
retains that coverage. JumpJet/transport/effect/timer-special/aircraft and moving
nonnull parent retarget branches remain unjoined. No E1 initialization, route
finding, production GI owner, animation/drawing, SDL walking or mission success
is inferred. Local verification is not independent acceptance or whole-game proof.

The tank regression replays all819 sequences /1,833 roots from immutable
`private/map-depth-1006/unit-destination-v3/expected.json` with rebuilt normal and
sanitizer runners, plus an uncached inspection control. Final reports are
`unit-foot-replay-{normal,sanitize,uncached}-a3.json`. The new targeted
`compare_unit_destination_current.py` adapter validates the old receipt against
its actual historical identity, then independently requires every original
Python/inspection dependency to match. Current transitive C++/CMake and runner
identities remain separate and guarded. No native input producer exists in this
old generator. The old comparator, receipt and outputs are unchanged; no receipt
is imported into the general cache. See [ORIGINAL_RESULT_REUSE.md](ORIGINAL_RESULT_REUSE.md).

Both complete native builds pass; the normal application is arm64. `./test.command`
passes79 normal CTests and its asset/tool tests;78 sanitizer CTests and1,248
Python tests pass. The broad Python run initially found two explicit dependency
manifests missing the new header; both now include it. Their original metadata
keys conservatively change; no unchanged original inventory was regenerated or
relabeled. No new SDL run is claimed for this internal dependency join.

Fresh original generation is0.931s; final normal/sanitizer/uncached replay driver
times are0.262s/0.552s/0.579s (audits0.410s/0.700s/0.718s). Tank replay audit
times are0.502s/2.265s/0.445s. Focused target builds took1.802s/1.192s; tank
builds1.219s/0.695s. Configure took9.839s/8.513s; total later full-build time
was not separately measured. `./test.command` took1.952s; sanitizer CTest7.153s;
final Python command31.292s (test body27.067s). This is bounded verification
cost, not game performance. Manual inspection/review/repair time is unavailable.

Preserved `destination-fresh-a1` also passed; a2 genuinely regenerated after
adding the exact-base JumpJet naming guard, and all original streams are equal.
Two early test assertions about scenario counts/uniqueness and an adapter
filename rejected by the evidence wrapper were corrected before original
generation. The first broad Python failure took27.401s. There were no failed
original/native comparisons. The private `destination-validation.json` retains
identities, measurements and failure scopes. No new cache framework, dependency,
Windows action, download or runtime executable read was introduced.

## Reproduce

From the project root; preserve `DEVELOPER_DIR`:

```sh
./build.command
./test.command
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake -S . -B build/sanitize -DRA2_SANITIZE=ON
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/sanitize --target infantry-destination-vectors --parallel 6

env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/infantry-walk-20261018/destination-check-new.audit.json \
  tests/compare_infantry_destination.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/infantry-destination-vectors \
  --expectations private/infantry-walk-20261018/destination-fresh-a2/expected.json \
  --report private/infantry-walk-20261018/destination-check-new.json
```

Use the sanitizer runner and fresh report/audit names for its replay. Add
`--uncached` before the driver for the inspection control; original expectations
are still reused. To generate new originals in the authorized Mac host JIT
context, replace `--expectations`/`--report` with `--output private/NEW_DIRECTORY`.
Do not replace canonical receipts. The ordinary parent/Foot profile stays bounded.

Tank regression (configure/build its separate normal/sanitizer check projects
first, as in [UNIT_DESTINATION_1006.md](UNIT_DESTINATION_1006.md)):

```sh
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/infantry-walk-20261018/unit-foot-check-new.audit.json \
  tests/compare_unit_destination_current.py \
  --exe private/official-1006-probe/game.exe \
  --native build/unit-destination/unit-destination-vectors \
  --expectations private/map-depth-1006/unit-destination-v3/expected.json \
  --report private/infantry-walk-20261018/unit-foot-check-new.json
```

`./run.command --boot-camp-preview` still opens the static content/selection mode.
Next bind real E1 type/actor/target/timers and commands to Process on the existing
mutable map, recover encountered moving retarget48C, then infantry animation/draw
and ordinary SDL walking. Actual discovery/scheduler/actions still precede the
first objective transition. The full reconstruction goal remains active.
