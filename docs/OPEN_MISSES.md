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
- UnitClass drawing family (Unit155 drafts/, NOTES): slot 311 0x7005B0 87.08 (slot311_7005b0.cpp with hdr311/:
  needs an inline UnknownObjectPair::Is_Loaded() in object_type.hpp and `Matrix3D __fastcall
  unknown_voxel_matrix_717f90()`; left are load scheduling and a zero kept in ebx into slot 246's zero args);
  Draw_It 0x700E70 85.75 (draw_it_700e70.cpp: frame 0x48 vs 0x40, the original shares one slot between the
  angle double and the projected CoordStruct; still carries `int const &direction`/`ColorScheme *const &scheme`
  steering to replace); slot 310 0x6FF690 not drafted (seed does not compile; reuse slot 311's idioms).
- MSAnim unit (MSAnim157 NOTES): MSPrintAnim::Set_Rect 0x5AE7E0 (439 B) is byte-exact in the unit but refused
  ("Unsupported independent bound": Ghidra splits it at 0x5AE806 around a phantom 0x5AE808); needs a bounds row
  0x5AE7E0-0x5AE996 (caller 0x5AE752), then one row (src1/MSPrintAnim_Set_Rect_005ae7e0.cpp,
  ?Set_Rect@MSPrintAnim@@QAEXABVRect@@@Z). MSShapeAnim slot 4 0x5AC850 81.74 (v/s4_a.cpp; v/s4_y2.cpp 80.70 has
  the right inline pattern), register allocation only: compare with the exact MSFadeAnim slot 4. 0x5AF430 sits in
  seed population-88. Rule: VC6 defers code generation to the end of the unit under /Ob2, so inlines defined
  later in the unit expand into earlier functions.
- TerrainClass unit complete except (Terrain160 w/miss/, NOTES): slot 63 0x6E4430 88.79 (Offset_Rect/Rects_Overlap
  form; register allocation after the slot73 call), Read_INI 0x6E4260 80.21 (the original copies the cell into
  the shared local inside each branch from different registers; ours merges the store after the join). Both
  Windows near-miss work. Rules: an if/else on a file-level inline predicate keeps a flags ternary from being
  if-converted (slot 67); a by-value inline accessor gives one hoisted Coord copy per use (slot 86).
- Type-class readers (Types161 dr/, NOTES): WarheadTypeClass::Read_INI 0x7204E0 99.80 (Verses loop: the shared
  fstp [ebx] sits after the two strtok pushes in the original), TechnoTypeClass::Load 0x6DE260 99.64 (palette at
  point of use: shape 100, cached zero in ebx vs ebp), UnitTypeClass::Read_INI 0x70AB40 50.00 (shape 93.4, register
  assignment of this/ini/ID/art section differs throughout). Windows near-miss work.
- AnimClass unit (Anim162, zero bytes; NOTES, drafts/, overlays hv/ hy/): ctor 0x420110 95.68 (531/533 insns, frame
  right; Center_Coord inline in the ctor; 0x436DC0 is `void (CoordStruct const &, double, double, double,
  Vector3 const &, double)`; a free operator+ gives 98.40 but breaks accepted 0x420D90 at 77.67), landing spot
  0x4237B0 73.22 (stack slots, x/y in edi/ebx). Not started: AI 0x421710, draw 0x420E50, 0x423120 (codex1 drafts
  72.36/81.82/84.50 need porting). 0x42007B, 0x420A8E, 0x42151B are inventory fragments inside accepted regions.
- Left163 (NOTES, miss/): CellClass::Load 0x478CB0 91.12 in the population composite (plan pl/cell-t1.json 86/87;
  needs the VectorClass<FoggedObjectClass*> ctor specialization under auto_inline(off), an inline DVC ctor
  specialization, and the accepted noinit ctor 0x470680 rewritten as an init list (owner decision, still exact);
  left: the original keeps a second null test on the deleted map-table cell). CellClass ctor 0x470F10 72.45.
  HouseClass::AI is one function 0x4E4110..0x4E4EE7 (3536 B; inventory rows 0x4E4110 + 0x4E414C), a class-lane
  target of its own (raw seed 24.45). Inventory artifacts: TEventClass 0x6E6D9D is 3 NOPs before the accepted
  ??_G 0x6E6DA0; DynamicVectorClass<FoggedObjectClass *> lists 0x478CB0 as a vptr writer.
- TeamClass after Team165 (v/, v159/, NOTES; score with HD=hr and the 0x6BAA60 EXTRA in its sc.sh): GatherAtEnemy
  0x6BDAA0 95.67 (stack slots), 0x6BD240 93.13 (x87 add order), 0x6BCBB0 88.06 (coord copy during argument
  evaluation; needs HouseClass::unknown_4eec70), TMission_Load 0x6BB5F0 85.10 (transport register), 0x6BE010 76.32
  and 0x6BE440 65.81 (0x6BDD80 still inlined: one inline call short after the leader pick). Not drafted:
  0x6B88B0, Calc_Center 0x6B9610 (the original calls UnknownVector3::Length 0x41B780 in one loop and inlines it in
  the other: Length is inline in RA2, a header change touching EMPulse 0x4B4E30 and BuildingClass 0x445620),
  AI 0x6B7AD0. Type hypotheses in landed source: 0x6BC7B0 casts 0x6BCF70's result to ObjectClass *; 0x6B91C0 reads
  the stand-in Infantry elements as FootClass *. Inventory rows 0x6BBEE1 and 0x6BC565 are mid-function.
- HouseClass::AI 0x4E4110 (body 3544 B, not 3536: the two inventory rows miss 8 bytes) 99.32, shape 100, 1034/1034
  (House164 miss/HouseClass_AI_004e4110_99.32.cpp with miss/inc/; NOTES has the whole-unit scoring commands): two
  variables get ebp where the original has ebx (flag-home damage-loop counter, capacity local in the money check).
  Landing it needs a rename (TeamTypeClass::Create_One_Of 0x6BEC80 const), about eight HouseClass helper
  declarations, IUnknownHouseAI for +0x56CC, map_view members, and resolving ownership of 0x4F6F30/0x4F7CD0
  (accepted today under other sources; AI makes the House unit emit them). Windows near-miss work.
- Queue.CPP (population-466, 0x622FB0-0x62EAF0) and Event.cpp (population-2590) after Queue166 (NOTES, w/, hv/):
  Queue_AI 0x623770 91.78 (the original calls QueueClass<EventClass,128>::Next 0x62E9E0 out of line, accepted
  as seed FUN_0062e9e0 in population-42, so a plan must retire it; defining Next late pushes Clean_DoList inline
  instead), EventClass type-5 ctor 0x4B61F0 97.67. Not started: Compute_Game_CRC 0x629FA0 (924 B, maps onto Red
  Alert's), the unit statics 0x623210/0x623230/0x6232D0/0x623320/0x623370 (need data definitions and retiring five
  seeds), EventClass::Execute 0x4B65C0 (4994 B), Queue_AI_Multiplayer, Wait_For_Players, Execute_DoList,
  Send_Packets, Build_Send_Packet, Print_CRCs (917-5519 B), dialog code 0x626FE0, 0x626CB0, 0x627350.
- TechnoClass (Techno167 w/, NOTES): ctor 0x6C0CD0 99.66 (mov eax,0xa scheduled early), slot 220 Assign_Target
  0x6C9AF0 98.82 (mov ebp,esi early; inline Target_Legal), NoInit ctor 0x6C1F10 66.06 (exact only with four more
  pending inline sites after the vectors: no natural source yet), helper 0x6C3950 69.29, slot 65 0x6C3B30 28.57
  (decoded; inline budget). Not started: Take_Damage 0x6CDC40, AI 0x6C74C0, slot 66 0x6C2C40.
- Conquer.CPP (population-2425; little of Red Alert's CONQUER.CPP survives here): 0x481BF0 (780 B, the game-session
  loop) stores ESP/EBP and a code label (`lea eax,[0x481cd8]`) into 0x865C14/1C/18 -- evidenced handwritten
  assembly, a separate ledger category, not C. 0x482110 Service_Network_Handshake (2438 B, seed 22.78) needs the
  0xA40978 manager members, Unknown84E8D0 methods, session/packet layouts and retiring seed 0x482AA0 (atexit
  destructor of the function-static timer at 0x850D94): a layout-recovery lane.
- Queue.CPP after Queue168 (u-misses/, NOTES; hv/shared is ahead of main: rebase before resuming): 0x6279D0 83.46
  (save kept in cl and tested twice), 0x629220 82.05 (loop tail jg/jmp and shared epilogue), Process_Receive_Packet
  0x6265C0 66.27 (packet/net registers, one more local), response-time bars 0x626CB0 46.93 (registers). Not started:
  Add_Compressed_Events 0x627B60, Extract_Compressed_Events 0x6282D0, Execute_DoList 0x628880, 0x629290,
  Queue_AI_Multiplayer 0x623B00, Wait_For_Players 0x624C10, Print_CRCs 0x62A360 (11 KB), 0x62CF40, 0x62DBA0, the
  templates 0x62EA00/0x62EA40, Queue_AI 0x623770. Unit rules: ms_engine.hpp adds an initializer (use map.hpp's
  unknown_481fb0), display.hpp must precede map_view.hpp.
- TAction.CPP after TAction172 (w/, NOTES): show text 0x6B0440 92.86 (Rules pointer register), reveal zone 0x6B0840
  62.39 (needs map_view Unknown_0055AA50/0055A910; coordinate temporaries scheduling), reveal some 0x6B0670 43.97
  (original keeps a Cell(half, half) temporary slot), 0x6AFD80 not drafted (Seed90 58; needs the 0x41B630 chain),
  Execute 0x6ADAE0 (7.3 KB switch) not started. Stale inventory starts here: 0x6AFD46 is 0x6AFD50, 0x6B01A2 is
  0x6B01A0, 0x6B02F0 is two functions (0x6B02F0, 0x6B0360), 0x6B03D0/0x6B05FD/0x6B082B/0x6B0A59 are tails or padding.
- Init.CPP (population-2752) after Init174 (NOTES, w/; score drafts as w/pre.txt + draft): PlanningMode slot 5
  0x51B9B0 42.86 (the original returns a full-register 0/1; bool forms give setne), 0x516E70 97.62 (push 0 / xor cl,cl
  order in the inlined 0x517370 call), 0x513290 needs LoadOptionsClass::Unknown_0053C5C0 (Windows-owned class).
  Not started: 0x5127F0, 0x514EE0, 0x516900, 0x51A690, 0x515710, 0x51A330, 0x519500, 0x519E70, 0x515110, 0x5173C0,
  INIClass/CCINIClass ctors 0x51AD50/0x51ADE0 (emitted only with their callers). About 20 inventory extents in this
  range are wrong (0x5116A0 is about 4.4 KB); Init174's ext.py checks them.
- Session.CPP (population-329, 0x66E0A0-~0x674FFF, RA SESSION.CPP order; Session173 open/, NOTES): Create_Connections
  0x66EE50 99.09 (two cmp al,bl vs test al,al; needs open/owner_talk.hpp), Free_Scenario_Descriptions 0x6714B0 exact
  in the unit but needs a DynamicVectorClass<Wstring> GameModes member at MultiMission +0x1A4, which makes a
  multi_mission.hpp header-user population emit unaccounted COMDATs. 0x66FF90 + 0x670061 are one function split by
  the inventory (bound decision). Not started: ctor 0x66E380, dtor 0x66EB20, Read_MultiPlayer_Settings 0x66F3A0,
  0x6707D0, Read_Scenario_Descriptions 0x670C50, 0x671670, MultiMission ctor 0x671C50, 0x66E330. Lesson: acceptance
  binds references per candidate, so a draft needs @ref lines for what other drafts inline into it.
- Scenario.CPP (population-2709, 0x65B2C0-~0x663440; Scenario177 open/, NOTES): Wait_For_Players 0x65C520 90.40
  (shape 100; drop-loop register permutation), Multiplayer_Start_Waypoints 0x65FFF0 66.67, Scan_Place_Object 0x660B60
  51.74 (RA shape with file-static Clip_Move/Clip_Scatter; shape 91.97), NoInit ctor 0x65B780 64.00 (TTimerClass
  needs an empty NoInit ctor; TypeList DVC ctors must stay out of line: inline budget), Clear_Scenario 0x65D370 99.32,
  Fill_In_Data 0x65CDD0 93.73 (needs a RadarClass/Tactical slot 52 CoordStruct rename). 0x65D7EA and 0x661408 are
  tail chunks of accepted functions.
- NullDlg.CPP (population-293) / NullMgr.CPP (population-2691) after Null175 (NOTES): the serial dialog main loop
  0x5CDF00 (2567 B + jump table at 0x5CE904; the inventory start 0x5CDEFA is padding) needs stack dialog class
  layouts (PhoneEd 0x60D970, ModemGst 0x598E10/0x596010, SerialEd 0x66CA70) and helpers 0x5FF610/0x600120, and
  inlines TTimerClass::Time at some sites while calling 0x5CFDB0 (31 B, lands with it) at others. Init_Null_Modem
  0x5CEA30 is accepted in population-2402 under a stand-in class but belongs to population-293 (debt).
- House.CPP after House171 (miss/, NOTES; score inside the unit): 0x4F3F40 95.45 (index+base operand order),
  0x4E67A0 84.06 (inlined Is_Ally result kept as 0/1 in al; 0x4EB360 has the same pattern), House_Facing_Score
  0x4F02E0 81.82, Spend_Money 0x4E5280 76.61, All_Prerequisites_Available 0x4EF740 39.07. Not drafted: Flag_Attach
  0x4E76A0 (needs +0x5308 and Flag_Remove as AbstractClass *), 0x4F1E50/0x4F1FF0/0x4F2190 (return a DVC by value;
  VectorClass ctor 0x4F8900 is accepted under a seed name), 0x4E64F0, 0x4EAF30, 0x4EA1B0, 0x4EA4D0, the >800 B rest.
  Is_Human_Control is now the mode==0-first inline: recheck House164's AI draft with it. Type debt: Sell_Wall casts
  `(int)this` into building-type slot 33 (Cost_Of(HouseClass *) declared int); unknown_max_ahead_a3d560 is a
  file-level extern (ipx_manager.hpp has the other declaration; unknown_globals.hpp is the better home).
- Init.CPP after Init176 (w/, NOTES with true extents): Init_Bulk_Data 0x516900 82.35, best selected object 0x51A690
  60.34 (bit0 bool stored to a stack byte), Init_Theater 0x519E70 78.06, Allocate_Surfaces 0x519500 76.84; 0x514EE0
  writes session globals at widths that conflict with their declarations. Not started: 0x5134C0, 0x513080,
  0x516C40, 0x516F00, 0x5171D0, 0x515E70, 0x516560, 0x51A880, 0x5129C0, 0x5147A0, 0x5135F0, 0x5116A0, 0x5173C0.
  Rules: a parameterless function called with this-style object setup matches as __fastcall (as __cdecl VC6
  schedules the object-address lea/mov ecx after the pushes); a unit doing CCINIClass new/delete emits ??_GCCINIClass
  and ??_GGenericNode, which need ArtINI_init_0040de40.cpp's @ref block; queue.hpp's include chain ahead of 0x515710
  grows Delete_All_Objects by 64 bytes.
- CampScor.cpp (population-423) after CampScor180 (misses/, NOTES): end-screen dialog proc 0x467330 93.49 (shape
  99.20; ebp pushed right after the dialog-handler early return in the original), Presentation 0x466A50 98.98 (now as
  a whole-unit TU: misses/tu_...; use unknown_session_a3d298.Scores/.ScoreCount and controls_7d1484[i][5]; the
  ctor draft must also define DYNAMIC_DELETE_OBJECT, DYNAMIC_DELETE_INDEX and VECTOR_CLEAR to land it). Inventory
  rows 0x465D01, 0x465F96, 0x46622A, 0x466754, 0x4669E8, 0x46743A, 0x4676CF, 0x467963 are false entries.
- netshare.cpp (populations 2763/2769) after Netshare179 (misses/, NOTES; score with sc.sh -a against the whole
  unit): 0x5C67C0 91.87 (dialog handle register copy), 0x5CA540 56.30 (strength-reduced second loop), 0x5CB170
  52.86, 0x5CAE00 ~30. Blocked: 0x5CC700 inlines accepted 0x5C9950 (population-955; owner approved moving it into
  2763), 0x5CC890 reads an int at 0xA3D2B0 that the headers declare as UnknownLobbyState/UnknownBlock_a3d2b0 (type
  decision), 0x5CA000 not drafted. About 20 larger functions and the unit start 0x5C2BA0-0x5C3D90 not started.
- Init.CPP after Init181 (w/, NOTES): Load_Title_Page 0x516560 99.63 (pop edi one instruction early inside the
  64-bit Audio_Now()+5000 store), 0x516F00 95.15 (score as pre.txt + draft + w/e/tail.txt; the original puts the
  memset else-branch after the epilogue), Init_Rules 0x5129C0 45.98 (VectorClass<CCINIClass*> ctor 0x51E710 out of
  line with the Dynamic part inline; out-of-line INIClass ctor 0x51AD50 is unaccepted and needs its own row).
  Not started: 0x5147A0 (1842), 0x5135F0 (4356), 0x5116A0 (4420), 0x5173C0 (7807).
- ModemHst.cpp after Modem182 (build/class-work/Modem182/NOTES.md): undrafted. 0x59B090 SelectMultiMap and
  0x59B2C0 use the result of 0x5C6960 (accepted as void Open_Lobby_Dialog_005c6960: needs a rename to int with
  0x7359E0's return type); 0x59BC90 Send_Options needs the command 0x65 bitfield packet layout; large bodies
  0x599920, 0x598FA0 (jump table), 0x59B690, 0x59C290, 0x59C8B0, 0x59CBA0, 0x59CD00. ModemGst.cpp (16) untouched.
- PlanMgr.cpp after PlanMgr178 (build/class-work/PlanMgr178/v, NOTES): 0x615ED0 Can_Add 92.00 (__fastcall, count/added
  registers swapped), 0x6171E0 81.58, 0x616A50 77.83 (js vs test/jl), 0x616B40 75.76 (kind -1 in ebp), 0x616960 60.10
  (Next inlined), Rect family 0x615D30 56.69/0x616140 65.41/0x616070/0x617900 (one extra frame Rect), 0x615A80 39.38;
  0x615C00 exact only with Pick_Drawn inline. Twelve undrafted (list in NOTES); inventory bounds wrong, ext.py.
- netshare.cpp after Netshare183 (build/class-work/Netshare183/misses, NOTES): 0x5C34F0 97.37 (mov esi,eax before
  the pushes), 0x5CB560 Clear_Observer_Slots 98.97 (tail-call arguments before the pops), 0x5C2DA0 56.09 (registers),
  0x5C67C0 91.06 (needs pop-67 seed 0x5C67A0 in the unit). Blocked: 0x5C3C60/0x5C3D90 (packet type past 0x1C7),
  0x5C6310 (WOL hash table), 0x5C8420/0x5C84E0 (random-map CRC). 0x5C5EC0 is inside 0x5C3FF0.
- netdlg2.cpp after Netdlg184 (build/class-work/Netdlg184/misses, NOTES): 0x5BCCF0 Set_Slot_Country_Color 87.73 (name in
  ebp, country spilled across the slot loop), 0x5BC940 Build_Game_Options 86.47 (register rotation after
  description.Get()); 0x5BC460 Init_Network exact (w_hold_abc460.cpp) now that Set_Bridge has landed. Undrafted:
  0x5BBDD0 (WolLadderListCell hash table), 0x5BD070 (4915), 0x5BE6B0, 0x5BEFE0, 0x5C01D0 (three local timer statics,
  atexit dtors are pop-67 seeds), 0x5C08A0 (6798), 0x5C2330.
