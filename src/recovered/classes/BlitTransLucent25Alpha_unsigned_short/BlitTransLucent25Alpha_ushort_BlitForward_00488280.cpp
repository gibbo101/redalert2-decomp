// Translate opaque indices through the alpha row and blend three quarters source, one quarter destination.
#include "shared/trans_lucent_alpha_blitter.hpp"
#include "shared/blit.hpp"
// @ref ?ZBufferPtr@@3PAVZBuffer@@A=008315b4
template <>
void BlitTransLucent25Alpha<unsigned short>::BlitForward(void *target, void const *source, int length,
                                                        int, int, int buffer, int level, int) const
{
    unsigned short *alpha = (unsigned short *)buffer;
    int row = level > 0 ? level : 0;
    row = (row * 261) >> 11;
    if (row > 254) row = 254;
    unsigned short const *table = AlphaTable[row];
    if (length > 0) {
        unsigned short *dest = (unsigned short *)target;
        int count = length;
        do {
            unsigned char color = *(unsigned char const *)source;
            source = (unsigned char const *)source + 1;
            if (color) {
                unsigned int translated = table[*alpha];
                *dest = ((Palette[translated | color] >> 2) & ChannelMask) * 3 + ((*dest >> 2) & ChannelMask);
            }
            alpha++;
            dest++;
            alpha = ZBufferPtr->Wrap_Pointer(alpha);
        } while (--count);
    }
}
