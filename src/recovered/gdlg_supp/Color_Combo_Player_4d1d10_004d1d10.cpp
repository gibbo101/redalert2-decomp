// int __fastcall Color_Combo_Player_4d1d10(int id) (0x004D1D10)
// The player row of a colour combo box id (the inverse of 0x004D1CB0), or -1.
#include "shared/gdlg_supp.hpp"

int __fastcall Color_Combo_Player_4d1d10(int id)
{
    if (id == 0x6A2) {
        return 0;
    }
    if (id == 0x522) {
        return 1;
    }
    if (id == 0x523) {
        return 2;
    }
    if (id == 0x524) {
        return 3;
    }
    if (id == 0x525) {
        return 4;
    }
    if (id == 0x526) {
        return 5;
    }
    if (id == 0x527) {
        return 6;
    }
    if (id == 0x528) {
        return 7;
    }
    return -1;
}
