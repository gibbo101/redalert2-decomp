// bool MapClass::Remove_Crate(Cell const &cell) (0x0054E6E0)
// Removes the crate at a cell (TibSun Remove_Crate): in the campaign a crate overlay
// (+0x27A of its type) is taken off the cell (+0x44 = -1, +0x11E = 0) and its overlay
// rectangles (0x00474EB0, 0x00475100) are redrawn; otherwise the +0x154 entry holding the
// cell removes its crate (0x00493930). False when there was no crate.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/overlay_view.hpp"
#include "shared/tactical.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?unknown_474eb0@CellClass@@QBE?AVRect@@XZ=00474eb0
// @ref ?unknown_475100@CellClass@@QBE?AVRect@@XZ=00475100
// @ref ?Register_Dirty_Area@Tactical@@QAEXVRect@@_N@Z=006a3020
// @ref ?Unknown_00493930@UnknownMapEntry154@@QAE_NXZ=00493930
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref ?unknown_int_839634@@3HA=00839634
// @ref ?unknown_overlay_types_a35de8@@3V?$DynamicVectorClass@PAUUnknownOverlayType@@@@A=00a35de8

bool MapClass::Remove_Crate(Cell const &cell)
{
    if (unknown_game_mode_a3d298 != 0) {
        for (int index = 0; index < 256; index++) {
            if (unknown_154[index].Cell != unknown_cell_a6f238 && cell == unknown_154[index].Cell) {
                return unknown_154[index].Unknown_00493930();
            }
        }
    } else {
        CellClass *cellptr = &(*this)[cell];
        if (cellptr->OverlayIndex != -1 && unknown_overlay_types_a35de8[cellptr->OverlayIndex]->unknown_27a) {
            Rect dirty = Union(cellptr->unknown_474eb0(), cellptr->unknown_475100());
            dirty.Y -= unknown_int_839634;
            unknown_tactical_83996c->Register_Dirty_Area(dirty, 0);
            cellptr->OverlayIndex = -1;
            cellptr->OverlayData = 0;
            return true;
        }
    }
    return false;
}
