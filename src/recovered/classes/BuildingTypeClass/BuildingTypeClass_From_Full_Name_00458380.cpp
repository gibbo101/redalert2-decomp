// static int __fastcall BuildingTypeClass::From_Full_Name(char const *name) (0x00458380)
// Index of the type whose Name= matches (case-insensitive), or -1.
#include "shared/building_type.hpp"
// @ref ?BuildingTypes@@3V?$DynamicVectorClass@PAVBuildingTypeClass@@@@A=00a35cd8
// @ref __stricmp=00781f20

int __fastcall BuildingTypeClass::From_Full_Name(char const *name)
{
    if (name) {
        for (int index = 0; index < BuildingTypes.Count(); index++) {
            if (_stricmp(BuildingTypes[index]->Name, name) == 0) {
                return index;
            }
        }
    }
    return -1;
}
