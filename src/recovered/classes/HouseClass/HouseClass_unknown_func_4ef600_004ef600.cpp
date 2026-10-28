// BuildingTypeClass *HouseClass::unknown_func_4ef600(DynamicVectorClass<BuildingTypeClass *> const &types) (0x004EF600)
// The first building type of the list that this house may build: its owner
// set holds the parent country's house index, its required/forbidden house
// sets allow this house type, its side matches (or is -1) and its super
// weapon, when it has one, is not disableable (always accepted in the session
// flag 0x00A3D2C3).
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/super.hpp"
#include "shared/building_type_class.hpp"
#include "shared/techno_type.hpp"
// @ref ?unknown_session_a3d2c3@@3EA=00a3d2c3

BuildingTypeClass *HouseClass::unknown_func_4ef600(DynamicVectorClass<BuildingTypeClass *> const &types)
{
    int owner_bit = 1 << HouseTypeClass::Find_Index(Type->ParentCountry);
    for (int index = 0; index < types.Count(); index++) {
        BuildingTypeClass *building = types[index];
        if ((building->Owner & owner_bit) != 0
            && (building->RequiredHouses == -1 || (building->RequiredHouses & (1 << Type->House)) != 0)
            && (building->ForbiddenHouses == -1 || (building->ForbiddenHouses & (1 << Type->House)) == 0)
            && (building->AIBasePlanningSide == -1 || building->AIBasePlanningSide == Type->Side)) {
            if (unknown_session_a3d2c3 || building->SuperWeapon == -1 || !Supers[building->SuperWeapon]->Type->DisableableFromShell) {
                return building;
            }
        }
    }
    return 0;
}
