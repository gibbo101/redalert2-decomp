// bool TechnoClass::unknown_slot192(HouseClass *house) (0x006D7C40, slot 192)
// Cell test 0x0047C2E0 for a house.
#include "shared/techno.hpp"
#include "shared/gscreen.hpp"
#include "shared/techno_map.hpp"
// @ref ?unknown_47c2e0@UnknownCellClass@@QAE_NH@Z=0047c2e0

bool TechnoClass::unknown_slot192(HouseClass *house)
{
    if (house) {
        return Map_Cell(Center_Coord())->unknown_47c2e0(house->ArrayIndex);
    }
    return false;
}
