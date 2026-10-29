// int __fastcall Handle_Timeout(ConnManClass *net, UnknownFrameTiming *their) (0x00627910): reconnect a modem game or kick the oldest network player.
#include "shared/queue.hpp"
// @ref ?Reconnect_Modem@@YA_NXZ=005ceb40
// @ref ?Kick_Player_Now@@YIXPAVConnManClass@@HPAUUnknownFrameTiming@@E@Z=00627740

int __fastcall Handle_Timeout(ConnManClass *net, UnknownFrameTiming *their)
{
    int oldest_index;
    int i, j;

    if (unknown_game_mode_a3d298 == 1 || unknown_game_mode_a3d298 == 2) {
        if (net->Num_Connections()) {
            unknown_counter_a3fabc++;
            if (!Reconnect_Modem()) {
                unknown_counter_a3fabc--;
                return 0;
            }
            unknown_counter_a3fabc--;
            return 1;
        }
    } else if (unknown_game_mode_a3d298 == 3 || unknown_game_mode_a3d298 == 4) {
        j = 0x7FFFFFFF;
        oldest_index = 0;
        for (i = 0; i < net->Num_Connections(); i++) {
            if (their[i].Frame < j) {
                j = their[i].Frame;
                oldest_index = i;
            }
        }
        Kick_Player_Now(net, oldest_index, their, 1);
    }
    return 1;
}
