// wchar_t const *__fastcall Entry_Type_Name_005c9870(NodeNameType *entry) (0x005C9870)
#include "shared/lobby.hpp"
#include "shared/string_table.hpp"
// @ref ??_C@_0BA@HBDP@STT?3PlayerHuman?$AA@=007e7328
// @ref ??_C@_0BB@KLPO@STT?3PlayerClosed?$AA@=007e738c
// @ref ??_C@_0BE@EJOA@D?3?2Ra2?2netshare?4cpp?$AA@=007e6ebc
// @ref ??_C@_0BH@HBKA@STT?3PlayerOpenObserver?$AA@=007e7338
// @ref ??_C@_0P@IBDI@STT?3PlayerOpen?$AA@=007e73a0
// @ref ??_C@_0BB@FAHH@STT?3PlayerDumbAI?$AA@=007e7378
// @ref ??_C@_0BC@LDDH@STT?3PlayerSmartAI?$AA@=007e7364
// @ref ??_C@_0BD@PLEH@STT?3PlayerGeniusAI?$AA@=007e7350
// @ref ?unknown_closed_entry_a72d30@@3PAUNodeNameType@@A=00a72d30
// @ref ?unknown_easy_ai_entry_a72d34@@3PAUNodeNameType@@A=00a72d34
// @ref ?unknown_hard_ai_entry_a72d3c@@3PAUNodeNameType@@A=00a72d3c
// @ref ?unknown_medium_ai_entry_a72d38@@3PAUNodeNameType@@A=00a72d38
// @ref ?unknown_open_entry_a72d2c@@3PAUNodeNameType@@A=00a72d2c

wchar_t const *__fastcall Entry_Type_Name_005c9870(NodeNameType *entry)
{
    if (entry == unknown_open_entry_a72d2c) {
        return StringTable::Load_String("STT:PlayerOpen", 0, "D:\\Ra2\\netshare.cpp", 0x11BA);
    }
    if (entry == unknown_closed_entry_a72d30) {
        return StringTable::Load_String("STT:PlayerClosed", 0, "D:\\Ra2\\netshare.cpp", 0x11BC);
    }
    if (entry == unknown_easy_ai_entry_a72d34) {
        return StringTable::Load_String("STT:PlayerDumbAI", 0, "D:\\Ra2\\netshare.cpp", 0x11BE);
    }
    if (entry == unknown_medium_ai_entry_a72d38) {
        return StringTable::Load_String("STT:PlayerSmartAI", 0, "D:\\Ra2\\netshare.cpp", 0x11C0);
    }
    if (entry == unknown_hard_ai_entry_a72d3c) {
        return StringTable::Load_String("STT:PlayerGeniusAI", 0, "D:\\Ra2\\netshare.cpp", 0x11C2);
    }
    if (entry == unknown_player_a72d44) {
        return StringTable::Load_String("STT:PlayerOpenObserver", 0, "D:\\Ra2\\netshare.cpp", 0x11C4);
    }
    return StringTable::Load_String("STT:PlayerHuman", 0, "D:\\Ra2\\netshare.cpp", 0x11C6);
}
