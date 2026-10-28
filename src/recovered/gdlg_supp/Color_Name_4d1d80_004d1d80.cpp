// wchar_t const *__fastcall Color_Name_4d1d80(int color) (0x004D1D80)
// The name of a player colour (STT:PlayerColor<Colour>; -2 random, 8
// observer), null for any other value.
#include "shared/gdlg_supp.hpp"
#include "shared/string_table.hpp"
// @ref ??_C@_0BG@PHDO@STT?3PlayerColorRandom?$AA@=007d8728
// @ref ??_C@_0BE@BMPB@STT?3PlayerColorGold?$AA@=007d8714
// @ref ??_C@_0BD@HKPC@STT?3PlayerColorRed?$AA@=007d8700
// @ref ??_C@_0BE@DJBA@STT?3PlayerColorBlue?$AA@=007d86ec
// @ref ??_C@_0BF@KPFE@STT?3PlayerColorGreen?$AA@=007d86d4
// @ref ??_C@_0BG@CEHN@STT?3PlayerColorOrange?$AA@=007d86bc
// @ref ??_C@_0BH@EAAP@STT?3PlayerColorSkyBlue?$AA@=007d86a4
// @ref ??_C@_0BG@LCDA@STT?3PlayerColorPurple?$AA@=007d868c
// @ref ??_C@_0BE@HDBB@STT?3PlayerColorPink?$AA@=007d8678
// @ref ??_C@_0BI@MHFG@STT?3PlayerColorObserver?$AA@=007d8660

wchar_t const *__fastcall Color_Name_4d1d80(int color)
{
    if (color == -2) {
        return StringTable::Load_String("STT:PlayerColorRandom", 0, "D:\\Ra2\\GDlgSupp.cpp", 429);
    }
    if (color == 0) {
        return StringTable::Load_String("STT:PlayerColorGold", 0, "D:\\Ra2\\GDlgSupp.cpp", 431);
    }
    if (color == 1) {
        return StringTable::Load_String("STT:PlayerColorRed", 0, "D:\\Ra2\\GDlgSupp.cpp", 433);
    }
    if (color == 2) {
        return StringTable::Load_String("STT:PlayerColorBlue", 0, "D:\\Ra2\\GDlgSupp.cpp", 435);
    }
    if (color == 3) {
        return StringTable::Load_String("STT:PlayerColorGreen", 0, "D:\\Ra2\\GDlgSupp.cpp", 437);
    }
    if (color == 4) {
        return StringTable::Load_String("STT:PlayerColorOrange", 0, "D:\\Ra2\\GDlgSupp.cpp", 439);
    }
    if (color == 5) {
        return StringTable::Load_String("STT:PlayerColorSkyBlue", 0, "D:\\Ra2\\GDlgSupp.cpp", 441);
    }
    if (color == 6) {
        return StringTable::Load_String("STT:PlayerColorPurple", 0, "D:\\Ra2\\GDlgSupp.cpp", 443);
    }
    if (color == 7) {
        return StringTable::Load_String("STT:PlayerColorPink", 0, "D:\\Ra2\\GDlgSupp.cpp", 445);
    }
    if (color == 8) {
        return StringTable::Load_String("STT:PlayerColorObserver", 0, "D:\\Ra2\\GDlgSupp.cpp", 447);
    }
    return 0;
}
