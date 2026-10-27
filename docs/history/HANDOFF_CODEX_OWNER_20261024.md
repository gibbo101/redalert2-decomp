# Handoff — original-target decompilation

Accepted state: numbers in [STATUS.md](STATUS.md) (generated per commit).
Workflow: [process](ORIGINAL_TARGET_PROCESS.md). Tools/commands:
[build](ORIGINAL_TARGET_BUILD.md). Older per-batch detail: [history/](history/).
The Codex owner goal is paused at the user's request; recovery is incomplete.
For the prepared transfer back to Claude, start with [CLAUDE_HANDOFF.md](CLAUDE_HANDOFF.md).
The goal text and the other workers' goals are unchanged.

## 2026-10-20 process reset

The user approved a throughput-oriented workflow (see [AGENTS.md](../AGENTS.md)):
iterate on near misses instead of closing them, score candidates with
`diff_candidate.py`, seed from Ghidra with `seed_candidate.py`, sweep with
`sweep_seeds.py`, select by class with `class_inventory.py`, no separate
reviewer requirement, full build before commits only, generated status. Earlier "closed at zero", "no steering/tuning" and "do not reopen" holds
in history notes are lifted: they are resumable misses. Original-bound, reference
and padding holds still stand; those are evidence questions, not effort limits.

Trial evidence for the new loop (scratch only, nothing accepted):

- `build/sweep-trial/queue.md`: 300 unrecovered functions seeded and compiled in
  3.6 minutes; 230 compiled, **34 byte-exact from unedited Ghidra seeds**
  (786 body bytes), 26 more scoring ≥75.
- The closed A16 6B1710 first model scores 64 (`diff_candidate.py`, 245-byte
  frozen bound): same calls and constants, differences in register choice and
  store scheduling. A normal iteration target.

Build speed: `build.py` compiles every group (about 1,700, one per
population/option set or separate template unit) in four concurrent Wine
sessions in one prefix (`parallel_sessions` in the config, default 4); a full
fresh build takes about 3.7 minutes. Plain Wine 11.18 is the host (see build
doc); `diff_candidate.py` takes about 2s per run.

## Owner handoff (2026-10-24)

Updated 2026-10-25. The Claude session is owner again (user decision,
2026-10-25); codex1's DirectDraw rendering probe 0x4957E0 (R1126, 386+14) has
landed. Since then: Techno13 (Mac, Sonnet) TechnoClass, RadioClass and
MissionClass::AI rounds; Objs13 (Mac, Sonnet) OverlayClass Read_INI/Load/slot 68
and TeamTypeClass. The old queue items /GR tooling, Cell/BaseNodeClass with
HouseClass::Detach and the bool returns of TeamClass 0x6B8FB0 / TechnoClass slot
214 were already landed by the Codex owner (6e61ae62, 15fdd70c). Pending: a
Techno13 rename batch (slots 199/263, Is_Busy, Unknown_00549C50, Display
0x49E000) and an Objs13 TeamClass batch (0x6B3DF0 returns bool; no duplicate
AITriggerTypeClass view). Lanes: Codex BOARD.md.

Open evidence (Objs16, 2026-10-26; drafts in build/class-work/Objs16/):
0x721B00 is 238 bytes (ret 8 at 0x721BED) and 0x60B670 is 1,277 bytes (ret at
0x60BB6C), both need stated body_bytes; 0x6A7110 is a TacticalClass member
(ECX from 0x83996C), not the free unknown_cell_byte_11c; ParticleClass +0xBC is
one Vector3 (needs 0x60A0E0 and ctor 0x608980 re-supplied); CellClass 0x475840
is bool(unsigned, int) const. Matrix3D: the original both calls the copy
constructor 0x58FE10 (15 sites) and copies inline (rep movsd) in 0x608BB0,
0x609540, FootClass slot 246 and 0x718D60; keep the declaration and try
assignment (implicit operator=) at the inline sites rather than removing it. Template debt (Tmpl18, 2026-10-26): hsv_class.hpp,
hash_string.hpp and vector_elements.hpp redefine element types also defined
in ccini_extra.hpp / text_print.hpp (no unit includes both yet); unify into
one definition each. SubzoneTrackingStruct Fetch/Clear/Resize are exact in
isolation but emit template copies with no original standalone function. Naming (TType21 r4, landed): InfantryTypes, UnitTypes,
AircraftTypes, BuildingTypes, their From_Name and ArtINI now carry real names
everywhere. Clean22 (r1-r3, f9a15c48) named 32 more global lists, single-declared
Debug_Printf, unknown_check_406f30 (sound_available.hpp), BuildingTypes
(building_type_list.hpp) and ThemeClass. Remaining naming debt: Triggers, Particles,
Bullets, Overlays and Buildings keep placeholders because the names collide with
class members (would rebind silently); anim_type.hpp types AnimTypes as TypeList but
the globals unit proves a DynamicVectorClass (vtable 0x7A2824), ~92 refs to retype;
unknown_anims_a35e60/supers_a35db8/tubes_8661c8/overlay_types_a35de8 are typed stand-ins;
IsoTileTypes is declared in isometric_tile.hpp and map_cell_view.hpp. Partial class
views (house_screen HouseClass) are load-bearing: the full house.hpp adds static
initializers.

