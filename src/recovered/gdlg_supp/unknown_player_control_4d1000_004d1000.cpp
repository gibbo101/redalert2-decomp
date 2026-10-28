// int __fastcall unknown_player_control_4d1000(int player) (0x004D1000)
// A player row's control id (0x754-0x75B; meaning not recovered), -1 for any other value.
#include "shared/gdlg_supp.hpp"

int __fastcall unknown_player_control_4d1000(int player)
{
    if (player == 0) {
        return 0x754;
    }
    if (player == 1) {
        return 0x755;
    }
    if (player == 2) {
        return 0x756;
    }
    if (player == 3) {
        return 0x757;
    }
    if (player == 4) {
        return 0x758;
    }
    if (player == 5) {
        return 0x759;
    }
    if (player == 6) {
        return 0x75A;
    }
    if (player == 7) {
        return 0x75B;
    }
    return -1;
}
