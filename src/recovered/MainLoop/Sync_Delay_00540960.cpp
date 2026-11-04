// void Sync_Delay() (0x00540960; Westwood's Sync_Delay)
#include "shared/main_loop.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/queue.hpp"
#include "shared/gscreen.hpp"
#include "shared/map_view.hpp"
#include "shared/tactical.hpp"
#include "shared/win32_api.hpp"
// @ref ?unknown_frame_timer_839990@@3V?$CDTimerClass@VSystemTimerClass@@@@A=00839990
// @ref ?unknown_net_frame_timer_839970@@3V?$CDTimerClass@VMSTimerClass@@@@A=00839970
// @ref ??BMSTimerClass@@QBEJXZ=005b6a20
// @ref ?unknown_spare_ticks_a4031c@@3HA=00a4031c
// @ref ?unknown_frames_this_second_a6eb18@@3IA=00a6eb18
// @ref ?Wait_For_Surface_Blit_004961d0@@YAJXZ=004961d0
// @ref _atexit=0078298a
// @ref _?$S73@?BJ@??Sync_Delay@@YIXXZ@4EA=00a6eb81
// @ref _?fps_timer@?BJ@??Sync_Delay@@YIXXZ@4V?$CDTimerClass@VSystemTimerClass@@@@A=00a6eb60

void __fastcall Sync_Delay()
{
    unknown_spare_ticks_a4031c += unknown_frame_timer_839990.Value();
    if (unknown_game_mode_a3d298 != 0 && unknown_game_mode_a3d298 != 5) {
        while (unknown_net_frame_timer_839970.Value()) {
            Service_Game_IO_00481fb0();
            if (unknown_int_a40d48 == 0 && unknown_flag_a40d28 == true) {
                int input = 0;
                int x;
                int y;
                if (unknown_net_frame_timer_839970.Value() > 10) {
                    Map.Get_Input(input, x, y);
                    Keyboard_Process(input);
                    unknown_tactical_83996c->AI();
                    Map.Render();
                } else {
                    Sleep(0);
                }
                if (!unknown_net_frame_timer_839970.Value()) {
                    break;
                }
            }
            Sleep(0);
        }
    } else {
        if (unknown_frame_timer_839990.Value()) {
            Wait_For_Surface_Blit_004961d0();
            while (unknown_frame_timer_839990.Value()) {
                Sleep(unknown_frame_timer_839990.Value());
            }
        }
    }

    static CDTimerClass<SystemTimerClass> fps_timer;
    if (!fps_timer) {
        unknown_a6eb1c = unknown_frames_this_second_a6eb18;
        unknown_frames_this_second_a6eb18 = 0;
        accumulated_fps_00a6eb20 += unknown_a6eb1c;
        fps_sample_count_00a6eb24++;
        if (accumulated_fps_00a6eb20 > 0x7FFFFFFF) {
            accumulated_fps_00a6eb20 = 0;
            fps_sample_count_00a6eb24 = 0;
        }
        fps_timer = 60;
    }
}
