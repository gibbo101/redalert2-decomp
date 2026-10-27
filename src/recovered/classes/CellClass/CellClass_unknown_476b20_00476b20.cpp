// void CellClass::unknown_476b20(int house, int value) (0x00476B20): passes
// the cell's map block (Map.Unknown_0054E370) and value to
// HouseClass::unknown_func_4e5dc0 of every other house that fails
// Unknown_004F52F0 or is not house's ally.
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/house.hpp"
// @ref ?Houses@@3V?$DynamicVectorClass@PAVHouseClass@@@@A=00a32298

void CellClass::unknown_476b20(int house, int value)
{
    Cell cell = MapCoords;
    int block = Map.Unknown_0054E370(cell);
    for (int index = 0; index < Houses.Count(); index++) {
        HouseClass *other = Houses[index];
        if (other != 0 && other->ArrayIndex != house
            && (!other->Unknown_004F52F0() || !other->Is_Ally(house))) {
            other->unknown_func_4e5dc0(block, value);
        }
    }
}
