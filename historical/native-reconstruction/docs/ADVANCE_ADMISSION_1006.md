# Ordinary Advance admission: rejected switch and result7 continuation

The subsequent [commands/preview/SDL integration](OWNED_ADVANCE_RUNTIME_1006.md)
now explicitly enables this policy in the bounded SDL runtime after original
command/finalization, full native preview isolation and actual SDL result7
acceptance. Low-level defaults stay guarded; Advance6/scatter remain refused.
The open gates and runtime-guarded statements below describe earlier checkpoints.
Current receipts and limits are in the opening [HANDOFF.md](HANDOFF.md).

This Advance-only checkpoint is retained below. The separate complete Process
join is now verified in [PROCESS_ADVANCE_ADMISSION_1006.md](PROCESS_ADVANCE_ADMISSION_1006.md).
The production owned world/runtime still retains its Advance7 guard pending
shared-world/preview/drawing and SDL acceptance. Earlier Process-unwired statements
below describe this note's original checkpoint.

`advanceWithOrdinaryAdmission` adds a separate **unwired** result-bearing entry
around the existing complete ordinary Advance kernel. It accepts actual admission
0/2 only in the supplied Unit-kind1/Passive0 rejected-switch profile, and result7
through its distinct unsigned default continuation. It duplicates no movement
algorithm. Complete Process, shared owned movement and `--owned-demo` retain their
existing Advance7 refusal until their caller/world joins are verified. Advance6,
scatter and the other exclusions stay refused. Base RA2 then YR remain incomplete.

## Exact target and branch

The private user-supplied target is 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage and reported no-CD provenance remain distinct;
pristine authenticity is unverified. These addresses apply only to that target.
No external code, dependency, extracted table or runtime executable-read expansion
was introduced. Existing reference/license boundaries in [REFERENCES.md](REFERENCES.md)
apply; no new public reference was needed.

Complete Advance is `4A1000..4A2649`. Its queued jump-point admission call is
`4A1C99`; `4A1C9F` compares the result with 6, and the **unsigned** branch at
`4A1CA2` takes 7 directly to `4A1F8D`. That continuation increments and stores the
current Drive index at `4A1F98`. It does not enter result6's resident effects.
Earlier handoff language grouped “Advance6/7 aftermath” as exclusions; that was
not evidence that their behavior was identical.

The complete table at `4A264C` is pinned for inspection:

| Admission | Destination | Verified scope here |
| --- | --- | --- |
| 0,2 | `4A1CAF` | Actual kind1/Passive0 rejection, then continuation |
| 1 | `4A1E97` | Inspection only; refused |
| 3 | `4A1EB2` | Inspection only; refused |
| 4,5 | `4A1F8D` | Inspection only; refused in this bounded admission profile |
| 6 | `4A1F05` | Inspection only; resident effects still refused |
| 7 | unsigned branch to `4A1F8D` | Actual admission, unchanged track/queue, index increment |

An unsigned default branch is not permission to accept arbitrary unsupported
return codes. The entry accepts only the measured0/2/7 domain. For0/2, Passive0
and actual actor kind1 remain supplied, immutable type/actor inputs; general
Passive switching is not recovered by this entry.

Before admission, retain the original two current-coordinate Cell queries,
second result's signed level, then target word lookup. Divide signed coordinates
by256 toward zero **before** truncating to16 bits. Pass the returned Cell's
identity immediately; the shared fallback can change coordinates during queries.
Admission occurs after committed placement/Facing and occupation-unmark effects,
and before index increment. An unsupported result throws a typed refusal after
that prefix; it is not a rollback or an original return value.

## Evidence and boundaries

`private/map-depth-1006/advance-admission-v1/` contains a fresh original proof and
normal/ASan+UBSan/uncached replays: **260 scenarios /5,644 complete Advance calls**.
Actual admission returns are7:230,0:17,2:1. All 230 result7 calls reach the measured
default continuation and its index store. All returns, logged queries/services,
**17,336 selected actor stores and 7,747 selected Drive stores** match. Subsequent
Advance, terminal cleanup, residual interpolation and inactive calls also match.
This is selected-store evidence, not a trace of every machine write.

