#include "shared/map_region.hpp"
// @ref ?unknown_map_cell_side_84e804@@=0084e804
// @ref ?unknown_map_cells_a70a24@@=00a70a24
void MapRegionClass::Count_Grid_Cells_0056dbd0()
{
    CellCount = 0;
    int count = unknown_map_cell_side_84e804 * unknown_map_cell_side_84e804;
    for (int i = 0; i < count; i++) {
        if (unknown_map_cells_a70a24[i].RegionIndex == Index && unknown_map_cells_a70a24[i].Position != Cell(0, 0)) {
            CellCount++;
        }
    }
}
