// bool __fastcall unknown_53fbd0() (0x0053FBD0; Westwood's Main_Loop): one game frame; true when
// the game is over or a player flag ends it (0x0053F840 then runs the end-of-game handlers).
// This unit declares UnknownSessionA3D29C slot 34 with its argument (shared/unknown_globals.hpp).
#define UNKNOWN_SESSION_DECLARE_SLOT34_ARG
#include "shared/main_loop.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/win32_api.hpp"
#include "shared/msgloop.hpp"
#include "shared/session_state.hpp"
#include "shared/id_source.hpp"
#include "shared/theme.hpp"
#include "shared/sound_available.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/gscreen.hpp"
#include "shared/map_view.hpp"
#include "shared/tactical.hpp"
#include "shared/target.hpp"
#include "shared/object.hpp"
#include "shared/layer.hpp"
#include "shared/unknown_list_832470.hpp"
#include "shared/fogged_object.hpp"
#include "shared/keyboard.hpp"
#include "shared/queue.hpp"
#include "shared/load_dlg.hpp"
#include "shared/crt_string.hpp"
#include "shared/techno.hpp"
// @ref ?unknown_53fbd0@@YI_NXZ=0053fbd0
// @ref ??_C@_04IHGP@?4sav?$AA@=007dfba8
// @ref ??_C@_19GFJK@?$AA?$FL?$AA?$CF?$AAs?$AA?$FN?$AA?$AA@=007dfb9c
// @ref ??0MSTimerClass@@QAE@XZ=005b6a00
// @ref ??1MSTimerClass@@QAE@XZ=005b6a10
// @ref ??BMSTimerClass@@QBEJXZ=005b6a20
// @ref ?Queue_AI@@YIXXZ=00623770
// @ref ?Sync_Delay@@YIXXZ=00540960
// @ref ?Trap_Object_006715c0@UnknownSessionState@@QAEXXZ=006715c0
// @ref ?Unknown_0053D890@UnknownList832470@@QAEXXZ=0053d890
// @ref ?Unknown_00614010@@YAXXZ=00614010
// @ref ?Unknown_006A67B0@Tactical@@QAE?AUPoint2D@@XZ=006a67b0
// @ref ?unknown_flag_a40b51@@3_NA=00a40b51
// @ref ?unknown_frame_timer_839990@@3V?$CDTimerClass@VSystemTimerClass@@@@A=00839990
// @ref ?unknown_int_8325d4@@3HA=008325d4
// @ref ?unknown_layers_852578@@3PAVLayerClass@@A=00852578
// @ref ?unknown_net_frame_delay_a6ebcc@@3HA=00a6ebcc
// @ref ?unknown_net_frame_timer_839970@@3V?$CDTimerClass@VMSTimerClass@@@@A=00839970
// @ref ?unknown_process_frames_a3d574@@3HA=00a3d574
// @ref ?unknown_process_ticks_a3d570@@3HA=00a3d570
// @ref ?unknown_process_timer_a3d56c@@3KA=00a3d56c
// @ref ?unknown_scroll_factor_7dfb74@@3MA=007dfb74
// @ref ?unknown_scroll_keys_a6ebdc@@3HA=00a6ebdc
// @ref ?unknown_scroll_rate_7dfb70@@3HA=007dfb70
// @ref ?unknown_slot41@DisplayClass@@QAE_NHPAH_N@Z=00499b60
// @ref ?unknown_team_event_a6ebc4@@3HA=00a6ebc4
// @ref ?unknown_team_number_a6ebc8@@3HA=00a6ebc8
// @ref ?unknown_trap_check_heap_a40d1a@@3_NA=00a40d1a

extern "C" char *__cdecl strrchr(char const *string, int character);
extern "C" int __cdecl swprintf(wchar_t *buffer, wchar_t const *format, ...);

