// UnknownPathEstimator::Unknown_00427E90() (0x00427E90): starts a new search.
#include "shared/path_estimator.hpp"
#include "shared/map_view.hpp"
#include "shared/map_region.hpp"

void UnknownPathEstimator::Unknown_00427E90()
{
    unknown_0c->entries[0xFFFF].unknown_14 = 0;
    unknown_10->entries[0xFFFF].unknown_0c = 0;
    unknown_14->Clear();
    unknown_68->Clear();
    if (++unknown_28 == 0) {
        for (int index = unknown_map_cell_side_84e804 * unknown_map_cell_side_84e804 - 1; index >= 0; index--) {
            unknown_18[index] = 0;
            unknown_1c[index] = 0;
        }
        for (int layer = 0; layer < 3; layer++) {
            int size = Map.unknown_70[layer];
            int *first = unknown_40[layer];
            int *second = unknown_4c[layer];
            int *third = unknown_58[layer];
            for (int entry = size - 1; entry >= 0; entry--) {
                first[entry] = 0;
                second[entry] = 0;
                third[entry] = 0;
            }
        }
        unknown_28++;
    }
}
