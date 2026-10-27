// wchar_t const *__fastcall Unknown_Health_Message_006F7E40(int state) -- 0x006F7E40
// The status message for a health state: 0 critical, 1 heavily damaged, 2 healthy; empty for any
// other state (hypothesis).
#include "shared/string_table.hpp"
// @ref ??_C@_0BD@BJM@D?3?2Ra2?2UICmnds?4cpp?$AA@=007f8c10
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ??_C@_0N@IEJB@MSG?3Critical?$AA@=007f8ca8
// @ref ??_C@_0BD@EMHN@MSG?3HeavilyDamaged?$AA@=007f8c94
// @ref ??_C@_0M@EGJA@MSG?3Healthy?$AA@=007f8c88
// @ref ?unknown_empty_wide_839d4c@@3QBGB=00839d4c
extern wchar_t const unknown_empty_wide_839d4c[];

wchar_t const *__fastcall Unknown_Health_Message_006F7E40(int state)
{
    if (state == 0) {
        return StringTable::Load_String("MSG:Critical", 0, "D:\\Ra2\\UICmnds.cpp", 0x5ae);
    }
    if (state == 1) {
        return StringTable::Load_String("MSG:HeavilyDamaged", 0, "D:\\Ra2\\UICmnds.cpp", 0x5b0);
    }
    if (state == 2) {
        return StringTable::Load_String("MSG:Healthy", 0, "D:\\Ra2\\UICmnds.cpp", 0x5b2);
    }
    return unknown_empty_wide_839d4c;
}
