// bool IsometricTileTypeClass::Is_Randomized(int tile) const (0x0052B730)
#include "shared/isometric_tile_type.hpp"

bool IsometricTileTypeClass::Is_Randomized(int tile) const
{
    IsoTileImageStruct const *image = (IsoTileImageStruct const *)unknown_slot39();
    if (image != 0) {
        IsoTileCellStruct const *record = (IsoTileCellStruct const *)image->Tiles[tile % (image->unknown_00[0] * image->unknown_00[1])];
        if (record != 0) {
            return record->IsRandomized;
        }
    }
    return 0;
}
