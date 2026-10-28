# Handoff — original-target decompilation

Current state only; rewritten 2026-10-28. Numbers: [STATUS.md](STATUS.md).
Workflow: [process](ORIGINAL_TARGET_PROCESS.md). Commands:
[build](ORIGINAL_TARGET_BUILD.md). Matching rules: [VC6 notes](VC6_MATCHING_NOTES.md).
Earlier owner periods: [history/HANDOFF_CODEX_OWNER_20261024.md](history/HANDOFF_CODEX_OWNER_20261024.md),
[history/CLAUDE_HANDOFF_20261026.md](history/CLAUDE_HANDOFF_20261026.md).

## Owner and lanes

Claude (Mac) owns integration. Mac lanes (Opus, at most four at once; the Mac
has 16 GB): Seed70 (seed sweep 100-1500 B below 0x680000), Seed76 (the same sweep
from 0x680000), Surf77 (DSurface
Draw_Shaded_Line and slots 13-16), Big75 (1-4 KB functions, controlled-study method). Windows: one Codex lead
(LEAD.md in the coordination folder) staffing codex1 (Sol) pathfinding
0x570000-0x58FFFF, codex2 (Sol) BuildingClass, codex3 (Terra) bound evidence;
the lead itself owns seed tooling and sweeps. BOARD.md is the lane authority.
Each lane's resume notes are in `build/class-work/<Lane>/NOTES*` (ignored).

## Integration loop

1. Take a delivery: frozen `d/rN/` folder with plans, drafts, header copies,
   base commit. Plans use forward-slash paths and LF endings.
2. Frozen whole-population plans carry context drafts from their base commit; when later landings
   rewrote those sources, `private/tools/rehead_plan.py PLAN` writes PLAN.head.json with unchanged
   context rows re-pointed at HEAD sources (drafts that rewrite a source are kept; missing population
   rows are added; Windows `C:/` prefixes are stripped). Accept the .head.json.
   `private/tools/land_round.sh DIR "message" PLAN...` does header merge, rehead, accept and land.
