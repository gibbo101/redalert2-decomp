// void MapClass::Unknown_0056A480(Cell const &cell, HouseClass *house, BuildingTypeClass *type) (0x0056A480)
// Joins a new firestorm wall to the house's (TibSun Place_Firestorm_Wall): looks along
// each of the four straight directions up to the type's ThreatRange cells for a
// firestorm wall building (type +0x135A) of the house, and fills the gap with new
// buildings of the type (slot 35, placed with slot 53); a cell where the type may not be
// placed (0x004718B0) ends the direction.
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_techno.hpp"
#include "shared/map_adjacent.hpp"
#include "shared/house_screen.hpp"
// @ref ?unknown_4718b0@CellClass@@QAE_NHPBVBuildingTypeClass@@PAVHouseClass@@@Z=004718b0
// @ref ?unknown_4717b0@CellClass@@QBEPAVObjectClass@@XZ=004717b0

void MapClass::Unknown_0056A480(Cell const &cell, HouseClass *house, BuildingTypeClass *type)
{
    for (int dir = 0; dir < 8; dir += 2) {
        Cell current_cell = cell;
        int radius = type->ThreatRange >> 8;

        for (int distance = 0; distance < radius; distance++) {
            current_cell = (Cell)Adjacent_Cell(current_cell, dir);

            BuildingClass *building = (BuildingClass *)Map[current_cell].unknown_4717b0();
            if (building != 0 && building->Type->FirestormWall && building->House == house) {
                if (distance > 0) {
                    Cell place_cell = (Cell)Adjacent_Cell(cell, dir);
                    for (int i = 0; i < distance; i++) {
                        ObjectClass *object = type->unknown_slot35(house);
                        object->unknown_slot53(place_cell, 0);
                        place_cell = (Cell)Adjacent_Cell(place_cell, dir);
                    }
                }
                break;
            }

            if (!Map[current_cell].unknown_4718b0(type->Speed, type, house)) {
                break;
            }
        }
    }
}
