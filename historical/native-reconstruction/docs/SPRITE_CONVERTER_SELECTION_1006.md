# Sprite converter selection on Building owners

This recovers the ordinary Techno virtual1CC selector6D1480, a dependency of
original Building presentation for Boot Camp discovery/Objective1. It does not
schedule frames, sight, arrival or mission actions. Both games remain incomplete;
only Apple Silicon macOS is tested.

## Exact original and ownership

Supplied executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Complete6D1480 is138 bytes/46 instructions,
ending6D1509, code SHA256
`91c277ae008125e0701002bb8d2de6ef74e1f53fc43a5ff60cba888680f028cc`.
All three returns and their joining branches are inspected, not just first-return
linear decoding. No original instructions are changed or run in the application.

The parent calls Type80 first, then reads actor1B4, saved TypeB8C and House15F40.
Even a nonnull Type override still reads/saves that House index. Its nonnull branch
loads override backing4, selects the scheme and returns scheme30C. With no override,
the parent reads current HouseA35DB4 and calls owner predicate3D4. A nonzero low byte
uses the saved owner index. Otherwise CC(1) is tested; a null result uses the saved
index, while nonnull causes a second CC(1) call and a late15F40 load from its new
result. It then reads global backingAB6EFC and selects scheme30C. Never coalesce
those CC calls, reread the saved owner index or cache the global backing early.
Table indexing preserves the original32-bit scaled offset: indices1073741824
and INT_MIN alias offset0, rather than indexing a host-sized container. The native
field view receives the wrapped byte offset and refuses addresses outside actual
backing. A null converter field is a valid result; a null House/scheme dereference is not
a fabricated fallback. Virtual children and startup remain supplied boundaries.

`SpriteConverterSelectionServices` borrows fields/identities without owning another
actor, House, table or palette cache. `BootCampMissionWorld::structureSpriteConverter`
binds the actual Structure418 Type, discovery owner1B4 and shared House15F40, plus
the actual current player House. The bounded Building CC child returns null.
TypeB8C startup is supplied null; a changed nonnull field refuses because its
actual table owner has not been recovered/bound. The generic kernel covers valid
nonnull override records separately; this is not original Type loader recovery.

Renderer services borrow the existing asset color-scheme records and existing
converter vector. Their scheme-to-converter association is supplied construction,
not original registry/ColorScheme initialization. Scheme and converter identities
remain distinct, and a foreign table/slot/converter refuses. The pixel dispatcher
accepts the actual selected member of that existing vector, preserving independent
17C stores instead of forcing the currently selected UI color's converter.
No new runtime executable reads, original execution or public dependency.

## Evidence and validation

The test-only original fixture executes unmodified complete6D1480 and observes
ordered real field reads, virtual receiver/arguments and final converter identity.
Virtual Type80/predicate3D4/CC children are supplied explicitly. Child mutations
change the actor owner/Type override, House indices and global table between reads.
Independent converter/scheme/table/House identities include null converter results.
Caller stack/nonvolatile registers, immutable code/vtable and unrelated arena/
global bytes are audited. Native expectations are never used as original answers.

The first two attempts entered a negative-index fixture that also returned that
same negative-index House on the alternate branch, causing a real unmapped
original read. Those failed attempts remain failed at their true fixture scope;
no original/native mismatch was claimed. The corrected valid corpus retains
negative saved indices only when the used alternate index is valid. The initial2,406-case valid proof is retained with its original scope. The final
corpus adds24 scaled-offset aliases; that changed original input scope requires a
new generation. Initial unconfigured native-target build failure remains separately
recorded.

## Commands and limits

```sh
./build.command
./test.command
build/native/boot-camp-walk-check private/official-1006-probe
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest \
  tests/test_sprite_selection.py tests/test_sprite_converter.py tests/test_techno_sprite.py
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/NEW.audit.json \
  tests/compare_sprite_selection.py --exe private/official-1006-probe/game.exe \
  --native build/native/sprite-selection-vectors \
  --expectations private/sprite-selection-20261019/fresh-a4/expected.json \
  --report private/NEW.json
./run.command --boot-camp-walk
```

Use new report/audit paths; replay runs current native and explicitly reuses
original answers. Sanitizer replay substitutes build/sanitize's runner. Fresh
changed-scope generation uses a new `--output private/NEW` instead of expectations/
report; Unicorn remains research/test-only. Native source changes alone do not
require original regeneration. Local verification is not independent acceptance.

Original Type override owner/loader, registry startup/lifetime, owner predicate,
optional depth-image owner/children and other frame/partner/animation/special
children remain open. No production frame/sight/arrival/Objective1 scheduling is
enabled. No Windows actions/transfers, downloads, system/Xcode/DRM changes,
proprietary shipment or worker use. Costs/current receipt are recorded below.

## Current checks and measured costs

Final2,430-case complete original generation passes; the separate2,406-case origin
remains unchanged. Normal/sanitizer current runners each replay2,430 selector,288
converter-word,832 sprite-parent and384 pixel answers:3,934 hits/zero misses.
214/213 CTests,12 Python guards and both actual-owner checks pass. The owner test
uses actual Type/House fields, live Gold/slot0 selection, missing/competing service,
null owner/negative address/nonnull Type-table refusals, and the full static ->
visibility -> ordinary -> sprite -> selection -> pixels composition. Existing
warm clone/source destruction and source/map/queue isolation checks are retained.
These native composition checks remain separate from original expectations.
SDL256ticks passes; both horizontal captures retain the prior inspected hashes.

Generation.567s, final builds62.18s/43.24s, owner checks7.40s/81.63s, native test
command6.19s/sanitizer CTests20.01s, SDL7.40s. Concurrent durations are nonadditive.
The prior integrated builds61.51s/64.93s and narrowed corpus retain their true
scope. A wrongly named pixel runner failed before audit setup; subsequent missing
render-data arguments failed parsing. Corrected commands replay the unchanged
original pixel answers. No failed attempt was relabeled; no original/native
mismatch occurred. Total manual inspection/edit/repair time and early target-build/
failed command durations were not instrumented. Receipt:
`private/sprite-converter-selection-receipt-a1.json`.
