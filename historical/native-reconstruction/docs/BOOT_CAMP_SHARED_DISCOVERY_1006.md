# Boot Camp shared Cell flags and discovery Houses

The initialized discarded Walk-arrival preview now runs position discovery on
actual revealed Cell flags and the GI's existing discovery/mission record.
Sight and movement share every Cell140 word, including the fallback. Discovery,
mission actions and movement control borrow stable House records. Live arrival,
fog drawing and Objective1 remain disabled.

## Ownership and exact behavior

The target remains `private/official-1006-probe/game.exe`, 4,485,392 bytes,
SHA256 `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. No original instruction or source file
was modified; no runtime executable read or dependency was added.

`CellVisibilityState` has two explicit storage modes. Standalone fixtures own
flags140; production construction borrows `MapCellInput::flags` by reference.
The visibility vector reserves its final capacity before binding; its stable
Cells/fallback outlive every synchronous kernel invocation. Copy construction
makes a value snapshot with independent flags storage. Assignment copies values
into the destination's existing binding. Tests verify every production Cell and
fallback address and ensure modifying a copied snapshot does not affect terrain.
There is no second authoritative flags140 word in the production sight view.
Cell12C remains owned once by the visibility owner and is read by position effects.

The map visibility kernel gains an optional owner lookup returning fields for
immediate consumption, without a persistent mirrored table. Its old table path
retains original Cell references and observer identity. Both paths share the
single projection/odd-height/neighbor/blocked algorithm. Boot Camp movement now
uses those recovered primary/secondary predicates after startup instead of
constant visible results. Initial insertion still uses supplied visible startup.
The separate visibility divisor is explicitly104 from the verified5440D0 chain;
it is not an alias of the map/reveal divisor. Mode/override remain supplied0;
current House13D comes from the actual House. Both odd-height fallback assignments
forward immediately to the terrain fallback's coordinates and flags owner.

`BootCampMissionWorld` now owns one persistent `UnitDiscoveryWorld`. Structure
Tag execution uses it synchronously and clears the temporary Tag service on
success or exception; it no longer copies/replaces the House map. Movement's
human/control references and mission House identities therefore stay valid.
Null-Tag Infantry discovery uses this same world and refuses an active structure
event or nonnull Tag. The position callback checks both actual actor34 presence
and the GI discovery record's Tag presence before entering it. Startup House and
actor associations remain supplied.

## Arrival preview and remaining gates

For the actual GI order `(57,89) -> (59,89)`, the disposable graph reaches
selected-head arrivals on Process calls26 and52. First arrival reads revealed12C,
executes complete native discovery and sets actual actor373/owner5668/5669/13C.
Second arrival retains373 and skips the first tail map lookup: position-effect
Cell queries are3 then2, discovery calls1 then0. Sight removal/addition and
persistent position scratch/state remain joined. The source's actors, all mapped
Cell flags/visibility counters/bytes, fallback, floor and Houses are unchanged.
The two owner checks log those exact counts.

The preview remains initialized-only: tick/position, visibility query state and
initial House/mission state are guarded. A warmed visibility preview is refused
without mutation instead of rebuilding it as cold. This is not a general warm
world clone or a live scheduling claim. Copies of bound callbacks are never used.

Before enabling live arrival, join visibility resident traversal with the actual
mutable membership/Next records: visibility still has the two objective-structure
associations, while GI membership owns its own heads. Complete warm/discarded
preview ownership, entered parent/child effects and ordinary SDL discovery also
remain gates. Mark notification/recalculation and redraw/refresh remain named
services. Team spawning, objective text/audio/reveal/alliance effects and campaign
continuation are not completed by recording requests. No full Cell-owner, fog,
frame, mission-completion or whole-game fidelity claim follows.

## Verification and receipts

Fresh affected predicate/discovery proof:
`private/boot-camp-20261018/shared-visibility-discovery-fresh-a1/expected.json`,
SHA256 `4e691930d663d08b710fd9c12580ed9f1363fc26abd4a3a1de2df25acb7ce81d`.
All884 results pass, including456 primary/secondary predicate cases checked on
both native lookup paths against the same original trace and final fallback.
The old driver's combined original/native source guard required this fresh
identity; its commands, labels and expected outputs are identical to prior
`private/map-depth-1006/unit-discovery-v3/expected.json`. Neither receipt was
relabelled or edited. Normal/sanitizer/uncached replays all pass.

Rebuilt normal/sanitizer runners reuse unchanged original expectations for128
mask,192 Cell-change,48 reveal-area,64 post-sight,360 position-discovery and80
joined position/sight roots:872 results per build, zero misses. Their reports
are `shared-visibility-{mask,change,reveal,post,position,sight}-{native,sanitize}-a1.json`
under the same private folder. No whole inventory refresh or closed finalizer ran.

Full builds,114 normal CTests,113 sanitizer CTests and1,349 Python tests pass.
Final owner checks are `shared-visibility-owner-{normal,sanitize}-a3.log`.
Final106-tick SDL acceptance is `shared-visibility-sdl-a2/`; arrival drawing was
visually inspected. Its report retains objectives disabled and explicitly denies
original fidelity from the smoke test. The earlier a1 SDL run also passed before
the final separate-divisor/House binding. Local source/runner/log hashes and old/
new projection parity are in `shared-visibility-owner-receipt-a1.json`; this
receipt is explicitly native-only, not original execution or independent acceptance.

Fresh original generation took1.024s; full driver1.372s. Normal/sanitizer/uncached
replays took0.465/1.175/1.895s, comparisons0.023/0.334/0.021s. Concurrent broad
checks took7.23s normal CTest,19.41s sanitizer CTest,32.35s Python. Build/SDL/manual
wall cost was not separately instrumented. Only Apple Silicon macOS was tested.

## Reproduce

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
./test.command
build/native/boot-camp-walk-check private/official-1006-probe
build/sanitize/boot-camp-walk-check private/official-1006-probe

env PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/shared-discovery-next.audit.json \
  tests/compare_unit_discovery.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/unit-discovery-vectors \
  --expectations private/boot-camp-20261018/shared-visibility-discovery-fresh-a1/expected.json \
  --report private/shared-discovery-next.json

./run.command --boot-camp-walk
```

Use fresh audit/report paths; select the sanitizer runner or add `--uncached`
before the driver for controls. Keep the driver's source/runner/prepared-data/
receipt guards. Fresh original execution requires private Unicorn JIT permission
and uses `--output private/NEW-DIRECTORY` rather than expectations/report.
User data, binaries, previews and receipts remain ignored. Source installations,
Windows and the sibling project remain untouched. No public/YR/recomp code or
behavior supplied this integration.
