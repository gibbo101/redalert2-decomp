// The network/event queue unit (Queue.CPP, 0x00622FB0-0x0062EAF0; Red Alert's
// QUEUE.CPP descendant: Queue_Mission, Queue_Options, Queue_Exit, Queue_AI,
// the frame-sync processing and the DoList). Names follow Red Alert where the
// body matches its function; the others are hypotheses.
#ifndef RA2_SHARED_QUEUE_HPP
#define RA2_SHARED_QUEUE_HPP

#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#include "shared/vector_class.hpp"
#include "shared/event.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/connection.hpp"
#include "shared/house.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/conn_man.hpp"
#include "shared/keyboard.hpp"
#include "shared/mouse.hpp"
#include "shared/exit.hpp"
#include "shared/special.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/owner_talk.hpp"
#include "shared/win32_api.hpp"
#include "shared/system_timer.hpp"

// Queue a MEGAMISSION (type 4) event for the player (0x006233A0).
bool __fastcall Queue_Mission(TargetClass whom, int mission, TargetClass const &target, TargetClass const &destination);
// Queue a MEGAMISSION_F (type 5) event with the formation speeds (0x00623480).
bool __fastcall Queue_Mission(TargetClass whom, int mission, TargetClass const &target, TargetClass const &destination, int speed, int maxspeed);
// Queue an OPTIONS (type 0x0C) event unless the player is out (0x00623550).
bool __fastcall Queue_Options();
// Queue a type 0x22 event unless the player is out (0x00623600; name hypothesis).
bool __fastcall Queue_Event_22();
// Queue an EXIT (type 0x13) event, or 0x27 when the master leaves a network
// game of more than two players (0x006236B0).
bool __fastcall Queue_Exit();
// Drops the executed and past events from the head of DoList (0x00629E80).
void __fastcall Clean_DoList(ConnManClass *net);
// Writes this frame's unexecuted DoList events to the record file (0x00629ED0).
void __fastcall Queue_Record();

// A player's frame-sync record (24 bytes; the arrays at 0x00AABCF0 and 0x00AABDD0
// hold 7, built by the out-of-line constructor 0x00623210). Red Alert keeps
// their_frame/their_sent/their_recv arrays; the fields are hypotheses.
struct UnknownFrameTiming {
    UnknownFrameTiming();               // 0x00623210 (Frame -1, the rest 0)
    long Frame;                         // +0x00 their frame
    int unknown_04;
    int unknown_08;
    int unknown_0c;
    int unknown_10;
    unsigned long unknown_14;           // +0x14 a timeGetTime() stamp (0x00623300)
};

// Sends a FRAMESYNC packet with the command count (0x00626500; Red Alert's Send_FrameSync).
void __fastcall Send_FrameSync(ConnManClass *net, int cmd_count);
// Reconnects a modem game or drops the oldest network player; 0 ends the game
// (0x00627910; Red Alert's Handle_Timeout).
int __fastcall Handle_Timeout(ConnManClass *net, UnknownFrameTiming *their);
// Kicks the player at a connection index: marks the house, shifts the
// frame-sync records and calls Destroy_Connection (0x00627740; named by its
// trace "Kick_Player_Now bailing").
void __fastcall Kick_Player_Now(ConnManClass *net, int index, UnknownFrameTiming *their, unsigned char error);
// A count over the other houses (0x005C3150; ECX is the house; hypothesis: a free function).
int __fastcall Unknown_005C3150(HouseClass *house);
// 0x0069A160 (restarts a timer at 0x00ABD4C4).
void Unknown_0069A160();
// The list box trim of the reconnect dialog: at most 50 lines, the last one shown (0x00626FA0).
void __fastcall Unknown_00626FA0(HWND list);
// Records a kick vote of player id against the connection index and shows it in the
// reconnect dialog (0x00627210; trace "Player %s votes to kick player %s").
void __fastcall Unknown_00627210(int id, int index);
// Reconnects a modem game (0x005CEB40; Red Alert's Reconnect_Modem).
bool Reconnect_Modem();

