// int __fastcall Side_Combo_Player_4d13b0(int id) (0x004D13B0)
// The player row of a side combo box id (the inverse of 0x004D1350), or -1.
#include "shared/gdlg_supp.hpp"

int __fastcall Side_Combo_Player_4d13b0(int id)
{
    if (id == 0x6A1) {
        return 0;
    }
    if (id == 0x510) {
        return 1;
    }
    if (id == 0x513) {
        return 2;
    }
    if (id == 0x51E) {
        return 3;
    }
    if (id == 0x514) {
        return 4;
    }
    if (id == 0x51F) {
        return 5;
    }
    if (id == 0x520) {
        return 6;
    }
    if (id == 0x521) {
        return 7;
    }
    return -1;
}
