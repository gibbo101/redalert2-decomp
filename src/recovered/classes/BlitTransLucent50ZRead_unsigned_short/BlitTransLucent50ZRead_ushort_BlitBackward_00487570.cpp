// Backward entry forwards through the virtual forward slot, with zero as the last argument.
#include "shared/basic_depth_blitters.hpp"
template <>
void BlitTransLucent50ZRead<unsigned short>::BlitBackward(void *target, void const *source, int length,
                                                         int a, int b, int c, int d) const
{
    BlitForward(target, source, length, a, b, c, d, 0);
}
