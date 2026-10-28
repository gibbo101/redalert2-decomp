// Scalar and pointer globals of the data segment that several headers need (one declaration
// each; addresses in the comments).
#ifndef RA2_SHARED_UNKNOWN_GLOBALS_HPP
#define RA2_SHARED_UNKNOWN_GLOBALS_HPP

class Surface;
class HouseClass;
class ConvertClass;
class BuildingClass;

extern int unknown_int_7add80;
extern ConvertClass *unknown_drawer_8323b8;  // 0x008323B8 (OverlayTypeClass slot 40; also CellClass 0x474C6B)
extern ConvertClass *unknown_drawer_8323cc;  // 0x008323CC
extern bool unknown_flag_8373c1;  // 0x008373C1 the power bar is shown (Power AI/Draw_It, Radar 0x00630350)
extern bool unknown_flag_8373c3;  // 0x008373C3
extern bool unknown_flag_83740c;
extern int unknown_int_839630;
extern int unknown_int_839634;
extern int unknown_int_839638;  // 0x00839638 sidebar x offset
extern int unknown_int_839648;  // 0x00839648 screen width
extern int unknown_int_83964c;  // 0x0083964C screen height
extern Surface *unknown_surface_839948;  // 0x00839948 (sidebar surface)
extern Surface *unknown_surface_839950;  // 0x00839950 screen
extern Surface *unknown_surface_839954;  // 0x00839954 (Get_Input draws the buttons on it)
extern Surface *unknown_surface_839958;  // 0x00839958 background
extern Surface *unknown_surface_83995c;  // 0x0083995C current drawing surface
extern Surface *unknown_surface_839964;  // 0x00839964 the surface Render composes
extern bool unknown_flag_839c4c;  // 0x00839C4C
extern int unknown_8523e0;  // 0x008523E0 VQA frame width (hypothesis)
extern int unknown_8523e4;  // 0x008523E4 VQA frame height (hypothesis)
extern bool unknown_flag_852fd7;  // 0x00852FD7
extern HouseClass *unknown_player_a35db4;  // 0x00A35DB4 the player's house
extern int unknown_game_mode_a3d298;  // 0x00A3D298
// The session object at 0x00A3D298 (its first word is unknown_game_mode_a3d298;
// SessionClass in TS, hypothesis).
struct UnknownSessionState {
    int Value_0124_006729f0();
    int Value_011c_00672a10();
    void Set_Value_00672a30(int value, bool update);
    void Set_Value_00672ae0(int value, bool update);
    // Reports scenario-loading progress in percent (redraws the loading
    // screen and sends it to the other players; 0x00672160, name hypothesis).
    void Loading_Progress_00672160(int percent);
    // The colour scheme of a player colour (0x006715D0; -2 reads as 8).
    int Unknown_006715D0(int color);

