// Translate every source index through the palette and the selected alpha lookup row.
#include "shared/plain_xlat_alpha_blitter.hpp"
#include "shared/blit.hpp"
// @ref ?ZBufferPtr@@3PAVZBuffer@@A=008315b4
template <>
void BlitPlainXlatAlpha<unsigned short>::BlitForward(void *target, void const *source, int length,
                                                   int, int, int buffer, int level, int) const
{
    unsigned short *alpha = (unsigned short *)buffer;
    int row = level > 0 ? level : 0;
    row = (row * 261) >> 11;
    if (row > 254) row = 254;
    unsigned short const *table = AlphaTable[row];
    if (length > 0) {
        unsigned char const *input = (unsigned char const *)source;
        unsigned short *dest = (unsigned short *)target;
        int count = length;
        do {
            unsigned char color = *input++;
            unsigned int value = *alpha++;
            *dest++ = Palette[table[value] | color];
            alpha = ZBufferPtr->Wrap_Pointer(alpha);
        } while (--count);
    }
}
