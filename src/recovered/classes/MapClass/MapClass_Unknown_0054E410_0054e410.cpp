// bool MapClass::Unknown_0054E410() (0x0054E410)
// Places a crate on a random cell (TibSun Place_Random_Crate): the first +0x154 entry whose
// cell is unknown_cell_a6f238; up to 1000 random cells inside the map's cell rectangle, each
// moved to a reachable cell nearby (0x005502E0; speed type 5 on water, land type 2, else 1)
// and offered to the entry (0x004939A0). False when no entry is free or no cell took the crate.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/id_source.hpp"
// @ref ?Unknown_004939A0@UnknownMapEntry154@@QAE_NAAVCell@@@Z=004939a0
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0

bool MapClass::Unknown_0054E410()
{
    int crateindex = 0;
    for (crateindex = 0; crateindex < 256; crateindex++) {
        if (unknown_154[crateindex].Cell == unknown_cell_a6f238) break;
    }
    if (crateindex == 256) {
        return false;
    }

    for (int index = 0; index < 1000; index++) {
        int x = Map.unknown_120 + Random_Pick(0, Map.unknown_128 - 1);
        int y = Map.unknown_124 + Random_Pick(0, Map.unknown_12c - 1);
        Cell cell = XY_Cell(x, y);

        if (Map[cell].unknown_ec == 2) {
            cell = Map.Unknown_005502E0(cell, 5, -1, 0, false, Point2D(1, 1), false, false, false, true, Cell(0, 0), 0);
        } else {
            cell = Map.Unknown_005502E0(cell, 1, -1, 0, false, Point2D(1, 1), false, false, false, true, Cell(0, 0), 0);
        }

        if (unknown_154[crateindex].Unknown_004939A0(cell)) {
            return true;
        }
    }
    return false;
}
