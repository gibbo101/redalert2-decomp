// wchar_t const *InfantryClass::unknown_slot35() (0x00506160, slot 35)
// The name shown: "Technician" while +0x5C1 is set; the disguise type's
// name to other houses than the player's allies; else the type's UIName.
#include "shared/infantry.hpp"
#include "shared/string_table.hpp"
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?Is_Ally@HouseClass@@QBE_NPBV1@@Z=004e5540
// @ref ??_C@_0P@DJJM@TXT_TECHNICIAN?$AA@=007daf08
// @ref ??_C@_0BE@FGIL@D?3?2Ra2?2Infantry?4CPP?$AA@=007daf18

wchar_t const *InfantryClass::unknown_slot35()
{
    if (unknown_5c1) {
        return StringTable::Load_String("TXT_TECHNICIAN", 0, "D:\\Ra2\\Infantry.CPP", 4221);
    }
    if (unknown_slot48() && !House->Is_Ally(unknown_player_a35db4)) {
        return unknown_slot50(true)->UIName;
    }
    return Type->UIName;
}
