# Overlay and wall admission in the complete Unit root

The separate `overlayUnitAdmission` entry recovers the overlay decisions inside
the existing complete Unit admission kernel. It accepts typed borrowed Cell/type,
House and selected-weapon fields; it does not supply an admission answer. The
ordinary and production bindings retain their overlay-free scope. This is an
internal dependency toward an actual overlay interaction, not playable crushing.

## Original behavior and boundaries

The private supplied base executable is 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
It was rehashed before inspection. Embedded1.08, supplied1.006 lineage, reported
no-CD provenance and unverified pristine authenticity remain distinct. All
original instructions execute unchanged; no public/generated/lifted code or new
dependency is incorporated.

Complete Unit703040 first performs its existing registry, Foot terrain and
locomotor checks. Only then does703331 read target Cell+44. Overlay -1 skips
the branch; other supported indices resolve the supplied A35DEC registry.

| Entered fields | Actual decision |
| --- | --- |
| Overlay+27A nonzero | Call complete House4F52F0. If its AL is zero, reread globalA3D298 and return7 only when that global is also zero. |
| House4F52F0 | With nonzero global, return raw House+134; otherwise normalize House+134 or House+135. |
| Overlay+278 zero | Continue to residents without a wall decision. |
| Wall, nonzero Crushable+1FD, and mover Crusher or ability17 | Actual House index-alliance query on Cell+50. Allied owner promotes the current result to4; other owners retain it. |
| Other wall | Actual canFire and repeated selected-weapon query. Missing weapon returns7. Read selected weapon+AC warhead: nonzero+144 permits it; otherwise require nonzero+146 and overlay armor+9C equal6. Failure returns7. |
| Wall weapon permitted | Actual owner alliance promotes result4 for allied,5 otherwise. |

Residents, self/mission decisions and speed rejection still execute after the
wall decision. A nonzero result bypasses the later occupation decision only at
its original point. Preserve low-byte flags, wrapped House bit indices, repeated
weapon queries and shared fallback identity. The returned numbers remain unnamed;
successful admission is not destruction or movement.

`UnitAdmissionOverlayServices` returns references to stable supplied fields.
All field owners/callback captures must outlive the synchronous call. Binding
makes no queries, and missing services refuse only when entered. There is no
second admission algorithm: the optional services extend the existing template,
and old entries pass its null default. No application binding or terrain guard
changes. The native fixture requires explicit `--overlay` and a separate `V`
prefix; legacy parsing refuses that prefix.

Initial Cell/type/House/weapon/warhead associations, registry, direction pairs,
speed bits and actor records remain supplied. Existing restriction=-1,
loading1, unpromoted/count704=0, empty passenger/team and stationary-resident
limits remain. Crushing residents and other excluded original children still
refuse. Full candidate-crush preparation, later curve64/actor59F/velocity effects,
overlay destruction, complete Process over overlays and runtime entry remain open.

## Verification

Canonical evidence: `private/overlay-entry-20261018/fresh-a3/`, its adjacent audit,
and `replay-normal-a3.json`/`replay-sanitize-a3.json` with separate audits.
**473 scenarios /481 complete original Unit roots** match current native outputs
and ordered diagnostic query/store events. Original returns0/4/5/6/7 execute.
Coverage includes raw flags/global controls, weapon/armor combinations, positive
Crusher, allied/enemy/unowned/wrapped owners, resident/speed precedence, three
absent-overlay targets, three early returns with no overlay query, and repeated
shared fallback/word-wrap sequences. Required branch/return coverage is checked
on fresh generation and replay. This is not an exhaustive ordered field-read or
store trace, a Process proof, or an original-game observation.

The derived oracle retains the parent's complete arena/fallback, allowed-write,
immutable input, register, stack and instruction audits. It permits only the
newly inspected registry instruction and complete13-instruction House leaf beyond
the parent's domain. No original instruction or callback result is substituted.
`fresh-a1/` retains its earlier387-call proof at its own source/input identities;
the enlarged proof does not relabel it. `fresh-a2/` retains the same473 scenarios
at its preceding driver identity; a final whitespace correction required a3's
fresh source identity. All commands, labels and answers remain identical.

Normal and ASan/UBSan native guards test post-binding owner/flag/global/weapon
changes, no-query binding and entered missing-association refusals. The comparator
also executes six malformed/mode refusals. Python tests cover source/inspection/
engine/profile/receipt/input/coverage guards and permit rebuilt native identities
only with current validated expectations. Strict replay always runs current C++.
The small new driver does not add persistent original-result caching.

The affected production encounter uses the existing require-hit protocol and key
`9fc6378d845762e6b91a53776b832d5f5e01356d1f3cd68882a99fe12c74f945`.
Both rebuilt normal/sanitizer runners retain139 results /256 original Process
roots /6 complete draws with zero original execution. Historical original
provenance is unchanged. No unchanged original matrix or closed finalizer reruns.
Both dedicated runtime checks and1,198 Python tests pass. The rebuilt arm64 app
and68 current root CTests pass. No new SDL acceptance is claimed for this unwired
dependency; the prior positive-neighbor SDL baseline is documented separately in
[PREPARATION_NEIGHBOR_1006.md](PREPARATION_NEIGHBOR_1006.md). Local verification
is not independent acceptance. Only Apple Silicon macOS is tested.

Final measured CLI costs: fresh proof2.04s (1.189s original generation); normal/
sanitizer strict replay0.32s/2.05s; encounter hits13.21s/6.29s; app build26.77s;
focused normal/sanitizer builds10.11s/11.01s; dedicated normal/sanitizer builds
14.97s/13.94s; dedicated checks13.65s/78.71s; Python24.33s CLI /22.327s reported;
`./test.command`1.02s. Some checks/builds overlapped; these samples are not
additive or comparable speed benchmarks. The earlier focused build1.79s and
387-call proof1.32s are retained separately. The preceding enlarged proof2.16s and
its replays0.31s/2.18s remain recorded. Manual repair and total task wall
were not separately measured.

## Reproduce

```sh
./build.command
./test.command
./run.command --owned-demo
build/native/unit-admission-vectors --overlay-guards
build/sanitize/unit-admission-vectors --overlay-guards

# Fresh original execution needs the authorized Mac host research/JIT context.
# Always choose new private output/audit paths.
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/overlay-proof-NEW.audit.json \
  tests/compare_overlay_unit_admission.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/unit-admission-vectors --output private/overlay-proof-NEW

# Strict replay: current sources must match the recorded proof.
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/overlay-replay-NEW.audit.json \
  tests/compare_overlay_unit_admission.py \
  --exe private/official-1006-probe/game.exe \
  --native build/sanitize/unit-admission-vectors \
  --expectations private/overlay-entry-20261018/fresh-a3/expected.json \
  --report private/overlay-replay-NEW.json

# Affected encounter: current native execution, eligible original expectations.
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/overlay-encounter-NEW.audit.json \
  tests/compare_owned_scatter_world.py \
  --exe private/official-1006-probe/game.exe \
  --native build/owned-terrain-runtime/owned-terrain-runtime-vectors \
  --original-cache private/original-results --original-cache-require-hit \
  --output private/overlay-encounter-NEW
```

Build the sanitizer fixture with `cmake --build build/sanitize --target
unit-admission-vectors --parallel 4` using the existing toolchain environment.
Dedicated runtime build/CTest commands remain in the preparation-neighbor note.
Next recover the actual preparation candidate byte and later effects, then join
an overlay interaction on the production owners before ordinary SDL adoption.
Direct routing/controls/scheduling/startup remain supplied; no pathfinding,
combat, full-game or YR completion follows from this dependency.
