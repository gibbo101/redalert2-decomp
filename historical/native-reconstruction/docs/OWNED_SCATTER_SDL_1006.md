# Two-tank resident displacement through SDL

The later [preparation-neighbor fix](PREPARATION_NEIGHBOR_1006.md) retains the
first2,034 frames/56 PPMs and appends the formerly failing200-tick control. The
3,418-frame/81-PPM checkpoint reaches92,105 and clears the target at tick884.
The current3,665-frame/88-PPM extension retains that entire prefix and adds an
ordinary positive Crushable-neighbor approach87,101 ->86,102 beside85,103,
actual curve64=1, arrival and strict overlay-command refusal. See that note and
the opening HANDOFF for current receipts and the original proof's bounded scope.
The failure/next-step account below describes the earlier checkpoint.

Normal `--owned-demo` now explicitly selects the existing `ordinaryScatter`
profile on construction and reset. Two actual actors retain their own Drives,
commands, timers, turrets and drawing resources on one mutable map. There is no
new movement algorithm or mirrored world. Low-level inputs and the optional
factory argument keep guarded defaults. `--owned-smoke-test` explicitly retains
the earlier ordinary0/2/7 regression profile; `--owned-scatter-smoke-test` uses
the same profile as normal play.

The factory now supplies destination delay8, matching the separately supplied
wait duration and original-backed encounter inputs. Foot destination writes this
to wait558, while retry530 is cleared. This is an explicit supplied setup value,
not recovery of original rules initialization. Initial actor/type/House records,
direct routing and its one-positive-response budget, close threshold0, named
heap/mission effects, controls, clearance, camera and scheduling remain supplied.

## Observable capability

The 2,034-frame SDL sequence injects actual LMB/RMB/Ctrl-RMB/Q/D/Space/R/H events
through the interactive handler and uploads/presents real frames. It never edits
positions, targets, membership, Drive indexes or queues to manufacture the case.
It does not use K or full-journey prediction to accept commands.

On `mp03t4.map`, ordinary moves stage actor1 at94,101, actor0 at91,101 then91,104,
and actor1 at93,104. Supplied staging waits110/137/95/114 match measured native
arrival intervals. At tick456, actor0 receives a direct order toward94,104.
The actual candidate preparation dispatches stationary resident1 once at tick497.
Actual nearby handling selects92,103, destination XYZ23680,26496,416. Complete
drawing immediately after Process0 preserves its actual nonnull target before
the supplied route follower runs. Resident1's later Process calls move it there;
the first recorded arrival/target-clear frame is tick553. Drawing checks actual
target state and distinct poses/resources/registry identities every frame.

Actor0 subsequently enters the vacated93,104 Cell; actor1 independently moves to
92,104 and receives body/turret commands. A masked-Cell RMB command preserves both
positions, destinations, all24 queues, commands, targets and the tick. Separate
native checks compare the complete selected world snapshot and warm pixels for
out-of-domain, overlong and masked refusals. Existing clone/target/counter/fault
isolation tests remain, including a propagated observer fault on a discarded clone.

After a real reset, a second ordinary input sequence reaches curved Advance6 at
tick514 with directions2/4/3. Its late head Cell dispatches the mover itself,
not the other tank at the candidate Cell. Nearby handling selects92,104; actual
arrival/target clear first appears at tick556. The other tank stays put and later
accepts an independent command. Pause/resume/reset and warm cache reuse pass.

The candidate's resident-target, vacated-Cell and self-target frames were visually
inspected. The final rebuilt app's trace and all56 PPMs equal that candidate.
The retained ordinary regression passes1,573 frames, including actual Advance7;
its trace and all58 PPMs equal the previous target-drawing baseline. That separate
profile retains its occupied/future reservations; normal Scatter play uses actual
tick-time resident handling instead of those command reservations.

## Original evidence and limitations

The [distinct original pair](OWNED_SCATTER_PROCESS_PAIR_1006.md) remains the
original/native evidence:256 actual Process roots,139 results and six complete
draws on distinct actors/Drives sharing one guest/map/graphics state. The exact
supplied executable SHA256 is
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`,
4,485,392 bytes. Embedded1.08, supplied1.006 lineage, reported no-CD provenance
and unverified pristine authenticity remain distinct.

Current rebuilt normal/sanitizer runners reuse eligible immutable original answers
and compare all139 results. Their source and binary identities differ from the
origin; both run current native code with zero original execution. No origin is
edited/imported/relabelled. The origin's `normal_SDL_Scatter_still_guarded` field
describes its earlier checkpoint; current SDL policy is established by this
source and the new SDL receipts, not that historical field. Selected snapshots
and complete drawing tokens are compared; Process event prefixes remain
diagnostics, not an all-Process ordered-store proof. No new original addresses,
runtime executable reads, dependencies or generated/lifted code are introduced.

The first SDL attempt used200 ticks for each staging move. At tick841 nearby
handling selected92,105; a later live movement query refused the existing terrain
profile at tick847. Its failed log/trace/frames remain under `candidate-a1/`.
No terrain guard, candidate ordering or original decision was changed to evade
it. The supported scenario uses the already measured staging schedule. Other
timings/routes can still enter unsupported terrain children and terminate the
prototype; command acceptance does not predict eventual arrival or roll back
partially executed live ticks. Recovering that exact refused query is next.
Do not redirect the original-selected destination to a more convenient Cell.

SDL events and screenshots are native integration evidence, not original UI,
whole-frame fidelity, original pathfinding or game completion. Only Apple Silicon
macOS is tested. Local verification is not independent acceptance. Base RA2/YR
and the full-game objective remain incomplete.

## Reproduce

```sh
./build.command
./run.command --owned-demo
# LMB either tank, RMB direct move, Ctrl-RMB waypoint, Shift-RMB aim;
# Q/E body, A/D turret, S stop, Space pause, R reset, H center.
./run.command --owned-scatter-smoke-test private/try-scatter-sdl
./run.command --owned-smoke-test private/try-ordinary-sdl
./test.command

env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  build/tools-env/bin/cmake --build build/owned-terrain-runtime --parallel 4
build/tools-env/bin/ctest --test-dir build/owned-terrain-runtime --output-on-failure
# Repeat in build/owned-terrain-runtime-sanitize (-DRA2_SANITIZE=ON).

# New private output/audit paths each time. Hit-only refuses a cold key.
/usr/bin/time -p env DEVELOPER_DIR=/Library/Developer/CommandLineTools \
  PYTHONHASHSEED=0 PYTHONPATH=tools:tests \
  build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/scatter-sdl-next.audit.json \
  tests/compare_owned_scatter_world.py \
  --exe private/official-1006-probe/game.exe \
  --native build/owned-terrain-runtime/owned-terrain-runtime-vectors \
  --original-cache private/original-results --original-cache-require-hit \
  --output private/scatter-sdl-next
# Sanitizer: build/owned-terrain-runtime-sanitize/owned-terrain-runtime-vectors.
```

SDL needs the Mac host display context. No system/Xcode/DRM changes or Windows
actions are involved. Current receipts, hashes, check costs and remaining work
belong in the opening HANDOFF and `private/owned-scatter-sdl-20261018/`.
