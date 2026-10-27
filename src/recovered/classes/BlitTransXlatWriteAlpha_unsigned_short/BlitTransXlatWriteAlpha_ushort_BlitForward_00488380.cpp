// Store clamped source-index-plus-level values for nonzero pixels, wrapping the buffer ring.
#include "shared/xlat_alpha_blitter.hpp"
#include "shared/blit.hpp"
// @ref ?ZBufferPtr@@3PAVZBuffer@@A=008315b4
template <>
void BlitTransXlatWriteAlpha<unsigned short>::BlitForward(void *target, void const *source, int length,
                                                         int level, int, int buffer, int, int) const
{
    unsigned short *dest = (unsigned short *)buffer;
    if (length > 0) {
        int count = length;
        int base = level;
        do {
            unsigned char color = *(unsigned char const *)source;
            source = (unsigned char const *)source + 1;
            if (color) {
                *dest = (unsigned short)(color + base >= 255 ? 255 : color + base);
            }
            dest++;
            dest = ZBufferPtr->Wrap_Pointer(dest);
        } while (--count);
    }
}
