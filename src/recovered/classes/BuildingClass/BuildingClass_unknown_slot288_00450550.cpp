// void BuildingClass::unknown_slot288(Cell cell) (0x00450550, slot 288)
// The cells within the type's SensorsSight of a cell (this building's
// own cell for the zero cell) for the owning house (0x0047C360): units there
// are told (slot 238).
#include "shared/building.hpp"
#include "shared/house.hpp"
#include "shared/gscreen.hpp"
#include "shared/techno_map.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0047C360@UnknownCellClass@@QAEXH@Z=0047c360

void BuildingClass::unknown_slot288(Cell cell)
{
    if (!unknown_slot195()) {
        return;
    }
    int range = Type->SensorsSight;
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
                object->Unknown_0047C360(house);
                for (ObjectClass *occupier = object->unknown_e4; occupier != 0; occupier = occupier->unknown_30) {
                    int kind = occupier->Kind_Of();
                    if (kind == 1 || kind == 15 || kind == 2) {
                        ((TechnoClass *)occupier)->unknown_slot238();
                    }
                }
            }
        }
    }
}
