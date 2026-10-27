// Skip the clipped left portion of an RLE row, then translate its visible nonzero pixels.
#include "shared/byte_rle_blitters.hpp"
template <>
void RLEBlitTransZRemapXlat<unsigned short>::Blit(void *target, void const *source, int length, int skip,
                                          int, int, int, int, int, int) const
{
    int pixels_to_skip = skip;
    unsigned short *dest = (unsigned short *)target;
    unsigned char const *input = (unsigned char const *)source;
    unsigned char const *remap = *RemapTable;
    if (pixels_to_skip > 0) {
        pixels_to_skip = Skip_RLE_Pixels(input, pixels_to_skip);
        pixels_to_skip = -pixels_to_skip;
        dest += pixels_to_skip;
        length -= pixels_to_skip;
    }
    while (length > 0) {
        unsigned char color = *input++;
        if (color == 0) {
            color = *input++;
            length -= color;
            dest += color;
        } else {
            *dest++ = Palette[remap[color]];
            length--;
        }
    }
}
