// Decode an RLE row, depth-test each opaque pixel with its signed adjustment,
// and translate it through the alpha row. Both auxiliary pointers wrap in their rings.
#include "shared/rle_alpha_depth.hpp"
#include "shared/blit.hpp"
// @ref ?ZBufferPtr@@3PAVZBuffer@@A=008315b4
// @ref ?ABufferPtr@@3PAVABuffer@@A=00839c6c
template <>
void RLEBlitTransXlatAlphaZReadWrite<unsigned short>::Blit(void *target, void const *source, int length, int skip,
                                                    int depth, int depth_buffer, int buffer, int level, int, int adjustments) const
{
    unsigned char const *input = (unsigned char const *)source;
    unsigned short *dest = (unsigned short *)target;
    unsigned short *alpha = (unsigned short *)buffer;
    char const *delta = (char const *)adjustments;
    unsigned short *depth_ptr = (unsigned short *)depth_buffer;
    int row = level > 0 ? level : 0;
    row = (int)((unsigned int)row * 261u) >> 11;
    if (row > 254) row = 254;
    unsigned short const *table = AlphaTable[row];
    if (skip > 0) {
        skip=Skip_RLE_Pixels(input,skip);
        skip = -skip;
        dest += skip;
        depth_ptr = (unsigned short *)depth_buffer + skip;
        length -= skip;
        depth_ptr = ABufferPtr->Wrap_Pointer(depth_ptr);
        alpha += skip;
        alpha = ZBufferPtr->Wrap_Pointer(alpha);
    }
    while (length > 0) {
        unsigned char color = *input++;
        if (color == 0) {
            color = *input++;
            length -= color;
            dest += color;
            delta += color;
            depth_ptr += color;
            alpha += color;
        } else {
            if (depth - *delta < *depth_ptr) {
                unsigned int translated = table[*alpha];
                *dest++ = Palette[translated | color];
                *depth_ptr++ = (unsigned short)(depth - *delta);
                ++delta; --length;
            } else {
                ++delta; ++dest; ++depth_ptr; --length;
            }
            ++alpha;
        }
        depth_ptr = ABufferPtr->Wrap_Pointer(depth_ptr);
        alpha = ZBufferPtr->Wrap_Pointer(alpha);
    }
}