// The IPX manager calls made only in an IPX game (0x00623260: unknown_527800,
// 0x00623280: unknown_5277f0).
void __fastcall Unknown_00623260();
void __fastcall Unknown_00623280();
// Sends NET_PORT_UNREACHABLE (0x2F) to every router connection but the player's own
// and waits up to 300 ticks for the sends (0x0062E840; named by its trace).
void __fastcall Send_Port_Unreachable();
// Stores a player's frames behind at session +0x28EC (unknown_a3fb84; 0 outside IPX)
// (0x0062E5C0).
void __fastcall Unknown_0062E5C0(UnknownFrameTiming *their, int index);
// Puts a local event at the head of DoList for the next send frame; TXT_QUEUE_FULL
// ends a multiplayer game when it is full (0x0062E6E0).
void __fastcall Unknown_0062E6E0(EventClass *event);
// UnknownGlobalPacket (Red Alert's GlobalPacketType) is in shared/unknown_globals.hpp.
// Proposes to kick the player at a list index from the reconnect dialog: refused for the
// player himself and in game mode 4 while unknown_b2a7ec is set (0x00626FE0; named by its trace).
void __fastcall Propose_Kick_Player(HWND dialog, int index);
// Adds a copy of a received global packet to the session's list (0x00627190; the
// caller 0x004824BE passes the session's packet +0x23A8 and its address +0x2574,
// which is not read; name hypothesis).
void __fastcall Unknown_00627190(UnknownGlobalPacket *packet, IPXAddressClass *address);

// The return codes of the multiplayer queue routines (Red Alert's RetcodeEnum).
enum RetcodeType {
    RC_NORMAL,                          // no news is good news
    RC_PLAYER_READY,                    // a new player has been heard from
    RC_SCENARIO_MISMATCH,
    RC_DOLIST_FULL,
    RC_SERIAL_PROCESSED,                // modem: a SERIAL packet was processed
    RC_PLAYER_LEFT,                     // modem: the other player left the game
    RC_HUNG_UP,                         // modem: hung up
    RC_NOT_RESPONDING,
    RC_CANCEL
};
// A modem game's packet (packed; Red Alert's SerialPacketType; only the fields
// Process_Serial_Packet reads; the same bytes are read as an EventClass; 0xFA bytes).
#pragma pack(push, 1)
struct UnknownSerialPacket {
    int Command;                        // +0x00 (0x66 sign off, 0x68 message, 0x69, 0x6A, 0x78 taunt)
    char Name[0x18 - 0x04];             // +0x04 the sender (narrow)
    unsigned char ID;                   // +0x18
    union {
        unsigned short Message[1];      // +0x19 a message's text (wide; length not recovered)
        char Taunt;                     // +0x19 a taunt's packed byte
        int Progress;                   // +0x19 the sender's loading progress (command 0x6C; 0x00672160)
        struct {
            char unknown_19[4];
            char Color;                 // +0x1D the player leaving
        } ScenarioInfo;
        struct {
            char unknown_19[0x9A - 0x19];
            unsigned long ResponseTime; // +0x9A the sender's response time (command 0x69, ModemHost 0x0059B560)
        } Timing;
        // The game options (command 0x65): the sender's country, colour, version range and INI
        // checksums (both sides send them; ModemGuest 0x00598330, 0x00597680) and the host's
        // settings (ModemGuest 0x00597E50 reads them). Names follow the session members.
        struct {
            int House;                      // +0x19 the sender's country (unknown_a3d3bc)
            char Color;                     // +0x1D the sender's colour (unknown_a3d3b4)
            unsigned long MinVersion;       // +0x1E the sender's version range
            unsigned long MaxVersion;       // +0x22
            unsigned short MapName[44];     // +0x26 the map's description
            int Credits;                    // +0x7E session +0x24
            unsigned Bases : 1;             // +0x82 bit 0 session +0x20
            unsigned unknown_28 : 1;        // bit 1 session +0x28 (DestroyableBridges)
            unsigned Crates : 1;            // bit 2 session +0x29
            unsigned unknown_bit_3 : 1;
            unsigned IsOfficial : 1;        // bit 4 session ScenarioIsOfficial_880
            unsigned unknown_bits_5 : 27;
            int Checksum;                   // +0x86 the sender's INI checksum sum (Unknown_006525F0)
            unsigned char TechLevel;        // +0x8A
            unsigned char UnitCount;        // +0x8B session +0x38
            unsigned char AICount;          // +0x8C session +0x3C
            unsigned char AIDifficulty;     // +0x8D session +0x40
            unsigned unknown_bit_0 : 1;     // +0x8E
            unsigned unknown_a5 : 1;        // bit 1 session +0xA5 (HarvesterImmune)
            unsigned unknown_a8 : 1;        // bit 2 session +0xA8
            unsigned FogOfWar : 1;          // bit 3 session +0xA7
            unsigned unknown_2a : 1;        // bit 4 session +0x2A
            unsigned unknown_2b : 1;        // bit 5 session +0x2B
            unsigned unknown_2c : 1;        // bit 6 session +0x2C
            unsigned unknown_34 : 1;        // bit 7 session +0x34
            unsigned unknown_bits_8 : 24;
            unsigned int Seed;              // +0x92 the random seed (Seed 0x00A40D3C)
            SpecialClass Special;           // +0x96 the game options word
            unsigned long unknown_9a;       // +0x9A
            int FileLength;                 // +0x9E session ScenarioFileLength_87c
            unsigned char GameSpeed;        // +0xA2 session +0x30
            char FileName[13];              // +0xA3 session ScenarioFileName_658
            char Digest[0x20];              // +0xB0 session ScenarioDigest_85a
            int INIID;                      // +0xD0 the sender's unknown_ini_8397a0_unique_id
            int ArtID;                      // +0xD4 the sender's unknown_art_ini_unique_id
            unsigned long Version;          // +0xD8 the sender's version number (0x00737AF0)
        } Options;
        char unknown_19[0xFA - 0x19];   // the packet is 0xFA bytes (Reconnect_Null_Modem's send and receive copies)
    };
};
#pragma pack(pop)
// Ends the modem connection of a player (0x005CEBA0; Red Alert's Destroy_Null_Connection).
void __fastcall Destroy_Null_Connection(int id, int error);
// Handles a modem game's packet: sign-off, message, taunt and the other serial
// commands; an event packet comes back as RC_NORMAL (0x00626B30; Red Alert's
// Process_Serial_Packet).
RetcodeType __fastcall Process_Serial_Packet(char *multi_packet_buf, int first_time);

