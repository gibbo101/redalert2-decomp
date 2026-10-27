// Random3Class::operator()(int minval, int maxval) (0x006389D0)
// A random number in [minval, maxval].
#include "shared/random.hpp"

int Random3Class::operator()(int minval, int maxval)
{
    return Pick_Random_Number(*this, minval, maxval);
}
