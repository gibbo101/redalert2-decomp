// void __fastcall Do_Lose_0065dec0() (0x0065DEC0)
// @ref ??0UnknownScore_005AAA20@@QAE@XZ=005aaa20
// @ref ??_C@_06LMML@TXT_NO?$AA@=007dfa64
// @ref ??_C@_07EALP@TXT_YES?$AA@=007dfa5c
// @ref ??_C@_0BE@DADK@D?3?2Ra2?2Scenario?4CPP?$AA@=007f1df0
// @ref ??_C@_0CP@HLKF@Toggling?5display?5mode?5back?5to?564@=007f1ed4
// @ref ??_C@_0O@GBIM@TXT_TO_REPLAY?$AA@=007f20c4
// @ref ??_C@_13ECNF@?$AA?5?$AA?$AA@=007d64f4
// @ref ?Presentation_005AAA40@UnknownScore_005AAA20@@QAEXXZ=005aaa40
// @ref ?Process@WWMessageBox@@QAEHPBG000_N@Z=005b46b0
// @ref ?Unknown_0053F780@@YIXXZ=0053f780
// @ref ?Unknown_005BC460@@YI_NXZ=005bc460
// @ref ?Unknown_00624850@@YIXXZ=00624850
// @ref ?Create_Connections@UnknownSessionState@@QAEHXZ=0066ee50
// @ref ?unknown_5159b0@@YIXH_N@Z=005159b0
// @ref ?unknown_a3f58c@@3HA=00a3f58c
// @ref ?unknown_a3f598@@3HA=00a3f598
// @ref ?unknown_a3d580@@3HA=00a3d580
// @ref ?unknown_flags_a3f600@@3EA=00a3f600
// @ref ?unknown_host_name_a3f618@@3PAGA=00a3f618
// The player lost (Westwood's Do_Lose, name hypothesis): stops the game time,
// closes the sidebar and the mouse, switches back to 640 x 480, fades out the
// sound and waits for the speech; in a networked game shows the score and asks
// the session whether to replay; in a campaign plays the Lose movie and asks
// "replay?". A replay restarts the scenario (re-creating the network transport
// for mode 3 with the computer players kept) and restores the checkpoint.
#include "shared/id_source.hpp"
#include "shared/session_state.hpp"
#include "shared/scenario_checkpoint.hpp"
#include "shared/system_timer.hpp"
#include "shared/t_timer.hpp"
#include "shared/comm_buffer.hpp"
#include "shared/tool_tip.hpp"
#include "shared/gscreen.hpp"
#include "shared/audio.hpp"
#include "shared/vox_class.hpp"
#include "shared/keyboard.hpp"
#include "shared/mouse.hpp"
#include "shared/map_view.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/string_table.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/crt_memory.hpp"
#include "shared/dsurface.hpp"

#define Max(a, b) ((a) < (b) ? (b) : (a))

