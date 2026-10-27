// RandomClass::operator()(int minval, int maxval) (0x00638720)
// A random number in [minval, maxval].
#include "shared/random.hpp"

int RandomClass::operator()(int minval, int maxval)
{
    return Pick_Random_Number(*this, minval, maxval);
}
