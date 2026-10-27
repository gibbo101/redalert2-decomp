// RLE transparent translation with a selected alpha lookup row and a wrapping buffer.
#include "shared/rle_blitter.hpp"
#include "shared/blit.hpp"
// @ref ?ZBufferPtr@@3PAVZBuffer@@A=008315b4
template <>
void RLEBlitTransXlatAlpha<unsigned short>::Blit(void *target, void const *source, int length, int skip,
                                                int, int, int buffer, int level, int, int) const
{
    unsigned char const *input = (unsigned char const *)source;
    unsigned short *dest = (unsigned short *)target;
    unsigned short *alpha = (unsigned short *)buffer;
    int row = level > 0 ? level : 0;
    row = (row * 261) >> 11;
    if (row > 254) row = 254;
    unsigned short const *table = AlphaTable[row];
    if (skip > 0) {
        do {
            if (*input++ == 0) skip -= *input++;
            else skip--;
        } while (skip > 0);
        skip = -skip;
        length -= skip;
        alpha = (unsigned short *)buffer + skip;
        dest += skip;
        alpha = ZBufferPtr->Wrap_Pointer(alpha);
    }
    while (length > 0) {
        unsigned char color = *input++;
        if (color == 0) {
            color = *input++;
            length -= color;
            dest += color;
            alpha += color;
        } else {
            unsigned int translated = table[*alpha];
            *dest++ = Palette[translated | color];
            length--;
            alpha++;
        }
        alpha = ZBufferPtr->Wrap_Pointer(alpha);
    }
}
