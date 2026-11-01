// bool IsometricTileTypeClass::Is_Tile_Index_Valid(int tile, bool load) (0x00529340)
#include "shared/isometric_tile_type.hpp"

bool IsometricTileTypeClass::Is_Tile_Index_Valid(int tile, bool load)
{
    if (load) {
        Load_Tile_Image();
    }
    IsoTileImageStruct const *image = (IsoTileImageStruct const *)unknown_slot39();
    if (image != 0 && tile < image->unknown_00[0] * image->unknown_00[1] && image->Tiles[tile] != 0) {
        return true;
    }
    return false;
}
