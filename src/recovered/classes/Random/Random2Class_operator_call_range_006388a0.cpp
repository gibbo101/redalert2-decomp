// Random2Class::operator()(int minval, int maxval) (0x006388A0)
// A random number in [minval, maxval].
#include "shared/random.hpp"

int Random2Class::operator()(int minval, int maxval)
{
    return Pick_Random_Number(*this, minval, maxval);
}
