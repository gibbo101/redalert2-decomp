// MainLoop.CPP (unit 0x0053F270-0x00541F59): main loop state and helpers.
#ifndef SHARED_MAIN_LOOP_HPP
#define SHARED_MAIN_LOOP_HPP

#include "shared/cd_timer.hpp"
#include "shared/system_timer.hpp"

// Set by 0x0053F470, cleared by 0x0053F480 and after the end-of-game handlers in
// 0x0053F840, read by unknown_53f460 (0x00A6EB30; meaning not recovered).
extern bool unknown_main_loop_flag_a6eb30;
void Set_Main_Loop_Flag_0053f470();
void Clear_Main_Loop_Flag_0053f480();

// Keyboard scroll keys held (0x00A6EBDC): left 0x100, right 0x1000, up 0x01, down 0x10;
// Keyboard_Process sets a bit on the arrow key press and clears it on its release.
extern int unknown_scroll_keys_a6ebdc;

// For network and modem games, processes the key for inter-player messages (0x00540C20).
void __fastcall Message_Input(int &input);

// The sidebar tab key action on the screen object (0x006818B0; name hypothesis).
class SidebarClass;
void __fastcall Sidebar_Tab_Key_006818b0(SidebarClass *sidebar);

// The end-of-game flags (Westwood's PlayerWins, PlayerLoses, PlayerRestarts and
// PlayerAborts; names from their use in 0x0053F840).
extern bool player_wins_a35db1;         // 0x00A35DB1
extern bool player_loses_a40c78;        // 0x00A40C78
extern bool player_restarts_866250;     // 0x00866250
extern bool player_aborts_a35db0;       // 0x00A35DB0
// Raised while the end-of-game handlers run (0x00A3FABC; also Start_Scenario).
extern int unknown_a3fabc;

void __fastcall Unknown_Reload_Art_Set_006F31B0();
// Also declared in shared/wol_sink.hpp, which units of this file cannot include (its
// templates emit code this unit does not have).
void __fastcall Unknown_00698D00(bool arg);             // 0x00698D00

// Every 1024 frames queues the player's type-8 event, then runs the end-of-game
// handler for the flag that is set; true when the game is no longer active
// (0x0053F840; the end of Westwood's Main_Loop).
bool __fastcall Main_Loop_End_0053f840();

// A millisecond time source (operator long 0x005B6A20; Westwood's MSTimerClass, name
// hypothesis): the network frame timer counts with it.
class MSTimerClass {
public:
    operator long() const;                  // 0x005B6A20
};
// The frame timers (Westwood's FrameTimer and NetFrameTimer, names hypotheses).
extern CDTimerClass<SystemTimerClass> unknown_frame_timer_839990;     // 0x00839990
extern CDTimerClass<MSTimerClass> unknown_net_frame_timer_839970;     // 0x00839970
// The ticks Sync_Delay waits away (Westwood's SpareTicks; 0x00A4031C).
extern int unknown_spare_ticks_a4031c;
// The frames counted this second (0x00A6EB18; Westwood's FramesThisSecond).
extern unsigned int unknown_frames_this_second_a6eb18;
// Waits for the screen blit (0x004961D0; also shared/main_opt.hpp).
long Wait_For_Surface_Blit_004961d0();
// Waits out the frame: services the network and the input while a network game's
// frame timer runs, else blits and sleeps; once a second samples the frame rate
// (0x00540960; Westwood's Sync_Delay).
void Sync_Delay();

#endif
