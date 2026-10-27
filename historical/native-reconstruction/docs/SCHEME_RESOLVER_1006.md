# Scheme resolver and complete stock refresh

`SchemeResolver.hpp` recovers complete663D30 and joins it beneath the existing
stock actor/copy/mark/pixel refresh. It reuses `compareStringLookupKeys` for the
actual781F20 locale-zero branch. The composition remains unwired; startup,
nonzero632000 and production coverage are not recovered by this join.

## Exact target, reads and ownership

The supplied private base target remains `private/official-1006-probe/game.exe`,
4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity are distinct. Addresses apply only to this fingerprint.
No public implementation, dependency or runtime executable read was added.

663D30 (90 bytes) reads signed countAB6F08 first. Nonpositive count returns null
without accessing the registry, names or locale. Otherwise it retains the key and
category, reads the registryAB6EFC and visits slots in increasing order. It compares
the current record's name304 through actual781F20 before reading category310.
The registry is reloaded after every comparison, including unequal names. Equal
names check category on the reloaded slot. A match rereads that saved registry's
slot for return. A failure rereads count, increments the signed index and continues
using the saved registry rather than issuing an additional global registry read.

The separate kernel borrows the registry span, count, locale and pure name/category
views. It keeps the saved span across category observations and the next iteration.
Diagnostic return probes can alter fields/global associations at the original
instruction boundaries; those probes are not gameplay observations. Name views
must remain valid through the comparison. Returned record identities are the same
`SurfaceMarkScheme` records consumed by mark palette/index reads; no mirror palette
or lookup cache is introduced. The composed binding borrows the mark service's
same live registry; all records, names and callback owners must outlive calls.

Only locale zero is supported when comparison is actually entered. A nonzero locale
refuses instead of adopting host locale rules. Invalid/null slots and excessive
traversal explicitly refuse; the4096-iteration host limit is a safety bound, not a
recovered original bound or a substituted search result. Count does not imply
backing validity. Null returns are preserved by the standalone resolver; the
existing mark kernel still refuses a missing color scheme/palette. Binding makes
no queries, restores on faults and propagates faults without a rollback claim.

The mark caller uses verified fixed key `LightGrey`, category1. Its private joined
fixture supplies three stable scheme records and two live registries over those
same records. Initial names/categories/count, allocation, class/House/palette and
surface associations remain supplied. Actual initialization is not inferred from
these fixtures. The original fixed-key bytes are fingerprinted as input; they are
not runtime executable reads.

## Evidence and limits

All2,352 isolated sequences match, with two roots each and actual locale-zero CRT
comparisons. Inputs cover signed/nonpositive counts, empty/case-folded/high-byte/
embedded-NUL names, category extrema, both registries, late global/count/name/
category/slot mutations, repeated calls and null results. Comparison and category
probes distinguish the saved slot, the reloaded global and a subsequently replaced
registry. Original instructions execute unchanged only in research Unicorn, with
inspected-code, stack/callee-saved, whole-arena and expected-global guards.

The joined fixture retains a valid matching scheme for the mark caller. Mutation
masks disallow comparison-time registry switching except at slot0 and category-time
switching at slot0. Together with its fixed first/last matching names and last
category1 record, this preserves that fixture precondition while exercising late
registry changes. These are explicit fixture constraints, not restrictions imposed
on the recovered resolver. The isolated proof retains unrestricted supported
mutations and verifies null results separately.

Joined preflightA1 and freshA1 both rejected the initial authored fixture's missing
scheme: its synthetic registry/name mutation could skip its only matching record.
No accepted comparison or expectations were produced. The fixture now supplies a
valid late-registry profile, native preflightA2 passes, and freshA2 is the canonical
composed proof. No original algorithm was changed to return a fallback scheme.
A private name-storage overlap with the inherited pixel region was found and moved
to disjoint storage before originalA1; no execution receipt relies on that overlap.

All1,454 composed sequences match full pixels/locks, bitmap/entries, actors/Houses,
schemes and ordered traces. They include919 complete634030 parents,1,454 actual6324A0
roots,7,016 actual C0/pixel writes,2,739 actual resolver calls and6,632 actual CRT
comparisons. All supplied C0/CC/resolver hook counts are zero. The isolated proof
contains4,704 resolver roots and16,914 actual CRT calls.

Forty-two Python checks, ten focused CTests per profile and30 guarded family
replays pass. Normal/sanitizer/uncached replays retain prior actor, stock-refresh,
copy/mark/pixel fixture outputs. No complete inventory or closed finalizer was
rerun. Original isolated1.398s/native.037s; original joined57.798s/native.100s.
Final configuration2.632s/9.618s, builds9.243s/10.895s. Other build/preflight/check/
replay costs and hashes are recorded in
`private/boot-camp-20261019/scheme-resolver-receipt-a1.json`. Task/repair wall and
failed preflightA1 elapsed were not measured. App/owner hashes retain the previous
106-tick SDL walking baseline; no runtime/GUI adoption or rerun. Local verification
is not independent acceptance or whole-frame fidelity.

Canonical expectations under `private/boot-camp-20261019/`:

- `scheme-resolver-fresh-a1/expected.json`, SHA256
  `eee9dd713242e8cac085d7a2b5d730a56659e43adaa7b6933587575d67c93779`.
- `resolved-radar-refresh-fresh-a2/expected.json`, SHA256
  `bed59e87dcbfb1992dee079487f1cd0ac6fb9a8015461d6c44ac6577fbe26ab2`.

## Commands and next work

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake -S . -B build/native
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake --build build/native --target scheme-resolver-vectors resolved-radar-refresh-vectors
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_scheme_resolver test_resolved_radar_refresh
build/tools-env/bin/ctest --test-dir build/native -R '^(scheme-resolver|resolved-radar-refresh)-domain$' --output-on-failure
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py --audit private/boot-camp-20261019/scheme-local.audit.json tests/compare_resolved_radar_refresh.py --exe private/official-1006-probe/game.exe --native build/native/resolved-radar-refresh-vectors --expectations private/boot-camp-20261019/resolved-radar-refresh-fresh-a2/expected.json --report private/boot-camp-20261019/scheme-local.json
```

Use fresh audit/report names. The isolated driver is `tests/compare_scheme_resolver.py`
and canonical expectations `scheme-resolver-fresh-a1/expected.json` in the same
private dated directory. Fresh original execution replaces expectations/report with
a new `--output` directory and needs host Unicorn JIT permission. Sanitizer runners
are under `build/sanitize`; `--uncached` before the driver disables only immutable
inspection reuse. Original executions and native results are not cached.

Preliminary next inspection is private `surface-nonzero-inspection-a1.txt`: it
shows632000 through63249C ret4, map/floor/discovery/House children and surface
virtuals. This is not a complete-root proof; existing recovered children should be
reused only after confirming these call contexts.

Next recover nonzero632000 and stock surface startup/association, then
coverage refresh/redraw/power and production owned/warm/scan joins. Diplomacy/
action37 and ordinary SDL Boot Camp Objective1 remain incomplete, as do both games.
Existing delivered walking remains `./build.command`, `./run.command --boot-camp-walk`;
`./test.command` remains the broader verification entry. No workers, Windows actions,
downloads, publication or runtime-read expansion.
