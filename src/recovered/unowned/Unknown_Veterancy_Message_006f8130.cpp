// wchar_t const *__fastcall Unknown_Veterancy_Message_006F8130(int rank) -- 0x006F8130
// The status message for a veterancy rank: 0 elite, 1 veteran, 2 little experience; empty for any other rank
// (hypothesis).
#include "shared/string_table.hpp"
// @ref ??_C@_0BD@BJM@D?3?2Ra2?2UICmnds?4cpp?$AA@=007f8c10
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ??_C@_09MLOC@MSG?3Elite?$AA@=007f8cdc
// @ref ??_C@_0M@KCCB@MSG?3Veteran?$AA@=007f8cd0
// @ref ??_C@_0BF@BENO@MSG?3LittleExperience?$AA@=007f8cb8
// @ref ?unknown_empty_wide_839d4c@@3QBGB=00839d4c
extern wchar_t const unknown_empty_wide_839d4c[];

wchar_t const *__fastcall Unknown_Veterancy_Message_006F8130(int rank)
{
    if (rank == 0) {
        return StringTable::Load_String("MSG:Elite", 0, "D:\\Ra2\\UICmnds.cpp", 0x5f8);
    }
    if (rank == 1) {
        return StringTable::Load_String("MSG:Veteran", 0, "D:\\Ra2\\UICmnds.cpp", 0x5fa);
    }
    if (rank == 2) {
        return StringTable::Load_String("MSG:LittleExperience", 0, "D:\\Ra2\\UICmnds.cpp", 0x5fc);
    }
    return unknown_empty_wide_839d4c;
}
