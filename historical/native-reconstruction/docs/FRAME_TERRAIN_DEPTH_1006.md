# Queued Cell terrain depth pass

The explicit [plane clear/scroll seam](FRAME_PLANES_1006.md) now owns persistent
Renderer depth/alpha offsets and bases; this consumer borrows those fields.
The original answers below retain their recorded field/input provenance; the
former actual-owner association started at zero scroll. Production frame
scheduling and other nonzero-scroll consumers remain open.

This entered frame child clears a clipped terrain diamond on the existing
Renderer depth plane. It is a dependency of phase1 region preparation before
Building draws, needed to present Boot Camp structures under the original frame
protocol. It does not repaint terrain colors, finish6A45A0, schedule sight/arrival
or advance Objective1. Both games remain incomplete; only Apple Silicon macOS
has been tested.

## Evidence boundary

The supplied executable is4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. The verifier fingerprints complete4754B0
(102 bytes), complete52C230(6,967 bytes), both52-byte plane-address helpers,
stock BSurface methods and the retained-hit alpha cache paths. The original TMP
mask is checked against the readable diamond formula; no new runtime executable
read or extracted table is added. Previous ordinary TMP color proofs retain their
original scope; they excluded the special flags used by this caller.

4754B0 sign-extends Cell10C brightness and Cell11B level, copies the clip by value
and forwards point, surface, first template and first converter. Its fixed
arguments are sub0/depth1/variant0/fill0/**depth-only1**/checker0/color0.
This selects a different52C230 branch from ordinary terrain color drawing.
The accepted profile uses a resident60x30 template/subtile0 with depth flag2.
Nonresident/alternate template and depth-disabled drawing are unsupported.

The child acquires a retained alpha-cache entry even though these pixels do not
use its table, checks destination format2, obtains the resident header, clips the
60x29 diamond, then gets pitch and locks the destination. It obtains **both**
depth776340 and alpha411230 pointers. Each helper locks the live surface, saves
the pointer, rereads the surface and unlocks before adding offset10 and applying
one unsigned end1C/bytes20 wrap. This is not modulo arithmetic. Offset0 denotes
a nonnull common backing allocation in native code.

The diamond has29 nonempty rows: width4*(y+1) above row15 and4*(29-y)
thereafter, centered in60 columns. Only depth words receiveFFFF; color and alpha
backing remain unchanged. The wrapped branch normalizes each row prefix and each
pixel advance, retaining the unnormalized row base. The fast path omits those
wrap tests. GlobalA6E394 does not suppress the depth-only branch. Destination
unlock precedes retained-cache release. Empty clips and early format/header
returns still release the acquired entry; null converter returns before acquire.
Cache misses/construction/free, fault compatibility and arbitrary scratch-global
state parity remain outside this bounded profile. The compact native geometry
replaces scratch arrays; it does not claim their exact address/state layout.
The unused shade/depth-base scratch values are not native rendering state.

The oracle executes original4754B0 and the entered complete52C230 paths with
actual stock surfaces, both address helpers and retained-cache acquire/release.
Only the resident file getter is a supplied service. Synthetic surface placement,
cache entry and mutable fields are authored probes, not original-game observations.
Caller stack/return/callee-saved/code/vtable/immutable input and full arena guards
are separate from the ordered call/store and full-plane comparisons. No original
code executes in the application; Unicorn remains research/test-only.

## Actual owner integration

`TileImage` retains input subtile flags. `BootCampVisibilityWorld::redrawCellLevel`
resolves the canonical Cell/shared fallback, refusing foreign identities.
`Renderer::refreshCellTerrainDepth` validates the actual Cell identity/point/level
and consumes the existing Cell-light terrain brightness, first resident template,
terrain palettes and existing color/depth/alpha vectors. The first-template/
converter, retained cache, zero-scroll and startup associations remain supplied.
Persistent stock locks return to their initial values; no parallel pixel plane,
mission registry or runtime source read is introduced.

The explicit actual-owner check queues a real GI Cell through the existing redraw
producer, composes6A33F0 into the new pass and requires900 ordered depth-word
stores with changed depth pixels. It requires unchanged color/alpha, restored
cache/lock owners and retained Cell slots/count/tails/source and clone isolation.
This is native integration evidence, not a nested-original complete frame proof
or independent acceptance. The older403 original6A33F0 answers retain their
supplied terrain/depth child provenance. The frame loop and queue-reset tail
remain off. Genuine sight/arrival and mission effects remain separate requirements.

