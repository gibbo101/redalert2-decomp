# A15 — empty word storage and signed coordinate pairs

Eleven regions add 415 exact C++ body bytes and 145 independently frozen NOP bytes.
Nine ordinary empty-vector constructors reuse the existing 24-byte storage view;
two coordinate helpers divide signed 32-bit values by 256, narrow to 16 bits and write
the combined pair after both source reads. Concrete game classes and original
hidden-return APIs remain unknown. Most original code remains unrecovered.

## Sources, semantics and original bounds

`src/recovered/word_storage/EmptyWordVector_ADDRESS.cpp` contains nine distinct
ordinary constructor classes declared in `src/shared/empty_word_vector_views.hpp`.
They preserve backing/capacity zero, byte +0C=1, ownership +0D=0, growth +14=10,
count +10=0 and the actual dispatch word last. Bytes 0E/0F remain untouched.
All nine 34-byte bodies and their whole 14-NOP gaps have independent original
entry/following witnesses and explicit both-population body/data/symbol/flow/
fallthrough/operand and whole-file unaligned raw 32-bit exclusion checks.58DC70 is
held whole because a raw word points into its padding at 58DC97. No trimming.
Table relationships to storage-copy/name-list/filter evidence are qualified
connections, not proof that the original concrete classes are identical.

The two files under `src/recovered/coordinates/` preserve source fields 0/4 and
34/38 respectively, signed division truncating toward zero, low16 narrowing and
combined 32-bit output write after both source reads. This retains alias-sensitive
input/output ordering. Their complete54/55-byte bodies and 10/9-NOP gaps are
frozen from the unchanged coherent baseline pair.41B320 remains held whole for
its 691-byte unclassified gap. Explicit observed member/output-pointer ABI is a
source projection; original hidden aggregate return remains a hypothesis.

Original readiness and author-independent source reviews are retained privately
under `recovery-a15-vector-initializers/`, `recovery-a15-next-population/` and
`owner-a15-integration/`. Target SHA256 remains
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Accepted populations 37/38 use unchanged baseline functions SHA256
`82d76aac864d26e1a63b17341b43281aa316ce10c95f0d35474ebdba4d64c791`
and gaps SHA256
`fc491a93adcd49a62ae199caad76cf7fff9e4553116a461478335a50bacdd82b`.

## Exact source checks and regeneration

First coordinate trial strictly matches two regions / 109 body / 19 padding in
`owner-a15-coordinates-first/`,7.77258s. Nine constructors strictly match
306 body / 126 padding in `owner-a15-vectors-first/`,6.7679455s. Receipts and V4
strict verification are required; preliminary `accepted.json` alone is not proof.
Both populations preserve recordedG5 options. No new compiler-output allowance,
library exception or discarded helper is introduced.

Tracked plans `integer_coordinate_family.json` and `empty_word_vector_family.json`
reuse the existing `generate_message_gadget.py` renderer. Their actual canonical
regeneration outputs under `owner-a15-integration/` reproduce all 11 source files
and the three shared-header dependencies byte for byte. Existing accepted sources
and authored Python tools remain unchanged. The canonical manifest supplies paths;
no address-derived path reconstruction is added. Independent canonical promotion
review SHA256:
`8f717e25e48d67646e0cf3d86eff9b5db41eb8d097714e18303cdca26b281c2a`.
This is artifact/source review, not independent compiler execution.

## Bounded failures and held original evidence

Twenty source hypotheses across five families total 3,266 attempted body bytes;
11 match 415 body bytes. Repeated options and corrected recipes do not multiply recovery.
The other 2,851 body bytes remain original scaffold:

- Three name-list readers, 1,392 body: all nine first trials miss. Observed ABI,
  calls and append order agree, but PMF encoding/frame/schedule differences have
  no supported correction. No register/frame tuning.
- Two collection filters, 810 body / 22 NOP: first trial and one real count-store-before-
  backing-write correction miss; unknown out-of-line helper/reference output
  refuses. The third candidate 4F2190 remains held whole for its mixed code gap.
- Two integer projections, 221 body: one original-grounded correction prevents VC6
  from hoisting negation through signed halving at wrapped product INT_MIN.
  Unsigned sign-bias plus arithmetic shift preserves all bit patterns; independent
  review includes the concrete y=0x20000000 failure case. Corrected actual output
  fixes that discrepancy but still misses complete extents. No third recipe.
