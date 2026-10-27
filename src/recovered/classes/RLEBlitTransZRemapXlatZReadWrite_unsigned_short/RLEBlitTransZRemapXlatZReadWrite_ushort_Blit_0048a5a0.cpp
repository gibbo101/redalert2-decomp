// Snapshot the shared remap once, then translate visible RLE pixels after a depth test.
// Opaque writes consume two signed adjustment bytes; zero runs consume one per skipped pixel.
#include "shared/rle_remap_depth.hpp"
#include "shared/blit.hpp"
// @ref ?ABufferPtr@@3PAVABuffer@@A=00839c6c
template <>
void RLEBlitTransZRemapXlatZReadWrite<unsigned short>::Blit(void *target, void const *source, int length, int skip,
                      int depth, int depth_buffer, int, int, int, int adjustment) const
{
    unsigned char const *input = (unsigned char const *)source;
    char const *delta = (char const *)adjustment;
    unsigned short *output=(unsigned short *)target;
    unsigned char const *remap=*RemapTable;
    unsigned short *depth_ptr = (unsigned short *)depth_buffer;
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
            if (depth - *delta++ < *depth_ptr) {
                *output++ = Palette[remap[color]];
                *depth_ptr++=(unsigned short)(depth-*delta++);
                --length;
            } else {
                ++delta;
                output=(unsigned short *)output+1;
                ++depth_ptr; --length;
            }
        }
        depth_ptr = ABufferPtr->Wrap_Pointer(depth_ptr);
    }
}
