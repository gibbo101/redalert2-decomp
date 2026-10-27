// Whether the supplied infantry can occupy or assault this building.
#include "shared/building.hpp"
#include "shared/infantry.hpp"
#include "shared/house_type.hpp"
// @ref ?Is_Ally@HouseClass@@QBE_NPBVTechnoClass@@@Z=004e5580
// @ref ?unknown_func_5d45b0@ObjectClass@@QBEHXZ=005d45b0
bool BuildingClass::Unknown_00452EB0(TechnoClass *techno)
{
    if(!Type->CanBeOccupied) return false;
    InfantryClass *infantry=static_cast<InfantryClass *>(techno);
    if(infantry->Type->Occupier) {
        if((House==infantry->House || House->Type->MultiplayPassive)
           && unknown_554.Count()!=Type->MaxNumberOccupants
           && !(char)unknown_func_5d45b0() && !infantry->unknown_234) goto allowed;
    } else if(infantry->Type->Assaulter && !House->Is_Ally(infantry) && unknown_554.Count()) goto allowed;
    return false;
allowed:
    return true;
}
