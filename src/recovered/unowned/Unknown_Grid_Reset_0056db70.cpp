#include "shared/map_region.hpp"
// @ref ?unknown_map_cell_side_84e804@@=0084e804
// @ref ?unknown_map_cells_a70a24@@=00a70a24
// Original repeatedly clears the SAME side*side indexed byte; no corrected traversal is inferred.
void Unknown_Grid_Reset_0056db70()
{
    int count = (int)((unsigned)unknown_map_cell_side_84e804 * (unsigned)unknown_map_cell_side_84e804);
    int index = count;
    while (count > 0) {
        unknown_map_cells_a70a24[index].unknown_45[0] = 0;
        --count;
    }
}
