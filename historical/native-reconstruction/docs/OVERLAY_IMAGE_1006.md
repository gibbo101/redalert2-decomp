# Overlay demand images and NewTheater

Tutorial purpose: Day1's bridge overlays need real image headers for the radar
terrain path below Objective1's alliance/House sight effects. Complete5DD150 and
5D7BD0 now join that chain, and an explicit demand query uses the actual prepared
overlay owner and supplied installation. Nonlazy startup and SDL adoption remain
open; this does not enable sight scheduling or complete an objective.

## Recovered policy

`assets/OverlayImage.hpp` borrows `OverlayTypeInputs`, its canonical optional Data
and an owned byte. Handle/Data consistency is checked. A resident image returns
immediately; a null image with demandLoad0 returns null without services. Otherwise
Theater takes precedence and builds imageName plus TEM/SNO/URB for base theaters
0/1/2. NewTheater builds imageName.SHP and applies complete5D7BD0. That helper
returns immediately for theater-1; otherwise it lowercases ASCII only for its
comparison, accepts first letterg/n/c and second lettera/t, and replaces only
byte1 with the selected T/A/U. Other prefixes retain all bytes and case.
The base three-theater domain is explicit; no runtime executable table read was
added. Short strings and unsupported filename/table accesses refuse safely.

Complete5DD150 then constructs/reads a temporary file through supplied portable
services, stores the returned image handle even when null, sets owned1 only for
a nonnull image, performs the two cleanup phases and returns the saved result.
Failure leaves the prior owned byte and permits a later retry. Success makes
later calls cached, even if the supplied theater changes. Data copies share
immutable bytes, while the explicit native handles replace original addresses.
The original no-op4068F0 debug child executes unchanged. With both Theater and
NewTheater clear, a demand call reaches an uninitialized stack filename in this
build; native refuses that unsupported path before file services or owner stores.
This is a bounded complete parent policy, not original CRT/Windows IO/heap fidelity.

Exact supplied engine:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage and reported no-CD provenance remain distinct;
pristine authenticity is unverified. Complete5DD150:271 bytes/72 instructions,
SHA256 `e6867c875bd0241999c068110a35c5ddf1fb777790653e9212619cedb56d27b1`.
Complete5D7BD0:74 bytes/31 instructions, SHA256
`dbeb9ffea788b96b65e91c65810bb1fd86027e5ca54d6cdb37ca4eb53d07a249`.
The verifier pins both, checks the three theater suffix/letter records and
inspects the complete5D7810 base parent for the selected art-field association.
That base parent is inspection only; its other fields/children are not recovered
or executed by this checkpoint. No public/generated/lifted code was incorporated.

## Actual source association and owners

The native prepared-map adapter previously read Theater from the overlay ID.
The inspected base parent resolves the rules Image name, then queries art fields
through that image-name field1C8, including Theater1FC and NewTheater207. The
adapter now follows that association and retains NewTheater in the existing type
projection. On actual Day1, overlay127 isTIB2_01 with ImageTIB01; artTIB01 supplies
Theater. This repair does not establish all original base construction/INI parsing.

`PreparedTerrainMap::demandOverlayImage` binds the recovered getter to retained
`overlayInputs`, `overlayImages` and `overlayImageOwned`. AssetStore supplies Data
and a stable native handle; native RAII replaces temporary file objects. The
explicit query for actual type83 reads LOBRDG10.TEM, shares its canonical Data,
stores handle84/owned1 and preserves the same cached identity when queried later
with theater2. Normal/sanitizer Day1 checks compare those bytes to the supplied
file, check the corrected ore/bridge art fields and retain movement, Stop/repeated
orders, refusal isolation, warm clones/source destruction and mission owners.
A demandLoad0 rock query stays unbound: no nonlazy startup image is synthesized.

The private read-only source inventory is
`private/boot-camp-20261020/overlay-asset-probe-a1.txt`. Its initial flags predate
the art-name repair; retain that true historical scope. It establishes available
file candidates, not original startup/load decisions or executable observations.
Source installations stay unchanged. No extracted content is tracked or shipped.

## Executed evidence and limits

All280 standalone sequences match728 original roots,248 file constructs/loads,
200 NewTheater entries,324 ordered image/owned stores and496 cleanup calls.
Cases include noncanonical flag bytes, resident/zero-demand paths, all supported
theaters, mixed-case/rejected prefixes, both-flag precedence, failed retries,
owned-byte preservation and cached repeat calls. CRT makepath, file storage/read
and cleanup effects remain supplied at verified callers/receivers. Whole guest
arena, code/constants, allowed writes, caller stack and saved registers are
checked. Original instructions are unmodified.

