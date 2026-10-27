# Scenario SpecialFlags and Boot Camp sight

The scenario first dword consumed by499FC0 is the SpecialFlags word. Complete
68B320 initializes it and complete68B5A0 reads thirteen keys from SpecialFlags.
FogOfWar is bit12 (1000), the late local-refresh gate identified previously.
Both supplied training maps explicitly contain FogOfWar=no. Their content and
this recovered caller establish why ordinary training sight does not enter
47BE00 through this gate; a previously supplied zero alone did not establish it.

This removes a concrete startup dependency before the first Boot Camp discovery
transition. Tick/arrival/SDL scheduling remains disabled; objectives remain
incomplete. Local refresh47BE00/47BE60 still needs recovery for entered profiles,
but is not a prerequisite merely because it appears in a callback list.

## Recovered boundary

The supplied base target is4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. No public implementation/reference code
or new dependency was used. Inspected constructor65B4F0 calls68B320 on the
scenario itself; startup5116A0 stores the resulting scenario atA3D290. Inspected
661980 passes its INI argument and scenario this through to68B5A0. These containing
callers/constructors are inspected only, not completely executed/reconstructed.
Private disassembly stays in scenario-flags-inspect-a1, outside Git.

Complete202-byte68B320 clears the low three bits before its registry requests.
It opens HKLM's Red Alert 2 key with accessF003F, queries four-byte EscapeMovies
only on successful open and closes every successfully opened handle. Query
success plus type4 admits only data bit0. The final store rereads the flags,
preserves maskFFF88087, sets8080 and stores the selected bit at position3.
Registry calls are explicit supplied child services, never host registry access.
The app chooses registry absence and an incoming word0 as portable supplied
policies. This is not recovered allocation, full constructor or Windows registry
emulation. High/unmanaged startup bits are not established by this fixture.

Complete567-byte68B5A0 reads, in order:

| Key | Bit |
| --- | ---: |
| TiberiumExplosive | 14 |
| MCVDeploy | 8 |
| InitialVeteran | 9 |
| IonStorms | 17 |
| Meteorites | 16 |
| Visceroids | 18 |
| TiberiumGrows | 6 |
| TiberiumSpreads | 7 |
| DestroyableBridges | 15 |
| FixedAlliance | 10 |
| FogOfWar | 12 |
| Inert | 5 |
| HarvesterImmune | 11 |

Each default preserves AND AL,1 rather than truncating the full pushed dword.
Each result consumes bit0 and rereads the live word before replacing that bit.
After six reads, nonzero sessionA3D298 with zero overrideA40D13 skips the last
seven. Both globals are read after those callbacks, not saved at entry.
Supplied children deliberately mutate flags/session/override to test that order.
GetBool is a supplied probe in this complete-parent proof. Application INI
association uses the existing recovered locale-zero first-byte Boolean boundary;
the text/index decoder and session0/override0 association remain supplied.
Initializer return-register leftovers are not used as an application result.

## Actual owner and verification

The existing BootCampVisibilityWorld scenario byte vector now owns the word,
alongside its existing waypoint records. No second scenario/visibility mirror
was introduced. Default Cell/sight/waypoint changes call the late getter against
those bytes; explicit optional snapshots retain diagnostic override behavior.
Clones copy/rebind the actual owner, and getter calls capture this rather than
a source buffer. The Day1 word is8080 under the stated portable startup policy;
its FogOfWar bit comes from the actual original map. A test-only warm clone
sets that bit, verifies a refresh request against its actual Cell, checks explicit
zero override/source isolation, then verifies a further clone after source
destruction. That refresh child remains supplied: a request is not the animation/
vector effect or a live objective. Ordinary Day1 behavior retains the disabled
bit and all existing actual-owner movement/sight/mission regressions.

613 original sequences execute273 complete initializers,343 complete readers
and3,920 supplied GetBool probes. They cover open/query success/failure/type,
low-bit selection, preserved unrelated bits, raw defaults, both session branches,
live word/global mutations and joined actual training Boolean inputs. Original
code, strings/tables, complete arena outside named fields, caller stack/return
and callee-saved registers are guarded. Registry and GetBool children are supplied;
these are isolated routines, not original-game observations or full startup.
Both profiles explicitly reuse613 originals with zero misses and always run
current native. Canonical results:
`private/boot-camp-20261020/scenario-flags-fresh-a1/expected.json`.
The unchanged578-case late-load and192-case fixed-snapshot proofs retain their
previous commit scopes; neither core nor those native input producers changed.

Standard201 and ASan/UBSan200 CTests, test.command, eight focused Python tests
and both rebuilt actual Boot Camp owner profiles pass. No SDL acceptance is
claimed for an unscheduled sight change. Original generation.304s, fresh outer
audit.836s, native replay outer audit.743s, normal CTest13.33s. Full replay/
sanitizer costs, hashes, commands and unmeasured build/owner/repair/total wall
costs are in scenario-flags-receipt-a1.json under the same private directory.
No original/native comparison or build failure occurred; no unchanged original
matrix was regenerated. Local verification is not independent acceptance.

```sh
./build.command
./test.command
./run.command --boot-camp-walk
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest \
  tests/test_scenario_special_flags.py tests/test_cell_visibility_live_flags.py
# Use fresh report/audit paths for every run.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/scenario-flags-next.audit.json \
  tests/compare_scenario_special_flags.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/scenario-special-flags-vectors \
  --expectations private/boot-camp-20261020/scenario-flags-fresh-a1/expected.json \
  --report private/scenario-flags-next.json
# Substitute build/sanitize/scenario-special-flags-vectors for sanitizer replay.
```

Next finish the actually entered position/membership effects and their complete
Walk/Cell-crossing producers on these same owners before live sight scheduling,
then viewport/queue consumption and required mission children for ordinary SDL
Objective1. Full scenario loading, shared flags for other game subsystems,
registry persistence, FogOfWar-enabled local refresh and both complete games
remain open. Only Apple Silicon macOS is tested. No new runtime executable read,
Windows action, system change, download or proprietary tracked data was added.
