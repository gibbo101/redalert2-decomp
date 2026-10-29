// bool CarryoverClass::Create() const (0x00468D50)
// Recreates the object for its house at its cell with its strength;
// infantry is placed with unknown_a40774 cleared. Always false.
#include "shared/carryover.hpp"
#include "shared/building_class.hpp"
#include "shared/unit.hpp"
#include "shared/infantry.hpp"
#include "shared/building_type_list.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/cell.hpp"
// @ref ?As_Pointer@HouseClass@@SIPAV1@H@Z=004ed760
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0UnitClass@@QAE@PAVUnitTypeClass@@PAVHouseClass@@@Z=006fa400
// @ref ??0BuildingClass@@QAE@PAVBuildingTypeClass@@PAVHouseClass@@@Z=00438ce0
// @ref ??0InfantryClass@@QAE@PAVInfantryTypeClass@@PAVHouseClass@@@Z=004ff640
// @ref ?UnitTypes@@3V?$DynamicVectorClass@PAVUnitTypeClass@@@@A=00a35d48
// @ref ?BuildingTypes@@3V?$DynamicVectorClass@PAVBuildingTypeClass@@@@A=00a35cd8
// @ref ?InfantryTypes@@3V?$DynamicVectorClass@PAVInfantryTypeClass@@@@A=00a40350
// @ref ?unknown_a40774@@3HA=00a40774

bool CarryoverClass::Create() const
{
    HouseClass *house = HouseClass::As_Pointer(House);
    TechnoClass *techno = 0;
    switch (RTTI) {
        case 1:
            techno = new UnitClass(UnitTypes[Type], house);
            break;
        case 6:
            techno = new BuildingClass(BuildingTypes[Type], house);
            break;
        case 15:
            techno = new InfantryClass(InfantryTypes[Type], house);
            break;
    }
    if (techno) {
        bool old = unknown_a40774 != 0;
        techno->Strength = Strength;
        if (RTTI == 15) {
            unknown_a40774 = 0;
        }
        CoordStruct coord(Position.X * 256 + 128, Position.Y * 256 + 128, 0);
        techno->unknown_slot53(&coord, 0);
        if (RTTI == 15) {
            unknown_a40774 = old;
        }
    }
    return false;
}

