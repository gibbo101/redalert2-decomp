// UnknownPathEstimator::Unknown_00427F70() (0x00427F70): whether a cell index is
// marked in the current generation.
#include "shared/path_estimator.hpp"

bool UnknownPathEstimator::Unknown_00427F70(int unused, bool first, int index)
{
    if (first) {
        if (unknown_18[index] == unknown_28) return true;
        return false;
    }
    if (unknown_1c[index] == unknown_28) return true;
    return false;
}