- Two INI triple parsers, 428 body / 4 NOP: first trial misses both. One float-only
  union-word correction restores raw 32-bit copy semantics, three local float32 stores
  and output ordering, but still misses the complete extent. Integer first source
  stays frozen. Early fallback snapshot elision and remaining schedules/frames
  do not license another model.

Closures: `recovery-a15-name-list/first-model-actual-closure.json`,
`recovery-a15-collection-filter-original/CORRECTED-MODEL-CLOSED.json`,
`recovery-a15-next-population/projection-final-closure.json` and
`recovery-a15-vector-initializers/TUPLE-FAMILY-CLOSED.json`. Failed source/header/
object/disassembly evidence remains private. Failed-family provisional root headers
and pins were removed after confirming identical private copies.

Original-only selection considered ten vector initializers/five coordinate roots,
retaining the two whole holds above. The separate 661770 scenario-variable-name
loader has an unsupported following gap and remains an uncompiled lead. Size-only
cohort collisions are not treated as common algorithms. No claim that this finite
selection exhausts unattempted original code.

Preflight failures are retained: coordinate provenance used an unsupported wrapper
until a schema-only repair; vector include paths required canonical spellings.
Sources/headers remained frozen across schema-only changes except those explicit
include spellings. No acceptance logic was weakened. Earlier owner syntax/context
preflight errors and repair scope are recorded separately; manual cost is unavailable.

## Combined build and accounting

Fresh accepted-only build `build/recovery-a15-fresh/` passes: all 6,834 canonical
sources / 50 groups reproduce every one of the4,485,392 supplied bytes in348.409s.
Build receipt SHA256:
`f73979fbdc275732d84801c615586b9ce7c2d4b8e9e6eb74a2fd8137245f6259`.
Canonical manifest SHA256:
`dd53b77475ae7091f146f84af6eb5cc12f3559f3a2c440f3f170a06b29cf03b0`.
Final ledger SHA256:
`08a400d47f92f5166931261fb5f95cd5532f741a15b43cbb613130fac97f2ed6`,
overlay cost0.837838334s. The ledger records222,597 body /58,084 padding and
3,489,124 logical `.text` scaffold bytes. These are regions, not confirmed
function counts or a whole-program percentage. Existing 8,245 archive-identity
bytes remain scaffold with zero library/source credit. Data, retained PE headers,
file padding, overlay and implicit zero tails retain their existing boundaries.

A15's named interval begins 2026-10-20T21:54:17.274402UTC after first-family original
peer readiness; earlier original preparation is outside it. Serialized candidate
driver calls total 60.357278624s across eight trials, including unsuccessful
families and bounded corrections. Driver compile/queue/comparison scopes nest;
do not add nested components again. Manual/model/generation/usage costs not
instrumented remain unavailable, not zero. Final review/interval costs follow in the completed receipt. No native/SDL regression or original game launch was
needed; native adaptation and gameplay delivery remain later.


The raw linker file differs:7,606,784 bytes,4,177,167 differing common bytes and
3,121,392 extra bytes. Packaging retains the original4,096 header bytes and272-byte
overlay after checking all four logical payloads and implicit zero tails. This is
explicit original metadata scaffolding, not original linker metadata recovery.
The two existing A14 helper omission policies remain unchanged and physically
verified; no original helper/source/library credit is added. Independent final artifact review passes:
`b02ceb900c6ff36eb0f833cacf9ec5929c497cb069e9e78d3b8575955a4634c4`,20.758039042s. It checks all50 fresh objects /6,834
complete extents /14,582 bindings and placements, all payloads/zero tails/file,
unchanged physical helper omissions and72,424 ledger intervals. Existing labels
and217,583 prior-field values remain intact. No compiler/linker rerun.


The completed named wall interval is 2145.071s (2026-10-20T21:54:17.274402+00:00 through 2026-10-20T22:30:02.345640+00:00), including failures,
repairs, reviews, docs and interleaved A16 preparation. Earlier original
preparation and later local commit are excluded. Components nest/overlap and
manual/generation/usage costs remain unavailable; no improved throughput claim.
Private scope receipt: `owner-a15-integration/final-cost-scope.json`.
