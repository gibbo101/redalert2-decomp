// void BuildingClass::unknown_44d6c0() (0x0044D6C0)
// Clears unknown_5ba and refreshes the house's active buildings (0x0044F8E0,
// after 0x0044E5A0 for a laser fence post); hands 0 to the owned object at
// +0x4E8; a cloak generator type sets unknown_5bb to -1, takes the type's
// CloakRadiusInCells into an unset unknown_5bc and sets unknown_75; a gap
// generator type with +0x1FD set runs slot 236; then the laser field and
// 0x00422C10 on each animation whose Anims entry is Powered.
#include "shared/building.hpp"
#include "shared/house.hpp"
// @ref ?unknown_44e5a0@BuildingClass@@QAEXH@Z=0044e5a0
// @ref ?unknown_44f8e0@BuildingClass@@QAEXXZ=0044f8e0
// @ref ?unknown_537560@UnknownBuilding4E8@@QAEXH@Z=00537560
// @ref ?unknown_422c10@UnknownBuildingAnim@@QAEXXZ=00422c10

void BuildingClass::unknown_44d6c0()
{
    HouseClass *house = House;
    unknown_5ba = false;
    int count = house->Buildings.Count();
    for (int index = 0; index < count; index++) {
        BuildingClass *building = house->Buildings[index];
        if (building->unknown_7d && !building->unknown_76) {
            if (building->Type->LaserFencePost) {
                building->unknown_44e5a0(0);
            }
            building->unknown_44f8e0();
        }
    }
    if (unknown_4e8) {
        unknown_4e8->unknown_537560(0);
    }
    if (Type->CloakGenerator) {
        unknown_5bb = -1;
        if (!unknown_5bc) {
            unknown_5bc = Type->CloakRadiusInCells;
        }
        unknown_75 = true;
    }
    if (Type->GapGenerator && unknown_1fd) {
        unknown_slot236();
    }
    if (Type->LaserFencePost) {
        unknown_44e5a0(0);
    }
    for (int anim = 0; anim < 18; anim++) {
        if (Type->Anims[anim].Powered && unknown_454[anim]) {
            ((UnknownBuildingAnim *)unknown_454[anim])->unknown_422c10();
        }
    }
}
