// wchar_t const *UnitClass::unknown_slot35() (0x0070A0E0, slot 35)
// The name to show: a disguised unit (slot 49 for the player, with a
// disguise type and house) shows the disguise's name; a unit with an
// occupied passenger slot (0x006D83E0/0x006D83D0) shows its type's name
// prefixed by the first passenger's role (Tip:Repair for a passenger whose
// slot 193 holds, Tip:MachineGun for a non-civilian infantry whose weapon's
// warhead has Bullets, otherwise its own name; Tip:Rocket by default).
#include "shared/unit.hpp"
#include "shared/infantry_type.hpp"
#include "shared/warhead_type.hpp"
#include "shared/string_table.hpp"
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?unknown_6d83e0@TechnoClass@@QAE_NXZ=006d83e0
// @ref ?unknown_6d83d0@TechnoClass@@QAE_NXZ=006d83d0
// @ref ?unknown_468a10@UnknownCargo@@QBEPAVObjectClass@@XZ=00468a10
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref _swprintf=00783764
// @ref ??_C@_0BA@DDPG@D?3?2Ra2?2Unit?4CPP?$AA@=007f8fe0
// @ref ??_C@_0L@HLLD@Tip?3Repair?$AA@=007f8fd4
// @ref ??_C@_0P@PHIP@Tip?3MachineGun?$AA@=007f8fc4
// @ref ??_C@_0L@CEBA@Tip?3Rocket?$AA@=007f8fb8
// @ref ??_C@_1M@EOJM@?$AA?$CF?$AAs?$AA?5?$AA?$CF?$AAs?$AA?$AA@=007dc0d0

// An infantry passenger's type (a view until shared/infantry.hpp is installed).
struct UnknownUnitInfantryView : TechnoClass {
    char unknown_418[0x5A8 - 0x418];
    InfantryTypeClass *Type;                // +0x5A8
};

wchar_t const *UnitClass::unknown_slot35()
{
    if (unknown_slot49(unknown_player_a35db4) && unknown_slot50(true)) {
        if (!unknown_slot51(true)) {
            return 0;
        }
        return unknown_slot50(true)->UIName;
    }
    if (unknown_6d83e0() && unknown_6d83d0()) {
        wchar_t const *role = 0;
        TechnoClass *passenger = (TechnoClass *)Cargo.unknown_468a10();
        if (passenger && passenger->Kind_Of() == 15) {
            if (passenger->unknown_slot193()) {
                role = StringTable::Load_String("Tip:Repair", 0, "D:\\Ra2\\Unit.CPP", 10328);
            } else if (!((UnknownUnitInfantryView *)passenger)->Type->Civilian) {
                role = passenger->Class_Of()->UIName;
                WeaponStruct *weapon = passenger->unknown_slot230();
                if (weapon && weapon->WeaponType && weapon->WeaponType->Warhead && weapon->WeaponType->Warhead->Bullets) {
                    role = StringTable::Load_String("Tip:MachineGun", 0, "D:\\Ra2\\Unit.CPP", 10341);
                }
            }
        }
        if (!role) {
            role = StringTable::Load_String("Tip:Rocket", 0, "D:\\Ra2\\Unit.CPP", 10349);
        }
        swprintf(unknown_5d0, L"%s %s", role, Type->UIName);
        return unknown_5d0;
    }
    return Type->UIName;
}
