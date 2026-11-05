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
- PlanMgr.cpp after PlanMgr186 (build/class-work/PlanMgr186/v, NOTES; parked): nearly every miss is an inline split
  where the original expands less. 0x616350 Path_Add exact except relocations with Close_Loop inline, but Close_Loop's
  only out-of-line caller is 0x614BA0 Execute (65.84): land the three together (~1.17 KB). 0x617AF0 90.00 (Member_Event(0)
  and second Planning_Help(4) out of line), 0x617680 64.31 (Rect family), 0x614850 37.75 (first 612b50 inline, second
  called; needs 0x610770 and 0x613310 taken over from pops 1640/42), 0x6155E0 56.43, 0x615480 40.15, 0x6165A0 49.28.
  Exact supporting rewrites in v/ (0x611E20, 0x613A80, 0x611310, 0x61A8B0 operator== returning bool, 0x615FB0).
- Modem units after Modem185 (build/class-work/Modem185/w, NOTES): guest Init_Dialog 0x596540 66.11 (this/GetDlgItem
  pointer ebx/ebp swapped), guest Start_Game 0x5986F0 98.50 (TechLevel store eax/edx swapped), host Send_Options 0x59BC90
  93.30 (last IsOfficial store load order). Host Dialog_Proc 0x598FA0 needs the chat chain form (Show_Chat leaf <-
  Send_Chat(text) <- Send_Chat()); accepted host 0x59A880/0x59BFA0 are hand-expanded and may need rewriting.
- netshare.cpp after Netshare187 (build/class-work/Netshare187/misses, NOTES): 0x5C71F0 87.67 (lobby HWND through eax;
  needs 0x75CA30 unknown_dialog_c2_call -> bool(int,bool,bool) rename), 0x5C67C0 91.87 (same eax copy), 0x5C7570 80.45
  (CCFileClass temporary overlaps case buffers), 0x5C7EF0 73.91 (needs a wol_chat.hpp with IChat slot 15 and
  unknown_identifier_a71b18; owner: allowed as a new header), 0x5CCA30 73.63. 0x5C8420/0x5C84E0 use MapSeedClass (now
  free: the map-generator rename landed). 0x5C5FF0/0x5C6310 WideString hash-set template family.
- netdlg2.cpp after Netdlg188 (build/class-work/Netdlg188, NOTES): 0x5C01D0 Send_Join_Queries 98.94 (Games[curgame]
  vector before index; then take 0x5C05C0/D0/E0 atexit rows from pop-67), 0x5BEFE0 Host_Dialog_Proc 95.68
  (message/lparam ebx/edi swap; needs Open_Lobby_Dialog_005c6960 int and Is_Host_005c86a0 bool rename, and
  Send_Slot_Names via Session.Handle). Undrafted 0x5BBDD0 (hash container from 0x5C5FF0/0x5C6310), 0x5BD070, 0x5C08A0.
  The scorer never reports byte-exact for switch-table functions: check with Netdlg188/t/tdiff.py.
- WDTSel.cpp after WDTSel189 (build/class-work/WDTSel189, NOTES): blocked on two-level rc_ptr chains
  (TheCampaign->TheHistory->Get_State(): original `add eax,8; mov ecx,[eax+4]`, ours folds to [eax+0xC]); 25 operator->
  spellings tried. 0x72DEA0 96.15, 0x72F180/0x72F200 92.54 (dead lea), 0x72F6E0 82.14, 0x72FCD0 76.19, 0x72FF30 76.36,
  0x72F540 73.68, 0x72F430 58.50, 0x72E650 41.18; ctor 0x72D560, dtor 0x72D990 and ~5.5 KB wait on the chain.
- ModemHst.cpp after Modem190 (build/class-work/Modem190/w, NOTES): Dialog_Proc 0x598FA0 88.36 (case bodies in the
  original's jump-table order; /Ob2 cap is size; WM_DESTROY delete preview must call ??_GUnknownPreview 0x59CB80; land
  with the exact chat-chain rewrites w/sc880.cpp, w/scfa0.cpp), Send_Options 0x59BC90 93.30, guest Init_Dialog
  0x596540 85.97 (w/gi1.cpp, this/GetDlgItem ebx/ebp), guest Start_Game 0x5986F0 98.50. 0x59B090/0x59B2C0 now
  unblocked by the Lobby191 rename (f0fafc38).
- Lobby after Lobby191 (build/class-work/Lobby191/misses, NOTES): Make_Random_Map 0x5C84E0 99.18 (mov edi,eax after push
  0x1bc; inventory body 120, real 379), Send_Join_Queries 98.94, Host_Dialog_Proc 95.68 (tool-tip block), 0x5C67C0 91.87
  and 0x5C71F0 87.67 (HWND through eax; the rename did not move them). Undrafted: 0x5CB8D0, 0x5CA6C0, 0x5CBF20,
  0x5C69E0, 0x5C3FF0, 0x5BD070, 0x5C08A0, 0x5C7EF0.
- House.CPP after House193 (build/class-work/House193/w, NOTES): 0x4F2CC0 power recount 94.21 (was_low stack slot),
  0x4F3910 super-weapon AI 79.71 (original frame 4 bytes larger: two inlined Cell locals in separate slots).
  Begin_Production 0x4E5E30 analysed (e5e30.dis). 0x4F1E50/0x4F1FF0/0x4F2190 need VectorClass ctor 0x4F8900 taken over;
  Flag_Attach 0x4E76A0 needs a retype rename. True extents: 0x4EECB0 2276 B, 0x4F1190 3264 B.
- WDTSel.cpp after WDTSel196 (build/class-work/WDTSel196, NOTES): Select_Territory 0x72ED80 90.55 (mov eax,2 preload
  for Voices::Say kind; needs a Conflict::Is_Territory inline), Click 0x72E430 62.14 (original calls Get_Territory out
  of line; keep Click under auto_inline(off) or Choose_Territory stops matching), Hover 0x72E650 exact only as
  `true ? TheMap->Get_Territory(x) : rc_ptr<Territory>()` (refused as steering; the original zeroes a temporary-
  construction flag and copies the result: find a natural form). Undrafted: ctor 0x72D560, Show_State 0x72E780.
- Session.CPP after Session194 (build/class-work/Session194, NOTES): Create_Connections 0x66EE50 99.09; Set_Official
  0x6720AF (inventory starts on a nop; real entry 0x6720B0: needs a bound decision); MultiMission ctor 0x671C50 (body
  runs to 0x671F00; emits the DVC<Wstring> vtable so 0x674850/0x674AF0 join the unit; 0x671670 depends on it).
  Undrafted: 0x672440, 0x673090, ctor 0x66E380, dtor 0x66EB20, 0x66F3A0, 0x6707D0, 0x670C50, 0x66FF90(+0x670061).
- House.CPP after House197 (build/class-work/House197, NOTES): Zone_Cell 0x4EAF30 exact (f/, body_bytes 828), landable
  now that acceptance strips the 8D 49 00 fill; AI 0x4E4110 99.32 (two ebx/ebp choices), Check_Raise_Money 0x4E8D80
  84.60 (vector pointer kept in eax across the Factories loop), Expert_AI 0x4E8990 62.21. Begin_Production 0x4E5E30
  has four byte-indexed tables (~1464 B). 0x4F1E50/0x4F1FF0/0x4F2190 need the VectorClass<BuildingTypeClass*> ctor
  0x4F8900 emitted by the House unit and its seed row retired, and call unrecovered 0x4EF740.
- UICmnds.cpp after UICmnds199 (build/class-work/UICmnds199/w, NOTES): 0x6F7020 77.52 (original pushes ebx inside
  branch 1), 0x6F71E0 73.33 (saved sound flag in bl). Undrafted 0x6F6D00, 0x6F79C0, 0x6F7B80, 0x6F7EC0, 0x6F81B0
  (calls unrecovered 0x6F85E0), 0x6F7360 (end unclear: no ret between 0x6F7353 and 0x6F763E). Inventory extents
  wrong for 0x6F6930/0x6F69F0/0x6F6AD0/0x6F76C0 (lens.txt).
- WDTSel.cpp after WDTSel198 (build/class-work/WDTSel198, NOTES; parked): ctor 0x72D560 cmp 0.892 (Sounds' base vector
  ctor 0x7304C0 inlined in ours; 3+ extra pending inline sites after Sounds make it exact in the lab, natural source
  unknown: try an inline INIClass::Load(FileClass &), Map rect accessors, string-fetch wrapper), Show_State 0x72E780
  0.827 (original calls the TerritoryCursor ctor out of line), Select_Territory 0x72ED80 0.959 (Conflicts loop load
  order), Click 0x72E430, Hover 0x72E650.
- House.CPP after House201 (build/class-work/House201/w, NOTES): Begin_Production 0x4E5E30 78.85 (w/bp18.cpp; the
  four tables are inlined copies of 0x4EB550/0x4EB770/0x4EB580/Set_Factory; 0x4EB810 stays a call only under
  auto_inline(off) on its own source - acceptable only if the original never inlines it anywhere; diffs: `later`
  store after the first Who_Can_Build_Me test, default-case `xor esi,esi` not jump-threaded), 0x4F3F40 95.45 (SIB
  operand order at four sites), 0x4E76A0 needs a rename (void->bool, int arg->bool, +0x5308 AbstractClass*).
  Zone map +0x5640..+0x5654 and cell array +0x15F44 missing from house.hpp (needed by 0x4F02E0, 0x4F1190).
- Session.CPP after Session200 (build/class-work/Session200/w, NOTES): MultiMission(INIClass &, section) 0x671670 93.82
  (1496 B, inventory 650; two Wstring frame slots swapped; needs INIClass::Get_Wide_String 0x50F010 declared),
  0x672440 85.89 (original keeps not/dec/add 0x20 for new char[strlen+0x20]; VC6 folds ours to add 0x1F; squad
  strings 0xB2A820/0xB293D8 mistyped bool in unknown_globals.hpp), Set_Official real entry 0x6720B0 (13 B; inventory
  row starts on the nop at 0x6720AF: needs an inventory bound correction). Undrafted 0x673090, ctor 0x66E380, dtor 0x66EB20.
- UICmnds.cpp after UICmnds202 (zero bytes; build/class-work/UICmnds202, NOTES CORRECTION): 0x6F7B80 and 0x6F7EC0 are
  exact only when the list builders 0x6F6AD0/0x6F69F0 are declaration-only; in the whole-population TU VC6 expands
  them at these first call sites (7B80 grows to 752 B). The original expands them in 0x6F79C0/0x6F7800/0x6F7020/
  0x6F71E0 but calls them here: explain with the Study152 depth-first budget (VC6_MATCHING_NOTES) in the full plan TU.
  0x6F79C0 53.70 (registers). True ends: 0x6F7360 682 B (ret 0x6F7609), 0x6F6D00 to 0x6F6FD4, 0x6F81B0 >= 741 B.
- MainOpt.cpp / LoadDlg.CPP after MainOpt203 (build/class-work/MainOpt203/w, NOTES): Main_Options_Dialog 0x542460 98.91
  (w/d3.cpp uses an `OptionsClass *options = &Options` local that is borderline steering; 97.30 without), Video_Mode_Proc
  0x543CF0 66.37 (registers), Has_Saved_Games 0x53C5C0 97.83 (mov al,bl after pop edi). Undrafted: Main_Options_Proc
  0x542590 (1996), 0x542D60 (1909, IPX card dialog), Set_Display_Mode 0x5434E0 (1414), 0x53B770 (2068), Fill_List 0x53C040.
  The scorer can report 100 with a wrong constant (0x79C570 is double 0.1): trust check_plans.
- House.CPP after House204 (build/class-work/House204/w, NOTES): Random_Cell_In_Zone 0x4ECA50 53.51 (1276 B with fill
  and table; clamp head, case order and quadrant bitfield write match; left: bitfield store/reload as movsx word, case-0
  x/y swap, Cell ctor 0x42AD30 out of line in the original, frame 0x34 vs 0x44). +0x5640..+0x5650 is BaseClass
  unknown_50/unknown_54, +0x15F44 an int grid pointer. Map 0x568D60 returns Cell by hidden pointer.
- Session.CPP after Session205 (zero bytes; build/class-work/Session205, NOTES): dtor 0x66EB20 byte-exact (d/r1, 50/50
  accepted) but the full build fails "Function symbol ambiguous/missing: _$E2" after the UnknownSessionState header
  additions (CCFileClass RecordFile +0x2304, two NodeNameType lists, ~UnknownSessionState, ~MessageListClass) - cause
  unknown. Ctor 0x66E380 98.59 (w/ctor_best.cpp, inc_a: three-instruction scheduling diff; needs six inline DVC ctors,
  unknown_geometry_l and a long @ref set). 0x673090 disassembled only.
- UICmnds.cpp after UICmnds206 (build/class-work/UICmnds206/w, NOTES; score with ws.py): 0x6F81B0 99.60 (pop ebp
  before the 0xAC132C store), 0x6F7360 61.57 (needs 0x6F6C90 retyped to DynamicVectorClass<char const *> const & and
  moved out of population-1642 by a rename spec; then 0x6F76C0 calls it, both exact), 0x6F79C0 58.10, 0x6F7020 77.52,
  0x6F71E0 73.33.
- MainOpt.cpp after MainOpt207 (build/class-work/MainOpt207/w, NOTES): Main_Options_Proc 0x542590 84.05 (two register
  gaps), Main_Options_Dialog 0x542460 98.91 without the local once 0x5DA360 is renamed to OptionsClass::Unknown_005DA360()
  (rename not delivered; push 0 scheduling left), Has_Saved_Games 0x53C5C0 97.83. Undrafted IPX proc 0x542D60; 0x53B770 is
  LoadOptionsClass::Process and Fill_List 0x53C040 (LoadOptionsClass: Windows scope).
- House.CPP after House208 (build/class-work/House208/w, NOTES): AI_Building 0x4E9660 99.42 (w/bld_best.cpp; needs
  VECTOR_IMPLEMENT_DYNAMIC_INSERT_AFTER in VECTOR_IMPLEMENT_ALL - whole-tree --build check for new COMDATs - and a
  4-argument BaseNodeClass ctor; left: store order of `BaseNodeClass copy = *node`). Not started: 0x4E90F0 (production
  driver, after AI_Building), Place_Object 0x4E6950, 0x4E77F0 (MPlayer_Defeated-like).
- UICmnds.cpp after UICmnds210 (build/class-work/UICmnds210, NOTES; parked): 0x6F81B0 99.60 (pop ebp slot), 0x6F7360
  48-62 (needs 0x6F7610 retyped from population-1641; original calls 0x6F6790 out of line), 0x6F58E0 exact alone but
  defining it makes 0x6F6D00 inline it; 0x6F7020/0x6F71E0: our functions keep more inline budget at the end than the
  original - one shared cause to find. Score in the whole TU (ws.py).
- Session.CPP after Session209 (build/class-work/Session209, NOTES): its ren1 (CDFileClass statics moved into an invented
  nested SearchList holder) is REFUSED by the owner: RA's CDFILE.H has them as direct CDFileClass statics. Honest route:
  split UnknownSessionState (with CCFileClass RecordFile) out of unknown_globals.hpp into its own header included only by
  units that use the session, then land the dtor 0x66EB20 (exact, d/r1). Ctor 0x66E380 98.59 (~280 store orders tried;
  idea: 0x2C0-0x2EC or 0x638-0x63A is a nested struct with an inline ctor/clear); 0x673090 Allocate_Ports 87.47.
- TAction.CPP after TAction211 (build/class-work/TAction211/w, NOTES): iron curtain 0x6B26D0 96.34, reveal 0x6B1050 92.11,
  waypoint sound 0x6B0EC0 85.07 (esi/edi), show text 0x6B0440 92.86. Not started: 0x6AFD80 (755), Execute 0x6ADAE0
  (7.3 KB switch). Type debt: 0x6B2400/0x6B2860 cast `(AbstractClass *)&Map[coord]` because map_cell.hpp's stand-in
  CellClass does not derive from AbstractClass.
- NullDlg.CPP after NullDlg213 (build/class-work/NullDlg213/w, hdr/, NOTES): Select_Serial_Dialog 0x5CDF00 83.17 (2567 B;
  structure, frame, jump table and inline budget match; left: UpdateWindow/ShowWindow import pointers in swapped
  registers, cached zero in edi used in case 0x653). Landing needs Init_Null_Modem 0x5CEA30 moved from population-2402
  into the unit under its real name, Options.Seed as int in queue.hpp, SetCommBreak/ClearCommBreak, new phone_ed.hpp /
  serial_ed.hpp. Register-allocation work: Windows lead 2 queue. 0x5CFDB0 (31 B) lands with it.
- House.CPP after House212 (build/class-work/House212/w, NOTES; parked): AI_Building 0x4E9660 99.42 (original reads Type
  before the Cell store but stores Type after it; ~15 copy forms tried), AI_Raise_Money 0x4E90F0 87.22 (w/rm_best.cpp,
  overlay i6: the original keeps Factories.Vector in eax across the Suspend/Abandon/delete loop, loading before and
  reloading after the delete - same blocker as 0x4E8D80 and the function near 0x4F4128; only `if (Factories[f]) delete
  Factories[f];` reproduces it in tests, with an extra null test). Place_Object 0x4E6950, 0x4E77F0 not started.
- TAction.CPP after TAction215 (zero bytes; build/class-work/TAction215, NOTES; parked): Execute 0x6ADAE0 69.14 (body_bytes
  7752 = 7284 code + 117-entry table at 0x6AF754; case order and member map recovered in w/exec2.cpp; shape `bool success
  = true; ... case N: success = member(...); break;`; blocked by the /Ob2 budget: ours also inlines 0x6B1270, 0x6B19A0,
  the timer Stop and CDTimer ctor and runs out at case 55, the original at case 74 - members likely cost more to inline in
  the original; exact member rewrites in w/r_*.cpp). 0x6AFD80 49.66 (one function; same budget pattern).
  Execute needs seed take-overs 0x6B0540 (pop-148), 0x6B1AC0/0x6B1AE0/0x6B1AF0 (pop-88).
- Session.CPP after Session214 (build/class-work/Session214/w, NOTES; parked): ctor 0x66E380 98.59 (w/ctor1.cpp; +0x63A and
  +0x2C4 stores out of order; HEAD's unsigned short[8] loop works for 0x3022; needs unknown_geometry_l binding and inline
  DVC ctors), Allocate_Ports 0x673090 87.47 (rotated registers). Session state is now in src/shared/session_state.hpp.
- SerialEd.cpp after Scenario216 (build/class-work/Scenario216/open, NOTES): Fill_Port 0x66D5A0 71.93 (this/SendMessageA
  ebp/ebx swap; original pushes all four callee-saved registers in the prologue), Read_Custom_Port 0x66DB50 83.04.
  Clear_Scenario note: the inlined check is unsigned (cmp esi,0x802; jae) while the loop test is signed (jl).
- Small units after Small217/Small218 (build/class-work/Small217, Small218, NOTES): Options_Menu_Proc 0x4DD8A0 86.53 (first
  latency timer ctor inlines; original calls 0x4DE1E0), LdPrgMgr 0x5359E0 61.74 / 0x535AB0 69.16 (registers), WorldDom
  Mouse_Move 0x768840 64.00 (soviet block before allied). Startup.CPP is WinMain 0x68E280 (~10 KB, EH frame) and shutdown
  0x6909E0 (2345 B): each needs its own lane. LdPrgMgr 0x535BF0 is one 3978 B function (inventory splits it).
- Init.CPP after Init219 (build/class-work/Init219, NOTES, d/r2-blocked): 0x5173C0 command registration (7807 B) and four
  template rows (DVC<CommandClass const *>::Add 0x51E360, IndexClass<int,CommandClass*> Add_Index/Remove_Index/Is_Present)
  are exact only with wwlib VECTOR.H's `T & operator[](int)` and `(*this)[ActiveCount++] = object` in Add; that header
  change makes WDT Conflict::Init_Options 0x727480 inline rc_ptr<FlagGameOption>'s dtor and the build fails: needs a
  whole-tree impact study (lane Vector223). Select_Game 0x5135F0 is 4516 B with a 40-entry table (inventory stops before
  it); Init_Game 0x5116A0 (4420) not drafted.
- Skirmish.cpp after Skirmish222 (zero bytes; build/class-work/Skirmish222/misses, NOTES, score in the unit with sc.sh):
  0x683FC0 97.43 (shape 100; the slot loop's strength-reduced pointer starts at Slots[1][1] in the original, ours at
  Slots[1][0]), 0x6829F0 78.89 (the original calls Skirmish_Is_Computer 0x6836B0 in the player-type case; ours inlines it).
  LdPrgMgr 0x535BF0 (3978 B) not started (disassembly Small218/o_535bf0.s).
- Queue.CPP after Queue225 (build/class-work/Queue220, Queue225 NOTES; 0x62DBA0 and 0x62CF40 landed; Queue220's literal
  refusal was a stale check, wrong @ref literal names pass ws.py but fail acceptance). Print_CRCs 0x62A360 (11,223 B)
  outlined in Queue225 NOTES. Queue_AI 0x623770 exact only with
  static Queue_AI_Multiplayer 0x623B00 (3355) in the unit plus the Next 0x62E9E0 seed take-over (pop-42).
  Extract_Compressed_Events 0x6282D0 43.24 (registers/frame), 0x629220 82.05.
- WorldDom.cpp after SendFile221 (build/class-work/SendFile221/NOTES.md, misses/768c70): Faction_Select_Dialog 0x768C70
  82.11 (Load_Image static helper and three named image members zeroed in the init list fix the dtor inlining and vptr
  order, so header and dtor 0x768800 change together; remaining: register arguments set before the stack pushes).
  0x768E90 (1272 B state machine) not started, needs ctor COMDAT 0x769790 in the plan; Mouse_Move 0x768840 64.00.
- Vector forms after Vector223 (build/class-work/Vector223/NOTES.md, impact.py): Westwood Add/ID landed (r1, zero impact).
  int operator[] still moves BaseClass::Get_Building 0x42C0A0 (99.20, lea operand order) and WDT Conflict::Init_Options
  0x727480 (rc_ptr<FlagGameOption> dtor inlines); HouseClass 0x4E68D0 has a natural fix. Init 0x5173C0 99.48 under r1.
- ownrdraw.cpp after OwnrDraw224 (one TU 0x5DE660-0x605F30, build/class-work/OwnrDraw224/NOTES.md, c/): 0x5E1640 89.80
  (original jumps from the kind 0x94 test into the 0x72B compare, no stored bool), 0x5E8BA0 67.67 (parent width before
  `test bl`, dx in ebp; six placement siblings share it).
- Init 0x5173C0 after Init227 (zero bytes; build/class-work/Init227/NOTES.md, u/): a one-call-wide inline budget
  window. Unsigned operator[]: 99.48, exact only with 6 extra out-of-line calls; int operator[]: exact, but WDT
  Conflict::Init_Options 0x727480 drops to 73.75 (sixth rc_ptr<FlagGameOption> temporary's dtor inlines). Get_Building
  0x42C0A0 is exact under both headers with `BaseNodeClass const &node = Nodes[index]; Cell cell = node.Cell;`.
- Queue.CPP after Queue228 (zero bytes; build/class-work/Queue228/NOTES.md, u-misses/): Print_CRCs 0x62A360 (11,223 B)
  92.24, shape 99.84; needs MonoClass::Clear 0x59E290 and Set_Cursor 0x59E240 declared out of line with the Mono
  population taking over their transliterated rows (re-check ctor 0x59E190, View, Text_Print). Remaining: frame slot
  order and register allocation in the map-layer/logic loops. Queue_AI group not started.
- ownrdraw.cpp after OwnrDraw229 (NOTES, c/, s/): tooltip-label switch 0x5E22B0 71.54 (original is one else-if chain
  with a shared `return 0`), EnumChildWindows callback 0x5E8720 51.12 (original keeps Bucket_Index 0x602020 and Get
  0x601710 out of line inside the inlined 0x5E12A0/0x5E1CA0).
- Startup.CPP after Startup226 (NOTES): WinMain 0x68E280 (SEH __try/__except, 10,080 B) not drafted; 0x68DC70, 0x68E040,
  0x68E0AD, 0x691450 open.
- Event.CPP after Event231 (zero bytes; build/class-work/Event231/NOTES.md, w/best.cpp, hw/shared): EventClass::Execute
  0x4B65C0 (4994 B, table inside padding: body_bytes) 54.41, shape 94.10, call sequence identical. Remaining: register
  roles (original this=esi, (char)House=ebx, house=edi), frame 4 bytes short (slot at 0x10), then scheduling. Landing
  moves EventClass(int, unsigned char) 0x4B5FD0 from population-2913 into Event.CPP; slot 268/259 casts need a rename.
- Startup.CPP after Startup232 (NOTES, w/wm_b.cpp, out/): WinMain 0x68E280 25.98, drafted through OleInitialize plus the
  Main_Game __try. Needs acceptance-tool SEH support first (see HANDOFF), a TClassFactory<T> inline ctor in
  class_factory.hpp for the 74 registrations, and the 0x6983E0 IUnknownPtr dtor bound by @ref.
- ownrdraw.cpp after OwnrDraw233 (NOTES, s/, c/): 0x5E8720 51.12 (only Bucket_Index inside 5e12a0's Find differs in
  inlining: the original has more pending inline sites; frame 0x94 vs 0x90), 0x5E8BA0 68.66, 0x5E1640 90.53 (one
  cross-jump). 0x600260 drafted but has no inventory row.
- wonline.cpp after Wonline230 (one TU 0x73A6F0-0x7683B0, NOTES unit table): seven dictionary static destructors
  0x73AB20.. 98.95 (load order at the shrink-loop bottom); their exact initializers land only with them (initializer
  table contiguity). WolStringArray::Remove 0x7661F0 85.88. b29828 string array needs a rename (extern int Count).
- wonline.cpp after Wonline236 (NOTES slot map, c/): CChatEventSink OnSetTeam 0x765430 90.63 (two stack slots swapped),
  OnPagedUnicode 0x762C20 90.78 (ebp saved only in the dialog branch; 0x757CC0 result in ebx).
- Seed sweep after Sweep235 (build/class-work/Sweep235/NOTES.md, scan_atexit.py, rank80.txt): only 28 unaccepted rows
  score >= 85 (1.2 KB), mostly static-object _$E pairs; recover them by defining the real global with its real class.
  IsoTileType 0x529120 + VectorClass<unsigned short*> ctor 0x52ED90 exact alone but make Load 0x52E1C0 inline the ctor
  (57.89); ProgressScreen pair 0x61ECA0/0x61ECC0 ctor inlines into the initializer. Unexamined >=85: 0x5AADD0 95.45,
  0x7291C0, 0x732AA0, 0x6AAD40, 0x63F047.
- Init.CPP after Init234/Init238 (NOTES, gen.py/mix.py list every tried form): Select_Game 0x5135F0 (4516 B, 93.08 is
  the scorer ceiling) misses by one instruction pair in two draft families: Init234/u (single `started` join: original
  `jne 0x513E55` at 0x513E6B vs our cross-jump) and Init238/w/best_select_game_q.cpp (RA per-arm Dialog checks: modem
  code exact; only the while(process) back-edge reload order `or edi,-1; mov esi,1` differs; reshape the internet case
  and the case 16/17 switch). Its session_state edits rebase on Init238 r1. Init_Game 0x5116A0 (4420 B) not drafted.
- ownrdraw.cpp after OwnrDraw237 (NOTES, v4/, c/): 0x5FDF40 75.78 and 0x5FE020 47.47 (blue channel from a register copy
  of color in the original; 0x5FE020 also needs a rename: int return, ECX surface, EDX text, retypes 0x536D30). 0x600460
  exact only as an inline (needs an out-of-line caller). The 0x200 record is modelled three ways (UnknownControlRecord,
  UnknownListOwner_00600350, UnknownNodeList_006003d0): merge by rename spec. Population-1646 fails as one composite.
- netdlg2.cpp/netshare.cpp after Netdlg240 (NOTES unit table: netdlg2 0x5BBB20-0x5C29B0 has 7 large fns / 17.8 KB left,
  all plateaus; netshare 0x5C29B0-0x5CDB40 23 fns / 25 KB; nullconn.cpp 0x5CDB40-0x5CDD10). Its netshare plan was
  refused: LobbyNameSet Shrink/Grow wrapper functions under auto_inline(off) (the original inlines Grow_Table in
  Save_List_Selection). Misses: Save_List_Selection 0x5C5FF0 94.01, 0x5C34F0 97.37, 0x5CB560 7 bytes off.
- CampScor.cpp and neighbours after CampScor241 (NOTES: CampScor.cpp is population-2954, 0x465A00-0x467B3D, now complete
  except Presentation 0x466A50 98.98 - cached GetDlgItem/EnableWindow register tie, vp/p0.cpp + inc/ overlay).
  UnknownCargo Attach 0x468960 45.87 (per-flag bool stores). UnknownTechno230 still declares the two renamed
  CaptureManager methods (drop in a header batch). Seed 0x468140 (5 B) unclaimed.
- ownrdraw.cpp after OwnrDraw242 (NOTES: the 0x5F0F40-0x5FC8A0 area is 15 real control window procs, map in NOTES):
  progress bar 0x5FAFF0 86.15 in the unit (exact alone: unit context swaps esi/edi; score drafts with tux.sh), hot key
  proc 0x5FC330 98.12 (inlined BSurface ctor loads height before width in the original), Edit helper 0x5F2120 86.03.
  0x5F3CF0 has no inventory row; 0x5F42D0/0x5F0F40/0x5F3CF0 need the 0x5FE020 rename; seeds for 0x5F1900/0x5F0F40 are
  unusable. EgoClass_Draw_004b3690.cpp still declares 0x5FE1B0 locally.
- ObjectClass-derived holdouts after Objects246 (zero bytes; build/class-work/Objects246/NOTES.md inventory of all
  remaining Bullet/Anim/BuildingLight/Overlay/Particle/VoxelAnim/Veinhole/Team members): nearly all are recorded near
  misses. New: BuildingLightClass::AI 0x433970 71.88 (bl/ai5.cpp; CoordStruct ctor 0x41B630 out of line in the original
  inside the inlined 434530->434610->operator- chain), BulletClass::Detach 0x461520 74.38. Fresh large targets: Bullet AI
  0x45F710 (6438), Anim AI 0x421710, Team AI 0x6B7AD0 (3222; needs Foot/Techno slot declarations, coordinate with Windows).
- wonline.cpp after Wonline244 (NOTES): OnPublicGameOptions 0x761890 66.78 in the population (/Ob2 inlines
  Unknown_0074DA60, the original calls it; atexit 0x765980 + guard go with it), deleting dtors 0x765A60/0x765AC0 and
  ctor 0x765AA0 come from the unaccepted create-game dialog proc near 0x7459A0, OnLadderList 0x75D330 87.38.
  Special_Dialog_00481850.cpp declares Unknown_0073C230 locally as cdecl (it is __fastcall).
- Display hierarchy after Display245 (NOTES: 17 open members, 19.2 KB; class_inventory double-counts inherited slots):
  ScrollClass edge autoscroll 0x669EC0 82.07, PowerClass::Draw_It 0x61C8C0 89.69, RadarClass 0x62F310 90.22, 0x633000
  87.43, GScreenClass::Get_Input 0x4E09D0 82.81. Cell sums written as the member `AdjacentCell[f].unknown_42add0(cell)`
  load the table operand first like the original.
- netshare.cpp after Netshare247 (zero bytes; NOTES, c/, t/us.sh scores in the whole unit): Lobby_Dialog_Proc 0x5C69E0
  63.75 (four static helpers reproduce the 0x583/0x497 inline decisions; the 0x6EB case still inlines the local
  DynamicVectorClass ctor/Add the original calls; landing moves 0x5C7160 from population-2392 into netshare and renames
  MultiplayerGameMode slot 3 to take WideString*). 0x5CBF20 43.42 (the refusal path keeps `previous` on the stack in the
  original). 0x5C3FF0 (7,887 B) not started.
- wonline.cpp after Wonline249 (NOTES, c/, todo.txt; most inventory bounds in this TU are false splits): 0x744930 98.44
  (or eax,-1 before the pops), 0x73C480 96.05 and 0x75C980 89.19 (lea ecx before push eax: implicit conversions
  reproduce it), 0x73CB80 needs WolUserArray::Get inline (row 0x766020 in population-2411), 0x752210 static Wstring[16]
  table + atexit 0x752710. Not reached: OnPrivateGameOptions 0x761C50, OnUserList, OnFind, OnChannelJoin (2.3 KB+ each).
- Inline-rule application after Inline252 (zero bytes; NOTES, spend.py/stores.py/probe.py): Init 0x5173C0 needs caller S
  +21..27 under unsigned operator[] (int operator[] is exactly +46 via Add's conversion; Init_Options then needs a form 3
  units smaller); named locals shrink S here. PlanMgr 0x617AF0 90.00 needs ~100-190 more budget spent before the help
  calls (most promising). TAction Execute: 6b1270/6b19a0 are over the non-inline cap in the original (wordier sources);
  case bodies differ too. UICmnds 6D00 95.53. WDTSel ctor: maybe inline Wstring/WideString dtors in the original headers.
- Techno/Foot after TechFoot253 (NOTES lists every unrecovered Techno/Foot function with size and best score): 0x6D65B0
  87.83 (frame 8 bytes larger: slot 22 result buffer unshared), slot 223 0x6D5F40 52.75 (needs rename to
  void(CoordStruct const *, float)), 0x6C3950 69.29 (exact only with two more waiting inline sites after the second
  divide; source unknown). Slot 200 casts arg3/arg4 (really AbstractClass*; rename touches Aircraft 78/200 and two
  Building sources). Untried: 0x6C4BB0 range test, slot 251 0x6D5510, voxel draws 0x6D24E0/0x6D2810/0x6D21E0/0x6D1D00.
  Check the value behind every __real constant name (0x3F747AE1_58000000 is 0.002f*2.5).
- Display hierarchy after Display254 (NOTES, v/, inc/shared): ScrollClass 0x669960 98.59 (original keeps a branch with
  two epilogues; ours goes branchless; needs Unknown84E8D0::Unknown_0042E860 rename to take CoordStruct by value), edge
  scroll 0x669EC0 82.07, PowerClass::Draw_It 89.69, RadarClass 0x62F310 90.22 / 0x633000 87.43, GScreen 0x4E09D0 82.81,
  Sidebar slot 33 0x681ED0 64.89. Guarded statics: take the atexit thunk's seed row over with a stub source and read
  _$E<n>/$S<n> names from a compile of the concatenated unit.
- CellClass after Cell255 (NOTES unit map, false splits listed): 0x47C080 92.00, ctor 0x470F10 86.43, Spread_Tiberium
  0x478A40 85.84 (needs pending/cell255-ren1.json and 0x478950 ending `if (OccupierPtr != 0) return false; return true;`),
  0x47BFA0 64.29, 0x4755D0 61.54, 0x471660 60.23, 0x47BB30 59.78.
- Jumpjet after Loco256: Loco256 r3 refused (Process 0x52F3C0 used an empty inline `unknown_state_6() {}` to keep a jump
  table entry); Loco259 redoes the round without Process. Misses 0x530B00 85.56, 0x530180 91.69, Move_To 0x52F600 34.85.
- VQAClass after VQA257 (NOTES: span 0x717CE0-0x71DC10 is three TUs: quaternion/Matrix3D facing 0x717CE0-0x71C31F,
  VQAClass 0x71C320-0x71DB1F population-2639, option bits 0x71DB20-0x71DC0F own population): buffer stream callback
  0x71CA00 39.47 (count in edx, ebx pushed only around memcpy, position in edi; case 1-4 block first).
- Ini.CPP after Ini258 (NOTES unit map; mk.py states bounds, RETIRE= for retired rows): Save(Pipe) 0x50C620 98.57, Put_Unicode
  0x50ECF0 91.82, Load(Straw) 0x50BC30 84.36 (lands with CacheStraw dtor 0x510AD0), Get_Unicode 0x50EDF0 83.33 (frame
  0x5028 vs 0x5014). Follow-up rename: CampaignINI::Get_Wide_String -> INIClass::Get_Wide_String (0x50F010).
- Locomotion after Loco259 (NOTES; Ship and Drive are one source): Jumpjet 0x530B00 85.56 (frame slots only), Ship
  Piggyback_CLSID 0x6756D0 81.73 (com_ptr attach model), slope matrix 0x675A60 70.37, Will_Jump_Tracks 0x67AA10 82.67.
- Score.CPP / UndoInfo after Score260 (NOTES, usc.py): Efficiency 0x666040 98.33, Draw_Cursor 0x6672A0 83.00,
  ScoreDelay 0x667420 77.54 (Rect ctor 0x42BCD0 out of line in the original).
- Facing/ramp TU after Matrix261 (0x717CE0-0x71903F; NOTES): 0x718060 (3,290 B) 88.27 (/G5 scheduling only), 0x718E80
  96.15. Renegade WWMath is not in the sparse reference checkout (adding it is a fetch: needs the user).
- Score.CPP after Score264 (NOTES): ScoreDelay 0x667420 77.54 (our Blit_Score is just over the auto-inline cap; exact
  if unknown_surface_839954 were Surface*), Efficiency 0x666040 98.33. Presentation 0x663FE0, DVC<ScoreAnimClass*>::Add
  0x6684F0, UndoInfo 0x685290+ not started.
- Voxel library after Voxel265: 0x71BAA0 86.55, 0x71BF20 63.39 (true body 665 B); drawers/Read_File/Render_Shadow to do.
- Ship/Drive after Loco263: Draw_Matrix 82.25 (one Value call out of line in the first expansion only), Process 77.65
  (CDTimerClass(long) 0x463F80 out of line in Set_Slope), Piggyback_CLSID x5 (com_ptr.hpp attach model).
- VeinholeMonster after Vein270 (NOTES, u.cpp, w/u_best.cpp, w/hdr_best): Load_All 0x711E60 99.21 (body_bytes 740),
  Build_Growth_Queue 0x7115B0 98.39 (two stack slots), Draw_It 0x710880 81.32, dtor 0x70FDF0 66.91, AI 0x710250 64.19
  (body_bytes 1480; timer ctor 0x463F80 out of line inside Graphic_Logic). Rules->unknown_d4 read directly, not via inline.
- Voxel library after Voxel267 (NOTES, hdr/ overlay): Render_Shadow 0x719C10 78.11 (frame slots only; needs
  UnknownVoxelRecord48, unify with the globals unit 0x716F10's struct), Read_File 0x719160 73.61 (header retypes, frame
  0x13c vs 0x120, unsigned palette loop), lighting drawers 0x71AD30 81.84 / 0x71AFA0 88.58 (normal byte spilled to a slot).
- Event.CPP after Event271 (zero bytes; NOTES, w/best.cpp, hw/shared): Execute 0x4B65C0 54.41 -> 90.74 with TibSun shape
  (::Frame vs member Frame, function-level locals, one bool foot slot, session fields, House as char). Only the TIMING
  then-branch differs: original (MaxAhead + rate) + Frame - 1, ours (MaxAhead + Frame) + rate - 1.
- TAction.CPP after TAction272 (NOTES, w/, hdrx/hdry/hdrz overlays): Execute 0x6ADAE0 70.32 (CellClass+0x140 bridge flags
  as bitfields make Execute call 6b1270/6b19a0 like the original - a tree-wide header change over 79 files; CDTimerClass
  Is_Active() for the timer actions; set_house members bigger than the inline cap in the original; Execute also needs rows
  0x6B3230 and 0x6B32C0). Show text 0x6B0440 92.86, waypoint sound 0x6B0EC0 85.07, iron curtain 0x6B26D0 96.34, damage
  0x6AFD80 49.66.
- Path estimator after Span273 (zero bytes; NOTES, w_*): Apply_Path_Collision_Avoidance 0x4285D0 97.31, Cut_Corners
  0x428AE0 97.44, Get_Movement_Cost 0x427110 97.04, Optimize_Moves 0x4290C0 60.09, Try_Diagonal_Shortcut 0x428CF0 63.38
  (0x42ADD0 member-sum copy is unaccepted; byte-exact from the shared body once a unit emits it).
- Locomotion after Loco269: Fly Stop_Moving 0x4BC730 96.82, Hover Draw_Matrix 0x4FBBF0 95.80, Rocket Move_To 59.32.
- Event.CPP after Event278 (Execute and seven ctors landed 3bdf9770): MEGAMISSION_F ctor 0x4B61F0 (136 B, not even a seed)
  97.67 (one store [esi+0x1B] scheduled after +0x17; Event278/w, plan-r2.json). Execute keeps hypothesis casts on slot
  259/268 and (BuildingClass *) until a rename spec retypes them. Event.CPP's header-static source now includes the unit's
  full include list after its geometry includes (include order decides Execute's inline accessors).
- Span 0x775B60-0x781FF0 after Tail277 (NOTES table): ABuffer.cpp done; VQA32 library 0x776380-0x77EDD0 in files audio,
  buffer_, config, drawer, dstream, loader, task, timer, unvq (TibSun code/vqalib/ is the reference); 0x77EDD0-0x781572
  handwritten MASM (AudioUnzap, LCW, sosCODEC, ASM_UnVQ, cpuid/rdtsc: separate ledger, ~9.6 KB); linker thunks; CRT.
- Session.CPP after Session275: MultiMission(INIClass&) 0x671670 97.39, map reader 0x6707D0 95.30, ctor 98.59,
  Allocate_Ports 87.47; Read_Scenario_Descriptions 0x670C50 and Read_MultiPlayer_Settings 0x66F3A0 not drafted.
- Locomotion after Loco276: Fly Move_To 0x4BC3E0 54.77 (IFlyControl comip model in hdr/), Tunnel Stop_Moving 0x6EFDE0
  77.31, Tunnel Process 0x6F0000 79.16; Fly Stop_Moving 96.82 and Hover Draw_Matrix 95.80 unchanged.
- VQA loader after VQA281 (NOTES, w/loader.cpp): Load_VQF 0x779E90 withheld (its VPKZ case used an invented second copy
  Load_VPKZ of the VPTZ reader: refused; 83.69 without it), LoadFrame_Internal 0x778950 85.52, Load_MFCI 83.47,
  Load_MSCI 78.10, Load_CBPZ 96.77.
- Init.CPP after Init279: Draw_Loading_Screen 0x516560 99.63, 0x516E70 97.62, Select_Game 93.08 (scorer ceiling),
  Allocate_Surfaces 0x519500 77.26; Init_Game 0x5116A0 and 0x519E70 not drafted.
- VQA task.cpp after VQA280: plan refused because VQA_Open wrapped a call in `#pragma inline_depth(0)` copied from TibSun
  (a reconstruction pragma is not evidence; VQA285 redoes it). VQA_Reset 0x77C7D0 71.6 (register choice).
- Session.CPP after Session282: Read_Scenario_Descriptions 0x670C50 94.54 (true body 2142 B; only the wcsncat count
  fold `0x2B - used` vs inc/mov 0x2C/sub remains; needs 5+ pending inline sites after the INIClass), ctor 0x66E380 98.59,
  Allocate_Ports 0x673090 87.47.
- VQA task.cpp landed via VQA285 (the inline_depth pragma was not needed). VQA_Reset 0x77C7D0 75.68 (stop in esi).
- VQA unvq.cpp after VQA284 (NOTES, w/; joined rows need body_bytes through the final ret + bound_evidence, tails under
  allow_split): UnVQ2_C0_4x4_TRANS 0x77D940 95.52, UnVQ2_C4_4x2 0x77D5B0 86.84 (VC6 chains the 0x2000 masked block in
  place), UnVQ2_C0_4x2_TRANS 0x77E5B0 85.59, UnVQ2_C4_4x4 0x77D0C0 74.04, UnVQ2_C0_4x4_KEY 50.60; 0x77E1A0 and 0x77E9E0
  not drafted. Load_CBPZ 96.77 (VC6 canonicalises the address sum). VQA library parked (slow register hill-climbs).
- Init.CPP after Init283 (Init_Game landed 4a7917ca). Owner judgement: Init_Game calls empty file-static Init_Heaps and
  Init_Threads; Init_Heaps is a real static called at that point in Westwood's RA INIT.CPP (RA2's heaps are dynamic, so an
  empty body is plausible); Init_Threads is only in TibSun. Accepted as evidenced source, not empty steering calls.
  Init_Theater 0x519E70 77.74 (register allocation), Draw_Loading_Screen 99.63, 0x516E70 97.62, Select_Game 93.08,
  Allocate_Surfaces 77.26, 0x516F00 95.15, Init_Rules 45.98, 0x5173C0 (7807) not started.
- ownrdraw.cpp after OwnrDraw286: push-button proc 0x5F42D0 70.01 (frame slots; map in NOTES), progress 0x5FAFF0 76.92 in
  file context, Edit helper 0x5F2120 86.03.
- Scenario.CPP after Scenario289: Fill_In_Data 0x65CDD0 99.18, Clear_Scenario 0x65D370 99.66 (jge vs jae), Wait_For_Players
  90.40, Scan_Place_Object ~48.6, NoInit ctor 64.00. Rules.CPP: AudioVisual 0x643E10 ~48; Sides 0x64BC10 matches only with
  a DynamicVectorClass::ID/Count() header change (Vector223 found Count() adds a COMDAT in 144 units: owner decision, held).
- UnitClass after Unit288 (NOTES, map.txt): Explode 0x6FD3A0 99.33, Read_INI 0x706AE0 99.15, Desired_Load_Dir 0x704730
  68.92, Mission_Harvest 0x7025A0 76.70 (draft has steering: rewrite from TibSun). Slot 260 0x7053F0 is 5651 B with no
  inventory entry. By-value arguments fixed operand order (file-local operator< and Unit_Adjacent_Cell).
- Tactical.CPP after Tactical290: caption/timer drawer 0x6A5280 99.18, ctor 0x6A24B0 99.02, Render_Fogged_Objects
  0x6A3D00 59.46 and Render_Terrain 0x6A4350 51.05 (Coord_Snap CoordStruct ctor 0x41B630 out of line in the original),
  Register_Dirty_Area 0x6A3020 29.40 (second Union out of line); 0x6A9F50 take-over exact, lands with 0x6A3D00.
  The original inlines less here: helper sources are wordier (Inline293 studies it).
- ownrdraw.cpp after OwnrDraw292 (NOTES, c/, hdr/ overlay): Edit proc 0x5F1900 96.47 (which copy of the shared
  SetWindowLongA tail VC6 keeps), NewEdit 0x5F22A0 57.91, tab proc 0x5F0F40 42.51 (Bucket_Index out of line at 0x601C30),
  progress 0x5FAFF0 76.92, push-button 0x5F42D0 70.01. Static/ScrollBar/trackbar/ComboBox/ListBox not started.
- Scenario.CPP after Scenario291: Clear_Scenario 0x65D370 99.66 (jae vs jge on the inlined unknown_6612c0 range check:
  VC6 types the derived induction variable signed), Wait_For_Players 90.40, Scan_Place_Object 48.62 (try a FacingType
  enum with operator++), NoInit ctor 64.00. TeamClass 0x6B8BB0 still has a local extern of 866160 (scenario_tags.hpp).
- UnitClass after Unit294 (zero bytes; NOTES, w/, o/mh.asm): Explode 0x6FD3A0 99.33, Read_INI 0x706AE0 99.44 (bridge height
  is 0xAD057C), What_Action 0x703BD0 63.20 (no gotos; edi/ebp swap, frame 0x14), Desired_Load_Dir 68.92. Mission_Harvest,
  Per_Cell_Process, Assign_Destination need the inline COM query model (ComPtr297); Tunnel_AI needs FootClass::unknown_575
  signed char, out-of-line CoordStruct operator- 0x4348F0 with UnknownVector3::Length 0x41B780 as one type; Draw_It needs
  a slot 67 rename (Point2D const &, Rect const &).
- Map.CPP after Map295 (one TU population-3061; NOTES unit table): exact but blocked Local_Sector_Index_To_Cell 0x55AE50
  ("Unsupported independent bound"), crate-near-cell 0x54E580 (bound), Is_Same_Cell_Zone 0x54F7C0 (bool 5th param rename);
  misses Pick_Random_Location 0x559EB0 44.83, Closest_Edge_Cell 0x5689D0 46.64, In_Local_Radar 0x55A590 56.16.
- COM pointers after ComPtr297 (zero bytes; NOTES, model/shared): a faithful VC6 comip.h model of com_ptr.hpp (every member
  in-class; layered _QueryInterface/Attach/_Release/_AddRef; checked operator->) keeps 14 of 18 COM populations exact and
  makes the Unit/Mission_Harvest inline query natural. Four accepted functions inline more under it: FootClass::Load
  0x4C9D10, Aircraft 0x416420, Infantry 0x507530/0x500350 (ComPtr299 re-matches them). VC6 COMIP.H/COMDEF.H/COMUTIL.H were
  extracted read-only from the user's VS6 ISO into the ignored toolchain media folder.
- CellClass after Cell296 (NOTES): Draw_Overlay_Shadow 0x474830 exact once Overlay_Draw_Offset 0x475440 stays out of line
  (its real source is over the auto-inline cap; no natural form found) - unblocks 0x474EB0, 0x475100, 0x4749C0; Init_Light
  0x479440 needs inline Point2D::Length + take-over of 0x47D060 (population-1905); Bounce_Direction 0x479AC0 95.49;
  Cell_Render_Rect 0x4752B0 needs the real IsometricTileTypeClass slot 39; Init_Drawer rename (LightConvertClass*) pending.
- Tactical after Inline293: Register_Dirty_Area 0x6A3020 35.48; Render_Shroud 0x6A3EF0, Wipe_Depth 0x6A33F0 not drafted.
  Adding any member to CellClass broke the full build in another unit (repro in Inline293 NOTES).
- COM pointer model after ComPtr299 (zero bytes, parked by the stop rule; NOTES, v/in, unit/, model/): 15/18 COM
  populations exact under the comip model. Infantry: callers 0x507530/0x500350 become exact by calling 0x508D00 (TibSun
  Is_JumpJet) in model form, but 0x508D00 itself is 78.57 (success-path Attach->_Release inlines; 1-3 extra pending sites
  after the ctor fix it). Foot Load 0x4C9D10 85.41 (needs >=3 more sites after OleLoadFromStream), Aircraft 0x416420 63.48
  (1-2 more sites after Link_To_Object). Find the natural missing sites, then land model + overlays in one round.
- Map.CPP after Map298 (NOTES, w/, hdr/): Set_WasUnderBridge_Flags 0x568B00 58.10 (first Adjacent_Cell sum out of line
  0x42ADD0, ours calls the Cell ctor 0x42AD30 out of line: /Ob2 budget); Closest_Passable_Cell 0x568ED0 82.98 (inner-loop
  registers); Map295 misses 559EB0 44.83, 5689D0 46.64, 55A590 56.16. Undrafted: 549C20 (needs 549C50 signature), 5658C0,
  54A8F0, 5651E0, 567AE0, 55B060, destroy-bridge twins 551470/551810/551DD0, 5502E0 (2570).
- CellClass after Cell301 (NOTES): Draw_Overlay 0x4749C0 62.74 (needs CellClass +0x68 as Rect, slope-shape table 0xA52EB0
  conflicts with unknown_globals.hpp's single pointer; register allocation left); Init_Light 0x479440 83.65 (frame 0x2c vs
  0x3c, one shared CoordStruct slot; Point2D::Length takeover probably unnecessary); Closest_Free_Spot 0x4764B0 undrafted.
- Tactical after Tactical300 (NOTES, w/): Render_Shroud 0x6A3EF0 96.25 (moved-rect Y first); Get_Selectable_Object
  0x6AA990 90.07 (stack slots); Register_Dirty_Area 0x6A3020 65.58 (needs bool rename first; second Union inlines); ctor
  0x6A24B0 99.02. Inline members added to rect.hpp broke another unit's full build for Tactical300 (not bisected), yet
  Cell301's Point2D operator+/+= landed exact.
- FootClass after Foot302 (NOTES, w/): Can_Reach slot 102 0x4C8730 98.31 (one load scheduled late); Mission_Guard_Area
  slot 130 0x4C5900 83.70 (Delete 0x454B20 must stay out of line; needs 0x4CE210 re-owned from population-19);
  Mission_Hunt slot 132 0x4C48E0 80.95; Draw_Action_Line 0x4CAB90 74.06 (one Rect slot too many). Seeded: slot 78 0x4C61A0.
- Map.CPP after Map303 (NOTES): 0x549C50 (1,208 B, TibSun Sight_From) EXACT in unit context but declaring DisplayClass slot 38
  0x49A0F0 / RadarClass slot 37 0x62FCA0 in map_view.hpp breaks another unit's full build (unit unknown; header saved as
  map_view_with_slots.hpp); destroy-bridge twins 0x551470/551810/551DD0/5521A0 69.08 (/Ob2 budget, like 568B00); 5502E0 undrafted.
- FootClass after Foot304: undrafted 0x4CB110 Execute_Waypoint_Path 1465, 0x4C3000 Basic_Path 2246, 0x4C3950 2174,
  0x4C4C30 Approach_Target 3279, 0x4CBB40 1467; Foot302's misses unchanged.
- FootClass after Foot305 (NOTES; overlays hr, hb): Basic_Path 0x4C3000 91.99 (needs MapClass::Unknown_005502E0 arg8-11 as
  bool, a rename over 18 callers; then block-1 register allocation); slot 102 98.31; 0x4C4C30 (3279) and 0x4CBB40 (1467,
  needs DiscreteDistributionClass and the unit's COMDATs 0x4CE710/0x4CEA90/0x4CEAF0/0x4CEB30) undrafted.
- Header cleanups unblocked by Hdr306 (no byte credit, full builds passed at 55325943): Point2D::operator/(int) into
  rect.hpp (c2/hdrA + c2/w/6a33f0.cpp), Rect::operator+= (c2/hdrB), CellClass::Fetch_CellID member (c3/hdr).
- TechnoClass (Techno320 NOTES, 0 bytes): slot 248 health bar 0x6C3F00 40.61/85.8 shape (rename spec ren/techno320-ren1.json retypes slots 248/249; operator/ ctor goes out of line only with ~16 more pending inline sites), 0x6D7D20 Should_Use_High_Arc 89.87/100 shape (operand load order), 0x6CA340 96.08.
- BulletClass (Bullet322 NOTES, 0 bytes): Draw 0x4610D0 98.55 (w/draw_best_98.91.cpp, two scheduling diffs), AI 0x45F710 (6438 B) 43.37 first typed draft (frame 0x150 vs original 0x198; stack-slot map in NOTES; hdr/ overlay bullet.hpp additive). Shrapnel 0x462C50 is Windows near-miss work.
- AnimClass (Anim323 NOTES, 0 bytes; second zero handback after Anim162, unit parked): 0x4237B0 Next_Flaming_Guy_Coord 93.56/100 shape (needs a cell-left adjacent helper under its own name, not RA2_ADJACENT_CELL), ctor 0x420110 97.36 (Center_Coord Z register only). Not started: 0x423120 Flaming_Guy_AI, draw 0x420E50, AI 0x421710.
- OverlayClass (Overlay324/375 NOTES; unit otherwise complete; parked after Overlay375): Mark slot 71 0x5DA970 (true body 3251 B, ret 4 at 0x5DB620) 98.61 honest best (Overlay375 w/best_mark_member_sum.cpp, member Cell sums; rows 0x350/0x416/0x7DC/0x844 look like compiler context, untried levers in NOTES) (w/best_mark_ts_helper.cpp, 11 rows; the 99.07 two-helper draft is steering). Residue: 16-bit Cell addition operand order in the two low-bridge copies. Landing needs the atexit thunks 0x5DB660/650/640 taken over from population-67 seeds and a 1-byte row 0x5DB630.
- Particle family (Particle325 NOTES, best/): Fire AI 0x60C7C0 97.07 (only TargetCoord's 12-byte copy from the out-of-line 0x41B630 temporary differs: needs the coord.hpp CoordStruct(int,int,int)/UnknownVector3 identity question settled, owner decision; a reference cast reaches 98.17 but is not source), ParticleClass ctor 0x608440 91.21, Spawn_Particle 0x60B2D0 82.98 (edi/ebx swap), slot 67 0x609D10 66.55, Smoke AI 0x60BB70 38.32; Spark AI 0x60B670 is 1277 B (inventory split at operator new). Smoke/Spark: original calls DVC<ParticleClass*>::Add 0x60D050 out of line at the spawn sites.
- AircraftClass (Aircraft321 NOTES; r1-r3 landed 3,055 B): Good_Fire_Location 0x418F10 99.21 (alt.Y load order), Select_Landing_Destination 0x4185B0 79.51 (frame 0x4C vs 0x44), radio 0x418840 93.01, render 0x4141C0 90.30; not attempted 0x415790 slot 221 (with helper 0x41B6E0 97.14) and 0x4178A0 slot 126. Re-score inside the whole unit (splice.py): the r1 auto_inline(off) on 0x41B630/0x41B780 changes inlining there.
- TeamClass AI 0x6B7AD0 (Team331 NOTES, w/TeamClass_AI_006b7ad0.cpp, chk.sh): 91.32 at LEN=3460, all code instructions match in a lone compile; last whole-population check missed only the AI row (reason unread). Needs Team331 ren1 (bool handlers, queued), team.hpp handler decls + Timer_Value, Team327 r2, 0x6BD990 taken over from population-42 (allow_split), the 0x6BADC0 if/else rewrite, @ref for the debug string 0x7F6DC4. d/r1 there is an unfinished draft folder: do not land. Other handlers: 0x6BDAA0 95.67, 0x6BD240 93.13, 0x6BCBB0 88.06 (needs house.hpp decl, codex4), 0x6BB5F0 85.10 (needs techno.hpp UnknownCargo::How_Many), 0x6BE010 76.32, 0x6BE440 65.81.
- Init.CPP after Init328 (NOTES; unit 0x5116A0-0x51DA28 otherwise accepted): Init_Theater 0x519E70 99.68 (TS min(12 + s/prog_step, 25) through Westwood's min template, needs a shared home for it plus Init283's color_scheme.hpp addition; last push/mov ecx order), 0x516E70 97.62 (same order inside inlined 0x517370), Allocate_Surfaces 0x519500 71.67 (DSurface ctor int third parameter rename). Lesson: re-score plateaus after their blockers land.
- ownrdraw.cpp after OwnrDraw330 (NOTES, h1/ overlay): Draw_Dialog_Back 0x5FEE70 81.90 and dialog setup 0x5FF7E0 41.71 are inline-budget misses (the original calls Bucket_Index/Get out of line at later lookup sites; the TU setters likely use Get, not Find); BitFont text draw 0x5FE1B0 57.93 (needs od330-ren1); 0x5FFB00, 0x600830 not started. Owner note: "inline sites that cost nothing" would be steering (LANE_BRIEF), so the next idea must be real source.
- BuildingLightClass (Light332 NOTES; second zero handback after BLight150: parked): ctor 0x432FC0 73.59 (needs one natural inline site after the second Coord_Along_Facing in 0x4341D0, plus the ID(this) loop register swap), AI 0x433970 78.68 (frame slots; four invented helpers), slot 67 0x433380 54.51.
- OWNER DECISION (coord.hpp): whether CoordStruct gets an out-of-line (x,y,z) constructor (0x41B630) and Length (0x41B780), or TS's separate Coord type (UnknownCoord434820 with conversion). Blocks Particle Fire AI 0x60C7C0 (97.07), BuildingLight slot 67 0x433380 and likely its ctor; see coord.hpp's 0x41B630/0x434820 note and the Aircraft unit's auto_inline(off) rows.
- AircraftClass after Aircraft329 (NOTES): Fire_At slot 221 0x415790 94.29 (frame 0x64 vs 0x6C, needs a bullet.hpp BulletVelocity::Get_Pitch member decl for helper 0x41B6E0, which is 87.32 with the 4-byte UnknownFacingDir vs Air146's 97.14 with a 2-byte direction: owner decision on the direction type), render slot 67 0x4141C0 91.41, slot 126 0x4178A0 not attempted.
- VeinholeMonsterClass (Vein333 NOTES; second zero handback after Vein270: parked): Load_All 0x711E60 99.21 (push ebx before lea ecx), Build_Growth_Queue 0x7115B0 98.39 (facing/node spill slots), Draw_It 0x710880 81.32, dtor 0x70FDF0 68.38, AI 0x710250 64.19 (timer ctor 0x463F80 goes out of line only under a tighter inline budget). AI needs `bool Unknown_005680A0(Cell const &, int)` in map_view.hpp (codex3's header). The older "0x711D20 85.71" entry is stale: 0x711D20 is accepted.
- RadarClass after Radar334 (NOTES): Plot_Radar_Background 0x631600 99.14 (needs RadarClass +0x1244 as Rect, h3/; ctor 0x62EDE0 then needs unknown_1244(0,0,0,0), exact in w/dede0.cpp), Resolve_Radar_Point 0x632AA0 98.10 (real signature void (Point2D const&, Cell &, TechnoClass *&)), slot 29 0x630840 89.43, slot 53 0x62F310 90.22, 0x634670 75.33 (true body 758 B). Not drafted: dialog proc 0x6340F0 (+0x634310), 0x630B70, 0x632000, 0x633210, RTacticalClass::Action 0x62FE30.
- ownrdraw.cpp OwnrDraw326 r2 (2,251 B: 0x5FD290, 0x5FE7C0, 0x5FF430 + header inline Blend_Color with two function statics) is NOT landed: accepted 113/113, but the full build then refuses UnknownMapGenerator 0x587CF0 (and 0x589AC0) "DIR32 not at original operand boundary" for unknown_map_random_a705c0, reproducibly (both lanes saw it too). Map generator does not include the header; suspect the inline function's statics (COMDAT .bss) shifting data symbol resolution. OwnrDraw330 r1 (0x5FE490, 806 B) depends on r2 and is held with it. Init328 r1 (Parse_Command_Line/Init_Rules, 3,244 B; session_state.hpp bit-fields, win32_api.hpp DialogBoxParamA) hit the SAME refusal (0x589AC0+211 DIR32 for unknown_map_random_a705c0) after its 103/103 acceptance, so the cause is likely in the map-generator rows' fragility (landed through codex1 r343-r373), not in either round: any new population/data may shift it. Next owner: reproduce on HEAD + Init328 r1, read the refusal against the map generator object, fix there; then reland the three held rounds (private/tools/landing-queue-held.txt).
- Power.CPP is complete except PowerClass::Draw_It 0x61C8C0 89.69 (Power338 NOTES, w/a0.cpp; the x-shift ternary must be computed in eax then copied to ebx; ~80 variants tried; untried: an int-width conversion VC6 keeps, or another type for id_source.hpp unknown_2239). PowerClass's other open vtable slots are inherited Radar/Display/Map bodies.
- RadarClass after Radar335 (NOTES; r1 Plot_Radar_Background queued): Compute_Background 0x630B70 95.56 (true body 1746 B, body_bytes; needs rename w/ren1-prepared/spec.json to Rect (Rect const&, Rect&, bool) and Westwood's min template in a shared header), Resolve_Radar_Point 0x632AA0 98.10 (header copy only, h5), Plot_Radar_Pixel 0x632000 74.03 (frame 0x30 vs 0x20). OWNER DECISION: a shared home for Westwood's `template<class T> T min(T,T)` (also needed by Init_Theater 0x519E70 99.68).
- AircraftClass after Aircraft336 (NOTES; slot 126 0x4178A0 queued): render slot 67 0x4141C0 91.41 (scheduling only), BulletVelocity::Get_Pitch 0x41B6E0 87.32 (original writes the word straight into the hidden return slot; bullet.hpp decl in hdr/), Fire_At 0x415790 94.29 (lands only with 0x41B6E0). Direction type decided: 4-byte UnknownFacingDir (Dir_To_* read 32 bits; slot 126 matches with it).
- FRAGILE ROWS (Dir337, 2026-10-31): UnknownMapGenerator Generate_Rural_Buildings 0x589AC0 and Generate_Urban_Buildings 0x587CF0 match only for some counts of earlier declarations in their TU (k unused externs: Rural fails k mod 64 in 3..8, Urban 9..11). Any header addition seen before them can break the full build (spill/reload placement in the 60-try loop shifts a reloc by 7 bytes). codex1 asked for a residue-independent shape; until then rounds that trip it are held (private/tools/landing-queue-held.txt) and retried after each HEAD change. Placement games to dodge it are steering.
- Tab/Scroll/Mouse after Scroll346 (NOTES, v/; Mouse.CPP complete; other open vtable slots are inherited Display/Radar/Map bodies): Tab 0x6A1880 97.30 (flag stores sink below the vtable load), 0x6A1AB0 88.10 (/Ob2 budget: 0x6A1270 inlined 5x vs 4x; 0x6A20C0 ToolTip() copy follows it), Scroll 0x669650 63.85 (needs tactical.hpp Unknown_006AA990), 0x669EC0 82.07 (this in esi vs edi).
- Tactical.CPP after Tactical342 (NOTES; ren2 + r1 Register_Dirty_Area queued, with an additive vector_elements.hpp DirtyAreaStruct ctor accepted by the owner): next is Render 0x6A45A0 (3,288 B, TibSun Render, no known blocker); then the projection family 0x6A27A0/0x6A29D0 (unblocks Draw_Overlays 0x6A7350 79.10, Draw_Placement 0x6A5670, Draw_Objects 0x6A93F0, Setup_Trigger_Scroll); Pixel_To_Cell 0x6A6BD0 44.11 needs 0x6A2900 taken over from population-2850; 0x6A7E80 needs cell.hpp lines (0x47CB50 bool, +0xFC PixelFXClass *).
- OWNER DECISION (user, 2026-10-31: retry, then retire): codex1 r405 retires Generate_Urban_Buildings 0x587CF0 (1,029 B) and Generate_Rural_Buildings 0x589AC0 (1,081 B) back to scaffolding (2,110 B less credit) so the held rounds can land; callers in populations 3187/3189/3192/3234 bind them by original address. Both return to codex1 as open misses (former sources under codex1 d/r405/misses): any landed shape must be residue-independent (Dir337 REPORT, build/class-work/Dir337/REPORT.md).
- RadarClass after Radar344 (NOTES; r1 Fetch 0x634C10 + Radar335 r1 queued): Compute_Background 0x630B70 96.19 (Westwood min template only for surf_right/surf_bottom, the rest is the always.h MIN macro; Radar335's rename spec needs rebuilding), Resolve_Radar_Point 0x632AA0 98.10, Plot_Radar_Pixel 0x632000 74.03, slot 29 0x630840 89.43, slot 53 0x62F310 90.29, 0x634670 75.33. Undrafted: dialog proc 0x6340F0 (one body, 1395 B, 0x634310 is inside it), Render_Radar 0x633210; RTacticalClass::Action 0x62FE30 needs map.hpp/declaration lines (codex3 holds map.hpp). Lanes' check_plans copy the owner's uncommitted landing state: run lane checks between landings when possible.
- Type classes after Types347 (NOTES; Aircraft/InfantryType complete; r1 UnitType ctor 0x70A600 + Get_Voc_List 0x50B610 queued): BuildingType Get_Draw_Rect 0x45E290 + Get_Frame_Rect 0x45ED50 (~1.3 KB) 98.65 after Types349 (w/bt/e5.cpp, w/hdr; one Union compare register swap left; family parked after Types349's zero handback) with shape_file.hpp additions (ShapeFileFrameStruct::Get_Rect, ShapeFileStruct::Get_Count: owner-accepted as additive, verify other Get_Frame_Rect users with the full build); TechnoTypeClass::Load 0x6DE260 99.64 (ebx/ebp), UnitTypeClass::Read_INI 0x70AB40 49.87, Damage_Smoke_Offset 0x6DF6C0 60.00.
- Display339 r1/r2 (Constrained_Look 0x49E1D0, Center_Map 0x49E3B0, Help_Text 0x49E610; 1,340 B) are held for a rebase onto Display343 r1: with their coord.hpp/map_cell.hpp/display.hpp changes the full build also refuses UnknownPathEstimator 0x428370 ("Complete compiler extent differs at +f0", the Hdr306 type-count-sensitive row; its unit includes cell.hpp -> coord.hpp). Next Display lane: rebase them, bisect which header addition flips 0x428370. Display343 also left Read_INI 0x49CFD0 (rename + Straw takeovers), Calculated_Cell 0x49A700 (bool rename; vector_class member definitions decision), Mouse_Left_Up 0x49B0F0 (no blocker).
- CellClass after Cell345 (NOTES, w/; r2 queued, 1,516 B): Bounce_Direction 0x479AC0 95.49, Spread_Tiberium 0x478A40 85.84 (renames 478ba0/47c3a0/478a40), Cell_Techno 0x471660 70.86 (take over Point2D::Length 0x47D060 from population-1905), Is_Near_Tunnel_ES/NW 0x479F70/0x479CF0 64.34/46.30 (inline budget), Occupy_Down 0x473B30 38.63; Incoming 0x476920's threat parameter is really CoordStruct const & (rename of six callers). Blocked: tile-draw family needs the real IsometricTileTypeClass instead of the map_cell_view.hpp stand-in; 47cc10/47c930 need the COM pointer model.
- OWNER DECISION (2026-10-31, reversible): CoordStruct::operator/ may become an inline member in coord.hpp (TibSun `(coord - bestc) / (n - 1)`) with Techno row 0x6D9770 kept as the out-of-line copy its unit emits (no accepted region calls it). This replaces Display339's Quotient stand-in, which with += and /= tipped UnknownPathEstimator 0x428370 (count effect, Display350 bisect), and makes Center_Map 0x49E3B0 exact with `sum / n`. Lands only if the full build stays exact; codex3 holds the Techno population and is told.
- DisplayClass after Display350 (NOTES; r1 Constrained_Look + Help_Text on Display343 r1 queued): Mouse_Left_Up slot 46 0x49B0F0 59.86 (with the verified +0x11C8 RGBClass WaypointColor header change; merge of duplicate Set_Default_Mouse blocks across the two switches; cell in ebx), Read_INI 0x49CFD0 not started (map_view.hpp Read_INI_0049CFD0 is codex3's).
- Tactical.CPP after Tactical348 (NOTES; r1 projection family 0x6A27A0/0x6A2870/0x6A29D0 + Setup_Trigger_Scroll queued after Tactical342): Render 0x6A45A0 41.62 (global register allocation; needs house_screen.hpp +0x1EC CDTimerClass<FrameTimerClass>, techno.hpp unknown_list_a40c20, super.hpp SuperStateStruct +4 unsigned __int64); merging population-2850 into Tactical.CPP's 3242 accepts 58/65 (drop 0x6A9170's redeclared extern; Wipe_Depth and six Render_* passes inline 0x6A27A0 which the original calls out of line: the next blocker, gating Draw_Overlays 62.31, Pixel_To_Cell, Draw_Placement, Draw_Objects). Pending rename round: 0x6A27A0 Coord_To_Pixel_Absolute, 0x6A29D0 Coord_To_Pixel, 0x6A2CB0 Setup_Trigger_Scroll, 0x6A45A0 Render.
- BulletClass AI 0x45F710 (6,438 B) after Bullet352: 59.05 (w/ai_best_59.05.cpp, hdr/), frame 0x180 vs 0x198; main gap: VC6 copy-propagates the two new_velocity copies the original keeps (TibSun TVelocity3D shape in hdr4/ brings back one; hdr4 changes BulletVelocity used by 10 accepted files: whole-population checks first). ~2.5 h of its 4 h time box used. Shrapnel 0x462C50 53.52/66.76, Draw 0x4610D0 98.55.
- CellClass after Cell351 (NOTES; r3 queued after Cell345 r2): the large unrecovered Cell function around 0x4770xx-0x4786xx carries five of the bit-0 spill sites (VC6_MATCHING_NOTES "Dead byte spill"); Init_Light 0x479440 83.65 (frame), ctor 0x470F10 86.43 (bitfields?), Bounce_Direction 0x479AC0 95.49, Spread_Tiberium 0x478A40 85.84 (renames).
- DisplayClass after Display353 (NOTES; r1 Center_Map + Techno plan queued): Mouse_Left_Up 0x49B0F0 61.44 (both jump tables decoded; VC6 merges the duplicate 0x23 block the other way and never merges normal case 1 into the shadow 1,5 block; the is-techno bit tests store the masked byte to [esp+0x28]); Read_INI 0x49CFD0 waits on map_view.hpp (codex3). DisplayClass parked for Mac lanes until one of those has a new lever.
- BulletClass (parked: AI's 4 h time box used up, Bullet322/352/355 NOTES): AI 0x45F710 best structure w/ai_switch_u0db_ms80.11_hdr4.cpp (post-flight dispatch is a switch, TibSun bullet.cpp 764; judge by ms.py/calls.sh, diff_candidate's aligner desyncs), still new_velocity copy-propagated; Shrapnel 0x462C50 66.06 (frame 0xB0 vs 0xA8; Direction_Of target coord copies only X); hdr4/e6 change BulletVelocity (10 accepted users): whole-population checks first.
- Tactical.CPP after Tactical354 (NOTES; ren1 + r1 merge of population-2850 into 3242 queued, 0 new bytes): Pixel_To_Cell 0x6A6BD0 42.06 (27A0 out of line for the unused abspixel at first level), Draw_Fence_Placement 0x6A5D70 57.45, placement drawers 0x6A6010/0x6A6290 undrafted (share Fence's loop), Draw_Overlays 0x6A7350 needs cell.hpp 0x4749C0 (requested from Cell356), Render_Shroud 0x6A3EF0 needs alpha_shape.hpp Draw_In_Area, Render 0x6A45A0 41.62, Get_Selectable_Object 0x6AA990 90.07.
- Leaf classes after Leaves358 (NOTES, best/; r1 Wave Brighten_Pixel, Terrain Read_INI, Radio ctor queued; Smudge and Radio complete): Terrain slot63 0x6E4430 88.79, Wave Set_Laser_Pixel 0x721B00 84.72 (pack order), Wave Load 0x7221D0 79.67 (DVC(0,0) ctor 0x7246D0 must stay out of line), Draw_Laser 0x722CB0 43.47; not started Draw_Sonic 0x7225B0, Wave_Recalc_Affected_Cells 0x723360 (Lerp 0x7220C0 by-value rename first), Build_Wave_Shape 0x7238B0. Westwood's template min/max (JSHELL.H) is now needed file-locally in three units (Radar, Init, Wave): a shared header for it is a pending owner choice.
- CellClass after Cell356 (NOTES; r2 Bounce_Direction + Init_Light queued): ctor 0x470F10 97.98 (bitfield unions at +0x12C/+0x140 and unknown_118 0xFF; only lea edi / mov ecx order in two memsets; overlay hdrB not yet full-built), Spread_Tiberium 0x478A40 85.84, ZBuffer drawers 474260/474510 not started; Goodie_Check 0x476CC0 is ONE function of 6,545 B (+switch data, full extent 6,672 B, ret 4 at 0x47864E and 0x477721) holding all five bit-0 spill sites: a dedicated study, crate tables in NOTES.
- Sidebar.CPP after Sidebar357 (NOTES, w/us.py whole-unit scoring; r2 Blit 0x67D420 + 0x6822B0 queued; ~13.7 KB still open): slot 54 0x67E210 99.04 (row-count order), slot 34 0x6819A0 68.34, AI 0x67DC90 65.13, slot 33 0x681ED0 64.89, 0x67CA50 45.57 and Add 0x67C530 48.09 (depth-first inline budget: original keeps nested Deactivate out of line and expands 0x67C850), caption 0x682140 44.12; untried StripClass AI 0x67F050, strip draw 0x67F800, recalc 0x6802D0, SelectClass::Action 0x6809F0 (8.9 KB, TibSun shapes).
- Tactical.CPP parked after two zero handbacks (Tactical354 merge-only, Tactical359; NOTES): Render_Shroud 0x6A3EF0 95.62 (alpha_shape.hpp Draw_In_Area decl, overlay hs/; moved rect Y first), Get_Selectable_Object 0x6AA990 90.07 (real body 461 B), Wall drawer 0x6A6290 61.23 (original 0x6A27A0 goes through the TacticalProjection(int,int) ctor 0x6A2740: a Rectangular_To_Isometric shape on that ctor that keeps the Y store/reload is the next lever), Fence 0x6A5D70 57.45, Firestorm 0x6A6010 40.21 (this in ebx; body-size budget), Pixel_To_Cell 42.06, Render 41.62, Draw_Overlays waits on cell.hpp 0x4749C0 (in Cell356 r2, queued).
- CellClass after Cell360 (NOTES; r1 ctor, ren1 shroud/fog names, r2 Draw_Fog_Shape queued): Goodie_Check 0x476CC0 block map ready (18 crate cases, jump tables, offsets, five bit-0 spill sites, headers needed); 0x474260 Draw_Shroud_Or_Fog_Shape has an ebp frame and compares against both the dword at 0x79DAD0 and an immediate 0xFE: likely a C function with an __asm block (handwritten-assembly ledger candidate, owner to classify); Spread_Tiberium 0x478A40 85.84.
- Sidebar.CPP after Sidebar361 (NOTES, w/us.py; r1 StripClass::AI 0x67F050 queued): slot 34 0x6819A0 98.22 (rows order: original subtracts the 18/26 term before abcd64; same puzzle as the draw), strip draw 0x67F800 87.03 (structure matches; registers), slot 54 0x67E210 99.04, Recalc 0x6802D0 35.99 (inlines 0x67CA50: lands with or after it), SelectClass::Action 0x6809F0 untried. Needs house_screen.hpp unknown_4e3660 / unknown_func_4eb580 / Is_Build_Limited (codex4 asked) and staged super.hpp/sidebar.hpp lines (w/hdr).
- WaveClass after Wave362 (NOTES, best/; one zero handback; ren1 Lerp renames queued): Set_Laser_Pixel 0x721B00 95.83, Draw_Laser 0x722CB0 52.67 (frame one slot short), Draw_Sonic 0x7225B0 40.47, Load 0x7221D0 79.67 (three more Load-level call sites push the DVC(0,0) ctor out: source unknown); Wave_Recalc_Affected_Cells 0x723360 blocked on the coord.hpp decision (inlined Lerps call 0x434820); Build_Wave_Shape 0x7238B0 undrafted (static Vector3 WaveSize[3][4], guard 0xAF9140, atexit 0x7241F0).
- Goodie_Check 0x476CC0 (4 h time box used up: Cell364/366/369 NOTES; best Cell366 best.cpp + hdrbest366/): 89.32; only the static Adjacent_Cell 0x47CFC0 at 0x47710E is inlined where the original calls it (next idea: model it as TibSun INLINE.H's global inline whose out-of-line COMDAT copy is 0x47CFC0, defined after Goodie_Check; recheck 476AC0 too) (shape 98.18), out-of-line call sequence exact; solved: UnknownCellCoord(Cell) built in place (maybe the same class as coord.hpp UnknownCoord434820: owner call), money case first in source, Is_Techno/Is_Foot inline in abstract_class.hpp (owner-approved additive), Length3 TibSun TPoint3D::Length helper, heal Take_Damage last arg 1. Left: gas Adjacent_Cell 0x47CFC0 still inlined, temporary slot order in reveal/fire/money/napalm/loop. Landing needs the Goodie_Check(FootClass *) rename and codex3-held map/map_view/techno/foot lines (Cell364 entry).
- Container templates after Templates363 (NOTES, scratch/ scans; r1+r2 queued, 2,175 B): template rows go in new template-only populations (a later VECTOR_IMPLEMENT_* define does nothing inside an existing TU); ctors as explicit specializations with the generic body plus @ref bindings. Open: UndoInfoStruct Resize 0x687030 72.97 / 0x6871E0 77.98 (needs a different UndoInfoStruct shape); rows that need a caller first: 0x726FD0 (Campaign ctor 0x725F40), 0x72CF20 (0x72BEF0/0x72BFA0), 0x6C08D0 (Suggested_New_Teams 0x6BED50), 0x56C2E0 (Map 0x563D80), 0x605640 ??_E; 0x62EA00 element type unknown. Next scans: Add_Head / Add_After / NoInit / copy-ctor shapes.
- Sidebar.CPP after Sidebar365 (NOTES, w/hdr overlay; r2 slot 33 + caption printer queued): SelectClass::Action 0x6809F0 (3,083 B) 66.86 / shape 96.25 (block order via inline UnknownFactory::Is_Building(); registers: index*0x30 in ebx, id in edi; frame 0x9C vs 0xA0); strip draw 0x67F800 89.23; slot 34 98.22 and slot 54 99.04 share the rows puzzle (flag in al and the 18/26 term subtracted before abcd64; ~25 variants in NOTES). Action needs house_screen.hpp 0x4EB620, 0x4EB770, 0x4E7070 and Available_Money via IHouse +0x24 slot 6 (codex4 asked).
- Container templates after Templates367 (NOTES, scratch/; r1 landed 5f27ff2d; family exhausted within reach): JShell Fatal 0x52EE00 exact locally but refused (.CRT$XCU via queue.hpp's header statics: move Unknown_00691320's declaration to a light header such as exit.hpp, add _iobuf/vfprintf/_iob/stderr to crt_stdio.hpp); ~710 B of IndexClass<int,CommandClass*> COMDATs need the command-table setup (gap 0x5174C0-0x51923F) and keyboard handler 0x5406E0 recovered first; UndoInfoStruct Resize 0x687030 78.57 (time box spent); 0x595D60 needs MixFileClass made non-template (RTTI).
- Sidebar.CPP after Sidebar368 (one zero handback; NOTES, w/): strip draw 0x67F800 90.46 (SelectButton index `(row*2 + ID*15*4) + col` with ID*15 spilled; VC6 factors to 2*(row+ID*30)+col), slot 34 98.22, slot 54 99.04 (abcd64 in edi vs ecx: allocator state), Action 0x6809F0 66.98 (wants the real FactoryClass from factory_class_decl.hpp; early return 1 not tail-merged in the original). Rows-puzzle lead: `unsigned short extra` with the if/else reproduces order and registers but adds an and eax,0xffff. Next: 0x67C530 48.09, 0x67CA50 45.57, or close the unit.
- IPX/ConnMan after IPX370 (NOTES, v/; r1 landed ec9be1db, r2 Store_Stats queued): Start_Listening 0x523C80 60.32 (Open_Socket inlined: original loads the 16-bit Socket as a dword into esi, masks late), Receive_Packet 0x5243D0 80.65 (prologue: ebx/edi pushed after the magic-number early return), unknown_slot17 0x524870 98.50; undrafted: stats dump 0x526D90 (2,208 B, 16 swprintf + Fancy_Text_Printf blocks), Service 0x525F60 (2,691 B; structural map in NOTES, needs OwnerTalkClass 0x63FB60/0x63F840 declarations). Guard names of function statics: read them from a whole-population compile ($S56), not diff_candidate's standalone $S17.
- Command keys (Keys371 NOTES, w/k5.cpp; parked): Keyboard_Process 0x5406E0 (636 B, MainLoop.cpp, population-261) 29.59 natural: shape recovered, only inline decisions differ (Search_For_Node out of line at all three lookups, Is_Archive_Same inline at the first two); needs ~120 IL of real code before the lookups plus 1-2 later inline sites, source not found; command registration 0x5173C0 is ONE 7,807 B function (to 0x51923E), 99.48 (ScreenCapture's implicit ctor out of line). Their IndexClass COMDATs wait on them.
- AircraftClass parked (two zero handbacks, Aircraft341/372 NOTES): only Fire_At 0x415790 94.29 (call pattern exact only with ~13-16 extra pending inline sites after ROT0's Set_Yaw; Position_Coord_004f3f40 supplies 7 naturally; frame 0x64 vs 0x6C), Get_Pitch 0x41B6E0 97.14 (TibSun member form with Horizontal_Speed, exact for 0x41B750), render 0x4141C0 91.41 remain. Member form needs a rename making rows 0x41B750/7C0/7F0/830/860 comment-only COMDAT rows and whole-population Bullet/TAction checks.
- IPX/ConnMan after IPX373 (NOTES, drafts/; one zero handback): Multiplayer_Debug_Print 0x526D90 (2,208 B) 80.57 / shape 98.42: everything matches except the original walks the global arrays with pointers relative to this (VC6 does that only when the indexed member array is at offset 0; Connection is at +0x28: a source form is missing); Start_Listening 0x523C80 85.25 (Open_Socket int socket: a rename), slot17 98.50, Receive_Packet 80.65, Service 0x525F60 undrafted.
- CCToolTip (parked after Tip130/Tip376, NOTES): Show 0x46DFC0 98.95 (VC6 reassociates the sum; with a pointer chosen from global Rects it subtracts Width first, the original X first as for an opaque pointer: try a Rect pointer from a member/global/function), Debug_Print 0x46E250 73.20 (left kept in edi; try an inline Rect/tagRECT builder).
- ownrdraw.cpp after OwnrDraw377 (NOTES; r1 0x5E9F00 queued): 0x5FF7E0 99.60 in the TU with every inline decision right (needs the TU setters 0x5EA230-0x5EAAA0 made inline Get-form, the out-of-class TibSun UnknownControlIndex::Get in a shared header checked against every TU user, and a name decision vs lobby.hpp's unknown_show_dialog_5ff7e0); one store order left. 0x5FFB00 is the common dialog handler (1,482 B incl. tables) 61.98, structure right, early sites get too much inline budget. Untouched: 0x600830, Static 0x5F2B50, ComboBox 0x5F4BA0, ListBox 0x5F6690, ScrollBar 0x5F9FB0, trackbar 0x5FB270.
- Near-miss pass NearMiss380 (NOTES, w/): no change on ten >=98% plateaus (all register allocation / scheduling): TechnoType Load 99.64, Init_Theater 99.68, Sidebar slots 54/34, Veinhole Load_All/Build_Growth_Queue (score with --length 740 / 1250), CCToolTip Show 98.95, Get_Draw_Rect 98.65, IPX slot17 98.50, Bullet Draw 98.55. Resume only with a structural idea (a real header type change or an inline found in Westwood/TibSun source), not spelling sweeps.
- FootClass after Foot379 (NOTES; r1 landed, r3 slots 132/130 queued; ~8.1 KB left): Basic_Path 0x4C3000 91.99 and Approach_Target 0x4C4C30 (3,279 B) wait on a codex3 rename of MapClass::Unknown_005502E0 args 8-11 to bool (asked); slot 102 0x4C8730 98.31; Draw_Action_Line 0x4CAB90 74.06 (needs foot.hpp decl, asked); 0x4C9FE0/0x4C6F10 need COM smart pointers. Owner accepted r1's file-local Tiberium_Value helper (a real call wrapper around Get_Tiberium_Value 0x47A230).
- Map.CPP after Map382 (NOTES; r1 landed, r2 Damage_Bridge + r3 Prune_Water/Get_Water_Mask queued; ~105 functions / 108 KB still open, unrec.py lists them; score inside the unit only): Get_Bridge_Zone_Connection_Cell 0x564F70 91.09, Find_Bridge_Span_End_Cell 0x5653C0 61.88, 0x565610 55.37, Place_Firestorm_Wall 0x56A480 62.82, Place_Wall 0x56A660 47.84 (map_techno.hpp stand-ins), Base_Region 0x550DC0 needs house_screen.hpp Which_Zone 0x4EAEF0 (codex4); next cheap: 0x55C2C0 (Build_All_Shores), 0x55C630 (Expand_Water), Firestorm_On_Path 0x569FB0.
- FRAGILE ROW (OwnrDraw381, 2026-10-31): Refresh_Wonline_Players 0x73FEE0 (codex2, population-3320) changes code after some owner_draw_dialog_control.hpp edits it does not use (adding a class or certain field splits + declarations; comments and renames are safe): a type-count-sensitive row like 0x428370. TU test in OwnrDraw381 NOTES (99.30 good, 99.23 broken). codex2 told. ownrdraw.cpp after OwnrDraw381: 0x5FF7E0 99.60 (import-pointer load before the global store), 0x601C50 Remove untried, UnknownPairIndex::Resize 0x6022A0 exact but parked on the fragility; large procs (Static 0x5F2B50, ComboBox 0x5F4BA0, ListBox 0x5F6690, ScrollBar 0x5F9FB0, trackbar 0x5FB270) and 0x600830 not started, seeds in s/.
- netshare.cpp after Netshare383 (NOTES, t/us.sh; r1, ren1, ren2, r2 queued; wol_chat.hpp is a pure move out of codex2's wol_sink.hpp): Options-string parser 0x5C3FF0 (~8 KB, sections mapped in NOTES, draft from t/3ff0.txt) not started; 0x5C7570 81.51 (frame 0x258 vs 0x1F4: the tail CCFileClass temporary doesn't share the case buffers' slot), 0x5CAE00 46.15, 0x5C67C0 91.87 (LEN=414), 0x5C5FF0 94.01, and unretried 0x5CA6C0 85.84, 0x5C71F0 87.67, 0x5C7EF0 73.91 (IChat slot 15 now available).
- netshare Receive_Game_Options 0x5C3FF0 (8,191 B; Netshare385 NOTES, c/3ff0.cpp; ~1 h of its 4 h box used): 64.58 (loose 80.10, shape 94.67, 2491/2495 instructions), all sections drafted; whole-function misses: register allocation (original esi=text, ebp=sender, ebx=copy, edi constant 0) and frame 0x3D8 vs 0x390 (slot map in NOTES).
- netshare 0x5C3FF0 after Netshare387 (zero bytes; NOTES, c/best.cpp 64.86, c/frame128.cpp structural base with receiver[128] frame 0x374 vs 0x390; t/lab.py, fmap.py, regs.py, slots.py): second zero-byte handback, STOP RULE applies. Entry `xor edi,edi` is the ternary-flags zero; any real Z section blocks it (our Z1 keeps copy in edi across the loop; original reads it from [esp+0x28]). Frame: VC6 reuses a slot only for objects <=2x its current size. Inline budget: original calls 0x40E160/0x40E180 out of line, ours inlines them and calls Unlink. Resume only aimed at a Z1 copy-from-stack form.
- Map.CPP after Map384 (NOTES; r1-r3 queued as r3, 4,101 B): every later Map.CPP plan must keep the header-static rows 0x55CBC0/0x567CC0 at symbol_prefix _$E63/_$E67 (a `new X[n]` of a class with a ctor uses an $E number). Open: Place_Shore 0x55CEF0 84.78 (block layout), Get_High_Ground_Mask 0x55BD70 18.44 (inline-budget gradient). Next: 0x54E8D0(+0x54E9C2), dispatchers 0x556BF0/0x556E30, twins 0x5576A0/0x5579C0 and 0x557CE0/0x558010, 0x55DCA0/0x55EDB0, 0x569B60(+0x569DAD), 0x567490(+0x56751B).
- ownrdraw.cpp after OwnrDraw386 (NOTES, c/, s/, plans p/; r1 landed, r2 queued): 0x5E9FA0 18.99 shape 100 (lookup node/key in swapped scratch registers), 0x601C50 Remove (needs 0x6027E0 Shrink row and the 0x600350 Release class settled), 0x5E7EB0 (Bucket_Index 0x602020 row), large procs 0x5F2B50/0x5F4BA0/0x5F6690/0x5F9FB0/0x5FB270 (seeds need Ghidra-type to real-type conversion and --length), 0x5FF7E0 99.60 (try the __fastcall callee probe). Findings: pointer-countdown fill loops give rep stosd/adc/rep stosw; an inline template max `a < b ? b : a` flips operand order where always.h's form does not.
- Map.CPP after Map388 (NOTES, w/, fix.py; r1 queued: 0x567490, 0x569B60): Close_Object 0x54E8D0 natural best 50.59 (a probe with one extra empty inline call after the second Distance gives 97.67, so the original has one more pending inline site there; needs CoordStruct Length; its local static takes $S57/$E58 = row 0x54EBC0 and shifts 0x55B520/_$E61, 0x55CBC0/_$E65, 0x567CC0/_$E70); destroy-low-bridge family 0x5576A0 51.67 (w/5576a0b.cpp; 0x5579C0, 0x557CE0, 0x558010 same shape, ~3.2 KB: loop counter in the dead argument slot, frame 0x34 vs 0x30); 0x556BF0/0x556E30 (TibSun Repair_Low_Bridge_Span shape) need member thiscall Cell::operator- (COMDAT 0x56AA40, X first) in coord.hpp. Check_Map declares MovementZoneNames (0x7D1A68) locally because ccini_extra.hpp cannot be included in the Map unit.
- netshare after Netshare390 (NOTES, c/, t/bytes.py, t/odis.py; r1 exact 0x5C67C0, 0x5C71F0, 0x5C7570, 0x5CA6C0 = 3,707 B): 0x5C5FF0 94.01 (c/s1.cpp; only the `name` and spilled loop-index slots swap, 10 variants listed; lands with Grow 0x5CDA50); 0x5C7EF0 75.82 (c/w3.cpp, c/w2.cpp; frame exact with function-scope `char options[256]`; ours keeps zero in ebx where the original keeps 0x1C7 through both loops, and the NAT/IP blocks and Z3 send land at the end; needs WolUnknownIdentifier and unknown_identifier_a71b18 moved from wol_sink.hpp 395-396 into wol_chat.hpp, a pure move requested from codex2); 0x5C3FF0 parked; 0x5CAE00 46.15 not retried.
- ownrdraw.cpp after OwnrDraw389 (NOTES, c/, tu.sh, op.py; ren1 + r1 exact 0x5FF7E0 796 B): 0x5FFB00 54.19 (c/5ffb00a.cpp, --length 1482; inline budget reversed: ours inlines WM_PAINT Bucket_Index/Get and the 0x84 case's 0x5E2100 and leaves unknown_prepare_dialog out of line; case bodies follow case-value order, inline decisions follow source order); trackbar 0x5FB270 48.74 (c/5fb270s1.cpp, --length 3504, TibSun TrackBarCtrlProc shape, state at record+0xE8..0x108); 0x5E9FA0 18.99 shape 100 (c/5e9fa0i.cpp, swapped scratch registers in the inline lookup; when it lands, 5FF7E0's local `unknown_5e9fa0(HWND)` becomes `unknown_mark_control_5e9fa0(unsigned int)`); progress bar 0x5FAFF0 86.15. Never mark the setters inline. Static 0x5F2B50, ComboBox 0x5F4BA0, ListBox 0x5F6690, ScrollBar 0x5F9FB0 not started.
- OWNER DECISION (2026-10-31, fragile row): adding `Draw_0068cce0` to UnknownBitmapWriter in pcx_cache.hpp flips Refresh_Wonline_Players 0x73FEE0 (99.30 -> 99.23). The trackbar 0x5FB270 and push-button 0x5F42D0 need it, so declare it in a unit-local ownrdraw header (owner_draw_bitmap.hpp, a free/extern declaration of the same 0x68CCE0 symbol), which 0x73FEE0's unit never includes. Reversible: move it into pcx_cache.hpp once the 0x73FEE0 sensitivity is understood.
- Near-miss pass NearMiss392 (NOTES, t/; 5 exact = 2,512 B): unchanged after convention probes: Presentation 0x466A50 98.98 (CampScor241/vp/p0.cpp; GetDlgItem/EnableWindow cached-import register naming), Draw_Loading_Screen 0x516560 99.63 (Init328/u), UICmnds 0x6F81B0 99.60 (UICmnds210/w/81b0e2.cpp; pop/store tie after operator delete), Select_Game 0x5135F0 92.40 (Init238 w/best_select_game_q.cpp + NearMiss392/hsg; back-edge `or edi,-1; mov esi,1` order). No convention lever (member/import/variadic callees): 0x666040 98.33, 0x6B0440 92.86, 0x5C01D0 98.94, 0x53C5C0, 0x65C520.
- Map.CPP after Map391 (NOTES, w/, labs/; r1 exact 0x5576A0/0x5579C0/0x557CE0/0x558010 low-bridge family + 0x559EB0 = 3,322 B): Destroy_Low_Bridge_Span 0x556BF0 65.37 (w/bfq1.cpp with HDR=labs/m0 and w/il1.cpp for 0x562930) is an /Ob2 inline-budget miss: the original keeps everything inline except the final `cell - Cell(1,0)` (COMDAT 0x56AA40). Probes bracket it: caller ~90 IL units larger reproduces the call pattern; a plain-store Cell(short,short) ctor inlines everything. Same blocker expected for 0x556E30, 0x55DCA0/0x55EDB0 (Damage_Low_Bridge) and Map303's 0x551470 twins. 0x55A590 56.16 (w/ir1.cpp; 32-bit sum narrowed at the store wants an int-parameter Cell ctor); 0x568ED0 82.98.
- OWNER DECISION (2026-10-31, Cell arithmetic): COMDAT 0x56AA40 (14 Map.CPP callers) is the named member `Cell unknown_56aa40(Cell const &right) const` in coord.hpp (precedent unknown_42add0; a member operator- is ambiguous with the free operator- in Sight_From 0x549C50). Lanes may add it in their round overlay. The Cell constructor's IL cost (the ~90-unit budget gap) stays OPEN: do not change Cell(short,short) in shared coord.hpp without a whole-build check of every accepted Cell user; probe the cost in a lab first.
- ownrdraw.cpp after OwnrDraw393 (zero bytes; NOTES, c/, hb/, t/*.asm, tu.sh, dd.py, slots.py): Static 0x5F2B50 77.70 shape 93.74 (c/5f2b50s1.cpp with EXTRA 5de660=c/5de660v.cpp; --length 4512), ScrollBar 0x5F9FB0 66.69 shape 94.54 (c/5f9fb0i.cpp, HDR=hb; --length 4152), ComboBox 0x5F4BA0 (--length 6895) and ListBox 0x5F6690 (--length 14618) bounded but not drafted; push-button 0x5F42D0 70.01. Inventory fragments 0x5F31EA, 0x5F38CB, 0x5FA913, 0x5FAB5D, 0x5FADA7 lie inside these bodies; 0x5F3FAD belongs to 0x5F3CF0. The static needs row 0x5DE660 to define VECTOR_IMPLEMENT_VECTOR_ACCESSORS/DYNAMIC_ACCESSORS before its includes (whole-TU check needed). Findings in NOTES: dead Get local holds a frame slot; one function-scope POINT; cast before the null test; layout-order cases; colour bytes evaluate blue first; `#pragma intrinsic(log)`.
- OWNER DECISION (2026-10-31): the unit-local form of Draw_0068cce0 is OwnrDraw393's `class UnknownBitmapDrawer : public UnknownBitmapWriter { bool Draw_0068cce0(...); }` in owner_draw_bitmap.hpp, called through static_cast with an @ref to 0x68CCE0 (a free function cannot be thiscall). Explicit hypothesis; fold into UnknownBitmapWriter once pcx_cache.hpp can take it without flipping 0x73FEE0. Check 0x73FEE0 when it first lands.
- Convention pass NearMiss395 (NOTES, w/; 4,186 B exact): unchanged: TAction show text 0x6B0440 92.86 (w/ta0.cpp; Rules loaded into eax vs ecx), Find_Disk_Drive 0x715090 86.33 as __fastcall (w/cd_w_0_1.cpp), Bullet slot67 0x4610D0 98.91 (w/bd0.cpp), Find_Movie_File 0x5A1BB0 96.95 (w/fmf0.cpp; inline strcpy registers). 0x671FA0 now has a second name Set_Description_00671FA0 (MultiMission, multi_mission.hpp) beside UnknownDescribed_00671FA0::unknown_set_description; a later rename can merge them. Next lead: sweep_seeds filtered on no-argument free functions (@@YAXXZ-style) below the 80 threshold, probed as __fastcall.
- Map.CPP after Map394 (NOTES, w/, hdr/; r1 exact Overpass 0x54B2E0 630 B after ren1 int return): Region_Threat 0x567D20 99.36 shape 99.68 (w/rt1.cpp; X part of the first quadrant sum scheduling; ~10 variants in NOTES), Mark_Fill_Area 0x567710 85.67 (w/mf2.cpp; second region_cells.Add should call 0x56BA30: budget=2S regime, ~1-45 IL more before it or ~20 less S), Spring_Bridge_Destruction_Triggers 0x558340 45.16 (w/sb4.cpp; Cell-budget family), Compute_Zone_Connections 0x54FDA0 mapped (function-static tables 0x7E0244/0x7E0284/0x7E02C4). Next: 0x54FDA0, 0x5629D0, 0x565EB0, 0x565A50, 0x564B60, 0x563D80. XY_Cell gives the original's 32-bit cell sums where Cell(short,short) does not.
- Map.CPP after Map397 (NOTES, w/, hdr/, labs/; r1 exact forwarder 0x549C20 45 B): Compute_Zone_Connections 0x54FDA0 60.24 shape 92.91 (w/cz7.cpp; function-static tables bind as `_?_name@?1??...` with a leading underscore; register allocation: original keeps cptr in ebp), Find_Nearby_Shroud 0x5629D0 63.32 shape 95.70 (w/fs3.cpp; inline budget: fourth scan calls Cell ctor 0x42AD30 out of line), Build_Reachable_Subzones 0x565EB0 47.66 (w/br1.cpp; inline clamped index 0x54FAB0 calls 0x54FAF0 out of line at two sites in the original; forced probe 71.85), Region_Threat 0x567D20 99.36 (~20 more forms), Closest_Edge_Cell 0x5689D0 46.64 (original re-reads MapLocalSize after storing point). 0x565A50, 0x564B60 (needs COMDATs 0x56BC00/0x56CD60), 0x563D80 (COMDAT 0x56C2E0) not drafted.
- CROSS-CUTTING BLOCKER (2026-10-31): /Ob2 inline-budget decisions now block most remaining Map.CPP rows (Cell ctor 0x42AD30 / Cell arithmetic 0x42ADD0 / 0x56AA40 family, 0x54FAF0 inside 0x54FAB0 at 0x564B60/0x565EB0) and ownrdraw 0x5FFB00. Our compiles always expand where the original kept some calls out of line. A dedicated lab study of VC6's inline budget (what IL cost the original's headers must have) is the next lever; see Map391/Map394/Map397 and OwnrDraw389 NOTES.
- netshare 0x5C7EF0 (Netshare390 c/w3.cpp, 75.82): its wol_chat.hpp prerequisite (WolUnknownIdentifier, unknown_identifier_a71b18) landed in codex2 r2791 (60269a521); drafts can drop their local declarations.
- ConvSweep396 (NOTES, rank.txt: all 292 no-argument seeds scored cdecl vs __fastcall): Audio_Events_Shutdown 0x403F80 98.25 (second-pass reload of Audio_Event_List.Next scheduling; not a convention miss). rank.txt is a ready list of 270 more no-argument seeds outside the excluded units.
- InlineLab398 (NOTES, lab/, d/cell-model/, build/check/inl398-{x,y,z}): 0x556BF0 byte-exact under the TibSun Cell model (d/cell-model/coord.hpp); 0x565EB0 71.31 with a charged subzone-ID inline helper (w/brh1.cpp; remaining count-in-edi and frame slots); 0x5629D0 82.86 with the uniform fourth Get_Height scan (w/fs3a.cpp; ecx/edx swap left); Mark_Fill_Area 0x567710 83.59 under the TibSun model; ownrdraw 0x5FFB00 not attempted (prediction in NOTES).
- OWNER DECISION (2026-10-31 ~21:00Z, Cell model): adopt TibSun's `Cell : TPoint2D<short>` model (template TPoint2D<T> with member operators returning `TPoint2D<T> const`, `Cell(int x, int y) : BASECLASS(x, y) {}`) as one family migration, run by a dedicated lane in a private worktree: introduce the template beside rect.hpp's int TPoint2D (rename the old one if needed), re-shape the ten accepted rows it breaks (0x660320, 0x6FBF40, 0x7072D0, 0x49A0F0, 0x429570, 0x4296F0, 0x4C7220, 0x4CB8F0, 0x6C4F50, 0x54AB00) to exact, and land only as a whole-file-exact rename round plus 0x556BF0. Fragile rows 0x428370/0x42C460/0x73FEE0 must stay exact. Reversible: if the ten cannot all be re-matched within the box, the model stays a lab result and the rows stay as they are.
- Seeds399 (NOTES, w/; 10 exact = 787 B from ConvSweep396 rank.txt): Mono_Window_Create 0x59DB30 97.06 (w/mwb30_c.cpp with hm1), Audio_Streams_Stop_Filling 0x408070 95.65 (w/asf.cpp), Audio_Streamer_Init 0x407480 92.22 (w/asi.cpp; true body 302 B, ret at 0x4075AD; needs @refs Reset@AudioTimeSpan 0x403820 and Audio_Streamer_Id 0x831504): all three share an "eager post-call scheduling" residue (the original stores a call's result or sets ecx before the next call's pushes) in library-style units: worth a controlled study. IPXConnClass::Start_Listening 0x523C80 85.25 (w/t_ipx_v.cpp; inline Open_Socket keeps the ushort in esi). Mono_View_Page 0x59DA60 byte-exact at --length 104 (w/mwa60.cpp) but the inventory splits it 8 + 96 and the plan refuses body_bytes 104 as "Unsupported independent bound" (nothing references 0x59DA68): OPEN, needs independent bound evidence (e.g. a reachable-code walk proving 0x59DA68 is inside the body), not a tool loosening. Skipped: atexit vector dtors (population-08 seeds), ownrdraw WolDictionary pairs 0x5DE9C0/0x5DEA60 (1,164 B), MainLoop.CPP ~9 KB (needs a new joined population; 0x53F840 inlines 0x53F780).
- MainLoop.CPP after MainLoop401 (NOTES, w/, t/probe.py; r1 joined unit = population-261 statics + 0x53F460/0x53F470/0x53F480/0x53F780/0x53F840, 1,110 B): unit 0x53F270-0x541F59 (functions listed in NOTES). Keyboard_Process 0x5406E0 44.66 natural (w/ke.cpp; a probe with three extra pending inline sites gives shape 100, so the original's three hotkey lookups see three more inline sites); Sync_Delay 0x540960 54.50 (w/s540960.cpp; first FrameTimer CDTimerClass::Value stays out of line); Motion_Capture 0x53F490 needs a 741 B bound (inventory split at 0x53F656 is false); Main_Loop 0x53FBD0 (2,831), Message_Input 0x540C20 (3,507), Multiplayer_Debug_Print 0x5419E0 (1,189) not drafted. The IndexClass<int,CommandClass*> COMDATs 0x541EC0/0x541EE0 land only with Keyboard_Process.
- OWNER DECISION (2026-10-31 ~22:15Z): unknown_globals.hpp declares session slot 34 as `unknown_slot34(bool player_wins)` only under UNKNOWN_SESSION_DECLARE_SLOT34_ARG (MainLoop units define it); every other unit keeps `unknown_slot34()` because any argument there renumbers Refresh_Wonline_Players 0x73FEE0's $L labels (99.23). Same vtable slot; explicit, reversible hypothesis. Unify to the bool form once 0x73FEE0's unit no longer sees the declaration (or 0x73FEE0 is re-shaped).
- Cell model after CellModel400 (NOTES, h0/, fx/, ren/s0.json, t/rc.sh, rc-g7.txt): under TibSun's TPoint2D<T> member-operator model every accepted row recompiles exact (22 re-shapes in fx/) except Local_Sector_Index_To_Cell 0x55AE50 (49 B; w/f8_o.cpp: two Cell temporaries' stack slots swapped; ~30 forms in w/f8_*). COMDAT 0x56AA40 exact as TPoint2D<short>::operator-; 0x556BF0 shape 100 (w/lb.cpp, needs its @ref). OWNER DECISION (2026-10-31 ~22:40Z): Foot.CPP rows 0x4CBB40, 0x4C45B0, 0x4C7220 use a unit-local guarded free operator+(Cell const&, Cell const&) in the unit's first source (precedent: BuildingClass slot 52's unit-local copy); explicit hypothesis that Foot.CPP's original headers had a free Cell sum.
- Cell model LANDED (bfe9eec9a ren1 + 8f55aa922 r1, +6,224 B): 0x55AE50 needed a file-local inline Sector_Offset_Cell(x, y) (one more charged inline level; putting that body in coord.hpp's XY_Cell breaks 13 rows).
- MainLoop.CPP after MainLoop402 (NOTES, w/; ren1 + r1 = 5,521 B: Main_Loop 0x53FBD0 __fastcall, Keyboard_Process, Sync_Delay __fastcall, Multiplayer_Debug_Print, COMDATs 0x541E90/0x541EC0/0x541EE0, atexit 0x540C10): Keyboard_Process's three missing pending inline sites were an inline keyboard accessor Main_Loop_Keyboard() in the repeat-key loop; Main_Loop needs TibSun's record/playback as a static inline and the int-key wrappers + min<int> after it. Guard macros SESSION_STATE_DECLARE_TRAP_OBJECT and MAP_VIEW_DECLARE_SLOT41 keep 0x73FEE0 exact (each addition alone breaks it). Message_Input 0x540C20 (3,507 B, seed 38.44; w/o540c20.s) and Motion_Capture 0x53F490 (741 B bound) remain.
- Map.CPP after Map404 (NOTES, w/, hdr2/; r1 = 5,147 B: 0x55A590, Repair_Low_Bridge_Span 0x561100/0x561340, Internal_Destroy_High_Bridge twins 0x554960/0x554D00/0x5552C0/0x555690): Damage_Low_Bridge_EW 0x55DEF0 46.17 natural (w/de1.cpp): its only callee Spring_Low_Bridge_Destroyed_EW 0x55EA50 is inlined by us, called by the original (steering probe 97.72 shape 100): either 0x55EA50 is over the auto-inline cap or the caller's root budget is ~100-200 smaller; this gates a ~10 KB family (0x55E410, 0x55F020/0x55F540, 0x5615A0/0x561A80/0x561F60/0x562450, 0x55FCC0) that needs hdr2's map_rect.hpp (TibSun TRect::operator-/Top_Left). Destroy_Train_Bridge_Span 0x553000 56.66 (w/ts2.cpp; frame 0x38 vs 0x4C) and twin 0x558660; Spring_Bridge_Destruction_Triggers 0x558340 55.64 (w/sb3.cpp; needs point.hpp operator+=, which flips 0x428370 when added globally); Mark_Fill_Area 0x567710 83.59; Region_Threat 0x567D20 dropped to 77.91 under the TPoint2D model; Set_WasUnderBridge_Flags 0x568B00 54.75. TibSun names: 0x553570/0x558BD0 Destroy_Train/High_Bridge_Connections, 0x55FCC0 Damage_Low_Bridge_Piece_EW.
- MainLoop.CPP after MainLoop403 (r1 Message_Input 0x540C20 3,507 B; NOTES, t/walk.py, d/walk-53f490.txt): the unit is complete except Motion_Capture 0x53F490. Evidence: reachable-code walk 0x53F490-0x53F774 = 741 B (211 instructions, ends in ret, no gaps); 0x53F656 is the 5th byte of `mov eax,[0xA6EBD8]` at 0x53F652, its only "reference" is entry 159 of a numeric dword table at 0x822ACC-0x823307. No inventory pass has a contiguous 741 B row and nothing references the entry, so acceptance refuses; OPEN (same class as Mono_View_Page 0x59DA60): needs an evidence-based bound mechanism for unreferenced functions, decided by the user, not a tool loosening.
- ownrdraw.cpp after OwnrDraw406 (zero bytes; NOTES, c/, tu.sh; PARKED): Static 0x5F2B50 80.86 shape 94.69 (c/5f2b50best.cpp; single return after the switch with `default:` falling into CallWindowProc; `int delay` ternary for 0x4D3; Rect local before Rect screen; open: window handle kept in edi after GetParent (c/x4.cpp has the exact frame but loses edi to the constant 1), BSurface/Rect `inc`-in-place pattern as 0x5FC330). 0x5FFB00 53.32 natural (probe-only measurements in c/m06/n02/g80: the original has ~two more pending inline sites between WM_PAINT and case 0x110, likely small inline helpers in case 0x84, and a different first lookup). Progress bar 0x5FAFF0 86.15 unchanged (TibSun passes the surface by reference: untested, needs a rename).
- Map.CPP after Map405 (zero bytes; NOTES, w/, lab/, hdr4/, extra.txt with the four exact Spring_Low_Bridge_Destroyed walks 0x55EA50/0x55E930/0x55FB90/0x55FA60): Damage_Low_Bridge 0x55DEF0 (w/de1.cpp), 0x55E410 (w/dm_NS.cpp), 0x55F020 (w/dm_EW2.cpp), 0x55F540 (w/dm_NS2.cpp) all 98.73 shape 100 under hdr4: the only miss is the first inlined Union's third compare `result.X + result.Width < rect2.X + rect2.Width` (ours computes the result side first, the original rect2's side); contextual evaluation order, not budget (accepted Remove_Crate 0x54E6E0 makes the same call rect2-first). Repair_Low_Bridge 0x5615A0/0x561A80/0x561F60/0x562450 likely share it. Damage_Low_Bridge_Piece_EW 0x55FCC0 22.14 (w/pe1.cpp; siblings 0x5601F0/0x5606D0/0x560C10). Destroy_Train_Bridge_Span 0x553000 76.36 shape 95.52 (w/dt1.cpp; frame 0x3C vs 0x4C: the original gives the Rect(minx-64,...) Union temporary a 16-byte home), twin 0x558660 untried.
- Super.CPP after Scout407 (NOTES with TS field map, w/, mk.sh, sc.sh, t/eprobe.sh; r1 = 11 SuperClass functions, 1,852 B; UNITS.md ranks the next fresh units: Beacon/Bink/BitFont 0x42D9E0-0x432D90 ~11 KB, SpecialClass 0x68B320-0x68D950 5.8 KB (contains fragile-closure 0x68CCE0), MPLayer.CPP 0x5A73E0-0x5AA530 5.7 KB, WinModemClass 0x732CB0-0x7371B0 5.5 KB (TS wincomm.cpp), IsometricTileTypeClass 0x528380-, GOptions.CPP 0x4DD8A0-0x4DEEE0 2.6 KB): Grant 0x69CCF0 88.77 (w/s_ccf0_best.cpp), Discharged 0x69D090 87.82 (w/s_d090.cpp), 0x69CB30 82.05 (w/s_cb30.cpp): all three are inline-budget probes (more pending sites in the original, ~20-26 calls or one empty site): one IL-size mismatch among the shared inlines (CDTimerClass, DynamicVectorClass Add/Delete, unknown_69ca70) is the likely cause. Place 0x69D850 (4,357 B switch) not attempted.
- Damage_Low_Bridge family after Map408 (PARKED; NOTES, lab8/u: cc.py, ex.py, norm.py, bis.py ~0.3 s real-CL lab): the Union compare order in 0x55DEF0/0x55E410/0x55F020/0x55F540 (98.73) is decided only by MapClass::operator[](Cell const &) 0x548070's body, auto-inlined three times into each: its `int index` local makes ours result-first; without the local the order flips to rect2-first but the sign test becomes `test; jl` instead of the original's `add; js` (91.05). Every js-keeping index form stays result-first; behaves like a count threshold (truncated lab flips after 8 extra live int+call pairs), not liveness. Resume: an operator[] body / Cell-temporary spelling that keeps js and stays exact for 0x548070 and its inliners. p1.json/hdr4 need rebuilding from HEAD.
- Super.CPP after Super409 (zero bytes; NOTES, w/, lab/, tools mk.sh/s3.sh/pc.sh): IL sizes measured (DVC Delete(int) HEAD form 99-100, Westwood `(*this)[i]` form 103-104; Add ~140; CDTimerClass Stop 51-52, Value 91-92, Start 45-46, ctor 43-44, operator long free). 0x69CB30 is exact with the Westwood Delete(int), but that shared change drops dtor 0x69C8B0 and a ~102-unit mixed form breaks 17 accepted out-of-line DVC Delete instances (0x58EFB0, 0x61AD90, ..., 0x63CA50) and 0x66EB20: the shared Delete(int) is pinned to HEAD's form. TibSun-shaped cd_timer.hpp changes nothing. Lead: Place calls 0x69CB30 out of line while ours inlines it: a cap miss (the original 0x69CB30 is wordier). Place 0x69D850 draft 61.13 shape 90.60 (w/s_d850.cpp; body_bytes 4388 to the end of its jump table 0x69E974; case layout order 3,4,2,1,5,6,0; ChronoWarp COM AddRef helpers 0x69ED20/0x453EA0 out of line = the parked comip model; COMDAT 0x69ECF0 still to be a row). Grant 88.77, Discharged 87.82 unchanged.
- Win32 dialog/window helper unit 0x735690-0x7371AA after Modem410 (NOTES, w/; r1 = 23 functions + WinModemClass::Set_Serial_DTR 0x734900, 5,242 B; the survey's "WinModemClass" range is three units: WeaponType.CPP (complete), wincomm.cpp, this helper unit in population-3045): End_Dialog 0x7357E0 87.67 (w/u_7357e0.cpp; found-index register: original keeps the counter in eax and moves to edi after cmp eax,-1; also needs a rename: callers know it as void Unknown_007357E0(void*, int) / Close_Online_Dialog_007357e0), drag info 0x736490 76.06 (w/u_736490.cpp). Follow-ups: Dialog_Loop_007359e0 (bool flags) vs lobby.hpp's Unknown_007359e0 (int flags) could merge by rename; win_util.hpp's redeclarations can fold into their owners. Rule: check every `??_C` string literal length against the original bytes (trailing spaces in "Windows 95 " etc.; inline strcpy hides wrong lengths from the scorer).
- Beacon/Bink/BitFont span after Beacon411 (NOTES, w/; r1 Beacon.CPP 9 rows + r2 Benchmark unit and Chars_In_Width = 2,463 B). Unit extents from the .CRT$XCU table: Beacon.CPP 0x42D770-0x42F09F, Benchmark 0x42F0A0-0x42F1F7, BufferIOFileClass (complete), Bink.cpp 0x42FE50-0x43101F, BitFont 0x431020-0x43226F, BitText 0x432270-0x432DCF. Misses: Set 0x42DD60 88.46 (v/dd60_i3b.cpp, hm2), Place 0x42E370 87.04 (b_e370.cpp), radar marker 0x42DE20 57.89 (frame 0x38 vs 0x28; radar.hpp vs map_view.hpp declare Unknown_00631BA0 differently), Benchmark ctor 0x42F0C0 85.00 / Begin 0x42F100 73.91 (Started stored first in the original), Draw_String 0x431CC0 77.90 (channels R|B|G), Draw_Char 0x4318E0 26.68, Bink 0x430600 98.80. BitTextClass::Print_Box 0x432490 returns bool (HEAD says int): rename first. Pattern: search loops whose miss exits straight to a return are `for ... if (...) goto found;`.
- OWNER DECISION (2026-11-01 ~03:00Z, MPMath Signed_Mult 0x5A8340): accepted with `XMP_Init(abs_x, 0, precision)` burn-clears of its two local abs_ arrays after their last use (PGP/Westwood idiom; TibSun/RA1 mpmath end Reciprocal and Exponent_Mod the same way). VC6 removes the dead clears but they add the 2-4 pending inline sites that send the first Neg's XMP_Inc out of line. Explicit hypothesis, not a dummy call: it is the file's own security idiom. Revisit if a cleaner form appears.
- MPLayer/MPMath/GraphicMenu after Units412 (NOTES, w/, jsc.sh, vsn.sh; r1 3,884 B + r2 Signed_Mult 507 B): units: MPLayer.CPP 0x5A71F0-0x5A7522, MPMath.cpp 0x5A7530-0x5AA52A (TibSun mpmath.cpp is the exact shape), GOptions.CPP 0x4DD5E0-0x4DE23F (only Options_Menu_Proc 0x4DD8A0 86.53 left), GraphicMenu 0x4DE240-0x4DEF2F (separate TU). Misses: Is_Prime 0x5AA380 99.31 (inlined Fermat compare jl vs jb), Exponent_Mod 0x5A9860 83.88, Reciprocal 0x5A8CF0 74.59 (hmx overlay), Mod_Mult 0x5A9400 68.69, Set_Item_Visible 0x4DE960 64.79; GraphicMenu::Load(INIClass&) 0x4DE380 (1,173 B) and Run 0x4DE9E0 (826 B) undrafted (shapes in NOTES).
- GraphicMenu/MPMath/GOptions after GMenu414 (NOTES "GMenu414 misses", w/, v/, go/; r1 Load(INIClass&) 0x4DE380 1,173 B + Run 0x4DE9E0 826 B): Set_Item_Visible 0x4DE960 66.67 (v/e960_4.cpp; original re-reads the vector array pointer and element), Is_Prime 0x5AA380 99.31 (inlined Fermat pointer compare jb vs jl; ~6 more forms in NOTES), Exponent_Mod 83.88, Reciprocal 74.59, Mod_Mult 68.69, Options_Menu_Proc 0x4DD8A0 86.53 (go/t_1.cpp: the original calls the CDTimer(long) ctor 0x4DE1E0 out of line at both `timer = 900` sites; ours inlines the first; budget at that site ~30-60 IL too large: 8 extra calls flip both, 4 do not).
- BitText/BitFont/Bink after Bink413 (NOTES, w/text, w/font, w/bink; ren1 Print_Box bool + r1 BitText split/Bink 5 rows + r2 bit codec = 2,622 B): BitFont.cpp and BitText.cpp are separate units (population-3392 had joined them, wrongly inlining Glyph_Data into Print_Box). Print_Box_Shadow 0x432B00 exact (w/text/t_2b00.cpp, hc) awaiting freeze; Print_Box_Bold 0x432BB0 92.82; Print_Box 0x432490 38.44; Load_Font_Data 0x431150 90.58 (624 B extent); Bink Open 0x42FF30 69.63; Draw_String 77.90; Draw_Char 26.68.
- OWNER DECISIONS (2026-11-01 02:20Z, Windows): codex4 may decide BuildingClass slot 280/282/283 signatures from evidence and deliver them as R rounds (ABI acceptance included); its next unit after BuildingClass is ParticleClass/ParticleSystemClass 0x608440-0x60D110. codex2 standing rule: byte-neutral standalone renames touching an out-of-range function or an unheld header are pre-approved as plain R lines when whole-file exact.
- BitText/BitFont after BitText415 (NOTES, w/text, w/font, w/c5, overlays hx_*; r1 = Print_Box_Shadow, Print_Box_Bold, BinkClass::Open, Load_Font_Data, Draw_String = 2,197 B): Print_Box 0x432490 81.61 natural (w/c5/z0.cpp); 94.33 only with two probe Nop_() inline sites (w/text/t_2490q.cpp, not source): the original has ~two more inline-candidate sites after the first flush; its COMDAT 0x432D90 RGB_To_Pixel (red|green|blue builder in hicolor_pixel.hpp) joins the plan when it lands. Draw_Char 0x4318E0 26.68 not reworked.
- OWNER DECISION (2026-11-01 ~04:00Z): provider-only declaration guards RA2_COORD_PLUS_SOURCE (coord.hpp, CoordStruct::operator+ COMDAT 0x69ECF0) and RA2_CDTIMER_VALUE_SOURCE (cd_timer.hpp, CDTimerClass<SystemTimerClass>::Value 0x4DE200) accepted, same pattern as RA2_COORD_DIVIDE_SOURCE: only the provider TU sees the out-of-line declaration; all callers keep the inline definition. (codex3 r228)
- IsoType unit 0x528380-0x52EDDF after Iso416 (NOTES, w/, hmx/, t/renum.sh, fixb.py; r1 = 18 functions + 3 takeovers, 5,687 B; layout 0x264-0x2D8, size 0x2DC; static members behind ISOMETRIC_TILE_TYPE_DECLARE_STATICS, Cell::Clear_Icon behind CELL_DECLARE_CLEAR_ICON): Build_Preview_Tiles 0x52E3D0 (644 B) BYTE-EXACT in the scorer (w/s_e3d0.cpp) but refused at acceptance: "Unsupported allocatable data section .rdata #2" (its function-local `static float const` at 0x7A5134 shares the unit's .rdata with the header-static constants). RESOLVED 2026-11-01: the user approved the extension; audit commit 53f108001 (per-symbol check for unrelocated data whose symbols come from different original places), landed as ed8c257da. Preview_Tile 0x52E390 81.25; Read_Control_File 0x529870 (6,762 B), 0x52B8B0 (2,403 B), Draw_Tile 0x52C230 (6,967 B) undrafted. Real `Point2D Offset` member (empty ctor = one more pending inline site) fixed the recorded VectorClass ctor inline problem.
- ParasiteClass after Scout417 (NOTES, w/, UNITS.md re-ranked on HEAD: next fresh units WaveClass 0x7211B0 7.4 KB wave.cpp, UnitTypeClass 0x70A410 5.4 KB unittype.cpp, UndoInfoStruct 0x684D50 5.8 KB, SpecialClass 0x68B130 5.8 KB, span 0x403CE0, SubTitle, AlphaShapeClass, ParticleTypeClass, OwnerTalk, StringTable, ThemeClass, ToolTip, PhoneEd; r1 = 5 functions 1,025 B): grapple update 0x606780 93.35 (best_6780_93.35.cpp: code identical, only the stack frame slot order differs; the three reset pairs become a member at 0x6066A0 taking over the pop-88 seed), 0x607980 87.40 (the original calls DVC Delete(int) 0x454B20 out of line; ~3 more pending inline sites), 0x607C30 59.06 (original auto-inlines Can_Exit 0x607BA0: its Can_Exit is under the auto-inline cap, ours not; also blocks 0x607440, 1,198 B), AI 0x606F50 (Para131 98.10) needs the TechnoClass slot 223 rename. Victim +0x44 is really an AnimClass*.
- IsoType after Iso418 (NOTES, w/, v/, frz.sh, v9.sh, t2/strrefs.py; r1 Shadow_Caster_List 0x52B8B0 2,403 B + exit thunk 0x52C220): Read_Control_File 0x529870 (6,762 B) 95.35 shape 100 (w/s_9870.cpp; all 1,590 instructions align, 51 differ only in stack offsets: spill slots of the 46 [General] locals and the two `callback_timer = 4` temporaries 0x174 vs 0x120; needs `static void __fastcall Read_Control_File(int theater, bool from_ccfile)` from hm/shared); Preview_Tile 0x52E390 81.25; Draw_Tile 0x52C230 (6,967 B) undrafted (TibSun ~820 lines; needs IsoDrawData 0xA52F08, span tables, depth/alpha buffers; two function-local statics in .rdata 0x7A49B0/0x7A4A28, now supported by 53f108001).
- IsoType after Iso420 (zero bytes; NOTES, w/, t2/ frame-map tools, t3/gen_dt.py): Read_Control_File 0x529870 95.35 shape 100: code identical, 24 [General] spill/timer-temporary slots in -2028..-1925 ordered differently (the original behaves as if the first `callback_timer = 4` temporary were not a separate sort element; ~10 forms in NOTES). Draw_Tile 0x52C230 first draft 28.53 shape 90.03 (w/s_c230.cpp; the variation walk is a tail call; globals _iso_row_offsets 0xA6CF68, _iso_start_cols 0xA52594, _iso_run_lengths 0xA53398, flags 0xA6E395/0xA6E394, Iso_Blit_Asm2 0x77F3DF, IsoDrawData 0xA52F08 = TibSun IsoBlitState; function-local statics 0x7A49B0/0x7A4A28; blit.hpp's ABufferPtr 0x839C6C/ZBufferPtr 0x8315B4 look swapped vs TibSun's Depth/Alpha). Landing needs its accepted caller CellClass 0x4754B0 retargeted from unknown_func_52c230 (owner: retarget by rename when Draw_Tile lands).
- OWNER DECISION (2026-11-01 ~04:30Z, Wave.CPP): coord.hpp guard RA2_COORD_AS_CELL (defined by the Wave unit's first source) gives that unit TibSun's CoordStruct::As_Cell (inline `Cell((int)X / 256, (int)Y / 256)`, out-of-line copy 0x413770) and member Cell ==/!= (copy 0x58DB50) instead of the free operators. Explicit unit-local hypothesis (precedent: Foot.CPP's free operator+), reversible.
- WaveClass after Wave419 (NOTES, w/, hy/ overlay; r1 Wave_Recalc_Affected_Cells 0x723360 1,359 B; WaveClass +0xE8..+0x10C edge coordinates): Build_Wave_Shape 0x7238B0 (2,358 B) 88.44 (w/bs_f1.cpp, hy; frame slots + two kept float stores; takes over seed 0x7241F0 when it lands), Set_Laser_Pixel 0x721B00 95.83 (w/lp_n.cpp; needs body_bytes 240), Load 0x7221D0 79.67 (w/ld_a.cpp; with hy's six Point2D members, three more pending inline sites make it exact), Draw_Sonic 0x7225B0 and Draw_Laser 0x722CB0 not attempted (Wave362 40.47 / 52.67).
- 0x70A410-0x70C610 after UnitType421 (NOTES, w/, js.sh/vs.sh/df.sh; r1 UnitTrackerClass unit + hi-colour VQA unit, r2 Turret_Adjust = 579 B new + takeovers): three units: unittype.cpp 0x70A410-0x70B68F (Read_INI 0x70AB40 2,013 B still at the 50.00 register plateau), hi-colour VQA unit 0x70B690-0x70C43F (TibSun unvqtblc.cpp; HicolorTable 0x00AD0614), UnitTrackerClass 0x70C440-0x70C60F (utracker.cpp). Misses: UnVQ2_4x4_Table 0x70B820 87.10 (w/uv2_44o1.cpp; case 0x6000: block counter in ebx, block pointer stepped in eax only), UnVQ1_4x4_Table 0x70BF60 52.48 shape 100 (ecx/edx swap), UnVQ2_4x2_Table 0x70BBC0 47.10 (real body 922 B; inventory row 0x70BD92 is bogus), UnVQ1_4x2_Table 0x70C0A0 undrafted. Follow-ups for holders: house.hpp's UnknownHouseTracker is UnitTrackerClass; movie.hpp's VQA_Unknown_0070B690/0070B7F0 and VQAClass::Unknown_0070B7D0 are the free Hicolor_*/UnVQ*_Table functions (renames pending).
- UndoInfoStruct terrain-deformation unit 0x684D50-0x6873D0 after Undo422 (NOTES, w/, undo.dis; r2 Get_Deformed_Cell_Height 0x686C90 + Get_Deformable_Cell_Corners 0x686DD0; r1 Special.cpp Init 0x68B320 + Equals_Options 0x68B3F0; 904 B): real bodies 0x685290 864, 0x685600 1209, 0x685AC0 2325 (contains the accepted 1-byte region 0x68633A: allow_split takeover when it lands), 0x6863E0 557 (returns bool; Generate_Hills declares void), 0x686610 585, 0x686860 391, 0x6869F0 667. Misses: Commit 0x6863E0 58.08 (cm_w.cpp), Deform_RMG 0x6869F0 61.14 (df_g.cpp), Deform 0x686860 54.75, Spread 0x686610 54.92: look for hidden by-value temporaries first (the 0x686C90/0x686DD0 key was Fetch_CellID().X/.Y temporaries). The accepted 0x6850B0/0x685150 really take a second bool in dl (two-parameter forms exact in w/co_a.cpp, w/cf_a.cpp): rename both when 0x685290/0x685600/0x685AC0 land. Past 0x68B7E0 the "SpecialClass span" is the parked ownrdraw HashTable family (0x68BD50 ctor, Wstring hash 0x68BDE0).
- Special/PCX span after Special423 (NOTES, w/, t/bounds.py, overlays h1/hm; r1 PCX image cache unit 0x68BC50-0x68D94F = 1,118 B + 2 takeovers): extents: special.cpp 0x68B130-0x68B7DF (special.hpp's 0x68B93F end is wrong), unit B 0x68B7E0-0x68BC4F (rotated blitter 0x68B800 1,100 B; inventory row 0x68B917 bogus), PCX cache 0x68BC50-0x68D94F (UnknownBitmapWriter = wlib Dictionary<Wstring, Entry>, Entry {Surface*, Palette[768]} with no destructor). Load_Image 0x68C600 99.69 (w/pl8.cpp, hm; one [edx+eax] operand order; needs a rename int -> bool, only @ref user 0x5FC8A0; with it Remove_Entry 0x68D540 and Grow_Table 0x68D8A0 are exact), Draw 0x68CE80 83.81, Unload 0x68CB30 70.80 (inline budget between two cases), Brighten 0x68BCE0 80.46; Write 0x68C040 (1,460), Draw-alpha 0x68CF90 (1,441) not attempted. Mechanism: a destructor on the dictionary's value type adds one inline site after Remove_Any (flips Shrink's inlining).
- AlphaShape/Theme after Alpha424 (NOTES, w/, overlays hm/ht; r1 AlphaShapeClass 4 functions 1,032 B; r2 ThemeClass 7 functions 1,376 B + ThemeControl ctor takeover; ThemeControl record behind THEME_CONTROL_RECORD in theme.hpp): AlphaShape unit 0x41E970-0x41FF1F (alpha table 0x83C670, ready flag 0x84C684; its "alpha buffer" is ZBufferPtr 0x8315B4); Draw_In_Area 0x41F1C0 41.92 (w/dia.cpp; frame 0xB8 vs 0xA0, more spills), Draw_All 0x41F5E0 34.72 (w/dal.cpp; first 0xCC bytes exact apart from frame offsets). Theme unit 0x6E7550-0x6E872F: Play_Song 0x6E7EB0 (668 B) and 0x6E8340 (249 B) not drafted. Rules: drafts in population-2683 must not include alpha_shape_list.hpp (a second .CRT$XCU initializer pair); an inline vector ctor emits both vector vtables (each slot @ref'd with the PAU mangling).
- PCX cache after PCX425 (NOTES, w/, overlays hm/hw, t/check_rp.py; ren1 Load_Image bool + r1 Load_Image/Remove_Entry/Grow_Table 1,892 B): Write 0x68C040 (1,460 B) 76.84 (w/pw17.cpp, hw; in-memory .bmp loader; no rename needed, only caller 0x75EF30 @refs the prefix), Draw 0x68CE80 83.81 (source++ induction with exit value computed in the inner guard), Brighten 0x68BCE0 80.46, Unload 0x68CB30 70.80 (original cross-jumps both Shrink_Table sites into one call), Draw-alpha 0x68CF90 (seed/0068cf90/candidate.cpp) and unit B 0x68B800 not attempted. Keys: a function-wide commutative operand tie flips when the single `int index` is shared with the hicolor table loop; ms_anim.hpp -> shape_file.hpp's static empty rect emits a second XCU initializer unless SHAPE_FILE_EMPTY_RECT is redirected (as AnimType.cpp does).
- ThemeClass and ToolTip.cpp complete after Theme426 (b170c5720, 65af04f6e; 3,159 B): Stop/Queue_Song re-shaped with TibSun's Still_Playing() == true and a chained Pending = Score = Current = -1 to fit under the auto-inline cap; ToolTip needs TOOL_TIP_UNIT guard and TibSun bsearch.h shape for Binary_Search; POINT mangles as PBUPOINT@@.
- Audio library after Span427 (NOTES, w/, t/check_rp.py; ren1 Audio_Streamer_Init __fastcall + r1/r2 = 2,609 B): extents: unit A 0x403CE0-0x4068FF (audio event C code, pop-2801/2827), unit B 0x406900- (library, no initializers: seed populations 2827, 953/40, 993, 1328, 1329, 2211, 2225; pop-2225 also holds 0x4025xx-0x402C40 of the 0x401000 unit, which wrongly inlines 0x402800 when joined), AlphaTableCache 0x40AC80 (pop-3031). Misses: Audio_Events_Shutdown 0x403F80 98.25 (one more pending inline site), Audio_DS_Channel_Open 0x40A180 93.10, Next_Piece 0x404B90 85.22, Load_Samples 0x404890 81.41, AudioLevel::Update 0x4070F0 74.63, Create 0x405170 70.27, DS_Open 0x409FB0 63.55, Ring_Is_Empty 0x408C80 47.06 (header calls it Is_Full), Queue_Update 0x4090E0 40.78, Ring_Destroy 0x408760 40.44; not drafted: Audio_Events_Update 0x4041B0 (1,316), Audio_Event_Update 0x4055D0 (1,038), Audio_Thread_Proc 0x4094D0 (709), Audio_DS_Channel_Start 0x40A260 (714). Inventory rows 0x403D4B, 0x40653A, 0x406D36 bogus.
- Storage/SubTitle/StringTable after Str428 (NOTES, w/, an.sh; r1 storage.cpp 391 B + subtitle manager unit 1,193 B + subtitle parser unit 1,960 B, r2 Reverse_String 55 B): extents: storage.cpp 0x69ABD0-0x69B00F (TibSun StorageClass with float amounts; inventory rows 0x69AEFC/0x69B9F1/0x69BE52 bogus), subtitle manager 0x69B170-0x69B67F (VQAMovieCompanion), subtitle parser 0x69B680-0x69C3AF, StringTable 0x6F8BE0-0x6FA1DF. StringTable Init 0x6F8E30 (965 B) 80.78 natural (w/s/best_6f8e30_80.78.cpp: ~CCFileClass 0x51AD20 called out of line at the failure return, inlined at success; ~3-4 more inline call sites in the original), Read_CSF 0x6F9400 (908 B) and Read_Text 0x6F9790 (1,317 B, no-argument: probe __fastcall; repeats Init's line-trim code three times: a shared Strip_Line helper?) not attempted. Keys: `return` inside `while (true)` keeps VC6 from rotating the loop; Rect::Set rather than `= Rect(...)`; every CRT relocation name and template vtable slot needs an @ref; a COMDAT callee defined in the unit must be a plan row.
- OWNER DECISION (2026-11-01 ~07:00Z): Audio_Event_Next_Sample 0x404790 moves from pop-2827 into the audio event unit (pop-2801, allow_split), evidenced by its address inside the event unit and by Audio_Event_Update 0x4055D0's inlining (Audio429 r1).
- Audio library after Audio429 (NOTES, w/, vc.sh prints a candidate's call targets, dsenv.sh DROP): Audio_Events_Update 0x4041B0 77.46 (w/eu_o2.cpp, e2.txt; inlining now exactly the original's via static helpers Sort/Rank/Destroy/Free_Lower + a final Audio_Events_Unlock(); needs hm/shared/audio.hpp type fields), Audio_Thread_Proc 0x4094D0 84.47 (w/tp_d.cpp; needs 0x40A8C0 to read the eight level pointers as named globals Audio_Global_Levels_0..7, still exact, so it fits the auto-inline cap), Audio_DS_Channel_Start 0x40A260 54.27 (VC6 places the create-buffer block before the reuse path whatever the source order), Shutdown 0x403F80 98.25, DS_Channel_Open 0x40A180 93.10. Pop-3434 is three pieces: the timer functions 0x409280-0x40930F and the 0x4025xx-0x402C40 rows are not in the DS unit (Audio_Now 0x4092D0 would inline for free if it were).
- OWNER DECISION (2026-11-01 ~07:40Z, StringTable Init 0x6F8E30): accepted with inline Close_File (fclose) wrappers at its three fclose calls and an Open_File (fopen "r") wrapper at the second fopen: the four extra inline call sites VC6's budget needs after Read_CSF_Header (3 is partial, 5 overshoots). Real wrappers doing real work, an explicit hypothesis about the original's helpers; revisit if Read_Text's source reveals the real helpers.
- StringTable after Str430 (NOTES, w/s/, t/walk.py; r1 String_Table_Init 1,134 B + Read_CSF_File 908 B + 2 takeovers): Read_Text 0x6F9790 (1,317 B with jump table) 70.92 (w/s/best_6f9790_70.92.cpp; __fastcall, helpers Strip_Line x2 / Convert_String / Collapse_White_Space; the original body is larger: Collapse only inlines with ~10-26 more IL, the draft uses an unnatural `if (duplicate) {}` placeholder: not landable; open: Convert_String registers out=edi/escape=ebp/in=esi). Read literal names from the candidate .obj (`??_C@_01LHO@r?$AA@`); Str428's guessed hash was refused.
- OwnerTalk/PhoneEd after Talk431 (NOTES, w/, t/bounds.py, fin.sh; ren1 + r1 OwnerTalkClass 3,189 B + r2 PhoneEd.cpp 3,427 B): OwnerTalk 0x63ED70-0x64026F (packet-router talk object: starts mph.exe, TALK_* messages; ConnectionListStruct 0x2A packed, TalkPacketStruct 0x152), PhoneEd.cpp 0x60D780-0x60EA5F (TibSun phoneed.cpp nearly line for line). Misses: Mask_Of_ID 0x63F4C0 59.74 (original pushes ebx/esi after the id == -1 early return, three separate -1 returns), Dial 0x60DC80 95.06 and Add 0x60E160 93.85 (shape 100; ecx/edx swap in the inlined PhoneBook.ID loop after PhoneBook.Add). Rules: PhoneEntryEdit::Dialog must end `if (RC != 1) return false; return true;` (the ?: form gets auto-inlined); a function-local static's atexit _$E needs its own @ref even as a plan row. Landing note: a round whose overlay was written post-rename but whose BASE predates the rename conflicts in land_round's 3-way merge: set its BASE to the rename commit.
- RadarEvent/RGB/RLE after Scout432 (NOTES, w/, UNITS.md re-ranked on HEAD: SaveLoad 0x654A50 13.4 KB, 0x639770 4.7 KB, CCFile span 0x401000, ControlClass span 0x483410, 0x61D240, 0x6F1810, TiberiumClass 0x6E8730, ProgressScreen 0x61EAB0, CStream 0x494320, RadBeam 0x6351B0, LightSource 0x536F30, CD.CPP 0x46DDD0, MPScore 0x5AA830; ren1 + r1-r3 = 3,681 B + 86 B takeovers): RadarEventClass ctor 0x63B6C0 97.48 (DVC Add register tie; `Add((RadarEventClass *)this)` is exact but steering, not delivered), Process 0x63B940 98.69 (ColorSpeed/ColorFactor load order). Keys: VECTOR_IMPLEMENT_* selective set in the unit's first source (ALL + radar.hpp emits unbound HashObject vtables); 0.02f must bind to 0x7A8EA8 (0x7AE2DC is a duplicate); Draw's constant 0x7A8EB0 is 0.70710678.
- quat.cpp/quarry.cpp after PType433 (NOTES, w/best_*.cpp, best_hm/; r1 1,228 B): ParticleTypeClass ptype.cpp was already complete; quat.cpp 0x622160-0x622FAF (wwmath Quaternion, free functions __fastcall). Misses: Axis_To_Quat 0x6229B0 95.35 and Trackball 0x622690 90.73 (both: last Normalize division fdivr mem vs fld/fdiv), operator* 0x622400 76.60, Build_Matrix3D 0x622EB0 68.71 (100 in a lab without Matrix3D's out-of-line copy ctor: OWNER DECISION PENDING, cross-cutting: 0x58FE10 is probably Matrix3D(Matrix3DStruct const &), not a copy ctor; locomotion Draw_Matrix/Shadow_Matrix return Matrix3DStruct by value in TibSun; only accepted @ref user Tunnel 0x6F0CE0), Make_Closest 0x622290 53.96. Name checks: Inverse/Conjugate 0x6225F0/0x622640 may be swapped (TibSun order); fast_math.hpp's Fast_Acos 0x4BA550 / Fast_Asin 0x4BA580 look swapped.
- OWNER DECISIONS (2026-11-01 ~11:00Z, after a Mac crash): approved and landed codex2 r2803 (LobbyNameSet alias in the Mac-landed netshare unit), codex3 r236-v2 (shape_file.hpp provider guard), codex4 r45 (Tactical_Get_Cell_Ramp member + unchanged CellClass declaration split into cell_class.hpp), codex4 r46 (guarded TPoint2D::operator+=). codex4 r43 Grand_Opening 0x4426D0 (4,004 B) held: its header changes are approved (CoordStruct(Cell const &, int z = 0) converting ctor etc.); Pose_Dir 0x417890 moves out of legacy population-01 into its real class population by allow_split takeover in the same round directory, instead of importing class headers into population-01.
- reinf.cpp unit 0x639770-0x63AE9F after Span435 (NOTES, w/; r1 _Create_Group 0x639DA0 682 B + Create_Air_Reinforcement 0x63A690 481 B; coord.hpp RA2_COORD_FROM_CELL and techno.hpp RA2_TECHNO_PAIR_ROOKIE guards): Do_Reinforcements 0x639970 99.43 shape 100 (three register reloads at the _Who_Can_Pop_Out_Of NULL exit), Create_Reinforcement 0x63A050 72.40, chrono 0x63A880 (1,567 B) and the MISSION.INI briefing unit 0x63AEA0 (0x63B090, 0x63B270) not started. SaveLoad after Save434 (5949ead84, 3,650 B): Put_All 0x6558B0 (4,055 B) and Get_All 0x656B80 (3,801 B) mapped (Save434 putall_lists.txt), Save_Game/Load_Game/Query_From not started.
- reinf.cpp/Restate.cpp after Reinf437 (NOTES, w/, t/var2.py, t/dv.sh; r1 Do_Reinforcements 1,069 B + r2 Restate.cpp unit 0x63AEA0 612 B): Create_Reinforcement 0x63A050 99.55 (w/best_0063a050_99.55.cpp: two instructions in the drop-pod adjacent loop load the table operand before newcell; changing loop 1 flips loop 2: global numbering), chrono 0x63A880 (1,567 B) undrafted (the original calls Release_Held 0x509860 out of line on both QueryInterface branches; infantry_piggyback_ptr.hpp releases inline: needs the comip-style release-in-destructor model, cf. COM_PTR_RELEASE_IN_DESTRUCTOR).
- OWNER DECISION (2026-11-01 ~13:00Z, SaveLoad Put_All 0x6558B0 / Get_All 0x656B80, Save436): accepted with TibSun's release-build `inline void DebugString(char const *) {}` calls (saveload_lists.hpp): they emit no code but their IL sets the caller's inline budget, so the original's 23 inline + 34 out-of-line Save_Vector sites (Put_All) and 44 inline + 13 out-of-line Skip_Objects sites (Get_All) reproduce. Explicit hypothesis about Westwood's real debug-logging idiom (strong for Get_All: it matched once every failure branch got its FAILED line; Put_All's exact set of "Saving ..." lines is a guess, 6-20 lines all give 23). A varargs inline DebugString is not expanded by VC6.
- SaveLoad after Save436 (NOTES "Not done", o6554a0.txt, o656890.txt): Save_Game 0x6554A0 (1,040 B), Load_Game 0x656890 (742 B, inlines Get_Savefile_Info), Query_From 0x6591C0 (117 B) need: takeovers of the out-of-line Release_Held 0x658050 (IStorage)/0x658060 (ILinkStream), a com_ptr.hpp CreateInstance variant calling _Release out of line under COM_PTR_RELEASE_IN_DESTRUCTOR, __uuidof(ILinkStream) GUID 0x7F1B50 in the unit's .rdata. chk.sh gotcha: pass the repo-relative header directory.
- SaveLoad complete after Save440 (Save_Game/Load_Game/Query_From 1,899 B; SavegameInformation 0x659240-0x65B2BF split into its own unit, TibSun savever.cpp): Save_Game/Load_Game also rely on the DebugString decision (Save_Game: TibSun lines through 'Creating content stream' + FAILED; Load_Game: two sites after the stream ctor). com_ptr.hpp Query_From rewritten in comip _QueryInterface form (the old deduced form made VC6 drop the call). Next unit Scenario.CPP pop-3144 0x65B2C0: NoInit ctor 0x65B780 64.00, Wait_For_Players 0x65C520 90.40, Clear_Scenario 0x65D370 99.66 (untried: 0x6612C0's check as int index >= 0 && index < 50), Scan_Place_Object 0x660B60 ~48.6.
- Ctrl439/Tib438/Misc442/Prog441 (2026-11-01 afternoon; NOTES in each lane folder): convert.cpp ConvertClass ctor 0x483650 99.04 (one [edi+ecx-1] vs [ecx+edi-1] store), CD::Insert_Disk 0x46E520 93.37, CDControl Unlock_Media 0x46F750 89.92; RadBeam 0x635C30 96.92, 0x636130 95.83, 0x6358D0 96.95 (hicolor channel pack order), Update_All 0x6354E0 79.45 (static __fastcall; needs 0x635E00 re-shaped `unknown_6c++; return unknown_6c >= Period;`), TiberiumClass Size_Of 0x6EA9C0 (6 B, no inventory row) undrafted; LightSourceClass ctor 0x537240 96.30; credits-range DirectDraw rows 0x4955D0/0x495970/0x495AD0/0x495C90 untouched; preview.cpp Create_Preview 0x61D660 62.63 (frame 0x98 vs 0x84), ProgressScreen 0x61EFA0 88.97 and Shape/Flag/Text_Offset 0x61F4B0/0x61F630/0x61F770 (~89.9; Get_Frame 0x620410 called out of line in the original: Box_Size ~152-157 IL, 4 more stores cross the 175 cap), Draw_Player 0x61FC20 (1,069 B) undrafted.
- Shell art unit 0x6F1810-0x6F55EF and audio library 0x401000-0x403CDF after Span443 (NOTES, w/; r2 shell art 4,173 B + 3 takeovers as one joint population, r3/r4 AudioLevelSet::Update + AudioTimeSpan::Is_Due 77 B): shell art accepted rows were scattered over ~10 separate-units seed populations (lost inlining); future rows belong in the joint population. Misses: Load_Palette 0x6F1FA0 43.22 (fa0h.cpp), AudioLevelSet::Init 0x401000 80.00, Combine 0x4010C0 92.98, Audio_Bag_Read 0x4018C0 51.72 (esi/edi swap); undrafted in the audio span: 0x4016F0, 0x401C00, 0x402990, 0x402C70 (632), 0x402F60 (585), 0x403210 (251), 0x403310, 0x4039C0, 0x403A80 (606), 0x4031B0. Rule: only a Rect returned from an inline with `-=` gives `sub reg,0xA8`; a direct `Width - 0xA8` gives `add reg,-0xA8`.
- Bounce/LCW/AnimFile/ColorList after Scout444 (NOTES, w/, UNITS.md re-ranked on HEAD: combat.cpp 0x47DFD0, mixfile.cpp (the "MissionClass" span 0x594310), GScreen 0x4E06E0, Layer/LCW 0x5346B0, movies.cpp 0x5A0060, TerrainType, Ini.CPP, LZO, MSAnim, VoxelAnim, WWKeyboard, MSEngine, CRC/Factory; 3,013 B): BounceClass::AI 0x4370E0 91.93 (frame 0x12C vs 0x130: second Rotate_Vector temporary shares the first's slot), BounceClass::Init (random) 0x436C70 96.91, GScreenClass::Get_Input 0x4E09D0 82.81 (esi/edi). matrix3d.hpp now has a guarded RA2_MATRIX3D_INLINE_COPY inline copy ctor (0x58FE10 its out-of-line copy): relevant to the pending 0x58FE10 Matrix3D(Matrix3DStruct const &) question from PType433.
- Audio library 0x401000-0x403CDF after Audio445 (NOTES, w/, hm/; ren3 + r1-r3 = 2,071 B): TU boundaries by inlining evidence: LevelSet 0x401000-0x4011BF, Bag 0x4011C0-0x4019DF, Bank 0x4019E0-0x40203F (pop-1335 held bag+bank: split), Device + AudioTimeSpan 0x402F60-0x403AFF, 0x402990-0x402BFF; channel code 0x402040-0x4028FF unsettled. Misses: Create_Device 0x402C70 90.86 (our inline budget far larger than the original's: unexplained), TimeSpan::Format 0x4039C0 79.73, Remove_Devices 0x403210 61.11 and System_Shutdown 0x402990 60.26 (the original keeps an 8-byte list cursor in memory; every form gets enregistered; System_Shutdown is void: rename needed incl. Audio_Shutdown 0x406C80), Bag_Read 0x4018C0 64.41, Combine 0x4010C0 92.98, TimeSpan::Reset 0x403820 95.45 as a real member, Device_Dump 0x403A80 undrafted. Rules: volatile fields fix load/store ordering (Bank entry unknown_0c, Device RefCount); address-taken locals declared at function top keep store-then-load order.
- combat.cpp / mixfile.cpp after Combat446 (NOTES, w/, hr3/; r1 combat 1,161 B + r2 mixfile 689 B): mixfile Cache(Buffer) 0x595810 BYTE-EXACT (w/m_cache.cpp, hr3/shared/sha_straw.hpp; also SHAEngine ctor 0x595D10 and ??_GSHAStraw 0x595D40) but blocked: defined in the population, the accepted static Cache 0x595770 inlines it (20.31); the original only inlines Finder there, so its member Cache must be over the remaining budget: frozen attempt in r3-draft-not-landing/ (never land). Calculate_Projectile_Angle 0x47F9B0 91.63 (dy stored and reloaded), Wide_Area_Damage 0x47F6E0 75.89 shape 100 (frame hole), Explosion_Damage 0x47E2C0 (4,611 B) undrafted, MixList atexit dtor 0x5951E0 (236 B) and List<MixFileClass*> ??_G 0x595D60 need the MixList static with 0x595190 taken over.
- movie.cpp complete after Movies447 (0x5A0060-0x5A0B4F; plus GScreenClass::Blit 0x4E0C90, VQA callbacks, Find_Movie_File; 3,694 B): GScreenClass::Get_Input 0x4E09D0 82.81 (this/input esi/edi swap); Movie_Create (VQA_Unknown_005A1010) 0x5A1010 (1,107 B; inventory 31) undrafted: needs pop-1615 + pop-2213 joined (one TU 0x5A0B50-0x5A1FBF), VQAMovie ctor with Rect member construction, a guarded template Intersect (first call 0x41FDF0 out of line, second inline), a bool last-parameter rename, and a __fastcall Lock callback type for the VQAClass ctor. Bag-population hazard: removing a bag's first row can change what the next first source emits (pop-2972: fixed by giving 0x5B4BD0 the VECTOR_IMPLEMENT_* macros).
- Logic.CPP complete, keyboard/Ini/terrtype after Lane448 (NOTES, w/; r1-r5 7,890 B; the Scout444 "LZO" span was LogicClass): WWKeyboardClass::Message_Handler 0x532A60 82.43 (w/ka60.cpp; TibSun shape, VK 1/2/4, WM_CHAR after the mouse cases, Available() >= 2; the original calls Put out of line at WM_CHAR where ours half-expands it; next: measure the inline budget at that site, InlineLab398 method); INIClass::Get_Unicode 0x50EDF0 83.33 (w/iedf0.cpp; the two inline Get_String CRC temporaries share stack slots in the original, frame 0x5014 vs our 0x5028).
- Cell.CPP after Cell450 (NOTES, w/, hm/shared overlay with unknown_47c930/unknown_47cc10 declarations; ren1 + r1 bridge 2,821 B, r2 CheckBoxClass 351 B): Reduce_Tiberium 0x475DB0 76.24 (shape 98.34; inlined Union copies to dirty instead of coalescing), On_Bridge_Collapse 0x47C930 38.10 (Locomotor.Checked()->Is_Moving_Here form 34.48 / shape 89.03; this in edi, cellptr/next spilled), Kill_Illegal_Occupiers 0x47CC10 28.08 (first draft); undrafted Reduce_Wall, Wall_Update, 0x472540 Recalc_Attributes, Is_Clear_To_Build, veins, Place_Tiberium, Get_Height.
- Tactical.CPP after Tact451 (NOTES, w/, h/ overlay, sc.py; r1 Render_Shroud 0x6A3EF0 528 B; 33 open rows ~26 KB): Draw_Radial_Indicators 0x6AC420 78.52 (w/ri1.cpp, shape 94.44; cached zero in ebx; needs atexit 0x6AC7A0 `_$E86` from pop-88), Draw_Tiles 0x6A7BA0 49.20 (Coord_To_Pixel 0x6A29D0 and the lepton CoordStruct ctor stay out of line in the original; inline-budget probe w/pr/ says ~700-850 more units spent; same problem for Draw_Shroud, Draw_Tile_Shadows, Draw_Tiles(Cell)), Set_Tactical_Position 0x6A66B0 55.14 (needs 0x6A6640 merged from pop-2821), Get_Selectable_Object 0x6AA990 90.07 (stack slots), ctor 0x6A24B0 99.02. Debug drawers 0x6AB810 (to 0x6ABC1B) / 0x6ABC20 (to 0x6AC153) need body_bytes over the mid-instruction inventory splits 0x6AB9B1/0x6ABE0E; they carry Point2D::operator-= 0x6AC850. Tactical.CPP is still split over ~10 legacy populations: merge into pop-3267 before cross-inlined callers. Parked: inline-budget plateau.
- Cell.CPP after Cell452 (zero-byte handback; NOTES, w/, hm/shared overlay on 6e7a1bf57 to rebase): Recalc_Attributes 0x472540 85.71 (shape 99.72; ebx/ebp swap tied to the tunnel block; needs RA2_COORD_FROM_CELL_INLINE in 0x470490 or `Cell const &cell = MapCoords`; next: TubeClass creation shapes), Reduce_Wall 0x475FE0 90.03 (shape 99.04; const Adjacent_Cell wrapper, int counters, uninitialized `bool destroyed`; scheduling only), Draw_Shadow_Cast 0x4755D0 61.54. Draw_It 0x475680 needs a real IsometricTileTypeClass vtable (slot 39). Undrafted: Wall_Update 0x475960, Is_Clear_To_Build 0x4718B0, 0x471D10, veins 0x47A7A0/0x47AD00, Place_Tiberium 0x47C3A0, Get_Height 0x4706C0. One more zero-byte lane parks the unit.
- SpecialClass / sprite.cpp / PCX cache / MPLayer after Special455 (NOTES, w/, hm/, hmp/; r1 sprite.cpp Scale_Rotate 1,100 B): special.cpp 0x68B130 and MPLayer.CPP 0x5A71F0-0x5A7522 complete; PCX Draw_0068cf90 0x68CF90 84.41 (w/cf90_best.cpp, shape 97.55, 449/449; needs a bool-return rename spec (caller 0x5FED10) and OwnerDraw::Blend_Color moved to a small header; residue an ebx/edi swap of start_x vs the center/pixels group), brighten 0x68BCE0 80.46 (load schedule), Draw 0x68CE80 83.81, XMP_Is_Prime 0x5AA380 99.31 (jl vs jb). Parked after one more 0x68CF90 try; the rest are multi-lane plateaus.
- Path estimator (TibSun astar.cpp, 0x426E70-0x42BCF0) after Span454 (NOTES, w/, hm/shared; r1 Find_Path_Hierarchical + Heapify 1,824 B): Get_Movement_Cost 0x427110 97.04 (ebx/ebp swap), Try_Diagonal_Shortcut 0x428CF0 60.13 (explicit Next_Cell loops at the Follow_Path sites; never rewrite 0x427060), Optimize_Moves 0x4290C0 60.09, Find_Path_Regular 0x427370 undrafted. OWNER DECISION (21:40Z): FootClass slot 101's 5th parameter is bool (0x427831 pushes `mov al,[esi+8]`); a Mac lane delivers it as a standalone R rename across foot.hpp/aircraft.hpp/building_class.hpp and the accepted slot-101 definitions (codex3 told), then the 0x427370 prerequisites (height fields from unknown_30, guarded Map.Cells.Vector, typed +0x14 queue).
- VQA library span 0x717CE0-0x71DC10 after VQA453 (NOTES, w/; r1-r3 2,212 B; four TUs: facing pop-3344, VXL voxel pop-3511, VQAClass pop-3510, VQA option bits pop-3076): 0x71AFA0 88.58 and 0x71AD30 81.84 (the original keeps normal and shade byte in one stack slot; 0x71AD30 also needs Fill_Delta_Table3 defined before it), Read_File 0x719160 73.61 (palette loop compare jb vs our jl; frame 0x13c vs 0x114). The span is otherwise complete: parked.
- Walk/Mech/Rocket locomotors after Scout456 (NOTES, w/, hdr/; r1 Walk Mark_Head_To 876 B; ranking build/class-work/Scout456/UNITS.md + units_full.tsv, HEAD 51909ed5c): Walk Movement_AI 0x71E220 55.44 (w/best_71e220.cpp, shape 89.8, 1505/1507; ours gets the aligned frame `and esp,-8` from the two sin/cos calls, the original a plain sub esp,0x38; a one-call probe is unaligned at 66.58), Mech Movement_AI 0x5919A0 undrafted (aligned in the original: start there with the Walk draft), Rocket 0x63DE10 88.89 and Move_To 0x63EA80 59.32 (passed to Rocket458).
- Path estimator after Path457 (zero bytes past ren1 1df043914; NOTES, w/, hm/shared overlay: CurrentCellHeight/DestCellHeight split, typed +0x14 PriorityQueue, guarded MAP_VIEW_DECLARE_CELLS, UnitTypeClass Passive +0xBA4; 0x427D40 exact rides with the split): Find_Path_Regular 0x427370 78.18 (shape 98.77; height via CoordStruct(foot->Coord).Z fixed the frame; residue stack slots and neighbor_cell/node_index*4 in ebx/ebp), Get_Movement_Cost 0x427110 97.04 (inc ebp position vs ebx/ebp swap), Optimize_Moves 0x4290C0 60.09, Try_Diagonal_Shortcut 0x428CF0 60.13. PARKED: resume only with a fresh register-allocation approach for 0x427370.
- Rocket locomotor / LaserDraw after Rocket458 (NOTES, w/, v/, dr/; r1 Rocket 1,227 B, r2 Laser Draw_All 32 B): Rocket 0x63DE10 88.89 (square-multiply registers), Move_To 0x63EA80 59.32 (LinkedTo->Type read before Rules; rocket in edx, &unknown_18 in ecx), Process 0x63DE90 undrafted (true extent to 0x63E7D0 with a 5-entry jump table at 0x63E7B4; NOTES maps the five states), Laser Draw_It 0x5334F0 / house-colour variant 0x533C80 undrafted (NOTES maps TibSun laser.cpp: function-static _glow_offsets, guard 0xA6E539).
- Mech/Walk Movement_AI after Mech459 (zero bytes; NOTES, w/): Mech 0x5919A0 76.55 (w/best_5919a0.cpp, frame 0x5c matches, shape 96.69; w/shape_5919a0.cpp 75.77 with exact Direction but frame 8 short; residue: locals 4-8 bytes off, LinkedTo reload registers; landing needs RA2_COORD_AS_CELL in the Mech unit's first draft), Walk 0x71E220 55.61 (still the aligned frame; not the Move_Coord form or frame size: compare the 8-byte stack accesses of the two original bodies). Unit 0x593680-0x594310 identified (facing-wrapper operators 0x5940B0/0x5940D0/0x5940F0, tolerance test 0x594110, rotate step 0x594140, vector rotate 0x5941B0, __fastcall trajectory 0x593870 2,101 B; the small rows land only with 0x593870). One more zero-byte lane parks Mech/Walk.
- RulesClass::Audio_Visual 0x643E10 (11,166 B) after Rules460 (NOTES, w/, ov7/, mkbest.py): w/P13.cpp is BYTE-EXACT (3069/3069) but reads ShroudGrow and ShakeScreen directly while every other Sound/Int/Bool/Double read goes through a named local: two hand-picked statements. w/V3.cpp (every read of those kinds through a local) is 99.87 (CloakSound +0x5C0 register tie-break). Needs: ConditionGreen `unknown_1360 = 1;` between AllyReveal and ConditionRed; Get_Type<AnimTypeClass const> second instantiation 0x653E40 (EMPulseSparkles/OreTwinkle const); rename AnimClass ctor 0x420110 to take AnimTypeClass const * (anim.hpp + map_techno.hpp duplicate, 15 sources); move 0x653DF0/0x653E40 from pop-1647 into pop-2672. OWNER DECISION (22:25Z): the 2026-10-27 one-rule-per-kind ruling stands; P13 does not land as is. A time-boxed lane looks for a natural rule (NOTES untried list: TibSun casts on PoseDir and the light lines, another source of ~12 locals of budget with int/bool direct) and lands the rename prerequisites meanwhile.
- Rocket Process / LaserDraw after Rocket461 (zero bytes; NOTES, v/, w/): Process 0x63DE90 67.67 (v/best_process.cpp + v/pre_a.h; shape 94.60; 0x63DCF0 must re-land in the nested-if form v/best_dcf0_nested.cpp (byte-identical alone) so it stays out of line at 0x63E1F3/0x63E470; `bool exploded` merges the return block; blocker: the original spends more inline budget between case 2 and case 4 (pitch CoordStruct ctor 0x41B630 out of line); the case-4 Length() 0x41B780 cast suggests UnknownVector3 is CoordStruct). Laser Draw_It 0x5334F0/0x533C80 blocked on surface.hpp slot 13/15/16 parameter types (parked surface family) and the _glow_offsets atexit dtor 0x533C70 (element type has a destructor). 0x63DE10 88.89 unchanged. One more zero-byte lane parks Rocket.
- Warhead/TEvent/Tunnel after Mix462 (NOTES, tu/; r1-r4 ~6,240 B incl. switch tables): Tunnel Stop_Moving 0x6EFDE0 82.91 (tu/sB.cpp; identical code, frame 0x24 vs 0x20, the 8-byte Point2D temporary keeps its own slot), Tunnel 0x6F0730 undrafted, Egos 0x4B37C0 not started.
- Egos / Tunnel residue after Egos466 (zero bytes; NOTES, eg/, tu/): Egos 0x4B37C0 86.20 (eg/BEST_e7.cpp scored with prefix eg/BEST_preA.cpp, which rewrites accepted EgoClass::Advance 0x4B3670 in TibSun if/else form, still exact, and must land with it; residue: label-copy loop reloads *text, frame/step spill slots, two loads in inlined Blend_Color; body_bytes must include the switch tables 0x4B42DC-), Tunnel 0x6F0730 91.14 (tu/BEST_6f0730_d2.cpp; coord.X copied into the slot shared with cell before sin; LinkedTo in esi at Take_Damage), Stop_Moving 0x6EFDE0 82.91.
- WideString / missile.cpp after Mix465 (NOTES, w/, ws/mk.py whole-population builder; r1/r2/r4 716 B; r3 superseded): missile.cpp unit 0x593680-0x594310 is TibSun missile.cpp: Projectile_Motion 0x593870 (__fastcall, RA2 adds a 4th bool) 99.22 (w/best_593870.cpp, 640/640); face.h/velocity.h helper copies 0x5940B0/0x5940D0/0x5940F0/0x594110/0x594140 exact from the same file, Set_Pitch 0x5941B0 99.11; residue three equal-cost orderings (Z load after a store in Set_Pitch and Get_Pitch 0x41B6E0; sub esp,8 in the COORD_NONE branch; delta-to-velocity copy order); landing needs shared DirType (dir_type.hpp), TPoint3D/Coord, TVelocity2D/3D headers (building_type_class.hpp's minimal TPoint3D clashes). WideString not started: Narrow_Copy 0x771280, 0x7715D0, 0x7716D0, 0x76CD40, 0x76EA90 (true bounds from disassembly; inventory rows are short). FacingClass 0x4B7DF0, SoundControlsDialog 0x688DA0 not started.
- OWNER DECISION (23:20Z): codex3 r243 dir_type.hpp additions (Dir256 enum, DirType(Dir256), From_Dir256, Snap_To_256; TibSun facing forms) and r242 shape_file.hpp RA2_SHAPE_RECT_SOURCE guard approved; the owner lands both from codex3's private packets. codex3 standing rule: small additive or guarded shared-header changes go out as plain P deliveries with a note, not as private H drafts.
- LdPrgMgr / LineTrail / small residue after Small467 (NOTES, w/, lt/, calls2.py; r1 Crate 841 B, r2 Slider 625 B): LdPrgMgr draw 0x535BF0 57.39 (3,978 B; calls all in order; inline helpers for the sprintf chain/name/unit areas/upper-case loop/string chains move the budget; Pixel_To_RGB 0x536ED0 must be an inline __fastcall returning RGBClass; literal Load_String line numbers; needs declarations 0x6F2400/0x6F2420/0x6F2450/0x6F2470/0x6F25B0/0x6F1AE0 and the 0x7DF370 filename globals), 0x5359E0 61.74, LineTrail::AI 0x539530 66.06 (ActiveSlot re-read from memory), LineTrail::Draw 0x5395C0 mapped (needs DSurface 0x4AE9C0 and global 0xA6E948). LayerClass 0x534D40/0x535530 are handwritten assembly; GScreen tail 0x4E1140-0x4E1240 is an ownrdraw string class. Zero-byte rename todo: Cell::Unknown_00493C80 is TibSun CrateClass::Get_Crate.
- Near-miss pass NearMiss469 (NOTES, w/, x/r2_failed, ht/ overlay; r1 Get_Unicode 532 B): Reduce_Wall 0x475FE0 BYTE-EXACT when 0x476AC0 CellClass::Adjacent_Cell(unsigned) names its result (`Cell adjacent = Adjacent_Cell(cell, facing); return Map[adjacent];`, w/ac_B.cpp; 0x476AC0 stays exact) plus rw_E1.cpp, but that breaks the accepted inliners 0x4732D0/0x473700 (90.03), 0x47A670 (63.16), 0x47BFA0 (64.29); TibSun model (const Adjacent_Cell real, non-const inline wrapper; rename to ?Adjacent_Cell@CellClass@@QBEABV1@I@Z) fixes 0x47A670 but not the others. Tunnel 0x6F0730 95.57 (w/tu_BM2.cpp, shape 100; frame slots only). Tactical ctor 99.02 needs a type for +0xac/+0xad. Message_Handler 82.43: WM_CHAR body is Put_Char 0x5326A0 (InlineLab398 budget next). Get_Selectable_Object 90.07, Get_Movement_Cost 97.04, XMP_Is_Prime 99.31, Rocket 0x63DE10 88.89 unchanged.
- Rocket Process after Loco468 (zero bytes, but 67.67 -> 97.51 in population; NOTES, v/best_process_w1b.cpp, u/pop_w1.cpp, lab/): frame exact via file-static helpers (switch-case temporary rule); open: case-5 tail (~10 instructions: unknown_50 loaded early; diff kept on the FP stack), 0x63DE10 alone 88.89 (multiply order; inlined copies match), two ground-distance helpers differ only in X*X/Y*Y order (suspect), UnknownVector3 Length() cast placeholder, bind ctor copy 0x41B630, re-land 0x63DCF0 nested. OWNER DECISION (23:55Z): the second zero-byte lane would park Rocket, but the 30-point jump earns one more continuation lane (Rocket473).
- Wstring/WideString complete after Missile470 r1 (8417be190; pops 2316+3532 joined, one TU). UDPInterfaceClass::unknown_slot16 0x76CD40 (1,685 B, Winsock handler) 97.73 (Missile470 u/best_76cd40.cpp, 573/573; the default port is a 16-bit read of an int global; u/alt_76cd40_m32.cpp fixes that region but swaps the two debug-print blocks; new globals unknown_port_7f60d4/unknown_b2af1c to move into udp_interface.hpp; not yet checked in pop-2675). missile.cpp Projectile_Motion 99.22 / Set_Pitch 99.11 unchanged (rebase on dir_type.hpp from 400116110).
- WinStub / except / SoundControls after Scout471 (NOTES, w/, hdr3/; r1 SoundControls 1,787 B, r2 except.cpp Dump_Exception 2,556 B, r3 WinStub 248 B; ranking build/class-work/Scout471/UNITS.md + units_full.tsv on cf6b5aa1f): Windows_Procedure 0x7375A0 (1,203 B) exact but for one `test al,al` on Is_Movie_Active 0x5A1ED0, whose accepted definition returns int (mov eax,1; a bool definition is 69.57) and MSVC mangling encodes the return type, so a caller-side bool prototype will not link to the same symbol — open question, not landable as is (w/wpv_a.cpp, w/pre_focus.cpp; Focus_Restore needs MAP_VIEW_DECLARE_WINDOW_PROC). Build_Version_String 0x737B50 needs seed 0x737B20 moved from pop-88 into pop-2811. 0x738190 screenshot writer waits on the surface family. Next fresh units: WorldDom.cpp 0x7683B0 (3.7 KB), Scenario residue, LoadDlg, MonoClass, CD.CPP.
- Cell.CPP after Adj472 (r1 Reduce_Wall 1,007 B, 7b22ff6bb; NOTES, w/, dr/, cat.py/var.py/sc.sh): OWNER DECISION (00:05Z Nov 2): the per-site const casts that pick the const or non-const Adjacent_Cell overload (bridge `back` sites in 0x4732D0/0x473700, 0x47A670's non-const call) are an overload choice reflecting the original's object constness, like an inline split, not steering; accepted. Wall_Update 0x475960 61.27 first draft (w/wu1.cpp, joined w/jx_a.cpp; the original keeps a dead half-inlined Union(474eb0, 475100) and calls 0x42ADD0/0x47D040/0x453E40 out of line). Tunnel 0x6F0730 still 95.57 (frame map in NOTES).
- Near-miss pass NearMiss474 (NOTES, w/, hv/, u/; r1 UDP 0x76CD40 1,685 B): Tactical ctor 0x6A24B0 code-exact in w/k8.cpp + hv/k8 overlay, needs +0xB0..+0xBC as four ints (TibSun TacPixelX/Y, LastTacPixelX/Y) and +0xAC/+0xAD as one 2-byte member of a class with an inline ctor; ~20 accepted sources read unknown_b0 as a Point2D (field-type change across them, each re-proved). XMP_Is_Prime 99.31 (true length 427; joined w/j0.cpp, LEN=427), missile.cpp 99.22/99.11 and Get_Pitch 0x41B6E0 97.14 plateau (untried: an inline-boundary point in Get_Pitch or the delta conversion), Get_Movement_Cost 97.04.
- Rocket Process landed after Rocket473 (fa5547192, 2,337 B code / body_bytes 2368; RA2_COORD_LENGTH guard in coord.hpp, CoordStruct::Length 0x41B780 and ctor 0x41B630 bound by @ref). OWNER NOTE: r1 keeps two ground-distance helpers that differ only in X*X/Y*Y order; real C, but probably not the original's form; revisit (TPoint2D::Length under RA2_POINT_LENGTH untried). 0x63DE10 stays unaccepted (defined `inline` in the unit, so no copy is emitted; 88.89 standalone, which register is squared first). Laser Draw_It needs a surface slot 13/15/16 typing round across the XSurface slot sources and the EBolt 0x4B1850 / RadBeam 0x635810 callers first.
- OWNER DECISION (00:55Z Nov 2): Tactical +0xAC is `struct UnknownFlags` (two bools, default ctor clears, empty NoInitClass ctor), landed with the Tactical ctor 0x6A24B0 (85b0e7cd3). No source names the type (TibSun: `bool field_58, field_59; /// Unused`); store order in both ctors is the only constraint and this is the one form consistent with both, so it stays an explicit hypothesis under an honest unknown name, to be replaced if a reader or TibSun evidence appears. Also: codex2 r2813 system_timer.hpp operator() declaration approved (one-line additive).
- Options.CPP complete and ObjectClass after Opts476 (NOTES, w/; r1 Options 3,117 B, r2 Coord_Bounds 225 B): ObjectClass 0x5D5090 nearest-object 96.30 (shape 100; FP multiply order in the first branch), 0x5D5010 average coord 75.00 (edi/ebx swap), Video_Mode_Proc 0x543CF0 67.69; not attempted: slot 73 0x5D31C0 (32.41), Main_Options_Proc 0x542590 (84.05), IPX proc 0x542D60, CCToolTip::Show 0x46DFC0 (98.95). Note: a declaration added to dialog_create.hpp breaks the fragile 0x73FEE0 (WOnline includes it).
- Surface slots / Laser / reinf after Mix479 (NOTES, miss/; R typing 986bcdc69, r2 Laser Draw_It 1,906 B 81bb03f80): Create_Reinforcement 0x63A050 99.55 (only loop 1's X sum loads the table operand first; untried: how the drop-pod block reads newcell), Draw_House_Color 0x533C80 43.84 (shape 77.17; own static table + atexit 0x534340 `_$E72`/`_$S71`; frame 0x6C vs 0x60), reinf 0x63A880 (1,567 B) undrafted (Reinf437 NOTES), TeamClass residue 0x6BDAA0/0x6BE440/0x6BE010 untouched. Rules: a bare-`ret` atexit dtor means an empty element dtor; a table filled from registers means elements built from temporaries of another type.
- WDT Voices complete and WOL main / ModemHost after Misc478 (NOTES, w/, hdr2/, hdr3/, cat.py; r1 Voices 1,870 B a9141cff9): Wonline_Main 0x73A300 94.14 (w/wm_m2.cpp + hdr2/shared/wol_main.hpp, body_bytes 884; unit 0x73A0F0-0x73A6F0 is its own TU, pop-399, not wonline.cpp; take over inline helper unknown_session_kind 0x73A2E0 from pop-3353; residue: `xor eax,eax` after `pop ebp` in the last exit; 0x73A680 unreferenced ??_E for a 12-byte BSTR class), ModemHost::Select_Multi_Map 0x59B090 96.02 (w/smm_d.cpp + hdr3/shared/modem_host.hpp, body_bytes 557; register ties in the non-2 path), SelectRandomMap 0x59B2C0 (~650 B) undrafted. Multiplayer.cpp skipped (Coop122 inline-budget conflict with accepted ctor 0x5B6CD0, CounterClass dependency).
- ColorScheme / MonoClass / HVA / Scenario after Scen480 (NOTES, w/, hdr5/, mkj.py; r1 940 B, r2 503 B, r3 362 B): Scenario.CPP plateaued (NoInit ctor 0x65B780 64.00, Wait_For_Players 0x65C520 90.40, Clear_Scenario 0x65D370 99.32 at true length 1140, jae vs jge; Scan_Place_Object 0x660B60 47.56); LoadDlg.CPP remaining rows are LoadOptionsClass (Windows lead scope r63/r65); MonoClass::Print 0x59E6D0 61.54 (hoisted `text - x` base), Mono_Dialog_Proc 0x59DCE0 60.23 (true extent 1148; blocked with Mono_View_Page 0x59DA60's OPEN bound; shared tail of four speech keys kept first in the original), Mono_Window_Create 0x59DB30 97.06. Rules: ColorScheme ramp builders need the double-returning sin/cos helpers (unknown_sin_4ba480/unknown_cos_4ba4d0) for qword int-to-double stores; named RGBClass temporary for store order.
- Near-miss pass Near481 (NOTES, w/BEST_*.cpp, lst.py; r1 Closest_Object 291 B): CCToolTip::Show 0x46DFC0 98.95 parked (VC6 orders loads off one base by falling offset; only the original's X block goes the other way), Tunnel 0x6F0730 96.31 (Point2D delta local fixes dx; cell/x slot [0x10] vs [0x0c], one extra 4-byte object or slot order), Main_Options_Proc 0x542590 85.62 (LEN=1996; register assignment only), Egos 0x4B37C0 86.44, ObjectClass 0x5D5010 75.00.
- OWNER DECISION (02:05Z Nov 2): LoadOptionsClass (LoadDlg.CPP) is released to Mac lanes: the 'Windows scope' label came from the old Windows lead (r63/r65), which stopped 2026-10-30; no Windows worker holds it (LoadDlg485).
- reinf / Laser house colour after Reinf482 (zero bytes; NOTES, miss/, t/probe.sh): chrono reinforcement 0x63A880 94.17 first draft (miss/chrono_63a880_94.17.cpp, shape 98.46, scored in the reinf population; leave infantry_piggyback_ptr.hpp out and define Query in comip's real _QueryInterface shape so both queries inline; residue: Move_To argument (`CoordStruct(coord)` fixes that block but swaps esi/edi, 81.77) and the final commence loop's first unlink (lea + indirect store)), Create_Reinforcement 0x63A050 99.55 (drop-pod newcell forms tried; loop 1's X is table-first in ours), Draw_House_Color 0x533C80 54.51 (miss/house_533c80_54.51.cpp; original branch order; frame 0x6C vs 0x64; this in ebx). TeamClass residue untouched. Rule: `RGBClass(r, g, b)` evaluates its arguments right to left after all three doublings are loaded.
- WOL main / ModemHost after Wol483 (NOTES, w/; r1 Wonline_Main 884 B + 0x753F50 __fastcall rename, r2 Select_Multi_Map/Select_Random_Map 1,217 B, r3 Send_Options 772 B): ModemHost::Dialog_Proc 0x598FA0 90.60 (w/dp_r.cpp; TibSun outer switch order; only Read_Tech_Level still inlines, needs ~one more small helper of budget before it; BM_GETCHECK reader edits unchecked against the readers' rows), 0x73A680 ??_E (106 B) unattempted.
- OWNER DECISION (02:50Z Nov 2): codex1 unblocked. Conquer169 NOTES and drafts copied to coordination owner-reference/Conquer169. A guarded Tracker 0x4128A0 declaration in codex3's foot.hpp, or a unit-only header, is allowed as a plain P delivery (standing small-header rule).
- LoadDlg.CPP complete and Multiplayer after LoadDlg485 (NOTES, w/, f/, hdr/; r1 1,764 B, r2 Dialog 2,068 B, r3 Init 0x513290 328 B, r4 0x5B7840 216 B): Multiplayer 0x5B8490 71.06 (shape 100 on r4's sources; Trim_Leading/Trim_Trailing " " temporaries get separate slots in the original), 0x5B7CE0 (677 B) undrafted (CounterClass), 0x5B8480 9 B InitializerBase ctor COMDAT, caller unidentified. Rules: a wrong or mis-mangled string literal can still score 100, and only check_plans refuses it; in Dialog, Pick_Filename and Clear_List stay out of line on budget alone.
- TeamClass after Team486 (NOTES, w/, t/; r1 0x6BE440 599 B): 0x6BE010 76.32 (needs ~4 more inline-candidate sites after the leader search to keep 0x6BDD80 out of line, rule ≥10 sites; probes 84.56), GatherAtEnemy 0x6BDAA0 95.67 (Center_Coord temp slot +0x44 vs ours +0x28; cell copy store after push esi), chrono 0x63A880 94.17 unchanged.
- WDT/NetDlg/stlscore after Scout484 (NOTES; r1-r6 ~3.7 KB; ranking build/class-work/Scout484/UNITS.md + units_full.tsv on ac309f39a): MapSizeGameOption::Describe 0x728AB0 77.48 (one extra 4-byte local in the original), HouseTypeClass ctor 0x4F90F0 95.24 (second inlined HouseTypes.ID loop registers), Map::Territory_At 0x72A660 79.49 (needs wdt_map.hpp unknown_24 as Surface*), WDT vector template rows (#8/#9, 26 rows) untouched. Dropship 0x4A6B90-0x4A95BF is one ~10.8 KB function; Ion 0x51F150/1F0/290 are guarded atexit dtors needing a pop-08 statics rewrite. Rule: VECTOR_IMPLEMENT_* guards only work when the population's first source defines them before its includes.
- OWNER DECISIONS (03:20Z Nov 2), resolving rulings that blocked near misses:
  (a) coord.hpp: CoordStruct HAS the out-of-line (int,int,int) constructor 0x41B630 and Length 0x41B780 (UnknownVector3 is CoordStruct). Rocket473 landed both as guarded CoordStruct members (RA2_COORD_LENGTH, @refs `??0CoordStruct@@QAE@HHH@Z=0041b630`, `?Length@CoordStruct@@QBEHXZ=0041b780`). Other units use the same guard. This unblocks Particle Fire AI 0x60C7C0 and BuildingLight slot 67.
  (b) RadarClass +0x1244 is a Rect (`unknown_1244`). Evidence: Plot_Radar_Background 0x631600 is exact with it, and the ctor 0x62EDE0 is exact with `unknown_1244(0,0,0,0)`. Deliver it as one round with the ctor rewrite, checked with check_plans --build.
  (c) map_view.hpp and other shared headers: guarded additive declarations are allowed under the standing rule. No per-case ruling is needed.
- TeamType / audio / Voc / UICmnds after Mix488 (NOTES, w/; r1-r4 2,515 B): Add_Message 0x5B4DA0 98.48 (memset/wcscpy register block), UICmnds 0x6F81B0 99.60, RadBeam 0x6358D0 96.95 (colour channel pack order), Find_Disk_Drive 0x715090 ~80 in its real population (anchor 0x715230; the old 86.33 used a local Drive_Info copy), ModemGuest Init_Dialog 0x596540 85.97, GScreen Get_Input 0x4E09D0 82.81 (this/input swap), AudioTimeSpan::Format 0x4039C0 79.73, Voc_Static_Save 0x714A90 74.12. Skipped: 0x40CE70 globals bag (whole-unit takeover), HashString thiscall members 0x4E1140-0x4E1240 (hash_string.hpp declares fastcall free operators at stub addresses: rename first), IPX span (unidentified class), Skirmish 0x6829F0. 0x6C03E0 is the DynamicVectorClass<TeamTypeClass const *> ctor (accepted under a placeholder name).
- Small residue after Small487 (NOTES, w/; r1-r9 ~3.4 KB): MSFont::Print 0x5B44F0 99.17 (first clamp compare ja vs jg: unsigned type), OverlayTypeClass 0x5DD000 87.16 (RGBClass(0,0,0) ctor 0x432D70 out of line in the ore branch), WWMouseClass::Process_Mouse 0x773400 59.17 (needs Surface slot 26 to take Point2D by value, TibSun entry_64: a rename spec first), MSEngine::Add_Rect 0x5B3110 42.71. Not done: Campaign ctor 0x725F40 (+ copy 0x726FD0), WDTSel 0x7302B0/0x730340 (callers first), MPSiegeTeam 0x5ABF60/0x5ABF70 (rdtsc: likely original inline asm), ObjectType 0x5D5790 (move initializer 0x5D5750 from pop-08 into pop-2504), TextLabelClass::Draw_Me 0x6F1620 (layout header). Rule: pick a new row's population by which header statics its includes emit (.CRT$XCU in the candidate .obj).
- WDTMap / WDTState after Wdt489 (NOTES, w/; r1-r3 2,109 B): WDTState() 0x72BEF0 35.15 (VectorClass::operator= inlined where the original calls 0x72CAC0; the temporary's ctor stays out of line), WDTState::unknown_72c3b0 0x72C3B0 57.30 (registers), unknown_72c490 0x72C490 (~1.3 KB) undrafted, MapSizeGameOption::Describe 0x728AB0 77.48 (90.76 variant adds a temporary), HouseTypeClass ctor 0x4F90F0 95.24 plateau, WDTMap loaders 0x729510 (~3.4 KB), 0x72A280, 0x72A880 (Centroid/VectorCursor helpers land with 0x72A880); 0x72A5E0 (accepted in pop-957 as UnknownNamedValue) is the AnimationPalette ctor copy. wdt_state.hpp is in the 0x73FEE0 closure (guard WDT_STATE_DECLARE_CONSTRUCTORS); WDTTerritory must keep its unknown_0c/unknown_15[] arrays for MapSeedClass::Apply_WDT_Territory 0x578BC0.
- VQA32 library / ABuffer tail after Abuf490 (UNITS.md, NOTES, w/, prefix3.cpp; r1 unvq.cpp 2,067 B): the "[ABuffer]" span 0x775B60-0x781FF0 is ABuffer.cpp plus the Westwood VQA32 player library (audio, buffer_, config, drawer, dstream, loader, task, timer, unvq); all C files complete except loader.cpp, task.cpp (VQA_Reset 0x77C7D0) and unvq.cpp. 0x77EDD0-0x781571 is genuine handwritten assembly (AudioUnzap, VQA_LCW_Uncompress, sosCODEC 0x780560/0x780581, ASM_UnVQ_*, cpuid/rdtsc/FPU helpers; TibSun ships them as .asm): handwritten-assembly ledger, then linker thunks and CRT. Open: UnVQ2_C0_4x4_TRANS 0x77D940 99.16 joined (w/jp/o0213.cpp; opaque-tail src in edx vs ecx; byte-exact alone but the tails merge in the population), UnVQ2_C0_4x4_KEY 0x77DD90 82.90 and 4x2_KEY 0x77E9E0 82.53 (src in ebp vs ours edi), C4_4x4 0x77D0C0 74.04, C4_4x2 0x77D5B0 86.84, Load_CBPZ 0x77B140 96.77 plateau; loader.cpp misses to rescore joined.
- WDTState / WDTMap after Wdt492 (NOTES, w/, x/729510.dis; r1 1,554 B, r2 Load_Anim 651 B with Get_Drawer 0x72A510 under #pragma auto_inline(off), since the original never inlines it): WDTState() 0x72BEF0 36.36 (w/ws1.cpp), loader 0x729510 (~3.4 KB) mapped in NOTES and undrafted (resume at x/729510.dis line 700), loader 0x72A880 (~1.6 KB) + Centroid/VectorCursor helpers not started (move 0x72A5E0 into pop-3590 with them).
- Map.CPP second half after Map491 (NOTES, w/, hdr/, u.py/us.sh/unrec.py; r1 2,123 B, r2 Closest_Passable_Cell 0x568ED0 438 B, byte-exact under the TPoint2D Cell model): Pick_Random_Tile_Variant 0x55D640 71.98 (block layout; needs hdr/ overlay lines), Place_Shore 0x55CEF0 84.78, Get_Bridge_Zone_Connection_Cell 0x564F70 85.15 (was 91.09 under the old model), Get_High_Ground_Mask 0x55BD70 49.58, Mark_Fill_Area 0x567710 84.49, Closest_Edge_Cell 0x5689D0 43.05. Rules: rescore old misses after a Cell model change (0x568ED0 became exact with no edits); never redeclare a class array the unit already defines (an empty `_$E` initializer renumbers the unit's statics).
- VQA32 loader after Vqa493 (NOTES, src/, hdr1/, w/join.py; r1 Load_VQF 0x779E90 1,196 B, VQA281's old draft, exact when joined, 83.69 standalone): VQA_LoadFrame_Internal 0x778950 99.79 (3,397 B; own `stopframe` local; VPKZ case calls Load_VPTZ; residue [edx+edi+8] vs [edi+edx+8] in both inlined ReadData helpers), Load_MFCI 0x77A4C0 84.25, Load_MSCI 0x77A940 78.10, Load_CBPZ 96.77, VQA_Reset 0x77C7D0 75.68, UnVQ2 TRANS 99.16 / KEY 82.90 / 4x2 KEY 82.53. Unit nearly exhausted.
- Cell-model rescore after Map495 (NOTES with full table, w/, hdr*/; r1 Place_Firestorm_Wall 0x56A480 478 B; RA2_COORD_FROM_CELL_INLINE now in the Map unit's first source): Place_Wall 0x56A660 92.26 (w/pw1.cpp; inner placement step: Y computed first into dx in the original), Find_Bridge_Span_End_Cell 0x5653C0 73.28 (needs RA2_POINT_LENGTH; stack homes and loop layout), Tactical Draw_Wall_Placement 0x6A6290 78.49, Spread_Tiberium 0x478A40 (85.84 old) needs a rename first (0x478BA0 takes TiberiumClass *, not bool), Cell Is_Near_Tunnel pair (static 0x47CFC0 must inline; defined later in the unit). Follow-up: Map drafts using Cell_Coord/Cell_Center where TibSun writes Coord(cell)/Unlimbo(cell) are worth one retry.
- WDTMap after Wdt494 (NOTES, w/g1.cpp, hdrg/, pl/p1.json; r1 Centroid += / Average 108 B under CENTROID_DECLARE_MEMBERS): loader Map::Load 0x729510 (3,440 B) 99.81 (one SideBar X load order; header overlay hdrg/ keeps the other 28 rows accepting; needs RA2_RECT_POINT_INLINE in the first source 0x728FD0, which must build on r1's version of that file), INI builder 0x72A880 (1,664 B) mapped in NOTES, needs a shared TRect<int> (COMDATs 0x72AF50/0x72B090/0x72AF70/0x72A7B0 land with it).
- Near497 (zero bytes; NOTES, lab/, w/, pl/): Map::Load 0x729510 99.81, VQA_LoadFrame_Internal 0x778950 99.79, Place_Wall 0x56A660 92.26 all unchanged. Lab: for `local.X + this->member.X` VC6 always makes the member the add destination; VC6 normalises address trees ([edx+edi+8]). Untried: unknown_44 read through an inline accessor of another type; Data element type or macro ReadData helpers. PARKED: one more attempt only with a new mechanism.
- Joined rescore after Rescore496 (zero bytes; NOTES has the full 98-entry table, w/rs.py joined scorer with @ref _$E/_?$S renumbering, w/fixinc.py, f/ fixed copies): every compiling old draft joins at its recorded score (genuine register/schedule misses), except BuildingType Get_Draw_Rect 0x45E290 (98.65 standalone, 83.07 joined in pop-3080: something inlines in the unit), BuildingLight ctor 0x432FC0 (30.00 -> 65.49 joined), Tunnel Stop_Moving 0x6EFDE0 (82.91 -> 85.71). About 25 old drafts no longer compile on HEAD (renamed headers/members; list with blockers in NOTES). Joined scoring needs _$E/_?$S renumbering, or old names bind to other units' symbols.
- Map/Cell after Map498 (NOTES, w/, hdr*/; ren1, ren2, r1 Is_Near_Tunnel_ES 427 B): a const method reaches Adjacent_Cell 0x476AC0 through the const inline wrapper (one extra inline level, which changes the /Ob2 budget), so Is_Near_Tunnel_ES had to become non-const. Making 0x476AC0 itself the const out-of-line form, as Westwood CELL.H does, breaks five accepted rows (refused). Is_Near_Tunnel_NW 0x479CF0 88.10 (last two Has_Tunnel sites must both be out of line), Spread_Tiberium 0x478A40 85.84 (registers in inlined 0x476AC0), Destroy_High_Bridge_Span 0x558660 76.36 (frame 0x3C vs 0x4C, twin of 0x553000), Find_Bridge_Span_End_Cell 0x5653C0 73.28 (TibSun while(true) shape but no entry jmp). Undrafted: 0x562F50 bridge collapse (3,568 B).
- ObjectType / MSFont / WDTMap builder after Mix499 (NOTES, w/, hdr/; r1 MSFont::Print 372 B: the unsigned literal written on both sides, `(0 >= oem - 33u) ? 0 : oem - 33u`; r2 ObjectTypeClass::ObjectTypes init 0x5D5750 + guarded atexit dtor 0x5D5790 149 B). OWNER DECISION (05:15Z Nov 2): r2 renamed ObjectTypes to the class static member inside the whole-population plan, not as a separate apply_rename spec. Accepted, because only same-population sources name the symbol and the check passed. WDTMap INI builder 0x72A880 62.65 joined, parked (w/ini_best.cpp, hdr/: new trect.hpp TRect<T>, guarded VectorClass::Count(), CDFileClass(Wstring const &) 0x46FD60; residue is the inline budget reversed: the original inlines List<INISection*>() and calls the cursor ctor 0x72B090 and operator= 0x72AF50 out of line). TextLabelClass::Draw_Me 0x6F1620 decoded in NOTES; needs a real TextLabelClass : GadgetClass header (the ctor 0x6F15C0 uses a stand-in, pop-31). Campaign ctor 0x725F40 not attempted.
- Ports / ID header after Port500 (NOTES, x/, h/; r1 PhoneEdit Dial/Add 825 B + HouseTypeClass ctor 600 B, r2 RulesClass::Sides 428 B; RulesClass::Sides needed the `"Sides"` literal @ref, which was the real cause of Rules23's .rdata refusal): Read_Scenario_Descriptions 0x670C50 94.54, TAction show-text 0x6B0440 92.86, Planning_Can_Add 0x615ED0 92.00 (needs a __fastcall rename), Get_Draw_Rect 0x45E290 (joined, Free_Buildup 0x45E920 inlines where the original calls it; the reason is still open), BuildingLight ctor 0x432FC0 76.62 natural (byte-exact with a diagnostic probe: needs one natural inline site after the second Coord_Along_Facing). Blocked ports listed in NOTES (0x66E380, 0x5135F0, 0x4141C0, VoxelAnim, Tactical).
- MapClass::Collapse_Cliff 0x562F50 after Bridge501 (zero bytes; NOTES, w/best_z1.cpp + EXTRA 54fab0=w/fab0a.cpp, hdr/; TibSun map.cpp ~l.9745): 86.66 (shape 97.92; first half 0x562F50-0x563645 byte-exact; diagnostic w/q1.cpp 90.77 with one forced out-of-line site). Blocker: the subzone-index call sites: the original calls 0x54FAB0 at sites 1-3 and inlines it at site 4; a Fine_Subzone reference helper (unevidenced hypothesis) reproduces 1, 2 and 4, but site 3 still inlines. The original's remaining inline budget at site 3 is far below ours. Rules: VC6 evaluates arguments right to left, so only an assignment argument comes first (lab-confirmed).
- ID sweep after IdSweep503 (zero bytes; NOTES table): Port500 already captured every ID-residue miss. Best remaining misses with inlined vector calls are Planning 0x617AF0 at 90.00 and SuperClass::Grant 0x69CCF0 at 89.32. About 15 more old drafts no longer compile on HEAD (list in NOTES).
- TextLabelClass after TextLabel502 (ren1 real class, r1 Draw_Me 439 B): Campaign ctor 0x725F40 parked at 86.69 joined (w/campaign_best_8669.cpp; ternary CSE folds two chains; edi/ebp in the INI tail; GENERIC_LIST_IMPLEMENT_CONSTRUCTOR makes it exact but breaks four other rows, so it is not the original shape). Follow-up zero-byte retype: MessageListClass's UnknownMessageNode (message_list.hpp, pop-3603) is TextLabelClass.
- SuperClass after Super504 (NOTES, w/, t/j.py gs.sh; r1 0x69CB30 301 B + Discharged 0x69D090 765 B). OWNER DECISION (06:20Z Nov 2): unknown_69ca70 uses `Delete((AbstractClass *)this)` upcasts at every Delete site. That is one form applied across the function, a natural base-pointer call, so it is accepted and is not steering; the equivalent fallback (`Delete(this)` + `if (AnimDetached != false)`) is recorded in the lane README. Open: Grant 0x69CCF0 89.32 (only the final Suspend(true) Stop inline; budget pattern needs unknown_69ca70 ~30 units larger and the pre-Recharge code ~55 cheaper; lands with COMDAT 0x69ED30, a pop-42 seed), Place 0x69D850 (4,388 B) 61.13 (waits on the parked comip model). The rest of Super.CPP is accepted.
- Audio DS after Cc505 (NOTES, w/; r1 Audio_Level_Fade_To 5 B): Audio_Thread_Proc 0x4094D0 (709 B) BYTE-EXACT locally (w/tpf/, overlay w/hm2) when AudioThreadBlock::Device and AudioChannelBuffer::FrameBytes are not volatile, but Audio_DS_Close 0x40A130 then misses (96.43). Suggested fix: make the global volatile instead (`extern AudioThreadBlock volatile Audio_Thread;`, a rename spec + casts in DS_Init; overlay w/hm3). Population-3434 is not the DS TU (the DS rows 0x409390-0x40AC80 need their own population, frozen attempt w/r2_draft/). Rule: a block ending in a forward `goto` is laid out after the function's returns. Misses: Audio_DS_Channel_Start 0x40A260 60.87, Channel_Open 0x40A180 93.10, AudioLevelSet::Combine 0x4010C0 92.98, Audio_Remove_Devices 0x403210 61.11, Audio_Ring_Is_Full 0x408C80 53.33, unknown_drag_info 0x736490 77.46.
- Near506 (NOTES, w/, lab/; ren1 + r1 Planning_Can_Add 215 B, ren2 MessageListClass nodes are TextLabelClass with UserData1 as int): Read_Scenario_Descriptions 0x670C50 94.54 (the second wcsncat count folds unless `used` is read again later: lab/t2, t3), TAction show text 0x6B0440 92.86 (Rules in eax vs ecx), Planning 0x617AF0 90.00 (inline budget). Rules: an if/else-if with duplicated statements can fix a register permutation that `||` causes; a widely included header must not pull in a wide header closure (it renumbers header-static populations).
- Audio after Audio507 (NOTES, w/; ren1 Audio_DS_Close __fastcall + r1 Audio_Thread_Proc 709 B, ren2 + r2 Audio_Level_Set_Combine 164 B as a free __fastcall function, r3 Audio_DS_Open 372 B): making the volatile global work fails (Handle becomes volatile and DS_Init/DS_Release miss); the no-argument __fastcall probe was the fix. Misses: Channel_Start 0x40A260 60.87 (textual layout kept), Channel_Open 0x40A180 93.10 (96.55 with a speculative volatile unknown_a8, not delivered), Ring_Is_Full 0x408C80 66.67 (setle form), Remove_Devices 0x403210 61.11, TimeSpan::Format 0x4039C0 79.73, AudioLevel::Update 0x4070F0 74.63. Undrafted: System_Shutdown, Create_Device, Bag_Read, Queue_Update, Ring_Destroy. Probe order for audio rows: the no-argument __fastcall convention, then free function vs member.
- Scout508 (UNITS.md top 30 + units_full.tsv on 24ba6f202; r1 CPU type 305 B, r2 Tube 224 B, r3 ScenarioCheckpoint 265 B, r4 tracker.cpp 1,169 B unit complete): Fill_Color_Combo 0x4D2080 86.09, FootClass Safety_Point 0x4BB3F0 41.46 (original reuses the dead `from` argument slot), Adjacent_Coord_With_Height 0x491880 69.44. Not started: TaskForceClass implicit copy ctor 0x6B69D0 (true 240 B) + 0x6B6AC0, GadgetClass 0x4CF290, WaypointPath Save 0x725170 85.44, KamikazeTracker 0x5317C0 87.67, TriggerClass Reset 0x6ED680 70.60. Rules: `extern T x;` after a class-type object's definition in the same TU makes VC6 emit a second dynamic initializer; dynamic_cast/typeid need `@ref ??_7type_info@@6B@=007b15e4`.
- PlanMgr.cpp after Plan509 (NOTES, v/, x/; ren1, r1 490 B, r2 Planning_Draw_All 411 B). Rect family: the original calls Planning_Coord_Pixel, Planning_Centered_Rect and PlanningNodeClass::Coord out of line when they sit 2-3 inline levels deep, and expands them in shallow callers. Ours expands one level too many, usually Centered_Rect inline with its Rect ctor 0x42BCD0 out of line. This one cause covers Is_At_Pixel 0x611230 78.95, Outer_Rect2 0x612C30 84.62, 0x612300 80.85 (true 281 B), Draw_Marker 0x6120F0 75.36 and Draw_Remembered 0x618090 35.66. Others: 0x617AF0 90.00, Thick_Line 0x61A6A0 88.57 / Dashed 0x61A6F0 95.35 (push scheduling), Fill_Marker_Colored 0x619BD0 96.92 (true 205 B), 0x61A3C0 47.59. Undrafted: 0x6182F0 (2,230 B), 0x618C00 (2,076 B), 0x619420, 0x619870, 0x612420, PlanningTokenClass rows.
- Audio after Audio510 (NOTES, w/; r1 Create_Device 632 B + TimeSpan::Format 177 B, ren1 shutdown functions return void, r2 Audio_System_Shutdown 347 B + Audio_First_Device / Audio_Cursor_Advance takeovers, r3 Audio_Bag_Read 72 B): Remove_Devices 0x403210 88.51 (needs Device_Remove/Destroy inlined from pop-3592 while First/Advance live in pop-3644: a population merge, with Create_Device kept alone), AudioLevel::Update 0x4070F0 84.16 (Flags register), Queue_Update 0x4090E0 47.85, Ring_Is_Full 0x408C80 53.33 (no callers). Rules: which population a row is joined into decides what inlines (Create_Device is exact only in a unit without the TimeSpan methods and Device_Destroy); to keep a cursor in memory, walk it with inlined free helpers taking &cursor.
- Pick511 (NOTES, w/, ren1/, pl/tf/; r1 Kamikaze AI 187 + Trigger Reset 190 + script mission 283 + Cargo Attach 143, r2 RTTI name table 93): TaskForceClass copy ctor 0x6B69D0 (240 B) exact only with AbstractClass +0x14 as a named bitfield struct member `AbstractFlags {IsTechno, IsObject, IsFoot}` (Pick511/ren1 spec over 89 files), but that breaks Pick_Lobby 0x744090 (parity of struct types in its headers) and InfantryClass 0x505390 (X add order): rematch both, then land. GadgetClass::Extract_At 0x4CF290 90.91, WaypointPath Save 0x725170 85.44; 0x40DBD0 needs its two conflicting manglings unified. Rules: repeating both calls in each branch gives a cross-jumped shared tail; switch case blocks are laid out in source order; an implicit copy ctor copies direct bitfields bit by bit but a named struct member as a whole byte.
- PlanMgr after Plan512 (NOTES, v/, lab/, x/fam.py; r1 901 B, r2 Draw_Marker 309 B): Draw_Remembered 0x618090 58.89 (Rect() must be refused under Draw_Marker_Outline -> Outer_Rect2 -> Outer_Rect), Draw_Node 0x619870 41.19 and 0x619420 34.63 (Member_Owner, Techno_Color, Branch Coord, CoordStruct(-1,-1,-1) ctor stay out of line in the original), 0x617AF0 90.00, 0x619BD0 96.92; 0x618C00/0x6182F0 not started.
- Mix513 (NOTES; r1-r3, ren1+r6, r7, r8 msgloop helpers 384 B; 2,416 B): Add_Accelerator 0x5B6130 91.43 (true 104 B), Average_Coord 0x5D5010 75.00, Remove_Devices 0x403210 88.51. Rule: TibSun DirType::Direction(Cell,Cell) keeps a dead `if (cell1 == cell2) Facing = 0;` that makes VC6 load from.X as a word and share the dead argument slot (Safety_Point 0x4BB3F0 exact).
- Flags514 (NOTES, w/; r1 AbstractFlags named struct member, r2 TaskForceClass copy ctor 0x6B69D0 240 B): Pick_Lobby 0x744090 flips with the parity of struct types declared before a point inside the first house_type.hpp inclusion. RA2_ABSTRACT_FLAGS_UNNAMED, defined in Refresh_Wonline_Players 0x73FEE0's source, keeps three direct bits there (codex2 told). InfantryClass 0x505390 needs `transport_ready = object->AbstractFlags.IsFoot != 0;`. GadgetClass::Extract_At 0x4CF290 plateau at 90.91 (~70 variants).
- PlanMgr Draw_Node family after Plan515 (zero bytes; NOTES, v/, lab/s/, x/v.py): 0x619870 47.00, 0x619420 35.62, Draw_Remembered 58.89, 0x618C00/0x6182F0 not started. Findings: Branch_Coord and Own_Branch_Coord need named-result bodies (v/bc2.cpp, v/obc2.cpp; byte-exact) so that 0x610950 is called; the branch count must be a local; the PlanningEventTargets cursor getters are static. Inliner labs: top-level sites are decided in forward source order against about 145 units per function; a refused callee costs nothing; for nested sites the result depends on how many top-level sites follow the parent (formula open). PARKED after two zero-byte lanes; resume only with the nested-call rule pinned (InlineLab518).
- OWNER DECISION (10:25Z Nov 2): Near517 r4 ModemHost::Dialog_Proc writes all 10 BM_GETCHECK checkbox readers in one form (`int state = SendMessageA(...); bool checked = state == 1; field = checked;`). It is one rule per kind across the unit, used for /Ob2 sizing, so it is accepted. Near517 open: Add_Accelerator 0x5B6130 91.43, Fill_Color_Combo 86.09, Spread_Tiberium 85.84, Average_Coord 75.00, Read_Scenario_Descriptions 94.54. The Overlay Write_INI 0x5DBA30 entry is stale (accepted in 9ff899d3d).

## Scout516 (2026-11-02, closed; 1,616 B landed in r1-r5)
Resume points and tried variants are in build/class-work/Scout516/NOTES.md, with drafts in w/.
- Fill_Port 0x66D5A0: 87.92 (703 B true extent). Only register choices differ, at three sites. Draft fp_a.cpp.
- IPXConnClass::Start_Listening 0x523C80: 53.97 (106 B). Ours spills the unsigned-short Socket argument to the stack; the original keeps it in esi. Draft sl_a.cpp.
- MapSizeGameOption::Describe 0x728AB0: 72.07 (177 B). The original reserves a 4-byte local for the operator+ temporary; ours reuses the dead territory argument slot. Draft ms_a.cpp.
- Not started: TerrainClass Render 0x6E4430 (needs an override declaration; check the vtable emission first), the CCINI overlapping rows 0x46AEA0/0x46BEFE, and the header-static initializer seeds 0x40ACB0-0x40F0A0.
- OWNER DECISION (10:15Z): BaseNodeClass operator== / != / > are out-of-line members guarded by RA2_BASE_NODE_MEMBER_OPERATORS, which only the unit's source defines. Every other includer keeps the free inline operators, so accepted rows are unchanged. Landed as Scout520 r1 (bd6b5dee4).
- Lessons: guard even a plain non-virtual member added to a widely included header; a caller of a double wrapper keeps the value on the FP stack; plans that take over rows from hand-written seed populations (pop-88, pop-129) need "allow_split": true.

## Scout520 (2026-11-02, closed; 444 B landed in r1-r2)
Resume notes are in build/class-work/Scout520/NOTES.md.
- PlayerProfile::Populate_Dialog 0x739B70: 74.72 (1,309 B). The only gap is one extra 4-byte stack slot. From the second statistic site on, VC6 keeps GetDlgItem in ebp, where the original calls it directly at every site and keeps the conditional result in ebp.
- 0x4D4520, 0x4D4620/0x4D4640 and 0x4D46C0: each is exact alone but must join pop-2660. An `extern` after the definition makes VC6 emit a duplicate _$E initializer/atexit pair. OWNER RULING (10:25Z): guard those externs the way RA2_WARHEAD_LIST_DEFINED does. Assigned to Scout522.
- Blocked on identity or layout: 0x40CAB0 (needs LogicClass's vtable and Submit; currently accepted under the UnknownList832470 alias), 0x40F090 (the StaticBufferClass layout contradicts its constructor at 0x69A1A0), and 0x4D45F0 (the version object is polymorphic).
- 0x4B550D is a .data switch-table entry, not code.

## Ob2Apply519 (2026-11-02, closed; 0 B landed)
Resume notes are in build/class-work/Ob2Apply519/NOTES.md.
- Collapse_Cliff 0x562F50: 86.66 -> 91.02 (shape 98.76). Every call now inlines or stays out of line as in the original, using the cc/f/v10.cpp form of 0x54FAB0, which is still exact. What remains is register allocation in the three half-2 loops. Not yet checked: 0x54FAB0's other callers 0x5688A0, 0x54FB20, 0x54FA60 and 0x54FC60 with v10.
- BuildingType Get_Draw_Rect 0x45E290 joined: 83.07 -> 98.65, equal to its standalone score. Free_Buildup uses the TibSun nested-if delete shape (bt/p/q1.cpp) with a lab stand-in class, which still needs evidence for a real RA2 shape class with an inline destructor. What remains is the Types349 Union register swap.
- Planning 0x617AF0: 90.00, unchanged. The original spends roughly 90 to 156 more IL units at depth 1 before the `int listed` loop. No natural shape found.
- Not attempted: Grant 0x69CCF0, WDTMap 0x72A880, Draw_Tiles 0x6A7BA0, LdPrgMgr 0x535BF0, Campaign ctor 0x725F40, Draw_Node 0x619870.

## Scout522 (2026-11-02, closed; 1,700 B landed in r1-r4)
Resume notes are in build/class-work/Scout522/NOTES.md.
- Populate_Dialog 0x739B70: 85.55 (w/Populate_Dialog_00739b70_best2.cpp). At each stats site the original calls GetDlgItem before taking the text and keeps the ?: pointer in ebp; ours takes the text first and caches GetDlgItem in ebp.
- Fill_Port 0x66D5A0: 87.92, parked. For short temporaries the original picks ecx/edx where ours picks eax/ecx.
- The pop-2660 .CRT$XCU run 0x7CA01C-0x7CA14C is one contiguous unit, so 0x4D4620/0x4D46C0 can only join after every earlier entry. The blocker is the version object 0x4D45F0.
- OWNER DECISION (11:00Z): the version object (ctor 0x712B20, vptr 0x7A2ABC, atexit 0x4D4610) is a polymorphic class with an inline virtual destructor whose scalar deleting destructor is 0x4D4980. This is a hypothesis from the one-slot vtable; the class name stays unknown_ until RTTI or strings show it. The full join of the 0x4D4540-0x4D48D0 entries into pop-2660 goes ahead on that layout.
- OWNER DECISION (11:00Z): unit-wide macros defined at the top of a unit's first source (RA2_RECT_POINT_INLINE, RA2_CCINI_UNIT_MEMBERS, the *_DEFINED list guards) are the standing pattern for unit-specific inline or declaration choices.
- Fixed: the player_profile.hpp comment for Save 0x7395D0 now sits on Save and says wolinfo.ini.

## Scout521 (2026-11-02, closed; 815 B landed in ren1, r1 and r2)
Resume notes are in build/class-work/Scout521/NOTES.md, with drafts in w/.
- GScreenClass::Get_Input 0x4E09D0: 82.81. Only `this` and `input` are swapped between esi and edi.
- LineTrail: ctor 0x5393E0 94.55 (operand order of the inlined Add's growth sum); AI 0x539530 66.06 (the original rereads ActiveSlot from memory); Draw 0x5395C0 65.64 (needs a guarded DSurface::Draw_Trail_Line_4AE9C0 declaration, drafted in hdrl/).
- OverlayClass::Mark 0x5DA970: 82.62 under the CellModel400 TPoint2D<short> model, against 98.61 under the old model. The inner fixup sum uses one register where the original uses two.
- MapPreview Create_Preview 0x61D660: 62.63. Adding TibSun's originy makes it worse.
- MPSiegeTeam 0x5ABF60/0x5ABF70 use rdtsc in an ebp frame: original inline assembly, a ledger category, not C.
- Dropship 0x4A6B90/0x4A9450 are fragments of one ~10.8 KB function.
- RTTI: vtables 0x7A4554 and 0x7A4574 are DynamicVectorClass<AnimClass const *> and VectorClass<AnimClass const *>; 0x7A2464 is the AnimClass * instantiation. The storm lists and pop-1597 rows 0x520C40-0x520F50 need a retyping rename batch. The bytes are identical, so this is a naming fix only.
- Tool: Scout521/t/check_ren_then_plans.py checks a rename spec plus its dependent plans in one throwaway worktree.

## Scout523 (2026-11-02, closed; 4,103 B landed in r1-r8)
Resume notes are in build/class-work/Scout523/NOTES.md.
- Get_Mangled_Port 0x5BAF50: 99.37. Multiplayer_Debug_Print 0x526D90: 99.25 (99.55 with an explicit loop guard, rejected as steering). Get_Allocation_Delta 0x5BAC50: 99.20 (jump threading drops a comparison). Add_Compressed_Events 0x627B60: 95.72 (esi/edi swapped, even with the guarded QueueClass Add overload). Get_Next_Port 0x5B9F10: 82.61. Set_Item_Visible 0x4DE960: 66.67; its true extent is 115 B, not the inventory's 64.
- The "loop tail" blocker: the original ends Get_Next_Port's loop with `jne top` plus a separate return copy; VC6 gives us a shared `je exit; jmp top`. The same loop is inlined in Get_Mangled_Port and twice in Detect 0x5BA2C0 (2,447 B). Assigned to Scout526 as a 75-minute study.
- FirewallSettings is 0x14 bytes: the field at +0x10 is the port pool 0xA71B28.

## Scout524 (2026-11-02, closed; about 5.0 KB landed in r1-r8, r10 and r11)
Resume notes are in build/class-work/Scout524/NOTES.md.
- Select_Game 0x5135F0: 93.08, the jump-table scoring ceiling. The back-edge constant restores at +0xAE6 come out in the wrong order. SpotLight shapes 0x5DD760: 55.83. Made_A_Kill 0x713360: 63.16 (the original keeps VeteranCap as an FP rvalue).
- Hidden units: translation units without .CRT$XCU initializers merge into the previous XCU span in Scout516's ranking (Interpal inside "Init.CPP", version/veteran inside "[VeinholeMonsterClass]"). Look for unaccepted gaps between accepted rows.
- OWNER DECISIONS (12:45Z):
  - Rename UnknownVersionObject to VersionClass (RTTI .?AVVersionClass@@, COL 0x7BA090), 0x4FEF70 to HSVClass::Adjust, and unify the two declarations of 0xA71B18 on FirewallSettings. All three are assigned to Scout525 as one rename round.
  - The lobby.hpp +0x44 TibSun bit-fields appear only under the version unit's macro; everywhere else the field stays `unsigned long Flags`, because of the Pick_Lobby parity rule. Accepted.
  - Unit 0x40CE70 is still blocked by the Map global 0x40D060/0x40D080, which needs the MouseClass ctor out of line; r8's population should be folded into the whole unit later.

## Scout526 (2026-11-02, closed; about 6,070 B landed in r1, r2 and r4-r11)
Resume notes are in build/class-work/Scout526/NOTES.md.
- Detect 0x5BA2C0: 83.54, shape 98.86 (w/det/h0.cpp plus head.cpp). In the mangler loop the original keeps the found-count in memory and the x4 index in ebx; ours swaps them and needs 4 bytes more frame.
- 0x4E1350: 62.92 (w/px/a.cpp; Scout525's range). 0x753F10: 54.05 (codex4's range).
- The scheme-table unit 0x603380-0x604CC0 (~5 KB) is assigned to Scout527: draft the whole unit, take over about 40 template instances, and keep DynamicVectorClass<char *> out of the unit.
- OWNER DECISIONS (14:50Z): the r11 static_buffer.hpp layout (Capacity +0, Buffer +4) and the new surface_region.hpp are accepted (landed). Merge the duplicate HashTableClass declarations (scheme_table.hpp and map.hpp) on the TibSun argument order (growth, count, hash); assigned to Scout527. Rename the PacketClass::Find_Field source file later.

## Scout525 (2026-11-02, closed; about 11.6 KB landed in 38 rounds plus ren1 and ren2)
Resume notes are in build/class-work/Scout525/NOTES.md.
- The gap space below 0x5B0000 is exhausted outside held units (aligned ret-preceded starts, rows straddling function starts, atexit and XCU references all scanned).
- Misses: UnknownTracker839EA0 0x4128A0 76.98 (2,337 B; also needs Append_Bin moved from pop-3461 and the 0x413770 As_Cell take-over); IPXConnClass::Start_Listening 79.37; Preview_Tile 0x52E390 81.25; EventClass MEGAMISSION_F ctor 97.67; Wide_Area_Damage 75.89; UnknownBeacon Set 88.46; Pause_All / Resume_All 94.12 / 90.00; Audio_Event_Channel_Done 70.59; voxel Render 98.30 / 83.24; Convert_Voxel_Colors 97.37; Wave Set_Laser_Pixel 95.83, Build_Wave_Shape 88.44, Load 79.67.
- MixFileClass is a plain class (ren2). That moved Cache under VC6's auto-inline cap and fixed the Combat446 0x595770 blocker.
- OWNER DECISIONS (16:15Z), assigned to Scout529:
  - LogicClass::Detach becomes virtual and the Submit override is declared everywhere, so the LOGIC_DECLARE_VIRTUALS guard can go.
  - 0x412390 is renamed to ahtoi.
  - UnknownVoxelRecord88 moves into one header.
  - HeaderStatics 0x536F30 and LightSource 0x537830 use shared/milsectmr.hpp.
  - voxel_cache's StaticBufferClass field names follow ctor 0x69A1A0.
  - The MouseClass Map global 0x40D060/0x40D080/0x40D160 waits for the Sidebar destructor chain (codex4 area, parked).

## Scout527 (2026-11-02, closed; 3,638 B landed in r1-r2, plus ren1 and ren2)
Resume notes are in build/class-work/Scout527/NOTES.md (lab w/u).
- Build_Schemes 0x604540: 94.43, shape 99.30. Only the second loop's stack slots are ordered differently. It is the only function that instantiates DynamicVectorClass<ColorScheme *>, so the tail 0x604CD0-0x604FF0 and 0x6055A0/F0 follow once it is exact.
- PaletteName::Load 0x603380: 89.62. The original keeps the HashObject(key, value) ctor 0x605D80 out of line at depth 3; ours inlines it.
- 0x603D50: 72.73 (the original keeps a constant 0 in ebx). 0x603750: 69.19 (an ebp/edi swap; it would also bring in 0x605120 and 0x6050C0).
- Findings:
  - VC6 inlines members whose definitions come later in the unit.
  - 0x603240 is ~SchemeNode.
  - DynamicVectorClass<char *> copies resolve to the 0x491xxx rows through catalog references, with no suppression needed.
  - 0x605DA0 stays in pop-35 and is bound by @ref.
- OWNER DECISIONS (16:10Z): the int hash return type of ren1 is confirmed. The ColorScheme ctor's 4th parameter becomes PaletteClass * (assigned to Scout530 as a rename).

## Scout531 (2026-11-02, closed; 620 B landed: Render() 0x7178E0 and Convert_Voxel_Colors 0x716FC0)
- Detect 0x5BA2C0: 83.54 -> 99.24, shape 100 (w/dj/best_99_24.cpp; two register choices left). Assigned to Scout532 as a 75-minute pass.
- Build_Schemes 0x604540: still 94.43. hsv's lifetime would have to overlap the first loop. OWNER DECISION (17:30Z): no non-zeroing HSVClass construction, because the zeroing ctor is evidenced by 0x605DA0. Parked.

## Scout528 (2026-11-02, closed; 3,810 B landed in r1-r12; r13 duplicated Scout530 r8 and was not landed)
- The 0x5B0000-0x700000 gap range is exhausted (pad-start rows, thunks and out-of-line wlib instances are done).
- Misses: Copy_Nodes_To (3-arg) 0x613550 94.34; UnknownListState copy ctor 0x6025A0 90.04; Planning selection 0x615DE0 84.09; control registry dictionary 0x5DED60 81.78; window un-subclass 0x5EDB20 69.04; Remove_Member 0x610E70 42.50.
- Later cleanups: ownrdraw has two type views of 0xA73688/0xA73640 (UnknownWindowProcIndex/UnknownControlIndex vs WolDictionary). The r10/r11 explicit specializations stand in for implicit instances and must move when their callers land.
## Scout530 (2026-11-02, closed; about 2,146 B landed in r1-r8 plus ren1)
- Misses: Find_First_Obstacle 0x4BB890 98.89 (with a guarded coord.hpp operator*, now allowed under RA2_COORD_TIMES); Get_Obstacle 0x4BBAF0 91.96; Matrix3D axis-angle ctor 0x58FF50 99.01; operator*(Matrix3D, Vector3) 0x591380 97.67; Pre_Rotate_Y 0x590550 96.59. BombClass 0x435D30 is undrafted and needs map.hpp declarations.
- r6 OwnerDraw 0x601050 is unreferenced. Its __stdcall ABI is a hypothesis.
## Scout532 (2026-11-02, closed; 4,135 B landed: Detect 2,447 B, MapRegionClass helpers 1,561 B, region statics 70 B, 0x56D5F0 37 B)
- Not taken: region list statics 0x56D530/0x56D570 (a guard flag at 0xA6FD40 and extra initializers); the extents of 0x56EAC0 and the 0x56DDA0 split are wrong.
- 0x56DFF0's .rdata weights at 0x7A5BE0-0x7A5BF0 are bound as extern const double; their names and types are a hypothesis.

## Scout533 / Scout535 (2026-11-02, closed; 0 B)
- Matrix3D axis-angle ctor 0x58FF50 99.01, operator*(Matrix3D, Vector3) 0x591380 97.67, Pre_Rotate_Y 0x590550 96.59: in each, the original schedules one integer op one or two FP ops later than ours. About 120 variants tried.
- Find_First_Obstacle 0x4BB890: 98.89. Copy_Nodes_To 0x613550: 94.34.
- Get_Obstacle 0x4BBAF0: 91.96 -> 97.38 (Scout535 w/best_4bbaf0_97.38.cpp). Named temporaries give the right call order but swapped edi/ebx; without them the registers are right and the call order is wrong.
- UnknownBeacon Set 0x42DD60: 88.46, but only with an (int x, int y, int z, int house) signature, which would need a rename spec. Preview_Tile 0x52E390: 81.25.

## Scout534 / Scout537 (2026-11-02, closed; 3,318 B landed: 0x5EDB20 518 B, Multiplayer_Debug_Print 2,208 B, 0x6025A0+0x601780 452 B, LineTrail::AI 140 B)
- Fill_Port 0x66D5A0: 87.92 (registers only). Planning_Same_Selection_Path 0x615DE0: 84.09 (resume from Scout534 w/pl/h10.cpp).
- Select_Game 0x5135F0: 92.40 joined (93.08 standalone). Only the +0xAE6 back-edge restore order is left: edi=-1 and esi=1 come back in the reverse of the original's order. Landing it needs the cheat-code and campaign-choice declarations moved out of the 0x516F00 and 0x5147A0 sources.
- GScreen Get_Input 0x4E09D0: 82.81. LineTrail::Draw 0x5395C0: 65.64 (variant c2 gets the right registers but scores 57.14).
- OWNER DECISION (18:50Z): 0xA780C0 keeps two type views for now: Scout523's local BasicTimerClass in the IPX debug unit and queue.hpp's UnknownElapsedTimer. Neither shared type matches the debug print, so unify them later when a single type fits both.

## Scout536 (2026-11-02, closed; 0 B)
- IonBlast One_Time 0x521A90: 94.19. With the mirror-pointer form the shape is exact but it scores 89.61: two coupled scratch-register swaps.
- Add_Compressed_Events 0x627B60: 95.72, exact shape. The esi/edi pair is nearly tied in priority; two variants flip it, but each also changes the code.
- Queue 0x6279D0: 84.96 -> 90.15 with an `i < 8 &&` guard that keeps the second `if (save)` test. The guard is steering, so this is a resume point only.
- codex1 (19:05Z): Map.CPP second half closed (all 27 left are capped). New assignment: retry them with today's mechanisms, then the truncated ownrdraw.cpp window procedures.

## Scout538 / Scout539 (2026-11-02, closed; 454 B landed: Copy_Nodes_To 0x613550)
- Get_Obstacle 0x4BBAF0: 97.38. The original's register pair appears only when H(last) is a compiler temporary evaluated first (`H(last) + 4 <= H(again)` gives the pair but `add ebx,4`, 96.25).
- Find_First_Obstacle 0x4BB890: 98.89 (the Z running sum is added into from.Z instead of into the sum register). Select_Game 0x5135F0: 92.40 joined (the +0xAE6 pair is the only real diff).
- PaletteName::Load 0x603380: 89.62 -> 98.23 (Scout539 hv/c2, t1 or h9). Two push/mov pairs are scheduled in the wrong order inside Add_Node; landing it also needs the 0x605D80 ctor row.
- Build_Schemes 0x604540: 94.43 (in the /FAs maps hsv always shares the RGB temp's slot). IonBlast One_Time: 94.19.

## Scout540 (2026-11-02, closed; 0 B)
- Add_Compressed_Events 0x627B60: 95.72. GScreen Get_Input 0x4E09D0: 82.81 (register ties decided by use counts; see VC6 notes). 0x603750: 69.19.
- MapSizeGameOption::Describe 0x728AB0: 75.68, after adding the missing MapSize_Labels @ref. A named joined temporary probe reaches 78.26 (Scout540 w/ms).

## Scout543 (2026-11-02, closed; 32 B landed: 0x56EA00)
- early.py pad-start scan below 0x5B0000: only 0x56EA00 (landed) and 0x451BF0 are real; 0x54BE80 is in codex2's hold and 0x475960 is Adj472's miss.
- Draw_Radial_Indicator 0x451BF0 (1,136 B): 97.22, shape 100 (Scout543 w/rad_best.cpp). One register tie is left in the spoke loop. Assigned to Scout544.

## Scout542 (2026-11-02, closed; 0 B)
- LineTrail::Draw 0x5395C0: 65.64 -> 96.94 (Scout542 w/lt/zb.cpp). Three instructions are left; assigned to Scout545.
- Planning_Same_Selection_Path 0x615DE0: 85.86 (w3.cpp is a layout lead). Fill_Port 0x66D5A0: 87.92. Find_First_Obstacle 0x4BB890: 98.89 loose.

## Scout541 (2026-11-02, closed; 0 B)
- PaletteName::Load 0x603380: 98.23. Get_Obstacle 0x4BBAF0: 97.38.
- Control registry 0x5DED60/0x5DEE00: the atexit is byte-exact joined (Scout541 x/jod.cpp), but cannot land yet:
  - The inventory bounds are short: the true bodies are 148 B and 369 B.
  - The Shrink_Table specialization 0x6027E0 must be emitted by its real caller, registry Remove 0x601C50 (Scout541 got 23.17).
  - Assigned to Scout547.

## Scout547 (2026-11-02, closed; 517 B landed: control registry 0x5DED60 + 0x5DEE00)
- CAUTION: the 0x6027E0 explicit specialization now only forwards to a guarded inline Shrink_Buckets() (RA2_WOL_DICTIONARY_SHRINK_ACCESSORS). When registry Remove 0x601C50 lands, drop both the specialization and Shrink_Buckets.
- 0x601C50 registry Remove: 28.63 (Scout547 w/rm1.cpp). Landing it needs operator= inlined (it calls inline setter 0x600510) and take-overs of 0x600510/0x600350/0x600460. 0x6027E0 is also called from the unrecovered window procs near 0x5EC360 and 0x5F8740 (codex1's ownrdraw assignment).

## Scout545 (2026-11-02, closed; 0 B)
- LineTrail::Draw 0x5395C0: 96.94. VC6 adds the extra &current->Value register whenever the entry block both assigns current and reads Value. The 83.67 family (Value read through next at the loop bottom) avoids it but leaves current in ebx; resume from Scout545 w/lt/mA1.
- Planning_Same_Selection_Path 0x615DE0: 85.23. It needs `@ref ??_C@_0BK@INKB@MSG?3PlanningModeHeteroSel?$AA@=007ebdc0`.

## Scout546 (2026-11-02, closed; 0 B)
- Wall_Update 0x475960: 61.27 -> 69.97 (Scout546 w/wx1.cpp; a member-wise Union result and pointer loops). The 73.08 probe (wy3) shows the original loop body has about three more cheap inline calls, probably TibSun-style accessors. The Union arguments are still called in the wrong order. Assigned to Scout550.
- IonBlast AI 0x521340: 79.38 (the vector3 double-divisor operator/ needs VECTOR3_DECLARE_WWMATH; the dead float stores are not reproduced; frame 0xA8 vs 0xB8).
- Wide_Area_Damage 0x47F6E0: 75.89. The original uses all 0x44 frame bytes where ours has 4 bytes of padding; a double probably needs a real stack home in the loop.
- Tool caution: diff_candidate runs share build/diff/<entry>, so run them serially.

## Scout548 (2026-11-02, closed; 0 B)
- Get_Obstacle 0x4BBAF0: 97.38. Diagnostics show VC6 always gives a read-only call-result temporary edi here; only a sub/add destination gets ebx. No source form found that puts the original's read-only temporary in ebx; probably unreachable from source as tried. Park.
- Fill_Port 0x66D5A0: 88.15 joined (`ModemCount++ + 5`, Scout548 w/fp_z4.cpp). The scratch-register rotation is now in step after 0x13E; the original's `add ecx,5 ... inc dword ptr` pair and the eax/ecx swap at 0xCD-0xE2 are left.

## Scout549 (2026-11-02, closed; 61 B landed: Made_A_Kill 0x713360)
- Tracker 0x4128A0 (2,337 B): 76.98 -> 97.61 standalone (Scout549 best_4128a0_97.61.cpp). An ebx/edi swap is left in the three diagonal blocks. Assigned to Scout553.
- SpotLight shapes 0x5DD760: 55.83, but shape 86.12 with the original 0x54 frame (copy-init source rect only). The constant-register roles are left.

## Scout550-552 (2026-11-02, closed; 2,177 B landed: Wall_Update 1,015 B, Wide_Area_Damage 459 B, Fill_Port 703 B)
- OWNER NOTE (20:55Z): Wall_Update uses an identity inline Wall_Rect wrapper to get the call order, and Fill_Port uses a file-local Send_Message wrapper. Both are real C++ that a Westwood source could contain, so they are accepted. They are marked as hypotheses: replace them with TibSun-shaped source if evidence turns up.
- IonBlast AI 0x521340: 81.29 (Scout552 w/ia_best.cpp; about 8 B of frame left: a height slot and the Cell argument copy). LineTrail::Draw 0x5395C0: 96.94 (VC6 reuses one &current->Value for the test and the Draw argument).

## Scout553-556 (2026-11-02; 2,337 B landed: tracker 0x4128A0)
- Tracker 0x4128A0 is exact: a named `side` local for the side bins in diagonal blocks 1-3. Append_Bin 0x412720 and As_Cell 0x413770 are bound by @ref (see the HANDOFF rehead lesson).
- Inline-wrapper lever passes (Scout554/556) left these unchanged; each needs a different source shape:
  - Get_Obstacle 97.38 and Find_First_Obstacle 98.89;
  - LineTrail::Draw 96.94;
  - the Matrix3D trio 99.01/97.67/96.59 (one integer op is placed among the FP ops differently);
  - PaletteName::Load 98.23 (the 0x605D80 ctor now binds byte-exact through hv/c2; pair 1 comes from Load's context);
  - Preview_Tile 81.25.

## Scout557-564 (2026-11-02, late passes; landed: region unit 985 B, BombClass 640 B, Techno timers 42 B, Matrix3D copy 18 B, UnknownBeacon 78 B, Collect_Boundary_Cells 394 B, Find_First_Obstacle 526 B)
- IonBlast AI 0x521340: 96.30 with the original frame (Scout563 best_521340_96.30.cpp). The to_blast copy order, one slot32 register and the fabs operand order are left.
- 0x613E50 Planning.cpp (446 B) needs ~PlanningTokenClass 0x612D20 first (Scout561 w/seed). PaletteName::Load 98.23: pair 1 comes from Load's register context. Get_Input 82.81: it matches TibSun statement for statement. Add_Compressed_Events 95.72, One_Time 94.19, SpotLight 0x5DD760 54.48, and Matrix3D 99.01/97.67/96.59 are unchanged.
- Follow-up rename: fold unknown_timer_ac0178/ac0168 into TechnoClass::ActionLineTimer/TalkBubbleTimer.

## Scout566/569 (2026-11-02 final passes)
- IonBlast AI 0x521340: 97.86 (Scout566 best_521340_97.86.cpp). One integer allocation decision is left: the blast-coord copy order and the second slot32 load register.
- Add_Compressed_Events: 95.72. The esi/edi choice comes from a register preference at the 0x1F arm's storedsize definition, not from use counts (Scout569 t13).

## Scout578 (2026-11-02, closed; 0 B)
- Extract_Compressed_Events 0x6282D0: 43.24 -> 56.53 (Scout578 misses/, overlay misses/event.hpp.overlay). The +0x07 dword stays in ebp only as a real POD union member.
- Execute_DoList 0x628880: fresh draft at 71.71 (j-loop allocation and a 4-byte frame left).
- OWNER DECISIONS (22:55Z):
  - The EventClass payload union may gain a POD target member (RA2Whom {long ID; unsigned char Kind;}) and a Variable {void *Pointer; int Size;} member at +0x07. This is a hypothesis evidenced by the ebp-held dword; guard it under a unit macro if other users change.
  - The Execute_DoList signature becomes (int, int, ConnManClass *, CDTimerClass<FrameTimerClass> *, UnknownFrameTiming *) __fastcall.
  - The new globals 0xA3D23C/0xA3D258/0xA402E0-E8/0xA40D1C and Unknown_00629290(int, int) __fastcall are allowed.
- Remaining unaccepted Queue.CPP rows: Queue_AI 0x623770, Queue_AI_Multiplayer 0x623B00, Wait_For_Players 0x624C10, Process_Receive_Packet 0x6265C0, 0x626CB0, 0x6279D0, 0x629290, Print_CRCs 0x62A360, plus the templates 0x62EA00/0x62EA40. IPX Service 0x525F60 is untouched.

## Scout579 (2026-11-02/03; 2,454 B landed: Execute_DoList 0x628880)
- Process_Receive_Packet 0x6265C0: 49.40 at HEAD -> 87.18 (Scout579 misses/). It needs c3.cpp, a byte-exact rewrite of 0x62E5C0 that refuses auto-inlining, in the same plan, plus the event.hpp POD union overlay.
- 0x626CB0: 52.58. Extract_Compressed_Events 0x6282D0: 56.53, parked after two attempts.

## Scout577 (2026-11-02/03, closed; 2,165 B landed: planning-token teardown 2,074 B and Planning_Event_Result 91 B)
- The in-class PlanningNodeClass::operator delete was an extra /Ob2 site inside ??_G; planning.hpp now drops it. 0x613E50's two list Clears are one file-local inline helper; this is a budget-count hypothesis.
- 0x6130B0: 77 (needs pop-3353 taken over whole, including 0x6142F0). Planning_Selection_Kind 0x616B40: 98.51 (Scout577 sk2's logic differs from the original). 0x616A50 77.83, 0x61A6A0 88.57, 0x61A6F0 95.35, 0x619BD0 96.92. Assigned to Scout581 together with the rest of the PlanMgr.cpp rows.

## Scout580 (2026-11-03, closed; 0 B)
- Process_Receive_Packet 0x6265C0: 87.67, parked. VC6 biases the index-form mega pointer to a non-zero field offset; the original's pointer is unbiased.
- Queue_AI 0x623770 is exact joined, but it lands only with Queue_AI_Multiplayer 0x623B00, which is at 84.67 (Scout580 misses/, queue.hpp overlay).
- Templates 0x62EA00 and 0x62EA40 land with their only callers, Wait_For_Players and 0x629290.
- OWNER RULING (00:20Z): the Queue.CPP unit-local declarations are allowed: the timeout table 0x7EC438, unknown_precalc_max_ahead_a3d57c, unknown_sync_counts_a76b74[8][8], Mono_Page_0059da50, the __fastcall Wait_For_Players, Westwood MAX/MIN, and the function statics bound by @ref.
- Queue.CPP pauses after three lanes (2,454 B in total). The next lanes take the inventory pass-7 rows.

## Scout581 (2026-11-03, closed; 2,477 B landed in r1-r3)
- The PlanMgr Rect family (Node_At 0x615D30, Pick_Node 0x616070; 0x616140/0x617900/0x615C00 depend on them) reaches 96.67/96.05 only with two probe inline sites after Planning_Inflate, so the natural source of those sites is still missing. Planning_Order_Kind 0x615A80 needs 9 or more extra sites.
- Planning_Techno_00615480: 83.93 (loose 98.21); keep that symbol, because EventClass::Execute binds it. 0x611BD0: 51.40 (ours expands operator== 0x61A8B0, the original calls it). Loop_Color 0x6129B0 92.95 and Branch_Color 0x6127E0 95.34 have one register diff each. 0x6130B0 and 0x616B40 were not attempted.

## Scout582 (2026-11-03, closed; 1,336 B landed: Options_Menu_Proc 0x4DD8A0)
- Pass-7 rank (Scout582 RANK.md): 46 workable rows (133,689 B) after holds; 51 rows are held (codex1 ownrdraw 18, codex4 31, House 1, PlanMgr 1).
- 0x685AC0 is ambiguous in pass 7 (the sweep could not decode it), so it is not a pass-7 row; leave 0x68633A until 0x685AC0 is bounded.
- Misses: UICmnds 0x6F81B0 99.60; Motion_Capture 0x53F490 97.63; ParticleClass ctor 0x608440 94.69 (shape 100, two frame slots swapped); Skirmish_Message_497 0x683FC0 97.43; Skirmish_Command 0x6829F0 78.89; Audio_Destroy_Devices 0x403210 61.11 (parked).
- Tool note: check_plans honours RA2_INVENTORY_PASSES only as an absolute path under the check worktree. Plans that state body_bytes don't need it.

## Scout583 / Scout584 (2026-11-03, closed at the account switch; 0 B)
- Rect family (Node_At 0x615D30, Pick_Node 0x616070): an inline IPW(Rect const &, int x, int y) helper fixes the add-order register diff; the inline split needs the Rect() subtree budget at about 166-181 units against the natural 250. 0x616070's true extent is 207 B (to 0x61613F), and the 0x616132 row is bogus.
- 0x6130B0: 78.61 (Scout583 w/rl1, hi2, ut3, h4). 0x613330: 50.13 on its first attempt (w/ts2). 0x616B40: 98.51. Branch_Color/Loop_Color: unchanged.
- Diplomacy dialog 0x6340F0: 65.66, shape 98.27 (Scout584 w/r40f0j1.cpp); a callee-saved register permutation is left. 0x5BBDD0 (netdlg2) was surveyed only; it needs 0x5C5FF0 first.

## Scout586 (2026-11-03, closed; 0 B; resume points in build/class-work/Scout586/NOTES.md)
- LdPrgMgr draw 0x535BF0 (3,978 B): 63.42 (Small467 had 57.39), w/best_535bf0_i2_63.42.cpp with the 0x536D30 rewrite w/d30.cpp (its byte identity is unchecked). The call sequence is exact through an inline Scheme_Pixel helper, which spends IL before the RGBClass ctor site. The frame is 0x1180 against 0x1184.
- LAN lobby refresh 0x5BBDD0 (1,552 B): 82.76, shape 95.44, frame exact. An inline Find_Lobby_Dialog(HWND &) places the tail. From 0x5BC11A the scratch registers are rotated by one. It needs declarations for 0x5C8680 and the globals 0xA71DE8/0xA71E18/0xA71E28.
- Save_List_Selection 0x5C5FF0 (793 B): 94.38; the name and index frame slots are swapped. OWNER ITEM: the accepted 0x5CDA50 Grow_Table (codex3 r259) is an explicit specialization, which makes the original's inlined Grow at site 2 a call (the row drops to 76.60). Landing 0x5C5FF0 needs Grow_Table back as an instantiation of the template. Reconcile the names Unknown_005c5ff0 (0x73FEE0) and Save_List_Selection_005c5ff0.
- Motion_Capture 0x53F490 97.63 and Skirmish_Message_497 0x683FC0 97.43: no change; parked (VC6 normalises every slot-pointer form).

## Scout585 (2026-11-03, closed; 0 B; resume points in build/class-work/Scout585/NOTES.md)
- Spark AI 0x60B670 (1,277 B): 86.56 (w/spark_best_86.56.cpp with EXTRA 0x60B190=w/b190t.cpp). A register rotation and one store/load order after the first Random call are left.
- Railgun AI 0x60C050 (1,904 B): 67.39. The original does not reuse the squared terms between its two Fast_Sqrt calls; ours does.
- ParticleClass ctor 0x608440: 94.69, unchanged (two 12-byte locals swapped).
- Spawn_Particle 0x60B190 in TibSun's early-return form is exact on its own (w/b190t.cpp) and gives the original's layout at both inline sites. Land it in the same plan as the first exact system AI.
- Still open in the family: 0x608BB0 (1,601 B), 0x609540 (1,069 B, TibSun Spark_Behavior_AI particle.cpp:441, with RA2_MATRIX3D_INLINE_COPY) and 0x609D10 (964 B). 0x620FDB (24 B) is a bogus row in header-statics padding.
- fast_math.hpp may have Fast_Acos and Fast_Asin (0x4BA550/0x4BA580) swapped; check before anyone relies on them.
- OWNER DECISION (coord.hpp, reversible): the inline CoordStruct ctor stays the default. Units that see the out-of-line ctors (0x434820, 0x41B630; Particle 0x609540 calls both) bind them per unit through RA2_COORD_TPOINT3D / UnknownCoord434820. Fire_AI 0x60C7C0 (codex4 r42, memcpy helper) moves to that form when next touched. This no longer blocks Particle.

## Scout587 (2026-11-03, closed; 2,058 B landed: ModemGuest Init_Dialog 0x596540 with the Send_Message wrapper)
- Radar per-house row 0x634670: 92.92, shape 100 (w/best_634670_r12_92.92.cpp). Its second Is_Ally call is `house->Is_Ally(player)`. Only a scratch-register rotation is left.
- Video_Mode_Proc 0x543CF0: 73.96. The list, SendMessageA and loop-index registers are rotated.
- Parked after two zero-byte attempts: Main_Options_Proc 0x542590 85.62, IonBlast One_Time 0x521A90 94.19 and Audio_Remove_Devices 0x403210 88.51 (merged pop-3592 + pop-3648; rotated loop forms lose the cached zero in ebp).
- Blocked: 0x68CF90 needs a bool rename whose caller 0x5FED10 is codex1's (pcx_cache.hpp). 0x5C69E0 (63.75) and 0x5CBF20 (43.42) need 0x5C7160 moved to another population and a slot-3 rename.
- Correction: Scout582 RANK rows marked fresh mostly have older drafts (Mix488, Small467 and others). Check jobs/NOTES before calling a row fresh.

## Scout588 (2026-11-03, closed; 964 B landed: ParticleClass slot 67 Draw_It 0x609D10, with frame_rate.hpp)
- Smoke particle AI 0x608BB0: 89.89 (w/sbb0_best_89.89.cpp, EXTRA 0x608250=w/hs250.cpp and 0x6093A0=w/p6093a0.cpp). In both diffs the original uses the left operand as the destination: `fld; fild; fsubp` for `velocity.Z -= Gravity`, and `add eax,ecx` for `height_gl + j`.
- Spark particle AI 0x609540: 64.60, parked. The original calls the out-of-line ctors 0x434820 (two early coordinates) and 0x41B630 (the last one), and an inline ctor always expands at those sites. OWNER DECISION (reversible): add these to coord.hpp as declarations guarded per unit (an out-of-line UnknownCoord434820(int,int,int) and the TPoint3D ctor 0x41B630), carried in the shared/ overlay of the round that first lands one. The draft's file-local stand-in types must not land.
- Spark system AI 0x60B670: 86.56, parked (a 3-register rotation). Smoke system AI 0x60BB70: 37.95. The original calls DVC Add 0x60D050 out of line in the two inlined Spawn_Held_Particle sites and expands it at the last one; measure the /Ob2 budget at the first Add.
- check_plans refuses RA2_INVENTORY_PASSES inside its worktree, relative or absolute ("not in the subpath"). For pass-7 rows, state body_bytes and bound_evidence in the plan.

## Scout589 (2026-11-03, closed; 1,956 B landed: CampaignScoreClass::Presentation 0x466A50 with the Get_Item wrapper)
- Radar row 0x634670: 97.35 (w/best_634670_c1_97.35.cpp; Get_Item on the 0x7EE0AC GetDlgItem only). A scratch rotation is left in the two 0x7EE0CC id loads. Wrapping those two sites rotates the callee-saved registers instead (81.42).
- Diplomacy dialog 0x6340F0: 80.56 (w/best_6340f0_r7P_80.56.cpp; Get_Item everywhere plus Show_Window after the loop). ebx holds EnableWindow in the loop; the original keeps ShowWindow there.
- Video_Mode_Proc 0x543CF0, Main_Options_Proc 0x542590 and Select_Serial_Dialog 0x5CDF00: wrappers neutral or worse (loop-index ties or the /Ob2 budget). Parked. The 0x5CDF00 draft needs shared/session_state.hpp.

## Scout590 (2026-11-03, closed; 0 B; resume points in build/class-work/Scout590/NOTES.md)
- ShipLocomotionClass unaccepted rows: Draw_Matrix 0x676010, Process 0x6765B0 (77.65, w/pr_best_77.65.cpp), While_Moving 0x676F60 and Start_Of_Move 0x6785C0.
- While_Moving 0x676F60 (5,720 B; pass-7 bounds confirmed: prologue at 0x676F60, 7-entry jump table 0x67859C-0x6785B7) is TibSun's DriveLocomotionClass::While_Moving(bool). It scores 69.94, shape 97.19 (w/wm_best_69.94.cpp with HDR=Scout590/hdr), and the frame matches at 0xE4. Left: the -1 constant web in edi, then frame slot order.
- Start_Of_Move 0x6785C0 (8,373 B, ends `ret 0xc`) is TibSun drive.cpp 1402-2040. Not drafted.
- DriveLocomotionClass has the same While_Moving code at 0x4A1000, unbounded in every pass. Owner item when the Ship row lands.
- Header overlay (Scout590/hdr/shared/): ship_locomotion.hpp declares While_Moving/Start_Of_Move. foot.hpp: UnitTypeClass +0xBA4 `bool Passive` and UnitClass +0x5B9 `bool unknown_5b9`; both replace char padding (owner: accepted as proposed when a row lands).

## Scout591 (2026-11-03, closed; 4,915 B landed: Net_Join_Dialog 0x5BD070 with the Start_Joined_Game / 0x5C3B70 rename)
- Get_Join_Responses 0x5C08A0 (6,798 B): not drafted (seed Scout591/w/s5c08a0, TibSun netdlg2.cpp 2411-3304). Net_Join_Dialog declares it locally as __fastcall by @ref; reconcile when it lands. Scout593 holds it.
- Lobby refresh 0x5BBDD0: 82.76, unchanged; Get_Item had no effect.
- Net_Join_Dialog_005bd070.cpp has file-local @ref declarations to move to shared headers when their rows land: Host_Dialog_Proc 0x5BEFE0, Seat_First_Player 0x5C8CD0, 0x5EAC30, Version 0x712B50, session +0x63C, 0xA3F808/0xA3F818.

## Scout592 (2026-11-03, closed; 0 B; ShipLocomotionClass PARKED after two zero-byte lanes; resume in build/class-work/Scout592/NOTES.md)
- Draw_Matrix 0x676010 (1,189 B): 97.08, shape 100, call sequence exact (w/dm_best_97.08.cpp with EXTRA 0x675A60/0x675B50 rewrites). Ten frame-slot lines are left. The original has a per-branch tilt and temp, which needs about 170 more root IL units. The 0x675A60/0x675B50 rewrites (TibSun shape, no blend/ramp Matrix3D locals, CDTimer Value bound to 0x4A4D20) would land in the same plan, and every Ship row that inlines them would need rescoring.
- Start_Of_Move 0x6785C0 (8,373 B): first draft 57.48, shape 93.74 (w/som_best_57.48.cpp, HDR=hdr). The TPoint3D ctor 0x41B630 and Length 0x41B780 are out of line at early sites and inline at later ones (budget). Use RA2_COORD_TPOINT3D + RA2_COORD_LENGTH for the unit. The original merges 12 `return false` and 2 `return true` epilogues.
- Process 0x6765B0: 77.65 (more /Ob2 sites after Set_Slope in the original). While_Moving 0x676F60: 69.94.

## Scout593 (2026-11-03, closed; 6,798 B landed: Get_Join_Responses 0x5C08A0, __fastcall confirmed)
- Lobby refresh 0x5BBDD0: 82.76, unchanged after about 20 variants (import wrappers, MAKELONG, alias convention probes, orders). The residue is a one-step scratch rotation at the 0x4A8 column sends, then ebp/edi in the LobbyNameSet cleanup. Untried: the `game_index == 0` else-branch first, a helper for the 0x4A8 sends, the cell/LobbyNameSet layout.

## Scout594 (2026-11-03, closed; 0 B; resume in build/class-work/Scout594/NOTES.md)
- Dropship_Screen 0x4A6B90 (pass 7: one function, 10,797 B, 0x4A6B90..0x4A95BC plus 3 NOP; the old 0x4A9450 row is a fragment of it). It is TibSun dropship.cpp 281-1070. Draft 80.86, shape 99.44, 2962/2967 instructions, frame 0x660 exact (w/ds_best_80.86.cpp, no overlay; the caller's name Unknown_004A6B90 is kept). About 2 h of its 4 h box is left.
- Left: frame slot order (about 270 offset lines; IL-level weights, the slot table is in NOTES); `input` in edi where the original has esi; the out-of-line Surface ctor 0x49ED90 at the old_surface site (budget); register choices in the cross-dissolve and green-shape loops.
- Every other row of population-2427 is accepted.

## Scout595 (2026-11-03, closed; 0 B; resume in build/class-work/Scout595/NOTES.md)
- The brief was stale: 0x5C71F0, 0x5C7570, 0x5CA6C0 and 0x5C67C0 landed in Netshare390 r1 (7f2661471). netdlg2 is now population-3876.
- Open netshare gaps: 0x5C2DA0 (384 B), 0x5C3FF0, 0x5C5FF0, 0x5C69E0, 0x5C7EF0, 0x5CAE00 (450 B), 0x5CB170 (400 B), 0x5CBF20, 0x5CCA30 (1,297 B). Open netdlg2 gaps: 0x5BBDD0, 0x5BC940 (640 B), 0x5BCCF0 (416 B), 0x5BEFE0, 0x5C01D0 (1,006 B, 98.94). The pass-7 functions.jsonl holds only its 97 re-bounded rows, so find gaps from the catalog.
- Host_Dialog_Proc 0x5BEFE0 (2,507 B): 95.68 (w/best_5befe0_95.68.cpp with EXTRA 5bbd20=w/ssn.cpp). Send_Slot_Names 0x5BBD20, rewritten to copy from unknown_session_a3d298.Handle, is exact on its own and fixes 0x5BEFE0's AICount store; land both in the same plan. Only the WM_NCHITTEST tool tip is left: the order of the x/y subtractions decides the message/lparam ebx/edi assignment.
- Save_List_Selection 0x5C5FF0: 94.38. The inlined Grow's bucket-pointer temporary shares i's slot and pushes it to the bottom of the frame.
- 0x5C7EF0: 75.82 as __fastcall (the member form scores 73.37); it uses unknown_firewall_a71b18. Receive_Game_Options 0x5C3FF0: 64.86 (the if/else-if chain compiles identically because every section returns). 0x5BBDD0: 82.76.

## Scout597 (2026-11-03, closed; 1,006 B landed: Send_Join_Queries 0x5C01D0 via the session Handle/Games members)
- OWNER DECISION: the plan took the three one-byte atexit thunk rows 0x5C05C0/0x5C05D0/0x5C05E0 from pop-67 (as Iso418 did with 0x52C220). An @ref binding is refused because the function-local CDTimerClass statics emit the thunks in the unit.
- Build_Game_Options 0x5BC940: 89.37 (w/e1.cpp). 0x5BCCF0: 88.44. 0x5C2DA0 (TibSun _DrawMessage): 79.41. Host_Dialog_Proc 0x5BEFE0: 95.68 (a global message/lparam ebx/edi priority swap). 0x5CCA30: 73.63. 0x5CAE00: 46.15. 0x5CB170: not attempted.
- 2026-11-03 04:45Z reassignments: codex2 parks House.CPP (no landing since r2829 at 00:10Z) and takes ShipLocomotionClass. codex3 gets the Dropship unit (Mac drafts in coordination owner-reference/2026-11-03-*). OWNER DECISION on codex3 r277: take the 0x61ECC0 _$E41 seed row from pop-135 into the plan, as with the Scout597 thunks.

## Scout596 (2026-11-03, closed; 3,264 B landed: Skirmish_Command 0x6829F0; resume in build/class-work/Scout596/NOTES.md, CANDIDATES.md)
- The landed extent is the 3,255 B pass-7 body plus 9 bytes of 0x90 fill that VC6 keeps inside the function's own section after its switch tables.
- dllimport check: every hand-declared USER32/KERNEL32/WINMM/GDI32 import is already dllimport. The plain WSOCK32/IMM32/VERSION prototypes match the original's thunks.
- Unchanged: Radar 0x634670 97.35 (all 256 Get_Item subsets tried), Diplomacy 0x6340F0 80.56, Main_Options_Proc 0x542590 85.62, Video_Mode_Proc 0x543CF0 73.96. Unlock_Media 0x46F750: 89.92 (the two failure tails are laid out in the other order). Read_Scenario_Descriptions 0x670C50: 94.54 (a constant fold).

## Scout598 (2026-11-03, closed; 4,734 B landed: DSurface slots 13/19 and XSurface::Fill_Circle from TibSun dsurface.cpp/xsurface.cpp)
- TibSun's dsurface.cpp/xsurface.cpp are the RA2 shapes (TibSun DepthBuffer = RA2 ABufferPtr 0x839C6C, AlphaBuffer = ZBufferPtr 0x8315B4; rename table in Scout598/TRIAGE.md). All remaining DSurface members are compiler output. XSurface::Fill_Rect 0x7743C0 stays inline asm.
- Slot 14 0x4ABBA0 Draw_Depth_Glow_Line: 87.57 (needs an R spec for the TibSun signature, plus the h3 overlay). Slot 15 0x4AC650: 16.23 (frame 0xD4 vs 0xC4). Trail line 0x4AE9C0: 66.04. Plot_Line 0x773F00: 99.44 (exhausted). Draw_Ellipse 0x7746C0: 22.71. Scout600 continues the unit.

## Scout599 (2026-11-03, closed; 3,689 B landed: BuildingLight ctor 0x432FC0, IPXGlobalConn slot 17 0x524870, TechnoTypeClass::Load 0x6DE260)
- Resume list: Scout599/LIST.md. Scout601 continues it. Anim Next_Flaming_Guy_Coord 0x4237B0: 96.95. Foot Can_Reach 0x4C8730: 98.31 (TibSun bitfield bridge tests, header change untried). IPXGlobalConn Receive_Packet 0x5243D0: 80.65 (deferred pushes). BuildingLight AI 0x433970: 78.68. Overlay Mark 0x5DA970: 80.07.

## Scout600 (2026-11-03, closed; 2,754 B landed: DSurface slot 16 0x4ADE00, plus the slot 14 Draw_Depth_Glow_Line rename)
- DSurface is now population-3881 (pop-2657 is empty). Slot 14 0x4ABBA0: 99.60 (w/s14_best_99.60.cpp, HDR=h3). Three instructions are left at the top of the dy loop. Trail line 0x4AE9C0: 67.30. Slot 15 0x4AC650: 16.11 (frame 0xD4 vs 0xC4). Scout602 continues.
- OWNER DECISION: a shared src/shared/always.hpp with TibSun's min/max templates is accepted; it arrives with the first round that needs it.

## Scout601 (2026-11-03, closed; 0 B; resume in build/class-work/Scout601/NOTES.md)
- BuildingLight Draw_It slot 67 0x433380: 66.29 (w/e1.cpp, overlay regenerated by Scout601/ov.py into hbl/shared: TibSun Length/Distance_To/Distance under RA2_COORD_LENGTH_INLINE, techno.hpp +0x5B7). 0x434610 written as TibSun Sweep_Stage is exact in the joined unit. 6-7 extra root inline sites after the third distance give the original's call sequence (77.01); their natural source is unknown (a separate TibSun Coord type is the leading candidate).
- BuildingLight AI 0x433970: 78.88 (@ref for the -0.5 constant at 0x79C9B0). ObjectClass slot 73 Get_Render_Rect 0x5D31C0: 45.42. Next_Flaming_Guy_Coord 0x4237B0 96.95 and IPXGlobalConn Receive_Packet 0x5243D0 80.65: unchanged.
- Not attempted: Overlay Mark 0x5DA970, IPXManager Service 0x525F60, Hover Process 0x4FBFC0, Anim AI 0x421710 / draw 0x420E50 / Flaming_Guy_AI 0x423120.

## Scout602 r1 / Scout603 (2026-11-03; landed DSurface slot 14 0x4ABBA0 2,735 B with shared always.hpp; AnimClass Flaming_Guy_AI 0x423120 1,676 B and Draw_It 0x420E50 1,711 B from TibSun anim.cpp)
- Flaming_Guy_AI binds a body-less TibSun member `UnknownFacingDir &Direction(CoordStruct const &, CoordStruct const &)` to 0x423EF0 (facing.hpp overlay). The original calls it out of line there, and the /Ob2 budget never refuses the accepted ctor at that site.
- AnimClass::AI 0x421710: 85.74, shape 99.41 (Scout603 w/ai_best_85.74.cpp, HDR=h3); only register allocation is left. Scout604 holds Hover Process, IPXManager Service, Overlay Mark and Anim AI.

## Scout604 (2026-11-03, closed; 0 B; resume in build/class-work/Scout604/NOTES.md)
- HoverLocomotionClass::Process 0x4FBFC0 (2,229 B): 62.05 natural, 66.43 with probes. TibSun hover.cpp shape plus the RA2 additions. Process returns COM boolean (`mov al,7` for MOVE_NO); the overlay changes every locomotor's Process to unsigned char (OWNER: accepted when a Process lands). Start 0x4FED20 is exact only in the TibSun `bool arrived = ...` form.
- Recurring pattern: the original calls As_Cell 0x413770 / Cell::operator== 0x4FEF20 (Hover) and the coord helpers (BuildingLight Draw_It 0x433380, Scout601) out of line where ours inlines them. Both need about 5-8 more free root inline sites than our source has. The leading hypothesis is a TibSun-style Coord type separate from CoordStruct, converted at call sites (it would also explain Hover's X/Y-only copy). Scout605 tests it.
- AnimClass::AI 0x421710: 85.74, unchanged. Overlay Mark 0x5DA970: 81.69 at HEAD (Scout521 q101). IPXManager Service 0x525F60: seeded only (about 15 debug strings need @refs).
- Scout602 (closed, r1 landed as 92d228ac4): Draw_Trail_Line 0x4AE9C0 is at 89.22 (w/tl_best_89.22.cpp, overlay h5). The TibSun operator- clip form and `int zwidth = ABufferPtr->Width;` got it there. Only the second clip block's frame slots and the dz loop slots are left. Slot 15 0x4AC650: 28.79. New tools: mut.py/mut2.py/hc.sh (adjacent-statement swap hill-climb; check each pick against the original). Owner todo: main_loop.hpp should include always.hpp and drop its own `min`.

## Scout605 (2026-11-03, study lane, 0 B; evidence and model in build/class-work/Scout605/NOTES.md)
- Coord-type hypothesis: PARTLY SUPPORTED. TibSun has `Coord : TPoint3D<int>` for the game and `CoordStruct` only for COM/ILocomotion. RTTI shows VectorClass<TPoint3D<int>> in RA2. TibSun's own conversion bodies are charged (68/74 IL units), and no out-of-line 12-byte conversion exists in the binary. Base-copy conversions measure as free, so only free crossings fit.
- Model (guarded overlays h2/hT2): BuildingLight Draw_It gets 5 of its 6 missing sites (56.26 natural; frame 0xA0 vs 0xC4). Hover Process gets the out-of-line As_Cell/Cell== pattern (63.06). Neither is exact. Do not land the headers: RA2_TP3_TIBSUN drops the free CoordStruct ==/!= every unit uses.
- Should affect: Particle 0x609540 (Coord(int,int,int) 0x434820 over TPoint3D 0x41B630), Ship While_Moving/Start_Of_Move (codex2), BuildingLight AI 0x433970.

## Scout607 (2026-11-03, closed; 0 B; resume in build/class-work/Scout607/NOTES.md)
- BuildingClass Read_INI 0x44AB80 (1,649 B, pass 7): 99.79 (w/ri_best_99.79.cpp with EXTRA 44d3e0=w/to1.cpp 44d600=w/po2.cpp 43bce0=w/tf2b.cpp). The extras are TibSun-shape rewrites of accepted rows, exact in the joined unit: 0x44D3E0 is TibSun Turn_On, 0x44D600 is Power_On, 0x44FA40 is Adjust_House_Power, 0x43BCE0 is Set_Turret_Frame. Left: one SIB operand order in the inlined anim loop ([ecx+edi+0xd14] vs ours [edi+ecx+0xd14]).
- Slot 126 Do_MISSION_ATTACK 0x446920 (2,336 B, 11-entry jump table at 0x447214): 79.45 (frame 0x48 vs 0x58). 0x44B770 delayed fire: 60.27 (naming `int delay` in Create_Laser 0x446820 keeps it out of line).
- Slot 142 Mission_Missile 0x448400 (3,036 B, bound verified) and slot 53 Unlimbo 0x43D3A0 (3,777 B): not drafted. 0x43DC50 (1,393 B) is a bogus tail of Unlimbo.

## Scout606 (2026-11-03, closed; 0 B; DSurface trail line PARKED; resume in build/class-work/Scout606/NOTES.md)
- Draw_Trail_Line 0x4AE9C0: 89.22 (fragile; any extra live local flips it to 81). The block-2 slot fix (w/b1.cpp) swaps the green/blue slots and the Build_Hicolor_Pixel argument order (79-82). w/b8.cpp scores 87.61. The original must hold both states at once, so another source difference is left, most likely in the dz loop. feat.py counts mismatches per region. LineTrail::Draw 0x5395C0 still waits on it; LineTrail ctor/AI are already accepted.
- Slot 15 0x4AC650: 28.79 (frame 0xD4 vs 0xC4: 16 extra bytes).

## Scout608 (2026-11-03, closed; 1,649 B landed: BuildingClass::Read_INI 0x44AB80; BuildingClass is now population-3892)
- Unlimbo slot 53 0x43D3A0 (3,777 B): 88.71, shape 98.1 (w/ul5.cpp, EXTRA from E2.txt). It needs exact rewrites of 0x452BE0 Should_Fog (member TPoint2D<short>::operator+) and 0x442060 slot 52 (drop the file-local RA2_CELLSTRUCT_PLUS operator+) in the same plan. Left: Should_Fog's operator+ goes out of line in the original (about 60-70 free sites short); Sell_Wall's tail merge direction; particle-system argument order.
- Mission_Missile 0x448400: seeded only (w/seedmm). Mission_Attack 0x446920: 79.45. Delayed_Fire 0x44B770: 60.27.

## Scout609 (2026-11-03, closed; 25 B landed: Surface(int,int) 0x49ED90; triage in build/class-work/Scout609/TRIAGE.md)
- XSurface/BSurface member residue is only Plot_Line 99.44, Fill_Rect (inline asm) and Draw_Ellipse 22.71. The rest of the classes.md count is other units' functions that build a BSurface inline.
- RadarClass Compute_Background 0x630B70 (1,746 B, TibSun radar.cpp): 99.29 (w/rb_best_99.29.cpp). Left: `lea ebp,[eax+1]` vs ours `inc eax; mov ebp,eax` at surf_bottom.
- Read_PCX_File 0x60D110: the true body is 1,635 B (ends `ret 8` at 0x60D770; the inventory row says 360 B). 89.68 (TibSun pcx.cpp).
- SpotLightClass::One_Time 0x5DD760 (983 B): 37.01, shape 90.75. It needs a spot_light.hpp overlay and the exact Clear_All 0x5DDB40 rewrite w/ct1.cpp in the same plan.

## Scout610 (2026-11-03, closed; 825 B: Update_Laser_Fence_Connections 0x44DC40 landed, Docking_Coord 0x4440E0 landing; BuildingClass is now population-3894)
- OWNER DECISION: Docking_Coord keeps its file-local `operator+(CoordStruct const &, TPoint3D<int> const &)`, because DockingOffsets are TPoint3D<int>. It is a hypothesis helper; move it to coord.hpp when a second unit needs it.
- Mission_Missile 0x448400: 84.70 (w/mm8a.cpp, file-local Velocity class from TibSun velocity.h). It needs a `case 4:` to keep the 5-entry table; the dead-block form used now is not natural. Parked at its time box. Connect_Laser_Fence 0x44DFC0: 66.67. Barrel_Pitch 0x43B7E0: 72.32 (frame 0x3C vs 0x44). 0x4444B0: 34.78.

## Scout611 (2026-11-03, closed; 0 B; all three PARKED after two lanes each; resume in build/class-work/Scout611/NOTES.md)
- Radar Compute_Background 0x630B70: 99.29 (about 100 variants). Ours puts the min argument in ftol's eax (`inc eax`); the original merges it into ebp (`lea ebp,[eax+1]`). The lever is probably a use count or an earlier variable's lifetime.
- Read_PCX_File 0x60D110: 89.68. In branch 3 the original keeps width*height in edi and reloads file into esi at each loop top.
- SpotLight One_Time 0x5DD760: 37.01. The original never keeps 1 in a register for the whole function; the cause lies before the constant.

## Scout612 (2026-11-03, closed; 0 B; InfantryClass population-3236; resume in build/class-work/Scout612/LIST.md, NOTES.md)
- Five rows (about 10.6 KB) left, all at plateaus; codex3's drafts already follow TibSun (on the Windows mount codex3/infantryclass/<row>/). Per_Cell_Process 0x500AA0 (4,617 B): 93.45 (w/pd3.cpp); the capture test is left (find a building use the original has). Scatter 0x504120 (1,563 B; the inventory's 544 B is wrong): 91.44. Assign_Destination 0x501CE0: 84.93. JumpJet_To_Walk 0x508AB0: 69.52 (comip model). Tunnel_AI 0x5025C0: 56.50 (Coord-type model).
- Cross-cutting blockers now: the comip / COM-pointer model (JumpJet_To_Walk, Assign_Destination, SuperClass::Place, ComPtr297/299) and the Coord-type model (Scout605). Scout614 studies comip.

## Scout613 (2026-11-03, closed; 0 B; TechnoClass population-3893; resume in build/class-work/Scout613/LIST.md, NOTES.md)
- Five rows left: Draw_Pre_Render slot 65 0x6C3B30 82.90 (/Ob2: about 30 root IL units short, 0x41B630 call pattern 4/4/4/4/3 vs 4/4/4/3/3). Take_Damage slot 86 0x6CDC40 88.72 (w/td5.cpp, natural control flow, byte-identical to codex3's best; two `result` reloads and two late register choices left). AI slot 23 0x6C74C0 (codex3 66.05; frame 0x68 vs 0x44, try TibSun's named locals). Draw_Post_Render slot 66 0x6C2C40 (36.14). NoInit ctor 0x6C1F10 (409 B, not attempted). codex3's drafts: /Volumes/mike-gaming/ra2/w/codex3/build/class-work/codex3/techno-*/.

## Scout614 (2026-11-03, study lane; 0 B; VC6_MATCHING_NOTES "What counts as an /Ob2 site")
- Under the ComPtr299 comip model, Aircraft 0x416420 is exact via the position accessor (w/a1.cpp, HDR=build/class-work/ComPtr299/model). Comip regressions left: FootClass::Load 0x4C9D10 and Is_JumpJet 0x508D00 (true body 194 B, 78.57). Once both are exact the model can land and unblock JumpJet_To_Walk, Assign_Destination and SuperClass::Place. Scout616 holds it.
- Hover Process k1/k2/k3 (accessor and Contact wrapper candidates) are unscored; the k1 compile hung while the disk was full.
- 2026-11-03 ~05:00Z: the Mac main drive filled and wedged Wine; the host was rebooted. r99 was re-landed from a clean tree after a stale runner lock was cleared. The monitor now alerts below 30 GiB free.

## Scout615 (2026-11-03, closed; 3,526 B landed: TechnoClass::AI 0x6C74C0 from TibSun techno.cpp)
- TechnoClass::AI needed: techno.hpp unknown_376 as unsigned char; FlasherClass::Process 0x4BBF00 declared and bound; @refs for every vtable slot of a local DynamicVectorClass<ParticleSystemTypeClass const *> and its base (otherwise "Unsupported allocatable data section .rdata"); a file-local Is_Foot helper at two of the three sites.
- NoInit ctor 0x6C1F10: 67.89 (w/ni2.cpp). The original calls the three VectorClass base ctors out of line; about 3-4 natural sites after the DVC members are missing. Draw_Post_Render 0x6C2C40: not attempted (codex3 36.14).

## Scout616 (2026-11-03, closed; 0 B; comip model PARKED after three zero-byte lanes; resume in build/class-work/Scout616/NOTES.md)
- Model v1 rebased on HEAD (model/shared: com_ptr.hpp with the core renamed Query_From, the accepted 0x6591C0 name; locomotion.hpp checked operator->; UnknownFlyPtr a typedef; overlays in unit/). com_ptr.hpp now reaches 53 populations; 47 are object-identical under the model.
- Six still differ: FootClass::Load 0x4C9D10 85.41 (3 sites), Is_JumpJet 0x508D00 78.57 (1-3), UnitClass Per_Cell_Process 0x6FE610 85.65 (exactly 2 after the persist ctor), BuildingClass slot 141 0x447260 81.63 (budget already lower before the ctor), Fly Process_Landing 0x4BDFB0 64.78 (needs more budget), Print_CRCs 0x62A360 (one load; type-count sensitivity).
- When the model lands, 0x454BF0 and 0x454C70 (out-of-line Query_From) become new rows. Resume order: Per_Cell_Process, 0x508D00, Foot Load, Building slot 141, Fly; then popcmp.sh and check_plans over the 13 changed populations.

## Scout617 (2026-11-03, closed; 0 B; UnitClass population-3202; resume in build/class-work/Scout617/LIST.md, NOTES.md)
- Read_INI 0x706AE0 (1,147 B): 99.72 (w/ri5.cpp). Its local DVC<int> is ctor plus an inlined TibSun Clear(); TibSun's `CoordStruct coord;` site has to go to keep the VectorClass ctor 0x46D020 out of line. One instruction is left: the unit->Type load comes before `fild strength`.
- Draw_It slot 67 0x700E70: 87.96 (frame 0x48 vs 0x40). What_Action slot 28 0x703BD0: 63.42. Desired_Load_Dir 0x704730: 77.48. Plan_Route 0x707F60 (6,185 B): 87.44 with a small hp/shared overlay. Not attempted: Mission_Harvest 0x7025A0 (80.08), Draw_Shape 0x7005B0, Mission_Unload 0x701580, Can_Enter_Cell 0x703040, Draw_Voxel 0x6FF690, Tunnel_AI 0x6FAA30. Assign_Destination 0x7053F0 needs the comip model.

## Scout618 (2026-11-03, closed; 907 B landed: DisplayClass Active_Click 0x49E870, Passes_Shroud_Check 0x499390; population-3612)
- Passes_Proximity_Check 0x4991D0: 69.14 (a loop register tie). Mouse_Left_Release 0x49BB20: 79.53. Not started: Set_Cursor_Pos 0x4994D0, Calculated_Cell 0x49A700, Mouse_Left_Up 0x49B0F0, Read_INI 0x49CFD0. 0x49DC80 is a bogus row inside 0x49DB60. Scout620 continues.

## Scout619 (2026-11-03, closed; 0 B; UnitClass; resume in build/class-work/Scout619/NOTES.md)
- Read_INI 0x706AE0: parked at 99.72 (every health-local form gives the same fild/fimul order; Class_Of and Techno_Type_Class are virtual in RA2). Draw_It 0x700E70: parked at 87.96 (frame map confirms the radians-slot reuse). Plan_Route 0x707F60: 88.17 (w/pd.cpp, overlay hq/shared; the parameter is the reassigned destination). Mission_Harvest needs the comip model.
- 2026-11-03 ~13:00Z: Wine compiles hung again (CL.EXE idle in state S; disk fine). A plain `wineserver -k` does not reach them: the project uses its own prefixes (private/tools/wine-prefix, -interactive, -w3; set in private/original-target.*.json). The fix is `WINEPREFIX=<prefix> wineserver -k` for each. Lanes cannot kill processes (auto-mode denies it), so the user runs it.

## Scout621 (2026-11-03, closed; 0 B; UnitClass PARKED after three zero-byte lanes; resume in build/class-work/Scout621/NOTES.md)
- Plan_Route 0x707F60: 88.26 (w/pj.cpp, overlay hq). w/pk.cpp reuses `last` (as TibSun reuses tospot) and gets all 30 Unknown_005502E0 result slots right (loose 97.11, main 85.97); left is which duplicated legs.Add tails VC6 merges.
- Draw_Shape slot 311 0x7005B0 (2,236 B): 89.36 (w/sg.cpp; one-expression Rotate_Z fixes the 0x118 frame; w/sl.cpp 89.29 uses the 0x79D090 extern). Six small differences left. Mission_Unload slot 137 0x701580: 79.88 (overlay ov1). Can_Enter_Cell 0x703040: not started.
- Wine note: a 180 s diff_candidate timeout can be a slow compile, not a hang (one took 155 s while the host was loaded).

## Scout620 (2026-11-03, closed; 438 B landed: Passes_Proximity_Check 0x4991D0; DisplayClass is now population-3901)
- Set_Cursor_Pos 0x4994D0: 72.04 (needs a non-virtual RadarClass `Cell unknown_slot51(Point2D const &)` in map_view.hpp, overlay hdr/shared). Calculated_Cell 0x49A700: 80.23 (needs an R spec: arg5 becomes bool in display.hpp and map_view.hpp, plus RA2_POINT_LENGTH for the unit). Read_INI 0x49CFD0 (2,358 B): not attempted (about 40 callees, Straw/Pipe COMDAT takeovers, slot 32 rename).

## Host limits (2026-11-03, after two reboots)
- 05:12 and 08:52 local: the drive filled, then memory ran out (three overlapping full builds on the 16 GiB Mac).
- One full build at a time: private/tools/fullbuild_lock.sh, taken by runq.sh around every landing and by the lane wrapper build/owner-watch/fullbuild.sh. The lock is pid-checked and cleared when its holder is gone.
- Lanes score one compile at a time and stop under 20 GiB free disk or over 1.5 GB swap (LANE_BRIEF "Host limits"). Wine reset: private/tools/wine_reset.sh. The monitor heartbeat is in build/owner-watch/last.txt.
- Windows workers never block their goals (WORKER.md 5a, assignments/fallback.md).

## Scout622 / Scout623 (2026-11-03; landed ObjectClass Get_Render_Rect 0x5D31C0 796 B and the Calculated_Cell bool rename)
- Get_Render_Rect gets the two /Ob2 sites the original has after the first Get_Frame_Rect: a file-local Object_Is_Building at the bib test, and a `Point2D position(x, y)` the Rect is built from. 0x5D3060 defines RA2_DRAW_SHAPE_OPERATIONS.
- Aircraft Fire_At 0x415790: 95.79 with no probes. A TibSun `Coord(int,int,int=0)` wrapper on each shroud-probe offset (file-local OffsetCoord) supplies the sites. Frame 0x64 vs 0x6c is left. Scout625 continues.
- DisplayClass Calculated_Cell 0x49A700 81.06 and Set_Cursor_Pos 0x4994D0 78.48: parked. Read_INI 0x49CFD0: Scout625.
- Fallback queue item 1 (DisplayClass mouse rows) is still open. Get_Pitch 0x41B6E0 97.14, Techno slot 65 83.54 and Foot Can_Reach 98.31: one attempt each, parked.

## Scout624 (2026-11-03, closed; 0 B; Sidebar.CPP population-3302; resume in build/class-work/Scout624/NOTES.md, LIST.md)
- Add 0x67C530 (788 B) and the emptied-tab handler 0x67CA50 (884 B) are one /Ob2 puzzle. With probes both are exact in-unit (recipe in NOTES: ca50_5's branch order, exactly two free sites in Select_Tab between F730 and Activate_Tab, 0x6820F0 over 40 IL, C850 comparing a free inline that computes Unknown_006820A0()*2). AI 0x67DC90 (1,315 B) and Recalc 0x6802D0 (1,732 B) hang on the same tree, about 4.7 KB in all. No natural source found yet. Next: measure real IL sizes (InlineLab518 x/meas.py, x/model.py).
- StripClass::Draw_It 0x67F800: 90.46. SelectClass::Action 0x6809F0: 66.98 (call sequence identical). Slots 54 0x67E210 and 34 0x6819A0 were skipped (listed for codex3 on BOARD).

## Scout625 (2026-11-03, closed; 2,358 B landed: DisplayClass Read_INI 0x49CFD0)
- OWNER DECISION (reversible): Read_INI's declarations in display.hpp and map_view.hpp sit behind RA2_DISPLAY_READ_INI, which only header statics 0x498760 define, because any new declaration there moves one load in Print_CRCs 0x62A360. This is the same pattern as PCX_CACHE_DECLARE_LOADS. Scout627 is studying how to harden Print_CRCs, Pick_Lobby and Refresh_Wonline_Players so the guards can go.
- Fire_At 0x415790: 99.81 (w/n1.cpp, overlay hB with the TibSun BulletVelocity copy and 3-double ctors; the 8 dead bytes are the unused Z of a 24-byte temporary). One instruction is left: the ROT1 Set_Yaw radian low-dword load order. It needs the w/s1.cpp re-landing of 0x4185B0.

## Scout626 (2026-11-03, closed; 0 B; Sidebar /Ob2 puzzle PARKED after two zero-byte lanes; resume in build/class-work/Scout626/NOTES.md)
- Natural pieces found: C850 without braces (w/c8w_nb.cpp, 168 -> 162 IL, byte-exact) and CA50 searching the strips itself (w/ca50_h2.cpp, removes the 70-unit 0x681980 site). The original's Recalc shows C850 calls 0x6820F0, which must be 42-46 IL units (`return Unknown_006820A0() * 2` in a natural form).
- With probes, CA50 and Add are both exact (`CA=ca50_h2 ./g.sh ps2x c8w_nb f0n/dg2`). Still open: two free sites (or one plus a larger Deactivate) in Select_Tab between F730 and Activate_Tab, and a natural 42-46 unit F0. IL sizes are in the NOTES table (cap about 175). sim.py predicts every compile tried.

## Scout628 (2026-11-03, closed; 461 B landed: Tactical Get_Selectable_Object 0x6AA990)
- Tactical Pixel_To_Cell 0x6A6BD0: 42.06. Our 0x6A27A0 is a free callee (40 IL units or less) that the original calls out of line twice, so the original 27A0 is larger or not an /Ob2 site. Next: measure with Scout626 mu.py. Draw_Wall_Placement 0x6A6290: 78.49 (0x6A2740 is a Point2D-by-value ctor; it needs Point2D::operator-= 0x6AC850 in the plan). Draw_Fence_Placement 0x6A5D70: 48.79.
- BulletClass Shrapnel 0x462C50 needs a merged BulletVelocity API at HEAD (10 accepted users); Scout629 is building it.

## Scout627 (2026-11-03, study; landed Pick_Lobby hardening 9c4945b18, 0 B)
- The PCX_CACHE_DECLARE_LOADS guard now protects Print_CRCs, not 0x73FEE0. Removing it breaks Print_CRCs at +0x9A9, and 12 natural re-rolls failed. RA2_ABSTRACT_FLAGS_UNNAMED is no longer defined anywhere; the `#else` branch in abstract_class.hpp can go.
- Accepted UnknownPathEstimator 0x428370 scores 99.06 in diff_candidate. Generate_Rural/Urban_Buildings 0x589AC0/0x587CF0 are no longer accepted rows (check).
- 2026-11-03: Time Machine local snapshots keep deleted build output on disk, so freed space doesn't return. Ask the user to thin snapshots and exclude build/ (and optionally private/).

## Scout629 / Scout631 (2026-11-03; landed the shared TibSun BulletVelocity model a4fea42dc, 0 B; Shrapnel and Fire_At PARKED)
- OWNER DECISION: bullet.hpp uses the TibSun velocity names (Set_Yaw, Set_Pitch, Set_Speed, Speed, Horizontal_Speed, Nonzero_Check, Get_Pitch). 0x41B6E0 stays unaccepted (the out-of-line copy of the inline Get_Pitch member). Some bullet.hpp variants flip Print_CRCs; probe before changing it.
- Shrapnel 0x462C50: 88.69 (Scout631 w/shrapnel_best_88.69.cpp). The original shares one slot for the first loop's Cell temporary and Create_Bullet's inlined `bullet` spill; ours keeps two (frame 0xB0 vs 0xA8). The FP term orders follow VC6's sort, not the source. Fire_At 0x415790: 99.81 (the angle low-dword reload after fstp: a store/load aliasing order).
- 2026-11-03 17:00-17:30Z: codex1 r932 was refused on Print_CRCs (+0x639) after a4fea42dc; codex1 is redoing it with a guard. Two retries left 31 GB of build/original-target-* outputs (disk fell to 16 GiB). land.sh now prunes on failure too.

## Scout630 (2026-11-03, closed; Init_Map 0x57AE00 4,175 B landed, Build_Corner_Ramp_NW 0x574E50 1,426 B landing)
- Map generator: NE corner 0x574930 82.91 (calls line up), SE corner 0x5743F0 64.98 (the original inlines Set_Cell_Region_Index 0x56E970 in both Assign expansions; a smaller 0x56E970 breaks the accepted SW corner), Seed_Lake 0x57E100 82.45 (block layout). Not attempted: Place_Tile_Patch 0x586340, Generate_Rural_Roads 0x58A1B0, Grow_Water_Region 0x5820B0. Drafts in Scout630/keep/.
- 0x587CF0 Urban / 0x589AC0 Rural were retired by the user's 2026-10-31 decision as counter-fragile rows (period-64 declaration counter). Rural is byte-exact again in codex1's R592 sources; re-adding it needs the user's decision. Left retired.
- USER DECISION (2026-11-03, in chat): re-add Generate_Rural_Buildings 0x589AC0 even though it is counter-fragile ("I'm fine re-adding it"). Scout633 delivers it and adds it to the fragile probe list. Urban 0x587CF0 is an ordinary miss at 90.73.

## Scout632 (2026-11-03, closed; 0 B; TechnoClass population-3899; resume in build/class-work/Scout632/NOTES.md)
- New Coord model (overlay hA/shared/selection_coord.hpp): `class Coord : public CoordStruct` with `Coord(int,int,int)` and `Coord(CoordStruct const &)`, and 0x41B630 bound as `??0CoordStruct@@QAE@HHH@Z`. Evidence: the original's inlined brackets call CoordStruct::operator+ 0x69ECF0 and operator/ 0x6D9770 out of line. Draw_Double_Selection_Bracket 0x6C3950 stays exact under it. The fragile probe has not been run yet.
- Draw_Pre_Render slot 65 0x6C3B30: 95.68 with the Coord model (call pattern exact; one color/dim register tie left). Draw_Post_Render slot 66 0x6C2C40: 42.79 natural, 74.93 with two probe sites (needs the single bracket inline before it plus an emitted 0x6C3A90 row). NoInit ctor 0x6C1F10: 67.89, parked (needs charged IL between the StageClass base and the DVC members, not extra sites).

## Scout633 (2026-11-03, closed; landed Rural 0x589AC0 1,081 B and Seed_Lake 0x57E100 2,839 B)
- OWNER DECISION (reversible): Seed_Lake took over Map_Clamped_Gaussian 0x5798F0 from hand-written population-2543 with allow_split. None of the four rows left in 2543 uses it, and the full build passes.
- The shared fragile probe is now build/class-work/Scout633/fragile_probe.py, with 0x589AC0 added; LANE_BRIEF points to it.
- NE corner 0x574930: 99.26 (keep/ne_574930_9926.cpp; one X-sum operand order). Grow_Water_Region 0x5820B0: 67.01 (the original calls operator+ 0x42ADD0 and ??_GUnknownVeinHeap 0x58DB20 out of line; it needs 0x5798D0 taken from population-953). Not attempted: 0x58A1B0, 0x586340, SE 0x5743F0, Urban 0x587CF0.

## Scout634 (2026-11-03, closed; 0 B; Coord-model rows PARKED after Scout632/634)
- Verdict: Coord (`class Coord : public CoordStruct` with base-copy conversions) belongs in opt-in selection_coord.hpp (overlay Scout632 hA). Appending it to coord.hpp flips Print_CRCs (+0x638, +0x9A8) and Pick_Lobby (+0x2AA) through the declaration counter. coord.hpp's UnknownCoord434820 (20 users) is the same class with a member-wise conversion; merging them needs a full build.
- Draw_Pre_Render 0x6C3B30: 95.68 (w/u3.cpp with `CoordStruct const &lepton = ...; ::Coord dim = lepton;` is one natural late free site short; u3i 95.55). BuildingLight Draw_It 65.85 and Hover Process 62.05: the model gives no sites there (derived-to-base is not a site). Fire_At 99.81 with ::Coord replacing the file-local OffsetCoord.

## Scout636 (2026-11-03, closed; Wave Set_Laser_Pixel 0x721B00 240 B landing)
- Stale entries: Init_Theater 0x519E70 and 0x516E70 were accepted in NearMiss392 r1 (a9c348882), Terrain slot 63 0x6E4430 in Scout522 r3 (697365b19). Ignore their older miss lines.
- Allocate_Surfaces 0x519500: 71.67, parked. The DSurface ctor 0x4AA4A0's third parameter is really bool (compared as a byte), so don't build the int rename. Wave Load 0x7221D0: 79.67 (TibSun layout; about 3 natural sites short after the NoInit ctor). Brighten_Pixel's file-local min can't share a unit with always.hpp, so the Wave unit uses a guarded MIN macro.

## Scout635 (2026-11-03, closed; Set/Get_Cell_Data_Spread 0x5818E0/0x581910 81 B landing)
- Grow_Water_Region 0x5820B0: 81.86 natural (keep/grow_water_5820b0_8186.cpp, overlay keep/hW3). operator+ 0x42ADD0 is a nested site inside Adjacent_Cell, refused only when root sites follow the call. Exact call sequence with one probe after Adjacent_Cell (84.97). It needs 0x5798D0 from pop-953 (allow_split, as approved for 0x5798F0). TibSun mapgen.cpp:7216.
- NE corner 0x574930: 99.26 (the only exact form computes both sums twice: steering, not delivered). Urban 0x587CF0: 90.41, parked (`cells` reload position). Set/Get_Cell_Data_Region 0x581870/0x5818A0 are exact in TibSun form but already accepted seeds of hand-written pop-45 (0 bytes, would need allow_split).

## Scout637 (2026-11-03, closed; landed IsUnderBridge accessor rename and Preview_Cell_Color 0x4710D0 plus accessor 0x4788D0, 502 B; survey in build/class-work/Scout637/TARGETS.md)
- TARGETS.md: about 23 fresh rows over 400 B with TibSun counterparts. Scout639 works it.
- Cell rows must be scored in the whole unit (Scout637 join.py). Find_Object 0x471760 inlines at every depth-1 site; the original reaches it through the unit's inline wrappers (Cell_Building 0x4717B0, Cell_Terrain 0x4717E0), which put it at depth 2.
- Cell_Color 0x4712C0 (924 B): 60.93 (w/keep/). Theaters[].unknown_50/54 are TibSun's radar brightness tables.

## Scout638 (2026-11-03, closed; 0 B; map generator PARKED, three /Ob2 budget plateaus; resume in build/class-work/Scout638/NOTES.md)
- Grow_Water_Region 0x5820B0: 84.09 (keep/gw_m3_8409.cpp; member Get_Cell_Data helpers put operator+ and ??_G out of line; the frontier's nested Get_Cell_Data is still refused). Place_Tile_Patch 0x586340: 51.10 (overlay keep/hI, TibSun bool Insert). Generate_Rural_Roads 0x58A1B0: 50.51 (needs pop-2900's two Link ctors 0x58B140/0x58B160 via allow_split, OWNER: approved if a round goes exact; the event.hpp QueueClass ctor overlay needs a fragile probe).
- Next for this unit: measure the IL sizes of the shared helpers (UnknownVeinHeap Insert, Get_Cell_Data, the Link ctors) with Scout626 mu.py before drafting more shapes.

## Scout639 (2026-11-03, closed; DriveLocomotionClass::Process 0x4A05F0 1,483 B landing)
- The Drive unit now uses Ship's COM Move_To (RA2_SHIP_MOVE_TO_VALUE, RA2_SHIP_CELL_ACCESSORS). Drive Move_To 0x49FE30 takes COMCoordStruct and stays exact.
- MapClass Zone_Reset 0x54EBD0: 81.49, shape 99.18 (w/keep/zone_reset_8149.cpp). The real body is 1,646 B (pass 5's 737 B is truncated). It returns bestzone, so it needs an R spec `...QAEXXZ` -> `...QAEHXZ` first. Register and slot pairing are left.
- Drive Draw_Matrix 0x4A0050: 83.48 (Ship twin plateau). Fly Nearing_Target 0x4BE720: not drafted (IFlyControl held pointer, out-of-line query 0x4BFC20). 0x473F20 is RA2-only.
- Owner tooling item (2026-11-03): codex1 r945 (DynamicVectorClass<HSVClass> ctor 0x6051F0 typed-identity rename, 0 B) is blocked because apply_rename does not regenerate population-36's closed compiler-output policies (rows 0x59FFE0, 0x6051F0, 0x621FA0, 0x682580). Deferred. It only unblocks PaletteName::Load 0x603380 (88.45).

## Scout641 (2026-11-03, closed; Zone_Reset int-return rename landed e3675bec6)
- Zone_Reset 0x54EBD0: 84.41 (w/keep/zone_reset_8441.cpp, EXTRA 54fab0=fab0a.cpp, overlay hZR, RA2_MAP_ZONE_RESET; body_bytes 1646). Left: register and slot choices coupled to the block layout of the inlined 0x54FAB0 clamp.
- House 0x4F5D30 (wall planning around ProtectWithWall buildings): 93.18 fresh. About 90 IL units short at the 6th insert (0x4F6BE0 may be a BaseNodeClass(int, Cell const &) ctor). Hover 0x4FCBC0 is TibSun's While_Moving (3.7 KB): not drafted.
- OWNER DECISION: codex4 r106 retires the bogus one-byte row 0x75272B inside its complete atexit cleanup 0x752710. Bogus rows wholly inside an independently bounded body may be retired in the plan.

## Scout640 (2026-11-03, closed; 6,897 B landed: Place_Down 0x54AB70, Pick_Up 0x54AF70, Repair_High_Bridge_Span 0x54B560, Repair_Train_Bridge 0x552570)
- New shared headers: map_overlay.hpp (OverlayClass stand-in), map_cell.hpp +0x140 flags union and TibSun Get_Bridge_Deck_Cell, map_adjacent.hpp Facing_Add/Facing_Sub.
- Repair_Bridge 0x555A60: 63.60 (one tail merge; frame 0x54 vs 0x48). Damage_Train_Bridge 0x5539B0: codex2 66.45. Likely quick: Repair_Train_Bridge_Span 0x54BE80 (codex2 86.94, the train twin of 0x54B560) and 0x553570 (needs Get_Bridge_Deck_Cell, which now exists). Scout643 continues.

## Scout642 / Scout643 (2026-11-03; landed the BaseNodeClass ctor rename, House wall planner 0x4F5D30 1,399 B, Repair_Train_Bridge_Span 0x54BE80 2,328 B)
- OWNER DECISION (reversible): 0x4F6BE0 is `BaseNodeClass(int, Cell const &)`, declared only in the House unit (RA2_BASE_NODE_FULL_ARGUMENTS). TibSun's member operator> 0x42BF60 is declared outside its guard so the declaration counter keeps Print_CRCs exact (only offsets -2..0 around HEAD are good). Option: Make_Base_Nodes 0x4EF890 stays exact with the 2-arg ctor, so the hypothetical 4-arg ctor could be retired.
- House 0x4F2350: 68.39. AI takeover 0x4F4070: 70.90 (not a plain budget shortfall; look for an inline wrapper at the second 0x4F52F0 site). 0x4F03C0 Where_To_Place_Building: codex2 60.23.
- Bridge walk-loop rows: 0x553570 61.84, 0x555A60 63.60, 0x5539B0 66.07 share one residue (the original hoists only &AdjacentCell[step&7]). Scout645 is studying it. 0x553000 (codex2 78.63) not started.
- IL sizes measured (Scout642): Cell(int,int) 42, operator+ 66, body-assignment ctor 64, init-list ctor 54, Insert_After 200.

## Scout644 / Scout645 (2026-11-03; landed TechnoClass slot 174 0x6C1380 592 B and Destroy_Train_Bridge_Connections 0x553570 1,088 B)
- Techno slot 186 0x6CD340: 80.18. Tunnel depth 0x6CFB60: 49.84. DistributedFire 0x6D4400: not drafted (four DVC vtables). Scout646 continues them. Tactical 0x6AB360 and PlanMgr 0x617340 wait on the TacticalProjection and Rect-family /Ob2 models; don't assign them yet.
- Repair_Bridge 0x555A60: 99.75 (one Y-sum operand order). OWNER DECISION: the redundant `if (X >= n) { while (X >= n) ... }` guard is accepted. Destroy_Train_Bridge_Span 0x553000: signature to settle first (Map405 76.36). Damage_Train_Bridge 0x5539B0: 66.07. Scout647 continues them.

## Scout646 / Scout647 (2026-11-03; landed TechnoClass DistributedFire 0x6D4400 673 B; bridge rows below 0x556000 PARKED)
- Repair_Bridge 0x555A60: 99.75. Its Y sum is origin-first; every accepted hoisted-address loop is table-first, and the only other origin-first case is 0x55730D in Destroy_Low_Bridge2_Span 0x557090. Copy that shape when 0x557090 goes exact. Destroy_Train_Bridge_Span 0x553000: 78.79 (signature stays `(Cell const &, FacingType, Rect *)`). Damage_Train_Bridge 0x5539B0: 66.07.
- Scout647 w/scan_all.txt lists 73 original loops with a hoisted AdjacentCell address.
- 2026-11-03 ~01:00Z (Nov 4): Map.CPP 0x556000-0x56CEF0 moves from codex1 (now on FlyLocomotionClass) to the Mac lanes.

## Scout646 (2026-11-04, closed; TechnoClass DistributedFire 0x6D4400 673 B landed)
- Slot 186 0x6CD340: 80.18, parked after two lanes. Its overlay (w/h1: foot.hpp UnitTypeClass `bool IsSimpleDeployer` at +0xBAB, building_type_class.hpp `bool unknown_45ec40() const`) is probe-clean and accepted.
- Tunnel depth 0x6CFB60: 80.77 (w/x1.cpp; `Map[Adjacent_Cell(cell, facing)]` for all six sums plus named MapCoords copies before each sum). Left: the first step's X-into-position store order and one esi/edi swap.

## Scout649 (2026-11-03, closed; 0 B; InfantryClass PARKED)
- Scatter 0x504120: 94.14 (w/s1.cpp; one spot left, `mov eax,[0xA41130]; imul eax,edi` vs ours `imul edi,[mem]`; the accepted UnitClass twin 0x7072D0 gets the original form). Per_Cell_Process 0x500AA0: 93.45 unchanged after 227 compiled mutations; only side-effect-breaking reorders flip the allocation (w/t1.cpp 99.24, not landable).
- Correction: diff_candidate.py has no remote path; only full builds (check_plans --build, landings) compile remotely. Scoring stays in local Wine, one compile at a time.
- Date correction: entries above dated 2026-11-04 happened on 2026-11-03 around 22:00Z.

## Scout648 (2026-11-03, closed; Destroy_High_Bridge_Connections 0x558BD0 1,066 B landed; table in build/class-work/Scout648/LIST.md)
- Near misses: Destroy_Low_Bridge2_Span 0x557090 and twin 0x556520 99.54 (one end-walk X sum), Repair_Bridge 0x555A60 99.75, 0x566C30 98.96, Damage_Low_Bridge family (4 rows, 5,220 B) 98.73, Place_Wall 0x56A660 96.62.
- Finding: which operand of a 16-bit Cell sum loads first does not follow source order. Dead locals shift it with period 8 (position irrelevant); extern declarations before the function have no effect; a `(Cell)` cast counts as one symbol. Scout651 studies it.

## Scout650 (2026-11-03, closed; 0 B; resume in build/class-work/Scout650/NOTES.md, drafts w/keep/)
- Overlay Mark 0x5DA970 (3,251 B): 99.30, shape 100 (one place-loop Y operand order). IPXManager Service 0x525F60 (2,704 B): 97.99 (0 cached in ebp shared with the final loop index). Hover While_Moving 0x4FCBC0 (3,696 B + 32 B table): 86.93 first draft.

## Scout651 (2026-11-03, closed; 4,466 B: bridge span twins 0x556520/0x557090, Place_Wall 0x56A660, Unregister_Subzone_Connection 0x566C30)
- Repair_Bridge 0x555A60: 88.86 at HEAD headers (the 99.75 no longer reproduces; w/keep/rb1.cpp; one spot at +0x371). Damage_Low_Bridge family (5.2 KB): 98.73 (w/keep/de2.cpp, fcc.cpp); landing it means re-landing the four Spring/0x55FA60/0x55FB90 sources.

## Scout652 (2026-11-03, closed; OverlayClass Mark 0x5DA970 3,251 B landed with atexit thunks 0x5DB630-0x5DB660)
- OWNER DECISION: Mark keeps `TPoint2D<short> next = Adjacent_Cell(work_cell, direction); work_cell = next;`. It is a used local, which the process treats as ordinary iteration, not steering, though TibSun has no twin for it.
- Hover While_Moving 0x4FCBC0: 92.56, shape 98.90 (w/keep/hover_while_moving_9256.cpp, w/keep/hs2.cpp; the whole Hover unit is 45/45 under RA2_COORD_AS_CELL, RA2_SHIP_CELL_ACCESSORS, RA2_CELL_AS_COORD, RA2_COORD_FROM_CELL_INLINE). Real code left only at 0x2FF-0x344. The clean fix types tube EnterCell/ExitCell as TPoint2D<short> in tube.hpp (fragile probe first). IPX Service 0x525F60: 97.99, parked (why T skips edi is unexplained).

## Scout654 (2026-11-03, closed; 5,973 B: Hover While_Moving 0x4FCBC0 + table, Stop 0x4FDA50, Process 0x4FBFC0; the Hover unit is complete)
- OWNER DECISION: `RA2_PROCESS_COM_BOOLEAN` makes Process return `unsigned char` (`mov al,7`) for the Hover unit only, so other units' declaration counters stay put. Retyping every override is a later 12-row rename.
- OWNER DECISION: tube.hpp stays untyped. Typing EnterCell/ExitCell refuses Can_Enter_Cell 0x503190 and five TubeClass rows at full build (the fragile probe was clean) and moves While_Moving's Cell-sum phase; the Hover draft binds `TPoint2D<short> const &enter = tube->EnterCell;`.
- Ship While_Moving 0x676F60: 70.20, shape 97.40 (Scout654 w/keep/sw0.cpp). Drive twin 0x4A1000: 68.94 (w/keep/dw0.cpp). One residue in both: ours caches -1 in edi from the first `unknown_58 == -1` through the acceleration block, the original compares with an immediate and starts -1 at the tube test. About 20 variants had no effect (NOTES.md). Untried: one more inline level around the Coord difference (`mov esi,edx` at 0xFB), possibly a TPoint3D operator-. Start_Of_Move 0x4A2670 / 0x6785C0 not attempted.

## Scout653 (2026-11-04, closed; 1,841 B: Get_Bridge_Zone_Connection_Cell 0x564F70, Find_Nearby_Shroud 0x5629D0; resume points in build/class-work/Scout653/NOTES.md, drafts w/keep/)
- Damage_Low_Bridge family (5,220 B): 98.73 (de2). Site +0x16F does not move over the full T mod 8 cycle, 65 declaration offsets, Union forms or parity forms; it flips only when a whole Damage call, the U2 statement or both Map[] lines go.
- Repair_Bridge 0x555A60: 90.89 (rb2; rb1 88.86 with 4 diffs is the fallback). +0x371 and W are fixed; op+ at 0x5C2 needs a charge over 40 between the walk and 0x5C2 with no new site.
- 0x558660 76.61 (dh1; dh2 fixes the frame by homing the Rect but moves `dir` into ebx). 0x567710 84.49 (mf3, overlay h3; the original refuses region_cells.Add). 0x55D640 75.88 (pv, overlay h4; block layout only). 0x568B00 76.62 (wb2 plus a cast; second first-step op+ must be refused). 0x5653C0 68.87 (sc2; original keeps a duplicate test ours merges).

## Scout655 (2026-11-04, closed; 0 B; Ship and Drive While_Moving PARKED after two lanes; build/class-work/Scout655/NOTES.md)
- Ship While_Moving 0x676F60: 74.75, shape 97.71 (w/keep/sw_x4.cpp, cleaner sw_u2.cpp 72.90; both need overlay ov/shared/{rect,locomotion,coord}.hpp, which has no fragile probe or full build yet). About 150 real diff lines stay even with the -1 web out of the way (probe sw_g4_headprobe.cpp 75.75, not landable). Resume: one real pseudo at the peak 0x104-0x135 that compiles to nothing. Also open: frame order, occupier join 0x978-0x995, Adjacent_Cell phase 0x46B, `partial` temp slots, zero web from 0xF97.
- Drive 0x4A1000 still 68.94: re-port once Ship goes exact. Start_Of_Move 0x4A2670 / 0x6785C0 still not attempted.
- OWNER DECISION: RA2_COORD_TPOINT3D and RA2_TRACK_POINT_STRUCT are not adopted for the Ship and Drive units yet, because both change every accepted row there. Decide when a row needs them for exact.

## Scout656 (2026-11-04, closed; 2,146 B: Spring_Bridge_Destruction_Triggers 0x558340, Get_High_Ground_Mask 0x55BD70; drafts in build/class-work/Scout656/w/keep/, Scout658 continues)
- 0x564B60 98.20 (zc_9820.cpp, overlay zc_h; registers only at +0x1B6..0x1D6). 0x565EB0 93.83 (br_9383.cpp; two ties). 0x565A50 87.74 (ra_8774.cpp; Cell ctor at site 4 must be refused). 0x5689D0 60.00 (ce_6000.cpp; frame 0x10 vs 0xC). Damage_High_Bridge 0x559000 51.10 (dh_5110.cpp; the original holds ebx=cell, ebp=this throughout, ours spills them).
- Not attempted: 0x563D80, 0x564290, 0x566340, 0x569320 (7,858 B).

## Scout657 (2026-11-04, closed; 3,988 B: ParticleClass ctor 0x608440, Motion_Capture 0x53F490, Railgun AI 0x60C050 with Spawn_Particle 0x60B190; drafts build/class-work/Scout657/w/keep/)
- OWNER DECISION: `Velocity_Limit` (file-local one-line inline, the only form that gives `fld st0; fld mem; fcompp`) stays as landed; make it a ParticleSystemTypeClass member when that class is typed. The file-local `operator+=(Vector3 &, Vector3 const &)` moves to vector3.hpp when that header is next opened.
- Spark AI 0x60B670 86.56 (s0.cpp + b190t.cpp; register rotation, 64 toggles flat). One_Time 0x521A90 94.19 (ot0.cpp; ot3.cpp has the shape, `mirror` outranks `row` for ecx). Audio_Remove_Devices 0x403210 88.51 (rdv9.cpp). Video_Mode_Proc 0x543CF0 73.96 (vm0.cpp) and Main_Options_Proc 0x542590 85.62 (mo0.cpp): one family, original keeps the index in a register and spills the other value. LdPrgMgr draw 0x535BF0 63.42 (ld0.cpp + d30.cpp; not iterated, frame slots dominate).
- Rows parked before Scout651 are worth one retry with the T probe and the fcompp and CSE forms.

## Scout658 (2026-11-04, closed; 1,999 B: Register_Zone_Connection_Entries 0x564B60, ring collector 0x565A50; drafts build/class-work/Scout658/w/keep/, Scout660 continues)
- 0x565EB0 99.73 (br_u3.cpp, overlay w/h1; one `inc edx` swap; br_s1.cpp fixes it but flips the Y sum at +0x2DC for every k, caused by dropping `writeptr`). 0x563D80 75.56, shape 93.09 (a5.cpp + opa_named.cpp, overlay w/h2; the 0x56C2E0 edit needs a full check). 0x566340 49.75 (c_e_4975.cpp; second FAF0 must be refused). 0x564290 no score (needs a rewrite from TibSun). 0x569320 not started (codex 38.88).
- The inline `SubzoneConnectionStruct::operator=` cannot land: it emits ??4 and resizes four Resize rows, 0x566C30 and 0x566F90.

## Scout659 (2026-11-04, closed; 0 B; drafts build/class-work/Scout659/w/keep/)
- PCX Draw 0x68CF90: 99.55, shape 100 (cf90_u7_99.55.cpp + ov4/, pcx_cache.hpp with bool return; 0x186 first Unlock uses edx, original eax). Exact needs the bool rename (caller 0x5FED10) and Blend_Color in a small header. Scout661 continues.
- Radar 0x634670 97.35 (any wrapper adding a result temp fixes scratch registers but flips the callee-saved trio). Diplomacy 0x6340F0 82.63. Save_List_Selection 0x5C5FF0 94.38 (`name`, `i` slots swapped). One_Time 0x521A90 94.19 (`center-row` computed once with no extra pseudo; every source form normalises it away). Lobby refresh 0x5BBDD0 82.76 (population 3945). Spark 0x60B670 86.56 (population 3963, needs no EXTRA). 0x5CBF20 43.91 (compiles in population-3760). 0x5C69E0 still needs the slot-3 rename. 0x403210 needs the population-3592/3648 merge.

## Scout660 (2026-11-04, closed; Build_Reachable_Subzones 0x565EB0 1,166 B; drafts build/class-work/Scout660/w/keep/, overlay w/h2; Scout662 continues)
- OWNER DECISION: `visited[ax][ay]++` and the named `slot` local in 0x565EB0 are real semantics and count as ordinary iteration, not steering.
- 0x569320 73.73, shape 95.08 (d_7373.cpp; last Map[] needs more charge, tile read order, arm temporaries, `return true` placement). 0x563D80 76.89 (a6_7689.cpp + opa_named.cpp; zero cached in ecx across the loop). 0x564290 42.47, shape 92.36 (b_4247.cpp; begin ebx, end esi, walker edi in the original; uses Span_Pack* because Zone_Pack* is file-local in 0x564B60's source, so landing needs a shared helper or rename). 0x566340 49.75 unchanged (c_e_4975.cpp; TibSun-flow rewrite from line 10900 is next).

## Scout661 (2026-11-04, closed; Place_Tile_Patch 0x586340 1,073 B; drafts build/class-work/Scout661/w/keep/; Scout663 continues the corners)
- SE 0x5743F0 99.51, SW re-roll 95.96, NE 0x574930 99.26 are one round of about 4 KB around one X-sum operand site: they need Mark's aux copy in TibSun Set_Region form, SW with `first-Cell(3,0)` and `second-Cell(2,0)`, an NE fix like SW's (61.20 under the new Mark until then), and a full check. `unknown_005743f0` is overlay-only in h_se and still needs a fragile probe.
- PCX Draw 0x68CF90 99.55 (one tied pair of vtable temps, about 40 variants flat; bool rename not applied). Urban 0x587CF0 90.73 (Scout635 keep; original reloads ebx in the latch). Grow_Water 0x5820B0 84.24 natural, 85.67 with probes (not landable; budget 480 too high at the end). Rural_Roads 0x58A1B0 50.51 (rr0.cpp, overlay h_rr; not iterated).
- OWNER DECISION: the double `unknown_00574930` call in Connect_Regions_With_Ramp stays as landed.
- Lane traps: pass-7 rows need `body_bytes` and `bound_evidence` on the plan row, and RA2_INVENTORY_PASSES must not be set for check_plans. Populations renumber at every landing, and a stale id joins an empty unit and gives garbage scores with no error.

## Scout662 (2026-11-04, closed; 0 B; drafts build/class-work/Scout662/w/keep/, overlay w/h2; Scout664 continues)
- OWNER DECISION: `switch (found) { case false: S; break; default: F; }` on a bool is acceptable source: it is semantically plain and the normal iteration the process allows. `Is_Span_EW(overlay, base)` stays as a file-local helper if 0x569320 lands; its name is a hypothesis.
- 0x569320 99.49, shape 100 (d_9949.cpp; `search` lands in [2c], the original has [14]; needs a join that survives until tail merge without adding refs to `search`). 0x566340 51.41, shape 97.61, calls equal (c_5141.cpp; ebx/edi swap plus spill order; `Cell_Passability` must become a MapClass inline under RA2_MAP_BRIDGE_PIECES before landing). 0x564290 42.47 and 0x563D80 76.89 unchanged.

## Scout663 (2026-11-04, closed; 3,975 B: corner ramps SE 0x5743F0, NE 0x574930 with SW re-rolled; Generate_Rural_Roads 0x58A1B0; drafts build/class-work/Scout663/w/keep/)
- OWNER DECISION: `Road_Tile_Set`, a file-local one-line `tile!=0xffff` helper in Rural_Roads, stays as landed: real semantics, name unevidenced, it supplies two free /Ob2 sites. The named `top` plus written-out Rect height is ordinary iteration.
- Find_Dirt_Road_Tile 0x58A6E0 (736 B): 96.60, shape 99.51 (find_58a6e0_9660.cpp + Map_Clamped_g1.cpp; loop count and walker eax/ecx swapped; needs 0x5798F0 re-rolled to `mean-deviation>maximum`, not fully checked). Urban 0x587CF0 90.73, Radar 0x634670 97.35 (7 init-order forms flat), Save_List_Selection 0x5C5FF0 94.38 (slot order follows surviving references) stay parked.

## Scout664 (2026-11-04, closed; 0 B; Map.CPP continuation PARKED after two zero-byte lanes; build/class-work/Scout664/NOTES.md lists what was ruled out)
- 0x569320 99.49: about 60 variants, plateau. Only a real source-level idea reopens it (a join block that survives tail merge and emits nothing; rotated loops give [14] but the head copies never merge). 0x566340 64.37, shape 98.45 (c_6437.cpp; register-clean, frame slots left; `Cell_Passability` still to move). 0x564290 42.47, 0x563D80 76.89 unchanged.

## Scout665 (2026-11-04, closed; 4,523 B: Build_East_Ramp 0x573040, Build_West_Ramp 0x573D40, Plan_Paved_Road_Junction 0x588560, Plan_Paved_Road 0x588850; drafts build/class-work/Scout665/w/keep/, LIST.md; Scout667 continues)
- OWNER DECISION: `RA2_POINT_ADD_IN_PLACE`, `Adjacent_Road_Cell` in Junction, and `Rect const &area = rect` in both Plan rows stay: real semantics, no TibSun evidence for the alias. Reopen them when Generate_Urban_Roads shows the caller. Both Plan rows are free `__stdcall` for now, as ECX is not read; the member form stays open until then.
- South ramp 0x5729F0 97.01 and North ramp 0x573680 97.14, shape 99.90 (one hunk: original `sub ax,[span]; sub ax,[edi]`, ours goes through esi; only rows reading the X field at offset 0). Find_Dirt_Road_Tile 0x58A6E0 96.60 parked (19 more forms flat; 0x5798F0 re-roll unchecked).
- Untouched: Create_Resources 0x583B80, Seed_Hill_Heights 0x584730, Generate_Vegetation 0x5852C0, Generate_Urban_Roads 0x587330, Connect_Regions_With_Bridge 0x570BC0. 0x58AD90 has no TibSun source. Inventory rows 0x581EE0, 0x579960, 0x585DC0, 0x586B40, 0x57D3A0 are truncated bounds, not real sizes.

## Scout666 (2026-11-04, closed; 0 B; drafts build/class-work/Scout666/w/keep/, LIST.md 266 rows; Scout668 continues)
- OWNER DECISION: slot 218's third parameter becomes bool across Techno, Aircraft, Building, Infantry and Unit when Can_Fire is ready to land, as an atomic rename. A second `if (weapon == 0) goto CANT;` that folds away is dead source kept only for block order and is not accepted; find a live form. File-local `Coord_Size` may land in Evaluate_Object if it goes exact.
- Evaluate_Object 0x6C5570 (2,998 B) 91.70, shape 99.84 (eo_9170.cpp; the `method` read for the 0x800 test is a separate eax load, the original keeps one edx web over all five tests). Can_Fire slot 218 0x6C9260 (2,089 B) 82.58, shape 98.88 (cf_8258.cpp; register rotation from 0x33E). Area_Modify 0x6C5270 96.38 (fourth-ring operand order). Is_Clear_To_Build 0x4718B0 51.04 (Find_Object(0x24) must stay a call).
- Best untouched twins: Draw_Pips 0x6D4920, Can_Build 0x4E3660, IsometricTileTypeClass::Init 0x52A790. Overlay w/h has not had a fragile probe or full check.

## Scout667 (2026-11-04, closed; 4,413 B: Create_Resources 0x583B80, Generate_Vegetation 0x5852C0, Seed_Hill_Heights 0x584730; drafts build/class-work/Scout667/w/keep/; Scout669 continues)
- OWNER DECISION: the one-line helpers `Cell_Distance`, `Rich_Starts`, `Start_Count`, `Overlay_Is_Clear`, `Set_Overlay` and `Hill_In_Radar` stay as landed (real semantics, names unevidenced). Seed_Hill's `double const &h = data.f; data.f = h;` stays: the original emits that store, and a plain self-assign vanishes.
- Source order: r2 and r3 sit after Rural 0x589AC0 in plan order because their declarations put Rural in its failing counter window. Later new rows before Rural need the same (Scout667 fz.sh AFTER/MOVE).
- Generate_Urban_Roads 0x587330 78.56, shape 98.12 (urban_roads_7856.cpp, overlay h1, junction_member.cpp, plan_member.cpp; zero web lands in esi and splits around the fill loop, original keeps ebp; removing every 3 in the horizontal part is the lead). Plan rows are members: the caller sets ECX=this; both stay exact as members, Plan_Paved_Road with Adjacent_Road_Cell at all three sites. Land with Urban; h1 has had no probe or check. Connect_Regions_With_Bridge 0x570BC0 72.04, shape 79.47 (bridge_7204.cpp; first pass). South/North ramps not attempted here.

## Scout668 (2026-11-04, closed; Can_Fire 0x6C9260 2,089 B plus the slot 218 bool rename; drafts build/class-work/Scout668/w/keep/; Scout670 continues on TibSun twins)
- Evaluate_Object 0x6C5570 91.70, parked after two lanes (eo_9170.cpp; the memory test `test byte [esp+0x40],0x40` at 0x901 splits the method web; `mask&0x40` there scores 99.67 and only that operand differs; resume needs a memory test that does not count as a ref of that live range). Overlay w/h has had no probe or full check.
- Area_Modify 0x6C5270 96.38, parked (site 4 `ADD y,[ptr].Y` reversed; source operand order does not reach it).
- Draw_Pips 0x6D4920 55.09, shape 91.09 (dp_5509.cpp; frame 0x7C vs 0x64, X/Y induction swapped). Can_Build 0x4E3660 and IsometricTileTypeClass::Init 0x52A790 not started.
- Tool idea: Scout668 t/check_both.py lifts the rename-plus-plans refusal in check_plans, so a lane can check a post-rename plan before the rename lands.

## Scout670 (2026-11-04, closed; Can_Build 0x4E3660 2,608 B with the rename; build/class-work/Scout670/NOTES.md; Scout671 continues)
- OWNER DECISION: file-local `House_Owner_Bit` stays as landed. It exists mainly to supply two root inline sites, and as a house_type.hpp member it broke Print_CRCs and Generate_Rural_Buildings.
- Row 0x52A790 is bogus: the true function is 0x529870, 6,762 B (pass-7 bound), fastcall (int theater, bool from_ccfile), TibSun Read_Control_File, 40.3, shape 96.8 (keep/ii_tmpl.cpp + gen_ii.py; ii_4006_nop5.cpp has probes and must not land). Also bound as Read_Tile_Control_00529870 in Init_Map 0x57AE00: unify when it lands.

## Scout669 (2026-11-04, closed; 8,305 B: South 0x5729F0, North 0x573680, Connect_Regions_With_Bridge 0x570BC0, Generate_Neutral_Tech_Buildings 0x58AD90; drafts build/class-work/Scout669/w/keep/; Scout672 continues)
- OWNER DECISION: `Pick_Region_Cell`, `Region_Size`, `Cell_Is_Free`, `Is_List_End` and `Cell_Height` stay as landed. The member Plan rows keep waiting for Urban.
- Generate_Urban_Roads 0x587330 99.06, shape 99.84 (urban_roads_9906.cpp, overlay h1 fragile-clean, no check_plans yet, junction_member.cpp, plan_member.cpp, scorer eu.sh). Residue: the horizontal width test, original `movsx ecx,cx; movsx edx,ax; sub edx,ecx; cmp edx,6`. `end.X>=start.X+6` gets the registers but emits `add ecx,6; cmp edx,ecx`; `end.X-start.X>=6` scores 87.22. Source must follow 0x570BC0 in plan order (Place_Tile_Footprint defaults).
- Find_Dirt_Road_Tile 96.60 and Urban Buildings 0x587CF0 90.73 unchanged. A landing can tear the catalog mid-read (ValueError "torn"); wait and rerun.

## Scout672 (2026-11-04, closed; 2,965 B: Generate_Urban_Roads 0x587330 with member Plan rows, 0x582FD0; drafts build/class-work/Scout672/w/keep/; Scout673 continues)
- OWNER DECISION: `bool valid` / `int first` in Urban Roads stays as landed: the flag is live and semantically plain, the same class as `if (placed && success)`.
- Seed_River 0x57ECF0 (4,386 B) 42.25, shape 91.14 (seed_river_57ecf0_4225.cpp, overlay h2 with no probe yet, rv.sh, nd.py; mostly frame offsets, needs 8 more frame bytes and `this` in memory with zero in edi). 0x57C780 68.93 (land_mass_57c780_6893.cpp; original keeps zero in esi, `this` in edi, maximum in memory). Find_Dirt_Road_Tile 96.60 and Urban Buildings 90.73 unchanged.
- Not attempted: 0x57C9E0 (1,231 B), 0x576420 (925 B), Place_Waterfall 0x57FF20 (6,413 B), 0x58B420 (58 B static init), Grow_Water 84.24. Drop from lists: 0x5824D0 (Grow_Water tail), 0x579D30 (Read_Settings tail); 0x576000 and 0x5760F4 look like bad bounds.

## Scout671 (2026-11-04, closed; 2,903 B: Cell_Color 0x4712C0, Get_Height 0x4706C0; drafts build/class-work/Scout671/w/keep/; Scout674 continues)
- Place_Tiberium 0x47C3A0 98.91, shape 100 (one eax/ebx pair at +0x3CC). Fixup_LAT 0x471D10 97.74 with 6 Nop probes, clean 69.63 (needs a rename to bool Fixup_LAT() and 6 real root sites). Is_Clear_To_Build 0x4718B0 71.99 (needs 0x471830 rewritten so it auto-inlines). Optional rename: unknown_4706c0 to Get_Height.

## Scout673 (2026-11-04, closed; Seed_River 0x57ECF0 4,386 B, the largest open map generator row; drafts build/class-work/Scout673/w/keep/, overlay h2 with bool Place_Waterfall; Scout675 continues)
- OWNER DECISION: `Clear_River_Region(int region, int const &height_source)`, the written-out Gaussians, `unsigned char success` and `unknown_lake_chance_7a5cb0` stay as landed. Retyping Unknown_0055C2C0 to bool is a later rename.
- Place_Waterfall 0x57FF20 (6,413 B) 33.08, shape 59.54; resume from waterfall_57ff20_rect_ctor.cpp (22.55, closer register pattern); the four inner cases 0x1000-0x2400 are most of the diff; return type bool. 0x57C780 70.06 (land_mass_57c780_7006.cpp; while form 66.29 has correct jumps). 0x57C9E0 53.92, shape 94.04 (arm 2's `Width` needs ebx; frame 0xb0 vs 0xb8). 0x576420 not attempted (stack IndexClass with qsort; no TibSun twin). Grow_Water 84.24 unchanged.

## Scout674 (2026-11-04, closed; AI takeover 0x4F4070 2,731 B; drafts build/class-work/Scout674/w/keep/; Scout676 continues on House)
- OWNER DECISION: file-local `Is_Network_Computer` in 0x4F4070 stays until the real member is identified. The swapped `power+=`/`drain-=` order and reused power locals are plain source order.
- Place_Tiberium 98.91, Fixup_LAT 69.63 clean (97.74 with Nop probes, not landable), Is_Clear_To_Build 71.99 (7 false-epilog copies vs our 10): boxes spent, parked. Place_Veins 0x47AD00 78.39, shape 98.66 (place_veins_7839.cpp + vein_frame_47a5a0.cpp; TibSun twin; ebx/ebp swap, draft carries `Is_Solid_Vein`, a site-supplying helper to review before landing; the 0x47A5A0 rewrite is unproven in the population). House perimeter 0x4F2350 68.39, shape 95.93 (wall1.cpp; mostly frame slots). 0x4F03C0 60.23 not reached. 0x4EEE10's decompile is garbage from an entry overlap: check its bound first.

## Scout675 (2026-11-04, closed; 0 B; drafts build/class-work/Scout675/w/keep/, overlay h2; Scout677 continues Waterfall)
- OWNER DECISION: retyping Unknown_0055C2C0 to bool is approved as a rename round when Waterfall needs it (no probe or check yet; Seed_River, Seed_Lake and Initialize_Region_Map call it).
- Place_Waterfall 0x57FF20 58.20, shape 90.01 (waterfall_57ff20_5820.cpp; 268 of 1,626 normalized diffs; most follow from why pre_x spills). 0x57C9E0 53.92 (two_rect_57c9e0_v2_norm39.cpp has best statements; Width must reach ebx). 0x57C780 70.06. All three want a loop-crossing pseudo in memory where ours keeps a short register stretch, so a statement diff may still hide in each. 0x576420 and Grow_Water not attempted.

## Scout676 (2026-11-04, closed; 0 B; drafts build/class-work/Scout676/w/keep/; Scout678 continues)
- OWNER DECISION: House.CPP gets a small unit-scoped house_adjacent.hpp with the cell-left Adjacent_Cell (TibSun inline.h) in place of file-local Wall_Adjacent and Step_Cell; infantry.hpp's offset-left form stays as it is. `Facing_Offset : Cell` and Coord_Span in 0x4F03C0 are provisional; revisit them when the row is near exact. Rename unknown_func_4f4b20 to Update_Present_Super_Weapons when 0x4F4B20 lands.
- AI_Build_Wall 0x4F2350 88.82, shape 98.74 (wall_8882.cpp; TibSun twin at house.cpp:8196; one misplaced block). Where_To_Place_Building 0x4F03C0 60.61, shape 98.10 (wp_6061.cpp, scored with no @refs, so it understates; `offset` slot 0x3c vs 0x94). Update_Present_Super_Weapons 0x4F4B20 87.59, shape 96.71 (super_x5_8759.cpp; original keeps `test bl,bl` that our threader removes). AI_Building 0x4E9660 99.42 (one scheduling block; all 24 copy-ctor orders swept).

## Scout677 (2026-11-04, closed; Place_Waterfall 0x57FF20 6,472 B with the bool rename; drafts build/class-work/Scout677/w/keep/)
- OWNER DECISION: `int seg = 0; if (seg < H) { ... do ... }` stays: it is live source, slightly better than `if (H > 0)`.
- 0x57C780 96.59, shape 100, zero normalized diffs (land_mass_57c780_9659.cpp; only `placed`/`attempts` slots swapped; 9602 has the right store order). 0x57C9E0 54.55 (two_rect_57c9e0_5455.cpp; frame 0xb0 vs 0xb8). 0x576420 45.80 (true extent 993 B, needs body_bytes; the original calls Destroy_Cell_Regions and Generation_Cell_In_Bounds out of line, so it may be a separate TU).

## Scout678 (2026-11-04, closed; AI_Build_Wall 0x4F2350 2,405 B; drafts build/class-work/Scout678/w/keep/; Scout680 continues)
- OWNER DECISION: `Rect &area` with the direct tail assign stays, the same class as the earlier reference alias. `house_adjacent.hpp` landed as a FacingType overload because the RA2_ADJACENT_CELL guard is already set in this population.
- Rename unknown_func_4f2350 to AI_Build_Wall pending (Scout680). Update_Present_Super_Weapons 0x4F4B20 87.59 (super_c0_7939.cpp is structurally closest; the threader sees through flags, only a path with the flag unknown keeps the test). AI_Building 0x4E9660 99.42 (schedule is alias-driven: no legal form yet). Where_To_Place_Building 0x4F03C0 63.99 with @refs bound (wp_w0_6399.cpp; wp_y1_rectfields.cpp has the original statement order, frame 0xdc). Place_Veins 78.39 unworked.

## Scout680 (2026-11-04, closed; Where_To_Place_Building 0x4F03C0 2,629 B with atexit thunks and the AI_Build_Wall rename; drafts build/class-work/Scout680/w/keep/, LIST.md has twins for 44 rows; Scout681 continues)
- `Facing_Offset`, `Coord_Span` and `Coord_Span2` stay provisional file-locals; Coord_Span2 is probably the inlined second site of one Length. 0x4F8C60 is really IndexClass<int,Cell>::Increase_Table_Size, bound by @ref, renaming touches many populations, so left.
- Redraw_Veins 0x47A7A0 77.77, shape 98.06. Place_Veins 78.39 parked (`Is_Solid_Vein` unjustified, without it 68.91). Random_Cell_In_Zone 0x4ECA50 53.51. Expert_AI 0x4E8990 62.21.

## Scout679 (2026-11-04, closed; 9,604 B: Draw_Pips 0x6D4920, Read_Control_File 0x529870; build/class-work/Scout679/NOTES.md; Scout682 continues on Ship and Drive)
- OWNER DECISION: all stay as landed: `int full = 1; int empty = 0;` pairs, `Expanded_Intersect`, `Point2D::operator*` under RA2_POINT2D_SCALE_OPERATOR (unguarded it breaks Print_CRCs and Pick_Lobby), `CDTimerClass<SystemTimerClass> fresh(4); callback_timer = fresh;`, and `char suffix[10]` at function scope. All are live source; none has TibSun evidence beyond the match.
- Later rename: unify ?Unknown_00529870@@YIXH_N@Z and Read_Tile_Control_00529870 in Init_Map 0x57AE00 as Read_Control_File.

## Scout681 (2026-11-04, closed; 2,455 B: Railgun_Beam_Damage 0x6D6ED0, Draw_Rally_Points 0x6AAFD0 with Point2D::operator-= COMDAT, Rectangular_To_Isometric rename; drafts build/class-work/Scout681/w/keep/; Scout683 continues)
- OWNER DECISION: `Point2D offset` stays as landed (live and natural source). Railgun's file-local Vector_Length, Percent_Chance and Vector3 operators move to shared headers when convenient.
- 0x6A2740 is `Point2D __fastcall Rectangular_To_Isometric(Point2D)`, not a TacticalProjection ctor, which reopens rows parked on that model (0x6AB360, PlanMgr 0x617340).
- Draw_Waypoints 0x6AB360 63.61 (waypoints_6361.cpp holds a Nop and a Shape_At wrapper: not landable). In_Range 0x6C4BB0 46.61 (about 6 real sites missing; rename unknown_6c4bb0 and a pointer-to-reference coord change go with it). Message_Handler 0x532A60 82.43 (last-site Put must stay a call). Trackball 0x622690 77.73 (needs @ref ??0Vector3@@QAE@MMM@Z=00437690). Draw_Placement 0x6A5670 depends on open rows 0x6A5D70, 0x6A6010, 0x6A6290. Redraw_Veins untouched.

## Scout682 (2026-11-04, closed; 0 B; drafts build/class-work/Scout682/w/keep/, overlay ov/shared, NOTES.md; Scout684 continues)
- Ship While_Moving 0x676F60 86.73, shape 99.10 (sw_8673.cpp, macros hs4.cpp). Drive 0x4A1000 83.63, shape 98.86 (dw_8363.cpp, macros dm.cpp; one T phase off from Ship through its `maxspeed` local). Residues: 0x7F6-0x855 `lea edx` with no copy; 0x997 test eax vs esi; frame 0xE8 vs 0xE4 (T386, the Set_Current dir temp, sits alone).
- Provisional and needing review before landing: `Cell here`, `object`, `CoordStruct(coord)`, `Object_Coord` for oldcoord, the Scout590-era helpers, and `Length`, an overlay macro whose form disagrees with accepted 0x41B780. Overlay rect.hpp predates RA2_POINT2D_SCALE_OPERATOR, so rebase it. No probe or full check yet. Start_Of_Move and Draw_Matrix not reached.

## Scout683 (2026-11-04, closed; Draw_Waypoints 0x6AB360 1,196 B; drafts build/class-work/Scout683/w/keep/, overlay h/; Scout685 continues)
- OWNER DECISION: file-local `Print_Label` and `Dash_Entries` stay as landed (live, plain source, no TibSun evidence). Get_Mouse_Start and Get_Mouse_Count stay behind RA2_MOUSE_FRAME_QUERIES; unguarded they break Do_Reinforcements 0x639970, which is another fragile row.
- Message_Handler 0x532A60 90.21 (mh_mh2_9021.cpp; ecx/edx rotation from the M double-click block; needs table-inclusive body_bytes). Draw_Wall_Placement 0x6A6290 92.79 (wall_z1.cpp; `15*h` tie). Draw_Fence_Placement 0x6A5D70 63.24 (fence_fa_6324.cpp). Trackball 77.73. Not attempted: Firestorm 0x6A6010, Render 0x6A45A0, Draw_Placement, In_Range. PlanMgr 0x617340 depends on the Planning Rect model (Scout583), not the projection.

## Scout684 (2026-11-04, closed; 0 B; drafts build/class-work/Scout684/w/keep/, overlay ov/shared; Scout686 continues)
- OWNER DECISION: `Length` here stays a separate inline, not unified with 0x41B780 (x,y,z with x*x+(y*y+z*z) is required; the accepted form scores 98.64). `a0`/`b0`, `gate`, `object` and `Cell here` are provisional until the row is exact.
- Ship While_Moving 0x676F60 99.32 (y4k5_9932.cpp, 90.84 without its `int probeN` T-phase locals). Drive 0x4A1000 99.17 (dz_k4_9917.cpp). Neither is landable until the probes are replaced by real locals (Ship needs 3 fewer or 5 more, Drive 4 either way). Two shared residues: 0x92D-0x94A Y and Z reads hoist above the X store; 0x995 original `mov esi,eax; test esi,esi`, ours `test eax,eax; mov esi,eax`, a sequence found only at these two sites in .text. RA2_COORD_SELF is probe-only; remove it and Cell_Occupier. RA2_COORD_TPOINT3D and RA2_TRACK_POINT_STRUCT are still unchecked against accepted rows.

## Scout685 (2026-11-04, closed; 4,444 B: Message_Handler 0x532A60, Draw_Wall_Placement 0x6A6290, In_Range 0x6C4BB0, Draw_Placement 0x6A5670; drafts build/class-work/Scout685/w/keep/; Scout687 continues)
- OWNER DECISION: In_Range's file-locals (`Coord_XY`, `As_Building`, `Distance_3D`, `Length_3D`, `Length_2D`, `Length_XY`), the locals `arcrange`, `speed`, `inrange`, `clear`, and Wall's `Point2D offset(0, -1 - height)` with two-step `zoff` stay as landed. Optional renames: unknown_6c4bb0 to In_Range, 0x532120 to Stop_Execution. Stale comment in WWKeyboardClass_Put_Char_005326a0.cpp.
- Firestorm 0x6A6010 98.93 (firestorm_gm_aef_9893.cpp; Y order at the first Adjacent_Cell). Fence 0x6A5D70 83.24 (fence_fo4_8324.cpp; fence_fk5_9892_probes.cpp has probes). Render 0x6A45A0 41.62, shape 89.65 (render_rn3_4151.cpp; rebase overlay hr/).

## Scout686 (2026-11-04, closed; 11,456 B: Ship While_Moving 0x676F60 5,720 B, Drive While_Moving 0x4A1000 5,736 B; build/class-work/Scout686/NOTES.md; Scout688 continues with Start_Of_Move)
- OWNER DECISION: `ObjectClass *&ref = object;` stays in both rows: plain live C++, the only form found that gives the bytes, no semantic job known. The phase-setting named locals (`unit`, `cell`, `ttype`, `target`) stay too: they are used and forward-substituted, their count is what T phase demands, and which ones were real is unknown. `a0`/`b0`, `gate`, `object` and `Cell here` stay. RA2_COORD_TPOINT3D and RA2_TRACK_POINT_STRUCT are adopted for both units; all accepted rows proved exact.
- Start_Of_Move 0x4A2670 / 0x6785C0 not started (Scout592 57.48; codex2 73.71).

## Scout687 (2026-11-04, closed; 1,552 B: Firestorm 0x6A6010, Contains_Selectable_Buildings 0x6AA180, Add_Buildings_To_Selectable 0x6AA300; drafts build/class-work/Scout687/w/keep/; Scout689 continues)
- OWNER DECISION: Firestorm's `zheight`, `px` and `py` stay as landed, and dropping TibSun's `if (range <= 0) continue;` is accepted (behaviour unchanged, `found` stays false). Redundant @refs for 0x6A6010 in Draw_Placement can go later. tactical.hpp declares two Unknown_006A66B0 overloads at one entry: resolve when that row is worked.
- The old "dead X store" projection parking is stale: 0x6AA180 went exact on the first draft. Retry 0x6A29D0, 0x6A8560, 0x6A92A0, 0x6AC420, 0x6A7350, 0x6A93F0.
- Fence 0x6A5D70 84.05 (285 variants, box spent). Render 0x6A45A0 41.51; resume from render_d.cpp (41.05, frame 0xFC vs 0xF8). Draw_Placement_Cursor 0x473F20 70.18 (cursor_c6.cpp; cursor_c7_promoted.cpp has frame 0x20). 0x6A66B0 53.12, 0x6AADD0 30.41 (a budget issue). cell_object_lp.cpp may unlock Is_Clear_To_Build 0x4718B0 (scored only).

## Scout688 (2026-11-04, closed; 0 B; drafts build/class-work/Scout688/w/keep/, overlay ov/shared, NOTES.md; Scout690 continues)
- OWNER DECISION: slot 302 takes `Cell const &` (TibSun Overrun_Square) as a rename round covering 0x41B530, 0x705160 and their callers, replacing the file-local `Overrun_Square_SOM`.
- Ship Start_Of_Move 0x6785C0 86.62, shape 97.89 (o11_ship_8662_k4.cpp). Drive 0x4A2670 86.00, shape 97.50 (dr1_drive_8600_k4.cpp). 8,373 B each; Drive's bound needs an independent check. Frame 0x4C and call sequence match. Both carry 4 phase probes, SOMNOP free sites (k>=3 after site 5) and RA2_SHIP_SOM scoping: not landable yet. Provisional: `here`, `under_bridge`, `Adjacent_Coord_SOM`, free `operator+(CoordStruct, Point2D)`. Draw_Matrix 0x676010 / 0x4A0050 not reached.

## Scout689 (2026-11-04, closed; 336 new B: Draw_Render_Hooks 0x6A92A0, plus Coord_To_Pixel 0x6A29D0 re-sourced with no new bytes; drafts build/class-work/Scout689/w/keep/; Tactical budget family PARKED for now)
- OWNER DECISION: do not adopt the wordy 0x6A2970; it breaks Draw_Placement and Draw_Waypoints. Try a 0x6A6800 or 0x6A2740 form first. Keep the unused Unknown_006A66B0(Point2D const &) declaration (dropping it changes Print_CRCs at +0x638). Slot 65 stays (int,int) for now.
- 0x6A66B0 256 B is exact locally but needs that 0x6A2970 form, 0x6A6640's `Point2D chosen`, and a merge of population-2821 into Tactical (rows_r3_draft.txt). Draw_Overlays 0x6A7350 94.41 (overlays_n1c_9441.cpp). Draw_Radial_Indicators 0x6AC420 77.41. Draw_Tiles(Cell) 0x6A8560 59.62, (Rect) 0x6A7BA0 50.11. Flag_Cell 0x6AADD0 30.41. Is_Clear_To_Build retry failed (55.22 with cell_object_lp). Draw_Objects 0x6A93F0, Render, 0x473F20 not reached.

## Scout690 (2026-11-04, closed; 16,746 B: Ship Start_Of_Move 0x6785C0, Drive Start_Of_Move 0x4A2670, with the slot 302 Overrun_Square rename; build/class-work/Scout690/NOTES.md; Scout692 continues with Draw_Matrix)
- OWNER DECISION: `here`, `next`, `unit`, `found` with `bool &result = found`, the scoped `center`, phase locals `overlay`, `ttype`, `dist`, `Adjacent_Coord_SOM` with free operator+(CoordStruct, Point2D), `Length_YZX`/`Distance_YZX` and the `(CellClass const *)` cast stay as landed. All live source; no natural reason known for the YZX forms.
- Draw_Matrix 0x676010 (97.08) and Drive 0x4A0050 (83.48) not reached.

## Scout692 (2026-11-04, closed; 0 B; drafts build/class-work/Scout692/w/keep/, NOTES.md; Scout693 continues)
- Ship Draw_Matrix 0x676010 95.91, shape 100, zero non-frame lines (f3.cpp, srE.cpp, hs.cpp, overlay ov_f3/; frame groups B0/E0, 110/170, 1D0/200 swapped). Scout592's 97.08 needed unlanded helper rewrites. It would need a Matrix3D unit guard with no user copy ctor, a rename to by-value Get_Slope_Matrix, and Slope_Ratio's unevidenced srE form. Drive 0x4A0050 not ported.
- Jumpjet Move_To 0x52F600 94.10, loose 99.43 (j10.cpp + jdef.cpp; X reload order). Tunnel 0x6F0730 96.31. Rocket Move_To 0x63EA80 60.00 (202 B body). Mech 0x5919A0 76.73. Not reached: Rocket 0x63DE10, Tunnel Stop_Moving 0x6EFDE0, Walk 0x71E220. Ship and Drive have no other gaps; Hover has none.

## Scout691 (2026-11-04, closed; 4,312 B: Draw_Post_Render 0x6C2C40, Draw_Pre_Render 0x6C3B30, 0x6C3A90 re-sourced as Draw_Single_Selection_Bracket; drafts build/class-work/Scout691/w/keep/; Scout694 continues)
- OWNER DECISION: `Flag_380`, `Is_Selected`, `Talk_Owner`, the named refs `lepton` and `position`, and the mixed halving forms stay as landed. RA2_COORD_DIVIDE_SOURCE goes only with the health bar row.
- Take_Damage slot 86 0x6CDC40 (4,412 B + 20 B table) 93.44, shape 99.53 (td6_9344.cpp). Health bar slot 248 0x6C3F00 49.73 (hb_hd1_4973.cpp; about 8 real sites, frame 0x40 vs 0x48). LdPrgMgr 0x535BF0 63.76 (ld_h5_6376.cpp; frame 0x1180 vs 0x1184). Tunnel depth 0x6CFB60 80.77, box spent. Not attempted: NoInit 0x6C1F10, slot 186 0x6CD340, PlanMgr 0x6130B0, IPX 0x525F60, Radar 0x630B70, Read_PCX 0x60D110.

## Scout693 (2026-11-04, closed; Jumpjet Move_To 0x52F600 852 B; drafts build/class-work/Scout693/w/keep/)
- Mech 0x5919A0 79.76, shape 98.35 (e1.cpp + mdef5.cpp; 14 of 138 bad; not a T problem). Walk 0x71E220 55.78 (ours `and esp,-8` over frame 0x6C, original `sub esp,0x38`). Rocket Move_To 0x63EA80 59.32, Rocket 0x63DE10 88.89 (removing `inline` from the Process row drops Process to 98.47), Tunnel Stop_Moving 0x6EFDE0 83.47 at body_bytes 544. Drafts carry `T *&type`, `Adjacent_Tube`, `Flat`, `Distance2`: none landed.

## Scout694 (2026-11-04, closed; 3,021 B from the promotion queue: UnitClass Draw_Shape 0x7005B0 from codex3's 99.70, Trackball 0x622690 from codex3's 91.55; drafts build/class-work/Scout694/w/keep/; Scout696 continues the queue)
- OWNER DECISION: `Unit_Negated_Vector_007005b0`, the SHAPE_FILE_EMPTY_RECT define, `Trackball_Length_00622690`, `Quat_Vector_Length` and the file-local operator- stay as landed. The `@ref ??0Vector3@@QAE@MMM@Z=00437690` binding stays; it was a caller hypothesis of codex3's. Landing messages used `codex3 r288 draft` as a credit label though r288 is a separate round.
- Take_Damage 0x6CDC40 93.44 parked (about 50 variants; the case-1 reload at 0xB2F is unique in the exe). Slot 186 0x6CD340 81.96 parked. Unlimbo 0x43D3A0 97.61 (ul_c2_9764.cpp root). Health bar 0x6C3F00 and NoInit 0x6C1F10 not attempted.

## Scout695 (2026-11-04, closed; BuildingClass AI 0x43C930 2,661 B from codex2's 99.60 draft; drafts build/class-work/Scout695/w/keep/; Scout697 continues; real Building state is in codex2's building/NOTES.md and RESUME.md on the PC)
- OWNER DECISION: RA2_COORD_TPOINT3D for the Building population is allowed only if every accepted row, Docking and Deconstruction included, proves exact at a full check; try it as its own step.
- Missile 0x448400 97.75 (codex2 proof 99.77; mm.cpp; two ties). Draw_It 0x43A5E0 97.70, shape 100 (di.cpp; `cell`/`shape` slots swapped, a counterexample to reference-count ordering). Cloak 0x44FB50 98.30 (needs h3/ and a rebuilt Do_Destruction). Editor_Draw_It 0x43A380 96.30. Draw_Extras 0x43ABD0 87.48. Take_Damage 0x43EE70 81.73. Not attempted: Mark 0x43BFC0, Captured 0x444660, Mission_Attack 0x446920, Barrel 0x43B7E0, 0x43DC50.

## Scout696 (2026-11-04, closed; Buddy list refresh 0x755180 2,892 B from codex4's draft; drafts build/class-work/Scout696/w/keep/, LIST.md; Scout698 continues)
- Dropship_Screen 0x4A6B90 (10,797 B) 99.83 (ds_c4_9983.cpp; 3 sum orders at 0x1171, 0x11C6, 0x2444 and a reload at 0x1508; carries `Read_Dropship_Clock`; all direct scores 88.26). peer 0x74E5E0 99.85 (needs a timer Value form in cd_timer.hpp). OnUserList 0x760C00 99.73. Session ctor 0x66E380 99.72. HouseAI_Building 0x4E9660 99.42. UnVQ2_TRANS 0x77D940 99.16. Locale 0x751190 98.20. Get_Obstacle 0x4BBAF0 97.38. ServerWait 0x751C30 96.21. Build_Schemes 0x604540 95.82.

## Scout697 (2026-11-04, closed; 4,198 B: Draw_It 0x43A5E0, Draw_Extras 0x43ABD0, both codex2 drafts; drafts build/class-work/Scout697/w/keep/; Scout699 continues)
- OWNER DECISION: `Barrel_Side_0043abd0` and `unknown_453900` returning Matrix3D under RA2_BUILDING_BARREL_MATRIX_VALUE stay as landed. RA2_COORD_TPOINT3D stays out of the Building population: check_plans gave 206/208 (Deconstruction 99.79, one local away; Docking 97.53, X-sum tie at 0x131 and 0x177, not T phase).
- Barrel 0x43B7E0 97.97. Editor_Draw_It 96.10. Missile 0x448400 full 99.77. Take_Damage 0x43EE70 81.11. Cloak 98.31 blocked on Docking. Not reached: Mission_Attack 0x446920, Captured 0x444660, Mark 0x43BFC0.

## codex3 r289-v3 (2026-11-04; Queue_AI_Multiplayer 0x623B00 3,388 B)
- OWNER DECISION: zero-credit takeover of the 1-byte row 0x624840 from population-3817 as the compiler's `_$E79` is approved, the same class as Scout679's and Scout680's atexit moves.
- Queue_AI 0x623770 can land next: it was waiting on this row.
- OWNER DECISION (r290): zero-credit takeover of Next 0x62E9E0 from population-42 as QueueClass<EventClass,128>::Next, and QAM file-static under RA2_QUEUE_STATICS, are approved; same ABI and mangling, all accepted Queue rows exact, full build exact.

## Scout699 (2026-11-04, closed; IonBlastClass Draw_It 0x521CE0 711+9 B, undrafted TibSun twin; drafts build/class-work/Scout699/w/keep/; Scout700 continues)
- OWNER DECISION: `short *pixel = dptr;` stays as landed (a code-free local that splits web weight). 0x43DC50 is not a row: it is interior to Unlimbo 0x43D3A0.
- Barrel 0x43B7E0 99.13 (bar_9913.cpp, overlay hb/ with signed Facing union, no probe or check yet; file-local XY_0043b7e0 needs a ruling). One_Time 0x521A90 93.29 (ot3.cpp shape 99.36). Captured 0x444660 78.23 (cap.cpp; `#pragma auto_inline(off)` must go). Mission_Attack 0x446920 81.79 (blocked on FP spills). Mark 0x43BFC0 72.36. Take_Damage 0x43EE70 81.11.

## Scout698 (2026-11-04, closed; 0 B; drafts build/class-work/Scout698/w/keep/, NOTES.md; Scout701 has one more attempt)
- Dropship 0x4A6B90 99.83 (ds_n10_9990_probes.cpp 99.90 with dead locals, not landable). The three sum sites move only with statements that produce a CSE or IV temp, like a hidden counter. peer 99.85, OnUserList 99.73, Session ctor 99.72 unchanged.

## Scout700 (2026-11-04, closed; 1,483 B: Cell_Render_Rect 0x4752B0, Draw_Shadow_Cast 0x4755D0, Draw_It 0x475680, Occupy_Down 0x473B30; drafts build/class-work/Scout700/w/keep/, LIST.md 511 rows; Scout702 continues)
- OWNER DECISION: the guarded CELL_DECLARE_DRAW_IT block and Fetch_Icon's `count` locals stay as landed. 0x474260 Draw_Shroud_Or_Fog_Shape looks like original inline asm (ebp frame, hand loops comparing a global dword; inferred): treat it as a handwritten-ledger candidate, do not draft it.
- 0x6A89B0 is the tail of 0x6A88A0. 0x6C9DF0 and 0x6A88A0 have pass-5 sizes far too small. Clear_Icon 0x4767A0 79.05. Laser_Zap 0x6C9DF0 71.54. Grant 0x69CCF0 89.32. Reduce_Tiberium 0x475DB0 76.24. 0x6A88A0 55.76.

## Scout702 (2026-11-04, closed; 1,796 B: On_Bridge_Collapse 0x47C930, Draw_Overlay 0x4749C0; drafts build/class-work/Scout702/w/; Scout703 continues)
- OWNER DECISION: RA2_IS_MOVING_HERE_VALUE, RA2_SHIP_MOVE_TO_VALUE across the Cell population, CellClass +0x68 as a real `Rect unknown_68` (TibSun LastBridgeDrawRect), the file-local externs in 0x4749C0, and `is_foot`, `flat` stay. Reconcile 0xA52EB0 with unknown_globals.hpp later.
- Kill_Illegal_Occupiers 0x47CC10 84.64. Redraw_Veins 0x47A7A0 83.60. Spread_Tiberium 0x478A40 85.84 (one X-sum tie). Techno 0x6D65B0 87.83, shape 100 (frame 8 B short). Laser_Zap 71.54. Draw_Placement_Cursor 67.85. Make_Closest 0x622290 53.96. Not reached: Radar 0x634310, Team 0x6BE010, 0x5689D0, 0x6D0DC0.

## Scout703 (2026-11-04, closed; Spread_Tiberium 0x478A40 352 B; drafts build/class-work/Scout703/w/keep/; Scout704 continues)
- OWNER DECISION: the four plain named locals in 0x478A40 (`overlay`, `count`, `facing`, `amount`) stay: used locals, T phase demands the count.
- Can_Enter_Cell 0x703040 (2,952 B) 94.91, shape 99.32 (sy3.cpp, overlay h/shared/techno.hpp; a vptr reload at 0x9EF; named index flips this/cell). RTacticalClass::Action 0x62FE30 (1,225+7 B with a byte table) 96.92 (rg5.cpp). Render_Radar 0x633210 43.42. Radar 0x634310 is not a row (inside 0x6340F0). Techno 0x6D0DC0 has no twin; its body runs across false row 0x6D10BD. Undrafted: Fire_At 0x6CA890 (6,019 B), Unit slot 310 0x6FF690, Tunnel 0x6FAA30.

## Scout701 (2026-11-04, closed; UnVQ2_C0_4x4_TRANS 0x77D940 1,101 B from codex1's r1039 draft, as a new one-row population; Dropship PARKED)
- OWNER DECISION: the one-row population stands; moving 0x77E1A0/0x77E5B0 into that unit is a later step if the TU split is confirmed.
- Dropship 0x4A6B90 parked at 99.83 (Scout701 w/d3.cpp, w/s2.cpp; 99.90 only with dead constants). Resume: explain why the original caches screen_origin.Y in edi and zero in ebx at 0x2096. TibSun does have dropship.cpp. `Read_Dropship_Clock` has no natural reason. Session 99.72, Locale 98.20, Get_Obstacle 97.38, Build_Schemes 95.82, ServerWait 96.21 parked.

## Scout704 (2026-11-04, closed; Can_Enter_Cell 0x703040 2,952 B; drafts build/class-work/Scout704/w/keep/; Scout706 continues)
- OWNER DECISION: `(otype = occupant->Class_Of())->unknown_1fd`, `int &tech = techface` and `contact` stay as landed: live source, each needed for exactness.
- RTactical Action 0x62FE30 97.18 (ra1_9718.cpp). Techno Fire_At 0x6CA890 (6,019 B) 70.37, frame 0xA4 (fb3_7037_frame.cpp). Unit slot 310 0x6FF690, Tunnel 0x6FAA30, slot 28 0x703BD0 undrafted.

## Scout705 (2026-11-04, closed; Update_Present_Super_Weapons 0x4F4B20 646 B; drafts build/class-work/Scout705/w/keep/; Scout707 continues)
- OWNER DECISION: the `on` and `alive` locals stay as landed (used, emit no extra code, not in TibSun). Rename unknown_func_4f4b20 pending.
- AI_Build_Defense 0x4F1190 (3,264 B to 0x4F1E50, TibSun house.cpp:7840) undrafted; listing w/keep/abd.dis. Team GatherAtEnemy 0x6BDAA0 98.70, shape 100 (gx1.cpp; three frame lines). Expert_AI 0x4E8990 77.89 (expert_7789.cpp; constant webs). Random_Cell_In_Zone 0x4ECA50 52.70, jump table unbound. GScreen Get_Input 0x4E09D0 82.81. AI_Building 99.42, Mech 79.76 unchanged.
- 0x4EEE10 and 0x4EF303 are interior to 0x4EECB0 (2,276 B, RA2-only, no twin). Team, Script, Trigger, Tag and TaskForce have no other unrecovered rows in the ranges checked, apart from Team 0x6BE010.

## Scout706 (2026-11-04, closed; 0 B; drafts build/class-work/Scout706/w/keep/, NOTES.md; Scout708 continues)
- Techno Fire_At 0x6CA890 86.42, frame right, 18 hunks (gk_a_best_score.cpp; no overlay; ga_a_probe_9127.cpp is a probe). Left: sound site `TypeList::Pick` ebx contest, scheduling ties at 0x231, 0x41e, 0x5cf, 0x6ab, 0x11ea, CDTimer temp [a4] vs [30]. The bullet.hpp Set_Yaw/Set_Pitch variant is not clean, so the file-local helpers stay and are flagged. Action 0x62FE30 97.18 unchanged.

## Scout707 (2026-11-04, closed; AI_Build_Defense 0x4F1190 3,264 B and the Update_Present_Super_Weapons rename; drafts build/class-work/Scout707/w/keep/; Scout709 continues)
- OWNER DECISION: `int const &lowest = best_value` and both `dy` locals stay as landed. `Dir_To_4` is TibSun's As_Dir4 and can move to facing.hpp. Row 0x4F2330 is a seed FUN_ that could be taken over at zero credit.
- Team 0x6BDAA0 98.70. Expert_AI 78.95. Get_Input 82.81. Bounce AI 0x4370E0 93.05 (ba_9305.cpp; frame 4 B short, one add destination). Next unclaimed: Particle 0x608BB0, 0x609540.

## Scout708 (2026-11-04, closed; Unit What_Action 0x703BD0 1,559 B; drafts build/class-work/Scout708/w/keep/; Scout710 continues)
- OWNER DECISION: `Land_Type_00703bd0` and `UnknownBuildingView_00703bd0` stay as landed.
- Fire_At 0x6CA890 83.80, shape 99.83, 8 hunks (g5_8380_h8.cpp); best raw 87.06 (g2_8706_h15.cpp). Building and bolt arms evict `weapon` alternately. @refs unaudited. Desired_Load_Dir 0x704730 78.93. Tunnel 0x6FAA30 45.37. Mission_Attack: the float Length mechanism does not explain its spills (80.68 at most; temps, not a struct). Undrafted: 0x6FF690, 0x701580 (4,128 B), 0x7025A0 (2,496 B).

## Scout710 (2026-11-04, closed; 0 B; drafts build/class-work/Scout710/w/keep/, NOTES.md)
- Unit Draw_It slot 67 0x700E70 (1,328 B) 92.87, shape 100 (u67_a_9287.cpp; frame 0x48 vs 0x40, radians and Move_Coord result share one slot). Do_MISSION_HARVEST slot 131 0x7025A0 (2,496 B) 91.66 (h1c_9166.cpp, overlay h/; 5 hunks; `FootClass::unknown_4cb830` takes bool arg2 if it lands; recheck slot 87 0x7072D0 too). Desired_Load_Dir 78.93. Tunnel 45.37, Fire_At 87.06 parked. 0x707F60 to 0x709790 look like one function of about 6 KB with a broken bound.
- Owner tool note: accept.sh now stops on any `"error"` in the accept log. Before this, a composite pass could succeed while a later pass refused a new row (codex1 r1077, commits 71c082a8e and e5841bccd landed no bytes).

## Scout709 (2026-11-04, closed; Particle Smoke AI 0x608BB0 1,601 B; drafts build/class-work/Scout709/w/keep/; Scout712 continues)
- OWNER DECISION: `Bridge_Height` and `double gravity` stay as landed. If Bounce lands, move Slope_Vector and Bridge_Height to a shared header rather than duplicating them.
- Bounce AI 0x4370E0 99.55, shape 100 (ba3_9955.cpp; one line `fld [esi+0x2c]` vs `fld [ebx+8]`). Spark particle 0x609540 66.45. Spark system AI 0x60B670 86.56. SpotLight Draw 0x5DDB90 60.23 (ld1.cpp).

## Scout711 (2026-11-04, closed; 2,882 B over four rounds: DirectDraw setup and fade 0x4955D0-0x495C90, OwnerDraw sidebar placement rows; drafts build/class-work/Scout711/w/keep/; Scout713 continues)
- OWNER DECISION: DIRECTDRAW_DECLARE_MODE_METHODS, RA2_PALETTE_CONSTRUCTORS, shared/ddraw_result.hpp, shared/owner_draw_sidebar.hpp, `area2`, `int left`, `box` and the fade's `PaletteClass original; memcpy` stay as landed. Names Fade_Palette_To, Get_Video_Memory and Sidebar_* are hypotheses.
- Preferred Type classes have no undrafted rows of 200 B or more. 0x5E8C50 74.32. RadSite 0x637A80 96.85, shape 100 (u637a80.cpp; frame slots). 0x5CB170 29.96. Next: EnumChild callback 0x5E9BB0 (real body 845 B, needs body_bytes and bound_evidence; calls 0x5E9410, 1,938 B). False rows: 0x68FEE0, 0x5E9C9C; 0x5ECF40 and 0x663FE0 look like mid-body pieces.

## Scout712 (2026-11-04, closed; 0 B; drafts build/class-work/Scout712/w/keep/, gr.py greedy toggle search)
- Barrel 0x43B7E0 99.42 (bar_9942_z.cpp; 2 lines at 0x1C3). Bounce 99.55. Team 0x6BDAA0 98.76. SpotLight 0x5DDB90 66.98, frame right. Spark rows, Missile, Unit Draw_It unchanged. These are spent register and slot ties; revisit only with a new mechanism.

## Scout713 (2026-11-05, closed; 1,308 B: EnumChild callback 0x5E9BB0, 0x5E8C50; drafts build/class-work/Scout713/w/keep/; Scout716 continues)
- OWNER DECISION: `Is_Placed_Control`, `Adjust_Control` and `Is_Lobby_Control` stay as landed. Bucket_Index binds by @ref to 0x602020, where the accepted row is named Key_Hash: reconcile later.
- 0x5E9410 (1,938 B) 99.79, shape 100 (e9410_9979.cpp; one compare operand order at +0x765).

## Scout714 (2026-11-05, closed; Do_MISSION_UNLOAD 0x701580 4,124 B; drafts build/class-work/Scout714/w/; Scout715 continues)
- OWNER DECISION: `current_dir`, `delay`, the early `attempt`, `CoordStruct &o`, and the duplicated `return Control()->Normal_Delay()...` stay as landed.
- Plan_Route 0x707F60 (6,185+7 B) 90.43 with 6 dead phase probes (tk_6.cpp, not landable). Draw_Voxel 0x6FF690 has no local draft.
- Host note: Wine wedged and the Mac hung on 2026-11-05 about 00:35Z; a reboot cleared it. accept.sh had been choosing local Wine for any plan containing the separate_units key, even when false: fixed.

## Scout716 (2026-11-05, closed; 1,244 B: Subclass_Dialog 0x5ECC90, Set_Paint_Disabled 0x5ECF40; drafts build/class-work/Scout716/w/keep/; Scout717 continues)
- OWNER DECISION: RA2_WOL_DICTIONARY_WLIB_STATEMENTS, `Set_Wide_Text_600510` and removing Get_Minimum_Size stay. campaign_score.hpp declares 0x5ECF40 void, the real return is BOOL: fix when next touched.
- InitializeCtrl 0x5ED180 (2,462+2 B) 93.66 clean, shape 100 with probes (ed180_t1_probe100.cpp, overlay keep/h2/, OwnerDraw_unknown_5de880_true_order.cpp; about 8 dead locals' worth of budget before the third Add). 0x5E9410 99.79 spent. RadSite 0x637A80 97.25, 0x637DC0 96.90 (one slot tie). 0x6014E0 52 (needs inline operator=).

## Scout715 (2026-11-05, closed; 0 B; drafts build/class-work/Scout715/w/keep/; Scout718 continues)
- Plan_Route 0x707F60 parked: 99.90 with probes (best_9990_probes.cpp), clean about 91.8 (cl.cpp). The legs.Add and unknown_478.Add mix by site has no natural explanation; the Count-store order at 0x600 and 0x15FF never appeared in 400+ variants.
- Super Place 0x69D850 (4,388 B) 78.46, shape 96.91 (place_vd_7846.cpp, overlay h5/; `Chrono_Place_Anim`, `Above_Five` are hypotheses; com_ptr.hpp Assign_Held unprobed).

## Scout717 and Scout718 (2026-11-05; Scout717 InitializeCtrl 0x5ED180, WolDictionary Add 0x6014E0, Remove 0x601C50; Scout718 Infantry Assign_Destination 0x501CE0 from a codex3 draft)
- OWNER DECISION: RA2_CELL_FROM_COORD_AS_CELL and RA2_INFANTRY_COMIP_PERSIST stay in row 0x4FF450. `As_Unit` and `is_jumpjet` stay. `operator&` in infantry_locomotion_ptr.hpp stays. Try the comip levels in shared com_ptr.hpp on Super Place next.
- Techno Get_Z_Adjust 0x6CFEA0 80.37 (z1.cpp; twin techno.cpp:5687; three rock arms merge in ours). JumpJet_To_Walk 0x508AB0 69.35. 0x5025C0 not attempted.

## Scout717 (2026-11-05, closed; 4,274 B: InitializeCtrl 0x5ED180, Add 0x6014E0, Remove 0x601C50, 0x5E1640; drafts build/class-work/Scout717/w/keep/; Scout720 continues)
- UnknownControlIndex::Shrink duplicates WolDictionary::Shrink_Table over the same object, bound by @ref: reconcile later, with the 0x6027E0 forwarding specialization. Pending rename: 0x5ED180 to InitializeCtrl. `Is_Listed_Kind_5e8590` is a hypothesis.
- Draw_Dialog_Back 0x5FEE70 84.63 (fee70_8463.cpp, overlay keep/h5; `Find_Record` is flagged). 0x5E8130 about 41 (e8130_m9.cpp). 0x5FE9B0 22.54. Not reached: 0x5FEB60, 0x5EB490, 0x5EBA80, 0x5E7EB0. Predicate 0x5E0DA0 looks like the same takeover for the Control_* rows.

## Scout719 (2026-11-05, closed; 0 B; drafts build/class-work/Scout719/w/keep/; Super Place PARKED after two lanes)
- Super Place 0x69D850 78.46. Comip levels did not help (77.09). Two 12-byte temps must stay unshared at depth 1 yet out of line, which budget does not explain; `Chrono_Place_Anim` looks suspect.
- Infantry Tunnel_AI 0x5025C0 60.32 (tunnel_ai_t4_6032.cpp; twin infantry.cpp:1255; Move_Coord must leave row 0x504BC0; Tube_* helpers need a ruling). Tunnel Stop_Moving 0x6EFDE0 85.71, shape 95.80, frame only.

## Scout720 (2026-11-05, closed; 3,749 B: EnumChild callback 0x5E4780, Draw_Dialog_Back 0x5FEE70; drafts build/class-work/Scout720/w/keep/; Scout722 continues)
- OWNER DECISION: `Kind_Of`, `Is_Option_Kind`, `Is_Kind_103`, `Is_Kind_108`, `Is_Rail_ID`, `Is_Owner_Button`, `Is_Free_Record`, `Lookup` and the `found` reference stay as landed. Reconcile the 0x5E0DA0 binding later: Is_Listed_Kind_5e0da0 vs the seed symbol.
- 0x5E7EB0 89.55, shape 100 (frame 8 vs 0xC). 0x5E8720 53.29. 0x5FEB60 55.56. 0x5E8130 31.24 at best (corrected imports: GetTickCount 0x79A0CC, SetTimer 0x79A4D4). 0x5E0DA0 is `bool __fastcall f(int kind)`; defined in the unit it inlines into 0x5E9410, which calls it.

## Scout721 (2026-11-05, closed; Techno line with end markers 0x6D0510 1,151 B; drafts build/class-work/Scout721/w/keep/, overlay keep/h; Scout723 continues)
- OWNER DECISION: `Moved_Rect` and the spelled-out pixel stay as landed. Rename 0x6D0510 and 0x6D0990 and make arg8/arg9 bool when convenient (needs FootClass slot 243 too). Do not land the stage.hpp overlay until the Anim and Factory 0x423F60 sites are checked.
- Draw_Action_Line 0x4CAB90 82.25, shape 100 (frame slots). Predict_Target_Coord 0x6D65B0 87.83, shape 100 (frame 8 B short). Rock slot 223 0x6D5F40 64.37, shape 99.77 (frame 8 short). 0x6D0990 46.96 with probes. NoInit 0x6C1F10 65.78 clean. Not reached: 0x6CA340 96.08, Scatter 0x504120 94.14, 0x6C89C0 90.31.

## Scout722 (2026-11-05, closed; ODRemoveFromDict 0x5EDD30 548 B; drafts build/class-work/Scout722/w/keep/; Scout724 continues)
- 0x5EB490 and 0x5EBA80 are not rows: both are interior to 0x5EAD20, a 7,648 B window procedure (likely ComboDropWinCtrlProc). 0x5FFB00 Default_Dialog_Proc (1,488 B, ownrdraw.cpp:6764) 66.88 clean (ffb00_ffc_6688.cpp with invented helpers). 0x5E7EB0 89.55. 0x5E8720 53.29.
- 0x5EDD30 compiles only in the joined unit (uses declarations from row 0x5EDB20's file).

## Scout724 (2026-11-05, closed; 0 B; drafts build/class-work/Scout724/w/keep/; Scout725 continues)
- ComboDrop 0x5EAD20: body 7,636 B + 12 pad to 0x5ECAF4 (independent decode, no tables); twin TibSun ComboDropWinCtrlProc; bogus rows 0x5EB490, 0x5EBA80 retire through the plan. 64.02, shape 96.80 (ead20_e3_6402.cpp, overlay keep/h, keep/rd35.cpp). Frame 0x380 vs 0x37C, zero webs, blend loop registers. Its teardown is row 0x5EDD30 inlined, so 0x601950 and 0x601C50 must become inline, landing as one round with ComboDrop; rd35 is 89.02 and needs about one more statement of IL.

## Scout723 (2026-11-05, closed; 906 B: aim point 0x6D65B0, rad beams 0x6CA340; drafts build/class-work/Scout723/w/keep/; Scout726 continues)
- OWNER DECISION: file-local Move_Coord in 0x6D65B0 and `Cell offset(ox, spread); offset.Y *= y;` in 0x6CA340 stay as landed (flagged, no dead stores).
- Draw_Action_Line 0x4CAB90 92.49, shape 100 (dal_j0_9249.cpp; one slot flip; `Clipped_Fill` would be new). Draw_Voxel 0x6FF690 52.54 (dv_h_5091_shape8537.cpp; cache lookup must inline at the first site). Rock 0x6D5F40 64.37. Area_Modify 96.38 flat.

## Scout725 (2026-11-05, closed; 0 B; drafts build/class-work/Scout725/w/keep/; Scout727 continues)
- ComboDrop 0x5EAD20 87.20, shape 99.12, frame right, calls 165/165 (e10_8743.cpp, overlay w/keep/h, rows r601950s, r601c50i, rd35, r5ded60n). Left: row loop 0x6EE-0x977 register roles, arm 1 Shrink, frame order above 0xAC, case 0x7E8. No check_plans yet; new Set_Wide_Text and remove_node forms unchecked in 0x5DEE00, 0x5ED180, 0x5ECC90, 0x5ECF40, 0x6005C0. `Get_Item_Text`, `UnknownScrollInfo`, `UnknownListItem` are invented names.
- Send_Statistics_Packet 0x698D00 (5,136 B) landed by Scout726 r1.

## Scout726 (2026-11-05, closed; 5,136 B: Send_Statistics_Packet 0x698D00; drafts build/class-work/Scout726/w/keep/; Scout728 continues)
- OWNER DECISION: file-local TRACKER and UNIT_TOTALS macros, the UnitTrackerClass cast of HouseClass's UnknownHouseTracker members, `int count`, `char digit` and the RA2_STATS_UNIT guard stay as landed. Unknown_00698D00 keeps its symbol until a rename.
- ScoreClass::Presentation 0x663FE0 (7,782 B) landed by Scout728 r1.
- build/class-work/Scout726/LIST.md covers 172 rows; gaps.py lists accepted-coverage gaps, which find real functions behind short rows. Undrafted: Fly 0x4BCD50 and 0x4BE720, Wait_For_Players 0x624C10, Queue 0x629290, Tactical 0x6A93F0, Cell 0x47E2C0, Fogged 0x4C1010, WOL 0x759E20, 0x7540A0, 0x7459A0, Planning 0x6182F0, 0x618C00.

## Scout728 (2026-11-05, closed; 7,782 B: ScoreClass::Presentation 0x663FE0; drafts build/class-work/Scout728/w/keep/; Scout729 continues)
- OWNER DECISION: Wait_For_Print as a plain inline ScoreClass member (hypothesis; TibSun has __forceinline), file-local ScoreSoundClass ctor and dtor, Open_Named, Fetch_Text and macros PRINT, WAIT, LOAD, WIPE, FETCH stay as landed. Rows 0x668280 and 0x6682B0 stay in their population.
- Wait_For_Players 0x624C10 (5,519 B) landed by Scout729 r1.

## Scout727 (2026-11-05, closed; 0 B; drafts build/class-work/Scout727/w/keep/; Scout730 continues)
- OWNER DECISION: RA2_COMBO_DROP_UNIT is acceptable in row 0x5DE660 alongside the RA2_OWNERDRAW_* defines. All new header declarations sit under it because any added declaration moved Print_CRCs.
- ComboDrop 0x5EAD20 (7,636 B) landed by Scout730 r1.

## Scout730 (2026-11-05, closed; 7,636 B: ComboDrop 0x5EAD20, 86.77 to exact in 55 minutes; tools build/class-work/Scout730/fm.py, em.py, rz.py)
- OWNER DECISION: function-scope `Rect fill;`, non-escaped `Rect row` with block-local `Rect outer` in the scrollbar arm, `if (master ? master->alternate_cd : false)` in the first fill arm only, `case 0xf` last in the source, text_rect order top, left, right, bottom, and invented names Get_Item_Text, UnknownScrollInfo, UnknownListItem stay as landed. The inline budget here is tight: two extra dead locals moved a Bucket_Index site.
- Default_Dialog_Proc 0x5FFB00 scores 62.23 on top of r1 rows (ff.sh; below its recorded 66.88; inline-budget row). 0x5E5150 not reached.

## Scout729 (2026-11-05, closed; 5,568 B: Wait_For_Players 0x624C10, Delete 0x62EA00; Scout732 continues)
- OWNER DECISION: Wait_For_Players keeps its mixed names on the exit path (unknown_game_mode_a3d298 for Session.Type, unknown_session_a3d298.unknown_2ec[0x340] and [0x341]) and one-name enum MAX_EVENTS. No dead code. A rename that merges those names breaks the row; the natural cause is unknown, so any later real-type sweep must find an equivalent location count. Print_CRCs tolerates one more declaration, not two.
- Fly Movement_AI 0x4BCD50: no draft; field map, RA2 differences and resume steps in build/class-work/Scout729/NOTES.md. Refrozen duplicate at build/class-work/Scout729/x/r1_refreeze_not_landed.
- Reference table: 19 population files map __imp__PostMessageA@16 to 0x79A4A0, SendMessageA's slot; 281 others have the correct 0x79A470. Wait_For_Players overrides it with a local @ref. Deferred: correct the 19 rows and the source of the value, under a full build.

## Scout731 (2026-11-05, closed; 0 B; drafts and NOTES.md in build/class-work/Scout731/w/keep/; generic harness rows.py, s.py, mk.py, cmpd.py, fa.py, fm.py)
- These rows look spent without a new mechanism; none beat its previous best. Dropship 0x4A6B90 99.83 (ds_c4.cpp): 3 sum orders and reload 0x1508, no frame fault. Plan_Route 0x707F60 91.78 clean, 99.90 with probes (pr_cl.cpp, pr_b.cpp): scheduler refuses to hoist the Vector load over the Count store at 0x600 and 0x15FF. Bounce 0x4370E0 99.55 (bn.cpp): only the gravity statements flip ebp/ebx; fcomp constant address at 0x589 differs, check @refs. Barrel 0x43B7E0 99.42 (bar.cpp): first return looks like a tail-duplicated join block. Fire_At 0x6CA890 83.80, shape 99.83 (fg5.cpp): weapon home contest, order velocity 0x40, fire_coord 0x58, pitch 0x64, weapon 0x68.
- OWNER DECISION: 0x5E9410 (1,938 B) stays parked at 99.79. It reaches 100 only with two dead `if (kind == C) { x = x; }` writes (e9_100_selfassign_probe.cpp), which are dead code and are not delivered. It lands if a natural source for those writes is found.

## Scout732 (2026-11-05, closed; 3,783 B: Fly Movement_AI 0x4BCD50; drafts build/class-work/Scout732/w/keep/; Scout734 continues)
- OWNER DECISION: RA2_MAP_EDGE_CELL guarding Unknown_00547F30 in map_view.hpp (Fly unit only), UnknownFlyControlPtr and the unit-local helipad views stay as landed. Release_Held 0x4BFBC0 keeps its `#pragma auto_inline(off)`, though Movement_AI's Release calls expand in place, so that pragma may stand in for a budget effect.
- Fly Nearing_Target 0x4BE720 (1,633 B): 80.50, loose 89.04, shape 98.16, 514/517 (nt_n3c.cpp). Frame 0x34 vs 0x2C: original keeps aim X in ebx, Y and Z in the home at 0x20, with a dead Z store, and its Point2D difference overlaps aim. Next: a scoped inline that owns aim. Rebuild popf.json, drop the landed FLX rows from n.sh and fb.sh, and h/shared is no longer needed.
- Queue 0x629290, WOL 0x7540A0 not reached.

## Scout734 (2026-11-05, closed; 3,048 B: Queue 0x629290, RA2 only; drafts build/class-work/Scout734/w/keep/; Scout735 continues)
- OWNER DECISION: `if (estimate > range && range > 0) found = false;` stays in Queue 0x629290. It folds away late, but the binary computes MAX+3, stores it and ignores it, and only a late-removed compare with two uses keeps that store, so some such construct existed; the exact expression is a guess. This differs from 0x5E9410, where the probe explains no visible output, which stays undelivered. The rule: a dead construct is acceptable only where it accounts for bytes in the target, and it is flagged.
- OWNER DECISION: the 6-entry named-constants enum and the row-local DynamicVectorClass ctor, both Clears and the VectorClass dtor stay. Enum sizes 4 to 7 keep Print_CRCs at 100, 3 fails; any later Queue row placed before Print_CRCs must re-measure.
- WOL 0x7540A0 (3,948 B code + jump table and byte index to 0x755067 + 8 pad, 4,048 B extent): 89.83, loose 90.06, shape 98.65 (a8983.cpp; pop_wa.json, anchor 0x753370; no catalog row, plan needs body_bytes, bound_evidence, symbol). Left: frame slots (105 esp lines), byte store order at 0xC02; target slot map in NOTES.md.
- Nearing_Target, Planning 0x6182F0, 0x618C00, Fogged 0x4C1010 not reached.

## Scout733 (2026-11-05, closed; 1,652 B: WDTMap.ini builder 0x72A880; drafts and tools build/class-work/Scout733/; Scout736 continues)
- OWNER DECISION: file-local To_Point(Point2D by value), block-scoped `reset` cursor and symbol unknown_write_wdtmap_ini_72a880 stay as landed. The VectorCursor virtual-operator form stays guarded until the WDTSel rows confirm it, then unify.
- Read_PCX_File 0x60D110: still 89.68 (Scout611/w/pcx_best_89.68.cpp); a trailing `pic->Unlock()` after the chain tail-duplicates and gives the reload but costs pic its esi (pcx_p2_trailing_unlock.cpp 67.70). No path to 100 seen.
- 0x5CDF00 not attempted (overlay far behind HEAD; needs 0x5CEA30 moved). WOL 0x7459A0 read only: fragile population-4058, new dialog class at vtable 0x7AF94C, about 40 calls. WOL 0x759E20: no twin for the quick-match part. Cell 0x47E2C0 not read; the span holds three rets.

## Scout735 (2026-11-05, closed; 5,673 B: Wonline_Account_Dialog 0x7540A0, Fly Nearing_Target 0x4BE720; drafts build/class-work/Scout735/w/keep/; Scout737 continues)
- Planning 0x6182F0 (2,230 B): 27.78, shape 71.59 (pd2778.cpp, X='61a6a0=w/keep/tl8571.cpp'). Its repeated blocks are inlined rows Planning_Draw_Dot, Planning_Draw_Midpoint, Planning_Draw_Thick_Line(3); depth-2 Centered_Rect, 0x47D040, 0x47D060, 0x42BCD0 stay out of line. Thick_Line 0x61A6A0 was the blocker; landed by Scout737.
- Fogged Draw_Fogged_Objects 0x4C1010 (2,711 B): 35.19, shape 82.86 (fo3519.cpp, overlay hf/shared/map_cell.hpp). Frame 0x130 vs 0x144. No catalog row; bound needs an independent check. Needs typed members in map_cell.hpp, so a shared-header round with fragile_probe.
- Symbol unknown_4be720 can take its rename later. Lane scratch x/fa/tmp left after a refused removal.

## Scout736 (2026-11-05, closed; 3,443 B over five rounds: WDTSel Show_State 0x72E780, Selection ctor 0x72D560, Hover 0x72E650, Click 0x72E430, GraphicMenu Set_Item_Visible 0x4DE960; WDTSel.cpp complete; NOTES and gaps2.py, hid.py in build/class-work/Scout736/)
- OWNER DECISION: Hover's `true ? TheMap->Get_Territory(x) : rc_ptr<Territory>()` stays. It is dead but accounts for the zeroed construction flag and copy visible in the target (plain form 39.22), so it meets the Scout734 rule.
- OWNER DECISION: single-call inline wrappers Walk_Territories and Hover_At stay; each explains an out-of-line call in the target, the real level may differ. `#pragma auto_inline(off)` on Click stays, in line with 41 existing files; without it Choose_Territory inlines Click (51.50). Show_State's Get_Filename versus ->Name inconsistency is forced by budget. WDT_SELECTION_ACCESSORS and VECTOR_CURSOR_VIRTUAL_OPERATORS (population-3827, 3398) stay guarded; do not unify yet.
- Not tried: MapSizeGameOption::Describe 0x728AB0 (77 B), WDTState() 0x72BEF0 (36 B). Holes of 1 KB or more not named elsewhere are in x/gaps.txt; Scout738 takes the MapClass and WOL ones.

## Scout737 (2026-11-05, closed; 626 B: Thick_Line 0x61A6A0, Dashed 0x61A6F0, Midpoint_Shape 0x61A3C0; NOTES in build/class-work/Scout737/; Scout739 continues)
- OWNER DECISION: `Point2D point(left, top);` in 0x61A3C0 stays: a dead store accounting for two stores visible at 0x61A4FE and 0x61A502. Unit-local inline Point2D::Length in row 0x61A2F0 (`int x = X; int y = Y;`) stays; not reconciled with row 0x47D060.
- Planning_Draw_Techno 0x6182F0 (2,230 B) landed by Scout739 r1. 0x618C00 undrafted, 0x619420 and 0x619870 not rescored, Fogged 0x4C1010 not reached.

## Scout738 (2026-11-05, closed; 0 B; NOTES, drafts and sc.sh, nd.py, sm.py in build/class-work/Scout738/; Scout740 continues)
- OWNER DECISION: Set_Map_Dimensions lands as a single-row unit with a guarded RA2_CELL_FULL_ASSIGN in cell_class.hpp, restating rows 0x548070, 0x54AAB0 and 0x55A550 as inline definitions, if check_plans accepts a one-row unit. Population-3967's rows read unknown_140 and unknown_12c as whole ints, which rules out its implicit op=. `unsigned :32` at +0x144 is a hypothesis; only the size is evidenced.
- MapClass slot 28 Set_Map_Dimensions 0x5484E0 (5,322 B, ret 0x10 at 0x5499B4, 3 nops): 80.25, shape 98.84, 1420/1421 (w/t3.cpp, overlay hB/). Roots: new's result in ebp vs store-and-reload, i and y swapped edi/ebp, last Cell op- computes Y first.
- MapClass Zone_Span 0x54F250 (1,386 B, ret 0xC at 0x54F7B7, 6 nops): 33.54, shape 96.54 (w/z10.cpp, overlay hZ/), mostly register colour. Add_Object overload needs a shared-header round.
- unknown_undo_commit 0x6863E0: 56.38, shape 90.21 (w/u13.cpp). Row 0x6850B0 must expand inline; `mov dl,..; test dl,dl` flag reads unexplained.
- Split by decode, not started: Undo 0x686610 587 B, 0x686863 390 B, 0x6869F0 669 B, 0x685290, 0x685600 (model 0x686C90). WOL 0x742FD0 1,857 B, 0x743720 2,404 B, 0x75F530 1,165 B, 0x75F9C1 196 B, 0x760853 539 B, 0x760B9F 37 B. 0x7469C0 looks like one 7,172 B dialog proc.

## Scout739 (2026-11-05, closed; 4,306 B: Planning_Draw_Techno 0x6182F0, twin 0x618C00; NOTES and tools in build/class-work/Scout739/; Scout741 continues)
- OWNER DECISION: file-local Planning_Owner_House_Color, Planning_House_Pixel and Planning_Reached stay in 0x618C00; replace the two colour helpers through Adjusted_Pixel once PlanningNodeClass::Color 0x6125D0 is solved. `dot = dim;` (a real copy, removal drops to 59.51) and the bare scope block after `else if (!has_nodes) return;` stay.
- PlanningNodeClass::unknown_619420 (1,104 B): 25.00, first shape (w/n1.cpp, key n4): Coord, Member_Owner, Techno_Color must stay out of line. 0x619870 not rescored. Every `int unused` hit in src is an exact row, so those are zero-byte renames (Find_Movie_File, Unknown_006D8F60, Unknown_Select_Art 0x6F2400/20, Dialog_Template_Size, FUN_00681940). Nine by-value fastcall signatures in byvalue_fastcall.txt, callers unchecked.
- Scout737 s.py scored the ALL copy of a row, not the draft; row-key scores there are false, so Techno_Color tc5 was not row-exact.

## Scout740 (2026-11-05, closed; 2,075 B: Build_Deform_Grid 0x685290, Init_Deform_Grid_RMG 0x685600; NOTES and v.py, perm.py, perm2.py, sp.py in build/class-work/Scout740/; Scout742 continues)
- A one-row unit passes check_plans structurally for 0x5484E0, so the Scout738 decision stands. Set_Map_Dimensions 84.61, shape 99.47, 1420/1419 (keep/md1_8461.cpp, overlay hB), past its box. A hoisted `cellcount = 0` in both arms gives the colouring. Left: `cmp esi,edi`, cellcount in [14] not [34], rect web in edi, `mov edx,1` at 0x702 and 0x847. keep/i3_probe.cpp is a probe, never delivered: an escaping `&cells` at the tail gives the first half byte for byte, so `cells = cells_base` is treated as a non-local copy, yet the second loop still hoists [48].
- Undo: Commit 0x6863E0 65.87 (w/cm3.cpp; returns bool while Generate_Hills declares void, so it needs a rename and a source change). Spread 0x686610 58.31 (w/sb1.cpp, w/sp2.cpp), Deform_RMG 0x6869F0 65.88 (w/df1.cpp), both: T keeps pos in memory homes and reloads after the inlined Add. Deform 0x686860 55.91 (w/dv1.cpp). 0x685AC0 (2,325 B) needs a bound and bogus row 0x68633A retired.
- r1 restates inline a function bound to 0x58DA10, which has no catalog row. fragile_probe reads `fail` sporadically even with an empty overlay, likely compile contention.

## Scout741 (2026-11-05, closed; 2,659 B: Planning_Draw_Node 0x619420, 0x619870, Draw_Remembered 0x618090, Fill_Node 0x619BD0; NOTES in build/class-work/Scout741/; Scout743 continues)
- OWNER DECISION: file-local level helpers Planning_No_Coord and Planning_Node_Color stay, on the s739-r2 precedent. Planning_Draw_Remembered's name and cdecl are hypotheses (caller Tactical 0x6A503A unrecovered; __fastcall scores the same). Fill_Marker_Colored and member unknown_619870 are unused declarations to drop in a later header round.
- The __fastcall list-order sweep is closed with zero gain outside Planning: every by-value signature already has the listed order, with accepted callers proving it.
- Fogged 0x4C1010: 50.26, shape 89.77 (w/fo_5026.cpp, overlay hf). Frame 0x12C vs 0x144; ctor 0x41B630 in Coord_Whole must refuse, which took only about 75-80 extra sites. Independent bound still needed.
- Branch_Color 0x6127E0 95.34, Loop_Color 0x6129B0 92.95, 0x616A50 77.83 (one `js` for `jl`), 0x617AF0 90.00, Node_At 0x615D30 28.80 (w/ keys bcl, lc, ua, pu, nd).

## Scout742 (2026-11-05, closed; 5,045 B: all Undo rows, Commit_Deform_Grid 0x685AC0, UndoInfoStruct Resize 0x687030, 0x6871E0; NOTES in build/class-work/Scout742/; Scout744 continues)
- OWNER DECISION: unit macros RA2_UNDO_INFO_POINT, RA2_RECT_MINUS_INLINE, RA2_RECT_POINT_INLINE, RA2_CELL_LAT_BOOL, RA2_MAP_VIEW_56A870 stay in HeaderStatics_diagonal_init_00684d50.cpp. 0x471D10 returns bool only inside this unit; a global rename touches 86 population manifests, so it stays guarded until that row lands. Names Ripple_Deform_Points and Commit_Deform_Grid are TibSun hypotheses.
- Login_Wonline 0x742FD0 (1,857 B): 68.06 clean, shape 92.81 (keep/w742fd0_clean.cpp). Get 0x765E60 is out of line at the first three sites and inline at the last two: a pending-site effect flipping between 20 and 30 sites after the third Get. keep/w742fd0_probe30_DO_NOT_DELIVER.cpp reaches 92.74 with empty sites. 0x743720 (2,404 B) not drafted.
- Bounds corrected: Ripple 587 B, Deform_Cell 393 B, Deform_Cell_RMG 669 B, 0x685AC0 2,327 B. New declarations in vector_elements.hpp broke Print_CRCs and 0x4F1190 AI_Build_Defense, added to fragile_probe.

## Scout743 (2026-11-05, closed; 1,171 B: Planning_Execute 0x614BA0, Planning_Path_Add 0x616350; NOTES in build/class-work/Scout743/; Scout745 continues)
- OWNER DECISION, PROVISIONAL: Is_At 0x611310 carries four chained `CoordStruct const &` aliases that emit nothing, only to make VC6 refuse the row at the 0x2C site and expand it at 0x2A. No natural form reached that size (`here == coord` 84-89; three aliases behave the same; four give 100). This is budget padding, the weakest form in the tree; it landed before the ruling and is exact, so it stays until a natural form is found. Execute and Path_Add depend on it. From this lane on, alias chains, empty sites and purposeless locals are not delivered.
- Planning_Restart_House 0x614850: not a row yet, body lives inline in Execute's file; 100.00 only with one extra /Ob2 site, 37.75 without (w/rh0.cpp).
- Branch_Color 0x6127E0 95.34 and Loop_Color 0x6129B0 92.95: owner is dead by the second instruction, so "live past the read" cannot be a later use. 0x616A50 77.83: the `test` may need a label when the js peephole runs. Planning_Path_Append 0x6165A0 49.28 (w/pp0.cpp). 0x617AF0 90.00, Node_At 0x615D30 28.80 not reached. Color 0x6125D0 is accepted, so dropping its pragma has no bytes.

## Scout744 (2026-11-05, closed; 0 B; drafts and NOTES in build/class-work/Scout744/; Scout746 continues)
- OWNER DECISION: wrappers that group real statements (Fetch_Server_List, Set_Login_Focus, Remember_Login) meet "wrappers with a purpose" even though the combination came from a scan (n7.py); they are level hypotheses, flagged. `~WolRegistryOptions() {}` stays out: its only evidence is budget.
- Login_Wonline 0x742FD0 (1,857 B) landed by Scout746 r1.
- WOL 0x7469C0: code 0x7469C0-0x748491 (6,866 B), last `ret 0x10` at 0x74848F, tables from 0x748494 and 0x7484DC; table end unmeasured. Not drafted. 0x743720 read only; it calls Login_Wonline and repeats the Close_Wonline_Wait sequence.

## Scout746 (2026-11-05, closed; 1,857 B: Login_Wonline 0x742FD0; NOTES in build/class-work/Scout746/; Scout747 continues)
- Join_WOL_Lobby 0x743720 (2,404 B) landed by Scout747 r1.
- 0x75F530, 0x75F9C1, 0x760853, 0x760B9F are one function, not four rows: CChatEventSink::OnChannelJoin, about 5,780 B, between OnChannelCreate and OnChannelLeave, with early `ret 0x10` at 0x75FA82 and 0x75FF8D; last ret still to measure. Earlier split entries are superseded.
- 0x7469C0 extent: 0x7469C0-0x7485C4, 7,172 B, 12 NOP to 0x7485D0; Scout747 holds it.

## Scout745 (2026-11-05, closed; 983 B: Planning_Order_Kind 0x615A80, Techno 0x615480, Hover 0x615C00, Selection_Kind 0x616B40; drafts and NOTES in build/class-work/Scout745/)
- Is_At 0x611310 remains provisional: `here = Coord(); return here == coord;` is row exact but drops Execute to 81.07.
- Parked: 0x617AF0 92.95 (pv3; Help(4) out of line, Help(3) expanded), 0x615DE0 81.32 (ss4), 0x6130B0 77.78 (tk3, ut3; needs a rename), 0x611BD0 67.87 (bd3), 0x614EC0 Add_Order 60.21 (ao9, env.sh; Add 0x61B300 needs spend, takeovers of 0x6159E0, 0x613C50), 0x617900 49.72, 0x617680 39.20. Rect family 0x616070, 0x616140, 0x615D30 at 78.43 (w/f6, cr1): only Coord still expands. Not attempted: 0x614010, 0x617340 (Point2D by value, needs a rename), 0x6165A0.
- Planning_Pick_Drawn is inline in guarded planning.hpp and row 0x616140 is still a hole, as with Restart_House. The h overlay's MouseClass view needs row 0x61A3C0's local class removed. Whether 0x61A8E0 is Is_Point_Within's COMDAT is untested.

## Scout748 (2026-11-05, closed; 0 B; drafts and NOTES in build/class-work/Scout748/; Scout749 continues)
- CChatEventSink::OnChannelJoin 0x75F530: extent to 0x760BC4, 5,780 B; see Scout749.
- OnPrivateGameOptions 0x761C50 has no catalog row and no git history under that name: only its prerequisites landed. Unclaimed with no twin: 0x759370 2,687 B, 0x758750 2,935 B, EBolt 0x4B1900 2,159 B.

## Scout747 (2026-11-05, closed; 9,760 B: Wonline_Main_Dialog 0x7469C0, Join_WOL_Lobby 0x743720, Apply_WOL_Settings 0x73C990; NOTES and lab23.py, lab24.py in build/class-work/Scout747/; Scout750 continues)
- OWNER DECISION: the Apply row's `#include "shared/wol_main.hpp"` and own prototype stay. They are real declarations, added to move the declaration counter past 0x73FEE0's bad window; the alternative is a re-roll of 0x73FEE0. Helper levels Make_Room, Refresh_*_Channels, Update_*_Channels, Request_Channel_Lists, Refresh_Channel_Lists, On_Lobby_Timer, On_Refresh_Lists, Restart_Lobby_Music, Wait_For_Join_Event stay as hypotheses with inline depth as evidence. `case 0x18: return 0;` and `case 0x53e: return 0;` account for a jump table entry and a `je` at +0x100. Unit macros in the first row stay guarded.
- Join symbol stays ?Unknown_00743720@@YIHPAUHWND__@@_N@Z. Queue-form Request_Chat/Game rows failed after Make_Room, so they stay full-body. Next in the unit: 0x7459A0, 0x749B50.

## Scout749 (2026-11-05, closed; 0 B; drafts and NOTES in build/class-work/Scout749/; Scout751 continues on 0x759370, 0x758750)
- OWNER DECISION: OnChannelJoin stays parked. A dead arm reaches 100.00 (keep/lab_c6_8_loc24.cpp) but accounts for no visible bytes, so it fails the rule and is not delivered.
- OnChannelJoin 0x75F530: natural best 94.21, loose 98.77, shape 99.74 (keep/c6_twinshape.cpp, overlay hN; twin TibSun wonline.cpp:3220). Three ties with thresholds: Add sites need about 8 more distinct data keys; the memmove cluster follows function IL size (about 20 more units); `mov ebx`/`mov edi` at 0x11cd cycles with size. So the original carries source that folds away with no bytes. Ruled out: orphan strings, inline-marked definition, Get forms, Add_Sorted, g_UserInfo index loop, swapped Length()+GrowthStep, nested Session accessor. OnUserFlags 0x7647B0 not re-proved.
- EBolt Draw_Bolt 0x4B1900 (2,159 B): 46.87, shape 82.23, 592/590 (keep/ebolt_e14.cpp, key eb, population-2432); mostly frame, size 0x3FC matches. `BoltFrame stack[8]` of CoordStruct arrays gives the vec-ctor loop; target slot map in NOTES.
- Lane scratch w/ and x/ (22 MB) left after a refused removal.

## Scout751 (2026-11-05, closed; 0 B; drafts in build/class-work/Scout751/keep/, NOTES.md, tools xr.py, idiom.py, calls.py; Scout752 continues)
- OWNER DECISION: a single address-taken local such as `bool const &ok = Find_Buddy_Game(...)` is deliverable where it reproduces visible bytes (`xor al,al; test al,al`), flagged. That differs from an alias chain used to reach a size.
- Buddy List main loop 0x759370 (body_bytes 2687, ret 0x759D15, table 0x759D18, index to 0x759DEE): 88.69 with an alias (keep/z1.cpp), 88.19 without (keep/n1.cpp). Left: `xor al,al; test al,al` at 0x75994D, budget window around the second Find's Get.
- Dialog proc 0x758750 (body_bytes 2935, index ends 0x7592C6): 70.62, shape 90.90 (keep/dp2.cpp); better first resume. Row rewrites leave2, clear2, rc2, rg2, svc2 are unproven; they must keep 0x7469C0, 0x743720, 0x73FEE0 exact.

## Scout750 (2026-11-05, closed; 3,173 B: Host_Game 0x7459A0, Wonline_Options_Dialog 0x749B50; NOTES in build/class-work/Scout750/)
- OWNER DECISION: `free_sides` in 0x73CFF0 stays: dead twin statements (TibSun wonline.cpp:947-953) that keep the row over the auto-inline limit and account for the visible call at 0x745B3C. Leave_Game_Channel's duplicate of row 0x744610 without its result, and Wonline_Text, Show_Game_Options, Reset_Session_Players stay as name hypotheses. Row 0x765AC0 is ??_GCreateGameDialogControl; its source file keeps the old name, rename when convenient.
- Start_Quick_Match 0x759E20 (2,202 B + 6 NOP): 78.77, shape 95.95 (keep/qn.cpp, X='73dd20=w/dd.cpp'). 0x752930 and 0x73D760 must go out of line while Clear and text fetches stay inline; qt.cpp overshoots at 74.40.
- Tool gap: lane_tools.py plan dropped body_bytes and bound_evidence on 0x7459A0, 0x74D780, 0x765AA0. Unit counters: shared/sound_controls.hpp moved `_$E210` to `_$E211` and `$S209` to `$S210`; later rows shifting this counter need the same edit. Failure reads "Unsupported allocatable data section .bss".
