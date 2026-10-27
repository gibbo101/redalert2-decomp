# Boot Camp first-objective production mission owners

`BootCampMissionWorld` now gives the application stable owners for the first
Day1 discovery objective. It binds supplied mission Tag `043BD15C`, Trigger
`043B011C`, its one discovery event and ten action records, and structures
`1019675`/`1019676` from the same `MissionDefinition` already used by
`BootCampWalkWorld`. The owner reuses recovered Unit discovery, Trigger, Tag,
expiration, deferred cleanup and destruction kernels. It is not a second
simulation or a replacement mission engine.

**Action4 Create Team, action11 Text Trigger, action19 Play Sound Effect, action21
Play Speech, action37 Make Ally, action53 Enable Trigger, action54 Disable Trigger
and action17 Reveal Around Waypoint parent forwarding are now recovered.
The application does not invoke structure discovery. Walking and objective status
are unchanged. The reveal child and its map/visibility effects remain supplied.** Read
[MISSION_CREATE_TEAM_ACTION_1006.md](MISSION_CREATE_TEAM_ACTION_1006.md),
[MISSION_AUDIO_ACTION_1006.md](MISSION_AUDIO_ACTION_1006.md),
[MISSION_ALLY_ACTION_1006.md](MISSION_ALLY_ACTION_1006.md),
[MISSION_TEXT_ACTION_1006.md](MISSION_TEXT_ACTION_1006.md),
[MISSION_REVEAL_ACTION_1006.md](MISSION_REVEAL_ACTION_1006.md) and
[MISSION_TRIGGER_CONTROL_1006.md](MISSION_TRIGGER_CONTROL_1006.md).

## Scope and ownership

The exact supplied base remains 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Only Apple Silicon macOS is tested. This
milestone performs no original execution, executable read, Windows action,
download or dependency change.

Construction validates the actual supplied Day1 relationships:

- Tag `043BD15C` has persistence0 and points to Trigger `043B011C`.
- The Trigger belongs to Other2, has exactly event4/value0 and the ten supplied
  action definitions with kinds `11,4,17,19,37,54,53,21,54,53`.
- Structures `1019675` (CAARMY04 at71,92) and `1019676` (CAARMY01 at69,96)
  both own the Tag. Recovered Object Tag assignment produces instance count2.
- House identities come from the mission's actual House table. The bounded
  `Other2`/`Other2 House` spelling association is explicit supplied startup policy.
- Trigger uses destruction registries A40AA0/AC0CB0/AC0D48 and Tag uses
  AC0CB0/AC0D48/ABFE48. The native owner retains four physical vectors with the
  middle two shared. The Tag expiration map/logic views also borrow those shared
  vectors instead of copying their values.
- Four actual action targets `0922D5DC`, `0922D40C`, `08FABE0C` and `09CA94AC`
  are stable owners in all three Trigger registries. Their timer events and action
  records come from the supplied map. Difficulty0, timer scratch0, initial disabled
  state and the `Americans`-to-player-House association remain supplied startup.

The application constructs this owner inside `BootCampWalkWorld`, alongside the
existing GI and mutable map owners. It does not schedule or synthesize discovery.
The real structure records are not yet rendered or inserted into recovered Techno
membership; their mission identity, Tag reference and discovery fields are stable
owned records at this bounded join.

## Native composition check

`boot-camp-walk-check` first verifies the production owner is cold: two tagged
structures, Tag instance count2, empty deferred queue and registry counts5/6/6/1.
Calling discovery without action effects refuses before any mission mutation.

With the named diagnostic action callback installed, actual `discoverUnit` invokes
the recovered Tag event on structure1019675. The recovered Trigger traverses all
ten actual action records. Kind11 records the Objective1 text request first,
kind4 records the 0B197B7C TeamType-child request, kind19 records the HealCrate sound-child request, kind37 records mutual
Other2/player alliance-child requests, kinds53/54 execute through the recovered
control kernel, kind21 records the Drill Sergeant speech-child request, and kind17
records the supplied reveal-child request. The Objective1 Trigger is
destroyed and queued, both Object Tag references clear through recovered Tag44
expiration, and the Tag is queued. Before cleanup, queue order is Trigger then Tag,
instance count is0, registries are5/5/5/1, controlled enabled bytes are0/1/0/1
and enabled timers hold1500/570 ticks. Recovered cleanup destroys Objective1's
Trigger then its Tag and leaves the four controlled Triggers in registries4/4/4/0.
Stable storage records base/free effects; it does not emulate heap deallocation.

Generic kind-38 expiration beyond the recovered Tag recipient remains supplied.
Initial construction/vtable/heap associations, original scheduler/pulse production,
House/difficulty startup, structure membership/rendering, reveal child effects,
timer firing and objective UI/state remain supplied or unrecovered. The test
callback's false results and absence of those effects are diagnostic inputs, not
original observations.

The exact behavior of every reused kernel remains covered by its existing fresh
original and normal/sanitizer/uncached replay receipts. This new composition is a
current-native shared-owner check against actual mission data. It adds no new
original evidence and is not independent acceptance.

## Checks and commands

Normal and sanitizer `boot-camp-walk-check` pass on the supplied Day1 assets,
including the prior eight-direction movement, Stop/repeated orders and refusal
isolation. Direct normal/sanitizer checks took1.38s/4.76s; their final incremental
build-plus-check invocations took2.07s/9.87s. Eleven mission CTests pass in each
build and24 related Python guards pass. The normal SDL application build took
1.97s and passes with the existing harmless duplicate-library warning.
No SDL smoke was rerun because this internal owner is not called by the current
player flow.

```sh
./build.command
./test.command
./run.command --boot-camp-walk
# Player-visible capability remains selection/walking/Stop/pause.
build/native/boot-camp-walk-check private/official-1006-probe
build/sanitize/boot-camp-walk-check private/official-1006-probe
```

Next recover the actual discovery producer/schedule that calls these production
records, then the relevant child effects. Only then may ordinary SDL movement into
discovery range advance Objective1. Do not substitute destination arrival or
diagnostic callbacks for original discovery/action behavior. Full base RA2/YR
remains incomplete.
