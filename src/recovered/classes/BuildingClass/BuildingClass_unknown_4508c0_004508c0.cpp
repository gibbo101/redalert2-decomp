// int BuildingClass::unknown_4508c0() (0x004508C0)
// A mask with bit (facing / 2) set for each of the four orthogonal
// neighbours (facings 0, 2, 4, 6) whose cell holds an active FirestormWall
// building that is not selected out.
#include "shared/building.hpp"
#include "shared/gscreen.hpp"
#include "shared/techno_map.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_00476AC0@UnknownCellClass@@QAEPAV1@H@Z=00476ac0
// @ref ?Unknown_004717B0@UnknownCellClass@@QAEPAVBuildingClass@@XZ=004717b0

int BuildingClass::unknown_4508c0()
{
    int mask = 0;
    CoordStruct coord = Coord;
    UnknownCellClass *cell = Map_Cell(coord);
    for (int facing = 0; facing < 8; facing += 2) {
        BuildingClass *building = cell->Unknown_00476AC0(facing)->Unknown_004717B0();
        if (building && building->Type->FirestormWall && !building->unknown_76 && building->unknown_7d) {
            mask |= 1 << (facing >> 1);
        }
    }
    return mask;
}
