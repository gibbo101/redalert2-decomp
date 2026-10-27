// static InfantryTypeClass *__fastcall InfantryTypeClass::Find_Or_Make(char const *name) (0x0050AED0)
// The type with this ID, a new one when unknown, 0 for "<none>"/"none".
#include "shared/infantry_type.hpp"
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc
// @ref __stricmp=00781f20
// @ref ??_C@_04KIKH@none?$AA@=007ce0ec
// @ref ?InfantryTypes@@3V?$DynamicVectorClass@PAVInfantryTypeClass@@@@A=00a40350
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0InfantryTypeClass@@QAE@PBD@Z=00509b20

InfantryTypeClass *__fastcall InfantryTypeClass::Find_Or_Make(char const *name)
{
    if (_stricmp("<none>", name) == 0 || _stricmp("none", name) == 0) {
        return 0;
    }
    for (int index = 0; index < InfantryTypes.Count(); index++) {
        if (_stricmp(InfantryTypes[index]->ID, name) == 0) {
            return InfantryTypes[index];
        }
    }
    return new InfantryTypeClass(name);
}
