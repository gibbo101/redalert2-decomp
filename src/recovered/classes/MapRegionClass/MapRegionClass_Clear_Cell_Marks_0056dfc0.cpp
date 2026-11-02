// void MapRegionClass::Clear_Cell_Marks_0056dfc0() (0x0056DFC0, static): sets every generation cell's +0x3C
// field to -1.
#include "shared/map_region.hpp"

void MapRegionClass::Clear_Cell_Marks_0056dfc0()
{
    int count = unknown_map_cell_side_84e804 * unknown_map_cell_side_84e804;
    for (int i = 0; i < count; i++) {
        unknown_map_cells_a70a24[i].unknown_3c = -1;
    }
}
