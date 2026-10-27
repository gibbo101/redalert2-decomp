# A11 — readable families and shared COM declarations

Current source hyperlinks follow the later byte-identical [filename correction](ACCEPTED_SOURCE_PATHS_20261020.md); A11 receipts retain their historical paths.

Migration baseline: `d190902` after the accepted A10 source/archive relocation.
This bounded checkpoint implements the user-approved readability standard while
retaining the existing two medium workers and paused sustained-goal lifecycle.
No whole-tree cleanup, native adaptation or new pilot was started.

## Recovery versus maintainability

New recovery: **17** derived storage-initializer regions, **1,581 body bytes**
plus **51 frozen NOP bytes**. The source explains zero-capacity behavior, optional
supplied storage, wrapping four-byte allocation sizing, allocation ownership and
base/derived dispatch stores. Fields `unknown_0x0c`, `unknown_0x10` and
`unknown_0x14` stay unknown; setting a word to ten does not establish its role.
Concrete class/API identity remains unverified. The ownership flag is set even if
the allocator returns null. Original widths, aliasing and ordered writes remain.

Existing recovery cleanup: **34** COM collection-serialization regions,
**4,318 already-accepted body bytes** plus **34 existing padding bytes**. They
now share one header with two bounded layout views, three callback signatures,
one named IID and one named import binding. This earns **zero recovered bytes**.
The observed API/IID supports serialization roles; it does not identify the
original game collection or concrete class types.

Combined accepted accounting: **6,780 source regions / 217,362 body bytes /
57,623 separate padding bytes / 3,494,820 remaining logical `.text` scaffold
bytes**. Region counts do not certify original functions or whole-game completion.
Final fresh combined-build evidence is recorded below.

## Concrete source improvements

Before, [006580c0.cpp](../../src/recovered/persistence/SavePersistableCollection_006580c0.cpp) repeated per-address Object/
Collection structs and callback typedefs, with anonymous literal/import symbols
and compact statements. Now it includes
[com_collection.hpp](../../src/shared/com_collection.hpp), describes serialization,
uses `stream`, `persist_stream` and the PE-bound `ra2_ole_save_to_stream`, and
explains escaping locals, live reloads and failure paths. Original addresses and
uncertain class/prototype details remain visible.

The target import at IAT `0x0079a5e8` is `ole32.dll!OleSaveToStream`. GUID
`00000109-0000-0000-c000-000000000046` at `0x007afcd0` independently matches the
supplied VC6 UUID library's `_IID_IPersistStream` symbol. No Microsoft header or
implementation source was copied. Slots 4/0/2 agree with Write/QueryInterface/
Release roles; their implementations are still original scaffold.

The original skips Release when serialization fails and tests Release's result
as a signed status, despite conventional unsigned COM reference-count semantics.
The source preserves both quirks, the escaping count local, the live item backing
reload and the queried pointer reload after the import. It adds no cleanup or
const/restrict assumptions.

New [0046d1f0.cpp](../../src/recovered/word_storage/InitializeWordStorage_0046d1f0.cpp) demonstrates the new family minimum:
multiline code, address/purpose/unknown notes, meaningful `requested_capacity` and
`supplied_storage` names, explicit wrapping and ownership quirks, and unresolved
fields named by offsets. It is not represented as an identified original class.

## Original evidence and review

The initializer family examines 18 previously unaccepted 93-byte regions. Seventeen
have independently frozen three-byte NOP padding; six original-only gap partitions
were refined coherently while keeping every function row and all 1,383,530 gap
bytes. `0x006f8a80` remains refused for missing independent following-entry evidence.
No compiler-derived endpoint or candidate-length trimming was used.

