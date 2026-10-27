// void BuildingClass::unknown_slot290(Cell cell) (0x004507B0, slot 290)
// While slot 195 holds, marks the cells within the type's DetectDisguiseRange
// of a cell (this building's own cell for the zero cell) for the owning
// house (0x0047C380).
#include "shared/building.hpp"
#include "shared/house.hpp"
#include "shared/gscreen.hpp"
#include "shared/techno_map.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0047C380@UnknownCellClass@@QAEXH@Z=0047c380

void BuildingClass::unknown_slot290(Cell cell)
{
    if (unknown_slot195()) {
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
                object->Unknown_0047C380(house);
                }
            }
        }
    }
}
