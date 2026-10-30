# Handoff — original-target decompilation

Current state only (2026-10-28). Numbers: [STATUS.md](STATUS.md). Workflow:
[process](ORIGINAL_TARGET_PROCESS.md). Commands: [build](ORIGINAL_TARGET_BUILD.md). Matching rules:
[VC6 notes](VC6_MATCHING_NOTES.md). Open misses and debt: [OPEN_MISSES.md](OPEN_MISSES.md).
Earlier owner periods are in [history/](history/).

## Owner, lanes and pacing

Claude (Mac) owns integration; a Codex session on the Mac may take over as standby owner using this
file, BOARD.md on Windows and git. Usage rules (2026-10-28 review, Pro plan):
- At most four Mac lanes. Each lane gets one class unit or family sharing one recovered layout (one lane per
  large sibling family when a class exceeds a few KB), runs the whole unit, delivers every 1-3 KB, and the next
  unit gets a fresh lane (brief: `build/class-work/LANE_BRIEF.md`, "Scope and budget"). Revised 2026-10-28:
  one-function lanes landed 300-900 B each at about 3x the tokens per KB of unit-sized lanes.
- Stop a lane past about 150 output tokens per landed byte or after two zero-byte handbacks;
  record its best score and draft in its NOTES.
- Near misses in a unit belong to whoever holds the unit (BOARD.md); Windows workers hold units like Mac lanes.
- Opus for class lanes with recovered layouts; Sonnet for mechanical loops.
- Lanes hand back at about 200 tool calls or 200K context, whichever first; the owner continues the unit in a
  fresh lane from NOTES. Mac lanes are at zero (user, 2026-10-30): the owner only lands Windows deliveries (a Monitor on deliveries/ wakes it; re-arm every 30 min), keeps assignments/BOARD current and steers codex1-4; no new Mac lanes; when the Claude week runs out, hand over to the
  Codex standby owner (commit, HANDOFF refresh, board message, one owner at a time).

