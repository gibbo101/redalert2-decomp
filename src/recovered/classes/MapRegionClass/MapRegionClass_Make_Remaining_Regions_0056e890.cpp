// void MapRegionClass::Make_Remaining_Regions_0056e890() (0x0056E890, static): creates a region for every real
// generation cell still without one (RegionIndex -1) whose map cell passes unknown_47b7e0 or unknown_47b9c0.
#include "shared/map_region.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
// @ref ?Create_Region_From_Cell_0056e100@MapRegionClass@@=0056e100
// @ref ?unknown_47b7e0@CellClass@@QBE_NXZ=0047b7e0
// @ref ?unknown_47b9c0@CellClass@@QBE_NXZ=0047b9c0

void MapRegionClass::Make_Remaining_Regions_0056e890()
{
    int count = unknown_map_cell_side_84e804 * unknown_map_cell_side_84e804;
    for (int i = 0; i < count; i++) {
        Cell position = unknown_map_cells_a70a24[i].Position;
        CellClass &cell = Map[position];
        if (unknown_map_cells_a70a24[i].RegionIndex == -1
            && (unknown_map_cells_a70a24[i].Position.X != 0 || unknown_map_cells_a70a24[i].Position.Y != 0)
            && (cell.unknown_47b7e0() || cell.unknown_47b9c0())) {
            Create_Region_From_Cell_0056e100(&cell);
        }
    }
}