Coverage includes all 32 curved transforms and 128 eligible queued directions,
all four incoming native FP modes, signed clock wrap, signed levels, zero/negative
speed inputs, marked-byte policies, speed suppression/accumulator boundaries,
negative coordinates/word truncation, shared fallback, full retained queue tails
and later track completion. A moving resident yields actual 2; a separate case
executes the same moving decision before late zero-speed 7 overrides it. Zero and
unordered admission rejection must not be generalized to negative finite speed:
the tested negative value returns0. Nonfinite supplied speeds remain outside this
fixture; earlier Unit admission evidence covers the comparison itself.

The original oracle reuses authored diagnostic construction and state projection,
then invokes **Advance itself**. The inherited fixture's disc-profile call address
`4A0BD0` translates to actual `4A1000`; the actual root is counted. It never enters
Process `4A05F0` or preparation `4A2670`. Root/callee stack/register/canary, original
code/input/dispatch, full actor/Drive/Cell/slot/fallback and resident/type/House arena
audits remain. Extra per-call checks forbid writes to Process queues, destination,
ramps/retries/waits and supplied residents. New expected results execute afresh;
no earlier expected state is an original input. Original instructions are unchanged.

The new native guard check exercises ordered repeated Cell queries, signed word
coordinates, immediate identity/level forwarding, replacement of a stale supplied
callback,0/2/7 continuation and seven typed unsupported-code refusals. It checks
that placement has happened before admission and refusal precedes index increment.
These authored native checks establish adapter behavior, not original fidelity.
The seven Python guard tests protect exact binary, source/input/receipt identities,
command parsing and the Advance-only scope against relabeling as Process proof.

Initial actor/Drive/type/House/flags/poses, Cells/directions/speeds and named Mark,
occupation, notification and post-Cell effects remain supplied diagnostic inputs.
No production mutable membership, second actor Process, complete drawing or SDL
behavior is verified by this entry. The current playable two-tank baseline and its
recorded acceptance retain their identical source/app/runner identities. There is
no new SDL capability or new SDL acceptance claim. Only Apple Silicon macOS is tested.

Two failed development attempts are retained privately: an incorrect negative-speed
expectation, and a boundary case that accidentally included a distant moving
resident beyond the native bearing domain. The expectation was corrected and that
coordinate-only case now supplies empty lists; the bearing guard was preserved.
An initial standalone-header command used the bare compiler without its SDK search
path; the configured `/usr/bin/c++` wrapper passed with the existing
`DEVELOPER_DIR`. No license or system tool selection was changed.

## Build, run and reproduce

```sh
./build.command
./run.command --owned-demo
./test.command

env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake -S tests/advance_admission -B build/advance-admission \
  -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_OSX_ARCHITECTURES=arm64 \
  -DCMAKE_PREFIX_PATH=/opt/homebrew
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/advance-admission \
  --target advance-admission-vectors --parallel 6
build/tools-env/bin/ctest --test-dir build/advance-admission --output-on-failure
# ASan/UBSan: repeat in build/advance-admission-sanitize with Debug and
# -DRA2_SANITIZE=ON, then run that directory's CTest.
PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  -m unittest discover -s tests -p 'test_*.py'

# Fresh original needs authorized Mac host Unicorn JIT and NEW private paths.
PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/map-depth-1006/advance-new-audit.json \
  tests/compare_advance_admission.py --exe private/official-1006-probe/game.exe \
  --native build/advance-admission/advance-admission-vectors \
  --output private/map-depth-1006/advance-new
# Replay: replace --output with --expectations
# private/map-depth-1006/advance-admission-v1/expected.json --report NEW_PRIVATE_JSON.
# Sanitizer: use its runner. Uncached control: add --uncached before the driver.
```

The nested checks are not registered in `./test.command`. Preserve source files
while a guarded invocation runs; never relabel old expectations or rerun closed
finalizers. The opening [HANDOFF.md](HANDOFF.md) records current closure, timings,
regressions and the refreshed terrain source enumeration.

Next join result7 to complete ordinary Process without duplicating its kernel,
then both genuine actors on the production shared world with later drawing,
preview isolation and an actual SDL interaction scenario before runtime adoption.
Recover result6 resident/scatter effects separately. General pathfinding, combat,
AI, economy, campaigns, multiplayer, audio, original saves and YR remain open.
