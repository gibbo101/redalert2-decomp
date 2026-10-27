# Late scenario flags in Cell visibility change

Subsequent [SpecialFlags recovery](SCENARIO_SPECIAL_FLAGS_1006.md) identifies
the first dword, loads it into the existing scenario owner and binds default
Cell/sight/waypoint callers to this late getter. FogOfWar is bit1000; both
training maps explicitly disable it. Earlier fixed-snapshot receipts and startup
limitations below retain their historical scopes. Full scenario startup, entered
local-refresh children and live sight scheduling remain incomplete.

`changeCellVisibilityWithLiveRefreshFlags` preserves the complete499FC0 parent's
late read of globalA3D290 and its first dword. This removes a snapshot assumption
before binding genuine Boot Camp sight/discovery to callbacks that can change
scenario state. It does not enable that runtime path or advance an objective.

The original order is discovery568520, reread Cell140 bit1, test the saved
entry-bit predicate, load globalA3D290, load its first dword, test bit1000, then
call47BE00. Redraw/discovery can therefore change the word, replace the global
pointer or clear Cell140 bit1 before the decision. An entry with bit1 already
set never reads the scenario flags, even if a child clears and sets it again.
The new getter runs only at that exact late boundary and must reread the owning
association. An empty getter refuses only when entered; no original null-pointer
fault parity is claimed. The existing scalar facade deliberately retains its
supplied fixed snapshot, including all existing application callers.

The name `refreshRules` in earlier interfaces is not evidence that this is a
RulesClass field or a recovered INI option. This proof leaves the scenario first
dword's meaning/startup/update producers unknown. In particular,
BootCampWalkWorld currently calls revealSight with the supplied default0, so its
explicit sight compositions do not enter47BE00. Neither that profile nor a
callback counter proves the original tutorial's startup value. Do not recover
an unentered animation/vector destruction branch merely to finish a callback
list. Establish the actual source value or an entered tutorial path first.

## Evidence

Exact supplied base:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. The new verifier pins the complete
existing wrapper/parent/map/counter spans plus the late loads/gates/call.

578 isolated complete wrapper/parent calls pass. Their actual map/counter
children execute original instructions; visibility masks, redraw, discovery and
refresh are explicitly supplied child probes. The matrix covers both entry
bits, both first-word1000 values, both post-callback values, pointer replacement
versus in-place mutation, redraw versus discovery versus no mutation, live
Cell-bit clearing/setting, both low-byte counter branches and actual/fallback
Cells. Two unchanged cases skip all callbacks and the scenario load. The
original enters224 late loads and112 refresh probes, with288 decrement and290
increment children. It preserves full ordered traces, final scenario pointer/
words and Cell fields. Code/inputs/whole arena and fallback guards, allowed
Cell writes, caller stack/return and callee-saved registers remain checked.
No lifted code, public implementation, new dependency or runtime executable
read was added. This is isolated differential evidence, not original-game
observation, independent acceptance or whole-game fidelity.

Canonical originals:
`private/boot-camp-20261020/cell-live-flags-fresh-a2/expected.json`.
The fresha1 and its normal/sanitizer replays also passed, but its outer audit
guard unnecessarily hashed the whole source checkout. A2 declares the actual
Python/native dependencies through the existing SOURCES protocol. Its changed
driver identity requires a distinct origin; a1 is preserved, not relabeled.
Original generation takes.830s; the outer fresh audit takes1.710s versus
89.936s for a1. This fixes this driver's guard scope using existing infrastructure,
not a new cache. Replays always run rebuilt native code. Old192-case original
expectations remain unchanged and explicitly reused.

Both native profiles pass the578 new comparisons and192 existing comparisons
with770 hits/zero misses each. Standard200 and ASan/UBSan199 CTests, the normal
test.command Python checks, seven focused Python checks and both rebuilt actual
Boot Camp owner checks pass. Their application path still uses the fixed0
snapshot; the actual-owner checks are regression evidence, not proof of live
scenario startup or callback mutation there. No SDL acceptance rerun is needed
for this unscheduled API addition. Native CTest17.71s, sanitizer49.42s;
build/configuration/owner/inspection/edit/repair/total wall costs were not fully
instrumented. A focused Python test initially expected the wrong Cartesian
case count (1154 rather than578); corrected without changing scenarios or
results. No original/native comparison or build failure occurred. Full hashes,
audit/replay costs and unavailable measurements belong to
`private/boot-camp-20261020/cell-live-flags-receipt-a2.json`.

## Commands and next binding

```sh
./build.command
./test.command
./run.command --boot-camp-walk
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest \
  tests/test_cell_visibility_change.py tests/test_cell_visibility_live_flags.py

# Choose a fresh report/audit name. Reuse only original answers; run current native.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/cell-live-flags-next.audit.json \
  tests/compare_cell_visibility_live_flags.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/cell-visibility-live-flags-vectors \
  --expectations private/boot-camp-20261020/cell-live-flags-fresh-a2/expected.json \
  --report private/cell-live-flags-next.json
# Substitute build/sanitize/cell-visibility-live-flags-vectors for sanitizer replay.
# Retain the existing192-case replay command in CELL_VISIBILITY_CHANGE_1006.md.
```

The next useful binding must identify actual scenario flags/lifetime alongside
the actual position/visibility/mission owners, preserving this late read through
real discovery children. Remaining position/membership effects, viewport/queue
consumption and required mission children still precede live Objective1. A
recorded discovery or local refresh request is not objective success. Both games
remain incomplete; only Apple Silicon macOS is tested.
