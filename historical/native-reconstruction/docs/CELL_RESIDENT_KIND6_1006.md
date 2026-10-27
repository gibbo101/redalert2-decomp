# Scenario-loop Cell kind-6 resident search

The image-initial byte at `A40958` is no longer treated as permanent zero for
the bounded Infantry update-position path. An inspected scenario-loop caller
sets it to one, and complete base `4717B0` conditionally searches a Cell's
primary resident list for the first object whose dynamic kind is 6.

## Setter and caller boundary

Exact supplied executable: 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.

The complete game-loop function range `481BF0..481EFC` is pinned at 780 bytes.
Its only two direct calls to `5135F0` are:

- `481CFA..481D08`, before the loop body;
- `481ED4..481EDF`, on loop continuation.

The executable has no other direct `call 5135F0` sites. The two inspected
top-level call sites at `690863` and `690883` enter `481BF0`. Both loop call
sites load the same byte at `7D3338` into `CL` before the call.

The bounded `5135F0..51362B` prefix is 59 bytes. It establishes its stack frame,
calls supplied `6E8510` and `6E7EB0`, loads the scenario owner, then writes byte
one to `A40958` unconditionally at `513624`. The rest of `5135F0`, scenario
selection, object construction and the full top-level caller are not translated
or claimed complete. `initializeCellResidentKind6` represents only this selected
store after entry to the inspected loop.

## Complete traversal

Base `4717B0..4717DF` is 47 bytes and complete. It preserves this order:

1. read the enable byte;
2. when zero, return null without reading the Cell head or calling a service;
3. read primary head `Cell + E4`;
4. when null, return null;
5. call each resident's virtual slot `+2C`;
6. return that resident immediately when the result is 6;
7. otherwise read `resident +30` and continue until null.

The native kernel keeps the enable state byte-sized. Kind and `Next` services
are required only on entered nonempty traversal. A kind-6 hit does not query its
`Next`, and the disabled path does not inspect a supplied nonnull head.

## Differential evidence

Canonical receipt:
`private/boot-camp-20261018/cell-resident-kind6-fresh-a3/`.
Expectation SHA256:
`307a59c2cf63a17b9e540d96ce357ece2789c467fb12c0e0595f3b8dcc8de2b3`.

The 64 fresh sequences execute 64 complete `4717B0` roots, both loop caller
slices, 40 actual setter stores, 133 supplied dynamic-kind calls and 112 actual
`Next +30` reads. They cover initial bytes 0, 1 and 255; disabled nonempty lists;
initialized empty lists; first, middle and absent kind-6 residents; and unrelated
negative and positive kinds. Original code bytes are unchanged. The virtual kind
child and the two calls before the setter remain explicit supplied boundaries.

Normal, sanitizer and uncached native replays each have 64 reuse hits and zero
misses. Fresh original generation was 0.010s and native comparison 0.011s inside
the 0.531s driver; wrapper and manual research costs are separate. Failed fresh
`a1`, superseded `a2`, and failed first normal replay receipts remain private and
are not accepted evidence.

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools PYTHONHASHSEED=0 \
PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/cell-resident-kind6-next.audit.json \
  tests/compare_cell_resident_kind6.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/cell-resident-kind6-vectors \
  --expectations private/boot-camp-20261018/cell-resident-kind6-fresh-a3/expected.json \
  --report private/cell-resident-kind6-next.json
```

## Remaining integration boundary

This establishes the loop-initialized value and the exact search algorithm. It
does not yet bind `findKind6` in the complete `500AA0` composition to the actual
Boot Camp mutable Cell primary list and actor `Next`/kind records. That ownership
join, followed by fresh affected parent/composition replays, still precedes
scheduling update-position effects in `BootCampWalkWorld`. Runtime and SDL
Objective 1 behavior remain unchanged.
