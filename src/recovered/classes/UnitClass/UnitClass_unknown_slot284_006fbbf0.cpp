// bool UnitClass::unknown_slot284() (0x006FBBF0, slot 284)
// True for DeployToFire types; for a type that deploys into a tick-tank
// building, owned by a non-human house (0x004F52F0), with a unit at
// +0x228: whether the cell here allows building (0x0047CDD0).
#include "shared/unit.hpp"
#include "shared/building_type.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0
// @ref ?unknown_47cdd0@CellClass@@QBE_NXZ=0047cdd0

bool UnitClass::unknown_slot284()
{
    if (Type->DeployToFire) {
        return true;
    }
    if (Type->DeploysInto && Type->DeploysInto->TickTank && !House->Unknown_004F52F0() && unknown_228) {
        switch (unknown_228->What_Am_I()) {
        case 1:
        {
            CoordStruct coord = Coord;
            return Map[coord].unknown_47cdd0() ? true : false;
        }
        case 6:
        case 15:
            return false;
        }
    }
    return false;
}
