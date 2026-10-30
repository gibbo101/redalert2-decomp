// UnknownPathEstimator::Unknown_0042A770() (0x0042A770): whether a subzone
// pair is in a layer's list.
#include "shared/path_estimator.hpp"

bool UnknownPathEstimator::Unknown_0042A770(unsigned short first, unsigned short second, int layer)
{
    if (second < first) {
        unsigned short swap = first;
        first = second;
        second = swap;
    }
    unsigned key = ((unsigned)first << 16) | second;
    DynamicVectorClass<unsigned int> &list = unknown_74[layer];
    for (int index = list.Count() - 1; index >= 0; index--) {
        if (list[index] == key) {
            return true;
        }
    }
    return false;
}
