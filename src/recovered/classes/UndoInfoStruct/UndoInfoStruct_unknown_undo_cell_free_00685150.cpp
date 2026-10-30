// bool __fastcall unknown_undo_cell_free_685150(CellClass *cell) (0x00685150)
// Whether the cell is free: every occupier with unknown_7d set is of kind
// 0x0F or 1, there is no second occupier, flag bits 0x500 are clear, the
// cell north (adjacent 0) is not blocked unless its 0x800 bit is set, the
// cell at adjacent 6 is blocked only with the 0x800 bit, there is no
// overlay, MapClass::Unknown_0054AAB0 accepts it and its tile type allows it.
#include "shared/cell.hpp"
#include "shared/object.hpp"
#include "shared/map_view.hpp"
#include "shared/adjacent_cell.hpp"
#include "shared/isometric_tile.hpp"
#include "shared/isometric_tile_type.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070
// @ref ?Unknown_0054AAB0@MapClass@@QAE_NABVCell@@@Z=0054aab0
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70
// @ref ?IsoTileTypes@@3V?$DynamicVectorClass@PAVIsometricTileTypeClass@@@@A=00a40cd0

bool __fastcall unknown_undo_cell_free_685150(CellClass *cell)
{
    for (ObjectClass *object = cell->OccupierPtr; object != 0; object = object->unknown_30) {
        if (object->unknown_7d && object->Kind_Of() != 0x0F && object->Kind_Of() != 1) {
            return false;
        }
    }
    if (cell->AltOccupierPtr == 0 && !(cell->unknown_140 & 0x500)) {
        unsigned int flags = Map[AdjacentCell[0] + cell->MapCoords].unknown_140;
        if (!(flags & 0x500) || !(flags & 0x800)) {
            flags = Map[cell->MapCoords + AdjacentCell[6]].unknown_140;
            if (!(flags & 0x500) || (flags & 0x800)) {
                if (cell->OverlayIndex == -1 && Map.Unknown_0054AAB0(cell->MapCoords)) {
                    int tile = cell->IsoTileIndex;
                    if (tile < IsoTileTypes.Count() && tile != 0xFFFF) {
                        return IsoTileTypes[tile]->unknown_2b0;
                    }
                    return true;
                }
            }
        }
    }
    return false;
}
