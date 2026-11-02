// void MapRegionClass::Reassign_Cells_0056ea20(int region, int value) (0x0056EA20): moves every generation cell of
// this region to region (clearing its +0x4B byte), clears the map cell's IsoTileIndex and +0x11A byte, sets its
// +0x11B byte to value unless value is -1, and empties this region's cell count.
#include "shared/map_region.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"

void MapRegionClass::Reassign_Cells_0056ea20(int region, int value)
{
    int count = unknown_map_cell_side_84e804 * unknown_map_cell_side_84e804;
    for (int i = 0; i < count; i++) {
        if (unknown_map_cells_a70a24[i].RegionIndex == Index) {
            unknown_map_cells_a70a24[i].RegionIndex = region;
            unknown_map_cells_a70a24[i].unknown_4b = 0;
            Cell position = unknown_map_cells_a70a24[i].Position;
            CellClass &cell = Map[position];
            cell.IsoTileIndex = 0;
            cell.unknown_11a = 0;
            if (value != -1) {
                cell.unknown_11b = (char)value;
            }
        }
    }
    CellCount = 0;
}
