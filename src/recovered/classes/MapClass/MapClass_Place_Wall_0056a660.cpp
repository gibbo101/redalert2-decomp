// void MapClass::Unknown_0056A660(Cell const &cell, HouseClass *house, BuildingTypeClass *type) (0x0056A660)
// Joins a new wall to the house's walls (TibSun Place_Wall): for a type with a wall
// overlay (+0xBEC), looks along each of the four straight directions up to the type's
// ThreatRange cells for a cell with that overlay owned by the house (+0x50), and fills
// the gap with new buildings of the type (slot 35, placed with slot 53); a cell where
// the type may not be placed (0x004718B0) ends the direction. `range` and `cellptr` are
// real symbols of the function: both operand orders depend on the symbol count mod 8.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_techno.hpp"
#include "shared/map_adjacent.hpp"
#include "shared/house_screen.hpp"
// @ref ?unknown_4718b0@CellClass@@QAE_NHPBVBuildingTypeClass@@PAVHouseClass@@@Z=004718b0

void MapClass::Unknown_0056A660(Cell const &cell, HouseClass *house, BuildingTypeClass *type)
{
    OverlayTypeClass const *overtype = type->ToOverlay;
    if (overtype == 0) {
        return;
    }

    for (int dir = 0; dir < 8; dir += 2) {
        Cell current_cell = cell;
        int range = type->ThreatRange;
        int radius = range >> 8;

        for (int distance = 0; distance < radius; distance++) {
            current_cell = (Cell)Adjacent_Cell(current_cell, dir);

            int overlay = Map[current_cell].OverlayIndex;
            if (overlay != -1 && overtype->unknown_264 == overlay && house->ArrayIndex == Map[current_cell].unknown_50) {
                if (distance > 0) {
                    Cell place_cell = (Cell)Adjacent_Cell_L(cell, dir);
                    for (int i = 0; i < distance; i++) {
                        ObjectClass *building = type->unknown_slot35(house);
                        building->unknown_slot53(place_cell, 0);
                        place_cell = (Cell)Adjacent_Cell((Cell)place_cell, dir);
                    }
                }
                break;
            }

            CellClass *cellptr = &Map[current_cell];
            if (!cellptr->unknown_4718b0(type->Speed, type, house)) {
                break;
            }
        }
    }
}