Mac lanes (2026-10-27): Rules23 (Opus; r6 next: Save 0x64DE70 and Sides
0x64BC10 need TypeList::Save `&(*this)[index]` and DynamicVectorClass::ID
looping on `index < Count()`, full build first), Screen26 (Opus; MapClass, ~200
Map.cpp functions left; pending Map slot 25 Detach rename batch, slot 29 0x549AE0
exact but techno.hpp drags house.hpp static initializers). Finished: Recomp24
(recomp boundary triage in build/class-work/Recomp24/triage.md, 471 too-short
inventory rows in inventory_fixes.json; open: command registration 0x5173C0 at
76.7 holding 47 dtors, Conflict::Init_Options 98.01), Surf25 (resume notes in
build/class-work/Surf25/NOTES.md; depth/alpha line family blocked on register
choice), Regalloc27 (rule now in VC6_MATCHING_NOTES.md). The recomp at
/Volumes/Lesalia/Code/redalert2-recomp (same build, MIT) supplies bound
hypotheses only: build/recomp-crosscheck/.
Template debt: RulesClass Sides 0x64BC10 is exact only when DynamicVectorClass::ID
loops on `index < Count()` (likely the real source), but 142 units that recover
vector copies with `template class DynamicVectorClass<X>;` then emit a Count
COMDAT the original never had (no out-of-line Count exists; the original was
linked without identical-code folding). VC6 ignores member-only explicit
instantiation, so those units need their copies emitted through real uses
instead (list: build/class-work/Rules23/d/sid/units.json; draft
Rules23/w/sides_exact_countID.cpp). Map.cpp header statics (population-263)
merge into the Map unit only once its two table initializers 0x5441D0/0x546190
(8,102 and 6,028 bytes, Cell spread tables) are recovered: the original
.CRT$XCU table at 0x7CA7E8 must appear contiguously (Screen26). TechnoType Load 0x6DE260 is at 98.19 (ebx/ebp choice),
Damage_Smoke_Offset ~63. Codex owner recovery had paused at the fully closed exact
checkpoint `cec6c563`. The next owner handoff is prepared for Claude in
[CLAUDE_HANDOFF.md](CLAUDE_HANDOFF.md); that document records the pause boundary,
current queue and worker identities. No owner integration job is in flight.
Full executable recovery is incomplete. Generated counts: [STATUS.md](STATUS.md).

**Current exact checkpoint.** Launcher validation491A10 and registry probe491B70,
plus table sine4BA480, cosine4BA4D0 and sine4096 4BA520, add five regions,
**551 C/C++ body bytes +41 padding**. Current complete launcher6/math9 plans
passed stock checking with no misses; canonical acceptance and a separate fresh
whole-file build passed. Counts: **12,971 regions /946,656 C/C++ body bytes
(25.11% of .text) /105,039 padding**. The4,485,392-byte executable matches target
SHA256 `e6418111c2c36081a1795fb000e0927beea1630170b334c5013d12102602e70f`.
Proof: `build/class-work/Owner/C1Ordinary-29c31b59-v1/landing/VERIFIED.json`.
Full executable recovery and native adaptation remain incomplete.

