// wchar_t const *__fastcall Side_Name_4d1420(int side) (0x004D1420)
// The name of a country (STT:PlayerSide<Country>; -2 random, -3 observer),
// null for any other value.
#include "shared/gdlg_supp.hpp"
#include "shared/string_table.hpp"
// @ref ??_C@_0BE@KGHJ@D?3?2Ra2?2GDlgSupp?4cpp?$AA@=007d862c
// @ref ??_C@_0BF@BJBE@STT?3PlayerSideRandom?$AA@=007d8614
// @ref ??_C@_0BH@LKKA@STT?3PlayerSideObserver?$AA@=007d85fc
// @ref ??_C@_0BG@KOJP@STT?3PlayerSideAmerica?$AA@=007d85e4
// @ref ??_C@_0BE@FFPM@STT?3PlayerSideKorea?$AA@=007d85d0
// @ref ??_C@_0BF@KIFM@STT?3PlayerSideFrance?$AA@=007d85b8
// @ref ??_C@_0BG@JHGK@STT?3PlayerSideGermany?$AA@=007d85a0
// @ref ??_C@_0BG@JFPI@STT?3PlayerSideBritain?$AA@=007d8588
// @ref ??_C@_0BE@EONH@STT?3PlayerSideLibya?$AA@=007d8574
// @ref ??_C@_0BD@PIMG@STT?3PlayerSideIraq?$AA@=007d8560
// @ref ??_C@_0BD@LEBM@STT?3PlayerSideCuba?$AA@=007d854c
// @ref ??_C@_0BF@ECGP@STT?3PlayerSideRussia?$AA@=007d8534

wchar_t const *__fastcall Side_Name_4d1420(int side)
{
    if (side == -2) {
        return StringTable::Load_String("STT:PlayerSideRandom", 0, "D:\\Ra2\\GDlgSupp.cpp", 231);
    }
    if (side == -3) {
        return StringTable::Load_String("STT:PlayerSideObserver", 0, "D:\\Ra2\\GDlgSupp.cpp", 233);
    }
    if (side == 0) {
        return StringTable::Load_String("STT:PlayerSideAmerica", 0, "D:\\Ra2\\GDlgSupp.cpp", 235);
    }
    if (side == 1) {
        return StringTable::Load_String("STT:PlayerSideKorea", 0, "D:\\Ra2\\GDlgSupp.cpp", 237);
    }
    if (side == 2) {
        return StringTable::Load_String("STT:PlayerSideFrance", 0, "D:\\Ra2\\GDlgSupp.cpp", 239);
    }
    if (side == 3) {
        return StringTable::Load_String("STT:PlayerSideGermany", 0, "D:\\Ra2\\GDlgSupp.cpp", 241);
    }
    if (side == 4) {
        return StringTable::Load_String("STT:PlayerSideBritain", 0, "D:\\Ra2\\GDlgSupp.cpp", 243);
    }
    if (side == 5) {
        return StringTable::Load_String("STT:PlayerSideLibya", 0, "D:\\Ra2\\GDlgSupp.cpp", 245);
    }
    if (side == 6) {
        return StringTable::Load_String("STT:PlayerSideIraq", 0, "D:\\Ra2\\GDlgSupp.cpp", 247);
    }
    if (side == 7) {
        return StringTable::Load_String("STT:PlayerSideCuba", 0, "D:\\Ra2\\GDlgSupp.cpp", 249);
    }
    if (side == 8) {
        return StringTable::Load_String("STT:PlayerSideRussia", 0, "D:\\Ra2\\GDlgSupp.cpp", 251);
    }
    return 0;
}
