// Byte-output translation; class naming hypothesis documented in the shared header.
#include "shared/basic_lucent_blitters.hpp"
template <>
void BlitTransLucent75<unsigned short>::BlitForward(void *target, void const *source, int length,
                                      int, int, int, int, int) const
{
    if (length > 0) {
        int count = length;
        do {
            unsigned char color = *(unsigned char const *)source;
            source = (unsigned char const *)source + 1;
            if (color) {
                *(unsigned short *)target = (unsigned short)((Palette[color] >> 2 & ChannelMask) + (*(unsigned short *)target >> 2 & ChannelMask) * 3);
            }
            target = (unsigned short *)target + 1;
        } while (--count);
    }
}
