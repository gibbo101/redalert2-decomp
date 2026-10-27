// Test flag 0x400000 on every cell of the building foundation.
#include "shared/building.hpp"
#include "shared/gscreen.hpp"
#include "shared/building_map.hpp"
#include "shared/cell.hpp"
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070
bool BuildingClass::unknown_452be0()
{
    Cell origin = unknown_slot104();
    Cell const *foundation = Type->unknown_slot36(0);
    bool all_cells_have_flag = true;
    do {
        if (foundation->X == 0x7fff && foundation->Y == 0x7fff)
            break;
        Cell cell((short)(origin.X + foundation->X),
                  (short)(origin.Y + foundation->Y));
        if (!(Cell_At(cell).unknown_140 & 0x400000)) {
            all_cells_have_flag = false;
            break;
        }
        ++foundation;
    } while (true);
    if (!all_cells_have_flag)
        return false;
    return true;
}
