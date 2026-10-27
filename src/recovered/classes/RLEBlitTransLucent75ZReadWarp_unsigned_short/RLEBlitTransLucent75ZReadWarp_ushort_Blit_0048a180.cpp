// Blend packed RLE pixels after a signed adjustment/depth test; no depth writes.
// Zero runs advance output, adjustment and depth; left clipping leaves adjustment unchanged.
#include "shared/rle_lucent_depth.hpp"
#include "shared/blit.hpp"
// @ref ?ABufferPtr@@3PAVABuffer@@A=00839c6c
template <>
void RLEBlitTransLucent75ZReadWarp<unsigned short>::Blit(void *target, void const *source, int length, int skip,
                      int depth, int depth_buffer, int, int, int warp_offset, int adjustment) const
{
    unsigned short *depth_ptr = (unsigned short *)depth_buffer;
    unsigned short *output=(unsigned short *)target;
    char const *delta = (char const *)adjustment;
    unsigned char const *input = (unsigned char const *)source;
    if (skip > 0) {
        skip = Skip_RLE_Pixels(input, skip);
        skip = -skip;
        output = (unsigned short *)output + skip;
        length -= skip;
        depth_ptr = (unsigned short *)depth_buffer + skip;
        depth_ptr = ABufferPtr->Wrap_Pointer(depth_ptr);
    }
    while (length > 0) {
        unsigned char color = *input++;
        if (color == 0) {
            color = *input++;
            length -= color;
            output = (unsigned short *)output + color;
            delta += color;
            depth_ptr += color;
        } else {
            if (depth - *delta++ < *depth_ptr++) {
                unsigned short previous=output[warp_offset];
                *output++ = ((Palette[color] >> 2) & ChannelMask) + ((previous >> 2) & ChannelMask) * 3;
                --length;
            } else {
                ++output; --length;
            }
        }
        depth_ptr = ABufferPtr->Wrap_Pointer(depth_ptr);
    }
}
