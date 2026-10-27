# House alliance prerequisites

The separate SDL-free `HouseAlliance.hpp` implements complete base `4EC4E0`
CanMakeAlly for nonnull borrowed House records, complete `4ED760` House lookup,
and complete `67AF90` country-name ordinal lookup around named supplied string
comparison `781F20`. It does not mutate production diplomacy. Action37 continues
to record its two ordered MakeAlly requests until the full mutation child is
recovered and joined to shared owners.

## Recovered behavior and owners

House lookup saves the signed registry count and backing once, returns the first
House whose type countryB8 matches, and accesses no records for nonpositive count.
The country finder returns the matching **slot ordinal**, not countryB8. It rereads
the country backing on each iteration and the live count after each nonmatch.
String comparison semantics (including CRT/locale behavior) remain supplied; no
ASCII replacement was assumed.

Eligibility first rejects self, equal signed House indices, and existing allies.
Index `-1` has no alliance bit; other indices use x86's low-five-bit shift count,
including negative and larger indices. It looks up `Civilian`, compares the result
with the target's **late** type parentBC, and applies the mode guard before the
unrestricted-global shortcut. Otherwise current field13D must be zero. The final
saved-registry scan counts records with zero field13D and zero type passive1A6,
then counts allies by pointer, equal index, or mask. The result is
`eligible != allied + 1`, so an empty registry returns true. Duplicate slots count
separately. Callback changes to the target type, current fields, globals, and
registry are consumed at the original late reads; entry guards are not repeated.

The API borrows actual fields and live spans. View callbacks must only return
field views, with stable identities and lifetimes; they are not query services.
Missing/null/foreign ownership and undersized registry backing are explicit native
refusals. Original null-target dereference faults are outside this domain. Initial
records, associations, globals, names, and comparison results remain supplied.
Diagnostic callback mutations exercise load order, not observed gameplay events.

## Exact-base evidence

The supplied target is 4,485,392 bytes, SHA256
`e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Embedded1.08, supplied1.006 lineage, reported no-CD provenance and unverified
pristine authenticity remain distinct. Verifier spans are `4EC4E0..4EC5DA`,
`4ED760..4ED78F`, and `67AF90..67AFCC`, plus the `Civilian` literal at `7CEB30`.
No instruction is patched; only the named comparison child is supplied. Original
caller stack, callee-saved registers, code/literal inputs, arena padding and all
mutable record/global projections are audited.

Fresh original-only expectations:
`private/boot-camp-20261018/house-alliance-fresh-a1/expected.json`, SHA256
`4e6c5295dbf18ea5333714dc61aadf28465d59d651886f7bf4065139d7d5a32f`.
All 1,305 sequences match: 1,064 eligibility entries, 86 House lookups, 1,120
country finders including nested calls, and 3,024 supplied comparisons. Cases
cover signed limits, all 256 raw byte values, aliased registry slots, first-match
selection, ordinal/B8 distinction, empty registries, wrapped shifts, early exits,
and five supplied callback modes including count/backing/owner mutation.

Fresh generation took 0.432s. Normal/sanitizer/uncached replays retain the same
original-only expectations with guarded identities; original execution and native
results are never cached. Full validation and elapsed costs are recorded in
`house-alliance-validation-a1.json`; final inventory and scope are in the opening
handoff and `house-alliance-receipt-a1.json`. Local verification is not independent
acceptance, an original whole-chain proof, or ordinary objective completion.

```sh
DEVELOPER_DIR=/Library/Developer/CommandLineTools ./build.command
./test.command
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  -m unittest test_house_alliance

# Each invocation requires new private output/audit paths.
PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py \
  --audit private/boot-camp-20261018/house-alliance-fresh-NEW.audit.json \
  tests/compare_house_alliance.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/house-alliance-vectors \
  --output private/boot-camp-20261018/house-alliance-fresh-NEW

PYTHONHASHSEED=0 PYTHONPATH=tools:tests build/tools-env/bin/python -B \
  tools/run_evidence.py \
  --audit private/boot-camp-20261018/house-alliance-replay-NEW.audit.json \
  tests/compare_house_alliance.py \
  --exe private/official-1006-probe/game.exe \
  --native build/native/house-alliance-vectors \
  --expectations private/boot-camp-20261018/house-alliance-fresh-a1/expected.json \
  --report private/boot-camp-20261018/house-alliance-replay-NEW.json
```

Recorded replays use `house-alliance-replay-{normal,sanitize,uncached}-a1`;
substitute `build/sanitize/house-alliance-vectors` for the sanitizer runner and put
`--uncached` before the driver for the control. The prior action37 parent uses
`house-prior-ally-replay-{normal,sanitize,uncached}-a1`, its existing canonical
`ally-action-fresh-a2/expected.json`, and `mission-ally-action-vectors`.
The application still runs via `./run.command --boot-camp-walk` with the existing
private data configuration. There is no new player-facing alliance command.

## Remaining MakeAlly work

The later [House threat recovery](HOUSE_THREAT_1006.md) implements complete
4F3420/4EEBA0 and their actual projection separately. MakeAlly/production adoption
remain open; the inspection checkpoint below explains their original context.

Inspection of `4E5660` shows eligibility followed by map services, mask changes,
threat-grid rebuilding (`4F3420`), threat/enemy updates (`4EEBA0`), per-Techno target
clearing and mode-dependent messages/audio. Those children are inspected only or
remain uninspected; a bit store would omit required behavior. Recover the entered
complete children and original parent before production adoption. Then bind shared
House/type/Techno owners, validate discarded full warm previews and continue Team,
audio, scheduling/UI and ordinary SDL objective acceptance. Both games and Boot
Camp Objective1 remain incomplete. No runtime executable reads or public/YR/recomp
code/dependency were added; Unicorn remains research/test-only.
