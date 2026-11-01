// int IsometricTileTypeClass::Fixup_Tile_Type(int type) (0x00529550)
#include "shared/isometric_tile_type.hpp"

int __fastcall IsometricTileTypeClass::Fixup_Tile_Type(int type)
{
    int new_type = type;
    if (type == 0xFFFF) {
        return new_type;
    }
    for (int i = 0; i < TileInsertTypes.Count(); i++) {
        TileInsertType *tileinsert = TileInsertTypes[i];
        if (tileinsert->Count > type) {
            break;
        }
        new_type += tileinsert->Offset;
    }
    return new_type;
}
