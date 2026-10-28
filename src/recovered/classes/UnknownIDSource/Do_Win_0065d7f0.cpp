// void __fastcall Do_Win_0065d7f0() (0x0065D7F0)
// @ref ??0UnknownScore_005AAA20@@QAE@XZ=005aaa20
// @ref ??0UnknownScore_0069A640@@QAE@XZ=0069a640
// @ref ??_C@_0CP@HLKF@Toggling?5display?5mode?5back?5to?564@=007f1ed4
// @ref ?Presentation_005AAA40@UnknownScore_005AAA20@@QAEXXZ=005aaa40
// @ref ?Presentation_0069A650@UnknownScore_0069A640@@QAEXXZ=0069a650
// @ref ?Unknown_00491A10@@YI_NXZ=00491a10
// @ref ?Unknown_004B37C0@@YIXXZ=004b37c0
// @ref ?Unknown_0053F780@@YIXXZ=0053f780
// @ref ?Unknown_0058F510@@YIXPAVUnknownIDSource@@@Z=0058f510
// @ref ?Unknown_0058F620@@YIXPAVUnknownIDSource@@PBD@Z=0058f620
// @ref ?Unknown_005BC460@@YI_NXZ=005bc460
// @ref ?Unknown_00624850@@YIXXZ=00624850
// @ref ?Unknown_0066EE50@UnknownSessionState@@QAEXXZ=0066ee50
// @ref ?unknown_5159b0@@YIXH_N@Z=005159b0
// @ref ?unknown_a3f58c@@3HA=00a3f58c
// @ref ?unknown_a3f598@@3HA=00a3f598
// @ref ?unknown_a3d580@@3HA=00a3d580
// @ref ?unknown_host_name_a3f618@@3PAGA=00a3f618
// @ref ?unknown_flags_a3f600@@3EA=00a3f600
// The player won (Westwood's Do_Win, name hypothesis): stops the game as Do_Lose
// does; in a networked game shows the score and asks the session whether to go
// on; plays the Win movie and (unless option bit 1) the score, the PostScore and
// PreMapSelect movies, then ends the campaign or picks the next scenario (map
// selection or NextScenario/AltNextScenario by variable 1); checkpoints the
// scenario state, raises +0x834 and starts the next scenario.
#include "shared/id_source.hpp"
#include "shared/unknown_globals.hpp"
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
#include "shared/campaign.hpp"
#include "shared/dsurface.hpp"

#define Max(a, b) ((a) < (b) ? (b) : (a))

void __fastcall Do_Win_0065d7f0()
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

    Toggle_Display_Mode_0065c480(false);

    if (unknown_game_mode_a3d298 != 0) {
        bool next = false;
        unknown_host_name_a3f618[0] = 0;
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
                next = unknown_session_a3d29c->unknown_slot36();
            }
            unknown_a3f598++;
            if (unknown_a3f598 >= 4) {
                unknown_a3f598 = 3;
            }
        }
        if (!next) {
            if (unknown_session_a3d29c != 0) {
                unknown_session_a3d29c->unknown_slot35(1);
            }
            unknown_flag_a40958 = false;
            return;
        }
        unknown_session_a3d29c->unknown_slot37();
    }
    Unknown_005A07F0(unknown_id_source_a3d290->WinMovie, -1, 1, 1, 1);
    if (!(unknown_flags_a3f600 & 2)) {
        WWKeyboard->Clear();
        if (!unknown_id_source_a3d290->SkipScore) {
            UnknownScore_0069A640().Presentation_0069A650();
        }
        if (unknown_id_source_a3d290->PostScoreMovie != -1) {
            Unknown_005A07F0(unknown_id_source_a3d290->PostScoreMovie, -1, 1, 1, 1);
        }
        if (unknown_id_source_a3d290->PreMapSelectMovie != -1) {
            Unknown_005A07F0(unknown_id_source_a3d290->PreMapSelectMovie, -1, 1, 1, 1);
        }
        if (!Unknown_00491A10() || unknown_id_source_a3d290->OneTimeOnly) {
            unknown_flag_a40958 = false;
            WWMouse->Show_Mouse();
            return;
        }
        if (unknown_id_source_a3d290->EndOfGame) {
            if (unknown_id_source_a3d290->unknown_224c != -1) {
                Unknown_005A07F0(Campaigns[unknown_id_source_a3d290->unknown_224c]->unknown_29c, -1, 1, 1, 1);
            }
            Unknown_004B37C0();
            unknown_flag_a40958 = false;
            WWMouse->Show_Mouse();
            return;
        }
        if (!((unknown_game_mode_a3d298 == 3 || unknown_game_mode_a3d298 == 4) && unknown_session_a3d29c != 0
              && unknown_session_a3d29c->unknown_slot2())) {
            if (unknown_id_source_a3d290->SkipMapSelect) {
                if (unknown_id_source_a3d290->Variables[1].Value) {
                    Unknown_0058F620(unknown_id_source_a3d290, unknown_id_source_a3d290->AltNextScenario);
                } else {
                    Unknown_0058F620(unknown_id_source_a3d290, unknown_id_source_a3d290->NextScenario);
                }
            } else {
                WWMouse->Show_Mouse();
                Unknown_0058F510(unknown_id_source_a3d290);
                WWMouse->Hide_Mouse();
            }
        }
        WWKeyboard->Clear();
    }
    WWMouse->Show_Mouse();
    unknown_scenario_checkpoint_00855a90.Capture_004B5AB0();
    unknown_id_source_a3d290->TechLevel++;
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
    unknown_flag_a40958 = Unknown_00491A10();
    if (!unknown_flag_a40958) {
        WWMouse->Show_Mouse();
        return;
    }
    Start_Scenario_0065bc70(unknown_id_source_a3d290->FileName, true, unknown_id_source_a3d290->unknown_224c);
    if ((unknown_game_mode_a3d298 == 3 || unknown_game_mode_a3d298 == 4) && unknown_session_a3d29c != 0
        && unknown_session_a3d29c->unknown_slot2()) {
        unknown_session_a3d298.Unknown_0066EE50();
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
    Unknown_004955D0(&unknown_palette_837e10, 7, unknown_481fb0);
}
