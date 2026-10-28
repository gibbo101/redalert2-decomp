// Cell const *IsometricTileTypeClass::unknown_slot36(int arg1) const (0x00529450)
// The occupation list: every cell of the image's grid that has a tile, then
// the 0x7FFF end marker (a function-local static list, not initialized).
#include "shared/isometric_tile_type.hpp"
// @ref _?$S40@?1??unknown_slot36@IsometricTileTypeClass@@UBEPBVCell@@H@Z@4EA=00a52e88
// @ref _?list@?1??unknown_slot36@IsometricTileTypeClass@@UBEPBVCell@@H@Z@4PAUUnknownStaticCell@@A=00a52c84
// @ref _$E41=00529510
// @ref _atexit=0078298a

Cell const *IsometricTileTypeClass::unknown_slot36(int arg1) const
{
    static UnknownStaticCell list[129];
    IsoTileImageStruct const *image = (IsoTileImageStruct const *)unknown_slot39();
    int const *tile = image->Tiles;
    UnknownStaticCell *cell = list;
    for (int index = 0; index < unknown_2b4 * unknown_2b8; index++) {
        if (*tile++ != 0) {
            cell->Cell = Cell(index % unknown_2b4, index / unknown_2b4);
            cell++;
        }
    }
    cell->Cell = Cell(0x7FFF, 0x7FFF);
    return &list[0].Cell;
}
