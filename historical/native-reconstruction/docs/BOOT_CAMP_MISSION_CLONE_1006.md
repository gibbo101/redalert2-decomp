# Warm Boot Camp mission ownership clone

`BootCampMissionWorld::clone(frame)` now returns an independent stable mission
owner before discovery, with deferred cleanup queued, or after cleanup. This is
an authored host ownership adapter, not a recovered original algorithm. The
Walk arrival preview still has its initialized-only guards; this clone is not
yet integrated into the complete Walk/visibility/map/renderer snapshot.

## Ownership and boundaries

A fresh constructor binds all reference views, spans, recipient/destruction
services and callbacks to the new owner and its supplied frame reference. Warm
copying then transfers values and remaps internal identities. No bound callback
or reference view is copied. Copied values include objective and controlled
Trigger events/actions/timers/padding/occurred flags, Tag links/counts/lifetime,
Building residents/discovery/radio state, all House fields, action-request
telemetry and supplied service state. Full deferred, control, recipient and four
expiration-registry backing arrays are copied with remapped pointers, including
unused retained tails. Fallback Tag/map links and global pointers are remapped.

Unknown nonnull identities refuse rather than retaining a source address.
In-progress Tag/discovery dispatch, external discovery observers and nonzero
opaque radio interfaces also refuse. Current radio state is supplied and empty;
these checks do not add interface recovery. Partial construction is private to
the discarded clone; failure cannot mutate the source. Fixed backing/span sizes
remain those of this bounded owner, with no new allocation service.

The mission definition remains a caller-owned immutable input and must outlive
both owners. Constructor-only map/rules Ini inputs are now owned immutable
copies, so later cloning does not borrow expired constructor arguments. The
supplied frame reference must outlive its clone. Separate frames are tested;
timer reset callbacks consume the clone's frame rather than the source frame.

All existing Building activation and mission-effect limitations remain. Text,
team, reveal, audio and alliance requests are not completed gameplay effects.
No live sight or arrival scheduling, complete world snapshot or Objective1
completion follows from this adapter. No simulation algorithm, executable read,
public/reference code or dependency changed.

## Verification

`tests/boot_camp_walk_check.cpp` exercises clones before discovery, during queued
Trigger/Tag deletion and after cleanup. It compares every public mission State
field, all House fields, changed Building residents and independent identities.
It destroys source owners before executing cloned discovery and cleanup to expose
stale services/references under ASan. Both objective Buildings are exercised;
repeated discovery/draining retain results without duplicate actions. An
interrupted unsupported-action dispatch refuses cloning without source mutation.
Constructor-only Ini input lifetime is also tested.

Full normal/sanitizer builds pass; 116 normal and 115 sanitizer CTests, all 1,353
Python tests and both private-data owner checks pass. Logs under
`private/boot-camp-20261018/` use prefix `mission-clone-`, with build logs
`build-{normal,sanitize}-a2.log`, owner logs `{normal,sanitize}-owner-a1.log`,
CTest logs `{normal,sanitize}-ctest-a1.log` and `python-a1.log`.

Both rebuilt runners retain all 1,034 original coordinate and 816 original
Building discovery sequences with zero misses. These are identity-checked replays
of existing expectations, not new original executions or evidence that cloning
is original behavior. Canonical expectations remain:

- `building-coordinate-fresh-a2/expected.json`, SHA256
  `a93d841b71b5b5f00dbaed6af4c48a63717a9fd7053f20ad1f36a93fbc371972`.
- `building-discovery-fresh-a2/expected.json`, SHA256
  `69f6b2b4c8d5a9e4da096994d35f70d9042a3886632409ad897a6cb10d7bc405`.

Both reside under the private directory above. Reports and outer audits use
`mission-clone-building-{coordinates,discovery}-{native,sanitize}-a1`.
No whole-inventory refresh, original-execution cache or closed finalizer ran.
The exact supplied executable remains 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`;
embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct.

Actual 106-tick SDL movement/input/drawing regression passes at
`mission-clone-sdl-a1/`; the arrival image was inspected. It retains objectives
disabled and `original_fidelity_from_this_smoke:false`. This confirms the rebuilt
application baseline, not SDL use of the new unwired clone. Local source/runner/
log/report hashes are in `mission-clone-receipt-a1.json`; local verification is
not independent acceptance or an original-game observation.

Under concurrent checks, normal/sanitizer owner commands took 6.44/8.88s elapsed;
CTest suites reported 2.96/8.69s; Python reported 30.960s (36.90s command elapsed).
SDL command elapsed was 2.83s. Builds, host approval latency and manual review
were not separately measured. No caching was added. No failed check required
repair; existing original expectations were reused with all guards intact.

## Reproduce and continue

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
./test.command
build/native/boot-camp-walk-check private/official-1006-probe
DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/sanitize --parallel 6
build/sanitize/boot-camp-walk-check private/official-1006-probe

env PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/mission-clone-next-coordinate.audit.json \
  tests/compare_building_coordinates.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/building-coordinates-vectors \
  --expectations private/boot-camp-20261018/building-coordinate-fresh-a2/expected.json \
  --report private/mission-clone-next-coordinate.json

env PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/mission-clone-next-discovery.audit.json \
  tests/compare_building_discovery.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/building-discovery-vectors \
  --expectations private/boot-camp-20261018/building-discovery-fresh-a2/expected.json \
  --report private/mission-clone-next-discovery.json

./run.command --boot-camp-walk
./run.command --boot-camp-walk-smoke-test private/NEW-DIRECTORY
```

Use new audit/report paths on each replay. The sanitizer replay substitutes the
corresponding `build/sanitize/` runner and fresh output names. Continue with full
warm Cell/fallback, GI/Walk/membership, visibility and renderer isolation, binding
this mission clone before dependent borrowed references are built. Keep all
initialized-preview guards until that composition is verified. Required entered
caller/effects and ordinary SDL discovery still precede live sight/arrival and
Objective1. The full-game goal stays active. No workers, Windows actions,
downloads, system changes or runtime-read expansion were used.
