// Whether this building makes the given occupied cell row impassable.
#include "shared/building.hpp"
#include "shared/cell.hpp"
// @ref ?unknown_4717b0@CellClass@@QBEPAVObjectClass@@XZ=004717b0
bool BuildingClass::Cell_Is_Impassable_Row_00453af0(CellClass const *cell)
{
    if (cell->unknown_4717b0() != this)
        return false;
    if (Type->NumberImpassableRows == -1)
        return true;
    int cell_x = cell->MapCoords.X;
    int origin_x = unknown_slot104().X;
    return (int)((unsigned int)Type->NumberImpassableRows + (unsigned int)origin_x) > cell_x ? true : false;
}
