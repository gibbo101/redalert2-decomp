# Mission-control data on the actual Boot Camp GI world

GI House-transfer resume now reads the persistent mission-control table instead
of refusing that lookup. Team admission uses the same owner's Recruitable byte
instead of supplied Guard/Return permissions. Both read the current mission at
their original query point. The stock Return12 path advances to the named
ability16 guard; Guard5 still bypasses those lookups and reaches radar removal.
This unblocks a data dependency of Script20 recruitment before the first Day1
objective transition. No partial transfer clone is adopted and no live Team,
Script20, arrival, sight or SDL objective scheduling is enabled.

## Recovered and inspected behavior

`src/sim/MissionControl.hpp` is SDL-free. Complete594DD0 constructs each record,
leaving padding untouched and preserving the six byte stores and five ordered
dword stores. Rate and AARate start with bits3F90624DD2F1A9FC. Complete4D4520
constructs30 records. Complete594E10 resolves the live index to the corresponding
mission section, with `<none>` for index-1. Complete594DB0 returns1 for mission-1
and otherwise reads Recruitable at the wrapped mission*32 address. Complete
5950D0 uses the same wrapped index addressing. Native accesses refuse addresses
outside the owned table; high-bit aliases whose wrapped address is in the table
retain their original behavior.

Complete594E30 checks the full section-result word, then reads NoThreat, Zombie,
Recruitable, Paralyzed, Retaliate and Scatter in that order. Each read resolves
the live record index again and takes the current byte as its default. Only the
returned low byte is stored. Rate uses its current double as default. The next
index is sampled before storing Rate, and AARate uses positive-zero default.
AARate is stored before testing the original x87 comparison's C3 bit. Both equal
zero and unordered (NaN) copy the live Rate with two ordered dword stores; both
words are loaded before the first copy store. This is not a plain `aa==0` test.

The bounded INI-return domain covers finite binary64 values, signed zero,
subnormals, infinities and quiet NaNs. Signaling-NaN returns explicitly refuse;
extended-only return values, exception-status equivalence and original INI
parsing are not proved. Named INI children50C9B0/50F410/50E3A0 remain supplied
services. Existing authored boolean-value behavior is reused by the runtime
adapter, but the full original INI implementation is not claimed recovered.

The6524F2..65250D Rules-parent loop is inspected, not executed as a complete
original parent: it writes indices0..29 immediately before each594E30 call.
Boot Camp uses that sequence on its existing Rules input. General Rules/map
layering and startup are supplied; nonempty map mission-control overrides refuse
rather than inventing precedence. The authored `Ini` now retains empty section
headers and exposes their presence. The actual table is copied as mutable value
storage by world cloning; callbacks borrow each clone's owner synchronously.

The existing complete4F52F0 House-control implementation now borrows the current
mission House and mode during resume. Other entered branches remain guarded,
including House194 and ability16; TypeB00 and other downstream children remain
unbound. Do not replace them with guessed defaults or clear the real Team.

## Evidence

All addresses require the supplied4,485,392-byte executable SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain separate. No public authored code, dependency,
Windows operation or new runtime executable read was introduced.

1,028 original sequences verify complete constructor/INI/name/recruitability/
lookup code and the complete30-record constructor. Cases cover every section,
missing/present full-word results, raw returned flags, wrapped address aliases,
Rate/AARate cross-products, untouched padding and five explicit live mutations.
The oracle guards original instructions, constant/name inputs, caller ABI, arena
bounds and ordered store widths. Named INI return values and initial records
remain supplied. These tests do not execute complete503C00 or the whole House
transfer with the new table; prior parent proofs retain their separate scope.

The actual-world checks separately bind the existing GI/House/Team owners. They
verify stock Return flags and index, warm clones/source isolation and live-table
consumption: setting the cloned Return Zombie byte to255 skips ability16 and
reaches the existing radar-removal refusal. No altered table is adopted by play.
This is native ownership/branch evidence, not original full-transfer acceptance.

Canonical originals: `private/mission-control-20261020/fresh-a5/expected.json`,
SHA256 `f4d773b41df1bf8c82ed8c963e275cb566ec323d91c15e4490a624499624b6e5`.
Final table replays: `validation-a2/final-mission-control-{native,sanitize}.json`.
The executable/oracle/inputs/environment provenance is separate from current
native source/runner identities. Native-only changes replay the originals while
rerunning native comparisons and guards. `SOURCES` limits the outer guard to the
actual dependency closure; unrelated checkout files are not proof inputs.

```sh
./build.command
./run.command --boot-camp-walk
./test.command
PYTHONPATH=tools:tests PYTHONHASHSEED=0 build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/mission-control-next.audit.json \
  tests/compare_mission_control.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/mission-control-vectors \
  --expectations private/mission-control-20261020/fresh-a5/expected.json \
  --report private/mission-control-next.json
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_mission_control
build/native/boot-camp-walk-check private/official-1006-probe
```

Use new audit/report paths and `build/sanitize/mission-control-vectors` for a
sanitizer replay. Fresh generation uses a new `--output` folder instead of
expectations/report and requires permitted research JIT access on this Mac.
Only generate again when actual original dependencies change. Final commands,
costs, repair history and coverage are summarized in the opening HANDOFF.

Only Apple Silicon macOS is tested. The sanitizer SDL app is not built. Ordinary
SDL walking and presentation retain their existing supplied boundaries. There
is no new playable tutorial transition, whole-frame fidelity or complete game
claim. Local verification is not independent acceptance. Next recover/bind the
entered ability16/TypeB00 resume path, then existing radar424/420 owners and the
wrapper before Script20 scheduling and ordinary first-objective acceptance.
