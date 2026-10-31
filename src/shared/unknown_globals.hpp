// Scalar and pointer globals of the data segment that several headers need (one declaration
// each; addresses in the comments).
#ifndef RA2_SHARED_UNKNOWN_GLOBALS_HPP
#define RA2_SHARED_UNKNOWN_GLOBALS_HPP

class Surface;
class Rect;
class HouseClass;
class ConvertClass;
class BuildingClass;
struct NodeNameType;

#include "shared/coord.hpp"
#include "shared/vector_class_decl.hpp"

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
// The machine profile Get_Performance_Profile (0x0051A880) rates once (-1 until then;
// 0x007DB564) and the texts it writes for the version dialog (0x00516C40): CPU, RAM, VRAM,
// blit speed and the profile (0x00A411FC, 0x00A41388, 0x00A41308, 0x00A41408, 0x00A4127C).
extern int unknown_performance_profile_7db564;
extern char unknown_profile_cpu_text_a411fc[];
extern char unknown_profile_ram_text_a41388[];
extern char unknown_profile_vram_text_a41308[];
extern char unknown_profile_blit_text_a41408[];
extern char unknown_profile_text_a4127c[];
extern Surface *unknown_surface_839944;  // 0x00839944 (a video memory surface: Get_Performance_Profile times blits from it)
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
extern int unknown_a3fba4;            // 0x00A3FBA4 the latency setting (the GOptions slider shows 3 - it; cleared when the GO arrives)
// The players of a multiplayer game (0x00A3D558, session +0x2C0; Red Alert's Session.MaxPlayers;
// moved from shared/queue.hpp, which pulls header statics into the netshare unit).
extern int unknown_max_players_a3d558;
// The observer mode switch ([MultiPlayer] ObserverMode of RA2.INI, 0x00A72C68; moved from shared/wol_sink.hpp).
extern int unknown_a72c68;
// Enables or disables the first session player's side and colour combo boxes unless that player
// is in the observer slot (0x005CD030; moved from shared/wol_sink.hpp).
typedef struct HWND__ *HWND;
void __fastcall Unknown_005cd030(HWND dialog, bool value);
// The World Online chat object, 0 when not connected (0x00A72CFC; moved from shared/wol_sink.hpp).
namespace WOL {
struct IChat;
// A WOL user (only the members WOnline.cpp reads here; moved from shared/wol_sink.hpp).
struct User {
    unsigned int flags;                 // +0x00
    char unknown_04[0x14 - 4];
    unsigned int unknown_14;
    unsigned long unknown_18;
    int unknown_1c;
    User *next;                         // +0x20
    char name[10];                      // +0x24
    char unknown_2e[0x57 - 0x2e];
    char unknown_57[0x64 - 0x57];
    int locale;                         // +0x64
    int team;                           // +0x68
};
}
// The first user of the channel list whose flags have bit 0 set (the game host; 0x0074DA60, hypothesis:
// it returns a copy in a static record, 0 when there is none).
WOL::User *Unknown_0074DA60();
extern WOL::IChat *unknown_chat_a72cfc;
HWND Unknown_00735B10();                                // 0x00735B10 (the current dialog window; moved from shared/wol_sink.hpp)
// Dialog helpers (moved from shared/queue.hpp and shared/wol_sink.hpp): 0x005FEE70 before a dialog paints,
// 0x005FE380 for WM_DRAWITEM, 0x007357E0 ends a dialog with a result (the command id).
void __fastcall Unknown_005FEE70(HWND dialog);
void __fastcall Unknown_005FE380(long item);
void __fastcall Unknown_007357E0(void *dialog, int arg);    // 0x007357E0
// Adds a formatted line to the chat display (hypothesis; 0x005C2C80; moved from shared/wol_sink.hpp).
void __cdecl Unknown_005C2C80(int color, unsigned short const *format, ...);
// The system chat colour (0x007A7360; moved from shared/wol_sink.hpp).
extern int unknown_color_7a7360;
// The same into the list 0x5B5 (0x005C2D10).
void __cdecl Unknown_005c2d10(int color, unsigned short const *format, ...);
// Adds a line to a dialog list box (0x005C2DA0; hypothesis: color -1 is the default; moved from shared/queue.hpp).
void __fastcall Unknown_005C2DA0(int color, unsigned short const *text, HWND list);
// The session's map name (0x00A3D342, session +0xAA; the lobby's map messages print it).
extern unsigned short unknown_map_name_a3d342[];
// 0x005159B0 (the lobby dialog opener calls it with 0, true before creating its dialog; moved from
// shared/ms_message_box.hpp).
void __fastcall unknown_5159b0(int unknown1, bool unknown2);
extern int unknown_a3d3b4;            // 0x00A3D3B4 (session +0x11C)
extern char unknown_name_a3d3a0[];    // 0x00A3D3A0 (the local nick name)
extern int unknown_a3d3bc;            // 0x00A3D3BC (session +0x124; the modem guest's colour list choice)
extern bool unknown_flag_a3d2b8;       // 0x00A3D2B8 (session +0x20: multiplayer bases)
// A global network packet (moved from shared/queue.hpp) (0x1C7 bytes, packed: Unknown_00627190 copies that many;
// Send_Port_Unreachable sends its first 0x2F; Red Alert's GlobalPacketType, the
// name RTTI gives the session's packet list DynamicVectorClass<GlobalPacketType *>).
#pragma pack(push, 1)
struct UnknownGlobalPacket {
    int Command;                        // +0x00
    char Name[20];                      // +0x04
    char unknown_18[0x2F - 0x18];       // +0x18 (NET_ANSWER_PLAYER: a narrow string, unknown_a71bc4)
    union {
        char unknown_2f[0x1C7 - 0x2F];
        struct {
            unsigned int IsOpen : 1;    // +0x2F the game is open (unknown_session_a3f616)
        } GameInfo;                     // command 1 (NET_ANSWER_GAME)
        struct {
            int unknown_2f;             // +0x2F session 0x006729F0 (+0x124)
            int unknown_33;             // +0x33 session 0x00672A10 (+0x11C)
            int unknown_37;             // +0x37 0x005BBA50 of the host's name
            char unknown_3b[0x53 - 0x3B];
            int Slot;                   // +0x53 unknown_lobby_a3fa94
            int Observer;               // +0x57 the slot is the observer slot and the player is an observer
        } PlayerInfo;                   // command 3 (NET_ANSWER_PLAYER)
        struct {
            int unknown_2f;             // +0x2F session 0x006729F0 (+0x124)
            int unknown_33;             // +0x33 session 0x00672A10 (+0x11C)
            char unknown_37[0x3B - 0x37];
            unsigned long unknown_3b;   // +0x3B version_object_00a40c88 0x007131B0
            unsigned long unknown_3f;   // +0x3F version_object_00a40c88 0x007131C0
            int unknown_43;             // +0x43 unknown_a71e9c
            int unknown_47;             // +0x47 unknown_a71ea4
            int unknown_4b;             // +0x4B unknown_a71ea0
            int unknown_4f;             // +0x4F 0x00737AF0
            char unknown_53[0x57 - 0x53];
            int unknown_57;             // +0x57 the joiner's flag argument
        } Join;                         // command 6 (NET_QUERY_JOIN)
        struct {
            int Why;                    // +0x2F the reason (4: by the host; Red Alert's REJECT_BY_OWNER)
        } Reject;                       // command 8 (NET_REJECT_JOIN)
        struct {
            unsigned long ID;           // +0x2F the session's UniqueID
            int Color;                  // +0x33 unknown_a3d3b4 (session +0x11C)
        } Chat;                         // command 4 (Red Alert's NET_CHAT_ANNOUNCE)
        struct {
            int Kickee;                 // +0x2F the id of the player proposed for a kick
            int Proposer;               // +0x33 the id of the player who proposes it
        } Kick;                         // command 0x1C (Propose_Kick_Player)
        struct {
            char unknown_2f;            // +0x2F
            unsigned short Buf[112];    // +0x30 the text (wide)
            int unknown_110;            // +0x110
            int unknown_114;            // +0x114 0x005BBA50 of the host's name
        } Message;                      // command 12 (NET_MESSAGE)
        struct {
            unsigned short Names[(0x1C7 - 0x2F) / 2];   // +0x2F the slot names (wide; Unknown_Slot_Names_005c8cf0 fills them)
        } Slots;                        // command 0x16
        struct {
            int Percent;                // +0x2F the sender's loading progress (UnknownSessionState 0x00672160)
        } Progress;                     // command 0x0F
        struct {
            char unknown_2f[0xAF - 0x2F];
            unsigned int FileLength;    // +0xAF the file's length
            char ShortFileName[0x1C7 - 0xB3];   // +0xB3 the file's name (length not recovered)
        } ScenarioInfo;                 // command 0x11 (Red Alert's NET_FILE_INFO; Get_File_From_Host 0x0066AEF0)
    };
};
#pragma pack(pop)
// The session's packet (0x00A3F640, session +0x23A8; Red Alert's Session.GPacket).
extern UnknownGlobalPacket unknown_gpacket_a3f640;
// The session object (0x00A3D298; its first word is unknown_game_mode_a3d298; SessionClass in TS,
// hypothesis); its layout is in shared/session_state.hpp.
struct UnknownSessionState;
extern UnknownSessionState unknown_session_a3d298;
// Two flags (0x00A3F120 for game mode 3, 0x00A3F121 for mode 4: session +0x1E88/+0x1E89; a received
// taunt packet is played only while the mode's flag is set; next to unknown_flags_a3f118).
extern bool unknown_flag_a3f120;
extern bool unknown_flag_a3f121;
// The last message text received (0x00A3F122, session +0x1E8A; Red Alert's Session.LastMessage).
extern unsigned short unknown_last_message_a3f122[];
// Plays the taunt with the packed byte (low nibble taunt, high nibble country; 0x00715FB0; hypothesis).
void __fastcall Unknown_Play_Taunt_00715fb0(char packed);
// The player count of a multiplayer map (0x005C6600; hypothesis).
int __fastcall Unknown_005c6600(int scenario);
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
    virtual int unknown_slot10();                        // slot 10 (the lobby: the default country in game modes 3 and 4; 0x005CA3F0)
    virtual void unknown_slot11();
    virtual bool unknown_slot12();                       // slot 12 (the lobby: the slot count is not limited; 0x005CB300)
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
    virtual int unknown_slot32();                        // slot 32 (the lobby: a player limit, -1 for none; 0x005C65A0)
    virtual void unknown_slot33();
    virtual void unknown_slot34();
    virtual void unknown_slot35(int arg);                // slot 35 (Do_Lose 0x0065DEC0 with 0 when there is no replay)
    virtual bool unknown_slot36();                       // slot 36 (Do_Lose: true replays)
    virtual void unknown_slot37();                       // slot 37 (Do_Lose, before the replay)
    virtual void unknown_slot38();
    virtual void unknown_slot39();
    virtual bool unknown_slot40();                       // slot 40 (the lobby: whether slot 7 becomes the observer slot; 0x005CA6C0, 0x005CB8D0)
    void Unknown_005B7CE0();                             // 0x005B7CE0 (after slot 27)
    CCINIClass *unknown_ini_005b7840();                 // 0x005B7840 (the session INI)
};
extern UnknownSessionA3D29C *unknown_session_a3d29c;     // 0x00A3D29C
// Services audio, queued movies and the network while a long operation runs
// (0x00481FB0).
void __fastcall Service_Game_IO_00481fb0();
bool unknown_53f460();                  // 0x0053F460 returns the byte at 0x00A6EB30
bool unknown_53fbd0();                  // 0x0053FBD0
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
class UnknownBeacon;
class Unknown84E8D0 {
public:
    UnknownBeacon *Unknown_0042E860(CoordStruct coord);  // 0x0042E860 (the beacon within 128 of the point)
    bool Unknown_0042E740(int x, int y, int z);            // 0x0042E740 (selects the beacon within 128 of the point)
    Unknown84E8D0();                                        // 0x0042D960 (the static initializer; inline)
    ~Unknown84E8D0();                                       // 0x0042D990 (the atexit destructor; inline)
    void Unknown_0042E370(int house, int x, int y, int z, int slot);   // 0x0042E370 (places a beacon; slot -1: the first free one)
    void Unknown_0042E290(Surface *surface, Rect rect);     // 0x0042E290 (draws the allied beacons)
    void Unknown_0042EED0(Surface *surface, Rect rect);     // 0x0042EED0 (draws the allied beacons during the blink phase)
    bool Unknown_0042EFD0();                               // 0x0042EFD0 (an allied beacon is shown and the blink phase is on)
    void Unknown_0042E150();                    // 0x0042E150 (frees the per-house blocks; last call of 0x00519960)
    void Unknown_0042E1A0();                    // 0x0042E1A0 (Read_Scenario_INI)
    void Unknown_0042EBE0(int house); // removes the house beacon slots, original56-byte RET4
    bool Unknown_0042E700(int house);           // 0x0042E700 true when one of the house's three slots is empty
    // +0x00 three owned blocks per house (8 houses): the static initializer 0x0042D960
    // clears the 0x18 words, its atexit 0x0042D990 deletes each non-null one.
    UnknownBeacon *unknown_00[8][3];
    int unknown_60;                 // the beacons are enabled
    int unknown_64;                 // +0x64..+0x6C the PBEACON.SHP width, height and frame count
    int unknown_68;
    int unknown_6c;
    int unknown_70;                 // +0x70..+0x78 the RDRBEACN.SHP width, height and frame count
    int unknown_74;
    int unknown_78;
    int unknown_7c;                 // +0x7C the radar beacon's blink cycle (frames << 2)
    CoordStruct unknown_80;         // +0x80 the position a new beacon starts at
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
// Cleared when the event queue is full; Init_Random keeps the seed while it is set
// (0x00A3D8C8; moved from shared/queue.hpp).
extern int unknown_a3d8c8;
// The game's random seed and the one the command line asks for (0x00A40D3C and
// 0x00A40D40; Red Alert's Seed and CustomSeed; Init_Random 0x00515710).
extern unsigned int Seed;
extern unsigned int CustomSeed;
// Records the side for the interface (stores it at 0x00AD0958; 0x007168C0).
void __fastcall Unknown_007168C0(int side);
// Called by Unknown_0051a330 before the side colour is chosen (0x006F44D0).
void Unknown_006F44D0();
// Copies one of two colours (0 or else) into the interface colour (0x006F45A0).
void __fastcall unknown_select_color(int which);
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
class Rect;
struct Unknown535910 {
    Unknown535910();                        // 0x005359A0
    virtual bool Message_00536ea0(int message, void *data);      // slot 0
    void Unknown_00535BF0();
    void Unknown_005359E0();                // 0x005359E0 (places itself by the screen size)
    Point2D Unknown_00535AB0();             // 0x00535AB0 (the loading screen's text position)
    int Unknown_00535B60();                 // 0x00535B60 (the name width: -1 in a campaign)
    void Unknown_00535B90();                // 0x00535B90 (opens LOAD.MIX)
    void Unknown_00536E00(Surface *surface);    // 0x00536E00 (copies its surface onto another)
    void Unknown_00536E20();                // 0x00536E20 (frees its buffers and surfaces)

