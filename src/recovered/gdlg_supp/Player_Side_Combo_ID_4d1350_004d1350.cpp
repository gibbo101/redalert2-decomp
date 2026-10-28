// int __fastcall Player_Side_Combo_ID_4d1350(int player) (0x004D1350)
// The side combo box id of a player row (0-7), -1 for any other value.
#include "shared/gdlg_supp.hpp"

int __fastcall Player_Side_Combo_ID_4d1350(int player)
{
    if (player == 0) {
        return 0x6A1;
    }
    if (player == 1) {
        return 0x510;
    }
    if (player == 2) {
        return 0x513;
    }
    if (player == 3) {
        return 0x51E;
    }
    if (player == 4) {
        return 0x514;
    }
    if (player == 5) {
        return 0x51F;
    }
    if (player == 6) {
        return 0x520;
    }
    if (player == 7) {
        return 0x521;
    }
    return -1;
}