static inline void Do_Record_Playback()
{
    int count;
    int tgt;
    int i;
    Point2D coord;
    ObjectClass *obj;
    unsigned int sum;
    unsigned int sum2;
    unsigned int ltgt;

    if (unknown_session_a3d298.Record) {
        coord = unknown_tactical_83996c->Unknown_006A67B0();
        unknown_session_a3d298.RecordFile.Write(&coord, sizeof(coord));

        count = unknown_objects_a40c60.Count();
        unknown_session_a3d298.RecordFile.Write(&count, sizeof(count));

        sum = 0;
        for (i = 0; i < count; i++) {
            ltgt = TargetClass(unknown_objects_a40c60[i]).Encode();
            sum += ltgt;
        }
        unknown_session_a3d298.RecordFile.Write(&sum, sizeof(sum));

        for (i = 0; i < count; i++) {
            tgt = TargetClass(unknown_objects_a40c60[i]).Encode();
            unknown_session_a3d298.RecordFile.Write(&tgt, sizeof(tgt));
        }

        unknown_session_a3d298.RecordFile.Write(&unknown_team_event_a6ebc4, sizeof(unknown_team_event_a6ebc4));
        unknown_session_a3d298.RecordFile.Write(&unknown_team_number_a6ebc8, sizeof(unknown_team_number_a6ebc8));
        unknown_team_event_a6ebc4 = 0;
        unknown_team_number_a6ebc8 = 0;
    }

    if (unknown_session_a3d298.Play) {
        if (unknown_session_a3d298.RecordFile.Read(&coord, sizeof(coord)) == sizeof(coord)) {
            unknown_tactical_83996c->Unknown_006A6640(coord);
        }

        if (unknown_session_a3d298.RecordFile.Read(&count, sizeof(count)) == sizeof(count)) {
            sum = 0;
            for (i = 0; i < unknown_objects_a40c60.Count(); i++) {
                ltgt = TargetClass(unknown_objects_a40c60[i]).Encode();
                sum += ltgt;
            }

            unknown_session_a3d298.RecordFile.Read(&sum2, sizeof(sum2));
            if (sum2 != sum) {
                Unknown_00482BC0();
            }

            unknown_sound_enabled_7d88d6 = true;

            for (i = 0; i < count; i++) {
                if (unknown_session_a3d298.RecordFile.Read(&tgt, sizeof(tgt)) == sizeof(tgt)) {
                    TargetClass tmp;
                    tmp.Decode(tgt);
                    obj = tmp.As_Object();
                    if (obj && (sum2 != sum)) {
                        obj->unknown_slot80();
                        unknown_sound_enabled_7d88d6 = false;
                    }
                }
            }

            unknown_sound_enabled_7d88d6 = true;
        }

        unknown_session_a3d298.RecordFile.Read(&unknown_team_event_a6ebc4, sizeof(unknown_team_event_a6ebc4));
        unknown_session_a3d298.RecordFile.Read(&unknown_team_number_a6ebc8, sizeof(unknown_team_number_a6ebc8));

        Map.Flag_To_Redraw();
        Map.Render();
    }
}