Ghidra pass 6 trial (2026-10-30, review-session request): build/pass6-trial/REPORT.md. ApplyKnowledge.java (tracked, landed in f2f511a3 with codex2 r2753) applied 9,190 accepted signatures and flat HouseClass/BuildingClass layouts to a pass5 copy; 20-function seed scores flat on average (6 up, 4 down, mean -0.1; 0x4E8990 27.5->43.7), readability much better (named fields, typed callees). User approved both (2026-10-30 midday): reference pass 6a EXISTS at inventory/seeded-pass6a (pass5 + 9,194 demangled accepted signatures, no re-analysis, 19,140 decompiles; read-only, seeds still use pass5; LANE_BRIEF and WORKER.md tell workers to read it; recipe in ORIGINAL_TARGET_BUILD.md). Pass 6b (layouts in seeds) is queued for codex4 after its House chain: seed_candidate must compile typed seeds against real shared headers (assignments/codex4-next.md, trial material in owner-reference/pass6-trial); Pass 6b DONE 2026-10-30: codex4's typed-seed tooling landed (e9d80f58, r21); inventory/seeded-pass6b holds 324 typed member functions (97 flat layouts rendered by build/pass6b/render_layouts.py from clang's MSVC layouts, sizes verified; members = unique vtable slots + pass5 __thiscall functions inside one class's accepted span). Select it with RA2_INVENTORY_PASSES. Sweep on 314 entries: typed 109 compiled / 2 byte-exact (0x73A090, 0x765AC0 -> codex2) / mean 31.0 vs pass5 262 / 0 / 29.7. codex4's seed tooling is capped (user, 2026-10-30): its r24 (landed) already carried the pass5 fallback and a typed compile-rate repair (109->153 of 314 compile); no further seed-tool work, House.CPP bytes. Raising the typed compile rate (typed-compile-regressions.txt, 154 entries) is backlog for any worker between units, no owner time. No Mac lanes running (last: Foot305, Hdr306). Landed 2026-10-30: Hdr306 (audit now names the refused row and first differing offset; 0x549C50 Sight_From 1,208 B; type-count rule in VC6_MATCHING_NOTES), Foot305 r2 (3,657 B with the 0x4CB110 bool rename), Map303 r1 (2,219 B), Foot304 r3 (5,255 B, slots 78/93, 0x4CCA40), Foot302 r2 (1,432 B, slots 54/77), Map298 r5 (10,138 B + 0x54F7C0 bool rename), Cell301 r1 (1,403 B + Init_Drawer rename), Tactical300 r1 (1,071 B; owner dropped its file-local Point2D operator+, now a rect.hpp member). Next lane candidates: Tactical rest (Tactical300 NOTES), Cell rest (Cell301 NOTES), Techno.CPP, TeamClass, Sidebar. Terrain160 landed
slots 86/67 (TerrainClass complete but two near misses); Types161 landed UnitTypeClass slot 32 0x70A9D0;
Anim162 zero bytes (AnimClass ctor 95.68); Left163
landed Smudge slot 71 0x687750; Team159 landed 11 TeamClass functions (6.6 KB) with the
Remove/Coordinate_Regroup rename; House164 landed Suggested_New_Team 0x4E5CF0 and 0x4EF6F0 (AI at 99.32);
Team165 landed 7 more TeamClass functions (4.3 KB) with the Fire_Sw Cell const & rename;
Queue166 landed 19 Queue.CPP/Event functions (3.5 KB) with the EventClass byte-type rename;
Techno167 landed TechnoClass Unlimbo 0x6C4610 and What_Action 0x6CC5D0; Conquer169 landed
Special_Dialog 0x481850; Queue168 landed 8 Queue.CPP functions (4.7 KB); TAction172
landed 12 trigger actions (CDTimerClass::Value now tests Started unsigned, as FTIMER.H); Init174 landed 29 Init.CPP
functions (19 CommandClass Execute slots, 3.6 KB); Session173 landed
9 Session.CPP functions (2.3 KB) with a rename; Scenario177 landed Set_Defaults 0x65B830;
Null175 landed 17 null-modem functions (11.3 KB); House171 landed 14
House.CPP functions (4.1 KB) with the Flag_To_Win/Lose rename; Init176 landed 7 Init.CPP
functions (3.4 KB) with the variadic 0x496460 rename; CampScor180 landed
12 CampScor.cpp functions (3.8 KB; unit complete but two near misses); Netshare179 landed
40 netshare.cpp functions (6.4 KB); Init181 landed 6 Init.CPP functions (4.6 KB); Modem182 landed 41 ModemHst.cpp functions (4.4 KB, new ModemHost layout); PlanMgr178 landed 12 PlanMgr.cpp functions (1.9 KB); Netshare183 landed 21 netshare.cpp functions (4.9 KB) and took over population-292's initializers; Netdlg184 landed 17 netdlg2.cpp functions (6.1 KB) with the Set_Bridge rename; PlanMgr186 landed Planning_Copy_Members 0x6167F0 and stopped on the token rule (PlanMgr.cpp parked: inline-split misses, see OPEN_MISSES); Modem185 landed ModemGst.cpp (ModemGuest, 8.1 KB) and ModemHost Process_Messages/Send_Preview (2.3 KB); Netshare187 landed 4 netshare.cpp functions (2.4 KB) with the Select_Scenario bool rename; Netdlg188 landed 3 netdlg2.cpp functions (3.4 KB); WDTSel189 landed 11 WDTSel.cpp functions (1.9 KB, Selection layout); Modem190 landed 6 ModemHst.cpp functions (6.6 KB; ModemRegistryEntryClass); Lobby191 landed the lobby return-type rename and Random_Map_CRC (lobby/modem near misses are register ties: Windows queue). Owner fixed three Winsock/UDP sources that named SendMessageA's import PostMessageA (cc317643). RcPtr192 solved the rc_ptr chain (empty null test in operator->) and landed 11 WDTSel.cpp functions (2.6 KB). House193 landed 8 House.CPP functions (4.1 KB); Is_Ally(TechnoClass) now calls Is_Ally(house), which gives callers the original's materialised bool. WDTSel196 landed the Selection dtor, Choose_Territory and Choose_Conflict (2.1 KB); its r3 Hover form `true ? call : rc_ptr()` was refused as steering. Ion195 finished Ion.cpp (16 functions, 6.3 KB) with the Set_Tint virtual / 0x49E5E0 member rename; its three static-list atexit dtors (264 B) need the seed objects and DynamicVectorClass<AnimClass*> rows taken over. (Sonnet lanes 199-205 ran under a pacing rule the user withdrew; new lanes are Opus.) Session194 landed 17 Session.CPP functions (3.0 KB) with a rename; MultiMission::GameModes is a DynamicVectorClass<Wstring> (units including multi_mission.hpp bind ??_EWstring). House197 landed Recalc_Center 0x4E8640 (house ZoneInfo[5]); acceptance now treats VC6's lea ecx,[ecx] / lea esp,[esp] fills before a jump table as alignment (00e3ce18), which unblocks Zone_Cell 0x4EAF30. UICmnds199 (Sonnet) landed 7 UICmnds.cpp list/selection helpers (1.4 KB). WDTSel198 landed Load_Layout 0x72DEA0; Session200 landed the MultiMission ctor 0x671C50 with its VectorClass<Wstring> ctor and DVC<Wstring> ??_G (971 B); Queue220 zero landed bytes (sync-file writer 0x62DBA0, 2417 B, exact but refused on a bound string literal); Skirmish222 zero bytes (Skirmish_Message_497 0x683FC0 97.43, Skirmish_Command 0x6829F0 78.89); Init219 landed the campaign choice dialog 0x5147A0 (1.8 KB); Small217 landed GOptions.CPP (970 B) and SendFile.CPP (791 B); Small218 landed LdPrgMgr.cpp (958 B) and WorldDom.cpp (789 B); Scenario216 landed the SerialEdDialog unit (SerialEd.cpp, 4.2 KB; unit is 0x66CA70-0x66E093; Scenario.CPP left as register/structural misses); Session214 moved UnknownSessionState into session_state.hpp (only session users include it; no unit renumbered) and landed the session destructor 0x66EB20; Session.CPP parked (ctors 98.59/87.47 past time box). TAction215 zero bytes (TAction.CPP parked: Execute 0x6ADAE0 69.14 is an /Ob2 budget puzzle); House212 landed three small House.CPP functions (235 B; House.CPP parked: AI_Building 99.42 and AI_Raise_Money 87.22 are store-order/loop-hoist misses); NullDlg213 landed Modem_Signoff (NullMgr.CPP complete; NullDlg.CPP left only Select_Serial_Dialog, a register-allocation miss); TAction211 landed 20 trigger actions (4.1 KB); UICmnds210 landed the 0x6F6C90 retype rename and list rebuild 0x6F79C0 (UICmnds.cpp parked: remaining misses are cross-function inline-budget puzzles); House208 landed AI_Unit/AI_Infantry/AI_Aircraft (2.9 KB); MainOpt207 landed Set_Display_Mode 0x5434E0 (1.4 KB); UICmnds206 landed 3 UICmnds.cpp commands (2.0 KB) and found the waiting-site rule; House204 landed 0x4F02E0 and 0x4E76A0 (463 B) with a rename; MainOpt203 landed 6 MainOpt.cpp and 5 LoadDlg.CPP functions (2.1 KB); House201 landed Zone_Cell 0x4EAF30 (828 B; the original orders the zone cases 1, 2, 4, 3); WDTSel.cpp parked (ctor needs 3+ more pending inline sites the source does not show, Show_State's cursor ctor goes out of line in the original). Windows lead: r59-r61 landed (imports.json fix 248a9174, MapRegion 0x5831C0/0x583450); codex2 approved for the TunnelLocomotion state family (2026-10-30T0100Z); r55-r58 landed (seed tools r23-r24 08c4416d, 0x56E970 provider rename af5c87ac, ModemGuest Start_Game 628d68cb); r46-r54 landed (seed tools r19-r22 b1891b98, sources 0f0028b8, user-approved map-generator rename 4b74187b); owner approved codex2 MessageList Add/Concat and the 0x56E970 cell-region provider rename (messages/2026-10-29T1500Z); earlier r43-r45 (858ffa6d); codex2 approved for the three ScoreFontClass methods;
the user approved the map-generator 0xA6FD68/A0 ownership rename (lead delivers it alone, rebased on main). Lanes read docs/WESTWOOD_SOURCES.md before drafting library members. Debt154 merged the two 0x4F52B0 names
(b24cc60c). Inf148 (InfantryClass) parked, zero bytes.
Landed this evening: Modem141, Base142 (Base unit complete), Ref143 (Release 0x639720, CampaignProperties and
Territory ctors), Score144 (CampaignScoreClass ctor 0x465BF0), VoxAnim145 (VoxelAnimClass::AI 0x70D380), Air146
(AircraftClass slot 147 0x415210), BLight150 (~BuildingLightClass 0x4332F0), Unit149
(MapClass 0x5502E0 Point2D rename; UnitClass slot 87 0x7072D0), Bullet151 (detonation 0x462110, NukeMaker
payload 0x463C50), Unit147 (MCV deploy search 0x6FD930 and two unit statics), Unit153
(slot 86 0x6FCA30, BuildingTypeClass 0x45EC50 bool, deploy attempt 0x6FDFC0), Study152 (inline rule now in
VC6_MATCHING_NOTES; WDT Map ctor 0x729330), Inline156 (MSPrintAnim::Draw 0x5AF030), Unit155 (slot 310-312 and
0x6D1510/slot 293 Point2D renames; slot 312 0x6FF3E0), MSAnim157 (20 MSAnim-unit functions, 5.1 KB;
MSFadeAnim Anims rename), Study158 (wwlib inline_depth/WWINLINE: neither explains any case; VC6 notes). Landed: Light137 Set_Tint 0x538AA0, Light140 ~LightConvertClass 0x538F20, Modem138
0x734CD0/0x735110. WDT136 (Campaign ctor 0x725F40) and Sink139 (OnLadderList 0x75D330) are misses in OPEN_MISSES.md.
Landed 2026-10-28 evening: Map129, Obj126, Para131, Iso128, MSAnim133, Score132, IPX135 (Send_To), Base134
(BaseClass ctor/Load/NoInit ctor). Near misses (OPEN_MISSES.md) go to the Windows lead; queue and drafts sent in
messages/2026-10-29T0130Z-owner-to-lead-backlog.md and owner-reference/. Lanes use lane_tools.py.
Windows lead backlog r17-r42 landed (last 5626377a). Lead plans built on old bases are refused by allow_split when
their population has grown: rebuild on the HEAD population keeping only the plan's new rows (owner scratch script
reheadpop.py pattern: lane_tools.build_plan + the plan's unaccepted rows and top-level keys), and drop helper
copies the unit now defines. Missing worker drafts come over ssh tar from C:/ra2/w/codexN (copy only the folders
a plan names: codex2's d/ is about 30 GB). Bounds rounds (r18, r26, r28, r31, r35, r39) are evidence only. Closed 2026-10-28 (resume folders `build/class-work/<Lane>/`): Seed118 (callee-pops
`lea` rule; Speech_Load, Voc_Static_Load), Seed119 (Speech_Update), Coop120 (MessageListClass::Input), Cd121
(0x715230), Cd124 (0x715300), Coop122 (fill combo 0x5B70B0, fill list 0x5B71E0; 0x5B8490 open), Seed123 and
Seed125 (zero bytes; Tactical family parked; 0x6AAFD0 is a register-tie near miss for Windows). Their misses
are in OPEN_MISSES.md.
Next-lane candidates (2026-10-30; fresh map build/class-work/Survey251/UNITS.md: unclassified tail 0x775B60-0x781FF0 (triage first), VQAClass 0x717CE0, 0x426E70-0x42BCF0, Ini.CPP, Beacon span, VeinholeMonster, Score.CPP, UndoInfo, Unit.CPP; unit table build/class-work/Survey170/UNITS.md): WorldDom.cpp rest (OPEN_MISSES), LdPrgMgr 0x535BF0 (4 KB), MainLoop 0x540C20 (3.5 KB).
Parked (OPEN_MISSES has resume points): com_ptr comip model (ComPtr297/299, two zero-byte lanes), netshare.cpp (Netshare247),  Startup.CPP WinMain (Startup232; needs SEH acceptance support: __except_handler3 0x7852D4, fs:[0] __except_list, per-compile $T scope table at 0x7AB990 - the only game-code SEH user), UICmnds.cpp, WDTSel.cpp, PlanMgr.cpp, TAction.CPP, Session.CPP,
Skirmish.cpp, NullDlg Select_Serial_Dialog. Pending landings: none (Mac lanes deliver on hand-back; Windows last r65).

Windows (user decision 2026-10-30, relayed by the review session): no lead layer. LEAD.md and LEAD2.md are withdrawn;
lead 1 was told to finish or freeze its in-flight delivery and stop (messages/2026-10-30T1900Z). Four individual Codex
workers codex1-4 work under WORKER.md (the Mac lane brief adapted for Windows), one unit each, reserved on BOARD.md:
codex1 pathfinding + map generation 0x570000-0x58FFFF; codex2 wonline.cpp (from 2026-10-31; Queue.CPP closed: plateaus); codex3 UnitClass (from 2026-10-31; BuildingClass parked at plateaus, misses in codex3 NOTES; holds map_view/map/foot/ObjectType headers for Plan_Route/Assign_Destination since R189, then InfantryClass); codex4 House.CPP (seed tooling capped at the pass5 fallback). codex5/6 unused. Two workers run on
Astra and two on Sol with identical briefs. Westwood reference clones for them are at C:\ra2\reference\ (copied without .git). TibSun reconstruction (OpenTS-Developers/TibSun dbfbfbf, code/ only; user-approved 2026-10-30) is cloned at private/reference/TibSun and C:\ra2\reference\TibSun: first place to look for a unit's names and shape (docs/WESTWOOD_SOURCES.md cautions). Optional readability follow-up when a lane next touches HouseClass: rename unknown_ members from TibSun house.h (unknown_142 FirestormDefenseActivated, unknown_18d IsBuiltSomething, unknown_144 IsRecalcNeeded, unknown_1bc JustBuiltUnit, unknown_54a0..54d0 PB/PU/PI/PAQuantity; BuildingClass::unknown_450950 Update_FS_Wall_State; Map 0x54EBD0 Zone_Reset, 0x5688A0 Recalc_Cells_In_List). 2026-10-30 20:24: the shared C:\ra2\repo\private\compiler and private\original-target-20261020 were emptied by a recursive delete through junctions (most likely the removal of the lead worktree C:\Users\Mike\.codex\worktrees\ra2-seed-lead, whose private folders were junctions; check trees under C:\ra2\c have the same junctions). Restored from the Mac (game.exe hash verified, 2719 inventory passes). Lead r66 (map reset 0x57BEA0, 545 B) was lost with that worktree, and so were the codex1, codex2 and codex4 scratch folders (codex3's survived); codex2-r2728 (Mono rename) is void and is being redone. Never delete a Windows worktree or check tree recursively without removing its junctions first. Deliveries arrive as deliveries/codexN-rN.md pointing at a frozen
build\class-work\codexN\d\rN (BASE, README with body bytes, shared/, plans, unit/); land them with land_round.sh
after rewriting the C:/ prefix, as for lead packets. The owner keeps assignments/codexN-next.md current for hand-backs; WORKER.md (2026-10-31) makes workers merge main and re-read messages/assignments before every delivery (codex4 kept delivering on BASE d5134dff because the brief never said to read messages). codex4's rebased r10 and ctor r11 landed (9020f4bf); r4/r6-r9 are void.
First line for each new Codex thread (N = 1..4):
`Read C:\ra2\coordination\ra2-recovery-w1\WORKER.md, you are codexN, and start assignments\codexN-next.md.`
Bytes landed per worker per day (first two days; body bytes from each delivery README):
| Date | codex1 | codex2 | codex3 | codex4 |
| --- | ---: | ---: | ---: | ---: |
| 2026-10-30 | 2,845 | 0 (Mono rename+takeover) | 11,110 | 780 |
| 2026-10-31 | 9,706 | 0 | 2,978 | 0 (r5 rename; r4 refused, r6 waits on r4) |
| 2026-10-31 (later) | 2,577 (r242, r249) | 6,051 (r2732-r2740 + r2733 fastcall rename) | 4,329 (r185, supersedes r182-r184) | 6,805 (r10 rebase + r11 ctor) |
| 2026-10-31 (evening) | 758 (r269; r266 rename, r279 header types) | 7,532 (r2741-r2745) | 629 (r186) | 3,028 (r12-r15; r16 rename) |
| 2026-10-31 (night) | 5,715 (r287-r334; r312, r324, r329 renames) | 18,359 (r2746-r2761) | 3,897 (r187, r188 UnitClass; r189 misses only) | 3,274 (r17, r19, r20; r18 IndexClass header) |
| 2026-11-01 | 3,580 (r343, r345, r347, r353; r339 rename) | 2,708 (r2763-r2765) | 299 (r191; r190 retype) | 2,999 (r22, r23; r24 seed tools: typed compile 109->153 of 314, pass5 fallback) |
BOARD.md is the lane authority. MPGameMode.cpp and MPCoop.cpp compile as one unit (population-2861),
so MPCooperative functions that call a base body need separate units.

## Integration loop

1. Take a delivery: frozen `d/rN/` folder with plans, drafts, header copies,
   base commit. Plans use forward-slash paths and LF endings.
2. `private/tools/land_round.sh DIR "message" PLAN...` merges DIR/shared against DIR/BASE (a header
   new at BASE that already landed is replaced only by a superset copy), reheads, accepts and lands;
   `private/tools/land_rename.sh SPEC "message"` applies a rename alone and lands. On a header
   conflict, resolve by hand and rerun with SKIP_HEADERS=1. Frozen whole-population plans carry context drafts from their base commit; when later landings
   rewrote those sources, `private/tools/rehead_plan.py PLAN` writes PLAN.head.json with unchanged
   context rows re-pointed at HEAD sources (drafts that rewrite a source are kept; missing population
   rows are added; Windows `C:/` prefixes are stripped). Accept the .head.json.
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
