// static int __fastcall InfantryTypeClass::From_Name(char const *name) (0x0050A070)
// Index of the type with this ID (case-insensitive), or -1 (also for
// "<none>" and "none").
#include "shared/infantry_type.hpp"
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc
// @ref __stricmp=00781f20
// @ref ??_C@_04KIKH@none?$AA@=007ce0ec
// @ref ?InfantryTypes@@3V?$DynamicVectorClass@PAVInfantryTypeClass@@@@A=00a40350

int __fastcall InfantryTypeClass::From_Name(char const *name)
{
    if (_stricmp(name, "<none>") == 0 || _stricmp(name, "none") == 0) {
        return -1;
    }
    for (int index = 0; index < InfantryTypes.Count(); index++) {
        if (_stricmp(InfantryTypes[index]->ID, name) == 0) {
            return index;
        }
    }
    return -1;
}
