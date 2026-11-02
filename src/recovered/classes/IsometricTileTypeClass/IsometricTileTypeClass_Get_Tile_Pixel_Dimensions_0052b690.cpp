// bool IsometricTileTypeClass::Get_Tile_Pixel_Dimensions(int, int &, int &) (0x0052B690)
#include "shared/isometric_tile_type.hpp"

bool IsometricTileTypeClass::Get_Tile_Pixel_Dimensions(int tile, int &width, int &height)
{
    IsoTileImageStruct const *image = (IsoTileImageStruct const *)unknown_slot39();
    if (image != 0) {
        IsoTileCellStruct const *record = (IsoTileCellStruct const *)image->Tiles[tile % (image->unknown_00[0] * image->unknown_00[1])];
        width = image->unknown_00[2];
        height = image->unknown_00[3];
        if (record != 0) {
            if (record->IsHasExtraData) {
                height += record->Y - record->ExtraY;
            }
        }
        return true;
    }
    return false;
}
