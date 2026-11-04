// bool BuildingClass::unknown_44c860() (0x0044C860)
// Removes the last upgrade (unknown_4c0 up to unknown_5c6). An upgrade with
// a turret clears them all and resets unknown_4d0; one with a super weapon
// tells the house (0x004F4B20). False when there was no upgrade.
#include "shared/building.hpp"
#include "shared/house.hpp"
// @ref ?unknown_44cfd0@BuildingClass@@QAEXH@Z=0044cfd0
// @ref ?Update_Present_Super_Weapons@HouseClass@@QAEXXZ=004f4b20

bool BuildingClass::unknown_44c860()
{
    if (!unknown_5c6) {
        return false;
    }
    bool super_weapon = false;
    if (unknown_4c0[unknown_5c6 - 1] && ((BuildingTypeClass *)unknown_4c0[unknown_5c6 - 1])->SuperWeapon != -1) {
        super_weapon = true;
    }
    if (unknown_4c0[unknown_5c6 - 1] && unknown_4c0[unknown_5c6 - 1]->Turret) {
        unknown_44cfd0(9);
        unknown_4c0[unknown_5c6 - 1] = 0;
        unknown_5c6 = 0;
        unknown_4d0 = -1;
        if (super_weapon) {
            House->Update_Present_Super_Weapons();
        }
        return true;
    }
    unknown_44cfd0(unknown_5c6 - 1);
    unknown_5c6--;
    unknown_4c0[unknown_5c6] = 0;
    if (super_weapon) {
        House->Update_Present_Super_Weapons();
    }
    return true;
}
