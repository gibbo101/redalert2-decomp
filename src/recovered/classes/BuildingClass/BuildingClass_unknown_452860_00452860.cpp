// int BuildingClass::unknown_452860() (0x00452860)
// The type's second super weapon index, or -1 while that super weapon's
// auxiliary building is not owned by the house (0x00491D10).
#include "shared/building.hpp"
// @ref ?Supers@@3V?$DynamicVectorClass@PAVSuperClass@@@@A=00a35d28
// @ref ?unknown_func_491d10@UnknownHouseCounter@@QAEHH@Z=00491d10

int BuildingClass::unknown_452860()
{
    if (Type->SuperWeapon2 != -1) {
        BuildingTypeClass *aux = Supers[Type->SuperWeapon2]->Type->AuxBuilding;
        if (aux != 0 && !House->unknown_5460.unknown_func_491d10(aux->ArrayIndex)) {
            return -1;
        }
    }
    return Type->SuperWeapon2;
}
