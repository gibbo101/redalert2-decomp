// Scalar and pointer globals of the data segment that several headers need (one declaration
// each; addresses in the comments).
#ifndef RA2_SHARED_UNKNOWN_GLOBALS_HPP
#define RA2_SHARED_UNKNOWN_GLOBALS_HPP

class Surface;
class Rect;
class HouseClass;
class ConvertClass;
class BuildingClass;

extern int unknown_int_7add80;
extern ConvertClass *unknown_drawer_8323b8;  // 0x008323B8 (OverlayTypeClass slot 40; also CellClass 0x474C6B)
extern ConvertClass *unknown_drawer_8323bc;  // 0x008323BC (TerrainClass slots 67/68 draw Tiberium spawners with it)
extern ConvertClass *unknown_drawer_8323cc;  // 0x008323CC
extern bool unknown_flag_7d88d5;  // 0x007D88D5 shadows are drawn (TerrainClass slots 67/68)
extern bool unknown_flag_8373c1;  // 0x008373C1 the power bar is shown (Power AI/Draw_It, Radar 0x00630350)
extern bool unknown_flag_8373c3;  // 0x008373C3
extern bool unknown_flag_83740c;
extern int unknown_int_839630;
extern int unknown_int_839634;
extern int unknown_int_839638;  // 0x00839638 sidebar x offset
extern int unknown_int_839648;  // 0x00839648 screen width
extern int unknown_int_83964c;  // 0x0083964C screen height
extern Surface *unknown_radar_surface_8336f8;  // 0x008336F8 (the radar view: TechnoClass slot 267 tests its Get_Rect)
extern Surface *unknown_surface_839948;  // 0x00839948 (sidebar surface)
// A screen-sized clipping window (0x00839640; 0, 0, 640, 400 at startup, 0x0040D920).
extern Rect unknown_window_839640;
extern Surface *unknown_surface_839950;  // 0x00839950 screen
class DSurface;
extern DSurface *unknown_surface_839954; // 0x00839954 (Get_Input draws the buttons on it; shared/dsurface.hpp)
extern Surface *unknown_surface_839958;  // 0x00839958 background
extern Surface *unknown_surface_83995c;  // 0x0083995C current drawing surface
extern Surface *unknown_surface_839964;  // 0x00839964 the surface Render composes
extern bool unknown_flag_839c4c;  // 0x00839C4C
extern int unknown_8523e0;  // 0x008523E0 VQA frame width (hypothesis)
extern int unknown_8523e4;  // 0x008523E4 VQA frame height (hypothesis)
extern bool unknown_flag_852fd7;  // 0x00852FD7
extern HouseClass *unknown_player_a35db4;  // 0x00A35DB4 the player's house
// A flag at 0x00A3D548 (radar: with the player's +0x13D, forces mode 1; no cheering while set;
// moved from shared/radar.hpp).
extern int unknown_int_a3d548;
extern int unknown_game_mode_a3d298;  // 0x00A3D298
extern int unknown_a3d3b4;            // 0x00A3D3B4 (session +0x11C)
extern char unknown_name_a3d3a0[];    // 0x00A3D3A0 (the local nick name)
extern int unknown_a3d3bc;            // 0x00A3D3BC (session +0x124; the modem guest's colour list choice)
extern bool unknown_flag_a3d2b8;       // 0x00A3D2B8 (session +0x20: multiplayer bases)
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
    char unknown_00[0x1C];
    int ScenarioIndex;                      // +0x1C the multiplayer map (unknown_multi_missions_a3d8d8 index; -1: none)
    char unknown_20[0x24 - 0x20];
    int unknown_24;                         // +0x24 every multiplayer house's third setup value (Assign_Houses)
    char unknown_28[0x38 - 0x28];
    int UnitCount;                          // +0x38 the multiplayer start units (Create_Units)
    int AICount;                            // +0x3C the computer players
    char unknown_40[0x44 - 0x40];
    int AIDifficulty[8];                    // +0x44
    int AICountry[8];                       // +0x64 (-1 none, -3 random)
    int AIColor[8];                         // +0x84
    char unknown_a4[0x12C - 0xA4];
    int unknown_12c;                        // +0x12C the player's colour (GDlgSupp 0x004D23C0)
    int unknown_130;                        // +0x130 (-2: the colour shows as random; 0x004D23C0)
    int unknown_134;                        // +0x134 the player's country (GDlgSupp 0x004D1820)
    int unknown_138;                        // +0x138 (-2 random, -3 observer: the country shows as that; 0x004D1820)
    char unknown_13c[0x638 - 0x13C];
    bool unknown_638;                       // +0x638 (cleared by 0x00672440)
    bool unknown_639;                       // +0x639 (cleared before the load wait, 0x0065C7D0)
    bool unknown_63a;                       // +0x63A (cleared before the load wait, 0x0065C7D0)
    char unknown_63b[0x2FC8 - 0x63B];
    // The game master (host): name and house index (-1: none). The load wait
    // 0x0065C520 clears both when it drops the master (names after TS/YR's
    // SessionClass MasterPlayerName/MasterPlayerID, hypothesis).
    unsigned short MasterPlayerName[21];    // +0x2FC8 (wide)
    char unknown_2ff2[0x301C - 0x2FF2];
    int MasterPlayerID;                     // +0x301C
    char unknown_3020[0x3080 - 0x3020];
    unsigned char unknown_3080;             // +0x3080 (0x00672F10 returns it; the dialog control test 0x005E0760)

    // Whether the house (null: the player's) is the game master: by MasterPlayerID,
    // else by name, in game mode 4 (0x0066F150; YR's Am_I_Master, hypothesis).
    bool Am_I_Master(HouseClass *house);
    void Unknown_0066EE50();                // 0x0066EE50 (Do_Lose after a networked replay restarts)
    void Unknown_00672440();                // 0x00672440 (game mode 4, after the load wait of 0x0065C7D0)
    unsigned char Unknown_00672F10();       // 0x00672F10 (+0x3080)
    void Unknown_00672940();                // 0x00672940 (MultiplayerGameMode slot 23)
};
extern UnknownSessionState unknown_session_a3d298;
// Saves the session settings (0x00670380; after the skirmish dialog and WOL games).
void __fastcall Save_Session_00670380(UnknownSessionState *session);
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
    virtual void unknown_slot30();
    virtual void unknown_slot31();
    virtual void unknown_slot32();
    virtual void unknown_slot33();
    virtual void unknown_slot34();
    virtual void unknown_slot35(int arg);                // slot 35 (Do_Lose 0x0065DEC0 with 0 when there is no replay)
    virtual bool unknown_slot36();                       // slot 36 (Do_Lose: true replays)
    virtual void unknown_slot37();                       // slot 37 (Do_Lose, before the replay)
    void Unknown_005B7CE0();                             // 0x005B7CE0 (after slot 27)
    CCINIClass *unknown_ini_005b7840();                 // 0x005B7840 (the session INI)
};
extern UnknownSessionA3D29C *unknown_session_a3d29c;     // 0x00A3D29C
// Services audio, queued movies and the network while a long operation runs
// (0x00481FB0).
void __fastcall Service_Game_IO_00481fb0();
// Drops a player's connection by house index: prints the "left" (error 0) or
// "connection lost" (error 1) message and removes the player (0x005BB5D0; YR's
// SessionClass::Destroy_Connection, hypothesis).
void __fastcall Destroy_Connection_005bb5d0(int id, int error);
// Game option bits (0x00A3F600, session +0x2368; bit 1 restricts the sidebar toggle
// and skips Do_Lose's score and replay; moved from shared/sidebar.hpp).
extern unsigned char unknown_flags_a3f600;
// The host's name (0x00A3F618, session +0x2380, wide; Do_Lose clears it in a
// multiplayer game; moved from shared/wol_sink.hpp).
extern unsigned short unknown_host_name_a3f618[];
// Session counters Do_Lose raises: games lost (0x00A3F58C, +0x22F4) and one capped at
// 3 (0x00A3F598, +0x2300); a mode-4 flag that keeps the IPX timing (0x00A3D580, +0x2E8).
// Meanings not recovered.
extern int unknown_a3f58c;
extern int unknown_a3f598;
extern int unknown_a3d580;
// Called before Do_Lose in a networked game without bit 1 (0x00624850, 0x0053F780;
// meanings not recovered).
void __fastcall Unknown_00624850();
void __fastcall Unknown_0053F780();
// The score screen (0x005AAA20 constructor clears the score statics; 0x005AAA40 shows
// it; an empty class built as a temporary; names hypotheses).
class UnknownScore_005AAA20 {
public:
    UnknownScore_005AAA20();
    void Presentation_005AAA40();
};
// Takes the palette at 0x00837E10 through value steps, calling the callback each
// step (0x004955D0; Do_Win: 7, the per-frame service; moved from shared/anim.hpp).
void __fastcall Unknown_004955D0(void *object, int value, void (*callback)());   // 0x004955D0
// A palette (0x00837E10): UnitTypeClass::One_Time converts through it (ConvertClass's art and
// screen palette), Rules' [Colors] schemes are made from it, 0x004955D0 fades it.
class PaletteClass;
extern PaletteClass unknown_palette_837e10;         // 0x00837E10
// Do_Win's campaign steps (meanings not recovered): 0x00491A10 decides whether the
// campaign goes on, 0x004B37C0 is the end of the campaign, 0x0058F510 the map
// selection and 0x0058F620 picks the named next scenario.
class UnknownIDSource;
bool __fastcall Unknown_00491A10();
void __fastcall Unknown_004B37C0();
void __fastcall Unknown_0058F510(UnknownIDSource *scenario);
void __fastcall Unknown_0058F620(UnknownIDSource *scenario, char const *name);
// Do_Win's score screen (0x0069A640 empty constructor, 0x0069A650 shows it;
// built as a temporary unless the scenario's SkipScore; names hypotheses).
class UnknownScore_0069A640 {
public:
    UnknownScore_0069A640();
    void Presentation_0069A650();
};
// Sets up the network game for a replay (0x005BC460; false: failed).
bool __fastcall Unknown_005BC460();
// A counter Start_Scenario raises around its disk check (0x00A3FABC; meaning not
// recovered).
extern int unknown_counter_a3fabc;
// Start_Scenario takes this scenario name instead of the campaign's when the flag
// is set (0x00A35EA8, 0x00A40D05; meanings not recovered).
extern char unknown_scenario_name_a35ea8[];
extern bool unknown_flag_a40d05;
// The dropship loadout before a scenario with StartingDropships (0x004A6B90;
// hypothesis).
void __fastcall Unknown_004A6B90();
// Plays a movie by index (0x005A07F0; Start_Scenario passes the scenario's Intro or
// Brief and Action movies with -1, 1, 1, 1; the arguments are not recovered).
void __fastcall Unknown_005A07F0(int arg1, int arg2, int arg3, int arg4, int arg5);   // 0x005A07F0
// Frees the art data before a scenario starts (0x006F30F0).
void __fastcall Unknown_Free_Art_Set_006F30F0();
void __fastcall Unknown_Free_Art_Sets_006F2510();                 // 0x006F2510
void __fastcall Unknown_Free_Art_Pair_006F26D0();                 // 0x006F26D0
// Deletes every LightConvertClass in the global list (0x00832398) and makes a
// new default one (tint 1000, 1000, 1000) (0x00529720; DisplayClass 0x0049E570
// and UnknownIDSource::Read_Basic call it; name hypothesis).
void __cdecl Reset_Light_Converts_00529720();
// Deletes every radar event (0x0063C640).
void RadarEventClass_unknown_delete_all_63c640();
// The object at 0x0084E8D0 (moved from shared/display.hpp).
class Unknown84E8D0 {
public:
    void Unknown_0042E150();                    // 0x0042E150 (frees the per-house blocks; last call of 0x00519960)
    void Unknown_0042E1A0();                    // 0x0042E1A0 (Read_Scenario_INI)
    bool Unknown_0042E700(int house);           // 0x0042E700 true when one of the house's three slots is empty
    // +0x00 three owned blocks per house (8 houses): the static initializer 0x0042D960
    // clears the 0x18 words, its atexit 0x0042D990 deletes each non-null one.
    void *unknown_00[8][3];
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
extern unsigned char unknown_session_a3d2c3;   // 0x00A3D2C3 (session +0x2B; tested as a flag, indexes a 0/1 table)
// The session's starting crate count (0x00A3D55C, session +0x2C4; bounded by Rules
// CrateMinimum/CrateMaximum; hypothesis).
extern int unknown_session_a3d55c;
extern int unknown_session_a3d2b4;              // 0x00A3D2B4 (session +0x1C; the scenario's TechLevel is set from it)
extern int unknown_session_a3d2c8;              // 0x00A3D2C8 (session +0x30)
extern int unknown_session_a3d2ac;              // 0x00A3D2AC (session +0x14; set to 2 by the pregame setup)
extern bool unknown_session_a3d33d;             // 0x00A3D33D (session +0xA5; HarvesterImmune of the global options)
extern int unknown_a40b18;                      // 0x00A40B18
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
void Unknown_006e9fe0();                                    // 0x006E9FE0 (walks the TiberiumClass list)
void __fastcall Unknown_006e9520();                         // 0x006E9520 (walks the TiberiumClass list)
void Unknown_006ecf10();                                    // 0x006ECF10 (walks the objects at 0x00AC0CD8)
// A lazily made object (0x00A6E7C4; 0x00535910 makes it, 0x00535BF0 runs it;
// vtable 0x007A549C with one slot). The progress screen sends it its percent
// before and after each change (message 0x11AE).
// Layout from the factory's stores (0x00535910, 0x60 bytes) and the release
// 0x00536E20; +0x04 is LOAD.MIX (0x00535B90 makes it), +0x5C a 0x20-byte
// surface (0x00535BF0 makes it).
struct Point2D;
class CCFileClass;
template <class T> class MixFileClass;
struct Unknown535910 {
    virtual bool Message_00536ea0(int message, void *data);      // slot 0
    void Unknown_00535BF0();
    void Unknown_005359E0();                // 0x005359E0 (places itself by the screen size)
    Point2D Unknown_00535AB0();             // 0x00535AB0 (the loading screen's text position)
    int Unknown_00535B60();                 // 0x00535B60 (the name width: -1 in a campaign)
    void Unknown_00535B90();                // 0x00535B90 (opens LOAD.MIX)
    void Unknown_00536E20();                // 0x00536E20 (frees its buffers and surfaces)

