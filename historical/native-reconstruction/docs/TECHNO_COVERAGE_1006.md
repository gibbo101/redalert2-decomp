# Stock Techno coverage add/remove

`changeTechnoCoverage` now implements complete base6C83F0 and6C86F0 around named
supplied virtual/House/height/map/refresh/redraw children. These are the actual
stock Infantry7A3540 and Building79CBBC virtual3AC/3B0 targets previously called
"image" effects in the House-map scan notes. Their parent code changes Cell
coverage counters and flags; this note does not infer type configuration names
or claim that image loading/rendering has been recovered. This separate entry
is not wired into Boot Camp, MakeAlly, action37 or SDL.

## Recovered behavior

Null current House and active1FD guards precede all children. Addition alone
queries virtual30C and tests its low byte. Zero range200 loads signed typeADE
through the supplied virtual80 service. Preserve the range store even when the
returned byte is zero. X88 is captured before the active1FD store, then Y8C/Z90;
height6A2970 is called twice with the saved Z. Each returned signed height is
truncated by -30, wrapped into a256-word displacement, added to the respective
saved coordinate, divided by256 toward zero and narrowed to signed16.

The loop saves range200 only after both height calls. It visits X outer/Y inner
from wrapped -2-range to wrapped range+2 exclusive and accepts strictly smaller
wrapped signed squared distances than wrapped (range+1)^2. Negative ranges and
empty traversals are retained; they are not clamped into a plausible radius.
The native host refuses an entered traversal wider than128 in either direction,
after the preceding stores/height calls. This is an explicit execution bound,
not recovered game arithmetic. No rollback is promised on an entered refusal.

Each accepted Cell repeats virtual3C/local4F52B0, direct Owner1B4/alliance4E5540
and late current-House13D tests independently before each counter branch.
The returned virtual Owner and direct Owner are distinct. The second privilege
query is not a cached copy of the first. Current House may change between calls.
Addition's nonprivileged branch reads130 against1, conditionally reads it again
against0, conditionally increments130, always increments134, then queries130
again before clearing flag12C bits16 and8 with two separate lookups/stores.
Removal decrements134, reads current-House566A, conditionally requeries134 and
decrements130, then requeries130 before setting bits8 and16 separately.
Privileged branches increment/decrement13C. Every counter operation wraps32 bits;
lookups can return different records on successive calls. Finally the late current
House188 byte is cleared if nonnull, followed by634030 and4E09A0(2), including
empty traversals. Store observers only report completed stores and make no queries.

## Evidence and boundaries

The exact supplied binary is4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD and unverified pristine remain
distinct. `verify_techno_coverage.py` checks its hash/PE, complete instruction spans,
key instructions and both stock virtual tables before execution. No public/YR/
recomp implementation, dependency or runtime executable-read expansion was added.

All252 fresh original parents match every named service event, ordered actor/
House/Cell store and final record projection:130 additions,122 removals. This
includes8,059 supplied Cell lookups,6,032 repeated Owner/local queries,5,200
alliance queries,428 height calls and214 refresh/redraw pairs. Original instruction
and arena/write/stack/callee-saved/input audits remain active. Diagnostic callbacks
mutate range/coordinates/Owner/current House and rotate lookup results. Those
mutations are adversarial inputs, not original gameplay observations.

Virtual30C/type80/Owner3C, local/allied House calculations, height projection,
map lookup,634030 and redraw4E09A0 are supplied services in this parent proof.
Their trace does not establish original child behavior. The associated typeADE,
active1FD/range200, Cell counters, House566A/188 startup/writers and complete
production ownership are still open. The optional store observer is diagnostic.
The input fixture bounds initial range to[-64,62] and type byte to[-128,62]; it
covers signed negative and zero reload behavior, not every possible original span.
No original whole-chain/whole-frame or completed mission/game claim follows.

Canonical original-only expectations:
`private/boot-camp-20261019/coverage-fresh-a1/expected.json`, SHA256
`5c1970326c54d9b1b8a4760e087c260ee255d6d6cfb97bcccbdbfddcc52e7389`.
Fresh original generation1.489s; native comparison0.029s. Four Python guard/reuse
checks, normal/sanitizer focused CTests and all three final guarded normal/
sanitizer/uncached replays pass. Final domain guards additionally check missing
entered services, no-query early returns and retained effects before refusal.
The rebuilt runner has a separate identity from the fresh proof runner.
Final builds0.909s/0.803s; final replays0.299s/0.395s/0.415s. Configuration and
other recorded costs remain private. Repair/task wall costs are unavailable.

The first negative trace fixture accidentally used valid decimal300/0x12C; it
was corrected to299 before original execution. The first build preceded CMake
regeneration; an initial C++ declaration edit then failed compilation and was
repaired. Failed attempts/logs are preserved. There was no original/native
comparison mismatch. No closed finalizer or whole inventory refresh was rerun.
Application/owner binaries retain the previous106-tick SDL baseline; they were
not rebuilt or rerun for this unwired kernel. Local checks are not independent
acceptance. Receipt: `private/boot-camp-20261019/coverage-receipt-a1.json`.

## Reproduce and next integration

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake -S . -B build/native
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake --build build/native --target techno-coverage-vectors --parallel 6
build/tools-env/bin/ctest --test-dir build/native -R techno-coverage-domain --output-on-failure
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_techno_coverage
# Use new private audit/report names on each invocation.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/NEW-COVERAGE.audit.json tests/compare_techno_coverage.py \
  --exe private/official-1006-probe/game.exe --native build/native/techno-coverage-vectors \
  --expectations private/boot-camp-20261019/coverage-fresh-a1/expected.json \
  --report private/NEW-COVERAGE.json
```

For fresh original execution replace expectations/report with a fresh `--output`
directory using the authorized research-only JIT. Use the sanitizer runner or
put `--uncached` before the driver for the other replay profiles. Existing
application entry points remain `./build.command`, `./test.command`, and
`./run.command --boot-camp-walk`; this entry adds no gameplay control.

Next join actual House/height/map children on shared records, recover the entered
permission/type initialization and634030 dependency, then production ownership/
full warm clone isolation and the map-scan caller. Keep the existing runtime
image refusal until those joins are accepted. Remaining redraw/session/UI/audio/
Team/scheduling and action37 still precede ordinary SDL Objective1 completion.
Both games remain incomplete. Only Apple Silicon macOS is tested.
