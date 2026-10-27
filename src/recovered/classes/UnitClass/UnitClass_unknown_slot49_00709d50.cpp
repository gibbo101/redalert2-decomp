// bool UnitClass::unknown_slot49(HouseClass *house) (0x00709D50, slot 49)
// arg1 is a house. True while slot 48 holds, the house is not allied with
// the owner, its bit 0x0047C300 of this cell is clear, and the disguise's
// house (+0x410) is that house, none, or one of its allies.
#include "shared/unit.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Is_Ally@HouseClass@@QBE_NPBV1@@Z=004e5540
// @ref ?unknown_47c300@CellClass@@QBE_NH@Z=0047c300

bool UnitClass::unknown_slot49(HouseClass *house)
{
    if (unknown_slot48()) {
        Cell position = Coord_Cell(Center_Coord());
        CellClass &cell = Map[position];
        if (!House->Is_Ally(house) && !cell.unknown_47c300(house->ArrayIndex)) {
            HouseClass *disguise = (HouseClass *)unknown_410;
            if (disguise == house || !disguise || house->Is_Ally(disguise)) {
                return true;
            }
        }
    }
    return false;
}
