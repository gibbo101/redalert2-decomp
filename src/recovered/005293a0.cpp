// bool IsometricTileTypeClass::Load_Tile_Image() (0x005293A0)
#include "shared/isometric_tile_type.hpp"

bool IsometricTileTypeClass::Load_Tile_Image()
{
    if (unknown_a4 == 0 && unknown_2c4) {
        unknown_func_52b560();
    }
    return unknown_a4 != 0;
}
