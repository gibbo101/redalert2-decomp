# Bounded catch-up of accepted source — 2026-10-20

Baseline `f63b6362`. The user authorized one finite pass over already accepted
source while the sustained goal remains paused and unchanged. No new recovery,
body-byte credit, new chat, permanent cleanup lane, whole-tree move or architecture
reinvention is part of this pass. [Source index](../RECOVERED_SOURCE_INDEX.md).

This records the completed catch-up through `836edc7b`. The later
[filename correction](ACCEPTED_SOURCE_PATHS_20261020.md) moves these same 823 files
without source-byte changes; source hyperlinks below now navigate to current paths.
Earlier receipts and the path choice described here remain historical evidence.

## Selection and actual changes

The selected A3/A4/A11 families contain **823 sources**: 331 guarded scaled
offsets, 154 word-sequence equality methods, 304 searches (151 guarded/153 ordinary)
and 34 COM collection serializers. They cover **36,316 already-accepted body bytes
and 5,492 existing padding bytes**; none is new recovery.

All 823 functions have descriptive operation names with stable eight-digit address
suffixes. At that checkpoint, examples retained their address-only source paths:

- `recover_658940` becomes `SavePersistableCollection_00658940` in
  [00658940.cpp](../../src/recovered/persistence/SavePersistableCollection_00658940.cpp), preserving its fastcall-compatible
  `@8` ABI, actual import/IID bindings and every failure/reload/Release quirk.
- `WordOffset_40b210::get` becomes `GetGuardedScaledOffset_0040b210` in
  [0040b210.cpp](../../src/recovered/address_offsets/GetGuardedScaledOffset_0040b210.cpp), without assuming bounds/alignment
  checks, a signed distance or a concrete container identity.
- `Loop_40b610::get` becomes `EqualWordSequences_0040b610` in
  [0040b610.cpp](../../src/recovered/word_sequences/EqualWordSequences_0040b610.cpp); equal nonpositive counts still succeed.
- `Loop_40b730::get` becomes `FindFirstWordIndexGuarded_0040b730` in
  [0040b730.cpp](../../src/recovered/word_sequences/FindFirstWordIndexGuarded_0040b730.cpp); false gate zero remains distinct
  from exhausted-search minus one.

The 789 old one-line word-helper sources now use conventional multiline formatting,
supported parameter/local names, purpose/address notes and explicit uncertainties.
Four bounded shared storage views replace repeated field declarations. Per-address
synthetic owner classes remain separate, so equal observed offsets do not assert
original class identity. The COM family continues to use its existing shared view.

Both family generators/templates emit fresh ignored review candidates. They never
write canonical source/manifests. Manual comments in 0040b610 and 006580c0 survived
actual regeneration; all 823 canonical hashes remained unchanged. Source-tree,
existing-output and escaped/symlink destinations refuse. Thirty-five synthetic
tool tests pass; an initially exposed macOS /var path-alias test failure was fixed
before compilation and preserved at its actual non-fidelity scope.

The tracked index groups supported operations by purpose, maps member addresses to
canonical named symbols/source paths, and explains data/interfaces, interactions
and unknowns. No accepted reference-map edges into these entries are currently
present; frozen original caller references remain evidence, not an assertion that
original callers do not exist. No game subsystem identity is invented.

## Deferrals and unchanged coverage

All other **5,957 sources** are unchanged. The 17 readable A11 initializers are
indexed without repeating their cleanup. Opaque accessors, math identities,
factory/lifetime helpers and broad class relationships are deferred. In particular,
cleanup field roles are ambiguous and guarded global-copy aliases deserve their
own evidence scope; neither became a new research assignment. Address filenames
were retained at that checkpoint. The later filename correction supersedes this
choice for the 823 understood operations; unknown/discovery files may remain address-only.

