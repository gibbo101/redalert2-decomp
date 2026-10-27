// void BuildingClass::unknown_slot291(Cell cell) (0x004506B0, slot 291)
// Marks the cells within the type's DetectDisguiseRange of a cell (this
// building's own cell for the zero cell) for the owning house (0x0047C390).
#include "shared/building.hpp"
#include "shared/house.hpp"
#include "shared/gscreen.hpp"
#include "shared/techno_map.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0047C390@UnknownCellClass@@QAEXH@Z=0047c390

void BuildingClass::unknown_slot291(Cell cell)
{
    int range = Type->DetectDisguiseRange;
    int range_squared = range * range;
    int house = House->ArrayIndex;
    if (cell == unknown_geometry_k) {
        cell = Coord_Cell(Center_Coord());
    }
    for (int y = -range; y < range; y++) {
        for (int x = -range; x < range; x++) {
            Cell spot = Cell(cell.X + x, cell.Y + y);
            if (x * x + y * y < range_squared) {
                UnknownCellClass *object = Map_Cell_At(spot);
                object->Unknown_0047C390(house);
            }
        }
    }
}
