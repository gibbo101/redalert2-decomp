// void BuildingClass::unknown_44dfc0(int dir) 0x0044DFC0 (TibSun building.cpp Connect_Laser_Fence):
// fills the gap toward the friendly post in dir (0x0044DDB0) with laser fence sections cell by cell,
// tearing the run down (0x0044E260) when one cannot be placed, then burns tiberium and veins under it.
#include "shared/building.hpp"
#include "shared/cell_class.hpp"
#include "shared/building_type_list.hpp"
#ifndef RA2_ADJACENT_CELL
#define RA2_ADJACENT_CELL
#include "shared/adjacent_cell.hpp"
inline Cell Adjacent_Cell(Cell const &cell, int facing)
{
    Cell const &offset = AdjacentCell[facing & 7];
    return Cell(cell.X + offset.X, cell.Y + offset.Y);
}
#endif
// @ref ?unknown_a40774@@3HA=00a40774
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70
// @ref ?BuildingTypes@@3V?$DynamicVectorClass@PAVBuildingTypeClass@@@@A=00a35cd8
void BuildingClass::unknown_44dfc0(int dir)
{
    BuildingClass *building;

    if (!unknown_a40774 && Type->LaserFencePost) {
        int range;
        if (Type->LaserFencePost) {
            range = Type->GuardRange.Value >> 8;
            range = range > 1 ? range : 1;
        } else {
            range = 1;
        }

        BuildingClass *post = unknown_44ddb0(dir, false, -1);
        if (post != 0 && post->unknown_slot91() != 19) {
            int fenceid;
            for (fenceid = 0; fenceid < BuildingTypes.Count(); fenceid++) {
                if (BuildingTypes[fenceid]->LaserFence) {
                    break;
                }
            }

            if (fenceid < BuildingTypes.Count()) {
                bool connected = false;
                Cell working_cell = Cell(Center_Coord());
                while (range > 0) {
                    working_cell = Adjacent_Cell(Cell(working_cell.X, working_cell.Y), dir);
                    building = (BuildingClass *)Map[working_cell].unknown_4717b0();
                    if (building == post) {
                        connected = true;
                        break;
                    }

                    building = (BuildingClass *)BuildingTypes[fenceid]->unknown_slot35(Owning_House());
                    if (!building->unknown_slot53(&CoordStruct(working_cell), Dir_To_256(Facing_Dir(dir & 3)))) {
                        delete building;
                        break;
                    }
                }
                if (!connected) {
                    unknown_44e260(dir, false);
                    return;
                }

                working_cell = Cell(Center_Coord());
                    do {
                        CellClass *cptr = &Map[working_cell];
                        if (cptr->Get_Tiberium_Type() != -1) {
                            cptr->unknown_475db0(12);
                        }
                        if (cptr->OverlayIndex == 0x7E) {
                            cptr->unknown_47c040();
                        }
                        working_cell = Cell(static_cast<TPoint2D<short> const &>(AdjacentCell[dir & 7]).operator+(working_cell));
                        building = (BuildingClass *)Map[working_cell].unknown_4717b0();
                    } while (building != post);
            }
        }
    }
}

// External names checked against complete original operands.
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70
// @ref ?BuildingTypes@@3V?$DynamicVectorClass@PAVBuildingTypeClass@@@@A=00a35cd8
// @ref ?Get_Tiberium_Type@CellClass@@QBEHXZ=0047a220
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_44ddb0@BuildingClass@@QAEPAV1@H_NH@Z=0044ddb0
// @ref ?unknown_44e260@BuildingClass@@QAEXH_N@Z=0044e260
// @ref ?unknown_4717b0@CellClass@@QBEPAVObjectClass@@XZ=004717b0
// @ref ?unknown_475db0@CellClass@@QAEHH@Z=00475db0
// @ref ?unknown_47c040@CellClass@@QAEHXZ=0047c040
// @ref ?unknown_a40774@@3HA=00a40774
