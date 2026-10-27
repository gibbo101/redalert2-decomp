// bool InfantryClass::unknown_slot49(HouseClass *house) (0x00509390, slot 49)
// True when slot 48 holds, house is not allied to the owner, the cell under
// the infantry fails the cell test 0x0047C300 for house, and +0x410 is
// unset, house itself, or allied to house.
#include "shared/infantry.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Is_Ally@HouseClass@@QBE_NPBV1@@Z=004e5540
// @ref ?unknown_47c300@UnknownCellClass@@QAE_NH@Z=0047c300

bool InfantryClass::unknown_slot49(HouseClass *house)
{
    if (unknown_slot48()) {
        Cell cell = Coord_Cell(Center_Coord());
        UnknownCellClass *object = (UnknownCellClass *)&Map[cell];
        if (!House->Is_Ally(house) && !object->unknown_47c300(house->ArrayIndex)) {
            if (unknown_410 == house || unknown_410 == 0 || house->Is_Ally(unknown_410)) {
                return true;
            }
        }
    }
    return false;
}
