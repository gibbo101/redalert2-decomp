// Byte-output translation; class naming hypothesis documented in the shared header.
#include "shared/basic_xlat_blitters.hpp"
template <>
void BlitTransZRemapXlat<unsigned short>::BlitForward(void *target, void const *source, int length,
                                      int, int, int, int, int) const
{
    unsigned char const *remap = *RemapTable;
    if (length > 0) {
        int count = length;
        do {
            unsigned char color = *(unsigned char const *)source;
            source = (unsigned char const *)source + 1;
            if (color) {
                *(unsigned short *)target = Palette[remap[color]];
            }
            target = (unsigned short *)target + 1;
        } while (--count);
    }
}
