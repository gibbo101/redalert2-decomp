// UnknownPathEstimator::Unknown_004284E0() (0x004284E0): sizes the cell marks
// and the facing offsets for the map rectangle.
#include "shared/path_estimator.hpp"
// Shared map-grid dimension; this pathfinding routine needs no MapRegionClass layout.
extern int unknown_map_cell_side_84e804;

void UnknownPathEstimator::Unknown_004284E0(Rect const &size)
{
    if (unknown_18) {
        delete unknown_18;
        unknown_18 = 0;
    }
    if (unknown_1c) {
        delete unknown_1c;
        unknown_1c = 0;
    }
    if (unknown_24) {
        delete unknown_24;
        unknown_24 = 0;
    }
    if (unknown_20) {
        delete unknown_20;
        unknown_20 = 0;
    }
    unknown_map_cell_side_84e804 = size.Width + size.Height + 1;
    int count = unknown_map_cell_side_84e804 * unknown_map_cell_side_84e804;
    unknown_1c = new int[count];
    unknown_18 = new int[count];
    unknown_24 = new float[count];
    unknown_20 = new float[count];
    unknown_path_facing_offsets_84c838[0] = -unknown_map_cell_side_84e804;
    unknown_path_facing_offsets_84c838[1] = 1 - unknown_map_cell_side_84e804;
    unknown_path_facing_offsets_84c838[2] = 1;
    unknown_path_facing_offsets_84c838[3] = unknown_map_cell_side_84e804 + 1;
    unknown_path_facing_offsets_84c838[4] = unknown_map_cell_side_84e804;
    unknown_path_facing_offsets_84c838[5] = unknown_map_cell_side_84e804 - 1;
    unknown_path_facing_offsets_84c838[6] = -1;
    unknown_path_facing_offsets_84c838[7] = -1 - unknown_map_cell_side_84e804;
}
