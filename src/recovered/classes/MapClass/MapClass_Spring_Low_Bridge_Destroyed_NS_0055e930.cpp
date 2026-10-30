// void MapClass::Spring_Low_Bridge_Destroyed_NS(Cell cell) (0x0055E930)
// Springs the destruction triggers of a north/south low bridge (TibSun name):
// the bridge's span runs from the last low bridge cell (0x00562930) north of
// the cell to the last one south of it (0x00558340).
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_adjacent.hpp"
// @ref ?Spring_Bridge_Destruction_Triggers@MapClass@@QAEXVCell@@0@Z=00558340

void MapClass::Spring_Low_Bridge_Destroyed_NS(Cell cell)
{
    Cell tmp = cell;
    do {
        tmp = Adjacent_Cell_XY(tmp, 0);
    } while (Unknown_00562930(tmp));

    Cell start = Adjacent_Cell_XY(tmp, 4);

    tmp = cell;
    do {
        tmp = Adjacent_Cell_XY(tmp, 4);
    } while (Unknown_00562930(tmp));

    Cell end = Adjacent_Cell_XY(tmp, 0);

    Spring_Bridge_Destruction_Triggers(start, end);
}
