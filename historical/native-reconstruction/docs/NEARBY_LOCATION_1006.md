# Nearby Cell destination search

`nearbyLocation` recovers the complete candidate enumeration and selection policy
at `5502E0`. It is a separate SDL-free dependency, unwired from Unit Scatter,
Advance, Process and the owned runtime. It finds a candidate destination; it does
not find a route or move a Unit. Permission, rectangle admission, burrowability
and projection remain explicit supplied services in this proof. Base RA2 first,
then Yuri's Revenge remain incomplete.

## Exact executable and caller findings

The private supplied executable is 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded 1.08, supplied 1.006 lineage and reported no-CD provenance remain distinct;
pristine authenticity is unverified. The existing local file matches, so the
previously authorized Windows copy was unnecessary. No transfer occurred.

Inspection of complete Advance `4A1000..4A2649` establishes that result6 passes
**pointer `852998`**, two flags 1 and an elevated-layer dword to Cell Scatter
`476920` at `4A1F88`. It does not pass a mover-position/nonzero away point. ESI is
the Drive's **head+40**, established at `4A1BF6`, and the final coordinate lookup
uses that head. Earlier flag/level lookups use the queued candidate at stack+18.
If its flag 100 is set, the second lookup follows an actor+88 coordinate read;
the signed level and signed actor-Z/global 8529D0 division determine the elevated
low byte with a strict absolute-difference>2 test. Its upper scratch bytes remain
retained. That global's initialization/value and the complete result6 caller
effects still require their joined proof; this is inspection, not execution.

Two complete original initializers, `49F600 -> 852998` and
`6FA390 -> AD04C0`, independently turn poisoned 12-byte records into zero. Unit
Scatter compares its away point with `AD04C0`; its zero branch calls `5502E0`
at `7074BA`. Thus the supplied initialized-zero profile requires the zero-point
branch. Do not substitute a nonzero point to reuse the earlier nonzero-point
composition. The supplemental initializer proof is private; it establishes
initializer outputs, not complete startup order or subsequent global lifetime.

The Unit call supplies source Cell coordinates from signed secondary X/Y /256,
speed type at type+5A4, zone -1, movement-zone 0, a raw bridge dword, rectangle 1x1,
overlay flag 0, match-level 1, burrowability 0, allow-bridge 1, a separate zero Cell
target, and final skip flag 0. Only the low byte of the bridge dword is replaced
with actor+79; upper bytes retain the signed Y quotient. Keep these arguments
distinct. Executing that actual Unit caller with this child remains next work.

## Recovered policy

- Save the signed source words, normalize only dword zone 65535 to -1, and query
  source level. A nonzero alternate low byte makes a second source lookup and
  adds 4 only for flag 100. Sum the supplied dimensions with dword wrapping and
  cap at 32; nonpositive sums do not search.
- Enumerate square rings starting at radius 0. For each X offset, visit the
  negative-Y edge then positive-Y edge; afterward visit negative-X then positive-X
  interiors. Radius 0 can append the same Cell twice. The final skip flag omits
  the negative-Y/negative-X edges and first positive-Y corner. Truncate each
  candidate coordinate to a signed word before the inline combined slot lookup.
- Forward the actual returned Cell immediately through permission and rectangle
  admission. Then apply the optional strict level-difference<2 test, optional
  predicate and bridge exclusion in that order. A miss updates the same shared
  fallback's coordinates. Keep the saved Cell identity across service calls.
- Append before projection. Failed projections remain candidates and count toward
  the 24-entry limit. A matching projection, or a nonzero alternate low byte,
  stops expansion only after the current ring. Reaching 24 stops immediately.
- Independently project **every retained candidate again**, preserving order in
  separate matching and nonmatching arrays. Use the matching array if nonempty.
  A supplied zero/sentinel target chooses by **signed frame remainder**, without
  consuming RNG. A negative remainder is an explicit native safety refusal,
  after consumed queries; it is not normalized or an original result.
- Otherwise compare distances to the live target. Square and add signed-word
  deltas with dword wrapping, then pass that signed result to the actual table
  square-root policy. Its negative-input branch takes the magnitude. Preserve
  float32 quantization, the 100000 initial best value and strict first-wins ties;
  do not widen the squared sum or substitute `std::sqrt`.

