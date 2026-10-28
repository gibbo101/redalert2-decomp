// int __fastcall Color_Entry_Of_Combo_4d1fc0(int id) (0x004D1FC0)
// The colour table entry a player row's colour combo box holds, or -1.
#include "shared/gdlg_supp.hpp"
// @ref ?unknown_color_entries_8660d8@@3PAUUnknownColorEntry@@A=008660d8

int __fastcall Color_Entry_Of_Combo_4d1fc0(int id)
{
    int player = Color_Combo_Player_4d1d10(id);
    for (int index = 0; index < 9; index++) {
        if (unknown_color_entries_8660d8[index].Index == player) {
            return index;
        }
    }
    return -1;
}
