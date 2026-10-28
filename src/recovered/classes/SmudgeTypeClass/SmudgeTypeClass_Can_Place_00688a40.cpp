// bool SmudgeTypeClass::Can_Place(Cell const &cell, bool arg2) const (0x00688A40)
// True when every cell of the Width x Height block at the cell lies on the
// map, has no smudge, overlay or blocking flag, is unoccupied (unless arg2)
// and has a tile type that accepts smudges.
#include "shared/smudge_type.hpp"
#include "shared/map_view.hpp"
#include "shared/isometric_tile.hpp"
// @ref ?Unknown_0054AAB0@MapClass@@QAE_NABVCell@@@Z=0054aab0
// @ref ?unknown_4717b0@CellClass@@QBEPAVObjectClass@@XZ=004717b0
// @ref ?IsoTileTypes@@3V?$DynamicVectorClass@PAVIsometricTileTypeClass@@@@A=00a40cd0

bool SmudgeTypeClass::Can_Place(Cell const &cell, bool arg2) const
{
    for (int y = 0; y < Height; y++) {
        for (int x = 0; x < Width; x++) {
            Cell pos = cell + Cell(x, y);
            CellClass &here = Map[pos];
            if (!Map.Unknown_0054AAB0(cell) || here.unknown_11c || here.SmudgeIndex != -1 || here.OverlayIndex != -1) {
                return false;
            }
            if (!arg2 && here.unknown_4717b0() != 0) {
                return false;
            }
            int tile = here.IsoTileIndex;
            if (tile < 0 || tile >= IsoTileTypes.Count()) {
                tile = 0;
            }
            if (!IsoTileTypes[tile]->unknown_2b0) {
                return false;
            }
        }
    }
    return true;
}
