// Decode visible RLE pixels after a signed adjustment/depth test; no depth write.
#include "shared/basic_rle_depth_blitters.hpp"
#include "shared/blit.hpp"
// @ref ?ABufferPtr@@3PAVABuffer@@A=00839c6c
template <>
void RLEBlitTransXlatZRead<unsigned char>::Blit(void *target, void const *source, int length, int skip,
                      int depth, int depth_buffer, int, int, int, int adjustment) const
{
    unsigned short *depth_ptr = (unsigned short *)depth_buffer;
    char const *delta = (char const *)adjustment;
    unsigned char *output=(unsigned char *)target;
    unsigned char const *input = (unsigned char const *)source;
    if (skip > 0) {
        skip = Skip_RLE_Pixels(input, skip);
        skip = -skip;
        output = (unsigned char *)output + skip;
        length -= skip;
        depth_ptr = (unsigned short *)depth_buffer + skip;
        depth_ptr = ABufferPtr->Wrap_Pointer(depth_ptr);
    }
    while (length > 0) {
        unsigned char color = *input++;
        if (color == 0) {
            color = *input++;
            length -= color;
            output = (unsigned char *)output + color;
            depth_ptr += color;
            delta += color;
        } else {
            if (depth - *delta++ < *depth_ptr++) {
                *(unsigned char *)output = Palette[color];
                ++output;
                --length;
            } else {
                ++output; --length;
            }
        }
        depth_ptr = ABufferPtr->Wrap_Pointer(depth_ptr);
    }
}
