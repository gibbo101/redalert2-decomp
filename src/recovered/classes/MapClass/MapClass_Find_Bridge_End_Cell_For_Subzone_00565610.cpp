// Select a bridge span end or side cell in the requested subzone, original00565610.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_adjacent.hpp"
#include "shared/cell_subzone.hpp"

Cell MapClass::Unknown_00565610(Cell const &cell, int layer, unsigned int subzone)
{
    CellClass *cellptr = &Map[cell];
    if (!(cellptr->unknown_140 & 0x100)) return cellptr->MapCoords;
    int facing = (cellptr->unknown_140 & 0x800) ? 2 : 4;
    int opposite = (facing - 4) & 7;
    CellClass *forward = cellptr;
    CellClass *back = cellptr;
    // Four-byte point-base view; the original local nominal type remains unknown.
    TPoint2D<short> front_end = unknown_cell_a6f238;
    Cell back_end = unknown_cell_a6f238;
    while (true) {
        if (forward->unknown_140 & 0x100) {
            forward = &forward->Adjacent_Cell(facing);
            if (!(forward->unknown_140 & 0x100) &&
                (forward->unknown_47b960() || forward->unknown_47b980()) && forward->unknown_ec != 3)
                front_end = forward->MapCoords;
        }
        if (back->unknown_140 & 0x100) {
            back = &back->Adjacent_Cell(opposite);
            if (!(back->unknown_140 & 0x100) &&
                (back->unknown_47b960() || back->unknown_47b980()) && back->unknown_ec != 3)
                back_end = back->MapCoords;
        }
        if (!(back->unknown_140 & 0x100) && !(forward->unknown_140 & 0x100)) break;
    }
    Cell candidates[6];
    candidates[0] = front_end;
    candidates[1] = Adjacent_Cell(front_end, (facing + 2) & 7);
    candidates[2] = Adjacent_Cell(front_end, (facing - 2) & 7);
    candidates[3] = back_end;
    candidates[4] = Adjacent_Cell(back_end, (facing + 2) & 7);
    candidates[5] = Adjacent_Cell(back_end, (facing - 2) & 7);
    for (int index = 0; index < 6; ++index) {
        Cell candidate = candidates[index];
        if (Map.Unknown_0055A660(candidate, true)) {
            int fine_index = Unknown_0054FAB0(candidate);
            CellSubzoneStruct *record = (CellSubzoneStruct *)unknown_6c + fine_index;
            if (record->SubzoneID[layer] == subzone)
                return candidate;
        }
    }
    return unknown_cell_a6f238;
}
