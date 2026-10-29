# Open misses and debt

Resumable near misses, plateaus and type/name debt, with the lane folder (`build/class-work/<Lane>/`, ignored) that holds the draft. Moved out of HANDOFF.md 2026-10-28; edit freely as items close.

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
  VectorClass ctor 0x727040 (needs the WorldDominationTour::Campaign ctor 0x725F40 emitted).
- TechnoClass/FootClass (Foot68 NOTES): ctor 0x6C0CD0 99.66, 0x6C16F0 97.41, slot 220 0x6C9AF0
  97.65, 0x6C5270 96.38, slot 234 0x6C89C0 90.31 (int -> void with BuildingClass 0x44FB50),
  Foot slot 77 0x4C69F0 65.32 (body 1312 with jump and byte tables).
- Coord stand-ins (Study72 FINDINGS): UnknownVector3 0x41B630 is CoordStruct(int,int,int);
  CoordStruct::Set_00434820 is the UnknownCoord434820 forwarding constructor.
- Surfaces (Surf71, Surf77 NOTES; parked on register tie-breaks): Plot_Line 0x773F00 99.44,
  Draw_Shaded_Line 0x4AE9C0 66.71, slot 16 0x4ADE00 67.11 (fully decoded), slots 13-15 share its
  skeleton, Draw_Ellipse 22.71; Intersect lives in rect_intersect.hpp because xsurface.cpp must not
  see it (Draw_Line 0x773980 calls 0x41FDF0).
- Debt73 NOTES: slot 234 0x6C89C0 89.83 (budget), Clear_Scenario 94.63, Coord stand-in renames
  blocked until the Aircraft/BuildingLight callers that keep them out of line are recovered.
- Tiny74 NOTES: guarded class-static lists (88 B atexits) renumber other units' `_$E` symbols when
  the static is declared in a shared header (convert.hpp); the Map global 0x40D060 needs MouseClass's
  ctor out of line and dtor inline; Mark_All_Occupation_Bits (Mech/Teleport/Walk) 92.00.
- Big75 plateaus (NOTES): Set_Video_Mode 0x5434E0 93.32 (Set_Cursor zero stores), Allocate_Surfaces
  0x519500 68.2, TeamClass 0x6BA1A0 78.32, OwnerDraw 0x5DEFB0 66.4; Create_Units' callee 0x660B60 32.