    MixFileClass<CCFileClass> *LoadMix;     // +0x04 LOAD.MIX
    char unknown_08[0x30];                  // +0x08 not written by the factory
    int unknown_38;                         // +0x38
    int unknown_3c;                         // +0x3C
    void *unknown_40;                       // +0x40 buffer, owned when unknown_4c
    void *unknown_44;                       // +0x44 buffer, owned when unknown_4d
    void *unknown_48;                       // +0x48 buffer, owned when unknown_4e
    bool unknown_4c;                        // +0x4C
    bool unknown_4d;                        // +0x4D
    bool unknown_4e;                        // +0x4E
    int unknown_50;                         // +0x50
    int unknown_54;                         // +0x54
    int unknown_58;                         // +0x58
    Surface *unknown_5c;                    // +0x5C (0x20 bytes, constructed by 0x0049ED90)
};
Unknown535910 *Unknown_00535910();
// The art data at 0x00AC1154 (0x006F2490; the campaign loading screen's bar drawer).
void *Unknown_Get_Art_6f2490();
// Assign_Houses' session data and globals (0x0065FBB0).
extern int unknown_house_setting_7d88d8;            // 0x007D88D8 (every new house's +0x11C)
class HouseClass;
extern HouseClass *unknown_house_a72d28;            // 0x00A72D28 (the player without a team)
// The index of a colour scheme by name (0x00663D90).
int __fastcall unknown_color_scheme_index_663d90(char const *name, int kind);
// An empty string used as an INI default (0x0083C55C).
extern char unknown_string_83c55c[];
// WOnline.cpp globals (moved from shared/wol_sink.hpp, which includes this header).
extern int unknown_b2a7ec;              // 0x00B2A7EC
extern int unknown_b2a7fc;              // 0x00B2A7FC (the game ID the loading screen shows)
extern int unknown_a40774;  // 0x00A40774 (a live-object count; BuildingClass, FactoryClass, ...)
extern int unknown_int_a40d48;  // 0x00A40D48 the mode the radar buttons select (1, 8, 9; Game Controls sets 4 and 6)
extern bool unknown_flag_a40d84;  // 0x00A40D84 (Game Controls: set with a session game, its sliders then stay visible)
extern bool unknown_flag_a40958;  // 0x00A40958 (the destructor then calls ObjectClass slot 52)
extern int unknown_a40b2c;          // 0x00A40B2C (LineTrail::Set_Decrement keeps the decrement when set, doubles it otherwise)
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