The sim helper borrows live world/target references; final selection rereads the
frame and target after service calls. Supplied diagnostic mutations verify those
late reads. `OriginalRounding` restores the caller's FP mode on returns and
exceptions. Binding and services do not establish production map ownership.
Unsupported/missing-service calls may consume stateful queries before refusal;
future previews must discard the whole call.

## Differential evidence and limits

Canonical: `private/map-depth-1006/nearby-location-v2/`. **306 complete original
search calls** match normal, ASan+UBSan and uncached native replays. The canonical
fixture also executes one sentinel initializer; the separate supplemental proof
executes both initializers. All 32 radii and all four candidate append sites run;
24-entry exhaustion occurs 13 times. There are 1,641 retained candidates and 3,167
supplied projection calls. Actual table square-root calls total 329: 297 positive,
8 zero and 24 negative. All four incoming native FP modes match. Original execution
covers 749 distinct instructions, not every branch of every inspected range.

Compare returned points, complete child-call arguments/order, projection sequence,
table-square-root outputs and final fallback/frame/target. Original whole arenas,
fallback, slot table, code/tables/globals, caller stack/registers and canaries are
guarded. Original instructions are unchanged. Service shims return authored
decisions at unchanged original targets; they do not execute those children.
No native machine-store-order or original-game observation is claimed.

Eight native safety checks per mode cover missing services, empty search,
duplicate/reread behavior, signed negative-frame refusal, zone normalization,
negative wrapped squared input and exception/FP restoration. Eight Python tests
protect parsing, exact binary/source/data/receipt identities and scope. Their
source closure and runner identities are guarded separately from the originals.
The opening handoff records full regressions and the 184-record closure; all 182
earlier records remain identical. Only Apple Silicon macOS is tested.

Initial Cells/slots, dimensions/frame/sentinels, coordinate associations and
permission/rectangle/burrowability/projection results remain supplied. This does
not join the earlier complete projection, actual permission or Cell passability.
In particular, `55A740` consumes a Cell directly; do not replace it with a helper
that performs an extra map lookup. No Unit/Cell Scatter caller, Advance6, Process,
production owned map, route search, rendering, preview or SDL behavior is added.
Runtime Scatter/Advance6 and all earlier exclusions remain refused.

YRpp `MapClass.h` at retained revision
`b22f1860dd7b100cad57123d4ca5d459b9020d88` supplies a nearby-location naming lead.
Its YR signature/address is not this base behavior. No license file was found;
no header/code is incorporated. Existing [reference boundaries](REFERENCES.md)
apply. No dependency, extracted table or runtime executable-read expansion.

## Build, try and reproduce

```sh
./build.command
./run.command --owned-demo
./test.command
PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  -m unittest discover -s tests -p 'test_*.py'

env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake -S tests/nearby_location -B build/nearby-location \
  -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_OSX_ARCHITECTURES=arm64 \
  -DCMAKE_PREFIX_PATH=/opt/homebrew
env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/nearby-location --parallel 6
build/tools-env/bin/ctest --test-dir build/nearby-location --output-on-failure
# Repeat in build/nearby-location-sanitize with Debug and -DRA2_SANITIZE=ON.

# Fresh original execution requires authorized host Unicorn JIT, NEW private paths.
PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/map-depth-1006/nearby-new-audit.json \
  tests/compare_nearby_location.py --exe private/official-1006-probe/game.exe \
  --native build/nearby-location/nearby-location-vectors \
  --output private/map-depth-1006/nearby-new
# Replay: replace --output with --expectations
# private/map-depth-1006/nearby-location-v2/expected.json --report NEW_PRIVATE_JSON.
# Sanitizer: select its runner. Uncached control: add --uncached before the driver.
```

The standalone runner is outside the app/legacy CTest graph. It uses only the
existing private hash-checked `private/derived/ra2-1006/render-data.bin` for the
already recovered square-root table. No executable read is added to the game.
Keep sources/runners fixed during guarded invocations; never rerun closed
finalizers. Pilots/v1 remain private and superseded: review removed an unnecessary
negative-distance refusal and expanded fresh v2 original cases. Initial pilot
repair supplied the required map pointer; no original instruction/result guard
was relaxed. Full manual review/repair time was not measured.

Next recover/join the required rectangle admission `550CF0 -> 478760`, direct-Cell
permission and existing projection on one shared fallback/map. Then join the
actual zero-point Unit Scatter caller, Cell dispatch and complete Advance6/
Process effects, followed by production owned actors, discarded full previews,
drawing and actual SDL acceptance. Keep all runtime guards until those joins pass.