    // Data (offsets from 0x00A3D298; the first word is unknown_game_mode_a3d298,
    // +0x40/+0x28/+0xA7 are declared separately in this header for now).
    char unknown_00[0x24];
    int unknown_24;                         // +0x24 every multiplayer house's third setup value (Assign_Houses)
    char unknown_28[0x3C - 0x28];
    int AICount;                            // +0x3C the computer players
    char unknown_40[0x44 - 0x40];
    int AIDifficulty[8];                    // +0x44
    int AICountry[8];                       // +0x64 (-1 none, -3 random)
    int AIColor[8];                         // +0x84
};
extern UnknownSessionState unknown_session_a3d298;
// The session's game mode object (+0x04, a MultiplayerGameMode; moved from
// shared/radar.hpp).
class CCINIClass;
class UnknownSessionA3D29C {
public:
    virtual void unknown_slot0();
    virtual bool unknown_slot1();
    virtual bool unknown_slot2();
    virtual void unknown_slot3();
    virtual void unknown_slot4();
    virtual void unknown_slot5();
    virtual void unknown_slot6();
    virtual void unknown_slot7();
    virtual void unknown_slot8();
    virtual void unknown_slot9();
    virtual void unknown_slot10();
    virtual void unknown_slot11();
    virtual void unknown_slot12();
    virtual void unknown_slot13();
    virtual void unknown_slot14();
    virtual void unknown_slot15();
    virtual void unknown_slot16();
    virtual void unknown_slot17();
    virtual void unknown_slot18();
    virtual void unknown_slot19();
    virtual void unknown_slot20();
    virtual void unknown_slot21();
    virtual void unknown_slot22();
    virtual void unknown_slot23();
    virtual void unknown_slot24();
    virtual void unknown_slot25();
    virtual bool unknown_slot26();                       // slot 26 (Read_Scenario_INI)
    virtual void unknown_slot27(bool official);          // slot 27 (multiplayer setup 0x0065E8C0: makes the units)
    virtual void unknown_slot28();                       // slot 28 (0x0065E8C0, at the end)
    virtual void unknown_slot29();                       // slot 29 (0x0065E8C0, after slot 28)
    void Unknown_005B7CE0();                             // 0x005B7CE0 (after slot 27)
    CCINIClass *unknown_ini_005b7840();                 // 0x005B7840 (the session INI)
};
extern UnknownSessionA3D29C *unknown_session_a3d29c;     // 0x00A3D29C
// Services audio, queued movies and the network while a long operation runs
// (0x00481FB0).
void __fastcall Service_Game_IO_00481fb0();
// Deletes every LightConvertClass in the global list (0x00832398) and makes a
// new default one (tint 1000, 1000, 1000) (0x00529720; DisplayClass 0x0049E570
// and UnknownIDSource::Read_Basic call it; name hypothesis).
void __cdecl Reset_Light_Converts_00529720();
// Deletes every radar event (0x0063C640).
void RadarEventClass_unknown_delete_all_63c640();
// The object at 0x0084E8D0 (moved from shared/display.hpp).
class Unknown84E8D0 {
public:
    void Unknown_0042E1A0();                    // 0x0042E1A0 (Read_Scenario_INI)
    bool Unknown_0042E700(int house);
};
extern Unknown84E8D0 unknown_object_84e8d0;
// Read_Scenario_INI's settings and helpers (0x0065EB40; meanings mostly not recovered).
extern int unknown_difficulty_a40b1c;           // 0x00A40B1C the campaign difficulty (the scenario's Difficulty)
extern int unknown_session_difficulty_a3d2d8;   // 0x00A3D2D8 (session +0x40) the multiplayer difficulty
extern bool unknown_session_fog_a3d33f;         // 0x00A3D33F (session +0xA7) fog of war
extern bool unknown_session_a3d2c0;             // 0x00A3D2C0 (session +0x28) false clears the global DestroyableBridges
// The game option byte that enables the map's +0x154 entries (crates; hypothesis)
// (0x00A3D2C1, session +0x29).
extern bool unknown_flag_a3d2c1;
// The session's starting crate count (0x00A3D55C, session +0x2C4; bounded by Rules
// CrateMinimum/CrateMaximum; hypothesis).
extern int unknown_session_a3d55c;
// Eight per-house flags all set at the end of the multiplayer setup 0x0065E8C0
// (0x00A3F118; meaning not recovered).
extern bool unknown_flags_a3f118[8];
extern int unknown_a40770;                      // 0x00A40770 (cleared before the houses are read)
extern bool unknown_a40d39;                     // 0x00A40D39 (game mode 5 reads TMCJ4F.INI)
extern bool unknown_7df630;                     // 0x007DF630 (false while the buildings are read)
void __fastcall Init_Theater_00519e70(int theater);         // 0x00519E70
bool __fastcall Unknown_0051a330(int side);                 // 0x0051A330 (side 0 allied, 1 soviet; false fails the scenario)
// TacticalClass: a height (leptons) as screen pixels (0x006A2970, __fastcall;
// hypothesis, the inverse of 0x006A29B0; the locomotors' Shadow_Point).
int __fastcall Unknown_006A2970(int height);
void __fastcall Unknown_006c0220();                         // 0x006C0220 (walks TeamTypes)
void __fastcall Unknown_006ef5c0(CCINIClass &ini);          // 0x006EF5C0 ([Tubes])
void Unknown_006e9fe0();                                    // 0x006E9FE0 (walks the TiberiumClass list)
void __fastcall Unknown_006e9520();                         // 0x006E9520 (walks the TiberiumClass list)
void Unknown_006ecf10();                                    // 0x006ECF10 (walks the objects at 0x00AC0CD8)
// A lazily made object (0x00A6E7C4; 0x00535910 makes it, 0x00535BF0 runs it).
struct Unknown535910 {
    void Unknown_00535BF0();
};
Unknown535910 *Unknown_00535910();
// Assign_Houses' session data and globals (0x0065FBB0).
extern int unknown_house_setting_7d88d8;            // 0x007D88D8 (every new house's +0x11C)
class HouseClass;
extern HouseClass *unknown_house_a72d28;            // 0x00A72D28 (the player without a team)
// The index of a colour scheme by name (0x00663D90).
int __fastcall unknown_color_scheme_index_663d90(char const *name, int kind);
// An empty string used as an INI default (0x0083C55C).
extern char unknown_string_83c55c[];
extern int unknown_a40774;  // 0x00A40774 (a live-object count; BuildingClass, FactoryClass, ...)
extern bool unknown_flag_a40958;  // 0x00A40958 (the destructor then calls ObjectClass slot 52)
extern bool unknown_flag_a40b30;  // 0x00A40B30 the sidebar is on the left
extern float unknown_volume_a40b44;  // 0x00A40B44 sound effect volume scale
extern bool unknown_flag_a40d04;  // 0x00A40D04 (FootClass::Detach keeps a live parasite while it is set)
extern bool unknown_a40d13;
extern bool unknown_flag_a40d13;  // 0x00A40D13
extern int unknown_ini_format_a40d24;
extern bool unknown_flag_a40d28;  // 0x00A40D28 application active (focus)
extern bool unknown_flag_a40d44;  // 0x00A40D44
extern int unknown_ab9174;        // 0x00AB9174 (cleared when the game pauses or resumes)
// The global sound volume kept while the game window has no focus (0x007F1DEC;
// 0x4000 otherwise) and the tooltip state restored with the focus (0x00A40B34).
extern int unknown_saved_volume_7f1dec;
extern bool unknown_tooltips_enabled_a40b34;
// Pauses or resumes the first queued radar movie (0x005A0A90; its slot 3).
void __fastcall Pause_Radar_Movie_005a0a90(bool pause);
extern long unknown_com_objects_a6eb14;  // 0x00A6EB14 (live COM object count; hypothesis)
extern bool unknown_flag_abcd84;  // 0x00ABCD84
extern int unknown_b263d8;  // 0x00B263D8

