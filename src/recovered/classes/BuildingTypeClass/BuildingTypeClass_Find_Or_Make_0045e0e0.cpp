// static BuildingTypeClass *__fastcall BuildingTypeClass::Find_Or_Make(char const *name) (0x0045E0E0)
// The type with this ID, a new one when unknown, 0 for "<none>"/"none".
#include "shared/building_type.hpp"
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc
// @ref __stricmp=00781f20
// @ref ??_C@_04KIKH@none?$AA@=007ce0ec
// @ref ?BuildingTypes@@3V?$DynamicVectorClass@PAVBuildingTypeClass@@@@A=00a35cd8
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0BuildingTypeClass@@QAE@PBD@Z=00457ac0

BuildingTypeClass *__fastcall BuildingTypeClass::Find_Or_Make(char const *name)
{
    if (_stricmp("<none>", name) == 0 || _stricmp("none", name) == 0) {
        return 0;
    }
    for (int index = 0; index < BuildingTypes.Count(); index++) {
        if (_stricmp(BuildingTypes[index]->ID, name) == 0) {
            return BuildingTypes[index];
        }
    }
    return new BuildingTypeClass(name);
}