// The megamission unit lists a compressed packet may refer to by slot instead of sending
// them again (0x00A76CA8: 8 slots of a 5-byte Whom and up to 127 more 5-byte units; the
// unit counts 0x00AABDB0 and the frames each slot was saved 0x00AABE94; names are hypotheses).
extern char unknown_megamission_lists_a76ca8[8][0x280];
extern int unknown_megamission_counts_aabdb0[8];
extern int unknown_megamission_frames_aabe94[8];
// Looks the megamission unit list (count, whom and the other units) up in the saved
// slots: a match with save set takes the units out of the packet (count 0, size less,
// the slot in whom[6]); without a match, save stores it in the free or oldest slot.
// True when it matched (0x006279D0; name hypothesis).
bool __fastcall Unknown_006279D0(unsigned char *count, int *size, char *whom, char *units, bool save);

// Sends OutList's events in packets of at most multi_packet_max bytes through the connection
// manager; the number of events sent (0x006261A0; Red Alert's Send_Packets, with
// Build_Send_Packet and Add_Uncompressed_Events inline).
int __fastcall Send_Packets(ConnManClass *net, char *multi_packet_buf, int multi_packet_max, int max_ahead, int my_sent);
// Puts a received compressed packet's events in DoList; the count, -1 when DoList is full
// (0x006282D0; Red Alert's Extract_Compressed_Events).
int __fastcall Extract_Compressed_Events(void *buf, int bufsize);
// Adds OutList's events to a send packet in the compressed form; the new size, the events
// added in *added (0x00627B60; Red Alert's Add_Compressed_Events).
int __fastcall Add_Compressed_Events(void *buf, int bufsize, int frame_delay, int size, int cap, int *added);

