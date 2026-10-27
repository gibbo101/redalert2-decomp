# Inclusive RNG ranges required by Unit Scatter

`rangedOriginalRandom` adds the original signed inclusive range policy over the
existing `OriginalRandomState` and raw XOR step. It preserves rejection sampling
and exact generator consumption. The helper is **unwired**; Unit Scatter,
Advance6 and their caller/world/preview/SDL joins remain open. Seeding and
association with the scenario/global generator remain supplied. Base RA2 first,
then Yuri's Revenge remain incomplete.

## Exact target and algorithm

The private supplied executable is 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 lineage and reported no-CD provenance are distinct;
pristine authenticity is unverified. No new executable reads enter the runtime.
No external code, header, table or dependency is incorporated; existing reference
and license boundaries in [REFERENCES.md](REFERENCES.md) apply.

The complete original root is `6388A0..63894D` (exclusive), 173 bytes / 66
instructions, including the inlined 250-word XOR step. All 66 instructions execute
in this suite. Unit Scatter's calls at `707574`, `707613` and `707656` are pinned
for inspection only. They request 1..4 and 0..2; the enclosing Unit Scatter root
does not execute here. The earlier raw-step proof is
[TILE_VARIANTS_1006.md](TILE_VARIANTS_1006.md).

Preserve these details:

- Equal signed endpoints return immediately, with no generator access. Otherwise
  swap endpoints by signed comparison, then subtract their unsigned bit patterns.
- For ordinary terminating spans, form a mask through the highest set width bit.
  Draw from the original generator, mask the full raw word and reject values
  exceeding the width. Add the accepted value to the lower endpoint with dword
  wrapping. Do not replace rejection sampling with modulo reduction.
- A disabled byte returns raw zero without reading/changing generator indices or
  table words. It still contributes one draw attempt for a sampled call.
  The existing raw-step implementation is reused; no second generator is added.
- Width `0x7FFFFFFF` follows the original signed `(width+1)<=width` branch.
  It returns lower+`0x80000000`, wrapped, without any generator access. For example,
  0..INT_MAX returns INT_MIN; INT_MIN..-1 returns 0. These out-of-range results
  are verified original behavior, not repaired arithmetic.
- Widths at least `0x80000000` are explicitly refused. Inspection shows the x86
  shift count wraps to zero, making the mask zero while the signed rejection
  threshold is negative. No original termination or error parity is claimed for
  this excluded profile. The native host draw bound is also a safety refusal;
  exhausted bounds retain already consumed draws and do not roll back state.

The optional read-only observer sees each raw draw and indices after the step,
before masking. It does not supply samples or influence the generator. Active
indices must be 0..249. Bypass and disabled cases preserve even invalid supplied
indices without dereferencing them. Native error guards are not original returns.

## Evidence and limitations

Canonical proof: `private/map-depth-1006/random-range-v1/`.
**371 fresh original sequences / 7,011 complete calls** match normal,
ASan+UBSan and uncached replays. Compare every result, all 7,096 raw draw attempts
and their post-step indices, then every generator word at each sequence end.
There are 718 actual rejections, 3,868 active XOR steps, 3,228 disabled attempts
and 633 no-draw calls. The longest authored rejection sequence consumes 101 draws.
Both index wrap stores execute (134 first-index / 36 second-index wraps).

The original harness checks every actual state store's instruction, address and
computed value, whole arena/caller stack/register/canaries and immutable code/
disabled/padding bytes. This is not a comparison of native machine write order.
Initial generator state is authored/supplied; Python's deterministic test-data
generator does not replace original execution or native RNG behavior. The suite
covers signed endpoint swaps, powers-of-two mask boundaries, full uint32 samples,
equal/index-tie/wrap/disabled cases, the signed-overflow branch, known rejection
prefixes and retained heterogeneous call sequences. It establishes no original
seeding, scenario lifetime, Unit Scatter, Advance6 or frame behavior.

Six native guard checks pass normally and under sanitizers. Eight new evidence
tests protect exact binary, source/header closure, input/receipt identity,
unsupported spans and scope flags. **993 Python tests, 67 normal / 66 sanitizer
legacy CTests and `./test.command` pass.** Both standalone CMake builds pass.
The new runner is outside the application/legacy test graph; compare it separately.
All 170 preceding replay records retain exact identities; adding the two range
records yields 172. The app remains unchanged at SHA256
`419aac6d0fbcbd33b0fe042ec57c03e508547f1fa3bc3d1971945fda1e3d2ecc`.
Earlier SDL acceptance is retained by identity; no new SDL acceptance is claimed.
Only Apple Silicon macOS is tested. Local verification is not independent acceptance.

Original generation took 1.575s; native comparison 0.091s. Guarded wrapper times
were fresh 8.224s, normal 0.337s, sanitizer 0.563s and uncached 0.461s. These are
verification costs, not game performance or a controlled speedup. Full repair/
manual-review time was not measured. The first pilot's disabled negative-index
trace used unsigned serialization; that oracle projection was corrected and the
pilot rerun afresh. Original instructions/results and native arithmetic were
unchanged; the failed record remains private.

## Build, try and reproduce

```sh
./build.command
./run.command --owned-demo
# Existing two-Rhino movement; Advance6/scatter still refused.
./test.command
PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  -m unittest discover -s tests -p 'test_*.py'

env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake -S tests/random_range -B build/random-range \
  -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_OSX_ARCHITECTURES=arm64
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/random-range --parallel 6
build/random-range/random-range-vectors --guards
# Sanitizer: build/random-range-sanitize, Debug and -DRA2_SANITIZE=ON.

# Fresh execution requires authorized host Unicorn JIT and NEW private paths.
PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/map-depth-1006/random-range-new-audit.json \
  tests/compare_random_range.py --exe private/official-1006-probe/game.exe \
  --native build/random-range/random-range-vectors \
  --output private/map-depth-1006/random-range-new

PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/map-depth-1006/random-range-try-audit.json \
  tests/compare_random_range.py --exe private/official-1006-probe/game.exe \
  --native build/random-range/random-range-vectors \
  --expectations private/map-depth-1006/random-range-v1/expected.json \
  --report private/map-depth-1006/random-range-try.json
# Use the sanitizer runner for its replay, or --uncached before the driver for
# the inspection-reuse control. Never rerun closed finalizers.
```

Next join actual Unit Scatter with its real mission/type eligibility, locomotor
interface ownership, Facing, mission-control, bearing/range selection, neighbor
map/admission and destination effects before enabling Advance6. Existing Cell
member callbacks remain supplied; do not substitute successful no-op scattering.
General pathfinding, combat, economy, AI, campaigns, multiplayer, audio, original
saves and YR remain open. Initial construction, controls/routes/clearance/schedule
remain supplied. No startup, full-frame or whole-game claim follows. Private
originals/assets/research/expectations/binaries remain ignored and unshipped.
Source installations/discs and outpost2 remain read-only. No workers, Windows
actions/transfers, downloads, publication, system/Xcode/DRM changes occur.
