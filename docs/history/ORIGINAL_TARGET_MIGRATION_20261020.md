# Canonical source migration — 2026-10-20

Migration baseline: `e159284eb9a771d136ef359824609fd3584117ec` (accepted A10).
This changes repository organization and build reproducibility, with no new
recovery credit and no goal resume. The existing recovery goal is paused.

## Preserved inputs and source

All **6,763** A10 accepted source files, **2,318,875 actual source-file bytes**,
are copied byte-for-byte into tracked `src/recovered/<entry>.cpp`.
`manifests/original_target.json` records each source hash, original entry,
recorded compiler options, symbol selector, reference/relocation expectation,
body/padding/full-extent sizes and hashes, and frozen original population identity.
No original instruction-byte hex, disassembly, proprietary binary, old absolute
source path or timestamped machine path is included in this catalog.

Frozen private acceptance manifest SHA256:
`429cc0e10efac56a089c0ba31234c0d9f917768a2fd9c26c138b162b05939d01`.
Its source hashes remain unchanged. `private/migration-20261020/source-mapping.json`
records old source paths to canonical destinations. Private experiments, accepted
manifests, bound inventories and receipts stay in place unchanged.

The prior native project moves as a coherent source/build/test/doc tree to
`historical/native-reconstruction/`. All **2,968** declared moved files retain
exact content and modes, checked against the pre-move SHA256 snapshot. The tracked
`manifests/native_archive.json` records every mapping/hash. Added local wrappers
and copies provide native documentation entrypoints and preserve license notices;
they do not overwrite immutable snapshots. No native build or regression ran.

## Active pipeline

Tracked `build.py` and `canonical.py` replace the essential ignored authored build
chain. The build consumes root canonical source only, compiling accepted sources
in **39 groups** by original population and recorded option, preserving relative
order. It runs no misses or candidate-search matrix. Private configuration takes
explicit input/tool/bottle/lock/inventory paths, with hashes pinned in tracked
manifests. Clang selection uses explicit configuration or `xcrun`, honoring
`DEVELOPER_DIR` without global changes.

The canonical adapter supplies original bound evidence to the existing strict
V4 acceptance logic. The build rejects source drift/incomplete catalogs, overlaps,
wrong full extents, incomplete original decoding, unbound/unsupported references,
wrong direct-call or DIR32 operands, common symbols and unaccounted emitted code/
data. Verified fresh compiler snapshots supply the transferred bytes; remaining
original scaffolding is generated directly from the hash-pinned private executable.
No ignored authored Python, historical candidate source or accepted object is an
execution dependency.

All four linked logical section payloads and complete virtual zero tails must
pass before packaging retains original headers, raw padding and overlay. The
complete output must equal all supplied bytes. Raw linker output differences
remain explicit. This remains a mixed recovered-source/original-scaffold build,
not full decompilation or a playable native game.

## Verification record

The synthetic tool suite passes **25 tests**, including malformed COFF,
source/hash/catalog refusal, path escapes, extra emitted sections, wrong extents,
original call and DIR32 bindings, and truncated/nonzero virtual tails. The first fresh build completed exact in 277.639s. Independent review then
identified a complete-catalog closure gap: accepting an incomplete submitted set
could otherwise hide omission behind scaffold. The verifier now requires exact
one-to-one equality with the entire ordered canonical compile plan; a dedicated
missing/extra/changed/duplicate/reordered-plan test refuses all six bad plans.

The finalized fresh build at `build/migration-final-a10/build-receipt.json`
completed in **300.992s**: all 39 groups / 6,763 sources freshly compiled, all
215,781 body bytes and 57,572 padding bytes verified, complete packaged output
**4,485,392 bytes**, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
All **3,127,748 zero-tail bytes** were checked. Raw linker output is **7,606,784
bytes** and differs; the final receipt records both parsed PE structures and
retained metadata scope. The initial run is preserved at
`build/migration-fresh-a10/` at its true pre-repair scope. No candidate option
search or unchanged original oracle matrix was rerun.

Independent pre-move classification/source hashes and post-move content/mode,
source metadata parity and dependency review are recorded under
`private/migration-20261020/coverage-audit/`. Independent authored-pipeline review,
synthetic missing-group reproduction and repair review are under
`private/migration-20261020/build-audit/`. Reviewers inspected artifacts and ran
synthetic tests; the build owner executed the compiler/linker. This is not
independent final-phase reproduction. A low-priority TMP/TEMP path-quoting edge
was identified; current simple paths are unaffected and repair is deferred to
the next tool change. Model/token cost and total migration wall time were not
measured; the two complete build costs above include local input validation and
compile/compare/assemble/link/package, not all editing/review/commit time.
