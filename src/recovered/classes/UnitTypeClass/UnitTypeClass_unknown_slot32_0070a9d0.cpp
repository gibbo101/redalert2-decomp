// bool UnitTypeClass::unknown_slot32(Cell const &cell, HouseClass *house) const (0x0070A9D0)
// Places a new vehicle of this type for the house at the cell centre, facing a
// random direction (RA1: Create_And_Place).
#include "shared/unit_type.hpp"
#include "shared/object.hpp"
#include "shared/id_source.hpp"
#include "shared/facing.hpp"
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0UnitClass@@QAE@PAVUnitTypeClass@@PAVHouseClass@@@Z=006fa400
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ??RRandom2Class@@QAEHXZ=00638840

bool UnitTypeClass::unknown_slot32(Cell const &cell, HouseClass *house) const
{
    ObjectClass *unit = (ObjectClass *)new UnitClass((UnitTypeClass *)this, house);
    if (unit != 0) {
        // A random facing in the direction's high byte (the 32-bit value
        // is rewritten, as the Dir_To_* readers read it).
        UnknownFacingDir dir(0);
        *(unsigned *)&dir = (*(unsigned *)&dir & 0xFFFF00FF) | ((unknown_id_source_a3d290->Random()() & 0xFF) << 8);
        CoordStruct coord(cell.X * 256 + 128, cell.Y * 256 + 128, 0);
        return unit->unknown_slot53(&coord, Dir_To_256(dir));
    }
    return false;
}
