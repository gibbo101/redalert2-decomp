// void MapRegionClass::Set_Unassigned_Regions_0056e910(bool flag) (0x0056E910, static __fastcall): creates a
// region for every real generation cell that has none yet (RegionIndex -1) and sets each new region's +0x1A flag.
#include "shared/map_region.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
// @ref ?unknown_map_cell_side_84e804@@=0084e804
// @ref ?unknown_map_cells_a70a24@@=00a70a24
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Create_Region_From_Cell_0056e100@MapRegionClass@@SIPAV1@PAVCellClass@@@Z=0056e100

void __fastcall MapRegionClass::Set_Unassigned_Regions_0056e910(bool flag)
{
    int count = unknown_map_cell_side_84e804 * unknown_map_cell_side_84e804;
    for (int i = 0; i < count; i++) {
        UnknownMapGenerationCell &cell = unknown_map_cells_a70a24[i];
        if (cell.RegionIndex == -1 && (cell.Position.X != 0 || cell.Position.Y != 0)) {
            MapRegionClass *region = Create_Region_From_Cell_0056e100(&Map[cell.Position]);
            if (region) {
                region->unknown_1a = flag;
            }
        }
    }
}
