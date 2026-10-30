// UnknownPathEstimator::Unknown_0042A7D0() (0x0042A7D0): records a subzone
// pair in a layer's list.
#include "shared/path_estimator.hpp"

void UnknownPathEstimator::Unknown_0042A7D0(unsigned first, unsigned second, int layer)
{
    if (first == second) {
        return;
    }
    if (second < first) {
        unsigned swap = second;
        second = first;
        first = swap;
    }
    unknown_74[layer].Add((first << 16) | second);
}
