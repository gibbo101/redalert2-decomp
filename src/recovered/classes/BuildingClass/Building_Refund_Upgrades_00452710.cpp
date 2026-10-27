// Refund/remove each installed upgrade, refresh the house's buildings, then call slot98.
// Original static/member ownership of this ECX-input helper remains a hypothesis.
#include "shared/building.hpp"
#include "shared/house.hpp"
void __fastcall Building_Refresh_House_Buildings_0044fa40(HouseClass *house);
void __fastcall Building_Refund_Upgrades_00452710(BuildingClass *building)
{
    while (building->unknown_5c6 > 0) {
        building->House->Refund_Money(building->unknown_4c0[building->unknown_5c6 - 1]
                                      ->unknown_slot46(building->House, true));
        building->unknown_44c860();
        building->House->unknown_5668 = true;
        building->House->unknown_5669 = true;
        Building_Refresh_House_Buildings_0044fa40(building->House);
    }
    building->unknown_slot98(1);
}
