// bool Main_Loop_End_0053f840() (0x0053F840): the end of Westwood's Main_Loop.
// This unit declares UnknownSessionA3D29C slot 34 with its argument (shared/unknown_globals.hpp).
#define UNKNOWN_SESSION_DECLARE_SLOT34_ARG
#include "shared/main_loop.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/event.hpp"
#include "shared/house.hpp"
#include "shared/id_source.hpp"
#include "shared/session_state.hpp"
#include "shared/tool_tip.hpp"
#include "shared/queue.hpp"
#include "shared/gscreen.hpp"
// @ref ?player_wins_a35db1@@3_NA=00a35db1
// @ref ?player_loses_a40c78@@3_NA=00a40c78
// @ref ?player_restarts_866250@@3_NA=00866250
// @ref ?player_aborts_a35db0@@3_NA=00a35db0
// @ref ?unknown_a3fabc@@3HA=00a3fabc
// @ref ?unknown_main_loop_flag_a6eb30@@3_NA=00a6eb30
// @ref ?Unknown_Reload_Art_Set_006F31B0@@YIXXZ=006f31b0
// @ref ??_H@YGXPAXIHP6EX0@Z@Z=0040aed0
// @ref ??_C@_0BH@NLBJ@Disconnect_Gracefully?6?$AA@=007dfb84

bool __fastcall Main_Loop_End_0053f840()
{
    if ((Frame & 0x3FF) == 0 && !Unknown_00491A10()) {
        OutList.Add(EventClass(unknown_player_a35db4->ArrayIndex, 8));
    }
    if (player_wins_a35db1 || player_loses_a40c78 || player_restarts_866250 || player_aborts_a35db0) {
        unknown_a3fabc++;
        Pause_Game_0065c3d0();
        if (player_wins_a35db1 || player_loses_a40c78) {
            if (ToolTips != 0) {
                ToolTips->Enable(false);
            }
        }
        if (player_wins_a35db1 || player_loses_a40c78) {
            if (unknown_session_a3d29c != 0 && (unknown_game_mode_a3d298 == 3 || unknown_game_mode_a3d298 == 4)) {
                unknown_session_a3d29c->unknown_slot34(player_wins_a35db1);
            }
        }
        if (player_wins_a35db1) {
            if (unknown_game_mode_a3d298 == 4 && !unknown_flag_a417c8) {
                if (unknown_b2a7ec != 0) {
                    unknown_flag_a3d8d1 = true;
                }
                Unknown_0069A160();
                Unknown_00698D00(false);
            }
            player_loses_a40c78 = false;
            player_wins_a35db1 = false;
            player_restarts_866250 = false;
            player_aborts_a35db0 = false;
            Unknown_Reload_Art_Set_006F31B0();
            unknown_session_a3d298.Unknown_00672E70();
            Do_Win_0065d7f0();
            unknown_session_a3d298.Unknown_00672DE0();
            unknown_main_loop_flag_a6eb30 = false;
            if (ToolTips != 0) {
                ToolTips->Enable(unknown_tooltips_enabled_a40b34);
            }
        } else if (player_loses_a40c78) {
            if (unknown_game_mode_a3d298 == 4 && !unknown_flag_a417c8) {
                if (unknown_b2a7ec != 0) {
                    unknown_flag_a3d8d1 = true;
                }
                Unknown_0069A160();
                Unknown_00698D00(false);
            }
            player_wins_a35db1 = false;
            player_loses_a40c78 = false;
            player_restarts_866250 = false;
            player_aborts_a35db0 = false;
            Unknown_Reload_Art_Set_006F31B0();
            unknown_session_a3d298.Unknown_00672E70();
            Do_Lose_0065dec0();
            unknown_session_a3d298.Unknown_00672DE0();
            unknown_main_loop_flag_a6eb30 = false;
            if (ToolTips != 0) {
                ToolTips->Enable(unknown_tooltips_enabled_a40b34);
            }
        } else if (player_restarts_866250) {
            player_wins_a35db1 = false;
            player_loses_a40c78 = false;
            player_restarts_866250 = false;
            player_aborts_a35db0 = false;
            unknown_session_a3d298.Unknown_00672E70();
            Do_Restart_0065e440();
            unknown_session_a3d298.Unknown_00672DE0();
            unknown_main_loop_flag_a6eb30 = false;
        } else if (player_aborts_a35db0) {
            player_wins_a35db1 = false;
            player_loses_a40c78 = false;
            player_restarts_866250 = false;
            player_aborts_a35db0 = false;
            Unknown_Reload_Art_Set_006F31B0();
            unknown_session_a3d298.Unknown_00672E70();
            Unknown_0065e590();
            unknown_session_a3d298.Unknown_00672DE0();
            unknown_main_loop_flag_a6eb30 = false;
            Unknown_0053F780();
        }
        unknown_a3fabc--;
    }
    return !unknown_flag_a40958;
}
