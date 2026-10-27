#define RA2_COORD_EQUAL_MEMBER
// void __fastcall Planning_Message(char const *label) (0x00616FB0)
// Shows a planning-mode help message (the string table label in ecx).
#include "shared/planning.hpp"
#include "shared/string_table.hpp"
// @ref ??_C@_0BD@KDIH@D?3?2Ra2?2PlanMgr?4cpp?$AA@=007ebd4c
// @ref ?Unknown_006F58E0@@YIXPBGH@Z=006f58e0

void __fastcall Planning_Message(char const *label)
{
    wchar_t const *text = StringTable::Load_String(label, 0, "D:\\Ra2\\PlanMgr.cpp", 3231);
    Unknown_006F58E0(text, 0x1E0);
}
