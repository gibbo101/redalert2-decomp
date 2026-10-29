// ObjectClass *__fastcall Building_Or_Terrain_At_006B0E40(CoordStruct const &coord) (0x006B0E40)
// The object in the cell of a coordinate: its building, else its terrain object; none for the unset cell (name hypothesis).
#include "shared/taction.hpp"
#include "shared/object.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_view.hpp"
// @ref ?unknown_4717b0@CellClass@@QBEPAVObjectClass@@XZ=004717b0
// @ref ?Cell_Terrain@CellClass@@QBEPAVObjectClass@@_N@Z=004717e0
// @ref ?unknown_cell_abfdb0@@3VCell@@A=00abfdb0
extern Cell unknown_cell_abfdb0;   // 0x00ABFDB0
// The building in a cell, else its terrain object (inline; name hypothesis).
inline ObjectClass *Building_Or_Terrain(CellClass &cellobj)
{
    ObjectClass *found = cellobj.unknown_4717b0();
    if (found == 0) {
        found = cellobj.Cell_Terrain(false);
    }
    return found;
}

// Execute calls it out of line; the waypoint sound actions after it inline it.
ObjectClass *__fastcall Building_Or_Terrain_At_006B0E40(CoordStruct const &coord)
{
    Cell cell = Coord_Cell(coord);
    ObjectClass *found = 0;
    if (cell != unknown_cell_abfdb0) {
        found = Building_Or_Terrain(Map[cell]);
    }
    return found;
}