// Called with 0 by RadarClass 0x00633D30 when the radar movie's flag (+0x04)
// sets +0x14B8, and with a trigger action's Data by TActionClass 0x006B2F90
// (meanings not recovered).
void __fastcall Unknown_0065C1F0(int arg);              // 0x0065C1F0

// Takes an index into the list at 0x00A71054 (count 0x00A71060) and a flag;
// does nothing in a multiplayer game (TActionClass 0x006B0D50/0x006B0D60
// pass a trigger action's Data with false/true; meaning not recovered).
void __fastcall Unknown_005A0920(int index, bool arg2);          // 0x005A0920
// Brings in a team of the type as reinforcements, at a waypoint or (-1) its
// own (TActionClass 0x006B1470/0x006B1490; Westwood's Do_Reinforcements,
// name hypothesis).
class TeamTypeClass;
bool __fastcall Do_Reinforcements(TeamTypeClass *team, int waypoint);   // 0x00639970
// Another reinforcement of a team type at a waypoint, in the same unit
// (TActionClass 0x006B2810; meaning not recovered).
bool __fastcall Unknown_0063A880(TeamTypeClass *team, int waypoint);    // 0x0063A880

// Switches the display to width x height; false when the mode cannot be set
// (0x005434E0; logs "About to set video mode").
bool __fastcall Set_Video_Mode_005434e0(int width, int height);

// Scenario.cpp's post-load refresh (0x0065D2C0) calls these in turn (meanings
// not recovered): 0x006EA9B0 is empty, 0x006F89E0 sets 0x007F8BCC/0x007F8BD4 to
// -100 and 0x007F8BD0 to -1, 0x0063C790 clears 0x00AB6788 (eight dwords) and
// sets 0x00AB67C8/0x00AB6818 to -1.
void Unknown_006EA9B0();
void Unknown_00520770();
void Unknown_006F89E0();
void __fastcall Unknown_0063C790();

// Forgets a building pending placement (0x006F8A20; seed name FUN_006f8a20).
void __fastcall Unknown_006F8A20(BuildingClass *building);
// Pending placement of a completed building (0x006F8A00; seed FUN_006f8a00).
void __fastcall Unknown_006F8A00(BuildingClass *building);
// An empty scenario writer (0x00668EA0; Write_Scenario_INI calls it like the task
// force and team type writers, with the INI and 0).
class CCINIClass;
void __fastcall Unknown_00668EA0(CCINIClass &ini, int is_global);
// Called when the sidebar is hidden (0x005A09E0).
void Unknown_005A09E0();

#endif