3. Merge header copies with `git merge-file src/shared/H BASE COPY` (BASE = the
   header at the worker's base commit). New headers are copied.
4. Accept each plan: `$RA2_PYTHON -B tools/original_target/accept_sources.py
   --config private/original-target.interactive.json --output
   private/original-target-20261020/accept-NAME PLAN` (accepted == candidates).
5. Land with `private/tools/land.sh "message"`: rehash, full build, commit only
   if `"whole_file_exact": true`, sync Windows, publish the GitHub snapshot,
   prune old build outputs.
6. Signature/name changes land alone through
   `tools/original_target/apply_rename.py SPEC --dry-run`, then with
   `--config private/original-target.interactive.json`, then `land.sh`.

Cadence: build after every accept (a land takes about a minute: tests, full
build, status and source index, commit, sync, publish), so a header change that
breaks another unit is isolated at once; rename batches land alone. Remote
compilation is configured by `RA2_REMOTE_COMPILE` (value in the owner's private
notes) (ssh needs the sandbox off; the user approved that for remote-compile
commands only). A worker check without `--build` can miss header impact on
other units; the full build is the gate.

## Time box and targets

Per function: about 30 minutes per KB of body, capped at four hours; record a
plateau with its best score and draft, then move on. A repeat delivery with no
new bytes is not a delivery. 489 unrecovered functions over 1 KB hold about
1 MB; big functions are worked with the controlled-study method (lab
experiments that yield a rule, then the rule applied), as in the VC6 notes.

## Open debt and resumable misses

- Map.cpp Cell tables (0x5441E0, 0x5461A0, 0x55B520, 0x55CBC0, 0x56B330, ~15.7 KB):
  exact with `Cell(short, short) { Set(x, y); }`; TechFoot39 is finishing the
  0x54AB00 and Overlay Read_INI 0x5DB670 refits.
- CounterClass: HouseClass::~HouseClass calls 0x491C20, which is accepted as the
  `template class VectorClass<int>` destructor; an out-of-line ~CounterClass matches House
  but makes the VectorClass<int> unit emit an extra destructor (Clean45 spec/counter2.json).
- Duplicates left (Clean45 d/globals/README.md): unknown_a40d13 vs unknown_flag_a40d13 (same
  bool), class-typed globals declared in several headers (MainWindow, Houses, Infantry,
  TeamTypes, IsoTileTypes, ...), unknown_object_index_abff58 typed UnknownIndexClass in
  building.hpp but IndexClass elsewhere.
- RulesClass Sides 0x64BC10 needs DynamicVectorClass::ID with `Count()`, which makes
  142 explicit-instantiation units emit an unaccounted Count COMDAT.
- Display chain parked on register tie-breaks (Disp52 NOTES): RTacticalClass::Action 0x62FE30
  97.18, DisplayClass slot 48 0x49BB20 78.29 (needs a slot 46/48 + 0x6D8F60 rename and header
  moves listed there), 0x4991D0 49.4.
- Write_Scenario_INI 0x65F980 uses an inline accessor on PreviewClass (YRpp name; its member is
  `DSurface *ImageSurface`); no plain member form comes close (21-43), so the accessor stays as an
  inline split (AGENTS.md lists inline splits as normal iteration).
- Near misses of 96 or more, ranked with drafts and the remaining difference:
  `build/class-work/Close64/queue.md` (Close64 closed only Sidebar Draw_It; the rest are
  register/scheduling tie-breaks, negative results in its FINDINGS.md). Bound fixes found there:
  Clear_Scenario 0x65D370 body 1140, WideString Trim_Trailing 0x770230 body 246 (inventory 103).
  RulesClass::Process 0x6433A0 returns void (rename pending; HEAD says bool).
- UnitClass (Unit62 NOTES): Read_INI 0x706AE0 99.44, death 0x6FD3A0 99.33, damage 98.08;
  the 0x704A80 leaf replacement is approved.
- Units60 (NOTES): progress Draw_Player 0x61FC20 41.06 (the original keeps Draw_Name out of
  line), Shape/Flag/Text_Offset ~89.9, WinModem Read_From_Serial_Port 0x734B30 77.97,
  Wait_For_Serial_Write 71.07; Get_Modem_Result 0x734CD0 and 0x735110 not drafted.
- InfantryClass (Inf65 NOTES): 0x507170 99.37, 0x504BC0 98.41, 0x4FFB70 82.95; FootClass slot 54
  0x4C8220 86.96. Uncovered template members: DynamicVectorClass<PlanningNodeClass*> Delete
  0x61B350/0x61B390, DynamicVectorClass<TechnoTypeClass*>::Delete 0x6DFA70.
- ObjectClass leaves (Leaf67 NOTES): Bullet Draw 0x4610D0 98.91, Terrain slot67 0x6E3990 95.56,
  slot63 88.79, Overlay Write_INI 0x5DBA30 86.91, Veinhole 0x711E60 86.51 / 0x711D20 85.71,
  VoxelAnim ctor 85.64; BuildingLight slot67 0x433380 and AI 0x433970 have short inventory bounds.
- Handwritten assembly (not C; ledger category): XSurface::Fill_Rect(clip, rect, color) 0x7743C0,
  BlitTrans<uchar>::BlitForward 0x775980 (Surf66).
- Promo69 (NOTES) closed the recorded-exact list; still blocked: Audio_Stream_Open 0x407A90 99.69
  (64-bit max compare jb/ja order), Planning_Close_Loop 0x6164E0 98.46, MSEngine slots 4/5,
  VectorClass ctor 0x727040 (needs the WDTState ctor 0x725F40 emitted).
- Plans with `separate_units` are accepted with a local compile (`private/tools/accept.sh` does
  this): remote compilation does not stage their out-of-tree draft paths.
- TechnoClass/FootClass (Foot68 NOTES): ctor 0x6C0CD0 99.66, 0x6C16F0 97.41, slot 220 0x6C9AF0
  97.65, 0x6C5270 96.38, slot 234 0x6C89C0 90.31 (int -> void with BuildingClass 0x44FB50),
  Foot slot 77 0x4C69F0 65.32 (body 1312 with jump and byte tables).
- Coord stand-ins (Study72 FINDINGS): UnknownVector3 0x41B630 is CoordStruct(int,int,int);
  CoordStruct::Set_00434820 is the UnknownCoord434820 forwarding constructor.
- Surfaces (Surf71 NOTES): Plot_Line 0x773F00 99.44, Draw_Ellipse 22.71 (decoded), DSurface slots
  13-16 (~14 KB) not started; Intersect lives in rect_intersect.hpp because xsurface.cpp must not
  see it (Draw_Line 0x773980 calls 0x41FDF0).
- Debt73 NOTES: slot 234 0x6C89C0 89.83 (budget), Clear_Scenario 94.63, Coord stand-in renames
  blocked until the Aircraft/BuildingLight callers that keep them out of line are recovered.
- Windows lead: r1-r16 landed (last e3e64c00, tools 728474f6); Factory/House declarations and the
  Leaf_4ea7f0 rename approved 2026-10-28 for the Building 0x44B480 caller plan.
- techno.hpp's UnknownTechno238 stand-in still declares SpawnManagerClass members 0x689B70,
  0x68A560, 0x68A4B0, 0x68A680 under other names (fold into SpawnManagerClass with a rename);
  SpawnManagerClass::AI 0x689C90 (2008 B) not drafted.
- Tiny74 NOTES: guarded class-static lists (88 B atexits) renumber other units' `_$E` symbols when
  the static is declared in a shared header (convert.hpp); the Map global 0x40D060 needs MouseClass's
  ctor out of line and dtor inline; Mark_All_Occupation_Bits (Mech/Teleport/Walk) 92.00.
- Best misses by lane: WarheadType Read_INI 0x7204E0 99.80, Sidebar Draw_It
  0x67CF80 99.43, TechnoType Load 0x6DE260 98.19 (cached-zero register),
  command registration 0x5173C0 76.7 (holds 47 destructors).
- The catalog is sharded per population under `manifests/original_target/` (index.json +
  populations/); load and write it only through `tools/original_target/catalog_io.py`.

## Environment

- Python with capstone/pefile: `private/matching-pilot/20261020T123117Z/env/bin/python`
  (`RA2_PYTHON` for `build.command`/`test.command`).
- Working copy `/Users/ivalice/Code/redalert2-native`. On the Mac `cp`/`mv`/`rm`
  are interactive aliases: use `/bin/cp -f` etc.; zsh noclobber is on (`>|`).
- Windows PC: host, key and mount are in the owner's private notes and
  `private/tools/sync_windows.sh`. Mirror `C:\ra2\repo`, worktrees `C:\ra2\w\codex1..4`,
  remote-compile jobs `C:\ra2\remote`. Windows full builds work with LLVM's
  clang as the scaffold assembler (`assembler` in the worker configs).
- Cold storage and the private GitHub snapshot: `private/tools/move_cold.sh`,
  `private/tools/publish_github.sh`.
