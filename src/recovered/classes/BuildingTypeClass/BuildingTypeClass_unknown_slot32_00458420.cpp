// bool BuildingTypeClass::unknown_slot32(Cell const &cell, HouseClass *house) const (0x00458420)
// Places a new building of this type for the house at the cell's centre.
#include "shared/building_type.hpp"
#include "shared/building_view.hpp"
// @ref ??0BuildingClass@@QAE@PAVBuildingTypeClass@@PAVHouseClass@@@Z=00438ce0

bool BuildingTypeClass::unknown_slot32(Cell const &cell, HouseClass *house) const
{
    BuildingClass *building = new BuildingClass(const_cast<BuildingTypeClass *>(this), house);
    if (building != 0) {
        CoordStruct coord(cell.X * 256 + 128, cell.Y * 256 + 128, 0);
        return building->unknown_slot53(&coord, 0);
    }
    return false;
}
