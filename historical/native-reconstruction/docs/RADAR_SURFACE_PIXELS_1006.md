# Stock GetPixel and nonzero radar surface composition

The shared `SurfacePixel.hpp` now also recovers complete7741D0 GetPixel.
`RadarSurfacePixelsBinding` joins actual GetPixel/SetPixel/lock/format/pitch/width/
unlock below632000 and its634030 nonzero caller, borrowing the same fields and
storage per surface. The composition remains unwired. Other named child effects,
initial surfaces and radar construction remain supplied or open.

## Target and recovered reader

Exact supplied base: `private/official-1006-probe/game.exe`,4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Addresses apply only to this fingerprint.
No public code, dependency or runtime executable read was added.

Stock BSurface79AEF8 slot28 selects7741D0 (80 bytes). The method copies point
X/Y before calling the existing stock411370 lock, preserving its wrapped lock
increment, saved buffer, early format and late width/pitch/format order. A null
lock returns0 without a post-lock format query or unlock; its increment remains.
A nonnull lock queries format70: exactly2 reads an unsigned little-endian word,
otherwise one unsigned byte. It saves the result before actual unlock4112F0 and
returns the saved value even if a diagnostic unlock observer changes storage.
No clipping, format normalization or geometry guard is imposed on the original
address calculation. Host backing/null-base/ambiguous-storage guards retain the
writer's existing explicit profile and fault behavior, without rollback.

All300 isolated cases match, including56 null locks, odd offsets, negative/outside
logical coordinates with valid backing, zero/negative/3/4 formats, wrapped lock
extrema, coordinate/pitch products and byte versus numeric16-bit storage. The
inherited input record retains an unused color field; varying it does not imply
reader color behavior. Original guards reject any actual pixel-storage write.
Native guards cover bounds/fault depth retention, null handling and saved-result
behavior across an unlock diagnostic mutation.

## Shared nonzero radar composition

The immovable scoped binding registers explicit stock table identities and installs
one replacement lookup on `RadarPixelServices`. Construction resolves no surface
views, width, buffer or lock queries; all replacements are allocated before the
callback is installed. Every get/set entry resolves a pure borrowed view and checks
that its width reference is the receiver's actual width. Both operations consume
that same format/buffer/allocation/lock owner. Numeric word or byte backing retains
explicit little-endian behavior; no mirrored pixel service is introduced.

Registered logical tables retain their identity even though both stock entries
execute the same methods. A saved first table can invoke SetPixel on a reloaded,
different first receiver after GetPixel's diagnostic entry probe. Width calls use
that actual receiver's current stock table. Entry probes precede point copies and
reads; read-result probes observe the saved returned value. Store/lock/result
observers must be passive outside authored diagnostic proofs. Named owners,
registration spans and service callbacks must outlive entered calls. The binding
restores the previous lookup on normal exit and faults; arbitrary non-stock tables
refuse. Construction/startup associations remain supplied.

All2,409 composed sequences match full surface buffers, lock depths, ordered
queries/stores and parent/world projections. There are1,020 complete634030 callers,
13,629 actual632000 entries,10,258 actual7741D0 reads,13,244 actual774220 writes and23,502
actual lock/unlock pairs. Actual format queries47,004 and pitch queries23,502 retain
the early/late order. Neither supplied get28 nor supplied set24 hook executes.
Original floor/discovery/House/type/C0/CC/resolver effects remain named supplied
services in this proof. The new composition is not a fresh proof of those effects.

Original instructions execute unchanged only in research Unicorn. Existing code/
constant/stack/callee-saved/allowed-write/whole-arena/expected-global guards remain;
additional buffer/lock writes are explicitly audited. The inherited caller scratch
is explicitly seeded as in the accepted parent proof. Diagnostic late field,
point, registry, surface, table, bucket, shift and timer changes are not in-game
observations. Full pixels and saved receiver/table behavior are compared, but
whole-frame fidelity, original construction, production/runtime adoption and
independent acceptance are not established by these local tests.

Forty-two Python checks, ten focused CTests per profile and30 guarded family
replays pass. Rebuilt prior pixel/mark/copy/refresh/actor/resolver fixtures retain
all previous outputs. No complete inventory or closed finalizer was rerun. Canonical
expectations under `private/boot-camp-20261019/`:

- `surface-get-pixel-fresh-a1/expected.json`, SHA256
  `6faff745418ee437867a6cc3f3c21f79cba7d8941ad01c34f913e31c96cfa7dc`.
- `surface-radar-pixels-fresh-a1/expected.json`, SHA256
  `929cda1357cd02cb1059bcfd2ebf2af0523036f5d4003aa5d8e7f8efb2e3da2a`.

Original isolated.073s/native.014s; original composed20.482s/native.117s. Final
configs2.349s/2.496s, builds11.902s/10.669s. Initial reader config/build, preflight,
check/replay costs and hashes are in
`private/boot-camp-20261019/radar-surface-pixels-receipt-a1.json`. Task/repair wall
and standalone native-preflight elapsed were not measured. An initially adapted
reader validator unit test retained the writer's invalid-result2 assumption;
changed to65536 and rejected all write traces before original execution. No build,
original-proof or native/original comparison failure occurred. App/owner hashes
retain the earlier106-tick SDL walking baseline; no runtime/GUI adoption or rerun.

## Commands and next integration

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake -S . -B build/native
DEVELOPER_DIR=/Library/Developer/CommandLineTools build/tools-env/bin/cmake --build build/native --target surface-get-pixel-vectors surface-radar-pixels-vectors
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_surface_get_pixel test_surface_radar_pixels
build/tools-env/bin/ctest --test-dir build/native -R '^surface-(get-pixel|radar-pixels)-domain$' --output-on-failure
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py --audit private/boot-camp-20261019/radar-surfaces-local.audit.json tests/compare_surface_radar_pixels.py --exe private/official-1006-probe/game.exe --native build/native/surface-radar-pixels-vectors --expectations private/boot-camp-20261019/surface-radar-pixels-fresh-a1/expected.json --report private/boot-camp-20261019/radar-surfaces-local.json
```

Use new audit/report paths. The isolated driver is `tests/compare_surface_get_pixel.py`
and canonical expectations `surface-get-pixel-fresh-a1/expected.json` under the
same private directory. Fresh execution replaces expectations/report with a new
`--output` directory and needs host Unicorn JIT permission. Sanitizer runners are
under `build/sanitize`; `--uncached` before the driver disables only immutable
inspection reuse. Original execution and native results are never cached.

Next recover568280 and compose floor/discovery/House/type/actor/resolver children
on shared owners, reusing existing recovered kernels and preserving their caller
contexts/refusals. Stock surface startup/association, coverage/redraw/power,
production owned/warm/scan and diplomacy/action37 remain open. Ordinary SDL Boot
Camp Objective1 and both games remain incomplete; goal active. Existing delivered
walking: `./build.command`, `./run.command --boot-camp-walk`; broader tests:
`./test.command`. No workers/Windows/downloads/publication/runtime-read expansion.
