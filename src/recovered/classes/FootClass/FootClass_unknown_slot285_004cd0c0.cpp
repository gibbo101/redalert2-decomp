// void FootClass::unknown_slot285(Cell cell) (0x004CD0C0)
// Enters the cells within the type's SensorsSight of a cell (the unit's own
// cell for the zero cell) for the owning house (0x0047C360):
// units there are told (slot 238) and a building of another house than the
// player's that answers slot 25 is flagged (+0x75).
#include "shared/foot.hpp"
#include "shared/house.hpp"
#include "shared/techno_type.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0047C360@UnknownCellClass@@QAEXH@Z=0047c360
// @ref ?Unknown_004717B0@UnknownCellClass@@QAEPAVBuildingClass@@XZ=004717b0
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4

void FootClass::unknown_slot285(Cell cell)
{
    int range = unknown_slot32()->SensorsSight;
    int range_squared = range * range;
    int house = House->ArrayIndex;
    if (cell == unknown_geometry_k) {
        cell = Coord_Cell(Center_Coord());
    }
    for (int y = -range; y < range; y++) {
        for (int x = -range; x < range; x++) {
            Cell spot = Cell(cell.X + x, cell.Y + y);
            if (x * x + y * y < range_squared) {
                UnknownCellClass *object = (UnknownCellClass *)&Map[spot];
                object->Unknown_0047C360(house);
                for (ObjectClass *occupier = object->unknown_e4; occupier != 0; occupier = occupier->unknown_30) {
                    int kind = occupier->Kind_Of();
                    if (kind == 1 || kind == 15 || kind == 2) {
                        ((TechnoClass *)occupier)->unknown_slot238();
                    }
                }
                BuildingClass *building = object->Unknown_004717B0();
                if (building != 0 && building->House != unknown_player_a35db4 && building->unknown_slot25(false, 0)) {
                    building->unknown_75 = true;
                }
            }
        }
    }
}
