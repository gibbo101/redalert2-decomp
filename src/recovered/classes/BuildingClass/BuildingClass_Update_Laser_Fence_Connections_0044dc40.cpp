// void BuildingClass::unknown_44dc40(int explode) 0x0044DC40 (TibSun building.cpp
// Update_Laser_Fence_Connections): records which sides of a laser fence post carry fence of
// its owner and removes those runs (0x0044E260 Disconnect_Laser_Fence).
#include "shared/building.hpp"
#include "shared/cell_class.hpp"
#ifndef RA2_ADJACENT_CELL
#define RA2_ADJACENT_CELL
#include "shared/adjacent_cell.hpp"
inline Cell Adjacent_Cell(Cell const &cell, int facing)
{
    Cell const &offset = AdjacentCell[facing & 7];
    return Cell(cell.X + offset.X, cell.Y + offset.Y);
}
#endif
// @ref ?unknown_a40774@@3HA=00a40774
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70
// @ref _?_facing_bits@?7??unknown_44dc40@BuildingClass@@QAEXH@Z@4PAHA=007cf648
void BuildingClass::unknown_44dc40(int explode)
{
    if (!unknown_a40774 && Type->LaserFencePost) {
        bool do_explode = false;
        if (explode == (int)true) {
            do_explode = true;
        }
        int dir = 0;
        Cell origin = Cell(Center_Coord());

        static int _facing_bits[] = { 1 << 0, 1 << 1, 1 << 2, 1 << 3 };

        for (int i = 0; i < 4; i++) {
            Cell adjacent = Adjacent_Cell(origin, dir);
            BuildingClass *building = (BuildingClass *)Map[adjacent].unknown_4717b0();
            if (building != 0 && building->Type->LaserFence) {
                if (Owner() == building->Owner()) {
                    if (((((*(unsigned const *)&building->unknown_2e0.Current()) >> 12) + 1) >> 1 & 3) == (dir & 3)) {
                        unknown_4ec |= _facing_bits[i];
                        unknown_44e260(dir, do_explode);
                    }
                }
            }
            dir = (dir + 2) & 7;
        }
    }
}
