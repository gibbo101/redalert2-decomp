# Original INI byte and line input

[INI_INPUT_LIFETIME_1006.md](INI_INPUT_LIFETIME_1006.md) separately recovers
buffer allocation/cleanup and source attachment/splicing. Actual parser/list/
index construction remains unjoined; earlier input evidence retains its scope.

`src/assets/IniInput.cpp` recovers complete line reader639670, buffered Read494760
and source forwarding69B0A0.306 original sequences compare returns, selected
ordered stores, persistent pipe fields and all supplied output/buffer bytes.
The line reader is tested both alone and through the actual buffered pipe and
forwarder. Upstream reads and CRT memcpy remain supplied services. This is an
unwired asset-loading dependency, not original INI parsing or scenario startup.

## Recovered behavior

The line reader consumes through LF or a read result other than exactly1.
It drops CR, keeps embedded NUL bytes in storage and returns the length through
the first NUL. Capacity limits stores, not consumption: an overlong line is
consumed completely before the next call. Capacity0 or null output returns0
without accessing children or EOF; negative nonzero capacity still consumes
input and writes a terminator. LF leaves the existing raw EOF byte unchanged.
A failed read sets EOF to1 and writes the output terminator twice. EOF may alias
the destination; ordered stores preserve that behavior. Unsafe null-EOF writes
and writes beyond supplied physical backing refuse.

The pipe borrows source4, mutable bufferC, signed size10, cursor18 and available1C.
A null buffer/output or nonpositive request returns0. Positive available bytes
are copied before refilling. Cursor and available are read after the copy child,
before either field store; cursor is written first. Refill snapshots buffer/size,
forwards through the current source, stores the raw result into available then
clears cursor. A negative nonzero source result retries; it is not clamped into
EOF. The supplied source must terminate within the bounded execution domain.
Source forwarding returns0 on null source, otherwise forwarding raw arguments
and result. These owners are explicit borrowed asset-layer fields, SDL-free and
independent of simulation/platform startup.

## Evidence boundary

Exact executable:4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD and unverified pristine
provenance remain distinct. The verifier fingerprints before using addresses.

| Complete span | Bytes / instructions | SHA256 |
| --- | --- | --- |
|639670|152 /68|`cbf2e6b3fdb809bf93b90819c60debf09ae5dcf1342ab6dd77fead74bdccb3c2`|
|494760|147 /63|`096b5ad627cea6c5c0fd48fd5fd3d02fcbccd7f2f21c4c349357b6899f689ac0`|
|69B0A0|30 /12|`5bf143545676ce6bf0d3b4b77efbd2fc07b3f2e1d9ae045d47d8b53202b63b4e`|

The actual INI pipe vtable7A3BBC+8 resolves to494760. Oracle execution keeps
original instructions unchanged. Caller stack/return/callee-saved registers,
immutable routine/vtable inputs and full supplied arena preservation are checked.
Upstream and memcpy arguments/ranges are checked; those children remain supplied.
Post-store mutations occur at the next instruction boundary, preserving original
write timing. Source/backing/size/cursor/available mutations exercise saved versus
late reads. Tests include repeated calls, preloaded buffers, signed requests,
negative/nonone/zero source results, CR/LF/NUL/high bytes, raw EOF/aliases and
510/511/512/600-byte lines at the parser's inspected512-byte capacity.

The first attempt failed a fixture range assertion for a valid zero-byte upstream
read into stack scratch. The corrected assertion permits an empty range; fresh-a2
passed. Both audits remain private. No original instruction patch or relabeled
failed receipt. Earlier truncated call scans and constructor/parser disassembly
are inspection leads only, not proofs.

## Reproduce

```sh
./build.command
./run.command --boot-camp-walk
./test.command
DEVELOPER_DIR=${DEVELOPER_DIR:-/Library/Developer/CommandLineTools} \
 build/tools-env/bin/cmake --build build/native --target ini-input-vectors -j 6
build/native/ini-input-vectors --guards
PYTHONPATH=tools:tests PYTHONHASHSEED=0 build/tools-env/bin/python -B \
 tools/run_evidence.py --audit private/NEW-ini-input.audit.json \
 tests/compare_ini_input.py --exe private/official-1006-probe/game.exe \
 --native build/native/ini-input-vectors \
 --expectations private/ini-construction-20261020/input-fresh-a2/expected.json \
 --report private/NEW-ini-input.json
PYTHONPATH=tools:tests build/tools-env/bin/python -B -m unittest test_ini_input
```

Use build/sanitize runners with distinct audit/report paths for sanitizer replay.
Original expectations are reused only with matching dependencies; current native
always reruns. No native verdict is cached. Fresh generation uses a new private
`--output` instead of `--expectations`/`--report` and requires research JIT access.

## Next dependency

Inspection of parser50BC30 finds separate initially-nonempty merge and initially-
empty construction paths. Nonempty loading calls50E5F0 WriteString; empty loading
constructs linked Sections/Entries and CRC indexes. Neither path is recovered by
this input proof. Next complete the entered buffer/list/index construction and
merge/replacement children, then the actual parser with original linked order.
Persistent observer/Type/Rules/FP ownership and entered Tag/base lifetime children
remain prerequisites to exhausted tick8/teardown. AC0C18/Neuron startup and
transferred-GI movement6BA990 remain open before genuine Team/arrival/sight/SDL
objectives. Both base RA2 and YR/full reconstruction remain incomplete.

Pinned YRpp CCINIClass.h was consulted only for names/navigation hypotheses.
Its existing unidentified-license restriction remains: no header/code was
incorporated, no YR address/behavior was assumed valid for base RA2. The algorithms
above derive from the fingerprinted base executable. No runtime executable read,
new dependency, live scheduling or visible gameplay capability is added.

## Validation and cost

Canonical306 answers:`private/ini-construction-20261020/input-fresh-a2/expected.json`, SHA256
`ac9b25c1fd25ce7629784a708d1e15dcae565781e0cbeab2aed4e62feedd510d`. Normal/sanitizer each pass11 focused
CTests and replay4,056 original sequences (306 new plus3,750 prior INI/observer/
Team sequences), all hits/zero misses/current native.37 Python tests pass.
No broad SDL repetition for this unwired layer. Local verification is not
independent acceptance or whole-game fidelity; only Apple Silicon macOS is tested.

Fresh-a2 original generation 1.363s. Normal/sanitizer focused builds
7.081/7.437s, CTest processes0.682/1.148s, sanitizer configure17.245s;
Python process0.732s. Input replay processes0.864/0.562s. All other
replay process timings and logs are retained in
`private/ini-construction-20261020/input-validation-a1/`; script:
`private/ini-construction-20261020/input-validate.py`. Earlier configure/build,
failed fixture attempt, inspection/edit/repair and total wall costs were not
separately measured. Durations may overlap and are not additive. Receipt:
`private/ini-input-receipt-a1.json`.
