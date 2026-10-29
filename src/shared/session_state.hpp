// The multiplayer session object (0x00A3D298, unknown_session_a3d298 in shared/unknown_globals.hpp;
// Red Alert's SessionClass) and the settings blocks only it holds.
#ifndef RA2_SHARED_SESSION_STATE_HPP
#define RA2_SHARED_SESSION_STATE_HPP

#include "shared/unknown_globals.hpp"
#include "shared/session_blocks.hpp"
#include "shared/serial_settings.hpp"
#include "shared/message_list.hpp"
#include "shared/mplayer_score_type.hpp"
#include "shared/cc_file_class.hpp"

// The ids of the players that voted to kick a connection (session +0x8D8, 8 per
// connection; Kick_Player_Now shifts them with the frame-sync records).
struct UnknownKickVoters {
    int ID[8];
};
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
    // Credits 10000, ten units, the five flags set, the rest 0 (0x0066E330; expanded into the session constructor).
    UnknownGameOptions();

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
    ~UnknownSessionState();                 // 0x0066EB20
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
    // The unknown_3022 value of the session player with this ID; 0 when none has it (0x00672F50).
    unsigned short Unknown_00672F50(int id);
    // The lobby slot whose name equals this session player's name; 0 when none (0x00672F90).
    int Unknown_00672F90(int player);
    // Entered once while unknown_flag_a40958 is set (+0x3080 records it): keeps the game speed in
    // unknown_game_speed_7f3230 (game mode 0 runs at speed 2), pauses the game, captures the mouse and sets the
    // global volume to full (0x00672DE0; callers around Special_Dialog 0x00481850; hypothesis).
    void Unknown_00672DE0();
    // Undoes 0x00672DE0: restores the speed, stops the sound and speech, disables the tooltips, releases and
    // hides the mouse (0x00672E70).
    void Unknown_00672E70();
    // Resolves the random choices before a game: observers (-3) get colour 8, random countries (-2) come from
    // the game mode (slot 23; the session's 0x00672940 without one) and random colours from 0x00672980, for the
    // session players and the eight computer slots (slot 24 for their countries); the first player's colour goes to
    // unknown_a3d3b4 (0x00672BB0).
    void Unknown_00672BB0();
    // The lobby slot whose name equals the text; 0 when none (0x00672FF0).
    int Unknown_00672FF0(char const *name);
    // The session player whose name equals this lobby slot's name; 0 when none (0x00673030).
    int Unknown_00673030(int slot);

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
    int unknown_11c;                        // +0x11C (also unknown_a3d3b4; with +0x120 the colour 0x00672AE0 copies from +0x12C)
    int unknown_120;                        // +0x120 (the join dialog copies +0x130 here)
    int unknown_124;                        // +0x124 (also unknown_a3d3bc)
    int unknown_128;                        // +0x128 (with +0x124 the country 0x00672A30 copies from +0x134)
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
    CCFileClass RecordFile;                 // +0x2304 (Red Alert's Session.RecordFile)
    char unknown_2368[0x2380 - 0x2368];
    unsigned short HostName_2380[20];       // +0x2380 the host's name (wide; also unknown_host_name_a3f618)
    char unknown_23a8[0x27B4 - 0x23A8];
    DynamicVectorClass<NodeNameType *> NodeList_27b4;  // +0x27B4 (a third of Red Alert's Games / Players / Chat lists)
    DynamicVectorClass<NodeNameType *> NodeList_27cc;  // +0x27CC
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
    DynamicVectorClass<unsigned short const *> CallWaitStrings;   // +0x28D4
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
    int Unknown_00672980();                 // 0x00672980 (a random colour not in use; returns it)
};

#endif
