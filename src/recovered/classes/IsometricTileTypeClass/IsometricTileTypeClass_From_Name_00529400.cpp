// int IsometricTileTypeClass::From_Name(char const *name) (0x00529400)
#include "shared/isometric_tile_type.hpp"

int __fastcall IsometricTileTypeClass::From_Name(char const *name)
{
    if (name != 0) {
        for (int index = 0; index < IsoTileTypes.Count(); index++) {
            if (_stricmp(IsoTileTypes[index]->ID, name) == 0) {
                return index;
            }
        }
    }
    return 0xFFFF;
}