The launcher source logs and checks the expected message, otherwise probes the
original registry value. Ordinary RegCloseKey(key) preserves Query/status/key,
Close and version-comparison order, with one unique reference-comment block.
The table functions preserve original FP loads/conversions, signed division and
remainder, negative wrapping, odd-index adjustment and last-index clamps. Ordinary
double sample locals emit the original final32-bit table read and no additional
FP store. The old read-specific volatile source forms are superseded and remain
frozen; no invented API effect, dead emitter or manual compiler-helper call.

Independent original checks cover all five complete closed CFGs, fixed padding,
entry CALL witnesses, predecessor/successor intervals, original PE import names
and FP memory widths/constants. CALL windows do not certify complete parents or
all incoming callers. Launcher bool/zero-argument fastcall source conventions and
original developer names remain explicit compatible hypotheses. Probe was not
canonical before this batch: its private cdecl-to-fastcall source change is not
an old canonical identity migration or an added alias. Trig's public float/cdecl
interface is unchanged. Earlier external double/name hypotheses in
unknown_geometry.hpp remain separate debt; no old declaration or used name is
rewritten here. Original tables, constants and string data earn zero source credit.

R1184 captures all602 frozen inputs plus index and the two ordinary-source
packets, superseding older R1113/R997 source. Their actual raw/report/accepted,
command/script, aggregate and COFF chains were replayed. All15 actual functions,
sections and relocations agree with the previous verified ordinary-source output.
All ten existing canonical sources, complete physical/quality/optional fields,
paths, signatures and used references remain fixed; all12956 unselected rows and
ordered maps are verbatim. All313 headers and all layouts/vtables stay fixed.
The current owner stock objects and fresh canonical build are independently
replayed. Two existing A14 zero-credit policies are unchanged; no masks, trims,
new output allowances, helper anchors or acceptance-tool changes.

**Next queue.** C1's separate rendering probe386+14 is captured at
`C1RenderingR1126Intake-29c31b59-v1` (128 frozen inputs plus index). Ordinary
DSurface source is inspected; independent original/API/full-output review and
current whole-unit gates remain. Check for a newer rendering/video-mode packet
before composing the current unit. No repeat credit
for these five551+41, prior buffer176+16, or Building736+16. C2 current Building155
includes reset44E570 at its retained flat path; select its whole membership.
New class deliveries remain the main queue. Reassign only completed classes;
recover locally when no deliverable is ready. Direct worker messages remain
authorized. Preserve frozen inputs and keep source/ABI/foreign-header reviews
separate, including selection/name migrations and offset ownership.

Scope13 at `C2RulesFieldsScope13-5d9681ab-v3` permits only a fresh private Rules
hole split for BuildingTypeClass*+3F0 and signed DWORD+3F8, retaining3F4 and
3FC..433 as reserved bytes and every existing interface/layout. Independent
original proof covers slot126 full2336 (2290 code/738 instructions,2 internal
alignment,44 switch data), primary Building VT126 and canonical447240 boundary.
Pointer/cap meaning remains a hypothesis; zero canonical/source credit. These
fields alone do not guarantee compilability. Slot221 ABI remains a separate
review: two evidence files are captured, with no new prototype scope granted.
C2 reports that Random2 can use the existing header; refresh that report before
assuming a new header or compiler-counter change is needed. No casts through stand-in owners,
duplicate classes, foreign implementations or sparse1057 source cut. Normal
current cumulative/header/full-output/full-build gates still apply.

**Previous checkpoints.** 29c31b59 recovered Building radius, barrel coordinates
and turret frame736+16.5d9681ab recovered buffer transfers176+16. e8ee708e
normalized the existing fence reset with zero new credit. Earlier exact results
and refusals remain in git/private evidence. Expanded outputs are archived locally
only after every member is verified, retaining reports and executable. Existing
SSH mirror verification remains the fallback when SMB is absent. Full recovery
remains incomplete; the owner is paused for handoff.

**Worker controls.** Direct lanes remain C1 unowned480000–4BFFFF, C2 Building,
C3 Aircraft and C4 Unit. Reassign when a class finishes; keep cumulative plans
and best misses. Other lanes stay parked incomplete. Timer704A80/full 32 overlaps
accepted RET704A9F; no trim/removal/credit. Anim by-value remains unproved.

