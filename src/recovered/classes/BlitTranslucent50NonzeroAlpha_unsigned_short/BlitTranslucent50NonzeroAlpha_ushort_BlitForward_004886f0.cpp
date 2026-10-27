// Half-blend a nonzero source pixel only when its alpha value satisfies the mask condition.
#include "shared/conditional_alpha_blitters.hpp"
#include "shared/blit.hpp"
// @ref ?ZBufferPtr@@3PAVZBuffer@@A=008315b4
template <>
void BlitTranslucent50NonzeroAlpha<unsigned short>::BlitForward(void *target, void const *source, int length,
                                       int, int, int buffer, int, int) const
{
    unsigned short *alpha = (unsigned short *)buffer;
    if (length > 0) {
        int count = length;
        do {
            unsigned char color = *(unsigned char const *)source;
            source = (unsigned char const *)source + 1;
            if (color && *alpha != 0) {
                *(unsigned short *)target = ((Palette[color] >> 1) & ChannelMask)
                                           + ((*(unsigned short *)target >> 1) & ChannelMask);
            }
            ++alpha;
            target = (unsigned short *)target + 1;
            alpha = ZBufferPtr->Wrap_Pointer(alpha);
        } while (--count);
    }
}