// A count-up timer: the time since Started (Process_Receive_Packet 0x006265C0 reads it).
struct UnknownElapsedTimer {
    UnknownElapsedTimer() : Started(Timer) {}
#ifdef RA2_QUEUE_STATICS
    // Empty but user-declared: Queue.CPP's static timer 0x00A780C0 registers the
    // atexit destructor 0x006232C0 (a bare ret). Declared only for Queue.CPP.
    ~UnknownElapsedTimer() {}
#endif
    long Started;                       // +0x00
    SystemTimerClass Timer;             // +0x04
};
// Frame-sync records (0x00AABCF0; 7, built by 0x00623230).
extern UnknownFrameTiming unknown_timing_aabcf0[7];
// The other players' frame-sync records (0x00AABDD0; 7, built by 0x006232D0).
extern UnknownFrameTiming unknown_their_timing_aabdd0[7];
// A count-up timer started at startup (0x00A780C0, built by 0x006232A0).
extern UnknownElapsedTimer unknown_timer_a780c0;
// The commands sent so far (0x00AABE78; Red Alert's Queue_AI_Multiplayer static my_sent).
extern unsigned short unknown_my_sent_aabe78;
// The session's meta packet buffer and its size (0x00A3F81A, 0x00A3FA48: session +0x2582,
// +0x27B0; Red Alert's Session.MetaPacket and Session.MetaSize).
extern char unknown_meta_packet_a3f81a[];
extern int unknown_meta_size_a3fa48;
// The entries of the router's MEGAFRAMEINFO (type 0x25: 13 bytes) and PACKETTIMING (type 0x26:
// 8 bytes) packets, after the event header; the entry count is the header's House byte.
#pragma pack(push, 1)
struct UnknownMegaFrameEntry {
    long Frame;                         // +0x00
    long unknown_04;
    unsigned short CommandCount;        // +0x08
    unsigned char Delay;                // +0x0A
    char ID;                            // +0x0B
    unsigned char Flags;                // +0x0C (bit 0: no response time)
};
struct UnknownPacketTimingEntry {
    char ID;                            // +0x00
    bool unknown_01;                    // +0x01 (set: report the player when this machine is the master)
    unsigned long ResponseTime;         // +0x02
    short unknown_06;
};
#pragma pack(pop)
// The router's response time and the largest response time of the other players
// (0x00A402DC is unknown_a402dc; 0x00A402CC, session +0x3034; hypothesis).
extern unsigned int unknown_a402cc;
// A player id the PACKETTIMING report skips (0x00A402D4, session +0x303C).
extern int unknown_a402d4;
// The other players' response times by connection index (0x00A76C88).
extern unsigned long unknown_response_times_a76c88[];
// Handles a received FRAMEINFO / FRAMESYNC packet (0x006265C0; Red Alert's
// Process_Receive_Packet, with the RA2 timing records and an elapsed timer).
RetcodeType __fastcall Process_Receive_Packet(ConnManClass *net, char *multi_packet_buf, int id, int packetlen,
    UnknownFrameTiming *their, UnknownElapsedTimer *timer);
// Sends the last commands and waits up to 600 ticks for every player to pass this frame
// before the score screen, resending the frame sync every 15 ticks (0x00624850; called by
// 0x0065D80A and 0x0065DEDA; name hypothesis).
void __fastcall Wait_For_End_Game();
// Handles the keyboard input of a frame (0x005406E0; Red Alert's Keyboard_Process).
void __fastcall Keyboard_Process(int &input);

// The reconnect dialog: the kick buttons (0x007EC3F8, in list order) and the
// response-time bars beside them (0x007EC418), one per player.
extern int unknown_kick_buttons_7ec3f8[8];
extern int unknown_timing_bars_7ec418[8];
// The reconnect dialog's ping counts (game mode 4): pings sent, seconds waited, the
// two warnings given and the flag that ends the wait (0x00AB62E0-0x00AB62F8; cleared by
// unknown_reset_globals_ab62e0 0x00627330).
extern bool unknown_ab62e0;
extern int unknown_ab62ec;
extern int unknown_ab62f0;
extern bool unknown_ab62f4;
extern bool unknown_ab62f5;
extern int unknown_ab62f8;
// Draws each player's response-time bar in the reconnect dialog (0x00626CB0).
void __fastcall Unknown_00626CB0(HWND dialog);
// The reconnect dialog's window procedure (0x00627350): the kick buttons, a
// once-a-second ping in game mode 4, and WM_USER + 0x97 to set it up.
BOOL __stdcall Unknown_00627350(HWND dialog, UINT message, WPARAM wparam, LPARAM lparam);
// The dialog helpers it calls (0x005B6000 on setup, 0x005B6060 on WM_DESTROY, and 0x005FEE70 /
// 0x005FE380, declared in shared/unknown_globals.hpp; hypotheses).
void __fastcall Unknown_005B6000(HWND dialog);
void __fastcall Unknown_005B6060(HWND dialog);