NewM/D commands compose complete demand loading below actual overlay/Cell colors,
resident search, terrain and projection. All398 sequences match526 Cell roots,
288 overlay/getter calls,80 successful file loads,160 ordered image/owned stores,
160 cleanup calls,64 terrain and32 projection joins. Whole output backings match
672 RGB/680 projected pixel writes. The cached owner is shared across each
sequence's Cells, rather than reloaded once per color call. Final review also
replaced separate fixture color/loading type projections with one shared type;
affected runners and domain checks were rebuilt/replayed using unchanged original
answers. A1 records the prior native phase; A2 includes final runner receipts. TMP installation,
resource classification, authored images/startup/variant/brightness inputs and
actual animation-class association retain earlier supplied boundaries.
Old366 standalone overlay and398 initialized-getter composed answers replay
unchanged on both rebuilt profiles, without original regeneration.

Seventeen Python checks and ten CTests/profile pass. Normal, sanitizer and
uncached-inspection replays report280/398 hits and zero misses respectively.
Current runner hashes remain identical after app/owner rebuilds. Day1 checks pass
in3.793s normal/40.374s sanitizer. App rebuilt; no new SDL input/drawing acceptance,
radar scheduling or whole-frame claim follows. Prior app receipts keep their
historical hashes. Only Apple Silicon macOS is tested; local verification is not
independent acceptance. Both games and ordinary Objective1 remain incomplete.

Canonical originals under `private/boot-camp-20261020/`:
`overlay-image-fresh-a1/expected.json`, `radar-demand-fresh-a1/expected.json`.
Fresh original/native/driver costs:.086/.019/.480s and4.730/.046/5.276s. Normal
replay.185/.322s; sanitizer.279/.715s; uncached-inspection.293/2.057s. Receipt
`overlay-image-receipt-a2.json` records costs/hashes and unavailable inspection/
edit/configure/build/task/repair wall measurements. Additional unchanged old366
replays are `demand-old-standalone-native-a1.json` and its sanitizer counterpart.
No failed proof or original mismatch occurred. No workers, Windows actions,
transfers, downloads, system changes or runtime executable-read expansion.

Next recover/bind nonlazy overlay theater/NewTheater image startup and the actual
animation owner only where entered; join recovered resource classification on the
same actual Cells/types. Retain explicit primary-variant/default0/brightness
boundaries. Then join630A00 startup with aliased source/region/native storage and
first-DSurface semantics before production House/coverage/actor/SDL integration.
Do not promote file existence or host image binding into original startup proof.

## Commands

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake -S . -B build/native
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake --build build/native --target overlay-image-vectors cell-radar-color-vectors radar-terrain-vectors boot-camp-walk-check redalert2-native --parallel 6
build/tools-env/bin/ctest --test-dir build/native -R '^(overlay-image|overlay-radar-color|cell-resident-search|cell-resident-kind6|cell-radar-color|radar-terrain|radar-projection|overlay-type-input|resource-type-input|map-overlay)-domain$' --output-on-failure
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_overlay_image test_overlay_radar_color test_cell_radar_color test_radar_terrain test_radar_projection test_cell_resident_search
build/native/boot-camp-walk-check private/official-1006-probe
# Explicit original-only reuse; select fresh audit/report paths.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/NEW-OVERLAY-IMAGE.audit.json tests/compare_overlay_image.py \
  --exe private/official-1006-probe/game.exe --native build/native/overlay-image-vectors \
  --expectations private/boot-camp-20261020/overlay-image-fresh-a1/expected.json \
  --report private/NEW-OVERLAY-IMAGE.json
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/NEW-RADAR-DEMAND.audit.json tests/compare_radar_demand_color.py \
  --exe private/official-1006-probe/game.exe --native build/native/cell-radar-color-vectors \
  --terrain-native build/native/radar-terrain-vectors \
  --expectations private/boot-camp-20261020/radar-demand-fresh-a1/expected.json \
  --report private/NEW-RADAR-DEMAND.json
```

Use `build/sanitize/` runners for sanitizer; `--uncached` before the driver checks
inspection without changing explicit original-result reuse. Fresh generation uses
new `--output` instead of expectations/report and needs research-only Unicorn JIT.
Entry points remain `./build.command`, `./test.command`,
`./run.command --boot-camp-walk`.
