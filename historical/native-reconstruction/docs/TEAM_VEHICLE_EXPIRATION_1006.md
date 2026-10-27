# Unit and Aircraft Team expiration — supplied base

Complete Unit707E90 and Aircraft41ADB0 now call the existing complete Foot
expiration kernel, then clear their own distinct references in original order.
This closes the algorithmic recipient gap found while auditing Team34's actual
registry: the map contains five GIs, a cow, a miner and a helicopter. The latter
two require these overrides. Actual recipient/registry ownership remains unbound;
this checkpoint enables no live teardown, scheduling or new playable behavior.

## Recovered behavior and evidence boundary

Each override is56 bytes/19 instructions, ending in `ret8`. It saves the subject
identity and actor across complete4C8460, reads the derived Type field after that
call and clears a match, then reads/clears5AC. Unit uses5B0; Aircraft uses5B4.
Neither field aliases Infantry5A8. Both derived clears occur regardless of the
removal word; inherited Object/Foot effects retain their low-byte conditions.
The inherited algorithms are shared, not copied into the new wrappers.

Exact supplied executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain separate. Full wrapper fingerprints:

| Root | SHA256 | Primary vtable virtual28 |
| --- | --- | --- |
|707E90|`0166cfcb183802606a92893cca7494e97cdf5c6810daddfbd9da5dc8077baa77`|7ADDF8|
|41ADB0|`c510c6b54abab1c943d085186deca1ea2feb7010133f8879beb71d9963abb4d7`|79B12C|

708 original sequences execute1,436 complete overrides (718 each) and their
actual inherited Foot/Techno/Radio/Object roots, with a distinct actual-Team-vtable
subject and retained real/null ObjectTag. Cases include matching/null/foreign
fields, removal0/256/1/257/FFFFFFFF, repeated calls and supplied predicateC child
mutations that set or remove matches before the wrapper reads its fields.
228 inherited scenarios retain existing vector/reference/timer/child coverage.
Ordered stores, arena integrity, input regions, caller stack and preserved
registers are checked. Named gameplay queries/effects, RNG, initial vectors and
startup remain supplied. No subject-Owner/coordinate/map child is entered.

This verifies the bounded Team-subject handlers, not actual miner/helicopter
startup, registration order, full original-composed gameplay or Tag-subject
vehicle behavior. No public authored implementation/dependency was incorporated.
Original instructions are unmodified and execute only in test-only Unicorn.

The first attempt generated its own original answers but failed native comparison
because the fixture seeded the inherited scratch slot at the old Foot entry depth.
The derived wrapper adds20 bytes of stack before Foot; a2 supplies the existing
scratch input at STACK-68 instead of STACK-48. The application algorithm did not
change to fit that fixture error. Failed a1 audit/results remain preserved.

## Validation, reuse and costs

Canonical original-only expectations:
`private/team-foot-owners-20261020/fresh-a2/expected.json`, SHA256
`1623885062179e427c7d2b788b68603af4cfc8fef43d4ad83291ff4f09e167f4`.
Original generation5.924s, fresh native comparison/guard checks.106s. Normal
explicit reuse validates708 new,228 existing Team Foot and871 existing Tag
sequences:1,807 hits/zero misses, always executing rebuilt current native.
The earlier families' original answers/sources remain unchanged.

Normal and sanitizer each pass7 focused CTests;19 Python tests pass. Each
profile explicitly replays1,807 originals with zero misses. No integrated gameplay boundary changed, so unchanged broad original
matrices, actual-world/SDL journey checks and inventory finalizers were not rerun.
Only Apple Silicon macOS is tested; these local checks are not independent
acceptance or whole-game/frame fidelity.

Normal replay processes:vehicle.558s, Foot.477s, Tag.629s; focused CTest process
.660s (7 tests/.09s reported test wall time), Python process.788s (19 tests/.526s
reported test time). Sanitizer configure34.933s and focused build5.607s.
Sanitizer replay processes:vehicle3.634s, Foot1.954s, Tag2.931s; focused CTest
process.721s (7 tests/.22s reported test wall time). Initial normal configure/build,
inspection/edit/repair/review and total elapsed
costs were not separately measured. Some operations overlap; times are not additive.
Full commands/logs/costs live in private/team-foot-owners-20261020/validate.py and
validation-a1/. No native verdict caching or unchanged-original regeneration.

## Reproduce and continue

```sh
./build.command
./run.command --boot-camp-walk
./test.command
PYTHONPATH=tools:tests PYTHONHASHSEED=0 build/tools-env/bin/python -B \
 tools/run_evidence.py --audit private/NEW-vehicle.audit.json \
 tests/compare_team_vehicle_expiration.py \
 --exe private/official-1006-probe/game.exe \
 --native build/native/team-vehicle-expiration-vectors \
 --expectations private/team-foot-owners-20261020/fresh-a2/expected.json \
 --report private/NEW-vehicle.json
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest \
 test_team_vehicle_expiration test_team_expiration \
 test_mission_typed_tag_expiration test_mission_techno_tag_expiration
```

Use the sanitizer runner and fresh report/audit paths for sanitizer replay.
Next bind complete recipient views over all eight actual map Foot owners,
borrowing existing GI/House/Walk/mission/Tag/Team fields and persistent vectors.
Audit missing fields, clone/remap every pointer and preserve real identities;
do not mirror existing fields or adopt partial clones. RegistryAC0C18 startup/
order and Neuron association remain supplied/unverified and must be made explicit.
Then complete A3D264 observer callbacks and entered Tag/base lifetime children
before actual exhausted tick8 adoption, movement verification and genuine tutorial
scheduling. Do not skip passive recipients or introduce no-op children. Both games
remain incomplete. No workers, Windows actions or runtime executable-read growth.