Canonical intervals, original populations/options, ordering, body/padding/full
extent hashes and numeric reference/relocation bindings are unchanged. There are
still **6,780 regions /217,362 body bytes /57,623 padding bytes /3,494,820 remaining
logical `.text` scaffold bytes**. Counts are not certified function totals or a
whole-game percentage. Naming, formatting and layout organization add zero bytes.

## Verification and evidence

Private bounded scope/source snapshots, candidate versions, manual-regeneration
receipts and reviews are under `private/catchup-20261020/`. Original A3/A4/A11
experiments/manifests/receipts remain unchanged. No candidate-search option matrix,
new original boundary investigation or unrelated native/SDL test was rerun.

Focused accepted-only comparison compiled four original population/option groups:
all **823 complete extents and actual bindings** match, **36,316 body bytes +5,492
padding bytes**, **39.672s** including input validation/compile/comparison. Receipt:
`private/catchup-20261020/focused-exact/focused-scope.json`. Both existing bounded
review lanes independently checked source/templates/storage offsets/ABI and the
actual fresh COFF/bindings. Owner executes the compiler; artifact review is not
an independent compiler reproduction. No source candidate changed compiler bytes,
so no candidate needed reversion or deferred-fidelity treatment.

The final fresh combined build is recorded below; final independent artifact
review receipts are retained with the bounded evidence. Source-quality policy in `f63b6362` remains the ongoing procedure;
this one-time catch-up does not become a repeated obligation or resume the goal.

## Fresh complete build

`build/catchup-fresh/build-receipt.json` records fresh compilation of all
**6,780 canonical tracked sources in40 original population/option groups**,
including both shared headers, followed by strict extent/binding checks, actual
assembly/link and complete packaging validation. Duration: **282.520s**.
The **4,485,392-byte** packaged file matches every supplied byte, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Receipt SHA256 `3827f2cd5cca62713f91da77e94fa10e63557899bc386ee7bfe842cf6157b28a`.

All **3,127,748 zero virtual-tail bytes** pass. Raw linker output remains
**7,606,784 bytes** and differs; original headers/file padding/overlay are retained
only after logical payload and zero-tail validation. Exact matching still uses
3,494,820 logical `.text` scaffold bytes; this is not full decompilation/playability.
Original compiler populations/options, all body/padding/extent hashes, source
ordering and numeric bindings remain unchanged. Actual COFF containers and symbolic
names change as expected; full resolved machine extents do not.

Both existing medium review lanes independently checked proposal/semantics, actual
focused COFF and final full artifacts under `private/catchup-20261020/review/` and
`recovery-review/`. The owner ran the compiler/linker; no peer compiler reproduction
is claimed. Token/model effort and total human/conversation wall cost are unavailable;
recorded scope timings are not whole-task efficiency measurements.

The one-time pass is complete. The sustained goal's condition and paused status are
unchanged, and no ongoing recovery is assigned or launched after this checkpoint.

Provenance version scopes: `private/catchup-20261020/source-changes.json` preserves
the initial pre-comment-repair proposal. Its after-hashes are superseded by
`source-changes-final.json`, which records all823 actual before/after source hashes
including the clarified loop comments and manual canonical explanation. That final
ledger was written before focused/full compilation and matches the canonical
manifest; the initial receipt is not relabeled or reused as the final ledger.

Final independent review: `private/catchup-20261020/review/final-catchup-independent-artifact-review.json`.
The peer read/hash/COFF/relocation/payload checks took5.821s without compiler/linker
execution. The independent review of index mappings is separately retained in
`review/source-index-independent-review.json`.

The second final independent strict/artifact review is
`private/catchup-20261020/recovery-review/full-build-review.json`, SHA256
`666491c25ea3999bcc8273512de30042178ed56664eec2431d40726ffdbc5d76`.
It took43.358s without compilation. Its `canonical-change-closure.json` confirms
exactly823 changed source hashes and5,957 unchanged, with all original numeric
coverage/options/bindings/order metadata unchanged. No final review findings remain.
