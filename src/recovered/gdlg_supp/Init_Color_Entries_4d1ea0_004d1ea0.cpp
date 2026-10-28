// void __fastcall Init_Color_Entries_4d1ea0() (0x004D1EA0)
// Fills the dialogs' colour table: each entry's abbreviated name
// (GUI:<Colour>Abbrev), its colour value from 0x007E6D94 and no combo box
// item yet (-1).
#include "shared/gdlg_supp.hpp"
#include "shared/string_table.hpp"
// @ref ?unknown_color_entries_8660d8@@3PAUUnknownColorEntry@@A=008660d8
// @ref ?unknown_color_values_7e6d94@@3QBHB=007e6d94
// @ref ??_C@_0P@IDCB@GUI?3GoldAbbrev?$AA@=007d87cc
// @ref ??_C@_0O@KGCJ@GUI?3RedAbbrev?$AA@=007d87bc
// @ref ??_C@_0P@NABE@GUI?3BlueAbbrev?$AA@=007d87ac
// @ref ??_C@_0BA@BIBC@GUI?3GreenAbbrev?$AA@=007d879c
// @ref ??_C@_0BB@OCNO@GUI?3OrangeAbbrev?$AA@=007d8788
// @ref ??_C@_0BC@IEAK@GUI?3SkyBlueAbbrev?$AA@=007d8774
// @ref ??_C@_0BB@IJAO@GUI?3PurpleAbbrev?$AA@=007d8760
// @ref ??_C@_0P@HAOC@GUI?3PinkAbbrev?$AA@=007d8750
// @ref ??_C@_0P@FOFO@GUI?3GrayAbbrev?$AA@=007d8740

void __fastcall Init_Color_Entries_4d1ea0()
{
    unknown_color_entries_8660d8[0].Name = StringTable::Load_String("GUI:GoldAbbrev", 0, "D:\\Ra2\\GDlgSupp.cpp", 455);
    unknown_color_entries_8660d8[1].Name = StringTable::Load_String("GUI:RedAbbrev", 0, "D:\\Ra2\\GDlgSupp.cpp", 456);
    unknown_color_entries_8660d8[2].Name = StringTable::Load_String("GUI:BlueAbbrev", 0, "D:\\Ra2\\GDlgSupp.cpp", 457);
    unknown_color_entries_8660d8[3].Name = StringTable::Load_String("GUI:GreenAbbrev", 0, "D:\\Ra2\\GDlgSupp.cpp", 458);
    unknown_color_entries_8660d8[4].Name = StringTable::Load_String("GUI:OrangeAbbrev", 0, "D:\\Ra2\\GDlgSupp.cpp", 459);
    unknown_color_entries_8660d8[5].Name = StringTable::Load_String("GUI:SkyBlueAbbrev", 0, "D:\\Ra2\\GDlgSupp.cpp", 460);
    unknown_color_entries_8660d8[6].Name = StringTable::Load_String("GUI:PurpleAbbrev", 0, "D:\\Ra2\\GDlgSupp.cpp", 461);
    unknown_color_entries_8660d8[7].Name = StringTable::Load_String("GUI:PinkAbbrev", 0, "D:\\Ra2\\GDlgSupp.cpp", 462);
    unknown_color_entries_8660d8[8].Name = StringTable::Load_String("GUI:GrayAbbrev", 0, "D:\\Ra2\\GDlgSupp.cpp", 463);
    for (int index = 0; index < 9; index++) {
        unknown_color_entries_8660d8[index].Color = unknown_color_values_7e6d94[index];
        unknown_color_entries_8660d8[index].Index = -1;
    }
}
