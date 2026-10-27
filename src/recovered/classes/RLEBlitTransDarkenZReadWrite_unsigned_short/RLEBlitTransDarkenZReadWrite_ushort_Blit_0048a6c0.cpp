// Decode an RLE row, depth-test each opaque pixel with its signed adjustment,
// and write depth after the pixel store. The depth cursor wraps in its ring.
#include "shared/rle_remaining_writers.hpp"
#include "shared/blit.hpp"
// @ref ?ZBufferPtr@@3PAVZBuffer@@A=008315b4
// @ref ?ABufferPtr@@3PAVABuffer@@A=00839c6c
template <>
void RLEBlitTransDarkenZReadWrite<unsigned short>::Blit(void *target, void const *source, int length, int skip,
                                                    int depth, int depth_buffer, int buffer, int level, int, int adjustments) const
{
    unsigned char const *input = (unsigned char const *)source;
    unsigned short *dest = (unsigned short *)target;
    char const *delta = (char const *)adjustments;
    unsigned short *depth_ptr = (unsigned short *)depth_buffer;
    if (skip > 0) {
        skip=Skip_RLE_Pixels(input,skip);
        skip = -skip;
        dest += skip;
        depth_ptr = (unsigned short *)depth_buffer + skip;
        length -= skip;
        depth_ptr = ABufferPtr->Wrap_Pointer(depth_ptr);
    }
    while (length > 0) {
        unsigned char color = *input++;
        if (color == 0) {
            color = *input++;
            length -= color;
            dest += color;
            delta += color;
            depth_ptr += color;
        } else {
            Write_Depth_Checked_Pixel(dest, depth_ptr, delta, depth, color, length);
        }
        depth_ptr = ABufferPtr->Wrap_Pointer(depth_ptr);
    }
}
