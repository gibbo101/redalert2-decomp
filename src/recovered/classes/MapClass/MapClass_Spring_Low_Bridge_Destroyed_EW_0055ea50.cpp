// void MapClass::Spring_Low_Bridge_Destroyed_EW(Cell cell) (0x0055EA50)
// Springs the destruction triggers of an east/west low bridge (TibSun name):
// the bridge's span runs from the last low bridge cell (0x00562930) west of
// the cell to the last one east of it (0x00558340).
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_adjacent.hpp"
// @ref ?Spring_Bridge_Destruction_Triggers@MapClass@@QAEXVCell@@0@Z=00558340

void MapClass::Spring_Low_Bridge_Destroyed_EW(Cell cell)
{
    Cell tmp = cell;
    do {
        tmp = Adjacent_Cell_XY(tmp, 6);
    } while (Unknown_00562930(tmp));

    Cell start = Adjacent_Cell_XY(tmp, 2);

    tmp = cell;
    do {
        tmp = Adjacent_Cell_XY(tmp, 2);
    } while (Unknown_00562930(tmp));

    Cell end = Adjacent_Cell_XY(tmp, 6);

    Spring_Bridge_Destruction_Triggers(start, end);
}
