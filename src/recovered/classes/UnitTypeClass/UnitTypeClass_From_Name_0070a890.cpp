// static int __fastcall UnitTypeClass::From_Name(char const *name) (0x0070A890)
// Index of the type with this ID (case-insensitive), or -1.
#include "shared/unit_type.hpp"
// @ref ?UnitTypes@@3V?$DynamicVectorClass@PAVUnitTypeClass@@@@A=00a35d48
// @ref __stricmp=00781f20

int __fastcall UnitTypeClass::From_Name(char const *name)
{
    if (name) {
        for (int index = 0; index < UnitTypes.Count(); index++) {
            if (_stricmp(UnitTypes[index]->ID, name) == 0) {
                return index;
            }
        }
    }
    return -1;
}