    MixFileClass<CCFileClass> *LoadMix;     // +0x04 LOAD.MIX
    int unknown_08[4];                      // +0x08 (x, y, width, height; 0x005359E0)
    int unknown_18[4];                      // +0x18 (x, y, width, height; 0x005359E0)
    int unknown_28[4];                      // +0x28 (x, y, width, height; 0x005359E0)
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
void Unknown_00535970();                    // 0x00535970 (releases and deletes the object)
extern Unknown535910 *unknown_load_progress_a6e7c4;   // 0x00A6E7C4
// The loading-screen sizes: widths 640, 800, 1024 (0x007ADD68) and heights
// 480, 600, 768 (0x007ADD74).
extern int unknown_screen_widths_7add68[3];
extern int unknown_screen_heights_7add74[3];
void __fastcall Unknown_006f24a0(int flag);     // 0x006F24A0 (loads the campaign loading art)
void __fastcall Unknown_006f25c0();             // 0x006F25C0 (loads the multiplayer loading art)
#ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif
// The loading screen's two text areas, centred on screens past 800x600
// (0x00536B80, 0x00536C00).
Rect __fastcall Unknown_00536b80();
Rect __fastcall Unknown_00536c00();
// Draws text in an area of the surface: flags 1 centres it, 2 right-aligns
// it; fill widens the area to width (0x00536C70).
void __fastcall Unknown_00536c70(wchar_t const *text, Surface *surface, int x, int y, int width, int flags, bool fill);
// Draws text in an area of the surface in a 16-bit colour through the game font, flags as for
// OwnerDraw::unknown_draw_text_5fe020 (0x00536D30).
void __fastcall Unknown_00536d30(wchar_t const *text, Surface *surface, Rect const &area, unsigned short color, int flags);
// Owner-draw helpers (ownrdraw.cpp; types are hypotheses).
struct RECT;
void __fastcall Unknown_005feb60(Rect *area, Surface *surface, int unknown_0, int unknown_9f);    // 0x005FEB60
class BitFontClass;
namespace OwnerDraw {
// Draws text clipped to area with the font in a Win32 colour (0x00BBGGRR); flags 4 centres it vertically;
// the rest of the arguments go to BitTextClass::Print_Box. Returns 0 (0x005FE020).
int __fastcall unknown_draw_text_5fe020(Surface *surface, wchar_t const *text, RECT *area, BitFontClass *font,
                                        unsigned long color, int flags, int unknown_7, int unknown_8, int unknown_9,
                                        int unknown_10);
}
// The art data at 0x00AC1154 (0x006F2490; the campaign loading screen's bar drawer).
void *Unknown_Get_Art_6f2490();
// Assign_Houses' session data and globals (0x0065FBB0).
extern int unknown_house_setting_7d88d8;            // 0x007D88D8 (every new house's +0x11C)
// Two values a recording starts with (Load_Recording_Values 0x00516BA0 / Save_Recording_Values 0x00516B00).
extern int unknown_a40d3c;                          // 0x00A40D3C
extern int unknown_a40c38;                          // 0x00A40C38
class HouseClass;
extern HouseClass *unknown_house_a72d28;            // 0x00A72D28 (the player without a team)
// The index of a colour scheme by name (0x00663D90).
int __fastcall unknown_color_scheme_index_663d90(char const *name, int kind);
// An empty string used as an INI default (0x0083C55C).
extern char unknown_string_83c55c[];
// WOnline.cpp globals (moved from shared/wol_sink.hpp, which includes this header).
extern int unknown_b2a7ec;              // 0x00B2A7EC
extern int unknown_b2a7fc;              // 0x00B2A7FC (the game ID the loading screen shows)
extern char unknown_b2a6d8[];           // 0x00B2A6D8 (MPCooperative slot 37 copies unknown_wstring_b26cb8 into it)
extern unsigned int unknown_b2ab84;     // 0x00B2AB84 (slot 37: unknown_protocol_7fd370)
extern int unknown_pings_b2a734[];      // 0x00B2A734 the players' pings in ms (1000: none)
// The two comma-separated lists of house names a game mode 4 session started with (Squad 1 and Squad 2:
// 0x00672440 makes each list's houses allies; MPCooperative slot 37 empties both).
extern char unknown_squad_1_b2a820[];    // 0x00B2A820
extern char unknown_squad_2_b293d8[];    // 0x00B293D8
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
// The game speed kept by UnknownSessionState::Unknown_00672DE0 (0x007F3230; -1: none).
extern int unknown_game_speed_7f3230;
// An empty function 0x00672E70 calls first (0x005173A0).
void Unknown_005173A0();
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
// GRFXTXT.PAL's data (0x00A41670), the converter built from it (0x00A41678) and GRFXTXT.SHP
// (0x00A41674), loaded by 0x00511C90 and freed by Prog_End.
extern void *unknown_grfxtxt_palette_a41670;
extern void *unknown_grfxtxt_shape_a41674;
extern ConvertClass *unknown_grfxtxt_drawer_a41678;
// Converters of CAMEO.PAL (0x008323B4) and of the surface 0x00839950 (0x008323B0), built by
// 0x00511C90; 0x008323C0 is the unit drawer.
extern ConvertClass *unknown_drawer_8323b4;
extern ConvertClass *unknown_drawer_8323b0;
extern ConvertClass *Unit_Draw_Convert_008323C0;
struct ShapeFileStruct;
extern ShapeFileStruct *unknown_building_depth_shape_85029c;   // 0x0085029C
extern Surface *unknown_surface_839968;                        // 0x00839968 (next to the screen surfaces)
// Blocks Prog_End frees (0x00A6E38C, 0x00A52EB0-0x00A52EBC; owners not recovered).
extern void *unknown_block_a6e38c;
extern void *unknown_block_a52eb0;
extern void *unknown_block_a52eb4;
extern void *unknown_block_a52eb8;
extern void *unknown_block_a52ebc;
class Buffer;
extern Buffer *unknown_buffer_a35e20;                          // 0x00A35E20
extern void *unknown_instance_00851ca8;                        // 0x00851CA8 (a loaded library)
// WinMain's active-object registration (0x00ABD484) and two handles it creates (0x00ABD480,
// 0x00ABD47C).
extern unsigned long unknown_active_object_abd484;
extern void *unknown_handle_abd480;
extern void *unknown_handle_abd47c;
// Shutdown steps Prog_End calls (names not recovered).
void Unknown_005DDB40();
void Unknown_00521CB0();
void Unknown_00603FA0();
void Unknown_0059D900();
void Unknown_005D5F40();
void Unknown_005EAC20();
void Unknown_00613E40();
void Unknown_006F57E0();
void Unknown_00714860();
void Unknown_005BB5A0();
void Unknown_00522930();
// The program's exit cleanup, registered with atexit by WinMain (0x006909E0; Red Alert's Prog_End).
void __cdecl Prog_End();

#endif
