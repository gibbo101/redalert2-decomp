// void IsometricTileTypeClass::Clear_Use_Counts() (0x0052B650)
#include "shared/isometric_tile_type.hpp"

void IsometricTileTypeClass::Clear_Use_Counts()
{
    IsometricTileTypeClass *type;
    for (int i = 0; i < IsoTileTypes.Count(); i++) {
        for (type = IsoTileTypes[i]; type != 0; type = (IsometricTileTypeClass *)type->unknown_28c) {
            type->UseCount = 0;
        }
    }
}
