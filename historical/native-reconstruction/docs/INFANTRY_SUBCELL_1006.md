# Infantry subcell selection and occupation

This recovers the standing-position rules needed by Boot Camp Day 1 walking.
`InfantrySubcell` borrows Cell occupation words, flags and House-index slots;
it creates no second map or simulation. The existing Walk movement/arrival
kernel is unchanged. **The static Boot Camp preview still has no runtime GI
walking or objective transition.** The nonempty Walk head caller, its Cell
admission, ordinary preparation/commands, production bindings and animation
remain to join before ordinary SDL movement.

## Recovered boundary

The supplied executable was freshly fingerprinted:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Private inspections/evidence stay under
`private/infantry-walk-20261018/`; no public code/header, lifted/generated game
code or new dependency is incorporated. Existing YR names are only hypotheses.

The original roots are classifier4763D0, Infantry occupy508410/release5084A0 and
Cell selector4764B0. Actual483390 initializes the five offsets; actual House
getter6C7420, integer-distance47D060, table sqrt4BA410, FTOL77F110 and inclusive
RNG6388A0 execute in the proof. The native code reuses the recovered RNG and
numeric policies. The offset initializer is a readable algorithm recovered from
instructions. The nine immutable order rows at7D2B6C remain private prepared
data, with a hash-pinned reader. No application runtime reads were added.

Preserved behavior:

- Classification masks coordinate low bytes, uses the original table square
  root and integer distance<60, then strict quadrant comparisons. The northwest
  quadrant returns0; classification does not select slot1.
- Occupy/release classify before lookup/floor, retain the returned Cell identity,
  then consume late Z/threshold/flags. Height addition wraps before signed
  comparison. Occupy needs flag0x100 for elevated occupation; release omits it.
- Occupation changes only one byte, preserving the upper24 bits. Occupy then
  reads the actual House index and writes the owner dword. Release clears the
  owner to-1 only when its saved resulting byte has no0x1C bits.
- The selector saves bases by clearing coordinate low bytes, including negative
  values. Raw force bypasses bit5/building logic; otherwise selected-layer bit5
  returns the supplied empty point. Entered ground building-bit0x40 policy
  explicitly refuses until its471760/44D880 children are recovered.
- A free preferred nonzero slot wins directly; otherwise the original row order
  skips slots0/1 and occupied slots. Center selection consumes actual inclusive
  RNG0..3, retaining all state and index wrapping. Initial seeding is supplied.
- X/Y are computed before floor; floor receives the original borrowed input
  point, not the selected point. Returned Z uses floor plus the late bridge
  height for any nonzero elevated byte. A floor-service mutation does not
  recompute the saved classification, base or Cell identity.

Initial actors/House/Cell/global associations, floor/map effects, scenario/RNG
state and empty sentinel are supplied. Building/lifecycle children, the Walk
head caller and production ownership are not covered by these roots. Diagnostic
mutations test consumption order, not original-game observations. Host FP mode
is restored, including exceptions. Missing services retain preceding writes;
these low-level entries promise no rollback.

## Evidence and cost

Canonical `subcell-fresh-a1/expected.json` and immutable `report.json` contain
**409 sequences /4,964 complete root calls plus one actual initializer**:
900 classifier roots,494 occupies,944 releases and2,626 selectors. All4,964
sqrt/FTOL calls,768 RNG calls,494 House getters and2,332 selected Cell stores
execute unchanged. The matrix covers center/threshold/quadrant boundaries,
signed low-byte alignment, all64 ordinary occupation masks, both layers, raw
force bytes, retained sequences, disabled/wrapped RNG, strict/wrapped height,
owner clearing and floor mutations of live data. Full RNG state is compared.

ABI, saved registers, caller return/tail, inspected code/tables/initialized
offsets and other arena bytes are guarded. Selected Cell writes/services and
final values are compared; this is not a whole-game or exhaustive read trace.
Original instructions are unmodified and execute only in the research oracle.

Fresh original answers are saved before native comparison, allowing native
repairs to replay them even after a mismatch. `native-comparison.json` records
fresh native validation separately. Current normal/sanitizer and uncached
replays execute current C++ and zero original instructions, retaining executable,
original-source/input/receipt identities and separate current native identities.
The wrapper now includes `--subcell-data` among guarded inputs; a mutation test
checks that guard. No new cache framework or broad original-matrix run was added.

Both builds pass six native guards. Four new evidence tests and the existing
Walk/reuse tests total66 passing Python tests; five focused mission/Walk/subcell
CTests pass in each build. Rebuilt earlier runners retain624 interpolation and
380 arrival outputs (`movement-replay-*-a4.json`, `arrival-replay-*-a3.json`).
No new broad capability regression, SDL run or playable lesson is claimed at
this internal boundary. Existing two-tank and static-preview coverage retains
its scope. Local verification is not independent acceptance.

Measured fresh proof3.67s (original generation3.301s/native comparison0.054s).
Subcell normal/sanitizer replay0.258s/0.472s; uncached replay0.313s. Configure
cost5.90s/4.92s; successful fixture build3.73s/5.61s. The first1.70s build failed
on a missing closing brace in the new reader; fixed before proof. A Python test
initially compared a macOS temp symlink path with its canonical path; fixed to
compare resolved paths. Focused CTests0.11s/0.40s;66 Python tests0.738s. Overlap
makes costs nonadditive. Manual repair and total task wall were not separately
measured. Private `subcell-validation.json` records reports and measured costs.

## Reproduce

```sh
./build.command
build/native/infantry-subcell-vectors --guards
env PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_infantry_subcell test_walk_arrival test_walk_movement

# Only prepare from the legitimate supplied executable, outside its directory.
env PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/prepare_infantry_subcell_data.py \
  --exe private/official-1006-probe/game.exe \
  --output private/derived/ra2-1006/infantry-subcell-data.bin

# New private report/audit names. Executes current native code, zero originals.
env DEVELOPER_DIR=/Library/Developer/CommandLineTools PYTHONHASHSEED=0 \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/subcell-next.audit.json tests/compare_infantry_subcell.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/infantry-subcell-vectors \
  --render-data private/derived/ra2-1006/render-data.bin \
  --subcell-data private/derived/ra2-1006/infantry-subcell-data.bin \
  --expectations private/infantry-walk-20261018/subcell-fresh-a1/expected.json \
  --report private/subcell-next.json
# Sanitizer: use build/sanitize/infantry-subcell-vectors and separate names.
# Uncached inspection control: add --uncached before the driver.
# Fresh originals only for changed original dependencies: omit expectations/report,
# use --output private/subcell-new-fresh and a new audit in the authorized Mac JIT
# context. Canonical report.json is original-only; native-comparison.json is separate.
```

`./run.command --boot-camp-preview` still provides static content/selection and
explicit RMB refusal. `./test.command` remains the broad native entry point at
capability integration. Next join actual nonempty71F590 head handling and its
Cell476CC0 admission, then ordinary Walk preparation/commands on the existing
production map/actor owners. Genuine discovery/action scheduling still precedes
the first objective; do not synthesize waypoint success. Base RA2 and YR remain
incomplete; only Apple Silicon macOS is tested.