## Commands

```sh
./build.command
./test.command
build/native/boot-camp-walk-check private/official-1006-probe
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest tests/test_terrain_depth_pass.py
./run.command --boot-camp-walk
```

Explicit original-result reuse uses the guarded317-root receipt and always
runs the current native executable:

```sh
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py --audit private/NEW.audit.json \
  tests/compare_terrain_depth_pass.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/terrain-depth-pass-vectors \
  --expectations private/terrain-depth-20261019/fresh-a4/expected.json \
  --report private/NEW.json
# For sanitizer replay, substitute build/sanitize/terrain-depth-pass-vectors.
env DEVELOPER_DIR="${DEVELOPER_DIR:-/Library/Developer/CommandLineTools}" \
  build/tools-env/bin/cmake --build build/sanitize --parallel 6
./run.command --boot-camp-walk-smoke-test private/NEW-SDL
```

Original executable/oracle/full transitive Python/environment/asset/commands/
receipt identities are checked separately from current native sources and runner.
Native-only repairs reuse originals; they never reuse native pass/fail. Missing or
changed original dependencies refuse. Fresh original scope uses `--output
private/NEW` instead of expectations/report and needs authorized host JIT access.
The old composition and frame comparisons retain their own documented explicit
reuse commands and original provenance. Traces are observational and callbacks
borrow owners synchronously; mutating inputs during them is outside this profile. Use unused
private report/audit/capture names. No unchanged original matrix should be
regenerated, and no native verdict is reusable. No workers, Windows/transfer/
download/system/Xcode/DRM action, public dependency/code or proprietary shipment.
Local verification is not independent acceptance.

## Current validation and costs

317 complete original Cell roots match82,870 ordered depth-word stores, full
color/depth/alpha hashes, forwarded signed/fixed arguments, cache reference and
stock lock stores. Both fast126 and wrapped36 entered draws are exercised;162
calls execute each plane-address helper.316 acquire/releases cover the nonnull
converter cases, including early format/header returns and wrapping references.
Native words and byte backing are separately exercised by the actual owner and
the original comparator. The native integration requires900 writes on the real
queued GI Cell, unchanged color/alpha and retained owner state.

Normal/sanitizer each explicitly reuse**4,898 original answers/zero misses**,
including317 new and4,581 retained frame/Building answers. Each also replays the
424 identity-checked historical composition answers against the current native
runner.219/218 CTests,24 focused Python guards, both actual-owner checks and the
256tick SDL walking/input/drawing regression pass. Horizontal GI captures retain
prior hashes: left`b563862e3269a58caabc92c6fb2b76b5d5eadd7753d5fb84ae841c2dd2d8c9a4`,
right`2d0364cb242b80dd7772264bad30d78af519f852dfef17ac6beca59e9b00b674`.
This is regression coverage, not original Infantry frame-selection fidelity.
No unchanged original matrix was regenerated.

Accepted original generation12.399s; final normal/sanitizer builds45.677/105.311s,
actual owners14.994/85.929s, test.command19.619s/sanitizer CTests20.538s,
Python guards2.992s, SDL7.139s. New317-answer replays1.246/1.015s;
retained composition replays9.146/7.263s. Other per-comparison/replay costs are
recorded under`private/terrain-depth-20261019/validation/`; concurrent timings
are nonadditive. Receipt:`private/terrain-depth-receipt-a1.json`.
Initial builds, the first owner check, manual inspection/repair and total milestone
wall time were not measured.

The first launch raced the unfinished focused build and failed before producing
an audit. Failed fresh-a2(193.535s) stopped in its write observer; fresh-a3(10.359s)
then exposed an odd-scroll two-byte store crossing the fixture's backing end.
Those rejected audits remain under`private/terrain-depth-fresh-a{2,3}.audit.json`;
no accepted original/native comparison was taken from them. The fixture now uses
the aligned stock-plane scroll domain and the original's own lazy table flag:
one cold setup followed by retained warm scratch. This removes redundant original
scratch construction without caching native results or adding a cache framework.
The accepted frozen fresh-a4 audit and expectation provenance remain unchanged.

Next recover the remaining entered6A45A0 children and compose the complete
0/1/map-callback/2 protocol on these same owners. Keep frame/sight/arrival/
Objective1 scheduling and isolated queue resets off until their entered paths
are complete. Sight/arrival and mission child effects remain separate gates to
the first actual Boot Camp objective. Local verification is not independent
acceptance; the full reconstruction goal remains active.
