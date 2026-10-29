// The network/event queue unit (Queue.CPP, 0x00622FB0-0x0062EAF0; Red Alert's
// QUEUE.CPP descendant: Queue_Mission, Queue_Options, Queue_Exit, Queue_AI,
// the frame-sync processing and the DoList). Names follow Red Alert where the
// body matches its function; the others are hypotheses.
#ifndef RA2_SHARED_QUEUE_HPP
#define RA2_SHARED_QUEUE_HPP

#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
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
#include "shared/ipx_manager.hpp"
#include "shared/owner_talk.hpp"
#include "shared/win32_api.hpp"

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
// Adds a line to a dialog list box (0x005C2DA0; hypothesis: color -1 is the default).
void __fastcall Unknown_005C2DA0(int color, wchar_t const *text, HWND list);
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
// A global network packet (0x1C8 bytes; Send_Port_Unreachable sends its first 0x2F;
// hypothesis: Red Alert's GlobalPacketType).
struct UnknownGlobalPacket {
    int Command;                        // +0x00
    char Name[0x2F - 4];                // +0x04
    char unknown_2f[0x1C8 - 0x2F];
};

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
// Prints the CRC log (0x0062A360; Red Alert's Print_CRCs).
void __fastcall Print_CRCs(EventClass *event);
// The other CRC log (0x0062DBA0; used instead of Print_CRCs while unknown_flag_ab62e8 is set).
void __fastcall Unknown_0062DBA0(int index, int unknown);
// Posts the main window's WM_DESTROY (0x00691320).
void Unknown_00691320();

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
extern int unknown_a3d8c8;              // 0x00A3D8C8 (cleared when the queue is full)
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
// The players of a multiplayer game (0x00A3D558, session +0x2C0; Red Alert's Session.MaxPlayers).
extern int unknown_max_players_a3d558;
// The mouse position a playback last saw (0x00A76B70, 0x00A76C78; Red Alert's
// Queue_Playback statics mx, my).
extern int unknown_mouse_x_a76b70;
extern int unknown_mouse_y_a76c78;

// The session's record file (0x00A3F59C, session +0x2304; Red Alert's Session.RecordFile).
extern CCFileClass unknown_record_file_a3f59c;

#endif
