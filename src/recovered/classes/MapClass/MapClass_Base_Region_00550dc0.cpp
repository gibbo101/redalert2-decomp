// bool MapClass::Base_Region(Cell const &cell, int &house, int &zone) (0x00550DC0)
// The house whose base holds a cell (TibSun Base_Region): for a cell other than
// unknown_cell_a6f238 inside the map (0x0054AAB0), the first house in Houses not defeated
// (+0x13D) with a base centre (+0x53BC) whose zone for the cell (0x004EAEF0) is not -1;
// house takes its type's index (+0xB8), zone the zone. False when there is none.
#include "shared/map.hpp"
#include "shared/house_screen.hpp"
#include "shared/map_techno.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?Which_Zone@HouseClass@@QBEHABVCell@@@Z=004eaef0

bool MapClass::Base_Region(Cell const &cell, int &house, int &zone)
{
    if (cell != unknown_cell_a6f238 && Unknown_0054AAB0(cell)) {
        for (int index = 0; index < Houses.Count(); index++) {
            HouseClass *h = Houses[index];

            if (h && !h->unknown_13d && h->BaseCenter != unknown_geometry_l) {
                zone = h->Which_Zone(cell);
                if (zone != -1) {
                    house = h->Type->House;
                    return true;
                }
            }
        }
    }
    return false;
}