// The queue processing of a frame: playback, single player or multiplayer (0x00623770).
void __fastcall Queue_AI();
// The multiplayer queue processing (0x00623B00; Red Alert's Queue_AI_Multiplayer).
void __fastcall Queue_AI_Multiplayer();
// Executes the DoList events of this frame for max_houses houses from base_house;
// 0 on a fatal error (0x00628880; Red Alert's Execute_DoList; the last three
// arguments are a hypothesis: Queue_AI_Multiplayer passes the connection manager,
// 0x00AABEB8 and 0x00AABDD0).
int __fastcall Execute_DoList(int max_houses, int base_house, ConnManClass *net, long *their_frame, void *timing);
// Adds the game state to GameCRC (0x00629FA0; Red Alert's Compute_Game_CRC).
void __fastcall Compute_Game_CRC();
// Saves the frame's game state into sync state slot index (the frame mod 256), after the game CRC; without
// sync logging only draws the random number (0x0062CF40).
void __fastcall Unknown_0062CF40(int index);
// Prints the CRC log (0x0062A360; Red Alert's Print_CRCs).
void __fastcall Print_CRCs(EventClass *event);
// The other CRC log (0x0062DBA0; used instead of Print_CRCs while unknown_flag_ab62e8 is set).
void __fastcall Unknown_0062DBA0(int index, EventClass *event);
// Unknown_00691320 (0x00691320, posts the main window's WM_DESTROY): shared/exit.hpp.

// A CRC sent in the FRAMESYNC packet (0x00A40770).
extern unsigned long unknown_crc_a40770;
// The FRAMESYNC packets sent (0x00AB62E4).
extern int unknown_frame_syncs_ab62e4;
// The time() of the last kick (0x00AB6304).
extern long unknown_last_kick_ab6304;
extern bool unknown_flag_a417c8;        // 0x00A417C8
extern bool unknown_flag_abd500;        // 0x00ABD500 (set when a kick leaves one house)
extern bool unknown_flag_a3d8d1;        // 0x00A3D8D1 (the same, unless another kick came within 60 s)
extern int unknown_a3fb84[];            // 0x00A3FB84 (session +0x28EC: frames behind per player)
extern int unknown_a3d568;              // 0x00A3D568 (session +0x2D0)
extern unsigned int unknown_a402dc;     // 0x00A402DC (session +0x3044)
extern unsigned int unknown_a6eb1c;     // 0x00A6EB1C
// unknown_a3d8c8 (0x00A3D8C8): shared/unknown_globals.hpp.
extern int unknown_a3d8cc;              // 0x00A3D8CC
extern int unknown_ab62dc;              // 0x00AB62DC
extern bool unknown_flag_a3d8d2;        // 0x00A3D8D2
void Unknown_0059DA00();                // 0x0059DA00
// The game CRC of this frame (0x00A76C74; Red Alert's GameCRC).
extern unsigned long GameCRC;
// The last 256 frames' CRCs (0x00AB5EDC; Red Alert's CRC[]).
extern unsigned long CRC[256];
// The frame at which a playback prints the CRCs and exits (0x00A40314, session +0x307C;
// Red Alert's Session.TrapPrintCRC).
extern int unknown_trap_print_crc_a40314;
// Selects Unknown_0062DBA0 for the CRC log (0x00AB62E8).
extern bool unknown_flag_ab62e8;
// The frames between packets (0x00A3D564, session +0x2CC; Red Alert's Session.FrameSendRate).
extern unsigned int unknown_frame_send_rate_a3d564;
// The mouse position a playback last saw (0x00A76B70, 0x00A76C78; Red Alert's
// Queue_Playback statics mx, my).
extern int unknown_mouse_x_a76b70;
extern int unknown_mouse_y_a76c78;

