// void MapClass::Spring_Bridge_Destruction_Triggers(Cell cell1, Cell cell2) (0x00558340)
// TibSun Spring_Bridge_Destruction_Triggers: walks the span from the lower end to the
// higher one and springs the bridge-destroyed event (0x1F) on the tags of each cell and
// of the cells beside it (one on one side, two on the other).
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_adjacent.hpp"
#include "shared/map_techno.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_cell_a6f238@@3VCell@@A=00a6f238

inline void Swap_Cells(Cell &first, Cell &second)
{
    Cell temp(first);
    first = second;
    second = temp;
}

void MapClass::Spring_Bridge_Destruction_Triggers(Cell cell1, Cell cell2)
{
    bool is_east_west = false;

    if (cell1.Y == cell2.Y) {
        is_east_west = true;
        if (cell1.X > cell2.X) {
            Swap_Cells(cell1, cell2);
        }
    } else if (cell1.Y > cell2.Y) {
        Swap_Cells(cell1, cell2);
    }

    Cell current = cell1;
    Cell end = cell2;
    while (current != end) {
        CellClass *cptr = &Map[current];
        if (cptr->unknown_3c != 0) {
            cptr->unknown_3c->Spring(0x1F, 0, unknown_cell_a6f238);
        }

        if (is_east_west) {
            cptr = &Map[Adjacent_Cell(current, 4)];
            if (cptr->unknown_3c != 0) {
                cptr->unknown_3c->Spring(0x1F, 0, unknown_cell_a6f238);
            }
            cptr = &Map[Adjacent_Cell(current, 0)];
            if (cptr->unknown_3c != 0) {
                cptr->unknown_3c->Spring(0x1F, 0, unknown_cell_a6f238);
            }
            cptr = &Map[Adjacent_Cell(cptr->MapCoords, 0)];
            if (cptr->unknown_3c != 0) {
                cptr->unknown_3c->Spring(0x1F, 0, unknown_cell_a6f238);
            }
            current.X++;
        } else {
            cptr = &Map[Adjacent_Cell(current, 2)];
            if (cptr->unknown_3c != 0) {
                cptr->unknown_3c->Spring(0x1F, 0, unknown_cell_a6f238);
            }
            cptr = &Map[Adjacent_Cell(current, 6)];
            if (cptr->unknown_3c != 0) {
                cptr->unknown_3c->Spring(0x1F, 0, unknown_cell_a6f238);
            }
            cptr = &Map[Adjacent_Cell(cptr->MapCoords, 6)];
            if (cptr->unknown_3c != 0) {
                cptr->unknown_3c->Spring(0x1F, 0, unknown_cell_a6f238);
            }
            current.Y++;
        }
    }
}
