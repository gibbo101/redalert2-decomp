# Base RA2 later-startup and theater archive requests

October 14, 2026. Ivalice / Apple Silicon macOS. Baseline: `47feaa6`.

**688 fresh original/native request results pass per exact engine**, with both
ASan/UBSan replays. Native helpers now express later-startup and base-theater
registration requests; they are not yet wired into AssetStore. Static inspection
establishes the language/bootstrap/later-startup bridge order. Effective patched
assets, preparation/runtime promotion and whole-game fidelity remain pending.

## Exact identities and reference boundary

The Allied-disc engine is SHA-256
`135a57a026aebd62d80ed71a896ad9b5ab56ada781cdf80be99727849db64743`.
The supplied 1.006 patch engine is SHA-256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`, still equal
to the approved private Windows transfer. Both embed 1.08; use hashes and supplied
patch lineage rather than that string. User-reported no-CD modifications remain
separate provenance. No Windows action or original-game observation occurred.

Revisited pinned YRpp `b22f1860dd7b100cad57123d4ca5d459b9020d88`, `MixFileClass.h`,
`CCFileClass.h`, `FileSystem.h`, via [REFERENCES.md](REFERENCES.md). Their archive
names/arrays are hypotheses; both base executables establish the behavior here.
No upstream/header/generated game code was incorporated. Existing OpenRA format
attribution remains in [THIRD_PARTY.md](../THIRD_PARTY.md).

## Inspected behavior and executed request boundary

`tools/verify_archive_sequence_mapping.py` independently checks **two complete
ranges / 824 instructions**, every changed operand, encoded bytes, branches and
all three 104-byte base theater metadata rows, in addition to the primitive verifier.

| Boundary | Disc VA | Supplied 1.006 VA |
| --- | --- | --- |
| Complete later startup | `5152C0` | `515E70` |
| Complete theater wrapper | `519290` | `519E70` |

Mapping receipt: `private/patch-inspection/archive-sequence-1006-mapping-v2.json`.
The earlier receipt preserves the earlier profile source. New addresses are explicit;
no universal relocation or installer-version inference is applied.

Later startup requests `CONQUER.MIX`, `CAMEO.MIX`, maps, `MULTI.MIX`, optional
`THEME.MIX`, then movies. Required missing families stop later requests. Selected
branches use media index + 1 for maps/movies. Enumeration branches retain the
supplied directory service's order, including repeated names. Original formatting,
branches and vector append stores execute; actual directory enumeration and media
selection are fixtures. The native runtime must never acquire media/authentication
requirements from this research helper.

For the first temperate transition, constructor requests are **GENERIC.MIX,
TEMPERAT.MIX, TEM.MIX, ISOTEMP.MIX, ISOGEN.MIX**, in that order. The earlier private
inspection hypothesis swapped TEM/ISOTEMP; execution corrects it. Snow requests
SNOW/SNO/ISOSNOW/ISOGEN, and urban requests URBAN/URB/ISOURB/ISOGEN. An unchanged
theater requests nothing. Generic reload is requested for a non-snow destination
when the previous theater is snow or -1. Existing archive destruction and palette/
cache/display events are recorded from supplied services; only constructor request
results are compared to the native helper.

`tools/verify_archive_startup_order.py` inspects each engine independently. In the
main graph, the language allocation and post-construction merge dominate both
initialization-wrapper calls. The optional constructor itself does not dominate:
allocation failure can skip it. The wrapper then calls initialization, whose
bootstrap call dominates its later-startup call.

| Inspected bridge | Disc | Supplied 1.006 |
| --- | --- | --- |
| Main entry | `683820` | `68E280` |
| Language constructor call | `6855B5` | `690015` |
| Initialization wrapper / initialization entry | `481E20` / `5109A0` | `481BF0` / `5116A0` |
| Bootstrap / later-startup calls | `510AA0` / `511534` | `5117A0` / `512234` |

Main graphs contain 3,571/3,567 reachable instructions; both initialization graphs
contain 1,191. Branches must land on nonoverlapping decoded boundaries. Graphs and
source engines are fingerprinted. Other calls are opaque, external tail jumps are
terminal, and this is static control-flow evidence, not full startup execution or
proof of every possible archive registration. Private order receipts are
`archive-startup-order-{disc,1006}.json` under `private/patch-inspection/`.

## Differential evidence and limits

| Compared group | Cases per engine |
| --- | ---: |
| Selected maps/movies, both media indexes, all six availability bits | 128 |
| Enumerated maps/movies, availability failures, empty/reversed/repeated names | 512 |
| Three theaters × four prior states × existing/null handles × palette present/absent | 48 |
| **Total request results** | **688** |

Each engine executes 689 audited root calls, including list initialization, and
100,881 audited guest writes. Inherited callable audits check return/EIP/ESP,
callee-saved registers, caller stack, permitted guest stores and selected immutable
inputs. Stream/allocator/constructor/destructor/cache/OS/directory/format/palette/
display services are supplied. Host service stores do not count as guest writes.
Startup handles begin null, allocation succeeds, vector capacity does not grow,
and theater color-type count is zero. Full actor/type/palette state, failure/growth,
cache ownership, heap lifetime and actual OS enumeration remain outside the claim.

Native code is `src/assets/ArchiveSequence.cpp/.hpp`; the runner is
`tests/archive_sequence_vectors.cpp`. Fresh receipts/expectations are under
`private/migration/{allied-disc,supplied-ra2-1006}/archive-sequence/`. They pin
complete inherited/new source identities, engine and expectation fingerprints.
Requests and service traces equal across engines. Eight evidence guards, seven new
native assertions, build, synthetic/owned/sanitizer integration and both actual
170-frame SDL regressions pass. These are not original full-frame measurements.

## Commands and next work

For current reader-source replay, use the fresh sibling receipts recorded in
[EFFECTIVE_ASSETS_1006.md](EFFECTIVE_ASSETS_1006.md). Earlier receipts remain historical.

```sh
./build.command
./test.command --data-dir "$PWD/private/game"
build/tools-env/bin/python tests/test_archive_sequence_profiles.py
build/tools-env/bin/python tools/verify_archive_startup_order.py \
  --exe private/official-1006-probe/game.exe
# Fresh private evidence requires the authorized Mac Unicorn JIT context.
build/tools-env/bin/python tests/compare_archive_sequence.py \
  --exe private/official-1006-probe/game.exe --output-dir private/archive-sequence-fresh
# After README's sanitizer build; select a new replay report destination.
build/tools-env/bin/python tests/compare_archive_sequence.py \
  --exe private/official-1006-probe/game.exe --native build/sanitize/archive-sequence-vectors \
  --expectations private/migration/supplied-ra2-1006/archive-sequence-registration-refresh/expected.json \
  --report private/archive-sequence-sanitizer-replay.json
```

Next: integrate bounded initial registration, nested/loose resolution and private
source manifests; verify effective patched inputs before preparing/promoting the
runtime. Keep deterministic host enumeration explicitly labeled where the original
OS order is unobserved. Preserve disc evidence and native executable-read limits.
Original installs/discs, Outpost 2, Xcode selection and system settings are untouched.
