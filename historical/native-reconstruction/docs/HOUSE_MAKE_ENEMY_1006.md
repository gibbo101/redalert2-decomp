# Complete House MakeEnemy caller

`HouseMakeEnemy.hpp` implements complete base4E5A70, including the out-of-line
4E5CD4..4E5CE9 speech tail. It composes actual4EEBA0 score/enemy selection and
the existing original-derived message duration conversion. Map sight, grid rebuild,
localization/format/display, redraw and speech remain named supplied services in
this proof. This is a separate unjoined entry, not production diplomacy or an
alliance-bit-only replacement. Boot Camp action37 remains request-only.

## Original order and unusual stores

Nonzero mode checks the target type's passive1A6 first, then the initiator's;
either nonzero byte exits before all effects. Mode0 bypasses those type checks.
Otherwise map sight is removed, then the initiator's threat score is incremented
by1 for the target through actual4EEBA0, even if the later alliance test fails.
A null target in mode0 still reaches that score child. Nonzero-mode null targets
are explicitly refused instead of reproducing the original dereference fault.

The alliance predicate accepts exact identity, equal signed index or an index
other than-1 with a wrapped mask bit. Accepted entry clears the target's bit on
the initiator, then samples unrestricted-global. The original NEG/SBB/INC sequence
on a nonzero shifted bit produces zero: **the entire initiator mask120 is cleared**.
This is deliberately not rewritten as a bit complement. Grid rebuild follows.

Reciprocal alliance is tested after that grid effect with live indexes/masks.
If accepted, the target's alliance mask loses the initiator's bit. With nonzero
unrestricted, the next mask120 store again targets the **initiator**, clearing
its own index bit, not the target's mask120. Then the target grid is rebuilt and
actual4EEBA0 increments the target's score for itself. Exact/self/equal-index,
index-1 and low-five-bit shifts retain their independent branch behavior.
These observations describe this exact supplied binary, not pristine provenance.

Message output occurs only after accepted alliance, with nonzero late mode,
zero unrestricted and initiator134 nonzero. Localization precedes formatting,
then live rules delay multiplication/conversion, then live initiator-type colorC0.
Display precedes redraw0. Announce is a byte and requires a saved reciprocal
success for speech. The late mode/current-player/134/135 tests can reach the
out-of-line target flag branch. The exact speech key is7DA338. Map sight is added
last on every non-passive return; redraw is not an unconditional epilogue.

Pure field views borrow owners. No eager type access replaces the mode0 bypass;
no preflight alliance check skips the initial score change. Missing entered
services, foreign/null required owners and finite conversion bounds retain
explicit native refusals. Earlier writes survive an exception; no rollback or
original fault parity is claimed. Store observers are nonmutating telemetry.
Initial House/type/score/registry/rules/UI associations remain supplied.

## Verification

Exact executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006, reported no-CD and unverified pristine are distinct.
The verifier fingerprints the entire file, complete634-byte parent including the
out-of-line tail,205-byte score child,61-byte numeric helper and900.0 constant.
No instruction is modified; Unicorn remains research/test-only.

All2,159 fresh original parent sequences match ordered effects/stores and final
mutable records. They enter3,696 actual score calls,882 actual conversions,
3,614 supplied grid calls,882 supplied messages/redraws and847 supplied speech
calls;7 enter the out-of-line tail. Coverage includes all raw House13D/134/135
values, passive bytes, self/duplicate/equal/signed indexes, wrapping scores,
mask120 stores, saved reciprocal result and diagnostic late mode/index/mask/UI
changes. Supplied callbacks are not original-game observations. Caller stack,
callee-saved registers, precise original write domains, code/constant inputs,
whole private arena/padding and global preservation are audited.

Canonical original-only expectations:
`private/boot-camp-20261018/make-enemy-fresh-a1/expected.json`, SHA256
`a9be1650c651a619933d9baf21d2d401ef154e320b3286cdb03cafeea5aacd5e`.
Fresh originals2.472s/native comparison0.064s. Both configured targeted builds,
6 focused normal/6 sanitizer CTests (including the separately selected new domain),
24 Python tests and15 guarded normal/sanitizer/uncached replays pass across
MakeEnemy/notification/MakeAlly/threat/mixed scans. No original comparison failed.
The initial CTest pattern selected the five prior domains; a separate exact new
MakeEnemy domain invocation supplies its coverage in both profiles.

Normal/sanitizer configuration12.517s/12.962s, builds2.079s/1.254s; other check
costs and exact commands are in `make-enemy-build-...-a1.json`,
`make-enemy-validation-...-a1.json` and `make-enemy-domain-a1.json` under the private
research directory. Receipt: `private/boot-camp-20261018/make-enemy-receipt-a1.json`.
Repair and task-wall costs were not measured. App/owner binaries retain the prior
shared-House SDL scope; no runtime code changed or new GUI acceptance is claimed.
No whole inventory/cache/closed finalizer rerun, public code, dependency, worker,
Windows action or runtime executable-read expansion. Local verification is not
independent acceptance; only Apple Silicon macOS is tested.

## Reproduce and continue

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
./test.command
./run.command --boot-camp-walk
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  -m unittest test_house_make_enemy

# Choose new output names; preserve earlier receipts.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/NEW-MAKE-ENEMY.audit.json \
  tests/compare_house_make_enemy.py --exe private/official-1006-probe/game.exe \
  --native build/native/house-make-enemy-vectors \
  --expectations private/boot-camp-20261018/make-enemy-fresh-a1/expected.json \
  --report private/NEW-MAKE-ENEMY.json
```

Use the sanitizer runner or `--uncached` before the driver for other profiles.
Fresh originals require a new `--output` directory and research-only JIT. No new
ordinary SDL control is introduced by this entry.

Next compose notification with both actual diplomacy parents on shared owners,
then bind actual grid/map/redraw/type/image effects and adopt both action37 calls.
Session startup/Team/audio/live scheduling/UI and ordinary SDL Objective1
acceptance remain open. Both games and Objective1 remain incomplete.
