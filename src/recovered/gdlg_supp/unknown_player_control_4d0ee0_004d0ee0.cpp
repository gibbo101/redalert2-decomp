// int __fastcall unknown_player_control_4d0ee0(int player) (0x004D0EE0)
// A player row's control id (0x6DA-0x6E1; meaning not recovered), -1 for any other value.
#include "shared/gdlg_supp.hpp"

int __fastcall unknown_player_control_4d0ee0(int player)
{
    if (player == 0) {
        return 0x6DA;
    }
    if (player == 1) {
        return 0x6DB;
    }
    if (player == 2) {
        return 0x6DC;
    }
    if (player == 3) {
        return 0x6DD;
    }
    if (player == 4) {
        return 0x6DE;
    }
    if (player == 5) {
        return 0x6DF;
    }
    if (player == 6) {
        return 0x6E0;
    }
    if (player == 7) {
        return 0x6E1;
    }
    return -1;
}
