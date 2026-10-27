# Supplied RA2 1.006 initialized resource map inputs

October 15, 2026, after `ea94d2f`. This continues the same terrain-aware
Foot/world crossing and parked `(51,72)`, elevation 4 capability. The native
resource input phase now supplies initialized records to the shared overlay
reader/placement/resource path. Complete startup, Cell recalculation and runtime
integration remain open. Full RA2/YR and the playable capability remain incomplete.

## Identity and references

The supplied base executable is pinned to 4,485,392 bytes and SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Both private copies have that identity. Embedded 1.08, supplied 1.006 lineage and
reported no-CD changes remain distinct; pristine authenticity is unverified.
No Windows/transfer/source-install/bypass/driver/security/system action occurred.

Consulted [REFERENCES.md](REFERENCES.md), pinned recomp
`eebcf725ef99f942a8f9a5e0437a8a6154d7d439` `docs/voxels.md`/LICENSE and YRpp
`b22f1860dd7b100cad57123d4ca5d459b9020d88` `TiberiumClass.h` properties/
FindIndex, `OverlayTypeClass.h` and `CellClass.h`. Hypothesis: placement should
consume constructor/INI-derived ranges/frames/values rather than diagnostic
contiguous runs. YR names are leads; exact base execution decides. Recomp's MIT
covers authored work, not generated/lifted output; its stale The Movies text
remains noted. No upstream/header/generated/lifted code or extracted table was
incorporated; no new dependency or THIRD_PARTY notice is needed.

## Native phase binding

[ResourceMapInputs.cpp](../src/assets/ResourceMapInputs.cpp) calls the recovered
numeric-key list and projects active primary registry order through
`mapResourceInputs()`. It preserves each resource's stored index and the chosen
overlay's stored index, frame/image/slope counts and value. Its output feeds
the unchanged shared resource classifier/update during actual decoded overlay
preparation. No replacement resource algorithm was added. The helper remains
unwired in the application; the existing crossing remains the playable baseline.

The new `J` fixture in `overlay-map-resource-vectors` initializes resources before
calling the same reader/placement/lifetime/wall/update/cleanup path as `N`.
The old `N` protocol retains diagnostic resource inputs and its prior scope.
The native registry/object records live through projection; the projected records
are immutable throughout shared placement. Native storage/phase order is supplied.

## Exact-original boundary

Original resource initialization executes the three complete roots / 360
instructions in [RESOURCE_TYPES_1006.md](RESOURCE_TYPES_1006.md). Selected
initialized records are then transferred into a **separate audited guest** for
the 40 complete ranges / 3,331 instructions in
[OVERLAY_MAP_RESOURCES_1006.md](OVERLAY_MAP_RESOURCES_1006.md). Together these
inspect 43 actual ranges / 3,691 instructions, but **do not execute an original
startup parent or prove original phase ordering**. No guest instructions are
rewritten. Host pointer relocation and selected-record transfer are explicit.

The resource fixture supplies only Image/Value overrides needed by this consumer;
other selected subtype defaults come from actual construction. Its four owned
rows correspond to supplied Tiberiums keys, Image and Value. Diagnostic names,
base defaults/INI, original text/CRT/color/animation/vector/heap services, overlay
type/index/image initialization and initial Cell state remain supplied. This is
not a complete rules-parser or type-startup proof. The earlier full resource INI
suite retains its broader field/edge scope and signaling-NaN service limitation.

Cell recalculation/passability still uses the diagnostic presence-based service.
Decoded streams, heap/growth, bounds/camera/queues/zones/broadcast/RTTI/base
destruction also remain supplied. Resource growth/spread/random replacement,
economy, full ownership/scheduling and frame parity remain outside the claim.

## Scenarios and reproduction

Nine scenarios cover small shared wall/resource/crate loading, type-only loading,
allocation failure, disabled Unlimbo, and both complete owned-map streams/type-only
loading: **660 overlays / 13,515 Cells in each owned execution**. Additional
cases cover overlapping initialized ranges/first match, signed wrapped resource
amounts and Image=2. A new Image=2 retains constructor slopes zero; updating an
existing Image=1 record to Image=2 retains eight slopes. Failed existing INI is
ignored and a signed-negative row length is skipped. Selected initialized-record
digests and complete overlay selected state/events are compared independently.