Fresh private scopes give no canonical approval or byte credit. Scope5 permits
only C3's existing Rules+10E0 byte-hole split and own landing declaration.
Scope6-v2 permits only real House4EF600 vector-reference declaration/needed
forward declaration, retaining const/name/caller-entry hypotheses. Its v1 wrong
slot association was refused: Unit slot132 is702F60;6FD930/6FDFC0 are absent from
its313-slot primary table. Scope7 permits only Unit slots310/311 prototypes with
X,Y,16-byte Rect and depth, provisional int return; no slot312/layout/vtable edit.
Scope8 permits only ZBuffer ctor/destructor/region-fill declarations and Height
+2C in fresh blit.hpp. ABuffer and Surface constructor guards remain outside scope.

Scope9 at WorkerPrivateScopes9-48468737-v1 permits only identical nonvirtual
MapClass::Unknown_0054E580(Cell,int) declarations in fresh private map.hpp and
map_view.hpp. Root verified genuine Unit slot86/call6FD178, packed Cell/second
DWORD,119 reachable callee instructions and two RET8/AL1/0 exits. Source types,
names and owner remain hypotheses; no certified Map successor/full-bound claim.
No callee implementation, fields/layout/statics/virtuals/other bodies are approved.
Combined proposals need explicit scope and normal owner merge/full gates.
Scope10 at WorkerPrivateScope10-bcfcd20e-v1 permits only the paired private
Techno base/Building override slot170 declarations with existing UnknownFacingDir
return and Abstract target. Original full 995/376-byte CFGs, RET8, vtables and
Building13NOP-to-VT285 successor are verified; zero canonical uses. Incoming
callers and exact source ABI spellings still require review. No base source,
layout, fields, vtable-count, aliases or availability cleanup is approved.
C1's R820 statistics-helper request is stale:4A97B0/827+5 is already canonical
at Draw_Type_Details_004a97b0.cpp; the worker was told to move on.

C3 may also iterate the owned nonvirtual418F10 private declaration using existing
Abstract types; no Rules1425/Cell/Bullet/foreign fields, slot126 or layout change.
This grants private exploration only, with original bounds/source ABI evidence
still required before canonical adoption.

Scope11 at `BufferStreamsOriginal-59331472-v1` permits C1 private recovery of
BufferStraw::Get773840 and BufferPipe::Put773730 outside its address lane.
Owner independently verified the original RTTI names, primary Straw/Pipe bases,
3/5 vtable slots and both observed 88-byte CFGs with +C/+10/+18 field accesses.
Use existing Straw/Pipe/Buffer types and propose fresh derived-header copies.
1C is a minimum observed prefix, without a certified allocation/class size;
complete boundaries, padding and source ABI still need review before adoption.
No constructor/destructor implementation, reserved display/INI caller source,
dummy emitter or manual compiler-helper call is authorized. The deleting
destructors49ED60/49EDD0 remain pending genuine original emitting units.
This is private scope only, with zero canonical approval or byte credit.

Other C2 Tactical/Techno/BuildingType and C4 Tube/Foot/House requests remain
separate evidence reviews. Retrieve local frozen files and message workers
directly; no outside publication/reverse-owner retry or goal changes.

**Roles.** The owner integrates: canonical manifest, shared headers, build
logic, `STATUS.md`/`HANDOFF.md`, commits. Workers deliver plans plus header
copies from their own folders. Four Codex workers run on the user's Windows PC
(below); no Claude workers are running.

**Tooling since 2026-10-27.** Remote compilation (15066627): set
`RA2_REMOTE_COMPILE='ssh://mike@192.168.4.38/C:/ra2/remote?identity=~/.ssh/mike-gaming&jobs=6'`
(ssh needs the sandbox off; the user approved that for these commands only); a full
build takes ~200 s instead of ~370 s, local Wine is the automatic fallback. Rename
batches (523dd767): workers deliver an `apply_rename.py` spec (mangling_rewrite +
source rewrite rules + header copies), not per-population plans; the owner runs
`apply_rename.py SPEC --dry-run`, then with `--config private/original-target.interactive.json`,
then the full build. It re-verifies only affected units and refuses on any leftover
old name (133-population retype: 99 s). Owner landing helper: private/tools/land.sh.
Pending signature batch: TechnoClass slot 222 first parameter is HouseClass * (codex2
evidence; still declared int, BuildingClass 0x453300 casts). Debt: UnknownPoint2D
(techno_type.hpp stand-in) duplicates Point2D; Tactical 0x6A2900 and BuildingType
MuzzleFlash/DamageFireOffset use it.

