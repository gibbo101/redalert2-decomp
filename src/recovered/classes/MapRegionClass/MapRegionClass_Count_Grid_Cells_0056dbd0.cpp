#include "shared/map_region.hpp"
// @ref ?unknown_map_cell_side_84e804@@=0084e804
// @ref ?unknown_map_cells_a70a24@@=00a70a24
void MapRegionClass::Count_Grid_Cells_0056dbd0()
{
    CellCount = 0;
    int count = (int)((unsigned)unknown_map_cell_side_84e804 * (unsigned)unknown_map_cell_side_84e804);
    for (int i = 0; i < count; ++i) {
        UnknownMapGenerationCell &cell = unknown_map_cells_a70a24[i];
        if (cell.RegionIndex == Index && (cell.Position.X != 0 || cell.Position.Y != 0)) {
            CellCount = (int)((unsigned)CellCount + 1u);
        }
    }
}
