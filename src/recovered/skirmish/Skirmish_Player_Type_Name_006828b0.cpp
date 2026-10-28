// wchar_t const *__fastcall Skirmish_Player_Type_Name(int type) (0x006828B0)
// The text of a player type (-1 none, 2 dumb, 1 smart, 0 genius computer), or null.
#include "shared/skirmish.hpp"
#include "shared/string_table.hpp"

// @ref ??_C@_0BE@OMOF@D?3?2Ra2?2Skirmish?4cpp?$AA@=007f3fd4
// @ref ??_C@_0P@IOHO@STT?3PlayerNone?$AA@=007f3fc4
// @ref ??_C@_0BB@FAHH@STT?3PlayerDumbAI?$AA@=007e7378
// @ref ??_C@_0BC@LDDH@STT?3PlayerSmartAI?$AA@=007e7364
// @ref ??_C@_0BD@PLEH@STT?3PlayerGeniusAI?$AA@=007e7350

wchar_t const *__fastcall Skirmish_Player_Type_Name(int type)
{
    if (type == -1) {
        return StringTable::Load_String("STT:PlayerNone", 0, "D:\\Ra2\\Skirmish.cpp", 0x85);
    }
    if (type == 2) {
        return StringTable::Load_String("STT:PlayerDumbAI", 0, "D:\\Ra2\\Skirmish.cpp", 0x87);
    }
    if (type == 1) {
        return StringTable::Load_String("STT:PlayerSmartAI", 0, "D:\\Ra2\\Skirmish.cpp", 0x89);
    }
    if (type == 0) {
        return StringTable::Load_String("STT:PlayerGeniusAI", 0, "D:\\Ra2\\Skirmish.cpp", 0x8B);
    }
    return 0;
}
