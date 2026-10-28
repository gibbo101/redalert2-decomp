// void __fastcall Color_Combo_Changed_4d2700(HWND dialog, int id) (0x004D2700)
// A row's colour selection changed: the row gives up the colour it held,
// takes the selected one (unless it is random, -2), and every row's colour
// list is refilled.
#include "shared/gdlg_supp.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/unknown_player_entry.hpp"
// @ref __imp__SendDlgItemMessageA@20=0079a484
// @ref ?unknown_color_entries_8660d8@@3PAUUnknownColorEntry@@A=008660d8
// @ref ?Fill_Color_Combo_4d2080@@YIXPAUHWND__@@H@Z=004d2080

void __fastcall Color_Combo_Changed_4d2700(HWND dialog, int id)
{
    int entry = Color_Entry_Of_Combo_4d1fc0(id);
    if (entry != -1) {
        unknown_color_entries_8660d8[entry].Index = -1;
    }
    int color = Color_Combo_Data_4d2900(dialog, id, -1);
    int player = Color_Combo_Player_4d1d10(id);
    if (color != -2) {
        unknown_color_entries_8660d8[color].Index = player;
    }
    Fill_Color_Combos_4d2300(dialog);
}
