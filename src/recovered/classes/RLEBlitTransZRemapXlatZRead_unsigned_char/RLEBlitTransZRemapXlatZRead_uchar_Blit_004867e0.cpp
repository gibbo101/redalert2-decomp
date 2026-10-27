// Snapshot the shared remap once, then translate visible RLE pixels after a depth test.
// Opaque reads consume one signed adjustment byte; zero runs advance all three cursors.
#include "shared/rle_remap_depth.hpp"
#include "shared/blit.hpp"
// @ref ?ABufferPtr@@3PAVABuffer@@A=00839c6c
template <>
void RLEBlitTransZRemapXlatZRead<unsigned char>::Blit(void *target, void const *source, int length, int skip,
                      int depth, int depth_buffer, int, int, int, int adjustment) const
{
    unsigned char const *input = (unsigned char const *)source;
    char const *delta = (char const *)adjustment;
    unsigned char *output=(unsigned char *)target;
    unsigned char const *remap=*RemapTable;
    unsigned short *depth_ptr = (unsigned short *)depth_buffer;
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
            delta += color;
            depth_ptr += color;
        } else {
            if (depth - *delta++ < *depth_ptr++) {
                *(unsigned char *)output = Palette[remap[color]];
                ++output;
                --length;
            } else {
                ++output; --length;
            }
        }
        depth_ptr = ABufferPtr->Wrap_Pointer(depth_ptr);
    }
}