Original freeze: `private/original-target-20261020/quality-derived-init-20261020/`.
Accepted manifest SHA256:
`b9f05b5ba7123f822d4aa85dc9b92a0994a6df8ebbbad55f2ded72c87ca20395`.
All 17 matched on the first source: 17 exact recorded-option cases, 51 variant
misses, 0 source repairs. Generation 0.285s; compiler sessions 8.106s. The variant
search covers only these new candidates. Frozen original review 6.155s and
independent source/object review 0.223s pass; owner strict V4 audit 0.331s passes.
Comparison/generation/queue cost boundaries stay in the private receipts; these
numbers are not total model/elapsed/token efficiency.

COM evidence, candidates, preserved first versions, independent initializer
reviews and generator/regeneration receipts live under
`private/quality-20261020/accepted-family/`. The owner promotion and focused-check
records are under `private/quality-20261020/`. Private experiments and A10 receipts
remain unchanged. Local full builds are executed by the owner; artifact review
and synthetic checks are independently performed by the existing peer.

## Regeneration and shared-header build

Both generators/templates produce new ignored candidates for explicit review.
They never overwrite accepted sources or manifests. The COM generator reads
current canonical metadata and records actual canonical hashes separately from
prior accepted hashes. An actual canonical manual comment about negative counts
survived regeneration; the candidate difference remained available for review.
Source-tree and existing-output destinations were refused. The generator's private
fixture test also preserved a manual comment before root integration. The new
initializer generator likewise preserved an actual canonical caution comment in
`0046d1f0.cpp` while reproducing the original readable candidate for review.
Its four synthetic tests cover manual comment/name preservation, output refusal,
exact independent-review approval and evidence/template drift. The combined tool
suite passes32 tests, independently rerun by the peer.

The build pins shared-header hashes and validates includes against tracked header
closure, including comment/line-splice/digraph/trigraph dependency spellings.
Private, implicit system, computed include and type-library dependencies refuse.
The compiler uses root `src/`, while exact emitted-section, original operand/
reference, complete extent and final packaging checks remain intact. Quoted
Windows TMP/TEMP assignment repairs the previously noted metacharacter path edge.

Remaining debt: most canonical files still have compressed formatting, duplicated
synthetic layouts and uncertain identities/types. This checkpoint demonstrates
one shared family and one readable new family; exact output is reported separately
from semantic understanding. Further bounded shared cleanup belongs in ordinary
bulk-recovery checkpoints, with independent review and no new native matrices.

Owner focused COM validation: `private/quality-20261020/owner-focused-com/`,
34 complete extents and renamed reference bindings exact in16.047s including
input validation/compilation/comparison. This focused scope was not composed or
reported as whole-catalog acceptance. Actual-root regeneration receipts:
`private/quality-20261020/owner-com-regeneration-review.json` and
`owner-initializer-regeneration-review.json`.

## Complete fresh build and acceptance

`build/quality-a11-fresh/build-receipt.json` records fresh compilation of all
**6,780 canonical tracked sources in40 recorded-option groups**, including the
shared header and manual source comments, followed by strict full extents and
actual reference bindings, scaffold assembly, linking and packaging. It completed
in **290.264s**. Every **4,485,392 output byte** equals the supplied target,
SHA256 `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
All **3,127,748 zero virtual-tail bytes** pass. Raw linker output remains
**7,606,784 bytes** and differs; parsed PE structures and retained metadata are
explicit. Receipt SHA256 `2de48e86b50bfa2bd13b6507b816d50b21f883aaa45e493bf3c3f8d805b12bb2`.

Owner executed compiler/linker; both peers independently reviewed source/tools/
actual object artifacts, not a second compiler reproduction. Current source/
header hashes, all compile memberships and final dependency/output receipts are
reviewed under the private quality evidence roots. No unchanged candidate matrix,
original oracle regeneration or native tests ran. Source recovery remains
incomplete; this checkpoint is not final-phase independent acceptance.

Final independent full-artifact review:
`private/original-target-20261020/quality-derived-init-20261020/peer-com34-review/combined-build-review.json`,
SHA256 `b3896a3529942b8d38d1baea59a45f2d6453d8e65297a4f8d440813eb96a12dd`.
The reviewer independently reran strict verification and read/hash/payload checks
in10.179s, without a compiler/linker rerun.
