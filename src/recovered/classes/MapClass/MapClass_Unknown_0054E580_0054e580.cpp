// bool MapClass::Unknown_0054E580(Cell cell, int arg2) (0x0054E580)
// Places a crate near a cell: the nearest reachable cell for speed type 5 on
// water (cell land type 2) or 1 elsewhere (0x005502E0), the first free entry
// of the +0x154 table (cell unknown_cell_a6f238) creates the crate there
// (0x004939A0), and unless arg2 is 0x14 the cell's +0x11E takes arg2.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
// @ref ?Unknown_004939A0@UnknownMapEntry154@@QAE_NAAVCell@@@Z=004939a0

bool MapClass::Unknown_0054E580(Cell cell, int arg2)
{
    if (Map[cell].unknown_ec == 2) {
        cell = Map.Unknown_005502E0(cell, 5, -1, 0, false, Point2D(1, 1), 0, 0, 0, 1, Cell(0, 0), 0);
    } else {
        cell = Map.Unknown_005502E0(cell, 1, -1, 0, false, Point2D(1, 1), 0, 0, 0, 1, Cell(0, 0), 0);
    }

    int index;
    for (index = 0; index < 256; index++) {
        if (unknown_154[index].Cell == unknown_cell_a6f238) {
            break;
        }
    }
    if (index == 256) {
        return false;
    }

    if (unknown_154[index].Unknown_004939A0(cell)) {
        if (arg2 != 0x14) {
            Map[cell].OverlayData = arg2;
        }
        return true;
    }
    return false;
}
