// int TerrainClass::unknown_slot101(...) (0x006E3CB0; ret 0x14)
// Whether the terrain object may stand in a cell: 0 when every cell of its
// occupation list (offsets from the cell, ended by 0x7FFF, 0x7FFF) accepts
// it, 7 when one does not (hypothesis: Can_Enter_Cell's MOVE_OK / MOVE_NO).
// Water-bound types ask with speed type 5, the others with 1. arg1 is the
// cell (its coordinates at +0x24); the other arguments are unused.
#include "shared/terrain.hpp"
#include "shared/map_view.hpp"
// @ref ?Unknown_004718B0@UnknownPlacementCellView@@QAE_NHPBVTechnoTypeClass@@PAVHouseClass@@@Z=004718b0
struct UnknownTerrainCellArg {
    char unknown_00[0x24];
    Cell MapCoords;                   // +0x24
};

static inline bool Is_List_End(Cell const *offset)
{
    return offset->X == 0x7FFF && offset->Y == 0x7FFF;
}

int TerrainClass::unknown_slot101(int arg1, int arg2, int arg3, int arg4, int arg5)
{
    Cell const *offset = unknown_slot64(0);
    Cell cell = ((UnknownTerrainCellArg *)arg1)->MapCoords;
    while (!Is_List_End(offset)) {
        if (Class->WaterBound) {
            if (!((UnknownPlacementCellView &)Map[*offset++ + cell]).Unknown_004718B0(5, 0, 0)) {
                return 7;
            }
        } else {
            if (!((UnknownPlacementCellView &)Map[*offset++ + cell]).Unknown_004718B0(1, 0, 0)) {
                return 7;
            }
        }
    }
    return 0;
}
