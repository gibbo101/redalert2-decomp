// int __fastcall Straight_Shore_Length(CellClass *cellptr, int direction) (0x0055CB00)
// Counts the cells of a straight shore (TibSun name): from the cell's neighbour
// along the facing snapped to east or south, while that side is land and the
// cell beyond it toward `direction` is water (0x0047A270).
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
// @ref ?unknown_47a270@CellClass@@QAE_NXZ=0047a270

int __fastcall Straight_Shore_Length(CellClass *cellptr, int direction)
{
    int snap[4] = {
        2,
        4,
        2,
        4,
    };

    int count = 1;
    int s_direction = snap[direction / 2];
    CellClass *adj1 = &cellptr->Adjacent_Cell(s_direction);
    CellClass *adj2 = &adj1->Adjacent_Cell(direction);
    bool side_1_is_land = adj1->unknown_47a270() == false;
    bool side_2_is_water = adj2->unknown_47a270();

    while (side_1_is_land && side_2_is_water) {
        count++;
        adj1 = &adj1->Adjacent_Cell(s_direction);
        adj2 = &adj2->Adjacent_Cell(s_direction);
        side_1_is_land = adj1->unknown_47a270() == false;
        side_2_is_water = adj2->unknown_47a270();
    }

    return count;
}
