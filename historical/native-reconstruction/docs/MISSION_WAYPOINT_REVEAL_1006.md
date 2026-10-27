# Mission waypoint reveal orchestration

Complete base6B0670 now has a readable SDL-free C++ implementation in
`src/sim/MissionWaypointReveal.hpp`. It is separate and unwired: Boot Camp's
production action17 still uses the earlier recording child. Actual waypoint
lookup663180, map lookup548070 and reveal-area54A110 remain supplied services
in this proof. This is not a terrain reveal or live objective milestone.

## Recovered behavior

The child ignores all four inherited dispatcher arguments. It first loads current
House A35DB4 and returns low-byte1 immediately for nonzero House+188, without
reading the action, rules or waypoint services. Ordinary execution reads signed
action+74, obtains the waypoint through scenario A3D290 and consumes the returned
pointer's packed Cell, not an assumed scratch address.

The first Cell query tests flag140 bit100. Only if clear does a second query test
bit400. Either bit contributes4. A separate final Cell query supplies signed
byte11B; it may be a different record from earlier lookups. The resulting height
is divided by2 with signed truncation toward zero. Subtract that half from both
Cell words with16-bit wrapping, sign-extend and convert to center coordinates
(word*256+128). Z is the wrapped32-bit product of saved height and global ABFE08.
This scale is not silently identified with reveal-area's A6FC30 height divisor.

The first54A110 call receives center, rules839848+54C range, current House and
flags0/0/0/1/0. The second reconstructs the same XY from saved waypoint/height,
reloads ABFE08, rules pointer, current House pointer and range, then passes flags
0/0/0/1/1. A first-call change of globals or rules fields is visible to the second
call; saved waypoint/height are retained. Both child results are ignored and the
root returns low-byte1. Native arithmetic preserves word/dword wrapping.

## Exact original evidence

Target4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD and unverified pristine
authenticity remain distinct. The verifier fingerprints the target and pins the
complete399-byte6B0670..6B07FE range and key associations. No original instructions
are patched. Research-only Unicorn executes the root; original code is never
executed in the application.

Fresh expectations:
`private/boot-camp-20261018/waypoint-reveal-fresh-a2/expected.json`, SHA256
`afa9bf501ac2b21dfd538c52ab63ebe3922add5855acbc54582e02f40cf4cbd3`.
All1,327 complete original roots match ordered waypoint/Cell/reveal traces and
low-byte return. They make1,072 waypoint,2,704 Cell and2,144 reveal supplied calls.
Coverage includes all255 disabled bytes, all256 signed height bytes on four flag
paths, distinct query records, negative odd truncation, signed-word boundaries,
wrapped products, replaced globals and same-owner late range mutations. A second
House with disabled188 set is forwarded without rerunning entry admission.

The fixture returns a waypoint pointer distinct from requested scratch, retains
unused dispatcher arguments, supplies named global/record associations and
refuses any instruction outside the inspected root or the three named services.
Checked calls preserve caller stack/return/callee-saved registers, code bytes and
all unrelated arena data. Only named supplied changes to globals/rules are
allowed; the arena and four globals are compared after every call. This is
isolated routine evidence, not an original-game observation or startup proof.

Normal/sanitizer/uncached replays each retain1,327 hits/zero misses. Fresh original
execution0.475s; fresh driver1.036s. Exact report/runner identities and other
measured costs are in `waypoint-reveal-receipt-a1.json`. Build/repair/review/approval
and tool-dispatch overhead were not separately measured. No new cache was added;
existing immutable-inspection and original-expectation guards remain intact.

Both full builds pass. All131 normal/130 sanitizer CTests and1,416 Python tests
pass. The three new Python tests exercise scenario coverage, input/binary guards,
changed-original rejection and scope/trace receipt tampering.27 previous runners/
application/checks remain hash-identical, preserving their closed original/owner/
SDL evidence scopes. No closed finalizer, private-data owner check or SDL smoke
was rerun for this unwired dependency. Local verification is not independent
acceptance; native-only guards do not establish original fault parity.

The initial A1 receipt remains preserved. Completing the transitive native-source
manifest required fresh A2 original expectations; all commands/outputs are
identical. Both replay controls were repeated against A2, and the three affected
Python guards passed again. Native compiled sources and binaries did not change.

## Commands and remaining integration

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
./test.command
DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure

env PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/waypoint-reveal-next.audit.json \
  tests/compare_mission_waypoint_reveal.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/mission-waypoint-reveal-vectors \
  --expectations private/boot-camp-20261018/waypoint-reveal-fresh-a2/expected.json \
  --report private/waypoint-reveal-next.json
```

Use fresh paths. For sanitizer choose its runner; for an uncached control put
`--uncached` before the driver. Fresh original generation replaces expectations/
report with `--output private/NEW-DIRECTORY` and requires Unicorn JIT access.

Next recover waypoint663180 and join the actual reveal-area/visibility owners,
then connect production action17 with full warm discarded-preview isolation.
Team creation, alliance/audio effects and ordinary live arrival/discovery remain
separate gates before Objective1 acceptance. Startup House/rules/scenario/map
associations, unsupported null/fault profiles and visibility child effects remain
supplied. No public/YR/recomp code, new dependency/runtime executable read,
Windows action or system/DRM change was introduced. Both games remain incomplete.
