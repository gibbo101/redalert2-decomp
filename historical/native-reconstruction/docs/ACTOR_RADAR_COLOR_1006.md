# Stock actor radar colors and complete refresh

The separate `ActorRadarColor.hpp` recovers complete stock Infantry/Building C0
and CC queries, reusing the existing recovered House alliance predicate. Its scoped
binding joins those queries below the single copy/mark/pixel refresh composition.
This is an unwired rendering dependency; resolver663D30 and startup remain supplied.

## Exact target and behavior

The private supplied base executable is `private/official-1006-probe/game.exe`,
4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Addresses apply only to this fingerprint.
No public code, dependency or runtime executable read was added.

Both verified stock classes use41B410 (7 bytes), returning actor byte170 in AL.
Building CC uses41B2E0 (5 bytes) and returns null without consulting its argument
or House fields. Infantry CC uses509270 (61 bytes): save current HouseA35DB4,
call actual4E5540 with Owner1B4, then inspect the argument's low byte. Allied plus
zero returns the reread Owner; otherwise a reread alternate410 wins if nonnull,
else the reread current global wins. The alliance call happens even for nonzero
arguments. The shared4E5540 predicate retains null/current identity shortcuts,
signed House index30 comparisons and masked shift semantics over allies5674.
Do not merge these fields with the mark House scheme index15F40.

`ActorRadarColorBinding` installs only C0/CC and restores both on normal exit or
fault. Construction makes no queries. Actor and House views borrow live fields;
Owner/alternate/current are reread at their actual points. Kind/vtable association,
initial fields and diagnostic return probes remain supplied. There is no gameplay
observation or startup recovery claim. The binding and borrowed owners must outlive
entered calls; faults propagate without a rollback claim.

## Differential verification

The isolated proof covers4,224 sequences, each with one C0 and two CC roots:
12,672 audited original roots. It enters Infantry/alliance6,144 times each and
Building2,304 times, covering null/current/alternate choices, signed index aliases
and extrema, argument low bytes, repeated calls and late-field mutations.
All sequences match. Original generation1.032s, native comparison.037s.

The composed proof uses genuinely distinct actors with0x800 stride so field410
cannot overlap the next actor. Entries point to those actual records and the
stock class-specific virtuals execute on them. Diagnostic owner/entry mutations
and final projections resolve the same records. Surface geometry, pixels and
locks retain the existing shared owners. The old unused fixture records remain
private guarded data; no production conversion is implied. Supplied C0/CC hooks
must never execute. Resolver663D30 remains a named supplied child.

All entered original instructions remain unchanged and guarded by exact inspected
spans. Stack/callee-saved, input-code, whole-arena, permitted-write and current
House global guards remain enabled. Diagnostic mutations are authored probes,
not original in-game observations. Original instructions execute only in research
Unicorn; native runtime adoption, whole-frame fidelity and independent acceptance
are not established by these tests.

All1,334 composed sequences match, including859 complete634030 parents,
1,334 actual6324A0 roots,6,416 C0/pixel writes,3,993 Infantry/alliance calls and
2,038 Building CC calls. Supplied C0/CC count is zero; resolver remains supplied
2,139 times. Copy enters859 times with852 actual transfers. Full pixels, locks,
bitmap, entries, actors/Houses and ordered traces are compared. Original generation
48.666s/native comparison.091s; final configs7.077s/8.614s and builds4.069s/7.858s.

Thirty-three Python checks, eight focused CTests per profile and24 guarded
normal/sanitizer/uncached family replays pass. Affected prior mark/copy fixtures
retain their old projections. No complete inventory or closed finalizer was rerun.
Application/owner hashes retain the previous106-tick SDL walking baseline; no GUI
rerun or runtime adoption occurred. Check/build/preflight costs and hashes are in
`private/boot-camp-20261019/actor-radar-color-receipt-a1.json`.
Task/repair wall and the extra first native rebuild were not measured.

Joined attemptA1 completed original roots but failed trace validation because its
new alliance event reused existing height tag H. No accepted expectations/comparison
result was emitted. The diagnostic-only label changed to J in original/native and
a regression validates both labels. FreshA2 passed; failed audit remains private.
No algorithm repair or native/original comparison mismatch occurred.

Canonical expectations under `private/boot-camp-20261019/`:

- `actor-radar-color-fresh-a1/expected.json`, SHA256
  `86344f5218f9e3bdec1947a0c5f819f0f6fc5f82da3e10d582d08de3c06935ad`.
- `stock-radar-refresh-fresh-a2/expected.json`, SHA256
  `0999d593c00f5483e3b1b4b7befb1c36aa49835049c5ed6f6c5d63a8464e7b5d`.

## Commands and remaining integration

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake -S . -B build/native
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake --build build/native --target actor-radar-color-vectors stock-radar-refresh-vectors
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_actor_radar_color test_stock_radar_refresh
build/tools-env/bin/ctest --test-dir build/native -R '^(actor-radar-color|stock-radar-refresh)-domain$' --output-on-failure
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py --audit private/boot-camp-20261019/radar-local.audit.json tests/compare_stock_radar_refresh.py --exe private/official-1006-probe/game.exe --native build/native/stock-radar-refresh-vectors --expectations private/boot-camp-20261019/stock-radar-refresh-fresh-a2/expected.json --report private/boot-camp-20261019/radar-local.json
```

Use new audit/report paths. The isolated driver is `tests/compare_actor_radar_color.py`
and its canonical expectations are `actor-radar-color-fresh-a1/expected.json` in
the same private dated directory. Fresh proof replaces expectations/report with a
new `--output` directory and requires host Unicorn JIT permission. Sanitizer runners
are under `build/sanitize`; `--uncached` before the driver disables inspection reuse
while retaining evidence guards. Original executions and native results are not cached.

Next recover663D30 on live scheme registry/name/category fields, reusing the
verified locale-zero781F20 comparison only where its precondition holds. Current
resolver inspection is preliminary, not a differential proof. Nonzero632000,
stock surface startup, coverage/redraw/power, production owners/warm previews/scan
and diplomacy/action37 remain open. Ordinary SDL Boot Camp Objective1 and both
games remain incomplete. Try existing delivered walking with
`./build.command` and `./run.command --boot-camp-walk`; `./test.command` remains
the broader entry point. No workers/Windows/downloads/runtime-read expansion.
