# Team observer weight callbacks — supplied base

Complete41DFB0/41E070 now have readable, SDL-free C++ in
`src/sim/TeamObserverWeight.cpp`.580 original/native sequences execute900 complete
callbacks with no supplied arithmetic children. This is an internal dependency
of Team destruction, not actual-world observer initialization, Team teardown,
exhausted tick8 or tutorial scheduling. Player behavior is unchanged.

## Behavior and bounded floating point

Success41DFB0 starts with correction0. For signed trials108>0 it computes
`trials * (successes104 / trials - 0.5)` in that operation order and replaces a
negative correction with0. It loads Rules839848 afterward, adds RulesB8 to the
current weightB8, then adds the correction. Failure41E070 saves Rules first;
its correction multiplies the ratio-minus-half by RulesC8 before multiplying by
trials, and replaces a positive correction with0. Its base adjustment is RulesC0.
Names describe the counter updates, not a verified gameplay outcome association.

Both routines store weight, compare against minimumC0, then reload the stored
weight and compare against maximumC8. Each clamp copies low then high32-bit words,
rereading the high source after the low store. Success increments the late104
and saved108; failure increments only saved108. Counters wrap as32-bit words.
Borrowed fields, Rules references and optional post-store instrumentation retain
aliases, ordered stores and saved versus late reads. The Rules resolver is a
side-effect-free pointer projection, not a game callback.

The verified profile uses x87 precision53 with caller control word027F
(round-nearest) or0E7F(toward-zero), masked exceptions, and finite input doubles
that are zero or have absolute magnitude in[1e-100,1e100]. Portable arithmetic
inherits caller rounding and rounds each individual operation to binary64; strict
compiler flags and explicit intermediate stores prevent contraction/reassociation.
These bounds avoid the x87 extended-exponent difference. Integer inputs are exact
at53-bit precision. The original `fst` retains its register value for the first
comparison; within this bounded exponent/precision profile it equals the stored
double. Do not generalize that equivalence to other x87 precision/exponent modes.
NaNs, infinities, exponent-edge inputs and other rounding modes refuse before
stores. No soft-float runtime or alternate arithmetic model was introduced.

Actual caller FP startup/control word, observer initialization, Rules parsing and
A3D264 membership/order remain unjoined. The oracle supplies both FP modes; this
is not evidence that a particular game call uses either. Unsupported FP domains
must be recovered before widening the API or binding callers that need them.
No new runtime executable reads or public/generated/lifted implementation.

## Original evidence

Exact supplied executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD and unverified pristine
provenance remain distinct. Verifier fingerprints before relying on addresses:

- 41DFB0:191 bytes/47 instructions, SHA256
`3e8a0a0a58d2ac201d16691b5e0d6530344ccdb1daba545e027e8665f7378867`.
- 41E070:187 bytes/47 instructions, SHA256
`e2bf8c49458877a725c5676faebe7f7697acc0c26d6a74aa33d2f147bc4c5d0c`.

The two checked double constants are79B610=0 and79A728=0.5. No original
instructions are modified. The oracle executes only the complete verified spans,
checks every selected ordered store, unrelated arena bytes, immutable code/
constants/Rules pointer, caller stack/return, callee-saved registers, FP control
word and x87 stack depth. Fixtures supply fields, FP state and diagnostic
mutations; no game observation or original-composed destructor is claimed.

Coverage: signed nonpositive/extreme totals and counts, wraparound/repeated calls,
signed zero, inverted/equal bounds, both correction signs/coefficient signs,
finite exponent spread, adjacent binary64/half-ULP clamp boundaries, Rules aliasing,
late counter/bounds changes and split-clamp source mutations. Three Python tests
check matrix/domain, stream validation and original-source/scope reuse rejection;
the reuse test also accepts changed native identities while rerunning native.

Canonical original answers:
`private/team-observers-20261020/fresh-a2/expected.json`, SHA256
`1ed2f74e7316767fa8cd9b66c60d7a63395447cf74314abdb0af30ddef9c2983`.
Passing a1 retains its narrower556-sequence matrix. a2 adds24 half-ULP cases,
tightens stream validation and corrects the copied driver description; its changed
harness/matrix has fresh original provenance. An initial unit-test expected the
wrong matrix size(756 vs556); corrected before a1 generation. Nothing is relabeled.

## Reproduce and validation costs

```sh
./build.command
./run.command --boot-camp-walk
./test.command
DEVELOPER_DIR=${DEVELOPER_DIR:-/Library/Developer/CommandLineTools} \
 build/tools-env/bin/cmake --build build/native \
 --target team-observer-weight-vectors -j 6
PYTHONPATH=tools:tests PYTHONHASHSEED=0 build/tools-env/bin/python -B \
 tools/run_evidence.py --audit private/NEW-observer.audit.json \
 tests/compare_team_observer_weight.py --exe private/official-1006-probe/game.exe \
 --native build/native/team-observer-weight-vectors \
 --expectations private/team-observers-20261020/fresh-a2/expected.json \
 --report private/NEW-observer.json
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest \
 test_team_observer_weight test_team_destruction test_team_member_removal
```

Use the sanitizer runner in build/sanitize and fresh audit/report paths for a
separate replay. Normal/sanitizer each pass3 focused CTests and replay1,311
sequences:580 observers,266 destruction,465 unlink; all hits/zero misses/current
native.22 Python tests pass. No native pass/fail is cached. Existing original
families were not regenerated. With no owner/production change, broad world/SDL
acceptance was not repeated. Prior visible controls/drawing retain their scope.
Only Apple Silicon macOS is tested; local validation is not independent acceptance.

Final a2 original generation.131s; a1.092s. Final measured focused builds1.654/
2.181s, CTests.378/.232s(normal/sanitizer), sanitizer configure10.775s, Python
process.317s. Replay driver processes.233/.328s(observers),.339/.325s(destructor),
.361/.329s(unlink). Initial normal configure/build, inspection/edit/repair/review
and total wall time are not separately measured. Durations overlap, not additive.
Commands/logs/costs:private/team-observers-20261020/validate.py,validation-a1/.
Receipt:private/team-observer-weight-receipt-a1.json.

Next establish actual A3D264 observers and their construction/Type association,
Rules startup and caller FP state, then entered Tag/base lifetime children and
complete exhausted teardown. Existing eight map Foot recipients and actual unlink
remain separate composed owners. Original AC0C18/Neuron associations remain open.
Do not infer empty registries or skip notifications. Verify transferred-GI movement
including6BA990 before genuine Team/arrival/sight/objective scheduling. Both games
remain incomplete; no workers, Windows actions or runtime executable-read growth.

Private follow-up inspection is retained in
private/team-observers-20261020/registry-construction-inspection.txt. It identifies
constructor41C5C0, base410580, registryA3D260 append, TypeDC setter41DF90 and
static registry initializer4D2D90 as next leads. These spans are inspected only;
no construction/startup proof follows. The first linear xref scan stopped early
at undecodable bytes; registry-xrefs.json is partial. The later skip-data scan
in registry-xrefs-skipdata.json contains potential references, not a reachability
or completeness proof. Follow verified callers rather than treating either scan
as a recovered startup graph.
