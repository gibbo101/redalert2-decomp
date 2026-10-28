// bool __fastcall Color_Entry_Taken_4d2060(int entry) (0x004D2060)
// Whether a colour table entry is held by a player row.
#include "shared/gdlg_supp.hpp"
// @ref ?unknown_color_entries_8660d8@@3PAUUnknownColorEntry@@A=008660d8

bool __fastcall Color_Entry_Taken_4d2060(int entry)
{
    return unknown_color_entries_8660d8[entry].Index != -1;
}
