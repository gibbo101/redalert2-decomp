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
#include "shared/session_blocks.hpp"
#include "shared/serial_settings.hpp"
#include "shared/message_list.hpp"
#include "shared/mplayer_score_type.hpp"

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
    char unknown_57[0x6c - 0x57];
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
// The session object at 0x00A3D298 (its first word is unknown_game_mode_a3d298;
// SessionClass in TS, hypothesis).
// The ids of the players that voted to kick a connection (session +0x8D8, 8 per
// connection; Kick_Player_Now shifts them with the frame-sync records).
struct UnknownKickVoters {
    int ID[8];
};
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
    };
};
#pragma pack(pop)
// The session's packet (0x00A3F640, session +0x23A8; Red Alert's Session.GPacket).
extern UnknownGlobalPacket unknown_gpacket_a3f640;
// A block of multiplayer game settings (0x7C bytes), kept per game type in the
// session (the Skirmish, LAN and WonlinePref sections of RA2.INI).
class CCINIClass;
class MultiplayerGameMode;
class MultiMission;
struct UnknownGameOptions {
    // Reads the block from a section; the computer slots default to
    // (first_slot for slot 1, else other_slots, -2, -2) (0x0066F1F0).
    void Read(CCINIClass &ini, char const *section, int other_slots, int first_slot);
    void Write(CCINIClass &ini, char const *section);   // 0x00670270

