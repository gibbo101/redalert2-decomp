// static UnitTypeClass *__fastcall UnitTypeClass::Find_Or_Make(char const *name) (0x0070B540)
// The type with this ID, a new one when unknown, 0 for "<none>"/"none".
#include "shared/unit_type.hpp"
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc
// @ref __stricmp=00781f20
// @ref ??_C@_04KIKH@none?$AA@=007ce0ec
// @ref ?UnitTypes@@3V?$DynamicVectorClass@PAVUnitTypeClass@@@@A=00a35d48
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0UnitTypeClass@@QAE@PBD@Z=0070a600

UnitTypeClass *__fastcall UnitTypeClass::Find_Or_Make(char const *name)
{
    if (_stricmp("<none>", name) == 0 || _stricmp("none", name) == 0) {
        return 0;
    }
    for (int index = 0; index < UnitTypes.Count(); index++) {
        if (_stricmp(UnitTypes[index]->ID, name) == 0) {
            return UnitTypes[index];
        }
    }
    return new UnitTypeClass(name);
}