bool __fastcall unknown_53fbd0()
{
    int input;
    int y;
    int x;

    if (!unknown_flag_a40958) {
        return !unknown_flag_a40958;
    }

    unknown_main_loop_flag_a6eb30 = true;

    while (!unknown_flag_a40d28) {
        if (unknown_session_a3d298.Type == 0 || unknown_session_a3d298.Type == 5) {
            Sleep(500);
            Windows_Message_Handler();
        } else {
            Sleep(10);
            Windows_Message_Handler();
            break;
        }
    }

    if (Frame >= unknown_session_a3d298.TrapFrame) {
        unknown_session_a3d298.Trap_Object_006715c0();
    }

    unknown_process_timer_a3d56c = timeGetTime();

    if (unknown_session_a3d298.TrapCheckHeap) {
        unknown_trap_check_heap_a40d1a = true;
    }

    if (unknown_flag_a40380 == true && unknown_check_406f30()) {
        int theme = Theme.Score;
        if (theme == -1) {
            theme = Theme.Pending;
        }
        if (unknown_flag_a40b51) {
            if (theme == -1) {
                Theme.Queue_Song(-2);
            }
        } else if (theme != -3) {
            Theme.Stop(true);
            Theme.Queue_Song(-3);
        }
    }

    if (unknown_session_a3d298.Type != 0 && unknown_session_a3d298.Type != 5 && unknown_session_a3d2ac == 2) {
        if (unknown_session_a3d298.Play) {
            unknown_frame_timer_839990 = 0;
        } else {
            if (unknown_a3d568 == 0) {
                unknown_frame_timer_839990 = 2;
                unknown_net_frame_timer_839970 = 33;
            } else {
                unknown_frame_timer_839990 = 60 / unknown_a3d568;
                unknown_net_frame_timer_839970 = 1000 / unknown_a3d568;
            }
            unknown_net_frame_delay_a6ebcc = unknown_net_frame_timer_839970;

            int maxahead = unknown_max_ahead_a3d560;
            int worst_latency = 0;
            if (unknown_session_a3d298.Type == 4) {
                if (maxahead > 30) {
                    for (int i = 0; i < unknown_ipx_manager_a40978.Num_Connections(); i++) {
                        if (worst_latency <= unknown_a3fb84[i]) {
                            worst_latency = unknown_a3fb84[i];
                        }
                    }
                    if (worst_latency) {
                        if (worst_latency >= maxahead / 4) {
                            unknown_net_frame_timer_839970 = unknown_net_frame_timer_839970 + 10;
                        }
                        if (worst_latency >= maxahead / 2) {
                            unknown_net_frame_timer_839970 = unknown_net_frame_timer_839970 + 10;
                        }
                        if (worst_latency >= (3 * maxahead) / 4) {
                            unknown_net_frame_timer_839970 = unknown_net_frame_timer_839970 + 10;
                        }
                    }
                }
            }
        }
    } else if (unknown_session_a3d298.Type == 0 && !unknown_flag_a40d84) {
        unknown_a40b18 = 2;
        unknown_frame_timer_839990 = 2;
    } else {
        unknown_frame_timer_839990 = unknown_a40b18;
    }

    if (unknown_session_a3d298.Type == 0) {
        if (unknown_id_source_a3d290->unknown_630 && unknown_id_source_a3d290->unknown_620.Value() <= 0) {
            unknown_id_source_a3d290->unknown_630 = false;
            Release_Pause_0065c310();
        }
        if (unknown_id_source_a3d290->unknown_62c) {
            Windows_Message_Handler();
            Service_Game_IO_00481fb0();
            unknown_tactical_83996c->AI();
            Map.Render();
            Sync_Delay();
            unknown_main_loop_flag_a6eb30 = false;
            return !unknown_flag_a40958;
        }
    }

    if (!unknown_session_a3d298.Play) {
        if (unknown_int_a40d48 == 0 && unknown_flag_a40d28) {
            Map.Get_Input(input, x, y);
            Keyboard_Process(input);
            if (unknown_flag_a3d8c4) {
                Unknown_005419E0(false);
            }
            if ((Frame & 7) == 7 && unknown_session_a3d298.Type == 4) {
                unknown_ipx_manager_a40978.Store_Stats();
            }
            FoggedObjectClass::unknown_4c1ae0();
            Map.Render();
        }
    }

    unknown_flag_a40d45 = false;

    if (unknown_session_a3d298.Record || unknown_session_a3d298.Play) {
        Do_Record_Playback();
    }

    unknown_layers_852578[2].Sort();

    if (unknown_session_a3d298.Type == 0 && !unknown_flag_a6ebd0) {
        wchar_t description[56];
        char name[261];
        unknown_flag_a6ebd0 = true;
        strcpy(name, unknown_id_source_a3d290->FileName);
        name[260] = '\0';
        char *dot = strrchr(name, '.');
        if (dot != 0) {
            *dot = '\0';
        }
        strcat(name, ".sav");
        swprintf(description, L"[%s]", unknown_id_source_a3d290->Name);
        Unknown_006554A0(name, description, 0);
    }

    unknown_list_832470.Unknown_0053D890();

    int scroll = unknown_scroll_rate_7dfb70;
    if (Main_Loop_Key_Down(KeyForceMove1) || Main_Loop_Key_Down(KeyForceMove2)) {
        scroll = scroll * unknown_scroll_factor_7dfb74;
    } else if (Main_Loop_Key_Down(KeyForceFire1) || Main_Loop_Key_Down(KeyForceFire2)) {
        scroll = unknown_int_8325d0 > unknown_int_8325d4 ? unknown_int_8325d0 : unknown_int_8325d4;
        scroll <<= 8;
    }
    if (unknown_scroll_keys_a6ebdc & 0x100) {
        Map.unknown_slot41(6, &scroll, true);
    }
    if (unknown_scroll_keys_a6ebdc & 0x1000) {
        Map.unknown_slot41(2, &scroll, true);
    }
    if (unknown_scroll_keys_a6ebdc & 0x01) {
        Map.unknown_slot41(0, &scroll, true);
    }
    if (unknown_scroll_keys_a6ebdc & 0x10) {
        Map.unknown_slot41(4, &scroll, true);
    }

    unknown_delete_all_a76648();
    unknown_session_a3d298.Messages.Update_Messages();

    unknown_process_ticks_a3d570 += min<int>(1000, timeGetTime() - unknown_process_timer_a3d56c);
    unknown_process_frames_a3d574++;

    Queue_AI();
    unknown_delete_all_a76648();
    Service_Game_IO_00481fb0();

    if (!player_wins_a35db1 && !player_loses_a40c78 && !player_restarts_866250 && !player_aborts_a35db0) {
        Frame++;
        if (unknown_ab9174 != 0 && unknown_ab9174 < Frame) {
            Resume_Game_0065c420();
            unknown_ab9174 = 0;
        }
        Sync_Delay();
        Unknown_006ecf10();
        Unknown_00614010();
        unknown_main_loop_flag_a6eb30 = false;
        return !unknown_flag_a40958;
    }

    unknown_main_loop_flag_a6eb30 = false;
    return true;
}