    int GameMode;                           // +0x00 (default: the first registered mode's id)
    int ScenIndex;                          // +0x04
    int GameSpeed;                          // +0x08
    int Credits;                            // +0x0C
    int UnitCount;                          // +0x10
    bool ShortGame;                         // +0x14
    bool SuperWeaponsAllowed;               // +0x15
    bool BuildOffAlly;                      // +0x16
    bool MCVRepacks;                        // +0x17
    bool CratesAppear;                      // +0x18
    int Slots[8][3];                        // +0x1C (Slot01..Slot07 entries; slot 0 is not saved)
};
struct UnknownSessionState {
    int Value_0124_006729f0();
    // netdlg2's scenario download test for an official map (0x00672140; meaning not recovered).
    bool Unknown_00672140();
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
    union {
        struct {
            int Type;                       // +0x00 the game mode (also unknown_game_mode_a3d298; Red Alert's Session.Type)
            MultiplayerGameMode *Mode;      // +0x04 the game mode object (also unknown_session_a3d29c)
            char unknown_08[0x18 - 0x08];
            // +0x18 the first word of the 0xEC-byte options block at 0x00A3D2B0 (UnknownLobbyState in
            // shared/lobby.hpp; its 0x00672810 clears AICount and the AI tables): the game mode index that
            // UnknownGameOptions::GameMode saves (0x005CC890).
            int GameModeIndex;
        };
        char unknown_00[0x1C];
    };
    int ScenarioIndex;                      // +0x1C the multiplayer map (unknown_multi_missions_a3d8d8 index; -1: none)
    bool unknown_bases_20;                  // +0x20 multiplayer bases (also unknown_flag_a3d2b8)
    int unknown_24;                         // +0x24 every multiplayer house's third setup value (Assign_Houses)
    bool unknown_28;                        // +0x28 (false clears the global DestroyableBridges; unknown_session_a3d2c0)
    bool unknown_crates_29;                 // +0x29 crates (also unknown_flag_a3d2c1)
    bool unknown_2a;                        // +0x2A
    bool unknown_2b;                        // +0x2B
    bool unknown_2c;                        // +0x2C
    int GameSpeed_30;                       // +0x30 the game speed (0..5 pick the frame-ahead values; Options +0x0 copies it)
    bool unknown_34;                        // +0x34
    int UnitCount;                          // +0x38 the multiplayer start units (Create_Units)
    int AICount;                            // +0x3C the computer players
    int unknown_difficulty_40;              // +0x40 the multiplayer difficulty (also unknown_session_difficulty_a3d2d8)
    int AIDifficulty[8];                    // +0x44
    int AICountry[8];                       // +0x64 (-1 none, -3 random)
    int AIColor[8];                         // +0x84
    bool unknown_a4;                        // +0xA4
    bool unknown_a5;                        // +0xA5 (HarvesterImmune of the global options; unknown_session_a3d33d)
    bool unknown_a6;                        // +0xA6
    bool unknown_fog_a7;                    // +0xA7 fog of war (also unknown_session_fog_a3d33f)
    bool unknown_a8;                        // +0xA8 (unknown_session_a3d340)
    char unknown_a9[0x104 - 0xA9];
    unsigned long UniqueID;                 // +0x104 (One_Time: Compute_Unique_ID)
    char Handle[20];                        // +0x108 the player's name (also unknown_name_a3d3a0)
    char unknown_11c[0x120 - 0x11C];    // +0x11C (also unknown_a3d3b4)
    int unknown_120;                        // +0x120 (the join dialog copies +0x130 here)
    int unknown_124;                        // +0x124 (also unknown_a3d3bc)
    char unknown_128[0x12C - 0x128];
    int unknown_12c;                        // +0x12C the player's colour (GDlgSupp 0x004D23C0)
    int unknown_130;                        // +0x130 (-2: the colour shows as random; 0x004D23C0)
    int unknown_134;                        // +0x134 the player's country (GDlgSupp 0x004D1820)
    int unknown_138;                        // +0x138 (-2 random, -3 observer: the country shows as that; 0x004D1820)
    UnknownGameOptions SkirmishOptions;     // +0x13C
    UnknownGameOptions LANOptions;          // +0x1B8
    UnknownGameOptions WonlineOptions;      // +0x234
    int unknown_2b0;                        // +0x2B0 (also unknown_int_a3d548)
    char unknown_2b4[0x2B8 - 0x2B4];
    bool WOLLimitResolution;                // +0x2B8
    int LastNickSlot;                       // +0x2BC
    char unknown_2c0[0x2C8 - 0x2C0];
    unsigned int MaxAhead_2c8;              // +0x2C8 the frames ahead (set by the game speed; also unknown_max_ahead_a3d560)
    unsigned int unknown_2cc;               // +0x2CC
    char unknown_2d0[0x2E0 - 0x2D0];
    unsigned int unknown_2e0;               // +0x2E0 (MaxAhead_2c8 at the start of a cooperative map)
    unsigned int unknown_2e4;               // +0x2E4 (from MaxAhead_2c8 by the ping class, a multiple of 10)
    unsigned int unknown_2e8;               // +0x2E8 (by the game speed; 0 without pings; also unknown_a3d580)
    char unknown_2ec[0x638 - 0x2EC];
    bool unknown_638;                       // +0x638 (cleared by 0x00672440)
    bool unknown_639;                       // +0x639 (cleared before the load wait, 0x0065C7D0)
    bool unknown_63a;                       // +0x63A (cleared before the load wait, 0x0065C7D0)
    char unknown_63b[0x640 - 0x63B];
    // The multiplayer maps (also unknown_multi_missions_a3d8d8; Red Alert's Scenarios).
    DynamicVectorClass<MultiMission *> Scenarios;   // +0x640
    // The game's scenario as the host announces it (netdlg2.cpp; Red Alert's ScenarioFileName,
    // ScenarioDigest, ScenarioFileLength and ScenarioIsOfficial; hypotheses).
    char ScenarioFileName_658[0x85A - 0x658];   // +0x658
    char ScenarioDigest_85a[0x87C - 0x85A];     // +0x85A
    int ScenarioFileLength_87c;                 // +0x87C
    bool ScenarioIsOfficial_880;                // +0x880
    char unknown_881[0x884 - 0x881];
    int unknown_884;                            // +0x884 (sent in the game options text)
    char unknown_888[0x8A0 - 0x888];
    // +0x8A0 copies of received global packets (RTTI DynamicVectorClass<GlobalPacketType *>,
    // vtable 0x007A9584; Unknown_00627190 adds them).
    DynamicVectorClass<UnknownGlobalPacket *> GlobalPackets_8a0;
    int KickVotes[8];                       // +0x8B8 per connection: the kick votes received (0x00627210)
    UnknownKickVoters KickVoters[8];        // +0x8D8 per connection: the voters' ids
    MessageListClass Messages;              // +0x9D8 the on-screen messages (Red Alert's Session.Messages; 0x00A3DC70)
    char unknown_1e74[0x1F74 - 0x1E74];
    union {
        // The cooperative campaign's score records, one per player (CampaignScoreClass
        // 0x00465D10 fills them from the houses; also unknown_session_scores_a3f20c).
        MPlayerScoreType Scores[8];         // +0x1F74
        struct {
            char unknown_1f74[0x1FB4 - 0x1F74];
            int unknown_1fb4[4][28];        // +0x1FB4 four rows indexed by the +0x2300 counter (MPCooperative slot 34 sets -1)
        };
    };
    int unknown_22f4;                       // +0x22F4 (also unknown_a3f58c)
    int ScoreCount;                         // +0x22F8 the used Scores records (also unknown_session_score_count_a3f590)
    int ScoreWinner;                        // +0x22FC the last record of a house that did not lose (0x00465D10)
    int unknown_2300;                       // +0x2300 (capped at 3; also unknown_a3f598)
    char unknown_2304[0x2380 - 0x2304];
    unsigned short HostName_2380[20];       // +0x2380 the host's name (wide; also unknown_host_name_a3f618)
    char unknown_23a8[0x27E4 - 0x23A8];
    // The player list (the object at 0x00A3FA7C, shared/unknown_player_entry.hpp unknown_players_a3fa7c).
    DynamicVectorClass<NodeNameType *> Players;   // +0x27E4
    char unknown_27fc[0x2800 - 0x27FC];
    // +0x2800 the eight lobby player slots (also unknown_player_slots_a3fa98, shared/unknown_player_entry.hpp;
    // 0x005CA540 strength-reduces them and AIColor onto one pointer, so both are read through the session).
    NodeNameType *PlayerSlots[8];
    char unknown_2820[0x282C - 0x2820];
    int CurPhoneIdx;                        // +0x282C
    SerialSettingsType SerialDefaults;      // +0x2830
    char unknown_28a0[0x28A4 - 0x28A0];
    DynamicVectorClass<PhoneEntryClass *> PhoneBook;   // +0x28A4
    DynamicVectorClass<char *> InitStrings;            // +0x28BC
    // The modem call-waiting strings (wide; 0x0066EAA0 adds the four TXT_CWAIT_* texts).
    DynamicVectorClass<unsigned short *> CallWaitStrings;   // +0x28D4
    char unknown_28ec[0x290C - 0x28EC];
    int unknown_290c;                       // +0x290C the ping class (1: below 1000 ms, 2: above)
    bool ViaPacketRouter;                   // +0x2910 (also unknown_flag_a3fba8)
    char unknown_2911[0x293C - 0x2911];
    UnknownSessionBlock_293C unknown_293c;  // +0x293C (MPCooperative slot 34 saves it, slot 37 restores it)
    UnknownSessionBlock_299C unknown_299c;  // +0x299C (the same)
    char unknown_29bc[0x2FA0 - 0x29BC];
    UnknownSessionBlock_299C unknown_2fa0;  // +0x2FA0 (the same)
    char unknown_2fc0[0x2FC8 - 0x2FC0];
    // The game master (host): name and house index (-1: none). The load wait
    // 0x0065C520 clears both when it drops the master (names after TS/YR's
    // SessionClass MasterPlayerName/MasterPlayerID, hypothesis).
    unsigned short MasterPlayerName[21];    // +0x2FC8 (wide)
    char unknown_2ff2[0x2FF4 - 0x2FF2];
    int unknown_2ff4[8];                    // +0x2FF4 (Create_Connections sets each to TickCount)
    char unknown_3014[0x301C - 0x3014];
    int MasterPlayerID;                     // +0x301C
    char unknown_3020[0x3022 - 0x3020];
    UnknownSessionBlock_3022 unknown_3022;  // +0x3022 (MPCooperative slot 34 saves it, slot 37 restores it)
    char unknown_3032[0x3034 - 0x3032];
    int unknown_3034;                       // +0x3034 (also unknown_a402cc; Create_Connections clears it)
    bool unknown_3038;                      // +0x3038 (game mode 4: connect through the packet router)
    int unknown_303c;                       // +0x303C (also unknown_a402d4; -1)
    char unknown_3040[0x3044 - 0x3040];
    int unknown_3044;                       // +0x3044 (20)
    char unknown_3048[0x3080 - 0x3048];
    unsigned char unknown_3080;             // +0x3080 (0x00672F10 returns it; the dialog control test 0x005E0760)
    char unknown_3081[0x3AA4 - 0x3081];
    int unknown_3aa4;                       // +0x3AA4 (MPCooperative slot 34 saves it, slot 37 restores it)

