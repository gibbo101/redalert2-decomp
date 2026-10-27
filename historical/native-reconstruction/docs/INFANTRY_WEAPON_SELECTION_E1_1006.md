# Ordinary E1 weapon selection through a null target

October 18, 2026, after `5cdd6ee`. Complete base `508530` and its entered
complete base `6C1380` selector now have a readable SDL-free implementation for
ordinary Infantry states, stock E1 weapon slots and the null-target exit used by
the Boot Camp position-effects preview. This closes the former guessed-zero
`+2B8` child at that owner seam. It does not schedule position effects or add
combat.

## Exact identity and ranges

The private supplied base target is 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Its reported no-CD provenance, supplied 1.006 lineage and pristine authenticity
remain separate facts.

`tools/verify_infantry_weapon_selection.py` pins these complete ranges:

| Routine | Bytes | Instructions | SHA256 |
| --- | ---: | ---: | --- |
| Infantry override `508530..508570` | 64 | 19 | `c5d81692f8afcf28328c7d12497db868c7c03cb29e44f010c641122770cb2b5a` |
| Common selector `6C1380..6C15D0` | 592 | 207 | `dd9b7ba0993f6414080cceb4df6759ac5dd9abdb7e12eb252fdf41814065499d` |

The proof also executes and pins the actual Infantry type getter, multiple-
turret predicate, weapon getter, promotion test, normal/elite slot leaves,
mission getter and kind leaf. The verified Infantry vtable associations include
`+2C=509800`, `+80=6C12C0`, `+84=506950`, `+16C=594770`,
`+2B8=508530` and `+39C=6D8540`.

## Recovered bounded behavior

For tested ordinary signed states outside 27 through 30, the selected path:

1. queries the live actor type and refuses the unverified positive-turret-count
   branch in the native E1 profile;
2. queries secondary slot 1, then primary slot 0;
3. selects elite slots when veterancy is at least 2, but falls back to the same
   normal slot when an elite slot has no weapon;
4. returns zero when either effective slot is absent or the secondary weapon's
   byte `+112` is nonzero;
5. returns one when secondary byte `+126` is nonzero and the live mission is 16;
6. otherwise performs both actual Infantry-kind queries and returns zero for a
   null target.

The first native draft missed the elite-to-normal fallback. Fresh original
execution exposed the extra type/normal-slot query, and the accepted
implementation now preserves it. No failed draft receipt was accepted.

The field names `NeverUse` and `AreaFire` are navigation vocabulary from the
pinned YRpp header. Exact base reads at `secondary+112/+126`, branch behavior and
execution establish the algorithm. The supplied `rules.ini` E1 records identify
`M60`, `Para`, `M60E` and `ParaE`; all four sections exist, and `NeverUse` and
`AreaFire` are absent/false for these supplied records. This rules association is
explicit supplied startup data, not recovered WeaponType construction.

## Evidence and Boot Camp owner join

Canonical fresh receipt:
`private/boot-camp-20261018/infantry-weapon-selection-fresh-a3/`.
Its expectation SHA256 is
`fb6d7dadf7ef9d2d5adf21d06832312f89fe696f67c551830dfcbaa7b89660cd`.
The 64 fresh roots contain 64 complete `508530` and `6C1380` calls, 190 type
queries, 120 weapon getters, 77 normal-slot leaves, 49 elite-slot leaves, 16
mission queries and 64 kind calls. Normal, sanitizer and uncached replays retain
64 hits and zero misses.

`BootCampWalkWorld` stores the four supplied weapon records under its existing
E1 type owner. The discarded update-position preview passes the actual GI
`state5AC`, veterancy and kind. Stock Para reaches three type queries, no selector
mission query and result zero. Normal and sanitizer owner checks retain all live
Walk, mission, visibility and Cell state. The strengthened complete `4C7220` and
joined `500AA0` receipts now execute `508530` in the same guest. Their older
receipts retain the supplied-boundary identity under which they were generated.

The full normal build, all 113 normal CTests, all 112 SDL-disabled sanitizer
CTests and 1,340 project-local Python tests pass. A fresh 106-tick actual
host-display SDL regression passes selection, movement, drawing, pause, refusal,
Stop, repeated order and deselection at
`private/boot-camp-20261018/infantry-weapon-selection-sdl-a2/`. Its report keeps
`objectives_enabled: false`; this selector is exercised by the discarded owner
preview, while production crossing remains unchanged.

States 27 through 30, positive turret count, nonnull target decisions and every
later target/type/weapon branch remain explicit native refusals. Full WeaponType
startup, firing, damage and combat are not recovered here. Production Cell-
crossing position effects and Objective 1 remain unscheduled.

## Reproduce

```sh
./build.command
./test.command

env DEVELOPER_DIR=/Library/Developer/CommandLineTools PYTHONHASHSEED=0 \
  PYTHONPATH=tools:tests build/tools-env/bin/python -B tools/run_evidence.py \
  --audit private/infantry-weapon-selection-next.audit.json \
  tests/compare_infantry_weapon_selection.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/infantry-weapon-selection-vectors \
  --expectations private/boot-camp-20261018/infantry-weapon-selection-fresh-a3/expected.json \
  --report private/infantry-weapon-selection-next.json
# Use build/sanitize/infantry-weapon-selection-vectors for sanitizer replay.
# Add --uncached for an inspection-cache control and use new private names.

build/native/boot-camp-walk-check private/official-1006-probe
build/sanitize/boot-camp-walk-check private/official-1006-probe
./run.command --boot-camp-walk-smoke-test private/boot-camp-weapon-selection-next
```

That joined proof is now recorded in
`INFANTRY_UPDATE_POSITION_EFFECTS_E1_1006.md`. The parent sight/map join and
exact selected-head producer are now recorded separately; production scheduling
still waits for a joined original Walk-to-parent root.