**Integration loop (the owner's job, in order).**
1. Take a delivery: plans, drafts and header copies in the worker's folder.
   Confirm LF line endings and that existing regions keep their manifest
   `source`/`semantic_name`.
2. Merge the worker's header copies onto `src/shared` with
   `git merge-file TREE BASE WORKER` (BASE = the header at the commit the
   worker based its round on). Never overwrite a tree header wholesale.
3. Check: `RA2_CONFIG=private/original-target.w3.json
   private/matching-pilot/20261020T123117Z/env/bin/python
   tools/original_target/check_plans.py [--build] NAME HEADER_DIR PLAN...`
   (`--build` whenever shared headers change; it runs the full build in the
   throwaway worktree). Deliverable only when every plan shows accepted ==
   candidates and `"missed": []`.
4. Accept into the tree: copy the merged headers to `src/shared`, then per plan
   `private/matching-pilot/20261020T123117Z/env/bin/python -B
   tools/original_target/accept_sources.py --config
   private/original-target.interactive.json --output
   private/original-target-20261020/accept-NAME PLAN`. Hand-edited accepted
   sources or headers need their hashes refreshed: load and dump the manifest
   with `tools/original_target/catalog_io.py` after updating each region's
   `source_sha256` (and `regenerate_seeds.sync_headers`).
5. `RA2_PYTHON=private/matching-pilot/20261020T123117Z/env/bin/python
   ./build.command` (about 5 minutes; must print `"whole_file_exact": true`
   and SHA `e6418111...e70f`), then `status.py --write`, `source_index.py`,
   this file, commit (accepted source, manifest, docs, tools only; never
   `private/` or `build/`).
6. Sync Windows: `private/tools/sync_windows.sh` (bundles `main` to the
   mirror, copies new inventory passes, regenerates the workers' configs), then
   directly notify all four Codex workers to `git merge --ff-only main`.
   Shared status/deliveries remain the evidence record.
Signature-rename batches (they rewrite manglings in the manifest) land alone:
freeze other acceptance, apply the batch's headers, run its manifest rewrite,
accept its plans, build, commit, and only then integrate anything else.

**Windows Codex workers.** `ssh -i ~/.ssh/mike-gaming mike@192.168.4.38`
(the usual SMB mount `/Volumes/mike-gaming/ra2/` is currently absent; the existing
SSH fallback was used and verified at `cec6c563`). Mirror `C:\ra2\repo`
(fed by git bundle; repo-local `core.autocrlf false`); worktrees
`C:\ra2\w\codex1..4`; coordination `C:\ra2\coordination\ra2-recovery-w1`
(`SESSION.md`, `WORKER.md`, `BOARD.md`, `assignments/`, `status/`,
`messages/`, `deliveries/`; the owner writes assignments, the board and
messages, workers write status and deliveries). Lanes: codex1 unowned
0x480000-0x4BFFFF, codex2 BuildingClass (generation 1; BuildingType/surfaces parked incomplete),
codex3 AircraftClass (generation 1; Wave/Particle parked incomplete), codex4 UnitClass (Infantry parked incomplete). WOL generation 1 is parked
incomplete after R168; its frozen R163 held packet is queued (8 new regions /
1,728 body bytes, including the new 557 counted once). Workers were asked to deliver one cumulative plan per unit
every few hours. On the Mac, `cp`/`mv`/`rm` are interactive aliases that hang
background commands: use `/bin/cp -f` etc.

**Landing queue, in order.**
1. Codex37-plan backlog: complete in00a5f0be,148 new/28,377body.
2. Explicit-only /GR tooling: complete in6e61ae62,101 tests and fresh exact build.
3. Cell/BaseNode rename +House/GR: complete in15fdd70c,223 plans/7,418items,
   one600-byte HouseDetach; separate binder/config repair1aa9a637 has111 tests,
   6,000 ordered-map comparisons and fresh exact build. Both Windows-synced.
4. Objs12 bool returns: complete in811a804a,33 plans/1,838items, zero body credit.
5. Eight Techno additions: complete in1d952a23,whole138-member unit,974body.
6. Facing bool return: complete inf5e00e6c,33 plans/1,846items, zero body credit.
7. Effective V8 held packets: complete in347a3861 at50/745,261 new/60,088body.
8. Six cumulative follow-ons: complete at12/370,23 new/10,425body and fresh exact
   12,868-source executable; current checkpoint above. Do not reaccept them.
9. Fogged25 + Wave38: complete at4/231,seven new/1,795body and fresh exact
   12,875-source executable; current checkpoint above.
10. C1 R388 Factory, C2 R636 BuildingType, C4 UnitR14: complete3/174,
    six new/1094body and fresh exact12,881; R14 supersedes R3.
11. R449 collection, Rect/Aircraft/Unit/Building follow-ons and R470/R698/UnitR75:
    complete at the current exact checkpoint above. Building R725 is now complete;
    Unit R135, Building event R752/refresh R783, DropList R500 and the compatible14-method batch are complete; never repeat earlier packet credit.

12. C1 R656 CStream, SavedMap R676, compatible Building R989 and the isolated
    R991/R950 int-state signature, C3 R284 Aircraft97 and the isolated R990 bib
    signature, co-op player-score provider and current Building extensions are complete.
    C3 R385 Abstract, R394 Cargo and cumulative R410 Radio are complete at the
    59331472 checkpoint. C2 R1101 psychic/INI is complete at the current checkpoint.
    New deliveries and interface requests retain their gates.

13. The isolated47FCC0/51FC60 helper definition cleanup is complete with zero new credit.

14. Building fence traversal and upgrade animation are complete:938 body +22 padding.

15. Existing44E570 reset identity cleanup is complete with zero new credit.

16. BufferStraw Get and BufferPipe Put are complete:176 new body+16 padding; constructors/dtors still pending.

17. Building radius, voxel barrel coordinates and SHP turret frame are complete:736 body+16 padding.

18. Ordinary launcher validation/registry and table trig are complete:551 body+41 padding.

**Parked lanes with resume notes** (each folder's `NOTES.md`): Bldg12
(BuildingClass/BuildingTypeClass; Read_INI 0x459A00 translated at 77.7),
Objs12 (Overlay slot 71, Team AI, House ctor/AI), Objs11 (Wave ctor; Particle/ParticleSystem family now delegated to codex3 g2), Objs10 (Anim, Terrain), Foot11 (FootClass large
members), Unit8 (UnitClass), Objs9 (Bullet). Honest-source refusals to keep:
register-steering casts (BulletClass 0x461C10), hand-written compiler-helper
calls (`__RTDynamicCast`; use `dynamic_cast` under `/GR`).

**Debt.** Two `Adjacent_Cell` forms; stand-in UnitClass/UnitTypeClass in
`foot.hpp`; duplicate `UnknownVector3` in `display.hpp` and
`unknown_vector3.hpp`; repeated `wchar_t` typedef blocks (one shared header
would be cleaner); `UnknownMap8324E0` vs `Map`; a very long
`DynamicVectorClass_DiscreteDistributionClass_...` path (225 characters).

### Codex owner prompt

```text
You are the owner/integrator of the Red Alert 2 exact-match decompilation in
/Users/ivalice/Code/redalert2-native (macOS; the build runs VC6 under Wine).
Read AGENTS.md, then docs/HANDOFF.md ("Owner handoff (2026-10-24)" is your
starting point), docs/ORIGINAL_TARGET_PROCESS.md (workflow, Worker rules,
completion criteria), docs/ORIGINAL_TARGET_BUILD.md and
docs/VC6_MATCHING_NOTES.md. Goal: continue the recovery until the full
executable is recovered, keeping the recovered code clean and organized
(the text in docs/ORIGINAL_TARGET_GOAL.md). Work the landing queue in
HANDOFF.md in order, following its integration loop exactly: check every plan
with tools/original_target/check_plans.py (with --build when shared headers
change), accept with accept_sources.py, run ./build.command and commit only on
an exact whole-file build, then sync the Windows mirror with
private/tools/sync_windows.sh and message the Codex workers through
C:\ra2\coordination\ra2-recovery-w1 (mounted at /Volumes/mike-gaming/ra2/).
Integrate the workers' deliveries continuously, reassign lanes as they finish
(class layers, one cumulative plan per unit), and recover functions yourself
when the queue is empty. Never stage private/ or build/, never weaken
acceptance (no masks, no steering source, no hand-written compiler-helper
calls), use /bin/cp -f, /bin/mv -f and /bin/rm -f, and keep HANDOFF.md current.
```

## Earlier notes (before 2026-10-24; the landing queue above takes precedence)

State: see STATUS.md. Up to six workers (user, 2026-10-21), each with its own
compiler prefix: `private/original-target.{sweep-b,wine,w3,w4,w5,permute}.json`;
the owner uses `interactive`. Recovered class layers: Abstract, AbstractType,
Object, ObjectType, Mission, Radio (Techno pending), GScreen, Map (partial),
plus the utility units (file/stream/surface/mouse/keyboard/movie/MS* etc.),
the header statics of ~360 units and the unit-defined global lists.

Integration flow (the bottleneck): workers deliver plans plus proposed header
copies; when several deliveries touch the same shared headers, one worker
merges them into a single set and writes re-verified `-x`/`-t` plan copies of
every affected plan; the owner installs the set, accepts the plans in
dependency order, runs one full build and commits. `accept_sources.py`
refuses partial replacement of a hand-written unit and plans whose items share
a draft; plans default to `/O2`.

Round 3 (`build/class-work/Merge3/`) is committed. Round 4 is being merged in
`build/class-work/Merge4/`: Building/BuildingType, House, triggers (Tag,
TagType, Trigger, TriggerType, TEvent, TAction), Teams (TaskForce, Script,
TeamType, Team), Super/SuperWeaponType, Side/HouseType regroup, Cell and the
Overlay/Terrain/Smudge classes, Objects2 (BuildingLight, IsoTile, Wave,
Veinhole, EMPulse, LightSource), Gadgets (11 units), locomotors (9 units),
surfaces, Matrix3D, WOL sinks, Unit, Foot, Radar, ParticleSystem, VoxelAnim.
Every plan includes a unit whose header changed, so all need acceptance; a
"re-verified only" plan failed the fresh build audit in round 3.

Unit grouping rule: a unit's `_$E` header-static initializers are the
contiguous block immediately *before* its first member. Two accepted units
break it and are regrouped in round 4: population-571 (Side took Sidebar's
0x67B2C0 statics; its own are 0x67AC40) and population-570 (CCINI took
0x46DDD0; its own are 0x4694C0). `sidebar-plan-s2-y` waits on that.

Debt: names with two spellings — 0x8324E0 (UnknownMap8324E0 /
UnknownScreen8324E0), 0xABFF58 (object vs techno index), 0xA3D290
(UnknownIDSource / scenario view); `unknown_geometry.hpp` must leave
`abstract.hpp` so map.hpp can use the real CellClass; WWKeyboardClass::Down
returns bool (rename); ATL code in WOnline.cpp (~1.5 KB) has no ledger
category yet; inline `::Intersect` and `CCFileClass::Open` defined in drafts;
~5,400 address-named discovery sources remain in Ghidra-seed form.

Audit capabilities added this phase (all in `verify_manifest.py`): verified
COMDAT duplicates (vtables, literals, `??_G`), vtable slots naming
unrecovered virtuals (original slot must be a code address), zero-fill
globals and the empty literal, `.CRT$XC` initializer registrations,
switch tables after a body (`switch_data_bytes`), compiler-local labels,
single-variant class units, replacements claiming the following padding gap.

Workflow per class: header with `// +0xNN` members in `src/shared/`, drafts
with `class_seed.py`, iterate with `diff_candidate.py` (concatenate the unit
and pass `--symbol` when methods inline each other), accept the whole unit in
address order with `accept_sources.py`, full build, commit. Record names in
`manifests/symbols.json`. Rules that made classes match:
`docs/VC6_MATCHING_NOTES.md`.

## Environment

- Python with capstone/pefile: `private/matching-pilot/20261020T123117Z/env/bin/python`
  (set `RA2_PYTHON` for `build.command`/`test.command`).
- Canonical working copy: `/Users/ivalice/Code/redalert2-native` on the
  internal SSD. Current owner commands use that absolute path.
