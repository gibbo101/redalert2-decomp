// Translate or darken the destination where the source is nonzero.
#include "shared/destination_blitters.hpp"
template <>
void BlitTransDarken<unsigned short>::BlitForward(void *target, void const *source, int length,
                              int, int, int, int, int) const
{
    if (length > 0) {
        int count = length;
        do {
            unsigned char color = *(unsigned char const *)source;
            source = (unsigned char const *)source + 1;
            if (color) *(unsigned short *)target = (*(unsigned short *)target >> 1) & ChannelMask;
            target = (unsigned short *)target + 1;
        } while (--count);
    }
}
