// Radius selection with a shared result and the original signed byte/weapon units.
#include "shared/building.hpp"
#include "shared/weapon_type.hpp"
// @ref ?unknown_slot230@TechnoClass@@=006d85a0
// @ref ?Unknown_006D8640@TechnoClass@@=006d8640
int BuildingClass::unknown_451930()
{
    int radius=0;
    BuildingTypeClass *type=Type;
    int configured=type->PsychicDetectionRadius;
    if(configured>0) radius=configured;
    else if(type->GapGenerator) {
        char radius_byte=unknown_1fc ? type->SuperGapRadiusInCells : type->GapRadiusInCells;
        radius=radius_byte;
    } else if(type->SensorArray || type->CloakGenerator) radius=type->CloakRadiusInCells;
    else {
        WeaponStruct *weapon=TechnoClass::unknown_slot230();
        if(Unknown_006D8640(weapon) && weapon->WeaponType->unknown_b4>0) radius=weapon->WeaponType->unknown_b4/256;
    }
    return radius;
}
