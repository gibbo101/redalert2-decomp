// int __fastcall Player_Color_Combo_ID_4d1cb0(int player) (0x004D1CB0)
// The colour combo box id of a player row (0-7), -1 for any other value.
#include "shared/gdlg_supp.hpp"

int __fastcall Player_Color_Combo_ID_4d1cb0(int player)
{
    if (player == 0) {
        return 0x6A2;
    }
    if (player == 1) {
        return 0x522;
    }
    if (player == 2) {
        return 0x523;
    }
    if (player == 3) {
        return 0x524;
    }
    if (player == 4) {
        return 0x525;
    }
    if (player == 5) {
        return 0x526;
    }
    if (player == 6) {
        return 0x527;
    }
    if (player == 7) {
        return 0x528;
    }
    return -1;
}
