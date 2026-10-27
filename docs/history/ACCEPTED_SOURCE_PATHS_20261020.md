# Descriptive accepted-source paths — 2026-10-20

Bounded correction after `836edc7b`, while the full recovery goal remains paused
and unchanged. Exactly **823 already-understood sources** move to descriptive
actual filenames in conservative purpose directories. No source contents change.
The [move ledger](../../manifests/accepted_source_path_moves_20261020.json) records
every original/new path and unchanged source SHA256; historical private
experiments, manifests and receipts remain unchanged.

| Supported family | Files | Representative current path |
| --- | ---: | --- |
| Guarded scaled offset | 331 | [GetGuardedScaledOffset_0040b210.cpp](../../src/recovered/address_offsets/GetGuardedScaledOffset_0040b210.cpp) |
| Word equality | 154 | [EqualWordSequences_0040b610.cpp](../../src/recovered/word_sequences/EqualWordSequences_0040b610.cpp) |
| Word search | 304 | [FindFirstWordIndexGuarded_0040b730.cpp](../../src/recovered/word_sequences/FindFirstWordIndexGuarded_0040b730.cpp) |
| COM persistence | 34 | [SavePersistableCollection_00658940.cpp](../../src/recovered/persistence/SavePersistableCollection_00658940.cpp) |

For example, `src/recovered/00658940.cpp` becomes
`src/recovered/persistence/SavePersistableCollection_00658940.cpp`. No copies or
wrappers remain at old paths. All 5,957 other sources stay unchanged, including
the 17 A11 initializers; their relocation/naming is deferred. Concrete original
game/class identities remain unknown.

## Canonical mappings and generation

`manifests/original_target.json` authoritatively maps every entry to its source.
All metadata except the 823 selected paths is unchanged: IDs, hashes, symbols,
numeric references/relocations, accepted populations/options and source ordering.
The family map, generator plans/output paths and active source links follow that
mapping. No tool derives a canonical filename from an address. The shared stdlib
resolver allows safe nested paths while retaining normalization/containment
checks; the build fingerprints it alongside other authored dependencies.

Understood operations belong in descriptive actual filenames with stable address
suffixes under supported purpose/family directories. Unknown/discovery files may
remain address-only. The index supplements the source tree. This policy applies
during ordinary recovery, not through a permanent cleanup lane.

## Bounded verification

Owner evidence: `private/named-paths-20261020/owner-preservation.json`. All 6,780
canonical source hashes remain unchanged, exactly 823 paths move, all old paths
are absent, and every non-path catalog field is preserved. Three generators emit
789 word helpers, 34 COM serializers and 17 unchanged-path initializers into
fresh ignored review directories. Existing manual comments in 0040b610, 006580c0
and 0046d1f0 survive; candidate differences are comments/whitespace only.

39 focused tool tests pass, including safe descriptive nested paths, filename
policy, traversal/symlink escapes, duplicate/missing paths and generator output
mapping. No option searches, new recovery/original oracles or native/SDL regressions.

The single fresh full build compiled all **6,780 tracked sources in 40 original
population/option groups** from the new paths. Receipt:
`build/named-paths-fresh/build-receipt.json`, SHA256
`a00888781d3bf29d62f2b58936a3d8f79219097f0dfeecd03eed231b710723c8`.
All **4,485,392 packaged bytes** match SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
No prior compiler objects were reused. Input validation through compilation, strict
comparison, linking and packaging took **281.267s**. Word/COM candidate generation
took 0.730s/0.116s; storage generation, separate comparison/link/queue/repair times,
total owner effort and token costs were not separately measured.

The raw linked file remains **7,606,784 bytes** and differs; packaging checks
four logical section payloads and **3,127,748 zero-tail bytes**, then retains
4,096 header bytes, original raw padding and the 272-byte overlay. This is the
same explicit original-metadata boundary, not a raw-linker equality claim.

Independent path/source/tool/index/generator review passed:
`private/named-paths-20261020/coverage-review/named-paths-independent-review.json`.
The second reviewer independently confirmed all source hashes, non-path catalog
fields, candidate plans/output mappings and hostile-path refusals under
`private/named-paths-20261020/recovery-review/`. Both reviews use actual artifacts;
only the owner executed the compiler/linker. The final independent full artifact
review passed in10.929s:
`private/named-paths-20261020/recovery-review/full-build-review.json`, SHA256
`5ec661d8c51cded7b7f7744f379498f71130e097f8cf9d495ba6151b134f1887`.
It rechecked all6,780 actual source/aggregate/object/transfer mappings and
274,985 transferred bytes, strict bindings/complete extents, dependency pins,
logical payloads/zero tails and the complete target output without compiling again.

## Coverage and limits

Coverage remains **6,780 regions / 217,362 body bytes / 57,623 frozen padding bytes**;
**3,494,820 logical `.text` bytes** remain original scaffold. These counts are not
confirmed original function totals. Path organization earns zero recovery credit.
Raw linker output and retained original metadata remain separately reported; exact
packaging is not full decompilation, native porting or playability. No new recovery,
goal change, push or further ongoing work is authorized by this correction.