    // Whether the house (null: the player's) is the game master: by MasterPlayerID,
    // else by name, in game mode 4 (0x0066F150; YR's Am_I_Master, hypothesis).
    bool Am_I_Master(HouseClass *house);
    // Saves the player and serial settings, the init strings and the phone book to
    // RA2.INI (0x00670380; Red Alert's Write_MultiPlayer_Settings; after the skirmish
    // dialog and WOL games).
    void Write_MultiPlayer_Settings();
    // Adds the four TXT_CWAIT_* strings to CallWaitStrings (0x0066EAA0).
    void Unknown_0066EAA0();
    // Reads the scenario descriptions and sets UniqueID (0x0066EDB0; Red Alert's One_Time).
    void One_Time();
    void Read_Scenario_Descriptions();      // 0x00670C50
    // A number from the time, the free disk space and PATH (0x00671600).
    unsigned long Compute_Unique_ID();
    // Deletes the maps, the init strings and the phone book (0x006714B0).
    void Free_Scenario_Descriptions();
    // Makes a connection to every other player (game modes 3 and 4) and records the
    // houses' addresses; 0 in other modes (0x0066EE50; Red Alert's Create_Connections;
    // Do_Lose after a networked replay restarts).
    int Create_Connections();
    void Unknown_00672440();                // 0x00672440 (game mode 4, after the load wait of 0x0065C7D0)
    unsigned char Unknown_00672F10();       // 0x00672F10 (+0x3080)
    int Unknown_00672940();                // 0x00672940 (MultiplayerGameMode slot 23)
    bool Unknown_006728D0(int color);       // 0x006728D0 (whether a player or computer slot already has the colour; -2 never)
    void Unknown_00672980();                // 0x00672980 (a random colour not in use)
};
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
class UnknownBeacon;
class Unknown84E8D0 {
public:
    UnknownBeacon *Unknown_0042E860(int x, int y, int z);  // 0x0042E860 (the beacon within 128 of the point)
    bool Unknown_0042E740(int x, int y, int z);            // 0x0042E740 (selects the beacon within 128 of the point)
    Unknown84E8D0();                                        // 0x0042D960 (the static initializer; inline)
    ~Unknown84E8D0();                                       // 0x0042D990 (the atexit destructor; inline)
    void Unknown_0042E370(int house, int x, int y, int z, int slot);   // 0x0042E370 (places a beacon; slot -1: the first free one)
    void Unknown_0042E290(Surface *surface, Rect rect);     // 0x0042E290 (draws the allied beacons)
    void Unknown_0042EED0(Surface *surface, Rect rect);     // 0x0042EED0 (draws the allied beacons during the blink phase)
    bool Unknown_0042EFD0();                               // 0x0042EFD0 (an allied beacon is shown and the blink phase is on)
    void Unknown_0042E150();                    // 0x0042E150 (frees the per-house blocks; last call of 0x00519960)
    void Unknown_0042E1A0();                    // 0x0042E1A0 (Read_Scenario_INI)
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
extern char unknown_b2a6d8[];           // 0x00B2A6D8 (MPCooperative slot 37 copies unknown_wstring_b26cb8 into it)
extern unsigned int unknown_b2ab84;     // 0x00B2AB84 (slot 37: unknown_protocol_7fd370)
extern int unknown_pings_b2a734[];      // 0x00B2A734 the players' pings in ms (1000: none)
extern bool unknown_b2a820;             // 0x00B2A820
extern bool unknown_b293d8;             // 0x00B293D8
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
