// IsometricTileTypeClass *IsometricTileTypeClass::Next_Tile_From_Set(int index) (0x00529520)
#include "shared/isometric_tile_type.hpp"

IsometricTileTypeClass *IsometricTileTypeClass::Next_Tile_From_Set(int index)
{
    int num = NumTileTypesInSet;
    int i = index;
    if (i > num - 1) {
        i = i % num;
    }
    if (i == 0) {
        return this;
    }
    IsometricTileTypeClass *next = this;
    do {
        next = (IsometricTileTypeClass *)next->unknown_28c;
    } while (--i != 0);
    return next;
}
