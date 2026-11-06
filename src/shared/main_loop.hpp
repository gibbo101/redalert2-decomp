// MainLoop.CPP (unit 0x0053F270-0x00541F59): main loop state and helpers.
#ifndef SHARED_MAIN_LOOP_HPP
#define SHARED_MAIN_LOOP_HPP

// Declarations this unit needs from headers that Refresh_Wonline_Players 0x0073FEE0 also
// sees (any new declaration there renumbers its $L labels): included first in the unit.
#define SESSION_STATE_DECLARE_TRAP_OBJECT
#define MAP_VIEW_DECLARE_SLOT41
#define MESSAGE_LIST_DECLARE_EDIT_BUF
#define UNKNOWN_BEACONS_DECLARE_TEXT

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

// A key binding is down (the bindings are ints, pushed as dwords; WWKeyboardClass::Down takes
// a 16-bit KeyNumType; the same wrapper as the Scroll and TechnoClass units).
#include "shared/keyboard.hpp"
inline bool Main_Loop_Key_Down(int key) { return WWKeyboard->Down(key); }
// The keyboard as Keyboard_Process's repeat-key loop reads it (an inline accessor: three
// pending inline sites after its hotkey lookups, which decide their IndexClass inlining).
inline WWKeyboardClass *Main_Loop_Keyboard() { return WWKeyboard; }
// The character of an int key (Message_Input's chat keys; the same int-key wrapper: the key
// goes to To_ASCII as the caller's dword, the keyboard as an argument).
inline char Main_Loop_To_ASCII(WWKeyboardClass *keyboard, int key) { return keyboard->To_ASCII(key); }

// Westwood's always.h min (TibSun; Main_Loop's process time).
template <class T> T min(T a, T b)
{
    if (a < b) {
        return(a);
    } else {
        return(b);
    }
}

// For network and modem games, processes the key for inter-player messages (0x00540C20).
void __fastcall Message_Input(int &input);
// The WOL chat commands Message_Input tries on an internet message (unowned wonline units):
// a page ("/page <name> <text>"; 0: not one, 1: sent), an online command (nonzero: handled)
// and a reply to the last pager (0: not one, 1: sent).
int __fastcall Parse_Page_Command_00746480(unsigned short const *text);
int __fastcall Parse_Online_Command_00746240(unsigned short const *text);
int __fastcall Reply_To_Last_Pager_007466c0(unsigned short const *text);
// The last player who paged (narrow; 0x00B2AC48).
extern char unknown_last_pager_b2ac48[];
// The players Message_Input's chat goes to (0x00A6EBE0; set by the key that opened the edit line): 1 (Return)
// the houses marked in unknown_flags_a3f118, 2 (Backspace) the player's allies, 3 ('\\') every player; 0: none.
extern int unknown_chat_target_a6ebe0;
// Narrows a wide string into dst (at most limit characters; 0x006FA0F0; also shared/modem_guest.hpp).
void __fastcall Unknown_006FA0F0(char *dst, unsigned short const *src, int limit);

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
    MSTimerClass();                         // 0x005B6A00 (timeBeginPeriod(1))
    ~MSTimerClass();                        // 0x005B6A10 (timeEndPeriod(1))
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
void __fastcall Sync_Delay();

// Main_Loop (0x0053FBD0) state; names after TibSun's Session and Main_Loop (hypotheses).
extern unsigned long unknown_process_timer_a3d56c;   // 0x00A3D56C (Session.ProcessTimer)
extern int unknown_process_ticks_a3d570;             // 0x00A3D570 (Session.ProcessTicks)
extern int unknown_process_frames_a3d574;            // 0x00A3D574 (Session.ProcessFrames)
extern bool unknown_trap_check_heap_a40d1a;          // 0x00A40D1A (Debug_Trap_Check_Heap)
extern bool unknown_flag_a40b51;                     // 0x00A40B51 (picks the theme Main_Loop restarts)
extern int unknown_net_frame_delay_a6ebcc;           // 0x00A6EBCC (the network frame timer's time left)
extern bool unknown_flag_a40d45;                     // 0x00A40D45 (cleared once per frame; TibSun's drag_select_aborted)
extern int unknown_team_event_a6ebc4;                // 0x00A6EBC4 (TibSun's TeamEvent)
extern int unknown_team_number_a6ebc8;               // 0x00A6EBC8 (TibSun's TeamNumber)
extern bool unknown_flag_a6ebd0;                     // 0x00A6EBD0 (the scenario's save name is set once)
// The keyboard scroll distance (21) and its factor while a force-move key is held (2.5); this
// unit's first .data (0x007DFB70, 0x007DFB74).
extern int unknown_scroll_rate_7dfb70;
extern float unknown_scroll_factor_7dfb74;
extern int unknown_int_8325d0;                       // 0x008325D0
extern int unknown_int_8325d4;                       // 0x008325D4
class LayerClass;
extern LayerClass unknown_layers_852578[5];          // 0x00852578 (DisplayClass::Layer)
void unknown_delete_all_a76648();                    // 0x006142F0
void __fastcall Unknown_00614010();                             // 0x00614010
void Unknown_00482BC0();                             // 0x00482BC0 (Unselect_All, hypothesis)

// The value Multiplayer_Debug_Print shows in seconds when set (0x007EC498; -1: none).
extern unsigned int unknown_time_7ec498;

#endif
