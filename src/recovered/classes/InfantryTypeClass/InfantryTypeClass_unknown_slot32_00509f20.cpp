// bool InfantryTypeClass::unknown_slot32(Cell const &cell, HouseClass *house) const (0x00509F20)
// Places a new infantry of this type for the house at the nearest free spot
// of the cell, facing 0x40; deletes it when the cell has no room.
#include "shared/infantry_type.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ??0InfantryClass@@QAE@PAVInfantryTypeClass@@PAVHouseClass@@@Z=004ff640
// @ref ?Closest_Free_Spot@UnknownPlacementCellView@@QBE?AUCoordStruct@@ABU2@_N1@Z=004764b0
// @ref ?unknown_invalid_coord_a41170@@3UCoordStruct@@B=00a41170

// The "no coordinate" value (0x00A41170; hypothesis).
extern CoordStruct const unknown_invalid_coord_a41170;

// Whether a coordinate is not the "no coordinate" value.
static inline bool Is_Valid(CoordStruct const &coord)
{
    return coord.X != unknown_invalid_coord_a41170.X || coord.Y != unknown_invalid_coord_a41170.Y
        || coord.Z != unknown_invalid_coord_a41170.Z;
}

bool InfantryTypeClass::unknown_slot32(Cell const &cell, HouseClass *house) const
{
    InfantryClass *infantry = new InfantryClass(const_cast<InfantryTypeClass *>(this), house);
    if (infantry != 0) {
        CoordStruct coord(cell.X * 256 + 128, cell.Y * 256 + 128, 0);
        CoordStruct spot = ((UnknownPlacementCellView &)Map[coord]).Closest_Free_Spot(coord);
        if (Is_Valid(spot)) {
            return infantry->unknown_slot53(&spot, 0x40);
        }
        delete infantry;
    }
    return false;
}