void __fastcall Do_Lose_0065dec0()
{
    if (unknown_game_mode_a3d298 != 0 && unknown_game_mode_a3d298 != 5 && !(unknown_flags_a3f600 & 2)) {
        Unknown_00624850();
        Unknown_0053F780();
    }
    unknown_flag_a40d04 = false;
    unknown_flag_a40380 = false;
    unknown_id_source_a3d290->ElapsedTime.Stop();
    Unknown_005A09E0();
    WWMouse->Erase_Mouse(unknown_surface_839954, false);
    WWMouse->Release_Mouse();
    Map.Set_Default_Mouse(0, false);
    WWMouse->Hide_Mouse();
    Toggle_Display_Mode_0065c480(false);
    if (unknown_game_mode_a3d298 != 0) {
        unknown_host_name_a3f618[0] = 0;
    }
    Audio_Level_Fade_To_Zero(&Audio_Global_Levels[7]->Volume);
    Audio_Wait_Drain(&Audio_Global_Levels[7]->Volume);
    long end = TickCount.Time() + 300;
    while (Speech_Is_Playing() && end > TickCount.Time()) {
        Service_Game_IO_00481fb0();
    }
    Speech_Stop(true);
    Unknown_007160D0();
    Audio_Stop();
    Unknown_00714410();
    Audio_Global_Levels[7]->Volume.Set(0x4000);

    bool replay = false;
    if (unknown_game_mode_a3d298 != 0) {
        if (!(unknown_flags_a3f600 & 2)) {
            unknown_a3f58c++;
            if (unknown_session_a3d29c != 0) {
                if ((unknown_game_mode_a3d298 == 3 || unknown_game_mode_a3d298 == 4) && unknown_session_a3d29c->unknown_slot2()) {
                    unknown_5159b0(0, true);
                } else {
                    UnknownScore_005AAA20().Presentation_005AAA40();
                }
            } else {
                UnknownScore_005AAA20().Presentation_005AAA40();
            }
            if (unknown_session_a3d29c != 0) {
                replay = unknown_session_a3d29c->unknown_slot36();
            }
            unknown_a3f598++;
            if (unknown_a3f598 >= 4) {
                unknown_a3f598 = 3;
            }
        }
        if (!replay) {
            if (unknown_session_a3d29c != 0) {
                unknown_session_a3d29c->unknown_slot35(0);
            }
            unknown_flag_a40958 = false;
            return;
        }
        unknown_session_a3d29c->unknown_slot37();
    }
    Unknown_005A07F0(unknown_id_source_a3d290->LoseMovie, -1, 1, 1, 1);
    unknown_5159b0(0, true);
    if ((unknown_game_mode_a3d298 == 0 && !(unknown_flags_a3f600 & 2)
         && WWMessageBox(L" ").Process(
                StringTable::Load_String("TXT_TO_REPLAY", 0, "D:\\Ra2\\Scenario.CPP", 2612),
                StringTable::Load_String("TXT_YES", 0, "D:\\Ra2\\Scenario.CPP", 2612),
                StringTable::Load_String("TXT_NO", 0, "D:\\Ra2\\Scenario.CPP", 2612), 0, false) == 0)
        || replay) {
        if ((unknown_game_mode_a3d298 == 3 || unknown_game_mode_a3d298 == 4) && unknown_session_a3d29c != 0
            && unknown_session_a3d29c->unknown_slot2()) {
            if (unknown_game_mode_a3d298 == 3) {
                PacketTransport->Close_Socket();
                delete PacketTransport;
                PacketTransport = 0;
                PacketTransport = new IPXInterfaceClass;
            }
            PacketTransport->Init();
            int ai_count = unknown_session_a3d298.AICount;
            int colors[8];
            int countries[8];
            int difficulties[8];
            memcpy(colors, unknown_session_a3d298.AIColor, sizeof(colors));
            memcpy(countries, unknown_session_a3d298.AICountry, sizeof(countries));
            memcpy(difficulties, unknown_session_a3d298.AIDifficulty, sizeof(difficulties));
            if (!Unknown_005BC460()) {
                if (PacketTransport != 0) {
                    delete PacketTransport;
                    PacketTransport = 0;
                }
                unknown_flag_a40958 = false;
                return;
            }
            unknown_session_a3d298.AICount = ai_count;
            for (int index = 0; index < 8; index++) {
                unknown_session_a3d298.AIDifficulty[index] = difficulties[index];
                unknown_session_a3d298.AICountry[index] = countries[index];
                unknown_session_a3d298.AIColor[index] = colors[index];
            }
            WWKeyboard->Clear();
        }
        Start_Scenario_0065bc70(unknown_id_source_a3d290->FileName, false, unknown_id_source_a3d290->unknown_224c);
        if ((unknown_game_mode_a3d298 == 3 || unknown_game_mode_a3d298 == 4) && unknown_session_a3d29c != 0
            && unknown_session_a3d29c->unknown_slot2()) {
            unknown_session_a3d298.Create_Connections();
            if (unknown_game_mode_a3d298 == 3) {
                unknown_ipx_manager_a40978.Set_Timing(Max(unknown_ipx_manager_a40978.unknown_526c30() + 2, 15), -1, 600, true);
                unknown_ipx_manager_a40978.unknown_slot14(Max(unknown_ipx_manager_a40978.unknown_526c30() + 2, 60), -1, 600);
            } else if (unknown_game_mode_a3d298 == 4 && unknown_a3d580 == 0) {
                unknown_ipx_manager_a40978.Set_Timing(Max(unknown_ipx_manager_a40978.unknown_526c30() + 2, 60), -1, 600, true);
            }
        }
        unknown_scenario_checkpoint_00855a90.Restore_004B5B40();
        if (ToolTips != 0) {
            ToolTips->Enable(unknown_tooltips_enabled_a40b34);
        }
        Map.Render();
        return;
    }
    unknown_flag_a40958 = false;
}
