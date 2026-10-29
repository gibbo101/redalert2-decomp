// void __fastcall Unknown_0062E5C0(UnknownFrameTiming *their, int index) (0x0062E5C0): a player's frames behind.
#include "shared/queue.hpp"
// @ref ?Frame@@3HA=00a40d2c
// @ref __real@4@c004f000000000000000=007a867c
// @ref ?unknown_a3fb84@@3PAHA=00a3fb84
// @ref ?unknown_a3d568@@3HA=00a3d568
// @ref ?unknown_a402dc@@3IA=00a402dc
// @ref ?unknown_a6eb1c@@3IA=00a6eb1c
// @ref ?unknown_frame_send_rate_a3d564@@3IA=00a3d564
// @ref ?unknown_ipx_manager_a40978@@3VIPXManagerClass@@A=00a40978

void __fastcall Unknown_0062E5C0(UnknownFrameTiming *their, int index)
{
    long frame;
    unsigned int delay;

    if (unknown_game_mode_a3d298 != 4) {
        unknown_a3fb84[index] = 0;
        return;
    }
    frame = their[index].Frame;
    if (unknown_flag_a3fba8) {
        delay = (unsigned int)their[index].unknown_10 / 2 - (int)(-60.0f / (float)((double)unknown_a3d568 / unknown_frame_send_rate_a3d564)) / 2 + unknown_a402dc / 2;
    } else {
        delay = unknown_ipx_manager_a40978.unknown_slot22(index) / 2;
    }
    unknown_a3fb84[index] = ::Frame - delay * unknown_a6eb1c / 60 - frame;

}
