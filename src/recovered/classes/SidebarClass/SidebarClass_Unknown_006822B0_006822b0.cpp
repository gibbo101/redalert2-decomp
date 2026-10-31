// void SidebarClass::Unknown_006822B0(TechnoTypeClass *type, int delay) (0x006822B0)
// Finds a techno type's index in its type list and delays the matching
// icon of its strip (and the sidebar's next update) by `delay` frames.
#include "shared/sidebar.hpp"
class InfantryTypeClass;
class UnitTypeClass;
class AircraftTypeClass;
class BuildingTypeClass;
extern DynamicVectorClass<InfantryTypeClass *> InfantryTypes;   // 0x00A40350
extern DynamicVectorClass<UnitTypeClass *> UnitTypes;           // 0x00A35D48
extern DynamicVectorClass<AircraftTypeClass *> AircraftTypes;   // 0x00A3D278
extern DynamicVectorClass<BuildingTypeClass *> BuildingTypes;   // 0x00A35CD8
// @ref ?InfantryTypes@@3V?$DynamicVectorClass@PAVInfantryTypeClass@@@@A=00a40350
// @ref ?UnitTypes@@3V?$DynamicVectorClass@PAVUnitTypeClass@@@@A=00a35d48
// @ref ?AircraftTypes@@3V?$DynamicVectorClass@PAVAircraftTypeClass@@@@A=00a3d278
// @ref ?BuildingTypes@@3V?$DynamicVectorClass@PAVBuildingTypeClass@@@@A=00a35cd8

void SidebarClass::Unknown_006822B0(TechnoTypeClass *type, int delay)
{
    int index;
    for (index = 0; index < InfantryTypes.Count(); index++) {
        if ((TechnoTypeClass *)InfantryTypes[index] == type) {
            goto found;
        }
    }
    for (index = 0; index < UnitTypes.Count(); index++) {
        if (type == (TechnoTypeClass *)UnitTypes[index]) {
            goto found;
        }
    }
    for (index = 0; index < AircraftTypes.Count(); index++) {
        if (type == (TechnoTypeClass *)AircraftTypes[index]) {
            goto found;
        }
    }
    for (index = 0; index < BuildingTypes.Count(); index++) {
        if (type == (TechnoTypeClass *)BuildingTypes[index]) {
            goto found;
        }
    }
    return;

found:
    int kind = type->Kind_Of();
    int column;
    if (kind == 15 || kind == 16) {
        column = 2;
    } else if (kind == 1 || kind == 40 || kind == 2 || kind == 3) {
        column = 3;
    } else if (kind == 6 || kind == 7) {
        column = (Unknown_004EB550(kind, index) == 5);
    } else if (kind == 57 || kind == 32 || kind == 31) {
        column = 1;
    } else {
        return;
    }
    Column[column].Unknown_00682400(index, delay);
    unknown_4edc = Frame + 1 + delay;
}
