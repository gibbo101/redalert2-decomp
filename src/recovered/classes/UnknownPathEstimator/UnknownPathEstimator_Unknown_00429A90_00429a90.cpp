// UnknownPathEstimator::Unknown_00429A90() (0x00429A90): reallocates and
// clears the three layers' arrays.
#include "shared/path_estimator.hpp"
#include "shared/map_view.hpp"

void UnknownPathEstimator::Unknown_00429A90()
{
    for (int layer = 0; layer < 3; layer++) {
        if (unknown_40[layer]) {
            delete unknown_40[layer];
        }
        int *array = new int[Map.unknown_70[layer]];
        unknown_40[layer] = array;
        for (int entry = Map.unknown_70[layer] - 1; entry >= 0; entry--) {
            array[entry] = 0;
        }
        if (unknown_4c[layer]) {
            delete unknown_4c[layer];
        }
        array = new int[Map.unknown_70[layer]];
        unknown_4c[layer] = array;
        for (entry = Map.unknown_70[layer] - 1; entry >= 0; entry--) {
            array[entry] = 0;
        }
        if (unknown_58[layer]) {
            delete unknown_58[layer];
        }
        array = new int[Map.unknown_70[layer]];
        unknown_58[layer] = array;
        for (entry = Map.unknown_70[layer] - 1; entry >= 0; entry--) {
            array[entry] = 0;
        }
    }
}