- Seed76/Seed78 NOTES: WorldDom Faction_Name 0x7685A0 needs its four atexit thunks
  (0x768690-0x7686CF) as inventory rows; Temporal 0x6E2500/0x6E2610 need BuildingClass 0x44D380;
  misses Skirmish_Dialog 0x683BF0 98.72, RadBeam Start_Pass 0x635BA0 98.15, RadSite 0x637A80/0x637DC0
  ~96.9 (stack slot swap), LineTrail ctor 94.55. Guarded static lists live in holder structs in
  headers only their unit includes (a shared-header static renumbers other units' `_$E`).
- MapClass 0x55CEF0-0x562450 (Big86 NOTES/FINDINGS): 0x55DEF0 78.69 and its X/Y twin 0x55E410 76.67;
  two operator+ Cell constructors stay out of line on budget, and `else return changed;` folds to a
  constant where the original reloads the local. The other 11 family members wait for that rule.
- Plans can retire accepted regions they fully cover (`"retire": ["004d0020"]`, Tools91; used
  for 0x4CFFB0). 0xA3FA98 has two names (unknown_lobby_slots_a3fa98, unknown_player_slots_a3fa98).
  UICmnds 0x6F5B10 stays 98.55 after the slot 200 retype.
- Leaf92 (Leaf67 NOTES): VoxelAnim slot67 0x70CFC0 91.57 (draft Leaf67/w/va67k3.cpp, overlay hv/);
  BuildingLight slot67 0x433380 is 1510 B (ret 8 at 0x433963), AI 0x433970 is 1818 B; Trigger action
  0x6B2040 99.31 (one lea operand order, Seed90 w/t2/j1.cpp).
- Below 0x500000 (Seed110/Seed105/Seed104 NOTES): EventClass type-5 ctor 0x4B61F0 97.67, VQ audio
  close 0x411A60 92.41, 0x4763D0 94.0, Fly 0x4BCA00 86.96, BulletClass::Detach 0x461520 75.21 (Cell ctor
  0x42AD30 stays out of line in the original); not started: CCToolTip 0x46DFC0/0x46E250, 0x467A20,
  COM QueryInterface 0x49F710/0x4A6460, Aircraft 0x4141C0/0x418840.
- Symbol debt: manifests/symbols.json names 0x783810 `__strnicmp`, but it is strncmp; the real
  _strnicmp is 0x7858D0 (Coop108 evidence). Fixing it needs CDFileClass Set_Search_Drives 0x46FE70 to call
  strncmp and its population re-accepted with the new binding (a symbols-only edit fails the reference
  audit). FoggedObjectClass(BuildingClass *, bool) 0x4C0670 90.66 (Index109 w/f4c0670c.cpp).
- Best misses by lane: WarheadType Read_INI 0x7204E0 99.80, Sidebar Draw_It
  0x67CF80 99.43, TechnoType Load 0x6DE260 98.19 (cached-zero register),
  command registration 0x5173C0 76.7 (holds 47 destructors).
- MultiplayerGameMode/MessageListClass (Coop115 NOTES): Concat_Message 0x5B51C0 99.49, Add_Message
  0x5B4DA0 98.18, Input 0x5B56F0 81.55 (needs an inline Restack_Messages), INI getter 0x5B7840 43, fill
  combo 0x5B70B0/0x5B71E0 58.89 and register 0x5B8490 (inline budget keeps VectorClass ctor 0x5B98E0
  out of line in the original); 0x5B7CE0 blocked on CounterClass.
- Tactical projection family parked (Seed113, Seed114, Seed123 NOTES): 0x6A2870 82.14 and 0x6A27A0 73.24
  hinge on a dead store of the projected X at the lowest frame slot that no `int[2]`/struct layout reproduces
  (VC6 keeps only the highest element's store). The same shape blocks 0x6A29D0, 0x6A66B0, 0x6AA180, 0x6AA300,
  0x6AADD0, 0x6A92A0, 0x6A8560 (Seed125: X/256 dead store to the CellClass* slot at 0x6A8813). Untried: a references signature for 0x6A6800, an in-place TacticalProjection/Point2D member.
- Voc_Static_Save 0x714A90 74.12 (Seed118 w/voc2/save.cpp): register allocation only (-1 index in esi, node
  and result registers swapped); the callee-pops `lea` rule that fixed the loads does not apply.
- CD unit (Cd121, Cd124): Find_Disk_Drive 0x715090 85.61 (Cd121 dr/w_0_1.cpp, `i` wrongly at function scope);
  better-shaped Cd124 dr/x1.cpp 80.00 (shape 98.18, exact inner loop). Left: root/i/API-pointer register
  allocation (original esi/edi/ebx/ebp, GetDiskFreeSpaceA hoisted) and a `test al,al; setne al` tail after
  `CD().Force_Available` (untested: the virtual returns a 1-byte non-bool, a cd.hpp change touching its users).
  It inlines Drive_Info yet precedes it in population-2880; check emission order. Inventory debt: the function
  list splits 0x715230 at 0x715244 and 0x715300 at 0x715463 (last FindClose bytes; accepted with body_bytes
  201 and 369); the sweep/seed lists should drop 0x715244 and 0x715463.
- Tactical 0x6AAFD0 82.94 (Seed125 w/best_6aafd0.cpp, plan pl/t.json in population-2856, header overlays in
  hdr/shared: tactical.hpp declaration, rect.hpp Point2D::Unknown_006AC850 in-place difference): selected
  buildings' dashed target lines. Register/schedule ties only (b4/b0 load order, ctor X push register, a
  folded `lea` for `to += area; +2`, phase/vtable registers in the three draw calls), so Windows near-miss work.
- MultiplayerGameMode 0x5B8490 (1838 B) 61.28 (Coop122 w/r8490.cpp with hdr/; needs
  VECTOR_IMPLEMENT_DYNAMIC_INSERT_AFTER in the modes() 0x5B6C30 source). Shape is right: without the unit's
  LIST/INDEX_DECLARE_CONSTRUCTOR it is 71.06 at 100% shape, only stack slots differ, but ctor 0x5B6CD0 then
  drops to 74.15 (its `new CCINIClass` must call the List/Index ctors out of line while 0x5B8490's
  `INIClass ini;` inlines them), the same unit inline-budget problem as 0x5B7840. ABI debt: the draft
  const_casts to call non-const Create through a const & parameter (fix: const Create, 6 rows, or a non-const
  parameter, which renames register used by init_modes).
- TechnoClass slot 43 0x6C1830 (576 B) 98.30, 176/176 instructions (Techno127 w/best_6c1830.cpp, plan pl/t.json in
  population-2648): fire coordinate through Matrix3D. One scheduling tie: the original stores/fild's the turret
  int after `shr ecx,1; and ecx,0x1F` with its fmul after the second store. Untried: an inline TechnoClass member
  for the turret angle, another FacingClass accessor for +0x2E0. Windows near-miss work.
- ObjectClass slot 72 0x5D3060 98.29 (Obj126 misses/slot72_005d3060_98.29.cpp; signature `Rect unknown_slot72()`
  already right): register tie in the last overlap test (`add edi, edx` vs `add edx, edi`). Windows near-miss work.
- ObjectClass slot 73 0x5D31C0 32.41 (Obj126 misses/slot73_005d31c0_32.41.cpp): logic recovered; inline budget,
  the original calls Rect ctor 0x42BCD0 out of line inside all three Get_Frame_Rect expansions while Get_Frame,
  Is_Valid and the return Rect stay inline. Next: build the frame rects through a deeper header helper.
- CCToolTip::Show 0x46DFC0 98.95 (Tip130 best_show_0046dfc0.cpp, --symbol '?Show@CCToolTip'): two loads swapped
  (area X before Width in the no-tip branch). Windows near-miss work. CCToolTip::Debug_Print 0x46E250 60.92
  (best_debug_print_0046e250.cpp): register/stack-slot allocation in the text-box section.
- ParasiteClass::AI 0x606F50 98.10 (Para131 drafts/ParasiteClass_AI_00606f50.miss.cpp, inc/shared): needs the
  TechnoClass slot 223 rename to `int (CoordStruct const *, float)` (5 populations) first, then one scheduling
  tie (`add ebx,-0x3FFF` before the Random2Class call). Windows near-miss work.
- MSPrintAnim::Draw 0x5AF030 (MSAnim133 drafts/MSPrintAnim_Draw_005af030.cpp): byte-exact alone, but in
  population-2658 it expands Intersect inline because MSBinkAnim::Draw includes rect_intersect.hpp earlier in
  the unit; the original calls 0x41FDF0 out of line at 0x5ACC73, 0x5AD2D3, 0x5AD777, 0x5AF04D, 0x5AF50D while
  other sites expand an inline (Rect ctor 0x42BCD0 calls). Needs a rect.hpp/rect_intersect.hpp design (the
  expanding sites likely use a different inline). Symbol ?Draw@MSPrintAnim@@UAEXPAVSurface@@PBVRect@@@Z.
- Stale 0x4F52B0 manglings left in reference tables after Debt154 (harmless, no source user): two truncated @ref
  lines `?Unknown_004F52B0@HouseClass@@` in BuildingClass 0x443BA0 and 0x4519D0, and `?unknown_func_4f52b0@
  HouseClass@@QAEHXZ` (int return) rows.
- ScoreFontClass Print_Char 0x667B60 98.89, Print 0x667C70 99.11, Char_Pixel_Width 0x667AA0 98.28 (Score132
  misses/): one shared blocker, the char-index clamp's first test is `add eax,-0x21; test eax,eax; ja` (unsigned)
  where every draft gives `jg`; unsigned casts break the reuse of `ch - '!'`. Untried: OEM output char types, an
  inline helper taking unsigned, option variants. Windows near-miss work.
- IPXGlobalConnClass slot 17 0x524870 98.50 (IPX135 drafts/IPXGlobalConnClass_unknown_slot17_00524870.miss.cpp
  with drafts/ipx_global_conn.slot17.hpp): really `void unknown_slot17(unsigned long age)` (rename spec needed),
  one swapped load pair at +0x95 (original reads rec->ReceiveTime before age). Windows near-miss work. The
  `memset(&header->unknown_08, ...)` rule that fixed Send_To may lift IPXConnClass::Send_To 0x523D90 (52.7).
- CNetUtilEventSink::OnLadderList 0x75D330 (2195 B) 87.38, shape 99.67, 610/610 (Sink139 v/best.cpp; header overlay
  inc/shared/wol_sink.hpp built by mkhdr.py adds codex3 r14 declarations HEAD lacks; scores need --symbol and
  --include). Only the opening differs (original keeps the normalized list pointer in ebx). The structurally
  closer v/a1.cpp (74.53) swaps ebx/ebp (list vs cached SendMessageA) throughout. Windows near-miss work.
- WorldDominationTour::Campaign ctor 0x725F40 (914 B; not WDTState) 77.30 on HEAD headers (WDT136 v/c.cpp,
  --include inc); 84.47 (v/F_q.cpp, --include incopF) only with rc_ptr::operator-> written as a null-checked
  conditional and a WDTState Territory_List() accessor, a header change every rc_ptr user must be checked
  against. Left: the original does not fold properties->TheWDTState-> in the conflict loop, and an edi/ebp swap
  in the INI tail. VectorClass<rc_ptr<Conflict>> ctor 0x727040 is exact when emitted from the ctor's source and
  lands with it (check its ??_E COMDAT across the population).
- CampaignScoreClass::Presentation 0x466A50 (1956 B) 98.98, shape 100, 586/586 (Score144
  misses/CampaignScoreClass_Presentation_00466a50.cpp with misses/shared/campaign_score.hpp; symbol and include in
  Score144 NOTES): only the aborted (0x24) branch swaps the cached GetDlgItem/EnableWindow registers (edi/esi).
  Untried: the player-removal loop as a helper, an inline 0x24 branch, for(;;)/do-while main loop. Windows
  near-miss work. CampaignEndScoreClass 0x467A20 not started.
- WorldDominationTour::Map ctor 0x729330 (real extent 179 B, inventory cuts at a noreturn call) 74.00 (Ref143
  miss/map_ctor_729330.cpp with miss/wdt_map.hpp): the original calls VectorClass<rc_ptr<Territory>> ctor
  0x72BB10 out of line; VC6 inlines it here (like the Campaign ctor's vector), probably the unit's inline budget.
  Needs rows 0x729330 and 0x72BB10, body_bytes 179, and an @ref for ":" at 0x83C55C.
- VoxelAnimClass (VoxAnim145; the rest of the unit is recovered): slot 67 0x70CFC0 92.37 (w/s67_e.cpp with hv/:
  virtual unknown_slot67(int, int), unknown_f4 HouseClass*), raised.Z recomputed from esi in the original vs an
  `inc eax` reuse here; ctor 0x70C800 85.37 (w/c_0.cpp), cached-zero ebx kept through the meteor path (Study37
  pattern). Random_Pick (id_source.hpp) is worth trying wherever the original adds a random range result last.
- AircraftClass (Air146 best/, hdr/shared overlay; NOTES has the symbols): 0x418F10 99.21 (dest.Y load order),
  0x41B6E0 97.14 (pitch helper, 2-byte non-POD direction return; lands only with slot 221 0x415790, not started),
  radio slot 95 0x418840 93.01 (case 18 slot116 vptr register), render slot 67 0x4141C0 90.30 (Head_To_Coord copy).
  Not started: 0x416C20 (Air63 85.93), 0x4178A0, 0x4185B0, 0x4198B0, 0x416010 (no inventory row; tail jump of
  0x415FF0). Rule: an identical tail written in both the branch and after the if/else is merged by VC6 and gives
  the original's registers (slot 147).
- InfantryClass own members parked (Inf148, zero bytes; score drafts inside the whole unit, standalone scores
  mislead because the unit inlines later helpers): slot 87 0x504120 65.59 (Inf65 w/504120_a.cpp; constant 1 kept
  in edi/ebp only on part of the function), slot 86 0x4FFB70 83.76 (w/f2.cpp; the original places the post code
  between the NotHuman block and the switch), slot 67 0x500550 62.78 (w/p0.cpp, still has dead Map_Cell_At calls),
  slot 260 0x501CE0 70.74 (Cell ctor 0x42AD30 out of line: inline budget spent earlier), slot 101 0x503190 77.82,
  slot 93 0x500AA0 drafts stale. Needs a controlled study of partial-function constant registers first.
- BuildingLightClass (BLight150 best/, NOTES): ctor 0x432FC0 73.59 (96.54 with UnknownCoord434820 forced out of
  line: /Ob2 budget inlines the first 0x434820 site, every natural extra cost pushes the second out instead);
  slot 67 0x433380 54.51 fully decoded (inline pattern of operator- 0x4348F0 / 0x41B630 per site in NOTES, and
  an aligned frame from the `double angle` local); AI 0x433970 not started. COMDAT CoordStruct::operator-
  0x4348F0 lands with whichever of slot 67/AI first calls it out of line.
- UnitClass group 2 (Unit149 w/, NOTES): slot 28 What_Action 0x703BD0 56.84 (block layout: the DeploysInto==0
  block sits after the 4F52B0/action==7 body; needs shared declarations for 0x40DBD0 and 0x614B50, now local to
  Infantry 0x505390), slot 182 0x704730 59.71 (this/facing edi/ebp swap, frame 0x38 vs 0x34). Not drafted:
  slot 131 Mission_Harvest 0x7025A0 (seed s7025a0.cpp), slot 101 0x703040, slot 137 0x701580, 0x707F60.
  Slot 87's ad0488/ad04c0/ad0588 externs and the 0x79B628/0x79B630 facing constants still want a shared header.
- BulletClass shrapnel 0x462C50 (2757+11 B, ret at 0x463714; plan needs body_bytes) 49.25 (Bullet151
  best/s462c50_49.25.cpp with hdr2/ inline BulletVelocity API; codex1 66.76): the targeted loop calls the four
  Length helpers out of line, the later random loop expands all but XY().Length; waits on Study152. AI 0x45F710
  not started. Score Bullet drafts inside the whole unit (Bullet151 mkwhole.py).
- UnitClass group 1 (Unit147 w/, NOTES): slot 86 0x6FCA30 98.08 (crate 0x5502E0 call registers; retry with the
  new Point2D(1, 1) argument), idle 0x6FBF40 96.02 (cell sum operand order), slot 67 Draw_It 0x700E70 84.52
  (frame overlap; needs slot 310/311 `void (int, int, Rect, int)` and TechnoClass::unknown_6cc020), slot 312
  0x6FF3E0 66.67 (needs a rename spec), slot 93 0x6FE610 codex4 draft does not compile and has a comma-expression
  steering construct. Not drafted: 0x6FDFC0, 0x6FF690, 0x7005B0, 0x6FAA30. Cell::unknown_42add0 is an inline
  member standing for 0x42ADD0 (naming hypothesis). Unit statics 0xAD0488/0xAD04C0/0xAD057C are the header
  statics unknown_geometry_k/_l/_j.
- UnitClass remainder (Unit153 NOTES): 0x707F60's 1598 B inventory bound is wrong (the body jumps to 0x708AF0,
  0x709536, 0x70955C; ~11 fragments to 0x709790, about 6 KB): fix the bound before drafting (seed/00707f60).
  Tube walk 0x6FAA30 (1730 B) layout and math recovered, blocked on typing 0x4348F0/0x41B780/0x41B630 as
  CoordStruct helpers (HEAD has UnknownVector3). Slots 310 0x6FF690 and 311 0x7005B0 wait on the 310/311/312
  signature rename (Unit147 hdr/).
- Inline-budget cases after Study152 (rule now in VC6_MATCHING_NOTES): BuildingLight ctor 0x432FC0 gets the
  original call pattern by typing unknown_a0/unknown_ac as UnknownCoord434820 (Coord_Along_Facing building one;
  0x4341D0 stays exact) but the init-list copies then put zero in eax not edi (37.69): find the init-list
  spelling. MultiplayerGameMode 0x5B6CD0/0x5B8490/0x5B7840: `{ Invalidate_Message_Digest(); }` in the CCINIClass
  ctor reproduces the pattern but breaks other units (DIR32 operand boundary), so not the original spelling.
  MSPrintAnim::Draw 0x5AF030: one more pending inline site later in Draw, or a depth-3 Intersect, gives the
  original call; untested a two-level Rect::Intersect member chain (rect.hpp, whole-tree check). The Campaign ctor
  0x725F40 is not an inlining problem (folding/registers, WDT136).
- After Inline156 (NOTES, drafts in build/class-work/Inline156/): MSPrintAnim::Draw landed. Bullet shrapnel 0x462C50
  53.52 (bul/v/best_53.52.cpp with bul/inc2): the inline call pattern is solved by routing Coord copies through an
  inline by-value accessor (lab: free Coord_Of_462c50; really an ObjectClass member) and the random loop's cell
  through Map_Cell(cell); left is the count prefix (esi spill, Coord copied before Owner->Center_Coord) and a frame
  8 bytes too big, Windows near-miss work. BuildingLight ctor 0x432FC0: with a UnknownCoord434820 local in
  0x4341D0 (bl/v/f2.cpp, stays exact) the ctor reaches 87.01 but keeps owner in edi instead of rereading [ebp+8].
  The other out-of-line 0x41FDF0 call at 0x5AF50D is in an unrecovered MSPrintAnim function 0x5AF210-0x5AF790.
