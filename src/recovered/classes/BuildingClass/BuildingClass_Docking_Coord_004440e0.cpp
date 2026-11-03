// CoordStruct BuildingClass::unknown_slot41(int dock) const 0x004440E0 (slot 41; TibSun building.cpp
// Docking_Coord): a weeder's dock two cells right and one down of its position cell at its height, a
// refinery's half a cell right of the object's dock, and for a helipad or repair depot the docking
// offset of the contact's dock index (NumberOfDocks/DockingOffsets).
#include "shared/building.hpp"
// @ref ?unknown_slot41@ObjectClass@@UBE?AUCoordStruct@@H@Z=005d54f0
// @ref ?Unknown_00636E70@RadioClass@@QBEHPAVTechnoClass@@@Z=00636e70
// TibSun TPoint3D + TPoint3D (the docking offsets are TPoint3D<int>).
inline CoordStruct operator+(CoordStruct const &coord, TPoint3D<int> const &offset)
{
    return CoordStruct(coord.X + offset.X, coord.Y + offset.Y, coord.Z + offset.Z);
}
CoordStruct BuildingClass::unknown_slot41(int dock) const
{
    if (Type->Weeder) {
        Cell cell = unknown_slot104() + Cell(2, 1);
        CoordStruct coord = CoordStruct(cell);
        coord.Z = CoordStruct(Coord).Z;
        return coord;
    }
    if (Type->Refinery) {
        return ObjectClass::unknown_slot41(dock) + CoordStruct(128, 0, 0);
    }
    if (!Type->Helipad && !Type->UnitRepair) {
        return ObjectClass::unknown_slot41(dock);
    }
    switch (Type->NumberOfDocks) {
        case 0:
            return Center_Coord();

        case 1:
            return Center_Coord() + Type->DockingOffsets[0];

        default:
            {
                int index = Unknown_00636E70((TechnoClass *)dock);
                if (index >= 0 && index < Type->NumberOfDocks) {
                    return Center_Coord() + Type->DockingOffsets[index];
                }
            }
            return Center_Coord();
    }
}