// The session's record file (0x00A3F59C, session +0x2304; Red Alert's Session.RecordFile).
extern CCFileClass unknown_record_file_a3f59c;

// The frame rate samples and the largest MaxAhead of the game (0x00A6EB20, 0x00A6EB24, 0x00A3D578;
// the statistics file and the sync logs print them).
extern unsigned int accumulated_fps_00a6eb20;
extern unsigned int fps_sample_count_00a6eb24;
extern int max_max_ahead_00a3d578;

#pragma pack(push, 4)
// A house in a saved game state (0x5C bytes).
struct UnknownSyncHouse {
    char Name[0x14];                    // +0x00
    unsigned char IsHuman;              // +0x14
    char Color[0x20];                   // +0x15
    int ID;                             // +0x38 (-1: unused)
    char HouseType[0x20];               // +0x3C
};
// An infantry, unit, aircraft or building in a saved game state (0x68 bytes).
struct UnknownSyncObject {
    int Coord;                          // +0x00
    int Type;                           // +0x04
    char TypeName[0x18];                // +0x08
    char Owner;                         // +0x20 (a house index)
    int TargetID;                       // +0x24
    char Target[0x18];                  // +0x28
    int NavComID;                       // +0x40
    char NavCom[0x18];                  // +0x44
    int SpeedAccum;                     // +0x5C
    short TrackNumber;                  // +0x60
    short TrackIndex;                   // +0x62
    unsigned char Facing;               // +0x64
    unsigned char Facing2;              // +0x65
    unsigned char Mission;              // +0x66
    char Speed;                         // +0x67
};
// A map or logic layer object in a saved game state (0x28 bytes).
struct UnknownSyncLayerObject {
    int Value;                          // +0x00
    int Type;                           // +0x04
    char Name[0x18];                    // +0x08
    char Owner;                         // +0x20 (a house index, -1 none)
    char unknown_21[3];
    short RTTI;                         // +0x24
};
// A saved game state (0x33C bytes; 256 at 0x00A780D8, built by 0x006231A0 and filled by
// 0x0062CF40; 0x0062DBA0 writes one to a sync file).
struct UnknownSyncState {
    int unknown_000;                    // +0x000
    int RandomNumber;                   // +0x004
    int Frame;                          // +0x008
    UnknownSyncHouse Houses[8];         // +0x00C
    int ObjectCount;                    // +0x2EC the records at Objects
    int Counts[4];                      // +0x2F0 infantry, units, aircraft, buildings
    UnknownSyncObject *Objects;         // +0x300 in that order
    int LayerCounts[5];                 // +0x304
    UnknownSyncLayerObject *Layers[5];  // +0x318
    int LogicCount;                     // +0x32C
    UnknownSyncLayerObject *Logic;      // +0x330
    char *Buffer;                       // +0x334 the records (allocated on first use)
    unsigned int BufferSize;            // +0x338 (grown in 64K steps)
#ifdef RA2_QUEUE_STATICS
    // Out of line at 0x006231A0 and 0x006231F0 (accepted elsewhere); Queue.CPP's
    // initializer 0x00623320 and atexit destructor 0x00623370 expand them.
    // Declared only for Queue.CPP (RA2_QUEUE_STATICS, set by its first source).
    UnknownSyncState()
    {
        Objects = 0;
        ObjectCount = 0;
        for (int index = 0; index < 5; index++) {
            Layers[index] = 0;
            LayerCounts[index] = 0;
        }
        Logic = 0;
        LogicCount = 0;
        BufferSize = 0x20000;
        Buffer = 0;
    }
    ~UnknownSyncState()
    {
        if (Buffer != 0) {
            operator delete(Buffer);
        }
    }
#endif
};
#pragma pack(pop)
extern UnknownSyncState unknown_sync_states_a780d8[256];
// The random number drawn each frame while no sync log is kept (0x00AABCE0).
extern int unknown_random_aabce0;

#endif
