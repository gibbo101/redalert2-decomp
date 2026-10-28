// static int __fastcall TerrainTypeClass::From_Name(char const *name) (0x006E5510)
// Index of the type with this ID (case-insensitive), or -1.
#include "shared/terrain_type.hpp"
// @ref __stricmp=00781f20

int __fastcall TerrainTypeClass::From_Name(char const *name)
{
    if (name != 0) {
        for (int index = 0; index < TerrainTypes.Count(); index++) {
            if (_stricmp(name, TerrainTypes[index]->ID) == 0) {
                return index;
            }
        }
    }
    return -1;
}
