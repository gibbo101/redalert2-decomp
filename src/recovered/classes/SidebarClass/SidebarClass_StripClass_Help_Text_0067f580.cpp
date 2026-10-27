// wchar_t const *SidebarClass::StripClass::Help_Text(int gadget_index) (0x0067F580)
// The help text of a visible icon: a super weapon's name, or a type's name
// and cost for the player (one word per line).
#include "shared/sidebar.hpp"
#include "shared/super_weapon_type.hpp"
#include "shared/object_type.hpp"
// @ref ?SuperWeaponTypes@@3V?$DynamicVectorClass@PAVSuperWeaponTypeClass@@@@A=00a40338
// @ref ?unknown_flag_a40958@@3_NA=00a40958
// @ref ?unknown_flag_8373c0@@3_NA=008373c0
// @ref ?unknown_text_ab9484@@3PAGA=00ab9484
// @ref ?Unknown_00482C00@@YIPAVObjectTypeClass@@HH@Z=00482c00
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref _swprintf=00783764
// @ref _wcslen=00783605
// @ref ??_C@_0BD@MHFI@TXT_MONEY_FORMAT_2?$AA@=007f3e78
// @ref ??_C@_0BD@DIOB@TXT_MONEY_FORMAT_1?$AA@=007f3e8c
// @ref ??_C@_0BD@KJOF@D?3?2Ra2?2Sidebar?4CPP?$AA@=007f3ea0

wchar_t const *SidebarClass::StripClass::Help_Text(int gadget_index)
{
    int index = gadget_index + unknown_40 * 2;
    if (!unknown_flag_a40958 || index >= BuildableCount || BuildableCount >= 75) {
        return 0;
    }
    if (Buildables[index].unknown_04 == 31) {
        return SuperWeaponTypes[Buildables[index].unknown_00]->UIName;
    }
    ObjectTypeClass *type = Unknown_00482C00(Buildables[index].unknown_04, Buildables[index].unknown_00);
    if (unknown_flag_8373c0) {
        swprintf(unknown_text_ab9484,
            StringTable::Load_String("TXT_MONEY_FORMAT_1", 0, "D:\\Ra2\\Sidebar.CPP", 2627),
            type->unknown_slot33((int)unknown_player_a35db4));
    } else {
        swprintf(unknown_text_ab9484,
            StringTable::Load_String("TXT_MONEY_FORMAT_2", 0, "D:\\Ra2\\Sidebar.CPP", 2629),
            type->UIName, type->unknown_slot33((int)unknown_player_a35db4));
    }
    int length = wcslen(unknown_text_ab9484);
    for (int i = 0; i < length; i++) {
        if (unknown_text_ab9484[i] == ' ') {
            unknown_text_ab9484[i] = '\n';
        }
    }
    return unknown_text_ab9484;
}