Fresh evidence: `private/map-depth-1006/resource-map-inputs-v1/`; all **nine
original/native scenarios and both normal/ASan/UBSan replays pass**. There are
nine independently audited calls in each phase, with **16 constructor / 18 INI /
nine list entries**, **762 selected type stores / 334 supplied type calls**.
Overlay execution enters all 40 ranges: **958 resource / 8,622 classifier entries**,
four missing-resource logger services, 1,347 temporary constructors and 194 wall
updates. **984,375 selected overlay guest stores / 3,436,836 supplied calls**
compare through ordered digests. All six selected resource consumer fields and
complete selected overlay Cell/actor/registry/stream/provider/global/freed state
match. Type-phase events are audited here; their native ordered comparison stays
in the unchanged resource-type suite. Inherited caller,
return/register, code allowlist, immutable input, nonselected-byte/raw-allocation
and capacity-tail guards pass. No complete memory-read-order claim follows.

Changed-runner prior scope has fresh `overlay-map-resources-v2` proof and both
replays; commands, labels and outputs equal v1 exactly. Earlier unchanged sources/
runners remain current: **54 sets / 1,450 source entries**. Both builds, **588
Python tests**, **40 normal / 39 sanitizer CTests**, source/diff/local-link checks
pass. Actual rebuilt SDL crossing passes 79 samples/78 updates, brightness
1450..1512, selection/right-click, occlusion/clipping/culling/cache bypass/pan/no
trails. Converted occluded frame inspected. This checks existing native integration,
not new resource runtime use or original-frame fidelity. Local verification is not
independent acceptance.

New driver/original/native **248.023/241.625/0.151 s** (CLI 248.090 s);
replays CLI **6.176/17.680 s**. Refreshed prior-scope driver/original/native
246.854/242.716/0.162 s (CLI 246.953 s); replays CLI 4.073/15.612 s.
Four original probes pass in 74.627 s. Final normal/sanitizer runner builds
8.544/8.290 s; earlier builds 9.244/2.523 and sanitizer 10.708 s remain logged.
Python CLI 1.946 s (unittest 0.574 s), test.command 1.951 s, sanitizer CTest
3.634 s, SDL 2.451 s. The measured interval from the `ea94d2f` commit to closing
identity audit is **692.504 s**; full inherited/active-delivery elapsed is unavailable.
Independent runs overlap. No original/native comparison, build or test failed,
and no gameplay repair or evidence-cache infrastructure was added. A nonexistent
source read path was corrected by file search; no evidence was affected.

```sh
./build.command
./test.command
build/tools-env/bin/python -m unittest discover -s tests -p 'test_*.py'
build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/tools-env/bin/ctest --test-dir build/sanitize --output-on-failure
# Fresh original execution needs the authorized Mac host JIT context.
build/tools-env/bin/python tests/compare_resource_map_inputs.py \
  --exe private/official-1006-probe/game.exe \
  --output private/map-depth-1006/resource-map-inputs-new
build/tools-env/bin/python tests/compare_resource_map_inputs.py \
  --exe private/official-1006-probe/game.exe \
  --expectations private/map-depth-1006/resource-map-inputs-v1/expected.json \
  --report private/map-depth-1006/resource-map-inputs-v1/replay-new.json
# Add --native build/sanitize/overlay-map-resource-vectors for sanitizer replay.
./run.command --crossing-light-demo
# Select Rhino; G/right-click moves, L toggles light, R resets.
```

Next replace diagnostic recalculation with actual shared Cell/LAT/passability/TMP
children, preserving each overlay/data/passability write before subsequent queries.
Then execute the overlay-bearing preparation parent, verify prepared Cell/TMP into
actual Foot/base-depth and Unit/world, and exercise actual SDL crossing/parked
cliff. Runtime depth stays neutral until proven. Only Apple Silicon macOS is tested.
