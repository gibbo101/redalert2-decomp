# Radar discovery queries on a shared map

Complete base `568280..5683B4` now joins the existing `568140`, `476AC0`
and `548070` algorithms in the single SDL-free MapVisibility kernel. The scoped
`RadarDiscoveryBinding` replaces both discovery services beneath complete
`632000` and its nonzero `634030` caller, alongside actual stock pixel reads,
writes and lock children. Both queries borrow one table, Cell records, divisor,
direction offset and fallback. Binding makes no queries and restores the previous
services on destruction, including fault exits. This is a verified, unwired
composition; it does not add a playable capability or a production Cell owner.

## Identity and recovered behavior

The supplied target remains 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. `verify_radar_discovery.py` fingerprints
four complete ranges (309/309/86/56 bytes) and checks count/flag/division/call
associations before execution. Original instructions are unmodified.

`568280` divides signed Z by the independent map divisor, then projects X/Y as
signed division by256, truncates to words and subtracts `q/2 + (q&1)` as words.
Division truncates toward zero; negative odd quotients therefore differ from
mathematical ceiling. It uses the combined signed index `Y*512+X`, including
aliases, bounds/null checks and immediate fallback-coordinate assignment.

Unlike primary flag12C bit8 or secondary flag140 bit2 visibility, this predicate
tests **signed count13C > 0**. Odd quotients test the first Cell, return false
immediately on nonpositive count, otherwise call actual neighbor3 and test its
count. The neighbor uses the selected Cell's stored coordinates, adds words and
calls the distinct word lookup. Both paths share the same fallback, so a single
query can write it twice. There is no mode/House/override shortcut in568280.
Native division-by-zero/INT_MIN divided by-1 remains an explicit domain refusal.

The new count field is independent of both flag words. Existing aggregate Cell
views retain a default zero count; they are not silently promoted to production
radar count owners. Read-only query/count observers record diagnostics only.
The joined proof retains the parent's independent mode reads and changes to its
borrowed point between discovery calls, saved pixel table/late receiver, dirty
stores and surface lock/backing ownership. Result callbacks in diagnostic
fixtures apply named supplied mutations after actual child returns; these are
not observed gameplay effects.

## Evidence and limits

- `radar-discovery-fresh-a1`: 1,031 sequences /1,730 complete roots,
  including699 primary queries and743 actual neighbor/word-lookup calls.
- `radar-discovery-pixels-fresh-a2`: 2,409 sequences,1,020 complete refresh
  callers,13,629 pixel parent entries,12,536 primary and12,516 count queries,
  2,375 neighbor/word lookups,10,358 pixel reads and13,240 writes.
- Fresh old Unit discovery:884 results; fresh membership/discovery:560 sequences /
  3,376 sequence calls. Commands, labels and expected outputs exactly retain
  `unit-discovery-v3` and `unit-membership-discovery-v3` respectively.
- Normal/sanitizer domain checks and guarded normal/sanitizer/uncached replays
  cover the two new and four affected families. Replays retain source, binary,
  input, runner and receipt guards. Original execution and native outputs are
  never cached. A rebuilt standalone runner replays the original fresh identity;
  its earlier native source/runner identities remain recorded separately.

The fresh original harness checks entered instruction ranges, allowed writes,
immutable inputs, caller stack/return/callee-saved registers, whole private Cell
arenas and fallback bytes outside the selected coordinate store. Native traces
compare logical query/store order and returned state, not all machine reads or
native store widths. Local verification is not independent acceptance or frame
fidelity.

JoinedA1 matched outputs but failed final source identity validation because a
native cleanup was made while verification was running. Its original expectations,
audit and stdout remain private; A2 is a separate fresh proof after final rebuild,
not a relabeled A1. The first validation script requested two nonexistent Python
module names; corrected to the existing `_evidence` modules in a separate A2 run.
No original algorithm mismatch was accepted. No build failure occurred.

Receipt: `private/boot-camp-20261019/radar-discovery-receipt-a1.json`.
Fresh originals took .593s standalone,28.871s composed,.926s old Unit and14.896s
old membership; native comparisons .040/.168/.034/.095s. Final configurations
2.567/3.026s and builds5.140/5.158s (normal/sanitizer). Earlier builds and focused
checks/replays have separate private timing records. Task/repair wall and
unrecorded shell inspections are unavailable; concurrent times are not a total.

Application/owner hashes retain the prior106-tick SDL walking baseline; no new
runtime/GUI adoption or rerun. Floor55A280, House/type/actor/resolver effects,
initial records/counts/table associations/divisor/direction remain supplied in
this composed profile. Count producers, stock surface startup, coverage/redraw/
power and production warm/scan remain open. Next compose actual floor and the
remaining House/type/actor/resolver children on shared owners. Diplomacy/action37,
ordinary SDL Boot Camp Objective1, base RA2 and YR remain incomplete.

No workers, Windows action, transfer, download, public implementation, dependency,
DRM/system change or runtime executable read was added. Existing pinned public
references remain hypotheses only; this change derives from the local supplied
base binary. No upstream or lifted code was incorporated; no new license notice
is required. Proprietary files and all receipts stay ignored.

## Reproduce

```sh
./build.command
./test.command
./run.command --boot-camp-walk
# New helpers are not adopted by that runtime.
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake \
  --build build/native --target radar-discovery-vectors radar-discovery-pixels-vectors
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/boot-camp-20261019/radar-discovery-replay-new.audit.json \
  tests/compare_radar_discovery.py --exe private/official-1006-probe/game.exe \
  --native build/native/radar-discovery-vectors \
  --expectations private/boot-camp-20261019/radar-discovery-fresh-a1/expected.json \
  --report private/boot-camp-20261019/radar-discovery-replay-new.json
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/boot-camp-20261019/radar-discovery-pixels-replay-new.audit.json \
  tests/compare_radar_discovery_pixels.py --exe private/official-1006-probe/game.exe \
  --native build/native/radar-discovery-pixels-vectors \
  --expectations private/boot-camp-20261019/radar-discovery-pixels-fresh-a2/expected.json \
  --report private/boot-camp-20261019/radar-discovery-pixels-replay-new.json
```

Use new destinations. For a fresh original proof, replace `--expectations` and
`--report` with `--output private/boot-camp-20261019/NEW`; original execution needs
host JIT permission. Sanitizer replay uses the corresponding `build/sanitize/`
runner; an explicit `--uncached` before the compare script disables inspection
reuse. Full exact commands and timings also reside in the private checks record.
